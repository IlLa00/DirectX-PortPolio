#include "framework.h"

TextBox::TextBox(Vector2 pos)
{
	box = new Frame(L"Texture/Text Boxes.png", 1, 1, 250, 44);
	this->pos = pos;

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

TextBox::~TextBox()
{
	delete box;
	delete CB;
}

void TextBox::Update()
{
	this->scale.x = box->GetFrameSize().x * 5.0f;
	this->scale.y = box->GetFrameSize().y * 4.0f;

	WorldUpdate();
}

void TextBox::Render()
{
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	box->Render();
}
