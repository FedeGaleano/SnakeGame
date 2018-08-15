#include <iostream>
#include "Screen.h"
#include "rendering.h"
#include "charmasks.h"
#include "input.h"
#include "engine.h"
#include "game.h"
#include "utils.h"
#include "gameplay.h"

Color color = Color::GRAY, scoreTextColor = Color::YELLOW;
bool beaten = false;

const wchar_t * scoreText, * hiScoreText, * bottomText;
int x_gameOver = 21;
int x_score, x_bottomText, x_hiScore;

void GameOverScreen::prepareScoreRendering()
{
	if (score > highestScore)
	{
		highestScore = score;
		beaten = true;
	}

	static std::wstring s_score, s_hiScore, s_bottomText;
	s_score = L"SCORE: " + std::to_wstring(score);
	s_hiScore = L"HI-SCORE: " + std::to_wstring(highestScore);
	s_bottomText = L"PRESS ENTER TO RESTART, ESC TO CHANGE LEVEL";
	scoreText = s_score.c_str();
	hiScoreText = s_hiScore.c_str();
	bottomText = s_bottomText.c_str();
	x_score = int(x_gameOver + (charmasks::gameOverTitle.width - s_score.size()) / 2);
	x_bottomText = int(x_gameOver + (charmasks::gameOverTitle.width - s_bottomText.size()) / 2);
	x_hiScore = int(x_gameOver + (charmasks::gameOverTitle.width - s_hiScore.size()) / 2);
	scoreTextColor = beaten ? Color::GREEN : Color::YELLOW;
}

void GameOverScreen::KeyEnter()
{
	PlayingScreen::initialState();
	game::setScreen(PLAYING);
}

void GameOverScreen::KeyEscape()
{
	PressStartScreen::initialState();
	game::setScreen(PRESS_START);
}

void GameOverScreen::update()
{
	color = utils::switchValuesByTimeLapse(Color::GRAY, Color::YELLOW, 4);
	this->reactToKeys();
}

void GameOverScreen::render()
{
	rendering::renderSurroundingFrame(Color::RED);
	rendering::renderText(scoreText, { float(x_score), 10 }, scoreTextColor);
	rendering::renderCharMap(charmasks::gameOverTitle, { float(x_gameOver), 12 }, rendering::FULL_BLOCK, color);
	rendering::renderText(bottomText, { float(x_bottomText), 18 });
	if (beaten) rendering::renderText(L"(NEW) ", { float(x_hiScore - 6), 25 }, Color::GREEN);
	rendering::renderText(hiScoreText, { float(x_hiScore), 25 }, Color::GRAY);
}