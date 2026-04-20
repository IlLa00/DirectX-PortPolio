#include "framework.h"
#include "Battle/IBattleContext.h"

BattleManager::BattleManager(bool mode)
	: m_context(mode ? (unique_ptr<IBattleContext>)make_unique<VsPokemonContext>()
	                 : make_unique<VsChampionContext>())
	, is_appearance(true), m_appear_step(0), change_turn(0)
{
	vector<unique_ptr<Pokemon>> my_box, en_box;
	for (const auto& d : PokemonData::PLAYER)
		my_box.push_back(make_unique<Pokemon>(
			Vector2(WIN_CENTER_X / 2, 420), d.sx, d.sy, d.sw, d.sh, d.attack));
	player_box = make_unique<PokemonBox>(std::move(my_box));

	m_context->BuildEnemyTeam(en_box);
	enemy_box = make_unique<PokemonBox>(std::move(en_box));

	player_box->GetField()->SetActive(false);
	enemy_box->GetField()->SetActive(false);

	player_status = make_unique<StatusBox>(true,  g_state, false);
	enemy_status  = make_unique<StatusBox>(false, g_state, m_context->GetEnemyNameSlotOffset() > 0);

	button = make_unique<SelectButton>();
	button->is_active = false;

	behavior    = make_unique<BattleAnimation>(/*withChampion=*/!m_context->IsVsPokemon());
	action_proc = make_unique<ActionProcessor>(behavior.get());
}

BattleManager::~BattleManager() {}

// ─── Skill slot mapping ──────────────────────────────────────────────────────

UINT BattleManager::GetPlayerSkillSlot() const {
	static const UINT MAP[] = { 0, 3, 5 };
	return MAP[player_box->GetFieldIndex()];
}

UINT BattleManager::GetEnemySkillSlot() const {
	return m_context->GetEnemySkillSlot(enemy_box->GetFieldIndex());
}

// ─── Appearance (intro animation) ────────────────────────────────────────────

void BattleManager::Appearance() {
	if (m_context->IsVsPokemon()) {
		behavior->GetPlayer()->SetGender(g_state.gender);
		switch (m_appear_step) {
		case 0:
			behavior->GetAppearance()->Update(0);
			behavior->GetPlayer()->Update(0);
			if (!behavior->GetAppearance()->GetClips()[0]->isPlay()) m_appear_step++;
			break;
		case 1:
			enemy_box->GetField()->SetActive(true);
			enemy_box->GetField()->Update();
			enemy_status->pos = Vector2(WIN_CENTER_X - 380, 200);
			enemy_status->SetHPBar(enemy_box->GetField()->GetHP());
			enemy_status->SetIsStatus(true);
			enemy_status->Update();
			behavior->GetPlayer()->Update(1);
			if (!behavior->GetPlayer()->GetClips()[1]->isPlay()) m_appear_step++;
			break;
		case 2:
			behavior->GetPokeball()->Update(0);
			if (!behavior->GetPokeball()->GetClips()[0]->isPlay()) m_appear_step++;
			break;
		case 3:
			player_box->GetField()->SetActive(true);
			player_box->GetField()->Update();
			player_status->pos = Vector2(WIN_CENTER_X + 360, 450);
			player_status->SetHPBar(player_box->GetField()->GetHP());
			player_status->SetCurrentHP(player_box->GetField()->GetHP());
			player_status->SetIsStatus(true);
			player_status->Update();
			m_appear_step = 0;
			is_appearance = false;
			break;
		}
	} else {
		behavior->GetPlayer()->SetGender(g_state.gender);
		switch (m_appear_step) {
		case 0:
			behavior->GetChampion()->Update();
			behavior->GetPlayer()->Update(0);
			behavior->GetChampion()->pos.x += 250.0f * DELTA;
			if (behavior->GetChampion()->pos.x >= 1350) m_appear_step++;
			break;
		case 1:
			behavior->GetPokeball()->Update(1);
			if (!behavior->GetPokeball()->GetClips()[0]->isPlay()) m_appear_step++;
			break;
		case 2:
			behavior->GetAppearance()->Update(1);
			if (!behavior->GetAppearance()->GetClips()[1]->isPlay()) m_appear_step++;
			break;
		case 3:
			behavior->GetPlayer()->SetGender(g_state.gender);
			behavior->GetPlayer()->Update(1);
			enemy_box->GetField()->SetActive(true);
			enemy_box->GetField()->Update();
			enemy_status->pos = Vector2(WIN_CENTER_X - 380, 200);
			enemy_status->SetHPBar(enemy_box->GetField()->GetHP());
			enemy_status->SetIsStatus(true);
			enemy_status->Update();
			if (!behavior->GetPlayer()->GetClips()[1]->isPlay()) m_appear_step++;
			break;
		case 4:
			if (!behavior->GetPokeball()->GetClips()[0]->isPlay())
				behavior->GetPokeball()->GetClips()[0]->Play();
			behavior->GetPokeball()->Update(0);
			if (!behavior->GetPokeball()->GetClips()[0]->isPlay()) m_appear_step++;
			break;
		case 5:
			player_box->GetField()->SetActive(true);
			player_box->GetField()->Update();
			player_status->pos = Vector2(WIN_CENTER_X + 360, 450);
			player_status->SetHPBar(player_box->GetField()->GetHP());
			player_status->SetCurrentHP(player_box->GetField()->GetHP());
			player_status->SetIsStatus(true);
			player_status->Update();
			m_appear_step = 0;
			is_appearance = false;
			break;
		}
	}
}

