#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <clocale>
#include <windows.h>

namespace fs = std::filesystem;

int main() {
    SetConsoleOutputCP(65001);

    std::cout << "Привет! Подождите немного...\n";

    char* tempEnv = std::getenv("LOCALAPPDATA");

    if (tempEnv == nullptr) {
        std::cout << "Не удалось найти папку Localappdata" << std::endl;
        return 1;
    }

    std::filesystem::path fullPath = tempEnv;
    fullPath /= "Temp";

    int deletedFiles = 0;
    int skippedFiles = 0;

    if (!fs::exists(fullPath)) { 
        std::cout << "Temp не найдена на вашем ПК!\n";
    } else {
        std::cout << "Успешно! Найден путь: " << fullPath.string() << "\n";

      for (const auto& entry : fs::directory_iterator(fullPath)) {  
            try {
                fs::remove_all(entry.path());
                deletedFiles++;
            } 
            catch (const fs::filesystem_error& e) {
                skippedFiles++;
            }
        }
    }

    std::cout << "Удалено файлов: " << deletedFiles << std::endl;
    std::cout << "Пропущено файлов: " << skippedFiles << std::endl;

    std::cout << "\nНажмите Enter, чтобы выйти...";
    std::cin.get();

    return 0;
}