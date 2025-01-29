#pragma once

class vsPokemonScene : public Scene
{
private:
	BackGround* BG;
	BattleField* field[2];
	BattleManager* manager;

public:
	vsPokemonScene();
	~vsPokemonScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};