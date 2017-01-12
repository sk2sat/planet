TAR	= sim
PLOT	= plot.py
OBJS	= sim.o

PROF2POV= prof2pov
FFORMAT	= out/out%05d.prof
FNUM	= 99999

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
	./$(PLOT) show 2 $(FFORMAT) $(FNUM)

plot3:
	./$(PLOT) show 3 $(FFORMAT) $(FNUM)

plotgif2:
	./$(PLOT) save 2 $(FFORMAT) $(FNUM)

plotgif3:
	./$(PLOT) save 3 $(FFORMAT) $(FNUM)

conv:$(PROF2POV)
	./$< $(FFORMAT) $(FNUM)

clean:
	rm *.prof
	rm *.o
	rm $(TAR)

$(PROF2POV):prof2pov.o
	g++ -o $@ $^


