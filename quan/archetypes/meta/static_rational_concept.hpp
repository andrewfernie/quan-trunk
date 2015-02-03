#ifndef QUAN_ARCHETYPES_META_RATIONAL_HPP_INCLUDED
#define QUAN_ARCHETYPES_META_RATIONAL_HPP_INCLUDED
#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

/*
 Copyright (c) 2005-2013 Andy Little 

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>
*/
/*
    StaticRational extends StaticNumeric
*/

#include <quan/archetypes/meta/static_numeric_concept.hpp>
#include <quan/meta/numerator.hpp>
#include <quan/meta/denominator.hpp>

namespace quan{namespace meta{

    template < typename StaticRational>
    struct eval;

    template <typename StaticRational>
    struct is_integer;
    
}}

#endif
