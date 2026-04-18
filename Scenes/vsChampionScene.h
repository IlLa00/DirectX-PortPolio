#pragma once

class vsChampionScene : public Scene
{
private:
	unique_ptr<BackGround> BG;
	unique_ptr<BattleField> field[2];
	unique_ptr<BattleManager> manager;

public:
	explicit vsChampionScene(GameState& state);
	~vsChampionScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	SceneID GetNextScene() const override {
		return m_state.clear_vsChampion ? SceneID::Town : SceneID::None;
	}
	void OnEnter() override;
};