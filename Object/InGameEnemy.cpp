#include "framework.h"

InGameEnemy::InGameEnemy(Vector2 pos, wstring file, float x, float y, float w, float h)
{
	enemy = new Frame(file, x, y, w, h);
	this->pos = pos;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

InGameEnemy::~InGameEnemy()
{
	delete enemy;
	delete CB;
}

void InGameEnemy::Update()
{
	this->scale = enemy->GetFrameSize() * 1.5f;
	WorldUpdate();
}

void InGameEnemy::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	enemy->Render();
}
