# Motorsteuerung

## Funktionsweise
Siehe Dokumentation.

## Installation
1. Arduino installieren
2. Dateien aus der Zip Datei extrahieren.
3. `Motorsteuerung.ino` mit Arduino öffnen.
4. `Tools/Board/Arduino Mega or Mega 2560` auswählen.
5. Arduino anstecken und richtigen Port unter `Tools/Port` auswählen.
6. Aus `Upload` drücken.

## Git
Das Projekt wurde mithilfe von Git erstellt. Damit kann man im Projekt beim Fehler mehrere Schritte zurücksetzen oder mehrere Versionen verwalten.

### Status
Zeige alle modifizierten Dateien.
```
git status
```

### Geschichte
Zeige den Ablauf des Projekts (von Neu bis Alt).
```
git log
```

### Hinzufügen
Füge eine Änderung ein.
```
git commit -am "<Nachricht>"
```

### Neue Version
Erstelle eine neue Version. Alle änderungen berühren das alte nicht.
```
git checkout -b <Name>
```

### Welchsle Version
Welchse auf eine älteres oder neueres Version. Alle nicht hinzugefügten Änderungen folgen mit.
```
git branch <name>
```

Es gibt noch weitere nützliche Befehle wie `merge` und `diff`, jedoch sind sie nicht essentiell.

## Simulation
Für das Projekt wurde eine Simulation erstellt um es zu ermöglichen von Zuhause aus weiter zu schaffen. Das Simulationsprogramm heißt [SimulIDE](https://www.simulide.com/p/downloads.html).

### Installation (Linux)
Weil `apt` oder `dpkg` nicht zugelassen sind wird die Simulation mit appimage installiert. Der Name des Programms könnte sich ändern. In dem fall ändere die Namen bei den Schritten.

1. Installiere das Programm
```
wget https://mailfence.com/pub/docs/santigoro/web/SimulIDE_0.4.14/simulide_0.4.14-SR4.AppImage && chmod +x simulide_0.4.14-SR4.AppImage
```
2. Öffne das Programm
```
./simulide_0.4.14-SR4.AppImage
```
