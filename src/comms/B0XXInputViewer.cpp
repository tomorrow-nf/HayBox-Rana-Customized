#include "comms/B0XXInputViewer.hpp"

#include "core/InputSource.hpp"
#include "serial.hpp"

#define ASCII_BIT(x) (x ? '1' : '0');

B0XXInputViewer::B0XXInputViewer(InputSource **input_sources, size_t input_source_count)
    : CommunicationBackend(input_sources, input_source_count) {
    serial::init(115200);
}

B0XXInputViewer::~B0XXInputViewer() {
    serial::close();
}

void B0XXInputViewer::SendReport() {
    // Not using, do nothing
}