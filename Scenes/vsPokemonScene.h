#pragma once

class vsPokemonScene : public Scene
{
private:
	unique_ptr<BackGround> BG;
	unique_ptr<BattleField> field[2];
	unique_ptr<BattleManager> manager;

public:
	explicit vsPokemonScene(GameState& state);
	~vsPokemonScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	SceneID GetNextScene() const override {
		return m_state.clear_vsPokemon ? SceneID::Town : SceneID::None;
	}
	void OnEnter() override;
};