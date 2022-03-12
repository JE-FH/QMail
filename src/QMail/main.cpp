extern "C" {
#include <terminal_interface.h>
}
#include <memory>
#include <stdexcept>
#include <iostream>
#include "TITerminalWindow.hpp"

int safe_main(std::shared_ptr<TIState> terminal_interface);

int main() {
	try {
		std::shared_ptr<TIState> terminal_interface = std::shared_ptr<TIState>(TI_init(true), [](TIState* p) { TI_free(p); });
		return safe_main(terminal_interface);
	} catch (const std::exception& e) {
		std::cout << "Uncaught error: " << e.what() << std::endl;
	}
}

int safe_main(std::shared_ptr<TIState> terminal_interface) {
	TITerminalWindow window = TITerminalWindow(terminal_interface);

	window.print(U"Hello world!", OverflowHandling::WRAP, OverflowHandling::SCROLL);

	TI_update_display(terminal_interface.get());

	uint32_t c = TI_read_key(terminal_interface.get());
	window.print(U"read key", OverflowHandling::WRAP, OverflowHandling::SCROLL);
	TI_update_display(terminal_interface.get());
	return 0;
}