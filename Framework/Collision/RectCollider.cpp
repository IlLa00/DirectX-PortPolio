#include "framework.h"
#include "RectCollider.h"

bool RectCollider::isPointCollision(Vector2 point)
{
    Vector2 half = Size() * 0.5f;

    float left = GlobalPos().x - half.x;
    float right = GlobalPos().x + half.x;
    float top = GlobalPos().y - half.y;
    float bottom = GlobalPos().y + half.y;

    if (point.x > left && point.x < right)
        if (point.y > top && point.y < bottom)
            return true; 

    return false; 
}

bool RectCollider::isCircleCollision(CircleCollider* collider)
{
    return isOBB(collider);
}

bool RectCollider::isRectCollision(RectCollider* collider, Vector2* overwrap)
{
    if (overwrap != NULL)
        return isAABB(collider, overwrap);
    else
        return isOBB(collider);

}

bool RectCollider::isLineCollision(Vector2 line_start, Vector2 line_end)
{
    return false;
}

void RectCollider::CreateLine()
{
    Vector2 half = size * 0.5f;

    verticies.emplace_back(-half.x, +half.y);
    verticies.emplace_back(+half.x, +half.y);
    verticies.emplace_back(+half.x, -half.y);
    verticies.emplace_back(-half.x, -half.y);
    verticies.emplace_back(-half.x, +half.y);

    VB = new VertexBuffer(verticies.data(), sizeof(VertexPos), verticies.size());
}

bool RectCollider::isAABB(RectCollider* rect, Vector2* overwrap)
{
    float min_right = min(RightVX(), rect->RightVX());
    float max_left = max(LeftVX(), rect->LeftVX());

    float min_down = min(DownVX(), rect->DownVX());
    float max_up = max(UpVX(), rect->UpVX());

    Vector2 obstackle = Vector2(min_right - max_left, min_down - max_up);

    if (obstackle.x > 0 && obstackle.y > 0)
    {
        if (overwrap != NULL)
            *overwrap = obstackle; 
        return true;
    }
    else
        return false;
}

bool RectCollider::isOBB(RectCollider* rect)
{
    ObbDesc this_obb = GetObbDesc();
    ObbDesc rect_obb = rect->GetObbDesc();

    Vector2 nea1 = this_obb.Axis[0];
    Vector2 nea2 = this_obb.Axis[1];
    Vector2 ea1 = nea1 * this_obb.half_size.x;
    Vector2 ea2 = nea2 * this_obb.half_size.y;
    Vector2 neb1 = rect_obb.Axis[0];
    Vector2 neb2 = rect_obb.Axis[1];
    Vector2 eb1 = neb1 * rect_obb.half_size.x;
    Vector2 eb2 = neb2 * rect_obb.half_size.y;
    Vector2 distance = this_obb.pos - rect_obb.pos;

    float lengthA = ea1.GetLength();
    float lengthB = separateAxis(nea1, eb1, eb2);
    float length = abs(Vector2::Dot(distance, nea1));

    if (length > lengthA + lengthB)
        return false; 

    lengthA = ea2.GetLength();
    lengthB = separateAxis(nea2, eb1, eb2);
    length = abs(Vector2::Dot(distance, nea2));

    if (length > lengthA + lengthB)
        return false;

    lengthA = eb1.GetLength();
    lengthB = separateAxis(neb1, ea1, ea2);

    length = abs(Vector2::Dot(distance, neb1));

    if (length > lengthA + lengthB)
        return false;

    lengthA = eb2.GetLength();
    lengthB = separateAxis(neb2, ea1, ea2);

    length = abs(Vector2::Dot(distance, neb2));

    if (length > lengthA + lengthB)
        return false;

    return true; 
}

bool RectCollider::isAABB(CircleCollider* circle)
{
    return circle->isRectCollision(this);
}

bool RectCollider::isOBB(CircleCollider* Circle)
{
    return Circle->isRectCollision(this);
}

float RectCollider::separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2)
{
    float r1 = abs(Vector2::Dot(seperate, e1));
    float r2 = abs(Vector2::Dot(seperate, e2));

    return r1 + r2;
}

RectCollider::RectCollider(Vector2 size)
    : size(size)
{
    type = TYPE::RECT;

    CreateLine();
}

RectCollider::~RectCollider()
{
    delete VB;
}

RectCollider::ObbDesc RectCollider::GetObbDesc()
{
    obb_desc.pos = GlobalPos(); 
    obb_desc.half_size = Size() * 0.5f;
    obb_desc.Axis[0] = Right(); 
    obb_desc.Axis[1] = Up();

    return obb_desc;
}
