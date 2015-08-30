rm binaries/SoccerTool-w32.exe binaries/SoccerTool-w64.exe

i686-w64-mingw32-gcc source/main.c -o binaries/SoccerTool-w32.exe
x86_64-w64-mingw32-gcc source/main.c -o binaries/SoccerTool-w64.exe
