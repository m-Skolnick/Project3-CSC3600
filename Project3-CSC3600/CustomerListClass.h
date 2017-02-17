//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  CustomerListClass.cpp          ASSIGNMENT #: 3                              *
//*                                                                                                   *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : insertRecord - Insert one record of type RecordType into list of records         *
//*                  printRecords - Print each of the records in the list                             *
//*                  deleteRecord - Delete one record from the list	                                  *
//*                  changeRecord - Change one value of one record in record list                     *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <sstream>
using namespace std;
//*****************************************************************************************************
struct CustomerType {
		// The structure "CustomerType" holds each record file.
	int tArrival, tProcess;
	string name;
	CustomerType *next;
};
class CustomerListClass {
public:
	CustomerListClass();
	void printRecords(ofstream&, int&);
	void push(CustomerType);
	void pop(CustomerType);
	int getPTime();
private:
	CustomerType *StartPtr;
};
//*****************************************************************************************************
CustomerListClass::CustomerListClass() {
		// Initialize the start Ptr to NULL
	StartPtr = NULL;
}
//*****************************************************************************************************
void CustomerListClass::printRecords(ofstream&Outfile, int&lineCount) {
		// Receives – A the output file, and the line count.
		// Task - Prints each record in the list.
		// Returns - Nothing
	CustomerType  *CurrentPtr;
		// Initialize a current pointer to the start of the linked list
	//CurrentPtr = StartPtr;
		// Check for an Empty List
	/*if (CurrentPtr == NULL) {
		Outfile << "List is Empty" << endl;
		lineCount++;
		return;
	}
	*/	// Print a data header
	Outfile << endl << "                         MAILING LIST" << endl;
	Outfile << "Last Name   First Name  Address             City";
	Outfile << "        State Zip Code" << endl;
	Outfile << "======================================================================" << endl;
	lineCount += 4; // Increment the line count by 4
					// Print each member of the list
	//while (CurrentPtr != NULL)
	//{                               //  Print the data
	//	/*Outfile << CurrentPtr->lastName << CurrentPtr->firstName;
	//	Outfile << CurrentPtr->address << CurrentPtr->city;
	//	Outfile << CurrentPtr->state << "    " << CurrentPtr->zipCode << endl;*/
	//	lineCount++; // Increment the line count for each record
	//				 //  Move to the next NODE
	//	CurrentPtr = CurrentPtr->next;
	//}
	return;
}
//*****************************************************************************************************

inline void CustomerListClass::push(CustomerType customer)
{
	CustomerType *CurrentPtr, *newPtr;
	newPtr = new(CustomerType);
	newPtr ->tArrival = customer.tArrival;
	newPtr->tArrival = customer.tArrival;
	newPtr->name = customer.name;
	newPtr->tProcess = customer.tProcess;
	CurrentPtr = StartPtr;
		// If there are no nodes in list, push to start
	if (StartPtr == NULL) {
		StartPtr = newPtr;
		newPtr->next = NULL;
		return;
	}
		// Find the end of the list
	while (CurrentPtr ->next != NULL) {
		CurrentPtr = CurrentPtr->next;
	}
		// Push to the end of the list
	CurrentPtr ->next = newPtr;
	newPtr->next = NULL;
}
inline int CustomerListClass::getPTime() {

	CustomerType *CurrentPtr;
	CurrentPtr = StartPtr;
	int processTime = 0;
	if (StartPtr == NULL) {
		return 0;
	}
	while (CurrentPtr != NULL) {
		processTime += CurrentPtr->tProcess;
		CurrentPtr = CurrentPtr->next;
	}
	return processTime;
}
inline void CustomerListClass::pop(CustomerType customer)
{

}
