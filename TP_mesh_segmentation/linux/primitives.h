/******************************************************************************************
> [MESHMENTIC]                                                                            <
> Initial Sofware by [Yannick Verdie, Florent Lafarge], Copyright (C) Inria (TITANE)      <
> All Rights Reserved, 2013, [Version 1.0].                                               <
******************************************************************************************/

#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include <CGAL/Polyhedron_3.h>

//#include "bvd.h"
//#include "ramp.h"
//#include "bin.h"
//#include "sample.h"
//#include "binlist.h"

#define EPS 1e-12

////////////
// VERTEX //
////////////

template <class Kernel, class Refs, class T, class P>
class Enriched_vertex : public CGAL::HalfedgeDS_vertex_base<Refs, T, P>
{
public:
	typedef typename Kernel::FT FT;
	typedef typename Kernel::Point_3 Point;

	//typedef CBin<Kernel> Bin;
	//typedef CBinList<Kernel> Bin_list;
	//typedef typename std::list<Bin>::iterator bin_iterator;

private:
	// bin list also for a vertex so that we can have, e.g., none.
   // Bin_list m_bins; 
    unsigned m_index;

public:
	Enriched_vertex()  { m_index = 0; }

	Enriched_vertex(const P& pt) 
    : CGAL::HalfedgeDS_vertex_base<Refs, T, P>(pt)
	{
	}

    //Bin_list& bins() { return m_bins; }
    //const Bin_list& bins() const { return m_bins; }

    unsigned& index() { return m_index; }
    const unsigned index() const { return m_index; }
    
	//bool has_bins() const { return !m_bins.empty(); }
	//unsigned nb_bins() const { return m_bins.size(); }

	//bin_iterator bins_begin() { return m_bins.get_begin_iterator(); }
	//bin_iterator bins_end() { return m_bins.get_end_iterator(); }
    
	/*
	void draw_bin_centers() const { m_bins.draw_centers(); }
    
    void destroy_bins()
    {
        m_bins.clear();
    }
    
	unsigned generate_bins() 
	{ 
		unsigned nbins = m_bins.init_point(this->point());
		return nbins;
	}
    
    void compute_capacities()
    {
        if (!has_bins()) return;
        FT capacity = 1.0;
        for (bin_iterator bi = bins_begin(); bi != bins_end(); ++bi)
        {
            Bin& b = *bi;
            b.capacity() = capacity;
        }
    }
	*/
};

//////////////
// HALFEDGE //
//////////////

template <class Kernel, class Refs, class Tprev, class Tvertex, class Tface, class Normal>
class Enriched_halfedge : public CGAL::HalfedgeDS_halfedge_base<Refs,Tprev,Tvertex,Tface>
{
public:
	typedef typename Kernel::FT FT;
	typedef typename Kernel::Point_3 Point_3;
	typedef typename Kernel::Segment_3 Segment_3;

	//typedef CBin<Kernel> Bin;
	//typedef CBinList<Kernel> Bin_list;
//	typedef typename std::list<Bin>::iterator bin_iterator;

private:
   // Bin_list m_bins;

public:
	Enriched_halfedge() { }

public:
    //Bin_list& bins() { return m_bins; }
    //const Bin_list& bins() const { return m_bins; }

	//bool has_bins() const { return !m_bins.empty(); }
	//unsigned nb_bins() const { return m_bins.size(); }

	//bin_iterator bins_begin() { return m_bins.get_begin_iterator(); }
	//bin_iterator bins_end() { return m_bins.get_end_iterator(); }
    
	//void draw_bin_centers() const { m_bins.draw_centers(); }
    
    //void destroy_bins()
    //{
    //    m_bins.clear();
    //}
    
