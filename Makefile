all: test
	cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -S . -B build
	cmake --build build
	-mv build/compile_commands.json .

test:
	cmake -GNinja -DCMAKE_C_COMPILER=/usr/local/bin/gcc -DCMAKE_CXX_COMPILER=/usr/local/bin/g++ -S ./Tests -B build_test
	cmake --build build_test
	cd build_test && ctest
	-cd build_test && mv compile_commands.json ../Tests

clean:
	rm -rf build build_test

.PHONY: all test clean
