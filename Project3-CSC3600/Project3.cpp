//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Project2.cpp          ASSIGNMENT #:  2            Grade: _________          *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Micaiah Skolnick                                              *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 11                            DUE DATE:  February 6, 2017                  *
//*                                                                                                   *
//*****************************************************************************************************
//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program first reads a one character code, then depending on the code, processes   *
//*              values for a record list on the subsequent input lines. Records are stored in a      *
//*              structure, and the list of structures is built by a class which controls the list.   *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : newPage - Prints a blank line for each blank space left on the page              *
//*                  Footer - Prints a footer to signify end of program output                        *
//*                  Header - Prints a header to signify start of program output                      *
//*                  getData - Data from the input file is read into the program                      *
//*                  main - Variables are declared, functions are called, and headers are printed     *
//*                  processData - Read each Op code character and perform the subsequent action.     *
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
int lineCount;
int MAXLINECOUNT;
//*****************************************************************************************************
void newPage(ofstream&dataOUT) {
	// Receives – the output file
	// Task - Insert blank lines to fill the rest of the current page
	// Returns - Nothing
	while (lineCount < MAXLINECOUNT) {
		dataOUT << endl;
		lineCount++;
	}
	lineCount = 0; // Reset the line count to 0 for next page.
}
//*****************************************************************************************************
//*************************************  FUNCTION HEADER  *********************************************
void Header(ofstream &Outfile)
{       // Receives – the output file
		// Task - Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Micaiah Skolnick ";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(27) << "Spring 2017";
	Outfile << setw(30) << "Assignment #2" << endl;
	Outfile << setw(35) << "---------------------------------- - ";
	Outfile << setw(35) << "---------------------------------- - " << endl << endl;
	lineCount += 4;
	return;
}
//************************************* END OF FUNCTION HEADER  ***************************************
//*************************************  FUNCTION FOOTER  *********************************************
void Footer(ofstream &Outfile, int lineCount)
{
		// Receives – the output file
		// Task - Prints the output salutation
		// Returns - Nothing
	Outfile << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	lineCount += 4;
	return;
}
//************************************* END OF FUNCTION FOOTER  ***************************************
void checkForPops(CustomerListClass&pushedList, CustomerListClass&poppedList,CustomerListClass&List1,
	CustomerListClass&List2, CustomerListClass&List3, int currentTime) {

	if (List1.checkForPop(currentTime)) {
		poppedList.push(List1.pop());
	}
	else if (List2.checkForPop(currentTime)) {
		poppedList.push(List2.pop());
	}
	else if (List3.checkForPop(currentTime)) {
		poppedList.push(List3.pop());
	}

}
void processData(ifstream&dataIN,CustomerListClass&pushedList,CustomerListClass&poppedList) {
		// Receives – The input and output files
		// Task - Process each data record/op code.
		// Returns - Nothing
	
	int currentTime = -1;
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


		while (currentTime != customer.tArrival) {
			currentTime++;

			checkForPops(pushedList, poppedList, List1, List2, List3, currentTime);

			if (currentTime == customer.tArrival) {
				if (List1.getPTime() <= List2.getPTime() && List1.getPTime() <= List3.getPTime()) {
					List1.push(customer);
				}
				else if (List2.getPTime() <= List3.getPTime()) {
					List2.push(customer);
				}
				else {
					List3.push(customer);
				}
				pushedList.push(customer);
			}
			
		}		
		dataIN >> ws >> code >> ws; // Read in the next code
	}
}
//*****************************************************************************************************
void printResults(ofstream&dataOUT,CustomerListClass&pushedList,CustomerListClass&poppedList) {
	
	while (!pushedList.isEmpty()&&!poppedList.isEmpty()) {
		dataOUT << pushedList.pop().name;
		dataOUT << "    ";
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
	lineCount = 0;
	MAXLINECOUNT = 54;

	dataIN.open("queue_in.txt"); // Open the file containing data.
	dataOUT.open("dataOUT.doc"); // Create and open the file to write data to.		
	Header(dataOUT); // Print data header.
	//receiveData(dataIN, pushedList, poppedList);
	processData(dataIN,pushedList,poppedList); // Process each section of data from the input file.
	printResults(dataOUT, pushedList, poppedList);
	newPage(dataOUT); // Insert a page break before the footer
	Footer(dataOUT, lineCount); // Print footer. 
	dataIN.close(); // Close input data file. 
	dataOUT.close(); // Close output data file.

	return 0;
}