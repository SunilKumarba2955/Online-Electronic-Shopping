#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <fstream>

using namespace std;

class products
{
    char name[30],brand[30],colour[30],category[25],sub_category[30];
    int price,unique_code;
public:
    void display_all();
    int number_of_objects();
    void display_all(char*);
    void addcart(int);
    void viewcart();
    void delete_items(int);
    void buy_products();
};

int products::number_of_objects()
{
    ifstream in;

    in.open("data_file.txt",ios::in);
    in.seekg(0);
    int i=0;
    while(in)
    {
        in >> sub_category >> name >> unique_code >> brand >> colour >> price;
        i++;
    }
    in.close();
    return i-1;
}

void products::display_all()
{
    int n=number_of_objects();

    ifstream in;
    in.open("data_file.txt",ios::in);

    in.seekg(0);
    cout.setf(ios::left);
    cout << "\n\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n\t\t" << setw(7) << "SL.No." << setw(25) << "Sub Category" << setw(25) << "Name" << setw(15) << "Unique Code" << setw(20) << "Brand" << setw(20) << "Colour" << setw(15) << "Price"  << endl;
    cout << "\n\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;

    for(int i=0; i<n && in; i++)
    {
        cout << endl;
        in >> sub_category >> name >> unique_code >> brand >> colour >> price;
        cout.setf(ios::left);
        cout << "\t\t" << setw(7) << i+1 << setw(25) << sub_category << setw(25) << name << setw(15) << unique_code << setw(20) << brand << setw(20) << colour << "$"<< setw(15) << price << endl;
    }
    cout << "\n\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    in.close();
}

void products::display_all(char *cat)
{
    int n=number_of_objects();

    ifstream in;
    in.open("data_file.txt",ios::in);

    in.seekg(0);
    cout.setf(ios::left);
    cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n\t\t\t" << setw(7) << "SL.No." << setw(25) << "Sub Category" << setw(25) << "Name" << setw(15) << "Unique Code" << setw(20) << "Brand" << setw(20) << "Colour" << setw(15) << "Price"  << endl;
    cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;

    int k=1;
    for(int i=0; i<n && in; i++)
    {
        in >> sub_category >> name >> unique_code >> brand >> colour >> price;
        if(strcmp(cat,sub_category)==0)
        {
            cout << endl;
            cout.setf(ios::left);
            cout << "\t\t\t" << setw(7) << k++ << setw(25) << sub_category << setw(25) << name << setw(15) << unique_code << setw(20) << brand << setw(20) << colour << "$"<< setw(15) << price << endl;
        }
    }
    cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    in.close();
}

typedef struct node             /// Declaring a node
{
    char name[30],brand[30],colour[30],category[25],sub_category[30];
    int price,unique_code;
    struct node *next;
} NODE;

NODE *root=NULL;

