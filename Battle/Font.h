#pragma once
class Font : public Transform
{
private:
	vector<vector<TextFrame*>> player_name_box;
	vector<vector<TextFrame*>> enemy_name_box;
	vector<vector<TextFrame*>> player_level_box;
	vector<vector<TextFrame*>> enemy_level_box;
	vector<vector<TextFrame*>> player_max_hp_box;
	vector<TextFrame*> player_current_hp;
	vector<TextFrame*> font_box;

	wstring name;
	wstring file;

	float hp;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;
public:
	Font(wstring name, wstring file = L"Texture/StatusBox.png");
	~Font();

	void SetHP(float hp);

	void Update(UINT slot);
	void Render(UINT slot);
};