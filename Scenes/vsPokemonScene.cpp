#include "framework.h"

vsPokemonScene::vsPokemonScene()
{
	BG = new BackGround(L"Texture/PokemonBattleMap.png"); // 배경화면 설정
	field[0] = new BattleField(Vector2(WIN_CENTER_X / 2, WIN_CENTER_Y + 145),
		L"Texture/BattleBackGround.png", 896, 936, 152, 22);
	field[1] = new BattleField(Vector2(WIN_CENTER_X + 350, WIN_CENTER_Y),
		L"Texture/BattleBackGround.png", 1025, 886, 126, 32); 

	manager = new BattleManager(true);
}

vsPokemonScene::~vsPokemonScene()
{
	delete BG;
	delete field[0];
	delete field[1];
	delete manager;
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
	ImGui::SliderFloat2("Mouse Click pos", (float*)&mouse_click_pos, 0, 1280, NULL);
	ImGui::Text("My Pokemon HP : %f", manager->GetMyPokemonHP());
	ImGui::Text("Enemy Pokemon HP : %f", manager->GetEnemyPokemonHP());
	ImGui::Text("My First Pokemon : %s", manager->GetMyFirstPokemonSurvive() ? "true" : "false");
	ImGui::Text("My Second Pokemon : %s", manager->GetMySecondPokemonSurvive() ? "true" : "false");
	ImGui::Text("My Third Pokemon : %s", manager->GetMyThirdPokemonSurvive() ? "true" : "false");
}
