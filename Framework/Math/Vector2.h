#pragma once

class Vector2 : public Float2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(Float2 value);

	
	Vector2 operator+ (const Vector2& value) const;
	Vector2 operator- (const Vector2& value) const;
	Vector2 operator* (const Vector2& value) const;
	Vector2 operator/ (const Vector2& value) const;

	Vector2 operator* (const float& value) const;
	Vector2 operator/ (const float& value) const;


	void  operator+= (const Vector2& value);
	void  operator-= (const Vector2& value);
	void  operator*= (const float& value);
	void  operator/= (const float& value);

	float GetLength() const
	{
		return sqrt(x * x + y * y);
	} 

	void Normalize(); 
	Vector2 Normalized() const;
	
	float Angle() const; 

	static float Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	static Vector2 TransformCoord(const Vector2& vec, const Matrix& mt);

};