#include "framework.h"

HPBar::HPBar(Vector2 pos)
{
	bar = new Frame(L"Texture/HPBar.png", 252, 208, 48, 7);
	this->pos = pos;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

HPBar::~HPBar()
{
	delete bar;
	delete CB;
}

void HPBar::Update()
{
	this->scale.x = bar->GetFrameSize().x / 2.25f;
	this->scale.y = bar->GetFrameSize().y * 2.0f;

	WorldUpdate();
}

void HPBar::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	bar->Render();
}
