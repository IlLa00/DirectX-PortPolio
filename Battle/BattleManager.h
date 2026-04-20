#pragma once

struct IBattleContext;

class BattleManager
{
private:
	unique_ptr<PokemonBox>      player_box;
	unique_ptr<PokemonBox>      enemy_box;
	TurnManager                 turn_state;
	unique_ptr<ActionProcessor> action_proc;

	unique_ptr<StatusBox>       player_status;
	unique_ptr<StatusBox>       enemy_status;
	unique_ptr<SelectButton>    button;
	unique_ptr<BattleAnimation> behavior;

	unique_ptr<IBattleContext> m_context;
	bool is_appearance;
	UINT m_appear_step;
	UINT change_turn;

	void Appearance();
	void SyncStatusBoxes();
	void HandlePlayerFainted();
	void HandleEnemyFainted();
	void ProcessPlayerInput();
	void ProcessEnemyTurn();
	void RunCurrentAction();
	void RunChangeAction();

	UINT GetPlayerSkillSlot() const;
	UINT GetEnemySkillSlot()  const;
	bool HasAliveReserve()    const;

public:
	BattleManager(bool mode);
	~BattleManager();

	bool GetAttackState()   const { return turn_state.phase == ActionPhase::Attack; }
	bool GetRecoveryState() const { return turn_state.phase == ActionPhase::Recovery; }
	bool GetChangeState()   const { return turn_state.phase == ActionPhase::Change; }

	float GetMyPokemonHP()    const { return player_box->GetField()->GetHP(); }
	float GetEnemyPokemonHP() const { return enemy_box->GetField()->GetHP(); }

	bool GetMyFirstPokemonSurvive()     const { return player_box->GetPokemon(0)->GetIsSurvive(); }
	bool GetMySecondPokemonSurvive()    const { return player_box->GetPokemon(1)->GetIsSurvive(); }
	bool GetMyThirdPokemonSurvive()     const { return player_box->GetPokemon(2)->GetIsSurvive(); }
	bool GetEnemyFirstPokemonSurvive()  const { return enemy_box->GetPokemon(0)->GetIsSurvive(); }
	bool GetEnemySecondPokemonSurvive() const { return enemy_box->GetPokemon(1)->GetIsSurvive(); }
	bool GetEnemyThirdPokemonSurvive()  const { return enemy_box->GetPokemon(2)->GetIsSurvive(); }

	void Update();
	void Render();
};
