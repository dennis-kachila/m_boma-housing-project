// m_boma housing project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "boma.h"
#include<mysql.h>
#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<string>
#include "boma.h"
#include <ctime>  /* time_t, time, ctime */
#include <fstream>
int amount_paid;
string m_boma_contact = "+254756438790";
string m_boma_email = "mbomaresidentials@gmail.com"; //housing agency contact info(in case of any query)
string house_type;
string residential_area;
 char pass[20];
char password[20];

/*
#include<string>
#include<iostream>

*/

//#include "../../../Documents/GitHub/m_boma-housing-project/.vscode/boma.cpp"


using namespace std;

int qstate;
 

int main()
{
    Boma ops;
    Payment_runda runda;
    Payment_ruaka ruaka;
    Payment_kahawaa kahawaa;

    user_registration person;
   
// diplsays welcoming note to the user
void f_welcome_note();

      

    cout << "PLEASE ENTER YOUR FIRST NAME?" << endl;
    cin >> person.first_name;
    cout << "PLEASE ENTER YOUR SECOND NAME?" << endl;
    cin >> person.second_name;
    cout << "PLEAE ENTER YOUR EMAIL ?" << endl;
    cin >> person.email;
    cout << "PLEAESE ENTER PHONE NUMBER ?" << endl;
    cin >> person.phone_number;

    cout<<"PLease create new password To proceed"<<endl;
    cin>>pass;
    cout<<"PASSWORD SAVED!"<<endl;

    cout<<"Please input password again to preoceed"<<endl;
    cin>>password;


    
    
    while(1){

  state current = ACCOUNT_CREATION;
//displaying entered information about tyhe use
            /* code */
            switch (current)
            {
            case /* constant-expression */ACCOUNT_CREATION:
            /*registering to daata base
this icludes the entered name,email,hpone _number etc
*/
            void f_register_to_database(person.first_name,person.second_name,person.email,person.phone_number);
            disp_user_info(person);

             current = PASSWORD_VERIFICATION;
                /* code */
                break;


                case PASSWORD_VERIFICATION:
                pin_verification(pass,password);
                state= TOWN_DISPLAY;
                break;

                case TOWN_DISPLAY:
                f_queery_display();
                choice_input(ops);
                break;

                case HOUSE_TYPE_DISPLAY:
                choice_input(ops);
                runda_payment_details(runda);
                break;

                case MODE_OF_PAYMENT:
                f_payment_options();
                break;

                case ISSUANCE_OF_RECIPT:
                f_give_receipt();
                break;

            
            
            default:
            cout<<"Unknow error"endl;
                break;
            }
        }
}
      

   


   
   
   








