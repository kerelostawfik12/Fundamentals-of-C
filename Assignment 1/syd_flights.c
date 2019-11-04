/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name:
 * Student ID: 13220607
 * Date of submission: 03/05/2019
 * A brief statement on what you could achieve (less than 50 words):
 * Every function in the program.
 *
 * A brief statement on what you could NOT achieve (less than 50 words):
 * Test 11.
 * procedural programming I wish I didn't do it with OO design. 
 * MALLOC
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/

#include <stdio.h> /* printf, scanf, fgets, getchar */
#include <string.h> /* strlen, strcpy, strtoi, strtok */
#include <stdlib.h> /* malloc, calloc, free, atoi */

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/

#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/

/*******************************************************************************
 * Struct date_time
 *
 *
 * month - integer between 1 and 12 (inclusive)
 * day - integer between 1 and 31 (inclusive)
 * hour - integer between 0 and 23 (inclusive)
 * minute - integer between 0 and 59 (inclusive)
*******************************************************************************/

struct date_time {
    int month;
    int day;
    int hour;
    int minute;

};

typedef struct date_time date_time_t;

/*******************************************************************************
 * Struct flight
 *
 *
 * flightcode - array of MAX_FLIGHTCODE_LEN+1 chars (string)
 * departure_dt - a structure of date_time_t type as defined below
 * arrival_city - array of MAX_CITYCODE_LEN+1 chars (string)
 * arrival_dt - a structure of date_time_t type as defined below
*******************************************************************************/

struct flight {
    char flightcode[MAX_FLIGHTCODE_LEN + 1];
    date_time_t departure_dt;
    char arrival_city[MAX_CITYCODE_LEN + 1];
    date_time_t arrival_dt;

};
typedef struct flight flight_t;

/*******************************************************************************
  * Function prototypes - do NOT change the given prototypes. However you may
  * define your own functions if required.
*******************************************************************************/

void print_menu(void);

void initialise_flight_array(flight_t *flightArray[]);

char *read_choice1(void);

void use_menu(flight_t *flights_p[], FILE *fp);

void invalid_choice(void);

void use_flight_menu(flight_t *flights_p[]);

void set_flight_code(flight_t *flight, char *flightCode);

void set_arrival_city(flight_t *flight, char *flightCode);

date_time_t scan_date_time(void);

void add_flight(flight_t *flights_p[], flight_t *flight);

int is_valid_flight_code(char *ch);

int is_valid_date_time(date_time_t testDate);

int is_valid_city_code(char ch[]);

void print_flights(flight_t *flights_p[]);

void print_flight_array(flight_t *flights_p[]);

int check_flight_array(flight_t *flightArray[]);

void print_date_time(date_time_t date);

int compare_input_arrival_city(flight_t *flight, const char *input);

int check_arrival_city(flight_t *flights_p[], const char *input,
                       flight_t *flight_p[]);

void save_file(FILE *fp, flight_t *flights_p[]);

void load_file(FILE *fp, flight_t *flights_p[]);


