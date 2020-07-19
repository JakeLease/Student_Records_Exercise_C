#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//student info typedef struct
typedef struct {
	uint32_t rollNumber;
	uint8_t studentSemister;
	uint8_t dob[10];
	uint8_t studentMajor[50];
	uint8_t studentName[30];
}STUDENT_INFO_t;

// function prototypes
void display_all_records(STUDENT_INFO_t *pBaseAddyofRecords, uint32_t max_records);
void display_current_records(STUDENT_INFO_t *pBaseAddyofRecords, uint32_t current_record);
int8_t add_new_record(STUDENT_INFO_t *pBaseAddyofRecords, uint32_t current_record);
int8_t delete_record(STUDENT_INFO_t *pBaseAddyofRecords, uint8_t max_records);
int8_t check_duplicate_record(STUDENT_INFO_t *pBaseAddyofRecords, uint32_t max_records, uint32_t rollNumber);
void display_menu(void);
void decode_menu_option(int8_t option);
void wait_for_input(void);
void clear_input();


// this is a macro, at the time of doing this i haven't learned it completely
// using it to set a variable for the student struct
#define max_record_size 10


// GLobal variable for students info in order to have several students
STUDENT_INFO_t students[max_record_size];




int main(){
	while(1){
		display_menu();
		wait_for_input();
	}

	return 0;
}




// displays menu for user to pick from
void display_menu(){
	uint8_t option;
	printf("Student Record Management Program\n");
	printf("Display all Records\t-->1\n");
	printf("Add New Record\t\t-->2\n");
	printf("Delete a Record\t\t-->3\n");
	printf("Exit Application\t-->0\n");
	printf("Enter Your Option Here:");
	scanf("%c", &option);
	getchar();
	printf("\n");
	decode_menu_option(option);
}

// this will do our switching from the menu
void decode_menu_option(int8_t option){
	// switch to pick option
		switch(option){
		// case to exit
		case '0':
			printf("You are Exiting Thank you\n");
			wait_for_input();
			exit(0);
			break;
		// case to display all records
		case '1':
			display_all_records(students, max_record_size);
			break;
	//case to add a record
		case '2':
			if(add_new_record(students, max_record_size) == -1){
				printf("The Student Records Database is full\n");
			}
			break;

		// case for deleteing
		case '3':
			if (delete_record(students, max_record_size) == -1){
				printf("An Error has Accorded. No Record Deleted\n");
			}
			else{
				printf("A Record was Deleted\n");
			}
		}
}


// looping through the student structure array sent in and using i to
// go through the pointer and use the values given
void display_all_records(STUDENT_INFO_t *pBaseAddyofRecords, uint32_t max_records){

	// we need to check to see if its empty or not
	uint8_t empty_check = 0;

	// increase empty_check by 1 is the roll number is 0
	// if roll number is 0 then it is empty or was deleted
	for(uint8_t i = 0; i < max_records; i++){
		if (pBaseAddyofRecords[i].rollNumber == 0){
			empty_check++;
		}
	}

	//  if empty_check equal max records then it is empty and it prints and returns to menu
	if(empty_check == max_records){
		printf("There are no current records please enter one\n");
		return;
	}

	for(uint32_t i = 0; i < max_records; i++){
		if(pBaseAddyofRecords[i].rollNumber == 0){

		}
		else{
			printf("The Record at Position %d:\n", i);
			// can print a struct array using this way of the next one
			printf("The Roll Number of the Student is: %d\n", (pBaseAddyofRecords + i)->rollNumber);
			// can also access struct this way
			printf("The Major of the Student is: %s\n", pBaseAddyofRecords[i].studentMajor);
			printf("The Current Semester of the Student is: %c\n", (pBaseAddyofRecords + i)->studentSemister);
			printf("The Date of Birth of the Student is: %s\n",pBaseAddyofRecords[i].dob);
			printf("The Name of the Student is: %s\n\n", (pBaseAddyofRecords + i)->studentName);
		}

	}
}

