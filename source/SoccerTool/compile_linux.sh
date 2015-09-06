rm SoccerTool_64

#gcc -m32 source/main.c -o binaries/SoccerTool_l32 `pkg-config --libs gtk+-3.0`
gcc `pkg-config gtk+-2.0 --cflags --libs gtk+-2.0` -lportaudio -lsndfile -pthread -m64 main.c -o SoccerTool_64
