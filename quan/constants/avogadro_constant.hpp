#ifndef QUAN_AVOGADROS_NUMBER_HPP_INCLUDED
#define QUAN_AVOGADROS_NUMBER_HPP_INCLUDED
#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

// Copyright David Walthall 2006

// See QUAN_ROOT/quan_matters/index.html for documentation.

/*
    declaration of avogadro's number.
    The definition is in "quan_matters/src/avogadro_constant.cpp"
    required to link
    
    09 May 2006 renamed to avogadro_constant in sync with NIST SP 961
    Andy Little
*/
#include <quan/config.hpp>
#include <quan/fixed_quantity/fixed_quantity.hpp>
#include <quan/meta/rational.hpp>
#include <quan/meta/unit.hpp>
#include <quan/meta/abstract_quantity.hpp>
#include <quan/meta/dimension.hpp>
#include <quan/meta/conversion_factor.hpp>
#include <type_traits>

namespace quan {

    template<typename Value_type=double>
    struct avogadro_constant_{
       typedef  fixed_quantity<
            meta::unit<
                meta::abstract_quantity<
                    meta::dimension<
                        meta::rational<0>,
                        meta::rational<0>,
                        meta::rational<0>,
                        meta::rational<0>,
                        meta::rational<0>,
                        meta::rational<-1>, // per mole
                        meta::rational<0>
                    >
                >,
                meta::conversion_factor<
                    meta::rational<23>
                >
            >,
            typename std::add_const<Value_type>::type
        > Na_type;
        static Na_type const  Na;
    };
    struct avogadro_constant 
    : avogadro_constant_<quan::quantity_traits::default_value_type>{};

#ifdef QUAN_DEFINE_PHYSICAL_CONSTANTS_IN_HEADERS
template<typename T>
typename avogadro_constant_<T>::Na_type const
avogadro_constant_<T>::Na
= typename avogadro_constant_<T>::Na_type(6.0221415);
#endif

} //quan

#endif
