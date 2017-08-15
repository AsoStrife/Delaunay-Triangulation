#ifndef NODE_H
#define NODE_H
#include <Andrea/Headers/triangle.h>

class Node : public Triangle
{
public:
    Node();
    Node(Point2Dd* p1, Point2Dd* p2, Point2Dd*  p3);

    void setChildA(Node* t);
    void setChildB(Node* t);
    void setChildC(Node* t);
    void setChildren(Node* A, Node* B, Node* C);

    Node* getChildA();
    Node* getChildB();
    Node* getChildC();

private:
    Node* childA = nullptr;
    Node* childB = nullptr;
    Node* childC = nullptr;
};

#endif // NODE_H
