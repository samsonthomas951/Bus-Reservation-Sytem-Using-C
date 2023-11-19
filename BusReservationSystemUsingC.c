#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

struct{
	int bid;
	char name[25];
	char location1[25];
	char location2[25];
	char timing[15];
	char date[15];
}bus1;

struct{
	int busno,ID;
	int Maleadult;
	int Femaleadult;
	int children;
	char date[25];
	char time[25];		
}booking1;

struct{
	int sno,busid;
}seat;

#define NUM_ROWS 12
#define NUM_COLS 4
#define MAX_SEATS 48
#define FILENAME "booking_ids.txt"
#define MAX_STR_LEN 10
#define NUM_STRINGS 5

struct Bus {
    int uniqueNumber;
    char numberPlate[10];
    char departureLocation[20];
    char destination[20];
    char busTiming[10];
    char journeyDate[12];
    char busSeatingChart[NUM_ROWS][NUM_COLS];
};

char ch[32][100]={'\0'};
char name[32][100]={'\0'};
char number[32][2]={'\0'};
int num1[32]={0},busno,anumber;
char info[500];
char getid[32];
char bank_name[100];

void Add();
void bus();	//for list of bus
void booking();	//for booking the tickets
void status();	//for printing the status by user input
void cancel();
void login();
void delete();
void printBusDetails(struct Bus bus);
void loadBusData(struct Bus buses[], int *numBuses);
void displayBusSummary(const char *filename);


FILE *busrecord;
FILE *busbooking;
FILE *busseat;
FILE *fp2;
FILE *temp2;
FILE *seats;


int main()
	{
		login();	
    	int num,i;    
        struct Bus buses[100];
        int numBuses = 0;
    	do
		{
    	system("cls");
    	{
			time_t t;
			time(&t);
			printf("\n\t\t\t\t\tToday Date and Time is %s",ctime(&t));
		}
   		printf("\n============================================ WELCOME TO BUS RESERVATION SYSTEM ========================================");
   		printf("\n\t\t\t\t\t======== WELCOME TO ROYAL TRANSPORT ======== ");
    	printf("\n\t\t\t\t\t-------------------------------------------\n");
		printf("\t\t\t\t\t| S.No | Setup Process                    |\n");
    	printf("\t\t\t\t\t-------------------------------------------\n");
    	printf("\t\t\t\t\t| [1]  | => Add Bus Details		  |\n");
    	printf("\t\t\t\t\t| [2]  | => View Bus Details		  |\n");
    	printf("\t\t\t\t\t| [3]  | => Searching and Booking Ticket  |\n");
    	printf("\t\t\t\t\t| [4]  | => Bus Status Board		  |\n");
    	printf("\t\t\t\t\t| [5]  | => Cancel Booking		  |\n");
        printf("\t\t\t\t\t| [6]  | => Delete Buses schedule	  |\n");
    	printf("\t\t\t\t\t| [7]  | => View Bus History		  |\n");
        printf("\t\t\t\t\t| [8]  | => Exit		          |\n");
    	printf("\t\t\t\t\t-------------------------------------------\n");
    	printf("=======================================================================================================================\n\n");
    	printf("\t\t\tEnter Your Choice:: ");
    	scanf("%d",&num);
    	switch(num)
    	{
    		case 1:
        		Add();
        		break;
    		case 2:
        		bus();  
        		break;
    		case 3:
        		booking();
        		break;
    		case 4:
        		status();
        		break;
    		case 5:
        		cancel();	
    			break;
        case 6:
            delete();
            break;
        case 7:
            displayBusSummary("busbooking.txt");
            break;
    	}
    	getch();
		}
		while(num != 8);
    	printf("\t----------------------------------------------------------------------------------------------------------\n");
    	printf("\t\t\t\t\tThank You For Using This System\t\t\t\t\t\t\n");
    	printf("\t----------------------------------------------------------------------------------------------------------\n");
    	return 0;
	}

int generateBookingID() {
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int maxID = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        int id;
        if (sscanf(line, "%d", &id) == 1) {
            if (id > maxID) {
                maxID = id;
            }
        }
    }
    int newID = maxID + 1;
    fseek(file, 0, SEEK_END);
    fprintf(file, "%d\n", newID);
    fclose(file);

    return newID;
}

