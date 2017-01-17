#ifndef TYPES_H
#define TYPES_H

// kernel
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

// basic types from kernel
typedef Kernel::FT FT;
typedef CGAL::Bbox_3 Bbox;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;
typedef Kernel::Segment_3 Segment;
typedef Kernel::Triangle_3 Triangle;

// 3D triangulation
#include "dt3.h"
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Triangulation_data_structure_3.h>
#include <CGAL/Triangulation_vertex_base_3.h>
#include <CGAL/Triangulation_cell_base_3.h>
typedef CGAL::Triangulation_vertex_base_3<Kernel> Vb;
typedef CGAL::Triangulation_cell_base_3<Kernel> Cb;
typedef CGAL::Triangulation_data_structure_3<Vb, Cb> Tds;
typedef DT3<Kernel, Tds> Dt3;

#endif // TYPES_H


