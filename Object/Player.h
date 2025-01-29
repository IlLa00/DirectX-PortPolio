#pragma once
class Player : public Transform
{
private:
	enum PLAYER_ACTIVE
	{
		DOWN_IDLE = 0, // 0
		DOWN_WALK, // 1
		RIGHT_IDLE, // 2
		RIGHT_WALK, // 3
		UP_IDLE, // 4
		UP_WALK, // 5
		LEFT_IDLE, // 6
		LEFT_WALK, // 7
	}action;

	RectCollider* collider;
	vector<Clip*> clips;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	bool is_collision;
	bool is_gender;

	void CreateClip(bool gender);

public:
	Player(Vector2 pos = Vector2(0, 0));
	~Player();

	void Update();
	void Render();

	RectCollider* GetCollider() { return collider; }

	void SetClip(PLAYER_ACTIVE stat);
	
	bool GetCollisionState() { return this->is_collision; }
	void SetCollisionState(bool state) { this->is_collision = state; }
	void OnCollision();

	void SetColor(Float4 color)
	{
		CB->data.colour = color;
	}

	void SetGender(bool gender);

};