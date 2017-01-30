/******************************************************************************************
> [MESHMENTIC]                                                                            <
> Initial Sofware by [Yannick Verdie, Florent Lafarge], Copyright (C) Inria (TITANE)      <
> All Rights Reserved, 2013, [Version 1.0].                                               <
******************************************************************************************/

#ifndef _MESH_H_
#define _MESH_H_

// STL
#include <set>
#include <list>

// CGAL
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Simple_cartesian.h>

// Qt
#include <QtOpenGL>

// local
#include "console_color.h"
#include "primitives.h"
#include "cloud_segmentation.h"


// #ifdef __APPLE__
//     #include <OpenGL/gl.h>
// #else
//     #ifdef _WIN32
//      #include <windows.h>
//     #endif
//     #include <GL/gl.h>
// #endif



#undef min
#undef max

#define MINN -1e100
#define MAXN  1e100


class Mesh : public Polyhedron_Flo
{
public :
    typedef Mesh::Vertex          Vertex;
    typedef Mesh::Vertex_handle   Vertex_handle;
    typedef Mesh::Vertex_iterator Vertex_iterator;

    typedef Mesh::Halfedge          Halfedge;
    typedef Mesh::Halfedge_handle   Halfedge_handle;
    typedef Mesh::Halfedge_iterator Halfedge_iterator;
    
    typedef Mesh::Halfedge_around_vertex_circulator Halfedge_around_vertex_circulator;
    typedef Mesh::Halfedge_around_facet_circulator  Halfedge_around_facet_circulator;
    
    typedef Mesh::Edge_iterator Edge_iterator;
    
    typedef Mesh::Facet          Facet;
    typedef Mesh::Facet_handle   Facet_handle;
    typedef Mesh::Facet_iterator Facet_iterator;
    
    typedef Kernelsc::FT FT;
    // 2D types
    typedef Kernelsc::Ray_2      Ray_2;
    typedef Kernelsc::Line_2     Line_2;
    typedef Kernelsc::Point_2    Point_2;
    typedef Kernelsc::Vector_2   Vector_2;
    typedef Kernelsc::Segment_2  Segment_2;
    typedef Kernelsc::Triangle_2 Triangle_2;
    // 3D types
    typedef Kernelsc::Ray_3      Ray_3;
    typedef Kernelsc::Line_3     Line_3;
    typedef Kernelsc::Point_3    Point_3;
    typedef Kernelsc::Vector_3   Vector_3;
    typedef Kernelsc::Segment_3  Segment_3;
    typedef Kernelsc::Triangle_3 Triangle_3;
    typedef CGAL::Plane_3<Kernelsc> Plane_3;
    

    typedef std::set< Facet_handle, less_Facet_handle<Facet_handle> > Facet_handle_set;
    typedef std::set< Vertex_handle, less_Vertex_handle<Vertex_handle> > Vertex_handle_set;
    typedef std::set< Halfedge_handle, less_Halfedge_handle<Halfedge_handle> > Halfedge_handle_set;


    
public:
    Mesh() : Polyhedron_Flo() { }
    Mesh(const Polyhedron_Flo& c) : Polyhedron_Flo(c) {};			//important

    ~Mesh() { }
    

    Vertex_handle get_source_vertex(Halfedge_handle h) const
    {
        return h->opposite()->vertex();
    }
    
    Vertex_handle get_target_vertex(Halfedge_handle h) const
    {
        return h->vertex();
    }
    
    Vertex_handle get_opposite_vertex(Halfedge_handle h) const
    {
        return h->next()->vertex();
    }
    
    Halfedge_handle get_oriented_edge(Halfedge_handle edge) const
    {
        unsigned a = get_source_vertex(edge)->index();
        unsigned b = get_target_vertex(edge)->index();
        if (a > b) edge = edge->opposite();
        return edge;
    }
    

    bool is_vertex_boundary(Vertex_handle v) const
    {
        Halfedge_around_vertex_circulator vcirc = v->vertex_begin();
        Halfedge_around_vertex_circulator vend  = vcirc;
        CGAL_For_all(vcirc, vend)
        {
            if (vcirc->is_border_edge()) return true;
        }
        return false;
    }

