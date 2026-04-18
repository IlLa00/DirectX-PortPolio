#pragma once
class CharactorSelectScene : public Scene
{
private:
	unique_ptr<BackGround> BG;
	unique_ptr<SelectBox> Selectbox;
	unique_ptr<Select> boy;
	unique_ptr<Select> girl;
	bool m_selected = false;

public:
	explicit CharactorSelectScene(GameState& state);
	~CharactorSelectScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	SceneID GetNextScene() const override {
		return m_selected ? SceneID::Town : SceneID::None;
	}
	void OnEnter() override { m_selected = false; }
};