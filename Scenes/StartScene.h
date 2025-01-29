#pragma once
class StartScene : public Scene
{
private:
	StartBackGround* SBG;

public:
	StartScene();
	~StartScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};