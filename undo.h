#ifndef UNDO_H
#define UNDO_H
#include "app.h"
#include "glbl.h"
#include "game.h"

struct Tilecell;

struct Undo {
	static int lvl;	// where am i in the undo stack
	static int sz;		// where is the end of the valid part of the stack
	static int cap;	// when do i have to start pushing back again (this is not the STL capacity())
	Game *game;			// undo/redo can require switching game
	Tilecell *tile;
	char lhltr, rhltr;	// left hand and right hand i.e. older and newer letter

	Undo(Game*, Tilecell*, char, char);
	static void undo();
	static void redo();
	static void purge();
};
#endif // UNDO_H
