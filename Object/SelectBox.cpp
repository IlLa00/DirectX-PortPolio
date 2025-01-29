#include "framework.h"

SelectBox::SelectBox(wstring file, Vector2 pos, Vector2 size, Vector2 scale, float angle, Matrix* parent)
{
	image = new Quad(false, file); // 배경화면 전용 Quad가 아님
	image->pos = pos;
	this->size = image->Size();
	image->scale.x = this->size.x / image->Size().x;
	image->scale.y = (this->size.y / image->Size().y) / 1.25f;
}

SelectBox::~SelectBox()
{
	delete image;
}

void SelectBox::Update()
{
	this->pos = image->pos;
	image->WorldUpdate();
}

void SelectBox::Render()
{
	image->Render();
}
