#ifndef QUAN_STM32_USART_DETAIL_GET_IRQ_NUMBER_HPP_INCLUDED
#define QUAN_STM32_USART_DETAIL_GET_IRQ_NUMBER_HPP_INCLUDED

#include <quan/stm32/config.hpp>

#if defined QUAN_STM32F4
#include <stm32f4xx.h>
#elif defined QUAN_STM32F3
#include <stm32f3xx.h>
#elif defined QUAN_STM32F0
#include <stm32f0xx.h>
#else
#error need to define stm32 processor
#endif

#include <type_traits>
#include <quan/stm32/usart/typedefs.hpp>

namespace quan{ namespace stm32{ namespace usart{ namespace detail{

   template < typename Usart>
   struct get_irq_number;

#if defined QUAN_STM32_HAS_USART1
   template <> struct get_irq_number<quan::stm32::usart1> : std::integral_constant<IRQn_Type,USART1_IRQn>{};
#endif
#if defined QUAN_STM32_HAS_USART2
   template <> struct get_irq_number<quan::stm32::usart2> : std::integral_constant<IRQn_Type,USART2_IRQn>{};
#endif
#if defined QUAN_STM32_HAS_USART3
   template <> struct get_irq_number<quan::stm32::usart3> : std::integral_constant<IRQn_Type,USART3_IRQn>{};
#endif
#if defined QUAN_STM32_HAS_UART4
   template <> struct get_irq_number<quan::stm32::uart4> : std::integral_constant<IRQn_Type,UART4_IRQn>{};
#endif
#if defined QUAN_STM32_HAS_UART5
   template <> struct get_irq_number<quan::stm32::uart5> : std::integral_constant<IRQn_Type,UART5_IRQn>{};
#endif
#if defined QUAN_STM32_HAS_USART6
   template <> struct get_irq_number<quan::stm32::usart6> : std::integral_constant<IRQn_Type,USART6_IRQn>{};
#endif

}}}}

#endif // QUAN_STM32_USART_DETAIL_GET_IRQ_NUMBER_HPP_INCLUDED