// ─── Status box sync ─────────────────────────────────────────────────────────

void BattleManager::SyncStatusBoxes() {
	player_status->SetStatus(player_box->GetFieldIndex());
	enemy_status->SetStatus(enemy_box->GetFieldIndex());
}

// ─── Fainted handling ─────────────────────────────────────────────────────────

void BattleManager::HandlePlayerFainted() {
	if (turn_state.phase == ActionPhase::Attack) {
		turn_state.EndAction();
		action_proc->ResetAttack();
	}
	g_state.mouse_click_pos = Vector2(0, 0);
	turn_state.BeginAction(ActionPhase::Change);

	player_box->GetField()->SetIsSurvive(false);
	player_box->GetField()->Collapses();

	if (player_box->GetField()->pos.x <= 0) {
		player_status->SetIsStatus(false);

		if (player_box->AllFainted())
			m_context->OnPlayerLose(g_state);

		if (!behavior->GetPokeball()->GetClips()[0]->isPlay())
			behavior->GetPokeball()->GetClips()[0]->Play();
		behavior->GetPokeball()->Update(0);

		if (!behavior->GetPokeball()->GetClips()[0]->isPlay()) {
			player_status->SetIsStatus(true);
			if (player_box->SwitchToNext()) {
				player_status->SetHPBar(player_box->GetField()->GetHP());
				player_status->SetCurrentHP(player_box->GetField()->GetHP());
				player_box->GetField()->ResetPosition(Vector2(WIN_CENTER_X / 2, 420));
				turn_state.EndAction();
			}
		}
	}
}

void BattleManager::HandleEnemyFainted() {
	if (turn_state.phase == ActionPhase::Attack) {
		turn_state.EndAction();
		action_proc->ResetAttack();
	}
	g_state.mouse_click_pos = Vector2(0, 0);
	turn_state.BeginAction(ActionPhase::Change);

	enemy_box->GetField()->SetIsSurvive(false);
	enemy_box->GetField()->Collapses();

	if (enemy_box->GetField()->pos.x >= WIN_WIDTH) {
		enemy_status->SetIsStatus(false);

		m_context->OnEnemyFainted(g_state, enemy_box->AllFainted());

		if (m_context->IsVsPokemon())
			return;

		switch (change_turn) {
		case 0:
			if (!behavior->GetPokeball()->GetClips()[0]->isPlay())
				behavior->GetPokeball()->GetClips()[0]->Play();
			behavior->GetPokeball()->Update(1);
			if (!behavior->GetPokeball()->GetClips()[0]->isPlay()) {
				enemy_status->SetIsStatus(true);
				change_turn++;
			}
			break;
		case 1:
		{
			int cur = enemy_box->GetFieldIndex();
			int next = -1;
			if (cur == 0 && enemy_box->GetPokemon(1)->GetIsSurvive()) next = 1;
			else if (cur == 1 && enemy_box->GetPokemon(2)->GetIsSurvive()) next = 2;
			else if (cur == 2 && enemy_box->GetPokemon(0)->GetIsSurvive()) next = 0;

			int animSlot = (next == 1) ? 2 : (next == 2) ? 3 : 1;
			if (next >= 0) {
				behavior->GetAppearance()->Update(animSlot);
				if (!behavior->GetAppearance()->GetClips()[animSlot]->isPlay()) {
					enemy_box->SwitchToNext();
					enemy_status->SetHPBar(enemy_box->GetField()->GetHP());
					enemy_box->GetField()->ResetPosition(Vector2(WIN_CENTER_X + 345, 285));
					change_turn = 0;
					turn_state.EndAction();
				}
			}
			break;
		}
		}
	}
}

