#pragma once


// declaring the type of data structures
struct user_registration {
    /* data */
};

void disp_user_info(  user_registration );

void pin_verification(char pass[20],char password[20]);

void f_welcome_note();

enum state { ACCOUNT_CREATION , PASSWORD_VERIFICATION ,TOWN_DISPLAY,HOUSE_TYPE_DISPLAY,MODE_OF_PAYMENT,ISSUANCE_OF_RECIPT };
state current = ACCOUNT_CREATION;

void f_register_to_database(string a,string b,string c,int d);

class boma
{
private:
    /* data */
public:
    boma(/* args */);
    ~boma();
};

boma::boma(/* args */)
{
}

boma::~boma()
{
}


