#pragma once

class Scene
{
protected:
	VertexShader* VS;
	PixelShader* PS;

public:
	virtual ~Scene() {};
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
};