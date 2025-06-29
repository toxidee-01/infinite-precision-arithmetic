all :
	g++ main.cpp -o my_inf_arith

libmy_inf_arith:
	g++ calc.cpp -o my_inf_arith.o
	ar rcs libmy_inf_arith.a my_inf_arith.o
	rm my_inf_arith.o
clean:
	rm -f my_inf_arith libmy_inf_arith.a *.o
