#pragma once

enum class ButtonAction { None, Attack, Recovery, Change };

class SelectButton : public UIElement
{
private:
	vector<RectCollider*> button_list;
	vector<vector<TextFrame*>> text_list;
	TextBox* image;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	SelectButton();
	~SelectButton();

	RectCollider* GetAttackButton()     { return button_list[0]; }
	RectCollider* GetMeditationButton() { return button_list[1]; }
	RectCollider* GetChangeButton()     { return button_list[2]; }

	ButtonAction GetClickedAction(Vector2 clickPos) const;

	void Update();
	void Render();
};