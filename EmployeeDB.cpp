/********************************************************************************************************
 Assignment 3 - Employee Database
 
 Name: Kevin Geiszler
 Compiler: GCC C/C++ Version 6.2.0
 Operating System: macOS 10.11.6
 
 Usage: a.out <inputfile>
 
 This C++ program reads semicolon delimited employee data from a file and creates a linked list sorted by
 employee name. Each link contains the employee's name, age, and salary. Once the database has been established,
 the user can add employees, delete employees, search the database, display the database, save the database, 
 and exit the program. When saving the database, the program will overwrite the input file with updated database 
 information. The program will also save the database when the program exits.
 
 Created by Kevin Geiszler on 5/20/18.
 Copyright © 2018 home. All rights reserved.
 
 ********************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <limits>

#define NAME_SIZE 20

using namespace std;

/********************************************************************************************************/

// Used in switch statemnt in main() to handle user's menu selection.
enum MenuSelection { ADD=1, DELETE, SEARCH, LIST, SAVE, EXIT };

/*********************************************************************************************************
 
 Class Name: CEmployee
 
 Purpose: Represents an employee for the linked list storing employee data.
 
 Member Variables:
     char m_Name: The name of the employee
     unsigned int m_Age: The employee's age
     unsigned int m_Salary: The employee's salary
     CEmployee* m_pLink: Pointer to the next employee in the linked list (NULL by default)
 
 Public Member Functions:
     Function Name: Open
     Prototype: void Open(int argc, const char *pFileName, CEmployee *&pHead, CEmployee *&pCurrent)
 
     Function Name: AddEmployee
     Prototype: void AddEmployee(CEmployee *&pHead, CEmployee *&pCurrent)
     
     Function Name: DeleteEmployee
     Prototype: void DeleteEmployee(CEmployee *&pHead, CEmployee *&pCurrent)
     
     Function Name: SearchDatabase
     Prototype: void SearchDatabase(CEmployee *&pHead, CEmployee *&pCurrent)
     
     Function Name: ListAllEmployees
     Prototype: void ListAllEmployees(CEmployee *&pHead, CEmployee *&pCurrent)
     
     Function Name: SaveToFile
     Prototype: void SaveToFile(const char *pFileName, CEmployee *&pHead, CEmployee *&pCurrent);
     
     Function Name: ClearDatabase
     Prototype: void ClearDatabase(CEmployee *pHead)
     
 Private Member Functions:
     Function Name: Insert
     Prototype: void Insert(CEmployee *&pHead, CEmployee *&pCurrent)
     
     Function Name: GetNameFromUser
     Prototype: void GetNameFromUser()
     
     Function Name: GetAgeFromUser
     Prototype: void GetAgeFromUser()
     
     Function Name: GetSalaryFromUser
     Prototype: void GetSalaryFromUser()
     
     Function Name: DisplayCommaSalary
     Prototype: void DisplayCommaSalary()
 
 *********************************************************************************************************/

class CEmployee
{
public:
    void Open(int argc, const char *pFileName, CEmployee *&pHead, CEmployee *&pCurrent);
    void AddEmployee(CEmployee *&pHead, CEmployee *&pCurrent);
    void DeleteEmployee(CEmployee *&pHead, CEmployee *&pCurrent);
    void SearchDatabase(CEmployee *&pHead, CEmployee *&pCurrent);
    void ListAllEmployees(CEmployee *&pHead, CEmployee *&pCurrent);
    void SaveToFile(const char *pFileName, CEmployee *&pHead, CEmployee *&pCurrent);
    void ClearDatabase(CEmployee *pHead);

private:
    void Insert(CEmployee *&pHead, CEmployee *&pCurrent);
    void GetNameFromUser();
    void GetAgeFromUser();
    void GetSalaryFromUser();
    void DisplayCommaSalary();

    char m_Name[NAME_SIZE];
    unsigned int m_Age;
    unsigned int m_Salary;
    CEmployee *m_pLink;
};



/********************************************************************************************************/

// Non-member function prototypes:

