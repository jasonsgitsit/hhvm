#
# Autogenerated by Thrift for thrift/compiler/test/fixtures/py3/src/module.thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#

import enum
import thrift.py3.types
import module.thrift_enums as _fbthrift_python_enums

_fbthrift__module_name__ = "module.types"


AnEnum = _fbthrift_python_enums.AnEnum
AnEnumRenamed = _fbthrift_python_enums.AnEnumRenamed
Flags = _fbthrift_python_enums.Flags


class __BinaryUnionType(enum.Enum):
    iobuf_val = 1
    EMPTY = 0

    __module__ = _fbthrift__module_name__
    __slots__ = ()
