TAR	= sim
PLOT	= plot.py
OBJS	= sim.o

FFMPEG	= ffmpeg
PROF2POV= prof2pov
RENDER	= render.py
FMT	= out/out%05d
PROFFMT	= $(FMT).prof
POVFMT	= $(FMT).pov
PNGFMT	= $(FMT).png
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
	./$(PLOT) show 2 $(PROFFMT) $(FNUM)

plot3:
	./$(PLOT) show 3 $(PROFFMT) $(FNUM)

plotgif2:
	./$(PLOT) save 2 $(PROFFMT) $(FNUM)

plotgif3:
	./$(PLOT) save 3 $(PROFFMT) $(FNUM)

conv:$(PROF2POV)
	./$< $(PROFFMT) $(FNUM) +D

render:
	./$(RENDER) $(POVFMT) 0 $(FNUM)

mp4:
	$(FFMPEG) -r 30 -i $(PNGFMT) -vcodec libx264 -pix_fmt yuv420p -r 60 out.mp4

clean:
	rm *.prof
	rm *.o
	rm $(TAR)

$(PROF2POV):prof2pov.o
	g++ -o $@ $^


