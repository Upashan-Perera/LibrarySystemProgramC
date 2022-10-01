#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure prototypes
struct books{
    int id ;
    char name[100];
    struct books * next ;
};

struct orders{
    int bookId ;
    int customer_id ;
    char bookName[100];
    struct orders * next ;
};

struct stack{
    int bookID ;
    int customerID;
    char BOOKNAME[100] ;
    struct stack *nextPtr ;
};

//creating strucutre pointers
typedef struct books Books ;
typedef Books * BooksPtr ;

typedef struct orders Orders ;
typedef Orders * OrdersPtr ;

typedef struct stack Stack ;
typedef Stack * StackPtr ;

//function prototypes
Books* readFile(Books* startPtr, int SIZE);
int menu();
Books* display(BooksPtr startPtr);
Books* addBook(Books* startPtr, int SIZE);
int isEmpty( OrdersPtr headPtr );
int queue(OrdersPtr *headPtr , OrdersPtr *tailPtr , int count_lines2);
Books* dequeue(OrdersPtr *headPtr, OrdersPtr *tailPtr , Books* startPtr ,StackPtr topPtr , int *customer_num, int *searchKey );
void printfirstNode( OrdersPtr headPtr);
void printQueue( OrdersPtr *headPtr);
int newOrder(OrdersPtr *headPtr , OrdersPtr *tailPtr , BooksPtr startPtr , int SIZE , int count_lines2);
Stack* push( StackPtr *topPtr, int bookId , int customer_id , char BOOKNAME[100]);
Stack* printStack( StackPtr currentPtr );
Books* cancelOrder(Books* startPtr, Stack* topPtr);
int pop( StackPtr *topPtr );
Books* UpdateFile(Books* startPtr , int SIZE);

int main()
{
    //declaring variables
    FILE * fptr1 ;
    FILE * fptr2 ;
    int choice , count_lines = 0 , SIZE  , count_lines2 = 0 , customer_num , searchKey  ;
    BooksPtr startPtr = NULL ;
    OrdersPtr headPtr = NULL ;
    OrdersPtr tailPtr = NULL ;
    StackPtr topPtr = NULL ;
    char c , BOOKNAME[100];
    
    //to find the number of line there in the books.txt file originally
    fptr1 = fopen("books.txt", "r");
    
    for (c = getc(fptr1); c != EOF; c = getc(fptr1))
    {
        if (c == '\n') // Increment count if this character is newline
        {
            count_lines = count_lines + 1;
        }
    }
    
    fclose(fptr1);
    
    //to find the number of line there in the order.txt file originally
    fptr2 = fopen("order.txt", "r");
    
    for (c = getc(fptr2); c != EOF; c = getc(fptr2))
    {
        if (c == '\n') // Increment count if this character is newline
        {
            count_lines2 = count_lines2 + 1;
        }
    }
    
    fclose(fptr2);
    
    SIZE = count_lines ;
    
    //calling the readFile function to insert the data in the books file into a linked list
    Books * disp = readFile(startPtr, SIZE);
    
    //calling the queue function to insert the data in the order file into a queue linked list
    queue(&headPtr , &tailPtr , count_lines2 );
    
    //creating an infinite loop
    while(1)
    {
        //calling the menu function to displat the instructions and storing the choice
        choice = menu();    
        
        //creating a switch statement with the parameter of user's choice
        switch(choice)
        {
            case 1 :
                    //calling the display function
                    display(disp);
                    break;
            
            case 2 :
                    SIZE = SIZE + 1 ;
                    
                    //calling the addBook function to insert a new node to the linked list
                    addBook(disp , SIZE);
                    display(disp);
                    break;
            
            case 3 :
                    //calling the printfirstNode to print the first node in the queue
                    printfirstNode( headPtr);
                    break;
            
            case 4 :
                    //printing the whole data in the queue linked list
                    printQueue( &headPtr);
                    break;
            
            case 5 :
                    count_lines2 = count_lines2 + 1 ;
                    
                    //calling the newOrder function to insert a new node into the queue linked list
                    newOrder(&headPtr , &tailPtr , disp , SIZE , count_lines2);
                    break;
                    
            case 6 :
                    strcpy(BOOKNAME , headPtr->bookName);
                    
                    /*calling the dequeue function to remove the first order 
                    from the linked list and the queue list and storing the delete data*/ 
                    disp = dequeue(&headPtr, &tailPtr , disp , topPtr , &customer_num, &searchKey );
                    
                    //sstoring the deleted data into a stack linked list
                    push(&topPtr , searchKey , customer_num , BOOKNAME);
                    break;
                    
            case 7 :
                    /*cancelling the last order by re-entering the data into the linked list*/
                    cancelOrder(disp, topPtr);
                    
                    /*cancelling the last order by by removing the inserted
                    data from the stack linked list and*/
                    pop( &topPtr );
                    display(disp);
                    break;
                    
            case 8 :
                    //printing the data in the top of the stack which is the last proccessed order
                    printStack(topPtr);
                    break;
            
            case 9 :
                    //updating the books.txt file with the changes made in the above
                    UpdateFile(disp , SIZE);
                    break;
                    
            case 10 :
                    //End of the program
                    printf("End of the program\n");
                    exit(0);
                    
            default :
                    //giving the message to the user to enter a valid choice again
                    printf("Invalid choice \n");
                    break;
                    
        }
    }

    return 0;
}

