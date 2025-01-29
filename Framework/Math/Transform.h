#pragma once
class Transform
{
protected: 
	Matrix world;


	MatrixBuffer* WB; 

	Vector2 pivot;
	

	Matrix* parent; 

	Matrix S, R, T, P, IP; 

	XMFLOAT4X4 mat_world;
	Vector2 global_scale;
	
	Vector2 right;
	Vector2 up;

public:
	bool is_active;

	Vector2 pos; 
	Vector2 scale; 
	Float3 rot;

	Transform(Vector2 p = Vector2(0, 0), Vector2 s = Vector2(1, 1), float a = 0,
			Matrix* parent = NULL);
	~Transform();

	float GetAngle() { return rot.z; } 
	void SetAngle(float a) { rot.z = a; }

	void SetActive(bool active) { is_active = active; }
	bool GetActive() { return is_active; }
	
	void SetParent(Matrix* parent) { this->parent = parent; }
	
	void WorldUpdate();
	
	Matrix* GetWorld() { return &world; };

	Vector2 GlobalPos() 
	{
		return Vector2(mat_world._41, mat_world._42);
	}
	Vector2 GlobalScale() 
	{
		return global_scale;
	}

	Vector2 Right() { return right.Normalized(); }
	Vector2	Left() { return right.Normalized() * -1.0f; }
	Vector2 Up() { return up.Normalized(); }
	Vector2 Down() { return up.Normalized() * -1.0f; }

};

