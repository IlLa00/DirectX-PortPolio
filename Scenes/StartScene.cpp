#include "framework.h"

StartScene::StartScene()
{
	SBG = new StartBackGround();
}

StartScene::~StartScene()
{
	delete SBG;
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