//declaring the readFile function to store the data in the file into a linked list
Books* readFile(Books* startPtr, int SIZE)
{
    FILE *fptr ;
    char c ;
    int i ;
    BooksPtr newPtr ;
    BooksPtr currentPtr ;
    BooksPtr tempPtr ;
    BooksPtr previousPtr ;

    //opeing the books.txt file to read
    fptr = fopen("books.txt","r");
    
    if(fptr == NULL)
    {
        printf("File is not found");
        exit(0);
    }
    
    //creating a linked list by allocatiing memeory and storing in it
    for(i = 0 ; i < SIZE+1 ; i++)
    {
        newPtr = malloc(sizeof(Books));
     
        fscanf(fptr,"%d ",&newPtr->id);
        fgets(newPtr->name , 100 , fptr );
        newPtr->next = NULL ;
        
        previousPtr = NULL ;
        currentPtr = startPtr ; 
        
        //using a while loop in order to sort the linked list in alphabetical order of the book names
        while(currentPtr != NULL && strcmp(newPtr->name , currentPtr->name) > 0)
        {
            previousPtr = currentPtr ;
            currentPtr = currentPtr->next ;
        }
        
        if(previousPtr == NULL)
        {
            newPtr->next = startPtr ;
            startPtr = newPtr ;
        }
        else
        {
            previousPtr->next = newPtr ;
            newPtr->next = currentPtr ;
        }
    }
    
    fclose(fptr);
    
    return startPtr ;
 
}

//declaring the function menu to display the instructions
int menu()
{
    int choice ;
    
    printf("1. Display the current stock of books\n");
    printf("2. Add a new book to stock\n");
    printf("3. Display next order information \n");
    printf("4. Display all orders\n");
    printf("5. Add order to queue\n");
    printf("6. Process the next order\n");
    printf("7. Cancel last order\n");
    printf("8. Display info of last order\n");
    printf("9. Update book file \n");
    printf("10. Quit program\n");
    
    printf("\n");         
                
    //getting the user choice and returning it to the main
    printf("What is your choice? \n");
    scanf("%d",&choice);

    printf("\n");
    
    return choice ;
}

//declaring the display function to print all the data in the linked list
Books* display(Books* startPtr)
{
    BooksPtr currentPtr ;
    
    currentPtr = startPtr ;
    
    printf("------------------------------------\n");
 
    /* while not the end of the list*/
    while ( currentPtr != NULL )
    {
        printf("\n%d %s\n", currentPtr->id, currentPtr->name);
        currentPtr = currentPtr ->next;
    } /* end while*/
    
    printf("------------------------------------\n");
}

