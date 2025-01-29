#pragma once
class CircleCollider : public Collider
{
private:
	float radius;
	UINT vertex_count;

	virtual void CreateLine() override;

	bool isAABB(RectCollider* collider);
	bool isOBB(RectCollider* collider);

public:
	CircleCollider(float rad);
	~CircleCollider();


	float GetRadius() 
	{
		return radius * min(GlobalScale().x, GlobalScale().y);
	}

	virtual bool isPointCollision(Vector2 point) override;
	virtual bool isCircleCollision(CircleCollider* collider) override;
	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;
	virtual bool isLineCollision(Vector2 line_start, Vector2 line_end) override;
};