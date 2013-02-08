#ifndef QUAN_OF_FORCE_HPP_INCLUDED
#define QUAN_OF_FORCE_HPP_INCLUDED
#if (defined _MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// Copyright Andrew Little 2005
//
 

 
//
// See QUAN_ROOT/quan_matters/index.html for documentation.

#include <quan/components/of_named_quantity.hpp>

namespace quan{ namespace meta{ namespace components{

    struct of_force{

        static const char* abstract_quantity_name()
        {
            return "force";
        }

        template<typename CharType>
        static const CharType* unprefixed_symbol();

        enum{
            extent = 1,
            prefix_offset = 0
        };

        typedef meta::dimension<
            meta::rational<1>, // length
            meta::rational<-2>, // time
            meta::rational<1>, // mass
            meta::rational<0>, // temperature
            meta::rational<0>, // current
            meta::rational<0>, // substance
            meta::rational<0> // intensity
        > dimension;

        typedef meta::abstract_quantity<
            dimension,
            of_force
        > abstract_quantity;

        struct non_si_unit{
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-5>,
                    meta::rational<1,1>::type,
                    quan::meta::int32<1>
                >
            > dyn;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<0>,
                    meta::rational<196133,20000>::type,
                    quan::meta::int32<0>
                >
            > kgf;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<3>,
                    meta::rational<2224111,500000>::type,
                    quan::meta::int32<0>
                >
            > kip;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-1>,
                    meta::rational<2780139,1000000>::type,
                    quan::meta::int32<0>
                >
            > ozf;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<-1>,
                    meta::rational<27651,20000>::type,
                    quan::meta::int32<0>
                >
            > poundal;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<0>,
                    meta::rational<2241111,500000>::type,
                    quan::meta::int32<0>
                >
            > lbf;
            typedef meta::unit<
                abstract_quantity,
                meta::conversion_factor<
                    meta::rational<3>,
                    meta::rational<8896443,1000000>::type,
                    quan::meta::int32<0>
                >
            > ton_force;
        };

        typedef  of_force type;

    };

    template<>
    inline
    const char*
    of_force::unprefixed_symbol<char>()
    {
        return "N";
    }

}}}//quan::meta::components
#endif
