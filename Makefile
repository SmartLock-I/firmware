all: test
	cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -S . -B build
	cmake --build build
	-mv build/compile_commands.json .

test:
	cmake -GNinja -DCMAKE_C_COMPILER=/usr/local/bin/gcc -DCMAKE_CXX_COMPILER=/usr/local/bin/g++ -S ./Tests -B build_test
	cmake --build build_test
	./build_test/sli_firmware_test
	-cd build_test && mv compile_commands.json ../Tests

test_monitor:
	clear
	while sleep 3; do make test > /dev/null 2>&1; tput cup 0 0; clear; ./build_test/sli_firmware_test; done

clean:
	rm -rf build build_test

.PHONY: all test clean
