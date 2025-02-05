/*
 * This software is experimental and a work in progress.
 * Under no circumstances should these files be used in relation to any critical system(s).
 * Use of these files is at your own risk.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This files are free to use from http://engsta.com/stm32-flash-memory-eeprom-emulator/ by
 * Artur F.
 *
 * Modifications for QMK and STM32F303 by Yiancar
 *
 * This library assumes 8-bit data locations. To add a new MCU, please provide the flash
 * page size and the total flash size in Kb. The number of available pages must be a multiple
 * of 2. Only half of the pages account for the total EEPROM size.
 * This library also assumes that the pages are not used by the firmware.
 */

#pragma once

#include <ch.h>
#include <hal.h>
#include "flash_stm32.h"

// HACK ALERT. This definition may not match your processor
// To Do. Work out correct value for EEPROM_PAGE_SIZE on the STM32F103CT6 etc
#if defined(EEPROM_EMU_STM32F303xC)
#    define MCU_STM32F303CC
#elif defined(EEPROM_EMU_STM32F103xB)
#    define MCU_STM32F103RB
#elif defined(EEPROM_EMU_STM32F072xB)
#    define MCU_STM32F072CB
#elif defined(EEPROM_EMU_STM32F042x6)
#    define MCU_STM32F042K6
#elif defined(EEPROM_EMU_STM32F401xC)
#    define MCU_STM32F401xC
#else
#    error "not implemented."
#endif

#ifndef EEPROM_PAGE_SIZE
#    if defined(MCU_STM32F103RB) || defined(MCU_STM32F042K6)
#        define FEE_PAGE_SIZE (uint16_t)0x400  // Page size = 1KByte
#        define FEE_DENSITY_PAGES 2            // How many pages are used
#    elif defined(MCU_STM32F103ZE) || defined(MCU_STM32F103RE) || defined(MCU_STM32F103RD) || defined(MCU_STM32F303CC) || defined(MCU_STM32F072CB)
#        define FEE_PAGE_SIZE (uint16_t)0x800  // Page size = 2KByte
#        define FEE_DENSITY_PAGES 4            // How many pages are used
#    elif defined(MCU_STM32F401xC)
#        define FEE_PAGE_SIZE (uint32_t)0x20000  // Page size = 128KByte
#        define FEE_DENSITY_PAGES 1              // How many pages are used
#        define FEE_SECTOR_ID 7                  // sector id of the flash
#    else
#        error "No MCU type specified. Add something like -DMCU_STM32F103RB to your compiler arguments (probably in a Makefile)."
#    endif
#endif

#ifndef EEPROM_START_ADDRESS
#    if defined(MCU_STM32F103RB) || defined(MCU_STM32F072CB)
#        define FEE_MCU_FLASH_SIZE 128  // Size in Kb
#    elif defined(MCU_STM32F042K6)
#        define FEE_MCU_FLASH_SIZE 32  // Size in Kb
#    elif defined(MCU_STM32F103ZE) || defined(MCU_STM32F103RE)
#        define FEE_MCU_FLASH_SIZE 512  // Size in Kb
#    elif defined(MCU_STM32F103RD)
#        define FEE_MCU_FLASH_SIZE 384  // Size in Kb
#    elif (defined(MCU_STM32F303CC) || defined(MCU_STM32F401xC))
#        define FEE_MCU_FLASH_SIZE 256  // Size in Kb
#    else
#        error "No MCU type specified. Add something like -DMCU_STM32F103RB to your compiler arguments (probably in a Makefile)."
#    endif
#endif

// DONT CHANGE
// Choose location for the first EEPROM Page address on the top of flash
#define FEE_PAGE_END_ADDRESS ((uint32_t)(0x08000000 + FEE_MCU_FLASH_SIZE * 1024))
#define FEE_PAGE_BASE_ADDRESS ((uint32_t)((FEE_PAGE_END_ADDRESS) - FEE_DENSITY_PAGES * FEE_PAGE_SIZE))
#define FEE_DENSITY_BYTES ((FEE_PAGE_SIZE / 4) * FEE_DENSITY_PAGES - 1) // 4 Bytes for address, value pair
#define FEE_EMPTY_BYTE ((uint8_t)0xFF)
#define FEE_EMPTY_WORD ((uint16_t)0xFFFF)
#define FEE_EMPTY_VALUE ((uint32_t)0xFFFFFFFF)
#define FEE_DATA_ADDRESS(Address) ((Address)+2)     // flash address of the eeprom data
#define FEE_ADDR_ADDRESS(Address) (Address)         // flash address of the eeprom address
#define FEE_MAX_BYTES (FEE_DENSITY_BYTES+1) // eeprom size

// Use this function to initialize the functionality
uint16_t EEPROM_Init(void);
void     EEPROM_Erase(void);
uint16_t EEPROM_WriteDataByte(uint16_t Address, uint8_t DataByte);
uint8_t  EEPROM_ReadDataByte(uint16_t Address);
