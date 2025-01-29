#include "framework.h"

BattleField::BattleField(Vector2 pos, wstring file, float x, float y, float w, float h)
{
	field = new Frame(file, x, y, w, h);
	this->pos = pos;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

BattleField::~BattleField()
{
	delete field;
	delete CB;
}

void BattleField::Update()
{
	this->scale.x = field->GetFrameSize().x * 4.0f;
	this->scale.y = field->GetFrameSize().y * 2.8f;
	WorldUpdate();
}

void BattleField::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	field->Render();
}
