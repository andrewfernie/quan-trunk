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

// See QUAN_ROOT/quan_matters/index.html for documentation.

#include <quan/out/velocity.hpp>
#include <quan/out/mass.hpp>
#include <quan/out/force.hpp>
#include <quan/out/time.hpp>
#include <quan/out/density.hpp>
#include <quan/out/volume.hpp>

 quan::force::N  Force(
        const quan::mass::kg   & mass_in,
        quan::velocity::mm_per_s const & initial_veloc,
        const quan::velocity::m_per_s   & final_veloc,
        const quan::time::s   & t)
{
    quan::force::N result =  mass_in * (final_veloc - initial_veloc) / t;
    return result;
}

int main()
{
    //lab technician works in "odd units"...

    quan::mass::g               const mass(0.1f);
    quan::velocity::mm_per_min  const initial_v(5);
    quan::velocity::mm_per_min  const final_v(5.5);
    quan::time::min             const t_min(10);
    quan::time::s               const t_sec( 12);

    // function does the work ... he doesnt have to...

    std::cout << "force on mass = " << Force(mass,initial_v, final_v, t_min + t_sec) << '\n';
    quan::density::kg_per_m3 density = mass / quan::volume::m3(1);
    return 0;
}
