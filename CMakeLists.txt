project(cityscape LANGUAGES CXX)

# Require C++14-compliant compiler; only available for CMake v3.10 and up
set(CMAKE_CXX_STANDARD 14)

cmake_minimum_required(VERSION 3.10)

SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

# General compile settings
IF (NOT CMAKE_BUILD_TYPE)
 SET(CMAKE_BUILD_TYPE "Release")
ENDIF (NOT CMAKE_BUILD_TYPE)

# GNU specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

# Intel specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

# Clang specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-var-template")
endif()

# CMake seems to have no way to enable/disable testing per subproject,
# so we provide an option similar to BUILD_TESTING, but just for CITYSCAPE.
option(CITYSCAPE_BUILD_TESTING "enable testing for cityscape" ON)

# CMake Modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Boost Archive
find_package(Boost REQUIRED COMPONENTS system serialization)
include_directories(${BOOST_INCLUDE_DIRS})
link_libraries(${Boost_SERIALIZATION_LIBRARY} ${Boost_SYSTEM_LIBRARY})

# MPI
find_package(MPI)
if (MPI_FOUND)
  add_definitions("-DUSE_MPI")
  include_directories(${MPI_CXX_INCLUDE_DIRS})
  link_libraries(${MPI_CXX_LIBRARIES})
endif ()

# Pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
link_libraries(Threads::Threads)

## OpenMP
#find_package(OpenMP REQUIRED)
#if (OPENMP_FOUND)
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif ()


# Include directories
include_directories(BEFORE
  ${cityscape_SOURCE_DIR}/external/
  ${cityscape_SOURCE_DIR}/include/
  ${cityscape_SOURCE_DIR}/include/graph/
  ${cityscape_SOURCE_DIR}/include/spatial/
        ${cityscape_SOURCE_DIR}/include/io/
        ${cityscape_SOURCE_DIR}/tests/test_data/
)

# cityscape executable
SET(cityscape_src
  ${cityscape_SOURCE_DIR}/src/graph/edge.cc
  ${cityscape_SOURCE_DIR}/src/graph/graph.cc
  ${cityscape_SOURCE_DIR}/src/graph/node.cc
  ${cityscape_SOURCE_DIR}/src/index_manager.cc
        ${cityscape_SOURCE_DIR}/src/csv_reader.cc
  ${cityscape_SOURCE_DIR}/src/spatial/point.cc
        ${cityscape_SOURCE_DIR}/src/spatial/line.cc
        ${cityscape_SOURCE_DIR}/src/spatial/utils.cc
)
#add_executable(cityscape ${cityscape_SOURCE_DIR}/src/main.cc)

# Unit test
if(CITYSCAPE_BUILD_TESTING)
  SET(cityscape_test_src
    ${cityscape_SOURCE_DIR}/tests/graph/edge_test.cc
    ${cityscape_SOURCE_DIR}/tests/graph/graph_test.cc
    ${cityscape_SOURCE_DIR}/tests/graph/node_test.cc
    ${cityscape_SOURCE_DIR}/tests/index_manager_test.cc
    ${cityscape_SOURCE_DIR}/tests/spatial/point_test.cc
          ${cityscape_SOURCE_DIR}/tests/spatial/line_test.cc
          ${cityscape_SOURCE_DIR}/tests/spatial/segment_test.cc
          ${cityscape_SOURCE_DIR}/tests/spatial/spatial_index_test.cc
          ${cityscape_SOURCE_DIR}/tests/spatial/utils_test.cc
#          ${cityscape_SOURCE_DIR}/tests/spatial/bay_pipes.cc
          ${cityscape_SOURCE_DIR}/tests/csv_reader_test.cc
    ${cityscape_SOURCE_DIR}/tests/main_test.cc
    )
  add_executable(cityscapetest ${cityscape_src} ${cityscape_test_src})
  add_test(NAME cityscapetest COMMAND $<TARGET_FILE:cityscapetest>)
  enable_testing()
endif()

# Coverage
find_package(codecov)
if(ENABLE_COVERAGE)
  add_executable(cityscapetest_coverage ${cityscape_src} ${cityscape_test_src})
  add_coverage(cityscapetest_coverage)
endif()
