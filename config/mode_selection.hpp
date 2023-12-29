#ifndef _CONFIG_MODE_SELECTION_HPP
#define _CONFIG_MODE_SELECTION_HPP

#include "core/state.hpp"
#include "modes/DefaultKeyboardMode.hpp"
#include "modes/FgcMode.hpp"
#include "modes/Melee20Button.hpp"
#include "modes/ProjectM.hpp"
#include "modes/RivalsOfAether.hpp"
#include "modes/Ultimate.hpp"

extern KeyboardMode *current_kb_mode;

void set_mode(CommunicationBackend *backend, ControllerMode *mode) {
    // Delete keyboard mode in case one is set, so we don't end up getting both controller and
    // keyboard inputs.
    delete current_kb_mode;
    current_kb_mode = nullptr;

    // Set new controller mode.
    backend->SetGameMode(mode);
}

void set_mode(CommunicationBackend *backend, KeyboardMode *mode) {
    // Delete and reassign current keyboard mode.
    delete current_kb_mode;
    current_kb_mode = mode;

    // Unset the current controller mode so backend only gives neutral inputs.
    backend->SetGameMode(nullptr);
}

void select_mode(CommunicationBackend *backend) {
    InputState &inputs = backend->GetInputs();
    // A0 + MX for changing modes
    // P1: Melee
    // P2: P+
    // P3: U
    // K1: FGC
    // K2: RoA
    if (inputs.mx && !inputs.my && inputs.a0) {
        if (inputs.p1) {
            set_mode(backend, new Melee20Button(socd::SOCD_NEUTRAL, { .crouch_walk_os = false }));
        } else if (inputs.p2) {
            set_mode(
                backend,
                new ProjectM(
                    socd::SOCD_NEUTRAL,
                    { .true_z_press = false, .ledgedash_max_jump_traj = true }
                )
            );
        } else if (inputs.p3) {
            set_mode(backend, new Ultimate(socd::SOCD_NEUTRAL));
        } else if (inputs.k1) {
            set_mode(backend, new FgcMode(socd::SOCD_NEUTRAL, socd::SOCD_DIR2_PRIORITY));
        } else if (inputs.k2) {
            set_mode(backend, new RivalsOfAether(socd::SOCD_NEUTRAL));
        }
        // Keyboard mode: MY + A0 -> P1
    } else if (inputs.my && !inputs.mx && inputs.a0) {
        if (inputs.p1) {
            set_mode(backend, new DefaultKeyboardMode(socd::SOCD_2IP));
        }
    }
}

#endif
