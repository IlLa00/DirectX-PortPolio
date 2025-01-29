#include "framework.h"

vsChampionScene::vsChampionScene()
{
	BG = new BackGround(L"Texture/ChampionMap.png"); // 배경화면 설정
	field[0] = new BattleField(Vector2(WIN_CENTER_X / 2, WIN_CENTER_Y + 145),
		L"Texture/BattleBackGround.png", 1010, 1516, 161, 17);
	field[1] = new BattleField(Vector2(WIN_CENTER_X + 350, WIN_CENTER_Y),
		L"Texture/BattleBackGround.png", 1140, 1464, 124, 29);

	manager = new BattleManager(false);
}

vsChampionScene::~vsChampionScene()
{
	delete BG;
	delete field[0];
	delete field[1];
	delete manager;
}

void vsChampionScene::Update()
{
	BG->Update();
	field[0]->Update();
	field[1]->Update();
	manager->Update();
}

void vsChampionScene::Render()
{
	BG->Render();
	field[0]->Render();
	field[1]->Render();
	manager->Render();
}

void vsChampionScene::PostRender()
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
	ImGui::Text("Enemy First Pokemon Survive : %s", manager->GetEnemyFirstPokemonSurvive() ? "true" : "false");
	ImGui::Text("Enemy Second Pokemon Survive : %s", manager->GetEnemySecondPokemonSurvive() ? "true" : "false");
	ImGui::Text("Enemy Third Pokemon Survive : %s", manager->GetEnemyThirdPokemonSurvive() ? "true" : "false");
}
