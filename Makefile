CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./ -I/usr/include/crypto++
LDFLAGS = -lcryptopp -lpthread -lUnitTest++

# Основные файлы
SRC = main.cpp base.cpp calc.cpp communicator.cpp interface.cpp log.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = server

# Файлы тестов
TEST_SRC = TEST.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_TARGET = test_runner

# Основная цель
all: $(TARGET) $(TEST_TARGET)

# Сборка основного приложения
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Сборка тестов (не добавляем main.o)
$(TEST_TARGET): $(TEST_OBJ) base.o calc.o communicator.o interface.o log.o
	$(CXX) $(TEST_OBJ) base.o calc.o communicator.o interface.o log.o -o $(TEST_TARGET) $(LDFLAGS)

# Правило для компиляции .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJ) $(TARGET) $(TEST_OBJ) $(TEST_TARGET)

.PHONY: all clean
