#ifndef HELP_H
#define HELP_H
#include "app.h"
#include "glbl.h"

struct Help	{
	bool ismod;
	Fl_Text_Display *cntnr;
	Fl_Text_Buffer *buff;
	Help(int x, int y, int w, int h, string src, int fontnm, int fontsz, bool ro);
};

struct Helpwin : Fl_Window	{
	Help *help;
	Helpwin(string, int, int, bool);
};
void helpwin_cb(Fl_Widget*, void*);
void helpbuff_cb(int, int ins, int del, int, const char*, void*);

#endif // HELP_H

