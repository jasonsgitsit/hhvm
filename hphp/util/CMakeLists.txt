set(CXX_SOURCES)
auto_sources(files "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}")
list(APPEND CXX_SOURCES ${files})

set(ASM_SOURCES)
auto_sources(files "*.S" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}")
list(APPEND ASM_SOURCES ${files})

set(HEADER_SOURCES)
auto_sources(files "*.h" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}")
list(APPEND HEADER_SOURCES ${files})

# Disable Channeled JSON until we're sure it's going to stick
# sgolemon(2014-02-19)
HHVM_REMOVE_MATCHES_FROM_LISTS(ASM_SOURCES CXX_SOURCES HEADER_SOURCES
  MATCHES "/test/" "channeled-json-")

if (NOT MSVC)
  list(REMOVE_ITEM CXX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/portability/fnmatch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/portability/glob.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/portability/rand_r.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/portability/strfmon.cpp
  )
  list(REMOVE_ITEM HEADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/portability/fnmatch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/portability/glob.h
    ${CMAKE_CURRENT_SOURCE_DIR}/portability/rand_r.h
    ${CMAKE_CURRENT_SOURCE_DIR}/portability/strfmon.h
  )
endif()

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/low-ptr-def.h
  COMMAND INSTALL_DIR=${CMAKE_CURRENT_BINARY_DIR} bash ${CMAKE_CURRENT_SOURCE_DIR}/../tools/generate-low-ptr.sh ignored
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../tools/generate-low-ptr.sh
)

list(APPEND HEADER_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/low-ptr-def.h)

HHVM_PUBLIC_HEADERS(util ${HEADER_SOURCES})

find_package(LibNuma)
if (LIBNUMA_INCLUDE_DIRS)
  add_definitions("-DHAVE_NUMA=1")
  include_directories(${LIBNUMA_INCLUDE_DIRS})
endif()

if(MSVC)
  list(REMOVE_ITEM CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/afdt-util.cpp")
  list(REMOVE_ITEM HEADER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/afdt-util.h")
  list(REMOVE_ITEM CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/light-process.cpp")
  list(REMOVE_ITEM HEADER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/light-process.h")
endif()

get_target_property(CARGO_EXE cargo LOCATION)
get_target_property(RUSTC_EXE rustc LOCATION)

add_library(hphp_util STATIC ${CXX_SOURCES} ${ASM_SOURCES} ${HEADER_SOURCES})

include(HHVMRenderConfigSpecification)

HHVM_RENDER_CONFIG_SPECIFICATION(
    hphp_util
    TYPE defs
    OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/configs
)

auto_source_group("hphp_util" "${CMAKE_CURRENT_SOURCE_DIR}"
  ${ASM_SOURCES} ${CXX_SOURCES} ${HEADER_SOURCES})
if (ENABLE_COTIRE)
  cotire(hphp_util)
endif()

target_link_libraries(hphp_util brotli folly zstd)
if (LIBNUMA_LIBRARIES)
  target_link_libraries(hphp_util ${LIBNUMA_LIBRARIES})
endif()
