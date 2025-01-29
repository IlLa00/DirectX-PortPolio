#pragma once

class InGameEnemy : public Transform
{
private:
	Frame* enemy;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	InGameEnemy(Vector2 pos, wstring file, float x, float y, float w, float h);
	~InGameEnemy();

	void Update();
	void Render();

};