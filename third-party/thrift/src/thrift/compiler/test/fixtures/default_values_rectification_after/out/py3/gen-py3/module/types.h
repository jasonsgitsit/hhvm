/**
 * Autogenerated by Thrift for thrift/compiler/test/fixtures/default_values_rectification_after/src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#pragma once

#include <functional>
#include <folly/Range.h>

#include "thrift/compiler/test/fixtures/default_values_rectification_after/gen-cpp2/module_data.h"
#include "thrift/compiler/test/fixtures/default_values_rectification_after/gen-cpp2/module_types.h"
#include "thrift/compiler/test/fixtures/default_values_rectification_after/gen-cpp2/module_metadata.h"
namespace thrift {
namespace py3 {



template<>
inline void reset_field<::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct>(
    ::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct& obj, uint16_t index) {
  switch (index) {
  }
}

template<>
inline void reset_field<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>(
    ::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct& obj, uint16_t index) {
  switch (index) {
    case 0:
      obj.unqualified_int_field_ref().copy_from(default_inst<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>().unqualified_int_field_ref());
      return;
    case 1:
      obj.unqualified_bool_field_ref().copy_from(default_inst<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>().unqualified_bool_field_ref());
      return;
    case 2:
      obj.unqualified_list_field_ref().copy_from(default_inst<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>().unqualified_list_field_ref());
      return;
    case 3:
      obj.unqualified_struct_field_ref().copy_from(default_inst<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>().unqualified_struct_field_ref());
      return;
    case 4:
      obj.optional_int_field_ref().copy_from(default_inst<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>().optional_int_field_ref());
      return;
    case 5:
      obj.optional_bool_field_ref().copy_from(default_inst<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>().optional_bool_field_ref());
      return;
    case 6:
      obj.optional_list_field_ref().copy_from(default_inst<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>().optional_list_field_ref());
      return;
    case 7:
      obj.optional_struct_field_ref().copy_from(default_inst<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>().optional_struct_field_ref());
      return;
  }
}

template<>
inline const std::unordered_map<std::string_view, std::string_view>& PyStructTraits<
    ::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct>::namesmap() {
  static const folly::Indestructible<NamesMap> map {
    {
    }
  };
  return *map;
}

template<>
inline const std::unordered_map<std::string_view, std::string_view>& PyStructTraits<
    ::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>::namesmap() {
  static const folly::Indestructible<NamesMap> map {
    {
    }
  };
  return *map;
}
} // namespace py3
} // namespace thrift
