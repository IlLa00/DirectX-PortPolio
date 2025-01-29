#pragma once
class Appearance : public Transform
{
private:
	vector<Clip*>appearance;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	bool is_active[4];

public:
	Appearance();
	~Appearance();

	vector<Clip*> GetClips() { return appearance; }

	void Update(UINT slot);
	void Render();
};