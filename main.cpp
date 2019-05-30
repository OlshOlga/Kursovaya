#include <iostream>
#include <fstream>
#include <string>
#include "D:\Documents\SRChandger\SRCclass.h"
#include "D:\Documents\SRChandger\SRCclass.cpp"
using namespace std;

int main(int argc, char **argv)
{
	if (argc != 4) {
		cout << "Incorrect input of parameters\n";
		return 1;
	}
	ifstream f(argv[1], ios::binary);
	if(!f.is_open()) {
		cout << "File wasn't found\n";
		return 1;
	}

	ofstream fs(argv[2], ios::out | ios::binary);
	if(!fs.is_open()) {
		cout << "File wasn't created\n";
		return 1;
	}

	SampleRateChandger(samples);
	struct WavHeader *p;
	p = samples.getHeaderAdres();
	
	try {
		samples.read(f);
	} catch (ErrorWav & msg) {
		cerr << msg.getError() << endl;
		return 1;
	}
	f.close();
    
	char * op = argv[3];
	if (*op == '0') {
		if (p->SamplesPerSecond == 32000) {
			cout<<"SamplesPerSecond is already the max\n";
			return 1;
		}
		else samples.increase();
	} else if (*op == '1') {
		if (p->SamplesPerSecond == 8000) {
			cout<<"SamplesPerSecond is already the min\n";
			return 1;
		}
		else samples.decrease();
	} else {
		cout << "Not valid operation\n";
		return 1;	
	}	
	samples.write (fs);

	fs.close();


	return 0;
}
