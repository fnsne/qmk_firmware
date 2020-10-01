#pragma once

#include "quantum.h"
#include "webusb.h"

#ifndef WEBUSB_ENABLE
#    error "WebUSB needs to be enabled, please enable it!"
#endif

#ifndef VIA_EEPROM_MAGIC_ADDR
#    define VIA_EEPROM_MAGIC_ADDR (EECONFIG_SIZE)
#endif

#define VIA_EEPROM_LAYOUT_OPTIONS_ADDR (VIA_EEPROM_MAGIC_ADDR + 3)

// Changing the layout options size after release will invalidate EEPROM,
// but this is something that should be set correctly on initial implementation.
// 1 byte is enough for most uses (i.e. 8 binary states, or 6 binary + 1 ternary/quaternary )
#ifndef VIA_EEPROM_LAYOUT_OPTIONS_SIZE
#    define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 1
#endif

// Allow override of the layout options default value.
// This requires advanced knowledge of how VIA stores layout options
// and is only really useful for setting a boolean layout option
// state to true by default.
#ifndef VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT
#    define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x00000000
#endif

// The end of the EEPROM memory used by VIA
// By default, dynamic keymaps will start at this if there is no
// custom config
#define VIA_EEPROM_CUSTOM_CONFIG_ADDR (VIA_EEPROM_LAYOUT_OPTIONS_ADDR + VIA_EEPROM_LAYOUT_OPTIONS_SIZE)

#ifndef VIA_EEPROM_CUSTOM_CONFIG_SIZE
#    define VIA_EEPROM_CUSTOM_CONFIG_SIZE 0
#endif

// enum Oryx_Status_code {
//     PLACEHOLDER = WEBUSB_STATUS_SAFE_RANGE,
// }

enum Oryx_Command_Code {
    ORYX_GET_LAYER = WEBUSB_CMD_SAFE_RANGE,
    ORYX_CMD_LIVE_TRAINING,
    ORYX_CMD_LIVE_UPDATE_GET_KEYCODE,
    ORYX_CMD_LIVE_UPDATE_SET_KEYCODE,
    ORYX_CMD_LIVE_UPDATE_KEYMAP_RESET,
    ORYX_CMD_LIVE_UPDATE_GET_BUFFER,
    ORYX_CMD_LIVE_UPDATE_SET_BUFFER,
    ORYX_CMD_LIVE_UPDATE_GET_LAYER_COUNT,
    ORYX_CMD_LIVE_UPDATE_GET_MACRO_COUNT,
    ORYX_CMD_LIVE_UPDATE_GET_MACRO_BUFFER_SIZE,
    ORYX_CMD_LIVE_UPDATE_GET_MACRO_BUFFER,
    ORYX_CMD_LIVE_UPDATE_SET_MACRO_BUFFER,
    ORYX_CMD_LIVE_UPDATE_MACRO_RESET,
    ORYX_CMD_LIVE_UPDATE_EEPROM_RESET,
    ORYX_CMD_LIVE_UPDATE_KEYBOARD_RESET,

};

enum Oryx_Event_Code {
    ORYX_EVT_LAYER = WEBUSB_EVT_SAFE_RANGE,
    ORYX_EVT_LIVE_TRAINING,
    ORYX_EVT_LIVE_UPDATE_GET_KEYCODE,
    ORYX_EVT_LIVE_UPDATE_SET_KEYCODE,
    ORYX_EVT_LIVE_UPDATE_KEYMAP_RESET,
    ORYX_EVT_LIVE_UPDATE_GET_BUFFER,
    ORYX_EVT_LIVE_UPDATE_SET_BUFFER,
    ORYX_EVT_LIVE_UPDATE_GET_LAYER_COUNT,
    ORYX_EVT_LIVE_UPDATE_GET_MACRO_COUNT,
    ORYX_EVT_LIVE_UPDATE_GET_MACRO_BUFFER_SIZE,
    ORYX_EVT_LIVE_UPDATE_GET_MACRO_BUFFER,
    ORYX_EVT_LIVE_UPDATE_SET_MACRO_BUFFER,
    ORYX_EVT_LIVE_UPDATE_MACRO_RESET,
    ORYX_EVT_LIVE_UPDATE_EEPROM_RESET,
    ORYX_EVT_LIVE_UPDATE_KEYBOARD_RESET,
    ORYX_EVT_KEYDOWN,
    ORYX_EVT_KEYUP,
};

#ifdef DYNAMIC_KEYMAP_ENABLE
enum dynamic_macros_keycodes {
    MACRO00 = 0x5F12,
    MACRO01,
    MACRO02,
    MACRO03,
    MACRO04,
    MACRO05,
    MACRO06,
    MACRO07,
    MACRO08,
    MACRO09,
    MACRO10,
    MACRO11,
    MACRO12,
    MACRO13,
    MACRO14,
    MACRO15,
};
#endif

extern bool oryx_state_live_training_enabled;

void oryx_init(void);
bool webusb_receive_oryx(uint8_t *data, uint8_t length);
void oryx_layer_event(void);
bool is_oryx_live_training_enabled(void);
bool process_record_oryx(uint16_t keycode, keyrecord_t *record);
void layer_state_set_oryx(layer_state_t state);
