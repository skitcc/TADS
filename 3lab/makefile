# Компилятор и флаги
CC = gcc
CFLAGS = -std=c99 -Werror -Wall -Wextra -Wpedantic -Wvla
OUTPUT = app.exe

# Папки с исходниками, заголовочными файлами и объектными файлами
SRC_DIR = ./src
INC_DIR = ./inc
OUT_DIR = ./out

# Поиск всех .c файлов в папке ./src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Преобразуем пути исходников в пути объектных файлов (в папке ./out)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRCS))

# Основное правило сборки
$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJS) -o $(OUTPUT)

# Правило компиляции .c файлов в .o
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Создание папки для объектных файлов (если её нет)
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Правило очистки (удаление .o файлов и исполняемого файла)
clean:
	rm -rf $(OUT_DIR) $(OUTPUT)

# Правило "all" для сборки по умолчанию
all: $(OUTPUT)

# Псевдонимы для удобства
.PHONY: clean all
