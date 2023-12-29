#include "modes/ProjectM.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

ProjectM::ProjectM(socd::SocdType socd_type, ProjectMOptions options) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::a1,  &InputState::a3, socd_type},
        socd::SocdPair{ &InputState::a2, &InputState::a4, socd_type},
        socd::SocdPair{ &InputState::c1, &InputState::c3, socd_type},
        socd::SocdPair{ &InputState::c2, &InputState::c5, socd_type},
    };

    _options = options;
    _horizontal_socd = false;
}

void ProjectM::HandleSocd(InputState &inputs) {
    _horizontal_socd = inputs.a1 && inputs.a3;
    InputMode::HandleSocd(inputs);
}

void ProjectM::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.c4;
    outputs.b = inputs.k1;
    outputs.x = inputs.k2;
    outputs.y = inputs.p2;
    // True Z press vs macro lightshield + A.
    if (_options.true_z_press || inputs.mx) {
        outputs.buttonR = inputs.p1;
    } else {
        outputs.a = inputs.c4 || inputs.p1;
    }
    if (inputs.nunchuk_connected) {
        outputs.triggerLDigital = inputs.nunchuk_z;
    } else {
        outputs.triggerLDigital = inputs.k4;
    }
    outputs.triggerRDigital = inputs.k4;
    outputs.start = inputs.p4;

    // Activate D-Pad layer by holding Mod X + Mod Y or Nunchuk C button.
    if ((inputs.mx && inputs.my) || inputs.nunchuk_c) {
        outputs.dpadUp = inputs.c2;
        outputs.dpadDown = inputs.c5;
        outputs.dpadLeft = inputs.c1;
        outputs.dpadRight = inputs.c3;
    }

    // Don't override dpad up if it's already pressed using the MX + MY dpad
    // layer.
    outputs.dpadUp = outputs.dpadUp || inputs.a0;

    if (inputs.select)
        outputs.dpadLeft = true;
    if (inputs.home)
        outputs.dpadRight = true;
}

void ProjectM::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
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

    if (directions.diagonal) {
        if (directions.y == 1) {
            outputs.leftStickX = 128 + (directions.x * 83);
            outputs.leftStickY = 128 + (directions.y * 93);
        }
    }

    if (inputs.mx) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 70);
        }
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 60);
        }

        if (directions.cx != 0) {
            outputs.rightStickX = 128 + (directions.cx * 65);
            outputs.rightStickY = 128 + (directions.y * 23);
        }

        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 70);
            outputs.leftStickY = 128 + (directions.y * 34);

            if (inputs.k1) {
                outputs.leftStickX = 128 + (directions.x * 85);
                outputs.leftStickY = 128 + (directions.y * 31);
            }

            if (inputs.k4) {
                outputs.leftStickX = 128 + (directions.x * 82);
                outputs.leftStickY = 128 + (directions.y * 35);
            }

            if (inputs.c2) {
                outputs.leftStickX = 128 + (directions.x * 77);
                outputs.leftStickY = 128 + (directions.y * 55);
            }

            if (inputs.c5) {
                outputs.leftStickX = 128 + (directions.x * 82);
                outputs.leftStickY = 128 + (directions.y * 36);
            }

            if (inputs.c1) {
                outputs.leftStickX = 128 + (directions.x * 84);
                outputs.leftStickY = 128 + (directions.y * 50);
            }

            if (inputs.c3) {
                outputs.leftStickX = 128 + (directions.x * 72);
                outputs.leftStickY = 128 + (directions.y * 61);
            }
        }
    }

    if (inputs.my) {
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 35);
        }
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 70);
        }

        if (directions.diagonal) {
            outputs.leftStickX = 128 + (directions.x * 28);
            outputs.leftStickY = 128 + (directions.y * 58);

            if (inputs.k1) {
                outputs.leftStickX = 128 + (directions.x * 28);
                outputs.leftStickY = 128 + (directions.y * 85);
            }

            if (inputs.k4) {
                outputs.leftStickX = 128 + (directions.x * 51);
                outputs.leftStickY = 128 + (directions.y * 82);
            }

            if (inputs.c2) {
                outputs.leftStickX = 128 + (directions.x * 55);
                outputs.leftStickY = 128 + (directions.y * 77);
            }

            if (inputs.c5) {
                outputs.leftStickX = 128 + (directions.x * 34);
                outputs.leftStickY = 128 + (directions.y * 82);
            }

            if (inputs.c1) {
                outputs.leftStickX = 128 + (directions.x * 40);
                outputs.leftStickY = 128 + (directions.y * 84);
            }

            if (inputs.c3) {
                outputs.leftStickX = 128 + (directions.x * 62);
                outputs.leftStickY = 128 + (directions.y * 72);
            }
        }
    }

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    // We don't apply this for c-up + c-left/c-right in case we want to implement
    // C-stick nair somehow.
    if (directions.cx != 0 && directions.cy == -1) {
        // 3000 9875 = 30 78
        outputs.rightStickX = 128 + (directions.cx * 35);
        outputs.rightStickY = 128 + (directions.cy * 98);
    }

    // Horizontal SOCD overrides X-axis modifiers (for ledgedash maximum jump
    // trajectory).
    if (_options.ledgedash_max_jump_traj && _horizontal_socd && !directions.vertical &&
        !shield_button_pressed) {
        outputs.leftStickX = 128 + (directions.x * 100);
    }

    if (inputs.p3) {
        outputs.triggerRAnalog = 49;
    }

    // Send lightshield input if we are using Z = lightshield + A macro.
    if (inputs.p1 && !(inputs.mx || _options.true_z_press)) {
        outputs.triggerRAnalog = 49;
    }

    if (outputs.triggerLDigital) {
        outputs.triggerLAnalog = 140;
    }

    if (outputs.triggerRDigital) {
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
