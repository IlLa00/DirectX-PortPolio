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
	bool is_active;

public:
	Pokemon(Vector2 pos, float x, float y, float w, float h, float attack = 50.0f, wstring file = L"Texture/Pokemon.png");
	~Pokemon();

	float GetHP()         const { return hp; }
	bool  GetIsSurvive()  const { return is_survive; }
	bool  IsActive()      const { return is_active; }

	void SetIsSurvive(bool state) { is_survive = state; }
	void SetActive(bool state)    { is_active = state; }
	void ResetPosition(Vector2 startPos);

	void Attack(Pokemon* enemy);
	void Recovery();
	void Change();
	void Collapses();
	
	void Update();
	void Render();
};