void login()
{
    int a = 0, i = 0;
    char uname[10], c = ' ';
    char pword[10], code[10];
    char user[10] = "user";
    char pass[10] = "pass";
    
    do
    {
        system("cls");
        printf("\n  =========================  LOGIN FORM  =========================  ");
        printf("\n\t\t==== WELCOME TO ROYAL TRANSPORT ====  ");
        printf("\n\tNOTE : Only Admin / User can Login in this Page.....");
        printf(" \n\n\t\tENTER USERNAME: ");
        scanf("%s", uname);
        printf(" \t\tENTER PASSWORD: ");
        
        while (i < 10)
        {
            pword[i] = getch();
            c = pword[i];
            if (c == 13)
                break;
            else
                printf("*");
            i++;
        }
        pword[i] = '\0';
        i = 0;
        
        if (strcmp(uname, "user") == 0 && strcmp(pword, "pass") == 0)
        {
            printf("  \n\n\n\t\t\tWELCOME TO OUR SYSTEM !!!! LOGIN IS SUCCESSFUL");
            printf("\n\n\n\t\t\t\tPress any key to continue...");
            getch(); // holds the screen
            break;
        }
        else
        {
            printf("\n\n\n\t\t\tSORRY !!!!  LOGIN IS UNSUCCESSFUL");
            a++;
            getch(); // holds the screen
        }
    } while (a <= 2);
    
    if (a > 2)
    {
        printf("\nSorry you have entered the wrong username and password for three times!!! Program will now exit.");
        getch();
        exit(0); // This will terminate the program
    }
    else
    {
        system("cls");
    }
}

void Add()
{
    int i;
    busrecord = fopen("busrecord.txt","a+");
    system("cls");
    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n");
    printf("********************************************* ADD BUS SCHEDULE *************************************************\n");
    printf("\n\t\tEnter bus number eg 1234: ");
	scanf("%d",&bus1.bid);
    printf("\t\tEnter numberplate eg KAB123C :");
    scanf("%s",bus1.name);
    printf("\t\tEnter departure location :");
    scanf("%s",bus1.location1);
    printf("\t\tEnter destination location :");
    scanf("%s",bus1.location2);
    printf("\t\tEnter Bus Timing :");
    scanf("%s",bus1.timing);
    printf("\t\tEnter Date :");
    scanf("%s",bus1.date);
    
    fprintf(busrecord,"\n%d %s %s %s %s %s",bus1.bid,bus1.name,bus1.location1,bus1.location2,bus1.timing,bus1.date);
    fclose(busrecord);
    printf("\n\t\t (' ' ) A New Bus has been Added Successfully...");
}

void bus()
{
    system("cls");
    printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
    printf("*********************************************** BUS SCHEDULES *********************************************************");
	struct Bus buses[100]; 
    int numBuses = 0;
    loadBusData(buses, &numBuses);
    while (1) {
        printf("\n\t\t\t\tList of Buses:\n");
        for (int i = 0; i < numBuses; i++) {
            printf("\t\t\t%d. %s to %s, Timing: %s, Date: %s\n",
                   buses[i].uniqueNumber,
                   buses[i].departureLocation,
                   buses[i].destination,
                   buses[i].busTiming,
                   buses[i].journeyDate);
        }
        printf("\n*********************************************************************************************************************");
	    printf("\n\t\tEnter -1  to continue: ");
    
        int busNumber;
        scanf("%d", &busNumber);

        if (busNumber == -1) {
            break; 
        }
    system("cls");
    }
	
}

void loadBusData(struct Bus buses[], int *numBuses) {
    FILE *file = fopen("busrecord.txt", "r");
    if (file) {
         *numBuses = 0; // Initialize the number of buses
        while (*numBuses < 100 && fscanf(file, "%d %s %s %s %s %s",
               &buses[*numBuses].uniqueNumber,
               buses[*numBuses].numberPlate,
               buses[*numBuses].departureLocation,
               buses[*numBuses].destination,
               buses[*numBuses].busTiming,
               buses[*numBuses].journeyDate) == 6) {


            // Initialize the seating chart for each bus
            for (int i = 0; i < NUM_ROWS; i++) {
                for (int j = 0; j < NUM_COLS; j++) {
                    fscanf(file, " %c", &buses[*numBuses].busSeatingChart[i][j]);
                }
            }

            // Consume the newline character at the end of the line
            fscanf(file, "%*c");

            (*numBuses)++;
        }

        fclose(file);
    }
}




