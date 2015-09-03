rm binaries/SoccerTool_l32 binaries/SoccerTool_l64

#gcc -m32 source/main.c -o binaries/SoccerTool_l32 `pkg-config --libs gtk+-3.0`
gcc `pkg-config gtk+-2.0 --cflags --libs gtk+-2.0` -m64 source/main.c -o binaries/SoccerTool_64
