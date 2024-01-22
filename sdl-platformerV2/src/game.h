/**
 * @file game.h
 * @brief Deklarationen und Schnittstellen für das Gameplay des SDL Plattformspiels.
 *
 * Diese Datei definiert die Schnittstellen und globalen Variablen, die für die Initialisierung,
 * Ausführung und Steuerung des Spielablaufs verwendet werden. Sie enthält Funktionen zur
 * Spielinitialisierung und -ausführung, Level-Management und Spielerinteraktionen.
 */

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL_types.h>

/**
 * @var Level* level
 * @brief Globale Variable, die auf das aktuelle Level im Spiel zeigt.
 */
extern Level* level;

/**
 * @var Player player
 * @brief Globale Variable, die den Spielercharakter repräsentiert.
 */
extern Player player;

/**
 * @brief Initialisiert das Spiel und setzt es in den Ausgangszustand.
 */
void initGame();

/**
 * @brief Startet und führt die Hauptspielschleife aus.
 */
void runGame();

/**
 * @brief Setzt das aktuelle Level basierend auf Zeilen- und Spaltenindizes.
 *
 * @param r Zeilenindex für das Level.
 * @param c Spaltenindex für das Level.
 */
void setLevel( int r, int c );

/**
 * @brief Markiert das aktuelle Level als abgeschlossen und ändert den Spielstatus.
 */
void completeLevel();

/**
 * @brief Fügt dem Spieler Schaden zu und aktualisiert den Gesundheitszustand.
 *
 * @param damage Menge des Schadens, der dem Spieler zugefügt wird.
 */
void damagePlayer( int damage );

/**
 * @brief Tötet den Spielercharakter und aktualisiert den Spielstatus.
 */
void killPlayer();

#endif // GAME_H