void printBusDetails(struct Bus bus) {
    printf("Unique Number: %d\n", bus.uniqueNumber);
    printf("Number Plate: %s\n", bus.numberPlate);
    printf("Departure Location: %s\n", bus.departureLocation);
    printf("Destination: %s\n", bus.destination);
    printf("Bus Timing: %s\n", bus.busTiming);
    printf("Journey Date: %s\n", bus.journeyDate);
}

// Function to print the seating chart of a bus
void printBusSeatingChart(struct Bus bus) {
    printf("\t\t\t\tBus Seating Chart:\n");
    printf("\t\t\t\t  1   2   3   4\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        printf("\t\t\t\t%c ", 'A' + i);
        for (int j = 0; j < NUM_COLS; j++) {
            if (i == 0 && j < 2) {
                printf("[ST]");
            } else if (bus.busSeatingChart[i][j] == 'X') {
                printf("[X] ");
            } else {
                printf("[ ] ");
            }
        }
        printf("\n");
    }
}
// Function to save bus data to a file
void saveBusData(struct Bus buses[], int numBuses) {
    FILE *file = fopen("busrecord.txt", "w");
    if (file) {
        for (int i = 0; i < numBuses; i++) {
            fprintf(file, "%d %s %s %s %s %s\n",
                    buses[i].uniqueNumber,
                    buses[i].numberPlate,
                    buses[i].departureLocation,
                    buses[i].destination,
                    buses[i].busTiming,
                    buses[i].journeyDate);

            // Save the seating chart for each bus
            for (int j = 0; j < NUM_ROWS; j++) {
                for (int k = 0; k < NUM_COLS; k++) {
                    fprintf(file, "%c ", buses[i].busSeatingChart[j][k]);
                }
                fprintf(file, "\n");
            }
        }
        fclose(file); // Close the file after writing
    } else {
        printf("Error opening file for writing.\n");
    }
}

void saveSeatingPositions(int busno, int ID, char (*seatingPositions)[3], int totpass) {
    FILE *fp;
    fp = fopen("seatingPositions.txt", "a+");

    fprintf(fp, "%d\t%d\t", busno, ID);
    for (int i = 0; i < totpass; i++) {
        fprintf(fp, "%s\t", seatingPositions[i]);
    }
    fprintf(fp, "\n");

    fclose(fp);
}