//declaring the addBook function to add a new node to the linked list
Books* addBook(Books* startPtr, int SIZE)
{
    BooksPtr tempPtr , currentPtr , newPtr , previousPtr;
    char name[100] , temp;
    int id ;
    
    //getting the user input of the new book
    printf("enter the book Id with 4 digits: ");
    scanf("%d",&id);
    printf("enter the book name (with first letter capital): ");
    scanf("%c",&temp);
    scanf("%[^\n]s",name);
    
    //allocating new memory to store
    newPtr = malloc(sizeof(Books));
     
    newPtr->id = id;
    strcpy(newPtr->name , name );
    newPtr->next = NULL ;
        
    previousPtr = NULL ;
    currentPtr = startPtr ; 
        
    //searching the idial location to place the new book in the linked list according to the alphabetical order
    while(currentPtr != NULL && strcmp(newPtr->name , currentPtr->name) > 0)
    {
        previousPtr = currentPtr ;
        currentPtr = currentPtr->next ;
    }
        
    if(previousPtr == NULL)
    {
        newPtr->next = startPtr ;
        startPtr = newPtr ;
    }
    else
    {
        previousPtr->next = newPtr ;
        newPtr->next = currentPtr ;
    }
    
    return startPtr;
}

//declaring the isEmpty function
int isEmpty( OrdersPtr headPtr )
{
    return headPtr == NULL;
}/* end function isEmpty */

//declaring the queue function to create a queue linked list witht the data from order.txt file
int queue(OrdersPtr *headPtr , OrdersPtr *tailPtr , int count_lines2)
{
	//declaring the variabels
    OrdersPtr newPtr ;
    OrdersPtr currentPtr ;
    FILE *fptr ;
    int i ;
    char c ;
    
    fptr = fopen("order.txt", "r");
 
	//storing the data in the array in queue list
    for(i = 0 ; i < count_lines2 ; i++)
    {
        newPtr = malloc(sizeof(Orders));
        
        if ( newPtr != NULL)
        {
            fscanf(fptr, "%d %d " ,&newPtr->bookId ,&newPtr->customer_id);
            fgets(newPtr->bookName , 100 , fptr );
            newPtr->next = NULL;
                    
            /* if empty, insert node at head */
            if ( isEmpty( *headPtr ))
            {
                *headPtr = newPtr;
            } /* end if */
            else
            {
                (*tailPtr)->next = newPtr;
            } /* end else */
    
            *tailPtr = newPtr;
        }
        else
        {
            printf( " Not inserted. No memory available.\n");

        }
    }
    
    fclose(fptr);
}

//declaring the printQueue function to print all the data in the queue linked list
void printQueue( OrdersPtr *headPtr)
{
    OrdersPtr currentPtr ; 
    
    currentPtr = *headPtr ;
    
    printf("------------------------------------\n");
 
    /* while not the end of the list*/
    while ( currentPtr != NULL )
    {
        printf("%d %d %s\n", currentPtr->bookId, currentPtr->customer_id, currentPtr->bookName);
        currentPtr = currentPtr ->next;
    } /* end while*/
    
    printf("------------------------------------\n");
}

//declaring the printfirstNode function print the data in the first node of the queue linked list
void printfirstNode( OrdersPtr headPtr)
{
    OrdersPtr currentPtr ; 
    
    currentPtr = headPtr ;
    
    printf("------------------------------------\n");

    printf("%d\t %d\t %s\n", currentPtr->bookId, currentPtr->customer_id, currentPtr->bookName);
 
    printf("------------------------------------\n");
}

