#include "framework.h"

StatusBox::StatusBox(bool position) : position(position)
{
	if (position) // 플레이어 포켓몬
	{
		Box = new Frame(L"Texture/StatusBox.png", 7, 92, 128, 47);
		player_name = new Font(L"PLAYER_NAME");
		player_level = new Font(L"PLAYER_LEVEL");
		player_max_hp = new Font(L"PLAYER_MAX_HP");
		player_current_hp = new Font(L"PLAYER_CURRENT_HP");

		for (int i = 0; i < 10; i++)
			HPbar_list.push_back(new HPBar(Vector2(WIN_CENTER_X + 400 + 21.5 * i, 458.5)));
	}
	else // 상대 포켓몬
	{
		Box = new Frame(L"Texture/StatusBox.png", 156, 92, 122, 35);
		enemy_name = new Font(L"ENEMY_NAME");
		enemy_level = new Font(L"ENEMY_LEVEL");

		for (int i = 0; i < 10; i++)
			HPbar_list.push_back(new HPBar(Vector2(WIN_CENTER_X - 420 + 21.5 * i, 225)));
	}
	status_active = false;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

StatusBox::~StatusBox()
{
	if (position)
	{
		delete Box;
		delete player_name;
		delete player_level;
		delete player_max_hp;
		delete player_current_hp;

		for (auto h : HPbar_list)
			delete h;
		HPbar_list.clear();
	}
	else
	{
		delete Box;
		delete enemy_name;
		delete enemy_level;

		for (auto h : HPbar_list)
			delete h;
		HPbar_list.clear();
	}
	
	delete CB;
}

void StatusBox::Update()
{
	if (position) // 플레이어 포켓몬 상태창
	{
		status_active = true;

		this->scale.x = Box->GetFrameSize().x * 4.25f;
		this->scale.y = Box->GetFrameSize().y * 2.5f;

		for(auto h : HPbar_list)
			h->Update();

		player_name->Update(slot);
		player_level->Update(slot);
		player_max_hp->Update(slot);
		player_current_hp->Update(slot);
	}
	else // 상대 포켓몬 상태창
	{
		status_active = true;

		this->scale.x = Box->GetFrameSize().x * 4.5f;
		this->scale.y = Box->GetFrameSize().y * 3.25f;

		for (auto h : HPbar_list)
			h->Update();

		if (is_vsPokemon)
		{
			enemy_name->Update(slot);
			enemy_level->Update(slot);
		}
		else if (is_vsChampion)
		{
			enemy_name->Update(slot + 1);
			enemy_level->Update(slot + 1);
		}
	}
	
	WorldUpdate();
}

void StatusBox::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	if (position)
	{
		if (status_active)
		{
			Box->Render();

			UINT current_hp = (UINT)hp / 10;

			if (current_hp != 0) // 10단위로 체력바 출력
			{
				for (int i = 0; i < current_hp; i++)
					HPbar_list[i]->Render();
			}
		
			player_name->Render(slot);
			player_level->Render(slot);
			player_max_hp->Render(slot);
			player_current_hp->Render(slot);
		}
	}
	else
	{
		if (status_active)
		{
			Box->Render();
			
			UINT current_hp = (UINT)hp / 10;

			if (current_hp != 0) // 10단위로 체력바 출력
			{
				for (int i = 0; i < current_hp; i++)
					HPbar_list[i]->Render();
			}
				
			if (is_vsPokemon)
			{
				enemy_name->Render(slot);
				enemy_level->Render(slot);
			}
			else if (is_vsChampion)
			{
				enemy_name->Render(slot + 1);
				enemy_level->Render(slot + 1);
			}
			
		}
	}
}
