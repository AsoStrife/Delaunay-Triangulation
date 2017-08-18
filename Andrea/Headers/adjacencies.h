#ifndef ADJACENCIES_H
#define ADJACENCIES_H

#include <Andrea/Headers/node.h>

class Adjacencies{

private:

public:
    Adjacencies();

    static void addNodes(Node* n1, Node* n2, Node* n3);
    static void setAdjacenciesA(Node* father, Node* adj);
    static void setAdjacenciesB(Node* father, Node* adj);
    static void setAdjacenciesC(Node* father, Node* adj);

    bool isAdjacencies(Node* n1, Node* n2);
};

#endif // ADJACENCIES_H
