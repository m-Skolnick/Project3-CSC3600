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
	void push(CustomerType);
	CustomerType pop();
	bool checkForPop(int);
	bool isEmpty();
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
inline CustomerType CustomerListClass::pop()
{
	CustomerType *TempPtr;
	TempPtr = StartPtr;
	StartPtr = StartPtr->next;
	return *TempPtr;
}

inline bool CustomerListClass::checkForPop(int currentTime)
{
	if (StartPtr != NULL) {
		if (currentTime == StartPtr->tProcess + StartPtr->tArrival) {
			return true;		}		
	}
	else {
		return false;
	}
	
}

inline bool CustomerListClass::isEmpty()
{
	if (StartPtr == NULL) {
		return true;
	}
	else {
		return false;
	}
}
