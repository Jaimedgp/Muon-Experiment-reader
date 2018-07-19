/**
 *
 */

#ifndef Histograms_h
#define Histograms_h
#define BAR(a,b,c) A_BOLD, a, b, c, ' '|A_REVERSE|COLOR_PAIR(3), false
#include <cdk.h>

class Histogram {
	public:
		Histogram(WINDOW*, int, int, int *); // Constructor
		~Histogram(); // destructor

		void drawIncrement(int);

		void buildHistograms(WINDOW*);
		void eDraw();

   		int *vlue;
   		int maxVlue, numclmns;

	private:
		CDKSCREEN *cdkscreen;
   		CDKHISTOGRAM *eachHistograms[numclmns];

};

#endif