#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <Windows.h>

#define LIC_KEY 78261
#define LIC_TIME 180
#define LIC_COUNT 5
 
#define DEBUG 0


int main() {

    // Создание директории с файлом для защиты
    std::string license_file = std::getenv("APPDATA");
    license_file.append("\\lab2_names");
    CreateDirectory(license_file.c_str(), NULL);
    license_file.append("\\lb.lcns");

    if (DEBUG) {
        std::cout << "Debug: path of license file is " << license_file << std::endl;
    }

    std::ifstream lin(license_file);

    int lic_time = LIC_TIME;
    int lic_count = LIC_COUNT; // Изначальные лимиты

    std::clock_t begin_time = std::clock(); // Получаем время в начальный момент

    if (!lin.fail()) {
        lin >> lic_time >> lic_count; // Читаем лимиты
        lic_time ^= LIC_KEY;
        lic_count ^= LIC_KEY;
        lin.close();

        if (lic_count <= 0 || lic_time <= 0 || lic_time > LIC_TIME || lic_count > LIC_COUNT) {
            std::cout << "Limits are out. Buy a license or uninstall the program." << std::endl; // Лимиты вышли
            return 0; 
        }
    }

    // Простая программа
    std::string new_name;
    bool name_in_file = false;

    std::cout << "Enter the name:" << std::endl;
    std::getline(std::cin, new_name);

    std::string s;
    std::ifstream fin("names.txt");

    if (fin.is_open()) {
        while (std::getline(fin, s)) {
            if (s == new_name) {
                std::cout << "There is the name in names.txt" << std::endl;
                name_in_file = true;
            }
        }
    }
    
    fin.close();
    
    if (!name_in_file) {
        std::ofstream fout("names.txt", std::ios_base::app);
        fout << new_name << "\n";
        fout.close();
    }
    // Конец простой программы

    // Считаем время использования и обновляем лимиты
    int spend_time = int((std::clock() - begin_time) / 1000.0);
    if (spend_time < 1) spend_time = 1;
    lic_time -= spend_time;
    lic_count--;

    if (lic_count < 0) lic_count = 0;
    if (lic_time < 0) lic_time = 0;

    std::cout << "Limits\nMinutes left: " << (lic_time / 60.0) << "\nUses left: " << lic_count << std::endl;

    // Обновляем файл для защиты
    std::ofstream lout(license_file);
    if(!lout.fail()) {
        if (DEBUG) {
            std::cout << "Debug: license file created. Path " << license_file << std::endl;
        }
        lout << (lic_time ^ LIC_KEY) << " " << (lic_count ^ LIC_KEY);
        lout.close();
    }


    return 0;
}