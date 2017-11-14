#ifndef _NODECLASS_H
#define _NODECLASS_H

#include <iostream>
#include <list>
#include <string>
using namespace std;

class NodeClass {
  public:
    /*!
     \brief Konstruktor
     \param Initialwerte für den neuen Knoten
    */
    NodeClass(NodeClass *_parent, int32_t _value, int32_t _alpha, int32_t _beta, int _moveFrom, int _playerId, int _depth);

    /*!
     \brief Destruktor
    */
    ~NodeClass();

    /*!
    \brief Fügt der Liste der Nachfolgeknoten ein neuen Knoten hinzu. Übernimmt die Verantwortung für den Knoten (delete).
    \param child Pointer auf den Knoten welcher hinzugefügt werden soll.
   */
    inline void AddChild(NodeClass *child){childern.push_back(child);}

    /*!
     \brief Ausgabe aller Attribute der Klasse in std::out
    */
    void PrintDebug();

    int32_t id;                         // Einmalige Id des Knoten

    NodeClass *parent = nullptr;        // Vorgängerknoten im Baum

    int32_t value;                      // Bewertungswert des Knoten

    int32_t alpha;                      // Alpha Schranke

    int32_t beta;                       // Beta Schranke

    static int32_t countNode;           // Zählvariable für die Anzahl generierter Knoten um eine einmalige Id zuweisen zu können

    int moveFrom;                       // Zug welcher nötig ist um vom Vorgängerknoten zu diesem zu gelangen

    int moveTo;                         // Bester Zug von diesem Knoten aus

    int playerId;                       // SpielerId des Spielers für welcher dieser Konten steht

    int depth;                          // Tiefe des Knotens im Baum wobei kleinere Zahl = tiefer ist und somit 0 ein Blattknoten kennzeichnet

    bool isLast;                        // Zeit an, dass dies ein Blattknoten ist (Wenn Tiefe=0 oder Siegesstellung)

    list<NodeClass*> childern;          // Liste mit Pointern auf alle Nachfolgeknoten im Baum

    list<NodeClass*>::iterator childernIterator;                        // Iterator für den Umgang mit der "childern" List

    /*!
    \brief Gibt den eigenen Knoten und dessen Beziehungen zu den Nachfolgeknoten in "out" aus und ruft rekursive den operator << für alle Nachfolgeknoten aus. Ergibt die Ausgabe des gesamten Baumes im Graphviz Format.
    \param out Stream in welcher die Daten gelegt werden sollen.
    \param Source Knoten für welcher die Daten ausgegeben werden sollen.
   */
    friend ostream& operator <<(ostream &out, NodeClass &Source);
};


#endif
