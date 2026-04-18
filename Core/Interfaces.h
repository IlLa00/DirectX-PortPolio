#pragma once

class IUpdatable
{
public:
	virtual ~IUpdatable() = default;
	virtual void Update() = 0;
};

class IRenderable
{
public:
	virtual ~IRenderable() = default;
	virtual void Render() = 0;
};

class IGameObject : public IUpdatable, public IRenderable {};
