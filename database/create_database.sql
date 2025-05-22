-- M-BOMA Housing Project Database Creation Script

-- Create database if not exists
CREATE DATABASE IF NOT EXISTS mboma_housing;

-- Use the database
USE mboma_housing;

-- Drop existing tables if they exist
DROP TABLE IF EXISTS payments;
DROP TABLE IF EXISTS bookings;
DROP TABLE IF EXISTS payment_details;
DROP TABLE IF EXISTS rental_cost;
DROP TABLE IF EXISTS houses;
DROP TABLE IF EXISTS town;
DROP TABLE IF EXISTS county;
DROP TABLE IF EXISTS user_info;

-- Create county table
CREATE TABLE county(
  county_id INT,
  county_name VARCHAR(30),
  PRIMARY KEY(county_id)
);

-- Create town table
CREATE TABLE town(
  town_id INT,
  town_name VARCHAR(30),
  county_id INT,
  PRIMARY KEY(town_id),
  FOREIGN KEY (county_id) REFERENCES county(county_id)
);

-- Create houses table
CREATE TABLE houses(
  town_id INT,
  house_id VARCHAR(4),  -- Changed from INT to VARCHAR(4)
  house_type VARCHAR(50),
  house_address VARCHAR(100),
  map_link VARCHAR(100),
  deposit_fee DECIMAL(10,2),
  monthly_rent DECIMAL(10,2),
  is_available BOOLEAN DEFAULT TRUE,
  is_booked BOOLEAN DEFAULT FALSE,
  booked_until DATETIME,
  PRIMARY KEY(house_id),  -- Changed to single-column primary key
  FOREIGN KEY (town_id) REFERENCES town(town_id),
  INDEX (town_id)  -- Add index for foreign key reference
);

-- Create rental_cost table
CREATE TABLE rental_cost (
  house_id VARCHAR(4),  -- Changed from INT to VARCHAR(4)
  town_id INT,
  house_cartegory VARCHAR(60),
  deposit INT,
  monthly_rent INT,
  PRIMARY KEY (house_id, house_cartegory),  -- Removed town_id from primary key
  FOREIGN KEY (town_id) REFERENCES town(town_id),
  FOREIGN KEY (house_id) REFERENCES houses(house_id)
);

-- Create payment_details table
CREATE TABLE payment_details(
  house_id VARCHAR(4),  -- Changed from INT to VARCHAR(4)
  town_id INT,
  house_type VARCHAR(50),
  bank_acount VARCHAR(20),
  m_pesa_till_no VARCHAR(10),
  owner_contacts VARCHAR(15),
  PRIMARY KEY(house_id),  -- Changed to single-column primary key
  FOREIGN KEY (town_id) REFERENCES town(town_id),
  FOREIGN KEY (house_id) REFERENCES houses(house_id)
);

-- Create user_info table
CREATE TABLE user_info(
  user_id INT AUTO_INCREMENT,
  first_name VARCHAR(20),
  second_name VARCHAR(20),
  email VARCHAR(30) UNIQUE,  -- Added UNIQUE constraint
  phone_number VARCHAR(15),
  password VARCHAR(64),  -- Store hashed passwords
  PRIMARY KEY(user_id)
);

