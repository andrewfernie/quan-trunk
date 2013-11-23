#ifndef QUAN_STM32_F0_DETAIL_GET_BUS_HPP_INCLUDED
#define QUAN_STM32_F0_DETAIL_GET_BUS_HPP_INCLUDED

#ifndef QUAN_STM32F0
#error dont include directly
#endif

#include <quan/is_model_of.hpp>
#include <quan/undefined.hpp>

#include <quan/stm32/module.hpp>
#include <quan/stm32/f0/periph_map.hpp>
#include <quan/stm32/f0/detail/buses.hpp>

namespace quan{ namespace stm32{ namespace detail{
    
   template <typename Module, typename Where = void>
   struct get_bus;

   template <uint32_t Address, typename Where = void>
   struct get_bus_c { typedef quan::undefined type;};

  

   template<uint32_t Address>
   struct get_bus_c<Address,typename quan::where_c< 
      ((Address <= quan::stm32::periph_map::gpiof) && (Address >= quan::stm32::periph_map::gpioa)) >::type
   >{
      typedef ahb2 type;
   };

   template<uint32_t Address>
   struct get_bus_c<Address,typename quan::where_c< 
      ((Address <= quan::stm32::periph_map::tsc) && (Address >= quan::stm32::periph_map::dma)) >::type
   >{
      typedef ahb1 type;
   };


   template<uint32_t Address>
   struct get_bus_c<Address,typename quan::where_c< 
      ((Address <= quan::stm32::periph_map::dbgmcu) && (Address >= quan::stm32::periph_map::tim2)) >::type
   >{
      typedef apb type;
   };

   template <typename Module>
   struct get_bus<
      Module,
      typename quan::where_< quan::is_model_of<quan::stm32::Module,Module> >::type
   > : get_bus_c<Module::address>{};

}}}

#endif // QUAN_STM32F0_USART_GET_BUS_HPP_INCLUDED