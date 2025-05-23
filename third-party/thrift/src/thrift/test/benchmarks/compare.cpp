/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <limits>
#include <random>

#include <folly/Benchmark.h>
#include <folly/init/Init.h>
#include <thrift/lib/cpp2/op/Compare.h>
#include <thrift/lib/cpp2/op/Get.h>
#include <thrift/test/benchmarks/gen-cpp2/compare_types.h>

namespace apache::thrift::test {

std::mt19937 rng;
constexpr int N = 20;
MyStruct structs[N];
MyUnion unions[N];

SubSubStruct subSubStruct;
SubStruct subStruct;
SubSubStruct diffSubSubStructs[N];
SubStruct diffSubStructs[N];
MyNestedStruct nestedStructs[N];

void init() {
  subSubStruct.subsubfield_1() = 4207849484;
  subSubStruct.subsubfield_2() = std::numeric_limits<long>::max();
  subSubStruct.subsubfield_3() = -3.5650879601311513E283;
  subSubStruct.subsubfield_4() = std::numeric_limits<double>::max();
  subSubStruct.subsubfield_5() = 251;
  subSubStruct.subsubfield_6() = std::numeric_limits<int>::max();
  subSubStruct.subsubfield_7() = true;

  op::for_each_ordinal<SubStruct>(
      [&]<class Ord>(Ord) { op::get<Ord>(subStruct) = subSubStruct; });

  for (int i = 0; i < N; ++i) {
    constexpr size_t size = op::size_v<MyStruct>;
    op::for_each_ordinal<MyStruct>([&]<class Ord>(Ord) {
      if (folly::to_underlying(Ord::value) == size) {
        // Make the last field different
        op::get<Ord>(structs[i]) = std::string(100, '0') + char(rng() % 10);
        op::get<Ord>(unions[i]) = std::string(100, '0') + char(rng() % 10);
      } else {
        op::get<Ord>(structs[i]) = std::string(100, '0');
      }
    });

    diffSubSubStructs[i].subsubfield_1() = 4207849484;
    diffSubSubStructs[i].subsubfield_2() = std::numeric_limits<long>::max();
    diffSubSubStructs[i].subsubfield_3() = -3.5650879601311513E283;
    diffSubSubStructs[i].subsubfield_4() = std::numeric_limits<double>::max();
    diffSubSubStructs[i].subsubfield_5() = 251;
    diffSubSubStructs[i].subsubfield_6() = std::numeric_limits<int>::max();
    diffSubSubStructs[i].subsubfield_7() = i % 2 == 0;

    op::for_each_ordinal<SubStruct>([&]<class Ord>(Ord) {
      if (folly::to_underlying(Ord::value) == op::size_v<SubStruct>) {
        // Make the last field different
        op::get<Ord>(diffSubStructs[i]) = diffSubSubStructs[i];
      } else {
        op::get<Ord>(diffSubStructs[i]) = subSubStruct;
      }
    });

    op::for_each_ordinal<MyNestedStruct>([&]<class Ord>(Ord) {
      if (folly::to_underlying(Ord::value) == op::size_v<MyNestedStruct>) {
        // Make the last field different
        op::get<Ord>(nestedStructs[i]) = diffSubStructs[i];
      } else {
        op::get<Ord>(nestedStructs[i]) = subStruct;
      }
    });
  }

  // Sanity check
  for (int i = 1; i < N; i++) {
    CHECK_EQ(
        structs[i - 1] < structs[i],
        apache::thrift::op::detail::StructLessThan{}(
            structs[i - 1], structs[i]));
    CHECK_EQ(
        unions[i - 1] < unions[i],
        apache::thrift::op::detail::UnionLessThan{}(unions[i - 1], unions[i]));
    CHECK_EQ(
        structs[i - 1] == structs[i],
        apache::thrift::op::detail::StructEquality{}(
            structs[i - 1], structs[i]));
    CHECK_EQ(
        unions[i - 1] == unions[i],
        apache::thrift::op::detail::UnionEquality{}(unions[i - 1], unions[i]));
    CHECK_EQ(
        nestedStructs[i - 1] < nestedStructs[i],
        apache::thrift::op::detail::StructLessThan{}(
            nestedStructs[i - 1], nestedStructs[i]));
    CHECK_EQ(
        nestedStructs[i - 1] == nestedStructs[i],
        apache::thrift::op::detail::StructEquality{}(
            nestedStructs[i - 1], nestedStructs[i]));
  }
}

BENCHMARK(StructLess) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= structs[i - 1] < structs[i];
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK_RELATIVE(StructOpLess) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= apache::thrift::op::detail::StructLessThan{}(
        structs[i - 1], structs[i]);
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK(NestedStructLess) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= nestedStructs[i - 1] < nestedStructs[i];
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK_RELATIVE(NestedStructOpLess) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= apache::thrift::op::detail::StructLessThan{}(
        nestedStructs[i - 1], nestedStructs[i]);
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK(UnionLess) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= unions[i - 1] < unions[i];
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK_RELATIVE(UnionOpLess) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= apache::thrift::op::detail::UnionLessThan{}(unions[i - 1], unions[i]);
  }
  folly::doNotOptimizeAway(b);
}

BENCHMARK(StructEqual) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= structs[i - 1] == structs[i];
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK_RELATIVE(StructOpEqual) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= apache::thrift::op::detail::StructEquality{}(
        structs[i - 1], structs[i]);
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK(NestedStructEqual) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= nestedStructs[i - 1] == nestedStructs[i];
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK_RELATIVE(NestedStructOpEqual) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= apache::thrift::op::detail::StructEquality{}(
        nestedStructs[i - 1], nestedStructs[i]);
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK(UnionEqual) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= unions[i - 1] == unions[i];
  }
  folly::doNotOptimizeAway(b);
}
BENCHMARK_RELATIVE(UnionOpEqual) {
  bool b = true;
  for (int i = 1; i < N; i++) {
    b ^= apache::thrift::op::detail::UnionEquality{}(unions[i - 1], unions[i]);
  }
  folly::doNotOptimizeAway(b);
}
} // namespace apache::thrift::test

int main(int argc, char** argv) {
  folly::Init init(&argc, &argv);
  apache::thrift::test::init();
  folly::runBenchmarks();
}
