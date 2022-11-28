#include <iostream>
#include <string>
#include <fstream>

int main() {

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

    return 0;
}