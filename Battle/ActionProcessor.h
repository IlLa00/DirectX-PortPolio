#pragma once

class ActionProcessor {
	enum class AttackState   { Start, Animation, Damage };
	enum class RecoveryState { Start, Animation, Apply };

	AttackState   m_atkState = AttackState::Start;
	RecoveryState m_recState = RecoveryState::Start;

	BattleAnimation* m_behavior;

public:
	explicit ActionProcessor(BattleAnimation* behavior);

	// Returns true when action is complete (caller handles turn switch)
	bool RunPlayerAttack(UINT slot, Pokemon* atk, Pokemon* def, StatusBox* defStatus);
	bool RunEnemyAttack (UINT slot, Pokemon* atk, Pokemon* def, StatusBox* defStatus, StatusBox* atkStatus);
	bool RunRecovery    (Pokemon* target, StatusBox* status);

	void ResetAttack()   { m_atkState = AttackState::Start; }
	void ResetRecovery() { m_recState = RecoveryState::Start; }
};
