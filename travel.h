#ifndef TRAVEL_H
#define TRAVEL_H

#include <memory>
#include <stack>
#include <vector>
#include <memory.h>

#include "booking.h"
#include "graph.h"
#include "heap.h"
#include "globalTypes.h"

using namespace std;

class Travel
{
public:
    Travel(long id, long customerId);
    void addBooking(std::shared_ptr<Booking> booking);
    int getBookingCount();

    long getId() const;
    long getCustomerId() const;
    const vector<std::shared_ptr<Booking>> &getTravelBookings() const;

    void createGraph();
    void sortGraph(std::vector<VertexData> &data);
    void extracted(int &index);
    std::vector<std::shared_ptr<Booking>> sortTopologically();
    void topologicalSortUtil(int v, std::vector<bool> &visited, std::stack<int> &stack);

    Graph<std::shared_ptr<Booking>, 100> getGraph() const;
    void setGraph(const Graph<std::shared_ptr<Booking>, 100> &newGraph);

private:
    long id;
    long customerId;
    vector<std::shared_ptr<Booking>> travelBookings;
    Graph<std::shared_ptr<Booking>, 100> graph;
};

#endif // TRAVEL_H
