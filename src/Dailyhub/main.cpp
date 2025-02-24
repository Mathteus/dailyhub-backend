#include <cstdlib>
#include "Dailyhub/application.hpp"

int main() {
    try {
        const Dailyhub::Application app;
    } catch(std::exception& e) {
        spdlog::error(e.what());
    }
	return EXIT_SUCCESS;
}
