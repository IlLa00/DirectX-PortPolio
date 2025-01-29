#pragma once

class TextFrame : public Transform
{
private:
	vector<VertexUV> vertices;
	vector<UINT> indices;

	VertexBuffer* VB;
	IndexBuffer* IB;

	Texture* texture;

	Vector2 frame_size;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	TextFrame(wstring file, float x, float y, float w, float h);
	~TextFrame();

	void Render();

	Vector2 Size() { return texture->GetSize(); }
	Vector2 GetFrameSize() { return frame_size; }
};