CFLAGS = -O3 -Wall `pkg-config --cflags glfw3`

cosine_wave: 2dplot.cpp
	$(CC) $(CFLAGS) -o main 2dplot.cpp -lm `pkg-config --static --libs glfw3`

clean:
	rm -f *~ *.o *.obj cosine_wave
