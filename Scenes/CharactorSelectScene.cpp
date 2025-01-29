#include "framework.h"

CharactorSelectScene::CharactorSelectScene()
{
	BG = new BackGround(L"Texture/CharactorSelectMap.png");
	Selectbox = new SelectBox(L"Texture/SelectCharactor.png");
	boy = new Select(true);
	girl =  new Select(false);
}

CharactorSelectScene::~CharactorSelectScene()
{
	delete BG;
	delete Selectbox;
	delete boy;
	delete girl;
}

void CharactorSelectScene::Update()
{
	boy->pos = Vector2(WIN_CENTER_X - 300.0f, WIN_CENTER_Y);
	girl->pos = Vector2(WIN_CENTER_X + 300.0f, WIN_CENTER_Y);

	BG->WorldUpdate();
	Selectbox->Update();
	boy->Update();
	girl->Update();

}

void CharactorSelectScene::Render()
{
	BG->Render();
	Selectbox->Render();
	boy->Render();
	girl->Render();

}

void CharactorSelectScene::PostRender()
{
	ImGui::SliderFloat2("Mouse Click pos", (float*)&mouse_click_pos, 0, WIN_WIDTH);
	ImGui::Text("Mouse Select Gender - Next Scene");
}

