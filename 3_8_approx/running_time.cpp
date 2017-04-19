
#include "stdafx.h"
#include "utility.h"
#include <time.h>




double time_simple2d(int iterations,std::string inp) {


	clock_t start, end;
	double msecs;


	/* GOGOGOOGGOGO */
	start = clock();

	for (int i = 0; i < iterations; i++) {
		simple2D(inp);
	}

	end = clock();
	/**STOP**/

	msecs = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;


	return msecs;

}

double time_block2DA(int iterations, std::string inp) {


	clock_t start, end;
	double msecs;


	/* GOGOGOOGGOGO */
	start = clock();

	for (int i = 0; i < iterations; i++) {
		block2DA(inp);
	}

	end = clock();
	/**STOP**/

	msecs = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;


	return msecs;

}

double time_block3D(int iterations, std::string inp) {


	clock_t start, end;
	double msecs;


	/* GOGOGOOGGOGO */
	start = clock();

	for (int i = 0; i < iterations; i++) {
		block3D(inp);
	}

	end = clock();
	/**STOP**/

	msecs = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;


	return msecs;

}


double time_any(int iterations, std::string inp, string(*f)(string)) {


	clock_t start, end;
	double msecs;


	/* GOGOGOOGGOGO */
	start = clock();

	for (int i = 0; i < iterations; i++) {
		(*f)(inp);
	}

	end = clock();
	/**STOP**/

	msecs = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;


	return msecs;

}