void displayMenu();
int getUserInput();

/********************************************************************************************************/

// CEmployee public member functions:

/*********************************************************************************************************
 
 Function: void CEmployee::Open(int argc, const char *pFileName, CEmployee *&pHead, CEmployee *&pCurrent)
 
 Purpose: Checks for valid amount of command line arguments (2). Opens file (argv[1]), reads the data,
          and places each line of data into a linked list sorted alphabetically by name.
 
 Parameters: 
    int argc: Number of command line arguments.
    const char *pFileName: Name of input file (argv[1]).
    CEmployee *&pHead: Pointer to first link in linked list.
    CEmployee *&pCurrent: Pointer to current employee in linked list.
 
 Local Variables:
    char str[80]: String to hold line of data.
    char d[]: Holds the delimiter.
    ifstream InFile: Input file object.
 
 *********************************************************************************************************/

void CEmployee::Open(int argc, const char *pFileName, CEmployee *&pHead, CEmployee *&pCurrent)
{
    char str[80]; // String to be read from file
    char d[] = ";"; // Delimiter
    
    memset(str, '\0', 80); // Set every character in str to NULL.
    
    if (argc != 2) // Must have exactly 2 command line arguments.
    {
        cout << "\nError. Usage: EMPLOYEE_DB <datafile>\n\n";
        exit(1);
    } // end if
    
    ifstream InFile(pFileName); // Open file for reading.
    
    if (!InFile) // Check if file was successfully opened.
    {
        cout << "Error, cannot open data file " << pFileName << ".\n\n";
        exit(1);
    } // end if
    
    while (InFile.getline(str, 80)) // Read the file line by line and insert employee data into the linked list.
    {
        // Place line's data into this current object's member variables.
        strcpy(m_Name, strtok(str, d));
        m_Age = atoi(strtok(NULL, d));
        m_Salary = atoi(strtok(NULL, d));
        m_pLink = 0;
        
        // Create a new employee object based on *this object's data and place the new employee in the list.
        Insert(pHead, pCurrent);
        
    } // end while
    
    InFile.close();
    
    return;
}

/*********************************************************************************************************
 
 Function: void CEmployee::AddEmployee(CEmployee *&pHead, CEmployee *&pCurrent)
 
 Purpose: Gets input from user to create a new employee and adds them to the database. Uses *this current
          object's member variable to store user input data.
 
 Parameters:
     CEmployee *&pHead: Pointer to first link in linked list.
     CEmployee *&pCurrent: Pointer to current employee in linked list.
 
 Local Variables: None
 
 *********************************************************************************************************/

void CEmployee::AddEmployee(CEmployee *&pHead, CEmployee *&pCurrent)
{
    GetNameFromUser(); // Get emmployee's name from user and set it to m_Name.
    GetAgeFromUser(); // Get emmployee's age from user, set it to m_Age, and check for errors.
    GetSalaryFromUser(); // Get employee's salary from user, set it to m_Salary, and check for errors.
    
    cout << endl;
    
    // Create a new employee object based on *this object's data and place the new employee in the list.
    Insert(pHead, pCurrent);
    
    return;
}

/*********************************************************************************************************
 
 Function: void CEmployee::DeleteEmployee(CEmployee *&pHead, CEmployee *&pCurrent)
 
 Purpose: Deletes an employee from the database based on the name supplied by the user.
 
 Parameters:
    CEmployee *&pHead: Pointer to first link in linked list.
    CEmployee *&pCurrent: Pointer to current employee in linked list.
 
 Local Variables:
    CEmployee *pDeleteThis: Pointer to link user wants to delete.
    CEmployee *pPrev: Pointer to link before pCurrent.
 
 *********************************************************************************************************/

