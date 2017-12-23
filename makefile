CC = g++
CCFLAGS = -c
SRCS = src
OBJS = obj
BINS = bin

solv-simult: main.o simultaneous-equation.o
	$(CC) $(OBJS)/main.o $(OBJS)/simultaneous-equation.o -o $(BINS)/solv-simult

main.o: $(SRCS)/main.cpp
	$(CC) $(SRCS)/main.cpp -o $(OBJS)/main.o $(CCFLAGS)

simultaneous-equation.o: $(SRCS)/simultaneous-equation.cpp
	$(CC) $(SRCS)/simultaneous-equation.cpp -o $(OBJS)/simultaneous-equation.o $(CCFLAGS)

.PHONY: clean

clean: 
	rm -f $(OBJS)/*.o $(BINS)/solv-simult

$(shell mkdir -p $(BINS)/)
$(shell mkdir -p $(OBJS)/)