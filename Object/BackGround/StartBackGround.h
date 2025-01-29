#pragma once

class StartBackGround : public Transform
{
private:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	vector<Clip*> clips;

public:
	StartBackGround();
	~StartBackGround();

	void Update();
	void Render();
};