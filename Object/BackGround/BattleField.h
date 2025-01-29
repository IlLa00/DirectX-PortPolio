#pragma once

class BattleField : public Transform
{
private:
	Frame* field;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	BattleField(Vector2 pos, wstring file, float x, float y, float w, float h);
	~BattleField();

	void Update();
	void Render();
};