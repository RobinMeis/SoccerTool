##Spielplan
Die Datei plan_eingabe.c erstellt eine Datenbankdatei für SoccerTool. Sie enthält Teams, Gruppen, Spielzeit und Spielplan. SoccerTool ergänzt zusätzlich die Ergebnisse. Es sind precompiled binaries unter https://github.com/HcDevel/SoccerTool/releases verfügbar.

Kompillieren (mit gcc unter Linux):
Für 32 Bit: ``gcc -m32 plan_eingabe.c -o plan_eingabe_l32``.
Für 64 Bit: ``gcc -m64 plan_eingabe.c -o plan_eingabe_l64``.

Mit dem Debian Paketen ``gcc-mingw-w64 gcc-mingw-w64-i686`` kann die Windows Version direkt unter Linux kompilliert werden.

Für 32 Bit: ``i686-w64-mingw32-gcc plan_eingabe.c -o plan_eingabe-w32.exe``
Für 64 Bit: ``x86_64-w64-mingw32-gcc plan_eingabe.c -o plan_eingabe-w64.exe``

Es werden keine zusätzlichen Bibliotheken benötigt.
