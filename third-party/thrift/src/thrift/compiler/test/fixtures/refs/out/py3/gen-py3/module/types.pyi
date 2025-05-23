#
# Autogenerated by Thrift for thrift/compiler/test/fixtures/refs/src/module.thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#

import enum as _python_std_enum
import folly.iobuf as _fbthrift_iobuf
import thrift.py3.types
import thrift.python.types
import thrift.py3.exceptions
import typing as _typing

import sys
import itertools
import module.thrift_types


MyEnum = module.thrift_types.MyEnum
TypedEnum = module.thrift_types.TypedEnum

_MyUnionValueType = _typing.Union[None, int, str]

class MyUnion(thrift.py3.types.Union, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    anInteger: _typing.Final[_typing.Optional[int]] = ...
    aString: _typing.Final[_typing.Optional[str]] = ...

    def __init__(
        self, *,
        anInteger: _typing.Optional[int]=None,
        aString: _typing.Optional[str]=None
    ) -> None: ...

    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'MyUnion') -> bool: ...
    def __gt__(self, other: 'MyUnion') -> bool: ...
    def __le__(self, other: 'MyUnion') -> bool: ...
    def __ge__(self, other: 'MyUnion') -> bool: ...

    class Type(_python_std_enum.Enum):
        EMPTY: MyUnion.Type = ...
        anInteger: MyUnion.Type = ...
        aString: MyUnion.Type = ...

    @staticmethod
    def fromValue(value: _MyUnionValueType) -> MyUnion: ...
    type: _typing.Final[MyUnion.Type]
    value: _typing.Final[_MyUnionValueType]
    def get_type(self) -> MyUnion.Type: ...

    def _to_python(self) -> module.thrift_types.MyUnion: ...
    def _to_py3(self) -> MyUnion: ...
    def _to_py_deprecated(self) -> "module.ttypes.MyUnion": ...   # type: ignore

_NonTriviallyDestructibleUnionValueType = _typing.Union[None, int]

class NonTriviallyDestructibleUnion(thrift.py3.types.Union, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    int_field: _typing.Final[_typing.Optional[int]] = ...

    def __init__(
        self, *,
        int_field: _typing.Optional[int]=None
    ) -> None: ...

    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'NonTriviallyDestructibleUnion') -> bool: ...
    def __gt__(self, other: 'NonTriviallyDestructibleUnion') -> bool: ...
    def __le__(self, other: 'NonTriviallyDestructibleUnion') -> bool: ...
    def __ge__(self, other: 'NonTriviallyDestructibleUnion') -> bool: ...

    class Type(_python_std_enum.Enum):
        EMPTY: NonTriviallyDestructibleUnion.Type = ...
        int_field: NonTriviallyDestructibleUnion.Type = ...

    @staticmethod
    def fromValue(value: _NonTriviallyDestructibleUnionValueType) -> NonTriviallyDestructibleUnion: ...
    type: _typing.Final[NonTriviallyDestructibleUnion.Type]
    value: _typing.Final[_NonTriviallyDestructibleUnionValueType]
    def get_type(self) -> NonTriviallyDestructibleUnion.Type: ...

    def _to_python(self) -> module.thrift_types.NonTriviallyDestructibleUnion: ...
    def _to_py3(self) -> NonTriviallyDestructibleUnion: ...
    def _to_py_deprecated(self) -> "module.ttypes.NonTriviallyDestructibleUnion": ...   # type: ignore

