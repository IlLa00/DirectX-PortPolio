#include "framework.h"

ActionProcessor::ActionProcessor(BattleAnimation* behavior)
	: m_behavior(behavior)
{}

bool ActionProcessor::RunAttack(UINT slot, Pokemon* atk, Pokemon* def, StatusBox* defStatus) {
	Clip* clip = m_behavior->GetSkill()->GetClips()[slot];
	switch (m_atkState) {
	case AttackState::Start:
		if (!clip->isPlay()) clip->Play();
		m_atkState = AttackState::Animation;
		return false;
	case AttackState::Animation:
		m_behavior->GetSkill()->Update(slot);
		if (!clip->isPlay()) m_atkState = AttackState::Damage;
		return false;
	case AttackState::Damage:
		atk->Attack(def);
		defStatus->SetHPBar(def->GetHP());
		m_atkState = AttackState::Start;
		return true;
	}
	return false;
}

bool ActionProcessor::RunRecovery(Pokemon* target, StatusBox* status) {
	switch (m_recState) {
	case RecoveryState::Start:
		if (!m_behavior->GetMeditation()->GetClips()[0]->isPlay())
			m_behavior->GetMeditation()->GetClips()[0]->Play();
		m_recState = RecoveryState::Animation;
		return false;
	case RecoveryState::Animation:
		m_behavior->GetMeditation()->Update();
		if (!m_behavior->GetMeditation()->GetClips()[0]->isPlay())
			m_recState = RecoveryState::Apply;
		return false;
	case RecoveryState::Apply:
		target->Recovery();
		status->SetHPBar(target->GetHP());
		status->SetCurrentHP(target->GetHP());
		m_recState = RecoveryState::Start;
		return true;
	}
	return false;
}