void products::addcart(int unique)
{
    int flag=0;

    int n=number_of_objects();
    NODE *newnode,*temp;
    newnode=(NODE*)malloc(sizeof(NODE));     /// Allocating memory dynamically for newnode

    ifstream in;
    in.open("data_file.txt",ios::in);

    in.seekg(0);
    cout.setf(ios::left);
    for(int i=0; i<n && in; i++)
    {
        in >> sub_category >> name >> unique_code >> brand >> colour >> price;
        if(unique_code==unique)
        {
            flag=1;
            strcpy(newnode->brand,brand);
            strcpy(newnode->sub_category,sub_category);
            strcpy(newnode->name,name);
            strcpy(newnode->colour,colour);
            newnode->unique_code=unique;
            newnode->price=price;
            newnode->next=NULL;

            if(root==NULL)
                root=newnode;         /// For empty list
            else
            {
                temp=root;
                while(temp->next!=NULL)             /// traversing last node to insert newnode at the end
                    temp=temp->next;
                temp->next=newnode;                 /// inserting newnode at the end
            }
            cout << "\n\t\t\t\t" << unique << " Product is added to the cart\n" << endl;
            cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
    if(flag==0)
    {
        cout << "\n\t\t\t\t" << unique << " Product is not available\n" << endl;
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

void products::viewcart()
{
    NODE *temp=root;
    if(temp==NULL)
    {
        cout << "\n\t\t\t\tCart is Empty!!! Please add the products to buy " << endl;
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\t\t\t\t \"Cart Items\" " << endl;
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\n\t\t\t" << setw(7) << "SL.No." << setw(25) << "Sub Category" << setw(25) << "Name" << setw(15) << "Unique Code" << setw(20) << "Brand" << setw(20) << "Colour" << setw(15) << "Price"  << endl;
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;

        int k=1,total=0;
        while(temp!=NULL)
        {
            cout << endl;
            cout.setf(ios::left);
            total+=temp->price;
            cout << "\t\t\t" << setw(7) << k++ << setw(25) << temp->sub_category << setw(25) << temp->name << setw(15) << temp->unique_code << setw(20) << temp->brand << setw(20) << temp->colour << "$"<< setw(15) << temp->price << endl;
            temp=temp->next;
        }
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\n\t\t\t\t\t\t\t\t Total price of Cart Items : "<< "$" << setw(15) << total << endl;
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

void products::buy_products()
{
    NODE *temp=root;
    if(temp==NULL)
    {
        cout << "\n\t\t\t\tCart is Empty!!! Please add the products to buy " << endl;
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    else
    {
        int k=1,total=0;
        char user_name[50];
        char user_address[50];
        while(temp!=NULL)
        {
            total+=int(temp->price);
            temp=temp->next;
        }
        cout << "\n\n\t\t\t Please enter your details to Buy" << endl;
        cout << "\n\t\t\t\t Enter your name : " ;
        getchar();
        scanf("%[^\n]s",user_name);
        getchar();
        cout << "\n\t\t\t\t Enter the delivery address : " ;
        scanf("%[^\n]s",user_address);
        getchar();
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t Summary" << endl;
        cout << "\n\t\t\t\t\t\t\t\t Your Name : " << setw(30) << user_name << endl;
        cout << "\n\t\t\t\t\t Delivery address : " << setw(50) << user_address << endl ;
        cout << "\n\t\t\t\t\t\t\t\t Total Payable amount : " << "$" << setw(15) << total << endl ;
        cout << "\n\t\t\t\t\t\t\t\t Thanks for Purchasing.......:)" << endl ;
        cout << "\n\t\t\t\t\t\t\t\t\t\t\t Visit Again!!!" << endl ;
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
        exit(0);
    }
}

void products::delete_items(int unique)
{
    int key;
    NODE *temp,*prev=NULL;
    if(root==NULL)
    {
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\n\t\t\t Empty cart " << endl;
        cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    }
    else
    {

        temp=root;
        while(temp!=NULL && temp->unique_code!=unique)
        {
            prev=temp;
            temp=temp->next;
        }

        if(temp==NULL)
        {
            cout << "\n\t\t\t No such " << unique << " product is exist in cart" << endl;
            cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
        }
        else
        {
            if(prev==NULL)
                root=root->next;
            else
                prev->next=temp->next;
            free(temp);
            cout << "\n\t\t\t " << unique << " product is deleted from the cart" << endl;
            cout << "\n\t\t\t----------------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
}

int main()
{
    int choice=7;
    products p;
    cout << "\n\n\n\t\t\t\t\t\t      ---------------------------------------------------------- " << endl;
    cout << "\n\t\t\t\t\t\t\t   \"Welcome to Goblins On-line Electronic Shopping\" " << endl;
    cout << "\n\t\t\t\t\t\t      ---------------------------------------------------------- " << endl;
    while(choice!=0)
    {
        cout.setf(ios::left);
        cout << "\n\n\t\t\t   ";
        cout << setw(25) << "1. View All products" << setw(25) << "2. Mobiles" << setw(25) << "3. Laptops" << setw(25) << "4. Headphones" << setw(25) << "5. Air pods" << endl;
        cout << "\n\n\t\t\t   ";
        cout << setw(25) << "6. Air coolers" << setw(25) << "7. Mouse" << setw(25) << "8. Washing Machine" << setw(25) << "9. Television" << setw(25) << "10. Keyboards" << endl;
        cout << "\n\n\t\t\t   ";
        cout << setw(25) << "11. Printers" << setw(25) << "12. Smart Watches" << setw(25) << "13. Speakers" << setw(25) << "14. Alexa Devices" << setw(25) << "15. fans" << endl;
        cout << "\n\n\t\t\t   ";
        cout << setw(25) << "16. Tablet" << setw(25) << "17. Pen Drives" << setw(25) << "18. Memory Card" << setw(25) << "19. Camera" << setw(25) << "20. Trimmers" << endl;
        cout << "\n\n\t\t\t   ";
        cout << setw(25) << "100. Add to Cart" << setw(25) << "200. View Cart" << setw(25) << "300. Buy Products" << setw(25) << "400. Delete Items in Cart\t\t" << setw(25) << "0. Exit" << endl;

        cout << "\n\t\t Enter your choice : ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            p.display_all();
            break;

        case 100:
            int uniq;
            cout << "\n\n\t\t Enter unique code of the item : ";
            cin >> uniq;
            p.addcart(uniq);
            break;

        case 200:
            p.viewcart();
            break;

        case 300:
            p.buy_products();
            break;

        case 400:
            cout << "\n\n\t\t Enter unique code of the item to delete : ";
            cin >> uniq;
            p.delete_items(uniq);
            break;

        case 0:
            break;

        default:
            cout << "\n\n\n\t\t\t\t\t\t\t\t\t \"Products details\"" << endl;
            if(choice==2)
                p.display_all("Mobile");
            else if(choice==3)
                p.display_all("Laptop");
            else if(choice==4)
                p.display_all("Headphone");
            else if(choice==5)
                p.display_all("Air_pods");
            else if(choice==6)
                p.display_all("Air_coolers");
            else if(choice==7)
                p.display_all("Mouse");
            else if(choice==8)
                p.display_all("Washing_machine");
            else if(choice==9)
                p.display_all("Television");
            else if(choice==10)
                p.display_all("Keyboards");
            else if(choice==11)
                p.display_all("Printers");
            else if(choice==12)
                p.display_all("Smart_Watches");
            else if(choice==13)
                p.display_all("Speakers");
            else if(choice==14)
                p.display_all("Alexa_Devices");
            else if(choice==15)
                p.display_all("Fans");
            else if(choice==16)
                p.display_all("Tablet");
            else if(choice==17)
                p.display_all("Pen_drives");
            else if(choice==18)
                p.display_all("Memory_cards");
            else if(choice==19)
                p.display_all("Camera");
            else if(choice==20)
                p.display_all("Trimmers");
            break;
        }
    }
    cout << "\n\nt\t\t\t\t\t\t Implemented by Sunil Kumar B A (1SI20CS116) and Varsha H S(1SI20CS124) " << endl;
    return 0;
}
