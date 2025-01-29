#pragma once
class RectCollider : public Collider
{
public:
	struct ObbDesc 
	{
		Vector2 pos; 
		Vector2 Axis[2]; 
		Vector2 half_size;
	};

private:
	Vector2 size;
	ObbDesc obb_desc;

	virtual void CreateLine() override;
	
	bool isAABB(RectCollider* rect, Vector2* overwrap = NULL);
	bool isOBB(RectCollider* rect);
	bool isAABB(CircleCollider* circle);
	bool isOBB(CircleCollider* Circle);

	float separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2);

public:
	RectCollider(Vector2 size);
	~RectCollider();

	ObbDesc GetObbDesc();

	virtual bool isPointCollision(Vector2 point) override;

	virtual bool isCircleCollision(CircleCollider* collider) override;

	virtual bool isRectCollision(RectCollider* collider, Vector2* overwrap = NULL) override;

	virtual bool isLineCollision(Vector2 line_start, Vector2 line_end) override;

	Vector2 Size() { return size * GlobalScale(); }
	float RightVX() { return GlobalPos().x + size.x * 0.5f; }
	float LeftVX() { return GlobalPos().x - size.x * 0.5f; }
	float UpVX() { return GlobalPos().y - size.y * 0.5f; }
	float DownVX() { return GlobalPos().y + size.y * 0.5f; }
};