// ─── Player input ─────────────────────────────────────────────────────────────

bool BattleManager::HasAliveReserve() const {
	for (int i = 0; i < player_box->GetSize(); ++i) {
		if (player_box->GetPokemon(i) != player_box->GetField() &&
			player_box->GetPokemon(i)->GetIsSurvive())
			return true;
	}
	return false;
}

void BattleManager::ProcessPlayerInput() {
	const ButtonAction action = button->GetClickedAction(g_state.mouse_click_pos);
	switch (action) {
	case ButtonAction::Attack:
		turn_state.BeginAction(ActionPhase::Attack);
		break;
	case ButtonAction::Recovery:
		if (player_box->GetField()->GetHP() < 100.0f)
			turn_state.BeginAction(ActionPhase::Recovery);
		else
			g_state.mouse_click_pos = Vector2(0, 0);
		break;
	case ButtonAction::Change:
		if (HasAliveReserve())
			turn_state.BeginAction(ActionPhase::Change);
		break;
	default:
		break;
	}
}

// ─── Enemy turn start ─────────────────────────────────────────────────────────

void BattleManager::ProcessEnemyTurn() {
	turn_state.BeginAction(ActionPhase::Attack);
}

// ─── Voluntary change FSM ─────────────────────────────────────────────────────

void BattleManager::RunChangeAction() {
	player_box->GetField()->Collapses();

	if (player_box->GetField()->pos.x <= 0) {
		player_status->SetIsStatus(false);

		if (!behavior->GetPokeball()->GetClips()[0]->isPlay())
			behavior->GetPokeball()->GetClips()[0]->Play();
		behavior->GetPokeball()->Update(0);

		if (!behavior->GetPokeball()->GetClips()[0]->isPlay()) {
			player_status->SetIsStatus(true);
			if (player_box->SwitchToNext()) {
				player_status->SetHPBar(player_box->GetField()->GetHP());
				player_status->SetCurrentHP(player_box->GetField()->GetHP());
				player_box->GetField()->ResetPosition(Vector2(WIN_CENTER_X / 2, 420));
			}
			turn_state.EndAction();
			turn_state.SwitchTurn();
			g_state.mouse_click_pos = Vector2(0, 0);
		}
	}
}

// ─── Current action dispatcher ────────────────────────────────────────────────

void BattleManager::RunCurrentAction() {
	switch (turn_state.phase) {
	case ActionPhase::Attack:
		if (turn_state.IsPlayerTurn()) {
			bool done = action_proc->RunAttack(
				GetPlayerSkillSlot(),
				player_box->GetField(), enemy_box->GetField(),
				enemy_status.get());
			if (done) {
				turn_state.EndAction();
				if (enemy_box->GetField()->GetHP() > 0)
					turn_state.SwitchTurn();
				g_state.mouse_click_pos = Vector2(0, 0);
			}
		} else {
			bool done = action_proc->RunAttack(
				GetEnemySkillSlot(),
				enemy_box->GetField(), player_box->GetField(),
				player_status.get());
			if (done) {
				turn_state.EndAction();
				turn_state.SwitchTurn();
				g_state.mouse_click_pos = Vector2(0, 0);
			}
		}
		break;

	case ActionPhase::Recovery:
		if (action_proc->RunRecovery(player_box->GetField(), player_status.get())) {
			turn_state.EndAction();
			turn_state.SwitchTurn();
			g_state.mouse_click_pos = Vector2(0, 0);
		}
		break;

	case ActionPhase::Change:
		RunChangeAction();
		break;

	default:
		break;
	}
}

// ─── Update / Render ──────────────────────────────────────────────────────────

void BattleManager::Update() {
	if (is_appearance) {
		Appearance();
	} else {
		button->SetActive(turn_state.IsIdle());
		SyncStatusBoxes();

		if (player_box->GetField()->GetHP() <= 0)
			HandlePlayerFainted();
		else if (enemy_box->GetField()->GetHP() <= 0)
			HandleEnemyFainted();
		else if (!turn_state.IsIdle())
			RunCurrentAction();
		else if (turn_state.IsPlayerTurn())
			ProcessPlayerInput();
		else
			ProcessEnemyTurn();
	}

	enemy_box->GetField()->Update();
	player_box->GetField()->Update();
	button->Update();
	player_status->Update();
	enemy_status->Update();
}

void BattleManager::Render() {
	enemy_box->GetField()->Render();
	player_box->GetField()->Render();

	player_status->Render();
	enemy_status->Render();

	button->Render();

	behavior->Render();
}
