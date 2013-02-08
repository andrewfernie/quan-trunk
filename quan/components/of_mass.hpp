#ifndef QUAN_OF_MASS_HPP_INCLUDED
#define QUAN_OF_MASS_HPP_INCLUDED
#if (defined _MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// Copyright Andrew Little 2005
//
 

 
//
// See QUAN_ROOT/quan_matters/index.html for documentation.

#include <quan/components/of_named_quantity.hpp>

namespace quan{ namespace meta{ namespace components{

    struct of_mass{

        static const char* abstract_quantity_name()
        {
            return "mass";
        }

        template<typename CharType>
        static const CharType* unprefixed_symbol();

        enum{
            extent = 1,
            prefix_offset = 3
        };

        typedef meta::dimension<
            meta::rational<0>, // length
            meta::rational<0>, // time
            meta::rational<1>, // mass
            meta::rational<0>, // temperature
            meta::rational<0>, // current
            meta::rational<0>, // substance
            meta::rational<0> // intensity
        > dimension;

        typedef meta::abstract_quantity<
            dimension,
            of_mass
        > abstract_quantity;

        struct non_si_unit{
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-2>,
                    meta::rational<2916667,1000000>::type,
                    quan::meta::int32<0>
                >
            > AT;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<3>,
                    meta::rational<1016047,1000000>::type,
                    quan::meta::int32<0>
                >
            > ton_long;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<3>,
                    meta::rational<1,1>::type,
                    quan::meta::int32<1>
                >
            > t;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-4>,
                    meta::rational<2,1>::type,
                    quan::meta::int32<0>
                >
            > carat;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-5>,
                    meta::rational<6479891,1000000>::type,
                    quan::meta::int32<0>
                >
            > grain;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<1>,
                    meta::rational<1016047,200000>::type,
                    quan::meta::int32<0>
                >
            > hundredwgt_short;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<1>,
                    meta::rational<1133981,250000>::type,
                    quan::meta::int32<0>
                >
            > hundredwgt_long;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-2>,
                    meta::rational<354369,125000>::type,
                    quan::meta::int32<0>
                >
            > oz;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<1>,
                    meta::rational<777587,250000>::type,
                    quan::meta::int32<0>
                >
            > troy_oz;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-3>,
                    meta::rational<777587,500000>::type,
                    quan::meta::int32<0>
                >
            > dwt;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-1>,
                    meta::rational<1133981,250000>::type,
                    quan::meta::int32<0>
                >
            > lb;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-1>,
                    meta::rational<3732417,1000000>::type,
                    quan::meta::int32<0>
                >
            > troy_lb;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<1>,
                    meta::rational<145939,100000>::type,
                    quan::meta::int32<0>
                >
            > slug;
        };

        typedef  of_mass type;

    };

    template<>
    inline
    const char*
    of_mass::unprefixed_symbol<char>()
    {
        return "g";
    }

}}}//quan::meta::components
#endif
