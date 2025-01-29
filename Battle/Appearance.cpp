#include "framework.h"

Appearance::Appearance()
{
	wstring appearance_file = L"Texture/Pokemon.png";
	Texture* appearance_t = Texture::Add(appearance_file);
	
	Vector2 this_frame_size = { 35.0f, 39.0f };
	Vector2 init_pos = { 23, 250 };
	vector<Frame*> frames;

	frames.push_back(new Frame(appearance_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 59.0f, 47.0f };
	init_pos = { 90, 242 };

	frames.push_back(new Frame(appearance_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	appearance.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 0.8f)); // 찌르꼬 등장 0
	frames.clear();

	this_frame_size = { 80.0f, 80.0f };
	init_pos = { 244, 1594 };

	frames.push_back(new Frame(appearance_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 80.0f, 80.0f };
	init_pos = { 325, 1594 };

	frames.push_back(new Frame(appearance_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	appearance.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 0.8f)); // 화강돌 등장
	frames.clear();

	this_frame_size = { 80.0f, 80.0f };
	init_pos = { 244, 619 };

	frames.push_back(new Frame(appearance_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 80.0f, 80.0f };
	init_pos = { 325, 619 };

	frames.push_back(new Frame(appearance_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	appearance.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 0.8f)); // 로즈레이드 등장
	frames.clear();

	this_frame_size = { 80.0f, 80.0f };
	init_pos = { 1459, 1594 };

	frames.push_back(new Frame(appearance_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 80.0f, 80.0f };
	init_pos = { 1540, 1594 };

	frames.push_back(new Frame(appearance_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	appearance.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 0.8f)); // 한카리아스 등장
	frames.clear();

	for (auto i : is_active)
		i = true;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Appearance::~Appearance()
{
	for (auto a : appearance)
		delete a;
	appearance.clear();

	delete CB;
}

void Appearance::Update(UINT slot)
{
	if (slot == 0)
	{
		is_active[0] = true;
		this->pos = Vector2(WIN_CENTER_X + 345, 315);
		this->scale = appearance[0]->GetFrameSize() * 3.0f;
		this->WorldUpdate();
	}
	if (slot == 1)
	{
		is_active[1] = true;
		this->pos = Vector2(WIN_CENTER_X + 345, 315);
		this->scale = appearance[1]->GetFrameSize() * 3.0f;
		this->WorldUpdate();
	}
	if (slot == 2)
	{
		is_active[2] = true;
		this->pos = Vector2(WIN_CENTER_X + 345, 285);
		this->scale = appearance[1]->GetFrameSize() * 3.0f;
		this->WorldUpdate();
	}
	if (slot == 3)
	{
		is_active[3] = true;
		this->pos = Vector2(WIN_CENTER_X + 345, 285);
		this->scale = appearance[1]->GetFrameSize() * 3.0f;
		this->WorldUpdate();
	}
	appearance[slot]->Update();
}

void Appearance::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	if(is_active[0])
		appearance[0]->Render();
	if (is_active[1])
		appearance[1]->Render();
	if (is_active[2])
		appearance[2]->Render();
	if (is_active[3])
		appearance[3]->Render();
}
