#ifndef BRANCH_H
#define BRANCH_H


class Branch
{
public:
    Branch();
    Branch( int f, int c1, int c2, int c3);
    bool hasChild();

    // Getter
    int getChild(int child);
    int getFather();

    // Setter
    void setChild(int child, int v);
    void setFather(int f);

private:
    int father;
    int child1;
    int child2;
    int child3;
};

#endif // BRANCH_H
