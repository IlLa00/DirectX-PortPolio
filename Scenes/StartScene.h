#pragma once
class StartScene : public Scene
{
private:
	unique_ptr<StartBackGround> SBG;

public:
	explicit StartScene(GameState& state);
	~StartScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	SceneID GetNextScene() const override {
		return KEY_CON->Down(VK_SPACE) ? SceneID::CharacterSelect : SceneID::None;
	}
};