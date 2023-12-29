#include "modes/FgcMode.hpp"

FgcMode::FgcMode(socd::SocdType horizontal_socd, socd::SocdType vertical_socd) {
    _socd_pair_count = 7;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::a1,  &InputState::a3, horizontal_socd         },
 /*  TODO: Vertical SOCD should be "up always overrides down" to match FGC standard. 2IP is
  close enough for now. */
        socd::SocdPair{ &InputState::a2, &InputState::my, vertical_socd           },
        socd::SocdPair{ &InputState::a2, &InputState::c5, vertical_socd           },
        socd::SocdPair{ &InputState::a2, &InputState::a4, vertical_socd           },
 /* Up inputs override each other if multiple are pressed */
        socd::SocdPair{ &InputState::my, &InputState::c5, socd::SOCD_DIR1_PRIORITY},
        socd::SocdPair{ &InputState::a4, &InputState::my, socd::SOCD_DIR1_PRIORITY},
        socd::SocdPair{ &InputState::a4, &InputState::c5, socd::SOCD_DIR1_PRIORITY},
    };
}

void FgcMode::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Directions
    outputs.dpadLeft = inputs.a1;
    outputs.dpadRight = inputs.a3;
    outputs.dpadDown = inputs.a2;
    outputs.dpadUp = inputs.my || inputs.c5 || inputs.a4;

    // Menu keys
    outputs.start = inputs.c3;
    outputs.select = inputs.c2;
    outputs.home = inputs.c4;

    // Right hand bottom row
    outputs.a = inputs.k1;
    outputs.b = inputs.k2;
    outputs.triggerRDigital = inputs.k3;
    outputs.triggerLDigital = inputs.k4;

    // Right hand top row
    outputs.x = inputs.p1;
    outputs.y = inputs.p2;
    outputs.buttonR = inputs.p3;
    outputs.buttonL = inputs.p4;
}

void FgcMode::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    outputs.leftStickX = 128;
    outputs.leftStickY = 128;
    outputs.rightStickX = 128;
    outputs.rightStickY = 128;
    outputs.triggerLAnalog = outputs.triggerLDigital ? 255 : 0;
    outputs.triggerRAnalog = outputs.triggerRDigital ? 255 : 0;
}