void CEmployee::DeleteEmployee(CEmployee *&pHead, CEmployee *&pCurrent)
{
    SearchDatabase(pHead, pCurrent); // Sets pCurrent to found employee; NULL if not found.
    
    if (!pCurrent) // Employee to be deleted not found in database.
        return;
    
    CEmployee *pDeleteThis = pCurrent;
    cout << "Deleting " << m_Name << " from the employee database.\n\n";
    
    if (pHead == pDeleteThis) // Link to be deleted is first in the list.
    {
        pHead = pHead->m_pLink; // Second link in list becomes head.
        delete pDeleteThis;
        
        return;
    }
    
    CEmployee *pPrev = pHead; // Will eventually point to link before pCurrent.
    
    while (pPrev->m_pLink != pDeleteThis) // Traverse through list to set up pPrev.
        pPrev = pPrev->m_pLink;
    
    if (!pDeleteThis->m_pLink)                 // Link to be deleted is last in the list.
        pPrev->m_pLink = 0;                    // Connect previous link to NULL.
    else                                       // Link to be deleted is neither first nor last in list.
        pPrev->m_pLink = pDeleteThis->m_pLink; // Connect previous link to link found after pDeleteThis.
    
    delete pDeleteThis;
    
    return;
}

/*********************************************************************************************************
 
 Function: void CEmployee::SearchDatabase(CEmployee *&pHead, CEmployee *&pCurrent)
 
 Purpose: Searches database for employee whose name is supplied by the user. Sets pCurrent to the 
          employee's link.
 
 Parameters:
    CEmployee *&pHead: Pointer to first link in linked list.
    CEmployee *&pCurrent: Pointer to current employee in linked list.
 
 Local Variables: None
 
 *********************************************************************************************************/

void CEmployee::SearchDatabase(CEmployee *&pHead, CEmployee *&pCurrent)
{
    GetNameFromUser();
    
    pCurrent = pHead;
    
    // Search through linked list, looking for link with desired employee's name.
    while (pCurrent)
    {
        if (strcmp(pCurrent->m_Name, m_Name) == 0) // Found employee in database; pCurrent points to it.
        {
            cout << "\nFound " << m_Name << " in the employee database.\n\n";
            return;
        } // end if
        else if (strcmp(pCurrent->m_Name, m_Name) > 0) // Don't want to search longer than necessary
            break;
        
        pCurrent = pCurrent->m_pLink; // Traverse
    } // end while
    
    cout << "\nSorry, " << m_Name << " was not found in the employee database.\n\n"; // Name does not exist.
    pCurrent = 0;
    
    return;
}

/*********************************************************************************************************
 
 Function: void CEmployee::ListAllEmployees(CEmployee *&pHead, CEmployee *&pCurrent)
 
 Purpose: Displays each employee and their information to the screen.
 
 Parameters:
    CEmployee *&pHead: Pointer to first link in linked list.
    CEmployee *&pCurrent: Pointer to current employee in linked list.
 
 Local Variables: None
 
 *********************************************************************************************************/

void CEmployee::ListAllEmployees(CEmployee *&pHead, CEmployee *&pCurrent)
{
    pCurrent = pHead;
    
    cout << endl;
    cout << "  #  Employee Name        Age         Salary\n";
    cout << "==============================================\n";
    
    for (int num = 1; pCurrent; num++) // Loop through database and print each employee's data.
    {
        cout << setfill(' ') << right <<  setw(3)  << num                << ". ";
        cout << setfill(' ') << left  <<  setw(NAME_SIZE) << pCurrent->m_Name   << " ";
        cout << setfill(' ') << right <<  setw(3)  << pCurrent->m_Age    << " ";
        pCurrent->DisplayCommaSalary();
        
        pCurrent = pCurrent->m_pLink;
    }
    
    cout << "\n\n";

    return;
}

/*********************************************************************************************************
 
 Function: void CEmployee::SaveToFile(const char *pFileName, CEmployee *&pHead, CEmployee *&pCurrent)
 
 Purpose: Displays each employee and their information to the screen.
 
 Parameters:
    const char *pFileName: Name of output file (argv[1]).
    CEmployee *&pHead: Pointer to first link in linked list.
    CEmployee *&pCurrent: Pointer to current employee in linked list.
 
 Local Variables:
    ofstream OutFile: Output file object.
 
 *********************************************************************************************************/

