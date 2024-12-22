//TEST.cpp
/**
 * @file TEST.cpp
 * @brief Файл для тестирования классов.
 * @details Этот файл содержит тесты для классов base, calc, communicator и logger.
 * @author Липатов Егор
 * @date 22.12.2024
 * @license MIT License
 */

#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include "base.h"
#include "calc.h"
#include "communicator.h"
#include "interface.h"
#include "log.h"  // Добавление заголовка для логгера
#include <fstream>
#include <stdexcept>
#include <vector>
#include <limits>
#include <map>

SUITE(BaseTest) {
    TEST(CheckUserCountAfterLoad) {
        base userBase("multiple_users.txt");
        userBase.load();
        CHECK_EQUAL(3, userBase.get_users().size());
    }

    TEST(CheckUserCountAfterLoadEmptyFile) {
        base userBase("empty.txt");
        CHECK_THROW(userBase.load(), std::runtime_error);
    }
}

SUITE(CalcTest) {
    TEST(MultiplyNormalValues) {
        calc calculator({2, 3, 4});
        CHECK_EQUAL(24, calculator.send_res());
    }

    TEST(MultiplyWithZero) {
        calc calculator({2, 0, 4});
        CHECK_EQUAL(0, calculator.send_res());
    }

    TEST(MultiplyOverflow) {
        calc calculator({std::numeric_limits<uint32_t>::max(), 2});
        CHECK_EQUAL(std::numeric_limits<uint32_t>::max(), calculator.send_res());
    }

    TEST(SHA256NormalInput) {
        calc calculator({});
        CHECK_EQUAL("9F86D081884C7D659A2FEAA0C55AD015A3BF4F1B2B0B822CD15D6C15B0F00A08", calculator.calculate_sha256("test"));
    }

    TEST(SHA256EmptyInput) {
        calc calculator({});
        CHECK_EQUAL("E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855", calculator.calculate_sha256(""));
    }

    TEST(SHA256LongInput) {
        std::string longInput(1000, 'a'); // 1000 'a'
        calc calculator({});
        std::string expectedHash = "41EDECE42D63E8D9BF515A9BA6932E1C20CBC9F5A5D134645ADB5DB1B9737EA3"; // Предполагаемый хэш
        CHECK_EQUAL(expectedHash, calculator.calculate_sha256(longInput));
    }

    TEST(SHA256SpecialCharacters) {
        calc calculator({});
        CHECK_EQUAL("95CE789C5C9D18490972709838CA3A9719094BCA3AC16332CFEC0652B0236141", calculator.calculate_sha256("!@#$%^&*()"));
    }
}

SUITE(CommunicatorTest) {
    TEST(Sha256Hash) {
        std::string input = "test"; 
        std::string expectedHash = "9F86D081884C7D659A2FEAA0C55AD015A3BF4F1B2B0B822CD15D6C15B0F00A08"; 
        CHECK_EQUAL(expectedHash, communicator::sha256(input));
    }

    TEST(GenerateSalt) {
        communicator comm;
        uint64_t salt = comm.generate_salt();
        CHECK(salt >= 0);
    }

    TEST(UniqueSaltGeneration) {
        communicator comm1, comm2;
        uint64_t salt1 = comm1.generate_salt();
        uint64_t salt2 = comm2.generate_salt();
        CHECK(salt1 != salt2);
    }

    TEST(Sha256HashEmptyString) {
        std::string input = "";
        std::string expectedHash = "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855";
        CHECK_EQUAL(expectedHash, communicator::sha256(input));
    }

    TEST(GenerateSaltReturns64BitValue) {
        communicator comm;
        uint64_t salt = comm.generate_salt();
        CHECK(salt <= 0xFFFFFFFFFFFFFFFF); // Проверяем, что соль в пределах 64 бит
    }

    TEST(SaltToHexConversion) {
        communicator comm;
        uint64_t salt = 1234567890123456789;
        CHECK_EQUAL("112210f47de98115", comm.salt_to_hex(salt));
    }

    TEST(SaltToHexConversionZero) {
        communicator comm;
        CHECK_EQUAL("0000000000000000", comm.salt_to_hex(0));
    }

    TEST(SaltToHexConversionMaxValue) {
        communicator comm;
        CHECK_EQUAL("ffffffffffffffff", comm.salt_to_hex(0xFFFFFFFFFFFFFFFF));
    }
}

