#pragma once

class BattleBackGround : public Transform
{
private:
	Frame* BG;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	BattleBackGround(wstring file, Vector2 size = Vector2(WIN_WIDTH, WIN_HEIGHT), Vector2 scale = Vector2(1, 1));
	~BattleBackGround();

	void Update();
	void Render();
};