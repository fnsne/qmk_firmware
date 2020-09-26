#include "onekey.h"

void keyboard_pre_init_user(void) {
    setPinOutput(C13);
    writePin(C13, true);
}