    void enumerate_vertices()
    {
        unsigned index = 0;
        for (Vertex_iterator vi = Mesh::vertices_begin(); vi != Mesh::vertices_end(); ++vi)
        {
            Vertex_handle v = vi;
            v->index() = index++;
        }
    }

    void compute_bbox(FT& cx, FT& cy, FT& cz, FT& scale)
    {
        FT xmin = MAXN;
        FT xmax = MINN;
        FT ymin = MAXN;
        FT ymax = MINN;
        FT zmin = MAXN;
        FT zmax = MINN;
        for (Vertex_iterator vi = Mesh::vertices_begin(); vi != Mesh::vertices_end(); ++vi)
        {
            Vertex_handle v = vi;
            const Point_3& p = v->point();
            xmin = std::min(xmin, p.x());
            ymin = std::min(ymin, p.y());
            zmin = std::min(zmin, p.z());
            xmax = std::max(xmax, p.x());
            ymax = std::max(ymax, p.y());
            zmax = std::max(zmax, p.z());
        }
        
        FT dx = xmax - xmin;
        FT dy = ymax - ymin;
        FT dz = zmax - zmin;
        scale = std::max(dx, std::max(dy, dz));
        if (scale == 0.0) scale = 1.0;
        
        cx = 0.5*(xmax + xmin);
        cy = 0.5*(ymax + ymin);
        cz = 0.5*(zmax + zmin);
    }
    
    void fit_to_unit_box()
    {
        FT cx, cy, cz, scale;
        compute_bbox(cx, cy, cz, scale);
        
        Point_3 center(cx, cy, cz);
        for (Vertex_iterator vi = Mesh::vertices_begin(); vi != Mesh::vertices_end(); ++vi)
        {
            Vertex_handle v = vi;
            Point_3 p = CGAL::ORIGIN + (v->point() - center)/scale;
            v->point() = p;
        }
    }

    void displayRangeLineWidth()
    {
        GLfloat sizes[2];  // Store supported line width range
        GLfloat step;     // Store supported line width increments


        // Get supported line width range and step size
        glGetFloatv(GL_LINE_WIDTH_RANGE,sizes);
        glGetFloatv(GL_LINE_WIDTH_GRANULARITY,&step);

        printf("min %f max %f step %f\n" ,  sizes[0] ,  sizes[1] , step);
    }

    void turn_on_lights()
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
    }
    
    void turn_off_lights()
    {
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
    }

	void set_grey_color(){
		for (Facet_iterator fi = Mesh::facets_begin(); fi != Mesh::facets_end(); fi++)
			fi->color() = CGAL::Color(190,190,190);
	}

    void draw_edges(const float line_width, const float red, const float green, const float blue)
    {
        glLineWidth(line_width);
        glColor3f(red, green, blue);
        for (Edge_iterator ei = Mesh::edges_begin(); ei != Mesh::edges_end(); ei++)
        {
            Halfedge_handle h = ei;
            const Point_3& a = get_source_vertex(h)->point();
            const Point_3& b = get_target_vertex(h)->point();
            draw_segment(a, b);
        }
    }



    void draw_points(const float point_width, const float red, const float green, const float blue)
    {
        glPointSize(point_width);
        glColor3f(red, green, blue);
        for (Vertex_iterator v = Mesh::vertices_begin(); v != Mesh::vertices_end(); v++)
            draw_point(v->point());
    }
    
    //Not used
    void draw_facets(const float red, const float green, const float blue)
    {
        qDebug()<<"FIX ME: should not be called !";
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1, 10);
        turn_on_lights();
        glColor3f(red, green, blue);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        int count = 0;
        for (Facet_iterator fi = Mesh::facets_begin(); fi != Mesh::facets_end(); fi++)
        {
            const Point_3& a = fi->halfedge()->vertex()->point();
            const Point_3& b = fi->halfedge()->next()->vertex()->point();
            const Point_3& c = fi->halfedge()->next()->next()->vertex()->point();

            draw_triangle(a, b, c);

        }
        turn_off_lights();
        glDisable(GL_POLYGON_OFFSET_FILL);
    }

	/*void draw_facets_fromCGALColor()
	{
		qDebug() << "FIX ME: should not be called !";
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 10);
		turn_on_lights();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		int count = 0;
		for (Facet_iterator fi = Mesh::facets_begin(); fi != Mesh::facets_end(); fi++)
		{
			const Point_3& a = fi->halfedge()->vertex()->point();
			const Point_3& b = fi->halfedge()->next()->vertex()->point();
			const Point_3& c = fi->halfedge()->next()->next()->vertex()->point();

			float red = (float)fi->color.r();
			float green = (float)fi->color.g();
			float blue = (float)fi->color.b();
			glColor3f(red, green, blue);
			draw_triangle(a, b, c);

		}
		turn_off_lights();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}*/

