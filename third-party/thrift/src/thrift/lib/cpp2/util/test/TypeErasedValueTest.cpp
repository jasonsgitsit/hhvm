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

#include <gtest/gtest.h>
#include <thrift/lib/cpp2/util/TypeErasedValue.h>

namespace apache::thrift::util::test {

class TypeErasedValueTest : public testing::Test {
  void SetUp() override {}

 protected:
  class LifetimeOperationsTracker {
   public:
    enum class Ops {
      CONSTRUCT,
      MOVE,
      MOVE_ASSIGN,
      COPY,
      CONST_COPY,
      COPY_ASSIGN,
      CONST_COPY_ASSIGN,
      DESTRUCT,
      CLEAR,
    };

    using OpsSequence = std::vector<Ops>;

    LifetimeOperationsTracker() = delete;

    explicit LifetimeOperationsTracker(OpsSequence& operations)
        : operations_(&operations), initialized_(true) {
      operations_->push_back(Ops::CONSTRUCT);
    }
    ~LifetimeOperationsTracker() {
      clear();
      operations_->push_back(Ops::DESTRUCT);
    }

    LifetimeOperationsTracker& operator=(LifetimeOperationsTracker& other) {
      operations_ = other.operations_;
      initialized_ = other.initialized_;
      other.clear();
      operations_->push_back(Ops::COPY_ASSIGN);
      return *this;
    }

    LifetimeOperationsTracker& operator=(
        const LifetimeOperationsTracker& other) {
      operations_ = other.operations_;
      initialized_ = other.initialized_;
      operations_->push_back(Ops::CONST_COPY_ASSIGN);
      return *this;
    }

    operator bool() const { return initialized_; }

    // NOLINTNEXTLINE(facebook-hte-NonConstCopyContructor)
    LifetimeOperationsTracker(LifetimeOperationsTracker& other)
        : operations_(other.operations_), initialized_(other.initialized_) {
      other.clear();
      operations_->push_back(Ops::COPY);
    }
    LifetimeOperationsTracker(const LifetimeOperationsTracker& other)
        : operations_(other.operations_), initialized_(other.initialized_) {
      operations_->push_back(Ops::CONST_COPY);
    }

    LifetimeOperationsTracker(LifetimeOperationsTracker&& other) noexcept
        : operations_(other.operations_), initialized_(other.initialized_) {
      operations_->push_back(Ops::MOVE);
      other.clear();
    }
    LifetimeOperationsTracker& operator=(LifetimeOperationsTracker&& other) {
      operations_ = other.operations_;
      initialized_ = other.initialized_;
      other.clear();
      operations_->push_back(Ops::MOVE_ASSIGN);
      return *this;
    }

   private:
    OpsSequence* operations_;

    void clear() { initialized_ = false; }
    bool initialized_{false};
  };

  // Dummy class to keep track of initialization
  class NoopStorage {
   public:
    constexpr operator bool() const { return false; }
  };
  class CounterStorage {
   public:
    explicit CounterStorage(int count) : count_(count) {}

    operator bool() const { return count_ != 0; }
    int getCount() const { return count_; }

   private:
    int count_{0};
  };

