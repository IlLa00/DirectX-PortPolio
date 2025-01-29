#include "framework.h"

BattleManager::BattleManager(bool mode)
	: mode(mode)
{
	if (mode) // 야생포켓몬과 전투이면
	{
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 1621, 34, 80, 80)); // 팽도리
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 2107, 34, 80, 80, 60.0f)); // 엠페르트
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 2107, 2569, 80, 80, 80.0f)); // 디아루가

		enemy_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X + 345, 305), 23, 250, 35, 39)); // 찌르꼬
	}
	else // 챔피언과 전투이면
	{
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 1621, 34, 80, 80)); // 팽도리
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 2107, 34, 80, 80, 60.0f)); // 엠페르트
		my_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X / 2, 420), 2107, 2569, 80, 80, 80.0f)); // 디아루가

		enemy_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X + 345, 305), 244, 1594, 80, 80)); // 화강돌
		enemy_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X + 345, 285), 244, 619, 80, 80, 55.0f)); // 로즈레이드
		enemy_pokemon_box.push_back(new Pokemon(Vector2(WIN_CENTER_X + 345, 285), 1459, 1594, 80, 80, 60.0f)); // 한카리아스
	}
	field_my_pokemon = my_pokemon_box[0];
	field_my_pokemon->is_active = false;

	field_enemy_pokemon = enemy_pokemon_box[0];
	field_enemy_pokemon->is_active = false;

	// 매개변수로 포지션을 다르게 지정
	player_status = new StatusBox(true); // 플레이어 상태창
	enemy_status = new StatusBox(false); // 적군 상태창

	button = new SelectButton(); // 상호작용 버튼 공격, 회복, 교체
	button->is_active = false;

	behavior = new BattleAnimation(mode); // 애니메이션 관리

	turn = 0; // 0일때 플레이어 턴, 1일때 상대방 턴
	change_turn = 0; // 포켓몬 교체할때 사용

	// 열거형으로 상호작용 관리
	attackState = ATTACK_START;
	meditationState = MEDITATION_START;
	changeState = CHANGE_START;

	is_appearance = true; // true면 등장애니메이션 재생
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

void BattleManager::Appearance() // 등장
{
	if (mode) // 야생포켓몬과 전투일 때
	{
		behavior->GetPlayer()->SetGender(gender); // 플레이어 성별 설정

		switch (turn)
		{
		case 0:
			behavior->GetAppearance()->Update(0); // 찌르꼬 등장모션
			behavior->GetPlayer()->Update(0); // 플레이어 부동자세
			if (behavior->GetAppearance()->GetClips()[0]->isPlay() == false)
				turn++;
			break;
		case 1:
			field_enemy_pokemon->is_active = true;
			field_enemy_pokemon->Update();

			enemy_status->pos = Vector2(WIN_CENTER_X - 380, 200);
			enemy_status->SetHPBar(field_enemy_pokemon->GetHP());
			enemy_status->Update();

			behavior->GetPlayer()->Update(1); // 플레이어 포켓몬 소환
			if (behavior->GetPlayer()->GetClips()[1]->isPlay() == false)  // 플레이어 포켓몬 소환이 끝나면
				turn++;
			break;
		case 2:
			behavior->GetPokeball()->Update(0); // 포켓볼 등장
			if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false) // 포켓볼 등장이 끝나면
				turn++;
			break;
		case 3:
			field_my_pokemon->is_active = true; // 팽도리 출력
			field_my_pokemon->Update();

			player_status->pos = Vector2(WIN_CENTER_X + 360, 450);
			player_status->SetHPBar(field_my_pokemon->GetHP());
			player_status->SetCurrentHP(field_my_pokemon->GetHP());
			player_status->Update();

			turn = 0;
			is_appearance = false; // 모든 등장이 끝남
			break;
		}
	}
	else // 챔피언과 전투중이면
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
			behavior->GetPokeball()->Update(1); // 상대방이 포켓볼을 던짐
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

			if (behavior->GetPlayer()->GetClips()[1]->isPlay() == false) // 플레이어 모션이 끝나면
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
			is_appearance = false; // 모든 등장이 끝남
			break;
		}
	}
}

