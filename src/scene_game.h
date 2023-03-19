#pragma once
#include "main.h"
// ...

struct Scene_Game : SceneBase {
	void Init(GameLooper* looper) override;
	int Update() override;
};
