cmake_minimum_required(VERSION 3.16)

set(MY_PROJECT_NAME glim)
project(
  ${MY_PROJECT_NAME}
  VERSION 1.0.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX20)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} supports C++20")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
    set(CMAKE_CXX_STANDARD 20)
    set(MY_COMPILER_FEATURES cxx_std_20)
elseif(COMPILER_SUPPORTS_CXX17)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} supports C++17")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    set(CMAKE_CXX_STANDARD 17)
    set(MY_COMPILER_FEATURES cxx_std_17)
elseif(COMPILER_SUPPORTS_CXX14)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} supports C++14")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    set(CMAKE_CXX_STANDARD 14)
    set(MY_COMPILER_FEATURES cxx_std_14)
elseif(COMPILER_SUPPORTS_CXX11)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} supports C++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_STANDARD 11)
    set(MY_COMPILER_FEATURES cxx_std_11)
elseif(COMPILER_SUPPORTS_CXX0X)
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} supports C++0x")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(
  ${CMAKE_SOURCE_DIR}/fmt/include
  ${CMAKE_SOURCE_DIR}/stb
  ${CMAKE_SOURCE_DIR}/json/include
  ${CMAKE_SOURCE_DIR}/work
  ${CMAKE_SOURCE_DIR}/env/include
)

link_directories(${CMAKE_SOURCE_DIR}/env/lib)

set(FMT
  ${CMAKE_SOURCE_DIR}/fmt/src/format.cc
  ${CMAKE_SOURCE_DIR}/fmt/src/os.cc
)

set(SRC
  main.cpp
  Task.cpp
  Core.cpp
  FullTextIndexer.cpp
  FullTextSearcher.cpp
  Cmd.cpp
)

set(HEADERS
  Const.h
  Task.h
  Core.h
  FullTextIndexer.h
  FullTextSearcher.h
  Cmd.h
)

add_executable(${MY_PROJECT_NAME} ${SRC} ${FMT})
target_link_libraries(${MY_PROJECT_NAME} dl pthread lucy clownfish)
target_compile_features(${MY_PROJECT_NAME} PRIVATE ${MY_COMPILER_FEATURES})

#module with helper functions
include(gwf_module)

fix_format(${CMAKE_SOURCE_DIR}/work ${SRC} )
fix_format(${CMAKE_SOURCE_DIR}/work ${HEADERS} )