void booking() {
    struct Bus buses[100]; 
    int numBuses = 0; // Number of buses loaded from file
    int Found=0,Found1=0,Found2=0,Target,getid,getid2=0,tempid=0,conti,n,Maleadult, Femaleadult,children,bank_name, payment_name, price, gst=0, total=0,i=0, j,amt=500,totamt,bookedbusno;
    char cvv_number[4],a[20];
    // Load bus data from the file
    loadBusData(buses, &numBuses);

    while (1) {
        // Display the list of buses with their details
        system("cls");
        printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
        printf("*********************************************** BUS BOOKING *********************************************************");
        printf("\n\t\t\t\tList of Buses:\n");
        for (int i = 0; i < numBuses; i++) {
            printf("\t\t\t%d. %s to %s, Timing: %s, Date: %s\n",
                   buses[i].uniqueNumber,
                   buses[i].departureLocation,
                   buses[i].destination,
                   buses[i].busTiming,
                   buses[i].journeyDate);
        }

        printf("\n\n\t\t\tEnter the unique number of the bus to select (or -1 to exit): ");
        int busNumber;
        scanf("%d", &busNumber);

        if (busNumber == -1) {
            break; // Exit the program
        }

        int selectedBusIndex = -1; // Index of the currently selected bus

        // Find the selected bus by its unique number
        for (int i = 0; i < numBuses; i++) {
            if (buses[i].uniqueNumber == busNumber) {
                selectedBusIndex = i;
                break;
            }
        }

        if (selectedBusIndex == -1) {
            printf("\t\t\tBus with unique number %d not found.\n", busNumber);
        } else {
            system("cls");
            printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
            printf("*********************************************** BUS BOOKING *********************************************************");
            printf("\n\t\t\t\tBus Details:\n");
            printBusDetails(buses[selectedBusIndex]);
            busbooking = fopen("busbooking.txt","r");
            int getid = generateBookingID();
            printf("\tYour booking ID is : %d",getid);
           
            tempid=tempid+getid;
            while(!feof(busbooking) && Found2==0){
				fscanf(busbooking,"%d %d %s %s %d %d %d",&booking1.busno,&booking1.ID,booking1.date,booking1.time,&booking1.Maleadult,&booking1.Femaleadult,&booking1.children);
				if(getid != booking1.ID){
			     	Found2 = 0;
				}
				else{
				Found2 = 1;
		    }	
            }		
            if(Found2){
                    printf("Sorry!!......The Bookinng ID already exists....\nPlease try another ID :");
                        scanf("%d",&getid2);
                        tempid = getid2;
            }
            else if(!Found2){
                tempid = tempid;
            }	
            fclose(busbooking);
            
           
            system("cls");
            printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
            printf("*********************************************** BUS BOOKING *********************************************************");
            printf("\n\t\t\t\tBus Details:\n");
            printBusDetails(buses[selectedBusIndex]);
            printf("\n");
            printf("\tEnter No of Adult Male	: ");
			scanf("%d",&booking1.Maleadult);
			printf("\tEnter No of Adult Female	: ");
			scanf("%d",&booking1.Femaleadult);	
			printf("\tEnter No of Children : ");
			scanf("%d",&booking1.children);
			strcpy(booking1.date,buses[i].journeyDate);
			strcpy(booking1.time,buses[i].busTiming);
            
            booking1.busno = busNumber;
			booking1.ID = tempid;
            
			busbooking = fopen("busbooking.txt","a+");
			fprintf(busbooking,"\n%d\t%d\t%s\t%s\t%d\t%d\t%d\t",booking1.busno,booking1.ID,booking1.date,booking1.time,booking1.Maleadult,booking1.Femaleadult,booking1.children);
			fclose(busbooking);  
            int totpass = (booking1.Maleadult + booking1.Femaleadult + booking1.children);
            // Allocate memory for seatingPositions array
            char (*seatingPositions)[3] = malloc(totpass * sizeof(*seatingPositions));
            int seatsSelected = 0;
            while (1) {
                //system("cls");
                // Display the seating chart for the selected bus
                printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
                printf("*********************************************** BUS BOOKING *********************************************************");
                printf("\n");
                printBusSeatingChart(buses[selectedBusIndex]);

                printf("\t\t\tEnter row and column (e.g., A2) or -1 to go back to the bus selection: ");
                char input[10];
                scanf("%s", input);

                if (strcmp(input, "-1") == 0) {
                    // Go back to bus selection
                    break;
                }

                int row, col;
                row = input[0] - 'A';
                col = input[1] - '1';

                if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) {
                    printf("\t\t\tInvalid row or column. Please try again.\n");
                    continue;
                }

                if (row == 0 && col < 2) {
                    printf("\t\t\tStaff seat. Please choose another seat.\n");
                } else if (buses[selectedBusIndex].busSeatingChart[row][col] == 'X') {
                    printf("\t\t\tSeat already reserved. Please choose another seat.\n");
                } else {
                    buses[selectedBusIndex].busSeatingChart[row][col] = 'X';
                    printf("\t\t\tSeat reserved successfully!\n");
                    saveBusData(buses, numBuses);
                    // Save the selected seat position
                    sprintf(seatingPositions[seatsSelected++], "%c%d", 'A' + row, col + 1);

                    // If the user has selected totpass seats, save the seating positions and break the loop
                    if (seatsSelected == totpass) {
                        saveSeatingPositions(booking1.busno, booking1.ID, seatingPositions, totpass);
                        break;
                    }
                }
            }
            //clearing the allocated memory
            free(seatingPositions);
            

            //system("cls");
            printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
            printf("*********************************************** BUS BOOKING *********************************************************\n\n");
            printf("~---------------------------------------------------~\n");
			printf("| Search And Book Tickets                          |\n");
			printf("|---------------------------------------------------|\n");
			printf("| Booking ID : %d                                    \n", getid);
			printf("| From :         |    %s                          \n", buses[i].departureLocation);
			printf("| To   :         |    %s        \n", buses[i].destination);
            printf("|---------------------------------------------------|\n");
            printf("| Journey Date : |%s    |Time:%s             \n", buses[i].journeyDate, buses[i].busTiming);
            printf("|---------------------------------------------------|\n");
            printf("| Adult:         | Male/s: %d        Female/s: %d   |\n", booking1.Maleadult, booking1.Femaleadult);
            printf("| Children:      |                 %d                |\n", booking1.children);
            printf("| Unique Bus No|%d          Bus Noplate|           |\n",buses[i].uniqueNumber);
            printf("|---------------------------------------------------|\n");
            printf("Press any key to continue...");
            getch();
        
            system("cls");
		    printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n");//for selecting coach
            printf("*********************************************** BUS BOOKING *********************************************************");
            printf("\n\n\n\t\t\t\t\t Bill");
            printf("\n\t\t*******************************************");
            printf("\n\t\tCost of a ticket is KSh. 1500/=");
            totamt = 1500 * (booking1.Maleadult + booking1.Femaleadult + booking1.children);
            printf("\n\t\tEnter the Bank Name : ");
            char bank_name[100];
            char a[100];
            scanf("%s", bank_name);
            printf("\n\t\t|*******************************************\n");
            printf("\t\t|Enter the Name of Card Holder: ");
            scanf("%s",a);
            printf("\t\t|Total Amount : %d",totamt);
            printf("\n\t\t|Enter CVV no:");
            char cvv_number[4];
            for (j = 0; j < 4;) {
                char ch = getch();
                if (ch == '\r') { 
                    break; 
                }
                if (ch >= '0' && ch <= '9') { 
                    cvv_number[j++] = ch;
                    printf("*");
                }
            }
            cvv_number[4] = '\0';
            while (getchar() != '\n');
            int cvv_int;
            sscanf(cvv_number, "%d", &cvv_int);
            printf("\t\t|\n\n*******************************************\n");
            gst = ((totamt/100)*5);
            total = totamt + gst;
            system("cls");
            printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
            printf("*********************************************** BUS BOOKING *********************************************************\n\n");
            printf("*********************************************** RECEITPT *********************************************************");
            printf("\n\n\t\t Billing Address Payment Receipt ");
            printf("\n\t\t*******************************************");
            printf("\n\t\t Name		Price		GST		TOTAL ");
            printf("\n\t\t %s		%d		 %d		 %d", a,totamt,gst,total);
            printf("\n\t\t*******************************************\n");
            printf("\n\t\t Thank you! Visit it again ! Have a Safe journey! \n");
            printf("\n\t\t\t\t // POWERED BY\n");
            printf("\t\t\t\t  BILLDESK Ltd..,\n");

            // Wait for user input before returning to the bus selection screen
            printf("\n\t\tPress any key to continue...");
            getch();
            
        }
    }
}
void status()
{
	struct Bus buses[100]; 
    int numBuses = 0;
    loadBusData(buses, &numBuses);
    while (1) {
        system("cls");
        printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
        printf("********************************************* BUS BOARD STATUS *********************************************************\n\n");
        printf("\t\t\t\t\tList of Buses:\n");
        for (int i = 0; i < numBuses; i++) {
            printf("\t\t\t%d. %s to %s, Timing: %s, Date: %s\n",
                   buses[i].uniqueNumber,
                   buses[i].departureLocation,
                   buses[i].destination,
                   buses[i].busTiming,
                   buses[i].journeyDate);
        }

        printf("\n\t\t\tEnter the unique number of the bus to select (or -1 to exit): ");
        int busNumber;
        scanf("%d", &busNumber);

        if (busNumber == -1) {
            break; 
        }

        int selectedBusIndex = -1; 
        for (int i = 0; i < numBuses; i++) {
            if (buses[i].uniqueNumber == busNumber) {
                selectedBusIndex = i;
                break;
            }
        }

        if (selectedBusIndex == -1) {
            printf("\t\t\tBus with unique number %d not found.\n", busNumber);
        } else {
            system("cls");
            printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
            printf("********************************************* BUS BOARD STATUS *********************************************************\n\n");
            printf("\n\t\t\t\tBus Details:\n");
            printBusDetails(buses[selectedBusIndex]);
            printf("\n");
        }
            while (1) {
            printf("\n");
            printBusSeatingChart(buses[selectedBusIndex]);
            printf("\t\t\tEnter -1 to go back to the bus selection: ");
            char input[10];
            scanf("%s", input);
            if (strcmp(input, "-1") == 0) {
                // Go back to bus selection
                break;
            }
        }

    }
   
 
}

