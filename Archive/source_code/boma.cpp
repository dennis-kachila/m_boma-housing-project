#include "boma.h"
#include<mysql.h>
#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<string>
#include<iostream>
#include <ctime>  /* time_t, time, ctime */
#include <fstream>
int amount_paid;
string m_boma_contact = "+254756438790";
string m_boma_email = "mbomaresidentials@gmail.com"; //housing agency contact info(in case of any query)
string house_type;
string residential_area ;


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
	    bool passed = true;
        state = TOWN_DISPLAY;
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

void Boma::f_queery_display()
{
    string choice;
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
        string query = "SELECT * FROM town ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "This are the towns available" << endl;
            printf("Towns_code     town_name\n");
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout << row[0]<<"            " <<row[1] <<endl;
                // cout<< row[0];
                 //alternative metod of displaying infor from database--->> printf("%s    \n", row[0]);
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

   void choice_input(Boma ops)
   {
        cout<<"Please input the area code you want to explore : ";
    cin>>ops.choice
    switch (ops.choice)
    {
    case 100 :
          ops.display_runda_houses();
        /* code */
        break;
    case 200:
          ops.display_ruaka_houses();
    break;

    case 300:
       ops.display_kahawa_houses();
    break;   
    
    default:
    cout<<:"invalid option"<<endl;
     exit(EXIT_SUCCESS);
        break;
    }

   }
   

void Boma::display_runda_houses()
{
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT house_id,house_type FROM houses WHERE town_id = 100  ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "HOUSES AVAILABLE IN RUNDA" << endl;
            cout << endl;
            printf("House_code      House_type\n");
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout << row[0]<<"            " <<row[1] <<endl;
                // cout<< row[0];
                 //alternative metod of displaying infor from database--->> printf("%s    \n", row[0]);
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

void runda_payment_details(Payment_runda runda)
{
     int house_code;
    cout<<"Please input the house code of your Choice"<<endl;
    cin>>runda.house_code;
    switch (house_code)
    {
    case 101:
    runda.f_disp_bungalow_info();
          
        /* code */
        break;
    _ case 201:
    runda.f_disp_masionette_info();
        break;
    default:
    cout<<"invalid choice"<<endl;
    exit(EXIT_SUCCESS);
        break;
    }

}

void Boma::display_ruaka_houses()
{
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
    string query = "SELECT house_id,house_type FROM houses WHERE town_id = 200  ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "HOUSES AVAILABLE IN RUAKA" << endl;
            cout << endl;
            printf("House_code      House_type\n");
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout << row[0]<<"            " <<row[1] <<endl;
                // cout<< row[0];
                 //alternative metod of displaying infor from database--->> printf("%s    \n", row[0]);
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
void ruaka_payment_details(Payment_ruaka ruaka)
{
     int house_code;
    cout<<"Please input the house code of your Choice"<<endl;
    cin>>house_code;
    switch (house_code)
    {
        case 101:
         ruaka.f_disp_bungalow_info();
        break;
        case 201:
        ruaka.f_disp_masionette_info();
        break;
        case 301:
        ruaka.f_disp_apprtment_flats_info();
        break;
        case 401:
        ruaka.f_disp_bedsitters_info();
        case 501:
        ruaka.f_disp_singles_info();
        break;
    default:
    cout<<"invalid choice"<<endl;
    exit(EXIT_SUCCESS);
        break;
    }

}



void Boma::display_kahawa_houses()
{
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
    string query = "SELECT house_id,house_type FROM houses WHERE town_id = 300  ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "HOUSES AVAILABLE IN KAHAWA" << endl;
            cout << endl;
            printf("House_code      House_type\n");
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout << row[0]<<"            " <<row[1] <<endl;
                // cout<< row[0];
                 //alternative metod of displaying infor from database--->> printf("%s    \n", row[0]);
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

void kahawa_payment_details(Payment_kahawaa kahawaa)
{
     int house_code;
    cout<<"Please input the house code of your Choice"<<endl;
    cin>>kahawaa.house_code;
    switch (house_code)
    {
        case 101:
         kahawa.f_disp_bungalow_info();
        break;
        case 301:
        kahawaa.f_disp_apprtment_flats_info();
        break;
        case 401:
        kahawaa.f_disp_bedsitters_info();
        case 501:
        kahawaa.f_disp_singles_info();
        break;
    default:
    cout<<"invalid choice"<<endl;
    exit(EXIT_SUCCESS);
        break;
    }

}




void Payment_runda::f_disp_bungalow_info()
{
        
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 100 AND house_id = 101 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** BUNGALOW COSTINGS **** " << endl;
            cout << endl;
            
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout <<"Deposit =KSH. " <<row[0]<<"\n" <<"Monthly_RENT = KSH. "<<row[1] <<endl;
                // cout<< row[0];
                 //alternative metod of displaying infor from database--->> printf("%s    \n", row[0]);
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

void Payment_runda::f_disp_masionette_info()
{
        
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 100 AND house_id = 201 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** MANSIONETTE COSTINGS **** " << endl;
            cout << endl;
            
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout <<"Deopsit =KSH. " <<row[0]<<"\n" <<"Monthly_RENT = KSH. "<<row[1] <<endl;
                // cout<< row[0];
                 //alternative metod of displaying infor from database--->> printf("%s    \n", row[0]);
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

void Payment_ruaka::f_disp_bungalow_info()
{
        
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 200 AND house_id = 101 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** BUNGALOW COSTINGS **** " << endl;
            cout << endl;
            
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout <<"Deopsit =KSH. " <<row[0]<<"\n" <<"Monthly_RENT = KSH. "<<row[1] <<endl;
                // cout<< row[0];
                 //alternative metod of displaying infor from database--->> printf("%s    \n", row[0]);
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
 void Payment_ruaka::f_disp_apprtment_flats_infof_disp_apprtment_flats_info()
      {
      
     
    
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 200 AND house_id = 301 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** APPARTMENTS & FLATS  COSTINGS **** " << endl;
            cout << endl;
            cout << "|1->BEDROOM                                   |2->BEDROOM                                    |3->BEDROOMS" << endl;
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout << "Deposit ksh." << row[0]<<" ** " << "Monthly_rent ksh." << row[1]<<" ** ";
                // cout<< row[0];
                 //alternative metod of displaying infor from database--->> printf("%s    \n", row[0]);
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
      }
void Payment_ruaka::f_disp_bedsitters_info()
{
          
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 200 AND house_id = 401 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** BEDSITTERS COSTINGGS **** " << endl;
            cout << endl;
            
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout <<"Deopsit =KSH. " <<row[0]<<"\n" <<"Monthly_RENT = KSH. "<<row[1] <<endl;
                // cout<< row[0];
                 //alternative metod of displaying infor from database--->> printf("%s    \n", row[0]);
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
    void f_disp_singles_info()
    {
          
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 200 AND house_id = 501 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** SINGLES COSTINGGS **** " << endl;
            cout << endl;
            
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout <<"Deopsit =KSH. " <<row[0]<<"\n" <<"Monthly_RENT = KSH. "<<row[1] <<endl;
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

//starts here
void Payment_kahawa::f_disp_bungalow_info()
{
     string home = "BUNGALOW";   
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 300 AND house_id = 101 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** BUNGALOW COSTINGS **** " << endl;
            cout << endl;
            
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout <<"Deopsit =KSH. " <<row[0]<<"\n" <<"Monthly_RENT = KSH. "<<row[1] <<endl;
               
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
 void Payment_kahawa::f_disp_apprtment_flats_info()
      {
      
     
    
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 300 AND house_id = 301 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** APPARTMENTS & FLATS  COSTINGS **** " << endl;
            cout << endl;
            cout << "|1->BEDROOM                                   |2->BEDROOM                                    |3->BEDROOMS" << endl;
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout << "Deposit ksh." << row[0]<<" ** " << "Monthly_rent ksh." << row[1]<<" ** ";
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
      
void Payment_kahawa::f_disp_bedsitters_info()
{
          
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 300 AND house_id = 401 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** BEDSITTERS COSTINGGS **** " << endl;
            cout << endl;
            
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout <<"Deopsit =KSH. " <<row[0]<<"\n" <<"Monthly_RENT = KSH. "<<row[1] <<endl;
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
   
 void Payment_kahawa::f_disp_singles_info()
{
          
    int qstate;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
     {
       
        string query = "SELECT deposit,monthly_rent FROM rental_cost WHERE town_id = 300 AND house_id = 501 ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << "****** SINGLES COSTINGGS **** " << endl;
            cout << endl;
            
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 cout <<"Deopsit =KSH. " <<row[0]<<"\n" <<"Monthly_RENT = KSH. "<<row[1] <<endl;  
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

void f_payment_options()
{

    
 enum details {OPT,M_PESA,BANK,BOOKING}; 
details option = OPT;

	switch(option) {								//switch statement for payment options
		case OPT :
			  {
				  cout << "Which payment method would you like to use? " << endl; 
				  cout << "1. M_PESA" << endl << "2. BANK" << endl << "3.BOOKING AN APARTMENT" << endl;
				  cout << "Reply with service number" << endl;
				  cin >> option;
				  if(option ==1)
				  {
					  option = M_PESA;
				  }
				  else if(option ==2)
				  {
					  option = BANK;
				  }
				  else if(option == 3)
				  {
					  option = BOOKING; //booking an apartment does not need any deposit
				  }
				  else 
				  {
					  cout << "Invalid option. Please try again" << endl;
					  option = OPT;
				  }
			  }
		case M_PESA:
			{
				cout << "Payment is to be done to TILL NUMBER:45673" << endl;
				cout << "How much would you wish to pay(deposit)?" << endl;
				cin >> amount_paid;
				cout << "****making payment..." ; //payment is made to the till number
                current = ISSUANCE_OF_RECIPT;
				break;
			}
		case BANK:
			{
				cout << "Payment is to be done to the account number 34562781" << endl;
				cout << "How much would you wish to deposit in the account?" << endl;
				cin >> amount_paid;
				cout << "*****payment ongoing..."; //payment is made to the bank account
                current = ISSUANCE_OF_RECIPT;
				break;
			}
		case BOOKING:
			{
				cout << "The houses are available for booking for a grace period of 30 days,after which the house is released for booking by other potential customers";
				cout << "Remember to come back and make payment before 30 days elapse" << endl; 
				cout << "THANK YOU FOR CHOOSING M_BOMA. WE ARE HONOURED TO SERVE YOU" << endl;		//goodbye note
				cout << "WELCOME AGAIN" << endl;
				//exit the program;
			}
	}
}

void f_give_receipt()
{
    
	cout << "			*M_BOMA HOUSING SYSTEM*" << endl;				//company receipt
	time_t rawtime;
	time (&rawtime);

	cout << "Phone : " << m_boma_contact << "			"<< "Email_address : " << m_boma_email << endl;		//company contact information

	cout << "			HOUSE RENT RECEIPT " << endl;
	cout << endl;
	cout << "Payment done by: " ;
	fstream writer;
	writer.open("Receipt.txt",ios::out|ios::in); //writing to the file
	{

    int qstate;					//quering from the database

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "Dennis001", "m_boma_project", 3306, NULL, 0);

    if (conn)
    {
       
        string query = "SELECT * FROM user_info ";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {   

            printf("first_name	second_name	 email_address	phone_no\n");
            res = mysql_store_result(conn);

             while (row = mysql_fetch_row(res))
             {
                 writer << row[0] << endl;
				 cout << row[0] << "\t" ;		//displaying user info to the user interface
				 writer << row[1] << endl;
				 cout << row[1] << endl;
				 writer << row[2] << endl;
				 cout << row[2] << endl;
				 writer << row[3] << endl;
                 cout<< row[3] << endl;
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
	
	writer << amount_paid << endl;
	writer.close();

	
	fstream reader;										//reading from the file
	reader.open("Receipt.txt",ios::in);
	cout << "You have successfully paid the deposit for the house you wish to rent";			//printing of receipt still ongoing
	reader >> amount_paid;
	cout << "Amount received:	" << amount_paid << endl;
	cout << "Payment done by :   " <<option << endl;
	cout << "In case of any query on directions or any other kind of assistance needed,contact: " <<m_boma_contact<<"\n   email us at"<<m_boma_email<<endl;
	reader.close();

	cout << "The transaction time is:  " ;			//printing transaction time and date
	reader >> ctime(&rawtime);
	cout << ctime(&rawtime);

	cout << endl << endl;
	cout << "THANK YOU FOR CHOOSING M_BOMA. WE ARE HONOURED TO SERVE YOU" << endl;			//thank you note
	cout << "WELCOME AGAIN" << endl;
	
}
}









