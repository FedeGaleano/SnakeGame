#pragma once

#include "rendering.h"

static const char * titleBuffer =
"XXXX X  X XXXX X  X XXXX"
"X    X  X X  X X X  X   "
"XXXX XX X XXXX XX   XXXX"
"   X X XX X  X X X  X   "
"XXXX X  X X  X X  X XXXX";

static const char * underlineBuffer =
"XXXXXXXXXXXXXXXXXXXXXXXX";

static const char * gameOverBuffer =
" XXX   XXX  X   X XXXXX    XXX  X   X XXXXX XXXX "
"X     X   X XX XX X       X   X X   X X     X   X"
"XXXXX XXXXX X X X XXXXX   X   X X   X XXXXX XXXX "
"X   X X   X X   X X       X   X  X X  X     X   X"
" XXX  X   X X   X XXXXX    XXX    X   XXXXX X   X";

static const char * surroundingFrameBuffer =
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

namespace charmaps
{
	static const CharMap title(titleBuffer, 24);
	static const CharMap underline(underlineBuffer, 24);
	static const CharMap gameOverTitle(gameOverBuffer, 49);
	static const CharMap surroundingFrame(surroundingFrameBuffer, 49);
}