/* Copyright 2020 Nick Brassel (tzarc)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include_next "board.h"

#undef STM32_HSE_BYPASS
#undef VAL_GPIOB_MODER
#undef VAL_GPIOB_ODR

#define VAL_GPIOB_MODER                                                      \
  (PIN_MODE_INPUT(GPIOB_PIN0) | PIN_MODE_INPUT(GPIOB_PIN1) |                 \
   PIN_MODE_INPUT(GPIOB_PIN2) | PIN_MODE_ALTERNATE(GPIOB_SWO) |              \
   PIN_MODE_INPUT(GPIOB_PIN4) | PIN_MODE_OUTPUT(GPIOB_PIN5) |                \
   PIN_MODE_OUTPUT(GPIOB_LSM303DLHC_SCL) | PIN_MODE_INPUT(GPIOB_PIN7) |      \
   PIN_MODE_OUTPUT(GPIOB_PIN8) | PIN_MODE_ALTERNATE(GPIOB_LSM303DLHC_SDA) |  \
   PIN_MODE_ALTERNATE(GPIOB_MP45DT02_CLK_IN) | PIN_MODE_INPUT(GPIOB_PIN11) | \
   PIN_MODE_INPUT(GPIOB_PIN12) | PIN_MODE_INPUT(GPIOB_PIN13) |               \
   PIN_MODE_INPUT(GPIOB_PIN14) | PIN_MODE_INPUT(GPIOB_PIN15))

#define VAL_GPIOB_ODR                                                \
  (PIN_ODR_HIGH(GPIOB_PIN0) | PIN_ODR_HIGH(GPIOB_PIN1) |             \
   PIN_ODR_HIGH(GPIOB_PIN2) | PIN_ODR_HIGH(GPIOB_SWO) |              \
   PIN_ODR_HIGH(GPIOB_PIN4) | PIN_ODR_LOW(GPIOB_PIN5) |              \
   PIN_ODR_LOW(GPIOB_LSM303DLHC_SCL) | PIN_ODR_HIGH(GPIOB_PIN7) |    \
   PIN_ODR_LOW(GPIOB_PIN8) | PIN_ODR_HIGH(GPIOB_LSM303DLHC_SDA) |    \
   PIN_ODR_HIGH(GPIOB_MP45DT02_CLK_IN) | PIN_ODR_HIGH(GPIOB_PIN11) | \
   PIN_ODR_HIGH(GPIOB_PIN12) | PIN_ODR_HIGH(GPIOB_PIN13) |           \
   PIN_ODR_HIGH(GPIOB_PIN14) | PIN_ODR_HIGH(GPIOB_PIN15))
