// m_boma housing project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "boma.h"
#include<mysql.h>
#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<string>
#include "boma.h"

/*
#include<string>
#include<iostream>

*/

//#include "../../../Documents/GitHub/m_boma-housing-project/.vscode/boma.cpp"


using namespace std;

int qstate;
 

int main()
{
    
    user_registration person;
    char pass[20];
    char password[20];
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


    
    
    
//displaying entered information about tyhe user
    
        while (1)
        {
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
                break;

                case TOWN_DISPLAY:
                break;

                case HOUSE_TYPE_DISPLAY:
                break;

                case MODE_OF_PAYMENT:
                break;

                case ISSUANCE_OF_RECIPT:
                break;

            
            
            default:
            cout<<"Unknow error"endl;
                break;
            }
        }
        

}



   
   
   








