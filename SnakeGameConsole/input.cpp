#include "input.h"
#include <iostream>

const int keyMap[6] = { VK_UP, VK_LEFT, VK_DOWN, VK_RIGHT, VK_RETURN, VK_ESCAPE };
bool keyPressed[6] = { false, false, false, false, false, false };
bool isClosed = false;
int leftClosed = 0;
std::queue<int> inputChannel::messageQueue;

using inputChannel::messageQueue;

inline bool inputChannel::hasMessages()
{
	return !messageQueue.empty();
}

inline bool keyIsOrWasPressed(int key)
{
	return GetAsyncKeyState(key) & 0b1000000000000001;
}

void clearFlags()
{
	for (int i = 0; i < 6; ++i)
		GetAsyncKeyState(keyMap[i]);
}

void readInputNotRepeated()
{
	for (int i = 0; i < 6; ++i)
		if (keyIsOrWasPressed(keyMap[i]))
		{
			if (!keyPressed[i])
				messageQueue.push(i);

			keyPressed[i] = true;
		}
		else
		{
			keyPressed[i] = false;
		}
}

int inputChannel::popMessage()
{
	int ret = messageQueue.front();
	messageQueue.pop();
	return ret;
};

bool inputChannel::findKey(int key)
{
	while (inputChannel::hasMessages())
		if (popMessage() == key)
			return true;
	return false;
}

void inputChannel::closeFor(int ticks)
{
	isClosed = true;
	leftClosed = ticks;
}

void inputChannel::processInput()
{
	if (isClosed)
	{
		clearFlags();
		isClosed = --leftClosed != 0;
	}
	else
		readInputNotRepeated();
}