#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define G 9.8
double displacementX;
double initialVelocity;
int angleElevation;
void printMenu(void);
double flightTime(double displacement, double velocity, int angleElevation);
double height(double velocity, double time, int angleElevation);

int main(){
double h;
double time;
printf("Enter horizontal displacement: \n");
scanf("%lf", &displacementX);
printf("Enter initial velocity: \n");
scanf("%lf", &initialVelocity);
printf("Enter angle of elevation:\n");
scanf("%d", &angleElevation);

time = flightTime(displacementX, initialVelocity, angleElevation); 
printf("This is your flight time %lf", time);

h = height(initialVelocity, time, angleElevation);

printf("This is your height: %lf", h);

return 0;

}

double flightTime(double displacement, double velocity, int angleElevation){
double time = (displacementX)/initialVelocity*cos(angleElevation);
return time;
}

double height(double velocity, double time, int angleElevation){
double h = (initialVelocity*(sin(angleElevation)*(180/PI))*time)-(0.5*9.8*time*time);
return h;
}
