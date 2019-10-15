CC=g++ -std=c++14

run: run.o calculator.o 
	$(CC) -o run_calculator run.o calculator.o
	./run_calculator

test: test_bin
	./test_calculator
	make clean

test_bin: test_calculator.o calculator.o
	$(CC) -o test_calculator test_calculator.o calculator.o

run.o: run.cpp calculator.h
	$(CC) -c run.cpp

calculator.o: calculator.cpp calculator.h
	$(CC) -c calculator.cpp

test_calculator.o: test_calculator.cpp calculator.h catch2/catch.hpp
	$(CC) -c test_calculator.cpp

clean:
	rm -rf *.o test_calculator run_calculator
