#pragma once
class SelectBox : public Transform
{
private:
	Quad* image;
	Vector2 size;

public:
	SelectBox(wstring file, Vector2 pos = Vector2(WIN_CENTER_X, 640), Vector2 size = Vector2(1, 1),
		Vector2 scale = Vector2(1, 1), float angle = 0.0f, Matrix* parent = NULL);
	~SelectBox();

	void Update();
	void Render();
};