#include "framework.h"

BattleManager::BattleManager(bool mode)
	: mode(mode)
{
	if (mode) // �߻����ϸ�� �����̸�
	{
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 1621, 34, 80, 80)); // �ص���
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 2107, 34, 80, 80, 60.0f)); // ���丣Ʈ
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 2107, 2569, 80, 80, 80.0f)); // ��Ʒ簡

		enemy_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X + 345, 305), 23, 250, 35, 39)); // ���
	}
	else // è�Ǿ�� �����̸�
	{
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 1621, 34, 80, 80)); // �ص���
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 2107, 34, 80, 80, 60.0f)); // ���丣Ʈ
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 2107, 2569, 80, 80, 80.0f)); // ��Ʒ簡

		enemy_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X + 345, 305), 244, 1594, 80, 80)); // ȭ����
		enemy_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X + 345, 285), 244, 619, 80, 80, 55.0f)); // ����̵�
		enemy_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X + 345, 285), 1459, 1594, 80, 80, 60.0f)); // ��ī���ƽ�
	}
	field_my_pokemon = my_pokemon_box[0];
	field_my_pokemon->is_active = false;

	field_enemy_pokemon = enemy_pokemon_box[0];
	field_enemy_pokemon->is_active = false;

	// �Ű������� �������� �ٸ��� ����
	player_status = new StatusBox(true); // �÷��̾� ����â
	enemy_status = new StatusBox(false); // ���� ����â

	button = new SelectButton(); // ��ȣ�ۿ� ��ư ����, ȸ��, ��ü
	button->is_active = false;

	behavior = new BattleAnimation(mode); // �ִϸ��̼� ����

	turn = 0; // 0�϶� �÷��̾� ��, 1�϶� ���� ��
	change_turn = 0; // ���ϸ� ��ü�Ҷ� ���

	// ���������� ��ȣ�ۿ� ����
	attackState = ATTACK_START;
	meditationState = MEDITATION_START;
	changeState = CHANGE_START;

	is_appearance = true; // true�� ����ִϸ��̼� ���
	is_attack = false;
	is_recovery = false;
	is_change = false;
}

BattleManager::~BattleManager()
{
	for (auto b : my_pokemon_box)
		delete b;
	my_pokemon_box.clear();

	for (auto b : enemy_pokemon_box)
		delete b;
	enemy_pokemon_box.clear();

	delete player_status;
	delete enemy_status;

	delete button;

	delete behavior;
}

void BattleManager::Appearance() // ����
{
	if (mode) // �߻����ϸ�� ������ ��
	{
		behavior->GetPlayer()->SetGender(gender); // �÷��̾� ���� ����

		switch (turn)
		{
		case 0:
			behavior->GetAppearance()->Update(0); // ��� ������
			behavior->GetPlayer()->Update(0); // �÷��̾� �ε��ڼ�
			if (behavior->GetAppearance()->GetClips()[0]->isPlay() == false)
				turn++;
			break;
		case 1:
			field_enemy_pokemon->is_active = true;
			field_enemy_pokemon->Update();

			enemy_status->pos = Vector2(WIN_CENTER_X - 380, 200);
			enemy_status->SetHPBar(field_enemy_pokemon->GetHP());
			enemy_status->Update();

			behavior->GetPlayer()->Update(1); // �÷��̾� ���ϸ� ��ȯ
			if (behavior->GetPlayer()->GetClips()[1]->isPlay() == false)  // �÷��̾� ���ϸ� ��ȯ�� ������
				turn++;
			break;
		case 2:
			behavior->GetPokeball()->Update(0); // ���Ϻ� ����
			if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false) // ���Ϻ� ������ ������
				turn++;
			break;
		case 3:
			field_my_pokemon->is_active = true; // �ص��� ���
			field_my_pokemon->Update();

			player_status->pos = Vector2(WIN_CENTER_X + 360, 450);
			player_status->SetHPBar(field_my_pokemon->GetHP());
			player_status->SetCurrentHP(field_my_pokemon->GetHP());
			player_status->Update();

			turn = 0;
			is_appearance = false; // ��� ������ ����
			break;
		}
	}
	else // è�Ǿ�� �������̸�
	{
		behavior->GetPlayer()->SetGender(gender);

		switch (turn)
		{
		case 0:
			behavior->GetChampion()->Update();
			behavior->GetPlayer()->Update(0);
			behavior->GetChampion()->pos.x += 250.0f * DELTA;
			if (behavior->GetChampion()->pos.x >= 1350)
				turn++;
			break;
		case 1:
			behavior->GetPokeball()->Update(1); // ������ ���Ϻ��� ����
			if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
				turn++;
			break;
		case 2:
			behavior->GetAppearance()->Update(1);

			if (behavior->GetAppearance()->GetClips()[1]->isPlay() == false)
				turn++;
			break;
		case 3:
			behavior->GetPlayer()->SetGender(gender);
			behavior->GetPlayer()->Update(1);

			field_enemy_pokemon->is_active = true;
			field_enemy_pokemon->Update();

			enemy_status->pos = Vector2(WIN_CENTER_X - 380, 200);
			enemy_status->SetHPBar(field_enemy_pokemon->GetHP());
			enemy_status->Update();

			if (behavior->GetPlayer()->GetClips()[1]->isPlay() == false) // �÷��̾� ����� ������
				turn++;
			break;
		case 4:
			if(behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
				behavior->GetPokeball()->GetClips()[0]->Play(); 
			behavior->GetPokeball()->Update(0); 
			if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
				turn++;
			break;
		case 5:
			field_my_pokemon->is_active = true;
			field_my_pokemon->Update();

			player_status->pos = Vector2(WIN_CENTER_X + 360, 450);
			player_status->SetHPBar(field_enemy_pokemon->GetHP());
			player_status->SetCurrentHP(field_my_pokemon->GetHP());
			player_status->Update();

			turn = 0;
			is_appearance = false; // ��� ������ ����
			break;
		}
	}
}

