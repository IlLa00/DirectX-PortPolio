#include "framework.h"

TextFrame::TextFrame(wstring file, float x, float y, float w, float h)
{
	texture = Texture::Add(file); // 파일 불러오기
	
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

	VB = new VertexBuffer(vertices.data(), sizeof(VertexUV), vertices.size());
	IB = new IndexBuffer(indices.data(), indices.size());

	frame_size = Vector2(w / texture->GetSize().x, h / texture->GetSize().y);

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

TextFrame::~TextFrame()
{
	delete VB;
	delete IB;
	delete CB;
}

void TextFrame::Render()
{

	WB->SetVS(0);
	CB->SetPS(0);
	VB->Set();
	IB->Set();
	texture->Set();

	VS->Set();
	PS->Set();


	DVC->DrawIndexed(indices.size(), 0, 0);
}
