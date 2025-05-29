# Attendance Monitoring System Using RFID, Arduino and Qt

## About the Project

This project is a demonstrative version and serves as the practical component of an engineering thesis. It was developed to present a personal vision of improving the process of attendance monitoring at universities.

The system was implemented for a single virtual classroom. RFID technology is used for student identification. An Arduino board acts as an intermediary device, transferring data from the RFID reader to a computer. Attendance data is stored in a database managed using MariaDB.

The program that verifies checksums and marks attendance in the database, as well as the application displaying attendance information, were written in C++ using the Qt framework. Several Qt modules were utilized to build the user interface and manage database communication.

## Features

- RFID-based student identification
- Arduino microcontroller as data intermediary
- Attendance data logging to MariaDB
- C++/Qt application with GUI
- Checksum verification for data integrity

## Technologies Used

- **C++** with **Qt Framework**
- **Arduino**
- **RFID**
- **MariaDB**

## Screenshots

![image](https://github.com/user-attachments/assets/55d2268d-56d5-49f8-8fe5-7b12d769b760)

*Figure 1: Login panel view*

![image](https://github.com/user-attachments/assets/0500f703-33af-4c8e-9ac5-c97e3bc9d883)

*Figure 2: Timetable panel with calendar – part of the default view for student and university accounts*

![image](https://github.com/user-attachments/assets/f2b5f91b-60eb-4e82-b619-cb35e4e31ea2)

*Figure 3: Timetable view for student account - calendar hidden*

![image](https://github.com/user-attachments/assets/1245a762-7cc8-4ad4-bf04-bfc71d8cc29d)

*Figure 4: Statistics panel view for student and university accounts*

![image](https://github.com/user-attachments/assets/49e22c7f-c146-4baf-a979-eccca8c17f30)

*Figure 5: Timetable view for university account – calendar section hidden*

![image](https://github.com/user-attachments/assets/b5b262b1-623e-4dd3-a8bc-3c41b44bc6ee)

*Figure 6: Sample report generated from the statistics view of a university account*

![image](https://github.com/user-attachments/assets/9c060c61-eab9-43e0-a4b8-28366c110f34)

*Figure 7: Sample attendance list generated from the timetable view of a university account*

![image](https://github.com/user-attachments/assets/599135f1-3e66-49b9-bbb9-dfd2a4c69da4)

*Figure 8: Sample report generated from the statistics view of a student account*

## Installation

### Prerequisites

- Qt 5
- C++
- MariaDB
- Arduino IDE

### Setup Instructions

1. cd Aplikacja/ && qmake app.pro && make
2. cd ../Sterownik/ && qmake app.pro && make
3. systemctl start mariadb
4. ./sterownik /dev/ttyACM0 &
5. cd ../ && ./name_of_the_app
