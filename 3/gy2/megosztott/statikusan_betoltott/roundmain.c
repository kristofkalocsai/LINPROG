/* roundmain.c */
#include <stdio.h>
#include "round.h"

int errorCode = 0; // Erre hivatkozik majd a könyvtárbeli extern

int main()
{
        double x = 4.2;
        roundingMethod = 0;
        printf("%lf\n", round(x)); // 5.000000
        roundingMethod = 1;
        printf("%lf\n", round(x)); // 4.000000
        
        roundingMethod = 2;
        printf("%lf\n", round(x)); // 4.000000
                         
        roundingMethod = 3;
        printf("%lf\n", round(x));
        printf("%d\n", errorCode);  // -1
	return 0;
}

