/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <folly/MoveWrapper.h>

#include "squangle/mysql_client/AsyncHelpers.h"
#include "squangle/mysql_client/ConnectOperation.h"
#include "squangle/mysql_client/Connection.h"
#include "squangle/mysql_client/MultiQueryOperation.h"
#include "squangle/mysql_client/Operation.h"
#include "squangle/mysql_client/QueryOperation.h"
#include "squangle/mysql_client/SemiFutureAdapter.h"

namespace facebook::common::mysql_client {

void handleConnectionCompletion(
    ConnectOperation& op,
    folly::Promise<ConnectResult>& promise) {
  auto conn = op.releaseConnection();
  if (op.ok()) {
    // succeeded, let's build the result
    promise.setValue(ConnectResult(
        std::move(conn),
        op.result(),
        op.getKey(),
        op.opElapsed(),
        op.attemptsMade()));
  } else {
    // failed - build the exception
    promise.setException(conn->client().exceptionBuilder().buildMysqlException(
        op.result(),
        op.mysql_errno(),
        op.mysql_error(),
        conn->getKey(),
        op.opElapsed()));
  }
}

folly::SemiFuture<ConnectResult> toSemiFuture(
    const ConnectOperation_ptr& conn_op) {
  folly::MoveWrapper<folly::Promise<ConnectResult>> promise;
  auto future = promise->getSemiFuture();

  conn_op->setCallback([promise](ConnectOperation& op) mutable {
    handleConnectionCompletion(op, *promise);
  });
  conn_op->run();
  return future;
}

template <typename ResultType, typename Operation, typename QueryResult>
void handleQueryCompletion(
    Operation& op,
    QueryResult query_result,
    QueryCallbackReason reason,
    folly::Promise<std::pair<ResultType, AsyncPostQueryCallback>>& promise) {
  auto conn = op.releaseConnection();
  // Make a copy of the connection key here because we move `conn` below.
  auto conn_key = conn->getKey();
  if (reason == QueryCallbackReason::Success) {
    ResultType result(
        std::move(query_result),
        op.numQueriesExecuted(),
        op.resultSize(),
        std::move(conn),
        op.result(),
        std::move(conn_key),
        op.opElapsed());
    promise.setValue(
        std::make_pair(std::move(result), op.stealPostQueryCallback()));
  } else {
    promise.setException(conn->client().exceptionBuilder().buildQueryException(
        op.numQueriesExecuted(),
        op.result(),
        op.mysql_errno(),
        op.mysql_error(),
        std::move(conn_key),
        op.opElapsed()));
  }
}

// Handle pre-query callbacks (if they exist)
template <typename Operation>
folly::SemiFuture<folly::Unit> handlePreQueryCallback(Operation& op) {
  // Use the pre-query callback if we have it, or else an empty SemiFuture
  auto optFut = op.callPreQueryCallback(op);
  if (optFut) {
    return std::move(*optFut);
  }

  return folly::makeSemiFuture(folly::unit);
}

// Handle setting up the promise, the callbacks when the query is finished and
// running the query
template <typename ResultType, typename Operation>
folly::SemiFuture<std::pair<ResultType, AsyncPostQueryCallback>> handleRunQuery(
    const std::shared_ptr<Operation>& op) {
  folly::MoveWrapper<
      folly::Promise<std::pair<ResultType, AsyncPostQueryCallback>>>
      promise;
  auto future = promise->getSemiFuture();

  op->chainCallback(resultAppender([promise](
                                       Operation& op,
                                       auto query_result,
                                       QueryCallbackReason reason) mutable {
    handleQueryCompletion<ResultType>(
        op, std::move(query_result), reason, *promise);
  }));
  op->run();
  return future;
}

// Handle running the post-query callbacks (if they exist).  The query result
// will be in the first field of the result pair while the callback will be in
// the second field of the pair.
template <typename ResultType>
folly::SemiFuture<ResultType> handlePostQueryCallback(
    std::pair<ResultType, AsyncPostQueryCallback>&& resultPair) {
  if (resultPair.second) {
    // If we have a callback set, wrap (and then unwrap) the
    // result to/from the callback's std::variant wrapper
    return resultPair.second(AsyncPostQueryResult(std::move(resultPair.first)))
        .deferValue([](AsyncPostQueryResult&& result) {
          return std::get<ResultType>(std::move(result));
        });
  }
  return folly::makeSemiFuture(std::move(resultPair.first));
}

// Convert the query operation into a semifuture, starting with the pre-query
// callbacks then the query then the post-query callbacks.
template <typename ResultType, typename Operation, typename QueryResult>
folly::SemiFuture<ResultType> toSemiFutureHelper(
    std::shared_ptr<Operation> op) {
  // Run pre-query callbacks
  auto sfut1 = handlePreQueryCallback<Operation>(*op);
  auto sfut2 = std::move(sfut1).deferValue(
      [=](auto&& /* unused */) { return handleRunQuery<ResultType>(op); });

  return std::move(sfut2).deferValue([op = std::move(op)](auto&& result) {
    // Pass `op` into this lambda to verify it's lifetime until we have handled
    // post query callbacks
    return handlePostQueryCallback<ResultType>(std::move(result));
  });
}

folly::SemiFuture<DbQueryResult> toSemiFuture(QueryOperation_ptr query_op) {
  return toSemiFutureHelper<DbQueryResult, QueryOperation, QueryResult>(
      std::move(query_op));
}

folly::SemiFuture<DbMultiQueryResult> toSemiFuture(
    MultiQueryOperation_ptr mquery_op) {
  return toSemiFutureHelper<
      DbMultiQueryResult,
      MultiQueryOperation,
      std::vector<QueryResult>>(std::move(mquery_op));
}

} // namespace facebook::common::mysql_client
