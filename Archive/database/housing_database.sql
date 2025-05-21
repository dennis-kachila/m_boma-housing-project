-- GROUP 8(DEVELOPERS) PROJECT
-- MEMBERS
-- {DENNIS KACHILA
-- JOHN ITIBI
-- PERES DAPHNY
-- ALLAN JUMA}
-- M_BOMA HOUSING PROJECT DATABASE SCRIPT


-- creating table town

CREATE TABLE town(
town_id INT ,
town_name VARCHAR(15) ,
PRIMARY KEY(town_id)
);

DESCRIBE houses;
DROP TABLE houses;
-- creating table houses
CREATE TABLE houses(
town_id INT,
house_id INT,
house_type VARCHAR(50) ,
PRIMARY KEY(town_id,house_id),
FOREIGN KEY (town_id) REFERENCES town(town_id) 
);

-- creating table rental cost
CREATE TABLE rental_cost (
 house_id INT,
 town_id INT,
 house_cartegory VARCHAR(60),
 deposit INT,
 monthly_rent INT,
PRIMARY KEY (house_id,town_id,house_cartegory)
-- FOREIGN KEY (house_id) REFERENCES houses(house_id),
 -- FOREIGN KEY (town_id) REFERENCES town(town_id) 
);

ALTER TABLE rental_cost ADD  FOREIGN KEY (town_id) REFERENCES town(town_id);
ALTER TABLE rental_cost ADD  FOREIGN KEY (house_id) REFERENCES houses(house_id);
-- creating table payment details
CREATE TABLE payment_details(
house_id INT,
town_id INT,
house_type VARCHAR(50),
bank_acount INT,
m_pesa_till_no INT,
owner_contacts INT,
PRIMARY KEY(town_id,house_id),
-- FOREIGN KEY (house_type) REFERENCES houses(house_type),
FOREIGN KEY (town_id) REFERENCES town(town_id) 
-- FOREIGN KEY (house_id) REFERENCES houses(house_id)
);


-- iserting values into table town
INSERT INTO town VALUES(100,'Runda');
INSERT INTO town VALUES(200,'Ruaka');
INSERT INTO town VALUES(300,'Kahawa');

-- inserting valuse into table houses for RUNDA town
-- 1 RUNDA
INSERT INTO houses VALUES(100,101,'Bungalow');
INSERT INTO houses VALUES(100,201,'Mansionette');
-- houses in Ruaka town
INSERT INTO houses VALUES(200,101,'Bungalow');
INSERT INTO houses VALUES(200,301,'Appartments & Flats');
INSERT INTO houses VALUES(200,401,'Bedsitters');
INSERT INTO houses VALUES(200,501,'Singles');

-- houses in Kahawa town
INSERT INTO houses VALUES(300,101,'Bungalow');
INSERT INTO houses VALUES(300,301,'Appartments & Flats');
INSERT INTO houses VALUES(300,401,'Bedsitters');
INSERT INTO houses VALUES(300,501,'Singles');

-- inserting values fror rental cost 
-- 1.RUNDA
INSERT INTO rental_cost VALUES(101,100,"Bungalow",1000000,500000);
INSERT INTO rental_cost VALUES(201,100,"Mansionette",800000,400000);
-- 2.Ruaka
INSERT INTO rental_cost VALUES(101,200,"Bungalow",800000,450000);
INSERT INTO rental_cost VALUES(301,200,"3-Bedroom House",100000,55000);
INSERT INTO rental_cost VALUES(301,200,"2-Bedroom",70000,35000);
INSERT INTO rental_cost VALUES(301,200,"1-Bedroom",34000,17000);
INSERT INTO rental_cost VALUES(401,200,"Bedsitters",17000,8500);
INSERT INTO rental_cost VALUES(501,200,"Singles",8000,4000);
-- 3.KAHAWA
INSERT INTO rental_cost VALUES(101,300,"Bungalow",800000,400000);
INSERT INTO rental_cost VALUES(301,300,"3-Bedroom",80000,40000);
INSERT INTO rental_cost VALUES(301,300,"2-Bedroom",60000,30000);
INSERT INTO rental_cost VALUES(301,300,"1-Bedroom",20000,10000);
INSERT INTO rental_cost VALUES(401,300,"Bedsitters",16000,8000);
INSERT INTO rental_cost VALUES(501,300,"Singles",7000,3500);

-- INSERTING VALUES INTO PAYMENT DETAILS
INSERT INTO payment_details VALUES(101,100,"Bungalow",446574332,34858,0734458232);
INSERT INTO payment_details VALUES(201,100,"Mansionette",49593858,79585,077887949);
INSERT INTO payment_details VALUES(101,200,"Bungalow",898668488,75737,0747385867);
INSERT INTO payment_details VALUES(301,200,'Appartments & Flats',768658683,647376,0702847827);
INSERT INTO payment_details VALUES(401,200,"Bedsitters",0896987863,457275,0755673769);
INSERT INTO payment_details VALUES(501,200,"Singles",694868351,995573,0712945858);
INSERT INTO payment_details VALUES(301,300,'Appartments & Flats',458483894,024757,071112353);
INSERT INTO payment_details VALUES(401,300,"Bedsitters",1234683785,01010,0700345087);
INSERT INTO payment_details VALUES(501,300,"Singles",0896945832,01234,0712597944);
INSERT INTO payment_details VALUES(101,300,"Bungalow",0457781112,78641,0768664759);

SELECT *FROM rental_cost;

select * 
from user_info;

DESCRIBE user_info;

CREATE TABLE user_info(
first_name VARCHAR(20),
second_name VARCHAR(20),
email VARCHAR(30),
phone_number INT
);







