

/*
 Copyright (c) 2003-2014 Andy Little.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see http://www.gnu.org/licenses./
*/

//
 
 
 
//
// See QUAN_ROOT/quan_matters/index.html for documentation.
/*
    AbstractQuantity Concept check
    Check that a type fulfills the StaticAbstractQuantity requirements
*/
#include <quan_matters/test/test.hpp>
#include "quan/concept_check/meta/abstract_quantity_concept.hpp"
#include <quan/length.hpp>
void test1()
{
    quan::concept_check::meta::AbstractQuantityConcept<quan::length::abstract_quantity>();
}

int errors =0;
int main()
{
   test1();
}