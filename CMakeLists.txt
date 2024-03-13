# copied from fmt lib
cmake_minimum_required(VERSION 3.1.0)

if(${CMAKE_VERSION} VERSION_LESS 3.11)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.11)
endif()

set(MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MASTER_PROJECT ON)
    message(STATUS "CMake version: ${CMAKE_VERSION}")
endif ()
#end copied from fmt lib

project(catchy CXX)

add_subdirectory(external/fmt-10.2.1)

add_library(catch INTERFACE)
target_include_directories(catch
    INTERFACE
        external/catch
)
include(external/catch/Catch.cmake)
add_library(catch::catch ALIAS catch)


set(catchy_src
    catchy/approx.cc catchy/approx.h
    catchy/stringeq.cc catchy/stringeq.h
    catchy/mapeq.cc catchy/mapeq.h
    catchy/falsestring.cc catchy/falsestring.h
    catchy/catch_utils.h
    catchy/vectortostring.h
)
source_group("" FILES ${catchy_src})
add_library(catchy STATIC ${catchy_src})
target_compile_features(catchy PUBLIC cxx_std_17)
target_include_directories(catchy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(catchy
    PUBLIC
        fmt::fmt
        catch::catch
)
if(NOT MASTER_PROJECT)
  set_target_properties(catchy PROPERTIES FOLDER "External")
  set_target_properties(fmt PROPERTIES FOLDER "External")
endif()
add_library(catchy::catchy ALIAS catchy)

