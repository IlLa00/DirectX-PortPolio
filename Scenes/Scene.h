#pragma once

class Scene
{
protected:
	GameState&    m_state;
	VertexShader* VS;
	PixelShader*  PS;

public:
	explicit Scene(GameState& state) : m_state(state), VS(nullptr), PS(nullptr) {}
	virtual ~Scene() = default;

	virtual void Update()     = 0;
	virtual void Render()     = 0;
	virtual void PostRender() = 0;

	virtual SceneID GetNextScene() const { return SceneID::None; }
	virtual void    OnEnter()            {}
	virtual void    OnExit()             {}
};