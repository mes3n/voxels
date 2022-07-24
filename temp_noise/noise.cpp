#include <iostream>
#include <math.h>

#define PI 3.1415927

float noise (int x) { 
	static const int a = 0;
	static const int b = 37;

	x = (x<<13) ^ x;

	float y = ((x * (x*x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 2147483648.0;

	float ft = y * PI;
       	float f = (1.0 - cos(ft)) * 0.5;

	return a*(1.0-f) + b*f;
}


float smooth_noise (int x) {
	return noise(x)/2 + noise(x-1)/4 + noise(x+1) / 4;
}


int main () {
	int a = 1;
	int b = 10;
	for (int x = 0; x <= 100; x++) {
		int y = smooth_noise(x);
	       	std::cout << y << " ";	
		for (int c = 0; c < y; c++) {
			std::cout << "*";
		}
		std::cout << "\n";
	}
	
	return 0;
}
