CC = g++
CCFLAGS = -std=c++17 -Wall 

SRC_DIR = Funciones

BINS = explicit gapCoding huffman

# Obtén la lista de archivos .cpp en SRC_DIR
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) 
all: clean $(BINS)

explicit: $(SOURCES)
	$(CC) $(CCFLAGS) $(SOURCES) explicit.cpp -o $@ 

gapCoding:$(SOURCES)
	$(CC) $(CCFLAGS) $(SOURCES) gapCoding.cpp -o $@ 

huffman:$(SOURCES)
	$(CC) $(CCFLAGS) $(SOURCES) huffman.cpp -o $@ 
clean:
	@echo "[CLN] Removing binary files"
	@rm -f $(BINS)


