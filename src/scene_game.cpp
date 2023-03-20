#include "main.h"
#include "scene_game.h"
// ...

void Scene_Game::Init() {
	vk.Init();
}

int Scene_Game::Update() {
	vk.Update();
	//...
	vk.Draw();
	//...
	return 0;
}
