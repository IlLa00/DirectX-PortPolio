#include "framework.h"

Pokemon::Pokemon(Vector2 pos, float x, float y, float w, float h, float attack, wstring file)
{
	pokemon = new Frame(file, x, y, w, h);
	this->pos = pos;
	this->hp = 100.0f;
	this->attack = attack;

	is_survive = true;
	is_active = true;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Pokemon::~Pokemon()
{
	delete pokemon;
	delete CB;
}

void Pokemon::Attack(Pokemon* enemy)
{
	if (is_active)
	{
		enemy->hp -= this->attack;
		if (enemy->hp <= 0)
			enemy->hp = 0.0f;
	}
}

void Pokemon::Recovery()
{
	if (is_active)
	{
		if (this->hp <= 50.0f)
			this->hp += 50.0f;
		else
			this->hp = 100.0f;
	}
		
}

void Pokemon::Change()
{

}

void Pokemon::Collapses() 
{
	if (this->pos.x < WIN_CENTER_X)
		this->pos.x -= 300.0f * DELTA;
	if (this->pos.x > WIN_CENTER_X)
		this->pos.x += 300.0f * DELTA;
}

void Pokemon::Update()
{
	if (is_active)
	{
		this->scale = pokemon->GetFrameSize() * 3.0f;
		WorldUpdate();
	}
}

void Pokemon::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	if(is_active)
		pokemon->Render();
}