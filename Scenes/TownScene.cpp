#include "framework.h"

TownScene::TownScene()
{
	// 맵 1
	BG[0] = new BackGround(L"Texture/StartMap.png"); 
	
	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X - 205, WIN_CENTER_Y + 110), Vector2(160, 80), Vector2(1, 1), 0.0f)); 
	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X + 205, WIN_CENTER_Y + 110), Vector2(240, 50), Vector2(1, 1), 0.0f)); 
	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X + 205, WIN_CENTER_Y - 120), Vector2(160, 80), Vector2(1, 1), 0.0f)); 
	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X - 205, WIN_CENTER_Y - 130), Vector2(240, 100), Vector2(1, 1), 0.0f)); 
	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X - 285, WIN_CENTER_Y - 310), Vector2(210, 90), Vector2(1, 1), 0.0f)); 
	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X + 285, WIN_CENTER_Y - 310), Vector2(210, 90), Vector2(1, 1), 0.0f)); 
	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X + 20, WIN_CENTER_Y - 20), Vector2(40, 20), Vector2(1, 1), 0.0f)); 
	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X / 6, WIN_CENTER_Y), Vector2(250, WIN_HEIGHT), Vector2(1, 1), 0.0f)); 
	obstackle_list.push_back(new Obstackle(Vector2(1180, WIN_CENTER_Y), Vector2(250, WIN_HEIGHT), Vector2(1, 1), 0.0f)); 
	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X, WIN_HEIGHT), Vector2(WIN_WIDTH, 150), Vector2(1, 1), 0.0f));

	stage_obstackle.push_back(obstackle_list);
	obstackle_list.clear();

	next_stage[0] = new RectCollider(Vector2(400, 40));
	next_stage[0]->is_active = true;
	next_stage[0]->SetColor(0, 0, 0);

	// 맵 2
	
	BG[1] = new BackGround(L"Texture/Town2.png");

	obstackle_list.push_back(new Obstackle(Vector2(WIN_CENTER_X, WIN_CENTER_Y + 225), Vector2(WIN_WIDTH, 200), Vector2(1, 1), 0.0f));
	obstackle_list.push_back(new Obstackle(Vector2(160, WIN_CENTER_Y), Vector2(WIN_WIDTH / 3, WIN_HEIGHT), Vector2(1, 1), 0.0f));
	obstackle_list.push_back(new Obstackle(Vector2(1000, 200), Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2(1, 1), 0.0f));
	obstackle_list.push_back(new Obstackle(Vector2(220, 540), Vector2(500, 350), Vector2(1, 1), 0.0f));
	obstackle_list.push_back(new Obstackle(Vector2(310, 600), Vector2(500, 350), Vector2(1, 1), 0.0f));
	obstackle_list.push_back(new Obstackle(Vector2(200, 80), Vector2(500, 250), Vector2(1, 1), 0.0f));
	obstackle_list.push_back(new Obstackle(Vector2(850, 80), Vector2(500, 250), Vector2(1, 1), 0.0f));

	stage_obstackle.push_back(obstackle_list);
	obstackle_list.clear();

	next_stage[1] = new RectCollider(Vector2(200, 50));
	next_stage[1]->is_active = true;
	next_stage[1]->SetColor(0, 0, 0);
	battle_stage[0] = new RectCollider(Vector2(30,100));
	battle_stage[0]->is_active = true;
	battle_stage[0]->SetColor(0, 0, 0);
	battle_stage[1] = new RectCollider(Vector2(80, 80));
	battle_stage[1]->is_active = true;
	battle_stage[1]->SetColor(0, 0, 0);

	champion = new InGameEnemy(Vector2(525, 145), L"Texture/Champion.png",  453, 166, 21, 24);
	champion->is_active = true;

	pokemon = new InGameEnemy(Vector2(WIN_CENTER_X + 20, WIN_CENTER_Y + 30), L"Texture/OverWorldPokemon.png",  594, 77, 13, 17);
	pokemon->is_active = true;
	
	player = new Player(Vector2(835, 540));

	now_stage = 1;
}

TownScene::~TownScene()
{
	delete player;

	for (auto b : BG)
		delete b;

	for (auto o : obstackle_list)
		delete o;

	delete next_stage[0];
	delete next_stage[1];

	delete pokemon;
	delete champion;
}

