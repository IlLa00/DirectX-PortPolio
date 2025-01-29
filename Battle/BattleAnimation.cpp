#include "framework.h"

BattleAnimation::BattleAnimation(bool mode) : mode(mode)
{
	if (mode)
	{
		appearance = new Appearance();
		player = new BattlePlayer(Vector2(250, WIN_CENTER_Y + 80), gender);
		pokeball = new Pokeball();
		skill = new Skill();
		meditation = new Meditation();
	}
	else
	{
		champion = new Champion();
		player = new BattlePlayer(Vector2(250, WIN_CENTER_Y + 80), gender);
		pokeball = new Pokeball();
		appearance = new Appearance();
		skill = new Skill();
		meditation = new Meditation();
	}
}

BattleAnimation::~BattleAnimation()
{
	if (mode)
	{
		delete appearance;
		delete player;
		delete pokeball;
		delete skill;
		delete meditation;
	}
	else
	{
		delete champion;
		delete player;
		delete pokeball;
		delete appearance;
		delete skill;
		delete meditation;
	}
	
}

void BattleAnimation::Update(UINT slot)
{
	if (mode)
	{
		appearance->Update(slot);
		player->Update(slot);
		pokeball->Update(slot);
		skill->Update(slot);
		meditation->Update();
	}
	else
	{
		champion->Update();
		player->Update(slot);
		pokeball->Update(slot);
		appearance->Update(slot);
		skill->Update(slot);
		meditation->Update();
	}
	
}

void BattleAnimation::Render()
{
	if (mode)
	{
		appearance->Render();
		player->Render();
		pokeball->Render();
		skill->Render();
		meditation->Render();
	}
	else
	{
		champion->Render();
		player->Render();
		pokeball->Render();
		appearance->Render();
		skill->Render();
		meditation->Render();
	}
}
