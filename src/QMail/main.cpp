extern "C" {
#include "../../TerminalInterface/TerminalInterface/terminal_interface.h"
}
int main() {
	TIState* terminal_interface = TI_init(true);
	TI_clear(terminal_interface);
	TI_set_background_color(terminal_interface, TERM_COLOR_BLUE);
	TI_set_text_color(terminal_interface, TERM_COLOR_LIME);
	TI_write_no_wrap_sz(terminal_interface, "hello world!");
	TI_update_display(terminal_interface);
	return 0;
}
