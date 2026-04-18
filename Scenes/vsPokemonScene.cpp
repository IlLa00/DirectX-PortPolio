#include "framework.h"

vsPokemonScene::vsPokemonScene(GameState& state)
	: Scene(state)
{
	BG = make_unique<BackGround>(L"Texture/PokemonBattleMap.png"); // ï¿½ï¿½ï¿½È?¿½ï¿?ï¿½ï¿½ï¿½ï¿½
	field[0] = make_unique<BattleField>(Vector2(WIN_CENTER_X / 2, WIN_CENTER_Y + 145),
		L"Texture/BattleBackGround.png", 896, 936, 152, 22);
	field[1] = make_unique<BattleField>(Vector2(WIN_CENTER_X + 350, WIN_CENTER_Y),
		L"Texture/BattleBackGround.png", 1025, 886, 126, 32); 

	manager = make_unique<BattleManager>(true);
}

vsPokemonScene::~vsPokemonScene()
{
}

void vsPokemonScene::Update()
{
	BG->Update();
	field[0]->Update();
	field[1]->Update();
	manager->Update();
}

void vsPokemonScene::Render()
{
	BG->Render();
	field[0]->Render();
	field[1]->Render();
	manager->Render();
}

void vsPokemonScene::PostRender()
{
	ImGui::Text("Attack : %s", manager->GetAttackState() ? "true" : "false");
	ImGui::Text("Recovery : %s", manager->GetRecoveryState() ? "true" : "false");
	ImGui::Text("Change : %s", manager->GetChangeState() ? "true" : "false");
	ImGui::SliderFloat2("Mouse Click pos", (float*)&g_state.mouse_click_pos, 0, 1280, NULL);
	ImGui::Text("My Pokemon HP : %f", manager->GetMyPokemonHP());
	ImGui::Text("Enemy Pokemon HP : %f", manager->GetEnemyPokemonHP());
	ImGui::Text("My First Pokemon : %s", manager->GetMyFirstPokemonSurvive() ? "true" : "false");
	ImGui::Text("My Second Pokemon : %s", manager->GetMySecondPokemonSurvive() ? "true" : "false");
	ImGui::Text("My Third Pokemon : %s", manager->GetMyThirdPokemonSurvive() ? "true" : "false");
}

void vsPokemonScene::OnEnter()
{
	m_state.is_vsPokemon = false;
	manager = make_unique<BattleManager>(true);
}
