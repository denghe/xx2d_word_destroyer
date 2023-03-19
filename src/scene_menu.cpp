#include "main.h"
#include "scene_menu.h"
#include "scene_game.h"

void Scene_Menu::Init(GameLooper* looper) {
	this->looper = looper;
	menu.Init();
	menu.items.emplace_back().Init(this, {0, 150}, "play", 128, [this]() {
		this->looper->DelaySwitchTo<Scene_Game>();
	});
	menu.items.emplace_back().Init(this, {0, -150}, "exit", 128, [this]() {
		this->looper->scene.Reset();
	});
}

int Scene_Menu::Update() {
	menu.Update();

	menu.Draw();
	return 0;
}
