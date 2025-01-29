#pragma once
class TextBox : public Transform
{
private:
	Frame* box;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	TextBox(Vector2 pos = Vector2(WIN_CENTER_X, 625));
	~TextBox();

	void Update();
	void Render();
};