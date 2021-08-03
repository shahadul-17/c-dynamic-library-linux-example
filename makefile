build:
	mkdir -p bin
	gcc -shared -o bin/Mapping.so -fPIC Mapping.c common/StringUtilities.c
	gcc -shared -o bin/Reading.so -fPIC Reading.c common/StringUtilities.c
	gcc main.c common/StringUtilities.c -ldl -o bin/main

clean:
	rm -rf bin

rebuild: clean build

run-reading:
	bin/main reading $(filePath)

run-mapping:
	bin/main mapping $(filePath)

build-and-run-reading: build run-reading

build-and-run-mapping: build run-mapping