/*******************************************************************************
 * Main
*******************************************************************************/
int main(void){
    FILE* database = NULL;
    flight_t *flights[MAX_NUM_FLIGHTS];
    *flights = (flight_t *) calloc(MAX_NUM_FLIGHTS, sizeof(flight_t));
    initialise_flight_array(flights);
    print_menu();
    use_menu(flights, database);
    return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/

void print_menu(void)
{
    printf("\n"
           "1. add a flight\n"
           "2. display all flights to a destination\n"
           "3. save the flights to the database file\n"
           "4. load the flights from the database file\n"
           "5. exit the program\n"
           "Enter choice (number between 1-5)>\n");
}


/*******************************************************************************
 * This function initialises the flight pointers in the flight array to NULL
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/

void initialise_flight_array(flight_t *flightArray[])
{
    int i;
    for (i = 0; i < MAX_NUM_FLIGHTS; i++)
    {
        flightArray[i] = NULL;
    }

}


/*******************************************************************************
 * This function reads an integer from user input and returns the integer
 * that will be read as the choice used in the menu.
 * inputs:
 * - none
 * outputs:
 * - Integer used as menu option.
*******************************************************************************/

char *read_choice1(void)
{
    char *myMenuChoice = (char *) malloc(sizeof(char) * 10);
    fgets(myMenuChoice, 1000, stdin);
    return myMenuChoice;
}


/*******************************************************************************
 * Function that allows user to navigate through menu.
 * inputs:
 * - flight* flights_p[]: Array of pointers to flights
 * - FILE* fp pointer to database file
 * output:
 * none
*******************************************************************************/

void use_menu(flight_t *flights_p[], FILE *fp)
{
    char *choice = read_choice1();
    choice = strtok(choice, " ");
    int len = strlen(choice);
    while (choice[0] != '5')
    {
        if(len == 2 && choice[len-1] != '\n')
        {
            invalid_choice();
        }
        else
        {
            switch (choice[0])
            {
                case '1':
                    if(check_flight_array(flights_p) == 5)
                    {
                        printf("Cannot add more flights - memory full\n");

                        print_menu();
                        break;
                    }
                    else
                    {
                        use_flight_menu(flights_p);
                        break;
                    }
                case '2':
                    print_flights(flights_p);
                    break;
                case '3':
                    save_file(fp, flights_p);
                    break;
                case '4':
                    load_file(fp, flights_p);
                    break;
                case '\n':
                    break;
                case ' ':
                    break;
                default:
                    invalid_choice();
                    break;
            }
        }
        choice = read_choice1();
    }
    free(choice);
    choice = NULL;
}

/*******************************************************************************
 * prints error message and user menu
 * inputs:
 * - none
 * output:
 * - none
*******************************************************************************/

void invalid_choice()
{
    printf("Invalid choice\n");
    print_menu();
}

/*******************************************************************************
 * function that takes user input and turns it into a flight if valid.
 * adds the flight to the flight_array
 * inputs:
 * - flight* flights_p[]: pointer to memory address of the flight array 
 *   initialised to null in the main function.of the flight array.
 * output:
 * - none
*******************************************************************************/

void use_flight_menu(flight_t *flights_p[])
{

    char* flight_code = (char *) malloc(MAX_FLIGHTCODE_LEN + 1 * sizeof(char));
    flight_t *newFlight = (flight_t *) malloc(1 * sizeof(flight_t));
    while (0 == 0)
    {
        printf("Enter flight code>\n");
        fgets(flight_code, 1000, stdin);
        if (is_valid_flight_code(flight_code) == 0 )
        {
            set_flight_code(newFlight, flight_code);
            break;
        }
        else
        {
            printf("Invalid input\n");
        }
    }


    printf("Enter departure info for the flight leaving SYD.\n");
    while (0 == 0)
    {
        printf("Enter month, date, hour and minute separated by spaces>\n");
        date_time_t depart = scan_date_time();
        if (is_valid_date_time(depart) == 0)
        {
            newFlight->departure_dt = depart;
            break;
        }
        else
        {
            printf("Invalid input\n");
        }
    }

    while (0 == 0)
    {
        printf("Enter arrival city code>\n");
        char *arrivalCity = (char *) malloc(MAX_FLIGHTCODE_LEN *
                                            sizeof(char));
        fgets(arrivalCity, 1000, stdin);
        set_arrival_city(newFlight, arrivalCity);
        break;
    }

    printf("Enter arrival info.\n");
    while (0 == 0)
    {
        printf("Enter month, date, hour and minute separated by spaces>\n");
        date_time_t arrive = scan_date_time();
        if (is_valid_date_time(arrive) == 0)
        {
            newFlight->arrival_dt = arrive;
            add_flight(flights_p, newFlight);
            print_menu();
            break;
        }
        else
        {

            printf("Invalid input\n");
        }
    }
}



/*******************************************************************************
 * Function that initialises a valid flightcode in flight
 * inputs:
 * - flight_t *flight: array of pointers to flight
 * - char *flightCode
 * output:
 * - none
*******************************************************************************/

void set_flight_code(flight_t *flight, char *flightCode)
{
    strtok(flightCode, "\n");
    int i = 0;
    for (i = 0; i < MAX_FLIGHTCODE_LEN; i++)
    {
        flight->flightcode[i] = *(flightCode + i);
    }
}


/*******************************************************************************
 * Function that sets arrival city variable in character
 * inputs:
 * - flight_t *flight: pointer to a flight
 * - char* arrivalCity: pointer to a block of characters
 * output:
 * - none
*******************************************************************************/

void set_arrival_city(flight_t *flight, char *arrivalCity)
{
    int arrlen= 3;
    int i = 0;
    strtok(arrivalCity, "\n");
    strtok(arrivalCity, " ");
    for (i = 0; i<arrlen; i++)
    {

        flight->arrival_city[i] = *(arrivalCity + i);
    }
}

/*******************************************************************************
 * Function that adds flight to flight array in main
 * inputs:
 * - flight_t *flights_p[]: Array of pointers to flights
 * - flight_t *flight: pointer to a flight
 * output:
 * - none
*******************************************************************************/


void add_flight(flight_t *flights_p[], flight_t *flight)
{
    int i;
    for (i = 0; i < MAX_NUM_FLIGHTS; i++)
    {
        if (flights_p[i] == NULL)
        {
            flights_p[i] = flight;
            break;
        }
    }
}


/*******************************************************************************
 * Function that sets values for a date_time_t struct and returns them
 * inputs:
 * - none
 * output:
 * - date_time_t returns struct date_time_t with valid variables
*******************************************************************************/

date_time_t scan_date_time(void)
{
    date_time_t *ret = (date_time_t *) malloc(sizeof(date_time_t));
    scanf("%d %d %d %d", &ret->month, &ret->day, &ret->hour, &ret->minute);
    if(getchar() == 32)
    {
        getchar();
    }
    return *ret;
}


/*******************************************************************************
 * Function that tests if a flight code is valid (first 2 characters are capital
 * letters and 1-4 numerical values)
 * inputs:
 * - char *ch pointer to memory block of MAX_FLIGHT_CODE +1 (7) characters,
 * used for flight code.
 * outputs:
 * - returns 0 if flight code is valid
 * - returns 1 for invalid flight code
*******************************************************************************/

int is_valid_flight_code(char *ch)
{
    int flag = -1; /* variable to check if first 2 characters are caps A-Z */
    int chars = 0; /*character counter */
    if ((ch[0] >= 'A' && ch[0] <= 'Z') && (ch[1] >= 'A' && ch[1] <= 'Z'))
    {
        int i = 2; /* index counter */
        while (ch[i + 1] != '\0' && ch[i + 1] != '\n' && chars <= 4)
        {
            flag = 1; /* shows first if statement is true */
            if (!(ch[i] >= '0' && ch[i] <= '9') || ch[i] == ' ')
            {
                return 1;
            }
            i++;
            chars++;
        }
        if (flag == -1) /*if  the first two letters are capitals from A-Z*/
        {
            if (ch[2] >= '0' && ch[2] <= '9') /*if the third character is
            a number from 0-9*/
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        if (chars >= 4 || chars <= 0)
        {
            return 1;
        }
        else
            return 0;
    }
    return 1;

}


/*******************************************************************************
 * Function that checks if input date_time_t is valid
 * inputs:
 * - date_time_t testDate user generated date time
 * outputs:
 * - returns 0 if date time is valid
 * - returns 1 if date time is not valid
*******************************************************************************/

int is_valid_date_time(date_time_t testDate)
{
    if ((testDate.month >= 1 && testDate.month <= 12) &&
        (testDate.day >= 1 && testDate.day <= 31) &&
        (testDate.hour >= 0 && testDate.hour <= 23) &&
        (testDate.minute >= 0 && testDate.minute <= 59))
    {
        return 0;
    }
    return 1;
}

/*******************************************************************************
 * Function that checks if the input characters are a valid flight code ie.
 * if the first two characters are capital letters (A-Z) and the last is a
 * numerical value (1-9)
 * flight code
 * inputs:
 * - char *ch user generated block of characters
 * outputs:
 * - return 0 if the string valid flight code
 * - return 1 if the flight code is invalid
*******************************************************************************/

int is_valid_city_code(char ch[])
{
    if ((ch[0] >= 'A' && ch[0] <= 'Z') && (ch[1] >= 'A' && ch[1] <= 'Z') &&
        (ch[2] >= 'A' && ch[2] <= 'Z'))
    {
        return 0;
    }
    return 1;

}


/*******************************************************************************
 * Function that prints multiple all flights from array
 * inputs:
 * - flight_t *flights_p[] Array of pointers to flights
 * output:
 * - none
*******************************************************************************/

void print_flights(flight_t *flights_p[])
{
    flight_t *dupeFlight[MAX_NUM_FLIGHTS];
    *dupeFlight = (flight_t *) calloc(MAX_NUM_FLIGHTS, sizeof(flight_t));
    initialise_flight_array(dupeFlight);
    printf("Enter arrival city code or enter * to show all destinations>\n");
    char *input = (char *) malloc(sizeof(char) * 10);
    fgets(input, 100, stdin);
    if ((*input == '*') && (check_flight_array(flights_p) > 0))
    {
        printf("Flight Origin          Destination\n");
        printf("------ --------------- ---------------\n");
        print_flight_array(flights_p);
        print_menu();
    }
    else if ((check_flight_array(flights_p) > 0) &&
             (check_arrival_city(flights_p, input, dupeFlight) !=
              0))
    {
        printf("Flight Origin          Destination\n");
        printf("------ --------------- ---------------\n");
        print_flight_array(dupeFlight);
        print_menu();
    }
    else
    {
        printf("No flights\n");
        print_menu();
    }
}

/*******************************************************************************
 * Function that prints singular flight from flight array
 * inputs:
 * - flight_t *flights_p[] Array of pointers to flights
 * output:
 * - none
*******************************************************************************/
void print_flight_array(flight_t *flights_p[]) {
    int i = 0;
    int flight_array_MAX_NUM_FLIGHTS = check_flight_array(flights_p);
    for (i = 0; i < flight_array_MAX_NUM_FLIGHTS; i++)
    {
        printf("%-6s SYD ", flights_p[i]->flightcode);
        print_date_time(flights_p[i]->departure_dt);
        printf(" %.3s ", flights_p[i]->arrival_city);
        print_date_time(flights_p[i]->arrival_dt);
        printf("\n");
    }
}


/*******************************************************************************
 * Function that checks if flight array is not empty and returns number of
 * non-null characters in arrival city
 * inputs:
 * - flight_t *flightArray[] Array of pointers to flights
 * output:
 * - counter variable for non null number of characters
*******************************************************************************/
int check_flight_array(flight_t *flightArray[])
{
    int checker = 0;
    int i;
    for (i = 0; i < MAX_NUM_FLIGHTS; i++)
    {
        if (flightArray[i] != NULL)
        {
            checker++;
        }
    }
    return checker;
}

/*******************************************************************************
 * Function that prints the variables of the variables in date_time_t structure
 * in the format 00-00, 00:00 as two 2 digit numbers separated by a hyphen and
 * two 2 digit numbers separated by a colon. If the variable is a one digit
 * number a 0 is put in front eg. 9 is printed as 0-9.
 *
 * inputs:
 * - date_time_t date - the date whose variables need to be printed in the
 * - previously mentioned format.
 * output:
 * - none
*******************************************************************************/


void print_date_time(date_time_t date)
{
    int month;
    int day;
    int hour;
    int minute;
    month = date.month;
    day = date.day;
    hour = date.hour;
    minute = date.minute;
    printf("%02d-%02d ", month, day);
    printf("%02d:%02d", hour, minute);
}


/*******************************************************************************
 * Function that compares input to arrivalcity string stored in the flight array
 * and returns an integer count if input is identical to arrivalcity in array.
 * inputs:
 * - flight_t *flight Array of pointers to flights
 * - const char* input pointer to user input
 * output:
 * - returns number of identical non-null characters, if count == 3, they are
 * identical
 * - returns 0 if there are no equal characters.
*******************************************************************************/

int compare_input_arrival_city(flight_t *flight, const char *input)
{
    int i;
    int count = 0;
    if (flight != NULL)
    {
        for (i = 0; i < 3; i++)
        {
            if (*(input + i) == flight->arrival_city[i])
            {
                count++;
            }
        }
        return count;
    }
    else
    {
        return count;
    }
}


/*******************************************************************************
 * Function that checks if arrival city is not empty
 * inputs:
 * - flight_t *flights_p[] Array of pointers to flights in main
 * - const char *input is pointer to input character block
 * - flight_t *flight_p[] Array of duplicate flights
 * output:
 * - return 1 if arrival city does not have 3 characters
 * - return 0 if arrival city does have 3 characters
*******************************************************************************/

int check_arrival_city(flight_t *flights_p[], const char *input,
                       flight_t *flight_p[]) {
    int i;
    int j = 0;
    flight_t *flight;
    for (i = 0; i < MAX_NUM_FLIGHTS; i++)
    {
        if (compare_input_arrival_city(flights_p[i], input) == 3)
        {
            flight = flights_p[i];
            add_flight(flight_p, flight);
            j = 1;
        }
    }
    return j;
}

/*******************************************************************************
 * Function that saves flights into database file in main
 * inputs:
 * - FILE *fp pointer to memory location of database file in main
 * - flight_t *flights_p[] is an array of pointers to the flights in the filght
 *   array made in main
 * output:
 * - none

*******************************************************************************/

void save_file(FILE *fp, flight_t *flights_p[])
{
    fp = fopen(DB_NAME, "w");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);

    }
    int i = 0;
    int flight_array_MAX_NUM_FLIGHTS = check_flight_array(flights_p);
    for (i = 0; i < flight_array_MAX_NUM_FLIGHTS; i++)
    {
        fprintf(fp, "%3s-%d-%d-%d-%d-%s-%d-%d-%d-%d\n",
                flights_p[i]->flightcode,
                flights_p[i]->departure_dt.month,
                flights_p[i]->departure_dt.day,
                flights_p[i]->departure_dt.hour,
                flights_p[i]->departure_dt.minute,
                flights_p[i]->arrival_city,
                flights_p[i]->arrival_dt.month,
                flights_p[i]->arrival_dt.day,
                flights_p[i]->arrival_dt.hour,
                flights_p[i]->arrival_dt.minute);
    }
    fclose(fp);
    print_menu();

}


