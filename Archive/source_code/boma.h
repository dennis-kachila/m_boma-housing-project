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

class Boma{
    public:
    void display_runda_houses();
   void  display_ruaka_houses();
   void  display_kahawa_houses();
  void f_queery_display();
   friend void choice_input(Boma ops);

   protected:
   	void f_disp_bungalow_info();
    void f_disp_apprtment_flats_info();
    void f_disp_bedsitters_info();
    void f_disp_singles_info();


 private:
   int choice
	
};


class Payment_runda: protected Boma{
string town_name;
     public:
	
    friend void runda_payment_details(Payment_runda runda);
    protected:
    void f_disp_bungalow_info();
    void f_disp_masionette_info();


};

class Payment_ruaka:protected Boma,public Payment_runda{
string town_name;
   protected:
	void f_disp_bungalow_info();
    void f_disp_apprtment_flats_info();
    void f_disp_bedsitters_info();
    void f_disp_singles_info();
      public:
   friend void ruaka_payment_details(Payment_ruaka ruaka);



};

class Payment_kahawaa:protected Boma,public Payment_ruaka,public Payment_ruaka{
string town_name;
     public:
    friend void kahawa_payment_details(Payment_kahawaa kahawaa);
     protected:
	void f_disp_bungalow_info();
    void f_disp_apprtment_flats_info();
    void f_disp_bedsitters_info();
    void f_disp_singles_info();



};

void f_payment_options();

void f_give_receipt();




