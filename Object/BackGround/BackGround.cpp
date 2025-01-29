#include "framework.h"

BackGround::BackGround(wstring file, Vector2 pos, Vector2 size, Vector2 scale, float angle, Matrix* parent)
{
	image = new Quad(file);
	image->pos = pos;
	this->size = image->Size();
	image->scale = this->size / image->Size();
}

BackGround::~BackGround()
{
	delete image;
}

void BackGround::Update()
{
	image->WorldUpdate();
}

void BackGround::Render()
{
	image->Render();
}
