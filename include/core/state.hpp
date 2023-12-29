#ifndef _CORE_STATE_HPP
#define _CORE_STATE_HPP

#include "stdlib.hpp"

// Button state.
typedef struct inputstate {
    // Rectangle inputs.
    bool a0 = false;
    bool a1 = false;
    bool a2 = false;
    bool a3 = false;
    bool a4 = false;

    bool c1 = false;
    bool c2 = false;
    bool c3 = false;
    bool c4 = false;
    bool c5 = false;

    bool k1 = false;
    bool k2 = false;
    bool k3 = false;
    bool k4 = false;

    bool p1 = false;
    bool p2 = false;
    bool p3 = false;
    bool p4 = false;

    bool select = false;
    bool home = false;
    bool mx = false;
    bool my = false;

    // Nunchuk inputs.
    bool nunchuk_connected = false;
    int8_t nunchuk_x = 0;
    int8_t nunchuk_y = 0;
    bool nunchuk_c = false;
    bool nunchuk_z = false;
} InputState;

// State describing stick direction at the quadrant level.
typedef struct {
    bool horizontal;
    bool vertical;
    bool diagonal;
    int8_t x;
    int8_t y;
    int8_t cx;
    int8_t cy;
} StickDirections;

// Output state.
typedef struct outputstate {
    // Digital outputs.
    bool a = false;
    bool b = false;
    bool x = false;
    bool y = false;
    bool buttonL = false;
    bool buttonR = false;
    bool triggerLDigital = false;
    bool triggerRDigital = false;
    bool start = false;
    bool select = false;
    bool home = false;
    bool dpadUp = false;
    bool dpadDown = false;
    bool dpadLeft = false;
    bool dpadRight = false;
    bool leftStickClick = false;
    bool rightStickClick = false;

    // Analog outputs.
    uint8_t leftStickX = 128;
    uint8_t leftStickY = 128;
    uint8_t rightStickX = 128;
    uint8_t rightStickY = 128;
    uint8_t triggerRAnalog = 0;
    uint8_t triggerLAnalog = 0;
} OutputState;

#endif