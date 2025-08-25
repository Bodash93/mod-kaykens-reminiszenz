# Kaykens Reminiszenz Modul

Dieses Modul ergänzt einen benutzerdefinierten Raid- bzw. Instanzbereich "Kaykens Reminiszenz" mit mehreren Bossen, NPC-Skripten und Ereignissen für AzerothCore.

## Inhalte
- **src/** – C++-Skripte für Bosse wie Gorleax oder Polydeuces, das Instanz-Skript und diverse NPCs.
- **data/sql/** – SQL-Dateien zur Ergänzung der World-Datenbank (neue Kreaturen, Bewegungen, Flags und Texte).
- **conf/** – Beispieldatei `my_custom.conf.dist` zur Modulkonfiguration.
- **include.sh** – Shell-Skript zur Einbindung des Moduls in den Build-Prozess.

## Installation
1. Repository in den Ordner `modules/` der Core-Installation klonen.
2. Modul über `include.sh` in den Build integrieren (z. B. per `source include.sh` vor dem CMake-Lauf).
3. SQL-Skripte aus `data/sql/db-world` in die World-Datenbank importieren.
4. Optional: Ältere Skripte aus `data/sql/old_sql` nach Bedarf prüfen.
5. `conf/my_custom.conf.dist` nach `my_custom.conf` kopieren und nach Wunsch anpassen.

Nach dem Kompilieren und Starten steht die Instanz zur Verfügung.
