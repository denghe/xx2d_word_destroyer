#pragma once
#include "main.h"

struct Scene_Menu : SceneBase {
	Menu menu;
	void Init(GameLooper* looper) override;
	int Update() override;
};
