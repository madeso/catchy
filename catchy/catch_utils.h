#ifndef CATCHY_CATCH_UTILS_H
#define CATCHY_CATCH_UTILS_H

#include "catch.hpp"

// ASSERT_THAT
#define CATCH_IS_VECTOR(TYPE, ...)                                             \
    Catch::Matchers::Equals(std::vector<TYPE> {__VA_ARGS__})

#define GENERATE_AS(T, ...) GENERATE(Catch::Generators::as<T> {}, __VA_ARGS__)

#endif  // CATCHY_CATCH_UTILS_H
