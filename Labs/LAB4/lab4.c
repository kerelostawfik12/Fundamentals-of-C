#include<stdio.h>
#include<math.h>

#define MAX_LENGTH 5

void scanArray(int input_array[], int length);
void printArray(int input_array[], int length);
void powerArray(const int input_array[], int output_array[], int length);
int maxArray(const int input_array[], int length);

int main ()
{
	int inputArray[MAX_LENGTH];
	int outputArray[MAX_LENGTH];
    printf("Enter 5 values separated by spaces> \n");
    scanArray(inputArray, MAX_LENGTH);
	printf("Enter the value of n> \n");
	powerArray(inputArray, outputArray, MAX_LENGTH);
    printArray(inputArray, MAX_LENGTH);
    printf("The maximum is 25 %d", maxArray(outputArray, MAX_LENGTH))
    return 0;
}

void scanArray(int input_array[], int length){
	int i;
	for(i = 0; i<length; i++)
	{
	    scanf("%d", &input_array[i]);
	}
	
}
void powerArray(const int input_array[], int output_array[], int length){
	int power;
	int i;
	scanf("%d", &power);
	for(i = 0; i<length; i++)
	{
		output_array[i] = pow(input_array[i], power);
	}
}

void printArray(const int input_array[], int length){
	int i;
	for(i = 0; i<length; i++)
    {
	printf("%d ", input_array[i]);
    }
        printf("\n");
}

int maxArray(const int input_array[], int length){
	int i;
	int max = input_array[0];
	for(i = 1; i<length; i++)
	{
		if(input_array[i] > max)
		{
			max = input_array[i];
		}
	}
	return max;
}


