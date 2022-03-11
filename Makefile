.PHONY: clean run

all: bin/launcher_editor

bin/launcher_editor: build/launcher_editor.o | bin
	@echo "-- Building the binary file... --"
	g++ -o bin/launcher_editor build/launcher_editor.o
	@echo ""

bin:
	mkdir bin

build/launcher_editor.o: src/launcher_editor.cpp | build
	@echo "-- Building the object files... --"
	g++ -c -o build/launcher_editor.o src/launcher_editor.cpp
	@echo ""

build:
	mkdir build

clean:
	rm -rf build
	rm -rf bin

run: bin/launcher_editor
	./bin/launcher_editor