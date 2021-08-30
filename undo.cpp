#include "undo.h"

Undo::Undo(Game *_game, Tilecell *_tile, char _lh, char _rh) {
	game = _game;
	tile = _tile;
	lhltr = _lh;
	rhltr = _rh;
}
void Undo::undo() {

	if(lvl < 0)		// 	cout << "undo " << lvl << " of " << sz << " of " << cap << endl;
		return;

	Undo *undorec = app->uvec[lvl];
	Game *undogm = undorec->game;

	if(app->curgame != undogm) {

		Brwsr *b = app->brwsr;
		int j, n = b->size();

		for(j = 1; j <= n && b->data(j) != undogm; j++);		// probably can adapt this loop to load_first
		if(b->data(j) != undogm) {
			fl_alert("Undo: game not found.");
			return;
		}
		b->select(j);
		undogm->load(false);		// curtbl, curgm, setmsg
	}
	else {
		Tbl *tbl = app->curtbl;
		Tilecell *undotile = undorec->tile;
		undotile->take_focus();

		// tile kystrk is to be overwritten with undorec lh. remaining will be: tile kystrk ++, undorec lh --

		Alpharec	*inc = ty::srch_keytab(tbl->alphas, tbl->alphan, undotile->kystrk),
					*dec = ty::srch_keytab(tbl->alphas, tbl->alphan, undorec->lhltr);

		ty::update_cnts(inc, dec);

		if(dec) {												// overwrite displayed letter with older one ...
			undotile->kystrk = undorec->lhltr;
			undotile->copy_label(dec->uirep);
		}
		else {
			undotile->kystrk = FLLRCHR;				// ... which might have been empty
			undotile->copy_label(FLLRLBL);
		}
		lvl--;
	}
	return;
}
void Undo::redo() {
	cout << "redo " << lvl << " of " << sz << " of " << cap << endl;

	if(lvl < 0)
		lvl++;

	Undo *undorec = app->uvec[lvl];
	Game *undogm = undorec->game;

	if(app->curgame != undogm) {

		Brwsr *b = app->brwsr;
		int j, n = b->size();

		for(j = 1; j <= n && b->data(j) != undogm; j++);		// probably can adapt this loop to load_first
		if(b->data(j) != undogm) {
			fl_alert("Undo: game not found.");
			return;
		}
		b->select(j);
		undogm->load(false);		// curtbl, curgm, setmsg
	}
	else {
		Tbl *tbl = app->curtbl;
		Tilecell *undotile = undorec->tile;
		undotile->take_focus();

		// tile kystrk is to be overwritten with undorec rh. remaining will be: tile kystrk ++, undorec rh --

		Alpharec	*inc = ty::srch_keytab(tbl->alphas, tbl->alphan, undotile->kystrk),
					*dec = ty::srch_keytab(tbl->alphas, tbl->alphan, undorec->rhltr);

		ty::update_cnts(inc, dec);

		if(dec) {												// overwrite displayed letter with newer one ...
			undotile->kystrk = undorec->rhltr;
			undotile->copy_label(dec->uirep);
		}
		else {
			undotile->kystrk = FLLRCHR;				// ... which might have been empty
			undotile->copy_label(FLLRLBL);
		}
		if(lvl + 1 < sz)
			lvl++;
	}
	return;
}
void Undo::purge() {

	vector<Undo*>::iterator it =
		remove_if(							// remove_if does not remove anything but moves the offending recs to the back of the list
			app->uvec.begin(),			// and returns ptr to the first moved rec.
			app->uvec.end(),
			[] (auto it) { return it->game == app->curgame; }
		);
	app->uvec.erase(it, app->uvec.end());
	Undo::lvl = (Undo::cap = Undo::sz = app->uvec.size()) - 1;
}
