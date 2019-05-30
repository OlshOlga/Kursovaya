#pragma once
#include <fstream>
#include <cstdint>
using namespace std;

#pragma pack (1)
struct WavHeader {

	char rID[4] = {0}; // "RIFF"
	uint32_t rLen; // ����� ����� ��� ����� ���������
	char wID[4] = {0}; // "WAVE" - ��������� WAV
	char Fmt[4] = {0}; // "fmt " - thunk �������
	uint32_t Len; // ������ ����� thunka
	uint16_t Format; // ������
	uint16_t Channels; // ����� ������� (1)
	uint32_t SamplesPerSecond; // ��������/���
	uint32_t AvgBytesPerSecond; // ������/���
	uint16_t BlockAlign; // ������������ ������
	uint16_t BitsPerSample; // ����� �� ������
	char dID[4] = {0}; // "data"
	uint32_t dLen; // ����� ����� thunk�
};

class SampleRateChandger
{
protected:
	int16_t * value; // ����� ��� �������
	WavHeader header;
public:
	void read (ifstream & file); // ������ �����
	void decrease (); // ���������� ���-�� �������� � 2 ����
	void increase (); // ���������� ���-�� �������� � 2 ����
	void write (ofstream & file); // ������ � ����
	int16_t * getValueAdres (); // ���������� ��������� �� WavHeader
	WavHeader * getHeaderAdres (); // ���������� ��������� �� ������ �������

};

class ErrorWav
{
	string invalid_chunk;
public:
	explicit ErrorWav (string error):invalid_chunk(error) {};
	const string & getError() {
		return invalid_chunk;
	}
};

