#include "framework.h"

UIElement::UIElement() : pos(0, 0), scale(1, 1), is_active(true)
{
	wb = new MatrixBuffer();
}

UIElement::~UIElement()
{
	delete wb;
}

void UIElement::WorldUpdate()
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	Matrix T = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	wb->Set(S * T);
}
