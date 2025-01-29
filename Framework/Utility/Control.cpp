#include "framework.h"
#include "Control.h"

Control::Control()
	: cur_state{}, old_state{}, map_state{}

{
}

Control::~Control()
{
}

void Control::Update()
{
	memcpy(old_state, cur_state, sizeof(old_state));
	GetKeyboardState(cur_state);


	for (int i = 0; i < KEY_MAX; i++)
	{
		BYTE key = cur_state[i] & 0x80;

		cur_state[i] = key ? 1 : 0;
		

		BYTE old = old_state[i];
		BYTE cur = cur_state[i];


		if (old == 0 && cur == 1) 
		{
			map_state[i] = DOWN;
		}
		else if (old == 1 && cur == 1) 
		{
			map_state[i] = PRESS;
		}
		else if (old == 1 && cur == 0) 
		{
			map_state[i] = UP;
		}
		else 
		{
			map_state[i] = NONE;
		}

	}

}
