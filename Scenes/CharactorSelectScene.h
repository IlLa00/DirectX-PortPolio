#pragma once
class CharactorSelectScene : public Scene
{
private:
	BackGround* BG;
	SelectBox* Selectbox;
	Select* boy; 
	Select* girl;

public:
	CharactorSelectScene();
	~CharactorSelectScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};