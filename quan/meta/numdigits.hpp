#ifndef QUAN_META_NUMDIGITS_HPP_INCLUDED
#define QUAN_META_NUMDIGITS_HPP_INCLUDED

#include <type_traits>
#include <type_traits>
#include <type_traits>
#include <quan/meta/numbits.hpp>
#include <quan/where.hpp>

namespace quan{ namespace meta{
 
   template<typename I, typename Where = void> struct numdigits;

   template <typename I> struct numdigits<
		I, typename quan::where_<std::is_integral<I> >::type
   > {
         static const int value =  quan::meta::numbits<I>::value - (std::is_signed<I>::value ? 1: 0);
         typedef numdigits type;
   };
}}

#endif // QUAN_META_NUMDIGITS_HPP_INCLUDED
