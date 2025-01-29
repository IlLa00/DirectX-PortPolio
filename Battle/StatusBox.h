#pragma once
class StatusBox : public Transform
{
private:
	Frame* Box;

	Font* player_name;
	Font* enemy_name;

	Font* player_level;
	Font* enemy_level;

	Font* player_max_hp;
	Font* player_current_hp;

	vector<HPBar*> HPbar_list;

	bool position;
	UINT slot;
	float hp;

	bool status_active;
	bool player_status_active;
	bool enemy_status_active;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	StatusBox(bool position);
	~StatusBox();

	void SetStatus(UINT slot) { this->slot = slot; }
	void SetIsStatus(bool state) { status_active = state; }
	void SetCurrentHP(float hp) { player_current_hp->SetHP(hp); }
	void SetHPBar(float hp) { this->hp = hp; }

	void Render();
	void Update();
};