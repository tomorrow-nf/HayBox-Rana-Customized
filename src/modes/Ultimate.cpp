/* Ultimate profile by Taker */
#include "modes/Ultimate.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

Ultimate::Ultimate(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::a1,  &InputState::a3, socd_type},
        socd::SocdPair{ &InputState::a2, &InputState::a4, socd_type},
        socd::SocdPair{ &InputState::c1, &InputState::c3, socd_type},
        socd::SocdPair{ &InputState::c2, &InputState::c5, socd_type},
    };
}

void Ultimate::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.c4;
    outputs.b = inputs.k1;
    outputs.x = inputs.k2;
    outputs.y = inputs.p2;
    outputs.buttonR = inputs.p1;
    outputs.triggerLDigital = inputs.k3;
    outputs.triggerRDigital = inputs.p3;
    outputs.start = inputs.p4;
    outputs.select = inputs.a0;
    outputs.home = inputs.k4;

    // Turn on D-Pad layer by holding Mod X + Mod Y or Nunchuk C button.
    if ((inputs.mx && inputs.my) || inputs.nunchuk_c) {
        outputs.dpadUp = inputs.c2;
        outputs.dpadDown = inputs.c5;
        outputs.dpadLeft = inputs.c1;
        outputs.dpadRight = inputs.c3;
    }
}

