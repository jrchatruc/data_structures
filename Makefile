.PHONY: clean fmt check_fmt

TARGET=data_structures

CC=cc
CFLAGS=-std=c17 -Wall -Wextra -Wimplicit-fallthrough -Werror -pedantic -g -O0
SANITIZER_FLAGS=-fsanitize=address -fno-omit-frame-pointer
LN_FLAGS=

BUILD_DIR=./build
SRC_DIR=./src

SOURCE = $(wildcard $(SRC_DIR)/*.c)

HEADERS = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE))

# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJECTS:%.o=%.d)

default: $(TARGET)

$(TARGET): $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(SANITIZER_FLAGS) $^ -o $@ $(LN_FLAGS)

-include $(DEP)

# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
# The -MMD flags additionaly creates a .d file with
# the same name as the .o file.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(SANITIZER_FLAGS) -MMD -c $< -o $@

clean:
	-rm -rf $(BUILD_DIR)

run: $(TARGET)
	$(BUILD_DIR)/$(TARGET)

fmt:
	clang-format --style=file -i $(SOURCE) $(HEADERS)

check_fmt:
	clang-format --style=file -Werror -n $(SOURCE) $(HEADERS)
