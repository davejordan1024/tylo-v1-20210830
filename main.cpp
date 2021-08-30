#include "app.h"
#include "alpharec.h"
#include "glbl.h"
#include "bagrow.h"
#include "brwsr.h"
#include "brdcell.h"
#include "numcell.h"
#include "rckcell.h"
#include <iomanip>
#include <cassert>

App *app;				// extern App *app is declared in glbl.h.

int main(int argc, char *argv[]) {

	cout << COPYING;

	app = new App();
	app->curtbl = nullptr;
	app->curgame = nullptr;
	if(app->games.size())
		app->brwsr->load_first(app->opts["lastgame"].sval);
	app->setmod(false);
	cout << "init done\n";
	app->show();
	Fl::run();
}
