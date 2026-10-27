# Wrapper for cmake build system

OBJ_DIR = obj
BIN_DIR = bin
BUILD_DIR = build

# Compile le tout
compile: $(BUILD_DIR) $(OBJ_DIR) $(BIN_DIR)
	cmake --build $(BUILD_DIR)
	
# Utiliser quand le make à fail au moment de la génération du build
# Doit être relancer obligatoirement
configure:
	cmake -B $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR): configure

# Nettoye le tout
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(BUILD_DIR)
