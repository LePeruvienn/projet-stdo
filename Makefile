BINARY_NAME = projet-stdo

DEBUG = 1

# Dossiers
BUILD_DIR = build
BIN_DIR = bin
SOURCE_DIR = src
HEADER_DIR = header
OBJ_DIR = obj
# LIBS_DIR = libs

# Options de compilation
CC = gcc
C_FLAGS = -Wall -Wextra -Werror -std=c11
# LINK_FLAGS = -lglfw -lGL -lm -ldl
INCLUDES = -I$(HEADER_DIR)


# Ajouter -g quand on est en mode debug
ifeq ($(DEBUG),1)
	C_FLAGS += -g
endif

# Fichiers source
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.c=.o)))

LSP_SOURCES = $(wildcard $(SOURCE_DIR)/LSP/*.c)
LSP_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(LSP_SOURCES:.c=.o)))

# Libaries
LSP_STATIC_LIB = $(OBJ_DIR)/lsp.a

# Binaires
BINARY = $(BIN_DIR)/$(BINARY_NAME)

### Règles de compilation
all: $(OBJ_DIR) $(BIN_DIR) $(BINARY)

$(BINARY): $(OBJS) $(LSP_STATIC_LIB)
	$(CC) $(OBJS) $(LSP_STATIC_LIB) -o $@ $(LINK_FLAGS)

$(LSP_STATIC_LIB): $(LSP_OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/LSP/%.c
	$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@

### Règles pour la création des dossiers nécessaire
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	cmake -B $(BUILD_DIR)

### Wrapper pour CMake
# cmake: $(BUILD_DIR) $(BIN_DIR)
	# cmake --build $(BUILD_DIR)

### Fonction de nettoyage
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(OBJ_DIR)