//    void draw_selection_color(const CGAL::Color &c, int label)
//    {

//        int count = 0;
//        int next = 0;
//        for (Facet_iterator fi = Mesh::facets_begin() ; fi != Mesh::facets_end(); fi++, count++ )
//        {
//            float rc = fi->color().r()/255.f;
//            float gc = fi->color().g()/255.f;
//            float bc = fi->color().b()/255.f;

//            if (next < selection.size())
//            {
//               // qDebug()<<selection[next]<<"/"<<count;
//                if (count == selection[next])
//                {
//                    next++;
//                    fi->label() = label;
//                    fi->color() = M_original.getColorLabel(label);
//                }
//            }
//        }
//    }

    void draw_facets(const vector<int> &selection = vector<int>(), const bool rname = false)
    {
        if (!rname)
        {
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1, 10);
            turn_on_lights();
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        int count = 0;
        int next = 0;
        for (Facet_iterator fi = Mesh::facets_begin() ; fi != Mesh::facets_end(); fi++, count++ )
        {
            float rc = fi->color().r()/255.f;
            float gc = fi->color().g()/255.f;
            float bc = fi->color().b()/255.f;
            //std::cout<<rc<<endl;

            if (next < selection.size())
            {
               // qDebug()<<selection[next]<<"/"<<count;
                if (count == selection[next])
                {
                    next++;
                    rc/=2;gc/=2;bc/=2;//the selection is darker...
                }
            }
            //else
            //    qDebug()<<"selection empty";

            glColor3f(rc,gc,bc);

            const Point_3& a = fi->halfedge()->vertex()->point();
            const Point_3& b = fi->halfedge()->next()->vertex()->point();
            const Point_3& c = fi->halfedge()->next()->next()->vertex()->point();

            if (rname) glPushName(count);
            draw_triangle(a, b, c);
            if (rname) glPopName();
        }

        if (!rname)
        {
            turn_off_lights();
            glDisable(GL_POLYGON_OFFSET_FILL);
        }
    }

    void draw_segment(const Point_3& a, const Point_3& b) const
    {
        glBegin(GL_LINES);
        glVertex3d(a[0], a[1], a[2]);
        glVertex3d(b[0], b[1], b[2]);
        glEnd();
    }
    
    void draw_triangle(const Point_3& a, const Point_3& b, const Point_3& c) const
    {
        set_normal(a, b, c);
        glBegin(GL_TRIANGLES);
        glVertex3d(a[0], a[1], a[2]);
        glVertex3d(b[0], b[1], b[2]);
        glVertex3d(c[0], c[1], c[2]);
        glEnd();
    }
    
    void set_normal(const Point_3& a, const Point_3& b, const Point_3& c) const
    {
        Vector_3 n = CGAL::cross_product(b-a, c-b);
        n = n / std::sqrt(n*n);
        glNormal3d(n[0], n[1], n[2]);
    }
    
	void set_colors(std::vector < CGAL::Color> vector_colors)
	{
		int i = 0;
		for (Facet_iterator fi = Mesh::facets_begin(); fi != Mesh::facets_end(); fi++,i++)
			fi->color() = vector_colors[i];
	}

    void draw_point(const Point_3& p) const
    {
        glBegin(GL_POINTS);
        glVertex3d(p[0], p[1], p[2]);
        glEnd();
    }
};

#endif