void TownScene::Update()
{
	Vector2 obstackle_area;
	player->SetGender(gender);

	if (now_stage == 1) // 현재 1스테이지 (마을)
	{
		BG[0]->Update();
		next_stage[0]->pos = Vector2(WIN_CENTER_X, 30);

		if (player->GetCollider()->isCollision(next_stage[0]))
			ChangeStage(now_stage);

		
		for (auto s : stage_obstackle[0])
		{
			if (player->GetCollider()->isCollision(s->GetCollider(), &obstackle_area))
			{
				Vector2 player_pos = player->GetCollider()->pos;
				Vector2 obstackle_pos = s->GetCollider()->pos;

				if (obstackle_area.x > obstackle_area.y)
				{
					if (player_pos.y > obstackle_pos.y)
						player->pos.y += obstackle_area.y;
					else
						player->pos.y -= obstackle_area.y;
					
				}
				else
				{
					if (player_pos.x > obstackle_pos.x) 
						player->pos.x += obstackle_area.x;
					else
						player->pos.x -= obstackle_area.x;

				}
			}
			s->Update();
		}
			
		next_stage[0]->WorldUpdate();
	}

	else // 현재 2스테이지 (야생)
	{
		BG[1]->Update();
		next_stage[1]->pos = Vector2(WIN_WIDTH - 25, WIN_CENTER_Y + 75);
		battle_stage[0]->pos = Vector2(WIN_CENTER_X + 20, WIN_CENTER_Y + 80);
		battle_stage[1]->pos = Vector2(525, 150);
		pokemon->Update();
		champion->Update();

		if (player->GetCollider()->isCollision(next_stage[1]))
			ChangeStage(now_stage);

		for (auto s : stage_obstackle[1])
		{
			if (player->GetCollider()->isCollision(s->GetCollider(), &obstackle_area))
			{
				Vector2 player_pos = player->GetCollider()->pos;
				Vector2 obstackle_pos = s->GetCollider()->pos;

				if (obstackle_area.x > obstackle_area.y)
				{
					if (player_pos.y > obstackle_pos.y)
						player->pos.y += obstackle_area.y;
					else
						player->pos.y -= obstackle_area.y;
				}
				else
				{
					if (player_pos.x > obstackle_pos.x)
						player->pos.x += obstackle_area.x;
					else
						player->pos.x -= obstackle_area.x;

				}
			}
			s->Update();
		}

		if (player->GetCollider()->isCollision(battle_stage[0])) // 찌르꼬와 마주치면
			is_vsPokemon = true;

		if (player->GetCollider()->isCollision(battle_stage[1])) // 챔피언과 마주치면
			is_vsChampion = true;

		if (clear_vsPokemon) // 포켓몬과의 전투가 완료되면
		{
			if (!lose_vsPokemon) // 승리했다면
			{
				is_vsPokemon = false;
				battle_stage[0]->is_active = false;
				pokemon->is_active = false;
			}
			else
			{
				is_vsPokemon = false;
				player->pos = Vector2(WIN_WIDTH - 150, WIN_CENTER_Y + 75); // 재도전
				lose_vsPokemon = false;
				clear_vsPokemon = false;
			}
		}
		if (clear_vsChampion) // 챔피언과의 전투가 완료되면
		{
			if (!lose_vsChampion) // 승리했다면
			{
				is_vsChampion = false;
				battle_stage[1]->is_active = false;
				champion->is_active = false;
			}
			else
			{
				is_vsChampion = false;
				player->pos = Vector2(WIN_WIDTH - 150, WIN_CENTER_Y + 75); // 재도전
				lose_vsChampion = false;
				clear_vsChampion = false;

			}
		}
		next_stage[1]->WorldUpdate();
		battle_stage[0]->WorldUpdate();
		battle_stage[1]->WorldUpdate();
	}

	player->Update();
}

void TownScene::ChangeStage(UINT stage)
{
	if (stage == 1) // 마을이면 야생으로 넘어가야됨
	{
		BG[0]->is_active = false;
		next_stage[1]->is_active = false;

		BG[1]->is_active = true;
		next_stage[1]->is_active = true;
		battle_stage[0]->is_active = true;
		battle_stage[1]->is_active = true;
		champion->is_active = true;
		pokemon->is_active = true;

		player->pos = Vector2(WIN_WIDTH - 150, WIN_CENTER_Y + 75);

		now_stage++;
	}
	else // 야생이면 마을로 돌아가기
	{
		BG[1]->is_active = false;
		next_stage[1]->is_active = false;
		battle_stage[0]->is_active = false;
		battle_stage[1]->is_active = false;
		champion->is_active = false;
		pokemon->is_active = false;

		BG[0]->is_active = true;
		next_stage[0]->is_active = true;

		player->pos = Vector2(WIN_CENTER_X, 100);
		
		now_stage--;
	}
}

void TownScene::Render()
{
	if (now_stage == 1)
	{
		BG[0]->Render();

		for (auto o : stage_obstackle[0])
			o->Render();

		next_stage[0]->Render();
	}
	else
	{
		BG[1]->Render();

		for (auto o : stage_obstackle[1])
			o->Render();

		next_stage[1]->Render();
		battle_stage[0]->Render();
		battle_stage[1]->Render();

		if(pokemon->is_active)
			pokemon->Render();
		if(champion->is_active)
			champion->Render();
	}
	player->Render();
}

void TownScene::PostRender()
{
	ImGui::SliderFloat2("Player pos", (float*)&player->pos, 0, 1280, NULL);
}


