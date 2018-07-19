//

#ifndef hstgrm_h
#define hstgrm_h
#define BAR(a,b,c) A_BOLD, a, b, c, ' '|A_REVERSE|COLOR_PAIR(3), false
#include <cdk.h>

class Histogram {
	public:
		Histogram(int , char **, WINDOW*, int, int, int *); // Constructor
		~Histogram(); // destructor

		void drawIncrement(int);

		void buildHistograms(WINDOW*, CDK_PARAMS);

   		int *events;
   		int maxVlue, numclmns;

	private:
		CDKSCREEN *cdkscreen;
   		CDKHISTOGRAM *eachHistograms[10];

};

#endif
