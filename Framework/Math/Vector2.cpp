#include "framework.h"


Vector2::Vector2() : Float2(0, 0)
{
}

Vector2::Vector2(float x, float y) : Float2(x, y)
{
}

Vector2::Vector2(Float2 value) : Float2(value)
{
}

Vector2 Vector2::operator+(const Vector2& value) const
{
	return Vector2(x + value.x , y + value.y);
}

Vector2 Vector2::operator-(const Vector2& value) const
{
	return Vector2(x - value.x, y - value.y);
}

Vector2 Vector2::operator*(const Vector2& value) const
{
	return Vector2(x * value.x, y * value.y);
}

Vector2 Vector2::operator/(const Vector2& value) const
{
	return Vector2(x / value.x, y / value.y);
}

Vector2 Vector2::operator*(const float& value) const
{
    return Vector2(x * value, y * value);
}

Vector2 Vector2::operator/(const float& value) const
{
    return Vector2(x / value, y / value);
}

void Vector2::operator+=(const Vector2& value)
{
    x += value.x;
    y += value.y;
}

void Vector2::operator-=(const Vector2& value)
{
    x -= value.x;
    y -= value.y;
}

void Vector2::operator*=(const float& value)
{
    x *= value;
    y *= value;
}

void Vector2::operator/=(const float& value)
{
    x /= value;
    y /= value;
}


void Vector2::Normalize() 
{
    float length = GetLength(); 
    x /= length;
    y /= length;

}

Vector2 Vector2::Normalized() const
{
    float length = GetLength();
	return Vector2(x / length, y / length);
    
}

float Vector2::Angle() const 
{
	return atan2(y, x);
   
}

Vector2 Vector2::TransformCoord(const Vector2& vec, const Matrix& mt)

{
    XMVECTOR temp = XMLoadFloat2(&vec);
    temp = XMVector2TransformCoord(temp, mt);

    Vector2 temp_pos;
    XMStoreFloat2(&temp_pos, temp);

    return temp_pos;
}
