#pragma once
#define KEY_MAX 255

class Control : public Singleton<Control>
{
private:
	friend class Singleton;

	enum {
		NONE,
		DOWN,
		UP,
		PRESS,
		MAX
	};


	BYTE cur_state[KEY_MAX]; 
	BYTE old_state[KEY_MAX]; 
	BYTE map_state[KEY_MAX]; 

	Control();
	~Control();

public:
	void Update();

	bool Down(UINT key) { return map_state[key] == DOWN; }
	bool Up(UINT key) { return map_state[key] == UP; }
	bool Press(UINT key) { return map_state[key] == PRESS; }
};
