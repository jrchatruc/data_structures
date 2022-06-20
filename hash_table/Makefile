.PHONY: clean

TARGET=ht
TARGET_RELEASE=release

CC=cc
CC_FLAGS=-std=c17 -Wall -Wextra -pedantic

BUILD_DIR=./build
SRC_DIR=./src

SOURCE = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE))

# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJECTS:%.o=%.d)

default: $(TARGET)

$(TARGET): $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CC_FLAGS) $^ -o $@

-include $(DEP)

# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
# The -MMD flags additionaly creates a .d file with
# the same name as the .o file.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -MMD -c $< -o $@

clean:
	-rm -rf $(BUILD_DIR)

run: $(TARGET)
	$(BUILD_DIR)/$(TARGET)