	/*
	unsigned generate_bins(const FT quadrature) 
	{ 
		Segment_3 segment = make_segment();
		FT len = std::sqrt(segment.squared_length());
		if (len < EPS) return 0;

        unsigned nbins = unsigned(ceil(len * quadrature));
        if (nbins < 2) nbins = 2;
        nbins = m_bins.init_segment(segment, nbins);
		return nbins;
	}

    void compute_capacities()
    {
        if (!has_bins()) return;
        
        FT capacity = length() / nb_bins();
        for (bin_iterator bi = bins_begin(); bi != bins_end(); ++bi)
        {
            Bin& b = *bi;
            b.capacity() = capacity;
        }
    }  */  

	FT length() const
	{
		Segment_3 segment = make_segment();
		return std::sqrt(segment.squared_length());
	}

    Segment_3 make_segment() const
    {
        const Point_3& s = this->opposite()->vertex()->point();
        const Point_3& t = this->vertex()->point();
        return Segment_3(s, t);
    }    
};

///////////
// FACET //
///////////

template <class Kernel, class Refs, class T, class P, class Normal>
class Enriched_facet : public CGAL::HalfedgeDS_face_base<Refs, T>
{
public:
	typedef typename Kernel::FT FT;
	typedef typename Kernel::Point_3 Point_3;
    typedef typename Kernel::Vector_3 Vector_3;
	typedef typename Kernel::Triangle_3 Triangle_3;
	typedef typename Kernel::Triangle_3 Triangle;    
    
//	typedef CBin<Kernel> Bin;
//	typedef CBinList<Kernel> Bin_list;
//	typedef typename std::list<Bin>::iterator bin_iterator;
    
//	typedef CGAL::Triangulation_face_base_2<Kernel> Face_base;
//	typedef CGAL::Triangulation_vertex_base_2<Kernel> Vertex_base;
//	typedef CGAL::Triangulation_data_structure_2<Vertex_base, Face_base> TDS;
//    typedef CBvd<Kernel, TDS> Bvd;
    
private:
//    Bin_list m_bins;

public:
	Enriched_facet() { }

	FT area() const
	{
		Triangle_3 triangle = make_triangle();
		return std::sqrt(triangle.squared_area());
	}

	Triangle_3 make_triangle() const
	{
		Point_3 a = this->halfedge()->vertex()->point();
		Point_3 b = this->halfedge()->next()->vertex()->point();
		Point_3 c = this->halfedge()->next()->next()->vertex()->point();
		return Triangle_3(a, b, c);
	}
    
   // Bin_list& bins() { return m_bins; }
    //const Bin_list& bins() const { return m_bins; }

	//bool has_bins() const { return !m_bins.empty(); }
	//unsigned nb_bins() const { return 0; }//useless

	//bin_iterator bins_begin() { return m_bins.get_begin_iterator(); }
	//bin_iterator bins_end() { return m_bins.get_end_iterator(); }
    
	//void draw_bin_centers() const { m_bins.draw_centers(); }
    
	/*
    void destroy_bins()
    {
        m_bins.clear();
    }
    
	unsigned generate_bins(const FT quadrature) 
	{ 
		Triangle_3 triangle = make_triangle();
		FT area = std::sqrt(triangle.squared_area());
		if (area < EPS) return 0;

		FT sq_quadrature = quadrature*quadrature;
		unsigned nbins = unsigned(ceil(area * sq_quadrature));		
        if (nbins < 3) nbins = 3;
		nbins = m_bins.init_triangle(triangle, nbins);
		return nbins;
	}	*/
    
    void run_lloyd()
    {
		/*
        //if (!has_bins()) return;
        
        Bvd bvd(make_triangle());
        populate_bvd(bvd);
        
        std::list<Point_3> centroids;
        bool ok = bvd.get_centroids(std::back_inserter(centroids));
		if (!ok) return;
        
        typename std::list<Point_3>::const_iterator ci = centroids.begin();
        for (bin_iterator bi = bins_begin(); bi != bins_end(); ++bi, ++ci)
        {
           // Bin& b = *bi;
            b.point() = *ci;
        }
		*/
    }

