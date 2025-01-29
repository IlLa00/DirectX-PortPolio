#include "framework.h"

Player::Player(Vector2 pos)
{
	CreateClip(gender);

	action = PLAYER_ACTIVE::DOWN_IDLE; // ó���� ���� �ε��ڼ�
	
	 // �ִϸ��̼� ����� <- �ڵ尡 ��� �Լ��� ��
	// ���ݱ��� �ȱ� ���� + ���߿� �����Ŷ� �޸��� ���� ����

	collider = new RectCollider(Vector2(40,50));
	collider->pos = pos;
	collider->is_active = true;
	collider->SetColor(0, 0, 0);

	this->pos = pos;

	is_collision = false;
	is_gender = true;

	collider->WorldUpdate();
}

Player::~Player()
{
	delete collider;

	for (Clip* c : clips)
		delete c;

	delete CB;
}

void Player::Update()
{
	collider->pos = this->pos;
	this->scale = clips[(UINT)action]->GetFrameSize() * 2.0f;

	collider->WorldUpdate();

	if (KEY_CON->Press(VK_DOWN))
	{
		SetClip(PLAYER_ACTIVE::DOWN_WALK);
		this->pos.y += 0.1f;
		clips[(UINT)action]->Update();
	}
	else if (KEY_CON->Press(VK_RIGHT))
	{
		SetClip(PLAYER_ACTIVE::RIGHT_WALK);
		this->pos.x += 0.1f;
		clips[(UINT)action]->Update();
	}
	else if (KEY_CON->Press(VK_UP))
	{
		SetClip(PLAYER_ACTIVE::UP_WALK);
		this->pos.y -= 0.1f;
		clips[(UINT)action]->Update();
	}
	else if (KEY_CON->Press(VK_LEFT))
	{
		SetClip(PLAYER_ACTIVE::LEFT_WALK);
		this->pos.x -= 0.1f;
		clips[(UINT)action]->Update();
	}
	
	if (KEY_CON->Up(VK_DOWN))
	{
		SetClip(PLAYER_ACTIVE::DOWN_IDLE);
		clips[(UINT)action]->Update();
	}
	if (KEY_CON->Up(VK_RIGHT))
	{
		SetClip(PLAYER_ACTIVE::RIGHT_IDLE);
		clips[(UINT)action]->Update();
	}
	if (KEY_CON->Up(VK_UP))
	{
		SetClip(PLAYER_ACTIVE::UP_IDLE);
		clips[(UINT)action]->Update();
	}
	if (KEY_CON->Up(VK_LEFT))
	{
		SetClip(PLAYER_ACTIVE::LEFT_IDLE);
		clips[(UINT)action]->Update();
	}

	WorldUpdate();
}

void Player::Render()
{
	collider->Render();

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[(UINT)action]->Render();
}

void Player::SetClip(PLAYER_ACTIVE stat)
{
	if (action != stat) 
	{
		clips[(UINT)action]->Stop();
		action = stat;
		clips[(UINT)action]->Play();
	}
}

void Player::OnCollision()
{
	is_collision = true;

	if (PLAYER_ACTIVE::DOWN_WALK) // ������ �����־��ٸ�
		SetClip(PLAYER_ACTIVE::DOWN_IDLE);
	else if (PLAYER_ACTIVE::RIGHT_WALK)
		SetClip(PLAYER_ACTIVE::RIGHT_IDLE);
	else if (PLAYER_ACTIVE::UP_WALK)
		SetClip(PLAYER_ACTIVE::UP_IDLE);
	else if (PLAYER_ACTIVE::LEFT_WALK)
		SetClip(PLAYER_ACTIVE::LEFT_IDLE);
}

void Player::SetGender(bool gender)
{
	if (is_gender)
	{
		if (gender == false)
		{
			is_gender = false;
			return;
		}
		else
		{
			clips.clear();
			CreateClip(true);
			is_gender = false;
		}
	}
}

void Player::CreateClip(bool gender)
{
	if (gender == true)
	{
		wstring file = L"Texture/Player_boy.png";
		Texture* t = Texture::Add(file);

		Vector2 this_frame_size = { 17.0f, 23.0f };
		Vector2 init_pos = { 25, 37 };
		vector<Frame*> frames;

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 0�� �Ʒ� �ε��ڼ�

		this_frame_size = { 17.0f, 25.0f };
		init_pos = { 60, 36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		init_pos = { 95, 36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 1�� �Ʒ��� �ȱ�
		frames.clear();

		this_frame_size = { 17.0f, 23.0f };
		init_pos = { 131, 37 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 2�� ������ �ε��ڼ�

		init_pos = { 166, 36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 17.0f, 24.0f };
		init_pos = { 201, 36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 3�� ������ �ȱ�
		frames.clear();

		this_frame_size = { 17.0f, 23.0f };
		init_pos = { 235, 37 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 4�� ���� �ε��ڼ�

		this_frame_size = { 17.0f, 25.0f };
		init_pos = { 270, 36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		init_pos = { 305, 36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 5�� ���� �ȱ�
		frames.clear();

		this_frame_size = { 17.0f, 23.0f };
		init_pos = { 340, 37 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 6�� ���� �ε��ڼ�

		this_frame_size = { 17.0f, 24.0f };
		init_pos = { 375, 36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 17.0f, 23.0f };
		init_pos = { 410, 36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 7�� ���� �ȱ�
		frames.clear();
	}
	else if (gender == false )
	{
		wstring file = L"Texture/Player_girl.png";
		Texture* t = Texture::Add(file);

		Vector2 this_frame_size = { 17.0f, 24.0f };
		Vector2 init_pos = { 25, 36 };
		vector<Frame*> frames;

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 0�� �Ʒ� �ε��ڼ�

		this_frame_size = { 18,26 };
		init_pos = { 59,35 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 18,26 };
		init_pos = { 95,35 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 1�� �Ʒ��� �ȱ�
		frames.clear();

		this_frame_size = { 17,24 };
		init_pos = { 129,36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 2�� ���� �ε��ڼ�

		this_frame_size = { 16,25 };
		init_pos = { 165,35 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 18,24 };
		init_pos = { 198,36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 3�� ���� �ȱ�
		frames.clear();

		this_frame_size = { 17,23 };
		init_pos = { 235,37 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));
		
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 4�� �� �ε�

		this_frame_size = { 18,25 };
		init_pos = { 269,36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 18,25 };
		init_pos = { 305,36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 5�� �� �ȱ�
		frames.clear();

		this_frame_size = { 17,24 };
		init_pos = { 342,36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 6�� �� �ε�

		this_frame_size = { 18,24 };
		init_pos = { 377,36 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 16,25 };
		init_pos = { 412,35 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP)); // 7�� �� �ȱ�
		frames.clear();
	}

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

}
