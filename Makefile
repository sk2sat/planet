TAR	= sim
PLOT	= plot.py
OBJS	= sim.o

TWEET	= ~/python/twitter/tweet.py

PROF2VTK= ~/prof2vtk
FFMPEG	= ffmpeg
PROF2POV= prof2pov
RENDER	= render.py
FMT	= out/out%05d
PROFFMT	= $(FMT).prof
VTKFMT	= $(FMT).vtu
POVFMT	= $(FMT).pov
PNGFMT	= $(FMT).png
FNUM	= 99999
OUT_INTERVAL	= 10
#LUA_FILE= setting.lua

CC	= g++
CFLAGS	= --std=c++11 -g
CFLAGS	= -I/usr/include/lua5.3/
LDFLAGS	= -lm -L/usr/lib/ -llua5.3

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

vtu:
	$(PROF2VTK) $(PROFFMT) $(VTKFMT) $(FNUM)

vtu-tar:
	tar zcvf vtu-data.tar.gz out/*.vtu

run-vtu:
	make run
	$(TWEET) "sim end."
	make vtu
	$(TWEET) "prof->vtu end."
	tar zcvf vtu-data.tar.gz out/*.vtu
	$(TWEET) "tar end."

conv:$(PROF2POV)
	./$< $(PROFFMT) $(FNUM) $(LUA_FILE)

render:
	./$(RENDER) $(POVFMT) 0 $(FNUM) $(OUT_INTERVAL)

gif:
	convert out/*.png anim.gif

mp4:
	$(FFMPEG) -r 30 -i $(PNGFMT) -vcodec libx264 -pix_fmt yuv420p -r 60 out.mp4 > ffmpeg_status

clean:
	rm *.prof
	rm *.o
	rm $(TAR)

$(PROF2POV):prof2pov.o
	g++ -o $@ $^ $(LDFLAGS)


