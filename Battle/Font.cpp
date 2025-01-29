#include "framework.h"

Font::Font(wstring name, wstring file) : name(name), file(file)
{
	//wstring file = L"Texture/StatusBox.png";
	// vector<TextFrame*> font_box;

	if (name == L"PLAYER_NAME") // 플레이어 포켓몬 이름
	{
		font_box.push_back(new TextFrame(file, 375, 50, 6, 10)); // P
		font_box.push_back(new TextFrame(file, 630, 32, 2, 9)); // i
		font_box.push_back(new TextFrame(file, 581, 53, 6, 9)); // p
		font_box.push_back(new TextFrame(file, 518, 50, 3, 10)); // l
		font_box.push_back(new TextFrame(file, 501, 72, 6, 7)); // u
		font_box.push_back(new TextFrame(file, 581, 53, 6, 9)); // p

		player_name_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 359, 31, 6, 10)); // e
		font_box.push_back(new TextFrame(file, 533, 53, 6, 7)); // m
		font_box.push_back(new TextFrame(file, 581, 53, 6, 9)); // p
		font_box.push_back(new TextFrame(file, 565, 53, 6, 7)); // o
		font_box.push_back(new TextFrame(file, 518, 50, 3, 10)); // l
		font_box.push_back(new TextFrame(file, 565, 34, 6, 7)); // e
		font_box.push_back(new TextFrame(file, 565, 53, 6, 7)); // o
		font_box.push_back(new TextFrame(file, 549, 53, 6, 7)); // n

		player_name_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 343, 31, 6, 10)); // D
		font_box.push_back(new TextFrame(file, 630, 32, 2, 9)); // i
		font_box.push_back(new TextFrame(file, 501, 34, 6, 7)); // a
		font_box.push_back(new TextFrame(file, 518, 50, 3, 10)); // l
		font_box.push_back(new TextFrame(file, 597, 34, 6, 9)); // g
		font_box.push_back(new TextFrame(file, 501, 34, 6, 7)); // a

		player_name_box.push_back(font_box);
		font_box.clear();
	}
	else if (name == L"ENEMY_NAME")
	{
		font_box.push_back(new TextFrame(file, 423, 50, 6, 10)); // S
		font_box.push_back(new TextFrame(file, 645, 52, 5, 8)); // t
		font_box.push_back(new TextFrame(file, 501, 34, 6, 7)); // a
		font_box.push_back(new TextFrame(file, 613, 53, 6, 7)); // r
		font_box.push_back(new TextFrame(file, 518, 50, 3, 10)); // l
		font_box.push_back(new TextFrame(file, 565, 72, 6, 9)); // y

		enemy_name_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 423, 50, 6, 10)); // S
		font_box.push_back(new TextFrame(file, 581, 53, 6, 9)); // p
		font_box.push_back(new TextFrame(file, 630, 32, 2, 9)); // i
		font_box.push_back(new TextFrame(file, 613, 53, 6, 7)); // r
		font_box.push_back(new TextFrame(file, 630, 32, 2, 9)); // i
		font_box.push_back(new TextFrame(file, 645, 52, 5, 8)); // t
		font_box.push_back(new TextFrame(file, 565, 53, 6, 7)); // o
		font_box.push_back(new TextFrame(file, 533, 53, 6, 7)); // m
		font_box.push_back(new TextFrame(file, 517, 31, 6, 10)); // b

		enemy_name_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 407, 50, 6, 10)); // R
		font_box.push_back(new TextFrame(file, 565, 53, 6, 7)); // o
		font_box.push_back(new TextFrame(file, 629, 53, 6, 7)); // s
		font_box.push_back(new TextFrame(file, 565, 34, 6, 7)); // e
		font_box.push_back(new TextFrame(file, 613, 53, 6, 7)); // r
		font_box.push_back(new TextFrame(file, 501, 34, 6, 7)); // a
		font_box.push_back(new TextFrame(file, 549, 31, 6, 10)); // d
		font_box.push_back(new TextFrame(file, 565, 34, 6, 7)); // e

		enemy_name_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 391, 31, 6, 10)); // G
		font_box.push_back(new TextFrame(file, 501, 34, 6, 7)); // a
		font_box.push_back(new TextFrame(file, 613, 53, 6, 7)); // r
		font_box.push_back(new TextFrame(file, 533, 34, 6, 7)); // c
		font_box.push_back(new TextFrame(file, 613, 31, 6, 10)); // h
		font_box.push_back(new TextFrame(file, 565, 53, 6, 7)); // o
		font_box.push_back(new TextFrame(file, 533, 53, 6, 7)); // m
		font_box.push_back(new TextFrame(file, 581, 53, 6, 9)); // p

		enemy_name_box.push_back(font_box);
		font_box.clear();

	}
	else if (name == L"PLAYER_LEVEL") // 플레이어 포켓몬 레벨
	{
		font_box.push_back(new TextFrame(file, 375, 88, 6, 10)); // 5

		player_level_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 375, 88, 6, 10)); // 5
		font_box.push_back(new TextFrame(file, 295, 88, 6, 10)); // 0

		player_level_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 312, 88, 4, 10)); // 1
		font_box.push_back(new TextFrame(file, 295, 88, 6, 10)); // 0
		font_box.push_back(new TextFrame(file, 295, 88, 6, 10)); // 0

		player_level_box.push_back(font_box);
		font_box.clear();
	}
	else if (name == L"ENEMY_LEVEL") // 적군 포켓몬 레벨
	{
		font_box.push_back(new TextFrame(file, 327, 88, 6, 10)); // 2

		enemy_level_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 391, 88, 6, 10)); // 6
		font_box.push_back(new TextFrame(file, 312, 88, 4, 10)); // 1

		enemy_level_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 391, 88, 6, 10)); // 6
		font_box.push_back(new TextFrame(file, 295, 88, 6, 10)); // 0

		enemy_level_box.push_back(font_box);
		font_box.clear();

		font_box.push_back(new TextFrame(file, 391, 88, 6, 10)); // 6
		font_box.push_back(new TextFrame(file, 391, 88, 6, 10)); // 6

		enemy_level_box.push_back(font_box);
		font_box.clear();
	}
	else if (name == L"PLAYER_MAX_HP") // 건들필요없음
	{
		font_box.push_back(new TextFrame(file, 312, 88, 4, 10)); // 1
		font_box.push_back(new TextFrame(file, 295, 88, 6, 10)); // 0
		font_box.push_back(new TextFrame(file, 295, 88, 6, 10)); // 0

		player_max_hp_box.push_back(font_box);
		font_box.clear();
	}

	//font_box.push_back(new Frame(file, 295, 88, 6, 10)); // 0
	//font_box.push_back(new Frame(file, 312, 88, 4, 10)); // 1
	//font_box.push_back(new Frame(file, 327, 88, 6, 10)); // 2
	//font_box.push_back(new Frame(file, 343, 88, 6, 10)); // 3
	//font_box.push_back(new Frame(file, 359, 88, 6, 10)); // 4
	//font_box.push_back(new Frame(file, 375, 88, 6, 10)); // 5
	//font_box.push_back(new Frame(file, 391, 88, 6, 10)); // 6
	//font_box.push_back(new Frame(file, 407, 88, 6, 10)); // 7
	//font_box.push_back(new Frame(file, 423, 88, 6, 10)); // 8
	//font_box.push_back(new Frame(file, 439, 88, 6, 10)); // 9

	//font_box.push_back(new Frame(file, 295, 31, 6, 10)); // A
	//font_box.push_back(new Frame(file, 311, 31, 6, 10)); // B
	//font_box.push_back(new Frame(file, 327, 31, 6, 10)); // C
	//font_box.push_back(new Frame(file, 343, 31, 6, 10)); // D
	//font_box.push_back(new Frame(file, 359, 31, 6, 10)); // E
	//font_box.push_back(new Frame(file, 375, 31, 6, 10)); // F
	//font_box.push_back(new Frame(file, 391, 31, 6, 10)); // G
	//font_box.push_back(new Frame(file, 407, 31, 6, 10)); // H
	//font_box.push_back(new Frame(file, 424, 31, 4, 10)); // I                         
	//font_box.push_back(new Frame(file, 439, 31, 6, 10)); // J
	//font_box.push_back(new Frame(file, 295, 50, 6, 10)); // K
	//font_box.push_back(new Frame(file, 311, 50, 6, 10)); // L
	//font_box.push_back(new Frame(file, 327, 50, 6, 10)); // M
	//font_box.push_back(new Frame(file, 343, 50, 6, 10)); // N
	//font_box.push_back(new Frame(file, 359, 50, 6, 10)); // O
	//font_box.push_back(new Frame(file, 375, 50, 6, 10)); // P
	//font_box.push_back(new Frame(file, 391, 50, 6, 11)); // Q
	//font_box.push_back(new Frame(file, 407, 50, 6, 10)); // R
	//font_box.push_back(new Frame(file, 423, 50, 6, 10)); // S
	//font_box.push_back(new Frame(file, 439, 50, 6, 10)); // T
	//font_box.push_back(new Frame(file, 295, 69, 6, 10)); // U
	//font_box.push_back(new Frame(file, 311, 69, 6, 10)); // V
	//font_box.push_back(new Frame(file, 327, 69, 6, 10)); // W
	//font_box.push_back(new Frame(file, 343, 69, 6, 10)); // X
	//font_box.push_back(new Frame(file, 359, 69, 6, 10)); // Y
	//font_box.push_back(new Frame(file, 375, 69, 6, 10)); // Z

	//font_box.push_back(new Frame(file, 501, 34, 6, 7)); // a
	//font_box.push_back(new Frame(file, 517, 31, 6, 10)); // b
	//font_box.push_back(new Frame(file, 533, 34, 6, 7)); // c
	//font_box.push_back(new Frame(file, 549, 31, 6, 10)); // d
	//font_box.push_back(new Frame(file, 565, 34, 6, 7)); // e
	//font_box.push_back(new Frame(file, 581, 31, 5, 10)); // f
	//font_box.push_back(new Frame(file, 597, 34, 6, 9)); // g
	//font_box.push_back(new Frame(file, 613, 31, 6, 10)); // h
	//font_box.push_back(new Frame(file, 630, 32, 2, 9)); // i
	//font_box.push_back(new Frame(file, 645, 32, 4, 11)); // j
	//font_box.push_back(new Frame(file, 501, 50, 6, 10)); // k
	//font_box.push_back(new Frame(file, 518, 50, 3, 10)); // l
	//font_box.push_back(new Frame(file, 533, 53, 6, 7)); // m
	//font_box.push_back(new Frame(file, 549, 53, 6, 7)); // n
	//font_box.push_back(new Frame(file, 565, 53, 6, 7)); // o
	//font_box.push_back(new Frame(file, 581, 53, 6, 9)); // p
	//font_box.push_back(new Frame(file, 597, 53, 6, 9)); // q
	//font_box.push_back(new Frame(file, 613, 53, 6, 7)); // r
	//font_box.push_back(new Frame(file, 629, 53, 6, 7)); // s
	//font_box.push_back(new Frame(file, 645, 52, 5, 8)); // t
	//font_box.push_back(new Frame(file, 501, 72, 6, 7)); // u
	//font_box.push_back(new Frame(file, 517, 72, 6, 7)); // v
	//font_box.push_back(new Frame(file, 533, 72, 6, 7)); // w
	//font_box.push_back(new Frame(file, 549, 72, 6, 7)); // x
	//font_box.push_back(new Frame(file, 565, 72, 6, 9)); // y
	//font_box.push_back(new Frame(file, 581, 72, 6, 7)); // z


	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

}

