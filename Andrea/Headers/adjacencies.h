#ifndef ADJACENCIES_H
#define ADJACENCIES_H

#include <Andrea/Headers/node.h>

class Adjacencies{

private:

    // Un triangolo è un nodo
    std::vector<Node*> nodes;

public:
    Adjacencies();

    void addNodes(Node* n1, Node* n2, Node* n3);
    void setAdjacenciesA(Node* father, Node* adj);
    void setAdjacenciesB(Node* father, Node* adj);
    void setAdjacenciesC(Node* father, Node* adj);

    bool isAdjacencies(Node* n1, Node* n2);
};

#endif // ADJACENCIES_H
