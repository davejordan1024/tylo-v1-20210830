#ifndef MENU_H
#define MENU_H
#include "glbl.h"
#include "tbl.h"
#include "app.h"
#include "brwsr.h"
#include "game.h"
#include "ty.h"
#include "undo.h"

//class Tbl;
#define MCB_ARGS	Fl_Widget *w, void *v

struct Menu : Fl_Menu_Bar {
	Menu(int x, int y, int w, int h, vector<Tbl*>, optmap_t);

	static void new_mcb		(MCB_ARGS);
	static void save_mcb		(MCB_ARGS);
	static void rematch_mcb	(MCB_ARGS);
	static void clear_mcb	(MCB_ARGS);
	static void toggle_mcb	(MCB_ARGS);
	static void rename_mcb	(MCB_ARGS);
	static void del_mcb		(MCB_ARGS);
	static void quit_mcb		(MCB_ARGS);
	static void squish_mcb	(MCB_ARGS);
	static void copy_mcb		(MCB_ARGS);
	static void help_mcb		(MCB_ARGS);
	static void sort_mcb		(MCB_ARGS);
	static void undo_mcb		(MCB_ARGS);
	static void redo_mcb		(MCB_ARGS);
};
#endif // MENU_H
