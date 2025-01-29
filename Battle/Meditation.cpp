#include "framework.h"

Meditation::Meditation()
{
	wstring meditation_file = L"Texture/Attack/Healing.png";
	Texture* meditation_t = Texture::Add(meditation_file);

	Vector2 this_frame_size = { 17.0f, 17.0f };
	Vector2 init_pos = { 140, 117 };
	vector<Frame*>frames;

	frames.push_back(new Frame(meditation_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 20.0f, 20.0f };
	init_pos = { 115, 111 };

	frames.push_back(new Frame(meditation_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 49.0f, 86.0f };
	init_pos = { 115, 48 };

	frames.push_back(new Frame(meditation_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	meditation.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 4.0f));
	frames.clear();

	is_active = false;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Meditation::~Meditation()
{
	for (auto m : meditation)
		delete m;
	meditation.clear();

	delete CB;
}

void Meditation::Update()
{
	is_active = true;
	this->pos = Vector2(WIN_CENTER_X / 2, 440);
	this->scale = meditation[0]->GetFrameSize() * 3.0f;
	WorldUpdate();

	meditation[0]->Update();
}

void Meditation::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	if(is_active)
		meditation[0]->Render();
}
