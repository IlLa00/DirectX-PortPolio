#include "framework.h"

BattleBackGround::BattleBackGround(wstring file, Vector2 size, Vector2 scale) 
{
	BG = new Frame(file, 15, 566, 256, 144);

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

BattleBackGround::~BattleBackGround()
{
	delete BG;
	delete CB;
}

void BattleBackGround::Update()
{
	this->scale = BG->GetFrameSize() * 10.0f;
	WorldUpdate();
}

void BattleBackGround::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	BG->Render();
}
