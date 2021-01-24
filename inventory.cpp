#include "inventory.h"

Inventory::Inventory()
{
	size = 0;
	head = NULL;
	tail = NULL;
	previous = NULL;
}

void Inventory::printAll()
{
	node * current = head;
	while(current)
	{
		current->book.print();
		current = current->next;
	}	
}

void Inventory::readIn()
{
        char tempTitle[MAX_STR] = {'\0'};
        char tempAuthor[MAX_STR] = {'\0'};
        char tempPublisher[MAX_STR] = {'\0'};
        int tempISBN = 0;
        int tempInStock = 0;
        double tempPrice = 0;
        ifstream infile;
        infile.open("inventory.txt");
        if(!infile)
        {
                        cout << " " << endl;
                        cout << "Failed to open file " << endl;
                        return;
        }
        char c = infile.peek();
        infile >> size;
        infile.ignore();
        while(!infile.eof() && size <= MAX_STR && c != '\n')
        {
                infile >> tempISBN;
                infile.ignore(MAX_STR, '\n');
                infile.getline(tempTitle, MAX_STR);
                infile.getline(tempAuthor, MAX_STR);
                infile.getline(tempPublisher, MAX_STR);
                infile >> tempPrice;
                infile.ignore(MAX_STR, '\n');
 		infile >> tempInStock;
                infile.ignore(MAX_STR, '\n');
                c = infile.peek();
                buildList(tempISBN, tempTitle, tempAuthor, tempPublisher, tempPrice, tempInStock);
        }
        infile.close();
}

void Inventory::buildList(int tempISBN, char tempTitle[], char tempAuthor[], char tempPublisher[], double tempPrice, int tempInStock)
{
	tail = NULL;
	char currentTitle[MAX_STR] = {'\0'};
	node*  newNode = new node;
	newNode->book.setISBN(tempISBN);
	newNode->book.setTitle(tempTitle);
	newNode->book.setAuthor(tempAuthor);
	newNode->book.setPublisher(tempPublisher);
	newNode->book.setInStock(tempInStock);
	newNode->book.setPrice(tempPrice);
	newNode -> next = NULL;
	if(head == NULL)
        {
                head = newNode;
                tail = newNode;
        }
	else
	{
		current = head;
		found = false;
		while(current != NULL && !found)
		{
			current->book.getTitle(currentTitle);
			if(strcmp(currentTitle, tempTitle) > 0)
			{
				found = true;
			}
			else
			{
				previous = current;
				current = current->next;
			}
		}
		if(current == head)
		{
			newNode->next = head;
			head = newNode;
		}
		else
		{
			previous->next = newNode;
			newNode->next = current;
			if(current == NULL)
			{
				tail = newNode;
			}
		}
	}
}

void Inventory::find()
{
	found = false;
	current = head;//current is private/global to the class, it must be reset to head in each function or it will be where i left it at last time I traversed with it
        int newIsbn, tempISBN;
        cout << " " << endl;
        cout << "Enter isbn of book: " << endl;
        cin >> newIsbn;
        cin.ignore();
        while(current)
        {
                tempISBN = current->book.getISBN();
                if(tempISBN == newIsbn)
                {
                        current->book.print();
			found = true;
                }
		current = current->next;//equivalent to what has been up until now "++" incrementer 
        }
	if(newIsbn < 0)
        {
        	cout << " " << endl;
                cout << "that number is negative" << endl;
        }
	else if(found == false)
	{
               	cout << " " << endl;
               	cout << " ISBN of book does not exist " << endl;	
	}
}

void Inventory::search()
{
	current = head;
	found = false;
        char tempPublisher[MAX_STR] = {'\0'};
        char search[MAX_STR] = {'\0'};
        cout << " " << endl;
        cout << "Enter publisher of book: " << endl;
	cout << " " << endl;
        cin.getline(search, MAX_STR);
	cout << " " << endl;
        for(int i = 0; i < size; i++)//I wanted to try both loops, not sure why you would want the size yet but im trying to figure it out, doesnt seeem quicker than head
        {
                current->book.getPublisher(tempPublisher);
                if(strcmp(search,tempPublisher) == 0)
                {
                        current->book.print();
			found = true;
                }
		current = current->next;
        }
	if(found == false)
	{
        	cout << " " << endl;
        	cout << "That publisher does not exist " << endl;
	}
}

