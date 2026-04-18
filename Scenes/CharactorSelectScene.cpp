#include "framework.h"

CharactorSelectScene::CharactorSelectScene(GameState& state)
	: Scene(state)
{
	BG = make_unique<BackGround>(L"Texture/CharactorSelectMap.png");
	Selectbox = make_unique<SelectBox>(L"Texture/SelectCharactor.png");
	boy = make_unique<Select>(true);
	girl =  make_unique<Select>(false);
}

CharactorSelectScene::~CharactorSelectScene()
{
}

void CharactorSelectScene::Update()
{
	boy->pos = Vector2(WIN_CENTER_X - 300.0f, WIN_CENTER_Y);
	girl->pos = Vector2(WIN_CENTER_X + 300.0f, WIN_CENTER_Y);

	BG->WorldUpdate();
	Selectbox->Update();
	boy->Update();
	girl->Update();

	const Vector2& click = m_state.mouse_click_pos;
	if (click.x > 260.0f && click.x < 410.0f && click.y > 185.0f && click.y < 535.0f) {
		m_state.gender = true;
		m_selected = true;
	} else if (click.x > 865.0f && click.x < 1015.0f && click.y > 185.0f && click.y < 535.0f) {
		m_state.gender = false;
		m_selected = true;
	}
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
	ImGui::SliderFloat2("Mouse Click pos", (float*)&g_state.mouse_click_pos, 0, WIN_WIDTH);
	ImGui::Text("Mouse Select Gender - Next Scene");
}