void removeSeats(struct Bus buses[], int numBuses, int selectedBusIndex, int userID, int tot1) {
    FILE *seatingFile = fopen("seatingPositions.txt", "r");
    if (!seatingFile) {
        printf("Error opening seatingPositions.txt for reading.\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), seatingFile)) {
        int fileUserID;
        sscanf(line, "%*d %d", &fileUserID);
        if (fileUserID == userID) {
            char strings[NUM_STRINGS][MAX_STR_LEN];
            int val1, val2;
            sscanf(line, "%d %d %s %s %s %s %s ", &val1, &val2, strings[0], strings[1], strings[2], strings[3], strings[4]);
            for (int i = 0; i < tot1; ++i) {
                printf("str%d: %s\n", i + 1, strings[i]);
                int row = strings[i][0] - 'A';
                int col = strings[i][1] - '1';
                if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) {
                    printf("\t\t\tInvalid seating position found in the file. Please try again.\n");
                    fclose(seatingFile);
                    continue;
                }
                if (row == 0 && col < 2) {
                    printf("\t\t\tCannot remove staff seat. Please choose another seat.\n");
                } else if (buses[selectedBusIndex].busSeatingChart[row][col] != 'X') {
                    printf("\t\t\tSeat is not reserved. Please choose another seat.\n");
                } else {
                    buses[selectedBusIndex].busSeatingChart[row][col] = ' ';
                    printf("\t\t\tSeat removed successfully!\n");
                    saveBusData(buses, numBuses); // Save the updated seating chart
                }
            }
            fclose(seatingFile);
            return;
        }
        
    }
    printf("\t\t\tUserID not found in seatingPositions.txt. Please try again.\n");
    fclose(seatingFile);
}