void Ultimate::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
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

    bool shield_button_pressed = inputs.k3 || inputs.p3;

    if (inputs.mx) {
        // MX + Horizontal = 6625 = 53
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 53);
            // Horizontal Shield tilt = 51
            if (shield_button_pressed) {
                outputs.leftStickX = 128 + (directions.x * 51);
            }
            // Horizontal Tilts = 36
            if (inputs.c4) {
                outputs.leftStickX = 128 + (directions.x * 36);
            }
        }
        // MX + Vertical = 44
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 44);
            // Vertical Shield Tilt = 51
            if (shield_button_pressed) {
                outputs.leftStickY = 128 + (directions.y * 51);
            }
        }
        if (directions.diagonal) {
            // MX + q1/2/3/4 = 53 35
            outputs.leftStickX = 128 + (directions.x * 53);
            outputs.leftStickY = 128 + (directions.y * 35);
            if (shield_button_pressed) {
                // MX + L, R, LS, and MS + q1/2/3/4 = 6375 3750 = 51 30
                outputs.leftStickX = 128 + (directions.x * 51);
                outputs.leftStickY = 128 + (directions.y * 30);
            }
        }

        // Angled fsmash/ftilt with C-Stick + MX
        if (directions.cx != 0) {
            outputs.rightStickX = 128 + (directions.cx * 127);
            outputs.rightStickY = 128 + (directions.y * 59);
        }

        /* Up B angles */
        if (directions.diagonal && !shield_button_pressed) {
            // (33.44) = 53 35
            outputs.leftStickX = 128 + (directions.x * 53);
            outputs.leftStickY = 128 + (directions.y * 35);
            // (39.05) = 53 43
            if (inputs.c5) {
                outputs.leftStickX = 128 + (directions.x * 53);
                outputs.leftStickY = 128 + (directions.y * 43);
            }
            // (36.35) = 53 39
            if (inputs.c1) {
                outputs.leftStickX = 128 + (directions.x * 53);
                outputs.leftStickY = 128 + (directions.y * 39);
            }
            // (30.32) = 56 41
            if (inputs.c2) {
                outputs.leftStickX = 128 + (directions.x * 53);
                outputs.leftStickY = 128 + (directions.y * 31);
            }
            // (27.85) = 49 42
            if (inputs.c3) {
                outputs.leftStickX = 128 + (directions.x * 53);
                outputs.leftStickY = 128 + (directions.y * 28);
            }

            /* Extended Up B Angles */
            if (inputs.k1) {
                // (33.29) = 67 44
                outputs.leftStickX = 128 + (directions.x * 67);
                outputs.leftStickY = 128 + (directions.y * 44);
                // (39.38) = 67 55
                if (inputs.c5) {
                    outputs.leftStickX = 128 + (directions.x * 67);
                    outputs.leftStickY = 128 + (directions.y * 55);
                }
                // (36.18) = 67 49
                if (inputs.c1) {
                    outputs.leftStickX = 128 + (directions.x * 67);
                    outputs.leftStickY = 128 + (directions.y * 49);
                }
                // (30.2) = 67 39
                if (inputs.c2) {
                    outputs.leftStickX = 128 + (directions.x * 67);
                    outputs.leftStickY = 128 + (directions.y * 39);
                }
                // (27.58) = 67 35
                if (inputs.c3) {
                    outputs.leftStickX = 128 + (directions.x * 67);
                    outputs.leftStickY = 128 + (directions.y * 35);
                }
            }

            // Angled Ftilts
            if (inputs.c4) {
                outputs.leftStickX = 128 + (directions.x * 36);
                outputs.leftStickY = 128 + (directions.y * 26);
            }
        }
    }

    if (inputs.my) {
        // MY + Horizontal (even if shield is held) = 41
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 41);
            // MY Horizontal Tilts
            if (inputs.c4) {
                outputs.leftStickX = 128 + (directions.x * 36);
            }
        }
        // MY + Vertical (even if shield is held) = 53
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 53);
            // MY Vertical Tilts
            if (inputs.c4) {
                outputs.leftStickY = 128 + (directions.y * 36);
            }
        }
        if (directions.diagonal) {
            // MY + q1/2/3/4 = 35 59
            outputs.leftStickX = 128 + (directions.x * 35);
            outputs.leftStickY = 128 + (directions.y * 53);
            if (shield_button_pressed) {
                // MY + L, R, LS, and MS + q1/2 = 38 70
                outputs.leftStickX = 128 + (directions.x * 38);
                outputs.leftStickY = 128 + (directions.y * 70);
                // MY + L, R, LS, and MS + q3/4 = 40 68
                if (directions.x == -1) {
                    outputs.leftStickX = 128 + (directions.x * 40);
                    outputs.leftStickY = 128 + (directions.y * 68);
                }
            }
        }

        /* Up B angles */
        if (directions.diagonal && !shield_button_pressed) {
            // (56.56) = 35 53
            outputs.leftStickX = 128 + (directions.x * 35);
            outputs.leftStickY = 128 + (directions.y * 53);
            // (50.95) = 43 53
            if (inputs.c5) {
                outputs.leftStickX = 128 + (directions.x * 43);
                outputs.leftStickY = 128 + (directions.y * 53);
            }
            // (53.65) = 39 53
            if (inputs.c1) {
                outputs.leftStickX = 128 + (directions.x * 49);
                outputs.leftStickY = 128 + (directions.y * 53);
            }
            // (59.68) = 31 53
            if (inputs.c2) {
                outputs.leftStickX = 128 + (directions.x * 31);
                outputs.leftStickY = 128 + (directions.y * 53);
            }
            // (62.15) = 28 53
            if (inputs.c3) {
                outputs.leftStickX = 128 + (directions.x * 28);
                outputs.leftStickY = 128 + (directions.y * 53);
            }

            /* Extended Up B Angles */
            if (inputs.k1) {
                // (56.71) = 44 67
                outputs.leftStickX = 128 + (directions.x * 44);
                outputs.leftStickY = 128 + (directions.y * 67);
                // (50.62) = 55 67
                if (inputs.c5) {
                    outputs.leftStickX = 128 + (directions.x * 55);
                    outputs.leftStickY = 128 + (directions.y * 67);
                }
                // (53.82) = 49 67
                if (inputs.c1) {
                    outputs.leftStickX = 128 + (directions.x * 49);
                    outputs.leftStickY = 128 + (directions.y * 67);
                }
                // (59.8) = 39 67
                if (inputs.c2) {
                    outputs.leftStickX = 128 + (directions.x * 39);
                    outputs.leftStickY = 128 + (directions.y * 67);
                }
                // (62.42) = 35 67
                if (inputs.c3) {
                    outputs.leftStickX = 128 + (directions.x * 35);
                    outputs.leftStickY = 128 + (directions.y * 67);
                }
            }

            // MY Pivot Uptilt/Dtilt
            if (inputs.c4) {
                outputs.leftStickX = 128 + (directions.x * 34);
                outputs.leftStickY = 128 + (directions.y * 38);
            }
        }
    }

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    if (directions.cx != 0 && directions.cy != 0) {
        // 5250 8500 = 42 68
        outputs.rightStickX = 128 + (directions.cx * 42);
        outputs.rightStickY = 128 + (directions.cy * 68);
    }

    if (inputs.k3) {
        outputs.triggerLAnalog = 140;
    }

    if (inputs.p3) {
        outputs.triggerRAnalog = 140;
    }

    // Shut off C-stick when using D-Pad layer.
    if ((inputs.mx && inputs.my) || inputs.nunchuk_c) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}