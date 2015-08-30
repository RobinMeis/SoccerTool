rm binaries/SoccerTool_l32 binaries/SoccerTool_l64

gcc -m32 source/main.c -o binaries/SoccerTool_l32
gcc -m64 source/main.c -o binaries/SoccerTool_l64
