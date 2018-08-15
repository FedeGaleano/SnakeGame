#include "charmasks.h"

const char * titleBuffer =
"XXXX X  X XXXX X  X XXXX"
"X    X  X X  X X X  X   "
"XXXX XX X XXXX XX   XXXX"
"   X X XX X  X X X  X   "
"XXXX X  X X  X X  X XXXX";

const char * underlineBuffer =
"XXXXXXXXXXXXXXXXXXXXXXXX";

const char * gameOverBuffer =
" XXX   XXX  X   X XXXXX    XXX  X   X XXXXX XXXX "
"X     X   X XX XX X       X   X X   X X     X   X"
"XXXXX XXXXX X X X XXXXX   X   X X   X XXXXX XXXX "
"X   X X   X X   X X       X   X  X X  X     X   X"
" XXX  X   X X   X XXXXX    XXX    X   XXXXX X   X";

const char * misteriousBuffer =
"XXXXX  XXX  X   X XXXXX   X XXXXX"
"  X   X   X X  X  X       X   X  "
"  X   XXXXX XXX   XXXXX   X   X  "
"  X   X   X X  X  X       X   X  "
"  X   X   X X   X XXXXX   X   X  ";

namespace charmasks
{
	const CharMask title(titleBuffer, 24);
	const CharMask underline(underlineBuffer, 24);
	const CharMask gameOverTitle(gameOverBuffer, 49);
	const CharMask misterious(misteriousBuffer, 33);
}