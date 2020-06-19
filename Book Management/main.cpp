#include <iostream>
#include<string.h>
#include<fstream>
#include<stdio.h>
#include<conio.h>
using namespace std;

class Book{
private:
    int bookid;
    char title[20];
    float price;

public:
    Book()
    {

        bookid=0;
        strcpy(title,"No title");
        price=0;
    }
    void getBookData()
    {
        cout<<"Enter book_id, title and price of a book \n";
        cin>>bookid;
        cin.ignore();
        cin.getline(title,19);
        cin>>price;

    }
    void showBookData()
    {

        cout<<"\n"<<bookid<<"   "<<title<<"     "<<price;
    }
    int storeBookData();
    void viewAllData();
    // here in this function will give the address
    void searchBook(char *);
    void deleteBook(char *);
    void updateBook( char *);




};

int Book::storeBookData()
{

    if(bookid==0 && price==0)
    {

        cout<<"Book data not initialized";
        return(0);
    }
    ofstream fout;
    fout.open("my_file.DOCX",ios::app | ios::binary);
    fout.write((char*)this, sizeof(*this));
    fout.close();
    return (1);


}

void Book::viewAllData(){

ifstream fin;
fin.open("my_file.DOCX", ios::in | ios::binary);
if(!fin)
{

    cout<<"\n File not found";
}
else
{
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof()){
        showBookData();
        fin.read((char*)this,sizeof(*this));
    }
    fin.close();

}

}

void Book :: searchBook(char *t)
{
    ifstream fin;
    fin.open("my_file.DOCX", ios::in | ios :: binary);
    if (!fin){
        cout<<" \n File not Found";
    }
    else
    {
        int flag =0;
        fin.read((char*) this, sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(t,title))
            {
                showBookData();
                //return;
                flag=1;
            }
            fin.read((char*) this ,sizeof(*this));

        }
        fin.close();
        if(flag==0)
        {

            cout<<"\nThis Book is not in Library";
        }
    }

}

void Book :: deleteBook(char *t)
{
    ifstream fin;
    ofstream fout;
    fin.open("my_file.DOCX", ios :: in | ios:: binary);
    if (!fin)
    {
        cout<<"\n File Not Found";

    }
    else{
           // getch();
        fout.open("temp_file.DOCX", ios::out |ios::binary);
        //getch();
        fin.read((char*) this, sizeof(*this));
        while(!fin.eof())
        {
            if(strcmp(title,t))
            {
                fout.write((char*) this, sizeof(*this));

            }
            fin.read((char*) this, sizeof(*this));
        }

    }
    fin.close();
    fout.close();
   // getch();
    remove("my_file.DOCX");
   // getch();
    rename("temp_file.DOCX","my_file.DOCX");

}

void Book :: updateBook(char * t)
{
    // fstream when want to read and write at same time at same file
   fstream file;
   file.open("my_file.DOCX", ios::in | ios::out | ios::ate|ios::binary);
   // g is a pointer in fstream which is pointing to starting point
   file.seekg(0);
   file.read((char*)this ,sizeof(*this));

   while(!file.eof())
   {
       if (!strcmp(title,t))
       {
           getBookData();
           file.seekp(file.tellp()- sizeof(*this));
           file.write((char*)this ,sizeof(*this));
           return;
       }
       file.read((char*)this,sizeof(*this));

   }
   file.close();


}
int menu()
{
    int choice;
    cout<<"\n **********WELCOME TO BOOK MANAGEMENT *********\n";
    cout<<"\n           1.Insert Book record                ";
    cout<<"\n           2.View all Book record              ";
    cout<<"\n           3.Search Book record                ";
    cout<<"\n           4.Delete Book record                ";
    cout<<"\n           5.Update Book record                ";
    cout<<"\n           6.Exit                              ";
    cout<<"\n\n----Enter the choice --:" ;
    cin>>choice;
    return choice;

}


int main()
{
    Book b1;
    while(1)
    {
        system("cls");
        switch(menu())
        {
            case 1:
                b1.getBookData();
                b1.storeBookData();
                cout<<"\n Record inserted successfully";
                break;
            case 2:
                b1.viewAllData();
                break;
            case 3:
                cout<<"\nEnter the Book Name you want to search : ";
                char title[20];
                cin.ignore();
                cin.getline(title,19);
                b1.searchBook(title);
                break;

            case 4:
                cout<<"\n Enter the name of Book you want to Delete : ";
               // char title[20];
                cin.ignore();
                cin.getline(title,19);
                b1.deleteBook(title);
                cout<<"\nThis Book "<<"("<<title<<")"<<"has been deleted";
                break;
            case 5:
                cout<<"\nEnter book title to update record : ";
                //char title[20];
                cin.ignore();
                cin.getline(title,19);
                b1.updateBook(title);
                break;

            case 6:
                cout<<"\nThank you for using this application ";
                cout<<"\nPress any key to exit";
                getch();
                exit(0);
            default:
                cout<<"\n Invalid choice";


        }
        getch();

    }

    return 0;
}
