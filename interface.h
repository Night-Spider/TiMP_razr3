/**
 * @brief Класс для обработки пользовательского интерфейса.
 * @details Этот класс предоставляет методы для парсинга аргументов командной строки и настройки соединения.
 */
 
/**
 * @file interface.h
 * @brief Заголовочный файл для класса interface, который обрабатывает пользовательский интерфейс.
 * @details Этот файл содержит методы для парсинга аргументов командной строки и настройки соединения.
 * @author Липатов Егор
 * @date 22.12.2024
 * @license MIT License
 */

class interface {
public:
    /**
     * @brief Парсит аргументы командной строки.
     * @param argc Количество аргументов.
     * @param argv Массив аргументов.
     * @return true, если парсинг успешен, иначе false.
     */
    bool parser(int argc, const char** argv);

    /**
     * @brief Получает имя файла базы.
     * @return Имя файла базы.
     */
    std::string get_base() const;

    /**
     * @brief Получает имя файла лога.
     * @return Имя файла лога.
     */
    std::string get_log() const;

    /**
     * @brief Получает номер порта.
     * @return Номер порта.
     */
    uint32_t get_port() const;

    /**
     * @brief Настраивает соединение с базой.
     * @throws std::runtime_error Если возникает ошибка при загрузке базы.
     */
    void setup_connection();

private:
    std::string basefile_; ///< Имя файла базы.
    std::string logfile_; ///< Имя файла лога.
    uint32_t port_; ///< Номер порта.
};