class MyField(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    opt_value: _typing.Final[_typing.Optional[int]] = ...
    value: _typing.Final[_typing.Optional[int]] = ...
    req_value: _typing.Final[_typing.Optional[int]] = ...
    opt_enum_value: _typing.Final[_typing.Optional[MyEnum]] = ...
    enum_value: _typing.Final[_typing.Optional[MyEnum]] = ...
    req_enum_value: _typing.Final[_typing.Optional[MyEnum]] = ...
    opt_str_value: _typing.Final[_typing.Optional[str]] = ...
    str_value: _typing.Final[_typing.Optional[str]] = ...
    req_str_value: _typing.Final[_typing.Optional[str]] = ...

    def __init__(
        self, *,
        opt_value: _typing.Optional[int]=None,
        value: _typing.Optional[int]=None,
        req_value: _typing.Optional[int]=None,
        opt_enum_value: _typing.Optional[MyEnum]=None,
        enum_value: _typing.Optional[MyEnum]=None,
        req_enum_value: _typing.Optional[MyEnum]=None,
        opt_str_value: _typing.Optional[str]=None,
        str_value: _typing.Optional[str]=None,
        req_str_value: _typing.Optional[str]=None
    ) -> None: ...

    def __call__(
        self, *,
        opt_value: _typing.Union[int, None]=None,
        value: _typing.Union[int, None]=None,
        req_value: _typing.Union[int, None]=None,
        opt_enum_value: _typing.Union[MyEnum, None]=None,
        enum_value: _typing.Union[MyEnum, None]=None,
        req_enum_value: _typing.Union[MyEnum, None]=None,
        opt_str_value: _typing.Union[str, None]=None,
        str_value: _typing.Union[str, None]=None,
        req_str_value: _typing.Union[str, None]=None
    ) -> MyField: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['MyField'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'MyField') -> bool: ...
    def __gt__(self, other: 'MyField') -> bool: ...
    def __le__(self, other: 'MyField') -> bool: ...
    def __ge__(self, other: 'MyField') -> bool: ...

    def _to_python(self) -> module.thrift_types.MyField: ...
    def _to_py3(self) -> MyField: ...
    def _to_py_deprecated(self) -> "module.ttypes.MyField": ...   # type: ignore

class MyStruct(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    opt_ref: _typing.Final[_typing.Optional[MyField]] = ...
    ref: _typing.Final[_typing.Optional[MyField]] = ...
    req_ref: _typing.Final[_typing.Optional[MyField]] = ...

    def __init__(
        self, *,
        opt_ref: _typing.Optional[MyField]=None,
        ref: _typing.Optional[MyField]=None,
        req_ref: _typing.Optional[MyField]=None
    ) -> None: ...

    def __call__(
        self, *,
        opt_ref: _typing.Union[MyField, None]=None,
        ref: _typing.Union[MyField, None]=None,
        req_ref: _typing.Union[MyField, None]=None
    ) -> MyStruct: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['MyStruct'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'MyStruct') -> bool: ...
    def __gt__(self, other: 'MyStruct') -> bool: ...
    def __le__(self, other: 'MyStruct') -> bool: ...
    def __ge__(self, other: 'MyStruct') -> bool: ...

    def _to_python(self) -> module.thrift_types.MyStruct: ...
    def _to_py3(self) -> MyStruct: ...
    def _to_py_deprecated(self) -> "module.ttypes.MyStruct": ...   # type: ignore

class StructWithUnion(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        f: bool
        pass

    u: _typing.Final[_typing.Optional[MyUnion]] = ...
    aDouble: _typing.Final[_typing.Optional[float]] = ...
    f: _typing.Final[MyField] = ...

    def __init__(
        self, *,
        u: _typing.Optional[MyUnion]=None,
        aDouble: _typing.Optional[float]=None,
        f: _typing.Optional[MyField]=None
    ) -> None: ...

    def __call__(
        self, *,
        u: _typing.Union[MyUnion, None]=None,
        aDouble: _typing.Union[float, None]=None,
        f: _typing.Union[MyField, None]=None
    ) -> StructWithUnion: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithUnion'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithUnion') -> bool: ...
    def __gt__(self, other: 'StructWithUnion') -> bool: ...
    def __le__(self, other: 'StructWithUnion') -> bool: ...
    def __ge__(self, other: 'StructWithUnion') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithUnion: ...
    def _to_py3(self) -> StructWithUnion: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithUnion": ...   # type: ignore

class RecursiveStruct(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        mes: bool
        pass

    mes: _typing.Final[_typing.Optional[_typing.Sequence[RecursiveStruct]]] = ...

    def __init__(
        self, *,
        mes: _typing.Optional[_typing.Sequence[RecursiveStruct]]=None
    ) -> None: ...

    def __call__(
        self, *,
        mes: _typing.Union[_typing.Sequence[RecursiveStruct], None]=None
    ) -> RecursiveStruct: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['RecursiveStruct'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'RecursiveStruct') -> bool: ...
    def __gt__(self, other: 'RecursiveStruct') -> bool: ...
    def __le__(self, other: 'RecursiveStruct') -> bool: ...
    def __ge__(self, other: 'RecursiveStruct') -> bool: ...

    def _to_python(self) -> module.thrift_types.RecursiveStruct: ...
    def _to_py3(self) -> RecursiveStruct: ...
    def _to_py_deprecated(self) -> "module.ttypes.RecursiveStruct": ...   # type: ignore

class StructWithContainers(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    list_ref: _typing.Final[_typing.Optional[_typing.Sequence[int]]] = ...
    set_ref: _typing.Final[_typing.Optional[_typing.AbstractSet[int]]] = ...
    map_ref: _typing.Final[_typing.Optional[_typing.Mapping[int, int]]] = ...
    list_ref_unique: _typing.Final[_typing.Optional[_typing.Sequence[int]]] = ...
    set_ref_shared: _typing.Final[_typing.Optional[_typing.AbstractSet[int]]] = ...
    list_ref_shared_const: _typing.Final[_typing.Optional[_typing.Sequence[int]]] = ...

    def __init__(
        self, *,
        list_ref: _typing.Optional[_typing.Sequence[int]]=None,
        set_ref: _typing.Optional[_typing.AbstractSet[int]]=None,
        map_ref: _typing.Optional[_typing.Mapping[int, int]]=None,
        list_ref_unique: _typing.Optional[_typing.Sequence[int]]=None,
        set_ref_shared: _typing.Optional[_typing.AbstractSet[int]]=None,
        list_ref_shared_const: _typing.Optional[_typing.Sequence[int]]=None
    ) -> None: ...

    def __call__(
        self, *,
        list_ref: _typing.Union[_typing.Sequence[int], None]=None,
        set_ref: _typing.Union[_typing.AbstractSet[int], None]=None,
        map_ref: _typing.Union[_typing.Mapping[int, int], None]=None,
        list_ref_unique: _typing.Union[_typing.Sequence[int], None]=None,
        set_ref_shared: _typing.Union[_typing.AbstractSet[int], None]=None,
        list_ref_shared_const: _typing.Union[_typing.Sequence[int], None]=None
    ) -> StructWithContainers: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithContainers'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithContainers') -> bool: ...
    def __gt__(self, other: 'StructWithContainers') -> bool: ...
    def __le__(self, other: 'StructWithContainers') -> bool: ...
    def __ge__(self, other: 'StructWithContainers') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithContainers: ...
    def _to_py3(self) -> StructWithContainers: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithContainers": ...   # type: ignore

class StructWithSharedConst(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    opt_shared_const: _typing.Final[_typing.Optional[MyField]] = ...
    shared_const: _typing.Final[_typing.Optional[MyField]] = ...
    req_shared_const: _typing.Final[_typing.Optional[MyField]] = ...

    def __init__(
        self, *,
        opt_shared_const: _typing.Optional[MyField]=None,
        shared_const: _typing.Optional[MyField]=None,
        req_shared_const: _typing.Optional[MyField]=None
    ) -> None: ...

    def __call__(
        self, *,
        opt_shared_const: _typing.Union[MyField, None]=None,
        shared_const: _typing.Union[MyField, None]=None,
        req_shared_const: _typing.Union[MyField, None]=None
    ) -> StructWithSharedConst: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithSharedConst'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithSharedConst') -> bool: ...
    def __gt__(self, other: 'StructWithSharedConst') -> bool: ...
    def __le__(self, other: 'StructWithSharedConst') -> bool: ...
    def __ge__(self, other: 'StructWithSharedConst') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithSharedConst: ...
    def _to_py3(self) -> StructWithSharedConst: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithSharedConst": ...   # type: ignore

class Empty(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass


    def __init__(
        self, 
    ) -> None: ...

    def __call__(
        self, 
    ) -> Empty: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['Empty'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'Empty') -> bool: ...
    def __gt__(self, other: 'Empty') -> bool: ...
    def __le__(self, other: 'Empty') -> bool: ...
    def __ge__(self, other: 'Empty') -> bool: ...

    def _to_python(self) -> module.thrift_types.Empty: ...
    def _to_py3(self) -> Empty: ...
    def _to_py_deprecated(self) -> "module.ttypes.Empty": ...   # type: ignore

class StructWithRef(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    def_field: _typing.Final[_typing.Optional[Empty]] = ...
    opt_field: _typing.Final[_typing.Optional[Empty]] = ...
    req_field: _typing.Final[_typing.Optional[Empty]] = ...

    def __init__(
        self, *,
        def_field: _typing.Optional[Empty]=None,
        opt_field: _typing.Optional[Empty]=None,
        req_field: _typing.Optional[Empty]=None
    ) -> None: ...

    def __call__(
        self, *,
        def_field: _typing.Union[Empty, None]=None,
        opt_field: _typing.Union[Empty, None]=None,
        req_field: _typing.Union[Empty, None]=None
    ) -> StructWithRef: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithRef'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithRef') -> bool: ...
    def __gt__(self, other: 'StructWithRef') -> bool: ...
    def __le__(self, other: 'StructWithRef') -> bool: ...
    def __ge__(self, other: 'StructWithRef') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithRef: ...
    def _to_py3(self) -> StructWithRef: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithRef": ...   # type: ignore

class StructWithBox(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        a: bool
        b: bool
        c: bool
        pass

    a: _typing.Final[_typing.Optional[str]] = ...
    b: _typing.Final[_typing.Optional[_typing.Sequence[int]]] = ...
    c: _typing.Final[_typing.Optional[StructWithRef]] = ...

    def __init__(
        self, *,
        a: _typing.Optional[str]=None,
        b: _typing.Optional[_typing.Sequence[int]]=None,
        c: _typing.Optional[StructWithRef]=None
    ) -> None: ...

    def __call__(
        self, *,
        a: _typing.Union[str, None]=None,
        b: _typing.Union[_typing.Sequence[int], None]=None,
        c: _typing.Union[StructWithRef, None]=None
    ) -> StructWithBox: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithBox'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithBox') -> bool: ...
    def __gt__(self, other: 'StructWithBox') -> bool: ...
    def __le__(self, other: 'StructWithBox') -> bool: ...
    def __ge__(self, other: 'StructWithBox') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithBox: ...
    def _to_py3(self) -> StructWithBox: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithBox": ...   # type: ignore

class StructWithInternBox(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        field1: bool
        field2: bool
        pass

    field1: _typing.Final[Empty] = ...
    field2: _typing.Final[MyField] = ...

    def __init__(
        self, *,
        field1: _typing.Optional[Empty]=None,
        field2: _typing.Optional[MyField]=None
    ) -> None: ...

    def __call__(
        self, *,
        field1: _typing.Union[Empty, None]=None,
        field2: _typing.Union[MyField, None]=None
    ) -> StructWithInternBox: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithInternBox'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithInternBox') -> bool: ...
    def __gt__(self, other: 'StructWithInternBox') -> bool: ...
    def __le__(self, other: 'StructWithInternBox') -> bool: ...
    def __ge__(self, other: 'StructWithInternBox') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithInternBox: ...
    def _to_py3(self) -> StructWithInternBox: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithInternBox": ...   # type: ignore

class StructWithTerseInternBox(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    field1: _typing.Final[Empty] = ...
    field2: _typing.Final[MyField] = ...

    def __init__(
        self, *,
        field1: _typing.Optional[Empty]=None,
        field2: _typing.Optional[MyField]=None
    ) -> None: ...

    def __call__(
        self, *,
        field1: _typing.Union[Empty, None]=None,
        field2: _typing.Union[MyField, None]=None
    ) -> StructWithTerseInternBox: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithTerseInternBox'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithTerseInternBox') -> bool: ...
    def __gt__(self, other: 'StructWithTerseInternBox') -> bool: ...
    def __le__(self, other: 'StructWithTerseInternBox') -> bool: ...
    def __ge__(self, other: 'StructWithTerseInternBox') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithTerseInternBox: ...
    def _to_py3(self) -> StructWithTerseInternBox: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithTerseInternBox": ...   # type: ignore

class AdaptedStructWithInternBox(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        field1: bool
        field2: bool
        pass

    field1: _typing.Final[Empty] = ...
    field2: _typing.Final[MyField] = ...

    def __init__(
        self, *,
        field1: _typing.Optional[Empty]=None,
        field2: _typing.Optional[MyField]=None
    ) -> None: ...

    def __call__(
        self, *,
        field1: _typing.Union[Empty, None]=None,
        field2: _typing.Union[MyField, None]=None
    ) -> AdaptedStructWithInternBox: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['AdaptedStructWithInternBox'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'AdaptedStructWithInternBox') -> bool: ...
    def __gt__(self, other: 'AdaptedStructWithInternBox') -> bool: ...
    def __le__(self, other: 'AdaptedStructWithInternBox') -> bool: ...
    def __ge__(self, other: 'AdaptedStructWithInternBox') -> bool: ...

    def _to_python(self) -> module.thrift_types.AdaptedStructWithInternBox: ...
    def _to_py3(self) -> AdaptedStructWithInternBox: ...
    def _to_py_deprecated(self) -> "module.ttypes.AdaptedStructWithInternBox": ...   # type: ignore

class AdaptedStructWithTerseInternBox(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    field1: _typing.Final[Empty] = ...
    field2: _typing.Final[MyField] = ...

    def __init__(
        self, *,
        field1: _typing.Optional[Empty]=None,
        field2: _typing.Optional[MyField]=None
    ) -> None: ...

    def __call__(
        self, *,
        field1: _typing.Union[Empty, None]=None,
        field2: _typing.Union[MyField, None]=None
    ) -> AdaptedStructWithTerseInternBox: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['AdaptedStructWithTerseInternBox'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'AdaptedStructWithTerseInternBox') -> bool: ...
    def __gt__(self, other: 'AdaptedStructWithTerseInternBox') -> bool: ...
    def __le__(self, other: 'AdaptedStructWithTerseInternBox') -> bool: ...
    def __ge__(self, other: 'AdaptedStructWithTerseInternBox') -> bool: ...

    def _to_python(self) -> module.thrift_types.AdaptedStructWithTerseInternBox: ...
    def _to_py3(self) -> AdaptedStructWithTerseInternBox: ...
    def _to_py_deprecated(self) -> "module.ttypes.AdaptedStructWithTerseInternBox": ...   # type: ignore

class StructWithRefTypeUnique(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    def_field: _typing.Final[_typing.Optional[Empty]] = ...
    opt_field: _typing.Final[_typing.Optional[Empty]] = ...
    req_field: _typing.Final[_typing.Optional[Empty]] = ...

    def __init__(
        self, *,
        def_field: _typing.Optional[Empty]=None,
        opt_field: _typing.Optional[Empty]=None,
        req_field: _typing.Optional[Empty]=None
    ) -> None: ...

    def __call__(
        self, *,
        def_field: _typing.Union[Empty, None]=None,
        opt_field: _typing.Union[Empty, None]=None,
        req_field: _typing.Union[Empty, None]=None
    ) -> StructWithRefTypeUnique: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithRefTypeUnique'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithRefTypeUnique') -> bool: ...
    def __gt__(self, other: 'StructWithRefTypeUnique') -> bool: ...
    def __le__(self, other: 'StructWithRefTypeUnique') -> bool: ...
    def __ge__(self, other: 'StructWithRefTypeUnique') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithRefTypeUnique: ...
    def _to_py3(self) -> StructWithRefTypeUnique: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithRefTypeUnique": ...   # type: ignore

class StructWithRefTypeShared(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    def_field: _typing.Final[_typing.Optional[Empty]] = ...
    opt_field: _typing.Final[_typing.Optional[Empty]] = ...
    req_field: _typing.Final[_typing.Optional[Empty]] = ...

    def __init__(
        self, *,
        def_field: _typing.Optional[Empty]=None,
        opt_field: _typing.Optional[Empty]=None,
        req_field: _typing.Optional[Empty]=None
    ) -> None: ...

    def __call__(
        self, *,
        def_field: _typing.Union[Empty, None]=None,
        opt_field: _typing.Union[Empty, None]=None,
        req_field: _typing.Union[Empty, None]=None
    ) -> StructWithRefTypeShared: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithRefTypeShared'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithRefTypeShared') -> bool: ...
    def __gt__(self, other: 'StructWithRefTypeShared') -> bool: ...
    def __le__(self, other: 'StructWithRefTypeShared') -> bool: ...
    def __ge__(self, other: 'StructWithRefTypeShared') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithRefTypeShared: ...
    def _to_py3(self) -> StructWithRefTypeShared: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithRefTypeShared": ...   # type: ignore

class StructWithRefTypeSharedConst(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    def_field: _typing.Final[_typing.Optional[Empty]] = ...
    opt_field: _typing.Final[_typing.Optional[Empty]] = ...
    req_field: _typing.Final[_typing.Optional[Empty]] = ...

    def __init__(
        self, *,
        def_field: _typing.Optional[Empty]=None,
        opt_field: _typing.Optional[Empty]=None,
        req_field: _typing.Optional[Empty]=None
    ) -> None: ...

    def __call__(
        self, *,
        def_field: _typing.Union[Empty, None]=None,
        opt_field: _typing.Union[Empty, None]=None,
        req_field: _typing.Union[Empty, None]=None
    ) -> StructWithRefTypeSharedConst: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithRefTypeSharedConst'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithRefTypeSharedConst') -> bool: ...
    def __gt__(self, other: 'StructWithRefTypeSharedConst') -> bool: ...
    def __le__(self, other: 'StructWithRefTypeSharedConst') -> bool: ...
    def __ge__(self, other: 'StructWithRefTypeSharedConst') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithRefTypeSharedConst: ...
    def _to_py3(self) -> StructWithRefTypeSharedConst: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithRefTypeSharedConst": ...   # type: ignore

class StructWithRefAndAnnotCppNoexceptMoveCtor(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    def_field: _typing.Final[_typing.Optional[Empty]] = ...

    def __init__(
        self, *,
        def_field: _typing.Optional[Empty]=None
    ) -> None: ...

    def __call__(
        self, *,
        def_field: _typing.Union[Empty, None]=None
    ) -> StructWithRefAndAnnotCppNoexceptMoveCtor: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithRefAndAnnotCppNoexceptMoveCtor'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithRefAndAnnotCppNoexceptMoveCtor') -> bool: ...
    def __gt__(self, other: 'StructWithRefAndAnnotCppNoexceptMoveCtor') -> bool: ...
    def __le__(self, other: 'StructWithRefAndAnnotCppNoexceptMoveCtor') -> bool: ...
    def __ge__(self, other: 'StructWithRefAndAnnotCppNoexceptMoveCtor') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithRefAndAnnotCppNoexceptMoveCtor: ...
    def _to_py3(self) -> StructWithRefAndAnnotCppNoexceptMoveCtor: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithRefAndAnnotCppNoexceptMoveCtor": ...   # type: ignore

class StructWithString(thrift.py3.types.Struct, _typing.Hashable):
    class __fbthrift_IsSet:
        pass

    def_unique_string_ref: _typing.Final[_typing.Optional[str]] = ...
    def_shared_string_ref: _typing.Final[_typing.Optional[str]] = ...
    def_shared_string_const_ref: _typing.Final[_typing.Optional[str]] = ...
    unique_string_ref: _typing.Final[_typing.Optional[str]] = ...
    shared_string_ref: _typing.Final[_typing.Optional[str]] = ...

    def __init__(
        self, *,
        def_unique_string_ref: _typing.Optional[str]=None,
        def_shared_string_ref: _typing.Optional[str]=None,
        def_shared_string_const_ref: _typing.Optional[str]=None,
        unique_string_ref: _typing.Optional[str]=None,
        shared_string_ref: _typing.Optional[str]=None
    ) -> None: ...

    def __call__(
        self, *,
        def_unique_string_ref: _typing.Union[str, None]=None,
        def_shared_string_ref: _typing.Union[str, None]=None,
        def_shared_string_const_ref: _typing.Union[str, None]=None,
        unique_string_ref: _typing.Union[str, None]=None,
        shared_string_ref: _typing.Union[str, None]=None
    ) -> StructWithString: ...

    def __reduce__(self) -> _typing.Tuple[_typing.Callable, _typing.Tuple[_typing.Type['StructWithString'], bytes]]: ...
    def __hash__(self) -> int: ...
    def __str__(self) -> str: ...
    def __repr__(self) -> str: ...
    def __lt__(self, other: 'StructWithString') -> bool: ...
    def __gt__(self, other: 'StructWithString') -> bool: ...
    def __le__(self, other: 'StructWithString') -> bool: ...
    def __ge__(self, other: 'StructWithString') -> bool: ...

    def _to_python(self) -> module.thrift_types.StructWithString: ...
    def _to_py3(self) -> StructWithString: ...
    def _to_py_deprecated(self) -> "module.ttypes.StructWithString": ...   # type: ignore

_List__RecursiveStructT = _typing.TypeVar('_List__RecursiveStructT', bound=_typing.Sequence[RecursiveStruct])


class List__RecursiveStruct(_typing.Sequence[RecursiveStruct], _typing.Hashable):
    def __init__(self, items: _typing.Optional[_typing.Sequence[RecursiveStruct]]=None) -> None: ...
    def __len__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __copy__(self) -> _typing.Sequence[RecursiveStruct]: ...
    @_typing.overload
    def __getitem__(self, i: int) -> RecursiveStruct: ...
    @_typing.overload
    def __getitem__(self, s: slice) -> _typing.Sequence[RecursiveStruct]: ...
    def __add__(self, other: _typing.Sequence[RecursiveStruct]) -> 'List__RecursiveStruct': ...
    def __radd__(self, other: _typing.Sequence[RecursiveStruct]) -> 'List__RecursiveStruct': ...
    def __reversed__(self) -> _typing.Iterator[RecursiveStruct]: ...
    #pyre-ignore[14]: no idea what pyre is on about
    def __iter__(self) -> _typing.Iterator[RecursiveStruct]: ...


_List__i32T = _typing.TypeVar('_List__i32T', bound=_typing.Sequence[int])


class List__i32(_typing.Sequence[int], _typing.Hashable):
    def __init__(self, items: _typing.Optional[_typing.Sequence[int]]=None) -> None: ...
    def __len__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __copy__(self) -> _typing.Sequence[int]: ...
    @_typing.overload
    def __getitem__(self, i: int) -> int: ...
    @_typing.overload
    def __getitem__(self, s: slice) -> _typing.Sequence[int]: ...
    def __add__(self, other: _typing.Sequence[int]) -> 'List__i32': ...
    def __radd__(self, other: _typing.Sequence[int]) -> 'List__i32': ...
    def __reversed__(self) -> _typing.Iterator[int]: ...
    #pyre-ignore[14]: no idea what pyre is on about
    def __iter__(self) -> _typing.Iterator[int]: ...


class Set__i32(_typing.AbstractSet[int], _typing.Hashable):
    def __init__(self, items: _typing.Optional[_typing.AbstractSet[int]]=None) -> None: ...
    def __len__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __copy__(self) -> _typing.AbstractSet[int]: ...
    def __contains__(self, x: object) -> bool: ...
    def union(self, other: _typing.AbstractSet[int]) -> 'Set__i32': ...
    def intersection(self, other: _typing.AbstractSet[int]) -> 'Set__i32': ...
    def difference(self, other: _typing.AbstractSet[int]) -> 'Set__i32': ...
    def symmetric_difference(self, other: _typing.AbstractSet[int]) -> 'Set__i32': ...
    def issubset(self, other: _typing.AbstractSet[int]) -> bool: ...
    def issuperset(self, other: _typing.AbstractSet[int]) -> bool: ...
    def __iter__(self) -> _typing.Iterator[int]: ...


class Map__i32_i32(_typing.Mapping[int, int], _typing.Hashable):
    def __init__(self, items: _typing.Optional[_typing.Mapping[int, int]]=None) -> None: ...
    def __len__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __copy__(self) -> _typing.Mapping[int, int]: ...
    def __getitem__(self, key: int) -> int: ...
    def __iter__(self) -> _typing.Iterator[int]: ...


_List__i64T = _typing.TypeVar('_List__i64T', bound=_typing.Sequence[int])


class List__i64(_typing.Sequence[int], _typing.Hashable):
    def __init__(self, items: _typing.Optional[_typing.Sequence[int]]=None) -> None: ...
    def __len__(self) -> int: ...
    def __hash__(self) -> int: ...
    def __copy__(self) -> _typing.Sequence[int]: ...
    @_typing.overload
    def __getitem__(self, i: int) -> int: ...
    @_typing.overload
    def __getitem__(self, s: slice) -> _typing.Sequence[int]: ...
    def __add__(self, other: _typing.Sequence[int]) -> 'List__i64': ...
    def __radd__(self, other: _typing.Sequence[int]) -> 'List__i64': ...
    def __reversed__(self) -> _typing.Iterator[int]: ...
    #pyre-ignore[14]: no idea what pyre is on about
    def __iter__(self) -> _typing.Iterator[int]: ...


kStructWithRef: StructWithRef = ...
kStructWithRefTypeUnique: StructWithRefTypeUnique = ...
kStructWithRefTypeShared: StructWithRefTypeShared = ...
kStructWithRefTypeSharedConst: StructWithRefTypeSharedConst = ...