void cancel()
{  
    struct Bus buses[100]; 
    int numBuses = 0;
 	int seat_no,i,j,tot1,totcancel,Found,Target4;
    int selectedBusIndex;
 	char numstr[100],tempstr2[15]="number",tempstr1[15]="status";
    loadBusData(buses, &numBuses);
    system("cls");
    printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
    printf("********************************************* CANCEL TICKETS *********************************************************\n\n");
 	printf("\n\t\t\tEnter Booking ID :");
 	scanf("%d",&Target4);
 	fp2=fopen("fp2.txt","w");
    if((temp2=fopen("busbooking.txt","r"))==NULL)
    { 
		printf(" ! The file is empty...\n\n");
		getch();
	}
    else
    { 
        while(!feof(temp2)) { 
            fscanf(temp2,"%d %d %s %s %d %d %d",&booking1.busno,&booking1.ID,booking1.date,booking1.time,&booking1.Maleadult,&booking1.Femaleadult,&booking1.children); 

            if(Target4==booking1.ID) { 
                Found=1; 
            } else { 
                Found=0; 
            } 

            if(Found) { 
                for (int i = 0; i < numBuses; i++) {
                    if (buses[i].uniqueNumber == booking1.busno) {
                        selectedBusIndex = i;
                        break;
                    }
                }

                int userID = booking1.ID; 

                tot1 = booking1.Maleadult + booking1.Femaleadult + booking1.children; 
                removeSeats(buses, numBuses, selectedBusIndex,userID,tot1); 
                for (i=0;i<tot1;i++) { 
                    if(booking1.children>0) { 
                        booking1.children--; 
                    } else { 
                        if(booking1.Femaleadult>0) { 
                            booking1.Femaleadult--; 
                        } else { 
                            booking1.Maleadult--; 
                        } 
                    } 
                } 

                fprintf(fp2,"\n%d\t%d\t%s\t%s\t%d\t%d\t%d\t",booking1.busno,booking1.ID,booking1.date,booking1.time,booking1.Maleadult,booking1.Femaleadult,booking1.children); 
                break; 
            } else if(!Found) { 
                fprintf(fp2,"\n%d\t%d\t%s\t%s\t%d\t%d\t%d\t",booking1.busno,booking1.ID,booking1.date,booking1.time,booking1.Maleadult,booking1.Femaleadult,booking1.children); 
            } 

            if(feof(temp2)) { 
                break; 
            } 
        } 

        fclose(temp2); 
        fclose(fp2); 
        fclose(busbooking); 

        remove("busbooking.txt"); 
        rename("fp2.txt","busbooking.txt"); 

        printf("\n======================================================================================================\n"); 
        printf("\t\t\t\tKsh. %d has been Returned\t\t\t\n",1500*tot1); 
        printf("======================================================================================================\n"); 
    } 
}

