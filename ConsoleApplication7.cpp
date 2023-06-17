
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;
using namespace std;

class IFileCustom
{
public:
	virtual void toWrite(string filename, string data) = 0;
	virtual string toRead(string filename) = 0;
};

class FileManager : public IFileCustom
{
public:
	void toWrite(string filename, string data) override
	{
		ofstream file(filename);
		file << data;
		file.close();
	}

	string toRead(string filename) override
	{
		ifstream input_file(filename);
		string data((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
		input_file.close();
		return data;
	}
};

class Car
{
public:
	string brand;
	int year;
	string model;

	json toJson() const
	{
		json j;
		j["name"] = brand;
		j["year"] = year;
		j["model"] = model;
		return j;
	}

	void fromJson(const json& j)
	{
		brand = j["brand"];
		year = j["year"];
		model = j["model"];
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << " Создаём список Car\n";
	vector<Car> cars =
	{
		{"Ford", 2015, "Mondeo"},
		{"Audi", 2018, "A5"},
		{"KIA", 2013, "Rio"},
	};

	cout << "Записываем список в файл в формате JSON\n";
	json j;
	for (const auto& p : cars)
	{
		j.push_back(p.toJson());
	}

	ofstream file("cars.json");
	file << j.dump(4);
	file.close();

	cout << "Читаем список из файла и выводим в консоль\n";
	ifstream input_file("cars.json");
	json data;
	input_file >> data;

	for (const auto& j : data)
	{
		Car p;
		p.fromJson(j);
		cout << "Name: " << p.brand << endl;
		cout << "Age: " << p.year << endl;
		cout << "Address: " << p.model << endl;
		cout << endl;
	}

	FileManager fm;

	cout << "Записываем данные в файл\n";
	string data1 = "Hello, World!";
	fm.toWrite("file.txt", data1);

	cout << "Читаем данные из файла и выводим в консоль\n";
	string file_data = fm.toRead("file.txt");
	cout << file_data << endl;

	return 0;
}
