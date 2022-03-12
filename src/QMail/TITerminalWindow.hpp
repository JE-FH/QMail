#pragma once
#include "ITerminalWindow.hpp"
#include <memory>

class TITerminalWindow : public ITerminalWindow {
private:


	std::shared_ptr<TIState> ti_state;
public:
	TITerminalWindow(std::shared_ptr<TIState> ti_state);
	~TITerminalWindow();
	size_t get_width() override;
	size_t get_height() override;
	
	size_t get_cursor_x() override;
	size_t get_cursor_y() override;
	
	void set_cursor_pos(size_t x, size_t y) override;

	void set_text_color(TermColor color) override;
	void set_background_color(TermColor color) override;

	void print(std::u32string_view str, OverflowHandling width_of, OverflowHandling height_of) override;

	std::unique_ptr<ITerminalWindow> create_sub_window(size_t x, size_t y, size_t w, size_t h) override;

	/**
	 * @brief Set the border object
	 * 
	 * @param border_chars in the following order
	 * left top-left top top-right right bottom-right bottom bottom-left
	 */
	void set_border_chars(char32_t border_chars[8]) override;
};