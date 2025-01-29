#include "framework.h"

Pokeball::Pokeball() 
{
	wstring ball_file = L"Texture/PokeBall.png";
	Texture* ball_t = Texture::Add(ball_file);

	Vector2 this_frame_size = { 14.0f, 14.0f };
	Vector2 init_pos = { 51, 12 };
	vector<Frame*>frames;

	frames.push_back(new Frame(ball_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 14.0f, 14.0f };
	init_pos = { 67, 12 };

	frames.push_back(new Frame(ball_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 14.0f, 14.0f };
	init_pos = { 83, 12 };

	frames.push_back(new Frame(ball_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 14.0f, 14.0f };
	init_pos = { 99, 12 };

	frames.push_back(new Frame(ball_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 14.0f, 14.0f };
	init_pos = { 115, 12 };

	frames.push_back(new Frame(ball_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 16.0f, 12.0f };
	init_pos = { 131, 14 };

	frames.push_back(new Frame(ball_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	this_frame_size = { 14.0f, 23.0f };
	init_pos = { 149, 3 };

	frames.push_back(new Frame(ball_file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));

	pokeball.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 5.0f));
	frames.clear();

	is_active = false;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Pokeball::~Pokeball()
{
	for (auto p : pokeball)
		delete p;
	pokeball.clear();

	delete CB;
}

void Pokeball::Update(UINT state)
{
	is_active = true;

	if (state == 0)
		this->pos = Vector2(WIN_CENTER_X / 2, 500);
	else
		this->pos = Vector2(WIN_CENTER_X + 345, 315);

	this->scale = pokeball[0]->GetFrameSize() * 3.0f;
	WorldUpdate();

	pokeball[0]->Update();
}

void Pokeball::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	if (is_active)
		pokeball[0]->Render();
}
