#include "travel.h"
#include "algorithmen.cpp"

#include <stack>

Travel::Travel(long id, long customerId)
{
    this->id = id;
    this->customerId = customerId;
}

void Travel::addBooking(std::shared_ptr<Booking> booking){
    travelBookings.push_back(booking);
}

int Travel::getBookingCount()
{
    return travelBookings.size();
}

long Travel::getId() const
{
    return id;
}

long Travel::getCustomerId() const
{
    return customerId;
}

const vector<std::shared_ptr<Booking>> &Travel::getTravelBookings() const
{
    return travelBookings;
}

void Travel::createGraph(){
    for(size_t index = 0; index < travelBookings.size(); ++index){
        graph.insertVertex(index, travelBookings[index]);
    }

    //connect bookings based on predecessor
    int numBookings = travelBookings.size();
    for(int i = 0; i < numBookings; ++i){
        for(int j = 0; j < numBookings; ++j){
            auto booking1 = travelBookings[i];
            auto booking2 = travelBookings[j];
            if((booking1->getPredecessor1() == booking2->getId() || booking1->getPredecessor2() == booking2->getId())){
                graph.insertEdge(j,i);
            }
        }
    }
}

void Travel::sortGraph(std::vector<VertexData> & data){
    depthFirstSearch(graph);

    VertexData vertexData;
    for(size_t i = 0; i < travelBookings.size(); ++i){
        vertexData.booking = graph.getVertexValue(i);
        vertexData.endTime = graph.getEnd(i);

        data.push_back(vertexData);
    }

    std::sort(data.begin(), data.end(), [](const VertexData &a, const VertexData &b) {
        return a.endTime > b.endTime;
    });
}

std::vector<std::shared_ptr<Booking> > Travel::sortTopologically()
{
    std::stack<int> stack;
    std::vector<bool> visited(travelBookings.size(),false);

    for(int i = 0; i < travelBookings.size(); i++){
        if(!visited[i]){
            topologicalSortUtil(i, visited, stack);
        }
    }

    //push from stack to vector to get the sorted bookings
    std::vector<std::shared_ptr<Booking>> sortedBookings;
    while(!stack.empty()){
        sortedBookings.push_back(travelBookings[stack.top()]);
        stack.pop();
    }
    return sortedBookings;
}

void Travel::topologicalSortUtil(int v, std::vector<bool> &visited, std::stack<int> &stack)
{
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for(int i = 0; i < graph.getNumVertices(); i++){
        //check if there is an edge from v to i
        if(graph.isEdge(v,i) && !visited[i]){
            topologicalSortUtil(i, visited, stack);
        }
    }
    stack.push(v);
}

void Travel::setGraph(const Graph<std::shared_ptr<Booking>, 100> &newGraph)
{
    graph = newGraph;
}

Graph<std::shared_ptr<Booking>, 100> Travel::getGraph() const
{
    return graph;
}
