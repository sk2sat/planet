TAR	= sim
PLOT	= plot.py
OBJS	= sim.o

CC	= g++
CFLAGS	= --std=c++11 -g
LDFLAGS	= -lm

%.o:%.cpp
	g++ -c $< $(CFLAGS)

sim:$(OBJS)
	$(CC) -o $(TAR) $(OBJS) $(LDFLAGS)

run:
	make
	./$(TAR)

plot:
	./$(PLOT) 3 out%05d.prof 99999

clean:
	rm *.prof
	rm *.o
	rm $(TAR)
