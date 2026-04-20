#include "framework.h"

BattleAnimation::BattleAnimation(bool withChampion)
{
	appearance = make_unique<Appearance>();
	player     = make_unique<BattlePlayer>(Vector2(250, WIN_CENTER_Y + 80), g_state.gender);
	pokeball   = make_unique<Pokeball>();
	skill      = make_unique<Skill>();
	meditation = make_unique<Meditation>();

	if (withChampion)
		champion = make_unique<Champion>();
}

void BattleAnimation::Update(UINT slot)
{
	if (champion)
		champion->Update();

	player->Update(slot);
	pokeball->Update(slot);
	appearance->Update(slot);
	skill->Update(slot);
	meditation->Update();
}

void BattleAnimation::Render()
{
	if (champion)
		champion->Render();

	player->Render();
	pokeball->Render();
	appearance->Render();
	skill->Render();
	meditation->Render();
}
