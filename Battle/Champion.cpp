#include "framework.h"

Champion::Champion(Vector2 pos)
{
	champion = new Frame(L"Texture/vsChampion.png", 325, 900, 80, 80);
	this->pos = pos;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Champion::~Champion()
{
	delete champion;
	delete CB;
}

void Champion::Update()
{
	this->scale = champion->GetFrameSize() * 3.0f;
	WorldUpdate();
}

void Champion::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	champion->Render();
}
