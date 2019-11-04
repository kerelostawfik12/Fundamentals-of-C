#include <stdio.h> 

int main(){
int numerator, denominator;
printf("Enter the numberator and denominator separated by a space> ");
scanf("%d%d", &numerator, &denominator);
printf("%d/%d = %d %d/%d\n", numerator, denominator, numerator/denominator, numerator % denominator, denominator);
return 0;
}


