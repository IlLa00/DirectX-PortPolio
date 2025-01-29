#include "framework.h"

Skill::Skill()
{
	wstring file = L"Texture/Attack/Hydro-Pump.png";
	Texture* t = Texture::Add(file);
	vector<Frame*> frames;

	Vector2 this_frame_size = { 43.0f, 58.0f };
	Vector2 init_pos = { 78, 83 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 81.0f, 76.0f };
	init_pos = { 78, 212 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 178.0f, 139.0f };
	init_pos = { 78, 287 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 178.0f, 139.0f };
	init_pos = { 78, 432 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 184.0f, 139.0f };
	init_pos = { 72, 576 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 179.0f, 139.0f };
	init_pos = { 78, 720 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 181.0f, 143.0f };
	init_pos = { 75, 864 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 181.0f, 141.0f };
	init_pos = { 331, 0 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 176.0f, 143.0f };
	init_pos = { 336, 143 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 171.0f, 144.0f };
	init_pos = { 341, 287 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 172.0f, 132.0f };
	init_pos = { 340, 432 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 159.0f, 120.0f };
	init_pos = { 353, 576 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 110.0f, 122.0f };
	init_pos = { 402, 720 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 87.0f, 115.0f };
	init_pos = { 425, 866 };

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	skill.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f)); // 1 하이드로 펌프

	frames.clear();

	wstring Crunch_file = L"Texture/Attack/Crunch.png";
	Texture* Crunch_t = Texture::Add(Crunch_file);

	this_frame_size = { 104.0f, 116.0f };
	init_pos = { 0, 44 };

	frames.push_back(new Frame(Crunch_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 131.0f };
	init_pos = { 120, 38 };

	frames.push_back(new Frame(Crunch_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 148.0f };
	init_pos = { 266, 33 };

	frames.push_back(new Frame(Crunch_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 171.0f };
	init_pos = { 390, 21 };

	frames.push_back(new Frame(Crunch_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 157.0f };
	init_pos = { 525, 29 };

	frames.push_back(new Frame(Crunch_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 136.0f };
	init_pos = { 672, 42 };

	frames.push_back(new Frame(Crunch_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 111.0f };
	init_pos = { 817, 57 };

	frames.push_back(new Frame(Crunch_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 78.0f };
	init_pos = { 0, 260 };

	frames.push_back(new Frame(Crunch_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	skill.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f)); // 2 물기
	frames.clear();

	wstring Wood_file = L"Texture/Attack/Wood-Hammer.png";
	Texture* Wood_t = Texture::Add(Wood_file);

	this_frame_size = { 83.0f, 56.0f };
	init_pos = { 107, 488 };

	frames.push_back(new Frame(Wood_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 73.0f, 45.0f };
	init_pos = { 103, 123 };

	frames.push_back(new Frame(Wood_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 122.0f, 115.0f };
	init_pos = { 61, 0 };

	frames.push_back(new Frame(Wood_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 148.0f, 58.0f };
	init_pos = { 47, 182 };

	frames.push_back(new Frame(Wood_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 195.0f, 75.0f };
	init_pos = { 0, 346 };

	frames.push_back(new Frame(Wood_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	skill.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f)); // 3 우드해머
	frames.clear();

	wstring Surf_file = L"Texture/Attack/Surf-Regular.png";
	Texture* Surf_t = Texture::Add(Surf_file);

	this_frame_size = { 227.0f, 40.0f };
	init_pos = { 202, 513 };

	frames.push_back(new Frame(Surf_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 208.0f, 50.0f };
	init_pos = { 218, 445 };

	frames.push_back(new Frame(Surf_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 188.0f, 64.0f };
	init_pos = { 237, 376 };

	frames.push_back(new Frame(Surf_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 159.0f, 70.0f };
	init_pos = { 272, 301 };

	frames.push_back(new Frame(Surf_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 145.0f, 80.0f };
	init_pos = { 289, 214 };

	frames.push_back(new Frame(Surf_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 130.0f, 90.0f };
	init_pos = { 304, 111 };

	frames.push_back(new Frame(Surf_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 106.0f, 100.0f };
	init_pos = { 330, 0 };

	frames.push_back(new Frame(Surf_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	skill.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f)); // 4 파도타기
	frames.clear();

	wstring Dragon_file = L"Texture/Attack/Dragon-Claw.png";
	Texture* Dragon_t = Texture::Add(Dragon_file);

	this_frame_size = { 20.0f, 54.0f };
	init_pos = { 11, 110 };

	frames.push_back(new Frame(Dragon_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 28.0f, 62.0f };
	init_pos = { 11, 175 };

	frames.push_back(new Frame(Dragon_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 35.0f, 73.0f };
	init_pos = { 10, 250 };

	frames.push_back(new Frame(Dragon_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 41.0f, 87.0f };
	init_pos = { 12, 334 };

	frames.push_back(new Frame(Dragon_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 103.0f, 87.0f };
	init_pos = { 15, 434 };

	frames.push_back(new Frame(Dragon_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 87.0f };
	init_pos = { 17, 536 };

	frames.push_back(new Frame(Dragon_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 87.0f };
	init_pos = { 17, 631 };

	frames.push_back(new Frame(Dragon_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 104.0f, 87.0f };
	init_pos = { 17, 725 };

	frames.push_back(new Frame(Dragon_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	skill.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f)); // 5 드래곤클로
	frames.clear();

	wstring Face_file = L"Texture/Attack/Scary-Face-Reg.png";
	Texture* Face_t = Texture::Add(Face_file);

	this_frame_size = { 34.0f, 19.0f };
	init_pos = { 0, 23 };

	frames.push_back(new Frame(Face_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 68.0f, 40.0f };
	init_pos = { 120, 10 };

	frames.push_back(new Frame(Face_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 78.0f, 46.0f };
	init_pos = { 5, 71 };

	frames.push_back(new Frame(Face_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 73.0f, 55.0f };
	init_pos = { 103, 71 };

	frames.push_back(new Frame(Face_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 98.0f, 74.0f };
	init_pos = { 90, 137 };

	frames.push_back(new Frame(Face_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 106.0f, 80.0f };
	init_pos = { 42, 20 };

	frames.push_back(new Frame(Face_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	skill.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 3.0f)); // 6 
	frames.clear();
	
	for (auto i : is_active)
		i = false;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Skill::~Skill()
{
	for (auto s : skill)
		delete s;
	skill.clear();
	delete CB;
}

void Skill::Update(UINT slot)
{
	if (slot == 0)
	{
		is_active[0] = true;
		
		this->pos = Vector2(WIN_CENTER_X, 420);
		this->scale.x = skill[0]->GetFrameSize().x * 3.5f;
		this->scale.y = skill[0]->GetFrameSize().y * 1.5f;
		WorldUpdate();
		skill[0]->Update();
	}
	else if (slot == 1)
	{
		is_active[1] = true;

		this->pos = Vector2(WIN_CENTER_X / 2, 430);
		this->scale.x = skill[1]->GetFrameSize().x * 1.5f;
		this->scale.y = skill[1]->GetFrameSize().y * 1.5f;
		WorldUpdate();
		skill[1]->Update();
	}
	else if (slot == 2)
	{
		is_active[2] = true;

		this->pos = Vector2(WIN_CENTER_X / 2 - 25, 440);
		this->scale.x = skill[2]->GetFrameSize().x * 3.0f;
		this->scale.y = skill[2]->GetFrameSize().y * 3.0f;
		WorldUpdate();
		skill[2]->Update();
	}
	else if (slot == 3)
	{
		is_active[3] = true;

		this->pos.x = WIN_CENTER_X;
		this->pos.y = 420.0f;
		this->scale.x = skill[3]->GetFrameSize().x * 2.5f;
		this->scale.y = skill[3]->GetFrameSize().y * 2.5f;
		WorldUpdate();
		skill[3]->Update();
	}
	else if (slot == 4)
	{
		is_active[4] = true;

		this->pos = Vector2(WIN_CENTER_X / 2 - 25, 440);
		this->scale.x = skill[4]->GetFrameSize().x * 3.0f;
		this->scale.y = skill[4]->GetFrameSize().y * 3.0f;
		WorldUpdate();
		skill[4]->Update();
	}
	else if (slot == 5)
	{
		is_active[5] = true;

		this->pos = Vector2(WIN_CENTER_X + 345, 305);
		this->scale.x = skill[5]->GetFrameSize().x * 3.0f;
		this->scale.y = skill[5]->GetFrameSize().y * 3.0f;
		WorldUpdate();
		skill[5]->Update();
	}
}

void Skill::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	if (is_active[0])
		skill[0]->Render();
	if (is_active[1])
		skill[1]->Render();
	if (is_active[2])
		skill[2]->Render();
	if (is_active[3])
		skill[3]->Render();
	if (is_active[4])
		skill[4]->Render();
	if (is_active[5])
		skill[5]->Render();
		
}