void BattleManager::Update()
{
	if (is_appearance)
		Appearance(); // ���� ��� ���
	else
	{
		if (is_appearance || is_attack || is_recovery || is_change) // �ൿ ���̸� �ൿ ��ư�� Ȱ��ȭ ���� ����
			button->is_active = false;
		else
			button->is_active = true;

		// ����â ����
		if (field_my_pokemon == my_pokemon_box[0])
			player_status->SetStatus(0);
		else if (field_my_pokemon == my_pokemon_box[1])
			player_status->SetStatus(1);
		else if (field_my_pokemon == my_pokemon_box[2])
			player_status->SetStatus(2);

		if (field_enemy_pokemon == enemy_pokemon_box[0])
			enemy_status->SetStatus(0);
		else if (field_enemy_pokemon == enemy_pokemon_box[1])
			enemy_status->SetStatus(1);
		else if (field_enemy_pokemon == enemy_pokemon_box[2])
			enemy_status->SetStatus(2);
		else if (field_enemy_pokemon == enemy_pokemon_box[3])
			enemy_status->SetStatus(3);

		player_status->Update();
		enemy_status->Update();

		if (field_my_pokemon->GetHP() <= 0) // �÷��̾� ���ϸ� ü�� �˻�
		{
			if (is_attack)
				is_attack = false;

			mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
			attackState = ATTACK_START;

			is_change = true;

			if (is_change)
			{
				field_my_pokemon->SetIsSurvive(false);
				field_my_pokemon->Collapses();
				
				if (field_my_pokemon->pos.x <= 0)
				{
					player_status->SetIsStatus(false);

					if (!my_pokemon_box[0]->GetIsSurvive() && !my_pokemon_box[1]->GetIsSurvive() && !my_pokemon_box[2]->GetIsSurvive())
					{
						if (mode)
						{
							lose_vsPokemon = true;  // �Ʊ� ���ϸ��� ��� ���������� ���� �й�, �� ��� �ٽ� �絵�� ����
							clear_vsPokemon = true;
						}
						else
						{
							lose_vsChampion = true;  // �Ʊ� ���ϸ��� ��� ���������� ���� �й�, �� ��� �ٽ� �絵�� ����
							clear_vsChampion = true;
						}
					}

					if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
						behavior->GetPokeball()->GetClips()[0]->Play(); // �ٽ� ����ϱ� ���� �۾�	
					behavior->GetPokeball()->Update(0);
					if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
					{
						player_status->SetIsStatus(true);

						UINT current_index = -1; // ���� ���ϸ��� �ε����� ã��

						for (int i = 0; i < 3; ++i)
						{
							if (field_my_pokemon == my_pokemon_box[i])
							{
								current_index = i;
								break;
							}
						}

						for (int i = 1; i < 3; ++i)
						{
							int next_index = (current_index + i) % 3;
							if (my_pokemon_box[next_index]->GetIsSurvive() == true)
							{
								field_my_pokemon = my_pokemon_box[next_index];
								player_status->SetHPBar(field_my_pokemon->GetHP());
								player_status->SetCurrentHP(field_my_pokemon->GetHP());
								if (field_my_pokemon->pos.x != WIN_CENTER_X / 2)
									field_my_pokemon->pos.x = WIN_CENTER_X / 2;
								is_change = false;
								break;
							}
						}
					}
				}
			}
		}
		

		if (field_enemy_pokemon->GetHP() <= 0) // ���� ���ϸ� ü�� �˻�
		{
			if (is_attack)
				is_attack = false;

			mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
			attackState = ATTACK_START;

			is_change = true;
			if (is_change)
			{
				field_enemy_pokemon->SetIsSurvive(false);
				field_enemy_pokemon->Collapses();

				if (field_enemy_pokemon->pos.x >= WIN_WIDTH)
				{
					enemy_status->SetIsStatus(false);

					if (mode) // �߻����ϸ�� �������ٸ� �ٷ� �¸�
						clear_vsPokemon = true; // ���ϸ���� ������ Ż��
					else // è�Ǿ�� �������
					{
						if (!enemy_pokemon_box[0]->GetIsSurvive() && !enemy_pokemon_box[1]->GetIsSurvive() && !enemy_pokemon_box[2]->GetIsSurvive())
							clear_vsChampion = true; // ���� ���ϸ��� ��� ���������� ���� �¸�

						switch (change_turn)
						{
						case 0:
							if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
								behavior->GetPokeball()->GetClips()[0]->Play(); 
							behavior->GetPokeball()->Update(1);
							if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
							{
								enemy_status->SetIsStatus(true);
								change_turn++;
							}
								
							break;
						case 1:
							if (field_enemy_pokemon == enemy_pokemon_box[0] && enemy_pokemon_box[1]->GetIsSurvive() == true)  
								// ȭ������ �׾����� ����̵� ��ȯ
							{
								behavior->GetAppearance()->Update(2);
								if (behavior->GetAppearance()->GetClips()[2]->isPlay() == false)
								{
									field_enemy_pokemon = enemy_pokemon_box[1];
									enemy_status->SetHPBar(field_enemy_pokemon->GetHP());
									field_enemy_pokemon->pos.x = WIN_CENTER_X + 345;
									change_turn = 0;
									is_change = false;
									break;
								}
							}
							else if (field_enemy_pokemon == enemy_pokemon_box[1] && enemy_pokemon_box[2]->GetIsSurvive() == true) 
								// ����̵尡 �׾����� ��ī���ƽ� ��ȯ
							{
								behavior->GetAppearance()->Update(3);
								if (behavior->GetAppearance()->GetClips()[3]->isPlay() == false)
								{
									field_enemy_pokemon = enemy_pokemon_box[2];
									enemy_status->SetHPBar(field_enemy_pokemon->GetHP());
									field_enemy_pokemon->pos.x = WIN_CENTER_X + 345;
									change_turn = 0;
									is_change = false;
									break;
								}
							}
							else if (field_enemy_pokemon == enemy_pokemon_box[2] && enemy_pokemon_box[0]->GetIsSurvive() == true)
								// ��ī���ƽ��� �׾����� ȭ���� ��ȯ
							{
								behavior->GetAppearance()->Update(1);
								if (behavior->GetAppearance()->GetClips()[1]->isPlay() == false)
								{
									field_enemy_pokemon = enemy_pokemon_box[0];
									enemy_status->SetHPBar(field_enemy_pokemon->GetHP());
									field_enemy_pokemon->pos.x = WIN_CENTER_X + 345;
									change_turn = 0;
									is_change = false;
									break;
								}
							}
						}
					}
				}
			}
		}
	
		

		switch (turn)
		{
		case 0: // �÷��̾��� ��
			if (mouse_click_pos.x > 22 && mouse_click_pos.x < 405 && mouse_click_pos.y > 560 && mouse_click_pos.y < 726) // ���ݹ�ư Ŭ����
			{
				is_attack = true;

				if (is_attack)
				{
					if (field_my_pokemon == my_pokemon_box[0]) // ���� ���� �ʵ����ϸ��� �ص�����
					{
						switch (attackState)
						{
						case ATTACK_START:
							if (!behavior->GetSkill()->GetClips()[0]->isPlay())
								behavior->GetSkill()->GetClips()[0]->Play();
							attackState = ATTACK_ANIMATION;
							break;
						case ATTACK_ANIMATION:
							behavior->GetSkill()->Update(0);
							if (!behavior->GetSkill()->GetClips()[0]->isPlay())
								attackState = ATTACK_DAMAGE;
							break;
						case ATTACK_DAMAGE:
							field_my_pokemon->Attack(field_enemy_pokemon);
							enemy_status->SetHPBar(field_enemy_pokemon->GetHP());
							if (field_enemy_pokemon->GetHP() > 0)
							{
								attackState = ATTACK_START;
								turn++; // ������ �� ����
							}
							else
								attackState = ATTACK_END;
							break;
						case ATTACK_END:
							attackState = ATTACK_START; // ���� �ʱ�ȭ
							break;
						}
					}

					if (field_my_pokemon == my_pokemon_box[1]) //  ���� ���� �ʵ����ϸ��� ���丣Ʈ��
					{
						switch (attackState)
						{
						case ATTACK_START:
							if (!behavior->GetSkill()->GetClips()[3]->isPlay())
								behavior->GetSkill()->GetClips()[3]->Play();
							attackState = ATTACK_ANIMATION;
							break;
						case ATTACK_ANIMATION:
							behavior->GetSkill()->Update(3);
							if (!behavior->GetSkill()->GetClips()[3]->isPlay())
								attackState = ATTACK_DAMAGE;
							break;
						case ATTACK_DAMAGE:
							field_my_pokemon->Attack(field_enemy_pokemon);
							enemy_status->SetHPBar(field_enemy_pokemon->GetHP());
							if (field_enemy_pokemon->GetHP() > 0)
							{
								attackState = ATTACK_START;
								turn++; // ������ �� ����
							}
							else
								attackState = ATTACK_END;
							break;
						case ATTACK_END:
							attackState = ATTACK_START; // ���� �ʱ�ȭ
							break;
						}
					}
					if (field_my_pokemon == my_pokemon_box[2]) //  ���� ���� �ʵ����ϸ��� ��Ʒ簡��
					{
						switch (attackState)
						{
						case ATTACK_START:
							if (!behavior->GetSkill()->GetClips()[5]->isPlay())
								behavior->GetSkill()->GetClips()[5]->Play();
							attackState = ATTACK_ANIMATION;
							break;
						case ATTACK_ANIMATION:
							behavior->GetSkill()->Update(5);
							if (!behavior->GetSkill()->GetClips()[5]->isPlay())
								attackState = ATTACK_DAMAGE;
							break;
						case ATTACK_DAMAGE:
							field_my_pokemon->Attack(field_enemy_pokemon);
							enemy_status->SetHPBar(field_enemy_pokemon->GetHP());
							if (field_enemy_pokemon->GetHP() > 0)
							{
								attackState = ATTACK_START;
								turn++; // ������ �� ����
							}
							else
								attackState = ATTACK_END;
							break;
						case ATTACK_END:
							attackState = ATTACK_START; // ���� �ʱ�ȭ
							break;
						}
					}
				}
			}
			else if (mouse_click_pos.x > 440 && mouse_click_pos.x < 840 && mouse_click_pos.y > 560 && mouse_click_pos.y < 726) // ü��ȸ��
			{
				if (field_my_pokemon->GetHP() < 100)
				{
					is_recovery = true;

					if (is_recovery)
					{
						switch (meditationState)
						{
						case MEDITATION_START:
							if (!behavior->GetMeditation()->GetClips()[0]->isPlay())
								behavior->GetMeditation()->GetClips()[0]->Play(); // �ٽ� ����ϱ� ���� �۾�
							meditationState = MEDITATION_ANIMATION;
							break;
						case MEDITATION_ANIMATION:
							behavior->GetMeditation()->Update();
							if (!behavior->GetMeditation()->GetClips()[0]->isPlay())
								meditationState = MEDITATION_RECOVERY;
							break;
						case MEDITATION_RECOVERY:
							field_my_pokemon->Recovery();
							player_status->SetHPBar(field_my_pokemon->GetHP());
							player_status->SetCurrentHP(field_my_pokemon->GetHP());
							meditationState = MEDITATION_START;
							turn++; // �÷��̾��� �� ����
							break;
						}
					}
				}
				else // Ǯ���� ���¶� �������� ����
					mouse_click_pos = Vector2(0, 0);
			}
			else if (mouse_click_pos.x > 875 && mouse_click_pos.x < 1255 && mouse_click_pos.y > 560 && mouse_click_pos.y < 726) // ���ϸ� ��ü
			{
				for (auto p : my_pokemon_box) // ���� �ʵ� ���ϸ� ��������� ��ü�� �������ϴ� �˻�
				{
					if (p == field_my_pokemon)
						continue;
					if (p->GetIsSurvive())
					{
						is_change = true;
						break;
					}
				}

				if (is_change)
				{
					field_my_pokemon->Collapses();

					if (field_my_pokemon->pos.x <= 0)
					{
						player_status->SetIsStatus(false);

						if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
							behavior->GetPokeball()->GetClips()[0]->Play(); // �ٽ� ����ϱ� ���� �۾�	
						behavior->GetPokeball()->Update(0);
						if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
						{
							player_status->SetIsStatus(true);

							int current_index = -1; // ���� ���ϸ��� �ε����� ã��

							for (int i = 0; i < 3; ++i)
							{
								if (field_my_pokemon == my_pokemon_box[i])
								{
									current_index = i;
									break;
								}
							}

							for (int i = 1; i < 3; ++i)
							{
								int next_index = (current_index + i) % 3;
								if (my_pokemon_box[next_index]->GetIsSurvive() == true)
								{
									field_my_pokemon = my_pokemon_box[next_index];
									player_status->SetHPBar(field_my_pokemon->GetHP());
									player_status->SetCurrentHP(field_my_pokemon->GetHP());
									if (field_my_pokemon->pos.x != WIN_CENTER_X / 2)
										field_my_pokemon->pos.x = WIN_CENTER_X / 2;
									break;
								}
							}
							turn++; // �÷��̾��� �� ����
							break;
						}
					}
				}
				
			}
			break;
		case 1: // ������ ��
			if (mode) // �߻����ϸ�� ����
			{
				switch (attackState)
				{
				case ATTACK_START:
					if (behavior->GetSkill()->GetClips()[1]->isPlay() == false)
						behavior->GetSkill()->GetClips()[1]->Play();
					attackState = ATTACK_ANIMATION;
					break;
				case ATTACK_ANIMATION:
					behavior->GetSkill()->Update(1);  // ����� ���� �ִϸ��̼� ���
					if (behavior->GetSkill()->GetClips()[1]->isPlay() == false)
						attackState = ATTACK_DAMAGE;
					break;
				case ATTACK_DAMAGE:
					field_enemy_pokemon->Attack(field_my_pokemon);
					player_status->SetHPBar(field_my_pokemon->GetHP());
					player_status->SetCurrentHP(field_my_pokemon->GetHP());
					if (field_my_pokemon->GetHP() <= 0) // �÷��̾��� ü���� 0�̸�
					{
						if (is_attack)
							is_attack = false;
						if (is_recovery)
							is_recovery = false;
						if (is_change)
							is_change = false;
						attackState = ATTACK_START;
						turn--;
						mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
						break;
					}
				case ATTACK_END:
					if (is_attack)
						is_attack = false;
					else if (is_recovery)
						is_recovery = false;
					else if (is_change)
						is_change = false;
					turn--;
					attackState = ATTACK_START;
					mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
					break;
				}
			}
			else // è�Ǿ�� �������̸�
			{
				if (field_enemy_pokemon == enemy_pokemon_box[0]) // ���� ȭ�����̸�
				{
					switch (attackState)
					{
					case ATTACK_START:
						if (!behavior->GetSkill()->GetClips()[1]->isPlay())
							behavior->GetSkill()->GetClips()[1]->Play();
						attackState = ATTACK_ANIMATION;
						break;
					case ATTACK_ANIMATION:
						behavior->GetSkill()->Update(1);
						if (!behavior->GetSkill()->GetClips()[1]->isPlay())
							attackState = ATTACK_DAMAGE;
						break;
					case ATTACK_DAMAGE:
						field_enemy_pokemon->Attack(field_my_pokemon);
						player_status->SetHPBar(field_my_pokemon->GetHP());
						player_status->SetCurrentHP(field_my_pokemon->GetHP());
						if (field_my_pokemon->GetHP() <= 0)
						{
							if (is_attack)
								is_attack = false;
							if (is_recovery)
								is_recovery = false;
							if (is_change)
								is_change = false;
							attackState = ATTACK_START;
							turn--;
							mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
							break;
						}
						attackState = ATTACK_END;
						break;
					case ATTACK_END:
						if (is_attack)
							is_attack = false;
						if (is_recovery)
							is_recovery = false;
						if (is_change)
							is_change = false;
						attackState = ATTACK_START;
						turn--;
						mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
						break;
					}
				}
				if (field_enemy_pokemon == enemy_pokemon_box[1]) // ���� ����̵��̸�
				{
					switch (attackState)
					{
					case ATTACK_START:
						if (!behavior->GetSkill()->GetClips()[2]->isPlay())
							behavior->GetSkill()->GetClips()[2]->Play();
						attackState = ATTACK_ANIMATION;
						break;
					case ATTACK_ANIMATION:
						behavior->GetSkill()->Update(2);
						if (!behavior->GetSkill()->GetClips()[2]->isPlay())
							attackState = ATTACK_DAMAGE;
						break;
					case ATTACK_DAMAGE:
						field_enemy_pokemon->Attack(field_my_pokemon);
						player_status->SetHPBar(field_my_pokemon->GetHP());
						player_status->SetCurrentHP(field_my_pokemon->GetHP());
						if (field_my_pokemon->GetHP() <= 0)
						{
							if (is_attack)
								is_attack = false;
							if (is_recovery)
								is_recovery = false;
							if (is_change)
								is_change = false;
							attackState = ATTACK_START;
							turn--;
							mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
							break;
						}
						attackState = ATTACK_END;
						break;
					case ATTACK_END:
						if (is_attack)
							is_attack = false;
						else if (is_recovery)
							is_recovery = false;
						else if (is_change)
							is_change = false;
						attackState = ATTACK_START;
						turn--;
						mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
						break;
					}
				}
				if (field_enemy_pokemon == enemy_pokemon_box[2]) // ���� ��ī���ƽ���
				{
					switch (attackState)
					{
					case ATTACK_START:
						if (!behavior->GetSkill()->GetClips()[4]->isPlay())
							behavior->GetSkill()->GetClips()[4]->Play();
						attackState = ATTACK_ANIMATION;
						break;
					case ATTACK_ANIMATION:
						behavior->GetSkill()->Update(4);
						if (!behavior->GetSkill()->GetClips()[4]->isPlay())
							attackState = ATTACK_DAMAGE;
						break;
					case ATTACK_DAMAGE:
						field_enemy_pokemon->Attack(field_my_pokemon);
						player_status->SetHPBar(field_my_pokemon->GetHP());
						player_status->SetCurrentHP(field_my_pokemon->GetHP());
						if (field_my_pokemon->GetHP() <= 0)
						{
							if (is_attack)
								is_attack = false;
							if (is_recovery)
								is_recovery = false;
							if (is_change)
								is_change = false;
							attackState = ATTACK_START;
							turn--;
							mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
							break;
						}						attackState = ATTACK_END;
						break;
					case ATTACK_END:
						if (is_attack)
							is_attack = false;
						else if (is_recovery)
							is_recovery = false;
						else if (is_change)
							is_change = false;
						attackState = ATTACK_START;
						turn--;
						mouse_click_pos = Vector2(0, 0); // ���콺 Ŭ�� �ʱ�ȭ
						break;
					}
				}
			}
		}
	}


	field_enemy_pokemon->Update();
	field_my_pokemon->Update();

	button->Update();
}

void BattleManager::Render()
{
	field_enemy_pokemon->Render();
	field_my_pokemon->Render();

	player_status->Render();
	enemy_status->Render();

	button->Render();

	behavior->Render();
}
