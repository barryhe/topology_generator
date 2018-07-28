CC       = g++
CPPFLAGS = -Wall -g -std=c++11
BIN_DIR  = bin

topo_generator: generator.cpp 
	$(CC) $(CPPFLAGS) $^ -o $@

#$(BIN_DIR)/Node.o: Node.cpp $(BIN_DIR)/.dirstamp
#	$(CC) $(CPPFLAGS) -c $< -o $@

#$(BIN_DIR)/Map.o: Map.cpp $(BIN_DIR)/.dirstamp
#	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $@

.PHONY: clean

clean:
	-@rm -rf pa1
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