void CEmployee::SaveToFile(const char *pFileName, CEmployee *&pHead, CEmployee *&pCurrent)
{
    ofstream OutFile(pFileName); // Open file for writing.
    pCurrent = pHead;
    
    OutFile.seekp(0L); // Move cursor to top of file.
    
    cout << "\nWriting database to " << pFileName << ".\n\n";
    
    while (pCurrent) // Traverse through list, writing employee info to data file.
    {
        OutFile << pCurrent->m_Name << ";";
        OutFile << pCurrent->m_Age << ";";
        OutFile << pCurrent->m_Salary;
        
        if (pCurrent->m_pLink) // Insert newline because there are more employees to write to file.
            OutFile << "\n";
        
        pCurrent = pCurrent->m_pLink;
    }
    
    OutFile.close();
}

/*********************************************************************************************************
 
 Function: void CEmployee::ClearDatabase(CEmployee *pHead)
 
 Purpose: Deletes each link in the linked list. Called when user chooses to exit the program.
 
 Parameters:
    CEmployee *&pHead: Pointer to first link in linked list.
 
 Local Variables:
    CEmployee *pDeleteThis: Pointer to link to be deleted.
 
 *********************************************************************************************************/

void CEmployee::ClearDatabase(CEmployee *pHead)
{
    CEmployee *pDeleteThis = 0;
    
    while (pHead) // Traverse through list and delete each node.
    {
        pDeleteThis = pHead;
        pHead = pHead->m_pLink;
        delete pDeleteThis;
    }
}



/********************************************************************************************************/

// Private CEmployee member functions:

/*********************************************************************************************************
 
 Function: void CEmployee::Insert(CEmployee *&pHead, CEmployee *&pCurrent)
 
 Purpose: Inserts an employee into the database in alphabetical order. Used in CEmployee::Open() and
          CEmployee::AddEmployee(). Uses *this object's member data to initialize new employee's data.
 
 Parameters:
    CEmployee *&pHead: Pointer to first link in linked list.
    CEmployee *&pCurrent: Pointer to current employee in linked list.
 
 Local Variables:
    CEmployee *pPrev: Pointer to link before pCurrent.
    CEmployee *pNewEmployee: Pointer to new employee object created on the heap.
 
 *********************************************************************************************************/

void CEmployee::Insert(CEmployee *&pHead, CEmployee *&pCurrent)
{
    CEmployee *pPrev;
    CEmployee *pNewEmployee = new CEmployee;
    
    // Initialize the new employee's data.
    strcpy(pNewEmployee->m_Name, m_Name);
    pNewEmployee->m_Age = m_Age;
    pNewEmployee->m_Salary = m_Salary;
    pNewEmployee->m_pLink = 0;
    
    if (!pHead) // Linked list is empty
        pHead = pNewEmployee;
    else // Linked list is not empty
    {
        pCurrent = pHead;
        pPrev = 0;
        
        // Traverse through the list, looking for proper place to insert employee.
        while (pCurrent)
        {
            // New employee's name comes after current employee's name
            if (strcmp(pNewEmployee->m_Name, pCurrent->m_Name) > 0)
            {
                if (!pCurrent->m_pLink) // We've reached the end of the list, so insert at back of list
                {
                    pCurrent->m_pLink = pNewEmployee;
                    break;
                } // end if
                else // Proper spot has not been found yet. Traverse the list.
                {
                    pPrev = pCurrent;
                    pCurrent = pCurrent->m_pLink;
                } // end else
            } // end if
            else // New employee's name comes before current employee's name.
            {
                if (!pPrev) // Inserting at front of list
                {
                    pNewEmployee->m_pLink = pHead;
                    pHead = pNewEmployee;
                } // end if
                else // Inserting after front of the list, but before the end of the list.
                {
                    pPrev->m_pLink = pNewEmployee;
                    pNewEmployee->m_pLink = pCurrent;
                } // end else
                
                break;
            } // end else
        } // end while
    } // else
    
    return;
}

