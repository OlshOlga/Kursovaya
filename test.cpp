#include "D:\Documents\unittest-cpp\UnitTest++\UnitTest++.h"
#include "D:\Documents\SRChandger\SRCclass.h"
#include "D:\Documents\SRChandger\SRCclass.cpp"

struct readFixture {
	SampleRateChandger * obj;
	int16_t arr[10] = {0,1,2,3,4,5,6,7,8,9}; // массив сэмплов
	ifstream file;
	char r[4] = {'R','I','F','F'};
	char w[4] = {'W','A','V','E'};
	char f[4] = {'f','m','t',' '};
	char d[4] = {'d','a','t','a'};

	readFixture () {
		obj = new SampleRateChandger();
		file.open("/home/user/Downloads/Test.wav");
		obj -> read(file);
	}
	~readFixture() {
		delete obj;
		file.close();
	}
};

struct erFixture {
	ifstream fr; //файл с некорректным RIFF заголовком
	ifstream fw; //файл с некорректным WAVE заголовком
	ifstream ff; //файл с некорректным fmt заголовком
	ifstream fp; //файл с сжатием
	ifstream fc; //не однокональный файл
	ifstream fSR; //файл с недопустимой ЧД
	ifstream fBS; //файл с недопустимой битностью
	ifstream fd; //файл с некорректным data заголовком
	erFixture () {
		fr.open("/home/user/Downloads/1.wav");
		fw.open("/home/user/Downloads/2.wav");
		ff.open("/home/user/Downloads/3.wav");
		fp.open("4.wav");
		fc.open("/home/user/Downloads/5.wav");
		fSR.open("/home/user/Downloads/6.wav");
		fBS.open("/home/user/Downloads/7.wav");
		fd.open("/home/user/Downloads/8.wav");
	}
	~erFixture() {
		fr.close();
		fw.close();
		ff.close();
		fc.close();
		fSR.close();
		fBS.close();
		fd.close();
	}
};

struct iFixture {
	SampleRateChandger * obj;
	int16_t arrIncreased[19] = {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9}; // массив с удвоенным числом сэмплов
	ifstream file;
	iFixture () {
		obj = new SampleRateChandger();
		file.open("/home/user/Downloads/Test.wav");
		obj -> read(file);
		obj -> increase();
	}
	~iFixture() {
		delete obj;
		file.close();
	}
};

struct dFixture {
	SampleRateChandger * obj;
	int16_t arrDecreased[5] = {0,2,4,6,8}; //массив с уменьшиным в 2ое числом сэмплов
	ifstream file;
	dFixture () {
		obj = new SampleRateChandger();
		file.open("/home/user/Downloads/Test.wav");
		obj -> read(file);
		obj -> decrease();
	}
	~dFixture() {
		delete obj;
		file.close();
	}
};

struct writeFixture {
	SampleRateChandger * obj_1; // для записи
	SampleRateChandger * obj_2; // для чтения записанного файла
	int16_t arr[10] = {0,1,2,3,4,5,6,7,8,9}; // массив сэмплов
	char r[4] = {'R','I','F','F'};
	char w[4] = {'W','A','V','E'};
	char f[4] = {'f','m','t',' '};
	char d[4] = {'d','a','t','a'};
	ifstream f1; // для первого чтения
	ofstream f2; // для записи прочитанного
	ifstream f3; // для чтения записанного
	writeFixture () {
		obj_1 = new SampleRateChandger();
		obj_2 = new SampleRateChandger();
		f1.open("/home/user/Downloads/Test.wav");
		obj_1 -> read(f1);
		f1.close();
		f2.open("/home/user/Downloads/TestTest.wav");
		obj_1 -> write(f2);
		f2.close();
		f3.open("/home/user/Downloads/TestTest.wav");
		obj_2 -> read(f3);
		f3.close();
	}
	~writeFixture() {
		delete obj_1;
		delete obj_2;
	}
};

