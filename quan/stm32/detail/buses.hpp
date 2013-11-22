#ifndef QUAN_STM32_DEAIL_BUSES_HPP_INCLUDED
#define QUAN_STM32_DEAIL_BUSES_HPP_INCLUDED

#if defined QUAN_STM32F4
#include <quan/stm32/f4/detail/buses.hpp>
#elif defined QUAN_STM32F3
#include <quan/stm32/f3/detail/buses.hpp>
#elif defined QUAN_STM32F0
#include <quan/stm32/f0/detail/buses.hpp>
#else
#error 

#endif // QUAN_STM32_DEAIL_BUSES_HPP_INCLUDED
