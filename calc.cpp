/**
 * @file calc.cpp
 * @brief Реализация методов класса calc.
 * @details Этот файл содержит реализацию методов для выполнения математических операций и вычисления SHA256.
 * @author Липатов Егор
 * @date 22.12.2024
 * @license MIT License
 */

#include "calc.h"

uint32_t calc::send_res() {
    uint32_t result = 1;
    for (const auto& value : values) {
        if (value == 0) {
            return 0; // Возвращаем 0, если одно из значений равно 0
        }
        if (result > std::numeric_limits<uint32_t>::max() / value) {
            return std::numeric_limits<uint32_t>::max(); // Возвращаем максимальное значение при переполнении
        }
        result *= value;
    }
    return result;
}

double calc::divide() {
    if (values.empty()) {
        throw std::runtime_error("No values to divide");
    }
    double result = static_cast<double>(values[0]);
    for (std::size_t i = 1; i < values.size(); ++i) {
        if (values[i] == 0) {
            throw std::runtime_error("Division by zero");
        }
        result /= static_cast<double>(values[i]);
    }
    return result;
}

std::string calc::calculate_sha256(const std::string& input) {
    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::StringSource ss(input, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::StringSink(digest)
        )
    );

    // Преобразуем результат в шестнадцатеричный формат
    std::string hexDigest;
    CryptoPP::StringSource(digest, true,
        new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(hexDigest)
        )
    );

    return hexDigest; // Возвращаем результат в правильном формате
}
