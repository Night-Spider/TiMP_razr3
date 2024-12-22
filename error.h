/// \file error.h
/// \brief Заголовочный файл для обработки ошибок.

/**
 * @file error.h
 * @brief Заголовочный файл для определения классов ошибок.
 * @details Этот файл содержит определения классов критических и некритических ошибок.
 * @author Липатов Егор
 * @date 22.12.2024
 * @license MIT License
 */


#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>
#include <string>

/// \class crit_err
/// \brief Класс критической ошибки.
class crit_err : public std::runtime_error {
public:
    /// \brief Конструктор класса crit_err.
    /// \param message Сообщение об ошибке.
    explicit crit_err(const std::string& message) : std::runtime_error(message) {}
};

/// \class no_crit_err
/// \brief Класс некритической ошибки.
class no_crit_err : public std::runtime_error {
public:
    /// \brief Конструктор класса no_crit_err.
    /// \param message Сообщение об ошибке.
    explicit no_crit_err(const std::string& message) : std::runtime_error(message) {}
};

#endif // ERROR_H
