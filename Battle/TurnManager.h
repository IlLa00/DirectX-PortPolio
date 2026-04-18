#pragma once

enum class BattleTurn  { Player, Enemy };
enum class ActionPhase { Idle, Attack, Recovery, Change };

struct TurnManager {
	BattleTurn  current = BattleTurn::Player;
	ActionPhase phase   = ActionPhase::Idle;

	bool IsPlayerTurn() const       { return current == BattleTurn::Player; }
	bool IsIdle()       const       { return phase == ActionPhase::Idle; }
	void SwitchTurn()               { current = IsPlayerTurn() ? BattleTurn::Enemy : BattleTurn::Player; }
	void BeginAction(ActionPhase p) { phase = p; }
	void EndAction()                { phase = ActionPhase::Idle; }
};