SUITE(ReadTest)
{
	TEST_FIXTURE(readFixture, read_validWavHeader) {
		CHECK_ARRAY_EQUAL(r, obj -> getHeaderAdres() -> rID, 4);
		CHECK_EQUAL(56, obj -> getHeaderAdres() -> rLen);
		CHECK_ARRAY_EQUAL(w, obj -> getHeaderAdres() -> wID, 4);
		CHECK_ARRAY_EQUAL(f, obj -> getHeaderAdres() -> Fmt, 4);
		CHECK_EQUAL(16, obj -> getHeaderAdres() -> Len);
		CHECK_EQUAL(1, obj -> getHeaderAdres() -> Format);
		CHECK_EQUAL(1, obj -> getHeaderAdres() -> Channels);
		CHECK_EQUAL(16000, obj -> getHeaderAdres() -> SamplesPerSecond);
		CHECK_EQUAL(32000, obj -> getHeaderAdres() -> AvgBytesPerSecond);
		CHECK_EQUAL(2, obj -> getHeaderAdres() -> BlockAlign);
		CHECK_EQUAL(16, obj -> getHeaderAdres() -> BitsPerSample);
		CHECK_ARRAY_EQUAL(d, obj -> getHeaderAdres() -> dID, 4);
		CHECK_EQUAL(20, obj -> getHeaderAdres() -> dLen);
	}

	TEST_FIXTURE(readFixture, read_validWavSamples) {
		CHECK_ARRAY_EQUAL(arr, obj -> getValueAdres(), 10);
	}

	TEST_FIXTURE(erFixture, read_notValidRIFF) {
		CHECK_THROW (SampleRateChandger().read(fr), ErrorWav);
	}
	TEST_FIXTURE(erFixture, read_notValidWAVE) {
		CHECK_THROW (SampleRateChandger().read(fw), ErrorWav);
	}
	TEST_FIXTURE(erFixture, read_notValidFMT) {
		CHECK_THROW (SampleRateChandger().read(ff), ErrorWav);
	}
	TEST_FIXTURE(erFixture, read_notValidFormat) {
		CHECK_THROW (SampleRateChandger().read(fp), ErrorWav);
	}
	TEST_FIXTURE(erFixture, read_notValidCannels) {
		CHECK_THROW (SampleRateChandger().read(fc), ErrorWav);
	}
	TEST_FIXTURE(erFixture, read_notValidSR) {
		CHECK_THROW (SampleRateChandger().read(fSR), ErrorWav);
	}
	TEST_FIXTURE(erFixture, read_notValidBperS) {
		CHECK_THROW (SampleRateChandger().read(fBS), ErrorWav);
	}
	TEST_FIXTURE(erFixture, read_notValidDATA) {
		CHECK_THROW (SampleRateChandger().read(fd), ErrorWav);
	}

}

SUITE(IncreaseTest)
{
	TEST_FIXTURE(iFixture, increase_wavHeader) {
		CHECK_EQUAL(74, obj -> getHeaderAdres() -> rLen);
		CHECK_EQUAL(32000, obj -> getHeaderAdres() -> SamplesPerSecond);
		CHECK_EQUAL(38, obj -> getHeaderAdres() -> dLen);
	}

	TEST_FIXTURE(iFixture, increase_wavSamples) {
		CHECK_ARRAY_EQUAL(arrIncreased, obj -> getValueAdres(), 19);
	}
}

SUITE(DecreaseTest)
{
	TEST_FIXTURE(dFixture, decrease_wavHeader) {
		CHECK_EQUAL(46, obj -> getHeaderAdres() -> rLen);
		CHECK_EQUAL(8000, obj -> getHeaderAdres() -> SamplesPerSecond);
		CHECK_EQUAL(10, obj -> getHeaderAdres() -> dLen);
	}

	TEST_FIXTURE(dFixture, decrease_wavSamples) {
		CHECK_ARRAY_EQUAL(arrDecreased, obj -> getValueAdres(), 5);
	}
}

SUITE (WriteTest)
{
	TEST_FIXTURE(writeFixture, write_wavHeader) {
		CHECK_ARRAY_EQUAL(obj_1 -> getHeaderAdres() -> rID, obj_2 -> getHeaderAdres() -> rID, 4);
		CHECK_EQUAL(obj_1 -> getHeaderAdres() -> rLen, obj_2 -> getHeaderAdres() -> rLen);
		CHECK_ARRAY_EQUAL(obj_1 -> getHeaderAdres() -> wID, obj_2 -> getHeaderAdres() -> wID, 4);
		CHECK_ARRAY_EQUAL(obj_1 -> getHeaderAdres() -> Fmt, obj_2 -> getHeaderAdres() -> Fmt, 4);
		CHECK_EQUAL(obj_1 -> getHeaderAdres() -> Len, obj_2 -> getHeaderAdres() -> Len);
		CHECK_EQUAL(obj_1 -> getHeaderAdres() -> Format, obj_2 -> getHeaderAdres() -> Format);
		CHECK_EQUAL(obj_1 -> getHeaderAdres() -> Channels, obj_2 -> getHeaderAdres() -> Channels);
		CHECK_EQUAL(obj_1 -> getHeaderAdres() -> SamplesPerSecond, obj_2 -> getHeaderAdres() -> SamplesPerSecond);
		CHECK_EQUAL(obj_1 -> getHeaderAdres() -> AvgBytesPerSecond, obj_2 -> getHeaderAdres() -> AvgBytesPerSecond);
		CHECK_EQUAL(obj_1 -> getHeaderAdres() -> BlockAlign, obj_2 -> getHeaderAdres() -> BlockAlign);
		CHECK_EQUAL(obj_1 -> getHeaderAdres() -> BitsPerSample, obj_2 -> getHeaderAdres() -> BitsPerSample);
		CHECK_ARRAY_EQUAL(obj_1 -> getHeaderAdres() -> dID, obj_2 -> getHeaderAdres() -> dID, 4);
		CHECK_EQUAL(obj_1 -> getHeaderAdres() -> dLen, obj_2 -> getHeaderAdres() -> dLen);
	}

	TEST_FIXTURE(writeFixture, write_wavSamples) {
		CHECK_ARRAY_EQUAL(obj_1 -> getValueAdres(), obj_2 -> getValueAdres(), 10);
	}
}


int main(int argc, char **argv)
{

	return UnitTest::RunAllTests();
}
