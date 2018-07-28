CC       = g++
CPPFLAGS = -Wall -g -std=c++11
BIN_DIR  = bin

topo_generator: generator.cpp Manager.o Domain.o Node.o
	$(CC) $(CPPFLAGS) $^ -o $@

$(BIN_DIR)/Manager.o: Manager.cpp Domain.o $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/Domain.o: Domain.cpp Node.o $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/Node.o: Node.cpp $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $@

.PHONY: clean

clean:
	-@rm -rf topo_generator
	-@rm -rf $(BIN_DIR)
	-@rm -rf *.o
	-@echo "--- All Clean!---"
