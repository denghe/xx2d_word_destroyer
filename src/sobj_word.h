#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_Word {
	Scene_Game* scene{};
	ptrdiff_t indexAtContainer{-1};
	xx::XY pos{};
	float speed;
	ptrdiff_t typedLen{};
	std::u32string txt;
	xx::SimpleLabel body;

	void Init(Scene_Game* const& scene_, size_t const& idx, xx::XY const& pos_, float const& speed_, std::u32string_view const& txt_);
	bool Update();
	void Draw();

	void ClearTyped();
	int Hit(char32_t const& c);	// 1: match, has left   0: match, finish   -1: no match
};
