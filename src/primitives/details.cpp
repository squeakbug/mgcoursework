#include "primitives/details.h"
#include "errors/logicexceptions.h"


Details::Details()
{

}


Details::Details(const Details &details)
    : ribs(details.ribs),
      vertecies(details.vertecies)
{

}


Details::Details(Details &&details)
    : ribs(details.ribs),
      vertecies(details.vertecies)
{

}


std::vector<Vertex> Details::get_vertecies() const
{
    return vertecies;
}


std::vector<Rib> Details::get_ribs() const
{
    return ribs;
}


void Details::add_vertex(const Vertex &d)
{
    vertecies.push_back(d);
}


void Details::add_rib(const Rib &r)
{
    auto vertex_cnt = vertecies.size();

    if (r.indx1 < vertex_cnt && r.indx2 < vertex_cnt)
    {
        ribs.push_back(r);
    }
    else
    {
        throw NoSuchVertexException(__FILE__, typeid(*this).name(), __LINE__);
    }
}
