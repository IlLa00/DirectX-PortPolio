#pragma once

class Pokemon : public Transform
{
private:
	Frame* pokemon;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	float hp;
	float attack;

	bool is_survive;

public:
	Pokemon(Vector2 pos, float x, float y, float w, float h, float attack = 50.0f, wstring file = L"Texture/Pokemon.png");
	~Pokemon();

	bool is_active;

	float GetHP() { return this->hp; }
	bool GetIsSurvive() { return this->is_survive; }

	void SetIsSurvive(bool state) { is_survive = state; }

	void Attack(Pokemon* enemy);
	void Recovery();
	void Change();
	void Collapses();
	
	void Update();
	void Render();
};