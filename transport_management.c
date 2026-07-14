#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 10
#define MAX_NAME_LENGTH 50
#define MAX_PASSENGERS 25

typedef struct Schedule {
    char destination[MAX_NAME_LENGTH];
    char time[MAX_NAME_LENGTH];
    struct Schedule *next;
} Schedule;

typedef struct Passenger {
    char name[MAX_NAME_LENGTH];
    int age;
    struct Passenger *next;
} Passenger;

typedef struct Bus {
    int busID;
    char driverName[MAX_NAME_LENGTH];
    Schedule *scheduleHead;
    Passenger *passengerHead;
} Bus;

Bus busArray[MAX_BUSES];
int busCount = 0;

/* Function Prototypes */
void addBus();
void addSchedule();
void addPassenger();
void displayBuses();
void displaySchedule(int busID);
void displayPassengers(int busID);
void deleteBus();
void deleteSchedule();
void deletePassenger();
void freeSchedules(Schedule *head);
void freePassengers(Passenger *head);

int main()
{
    int choice;

    while (1)
    {
        printf("\n========== TRANSPORT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Bus\n");
        printf("2. Add Schedule\n");
        printf("3. Add Passenger\n");
        printf("4. Display Buses\n");
        printf("5. Display Schedule\n");
        printf("6. Display Passengers\n");
        printf("7. Delete Bus\n");
        printf("8. Delete Schedule\n");
        printf("9. Delete Passenger\n");
        printf("10. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addBus();
                break;

            case 2:
                addSchedule();
                break;

            case 3:
                addPassenger();
                break;

            case 4:
                displayBuses();
                break;

            case 5:
            {
                int id;
                printf("Enter Bus ID: ");
                scanf("%d",&id);
                displaySchedule(id);
                break;
            }

            case 6:
            {
                int id;
                printf("Enter Bus ID: ");
                scanf("%d",&id);
                displayPassengers(id);
                break;
            }

            case 7:
                deleteBus();
                break;

            case 8:
                deleteSchedule();
                break;

            case 9:
                deletePassenger();
                break;

            case 10:
                printf("Thank you!\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }
}

/* Add Bus */
void addBus()
{
    if(busCount >= MAX_BUSES)
    {
        printf("Maximum bus limit reached.\n");
        return;
    }

    Bus newBus;

    printf("Enter Bus ID: ");
    scanf("%d",&newBus.busID);

    printf("Enter Driver Name: ");
    scanf(" %[^\n]",newBus.driverName);

    newBus.scheduleHead=NULL;
    newBus.passengerHead=NULL;

    busArray[busCount++]=newBus;

    printf("Bus Added Successfully.\n");
}

/* Add Schedule */

void addSchedule()
{
    int busID,found=0;

    printf("Enter Bus ID: ");
    scanf("%d",&busID);

    for(int i=0;i<busCount;i++)
    {
        if(busArray[i].busID==busID)
        {
            found=1;

            Schedule *newSchedule=(Schedule*)malloc(sizeof(Schedule));

            if(newSchedule==NULL)
            {
                printf("Memory Allocation Failed.\n");
                return;
            }

            printf("Enter Destination: ");
            scanf(" %[^\n]",newSchedule->destination);

            printf("Enter Time: ");
            scanf(" %[^\n]",newSchedule->time);

            newSchedule->next=busArray[i].scheduleHead;
            busArray[i].scheduleHead=newSchedule;

            printf("Schedule Added Successfully.\n");
            return;
        }
    }

    if(!found)
        printf("Bus Not Found.\n");
}
/* Add Passenger */

void addPassenger()
{
    int busID, found = 0;

    printf("Enter Bus ID: ");
    scanf("%d", &busID);

    for(int i = 0; i < busCount; i++)
    {
        if(busArray[i].busID == busID)
        {
            found = 1;

            int passengerCount = 0;
            Passenger *temp = busArray[i].passengerHead;

            while(temp != NULL)
            {
                passengerCount++;
                temp = temp->next;
            }

            if(passengerCount >= MAX_PASSENGERS)
            {
                printf("Cannot add more passengers. Bus is full.\n");
                return;
            }

            Passenger *newPassenger =
                (Passenger *)malloc(sizeof(Passenger));

            if(newPassenger == NULL)
            {
                printf("Memory Allocation Failed.\n");
                return;
            }

            printf("Enter Passenger Name: ");
            scanf(" %[^\n]", newPassenger->name);

            printf("Enter Passenger Age: ");
            scanf("%d", &newPassenger->age);

            newPassenger->next = busArray[i].passengerHead;
            busArray[i].passengerHead = newPassenger;

            printf("Passenger Added Successfully.\n");
            return;
        }
    }

    if(!found)
        printf("Bus Not Found.\n");
}


/* Display Buses */

void displayBuses()
{
    if(busCount == 0)
    {
        printf("No Buses Available.\n");
        return;
    }

    printf("\n===== BUS LIST =====\n");

    for(int i = 0; i < busCount; i++)
    {
        printf("Bus ID : %d\n", busArray[i].busID);
        printf("Driver : %s\n\n", busArray[i].driverName);
    }
}


/* Display Schedule */

void displaySchedule(int busID)
{
    for(int i = 0; i < busCount; i++)
    {
        if(busArray[i].busID == busID)
        {
            Schedule *temp = busArray[i].scheduleHead;

            printf("\nSchedule for Bus %d\n", busID);

            if(temp == NULL)
            {
                printf("No Schedule Available.\n");
                return;
            }

            while(temp != NULL)
            {
                printf("Destination : %s\n", temp->destination);
                printf("Time        : %s\n\n", temp->time);

                temp = temp->next;
            }

            return;
        }
    }

    printf("Bus Not Found.\n");
}


/* Display Passengers */

void displayPassengers(int busID)
{
    for(int i = 0; i < busCount; i++)
    {
        if(busArray[i].busID == busID)
        {
            Passenger *temp = busArray[i].passengerHead;

            printf("\nPassengers in Bus %d\n", busID);

            if(temp == NULL)
            {
                printf("No Passengers Available.\n");
                return;
            }

            while(temp != NULL)
            {
                printf("Name : %s\n", temp->name);
                printf("Age  : %d\n\n", temp->age);

                temp = temp->next;
            }

            return;
        }
    }

    printf("Bus Not Found.\n");
}
/* Delete Bus */

void deleteBus()
{
    int busID, found = 0;

    printf("Enter Bus ID to Delete: ");
    scanf("%d", &busID);

    for(int i = 0; i < busCount; i++)
    {
        if(busArray[i].busID == busID)
        {
            found = 1;

            freeSchedules(busArray[i].scheduleHead);
            freePassengers(busArray[i].passengerHead);

            for(int j = i; j < busCount - 1; j++)
            {
                busArray[j] = busArray[j + 1];
            }

            busCount--;

            printf("Bus Deleted Successfully.\n");
            return;
        }
    }

    if(!found)
        printf("Bus Not Found.\n");
}


/* Delete Schedule */

void deleteSchedule()
{
    int busID, found = 0;
    char destination[MAX_NAME_LENGTH];

    printf("Enter Bus ID: ");
    scanf("%d", &busID);

    for(int i = 0; i < busCount; i++)
    {
        if(busArray[i].busID == busID)
        {
            found = 1;

            printf("Enter Destination to Delete: ");
            scanf(" %[^\n]", destination);

            Schedule *current = busArray[i].scheduleHead;
            Schedule *prev = NULL;

            while(current != NULL)
            {
                if(strcmp(current->destination, destination) == 0)
                {
                    if(prev == NULL)
                        busArray[i].scheduleHead = current->next;
                    else
                        prev->next = current->next;

                    free(current);

                    printf("Schedule Deleted Successfully.\n");
                    return;
                }

                prev = current;
                current = current->next;
            }

            printf("Destination Not Found.\n");
            return;
        }
    }

    if(!found)
        printf("Bus Not Found.\n");
}


/* Delete Passenger */

void deletePassenger()
{
    int busID, found = 0;
    char name[MAX_NAME_LENGTH];

    printf("Enter Bus ID: ");
    scanf("%d", &busID);

    for(int i = 0; i < busCount; i++)
    {
        if(busArray[i].busID == busID)
        {
            found = 1;

            printf("Enter Passenger Name to Delete: ");
            scanf(" %[^\n]", name);

            Passenger *current = busArray[i].passengerHead;
            Passenger *prev = NULL;

            while(current != NULL)
            {
                if(strcmp(current->name, name) == 0)
                {
                    if(prev == NULL)
                        busArray[i].passengerHead = current->next;
                    else
                        prev->next = current->next;

                    free(current);

                    printf("Passenger Deleted Successfully.\n");
                    return;
                }

                prev = current;
                current = current->next;
            }

            printf("Passenger Not Found.\n");
            return;
        }
    }

    if(!found)
        printf("Bus Not Found.\n");
}


/* Free Schedule List */

void freeSchedules(Schedule *head)
{
    Schedule *temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}


/* Free Passenger List */

void freePassengers(Passenger *head)
{
    Passenger *temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}