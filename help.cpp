#include "help.h"

// string src will either be the name of the app's help file or the name of a user-generated help file of arbitrary text content.
// the app's help file should not be editable but the widget showing the user-generated file should have minimal editing capability.

Helpwin::Helpwin(string src, int fontnm, int fontsz, bool ro) : Fl_Window(1,1,1,1) {

	int deco = app->decorated_h() - app->h();		// offset the window from the main app window

	resizable(this);			// note to self: not resizeble() or this->resizable()
	resize(app->x() + deco, app->y() + deco, app->w(), app->h());
	copy_label(src.c_str());
	help = new Help(0, 0, w(), h(), src, fontnm, fontsz, ro);
	if(! ro)
		callback(helpwin_cb);
}

Help::Help(int x, int y, int w, int h, string src, int fontnm, int fontsz, bool ro) {

	ismod = false;
	buff = new Fl_Text_Buffer();

	if(ro) {
		buff->append(COPYING);		// prepend credits to app help text
		buff->append("\n");
		cntnr = new nt Fl_Text_Display(x, y, w, h);
	}
	else
		cntnr = new nt Fl_Text_Editor(x, y, w, h);

	buff->tab_distance(3);
	buff->appendfile(src.c_str());
	buff->add_modify_callback(helpbuff_cb, this);		// dont need cb for Text_Display yet must assign after ->append
	cntnr->textfont(fontnm);
	cntnr->textsize(fontsz);
	cntnr->wrap_mode(Fl_Text_Editor::WRAP_AT_BOUNDS, 0);
	cntnr->buffer(buff);
}
void helpwin_cb(Fl_Widget* w, void*) {						// save changes. w is the Helpwin instance
	Helpwin *win = (Helpwin *) w;
	if(win->help->ismod)
		win->help->buff->savefile(UHLPFN);
	win->hide();
}
void helpbuff_cb(int, int ins, int del, int, const char*, void *v) {
	if(ins || del)
		((Help *)v)->ismod = true;
}