void delete(){
    struct Bus buses[100]; 
    int numBuses = 0;
    loadBusData(buses, &numBuses);
    while (1) {
        system("cls");
        printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
        printf("********************************************* CANCEL TICKETS *********************************************************\n\n");
        printf("\t\t\t\tList of Buses:\n");
        for (int i = 0; i < numBuses; i++) {
            printf("\t\t\t%d. %s to %s, Timing: %s, Date: %s\n",
                   buses[i].uniqueNumber,
                   buses[i].departureLocation,
                   buses[i].destination,
                   buses[i].busTiming,
                   buses[i].journeyDate);
        }
        printf("\n*********************************************************************************************************************");
        printf("\n\t\tEnter the ID of bus that you want to Delete (-1 to cancel): ");

        int busNumber;
        scanf("%d", &busNumber);

        if (busNumber == -1) {
            break; 
        }

        int indexToDelete = -1;
        for (int i = 0; i < numBuses; i++) {
            if (buses[i].uniqueNumber == busNumber) {
                indexToDelete = i;
                break;
            }
        }

        if (indexToDelete != -1) {  
            printf("Are you sure you want to delete the following bus?\n");
            printf("%d. %s to %s, Timing: %s, Date: %s\n",
                   buses[indexToDelete].uniqueNumber,
                   buses[indexToDelete].departureLocation,
                   buses[indexToDelete].destination,
                   buses[indexToDelete].busTiming,
                   buses[indexToDelete].journeyDate);
            printf("Enter 'y' to confirm deletion, or any other key to cancel: ");
            
            char confirmation;
            scanf("%c", &confirmation);
            
            if (confirmation == 'y' || confirmation == 'Y') {
                // Shift the remaining buses to fill the gap left by the deleted bus
                for (int i = indexToDelete; i < numBuses - 1; i++) {
                    buses[i] = buses[i + 1];
                }
                (numBuses)--;
                FILE *file = fopen("busrecord.txt", "w");
                if (file) {
                    for (int i = 0; i < numBuses; i++) {
                        fprintf(file, "%d %s %s %s %s %s\n",
                                buses[i].uniqueNumber,
                                buses[i].numberPlate,
                                buses[i].departureLocation,
                                buses[i].destination,
                                buses[i].busTiming,
                                buses[i].journeyDate);
                        
                        // Write the seating chart for each bus
                        for (int j = 0; j < NUM_ROWS; j++) {
                            for (int k = 0; k < NUM_COLS; k++) {
                                fprintf(file, " %c", buses[i].busSeatingChart[j][k]);
                            }
                        }
                        fprintf(file, "\n");
                    }
                    fclose(file);
                } else {
                    printf("Error opening the file for writing.\n");
                }
                printf("Bus with Unique Number %d has been deleted.\n", busNumber);
                // Optionally, you can save the updated bus data back to the file here
            } else {
                printf("Deletion canceled.\n");
            }
        } else {
            printf("Bus with Unique Number %d not found.\n", busNumber);
        }

    }
}




