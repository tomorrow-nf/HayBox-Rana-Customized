#include "modes/RivalsOfAether.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

RivalsOfAether::RivalsOfAether(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::a1,  &InputState::a3, socd_type},
        socd::SocdPair{ &InputState::a2, &InputState::a4, socd_type},
        socd::SocdPair{ &InputState::c1, &InputState::c3, socd_type},
        socd::SocdPair{ &InputState::c2, &InputState::c5, socd_type},
    };
}

void RivalsOfAether::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.c4;
    outputs.b = inputs.k1;
    outputs.x = inputs.k2;
    outputs.y = inputs.p2;
    outputs.buttonR = inputs.p1;
    if (inputs.nunchuk_connected) {
        // Lightshield with C button.
        if (inputs.nunchuk_c) {
            outputs.triggerLAnalog = 49;
        }
        outputs.triggerLDigital = inputs.nunchuk_z;
    } else {
        outputs.triggerLDigital = inputs.k3;
    }
    outputs.triggerRDigital = inputs.k4;
    outputs.start = inputs.p4;
    outputs.select = inputs.select;
    outputs.home = inputs.home;
    outputs.leftStickClick = inputs.p3;
    outputs.rightStickClick = inputs.a0;

    // Activate D-Pad layer by holding Mod X + Mod Y.
    if (inputs.mx && inputs.my) {
        outputs.dpadUp = inputs.c2;
        outputs.dpadDown = inputs.c5;
        outputs.dpadLeft = inputs.c1;
        outputs.dpadRight = inputs.c3;
    }
}

void RivalsOfAether::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.a1,
        inputs.a3,
        inputs.a2,
        inputs.a4,
        inputs.c1,
        inputs.c3,
        inputs.c5,
        inputs.c2,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.k3 || inputs.k4;

    // 48 total DI angles, 24 total Up b angles, 16 total airdodge angles

    if (inputs.mx) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 66);
            // MX Horizontal Tilts
            if (inputs.c4) {
                outputs.leftStickX = 128 + (directions.x * 44);
            }
        }

        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 44);
            // MX Vertical Tilts
            if (inputs.c4) {
                outputs.leftStickY = 128 + (directions.y * 67);
            }
        }

        /* Extra DI, Air Dodge, and Up B angles */
        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 59);
            outputs.leftStickY = 128 + (directions.y * 23);

            // Angles just for DI and Up B
            if (inputs.c5) {
                outputs.leftStickX = 128 + (directions.x * 49);
                outputs.leftStickY = 128 + (directions.y * 24);
            }

            // Angles just for DI
            if (inputs.c1) {
                outputs.leftStickX = 128 + (directions.x * 52);
                outputs.leftStickY = 128 + (directions.y * 31);
            }

            if (inputs.c2) {
                outputs.leftStickX = 128 + (directions.x * 49);
                outputs.leftStickY = 128 + (directions.y * 35);
            }

            if (inputs.c3) {
                outputs.leftStickX = 128 + (directions.x * 51);
                outputs.leftStickY = 128 + (directions.y * 43);
            }
        }
    }

    if (inputs.my) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 44);
        }

        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 67);
        }

        /* Extra DI, Air Dodge, and Up B angles */
        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 44);
            outputs.leftStickY = 128 + (directions.y * 113);

            // Angles just for DI and Up B
            if (inputs.c5) {
                outputs.leftStickX = 128 + (directions.x * 44);
                outputs.leftStickY = 128 + (directions.y * 90);
            }

            // Angles just for DI
            if (inputs.c1) {
                outputs.leftStickX = 128 + (directions.x * 44);
                outputs.leftStickY = 128 + (directions.y * 74);
            }

            if (inputs.c2) {
                outputs.leftStickX = 128 + (directions.x * 45);
                outputs.leftStickY = 128 + (directions.y * 63);
            }

            if (inputs.c3) {
                outputs.leftStickX = 128 + (directions.x * 47);
                outputs.leftStickY = 128 + (directions.y * 57);
            }
        }
    }

    // Shut off C-stick when using D-Pad layer.
    if (inputs.mx && inputs.my) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
