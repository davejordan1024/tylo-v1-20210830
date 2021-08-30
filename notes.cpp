#include "app.h"
#include "notes.h"
#include "brdcell.h"
#include "rckcell.h"

Notes::Notes(int x, int y, int w, int h, optmap_t o) : Fl_Text_Editor(x, y, w, h) {

	box			(FL_FRAME_BOX);
	textfont		(FL_COURIER);
	textsize		(o["notes_fs"].ival);
	color			(o["notes_bg"].ival);
	textcolor	(o["notes_fg"].ival);
	cursor_color(o["notes_cu"].ival);
	wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
	remove_key_binding(FL_Home,	FL_CTRL);						// remap ctrl-home and ctrl-end to home and end
	remove_key_binding(FL_End,		FL_CTRL);
	add_key_binding	(FL_Home,	0,			kf_ctrl_move);
	add_key_binding	(FL_End,		0,			kf_ctrl_move);
	add_key_binding	(FL_Tab,		0,			kf_ignore);			// ignore but don't absorb tab
	add_key_binding	('C',			FL_CTRL,	kf_ignore);			// "		" ctrl- u.c and l.c. 'C'
	add_key_binding	('c',			FL_CTRL,	kf_ignore);
}
int Notes::handle(int e) {

	switch(e) {
		case FL_SHORTCUT:	return EVNOTHANDLED;
		case FL_KEYBOARD: {

			int s = Fl::event_state();

			if(s & FL_ALT || s & FL_META)				// alt-*, meta-* -- pass onward
				return Fl_Text_Editor::handle(e);

			int k = Fl::event_key();

			if((! (s & (FL_CTRL | FL_ALT | FL_META))) && (k != FL_Tab))
				return Fl_Text_Editor::handle(e);	// regular alphanumeric key


			if(k == FL_Tab) {								// tab & shift-tab (no ctrl allowed)
				if(s & FL_CTRL)
					return Fl_Text_Editor::handle(e);
				if(s & FL_SHIFT)
					app->curtbl->rck[0]->take_focus();
				else
					app->brwsr->take_focus();
				return EVHANDLED;
			}
			if(s & FL_CTRL) {
				if(k == FL_Delete) {					// ctl-del -- erase all text
					this->buffer()->text(0);
					return EVHANDLED;
				}
			}
			return Fl_Text_Editor::handle(e);	// any other keystrokes -- pass onward
		}		// end kbd event
		break;
		case FL_FOCUS:		this->show_cursor();	return EVHANDLED;		// ? don't need PUSH
		case FL_UNFOCUS:	this->hide_cursor();	return EVHANDLED;
	}														// end switch
	return Fl_Text_Editor::handle(e);			// any other events
}
void notes_cb(int, int nInserted, int nDeleted, int, const char*, void* v) {
	if(nInserted || nDeleted)
		app->setmod(true);
}