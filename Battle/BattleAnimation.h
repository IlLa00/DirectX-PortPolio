#pragma once
class BattleAnimation
{
private:
	unique_ptr<Appearance>    appearance;
	unique_ptr<BattlePlayer>  player;
	unique_ptr<Pokeball>      pokeball;
	unique_ptr<Skill>         skill;
	unique_ptr<Meditation>    meditation;
	unique_ptr<Champion>      champion;   // null when not in vsChampion mode

public:
	explicit BattleAnimation(bool withChampion);
	~BattleAnimation() = default;

	Appearance*   GetAppearance()  { return appearance.get(); }
	BattlePlayer* GetPlayer()      { return player.get(); }
	Pokeball*     GetPokeball()    { return pokeball.get(); }
	Skill*        GetSkill()       { return skill.get(); }
	Meditation*   GetMeditation()  { return meditation.get(); }
	Champion*     GetChampion()    { return champion.get(); }

	void Update(UINT slot);
	void Render();
};