//declaring the newOrder function to insert a new node to queue linked list
int newOrder(OrdersPtr *headPtr , OrdersPtr *tailPtr , BooksPtr startPtr , int SIZE , int count_lines2)
{
    FILE *fptr ;
    OrdersPtr tempPtr , currentPtr , newPtr;
    int id , bookID , customerID , m =0  ;
    char BOOKNAME[100];
    
    //getting the user input
    printf("enter the book Id with 4 digits: ");
    scanf("%d",&bookID);
    printf("enter the customer Id with 3 digits: ");
    scanf("%d",&customerID);
    
    while(startPtr != NULL)
    {
        
		//searching whether the input name matches with a name in the database
        if( bookID == startPtr->id)
        {
            //getting the bookname of the book using the book id
            strcpy(BOOKNAME , startPtr->name);
            startPtr = startPtr->next  ;
        }
        else
        {
            m = m + 1 ;
            startPtr = startPtr->next  ;
        }
    }
    
	//giving the message to the user if it is not found
    if(m == SIZE)
    {
        printf("\nSorry there is no book with ID %d \n",bookID);
    }
    
    currentPtr = *headPtr ;
    
    //allocating new memory to store the new node
    newPtr = malloc(sizeof(Orders));
        
        if ( newPtr != NULL)
        {
            newPtr->bookId = bookID ;
            newPtr->customer_id = customerID;
            strcpy(newPtr->bookName , BOOKNAME );
            newPtr->next = NULL;
                    
            /* if empty, insert node at head */
            if ( isEmpty( *headPtr ))
            {
                *headPtr = newPtr;
            } /* end if */
            else
            {
                (*tailPtr)->next = newPtr;
            } /* end else */
    
            *tailPtr = newPtr;
        }
        else
        {
            printf( " Not inserted. No memory available.\n");

        }
    
    //calling the printQueue function to print all the data
    printQueue(headPtr);
}

/*declaring the function dequeue to process the data in the 
first node in queue linked list by deleting data from the linked list*/
Books* dequeue(OrdersPtr *headPtr, OrdersPtr *tailPtr , Books* startPtr ,StackPtr topPtr , int *customer_num, int *searchKey )
{
	//intializing the variables
    BooksPtr tempPtr1 ; /* temporary node pointer */
    OrdersPtr tempPtr2 ;
    BooksPtr currentPtr ;
    StackPtr currentPtr1 ;
    BooksPtr previousPtr ;
    int book_num ;
    char book_title[100] ;
    
    if(headPtr == NULL)
    {
        printf("The list is Empty! \n");
    }
    else
    {

        *searchKey = (*headPtr)->bookId;
        
        currentPtr = startPtr ;
        
        //searching for the book details in the linked list using the book id in the queue linked list
        if( *searchKey == startPtr->id)
        {
                //storing the data in a temporary variable in order to return
                strcpy(book_title , startPtr->name);
                
                tempPtr1 = startPtr;
                startPtr = startPtr->next;
                free( tempPtr1 );
        }
        else
        {
            previousPtr = startPtr ;
            currentPtr = startPtr->next;
            
            while ( currentPtr != NULL && currentPtr->id != *searchKey)
            {
                previousPtr = currentPtr ;
                currentPtr = currentPtr ->next;
            }
            
            if ( currentPtr != NULL )
            {
                //storing the data in a temporary variable in order to return
                strcpy(book_title , currentPtr->name);
                tempPtr1 = currentPtr;
                previousPtr->next = currentPtr->next;
                
                //deleting the node
                free( tempPtr1 );
            } /* end if*/
        } 
        
        //storing the data in a temporary variable in order to return
        *customer_num = (*headPtr)->customer_id ;
        tempPtr2 = *headPtr ;
        
        *headPtr = (*headPtr)->next ;
        
        if ( *headPtr == NULL )
        {
            *tailPtr = NULL;
        }/* end if */
        
        free( tempPtr2 );
    
        printf("------------------------------------\n");
        
        printf("%d %d %s\n", *searchKey , *customer_num , book_title);
        
        printf("------------------------------------\n");
     
        //calling the display function to print the whole linked list
        display(startPtr);
    }
    
    return startPtr ;
} /* end function dequeue */

