#include "framework.h"
#include "Data/PokemonData.h"

BattleManager::BattleManager(bool mode)
	: mode(mode), is_appearance(true), m_appear_step(0), change_turn(0)
{
	vector<unique_ptr<Pokemon>> my_box, en_box;
	for (const auto& d : PokemonData::PLAYER)
		my_box.push_back(make_unique<Pokemon>(
			Vector2(WIN_CENTER_X / 2, 420), d.sx, d.sy, d.sw, d.sh, d.attack));
	player_box = make_unique<PokemonBox>(std::move(my_box));

	if (mode) {
		for (const auto& d : PokemonData::VS_POKEMON_ENEMY)
			en_box.push_back(make_unique<Pokemon>(
				Vector2(WIN_CENTER_X + 345, 305), d.sx, d.sy, d.sw, d.sh, d.attack));
	} else {
		for (int i = 0; i < 3; ++i) {
			const auto& d = PokemonData::VS_CHAMPION_ENEMY[i];
			float py = (i == 0) ? 305.0f : 285.0f;
			en_box.push_back(make_unique<Pokemon>(
				Vector2(WIN_CENTER_X + 345, py), d.sx, d.sy, d.sw, d.sh, d.attack));
		}
	}
	enemy_box = make_unique<PokemonBox>(std::move(en_box));

	player_box->GetField()->is_active = false;
	enemy_box->GetField()->is_active  = false;

	player_status = make_unique<StatusBox>(true,  g_state, mode);
	enemy_status  = make_unique<StatusBox>(false, g_state, mode);

	button = make_unique<SelectButton>();
	button->is_active = false;

	behavior     = make_unique<BattleAnimation>(mode);
	action_proc  = make_unique<ActionProcessor>(behavior.get());
}

BattleManager::~BattleManager() {}

// ─── Skill slot mapping ──────────────────────────────────────────────────────

UINT BattleManager::GetPlayerSkillSlot() const {
	static const UINT MAP[] = { 0, 3, 5 };
	return MAP[player_box->GetFieldIndex()];
}

UINT BattleManager::GetEnemySkillSlot() const {
	if (mode) return 1;
	static const UINT MAP[] = { 1, 2, 4 };
	return MAP[enemy_box->GetFieldIndex()];
}

// ─── Appearance (intro animation) ────────────────────────────────────────────

void BattleManager::Appearance() {
	if (mode) {
		behavior->GetPlayer()->SetGender(g_state.gender);
		switch (m_appear_step) {
		case 0:
			behavior->GetAppearance()->Update(0);
			behavior->GetPlayer()->Update(0);
			if (!behavior->GetAppearance()->GetClips()[0]->isPlay()) m_appear_step++;
			break;
		case 1:
			enemy_box->GetField()->is_active = true;
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
			player_box->GetField()->is_active = true;
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
			enemy_box->GetField()->is_active = true;
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
			player_box->GetField()->is_active = true;
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

		if (player_box->AllFainted()) {
			if (mode) {
				g_state.lose_vsPokemon  = true;
				g_state.clear_vsPokemon = true;
			} else {
				g_state.lose_vsChampion  = true;
				g_state.clear_vsChampion = true;
			}
		}

		if (!behavior->GetPokeball()->GetClips()[0]->isPlay())
			behavior->GetPokeball()->GetClips()[0]->Play();
		behavior->GetPokeball()->Update(0);

		if (!behavior->GetPokeball()->GetClips()[0]->isPlay()) {
			player_status->SetIsStatus(true);
			if (player_box->SwitchToNext()) {
				player_status->SetHPBar(player_box->GetField()->GetHP());
				player_status->SetCurrentHP(player_box->GetField()->GetHP());
				if (player_box->GetField()->pos.x != WIN_CENTER_X / 2)
					player_box->GetField()->pos.x = WIN_CENTER_X / 2;
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

		if (mode) {
			g_state.clear_vsPokemon = true;
			return;
		}

		if (enemy_box->AllFainted())
			g_state.clear_vsChampion = true;

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
					enemy_box->GetField()->pos.x = WIN_CENTER_X + 345;
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

void BattleManager::ProcessPlayerInput() {
	const Vector2& click = g_state.mouse_click_pos;

	if (click.x > 22 && click.x < 405 && click.y > 560 && click.y < 726) {
		turn_state.BeginAction(ActionPhase::Attack);
	} else if (click.x > 440 && click.x < 840 && click.y > 560 && click.y < 726) {
		if (player_box->GetField()->GetHP() < 100)
			turn_state.BeginAction(ActionPhase::Recovery);
		else
			g_state.mouse_click_pos = Vector2(0, 0);
	} else if (click.x > 875 && click.x < 1255 && click.y > 560 && click.y < 726) {
		bool can_change = false;
		for (int i = 0; i < player_box->GetSize(); ++i) {
			if (player_box->GetPokemon(i) != player_box->GetField() &&
				player_box->GetPokemon(i)->GetIsSurvive()) {
				can_change = true; break;
			}
		}
		if (can_change) turn_state.BeginAction(ActionPhase::Change);
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
				if (player_box->GetField()->pos.x != WIN_CENTER_X / 2)
					player_box->GetField()->pos.x = WIN_CENTER_X / 2;
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
			bool done = action_proc->RunPlayerAttack(
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
			bool done = action_proc->RunEnemyAttack(
				GetEnemySkillSlot(),
				enemy_box->GetField(), player_box->GetField(),
				player_status.get(), player_status.get());
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
