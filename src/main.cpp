#include "main.h"
#include "scene_menu.h"

int main() {
	return GameLooper{}.Run("xx2d's game: space shooter");
}

void GameLooper::Init() {
	fnt = xx::engine.LoadBMFont("res/coderscrux.fnt"sv);
	fpsViewer.Init(fnt);

	scene = xx::Make<Scene_Menu>();
	scene->Init(this);
}

int GameLooper::Update() {
	if (xx::engine.Pressed(xx::KbdKeys::Escape)) return 1;

	if (!scene) return 1;
	if (int r = scene->Update()) return r;

	fpsViewer.Update();
	return 0;
}
