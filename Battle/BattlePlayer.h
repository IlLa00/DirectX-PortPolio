#pragma once
class BattlePlayer : public Transform
{
private:
	vector<Clip*> clips;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	bool is_gender;

	void CreateClip(bool gender);

public:
	BattlePlayer(Vector2 pos, bool gender);
	~BattlePlayer();

	bool is_active[2];

	vector<Clip*> GetClips() { return clips; }

	void SetGender(bool gender);
	void Update(UINT slot);
	void Render();
};