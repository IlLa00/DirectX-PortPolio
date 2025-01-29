#include "framework.h"

Obstackle::Obstackle(Vector2 pos, Vector2 size, Vector2 scale, float angle, Matrix* parent)
{
	this->pos = pos;

	collider = new RectCollider(size);
	collider->pos = pos;
	collider->is_active = true;
	collider->SetColor(0, 0, 0);
}

Obstackle::~Obstackle()
{
	delete collider;
}

void Obstackle::Update()
{
	collider->pos = pos;
	collider->WorldUpdate();
}

void Obstackle::Render()
{
	WB->SetVS(0);

	collider->Render();
}
