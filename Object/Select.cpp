#include "framework.h"

Select::Select(bool gender)
{
	wstring file = L"Texture/CharactorSelect.png";
	Texture* t = Texture::Add(file);
	vector<Frame*> frames;

	if (gender) // 남자
	{
		Vector2 this_frame_size = { 45.0f, 107.0f };
		Vector2 init_pos = { 251, 106 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 44.0f, 108.0f };
		init_pos = { 298, 104 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 41.0f, 107.0f };
		init_pos = { 345, 105 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 44.0f, 108.0f };
		init_pos = { 389, 104 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));

		frames.clear();
	}
	else // 여자
	{
		Vector2 this_frame_size = { 52.0f, 110.0f };
		Vector2 init_pos = { 435, 102 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 48.0f, 112.0f };
		init_pos = { 491, 99 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 46.0f, 110.0f };
		init_pos = { 546, 101 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		this_frame_size = { 48.0f, 112.0f };
		init_pos = { 596, 100 };

		frames.push_back(new Frame(file, init_pos.x, init_pos.y,
			this_frame_size.x, this_frame_size.y));

		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));

		frames.clear();
	}

	boy_select_box = new RectCollider(Vector2(150,350));
	boy_select_box->is_active = true;
	boy_select_box->SetColor(0, 0, 0);

	girl_select_box = new RectCollider(Vector2(150, 350));
	girl_select_box->is_active = true;
	girl_select_box->SetColor(0, 0, 0);

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Select::~Select()
{
	delete clips[0];
	delete boy_select_box;
	delete girl_select_box;
	delete CB;
}

void Select::Update()
{
	boy_select_box->pos = Vector2(335, WIN_CENTER_Y);
	girl_select_box->pos = Vector2(940, WIN_CENTER_Y);

	this->scale = clips[0]->GetFrameSize() * 3.0f;
	WorldUpdate();

	clips[0]->Update();
	boy_select_box->WorldUpdate();
	girl_select_box->WorldUpdate();
}

void Select::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[0]->Render();
	boy_select_box->Render();
	girl_select_box->Render();
}
