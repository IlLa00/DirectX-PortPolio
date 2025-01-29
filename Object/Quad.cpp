#include "Framework.h"

void Quad::SetPixelShader(wstring file)
{
	PixelShader::GetInstance(file);
}


Quad::Quad(bool is_background, wstring file, Vector2 scale, Vector2 startUV, Vector2 EndUV) : Transform()
{
	this->scale = scale;
	texture = Texture::Add(file);

	Vector2 size = texture->GetSize();
	Vector2 half_size = size * 0.5f;

	float left = -half_size.x;
	float right = half_size.x;
	float top = -half_size.y;
	float bottom = half_size.y;

	vertices.emplace_back(left, top, startUV.x, startUV.y);
	vertices.emplace_back(right, top, EndUV.x, startUV.y);
	vertices.emplace_back(left, bottom, startUV.x, EndUV.y);
	vertices.emplace_back(right, bottom, EndUV.x, EndUV.y);

	indices = { 0, 1, 2, 3, 2, 1 };

	Create();
}

Quad::Quad(wstring file, Vector2 scale, Vector2 startUV, Vector2 EndUV) // 배경화면
{
	texture = Texture::Add(file);

	Vector2 size = texture->GetSize();

	vertices.emplace_back(0, 0, startUV.x, startUV.y);
	vertices.emplace_back(1280, 0, EndUV.x, startUV.y);
	vertices.emplace_back(0, 720, startUV.x, EndUV.y);
	vertices.emplace_back(1280, 720, EndUV.x, EndUV.y);

	indices = { 0, 1, 2, 3, 2, 1 };

	Create();

}

Quad::Quad(wstring file, float x, float y, float w, float h, Vector2 scale)
{
	texture = Texture::Add(file);

	Vector2 size = texture->GetSize();
	Vector2 half_size = size * 0.5f;

	float left = -half_size.x;
	float right = half_size.x;
	float top = -half_size.y;
	float bottom = half_size.y;

	Vector2 cut_start = Vector2(x, y) / size;
	Vector2 cut_size = Vector2(w, h) / size;
	Vector2 cut_end = cut_start + cut_size;

	vertices.emplace_back(left, top, cut_start.x, cut_start.y);
	vertices.emplace_back(right, top, cut_end.x, cut_start.y);
	vertices.emplace_back(left, bottom, cut_start.x, cut_end.y);
	vertices.emplace_back(right, bottom, cut_end.x, cut_end.y);

	indices = { 0, 1, 2, 2, 1, 3 };

	Create();
}



Quad::~Quad()
{
	delete VB;
	delete IB;
	delete CB;
	delete WB;
}

void Quad::Render()
{
	WB->Set(world);
	WB->SetVS(0);
	CB->SetPS(0);

	VB->Set();
	IB->Set();

	texture->Set();

	VS->Set();
	PS->Set();

	DVC->DrawIndexed(indices.size(), 0, 0);
}

void Quad::Create()
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");

	VB = new VertexBuffer(vertices.data(), sizeof(VertexUV), vertices.size());
	IB = new IndexBuffer(indices.data(), indices.size());

	CB = new ColourBuffer();
	WB = new MatrixBuffer();
}
