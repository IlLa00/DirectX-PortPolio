#pragma once

class Skill : public Transform
{
private:
	vector<Clip*>skill;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	bool is_active[6];

public:
	Skill();
	~Skill();

	vector<Clip*> GetClips() { return skill; }

	void Update(UINT slot);
	void Render();
};