#include <Python.h>
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
//Briana Carlson

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int SearchItems(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

void main()
{
	while (1) {
		int userInput;
		//print statements for menu
		cout << "What would you like to do?" << endl;
		cout << "1. Display all number of items" << endl;
		cout << "2. Search for specific item" << endl;
		cout << "3. Produce Histogram" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your menu selection: " << endl;

		cin >> userInput;
		//loop to validate input if it's non-numerical or not between 1-4 then it will ask again
		while ((cin.fail()) || (userInput <= 0) || (userInput > 4)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Enter your menu selection: " << endl;
			cin >> userInput;
		}
		/*if user chooses first option it calls the CallProcedure function with argument
		DisplayAllItems to communicate with PythonCode.py and print the list with quantities*/
		if (userInput == 1) {
			CallProcedure("DisplayAllItems");
		}

		/*Gets input for items to search and calls the SearchItems function with arguments for 
		SearchItem function name from the py file and user input then prints returned values*/
		else if (userInput == 2) {
			string input;
			cout << "Which item are you searching? " << endl;
			cin >> input;
			while (!isalpha(input[0])) {
				cout << "Which item are you searching? " << endl;
				cin >> input;
			}
			cout << SearchItems("SearchItem", input) << endl;
		}

		/*Calls function and sends the python function name OutputHistogram then reads the file
		created by that function. Loop for reading input from file and assigning variables to 
		inputs for items and names. Added a break to immediately stop once the file ends 
		otherwise the last item is printed twice. Then outputs item name and a for loop prints 
		an asterisk for the item's quantity. When it ends the file is closed.*/
		else if (userInput == 3) {
			string itemName;
			int itemQuantity;

			CallProcedure("OutputHistogram");
			ifstream inputFile("frequency.dat");

			while (inputFile) { 
				inputFile >> itemName; 
				inputFile >> itemQuantity; 
				if (inputFile.eof()) break; 
				cout << itemName << " ";
				for (int i = 1; i <= itemQuantity; ++i) {
					cout << "*";
				}
				cout << endl;
			}
			inputFile.close();
			cout << endl;
		}
		else if (userInput == 4) {
			exit(0);
		}
	}
}