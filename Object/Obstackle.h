#pragma once

class Obstackle : public Transform
{
private:
	RectCollider* collider;

public:
	Obstackle(Vector2 pos, Vector2 size, Vector2 scale, float angle, Matrix* parent = NULL);
	~Obstackle();

	RectCollider* GetCollider() { return collider; }

	void Update();
	void Render();

};