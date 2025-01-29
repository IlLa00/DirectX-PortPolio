#pragma once
class BackGround : public Transform
{
private:
	Quad* image;
	Vector2 size;

public:
	BackGround(wstring file, Vector2 pos = Vector2(0, 0), Vector2 size = Vector2(1, 1),
		Vector2 scale = Vector2(1, 1), float angle = 0.0f, Matrix* parent = NULL);
	~BackGround();

	void Update();
	void Render();

};