// Новый набор тестов для logger
SUITE(LoggerTest) {
    TEST(LoggerDefaultPath) {
        logger log;
        CHECK_EQUAL("log.txt", log.get_path());
    }

    TEST(LoggerWriteLogDefault) {
        logger log;
        log.writelog("Test log message");
        std::ifstream logFile("log.txt");
        std::string line;
        std::getline(logFile, line);
        CHECK(line.find("Test log message") != std::string::npos);
    }

    TEST(LoggerWriteLogCustomPath) {
        logger log("test_log.txt");
        log.writelog("Custom log message");
        std::ifstream logFile("test_log.txt");
        std::string line;
        std::getline(logFile, line);
        CHECK(line.find("Custom log message") != std::string::npos);
    }

    TEST(LoggerOpenLogFileError) {
        logger log("/invalid/path/to/log.txt");
        CHECK_THROW(log.writelog("Log message"), std::runtime_error); // Проверяем, что выбрасывается исключение
    }

    TEST(LoggerMultipleWrites) {
        logger log("multiple_logs.txt");
        log.writelog("First message");
        log.writelog("Second message");
        std::ifstream logFile("multiple_logs.txt");
        std::string line1, line2;
        std::getline(logFile, line1);
        std::getline(logFile, line2);
        CHECK(line1.find("First message") != std::string::npos);
        CHECK(line2.find("Second message") != std::string::npos);
    }

    TEST(LoggerInvalidPathFormat) {
        logger log;
        CHECK_THROW(log.set_path("invalid_path_without_extension"), std::runtime_error); // Проверяем, что выбрасывается исключение
    }

    TEST(LoggerLogFileExists) {
        logger log("existing_log.txt");
        log.writelog("Check existence");
        std::ifstream logFile("existing_log.txt");
        CHECK(logFile.good());
    }

    TEST(LoggerLogFileNotWritable) {
        logger log("/root/readonly_log.txt"); // Путь к файлу, который не может быть записан
        CHECK_THROW(log.writelog("Test message"), std::runtime_error); // Проверяем, что выбрасывается исключение
    }
}
// Новый набор тестов для interface
SUITE(InterfaceTest) {
    TEST(ParserDefaultValues) {
        const char* argv[] = {"program_name"};
        interface iface;
        iface.parser(1, argv);
        CHECK_EQUAL("base.txt", iface.get_base());
        CHECK_EQUAL("log.txt", iface.get_log());
        CHECK_EQUAL(33333, iface.get_port());
    }

    TEST(ParserCustomValues) {
        const char* argv[] = {"program_name", "-b", "custom_base.txt", "-l", "custom_log.txt", "-p", "44444"};
        interface iface;
        iface.parser(7, argv);
        CHECK_EQUAL("custom_base.txt", iface.get_base());
        CHECK_EQUAL("custom_log.txt", iface.get_log());
        CHECK_EQUAL(44444, iface.get_port());
    }

    TEST(ParserHelpOption) {
        std::ostringstream output;
        std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

        const char* argv[] = {"program_name", "-h"};
        interface iface;
        CHECK(!iface.parser(2, argv));

        std::cout.rdbuf(originalCoutBuffer); // Восстанавливаем оригинальный буфер
        CHECK(output.str().find("Usage: vcalc [options]") != std::string::npos);
    }


    TEST(SetupConnectionFailure) {
        const char* argv[] = {"program_name", "-b", "invalid_base.txt"};
        interface iface;
        iface.parser(3, argv);

        // Проверяем, что выбрасывается исключение при попытке загрузить недопустимую базу данных
        CHECK_THROW(iface.setup_connection(), std::runtime_error);
    }

}


int main(int argc, char** argv) {
    return UnitTest::RunAllTests();
}
