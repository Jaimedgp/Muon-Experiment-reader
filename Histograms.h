/**
 *
 */

#ifndef Histograms_h
#define Histograms_h
#define BAR(a,b,c) A_BOLD, a, b, c, ' '|A_REVERSE|COLOR_PAIR(3), false
#include <cdk.h>
#include <vector>


class Histograms {
	public:
		Histograms(WINDOW* cursesWin, int maxValue, int numColumns); // Constructor
		~Histograms(); // destructor

		void drawIncrement(int i);

		void buildHistograms(WINDOW* cursesWin);
		void reDraw(void);
		void passTime (int newTime);

   		int maxVlue, numclmns;
   		std::vector<int> vlue;

		CDKSCREEN *cdkscreen;
   		CDKHISTOGRAM *eachHistograms[];
};

#endif