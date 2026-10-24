cmake_minimum_required(VERSION 3.20)
project(advent_of_code LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Wextra)

# Header-only shared code, reachable as #include <name.h>.
add_library(aoc_shared INTERFACE)
target_include_directories(aoc_shared INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Every <year>/<problem>_<part>.cpp becomes build/<year>/<problem>_<part>.
# Target names are prefixed with the year so they stay unique across years.
file(GLOB YEAR_DIRS LIST_DIRECTORIES true CONFIGURE_DEPENDS
  ${CMAKE_SOURCE_DIR}/[0-9][0-9][0-9][0-9])

foreach(YEAR_DIR ${YEAR_DIRS})
  if(NOT IS_DIRECTORY ${YEAR_DIR})
    continue()
  endif()
  get_filename_component(YEAR ${YEAR_DIR} NAME)
  file(GLOB SOURCES CONFIGURE_DEPENDS ${YEAR_DIR}/*.cpp)
  foreach(SOURCE ${SOURCES})
    get_filename_component(NAME ${SOURCE} NAME_WE)
    set(TARGET ${YEAR}_${NAME})
    add_executable(${TARGET} ${SOURCE})
    target_link_libraries(${TARGET} PRIVATE aoc_shared)
    # Headers shared between the parts of a problem live next to the sources.
    target_include_directories(${TARGET} PRIVATE ${YEAR_DIR})
    set_target_properties(${TARGET} PROPERTIES
      OUTPUT_NAME ${NAME}
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${YEAR})
  endforeach()
endforeach()
