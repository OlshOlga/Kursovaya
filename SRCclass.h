#pragma once
#include <fstream>
#include <cstdint>
using namespace std;

#pragma pack (1)
struct WavHeader {

	char rID[4] = {0}; // "RIFF"
	uint32_t rLen; // длина файла без этого заголовка
	char wID[4] = {0}; // "WAVE" - заголовок WAV
	char Fmt[4] = {0}; // "fmt " - thunk формата
	uint32_t Len; // длинна этого thunka
	uint16_t Format; // формат
	uint16_t Channels; // число каналов (1)
	uint32_t SamplesPerSecond; // отсчетов/сек
	uint32_t AvgBytesPerSecond; // байтов/сек
	uint16_t BlockAlign; // выравнивание блоков
	uint16_t BitsPerSample; // битов на отсчет
	char dID[4] = {0}; // "data"
	uint32_t dLen; // длина этого thunkа
};

class SampleRateChandger
{
	int16_t * value; 
	WavHeader header;
	int num_samples;
public:
	void read (ifstream & file); 
	void decrease (); 
	void increase (); 
	void write (ofstream & file);
	int16_t * getValueAdres (); 
	WavHeader * getHeaderAdres (); 
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

