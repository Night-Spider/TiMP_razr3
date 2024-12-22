/**
 * @brief Класс для ведения логирования.
 * @details Этот класс предоставляет методы для записи сообщений в лог-файл.
 */
 
/**
 * @file log.h
 * @brief Заголовочный файл для класса logger, который ведет логирование.
 * @details Этот файл содержит методы для записи сообщений в лог-файл.
 * @author Липатов Егор
 * @date 22.12.2024
 * @license MIT License
 */

class logger {
public:
    /**
     * @brief Конструктор класса logger.
     * @param path Путь к файлу лога.
     */
    logger(const std::string& path);

    /**
     * @brief Записывает сообщение в лог.
     * @param message Сообщение для записи.
     * @throws crit_err Если путь к файлу лога не задан или файл не может быть открыт.
     */
    int writelog(const std::string& message);

    /**
     * @brief Получает путь к файлу лога.
     * @return Путь к файлу лога.
     */
    std::string get_path() const;

private:
    std::string gettime(); ///< Получает текущее время в строковом формате.
    std::string path_to_logfile; ///< Путь к файлу лога.
};
