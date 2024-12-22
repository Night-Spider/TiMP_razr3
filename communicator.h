/**
 * @brief Класс для выполнения операций, связанных с коммуникацией.
 * @details Этот класс предоставляет методы для вычисления SHA256, генерации соли и настройки соединения.
 */
 
/**
 * @file communicator.h
 * @brief Заголовочный файл для класса communicator, который выполняет операции, связанные с коммуникацией.
 * @details Этот класс предоставляет методы для вычисления SHA256, генерации соли и настройки соединения.
 * @author Липатов Егор
 * @date 22.12.2024
 * @license MIT License
 */

class communicator {
public:
    /**
     * @brief Вычисляет SHA256 хэш для заданной строки.
     * @param input_str Входная строка.
     * @return Шестнадцатеричное представление хэша.
     */
    static std::string sha256(const std::string& input_str);

    /**
     * @brief Генерирует соль как 64-битное число.
     * @return Соль в виде 64-битного числа.
     */
    uint64_t generate_salt();

    /**
     * @brief Преобразует соль в шестнадцатеричный формат.
     * @param salt Соль в виде 64-битного числа.
     * @return Шестнадцатеричное представление соли.
     */
    std::string salt_to_hex(uint64_t salt);

    /**
     * @brief Устанавливает соединение на указанном порту.
     * @param port Порт для соединения.
     * @param base Словарь пользователей.
     * @param l Указатель на логгер.
     * @return Дескриптор сокета.
     */
    int connection(uint32_t port, const std::map<std::string, std::string>& base, logger* l);
};
