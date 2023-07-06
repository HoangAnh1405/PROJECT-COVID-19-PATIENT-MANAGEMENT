
//Nguyen Minh Hoa 19071602
//Nguyen Manh Thanh
//Le Hoang Anh
//Hoang Gia Phi
//Nguyen Duc Thang

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <windows.h>

using namespace std;
struct Patient {
   char PatientID[50];
   char Name[100];
   char Gender[10];
   int age;
   char PhoneNo[15];
   char Address[200];
   char InfectedDay[20];

};
//
struct Node {
   Patient key; //call patient is key 
   Node *Left, *Right; //declare note left and right
};
typedef Node *Tree;  //tree

                
int compare(Patient x, Patient y) // compare 2 item of key
{
   return strcmp(x.PatientID, y.PatientID);
}
//
// insert data to patient
Patient InsertInfo()
{
   Patient x;		//recall patient is x
   cout << "Insert patient's ID (Press 'Q' to return menu): ";
   gets(x.PatientID);
   if (strcmp(x.PatientID, "q") == 0 || strcmp(x.PatientID, "Q") == 0)		//if enter q or Q
   {
      return x;
   }
   cout << "Insert Patient's Name: ";
   gets(x.Name);
   cout<<"Insert Patient's Gender: ";
   gets(x.Gender);
   cout<<"Insert Patient's age: ";
   cin>>(x.age);
   while((x.age<=0) || (x.age>=120)){
   cout<<"Age not valid, insert patient's age again: " ;
   cin>>(x.age); }
   fflush(stdin);
   cout<<"Insert Patient's Phone Number: ";
   gets(x.PhoneNo);
   cout<<"Insert Patient's Address: ";
   gets(x.Address);
   cout<<"Insert Patient's infected day: ";
   gets(x.InfectedDay);


   while (getchar() != '\n');/////////////////

   return x;		//return patient
}
void Display(Patient x)		// display patient
{
   cout << "=================================" << endl;
   cout << "Patient's ID: " << x.PatientID << "\n";
   cout << "Patient's Name: " << x.Name << "\n";
   cout << "Patient's Gender: " << x.Gender << "\n";
   cout << "Patient's Age: " << x.age << "\n";
   cout << "Patient's Phone Number: " << x.PhoneNo << "\n";
   cout << "Patient's Address: " << x.Address << "\n";
   cout << "Patient was Infected Day: " << x.InfectedDay << "\n";
}
int insertNode(Tree &T, Patient x) // Insert one node to tree
{
   if (T != NULL) {
      if (compare(T->key, x) == 0)
         return -1;  // that node is exist 
      if (compare(T->key, x) > 0)
         return insertNode(T->Left, x); // insert to left node
      else if (compare(T->key, x) < 0)
         return insertNode(T->Right, x);   // insert to right node
   }
   T = (Node *)malloc(sizeof(Node));		//allocate memory in the heap
   if (T == NULL)
      return 0;    // not enough memory
   T->key = x;
   T->Left = T->Right = NULL;
   return 1;   // ok
}
void CreateTree(Tree &T)        // insert tree
{
   Patient x;
   while (1) {		//if true
      cout << "--Enter patient's information--" << endl << endl;
      
      x = InsertInfo();
      if (strcmp(x.PatientID, "q") == 0 || strcmp(x.PatientID, "Q") == 0)
         break;  // exit if x=0
      int check = insertNode(T, x);
      if (check == -1)
         cout << "---This patient was exist---\n" << endl;
      else if (check == 0)
         cout << "---Memory full---\n" << endl;
      else cout << "---Adding information successfully---\n\n";

   }
}
void LNR(Tree T)		//order by left, node, right
{

   if (T != NULL)
   {
      LNR(T->Left);
      Display(T->key);
      LNR(T->Right);
   }
}
Tree Searching(Tree T, char PatientID[])     // searching function 
{
   Node *P = T;
   if (T != NULL)
   {
      if (strcmp(T->key.PatientID, PatientID) == 0)		//compare PatientID with list of ID 
      {
         return P;

      }
      else if (strcmp(T->key.PatientID, PatientID) > 0)		//if patient < key.PatientId search in the left of tree
      {
         return Searching(T->Left, PatientID);
      }
      else													//if patient > key.PatientId search in the left of tree
         return Searching(T->Right, PatientID);
   }
   else
      return NULL;
}
Tree ChangeInfoPatient(Tree P)
{

   cout << "Change the name of the patient to (press Q to return menu): ";
   gets(P->key.Name);
   if (strcmp(P->key.Name, "q") == 0 || strcmp(P->key.Name, "Q") == 0)
   {
      return P;		//return tree
   }
   cout<< "Change Gender to: ";			//insert  new info of patient to change
   gets(P->key.Gender);
   
   cout << "Change the age of the patient: ";
   while (true)
   {
      cin >> P->key.age;
      if (cin.fail() || P->key.age>=0 || P->key.age<=120)
      {
         cin.clear();
         _flushall();
         cin.ignore();
         cout << "Insert the age again!: ";

      }
      else
         break;
   }
   
    cout<< "Change Phone Number to: ";
    gets(P->key.PhoneNo);
    
    cout<< "Change the Address to: ";
    gets(P->key.Address); 
    
    cout<< "Change the day that this patient was infected to: ";
    gets(P->key.InfectedDay);
  
   

   while (getchar() != '\n');/////////////////

   return P;
}
//Delete Patient
int delPatient(Tree &T, char PatientID[])     // delete patient by patientID
{
   if (T == NULL)
      return 0;
   else if (strcmp(T->key.PatientID, PatientID) > 0)
      return delPatient(T->Left, PatientID);
   else if (strcmp(T->key.PatientID, PatientID) < 0)
      return delPatient(T->Right, PatientID);
   else 		// T->key == x
   {
      Node *P = T;
      if (T->Left == NULL)
         T = T->Right;    // Node chi co cay con phai
      else if (T->Right == NULL)
         T = T->Left;   // Node chi co cay con trai
      else // Node co ca 2 con
      {
         Node *S = T, *Q = S->Left;
         // S la cha cua Q, Q la Node phai nhat cua cay con trai cua P
         while (Q->Right != NULL) {
            S = Q;
            Q = Q->Right;
         }
         P->key = Q->key;
         S->Right = Q->Left;
         delete Q;
      }
   }
   return 1;
}
void  writefile(char *filename, Tree &T)
{
   if (T != NULL)
   {
      
      FILE *f = fopen(filename, "ab");
      fprintf(f, "%s\n", T->key.PatientID);
      //fwrite(T->key.PatientID, 1, sizeof(T->key.PatientID), f);
      fprintf(f, "%s\n", T->key.Name);
      //fwrite(T->key.PatientID, 1, sizeof(T->key.PatientID), f);
      fprintf(f, "%s\n", T->key.Gender);
      fprintf(f, "%d\n", T->key.age);
      fprintf(f, "%s\n", T->key.PhoneNo);
      fprintf(f, "%s\n", T->key.Address);
      fprintf(f, "%s\n", T->key.InfectedDay); 
      writefile(filename, T->Left);
      writefile(filename, T->Right);
      fclose(f);
   }
}
void readfile(char *filename, Tree &T)
{
   Patient x;
   FILE *f = fopen(filename, "rb");
   if (f != NULL)
   {

      while (!feof(f))
      {
         fscanf(f, "%s\n", &x.PatientID);
         fscanf(f, "%s\n", &x.Name);
         fscanf(f, "%s\n", &x.Gender);
         fscanf(f, "%s\n", &x.age);
         fscanf(f, "%s\n", &x.PhoneNo);
         fscanf(f, "%s\n", &x.Address);
         fscanf(f, "%s\n", &x.InfectedDay);
         insertNode(T, x);
      }
      fclose(f);
   }
   else
   {
      cout << "!!--Warning: Database is empty, please insert patient's information--!!" << "\n\n";
      CreateTree(T); //Nhap cay
   }
   
}
int main()
{
   string username;
   string password;
   cout<<"\t\t-------PLEASE ENTER YOUR USER NAME AND PASSWORD TO LOGIN ------\n"<<endl;
   cout<<"\t\t\t\t---------------------"<<endl;
   cout<<"\t\t\t\t| User name: ";
   getline(cin,username);
   cout<<"\n\t\t\t\t|password: ";
   getline(cin,password);
   cout<<"\t\t\t\t---------------------"<<endl;
   while(username!="group9" || password!="12345678"){
   cout<<"\nIncorrect User Name or Password, Please login again!\n"<<endl;
   cout<<"\t\t\t\t---------------------"<<endl;
   cout<<"\t\t\t\t|User name: ";
   cin>>username;
   fflush(stdin);
   cout<<"\n\t\t\t\t|password: ";
   cin>>password;
   fflush(stdin);
   cout<<"\t\t\t\t---------------------"<<endl;
   }
   
   Tree T;
   T = NULL; //create empty tree
   cout << "------------ Programing for infected Covid-19 patients system------------" << "\n\n\n";
   char *f = "Patient.txt";
   readfile(f, T);
   // Create menu 
   int choice;
Menu: {
   system("cls");
   HANDLE hOut;
   cout << "----------MAIN MENU----------" << endl;
   cout << "1. Display all patient's information" << endl;
   cout << "2. Add patient to the system" << endl;
   cout << "3. Search Patient's info base on Patient'ID" << endl;
   cout << "4. Delete Patient's base on Patient's ID" << endl;
   cout << "5. Save the data" << endl;
   cout << "6. Exit" << endl;
   cout << "----------------------------------------------------" << endl;
   cout << "Enter your choice to continute: ";
   
   cin >> choice;
   }
     if (choice == 1)
     {
        system("cls");
        int f;
        LNR(T);
        cout << "----------------------------------------------------" << endl;
        cout << "1. Return Main Menu: ";
        cin >> f;
        if (f == 1)
           goto Menu;
     }
     // adding patient
     if (choice == 2)
     {
        system("cls");
        cin.ignore();
        CreateTree(T);
        goto Menu;
     }
     if (choice == 3)
     {
        system("cls");
        char PatientID[50];
        cin.ignore();
        cout << "Enter Patient's ID to sreach: ";
        gets(PatientID);
        Tree P = Searching(T, PatientID);
        if (P != NULL)
        {
           int choice;
        Menu2: {
           system("cls");
           cout << "----------Patient have the ID is " << PatientID << " exist in the system------------"<< endl;
           cout << "1. Display Patient's Information with ID " << PatientID << endl;
           cout << "2. Change the Patient's Information with ID " << PatientID << endl;
           cout << "3. Return Main Menu" << endl;
           cout << "----------------------------------------------------" << endl;
           cout << "Enter your choice to continute: ";
           cin >> choice;
           }
             if (choice == 1)
             {
                system("cls");
                int f;
                cout << "=================================" << endl;
                cout << "Patient's Id: " << P->key.PatientID << "\n";
                cout << "Patient's Name: " << P->key.Name << "\n";
                cout << "1. Return Main menu : ";
                cin >> f;
                if (f == 1)
                   goto Menu;
                goto Menu2;
             }
             if (choice == 2)
             {
                system("cls");
                cout << "Insert info to change" << endl;
                cin.ignore();
                ChangeInfoPatient(P);
                goto Menu2;
             }
             if (choice == 3)
             {
                system("cls");
                goto Menu;
             }
        }
        else
        {
           cout << "This patient is not exist" << endl;
           system("Pause");
        }
        goto Menu;
     }
     if (choice == 4)
     {
        system("cls");
        char PatientID[50];
        cin.ignore();
        cout << "Enter the ID to delete patient's info: ";
        gets(PatientID);
        Tree P = Searching(T, PatientID);
        if (P != NULL)
        {
           int choice;
           system("cls");
           cout << "----------Searching susccessfully for patient with ID is " << PatientID << "----------" << endl;
           cout << "Patient's ID: " << P->key.PatientID << "\n";
           cout << "Patient's Name: " << P->key.Name << "\n";
           cout << "Patient's Gender: " << P->key.Gender << "\n";
           cout << "Patient's Age : " << P->key.age << "\n";
           cout << "Patient's Phone Number: " << P->key.PhoneNo << "\n";
           cout << "Patient's Address: " << P->key.Address << "\n";
           cout << "Date of infection: " << P->key.InfectedDay << "\n";
           cout << "----------------------------------------------------" << endl;
           cout << "1. Delete patient " << PatientID << endl;
           cout << "2. Cancel! Return Main Menu" << endl;
           cout << "----------------------------------------------------" << endl;
           cout << "Enter your choice to continute: ";
           cin >> choice;
           if (choice == 1)
           {
              system("cls");
              cin.ignore();
              int del = 1;
              while (del)
              {
                 if (P != NULL)
                 {
                    cout << "---Delete successfully---" << endl;
                    del = delPatient(T, P->key.PatientID);
                 }
                 else
                 {
                    cout << "Database is empty" << endl;
                    del = 0;
                 }
                 system("Pause");
                 goto Menu;
              }
           }
           if (choice == 2)
           {
              system("cls");
              goto Menu;
           }
        }
        else
        {
           cout << "This patient's ID is does not exist'" << endl;
        }
        goto Menu;
     }
     if (choice == 5)
     {
        system("del QL.TXT");
        system("cls");
        cin.ignore();
        writefile(f, T);
        cout << "Saved Data" << endl;
        system("Pause");
        goto Menu;
     }
     if (choice == 6)
     {
        return 0;
     }

     system("Pause");
} 