//declaring the push function to create a stack linked list of the processed orders
Stack* push( StackPtr *topPtr, int bookId , int customer_id , char BOOKNAME[100])
{
    StackPtr newPtr , currentPtr; /* pointer to new node */
    
    //allocating new memeory to store new data
    newPtr = malloc( sizeof( Stack ));
    
    /* insert the node at stack top */
    if ( newPtr != NULL)
    {
        newPtr->bookID = bookId;
        newPtr->customerID = customer_id;
        strcpy(newPtr->BOOKNAME , BOOKNAME);
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } /* end if */
    else /* no space available */
    {
        printf( "%d not inserted. No memory available.\n",bookId);
    }/* end else */
    
    return *topPtr;
} /* end function push */

//calling the printStack function to print the first node in the stack linked list
Stack* printStack( StackPtr topPtr )
{
    StackPtr currentPtr ;
    
    currentPtr = topPtr ;
    
    /* if stack is empty */
    if ( currentPtr == NULL )
    {
        puts( "The stack is empty.\n" );
    } /* end if */
    else
    {
        puts( "The last order is:" );

        //printing the details of the last order processed
        printf( "%d %d %s\n", currentPtr->bookID , currentPtr->customerID, currentPtr->BOOKNAME);
        currentPtr = currentPtr->nextPtr;
        
        printf("\n");
 
    }/* end else */
} /* end function printStack */

//declaring the cancelOrder to insert data of the first node of the queueu linked list again into the linked list
Books* cancelOrder(Books* startPtr, StackPtr topPtr)
{
    BooksPtr tempPtr , currentPtr , newPtr , previousPtr;
    char name[100] , temp;
    int id ;
    
    //allocating new memory to insert the new data
    newPtr = malloc(sizeof(Books));
    newPtr->id = topPtr->bookID;
    strcpy(newPtr->name , topPtr->BOOKNAME );
    newPtr->next = NULL ;
        
    previousPtr = NULL ;
    currentPtr = startPtr ; 
     
    //finding the idial location to insert node according to the alphabetical order   
    while(currentPtr != NULL && strcmp(newPtr->name , currentPtr->name) > 0)
    {
        previousPtr = currentPtr ;
        currentPtr = currentPtr->next ;
    }
        
    if(previousPtr == NULL)
    {
        newPtr->next = startPtr ;
        startPtr = newPtr ;
    }
    else
    {
        previousPtr->next = newPtr ;
        newPtr->next = currentPtr ;
    }
    
    return startPtr;
}

//declaring the pop function to pop the first node of the stack linked list
int pop( StackPtr *topPtr )
{
    StackPtr tempPtr; /* temporary node pointer */
    
    tempPtr = *topPtr;
    *topPtr = ( *topPtr )->nextPtr;
    
    //deleting the node
    free( tempPtr );
    
} /* end function pop */

//declaring the UpdateFile function to update the books.txt file with the new changes made
Books* UpdateFile(Books* startPtr , int SIZE)
{
    Books array[SIZE];
    FILE *fptr ;
    BooksPtr currentPtr ;
    Books tempPtr;
    int i , j ;
    
    currentPtr = startPtr ;
 
    //copying the linked list data in to an array
    for(i =0 ; i < SIZE ; i++)
    { 
        array[i].id = currentPtr->id ;
        strcpy(array[i].name , currentPtr->name);
        currentPtr = currentPtr ->next;
    } 
    
    //sorting the array according to the ascending order of the book id
    for (i = 0; i < SIZE; ++i) 
    {
        for (j = i + 1; j < SIZE; ++j)
        {
            if (array[i].id > array[j].id) 
            {
                tempPtr =  array[i];
                array[i] = array[j];
                array[j] = tempPtr;
            }
        }
    }
    
    fptr = fopen("books.txt","w");
    
    //printing the data in the file 
    for(i =0 ; i < SIZE ; i++)
    { 
        fprintf(fptr ,"%d %s",array[i].id,array[i].name);
    } /* end while*/
    
    fclose(fptr);
}
