#include <fstream>
#ifndef INVENTORY_H
#define INVENTORY_H
using namespace std;
#include "book.h"
struct node{
		Book book;
		node *next;
};
class Inventory
{
        public:
                Inventory();
                void printAll();
                void readIn();
                void printMenu();
                void menu();
                void search();
                void find();
                void addBook();
                int checkIsbn(int newIsbn);
                int checkInStock(int newInStock);
                double checkPrice(double newPrice);
                //void addReader(int newIsbn, char newTitle[], char newAuthor[], char newPublisher[], double newPrice, int newInStock);
                void buildList(int tempISBN, char tempTitle[],char tempAuthor[], char tempPublisher[], double tempPrice, int tempInStock);
                void modify();
                void printModMenu();
                void changeISBN();
                void changeTitle();
                void changeAuthor();
                void changePublisher();
                void changeInStockTotal();
                void changePrice();
                void writeOut();
		void deleteBook();
        private:
		node *head, *tail, *previous, *current;
		bool found;      	//I use bool 'found' in many functions to know whether user found book or not-
		int size;  		//so I can reply appropriately(also used in buildList alrgorith)
};

#endif

