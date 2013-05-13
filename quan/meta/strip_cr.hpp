#ifndef QUAN_META_STRIP_CR_HPP_INCLUDED
#define QUAN_META_STRIP_CR_HPP_INCLUDED

/// Copyright Andrew Little 2007

// See QUAN_ROOT/quan_matters/index.html for documentation.
#ifndef __AVR__
#include <type_traits>
#else
#include <quan/std/tr1/remove_const.hpp>
#include <quan/std/tr1/remove_reference.hpp>
#endif
namespace quan{ namespace meta{

   template <typename T>
   struct strip_cr {
      typedef  typename std::remove_const< 
       typename std::remove_reference<T>::type
      >::type type;
   };

   template<typename T>
   struct strip_crv{
      typedef typename std::remove_volatile<
			typename strip_cr<T>::type
      >::type type;
   };
}}

#endif

