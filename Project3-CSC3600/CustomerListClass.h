//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  CustomerListClass.cpp          ASSIGNMENT #: 3                              *
//*                                                                                                   *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : add - Insert one record of type CustomerType into list of records                *
//*                  pop - Remove and return one record from the front of the list                    *
//*                  checkForPop - Check to see if the front customer is ready to be popped from list *
//*                  isEmpty - Check to see whether the list is empty                                 *
//*                  getPTime() - Get the total process time for the list of customers
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
	void add(CustomerType);
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
inline void CustomerListClass::add(CustomerType customer)
{
		// Receives – One structure of type CustomerType
		// Task - Add the received structure to the back of customerlist
		// Returns - Nothing

		// Read in the received customer to a new pointer.
	CustomerType *CurrentPtr, *newPtr;
	newPtr = new(CustomerType);
	newPtr ->tArrival = customer.tArrival;
	newPtr->name = customer.name;
	newPtr->tProcess = customer.tProcess;

		
	CurrentPtr = StartPtr;
		// If there are no nodes in list, put this one at the beginning and return
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
//*****************************************************************************************************
inline int CustomerListClass::getPTime() {
		// Receives – Nothing
		// Task - Add up the processing time for the list
		// Returns - The total processing time for this list
	CustomerType *CurrentPtr;
	CurrentPtr = StartPtr;
	int processTime = 0;
		// Add the processing time for each node
	while (CurrentPtr != NULL) {
		processTime += CurrentPtr->tProcess;
		CurrentPtr = CurrentPtr->next;
	}
		// Return the processing time for the list
	return processTime;
}
//*****************************************************************************************************
inline CustomerType CustomerListClass::pop()
{
		// Receives – Nothing
		// Task - Remove one node from front of list
		// Returns - The removed node.
	CustomerType *TempPtr;
	TempPtr = StartPtr;
	StartPtr = StartPtr->next;
	return *TempPtr;
}
//*****************************************************************************************************
inline bool CustomerListClass::checkForPop(int currentTime)
{
		// Receives – The current processing time in type int
		// Task - Check whether the front node of each list is ready to be removed
		// Returns - true or false whether it is time for first node to be removed
	int thisPtrTime;
		// if the start time+process time for the front node of the list is equal to the current time
		// return true signifying that the list is ready to be popped.
	if (StartPtr != NULL) {
		thisPtrTime = StartPtr->tProcess + StartPtr->tArrival;
		if (currentTime == thisPtrTime) {
			return true;		
		}	
		else {
			return false;
		}
	}
	else {
		return false;
	}
	
}
//*****************************************************************************************************
inline bool CustomerListClass::isEmpty()
{
		// Receives – Nothing
		// Task - Check whether the list is empty
		// Returns - true or false signifying whether the list is empty or not.
	if (StartPtr == NULL) {
		return true;
	}
	else {
		return false;
	}
}
