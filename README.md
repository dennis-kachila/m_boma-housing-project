# m_boma Housing Project

## Overview
m_boma Housing Project is a C++ application designed to help tenants find and book their desired houses for rent across various counties. The project was developed as part of a Computer Programming Unit at the university.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Setup & Installation](#setup--installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features
- User registration (Name, Phone, Email, Password)
- Navigation through sampled counties (e.g., Nairobi)
- View main towns and available houses in each town
- Display house details: type, deposit fee, monthly rent, and map link
- Multiple payment options (M-Pesa, bank)
- Receipt generation for payments
- House booking with a 30-day grace period

## Project Structure
```
├── database/
│   └── housing_database.sql         # SQL database schema
├── source_code/
│   ├── boma_main.cpp               # Main application entry point
│   ├── boma.cpp                    # Core logic implementation
│   └── boma.h                      # Header file(s)
├── Untested-main.cpp               # Additional/experimental code
└── README.md                       # Project documentation
```

## Setup & Installation
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd m_boma-housing-project
   ```
2. Compile the source code (using g++):
   ```bash
   g++ source_code/boma_main.cpp source_code/boma.cpp -o boma_housing
   ```
3. (Optional) Set up the database using the provided SQL script in `database/housing_database.sql`.

## Usage
Run the compiled program:
```bash
./boma_housing
```
Follow the on-screen instructions to register, browse houses, and make bookings.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request. For major changes, open an issue first to discuss your ideas.

## License
This project is for educational purposes.