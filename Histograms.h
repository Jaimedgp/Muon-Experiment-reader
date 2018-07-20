/**
 *
 */

#ifndef Histograms_h
#define Histograms_h
#define BAR(a,b,c) A_BOLD, a, b, c, ' '|A_REVERSE|COLOR_PAIR(3), false
#include <cdk.h>

class Histograms {
	public:
		Histograms(WINDOW*, int, int); // Constructor
		~Histograms(); // destructor

		void drawIncrement(int);

		void buildHistograms(WINDOW*);
		void reDraw();

   		int vlue[];
   		int maxVlue, numclmns;

	private:
		CDKSCREEN *cdkscreen;
   		CDKHISTOGRAM *eachHistograms[];

};

#endif