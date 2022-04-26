#ifndef INPUT_MAP_H
#define INPUT_MAP_H

#include<array>

enum class INPUT_STATE
{
	NOT_PRESSED = 0,
	PRESSED,
};

enum class KEY_ID
{
	KEY_FIRST = 0,
	KEY_ESC = KEY_FIRST,
	KEY_ENTER,
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_ARROW_UP,
	KEY_ARROW_DOWN,
	KEY_ARROW_LEFT,
	KEY_ARROW_RIGHT,
	KEY_LAST,
};

//typedef std::map<KEY_ID, INPUT_STATE> KeyStateMap;
typedef std::array<INPUT_STATE, static_cast<unsigned long int>(KEY_ID::KEY_LAST)> KeyStateArray;

#endif