void Inventory::menu()
{
        char choice;
        bool gameOn = true; //breaks the repeating menu when false
        while(gameOn != false)
        {
                printMenu();
                cin >> choice;
                cin.ignore();
                switch(choice)
                {
                        case '1':
                                printAll();
                                break;
                        case '2':
                                search();
                                break;
                        case '3':
                                find();
                                break;
                        case '4':
                                addBook();
                                break;
                        case '5':
                                modify();
                                break;
			case '6':
				deleteBook();
				break;
                        case '7':// quits menu
                                cout << " " << endl;
                                cout << "*** END OF PROGRAM **" << endl;
                                gameOn = false;
                                break;
                        default:
                                cout << " " << endl;
                                cout << "Choose between 1 and 6 " << endl;
                                break;
                }
        }
}

void Inventory::printMenu()
{
                cout << " " << endl;
                cout << " " << endl;
                cout << "********MAIN MENU******** " << endl;
                cout << "1 - Print Inventory " << endl;
                cout << "2 - Search by Publisher " << endl;
                cout << "3 - Find book by ISBN Number " << endl;
                cout << "4 - Add Book " << endl;
                cout << "5 - Modify " << endl;
		cout << "6 - Delete " << endl;
                cout << "7 - quit " << endl;
                cout << "Enter choice: " << endl;
}

void Inventory::addBook()
{
        int tempIsbn;
        int  tempInStock;
        char tempTitle[MAX_STR];
        char tempAuthor[MAX_STR];
 	char tempPublisher[MAX_STR];
        double tempPrice;
        cout << " " << endl;
        cout << "Book's ISBN? (must be unique) " << endl;
        cin >> tempIsbn;
        cin.ignore();
        tempIsbn = checkIsbn(tempIsbn);
        cout << " " << endl;
        cout << "Title:" << endl;
        cin.getline(tempTitle, MAX_STR);
        cout << " " << endl;
        cout << "Author? " << endl;
        cin.getline(tempAuthor, MAX_STR);
        cout << " " << endl;
        cout << "Publisher? " << endl;
        cin.getline(tempPublisher, MAX_STR);
        cout << " " << endl;
        cout << "Price?" << endl;
        cin >> tempPrice;
        cin.ignore();
        tempPrice = checkPrice(tempPrice);
        cout << " " << endl;
        cout << "In Stock Total?( < 0) " << endl;
        cin >> tempInStock;
        cin.ignore();
        tempInStock = checkInStock(tempInStock);
	buildList(tempIsbn, tempTitle, tempAuthor, tempPublisher, tempPrice, tempInStock);
        size++;
}

/*void Inventory::addReader(int tempIsbn, char tempTitle[], char tempAuthor[], char tempPublisher[], double tempPrice, int tempInStock)
{
	found = false;
	current = head;
	previous = NULL;
	node *newNode = new node;
	newNode->next = NULL;
	char currentTitle[MAX_STR] = {'\0'};	
	newNode->book.setISBN(tempIsbn);
	newNode->book.setTitle(tempTitle);
	newNode->book.setAuthor(tempAuthor);
	newNode->book.setPublisher(tempPublisher);
	newNode->book.setPrice(tempPrice);
	newNode->book.setInStock(tempInStock);
                while(current != NULL && !found)
                {
                        current->book.getTitle(currentTitle);
                        if(strcmp(currentTitle, tempTitle) > 0)
                        {
                                found = true;
                        }
                        else
                        {
                                previous = current;
                                current = current->next;
                        }
                }
                if(current == head)
                {
                        newNode->next = head;
                        head = newNode;
                }
                else
                {
                        previous->next = newNode;
                        newNode->next = current;
                        if(current == NULL)
                        {
                                tail = newNode;
                        }
                }
	if(found == true)
	{
		size++;
	}
}
*/
int Inventory::checkIsbn(int newIsbn)
{
        int tempIsbn;
	node *current = head;
        do
        {
                while(current)
                {
                        tempIsbn = current->book.getISBN();
                        if(newIsbn == tempIsbn)
                        {
                                cout << " " << endl;
                                cout << "That ISBN is already in the inventory. ";
                                cout << "Please re-enter." << endl;
                                cin >> newIsbn;
                                cin.ignore();
                        }
			current = current->next;
                }
        }while(tempIsbn == newIsbn);
        return newIsbn;
}

int Inventory::checkInStock(int newInStock)
{
        while(newInStock < 0)
        {
                cout << " " << endl;
                cout << "Negative price.  Please re-enter" << endl;
                cin >> newInStock;
                cin.ignore();
        }
        return newInStock;
}

