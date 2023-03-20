#pragma once
#include "xx2d.h"

struct VirtualKeyboard;
struct VirtualKeyboardItem {
	VirtualKeyboard* owner{};
	xx::KbdKeys key{};
	std::string t1, t2;
	xx::XY pos{}, wh{}, leftBottom{}, rightTop{};	// bounding box

	xx::Label lb1, lb2;
	xx::LineStrip border;

	void Init(VirtualKeyboard* const& owner_, xx::KbdKeys const& k, std::string_view const& t1
		, std::string_view const& t2, xx::XY const& pos_, xx::XY const& wh_);
	bool Inside(xx::XY const& p);
	void DrawTxt();
	void DrawBorder();
};

struct VirtualKeyboard {
	std::vector<VirtualKeyboardItem> items;
	float margin{ 16 }, width{ 80 }, height{ 80 };	// every key display config. total width = 1468
	float width_backspace{ 220 };
	float width_tab{ 180 }, width_backslash{ 120 };
	float width_capslock{ 200 }, width_enter{ 196 };
	float width_left_shift{ 246 }, width_right_shift{ 246 };
	float width_space{ 480 };
	xx::XY pos{};	// current root pos
	// todo: shift, capslock check
	void Init();
	void Update();
	void Draw();

	// show? hide? key press callback? blink effect tips?
};
