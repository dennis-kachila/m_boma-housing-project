#include "boma.h"
#include<mysql.h>
#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<string>
#include<iostream>


using namespace std;

// declaring the type of data structures
struct user_registration {
    /* data */
    string first_name;
    string second_name;
    string email;
    int phone_number;

};

void disp_user_info( user_registration person) {
     cout<<"ACCOUNT CREATION SUCCESSFUL"<<endl
    cout << "ACCOUNT INFO:" << endl;
    cout << "Name: " << person.first_name <<""<<person.second_name<< endl;
    cout << "Email: " << person.email << endl;
    cout << "Phone_number: " << person.phone_number;
}


void pin_verification(char pass[20],char password[20])
{
     int i=0;
	while( i <3)
    {


	if(strcmp(pass, password)==0)
	     {
		cout<<"SUCCESFULYY LOGGED IN";
		//for now but will define later
        break;
	     }
	else
	   {
		cout<<"INCORRECT PASSWORD PLEASE TRY AGAIN";
       }
            i++;
    }

}
void f_welcome_note()
{

	cout<< "                 /\\          " << endl;
	cout<< "                /  \\         " << endl;
	cout<< "               /    \\        " << endl;
	cout<< "              /      \\       " << endl;
	cout<< "             /        \\      " << endl;
	cout<< "            /          \\     " << endl;
	cout<< "           /            \\    " << endl;
	cout<< "          /              \\   " << endl;
	cout<< "         /__            __\\  " << endl;
	cout<< "            |          |      " << endl;
	cout<< "            |          |      " << endl;
	cout<< "            |          |      " << endl;
	cout<< "            |__________|      " << endl; 

	cout<<"Welcome to M BOMA HOUSING PROJECT services:"<< endl;
	cout<<"Please Create Account to Continue:" << endl;
}


void f_register_to_database(string a,string b,string c,int d)
{
     MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);
    
    if (conn)
    { 
        puts("successful connection to database !*");       
      
        if (!qstate)
        {
            
            string query = "INSERT INTO user_info(first_name,second_name,email,phone_number) VALUES ( '" + a + "','" + b + "','" + c + "','" + d + "')";
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);
            if (qstate != 0)
            {
                cout << mysql_error(conn) << endl;
                return 1;
            }
        }
        else
        {
            cout << "Querry failed: " << mysql_error(conn) << endl;
        }

    }

    else
    {
        puts("connection to database has failed!*");
    }
    return 0;
 }

}
void f_display_town()
{

    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = " SELECT monthly_rent FROM rental_cost WHERE town_id = 100 AND house_cartegory = 'Bungalow'";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            printf("town_id   Town_name\n");
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout << row[0];
                 // printf("%s    \n", row[0]);
            }
        }
        else
        {
            cout << "Querry failed: " << mysql_error(conn) << endl;
        }
    }

    else
    {
        puts("connection to database has failed!*");
    }

}



