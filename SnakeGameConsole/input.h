#pragma once
#include <windows.h>
#include <queue>
//enum Key 
//{
//	up = VK_UP,
//	left = VK_LEFT,
//	down = VK_DOWN,
//	right = VK_RIGHT,
//	enter = VK_RETURN,
//	escape = VK_ESCAPE
//};

enum Key { up, left, down, right, enter, escape };

namespace inputChannel
{
	extern std::queue<int> messageQueue;
	bool findKey(int key);
	void closeFor(int ticks);
	void processInput();
	int popMessage();
	bool hasMessages();
}

//extern bool theBool;