void displayBusSummary(const char *filename) {
    int busID;
    struct Bus buses[100]; 
    int numBuses = 0;
    loadBusData(buses, &numBuses);

    while (1) {
        // Clear the screen before displaying the list of buses
        system("cls");

        // Display the list of buses with their details
        printf("=========================================== BUS RESERVATION SYSTEM ==================================================\n\n");
        printf("*********************************************** BUS HISTORY *********************************************************");
        printf("\n\t\t\t\tList of Buses:\n");
        for (int i = 0; i < numBuses; i++) {
            printf("\t\t\t%d. %s to %s, Timing: %s, Date: %s\n",
                   buses[i].uniqueNumber,
                   buses[i].departureLocation,
                   buses[i].destination,
                   buses[i].busTiming,
                   buses[i].journeyDate);
        }
        printf("\n*********************************************************************************************************************");
        printf("\n\t\tEnter the ID of bus that you want view history of (-1 to cancel): ");
        // int busNumber;
        scanf("%d", &busID);
        getchar();

        if (busID == -1) {
            break; // Exit the program
        }

        int selectedBusIndex = -1; // Index of the currently selected bus

        // Find the selected bus by its unique number
        for (int i = 0; i < numBuses; i++) {
            if (buses[i].uniqueNumber == busID) {
                selectedBusIndex = i;
                break;
            }
        }

        if (selectedBusIndex == -1) {
            printf("\t\t\tBus with unique number %d not found.\n", busID);
        } else {
            FILE *busbooking = fopen("busbooking.txt", "r");
            if (busbooking == NULL) {
                printf("Error opening file\n");
                exit(1);
            }

            int totalChildren = 0, totalMaleAdults = 0, totalFemaleAdults = 0, onboardtotal = 0,totalseats=46,emptyseats=0;
            int busNo, ID, Maleadult, Femaleadult, children;
            char date[11], time[8];
            bool found = false;
            char foundDate[11], foundTime[8]; // Declare foundDate and foundTime here

            while (fscanf(busbooking, "%d\t%d\t%s\t%s\t%d\t%d\t%d", &busNo, &ID, &date, &time, &Maleadult, &Femaleadult, &children) == 7) {
                if (busNo == busID) {
                    totalChildren += children;
                    totalMaleAdults += Maleadult;
                    totalFemaleAdults += Femaleadult;
                    if (!found) {
                        strcpy(foundDate, date);
                        strcpy(foundTime, time);
                        found = true;
                    }
                }
            }

            fclose(busbooking);
            system("cls");
            onboardtotal = totalChildren+totalFemaleAdults+totalMaleAdults;
            emptyseats = totalseats-onboardtotal;
            printf("=========================================== BUS RESERVATION SYSTEM ============================================\n\n");
            printf("************************************************ BUS HISTORY *************************************************\n");
            printf("\n");
            printBusSeatingChart(buses[selectedBusIndex]);
            printf("\t|__________________________________________________________________________|\n");
            printf("\n\n\n");
            printf("\t\t\t\t|Summary for Bus ID %d:\t\t|\n", busID);
            printf("\t\t\t\t|_______________________________________|\n");
            printf("\t\t\t\t| Date: %s \t\t\t|\n", foundDate); 
            printf("\t\t\t\t| Time: %s \t\t\t\t|\n", foundTime);
            printf("\t\t\t\t| Total Children: %d \t\t\t|\n", totalChildren);
            printf("\t\t\t\t| Total Adult Males: %d \t\t\t|\n", totalMaleAdults);
            printf("\t\t\t\t| Total Adult Females: %d \t\t|\n", totalFemaleAdults);
            printf("\t\t\t\t| Total on board: %d \t\t\t|\n",onboardtotal);
            printf("\t\t\t\t| Empty seats: %d\t\t\t|\n",emptyseats);
            printf("\t\t\t\t|_______________________________________|\n");
            printf("\t\t\t\t\t Press any key to continue\n");
            getchar();
        }
    }
}
