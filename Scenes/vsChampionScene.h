#pragma once

class vsChampionScene : public Scene
{
private:
	BackGround* BG;
	BattleField* field[2];
	BattleManager* manager;

public:
	vsChampionScene();
	~vsChampionScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};