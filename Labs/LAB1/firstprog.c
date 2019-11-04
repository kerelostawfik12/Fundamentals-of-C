#include <stdio.h>
#define OZ_TO_ML 1/0.033814;

double oz;
double ml;

int main(){
    

printf("This program converts from ounces to milliliters. \n");
printf("Enter the volume in ounces>");
scanf("%lf ounces = ", &oz);

ml = oz*OZ_TO_ML;

printf("%.2f ounces = %.2f milliliters\n", oz, ml);

/*-ANSI IS STANDARD ANSIKEYBOARD -O IS SAYING OUTPUT WILL BE PUT IN THIS
-WALL W MEANS WARNING WALL MEANS GIVE ALL WARNINGS;
-WERROR MEANS TO GIVE ALL ERRORS;
*/
return 0;
}


