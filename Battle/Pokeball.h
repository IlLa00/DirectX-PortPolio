#pragma once
class Pokeball : public Transform
{
private:
	vector<Clip*>pokeball;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	bool is_active;

public:
	Pokeball();
	~Pokeball();

	void SetPos(Vector2 pos) { this->pos = pos; }

	Vector2* GetPos() { return &(this->pos); }

	vector<Clip*> GetClips() { return pokeball; }

	void Update(UINT state);
	void Render();
};