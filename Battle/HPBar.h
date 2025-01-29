#pragma once
class HPBar : public Transform
{
private:
	Frame* bar;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	HPBar(Vector2 pos);
	~HPBar();

	void Update();
	void Render();
};