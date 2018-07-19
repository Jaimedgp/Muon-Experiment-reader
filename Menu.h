/**
 *
 */

 #ifndef Menu_h
#define Menu_h
#include <ncurses.h>
#include <string.h>

class Menu {
	public:
		Menu (WINDOW *);
		//~Menu();

		void buildMenu();
		int choiseMenu();

	private:
		WINDOW *menuWin;
		
		int highlight, choice, n_choices;

};

#endif