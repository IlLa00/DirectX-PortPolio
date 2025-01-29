#pragma once

class Quad : public Transform
{
protected:
	vector<VertexUV> vertices = {};
	vector<UINT> indices = {}; 

	Vector2 size;

	VertexShader* VS;
	PixelShader* PS;

	VertexBuffer* VB;
	IndexBuffer* IB; 
	ColourBuffer* CB;
	MatrixBuffer* WB;

	Texture* texture; 

	void SetPixelShader(wstring file);

	void Create();
	
public:
	Quad(bool is_background, wstring file, Vector2 scale = Vector2(1, 1), Vector2 startUV = Vector2(0, 0), Vector2 EndUV = Vector2(1, 1));
	Quad(wstring file, Vector2 scale = Vector2(1, 1), Vector2 startUV = Vector2(0, 0), Vector2 EndUV = Vector2(1, 1));
	Quad(wstring file, float x, float y, float w, float h, Vector2 scale = Vector2(1, 1));
	virtual ~Quad();

	Vector2 Size() { return texture->GetSize() * scale; }
	void Render();

	void SetColor(Float4 color)
	{
		CB->data.colour = color;
	}
};