-- Create bookings table
CREATE TABLE bookings(
  booking_id INT AUTO_INCREMENT,
  user_id INT,
  house_id VARCHAR(4),  -- Changed from INT to VARCHAR(4)
  town_id INT,
  booking_date DATETIME,
  expiry_date DATETIME,
  is_paid BOOLEAN DEFAULT FALSE,
  PRIMARY KEY(booking_id),
  FOREIGN KEY (user_id) REFERENCES user_info(user_id),
  FOREIGN KEY (house_id) REFERENCES houses(house_id),
  FOREIGN KEY (town_id) REFERENCES town(town_id)
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
-- Counties
INSERT INTO county VALUES(1, 'Nairobi');
INSERT INTO county VALUES(2, 'Mombasa');
INSERT INTO county VALUES(3, 'Kisumu');
INSERT INTO county VALUES(4, 'Nakuru');

-- Towns
INSERT INTO town VALUES(100, 'Runda', 1);
INSERT INTO town VALUES(200, 'Ruaka', 1);
INSERT INTO town VALUES(300, 'Kahawa', 1);

-- Houses with unique IDs (using 4-letter IDs)
-- Runda
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(100, 'RB01', 'Bungalow', 'Runda Estate, Bungalow #RB01', 'https://maps.google.com/?q=Runda,Nairobi', 1000000, 500000);
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(100, 'RM01', 'Mansionette', 'Runda Estate, Mansionette #RM01', 'https://maps.google.com/?q=Runda,Nairobi', 800000, 400000);
-- Ruaka
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(200, 'UB01', 'Bungalow', 'Ruaka Estate, Bungalow #UB01', 'https://maps.google.com/?q=Ruaka,Nairobi', 800000, 450000);
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(200, 'UA01', 'Appartments & Flats', 'Ruaka Apartments, Flat #UA01', 'https://maps.google.com/?q=Ruaka,Nairobi', 100000, 55000);
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(200, 'UE01', 'Bedsitters', 'Ruaka Complex, Bedsitter #UE01', 'https://maps.google.com/?q=Ruaka,Nairobi', 17000, 8500);
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(200, 'US01', 'Singles', 'Ruaka Singles, Room #US01', 'https://maps.google.com/?q=Ruaka,Nairobi', 8000, 4000);
-- Kahawa
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(300, 'KB01', 'Bungalow', 'Kahawa Estate, Bungalow #KB01', 'https://maps.google.com/?q=Kahawa,Nairobi', 800000, 400000);
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(300, 'KA01', 'Appartments & Flats', 'Kahawa Apartments, Flat #KA01', 'https://maps.google.com/?q=Kahawa,Nairobi', 80000, 40000);
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(300, 'KE01', 'Bedsitters', 'Kahawa Complex, Bedsitter #KE01', 'https://maps.google.com/?q=Kahawa,Nairobi', 16000, 8000);
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent)
VALUES(300, 'KS01', 'Singles', 'Kahawa Singles, Room #KS01', 'https://maps.google.com/?q=Kahawa,Nairobi', 7000, 3500);

-- Rental costs
-- Runda
INSERT INTO rental_cost VALUES('RB01',100,'Bungalow',1000000,500000);
INSERT INTO rental_cost VALUES('RM01',100,'Mansionette',800000,400000);
-- Ruaka
INSERT INTO rental_cost VALUES('UB01',200,'Bungalow',800000,450000);
INSERT INTO rental_cost VALUES('UA01',200,'3-Bedroom House',100000,55000);
INSERT INTO rental_cost VALUES('UA01',200,'2-Bedroom',70000,35000);
INSERT INTO rental_cost VALUES('UA01',200,'1-Bedroom',34000,17000);
INSERT INTO rental_cost VALUES('UE01',200,'Bedsitters',17000,8500);
INSERT INTO rental_cost VALUES('US01',200,'Singles',8000,4000);
-- Kahawa
INSERT INTO rental_cost VALUES('KB01',300,'Bungalow',800000,400000);
INSERT INTO rental_cost VALUES('KA01',300,'3-Bedroom',80000,40000);
INSERT INTO rental_cost VALUES('KA01',300,'2-Bedroom',60000,30000);
INSERT INTO rental_cost VALUES('KA01',300,'1-Bedroom',20000,10000);
INSERT INTO rental_cost VALUES('KE01',300,'Bedsitters',16000,8000);
INSERT INTO rental_cost VALUES('KS01',300,'Singles',7000,3500);