double Inventory::checkPrice(double newPrice)
{
        while(newPrice < 0)
        {
                cout << " " << endl;
                cout << "Negative price.  Please re-enter" << endl;
                cin >> newPrice;
                cin.ignore();
        }
	return newPrice;
}

void Inventory::modify()
{
        char choice;
        bool gameOn = true; //breaks the repeating menu when false
        while(gameOn != false)
        {
                printModMenu();
                cin >> choice;
                switch(choice)
                {
                        case '1':
                                changeISBN();
                                break;
                        case '2':
                                changeTitle();
                                break;
                        case '3':
                                changeAuthor();
                                break;
                        case '4':
                                changePublisher();
                                break;
                        case '5':
                                changePrice();
                                break;
                        case '6':
                                changeInStockTotal();
                                break;
                        case '7':
                                gameOn = false;
                                break;
                        default:
                                break;
                }
        }

}

void Inventory::printModMenu()
{
                cout << " " << endl;
		cout << " " << endl;
                cout << "********Modify******** " << endl;
                cout << "1 - ISBN " << endl;
                cout << "2 - title " << endl;
                cout << "3 - author " << endl;
                cout << "4 - publisher " << endl;
                cout << "5 - price " << endl;
                cout << "6 - In Stock Total " << endl;
                cout << "7 - go back to main menu" << endl;
                cout << "Enter choice: " << endl;
}

void Inventory::changeISBN()
{
	current = head;
        int currentISBN, newISBN;
        cout << " " << endl;
        cout << "ISBN number of book to modify? " << endl;
        cin >> newISBN;
        cin.ignore();
        while(current)
        {
                currentISBN = current->book.getISBN();
                if(newISBN == currentISBN)
                {
                        cout << " " << endl;
                        cout << "New ISBN? " << endl;
                        cin >> newISBN;
                        cin.ignore();
                        current->book.setISBN(newISBN);
                        return;
                }
		current = current->next;
        }
        if(newISBN < 0)
        {
                cout << " " << endl;
                cout << "that number is negative" << endl;
        }
        else
        {
                cout << " " << endl;
                cout << " ISBN of book does not exist " << endl;
        }
}

void Inventory::changeTitle()
{
	previous = NULL;
	current = head;
        int newIsbn, currentIsbn;
        char newTitle[MAX_STR] = {'\0'};
        cout << " " << endl;
        cout << "ISBN number of book to modify? " << endl;
        cin >> newIsbn;
        cin.ignore();
        while(current)
        {
                currentIsbn = current->book.getISBN();
                if(newIsbn == currentIsbn)
                {
                        cout << " " << endl;						//this code find the book user wants to change, finds its place in the link list
                        cout << "Title? " << endl;					//and it gets the rest of the information on that specifice book, so that it can 
                        cin.getline(newTitle, MAX_STR);					// delete it, and than take the info stored in the temporary variables, and than run 
        		int  tempInStock;						// them into the same build list function 				
        		char tempAuthor[MAX_STR];
        		char tempPublisher[MAX_STR];
        		double tempPrice;
			tempInStock = current->book.getInStock();
			current->book.getAuthor(tempAuthor);
			current->book.getPublisher(tempPublisher);
			tempPrice = current->book.getPrice();
			previous -> next = current -> next;
			delete current;										//here delete the node that contained the book with old
			buildList(currentIsbn, newTitle, tempAuthor, tempPublisher, tempPrice, tempInStock);	//title, new one created in buildList function
			return;
                }
		previous = current;
		current = current->next;
        }
        if(newIsbn < 0)
        {
                cout << " " << endl;
                cout << "that number is negative" << endl;
        }
        else
        {
                cout << " " << endl;
                cout << " ISBN of book does not exist " << endl;
        }
}

void Inventory::changeAuthor()
{
	current = head;
        int newIsbn, currentIsbn;
        char newAuthor[MAX_STR] = {'\0'};
        cout << " " << endl;
        cout << "ISBN number of book to modify? " << endl;
        cin >> newIsbn;
        cin.ignore();
 	while(current)
	{
                currentIsbn = current->book.getISBN();
                if(newIsbn == currentIsbn)
                {
                        cout << " " << endl;
                        cout << "Author? " << endl;
                        cin.getline(newAuthor, MAX_STR);
                        current->book.setAuthor(newAuthor);
                        return;
                }
		current = current->next;
        }
        if(newIsbn < 0)
        {
                cout << " " << endl;
                cout << "that number is negative" << endl;
        }
        else
        {
                cout << " " << endl;
    //back = (back + r) % capacity;
                cout << " ISBN of book does not exist " << endl;
        }
}

