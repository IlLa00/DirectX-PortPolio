#pragma once
class Meditation : public Transform
{
private:
	vector<Clip*>meditation;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;
	
	bool is_active;

public:
	Meditation();
	~Meditation();

	vector<Clip*> GetClips() { return meditation; }

	void Update();
	void Render();
};