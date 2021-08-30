#include "app.h"
#include "rckcell.h"
#include "brdcell.h"
#include "notes.h"

Rckcell::Rckcell(int cellpix, int x, int y, int c, optmap_t o)	: Tilecell(x, y, cellpix, -1, c, o) {}

int Rckcell::handle(int e) {

	const static bool autor = app->opts["autoright"].ival;
	const static int reject = FL_CTRL | FL_ALT | FL_META;
	int k = Fl::event_key();
	int s = Fl::event_state();
	Tbl *tbl = app->curtbl;

	if(e == FL_SHORTCUT) return EVNOTHANDLED;

	if(Tilecell::handle(e) == EVHANDLED) {
		if(e == FL_KEYBOARD && k != FL_Delete && autor && this->col + 1 < tbl->rckn)		// autoright
			tbl->rck[this->col + 1]->take_focus();
		return EVHANDLED;
	}
	if(e != FL_KEYBOARD)
		return EVNOTHANDLED;					// certain unwanted events will leak thru from tilecell::handle()

	if(! (s & reject)) {
		if(s & FL_SHIFT) {					// shift-tab is the only valid shift
			if(k == FL_Tab)
				tbl->brd[tbl->brdn / 2][tbl->brdn / 2]->take_focus();
		}
		else {									// all else has no shift, ctl, alt, or meta. dont care about capslock or numlock etc
			switch(k) {
				case FL_Down		:	// same as tab
				case FL_Tab			:											tbl->notes					->take_focus(); break;
				case FL_Right		:	if(this->col < tbl->rckn - 1)	tbl->rck[this->col + 1]	->take_focus(); break;
				case FL_BackSpace	:	// same as left
				case FL_Left		:	if(this->col > 0)     			tbl->rck[this->col - 1]	->take_focus(); break;
				case FL_Home		:											tbl->rck[0]					->take_focus(); break;
				case FL_End			:											tbl->rck[tbl->rckn - 1]	->take_focus(); break;
				case FL_Up			:	tbl->brd[tbl->brdn / 2][tbl->brdn / 2]						->take_focus(); break;
			}
		}
		return EVHANDLED;
	}
	return EVNOTHANDLED;
}
