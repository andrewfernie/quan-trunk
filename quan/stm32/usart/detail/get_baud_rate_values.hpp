#ifndef QUAN_STM32F4_USART_DETAIL_GET_BAUD_RATE_VALUES_HPP_INCLUDED
#define QUAN_STM32F4_USART_DETAIL_GET_BAUD_RATE_VALUES_HPP_INCLUDED

#include <quan/stm32/config.hpp>

#if defined QUAN_STM32F4
#include <quan/stm32/f4/usart/detail/get_baud_rate_values.hpp>
#elif defined QUAN_STM32F3
#include <quan/stm32/f3/usart/detail/get_baud_rate_values.hpp>
#elif defined QUAN_STM32F0
#include <quan/stm32/f0/usart/detail/get_baud_rate_values.hpp>
#else
#error need to define stm32 processor
#endif

#endif // QUAN_STM32F4_USART_DETAIL_GET_BAUD_RATE_VALUES_HPP_INCLUDED