void BattleManager::Update()
{
	if (is_appearance)
		Appearance(); // 등장 모션 재생
	else
	{
		if (is_appearance || is_attack || is_recovery || is_change) // 행동 중이면 행동 버튼이 활성화 되지 않음
			button->is_active = false;
		else
			button->is_active = true;

		// 상태창 관리
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

		if (field_my_pokemon->GetHP() <= 0) // 플레이어 포켓몬 체력 검사
		{
			if (is_attack)
				is_attack = false;

			mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
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
							lose_vsPokemon = true;  // 아군 포켓몬이 모두 쓰러졌으면 게임 패배, 이 경우 다시 재도전 가능
							clear_vsPokemon = true;
						}
						else
						{
							lose_vsChampion = true;  // 아군 포켓몬이 모두 쓰러졌으면 게임 패배, 이 경우 다시 재도전 가능
							clear_vsChampion = true;
						}
					}

					if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
						behavior->GetPokeball()->GetClips()[0]->Play(); // 다시 재생하기 위한 작업	
					behavior->GetPokeball()->Update(0);
					if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
					{
						player_status->SetIsStatus(true);

						UINT current_index = -1; // 현재 포켓몬의 인덱스를 찾기

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
		

		if (field_enemy_pokemon->GetHP() <= 0) // 상대방 포켓몬 체력 검사
		{
			if (is_attack)
				is_attack = false;

			mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
			attackState = ATTACK_START;

			is_change = true;
			if (is_change)
			{
				field_enemy_pokemon->SetIsSurvive(false);
				field_enemy_pokemon->Collapses();

				if (field_enemy_pokemon->pos.x >= WIN_WIDTH)
				{
					enemy_status->SetIsStatus(false);

					if (mode) // 야생포켓몬과 전투였다면 바로 승리
						clear_vsPokemon = true; // 포켓몬과의 전투씬 탈출
					else // 챔피언과 전투라면
					{
						if (!enemy_pokemon_box[0]->GetIsSurvive() && !enemy_pokemon_box[1]->GetIsSurvive() && !enemy_pokemon_box[2]->GetIsSurvive())
							clear_vsChampion = true; // 상대방 포켓몬이 모두 쓰러졌으면 게임 승리

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
								// 화강돌이 죽었으면 로즈레이드 소환
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
								// 로즈레이드가 죽었으면 한카리아스 소환
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
								// 한카리아스가 죽었으면 화강돌 소환
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
		case 0: // 플레이어의 턴
			if (mouse_click_pos.x > 22 && mouse_click_pos.x < 405 && mouse_click_pos.y > 560 && mouse_click_pos.y < 726) // 공격버튼 클릭시
			{
				is_attack = true;

				if (is_attack)
				{
					if (field_my_pokemon == my_pokemon_box[0]) // 현재 나의 필드포켓몬이 팽도리면
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
								turn++; // 상대방의 턴 시작
							}
							else
								attackState = ATTACK_END;
							break;
						case ATTACK_END:
							attackState = ATTACK_START; // 상태 초기화
							break;
						}
					}

					if (field_my_pokemon == my_pokemon_box[1]) //  현재 나의 필드포켓몬이 엠페르트면
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
								turn++; // 상대방의 턴 시작
							}
							else
								attackState = ATTACK_END;
							break;
						case ATTACK_END:
							attackState = ATTACK_START; // 상태 초기화
							break;
						}
					}
					if (field_my_pokemon == my_pokemon_box[2]) //  현재 나의 필드포켓몬이 디아루가면
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
								turn++; // 상대방의 턴 시작
							}
							else
								attackState = ATTACK_END;
							break;
						case ATTACK_END:
							attackState = ATTACK_START; // 상태 초기화
							break;
						}
					}
				}
			}
			else if (mouse_click_pos.x > 440 && mouse_click_pos.x < 840 && mouse_click_pos.y > 560 && mouse_click_pos.y < 726) // 체력회복
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
								behavior->GetMeditation()->GetClips()[0]->Play(); // 다시 재생하기 위한 작업
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
							turn++; // 플레이어의 턴 종료
							break;
						}
					}
				}
				else // 풀피인 상태라서 실행하지 않음
					mouse_click_pos = Vector2(0, 0);
			}
			else if (mouse_click_pos.x > 875 && mouse_click_pos.x < 1255 && mouse_click_pos.y > 560 && mouse_click_pos.y < 726) // 포켓몬 교체
			{
				for (auto p : my_pokemon_box) // 현재 필드 포켓몬만 살아있으면 교체를 하지못하니 검사
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
							behavior->GetPokeball()->GetClips()[0]->Play(); // 다시 재생하기 위한 작업	
						behavior->GetPokeball()->Update(0);
						if (behavior->GetPokeball()->GetClips()[0]->isPlay() == false)
						{
							player_status->SetIsStatus(true);

							int current_index = -1; // 현재 포켓몬의 인덱스를 찾기

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
							turn++; // 플레이어의 턴 종료
							break;
						}
					}
				}
				
			}
			break;
		case 1: // 상대방의 턴
			if (mode) // 야생포켓몬과 전투
			{
				switch (attackState)
				{
				case ATTACK_START:
					if (behavior->GetSkill()->GetClips()[1]->isPlay() == false)
						behavior->GetSkill()->GetClips()[1]->Play();
					attackState = ATTACK_ANIMATION;
					break;
				case ATTACK_ANIMATION:
					behavior->GetSkill()->Update(1);  // 찌르꼬의 공격 애니메이션 재생
					if (behavior->GetSkill()->GetClips()[1]->isPlay() == false)
						attackState = ATTACK_DAMAGE;
					break;
				case ATTACK_DAMAGE:
					field_enemy_pokemon->Attack(field_my_pokemon);
					player_status->SetHPBar(field_my_pokemon->GetHP());
					player_status->SetCurrentHP(field_my_pokemon->GetHP());
					if (field_my_pokemon->GetHP() <= 0) // 플레이어의 체력이 0이면
					{
						if (is_attack)
							is_attack = false;
						if (is_recovery)
							is_recovery = false;
						if (is_change)
							is_change = false;
						attackState = ATTACK_START;
						turn--;
						mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
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
					mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
					break;
				}
			}
			else // 챔피언과 전투중이면
			{
				if (field_enemy_pokemon == enemy_pokemon_box[0]) // 현재 화강돌이면
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
							mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
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
						mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
						break;
					}
				}
				if (field_enemy_pokemon == enemy_pokemon_box[1]) // 현재 로즈레이드이면
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
							mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
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
						mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
						break;
					}
				}
				if (field_enemy_pokemon == enemy_pokemon_box[2]) // 현재 한카리아스면
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
							mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
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
						mouse_click_pos = Vector2(0, 0); // 마우스 클릭 초기화
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
