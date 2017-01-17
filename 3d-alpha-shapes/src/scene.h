#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <list>

#include "types.h"

#undef CGAL_CFG_NO_CPP0X_VARIADIC_TEMPLATES

class Scene
{
private:

	// input point set
	Bbox m_bbox;
	std::list<Point> m_points;

	// 3D Delaunay triangulation
	Dt3 m_dt;

	// alpha shape stored as set of transparent facets
	std::list<Triangle> m_triangles;

	// rendering options
	bool m_view_edges;
	bool m_view_points;
	bool m_view_alpha_shape;

public: // life cycle
	Scene();
	virtual ~Scene();

	// bbox
	const Bbox& bbox() const { return m_bbox; }
	FT bbox_diag() const;
	void update_bbox();
	void reset_bbox();

	// file menu
	int open(QString filename);

	// algorithms menu
	int compute_alpha_shape(const FT alpha);

	// toggle rendering options
	void toggle_view_edges()    { m_view_edges = !m_view_edges; } 
	void toggle_view_points()  { m_view_points = !m_view_points; } 
	void toggle_view_alpha_shape()  { m_view_alpha_shape = !m_view_alpha_shape; } 

	// rendering
	void render(); 
	void render_points();
	void render_alpha_shape();
	void set_opacity(const float gamma);
};

#endif // SCENE_H
