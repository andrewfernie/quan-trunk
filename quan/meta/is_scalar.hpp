#ifndef QUAN_META_IS_SCALAR_HPP_INCLUDED
#define QUAN_META_IS_SCALAR_HPP_INCLUDED

// Copyright Andrew Little 2006
// See QUAN_ROOT/quan_matters/index.html for documentation.

/*
    is T either a quantity or arithmetic
####################################################
    NOTE: this is not the same as std::is_scalar
    which allows pointers etc
####################################################
*/

#include <quan/config.hpp>
#ifndef __AVR__
#include <type_traits>
#else
#include <quan/std/tr1/is_arithmetic.hpp>
#endif
namespace quan{ namespace meta{

    template <typename T>
    struct is_scalar : std::is_arithmetic<T>{};

}}//quan::meta

#endif
