all: compile link

compile:
	g++ -Isrc/include -c coding/*.cpp

link:
	g++ *.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lsfml-audio

web-compile:
	emcc -Isrc/include -c coding/*.cpp -s ASYNCIFY

web-link:
	emcc *.o -o game.html -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -s ASYNCIFY --preload-file Image --preload-file sound --preload-file fonts

web: web-compile web-link