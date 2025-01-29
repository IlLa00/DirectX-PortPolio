#include "framework.h"

StartBackGround::StartBackGround()
{
	wstring file = L"Texture/StartScene.png";
	Texture* t = Texture::Add(file);

	Vector2 this_frame_size = { 2560.0f, 1440.0f }; // 지금까지 해온 half_size와 연관?
	Vector2 init_pos = { 0, 0 };

	vector<Frame*> frames;

	frames.push_back(new Frame(file, init_pos.x, init_pos.y,
		this_frame_size.x, this_frame_size.y));
	frames.push_back(new Frame(file, init_pos.x, 720.0f,
		this_frame_size.x, this_frame_size.y));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 3.0f));

	frames.clear();
	
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

StartBackGround::~StartBackGround()
{
	delete clips[0];
	delete CB;
}

void StartBackGround::Update()
{
	scale = clips[0]->GetFrameSize();
	WorldUpdate();
	clips[0]->Update();
}
	

void StartBackGround::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[0]->Render();
}
