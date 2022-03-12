#include "TITerminalWindow.hpp"
#include <stdexcept>

TITerminalWindow::TITerminalWindow(std::shared_ptr<TIState> ti_state) {
	this->ti_state = std::move(ti_state);
}


TITerminalWindow::~TITerminalWindow() {}

size_t TITerminalWindow::get_width() {
	int rv = 0;
	TI_get_size(ti_state.get(), &rv, nullptr);
	return (size_t)rv;
}

size_t TITerminalWindow::get_height() {
	int rv = 0;
	TI_get_size(ti_state.get(), nullptr, &rv);
	return (size_t)rv;
}

size_t TITerminalWindow::get_cursor_x() {
	int rv = 0;
	TI_get_cursor_pos(ti_state.get(), &rv, nullptr);
	return (size_t)rv;
}

size_t TITerminalWindow::get_cursor_y() {
	int rv = 0;
	TI_get_cursor_pos(ti_state.get(), nullptr, &rv);
	return (size_t)rv;
}

void TITerminalWindow::set_cursor_pos(size_t x, size_t y) {
	if (x > ((size_t) INT_MAX)) {
		x = INT_MAX;
	}

	if (y > ((size_t) INT_MAX)) {
		y = INT_MAX;
	}
	TI_set_cursor_pos(ti_state.get(), x, y);
}

void TITerminalWindow::set_text_color(TermColor color) {
	TI_set_text_color(ti_state.get(), color);
}

void TITerminalWindow::set_background_color(TermColor color) {
	TI_set_background_color(ti_state.get(), color);
}

void TITerminalWindow::print(std::u32string_view str, OverflowHandling width_of, OverflowHandling height_of) {
	if (height_of == OverflowHandling::WRAP) {
		throw std::runtime_error("Height overflow cannot wrap");
	}
	if (width_of == OverflowHandling::SCROLL) {
		throw std::runtime_error("Horizontal scrolling not implemented yet");
	}
	size_t w = get_width();
	size_t h = get_height();
	auto background_color = TI_get_background_color(ti_state.get());
	auto text_color = TI_get_text_color(ti_state.get());
	for (auto c : str) {
		size_t x = get_cursor_x();
		size_t y = get_cursor_y();
		if (c == '\n') {
			if (y + 1 < h) {
				x = 0;
				y += 1;
				set_cursor_pos(x, y);
			} else {
				if (height_of == OverflowHandling::HIDE) {
					return;
				} else if (height_of == OverflowHandling::SCROLL) {
					TI_scroll_down(ti_state.get(), 1);
					x = 0;
					set_cursor_pos(x, y);
				}
			}
		} else {
			TI_write_single(ti_state.get(), c, text_color, background_color);
			if (x + 1 < w) {
				x += 1;
			} else if (y + 1 < h) {
				if (width_of == OverflowHandling::WRAP) {
					x = 0;
					y += 1;
					set_cursor_pos(x, y);
				}
			} else {
				if (width_of == OverflowHandling::WRAP && height_of == OverflowHandling::SCROLL) {
					TI_scroll_down(ti_state.get(), 1);
					set_cursor_pos(0, y);
				} else if (width_of == OverflowHandling::HIDE && height_of == OverflowHandling::SCROLL) {
					continue;
				} else if (width_of == OverflowHandling::WRAP && height_of == OverflowHandling::HIDE) {
					return;
				} else if (width_of == OverflowHandling::HIDE && height_of == OverflowHandling::HIDE) {
					return;
				}
			}
		}
	}
}

std::unique_ptr<ITerminalWindow> TITerminalWindow::create_sub_window(size_t x, size_t y, size_t w, size_t h) {
	return nullptr;
}

void TITerminalWindow::set_border_chars(char32_t border_chars[8]) {
	
}