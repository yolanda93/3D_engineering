#ifndef _DT3_
#define _DT3_

#include <CGAL/basic.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Bbox_3.h>
#include <CGAL/Timer.h>

#include <QtOpenGL>
#include <QtOpenGL/qgl.h>

#include "render.h"

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


	typedef typename Render_transparent<Kernel>::Transparent_facet Transparent_facet;

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
		::glVertex3d(p.x(),p.y(),p.z());
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

	bool is_alpha(Facet &f, 
		const FT alpha)
	{
		assert( alpha > 0.0 );
		assert( ! Dt::is_infinite( f ) );

		Cell_handle c = f.first;
		int ic = f.second;

		Cell_handle n = c->neighbor(ic);

		Point p1, p2, p3;

		if ( ic%2 == 1 ) {
			p1 = c->vertex((ic+1)&3)->point(); // &3 au lieu de %4
			p2 = c->vertex((ic+2)&3)->point();
			p3 = c->vertex((ic+3)&3)->point();
		}
		else {
			p1 = c->vertex((ic+2)&3)->point();
			p2 = c->vertex((ic+1)&3)->point();
			p3 = c->vertex((ic+3)&3)->point();
		}

		if ( Dt::is_infinite( n ) ) {
			Point Oc = CGAL::circumcenter( c->vertex(0)->point(), 
				c->vertex(1)->point(),
				c->vertex(2)->point(),
				c->vertex(3)->point() );
			if ( CGAL::orientation( p1,p2,p3,Oc ) == CGAL::POSITIVE ) 
				return( alpha > 
				CGAL::squared_distance( p1, CGAL::circumcenter( p1,p2,p3 ) ) );
			else 
				return( alpha > CGAL::squared_distance( Oc, p1 ) );
		}

		if ( Dt::is_infinite( c ) ) {
			Point On = CGAL::circumcenter( n->vertex(0)->point(), 
				n->vertex(1)->point(),
				n->vertex(2)->point(),
				n->vertex(3)->point() );
			if (CGAL:: orientation( p1,p2,p3,On ) == CGAL::NEGATIVE ) 
				return( alpha > 
				CGAL::squared_distance( p1, CGAL::circumcenter( p1,p2,p3 ) ) );
			else 
				return( alpha > CGAL::squared_distance( On, p1 ) );
		}

		// now both c and n are finite

		Point Oc = CGAL::circumcenter( c->vertex(0)->point(), 
			c->vertex(1)->point(),
			c->vertex(2)->point(),
			c->vertex(3)->point() );
		Point On = CGAL::circumcenter( n->vertex(0)->point(), 
			n->vertex(1)->point(),
			n->vertex(2)->point(),
			n->vertex(3)->point() );

		FT R2c = CGAL::squared_distance( Oc, p1 );
		FT R2n = CGAL::squared_distance( On, p1 );

		if ( CGAL::orientation( p1,p2,p3,Oc ) != CGAL::orientation( p1,p2,p3,On ) ) 
			return ( ( alpha < CGAL::max( R2c, R2n ) ) 
			&&
			( alpha > 
			CGAL::squared_distance( p1, CGAL::circumcenter( p1,p2,p3 ) ) ) );
		else
			return ( ( alpha < CGAL::max( R2c, R2n ) ) 
			&&
			( alpha > CGAL::min( R2c, R2n ) ) );
	}




};

#endif // _DT3_


