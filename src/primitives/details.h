#ifndef DETAILS_H
#define DETAILS_H

#include <vector>

#include "base_objects/vertex.h"
#include "base_objects/rib.h"

class Details
{
public:
    Details();
    Details(const Details &details);
    Details(Details &&details);

    std::vector<Vertex> get_vertecies() const;
    std::vector<Rib> get_ribs() const;

    void add_vertex(const Vertex &d);
    void add_rib(const Rib &r);

private:
    std::vector<Rib> ribs;
    std::vector<Vertex> vertecies;
};

#endif // DETAILS_H
