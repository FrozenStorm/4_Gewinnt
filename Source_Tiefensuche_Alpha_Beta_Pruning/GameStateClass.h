#ifndef _GAMESTATECLASS_H
#define _GAMESTATECLASS_H


#include <vector>
#include <string>
using namespace std;

class FieldClass;

//#define DEBUG                     // Schaltet alle Debug-Ausgaben im Code frei

#define USE_ALPHA_BETA              // Wählt die GenerateSubtree() Methode welche die Tiefensuche mit Alpha Beta Pruning umsetzt
//#define USE_DEEPSEARCH            // Wählt die GenerateSubtree() Methode welche nur die Tiefensuche einsetzt


#define WINNIG_VALUE 1000000000     // Grosser Wert (grösser als jeder andere Bewertungswert welcher durch das Rating entstehen kann) welcher eine gewonnene Spielstellung als Bewertung erhält

class GameStateClass {

public:
    int timebank = 0;               // Die Zeit welche maximal für den nächsten Zug zur Verfügung steht

    int timePerMove = 0;            // Die Zeit welche pro Zug neu auf das Zeitkonto "timebank" kommt

    int playerCount = 0;            // Anzahl Spieler im Spiel

    vector<string> playerNames;     // Namen aller Spieler

    string yourBotName = "";        // Namen des eigenen Spielers

    int yourBotId = 0;              // Id des eigenen Spielers im Field

    int fieldColumns = 0;           // Anzahl der Spalten

    int fieldRows = 0;              // Anzahl der Zeilen

    int round = 0;                  // Aktuelle Spielrunde

    FieldClass *field = nullptr;    // Spielfeld

    /*!
     \brief Destruktor
    */
    ~GameStateClass();

    /*!
     \brief Setter-Funktion für Spielzustands-Attribute der Klasse. Umwandeln der String-Werte, die vom Parser kommen.
     \param key Schlüssel der Settings „timebank“ „time_per_move“ „player_names“ „your_bot“ „your_botid“ „field_columns“ „field_rows“
     \param Neuer Wert
    */
    void UpdateSettings(string key, string value);

    /*!
     \brief Setter-Funktion für Spielzustands-Attribute der Klasse. Umwandeln der String-Werte, die vom Parser kommen.
     \param key Schlüssel der Settings „round“ „field“
     \param Neuer Wert
    */
    void UpdateGame(string key, string value);

    /*!
     \brief Setter-Funktion für Spielzustands-Attribute der Klasse. Umwandeln der String-Werte, die vom Parser kommen.
     \param key Schlüssel der Settings „move“
     \param Neuer Wert für timebank
    */
    void UpdateMove(string key, string value);

    /*!
     \brief Ausgabe aller Attribute der Klasse in std::out
    */
    void PrintDebug();
};
#endif
