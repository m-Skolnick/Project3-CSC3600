//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Project3.cpp          ASSIGNMENT #:  3            Grade: _________          *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Micaiah Skolnick                                              *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                            DUE DATE:  February 22, 2017                 *
//*                                                                                                   *
//*****************************************************************************************************
//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program reads each a list of customers, then processes each customer thrugh the   *
//*                 correct register based on their arrival time to the checkout counter, and their   *
//*                 designated process time. A list of the order in which customers arrived, and a    *
//*                 list of the order that customers exited the store is provided to the user.        *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : Footer - Prints a footer to signify end of program output                        *
//*                  Header - Prints a header to signify start of program output                      *
//*                  processData - Data from the input file is read into the program and processed    *
//*                  main - Variables are declared, functions are called, and headers are printed     *
//*                  printResults - Read each Op code character and perform the subsequent action.     *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <sstream>
#include "CustomerListClass.h"
using namespace std;
//*************************************  FUNCTION HEADER  *********************************************
void Header(ofstream &Outfile)
{       // Receives – the output file
		// Task - Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Micaiah Skolnick ";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(27) << "Spring 2017";
	Outfile << setw(30) << "Assignment #3" << endl;
	Outfile << setw(35) << "---------------------------------- - ";
	Outfile << setw(35) << "---------------------------------- - " << endl << endl;
	return;
}
//************************************* END OF FUNCTION HEADER  ***************************************
//*************************************  FUNCTION FOOTER  *********************************************
void Footer(ofstream &Outfile)
{
		// Receives – the output file
		// Task - Prints the output salutation
		// Returns - Nothing
	Outfile << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	return;
}
//************************************* END OF FUNCTION FOOTER  ***************************************
void checkForPops(CustomerListClass&pushedList, CustomerListClass&poppedList,CustomerListClass&List1,
	CustomerListClass&List2, CustomerListClass&List3, int currentTime) {
		// Receives – List of input order, list of output order, each customer queue, and the current
			// time
		// Task - Check whether a node in each list is ready to be popped, if so, pop it.
		// Returns - Nothing
	int time = 0;
		// Check whether a customer should be popped from any of the lists.
	while (time <= currentTime) {

		if (List1.checkForPop(time)) {
			poppedList.add(List1.pop());
		}
		if (List2.checkForPop(time)) {
			poppedList.add(List2.pop());
		}
		if (List3.checkForPop(time)) {
			poppedList.add(List3.pop());
		}
		time++;
	}
}
//*****************************************************************************************************
void processData(ifstream&dataIN,CustomerListClass&arrivalList,CustomerListClass&departureList) {
		// Receives – The input and output files
		// Task - Process each data record/op code.
		// Returns - Nothing
	
		// Declare local variables
	int currentTime = 0;
	CustomerListClass List1, List2, List3;
	bool firstPrint = true;
	CustomerType customer;
	int fieldNumber;
	string newValue;
	int code;
	dataIN >> ws >> code >> ws; // seed read first code
	while (code != -99) {  // As long as there is another code, read it in
		customer.tArrival = code;
		std::getline(dataIN, customer.name);
		dataIN >> customer.tProcess;
			// Loop until the time of the next customer
		while (currentTime <= customer.tArrival) {
				// When the next customer arrival time is reached, add them to a list, and to the 
					// arrival order list.
			if (currentTime == customer.tArrival) {
				if (List1.getPTime() <= List2.getPTime() && List1.getPTime() <= List3.getPTime()) {
					List1.add(customer);
				}
				else if (List2.getPTime() <= List3.getPTime()) {
					List2.add(customer);
				}
				else {
					List3.add(customer);
				}
				arrivalList.add(customer);
			}	
				// Check whether any of the customers are ready to leave the store.
			checkForPops(arrivalList, departureList, List1, List2, List3, currentTime);			
			currentTime++;
		}
		dataIN >> ws >> code >> ws; // Read in the next code
	}
		// Check one more time to make sure all customers have left the store
	currentTime = 0;
	while (!List1.isEmpty() || !List2.isEmpty() || !List3.isEmpty()) {
		checkForPops(arrivalList, departureList, List1, List2, List3, currentTime);
		currentTime++;	
	}
}
//*****************************************************************************************************
void printResults(ofstream&dataOUT,CustomerListClass&pushedList,CustomerListClass&poppedList) {
		// Receives – The output file, order of customer arrival, and exit.
		// Task - Print each list of customers
		// Returns - Nothing	
	dataOUT << "The order of customer arrival is:    The order of customer departure is:" << endl;
	dataOUT << "--------------------------------- |  -----------------------------------" << endl;
	while (!pushedList.isEmpty()&&!poppedList.isEmpty()) {
		dataOUT << pushedList.pop().name;
		dataOUT << "              |   ";
		dataOUT << poppedList.pop().name << endl;
	}
}
//*****************************************************************************************************
int main() {
		// Receives – Nothing
		// Task - Call each necessary function of the program in order
		// Returns - Nothing
	// Declare variables used in program.	 
	ifstream dataIN;
	ofstream dataOUT;
	CustomerListClass pushedList, poppedList;

	dataIN.open("queue_in.txt"); // Open the file containing data.
	dataOUT.open("dataOUT.doc"); // Create and open the file to write data to.		
	Header(dataOUT); // Print data header.
	//receiveData(dataIN, pushedList, poppedList);
	processData(dataIN,pushedList,poppedList); // Process each section of data from the input file.
	printResults(dataOUT, pushedList, poppedList);
	Footer(dataOUT); // Print footer. 
	dataIN.close(); // Close input data file. 
	dataOUT.close(); // Close output data file.
	return 0;
}