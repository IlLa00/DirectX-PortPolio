#pragma once
class TownScene : public Scene
{
private:
	unique_ptr<BackGround> BG[2];

	vector<unique_ptr<Obstackle>> obstackle_list;
	vector<vector<unique_ptr<Obstackle>>> stage_obstackle;

	unique_ptr<Player> player;

	unique_ptr<RectCollider> next_stage[2];
	unique_ptr<RectCollider> battle_stage[2];

	unique_ptr<InGameEnemy> pokemon;
	unique_ptr<InGameEnemy> champion;

	UINT now_stage;

public:
	explicit TownScene(GameState& state);
	~TownScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void ChangeStage(UINT stage);

	SceneID GetNextScene() const override {
		if (m_state.is_vsPokemon)  return SceneID::VsPokemon;
		if (m_state.is_vsChampion) return SceneID::VsChampion;
		return SceneID::None;
	}
};