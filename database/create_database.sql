-- M-BOMA Housing Project Database Creation Script

-- Create database if not exists
CREATE DATABASE IF NOT EXISTS mboma_housing;

-- Use the database
USE mboma_housing;

-- Drop existing tables if they exist
DROP TABLE IF EXISTS payment_details;
DROP TABLE IF EXISTS rental_cost;
DROP TABLE IF EXISTS houses;
DROP TABLE IF EXISTS town;
DROP TABLE IF EXISTS user_info;

-- Create town table
CREATE TABLE town(
  town_id INT,
  town_name VARCHAR(15),
  PRIMARY KEY(town_id)
);

-- Create houses table
CREATE TABLE houses(
  town_id INT,
  house_id INT,
  house_type VARCHAR(50),
  PRIMARY KEY(town_id, house_id),
  FOREIGN KEY (town_id) REFERENCES town(town_id)
);

-- Create rental_cost table
CREATE TABLE rental_cost (
  house_id INT,
  town_id INT,
  house_cartegory VARCHAR(60),
  deposit INT,
  monthly_rent INT,
  PRIMARY KEY (house_id, town_id, house_cartegory),
  FOREIGN KEY (town_id) REFERENCES town(town_id),
  FOREIGN KEY (house_id, town_id) REFERENCES houses(house_id, town_id)
);

-- Create payment_details table
CREATE TABLE payment_details(
  house_id INT,
  town_id INT,
  house_type VARCHAR(50),
  bank_acount VARCHAR(20),
  m_pesa_till_no VARCHAR(10),
  owner_contacts VARCHAR(15),
  PRIMARY KEY(town_id, house_id),
  FOREIGN KEY (town_id) REFERENCES town(town_id),
  FOREIGN KEY (house_id, town_id) REFERENCES houses(house_id, town_id)
);

-- Create user_info table
CREATE TABLE user_info(
  user_id INT AUTO_INCREMENT,
  first_name VARCHAR(20),
  second_name VARCHAR(20),
  email VARCHAR(30),
  phone_number VARCHAR(15),
  password VARCHAR(64),  -- Store hashed passwords
  PRIMARY KEY(user_id)
);

-- Create bookings table
CREATE TABLE bookings(
  booking_id INT AUTO_INCREMENT,
  user_id INT,
  house_id INT,
  town_id INT,
  booking_date DATETIME,
  expiry_date DATETIME,
  is_paid BOOLEAN DEFAULT FALSE,
  PRIMARY KEY(booking_id),
  FOREIGN KEY (user_id) REFERENCES user_info(user_id),
  FOREIGN KEY (house_id, town_id) REFERENCES houses(house_id, town_id)
);

-- Create payments table
CREATE TABLE payments(
  payment_id INT AUTO_INCREMENT,
  booking_id INT,
  amount DECIMAL(10,2),
  payment_date DATETIME,
  payment_method VARCHAR(20),
  receipt_number VARCHAR(15),
  PRIMARY KEY(payment_id),
  FOREIGN KEY (booking_id) REFERENCES bookings(booking_id)
);

-- Insert sample data from original SQL file
-- Towns
INSERT INTO town VALUES(100,'Runda');
INSERT INTO town VALUES(200,'Ruaka');
INSERT INTO town VALUES(300,'Kahawa');

-- Houses
-- Runda
INSERT INTO houses VALUES(100,101,'Bungalow');
INSERT INTO houses VALUES(100,201,'Mansionette');
-- Ruaka
INSERT INTO houses VALUES(200,101,'Bungalow');
INSERT INTO houses VALUES(200,301,'Appartments & Flats');
INSERT INTO houses VALUES(200,401,'Bedsitters');
INSERT INTO houses VALUES(200,501,'Singles');
-- Kahawa
INSERT INTO houses VALUES(300,101,'Bungalow');
INSERT INTO houses VALUES(300,301,'Appartments & Flats');
INSERT INTO houses VALUES(300,401,'Bedsitters');
INSERT INTO houses VALUES(300,501,'Singles');

-- Rental costs
-- Runda
INSERT INTO rental_cost VALUES(101,100,"Bungalow",1000000,500000);
INSERT INTO rental_cost VALUES(201,100,"Mansionette",800000,400000);
-- Ruaka
INSERT INTO rental_cost VALUES(101,200,"Bungalow",800000,450000);
INSERT INTO rental_cost VALUES(301,200,"3-Bedroom House",100000,55000);
INSERT INTO rental_cost VALUES(301,200,"2-Bedroom",70000,35000);
INSERT INTO rental_cost VALUES(301,200,"1-Bedroom",34000,17000);
INSERT INTO rental_cost VALUES(401,200,"Bedsitters",17000,8500);
INSERT INTO rental_cost VALUES(501,200,"Singles",8000,4000);
-- Kahawa
INSERT INTO rental_cost VALUES(101,300,"Bungalow",800000,400000);
INSERT INTO rental_cost VALUES(301,300,"3-Bedroom",80000,40000);
INSERT INTO rental_cost VALUES(301,300,"2-Bedroom",60000,30000);
INSERT INTO rental_cost VALUES(301,300,"1-Bedroom",20000,10000);
INSERT INTO rental_cost VALUES(401,300,"Bedsitters",16000,8000);
INSERT INTO rental_cost VALUES(501,300,"Singles",7000,3500);

-- Payment details
INSERT INTO payment_details VALUES(101,100,"Bungalow",'446574332','34858','0734458232');
INSERT INTO payment_details VALUES(201,100,"Mansionette",'49593858','79585','077887949');
INSERT INTO payment_details VALUES(101,200,"Bungalow",'898668488','75737','0747385867');
INSERT INTO payment_details VALUES(301,200,'Appartments & Flats','768658683','647376','0702847827');
INSERT INTO payment_details VALUES(401,200,"Bedsitters",'896987863','457275','0755673769');
INSERT INTO payment_details VALUES(501,200,"Singles",'694868351','995573','0712945858');
INSERT INTO payment_details VALUES(301,300,'Appartments & Flats','458483894','024757','071112353');
INSERT INTO payment_details VALUES(401,300,"Bedsitters",'1234683785','01010','0700345087');
INSERT INTO payment_details VALUES(501,300,"Singles",'896945832','01234','0712597944');
INSERT INTO payment_details VALUES(101,300,"Bungalow",'457781112','78641','0768664759');

-- Add a test user
INSERT INTO user_info (first_name, second_name, email, phone_number, password)
VALUES ('Test', 'User', 'test@example.com', '0712345678', 'password');
