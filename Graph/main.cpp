#include <iostream>
#include <iomanip>
using namespace std;
#include "graph.h"
#include "algorithmen.cpp"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const int n = 8;
    Graph<int, n>* graph = new Graph<int, n>;
    graph->insertVertex(1, 10);
    graph->insertVertex(2, 20);
    graph->insertVertex(3, 30);
    graph->insertVertex(4, 40);
    graph->insertVertex(5, 50);
    graph->insertVertex(6, 60);

    graph->insertEdge(1, 2);
    graph->insertEdge(1, 4);
    graph->insertEdge(4, 2);
    graph->insertEdge(2, 5);
    graph->insertEdge(5, 4);
    graph->insertEdge(3, 5);
    graph->insertEdge(3, 6);
    graph->insertEdge(6, 6);
    graph->printVertices();
    graph->printAdjMatrix();

    cout << "===========Start Tiefensuche====================" << endl;
    depthFirstSearch(*graph);
    graph->printAdjMatrix();

    cout << "===========Graph wird geloescht==================" << endl;
    delete graph;

    cout << "===========Neuer Graph wird angelegt=============" << endl;
    graph = new Graph<int, n>;
    graph->insertVertex(1, 10);
    graph->insertVertex(2, 20);
    graph->insertVertex(3, 30);
    graph->insertVertex(4, 40);
    graph->insertVertex(5, 50);
    graph->insertVertex(6, 60);
    graph->insertVertex(7, 70);

    graph->insertEdge(1, 2);
    graph->insertEdge(2, 1);
    graph->insertEdge(1, 5);
    graph->insertEdge(5, 1);
    graph->insertEdge(2, 6);
    graph->insertEdge(6, 2);
    graph->insertEdge(3, 6);
    graph->insertEdge(6, 3);
    graph->insertEdge(6, 7);
    graph->insertEdge(7, 6);
    graph->insertEdge(4, 7);
    graph->insertEdge(7, 4);
    graph->printVertices();
    graph->printAdjMatrix();

    cout << "==========Start Breitensuche====================" << endl;
    breadthFirstSearch(*graph);

    return a.exec();
}