// using this function to just print one of the values of the array
void display_current_records(STUDENT_INFO_t *pBaseAddyofRecords, uint32_t current_record){
	printf("The %d record is:\n", current_record);
	printf("The Roll Number of the Student is: %d\n",pBaseAddyofRecords[current_record].rollNumber);
	printf("The Major of the Student is: %s\n", (pBaseAddyofRecords + current_record)->studentMajor);
	printf("The Current Semester of the Student is: %c\n", pBaseAddyofRecords[current_record].studentSemister);
	printf("The Date of Birth of the Student is: %s\n", (pBaseAddyofRecords + current_record)->dob);
	printf("The Name of the Student is: %s\n\n", pBaseAddyofRecords[current_record].studentName);
}

// function to add a student record
int8_t add_new_record(STUDENT_INFO_t *pBaseAddyofRecords, uint32_t max_records){
	// loop through roll numbers to find an empty one
	uint8_t current_record = 0;

	for(uint8_t i = 0; i < max_records; i++){
		if(pBaseAddyofRecords[i].rollNumber == 0){
			current_record = i;
			i = max_records;
		}
		else{
		current_record++;
		}
	}

	// if this is true then return -1 as error code because array is full
	if (current_record == max_records){
				return -1;
			}

	// have a loop that while the record we are going for has a roll number that is 0, then this while will repeat
	// this is so if they enter an already using roll number then we can keep asking them
	while(pBaseAddyofRecords[current_record].rollNumber == 0){
		begining:
		printf("Please Enter the Student Roll Number: ");
		// temp variable used to test the roll number
		uint32_t preRollNumber = 0;
		scanf("%d", &preRollNumber);
		getchar();
		if (check_duplicate_record(pBaseAddyofRecords, max_records, preRollNumber) == -1){
			preRollNumber = 0;
			goto begining;
		}
		else{
			pBaseAddyofRecords[current_record].rollNumber = preRollNumber;
		}

		printf("Please Enter the Students Major: ");
		scanf("%[^\n]s", pBaseAddyofRecords[current_record].studentMajor);
		getchar();

		printf("Please Enter the Students Current Semester Number: ");
		scanf("%c", &pBaseAddyofRecords[current_record].studentSemister);
		getchar();

		printf("Please Enter the Students Date of Birth using Format XX/XX/XXXX: ");
		scanf("%[^\n]s", pBaseAddyofRecords[current_record].dob);
		getchar();

		printf("Please Enter the Students Students Name: ");
		scanf("%[^\n]s", pBaseAddyofRecords[current_record].studentName);

		return 0;



	}

		return 0;
}

// check for a duplicate roll number
int8_t check_duplicate_record(STUDENT_INFO_t *pBaseAddyofRecords, uint32_t max_records, uint32_t rollNumber){
	for(uint8_t i = 0; i < max_records; i++){
		if(pBaseAddyofRecords[i].rollNumber == rollNumber){
			printf("There is already a student record with that roll number value\n");
					return(-1);
			}
	}
	return 0;

}

// deletes a record by setting the roll number equal to 0 which im defining as deleted.
int8_t delete_record(STUDENT_INFO_t *pBaseAddyofRecords, uint8_t max_records){
	uint32_t rollNumber;

	begining:

	printf("Please Enter the Roll Number you wish to delete: ");
	scanf("%d", &rollNumber);
	getchar();

	for(uint8_t i = 0; i < max_records; i++){
		if(pBaseAddyofRecords[i].rollNumber == rollNumber){
			uint8_t choice;
			// asks and shows user which record to delete
			printf("Would you like to delete this Record?\n");
			display_current_records(pBaseAddyofRecords, i);
			printf("\nY or N: ");
			scanf("%c", &choice);
			getchar();

			if(choice == 'Y' || choice == 'y'){
				pBaseAddyofRecords[i].rollNumber = 0;
				return 1;
			}
			else if(choice == 'N' || choice == 'n'){
				goto begining;
			}
			else{
				return -1;
			}


		}
	}
	return -1;
}



void wait_for_input(void){

	printf("\nPress enter to continue\n");

	while(getchar() != '\n'){
		// read input buffer
	}
	getchar();
}

