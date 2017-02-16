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
struct CustomerListType {
	CustomerType *TopPtr;
	CustomerType *LastPtr;
	int totProcessTime;
};
class CustomerListClass {
public:
	CustomerListClass();
	bool insertRecord(CustomerType);
	void printRecords(ofstream&, int&);
	bool deleteRecord(CustomerType record);
	bool changeRecord(CustomerType, int, string);
private:
	CustomerListType List1;
	CustomerListType List2;
	CustomerListType List3;
};
//*****************************************************************************************************
CustomerListClass::CustomerListClass() {
		// Initialize members of each list
	List1.TopPtr = NULL;
	List1.LastPtr = NULL;
	List1.totProcessTime = 0;
	List2.TopPtr = NULL;
	List2.LastPtr = NULL;
	List2.totProcessTime = 0;
	List3.TopPtr = NULL;
	List3.LastPtr = NULL;
	List3.totProcessTime = 0;
}
//*****************************************************************************************************
bool CustomerListClass::insertRecord(CustomerType customer) {
		// Receives – A single record of type RecordType
		// Task - Add a record to the list of records.
		// Returns - True or false indicating whether a record was added.
		// Declare local pointers
	CustomerType *newPtr, *PreviousPtr, *CurrentPtr;
		// Reserve memory for a new node
	newPtr = new(CustomerType);
		// Place the data in the new node
	newPtr->tArrival = customer.tArrival;
	newPtr->name = customer.name;
	newPtr->tProcess = customer.tProcess;	
	newPtr->next = customer.next;
	
	// need to test whether total process time includes the wait time etc. *******************************************************

		// if no list exists, place new node at the start of the list
	if (List1.TopPtr == NULL)
	{
		List1.TopPtr = newPtr;
		List1.LastPtr = newPtr;
		List1.totProcessTime += newPtr->tArrival;
	}
	else if (List2.TopPtr == NULL)
	{
		List2.TopPtr = newPtr;
		List2.LastPtr = newPtr;
		List2.totProcessTime += newPtr->tArrival;
	}
	else if (List3.TopPtr == NULL)
	{
		List3.TopPtr = newPtr;
		List3.LastPtr = newPtr;
		List3.totProcessTime += newPtr->tArrival;
	}
	else if (List1.totProcessTime<List2.totProcessTime && List1.totProcessTime < List3.totProcessTime)
	{
		List1.LastPtr -> next = newPtr;
		List1.LastPtr = newPtr;

		List1.totProcessTime += newPtr->tArrival;
	}
	else if (List2.totProcessTime<List3.totProcessTime)
	{
		List2.LastPtr->next = newPtr;
		List2.LastPtr = newPtr;

		List2.totProcessTime += newPtr->tArrival;
	}
		// If neither list1 or list2 process times were less than list3, automatically add to list 3
	else 
	{
		List3.LastPtr->next = newPtr;
		List3.LastPtr = newPtr;

		List3.totProcessTime += newPtr->tArrival;
	}
	//else
	//{	// insert the new node into the list
	//	PreviousPtr->next = newPtr;
	//	newPtr->next = CurrentPtr;
	//	return true;
	//}

	return false;
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
bool CustomerListClass::deleteRecord(CustomerType customer) {
		// Receives – A single record of type RecordType
		// Task - Delete a record from the list of records.
		// Returns - True or false indicating whether a record was deleted.
	CustomerType *tempPtr, *PreviousPtr, *CurrentPtr;
		//If the record to be deleted is the first record, reset the starting pointer
	//if (customer.lastName.compare(StartPtr->lastName) == 0
	//	&& customer.firstName.compare(StartPtr->firstName) == 0) {
	//	tempPtr = StartPtr;
	//	StartPtr = StartPtr->next;
	//	delete (tempPtr);
	//	return true;
	//}
	//else { 		// initialize local pointers to search for the node to be deleted
	//	PreviousPtr = StartPtr;
	//	CurrentPtr = StartPtr->next;
	//	//  step through the list until  the delete node is found or the list is exhausted
	//	while (CurrentPtr != NULL) {
	//		if ((customer.firstName != CurrentPtr->firstName) 
	//			|| (customer.lastName != CurrentPtr->lastName)) {
	//			PreviousPtr = CurrentPtr;
	//			CurrentPtr = CurrentPtr->next;
	//		}
	//		else {
	//			break;
	//		}
	//	}
	//		//  if the node is found, adjust pointers to removed it from the list, free up the space
	//		//  in memory used by the  deleted node, and return the data.
	//	if (CurrentPtr != NULL)
	//	{
	//		tempPtr = CurrentPtr;
	//		PreviousPtr->next = CurrentPtr->next;
	//		delete (tempPtr);
	//		return true;
	//	}
	//}
		// return a value that indicates the node was not found
	return false;
}
bool CustomerListClass::changeRecord(CustomerType record, int fieldNumber, string newVal) {
		// Receives – A record of type RecordType, an int indicating type of value and the new value
		// Task - change a record in the list of records.
		// Returns - True or false indicating whether a record was changed.
	CustomerType *PreviousPtr, *CurrentPtr, newRecord;
			// initialize local pointers to search for the node to be changed
		PreviousPtr = NULL;
		//CurrentPtr = StartPtr;  // Start searching at first node

			//  step through the list until  the change node is found or the list is exhausted
		//while (CurrentPtr != NULL) {
		//	if ((record.firstName != CurrentPtr->firstName) 
		//		|| (record.lastName != CurrentPtr->lastName)){
		//		PreviousPtr = CurrentPtr;
		//		CurrentPtr = CurrentPtr->next;
		//	}
		//	else {
		//		break;
		//	}
		//}
		//	//  if the node is found, delete the current record in the list, and add the
		//		// updated one.
		//if (CurrentPtr != NULL) {
		//		// Copy values of current node to new record.
		//	newRecord.firstName = CurrentPtr->firstName;
		//	newRecord.lastName = CurrentPtr->lastName;
		//	newRecord.address = CurrentPtr->address;
		//	newRecord.city = CurrentPtr->city;
		//	newRecord.state = CurrentPtr->state;
		//	newRecord.zipCode = CurrentPtr->zipCode;
		//	deleteRecord(record); // Delete the current record in the list
		//	switch (fieldNumber) { // Update the new record which will be added to the list
		//	case 1: newRecord.firstName = newVal;
		//		break;
		//	case 2: newRecord.lastName = newVal;
		//		break;
		//	case 3: newRecord.address = newVal;
		//		break;
		//	case 4: newRecord.city = newVal;
		//		break;
		//	case 5: newRecord.state = newVal;
		//		break;
		//	case 6: newRecord.zipCode = newVal;
		//		break;
		//	}
		//	insertRecord(newRecord); // Insert the updated record in the list
		//	return true;
		//}
	// return a value that indicates the node was not found
	return false;
}
