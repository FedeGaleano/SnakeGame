#pragma once

enum State
{
	BEGINNING_ANIMATION,
	PRESS_START,
	PLAYING,
	SECRET,
	GAME_OVER
};

class Screen
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
protected:
	void reactToKeys();
	virtual void KeyUp();
	virtual void KeyLeft();
	virtual void KeyDown();
	virtual void KeyRight();
	virtual void KeyEnter();
	virtual void KeyEscape();
};

class BeginningAnimationScreen : public Screen
{
public:
	void render() override;
	void update() override;
protected:
	void KeyEnter() override;
};

class PressStartScreen : public Screen
{
public:
	void render() override;
	void update() override;
	static void initialState();
protected:
	void KeyEnter() override;
	void KeyUp() override;
	void KeyDown() override;
};

class PlayingScreen : public Screen
{
public:
	void render() override;
	void update() override;
	static void initialState();
protected:
	void KeyUp() override;
	void KeyLeft() override;
	void KeyDown() override;
	void KeyRight() override;
};

class GameOverScreen : public Screen
{
public:
	void render() override;
	void update() override;
	static void prepareScoreRendering();
protected:
	void KeyEnter() override;
	void KeyEscape() override;
};

class SecretScreen : public Screen
{
public:
	void render() override;
	void update() override;
	static void init();
protected:
	void KeyUp() override;
	void KeyLeft() override;
	void KeyDown() override;
	void KeyRight() override;
};
