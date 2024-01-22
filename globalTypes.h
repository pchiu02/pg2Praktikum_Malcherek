#ifndef GLOBALTYPES_H
#define GLOBALTYPES_H

#include <QString>
#include "booking.h"

enum SortMode{
    id,
    price,
    startDate,
    endDate,
};

struct Edge{
    long from;
    long to;
};

struct TopologicalSortData{
    int vertexNumber;
    std::shared_ptr<Booking> vertex;
    int endTime;
};

struct VertexData{
    int endTime;
    std::shared_ptr<Booking> booking;
};

#endif // GLOBALTYPES_H
