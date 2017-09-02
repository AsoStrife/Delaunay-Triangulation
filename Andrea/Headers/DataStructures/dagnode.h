#ifndef DAGNODE_H
#define DAGNODE_H

#include <viewer/objects/objects.h>
#include <Andrea/Headers/DataStructures/triangle.h>

class Triangle;

class DagNode{

private:
    Triangle* tr = nullptr;
    DagNode* childA = nullptr;
    DagNode* childB = nullptr;
    DagNode* childC = nullptr;

public:
    DagNode();
    DagNode(Triangle* tr);

    // Getter & Setter
    DagNode* getChildA();
    DagNode* getChildB();
    DagNode* getChildC();
    Triangle* getTriangle();

    void setChildA(DagNode* dn);
    void setChildB(DagNode* dn);
    void setChildC(DagNode* dn);
    void setTriangle(Triangle* tr);
};

#endif // DAGNODE_H
