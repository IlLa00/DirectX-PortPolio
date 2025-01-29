#pragma once
class BattleAnimation
{
private:
	Appearance* appearance;
	BattlePlayer* player;
	Pokeball* pokeball;
	Skill* skill;
	Meditation* meditation;

	Champion* champion;

	bool mode;

public:
	BattleAnimation(bool mode);
	~BattleAnimation();

	Appearance* GetAppearance() { return appearance; }
	BattlePlayer* GetPlayer() { return player; }
	Pokeball* GetPokeball() { return pokeball; }
	Skill* GetSkill() { return skill; }
	Meditation* GetMeditation() { return meditation; }
	Champion* GetChampion() { return champion; }

	void Update(UINT slot);
	void Render();
};