#include "main.h"
#include "virtual_keyboard.h"

bool VirtualKeyboardItem::Inside(xx::XY const& p) {
	return p.x >= leftBottom.x && p.x <= rightTop.x
		&& p.y >= leftBottom.y && p.y <= rightTop.y;
}

void VirtualKeyboardItem::Init(VirtualKeyboard* const& owner_, xx::KbdKeys const& key_
	, std::string_view const& t1_, std::string_view const& t2_, xx::XY const& pos_, xx::XY const& wh_) {
	owner = owner_;
	key = key_;
	t1 = t1_;
	t2 = t2_;
	pos = pos_;
	wh = wh_;

	lb1.SetText(looper->fnt, t1);
	lb2.SetText(looper->fnt, t2);
	border.FillBoxPoints({}, wh);
	leftBottom = pos - wh / 2;
	rightTop = pos + wh / 2;
}

void VirtualKeyboardItem::DrawTxt() {
	// todo: switch txt1, 2 draw
	lb1.SetPosition(owner->pos + pos).Draw();
	// todo: set pos by owner->pos
}

void VirtualKeyboardItem::DrawBorder() {
	// todo: set pos by owner->pos
	border.SetPosition(owner->pos + pos).Draw();
}

void VirtualKeyboard::Init() {

	using namespace xx;
	std::array<KbdKeys, 54> keys;
	std::array<std::string_view, 54> txts1;
	std::array<std::string_view, 54> txts2;

	keys = {
		// ` 1 2 3 4 5 6 7 8 9 0 - = Backspace
		KbdKeys::Grave, KbdKeys::One, KbdKeys::Two, KbdKeys::Three, KbdKeys::Four,
		KbdKeys::Five, KbdKeys::Six, KbdKeys::Seven, KbdKeys::Eight, KbdKeys::Nine,
		KbdKeys::Zero, KbdKeys::Minus, KbdKeys::Equal, KbdKeys::Backspace,
		// Tab q w e r t y u i o p [ ] |
		KbdKeys::Tab, KbdKeys::Q, KbdKeys::W, KbdKeys::E, KbdKeys::R, KbdKeys::T,
		KbdKeys::Y, KbdKeys::U, KbdKeys::I, KbdKeys::O, KbdKeys::P,
		KbdKeys::LeftBracket, KbdKeys::RightBracket, KbdKeys::Backslash,
		// CapsLock a s d f g h j k l ; ' Enter
		KbdKeys::CapsLock, KbdKeys::A, KbdKeys::S, KbdKeys::D, KbdKeys::F,
		KbdKeys::G, KbdKeys::H, KbdKeys::J, KbdKeys::K, KbdKeys::L,
		KbdKeys::Semicolon, KbdKeys::Apostrophe, KbdKeys::Enter,
		// LeftShift z x c v b n m , . / RightShift
		KbdKeys::LeftShift, KbdKeys::Z, KbdKeys::X, KbdKeys::C, KbdKeys::V, KbdKeys::B,
		KbdKeys::N, KbdKeys::M,	KbdKeys::Comma, KbdKeys::Period, KbdKeys::Slash, KbdKeys::RightShift,
		// Space
		KbdKeys::Space
	};
	txts1 = {
		"`", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
		"Tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\",
		"CapsLock", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "Enter",
		"Shift", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "Shift",
		"Space"
	};
	txts2 = {
		"~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", "Backspace",
		"Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "|",
		"CapsLock", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "Enter",
		"Shift", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", "Shift",
		"Space"
	};

	items.reserve(keys.size());

	auto totalWidth1 = (width + margin) * 13 + width_backspace;
	auto totalWidth2 = width_tab + margin + (width + margin) * 12 + width_backslash;
	auto totalWidth3 = width_capslock + margin + (width + margin) * 11 + width_enter;
	auto totalWidth4 = width_left_shift + margin + (width + margin) * 10 + width_right_shift;
	assert(totalWidth1 = totalWidth2);
	assert(totalWidth1 = totalWidth3);
	assert(totalWidth1 = totalWidth4);
	auto totalHeight = height * 5 + margin * 4;

	xx::XY original = { -totalWidth1 / 2, totalHeight };

	size_t i = 0;
	auto xy = original;

	// ` 1 2 3 4 5 6 7 8 9 0 - = ........
	xy.y -= height / 2;
	for (; i < 13; i++) {
		xy.x += width / 2;
		items.emplace_back().Init(this, keys[i], txts1[i], txts2[i], xy, { width, height });
		xy.x += width / 2 + margin;
	}
	// ......................... Backspace
	{
		xy.x += width_backspace / 2;
		items.emplace_back().Init(this, keys[i], txts1[i], txts2[i], xy, { width_backspace, height });
		++i;
	}

	// Tab ...............................
	xy.x = original.x;
	xy.y -= height / 2 + margin + height / 2;
	{
		xy.x += width_tab / 2;
		items.emplace_back().Init(this, keys[i], txts1[i], txts2[i], xy, { width_tab, height });
		xy.x += width_tab / 2 + margin;
		++i;
	}
	// .... q w e r t y u i o p [ ]
	for (; i < 15+12; i++) {
		xy.x += width / 2;
		items.emplace_back().Init(this, keys[i], txts1[i], txts2[i], xy, { width, height });
		xy.x += width / 2 + margin;
	}

	//xy = { original.x, xy.y - siz.y - margin };

}

void VirtualKeyboard::Update() {
	pos = xx::engine.ninePoints[2];
	// todo
}

void VirtualKeyboard::Draw() {
	for (auto&& o : items) {
		o.DrawTxt();
	}
	for (auto&& o : items) {
		o.DrawBorder();
	}
}
