#include "Andrea/Headers/adjacencies.h"

Adjacencies::Adjacencies() {}

Adjacencies::Adjacencies(Triangle* t) {
    this->t = t;
}


void Adjacencies::setAdjacencies(Triangle* adj1, Triangle* adj2, Triangle* adj3, Adjacencies* father){


    //std::cout << "Il triangolo: (" << adj1->getA()->x() << ", " << adj1->getA()->y() << ") - (" << adj1->getB()->x() << ", " << adj1->getB()->y() << ") - (" << adj1->getC()->x() << ", " << adj1->getC()->y() << ")" << std::endl;

    Adjacencies* a = adj1->getAdjNode();

    // Setto al triangolo adj1 che adj2 è adiacente
    if(isAdjacencies(adj1, adj2) == true){
        Adjacencies::setAdjacency(adj2, a);
        //std::cout << "E' adiacente con: (" << adj2->getA()->x() << ", " << adj2->getA()->y() << ") - (" << adj2->getB()->x() << ", " << adj2->getB()->y() << ") - (" << adj2->getC()->x() << ", " << adj2->getC()->y() << ")" << std::endl;

    }

    // Setto al triangolo adj1 che adj3 è adiacente
    if(isAdjacencies(adj1, adj3) == true){
        Adjacencies::setAdjacency(adj3, a);
        //std::cout << "E' adiacente con: (" << adj3->getA()->x() << ", " << adj3->getA()->y() << ") - (" << adj3->getB()->x() << ", " << adj3->getB()->y() << ") - (" << adj3->getC()->x() << ", " << adj3->getC()->y() << ")" << std::endl;

    }

    // Per la terza adiacenza controllo il triangolo padre, ovvero quello in cui sono nati i 3 sotto triangoli
    if(father == nullptr)
        exit(0);

    std::vector<Point2Dd> adjacentPoints;

    if(father->getAdjA() != nullptr){
        adjacentPoints = isAdjacenciesFather(adj1, father->getAdjA() );

           if(adjacentPoints.size() > 0){
               //std::cout << "PUNTI ADIACENTI SU CUI EFFETTUARE LA RICERCA: " <<  adjacentPoints.at(0).x() << ", " << adjacentPoints.at(0).x() << std::endl;
               //std::cout << "PUNTI ADIACENTI SU CUI EFFETTUARE LA RICERCA: " <<  adjacentPoints.at(1).x() << ", " << adjacentPoints.at(1).x() << std::endl;

            //std::cout << "Trovata adiacenza padre A" << std::endl;
            // Primo parametro passo il corrispettivo nodo della dag del triangolo father, gli altri due parametri sono i vertici adiacenti
            Dag* d = Dag::navigateTwo(father->getAdjA()->getDagNode(), adjacentPoints.at(0), adjacentPoints.at(1) );
            Adjacencies::setAdjacency(d->getTriangle(), a );
        }
    }

    if(father->getAdjB() != nullptr){
        adjacentPoints = isAdjacenciesFather(adj1, father->getAdjB() );
            if(adjacentPoints.size() > 0){
                //std::cout << "PUNTI ADIACENTI SU CUI EFFETTUARE LA RICERCA: " <<  adjacentPoints.at(0).x() << ", " << adjacentPoints.at(0).y() << std::endl;
                //std::cout << "PUNTI ADIACENTI SU CUI EFFETTUARE LA RICERCA: " <<  adjacentPoints.at(1).x() << ", " << adjacentPoints.at(1).y() << std::endl;

            //std::cout << "Trovata adiacenza padre B" << std::endl;
            // Primo parametro passo il corrispettivo nodo della dag del triangolo father, gli altri due parametri sono i vertici adiacenti
            Dag* d = Dag::navigateTwo(father->getAdjB()->getDagNode(), adjacentPoints.at(0), adjacentPoints.at(1) );

            //std::cout << "E' adiacente con: (" << father->getAdjB()->getA()->x() << ", " << father->getAdjB()->getA()->y() << ") - (" << father->getAdjB()->getB()->x() << ", " << father->getAdjB()->getB()->y() << ") - (" << father->getAdjB()->getC()->x() << ", " << father->getAdjB()->getC()->y() << ")" << std::endl;

            Adjacencies::setAdjacency(d->getTriangle(), a );
        }
    }

    /* Non dovrebbe mai capitare questa situazione
     * if(father->getAdjC() != nullptr){
        if(isAdjacenciesFather(adj1, father->getAdjC() ) == true){
            std::cout << "Trovata adiacenza padre C" << std::endl;
            //Adjacencies::setAdjacency(father->getAdjA(), a );
       }
    }

    */

    //std::cout << " --- " << std::endl;
}


bool Adjacencies::isAdjacencies(Triangle* t1, Triangle* t2){

    if( t1->getA() == t2->getA() && t1->getC() == t2->getB() )
        return true;
    if( t1->getA() == t2->getA() && t1->getB() == t2->getC() )
        return true;

    return false;
}

// Potendoci essere diverse combinazioni possibili restituisco un vettore con due elementi che saranno i punti adiacenti

std::vector<Point2Dd>  Adjacencies::isAdjacenciesFather(Triangle* t1, Triangle* t2){
    // IL triangolo 1 sarà sempre B - C
    // Il triangolo 2 può essere: A - B oppure A - C oppure B - C
    //std::cout << "Controllo adiacenza padre (" << t1->getB()->x() << ", " << t1->getB()->y() << ") (" << t2->getA()->x() << ", " << t2->getA()->y() << " )" << std::endl;
    //std::cout << "Controllo adiacenza padre (" << t1->getC()->x() << ", " << t1->getC()->y() << ") (" << t2->getB()->x() << ", " << t2->getB()->y() << " )" << std::endl;
    //std::cout << "" << std::endl;
    std::vector<Point2Dd> p;

    if( t1->getB() == t2->getA() && t1->getC() == t2->getB() ){ // triangolo 2 AB
        p.push_back(*t2->getA());
        p.push_back(*t2->getB());
    }
    else if( t1->getB() == t2->getA() && t1->getC() == t2->getC() ){ // triangolo 2 AC
        p.push_back(*t2->getA());
        p.push_back(*t2->getC());
    }

    else if( t1->getB() == t2->getB() && t1->getC() == t2->getC() ){ // triangolo 2 BC
        p.push_back(*t2->getB());
        p.push_back(*t2->getC());
    }

    return p;
}

void Adjacencies::setAdjacency(Triangle *adj, Adjacencies *adjNode){
    if(adjNode->getAdjA() == nullptr)
        adjNode->setAdjA(adj);

    else if(adjNode->getAdjB() == nullptr)
        adjNode->setAdjB(adj);

    else if(adjNode->getAdjC() == nullptr)
        adjNode->setAdjC(adj);
}

// Getter & setter
// Getter & Setter
Triangle* Adjacencies::getTriangle(){
    return this->t;
}

Triangle* Adjacencies::getAdjA(){
    return this->adjA;
}

Triangle* Adjacencies::getAdjB(){
    return this->adjB;
}

Triangle* Adjacencies::getAdjC(){
    return this->adjC;
}

void Adjacencies::setTriangle(Triangle* t){
    this->t = t;
}

void Adjacencies::setAdjA(Triangle* t){
    this->adjA = t;
}

void Adjacencies::setAdjB(Triangle* t){
    this->adjB = t;
}

void Adjacencies::setAdjC(Triangle* t){
    this->adjC = t;
}