	/*
    void compute_capacities()
    {

        if (!has_bins()) return;

        Bvd bvd(make_triangle());
        populate_bvd(bvd);

        std::list<FT> areas;
        bool ok = bvd.get_cells_area(std::back_inserter(areas));
		if (!ok) return;

        typename std::list<FT>::const_iterator ai = areas.begin();
        for (bin_iterator bi = bins_begin(); bi != bins_end(); ++bi, ++ai)
        {
            Bin& b = *bi;
            b.capacity() = *ai;
        }
    }

    void draw_bvd()
    {
        if (!has_bins()) return;
        Bvd bvd(make_triangle());
        populate_bvd(bvd);
        bvd.draw_cells();
        bvd.draw_edges();
    }
    
    void draw_capacities()
    {
        if (!has_bins()) return;
        Bvd bvd(make_triangle());
        populate_bvd(bvd);        
        Ramp ramp;
        ramp.build_thermal();
        bvd.draw_cells_area(ramp);
    }
    
    void populate_bvd(Bvd& bvd)
    {
        for (bin_iterator bi = bins_begin(); bi != bins_end(); ++bi)
        {
            const Bin& b = *bi;
            bvd.add_point(b.point());
        }        
    }
	*/
};

///////////
// ITEMS //
///////////

struct Enriched_items : public CGAL::Polyhedron_items_3
{
	// wrap vertex
	template<class Refs, class Traits> struct Vertex_wrapper
	{
		typedef typename Traits::Point_3 Point;
		typedef typename Traits::Vector_3 Normal;
		typedef Enriched_vertex<Traits, Refs, CGAL::Tag_true, Point> Vertex;
	};

	// wrap face
	template<class Refs, class Traits> struct Face_wrapper
	{
		typedef typename Traits::Point_3 Point;
		typedef typename Traits::Vector_3 Normal;
		typedef Enriched_facet<Traits, Refs, CGAL::Tag_true, Point, Normal> Face;
	};

	// wrap halfedge
	template<class Refs, class Traits> struct Halfedge_wrapper
	{
		typedef typename Traits::Vector_3 Normal;
		typedef Enriched_halfedge<Traits, Refs, CGAL::Tag_true, CGAL::Tag_true, CGAL::Tag_true, Normal> Halfedge;
	};
};

/////////////////
// STRUCT LESS //
/////////////////

template <class T>
struct less_Vertex_handle
{
    bool operator() (const T& a, const T& b) const
    {
        return (a->index() < b->index());
    }
};

template <class T>
struct less_Halfedge_handle
{
    void get_vertices_id(const T& a, unsigned& i, unsigned& j) const
    {
        i = a->vertex()->index();
        j = a->opposite()->vertex()->index();
        if (i > j) std::swap(i, j);
    }
    
    bool operator() (const T& a, const T& b) const
    {
        unsigned a0, a1;
        get_vertices_id(a, a0, a1);
        
        unsigned b0, b1;
        get_vertices_id(b, b0, b1);
        
        if (a0 < b0) return true;
        if (a0 > b0) return false;
        if (a1 < b1) return true;
        return false;
    }    
};

template <class T>
struct less_Facet_handle
{
    void get_vertices_id(const T& face, unsigned& a, unsigned& b, unsigned& c) const
    {
        a = face->halfedge()->vertex()->index();
        b = face->halfedge()->next()->vertex()->index();
        c = face->halfedge()->prev()->vertex()->index();
    }
    
    bool operator() (const T& a, const T& b) const
    {
        unsigned a0, a1, a2;
        get_vertices_id(a, a0, a1, a2);
        
        unsigned b0, b1, b2;
        get_vertices_id(b, b0, b1, b2);
        
        if (a0 < b0) return true;
        if (a0 > b0) return false;
        
        if (a1 < b1) return true;
        if (a1 > b1) return false;
        
        if (a2 < b2) return true;
        return false;
    }
};

#endif // _PRIMITIVES_H_
