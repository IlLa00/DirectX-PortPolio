#pragma once

class BattleManager
{
private:
	vector<Pokemon*> my_pokemon_box;
	vector<Pokemon*> enemy_pokemon_box;
	Pokemon* field_my_pokemon;
	Pokemon* field_enemy_pokemon;

	StatusBox* player_status;
	StatusBox* enemy_status;

	SelectButton* button;

	BattleAnimation* behavior;

	UINT turn;
	UINT change_turn;

	bool mode; // vs야생포켓몬(True) vs챔피언(False)
	bool is_appearance;
	bool is_attack;
	bool is_recovery;
	bool is_change;

	enum AttackState {
		ATTACK_START,
		ATTACK_ANIMATION,
		ATTACK_DAMAGE,
		ATTACK_END
	}attackState;

	enum MeditationState {
		MEDITATION_START,
		MEDITATION_ANIMATION,
		MEDITATION_RECOVERY
	}meditationState;

	enum ChangeState {
		CHANGE_START,
		CHANGE_ANIMATION,
		CHANGE_END
	}changeState;


public:
	BattleManager(bool mode);
	~BattleManager(); 

	bool GetAttackState() { return is_attack; }
	bool GetRecoveryState() { return is_recovery; }
	bool GetChangeState() { return is_change; }

	float GetMyPokemonHP() { return field_my_pokemon->GetHP(); }
	float GetEnemyPokemonHP() { return field_enemy_pokemon->GetHP(); }

	bool GetEnemyFirstPokemonSurvive() { return enemy_pokemon_box[0]->GetIsSurvive(); }
	bool GetEnemySecondPokemonSurvive() { return enemy_pokemon_box[1]->GetIsSurvive(); }
	bool GetEnemyThirdPokemonSurvive() { return enemy_pokemon_box[2]->GetIsSurvive(); }

	bool GetMyFirstPokemonSurvive() { return my_pokemon_box[0]->GetIsSurvive(); }
	bool GetMySecondPokemonSurvive() { return my_pokemon_box[1]->GetIsSurvive(); }
	bool GetMyThirdPokemonSurvive() { return my_pokemon_box[2]->GetIsSurvive(); }

	void Appearance();
	void Update();
	void Render();
};