/**
 * Autogenerated by Thrift for thrift/compiler/test/fixtures/terse_write/src/deprecated_terse_write.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#pragma once

#include <vector>

#include <thrift/lib/cpp2/gen/module_metadata_h.h>
#include "thrift/compiler/test/fixtures/terse_write/gen-cpp2/deprecated_terse_write_types.h"


namespace apache {
namespace thrift {
namespace detail {
namespace md {

template <>
class EnumMetadata<::facebook::thrift::test::terse_write::deprecated::MyEnum> {
 public:
  static void gen(ThriftMetadata& metadata);
};
template <>
class StructMetadata<::facebook::thrift::test::terse_write::deprecated::MyStruct> {
 public:
  static const ::apache::thrift::metadata::ThriftStruct& gen(ThriftMetadata& metadata);
};
template <>
class StructMetadata<::facebook::thrift::test::terse_write::deprecated::MyUnion> {
 public:
  static const ::apache::thrift::metadata::ThriftStruct& gen(ThriftMetadata& metadata);
};
template <>
class StructMetadata<::facebook::thrift::test::terse_write::deprecated::StructLevelTerseStruct> {
 public:
  static const ::apache::thrift::metadata::ThriftStruct& gen(ThriftMetadata& metadata);
};
template <>
class StructMetadata<::facebook::thrift::test::terse_write::deprecated::FieldLevelTerseStruct> {
 public:
  static const ::apache::thrift::metadata::ThriftStruct& gen(ThriftMetadata& metadata);
};
template <>
class StructMetadata<::facebook::thrift::test::terse_write::deprecated::CppRefStructFields> {
 public:
  static const ::apache::thrift::metadata::ThriftStruct& gen(ThriftMetadata& metadata);
};
template <>
class StructMetadata<::facebook::thrift::test::terse_write::deprecated::DeprecatedTerseWriteWithCustomDefault> {
 public:
  static const ::apache::thrift::metadata::ThriftStruct& gen(ThriftMetadata& metadata);
};
template <>
class StructMetadata<::facebook::thrift::test::terse_write::deprecated::DeprecatedTerseWriteWithRedundantCustomDefault> {
 public:
  static const ::apache::thrift::metadata::ThriftStruct& gen(ThriftMetadata& metadata);
};
} // namespace md
} // namespace detail
} // namespace thrift
} // namespace apache
