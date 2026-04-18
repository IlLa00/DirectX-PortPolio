#include "framework.h"

StartScene::StartScene(GameState& state)
	: Scene(state)
{
	SBG = make_unique<StartBackGround>();
}

StartScene::~StartScene()
{
}

void StartScene::Update()
{
	SBG->Update();
}

void StartScene::Render()
{
	SBG->Render();
}

void StartScene::PostRender()
{
	ImGui::Text("DOWN SPACE - NEWT SCENE");
}
