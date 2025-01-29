#include "framework.h"

Collider::Collider()
{
	is_active = false;
	
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexPos.hlsl", 2);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelPos.hlsl");

	CB = new ColourBuffer();
	CB->data.colour = { 0, 1, 0, 1 };

	WB = new MatrixBuffer();
}

Collider::~Collider()
{
	delete CB;
	delete WB;
}

void Collider::Render()
{
	if (!is_active) return;

	WB->Set(world);
	WB->SetVS(0);
	CB->SetPS(0);

	VB->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	VS->Set();
	PS->Set();
	DVC->Draw(verticies.size(), 0);
}

bool Collider::isCollision(Collider* collider, Vector2* overwrap)
{
	if (!is_active || !(collider->is_active)) return false;

	switch (collider->type)
	{
	case TYPE::RECT:
		return isRectCollision((RectCollider*)collider, overwrap);

	case TYPE::CIRCLE:
		return isCircleCollision((CircleCollider*)collider);

	default:
		return false;
	}
}

bool Collider::isLineCrossCollision(Vector2 l1_start, Vector2 l1_end, 
	Vector2 l2_start, Vector2 l2_end)
{
	return false;
}
