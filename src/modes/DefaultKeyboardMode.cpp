#include "modes/DefaultKeyboardMode.hpp"

#include "core/socd.hpp"
#include "core/state.hpp"

DefaultKeyboardMode::DefaultKeyboardMode(socd::SocdType socd_type) {}

void DefaultKeyboardMode::UpdateKeys(InputState &inputs) {
    // Remapped for a silly classic FPS control scheme
    Press(HID_KEY_TAB, inputs.a0);
    Press(HID_KEY_A, inputs.a1);
    Press(HID_KEY_S, inputs.a2);
    Press(HID_KEY_D, inputs.a3);
    Press(HID_KEY_W, inputs.a4);

    Press(HID_KEY_C, inputs.mx);
    Press(HID_KEY_SPACE, inputs.my);

    Press(HID_KEY_1, inputs.p1);
    Press(HID_KEY_2, inputs.p2);
    Press(HID_KEY_3, inputs.p3);
    Press(HID_KEY_ESCAPE, inputs.p4);

    Press(HID_KEY_R, inputs.k1);
    Press(HID_KEY_F, inputs.k2);
    Press(HID_KEY_G, inputs.k3);
    Press(HID_KEY_V, inputs.k4);

    Press(HID_KEY_ARROW_LEFT, inputs.c1);
    Press(HID_KEY_ARROW_UP, inputs.c2);
    Press(HID_KEY_ARROW_RIGHT, inputs.c3);
    Press(HID_KEY_E, inputs.c4);
    Press(HID_KEY_ARROW_DOWN, inputs.c5);
}
