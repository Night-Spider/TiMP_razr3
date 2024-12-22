/**
 * @file main.cpp
 * @brief Главный файл приложения.
 * @details Этот файл содержит точку входа в программу и отвечает за инициализацию и запуск приложения.
 * @author Липатов Егор
 * @date 22.12.2024
 * @license MIT License
 */


#include "interface.h"
#include "base.h"
#include "communicator.h"
#include "log.h"

#include <iostream>

int main(int argc, const char** argv) {
    interface iface;
    if (!iface.parser(argc, argv)) {
        return 0; // Показать справку или ошибка парсинга
    }

    std::string basefile = iface.get_base();
    std::string logfile = iface.get_log();
    uint32_t port = iface.get_port(); 

    logger log(logfile);
    try {
        base user_base(basefile);
        user_base.load();

        // Запуск сервера
        communicator comm;
        comm.connection(port, user_base.get_users(), &log);
    } catch (const std::exception& e) {
        log.writelog("Ошибка: " + std::string(e.what()));
        return 1; // Завершение с ошибкой
    }

    return 0; // Успешное завершение
}