-- Payment details
INSERT INTO payment_details VALUES('RB01',100,'Bungalow','446574332','34858','0734458232');
INSERT INTO payment_details VALUES('RM01',100,'Mansionette','49593858','79585','077887949');
INSERT INTO payment_details VALUES('UB01',200,'Bungalow','898668488','75737','0747385867');
INSERT INTO payment_details VALUES('UA01',200,'Appartments & Flats','768658683','647376','0702847827');
INSERT INTO payment_details VALUES('UE01',200,'Bedsitters','896987863','457275','0755673769');
INSERT INTO payment_details VALUES('US01',200,'Singles','694868351','995573','0712945858');
INSERT INTO payment_details VALUES('KA01',300,'Appartments & Flats','458483894','024757','071112353');
INSERT INTO payment_details VALUES('KE01',300,'Bedsitters','1234683785','01010','0700345087');
INSERT INTO payment_details VALUES('KS01',300,'Singles','896945832','01234','0712597944');
INSERT INTO payment_details VALUES('KB01',300,'Bungalow','457781112','78641','0768664759');

-- Sample data for locations (counties and towns) and houses

-- Towns in Nairobi
INSERT INTO town VALUES(101, 'Karen', 1);
INSERT INTO town VALUES(102, 'Kitengela', 1);
INSERT INTO town VALUES(103, 'Runda', 1);
INSERT INTO town VALUES(104, 'Westlands', 1);

-- Towns in Mombasa
INSERT INTO town VALUES(201, 'Nyali', 2);
INSERT INTO town VALUES(202, 'Bamburi', 2);

-- Towns in Kisumu
INSERT INTO town VALUES(301, 'Milimani', 3);

-- Towns in Nakuru
INSERT INTO town VALUES(401, 'Bahati', 4);

-- Houses in Karen (Nairobi)
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(101, 'K001', 'Bungalow', 'Karen Road, House #123', 'https://maps.google.com/?q=Karen,Nairobi', 100000, 50000);

INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(101, 'K002', 'Villa', 'Karen Drive, House #456', 'https://maps.google.com/?q=Karen,Nairobi', 150000, 75000);

-- Houses in Kitengela (Nairobi)
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(102, 'KT01', 'Apartment', 'Kitengela Plaza, Apt #10', 'https://maps.google.com/?q=Kitengela,Nairobi', 30000, 15000);

INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(102, 'KT02', 'Studio', 'Kitengela Heights, Apt #5', 'https://maps.google.com/?q=Kitengela,Nairobi', 20000, 10000);

-- Houses in Runda (Nairobi)
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(103, 'RD01', 'Mansion', 'Runda Estate, House #789', 'https://maps.google.com/?q=Runda,Nairobi', 200000, 100000);

-- Houses in Westlands (Nairobi)
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(104, 'WL01', 'Penthouse', 'Westlands Towers, Apt #20', 'https://maps.google.com/?q=Westlands,Nairobi', 120000, 60000);

-- Houses in Nyali (Mombasa)
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(201, 'NY01', 'Beach House', 'Nyali Beach Road, House #101', 'https://maps.google.com/?q=Nyali,Mombasa', 180000, 90000);

-- Houses in Bamburi (Mombasa)
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(202, 'BM01', 'Cottage', 'Bamburi Beach, House #202', 'https://maps.google.com/?q=Bamburi,Mombasa', 40000, 20000);

-- Houses in Milimani (Kisumu)
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(301, 'ML01', 'Townhouse', 'Milimani Estate, House #303', 'https://maps.google.com/?q=Milimani,Kisumu', 60000, 30000);

-- Houses in Bahati (Nakuru)
INSERT INTO houses(town_id, house_id, house_type, house_address, map_link, deposit_fee, monthly_rent) 
VALUES(401, 'BH01', 'Duplex', 'Bahati Heights, House #404', 'https://maps.google.com/?q=Bahati,Nakuru', 50000, 25000);

-- Add a test user
INSERT INTO user_info (first_name, second_name, email, phone_number, password)
VALUES ('Test', 'User', 'test@example.com', '0712345678', 'password');
