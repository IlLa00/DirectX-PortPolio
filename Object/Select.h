#pragma once
class Select : public Transform
{
private:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	RectCollider* boy_select_box;
	RectCollider* girl_select_box;

	vector<Clip*> clips;

public:
	Select(bool gender);
	~Select();

	RectCollider* GetBoybox() { return boy_select_box; }
	RectCollider* GetGirlbox() { return girl_select_box; }

	void Update();
	void Render();
};