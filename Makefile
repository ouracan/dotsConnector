CFLAGS = -O3 -Wall `pkg-config --cflags glfw3 gl`

cosine_wave: 2dplot.cpp
	$(CC) $(CFLAGS) -o main 2dplot.cpp -lm `pkg-config --static --libs glfw3 gl`

clean:
	rm -f *~ *.o *.obj cosine_wave
