
#include <termios.h>
#include <signal.h>
#include <fcntl.h>

#include <iostream>

#include "sql.hpp"
#include "../arduino_RFID/common.hpp"

DB db;
int serial = -1;

static void closeSignal(int exitcode) {
	if(db.isOpen()) {
		db.closeDB();
	}
	if(serial != -1) {
		close(serial);
	}

	exit(exitcode);
}

int serialInit(const char* path){
	int serial = open(path, O_RDWR);
	struct termios tty;
	tcgetattr(serial, &tty);

	tty.c_cflag &= ~PARENB;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;

	tty.c_cflag &= ~CRTSCTS;
	tty.c_cflag |= CREAD | CLOCAL;
	tty.c_iflag &= ~(IXON | IXOFF | IXANY);
	tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	tty.c_oflag &= ~OPOST;

	tty.c_cc[VMIN]  = 0;
	tty.c_cc[VTIME] = 20;

	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);
	tcsetattr(serial, TCSANOW, &tty);

	tcflush(serial, TCIOFLUSH);

	return serial;
}

uint8_t hexToU8(char src[2]) {
	uint8_t ret;

	for(int i = 0; i < 2; i++) {
		int mult = i%2 ? 1 : 16;
		if(src[i] >= 48 && src[i] <= 57) {
			ret += (src[i]-48)*mult;
		}
		else if(src[i] >= 65 && src[i] <= 70) {
			ret += (src[i]-55)*mult;
		}
	}
	return ret;
}

uint32_t convertID(char* src) {
	uint32_t id;
	uint8_t checkSum = hexToU8(src);
	int i = 2;
	for(; i < DATA_SIZE-2; i += 2) {
		uint8_t byte = hexToU8(src+i);
		id <<= 8;
		id += byte;
		checkSum ^= byte;
	}

	if(checkSum == hexToU8(src+i)) {
		return id;
	}

	return 0;
}

int main(int argc, char **argv) {

	if(argc == 2) {
		char buf[DATA_SIZE];

		serial = serialInit(argv[1]);

		if(serial > 0) {
			signal(SIGINT, closeSignal);
			while(1) {
				do {
					read(serial, buf, 1);
				}while (buf[0] != START_BYTE);

				int s = 0;
				do {
					s += read(serial, buf+s, DATA_SIZE-s);
				}while(s < DATA_SIZE);

				if(uint32_t id = convertID(buf)) {
					if(db.connectDB()) {
						int userID = db.select(id);
						if(db.checkLastAttendance(userID)) {
							if(db.insert(userID)) {
								db.closeDB();
								std::cout<<"Obecność zarejestrowana"<<std::endl;
								write(serial, &STATUS_OK, 1);
							}else {
								std::cerr<<"Błąd. Obecność nie została"
									" zarejestrowana"<<std::endl;
							}
						}else {
							std::cout<<"Masz już obecność"<<std::endl;
							write(serial, &STATUS_OK, 1);
						}
					}else {
						std::cerr<<"Błąd. Program nie połączył się"
							" z bazą danych"<<std::endl;
					}
				}else {
					std::cerr<<"Błąd odczytu danych"<<std::endl;
				}
			}
		}else {
			std::cerr<<"Błąd. Nie można otworzyć port serial"<<std::endl;
		}
	}else {
		std::cerr<<"Błędna liczba argumentów programu"<<std::endl;
		std::cerr<<"Wzorzec: "<<argv[0]<<" urządzenie"<<std::endl;
	}

	return 0;
}