Font::~Font()
{
	if (name == L"PLAYER_NAME")
	{
		for (auto box : player_name_box)
		{
			for (auto frame : box)
				delete frame;
		}
	}
	else if (name == L"ENEMY_NAME")
	{
		for (auto box : enemy_name_box)
		{
			for (auto frame : box)
				delete frame;
		}
	}
	else if (name == L"PLAYER_LEVEL")
	{
		for (auto box : player_level_box)
		{
			for (auto frame : box)
				delete frame;
		}
	}
	else if (name == L"ENEMY_LEVEL")
	{
		for (auto box : enemy_level_box)
		{
			for (auto frame : box)
				delete frame;
		}
	}
	else if (name == L"PLAYER_MAX_HP")
	{
		for (auto box : player_max_hp_box)
		{
			for (auto frame : box)
				delete frame;
		}
	}

	for (auto c : player_current_hp)
		delete c;
	player_current_hp.clear();

	delete CB;
}

void Font::SetHP(float hp)
{
	this->hp = hp;
	player_current_hp.clear();

	while (hp >= 1.0f) 
	{
		float r = fmod(hp, 10.0);  // 나머지 구하기
		
		switch ((int)r)
		{
		case 0:
			player_current_hp.push_back(new TextFrame(file, 295, 88, 6, 10));
			break;
		case 1:
			player_current_hp.push_back(new TextFrame(file, 312, 88, 4, 10));
			break;
		case 2:
			player_current_hp.push_back(new TextFrame(file, 327, 88, 6, 10));
			break;
		case 3:
			player_current_hp.push_back(new TextFrame(file, 343, 88, 6, 10));
			break;
		case 4:
			player_current_hp.push_back(new TextFrame(file, 359, 88, 6, 10));
			break;
		case 5:
			player_current_hp.push_back(new TextFrame(file, 375, 88, 6, 10));
			break;
		case 6:
			player_current_hp.push_back(new TextFrame(file, 391, 88, 6, 10));
			break;
		case 7:
			player_current_hp.push_back(new TextFrame(file, 407, 88, 6, 10));
			break;
		case 8:
			player_current_hp.push_back(new TextFrame(file, 423, 88, 6, 10));
			break;
		case 9:
			player_current_hp.push_back(new TextFrame(file, 439, 88, 6, 10));
			break;
		}

		hp /= 10.0f;
	}

	reverse(player_current_hp.begin(), player_current_hp.end());
}

