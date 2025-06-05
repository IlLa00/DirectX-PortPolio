#include "framework.h"
#include "Frame.h"

Frame::Frame(wstring file, Vector2 startUV, Vector2 endUV)
{
	texture = Texture::Add(file);

	Vector2 size = texture->GetSize(); 

	Vector2 half_size = size * 0.5f; 

	float left = -half_size.x;
	float right = half_size.x;
	float top = -half_size.y;
	float bottom = half_size.y;

	vertices.emplace_back(left, top, startUV.x, startUV.y);
	vertices.emplace_back(right, top, endUV.x, startUV.y);
	vertices.emplace_back(left, bottom, startUV.x, endUV.y);
	vertices.emplace_back(right, bottom, endUV.x, endUV.y);

	indices = { 0, 1, 2, 2, 1, 3 };

	VB = new VertexBuffer(vertices.data(), sizeof(VertexUV), vertices.size());
	IB = new IndexBuffer(indices.data(), indices.size());

	frame_size = endUV - startUV;
}

Frame::Frame(wstring file, float x, float y, float w, float h)
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

	vertices.emplace_back(left, top, cut_start.x, cut_start.y );
	vertices.emplace_back(right, top, cut_end.x, cut_start.y );
	vertices.emplace_back(left, bottom, cut_start.x, cut_end.y );
	vertices.emplace_back(right, bottom, cut_end.x, cut_end.y);

	indices = { 0, 1, 2, 2, 1, 3 };

	VB = new VertexBuffer(vertices.data(), sizeof(VertexUV), vertices.size());
	IB = new IndexBuffer(indices.data(), indices.size());

	frame_size = Vector2(w / texture->GetSize().x, h / texture->GetSize().y);
}

Frame::~Frame()
{
	delete VB;
	delete IB;
}

void Frame::Render()
{
	VB->Set();
	IB->Set();
	texture->Set();

	DVC->DrawIndexed(indices.size(), 0, 0);
}
