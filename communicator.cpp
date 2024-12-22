/**
 * @file communicator.cpp
 * @brief Реализация методов класса communicator.
 * @details Этот файл содержит реализацию методов для выполнения операций, связанных с коммуникацией.
 * @author Липатов Егор
 * @date 22.12.2024
 * @license MIT License
 */


#include "communicator.h"
#include "error.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <random>
#include <sstream>
#include <iomanip>
#include <cryptlib.h>
#include <sha.h>
#include <hex.h>
#include <string>

std::string communicator::sha256(const std::string& input_str) {
    using namespace CryptoPP;

    byte digest[SHA256::DIGESTSIZE];
    SHA256 hash;

    hash.CalculateDigest(digest, (const byte*)input_str.c_str(), input_str.size());

    // Преобразуем в шестнадцатеричное представление
    std::string hexString;
    HexEncoder encoder;
    encoder.Attach(new StringSink(hexString));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return hexString;
}

uint64_t communicator::generate_salt() {
    std::random_device rd;
    std::uniform_int_distribution<uint64_t> dist(0, 0xFFFFFFFFFFFFFFFF); // Генерируем 64-битное число
    return dist(rd); // Возвращаем соль как 64-битное число
}

std::string communicator::salt_to_hex(uint64_t salt) {
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << salt; // Преобразуем в шестнадцатеричное представление
    return ss.str(); // Возвращаем строку в шестнадцатеричном формате
}

int communicator::connection(uint32_t port, const std::map<std::string, std::string>& base, logger* l) {
    // Реализация соединения (пример, можно адаптировать под ваши нужды)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        l->writelog("Ошибка создания сокета");
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        l->writelog("Ошибка привязки сокета");
        close(sockfd);
        return -1;
    }

    if (listen(sockfd, 5) < 0) {
        l->writelog("Ошибка прослушивания сокета");
        close(sockfd);
        return -1;
    }

    l->writelog("Сервер запущен и слушает на порту " + std::to_string(port));
    return sockfd; // Возвращаем дескриптор сокета
}