/*********************************************************************************************************
 
 Function: void CEmployee::GetNameFromUser()
 
 Purpose: Gets employee's name from the user and stores it in this->m_Name.
 
 Parameters: None
 
 Local Variables: None
 
 *********************************************************************************************************/

void CEmployee::GetNameFromUser()
{
    memset(m_Name, '\0', NAME_SIZE); // Set every character in m_Name to NULL.
    
    // Get employee's first and last name from user.
    cout << "\nEnter the employee's first and last name: ";
    cin.getline(m_Name, NAME_SIZE); // Using "cin >> name" only reads characters up to the first whitespace.
    
    return;
}

/*********************************************************************************************************
 
 Function: void CEmployee::GetAgeFromUser()
 
 Purpose: Gets employee's age from the user, stores it in this->m_Age, and checks for errors.
 
 Parameters: None
 
 Local Variables: None
 
 *********************************************************************************************************/

// Get emmployee's age from user and check for errors.
void CEmployee::GetAgeFromUser()
{
    cout << "\nEnter the employee's age: ";
    while (cin >> m_Age || !cin.eof())
    {
        // Ignore everything after the read value up to the max buffer size or newline
        // character (whichever comes first).
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Invalid input.
        if (!cin.good())
        {
            // Reset the fail flags in good() to true.
            cin.clear();
            
            // Ignore everything after the read value up to the max buffer size or newline
            // character (whichever comes first).
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "\nPlease enter a non-negative integer.\n";
            cout << "\nEnter the employee's age: ";
            
            continue;
        } // end if
        
        break;
    } // end while
    
    return;
}

/*********************************************************************************************************
 
 Function: void CEmployee::GetSalaryFromUser()
 
 Purpose: Gets employee's salary from the user, stores it in this->m_Salary, and checks for errors.
 
 Parameters: None
 
 Local Variables: None
 
 *********************************************************************************************************/

// Get emmployee's salary from user and check for errors.
void CEmployee::GetSalaryFromUser()
{
    cout << "\nEnter the employee's salary: ";
    while (cin >> m_Salary || !cin.eof())
    {
        // Ignore everything after the read value up to the max buffer size or newline
        // character (whichever comes first).
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Invalid input.
        if (!cin.good())
        {
            // Reset the fail flags in good() to true.
            cin.clear();
            
            // Ignore everything after the read value up to the max buffer size or newline
            // character (whichever comes first).
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "\nPlease enter a non-negative integer.\n";
            cout << "\nEnter the employee's salary: ";
            
            continue;
        }
        
        break;
    }
    
    cout << endl;
    
    return;
}

/*********************************************************************************************************
 
 Function: void CEmployee::DisplayCommaSalary()
 
 Purpose: Used in CEmployee::ListAllEmployees() to display this->m_Salary. Inserts commas if m_Salary
          is greater than 1000. This function is used to print salaries < 1000 (no comma required) to 
          keep display formatting consistent.
 
 Parameters: None
 
 Local Variables:
    char numStr[20]: Holds string version of m_Salary.
    int strLen: Length of string
    int index: Index of salary string.
    int commaCounter: Display comma when commaCounter % 3 == 0.
 
 *********************************************************************************************************/

void CEmployee::DisplayCommaSalary()
{
    cout << setw(9) << right;
    
    char numStr[20]; // Holds string version of m_Salary.
    int strLen = 0; // Length of string
    int index = 0; // Index of salary string.
    int commaCounter = 3; // Display comma when commaCounter % 3 == 0.
    
    memset(numStr, '\0', 20); // Initialize numStr.
    sprintf(numStr, "%d", m_Salary); // Create a char array representing the employee's salary.
    
    strLen = (int)strlen(numStr); // Get number of digits in salary.

    if (strLen % 3 == 0) // Display first 3 digits before displaying comma.
    {
        cout << numStr[0] << numStr[1] << numStr[2];
        index = 3; // Start at this index in while loop.
    }
    else if (strLen % 3 == 1) // Display first digit before displaying comma.
    {
        cout << numStr[0];
        index = 1; // Start at this index in while loop.
    }
    else if (strLen % 3 == 2) // Display first 2 digits before displaying comma.
    {
        cout << numStr[0] << numStr[1];
        index = 2; // Start at this index in while loop.
    }
    
    while (numStr[index]) // Display the rest of the string.
    {
        if (commaCounter % 3 == 0) // Display a comma, then another comma after every 3 digits.
            cout << ",";
        
        cout << numStr[index];
        index++;
        commaCounter++;
    }
    
    cout << endl;
}