/*******************************************************************************
 * Function that loads flights from the database file into the flight array
 * inputs:
 * - FILE* fp (database file) from main
 * - flight_t *flights_p[] Array of pointers to flights
 * output:
 * - none
*******************************************************************************/

void load_file(FILE *fp, flight_t *flights_p[])
{
    initialise_flight_array(flights_p); /* initialise all pointers null
    in flight pointer array to NULL */
    fp = fopen(DB_NAME, "r");
    if (fp == NULL)
    {
        fprintf(stdout, "%s", "Read error\n"); /* if you try loading the file
        before you save it */
        print_menu();
    }

    else
    {
        char *input = malloc(sizeof(char) * 300);
        char *line[10];
        char *replace;
        int i = 0;
        while (fgets(input, 100, fp))
        {
            replace = strtok(input, "-");
            while (replace != NULL)
            {
                line[i] = replace;
                i++;
                replace = strtok(NULL, "-");
            }
            i = 0;
            input = strtok(input, "-");
            flight_t *newFlight = (flight_t *) malloc(1 * sizeof(flight_t));
            date_time_t *depart = (date_time_t *) malloc(sizeof(date_time_t));
            date_time_t *arrive = (date_time_t *) malloc(sizeof(date_time_t));
            depart->month = atoi(line[1]);
            depart->day = atoi(line[2]);
            depart->hour = atoi(line[3]);
            depart->minute = atoi(line[4]);
            arrive->month = atoi(line[6]);
            arrive->day = atoi(line[7]);
            arrive->hour = atoi(line[8]);
            line[9] = strtok(line[9], "\n");
            arrive->minute = atoi(line[9]);
            newFlight->departure_dt = *depart;
            newFlight->arrival_dt = *arrive;
            strcpy(newFlight->flightcode, line[0]);
            strcpy(newFlight->arrival_city, line[5]);
            add_flight(flights_p, newFlight);
        }
        fclose(fp);
        print_menu();
    }

}