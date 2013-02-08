#ifndef QUAN_DETAIL_UNITS_OUT_IMPL_HPP_INCLUDED
#define QUAN_DETAIL_UNITS_OUT_IMPL_HPP_INCLUDED

// Copyright Andrew Little 2005

// See QUAN_ROOT/quan_matters/index.html for documentation.

/*
    implementation called by the 
    ostream& operator << (ostream&,fixed_quantity_units_out< ..>);
    defined in <quan/fixed_quantity/io/aux_units_out.hpp>
*/
#ifndef __AVR__
#include <iosfwd>
#else
#include <quan/avr/iostream_dummy.hpp>
#endif
//#include <quan/fixed_quantity/fixed_quantity.hpp>
#include <quan/archetypes/meta/static_unit_concept.hpp>
#include <quan/meta/si_units.hpp>
//#include <quan/components/adjusted_coherent_prefix.hpp>

namespace quan{ namespace detail{

    // specialised differently for
    //1) named And coherent types
    //2) anonymous Or named and incoherent types
    // via NamedCoherent condition
    template < 
        typename StaticUnit, // actuall only defined for quan::meta::unit
        bool IsNamedAndCoherent
    > struct fixed_quantity_units_output_impl;


    template <QUAN_INT32 Extent, QUAN_INT32 PrefixOffset>
    struct get_adjusted_prefix{
 
        template < QUAN_INT32 Exp>
        struct apply{
////////////////ASSERTION FAILURE ////////////////////////////
            // some hoisted quantities such as area in m2 ^-5
            // cannot be output in convenient form
            // and will need to be converted to the nearest 
            // representable form eg mm2 for example
            QUAN_STATIC_ASSERT(( (Exp % Extent) ==0));
///////////////ASSERTION FAILURE/////////////////////////////////
            enum{
                value = Exp / Extent + PrefixOffset
            };
            typedef quan::meta::rational<value> type;
        };
    };
    // This version is for use with
    // named-quantities that are also si-quantities
    template <
        typename StaticUnit
    > struct fixed_quantity_units_output_impl<
        StaticUnit,
        true
    >{
   
        typedef typename quan::meta::get_named_quantity_traits<StaticUnit>::type named_traits;
////////////////////////////////
        typedef typename quan::meta::get_conversion_factor<StaticUnit>::type conv_factor;
        typedef typename quan::meta::get_exponent<conv_factor>::type exponent;
        typedef typename get_adjusted_prefix<
            named_traits::extent, named_traits::prefix_offset
        >::template apply<quan::meta::numerator<exponent>::value >::type adjusted_exponent;
        typedef typename quan::meta::si_unit:: template prefix<
            quan::meta::conversion_factor<
                adjusted_exponent
            >
        > adjusted_prefix_type;

/////////////////////////////
        template<typename CharType>
        static std::basic_ostream<CharType>&  
        put(std::basic_ostream<CharType>& os)
        {
            os << adjusted_prefix_type::template symbol<CharType>()
            << named_traits::template unprefixed_symbol<CharType>();
            return os;
        }
    };

    // this version simply uses the pq.units() function
    // It is usually used for anonymous ct_quanties
    // though will also be invoked for incoherent named quantities
    // which have not had an overload of 
    // ostream operator << (ostream&, fixed_quantity_units_out<..>)
    template < 
        typename StaticUnit
    > 
    struct fixed_quantity_units_output_impl<
        StaticUnit,
        false
    >{
        template<typename CharType>
        static std::basic_ostream<CharType>&  
        put(std::basic_ostream<CharType>& os)
        {
            os  << fixed_quantity<
                StaticUnit,
                typename quantity_traits::default_value_type
            >::get_unit(); 
            return os;
        }
    };

}}//quan::detail

#endif
