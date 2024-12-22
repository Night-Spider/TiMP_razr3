/**
 * @file base.cpp
 * @brief Реализация методов класса base.
 * @details Этот файл содержит реализацию методов для загрузки пользователей и доступа к их данным.
 * @author Липатов Егор
 * @date 22.12.2024
 * @license MIT License
 */


#include "base.h"
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>

base::base(const std::string& filename) : filename_(filename) {}

void base::load() {
    std::ifstream file(filename_);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка открытия файла базы пользователей: " + filename_);
    }

    std::string line;
    bool isEmpty = true; // Флаг для проверки пустого файла

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue; // Игнорируем пустые строки
        }
        isEmpty = false; // Если хотя бы одна строка не пустая

        size_t pos = line.find(':');
        if (pos == std::string::npos) {
            throw std::runtime_error("Неверный формат строки: " + line);
        }

        std::string id = line.substr(0, pos);
        std::string password = line.substr(pos + 1);

        // Проверка на дубликаты
        if (users_.find(id) != users_.end()) {
            throw std::runtime_error("Обнаружен дубликат пользователя: " + id);
        }

        users_[id] = password;
    }

    // Проверка на пустой файл
    if (isEmpty) {
        throw std::runtime_error("Файл пуст: " + filename_);
    }

    file.close();
}

const std::map<std::string, std::string>& base::get_users() const {
    return users_;
}

std::string base::get_filename() const {
    return filename_; // Новый метод для тестирования
}
