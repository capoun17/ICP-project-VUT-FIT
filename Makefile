build:
	mkdir -p build
	cd build && qmake ../src && make -j 16
	cp build/ICP-final .

run: build
	./ICP-final

doxygen:
	doxygen Doxyfile

clean:
	rm -rf build
	rm -f ICP-final
	rm -rf doc