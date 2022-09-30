# LibrarySystemProgramC
A system for a book library using C language

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 Functions -:
 
 Print the whole book database
 Add a new book to the system
 Retrieve and print the first book hold request
 Retrieve and print all the book hold requests
 Processing book hold requests and storing all the processed request in another list
 Undo a processed request
 Updating the book database
 Updating the available book list database
 
 ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 

Theories used -: Advanced C language concepts, queue Linked Lists, Stack Linked Lists, file reading/write/delete/update
                 Open a file (database) and read/overright/delete and then update/save
                 Storing/Updating/Print data in queue/stack linked lists 

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

In depth Description -: 

This program is for a library system. Initially, the system opens the books.txt file and read the book details in it and the data is stored in a linked list which is in the alphabetical order of the book name. Then the program will open the order.txt file which contains the orders books by the customers in order and it is stored in a queue linked list. Then we give the user to choose an option by running the menu function. By the first option, it prints the data in the linked list. By the second option, it enables you to add a new book to the system (add a new node to the linked list). By the third option it prints the head pointer in the queue function which is the first order. By the 4th option, it prints all the data in the queue linked list. In the sixth option, the user can choose to process the order by deleting the book details in the linked list and adding them to a stack linked list. As well as the book details of the processed order in the queue linked list is deleted. By the seventh option, it gives the user to undo the processed order by adding the booking details again into the linked list, and removing the top pointer in the stack linked list. In the 8th order, it prints the top pointer of the stack linked list. In the ninth option, it updates the book.txt file by deleting all the in it and again inserting the updated book list in to the file. By the last function, it terminates the whole program. 