void Inventory::changePublisher()
{
	current = head;
        int newIsbn, currentIsbn;
        char newPublisher[MAX_STR] = {'\0'};
        cout << " " << endl;
        cout << "ISBN number of book to modify? " << endl;
        cin >> newIsbn;
        cin.ignore();
        while(current)
        {
                currentIsbn = current->book.getISBN();
                if(newIsbn == currentIsbn)
                {
                        cout << " " << endl;
                        cout << "Publisher? " << endl;
                        cin.getline(newPublisher, MAX_STR);
                        current->book.setPublisher(newPublisher);
                        return;
		}
		current = current->next;
	}
	if(newIsbn < 0)
        {
                cout << " " << endl;
                cout << "that number is negative" << endl;
        }
        else 
        {
                cout << " " << endl;
                cout << " ISBN of book does not exist " << endl;
        }

 }

void Inventory::changeInStockTotal()
{
        int currentIsbn, newIsbn, newInStock;
        cout << " " << endl;
        cout << "ISBN number of book to modify? " << endl;
        cin >> newIsbn;
        cin.ignore();
	current = head;
        while(current)
        {
                currentIsbn = current->book.getISBN();
                if(newIsbn == currentIsbn)
                {
                        cout << " " << endl;
                        cout << "In Stock Total? " << endl;
                        cin >> newInStock;
                        cin.ignore();
                        newInStock = checkInStock(newInStock);
                        current->book.setInStock(newInStock);
                        return;
                }
		current = current->next;
	}
        if(newIsbn < 0)
        {
                cout << "  " << endl;
                cout << "that number is negative" << endl;
        }
        else
        {
                cout << " " << endl;
                cout << " ISBN of book does not exist " << endl;
        }
}

void Inventory::changePrice()
{
        int currentIsbn, newIsbn;
        double newPrice;
        cout << " " << endl;
        cout << "ISBN number of book to modify? " << endl;
        cin >> newIsbn;
        cin.ignore();
	current = head;
        while(current != NULL)
        {
                currentIsbn = current->book.getISBN();
                if(newIsbn == currentIsbn)
                {
                        cout << " " << endl;
                        cout << "Price? " << endl;
                        cin >> newPrice;
                        cin.ignore();
                        newPrice = checkPrice(newPrice);
                        current->book.setPrice(newPrice);
                }
		current = current->next;
        }
        if(newIsbn < 0)
        {
                cout << " " << endl;
                cout << "that number is negative" << endl;
        }
        else
        {
                cout << " " << endl;
                cout << " ISBN of book does not exist " << endl;
        }
}

void Inventory::deleteBook()
{
	int newIsbn, tempIsbn;
	node *current = head;
	node *previous = NULL;
	cout << "ISBN of book to delete? " << endl;
	cin >> newIsbn;
	while(current)
	{
		tempIsbn = current->book.getISBN();
		if(tempIsbn == newIsbn)
		{
			if(current == head)
			{
				head = current->next;
				delete current;
				return;
			}
			else if(current->next == NULL)
			{
				previous->next = NULL;
				delete current;
				return;
			}
			else
			{
				previous->next = current->next;
				current = current->next;
				delete current;
				return;
			}
		}
		previous = current;
		current = current->next;
	}
	if(newIsbn < 0)
	{
		cout << "ISBN must be positive " << endl;
		return;
	}
	else
	{
		cout << "ISBN does not exist " << endl;
	}
}

void Inventory::writeOut()
{
        char tempTitle[MAX_STR] = {'\0'};
        char tempAuthor[MAX_STR] = {'\0'};
        char tempPublisher[MAX_STR] = {'\0'};
        int tempISBN = 0;
        int tempInStock = 0;
        double tempPrice = 0;
        ofstream outfile;
        outfile.open("inventory.txt");
        outfile << size << endl;
	current = head;
        while(current)
        {
                tempISBN = current->book.getISBN();
                outfile << tempISBN << endl;
                current->book.getTitle(tempTitle);
                outfile << tempTitle << endl;
                current->book.getAuthor(tempAuthor);
                outfile << tempAuthor << endl;
                current->book.getPublisher(tempPublisher);
                outfile << tempPublisher << endl;
                tempPrice = current->book.getPrice();
                outfile << tempPrice << endl;
                tempInStock = current->book.getInStock(); 
                outfile << tempInStock << endl;
		current = current->next;
        }
        outfile.close();
}


