#ifndef _DT3_
#define _DT3_

#include <CGAL/basic.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Bbox_3.h>
#include <CGAL/Timer.h>
#include <iostream>

#include <QtOpenGL>
#include <QtOpenGL/qgl.h>

#undef min
#undef max

template < class Kernel, class TDS >
class DT3 : public CGAL::Delaunay_triangulation_3<Kernel, TDS>
{
public:
	typedef DT3<Kernel,TDS> Dt;

	typedef typename Kernel::FT            FT;
	typedef typename Kernel::Point_3       Point;
	typedef typename Kernel::Vector_3      Vector;
	typedef typename Kernel::Segment_3     Segment;
	typedef typename Kernel::Line_3        Line;
	typedef typename Kernel::Triangle_3    Triangle;
	typedef typename Kernel::Tetrahedron_3 Tetrahedron;

	typedef typename Dt::Vertex                   Vertex;
	typedef typename Dt::Vertex_handle            Vertex_handle;
	typedef typename Dt::Vertex_iterator          Vertex_iterator;
	typedef typename Dt::Finite_vertices_iterator Finite_vertices_iterator;

	typedef typename Dt::Edge                  Edge;
	typedef typename Dt::Edge_iterator         Edge_iterator;
	typedef typename Dt::Finite_edges_iterator Finite_edges_iterator;

	typedef typename Dt::Facet                   Facet;
	typedef typename Dt::Facet_iterator          Face_iterator;
	typedef typename Dt::Facet_circulator        Face_circulator;
	typedef typename Dt::Finite_facets_iterator  Finite_facets_iterator;

	typedef typename Dt::Cell                  Cell;
	typedef typename Dt::Cell_handle           Cell_handle;
	typedef typename Dt::Cell_iterator         Cell_iterator;
	typedef typename Dt::Cell_circulator       Cell_circulator;
	typedef typename Dt::Finite_cells_iterator Finite_cells_iterator;


public:
	DT3() {}
	~DT3() {}

public:

	Vertex_handle get_source_vertex(const Edge& edge) const
	{
		return edge.first->vertex(edge.second);
	}

	Vertex_handle get_target_vertex(const Edge& edge) const
	{
		return edge.first->vertex(edge.third);
	}

	// RENDERING
	void gl_vertex(const Point& p)
	{
		::glVertex3d(p.x(), p.y(), p.z());
	}

	void render_edges(const float line_width,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue)
	{
		::glLineWidth(line_width);        
		::glColor3ub(red,green,blue);
		::glBegin(GL_LINES);

		Finite_edges_iterator e;
		for (e = Dt::finite_edges_begin(); e != Dt::finite_edges_end(); e++)
		{
			Edge edge = *e;
			gl_vertex(get_source_vertex(edge)->point());
			gl_vertex(get_target_vertex(edge)->point());
		}
		::glEnd();
	}

	template <class OutputIterator> // value_type = Triangle_3
	void compute_alpha_shape(const FT alpha, OutputIterator out)
	{
		Finite_facets_iterator fit;
		for (fit = Dt::finite_facets_begin(); fit != Dt::finite_facets_end() ; fit++ )
		{
			Facet f = *fit;
			if(is_alpha(f, alpha))
				*out++ = Dt::triangle(f);
		}
	}

	Point circumcenter(Cell_handle c)
	{
		return CGAL::circumcenter( c->vertex(0)->point(),
			c->vertex(1)->point(), 
			c->vertex(2)->point(), 
			c->vertex(3)->point());
	}

	bool is_alpha(Facet &f, const FT alpha)
	{
		assert( alpha > 0.0 );
		assert( ! Dt::is_infinite( f ) );

		// a facet is defined as a pair {Cell, index}
		Cell_handle c = f.first;
		const int ic = f.second; // index of vertex facing facet f

		// get incident cell
		Cell_handle n = c->neighbor(ic);

		// get facet points in right order
		Point p1, p2, p3; //  Points in facet c
		if ( ic%2 == 1 )
		{
			p1 = c->vertex((ic+1)%4)->point(); 
			p2 = c->vertex((ic+2)%4)->point();
			p3 = c->vertex((ic+3)%4)->point();
		}
		else
		{
			p1 = c->vertex((ic+2)%4)->point();
			p2 = c->vertex((ic+1)%4)->point();
			p3 = c->vertex((ic+3)%4)->point();
		}

		// TO COMPLETE...
                Point Oc = this->circumcenter(c); // compute circumcenter of c
                Point On = this->circumcenter(n); // compute circumcenter of n

                FT Rc = CGAL::squared_distance( Oc, p1 ); 
                FT Rn = CGAL::squared_distance( On, p1 ); 
                FT Rf = CGAL::squared_distance(p1, CGAL::circumcenter( p1, p2, p3 )); 

	       // case n is infinite
	       if ( Dt::is_infinite( n ) )
	       {
		if ( CGAL::orientation(p1, p2, p3, Oc) == CGAL::POSITIVE)	
      		    return alpha > Rf;
		else 
	            return alpha > Rc; 
	       }

	       // case c is infinite
	       if ( Dt::is_infinite( c ) )
	       {
	         if ( orientation(p1, p2, p3, On) == CGAL::NEGATIVE )
                      return alpha > Rf;
                 else
                      return alpha > Rn;
               }

	       // case both c and n are finite

               if ( orientation( p1,p2,p3,Oc ) != orientation( p1,p2,p3,On ) )
                   return alpha < CGAL::max( Rc, Rn ) && alpha > Rf;
               else
                   return alpha < CGAL::max( Rc, Rn ) && alpha > CGAL::min( Rc, Rn );
       }


};
#endif // _DT3_
