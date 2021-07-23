//============================================================================
// Name        : Bus.cpp
// Author      : Autumn Arnold
// Version     : 1.0.0
// Copyright   : 
// Description : Bus Reservation System
//============================================================================

#include <iostream>
#include <conio.h>
#include <cstdio>
#include <string.h>
#include <cstdlib>

using namespace std;

static int p = 0;

class bus_system {
	char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][10];

public:
	void install();
	void allotment();
	void empty();
	void show();
	void avail();
	void position(int i);
} bus[10];

// to make decorative character lines
void vline(char ch) {
	for(int i = 80; i > 0; i--) {
		cout << ch;
	}
}

// to add a new bus line
void bus_system::install() {
	cout << "Enter Bus No. : ";
	cin >> bus[p].busn;

	cout << "\nEnter Driver's Name : ";
	cin >> bus[p].driver;

	cout << "\nArrival Time : ";
	cin >> bus[p].arrival;		// input needs to be in military time

	cout << "\nDeparture Time : ";
	cin >> bus[p].depart;		// input needs to be in military time

	cout << "\nFrom : ";		// input needs to be a 3 character acronym
	cin >> bus[p].from;

	cout << "\nTo : ";			// input needs to be a 3 character acronym
	cin >> bus[p].to;

	bus[p].empty();
	p++;
}

// to add in passengers
void bus_system::allotment() {
	int seat;
	char number[5];
	top:
		cout << "Bus No. : ";
		cin >> number;

		int n;
		for(n = 0; n <=p; n++) {
			if(strcmp(bus[n].busn, number) == 0) {
				break;
			}
		}

		while(n <= p) {
			cout << "\nSeat Number : ";
			cin >> seat;
			if(seat > 32) {
				cout << "\nThere are only 32 seats available in this bus.";
			}
			else {
				if(strcmp(bus[n].seat[seat/4][(seat%4) - 1], "Empty") == 0) {
					cout << "Enter passanger's name : ";
					cin >> bus[n].seat[seat/4][(seat%4) - 1];
					break;
				}
				else {
					cout << "The seat no. is already reserved.\n";
				}
			}
		}

		if(n > p) {
			cout << "Enter correct bus no.\n";
			goto top;
		}
}

// to display an empty bus
void bus_system::empty() {
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 4; j++) {
			strcpy(bus[p].seat[i][j], "Empty");
		}
	}
}

// to show a bus's status
void bus_system::show() {
	int n;
	int a = 1;
	char number[5];
	cout << "Enter bus no. : ";
	cin >> number;
	for(n = 0; n <= p; n++) {
		if(strcmp(bus[n].busn, number) == 0) {
			break;
		}
	}

	while(n <= p) {
		vline('*');
		cout << "\nBus no. : " << bus[n].busn
			 << "\nDriver: " << bus[n].driver
			 << "\nArrival Time : " << bus[n].arrival
			 << "\nDeparture Time : " << bus[n].depart
			 << "\nFrom : " << bus[n].from
			 << "\nTo : " << bus[n].to << "\n";
		vline('*');

		bus[0].position(n);
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 4; j++) {
				a++;
				if(strcmp(bus[n].seat[i][j], "Empty") != 0) {
					cout << "\nThe seat no. " << (a-1) << " is reserved for " << bus[n].seat[i][j] << ".";
				}
			}
		}

		break;
	}

	if(n > p) {
		cout << "Enter correct bus no. : ";
	}
}

// to show seat availability of a bus
void bus_system::avail() {
	for(int n = 0; n < p; n++) {
		cout << "\n"
		vline('*');
		cout << "\nBus No. : " << bus[n].busn
			 << "\nDriver: " << bus[n].driver
			 << "\nArrival Time : " << bus[n].arrival
			 << "\nDeparture Time : " << bus[n].depart
			 << "\nFrom : " << bus[n].from
			 << "\nTo : " << bus[n].to << "\n";
		vline('*');
	}
}

// to show the seat position within a bus
void bus_system::position(int l) {
	int s = 0;
	p = 0;
	for(int i = 0; i < 8; i++) {
		cout << "\n";
		for(int j = 0; j < 4; j++) {
			s++;
			if(strcmp(bus[l].seat[i][j], "Empty") == 0) {
				cout.width(5);
				cout.fill(' ');
				cout << s << ".";
				cout.width(10);
				cout.fill(' ');
				cout << bus[l].seat[i][j];
				p++;
			}
			else {
				cout.width(5);
				cout.fill(' ');
				cout << s << ".";
				cout.width(10);
				cout.fill(' ');
				cout << bus[l].seat[i][j];
			}
		}
	}

	cout << "\n\nThere are " << p << " seats empty in Bus No. : " << bus[l].busn;
}

int main() {
	int w;

	system("cls");

	while(1) {
		cout << "\n\n";
		cout << "\t\t\t1. Install\n\t\t\t"
			 << "2. Reservation\n\t\t\t"
			 << "3. Show\n\t\t\t"
			 << "4. Buses Available.\n\t\t\t"
			 << "5. Exit";

		cout << "\n\t\t\tEnter your choice: -> ";
		cin >> w;
		switch(w) {
		case 1:
			bus[p].install();
			break;
		case 2:
			bus[p].allotment();
			break;
		case 3:
			bus[0].show();
			break;
		case 4:
			bus[0].avail();
			break;
		case 5:
			exit(0);
		}
	}

	return 0;
}
