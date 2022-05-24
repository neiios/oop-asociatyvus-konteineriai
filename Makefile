all:
	mkdir -pv build
	cmake -S . -B build -G Ninja
	cmake --build build --target all
run: all
	./build/src/egzaminas
clean:
	rm -rf build
