#pragma once

class Champion : public Transform
{
private:
	Frame* champion;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	Champion(Vector2 pos = Vector2(WIN_CENTER_X + 350, WIN_CENTER_Y - 125));
	~Champion();

	void Update();
	void Render();

};