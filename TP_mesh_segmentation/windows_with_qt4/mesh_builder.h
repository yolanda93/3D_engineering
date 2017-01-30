/******************************************************************************************
> [MESHMENTIC]                                                                            <
> Initial Sofware by [Yannick Verdie, Florent Lafarge], Copyright (C) Inria (TITANE)      <
> All Rights Reserved, 2013, [Version 1.0].                                               <
******************************************************************************************/

#ifndef _MESH_BUILDER_H_
#define _MESH_BUILDER_H_

#include <vector>
#include <CGAL/Polyhedron_incremental_builder_3.h>

template <class HDS>
class CMeshBuilder : public CGAL::Modifier_base<HDS>
{
public:
    typedef typename HDS::Vertex Vertex;
    typedef typename Vertex::Point_3 Point_3;
    typedef CGAL::Polyhedron_incremental_builder_3<HDS> Builder;
    
private:
    std::vector<Point_3> m_points;
    std::vector<unsigned> m_facets;

public:    
    CMeshBuilder(const std::vector<Point_3>& points, const std::vector<unsigned>& facets) 
    : m_points(points), m_facets(facets) 
    { }
    
    ~CMeshBuilder()
    { }
    
    void operator()(HDS& hds) 
    {
        if (m_points.empty() && m_facets.empty()) return;
        
        Builder builder(hds, true);
        builder.begin_surface(m_points.size(), m_facets.size()/3);
        // add vertices
        for (unsigned i = 0; i < m_points.size(); ++i)
        {
            const Point_3& p = m_points[i];
            builder.add_vertex(p);
        }
        // add facets
        for (unsigned i = 0; i < m_facets.size(); i+=3)
        {
            builder.begin_facet();
            for (unsigned j = 0; j < 3; ++j)
            {
                unsigned vertex = m_facets[i+j];
                builder.add_vertex_to_facet(vertex);
            }
            builder.end_facet();
        }
        //
        builder.end_surface();
    }
};

#endif