void Font::Update(UINT slot)
{
	if (name == L"PLAYER_NAME")
	{
		for (int i = 0; i < player_name_box[slot].size(); i++)
		{
			player_name_box[slot][i]->pos = Vector2((WIN_CENTER_X + 180) + 20 * i, 435);
			player_name_box[slot][i]->scale = player_name_box[slot][i]->GetFrameSize() * 3.25f;
			player_name_box[slot][i]->WorldUpdate();
		}
	}
	else if (name == L"ENEMY_NAME")
	{
		for (int i = 0; i < enemy_name_box[slot].size(); i++)
		{
			enemy_name_box[slot][i]->pos = Vector2(50 + 20 * i, 190);
			enemy_name_box[slot][i]->scale = enemy_name_box[slot][i]->GetFrameSize() * 3.25f;
			enemy_name_box[slot][i]->WorldUpdate();
		}
	}
	else if (name == L"PLAYER_LEVEL")
	{
		for (int i = 0; i < player_level_box[slot].size(); i++)
		{
			player_level_box[slot][i]->pos = Vector2((WIN_CENTER_X + 550) + 20 * i, 430);
			player_level_box[slot][i]->scale = player_level_box[slot][i]->GetFrameSize() * 2.5f;
			player_level_box[slot][i]->WorldUpdate();
		}
	}
	else if (name == L"ENEMY_LEVEL")
	{
		for (int i = 0; i < enemy_level_box[slot].size(); i++)
		{
			enemy_level_box[slot][i]->pos = Vector2(380 + 20 * i, 190);
			enemy_level_box[slot][i]->scale = enemy_level_box[slot][i]->GetFrameSize() * 2.5f;
			enemy_level_box[slot][i]->WorldUpdate();
		}
	}
	else if (name == L"PLAYER_MAX_HP")
	{
		for (int i = 0; i < player_max_hp_box[0].size(); i++)
		{
			player_max_hp_box[0][i]->pos = Vector2((WIN_CENTER_X + 520) + 20 * i, 480);
			player_max_hp_box[0][i]->scale = player_max_hp_box[0][i]->GetFrameSize() * 1.5f;
			player_max_hp_box[0][i]->WorldUpdate();
		}
	}
	else if (name == L"PLAYER_CURRENT_HP") // 이쪽이 현재체력 구하는 코드
	{
		for (int i = 0; i < player_current_hp.size(); i++)
		{
			player_current_hp[i]->pos = Vector2(WIN_CENTER_X + 400 + (20 * i), 480);
			player_current_hp[i]->scale = player_current_hp[i]->GetFrameSize() * 1.5f;
			player_current_hp[i]->WorldUpdate();
		}
	}
}

void Font::Render(UINT slot)
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	if (name == L"PLAYER_NAME")
	{
		for (auto a : player_name_box[slot])
		{
			a->Render();
		}
	}
	else if (name == L"ENEMY_NAME")
	{
		for (auto b : enemy_name_box[slot])
		{
			b->Render();
		}
	}
	else if (name == L"PLAYER_LEVEL")
	{
		for (auto c : player_level_box[slot])
		{
			c->Render();
		}
	}
	else if (name == L"ENEMY_LEVEL")
	{
		for (auto d : enemy_level_box[slot])
		{
			d->Render();
		}
	}
	else if (name == L"PLAYER_MAX_HP")
	{
		for (auto e : player_max_hp_box[0])
		{
			e->Render();
		}
	}
	else if (name == L"PLAYER_CURRENT_HP")
	{
		for (auto f : player_current_hp)
		{
			f->Render();
		}
	}
}