  using TypeErasedValueTestType = TypeErasedValue<
      sizeof(LifetimeOperationsTracker),
      alignof(LifetimeOperationsTracker)>;
  LifetimeOperationsTracker::OpsSequence sequence_;
};

/* Basic test for the test class */
TEST_F(TypeErasedValueTest, lifetimeOperationsTrackerTest) {
  {
    LifetimeOperationsTracker tracker(sequence_);
    ASSERT_TRUE(tracker);
    LifetimeOperationsTracker otherTracker(std::move(tracker));
    // @lint-ignore CLANGTIDY bugprone-use-after-move
    ASSERT_FALSE(tracker);
    ASSERT_TRUE(otherTracker);
  }
  {
    LifetimeOperationsTracker tracker(sequence_);
    ASSERT_TRUE(tracker);
    tracker = LifetimeOperationsTracker(sequence_);
    ASSERT_TRUE(tracker);
  }
  {
    LifetimeOperationsTracker tracker(sequence_);
    ASSERT_TRUE(tracker);
    LifetimeOperationsTracker otherTracker(sequence_);
    tracker = otherTracker;
    ASSERT_TRUE(tracker);
    ASSERT_FALSE(otherTracker);
  }
  {
    LifetimeOperationsTracker tracker(sequence_);
    ASSERT_TRUE(tracker);
    LifetimeOperationsTracker otherTracker(tracker);
    ASSERT_TRUE(otherTracker);
    ASSERT_FALSE(tracker);
  }
  {
    const LifetimeOperationsTracker tracker(sequence_);
    ASSERT_TRUE(tracker);
    LifetimeOperationsTracker otherTracker(tracker);
    ASSERT_TRUE(tracker);
    ASSERT_TRUE(otherTracker);
  }
  {
    const LifetimeOperationsTracker tracker(sequence_);
    ASSERT_TRUE(tracker);
    LifetimeOperationsTracker otherTracker(sequence_);
    otherTracker = tracker;
    ASSERT_TRUE(tracker);
    ASSERT_TRUE(otherTracker);
  }
  LifetimeOperationsTracker::OpsSequence expected{
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::MOVE,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::MOVE_ASSIGN,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::COPY_ASSIGN,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::COPY,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::CONST_COPY,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::CONST_COPY_ASSIGN,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
  };
  ASSERT_EQ(sequence_, expected);
}

TEST_F(TypeErasedValueTest, constructDestructTest) {
  {
    TypeErasedValueTestType storage;
    ASSERT_FALSE(storage.has_value());
    ASSERT_TRUE(storage.emplace<LifetimeOperationsTracker>(sequence_));
    ASSERT_TRUE(storage.has_value());
    ASSERT_TRUE(storage.value<LifetimeOperationsTracker>());
    {
      const auto& constStorage = storage;
      constStorage.value<LifetimeOperationsTracker>();
      ASSERT_TRUE(constStorage.value<LifetimeOperationsTracker>());
    }
  }
  LifetimeOperationsTracker::OpsSequence expected{
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
  };
  ASSERT_EQ(sequence_, expected);
}

TEST_F(TypeErasedValueTest, moveTest) {
  {
    TypeErasedValueTestType storage;
    ASSERT_FALSE(storage.has_value());
    ASSERT_TRUE(storage.emplace<LifetimeOperationsTracker>(sequence_));
    ASSERT_TRUE(storage.holds_alternative<LifetimeOperationsTracker>());
    ASSERT_TRUE(storage.has_value());
    ASSERT_TRUE(storage.value<LifetimeOperationsTracker>());
    TypeErasedValueTestType otherStorage(std::move(storage));
    // @lint-ignore CLANGTIDY bugprone-use-after-move
    ASSERT_FALSE(storage.holds_alternative<LifetimeOperationsTracker>());
    // @lint-ignore CLANGTIDY bugprone-use-after-move
    ASSERT_FALSE(storage.has_value());
    ASSERT_TRUE(otherStorage.holds_alternative<LifetimeOperationsTracker>());
    ASSERT_TRUE(otherStorage.has_value());
  }
  {
    TypeErasedValueTestType storage;
    ASSERT_FALSE(storage.has_value());
    ASSERT_TRUE(storage.emplace<LifetimeOperationsTracker>(sequence_));
    ASSERT_TRUE(storage.has_value());
    ASSERT_TRUE(storage.value<LifetimeOperationsTracker>());
    TypeErasedValueTestType otherStorage;
    otherStorage = std::move(storage);
    // @lint-ignore CLANGTIDY bugprone-use-after-move
    ASSERT_FALSE(storage.has_value());
    ASSERT_TRUE(otherStorage.has_value());
    ASSERT_TRUE(otherStorage.value<LifetimeOperationsTracker>());
  }
  LifetimeOperationsTracker::OpsSequence expected{
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::MOVE,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::MOVE,
      LifetimeOperationsTracker::Ops::DESTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
  };
  ASSERT_EQ(sequence_, expected);
}

TEST_F(TypeErasedValueTest, emptyStorageTest) {
  {
    TypeErasedValueTestType storage;
    ASSERT_FALSE(storage.has_value());
    ASSERT_FALSE(storage.holds_alternative<NoopStorage>());
    TypeErasedValueTestType otherStorage(std::move(storage));
    ASSERT_FALSE(otherStorage.has_value());
    ASSERT_FALSE(otherStorage.holds_alternative<NoopStorage>());
  }
  {
    TypeErasedValueTestType storage;
    TypeErasedValueTestType otherStorage;
    otherStorage = std::move(storage);
  }
}

TEST_F(TypeErasedValueTest, wrongTypeTest) {
  {
    TypeErasedValueTestType storage;
    ASSERT_TRUE(storage.emplace<LifetimeOperationsTracker>(sequence_));
    ASSERT_TRUE(storage.value<LifetimeOperationsTracker>());
    ASSERT_THROW(storage.value<NoopStorage>(), std::bad_cast);
    ASSERT_FALSE(storage.holds_alternative<NoopStorage>());
  }
  LifetimeOperationsTracker::OpsSequence expected{
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
  };
  ASSERT_EQ(sequence_, expected);
}

TEST_F(TypeErasedValueTest, replaceTypeTest) {
  {
    TypeErasedValueTestType storage;
    ASSERT_FALSE(storage.holds_alternative<LifetimeOperationsTracker>());
    ASSERT_TRUE(storage.emplace<LifetimeOperationsTracker>(sequence_));
    ASSERT_TRUE(storage.holds_alternative<LifetimeOperationsTracker>());
    ASSERT_TRUE(storage.value<LifetimeOperationsTracker>());
    ASSERT_THROW(storage.value<NoopStorage>(), std::bad_cast);
    ASSERT_FALSE(storage.holds_alternative<NoopStorage>());
    ASSERT_FALSE(storage.emplace<NoopStorage>());
    ASSERT_TRUE(storage.holds_alternative<NoopStorage>());
    ASSERT_FALSE(storage.holds_alternative<LifetimeOperationsTracker>());
    ASSERT_NO_THROW(storage.value<NoopStorage>());
    ASSERT_FALSE(storage.value<NoopStorage>());
    ASSERT_THROW(storage.value<LifetimeOperationsTracker>(), std::bad_cast);
  }
  LifetimeOperationsTracker::OpsSequence expected{
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
  };
  ASSERT_EQ(sequence_, expected);
}

TEST_F(TypeErasedValueTest, resetTest) {
  {
    TypeErasedValueTestType storage;
    ASSERT_FALSE(storage.has_value());
    ASSERT_TRUE(storage.emplace<LifetimeOperationsTracker>(sequence_));
    ASSERT_TRUE(storage.has_value());
    storage.reset();
    ASSERT_FALSE(storage.has_value());
  }
  LifetimeOperationsTracker::OpsSequence expected{
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
  };
  ASSERT_EQ(sequence_, expected);
}

TEST_F(TypeErasedValueTest, makeValueTest) {
  {
    TypeErasedValueTestType storage{
        std::in_place_type<LifetimeOperationsTracker>, sequence_};
    ASSERT_TRUE(storage.value<LifetimeOperationsTracker>());
    ASSERT_TRUE(storage.value_unchecked<LifetimeOperationsTracker>());
    ASSERT_EQ(storage.emplace<CounterStorage>(1).getCount(), 1);
    ASSERT_EQ(storage.value<CounterStorage>().getCount(), 1);
  }
  LifetimeOperationsTracker::OpsSequence expected{
      LifetimeOperationsTracker::Ops::CONSTRUCT,
      LifetimeOperationsTracker::Ops::DESTRUCT,
  };
  ASSERT_EQ(sequence_, expected);
}

TEST_F(TypeErasedValueTest, makeEmptyTest) {
  TypeErasedValueTestType storage{std::in_place_type<std::monostate>};
  ASSERT_THROW(storage.value<NoopStorage>(), std::bad_cast);
}

TEST_F(TypeErasedValueTest, swapTest) {
  TypeErasedValueTestType storageOne{std::in_place_type<CounterStorage>, 1};
  TypeErasedValueTestType storageTwo{std::in_place_type<CounterStorage>, 2};
  ASSERT_EQ(storageOne.value<CounterStorage>().getCount(), 1);
  ASSERT_EQ(storageTwo.value<CounterStorage>().getCount(), 2);
  std::swap(storageOne, storageTwo);
  ASSERT_EQ(storageOne.value<CounterStorage>().getCount(), 2);
  ASSERT_EQ(storageTwo.value<CounterStorage>().getCount(), 1);
  std::swap(storageOne, storageTwo);
  ASSERT_EQ(storageOne.value<CounterStorage>().getCount(), 1);
  ASSERT_EQ(storageTwo.value<CounterStorage>().getCount(), 2);
}

TEST_F(TypeErasedValueTest, moveAssignNonTrivial) {
  using StringStorage =
      TypeErasedValue<sizeof(std::string), alignof(std::string)>;
  StringStorage storage1;
  storage1.emplace<std::string>("hello");

  StringStorage storage2;
  storage2 = std::move(storage1);
  ASSERT_EQ(storage2.value<std::string>(), "hello");
}

} // namespace apache::thrift::util::test
