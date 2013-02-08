#ifndef QUAN_OF_CIRCULATION_HPP_INCLUDED
#define QUAN_OF_CIRCULATION_HPP_INCLUDED
#if (defined _MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// Copyright Andrew Little 2005
// See QUAN_ROOT/quan_matters/index.html for documentation.

#include <quan/components/of_named_quantity.hpp>

namespace quan{ namespace meta{ namespace components{

    struct of_circulation{

        static const char* abstract_quantity_name()
        {
            return "circulation";
        }

        template<typename CharType>
        static const CharType* unprefixed_symbol();

        enum{
            extent = 1,
            prefix_offset = 0
        };
//{2,-1}
        typedef meta::dimension<
            meta::rational<2>, // length
            meta::rational<-1>, // time
            meta::rational<0>, // mass
            meta::rational<0>, // temperature
            meta::rational<0>, // current
            meta::rational<0>, // substance
            meta::rational<0> // intensity
        > dimension;

        typedef meta::abstract_quantity<
            dimension,
            of_circulation
        > abstract_quantity;

        struct non_si_unit{
        };

        typedef  of_circulation type;

    };

    template<>
    inline
    const char*
    of_circulation::unprefixed_symbol<char>()
    {
        return "m2.s-1";
    }

}}}//quan::meta::components
#endif
