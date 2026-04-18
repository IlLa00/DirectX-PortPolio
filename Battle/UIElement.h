#pragma once

class UIElement
{
protected:
	MatrixBuffer* wb;
	void WorldUpdate();

public:
	Vector2 pos;
	Vector2 scale;
	bool    is_active;

	UIElement();
	virtual ~UIElement();

	void SetActive(bool active) { is_active = active; }
	bool GetActive() const      { return is_active; }
};
