#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <memory>

extern "C" {
#include <terminal_interface.h>
}

enum class OverflowHandling {
	SCROLL,
	WRAP,
	HIDE
};


class ITerminalWindow {
public:
	virtual ~ITerminalWindow() {}

	virtual size_t get_width() = 0;
	virtual size_t get_height() = 0;
	
	virtual size_t get_cursor_x() = 0;
	virtual size_t get_cursor_y() = 0;
	
	virtual void set_cursor_pos(size_t x, size_t y) = 0;

	virtual void set_text_color(TermColor color) = 0;
	virtual void set_background_color(TermColor color) = 0;

	virtual void print(std::u32string_view str, OverflowHandling width_of, OverflowHandling height_of) = 0;

	virtual std::unique_ptr<ITerminalWindow> create_sub_window(size_t x, size_t y, size_t w, size_t h) = 0;

	/**
	 * @brief Set the border object
	 * 
	 * @param border_chars in the following order
	 * left top-left top top-right right bottom-right bottom bottom-left
	 */
	virtual void set_border_chars(char32_t border_chars[8]) = 0;
};
