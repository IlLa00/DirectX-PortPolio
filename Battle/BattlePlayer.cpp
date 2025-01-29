#include "framework.h"

BattlePlayer::BattlePlayer(Vector2 pos, bool gender)
{
	CreateClip(gender);
	this->pos = pos;
	is_gender = true;
}

BattlePlayer::~BattlePlayer()
{
	for (Clip* c : clips)
		delete c;
	clips.clear();

	delete CB;
}

void BattlePlayer::SetGender(bool gender)
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

void BattlePlayer::Update(UINT slot)
{
	if (slot == 0)
	{
		this->pos = pos;
		this->scale = clips[slot]->GetFrameSize() * 3.5f;
		WorldUpdate();
	}
	else if (slot == 1)
	{
		this->pos.x -= pos.x * 3.0f * DELTA;
		this->scale = clips[slot]->GetFrameSize() * 3.5f;
		WorldUpdate();
	}
	clips[slot]->Update();
}

void BattlePlayer::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[0]->Render();
	clips[1]->Render();
}

void BattlePlayer::CreateClip(bool gender)
{
	Vector2 this_frame_size;
	Vector2 init_pos;
	vector<Frame*> frames;


	if (gender == true)
	{
		wstring file = L"Texture/Player_boy.png";
		Texture* t = Texture::Add(file);

		this_frame_size = { 47.0f, 59.0f };
		init_pos = { 305, 398 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f)); // 부동자세

		this_frame_size = { 59.0f, 56.0f };
		init_pos = { 364, 401 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 65.0f, 58.0f };
		init_pos = { 435, 399 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 69.0f, 57.0f };
		init_pos = { 512, 400 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 67.0f, 53.0f };
		init_pos = { 593, 404 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f));

		frames.clear();
	}

	else // 여자
	{
		wstring file = L"Texture/Player_girl.png";
		Texture* t = Texture::Add(file);

		Vector2 this_frame_size = { 56.0f, 63.0f };
		Vector2 init_pos = { 305, 394 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f)); // 부동자세

		this_frame_size = { 54.0f, 60.0f };
		init_pos = { 373, 397 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 66.0f, 62.0f };
		init_pos = { 439, 395 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 77.0f, 61.0f };
		init_pos = { 517, 396 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 74.0f, 56.0f };
		init_pos = { 606, 401 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f));

		frames.clear();
	}

	for (auto s : is_active)
		s = true;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}