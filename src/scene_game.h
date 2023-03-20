#pragma once
#include "main.h"
#include "virtual_keyboard.h"
// ...

struct Scene_Game : SceneBase {
	void Init() override;
	int Update() override;

	VirtualKeyboard vk;
};
