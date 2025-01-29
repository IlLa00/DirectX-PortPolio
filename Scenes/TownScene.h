#pragma once
class TownScene : public Scene
{
private:
	BackGround* BG[2];

	vector<Obstackle*> obstackle_list;
	vector<vector<Obstackle*>> stage_obstackle;

	Player* player;

	RectCollider* next_stage[2];
	RectCollider* battle_stage[2];

	InGameEnemy* pokemon;
	InGameEnemy* champion;

	UINT now_stage;

public:
	TownScene();
	~TownScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void ChangeStage(UINT stage);
};