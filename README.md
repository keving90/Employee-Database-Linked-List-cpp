# Employee Database Using a Linked List

## Introduction

This C++ program reads semicolon delimited employee data from a file and creates a linked list sorted
 by employee name. Each link contains the employee's name, age, and salary. Once the database has been
 established, the user can add employees, delete employees, search the database, display the database,
 save the database, or exit the program. When saving the database, the program will overwrite the input
 file with updated database information. The program will also save the database when the program exits.
 
## Usage

 Open Terminal and change the working directory to the the directory containing `employeeDB.cpp`.
 
 Compile the program in Terminal using: `g++ employeeDB.cpp`
 
 Run the program in Terminal using: `a.out inputFile.txt`
 
## Demonstration

#### The Input File

First, we will take a look at the sample input file. Notice that the records are not sorted. They are delimited by semicolons. They have the form: `name;age;salary`.

<img width="400" src="https://user-images.githubusercontent.com/30678180/40093055-526bf47c-5875-11e8-8c51-089a39d6807e.png">

#### The Main Menu

The main menu is displayed when the program begins:

<img width="200" src="https://user-images.githubusercontent.com/30678180/40093185-d9469150-5875-11e8-82ab-45bc0391e1b1.png">


#### Displaying the Database

The database has now been created. Each record is inserted into the list in sorted order. When selecting "List All Employees" (4), the database is displayed:

<img width="400" src="https://user-images.githubusercontent.com/30678180/40093281-469efa6c-5876-11e8-8d2e-d5e1ea58c904.png">

#### Entering a New User

The user can enter a new employee into the database by selecting "Add Employee" (1). They are asked to enter a name, age, and salary:

<img width="597" src="https://user-images.githubusercontent.com/30678180/40093385-d042d5cc-5876-11e8-84eb-c175cea82c07.png">

When we display the database again, we can see the record has been added (record #7):

<img width="400" src="https://user-images.githubusercontent.com/30678180/40094371-7214f048-587b-11e8-87a7-486e37e5fe8e.png">

#### Deleting a User

We can delete a user by selecting "Delete Employee" (2). We will delete the user we just entered into the database:

<img width="450" src="https://user-images.githubusercontent.com/30678180/40094441-d9b7e606-587b-11e8-934a-9793f0ec96be.png">

The user is no longer in the database:

<img width="400" src="https://user-images.githubusercontent.com/30678180/40094469-0e3f88d4-587c-11e8-998e-f5090572091b.png">

#### Searching for an Employee

We can search for employees to see if they are in the database:

<img width="450" src="https://user-images.githubusercontent.com/30678180/40094507-52e4fc94-587c-11e8-890b-326ca4ebffb5.png">

#### Saving the Database

Selecting "Save Employee Database" (5) will write the linked list to the original data file. The program will also save the database when the program exits. Notice that the data file is now in sorted order:

<img width="400" src="https://user-images.githubusercontent.com/30678180/40094575-9ee7c0ea-587c-11e8-983f-a8f5b225ea18.png">