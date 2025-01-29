#pragma once
class Collider : public Transform
{
public:
	enum class TYPE
	{
		RECT,
		CIRCLE
	};

protected:
	TYPE type; 

	VertexShader* VS;
	PixelShader* PS;

	VertexBuffer* VB;

	ColourBuffer* CB;
	MatrixBuffer* WB;

	vector<VertexPos> verticies;

public:
	Collider();
	virtual ~Collider();

	void Render();
	TYPE GetType() { return type; }

	virtual bool isCollision(Collider* collider, Vector2* overwrap = NULL);
	virtual bool isPointCollision(Vector2 point) = 0;
	virtual bool isCircleCollision(class CircleCollider* collider) = 0;
	virtual bool isRectCollision(class RectCollider* collider,
		Vector2* overwrap = NULL) = 0;
	virtual bool isLineCollision(Vector2 line_start, Vector2 line_end) = 0;

	static bool isLineCrossCollision(Vector2 l1_start, Vector2 l1_end,
		Vector2 l2_start, Vector2 l2_end);


	void SetColor(float r, float g, float b)
	{
		CB->data.colour = Float4(r, g, b, 0);
	}

protected:
	virtual void CreateLine() = 0;
};

