#include "framework.h"

void CircleCollider::CreateLine()
{
	float angle = 2 * M_PI;
	for (int i = 0; i <= vertex_count; i++)
	{
		verticies.emplace_back(cos(angle) * radius, sin(angle) * radius);
		angle -= 2 * M_PI / vertex_count;
	}

	VB = new VertexBuffer(verticies.data(), sizeof(VertexPos), verticies.size());
}

bool CircleCollider::isAABB(RectCollider* collider)
{
	Vector2 half = collider->Size() * 0.5f;
	Vector2 closest; 

	if (pos.x < collider->pos.x - half.x) 
		closest.x = collider->pos.x - half.x;
	else if (pos.x > collider->pos.x + half.x) 
		closest.x = collider->pos.x + half.x;
	else
		closest.x = pos.x;

	if (pos.y < collider->pos.y - half.y)
		closest.y = collider->pos.y - half.y;
	else if (pos.y > collider->pos.y + half.y)
		closest.y = collider->pos.y + half.y;
	else
		closest.y = pos.y;

	if (isPointCollision(closest))
		return true;
	else
		return false;
}

bool CircleCollider::isOBB(RectCollider* collider)
{
	Matrix T = XMMatrixTranslation(pos.x - collider->pos.x, pos.y - collider->pos.y, 0.0f);
	Matrix circle_world = S * R * T;

	circle_world *= XMMatrixRotationZ(-collider->rot.z);
	
	XMFLOAT4X4 temp_matrix;
	XMStoreFloat4x4(&temp_matrix, circle_world);
	Vector2 circle_obb_center = Vector2(temp_matrix._41, temp_matrix._42);
	Vector2 half = collider->Size() * 0.5f;
	Vector2 closest; 

	if (circle_obb_center.x < - half.x) 
		closest.x = - half.x;
	else if (circle_obb_center.x > + half.x) 
		closest.x = + half.x;
	else
		closest.x = circle_obb_center.x;

	if (circle_obb_center.y < - half.y)
		closest.y = - half.y;
	else if (circle_obb_center.y > + half.y)
		closest.y = + half.y;
	else
		closest.y = circle_obb_center.y;

	if ((circle_obb_center - closest).GetLength() < GetRadius())
		return true;
	else
		return false;
}

CircleCollider::CircleCollider(float rad)
	: radius(rad)
{
	type = TYPE::CIRCLE;
	vertex_count = 50;
	CreateLine();
}

CircleCollider::~CircleCollider()
{
	delete VB;
}

bool CircleCollider::isPointCollision(Vector2 point)
{
	Vector2 dir = pos - point;

	if (dir.GetLength() < radius)
		return true;
	else
		return false;
}
bool CircleCollider::isCircleCollision(CircleCollider* collider)
{
	Vector2 dir = pos - collider->pos;

	if (dir.GetLength() < radius + collider->GetRadius())
		return true;
	else
		return false;
}

bool CircleCollider::isRectCollision(RectCollider* collider, Vector2* overwrap)
{
	return isOBB(collider);
}

bool CircleCollider::isLineCollision(Vector2 line_start, Vector2 line_end)
{
    return false;
}
