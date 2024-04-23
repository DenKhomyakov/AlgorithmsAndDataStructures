#include <iostream>
#include <fstream>
#include <istream>
#include <random>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;

// Функция проверки открытия файла для записи
bool IsFileOpen(ofstream& file) {
	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;

		return false;
	}
	else {
		cout << "Файл успешно открыт!" << endl;

		return true;
	}
}

// Функция проверки открытия файла для чтения
bool IsFileOpen(ifstream& file) {
	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;

		return false;
	}
	else {
		cout << "Файл успешно открыт!" << endl;

		return true;
	}
}

// Функция создания файла со случайным массивос чисел
bool CreateFileWithRandomNumbers(const string& fileName, const int numbersCount, const int maxNumerValue) {
	ofstream file;
	file.open(fileName);

	IsFileOpen(file);

	std::random_device randomDevice;
	std::mt19937 generation(randomDevice());
	std::uniform_int_distribution<> distribution(0, maxNumerValue);

	for (int i = 0; i < numbersCount; ++i) {
		file << distribution(generation) << " ";
	}

	file.close();
	
	return true;
}

// Функция проверки упорядоченности массива в файле
bool IsFileContainsSortedArray(const string& fileName) {
	ifstream file;
	file.open(fileName);

	IsFileOpen(file);

	int previousNumber = -1;
	int currentNumber = -1;

	while (file >> currentNumber) {
		if (currentNumber < previousNumber) {
			return false;
		}

		previousNumber = currentNumber;
	}

	return true;
}

// Функция разбиения главного файла
void SplitFile(const string& inputFileName, const string& outputFileName1, const string& outputFileName2) {
	ifstream inputFile;
	inputFile.open(inputFileName);

	IsFileOpen(inputFile);

	// Создаём файлы для записи
	ofstream outputFiles[2];
	outputFiles[0].open(outputFileName1);
	outputFiles[1].open(outputFileName2);

	int outputFileIndex = 0;
	int presentElement;
	int previousElement;

	inputFile >> previousElement;

	while (inputFile >> presentElement) {
		outputFiles[outputFileIndex] << previousElement << endl;

		if (previousElement > presentElement) {
			outputFileIndex = 1 - outputFileIndex;
		}

		previousElement = presentElement;
	}

	outputFiles[outputFileIndex] << previousElement;

	inputFile.close();
	outputFiles[0].close();
	outputFiles[1].close();
}

// Функция слияния файлов в главный файл */
bool MergeFiles(const string& inputFileName1, const string& inputFileName2, const string& outputFileName1, const string& outputFileName2) {
	// Создаём главный файл, куда будем записывать данные
	ifstream inputFiles[2];
	inputFiles[0].open(inputFileName1);
	inputFiles[1].open(inputFileName2);

	ofstream outputFiles[2];
	outputFiles[0].open(outputFileName1);
	outputFiles[1].open(outputFileName2);

	int currentInputFileIndex = 0;
	int currentOutputFileIndex = 0;
	int presentElement[2];
	int previousElement[2];

	inputFiles[0] >> previousElement[0];

	if (!(inputFiles[1] >> previousElement[1])) {
		return 1;
	}

	while (!inputFiles[0].eof() || !inputFiles[1].eof()) {
		if (previousElement[currentInputFileIndex] > previousElement[1 - currentInputFileIndex] && !inputFiles[1 - currentInputFileIndex].eof()) {
			currentInputFileIndex = 1 - currentInputFileIndex;
		}

		outputFiles[currentOutputFileIndex] << previousElement[currentInputFileIndex] << endl;
		inputFiles[currentInputFileIndex] >> presentElement[currentInputFileIndex];

		if (inputFiles[currentInputFileIndex].eof() || previousElement[currentInputFileIndex] > presentElement[currentInputFileIndex]) {
			if (!inputFiles[1 - currentInputFileIndex].eof()) {
				currentInputFileIndex = 1 - currentInputFileIndex;
			}

			outputFiles[currentOutputFileIndex] << previousElement[currentInputFileIndex] << endl;
			inputFiles[currentInputFileIndex] >> presentElement[currentInputFileIndex];

			while (!inputFiles[currentInputFileIndex].eof() && previousElement[currentInputFileIndex] <= presentElement[currentInputFileIndex]) {
				previousElement[currentInputFileIndex] = presentElement[currentInputFileIndex];
				outputFiles[currentOutputFileIndex] << previousElement[currentInputFileIndex] << endl;
				inputFiles[currentInputFileIndex] >> presentElement[currentInputFileIndex];
			}

			previousElement[1 - currentInputFileIndex] = presentElement[1 - currentInputFileIndex];

			currentOutputFileIndex = 1 - currentOutputFileIndex;
		}

		previousElement[currentInputFileIndex] = presentElement[currentInputFileIndex];
	}

	for (int i = 0; i < 2; i++) {
		inputFiles[i].close();
		outputFiles[i].close();
	}

	return 0;
}

// Функция сортировки главного файла
void SortFile(const string& inputFileName) {
	string FileNames[4] = { "F1.txt", "F2.txt", "F3.txt", "F4.txt" };

	SplitFile(inputFileName, FileNames[0], FileNames[1]);

	while (!MergeFiles(FileNames[0], FileNames[1], FileNames[2], FileNames[3])) {
		string temporaryFileName;

		for (int i = 0; i < 2; i++) {
			temporaryFileName = FileNames[i + 2];
			FileNames[i + 2] = FileNames[i];
			FileNames[i] = temporaryFileName;
		}
	}
}

// Функция создания и сортировки главного файла
int CreateAndSortFile(const string& fileName, const int numbersCount, const int maxNumberValue) {
	if (!CreateFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
		return -1;
	}

	SortFile(fileName);

	if (!IsFileContainsSortedArray(fileName)) {
		return -2;
	}

	return 1;
}

int main() {
	setlocale(LC_ALL, "Rus");

	string labFileName = "MainFileSort.txt";
	const int numbersCount = 100000;
	const int maxNumberValue = 1000000;

	CreateAndSortFile(labFileName, numbersCount, maxNumberValue);

	cout << endl;

	return 0;
}