/********************************************************************************************************/

// Non-member functions:

/*********************************************************************************************************
 
 Function: int main(int argc, const char * argv[])
 
 Purpose: The main function.
 
 Parameters:
    int argc: Command line argument count.
    const char * argv[]: Command line argument vector.
 
 Local Variables:
    int menuInput: Menu selection entered by user
    CEmployee *pHead: The head of the linked list.
    CEmployee *pCurrent: Current node in the linked list.
    CEmployee EmployeeDB: Driver object for creating the database, adding employees, deleting, searching,
                          displaying, and clearing the database before exiting.
 
 *********************************************************************************************************/

int main(int argc, const char * argv[])
{
    CEmployee *pHead = 0, *pCurrent = 0, EmployeeDB;
    int menuInput = 0;
    
    EmployeeDB.Open(argc, argv[1], pHead, pCurrent); // Read input file and initialize database.
    
    while (menuInput != EXIT) // Get menu selection input from user until they choose to exit.
    {
        displayMenu();
        menuInput = getUserInput();
        
        switch (menuInput) // Perform action based on user input.
        {
            case ADD:
                EmployeeDB.AddEmployee(pHead, pCurrent);
                break;
                
            case DELETE:
                EmployeeDB.DeleteEmployee(pHead, pCurrent);
                break;
                
            case SEARCH:
                EmployeeDB.SearchDatabase(pHead, pCurrent);
                break;
                
            case LIST:
                EmployeeDB.ListAllEmployees(pHead, pCurrent);
                break;
                
            case SAVE:
                EmployeeDB.SaveToFile(argv[1], pHead, pCurrent);
                break;
                
            case EXIT:
                EmployeeDB.SaveToFile(argv[1], pHead, pCurrent);
                EmployeeDB.ClearDatabase(pHead);
                break;
                
            default:
                cout << "\nPlease enter an integer between 1 and 6.\n\n";
                break;
        } // end switch
    } // end while

    cout << "Goodbye!\n\n";
    
    return 0;
}

/*********************************************************************************************************
 
 Function: void displayMenu()
 
 Purpose: Displays the main menu to the screen.
 
 Parameters: None
 
 Local Variables: None
 
 *********************************************************************************************************/

void displayMenu()
{
    cout << "Menu Options:\n\n";
    cout << "1. Add Employee\n";
    cout << "2. Delete Employee\n";
    cout << "3. Search Employee\n";
    cout << "4. List All Employees\n";
    cout << "5. Save Employee Database\n";
    cout << "6. Exit Employee Database\n\n";
    cout << "Enter Your Choice: ";
}

/*********************************************************************************************************
 
 Function: int getUserInput()
 
 Purpose: Gets an integer input from the user and returns it for menu selection. The user must enter an
          integer. The switch statement in main() will make sure the integer is between 1 and 6.
 
 Parameters: None
 
 Local Variables:
    int menuInput: Menu input from the user
 
 *********************************************************************************************************/

int getUserInput()
{
    int menuInput = 0;
    
    // Get menu selection from user and check for errors.
    while (cin >> menuInput || !cin.eof())
    {
        // Ignore everything after the read value up to the max buffer size or newline
        // character (whichever comes first).
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (!cin.good())
        {
            cout << "\nPlease enter an integer between 1 and 6.\n\n";
            
            // Reset the fail flags in good() to true.
            cin.clear();
            
            // Ignore everything after the read value up to the max buffer size or newline
            // character (whichever comes first).
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            displayMenu();
            
            continue;
        }
        
        break;
    }
    
    return menuInput;
}

/*********************************************************************************************************/






















































