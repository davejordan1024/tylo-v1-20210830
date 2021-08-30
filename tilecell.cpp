#include "app.h"
#include "tilecell.h"
#include "undo.h"

Tilecell::Tilecell(int x, int y, int w_h, int8_t r, int8_t c, optmap_t o) : Fl_Box(x, y, w_h, w_h, 0) {

	col = c; row = r;
	kystrk = FLLRCHR;
	box(FL_FLAT_BOX);
	labelsize(o["cell_fs"].ival);
	labelfont(FL_COURIER);
	color(lolite = o["cell_bg"].ival);
	labelcolor(o["cell_fg"].ival);
	align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
	savecolor = 0;
};
int Tilecell::handle(int e) {

	const static int hilite = app->opts["cell_hi"].ival;

	switch(e) {
		case FL_KEYBOARD : {			// shortcut event is checked by child widget before this handle is called

			const static int reject = FL_CTRL | FL_ALT | FL_META;	// shift is ok b/c i dont want to trip up the user by rejecting upper case ltrs

			if(! (Fl::event_state() & reject)) {

				Tbl *tbl = app->curtbl;
				const int k = toupper(Fl::event_key());
				Alpharec *dec = NULL, *inc = NULL;

				// srch_keytab takes the int keystroke and returns a pointer to a struct containing (among other things)
				// the corresponding (possibly multibyte) UI symbol

				if(dec = ty::srch_keytab(tbl->alphas, tbl->alphan, k)) {			// if match, decrement count for letter entered
					inc = ty::srch_keytab(tbl->alphas, tbl->alphan, kystrk);		// and increment count for any overwrite
					ty::update_ustck(this, kystrk, k);
					ty::update_cnts(inc, dec);
					kystrk = k;
					copy_label(dec->uirep);
					app->setmod(true);
					return EVHANDLED;
				}											// if keystroke is delete, nothing is decremented, deleted letter is incremented
				else if(k == FL_Delete) {
					if(inc = ty::srch_keytab(tbl->alphas, tbl->alphan, kystrk)) {
						ty::update_ustck(this, kystrk, FLLRCHR);
						ty::update_cnts(inc, NULL);
						kystrk = FLLRCHR;
						copy_label(FLLRLBL);
						app->setmod(true);
						return EVHANDLED;
					}
				}
			}
			return EVNOTHANDLED;					// back to brdcell or rckcell ->handle() for further processing
		}
		case FL_PUSH:		take_focus();					break;
		case FL_FOCUS:		color(hilite);	redraw();	break;
		case FL_UNFOCUS:	color(lolite);	redraw();	break;
	}
	return EVHANDLED;
}
