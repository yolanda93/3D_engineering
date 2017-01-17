#include "scene.h"

#include <iostream>
#include <fstream>

#include <QFileInfo>
#include <QTextStream>
#include <QInputDialog>
#include <QtCore/qglobal.h>

#include <QGLViewer/qglviewer.h>


Scene::Scene()
{
	reset_bbox();

	// view options
	m_view_edges = true;
	m_view_points = true;
	m_view_alpha_shape = true;
}

Scene::~Scene()
{
}

FT Scene::bbox_diag() const
{
	double dx = m_bbox.xmax() - m_bbox.xmin();
	double dy = m_bbox.ymax() - m_bbox.ymin();
	double dz = m_bbox.zmax() - m_bbox.zmin();
	return FT(std::sqrt(dx*dx + dy*dy + dz*dz));
}

void Scene::update_bbox()
{
	reset_bbox();
	if (m_points.size() == 0) 
		return;

	std::list<Point>::const_iterator it;
	for (it = m_points.begin(); it != m_points.end(); it++)
		m_bbox = m_bbox + it->bbox();
}

void Scene::reset_bbox()
{
	m_bbox = Bbox(0., 0., 0., 0., 0., 0.);
}

int Scene::open(QString filename)
{
	QFileInfo fileinfo(filename);
	std::ifstream ifs(filename.toUtf8());

	if(!ifs || !fileinfo.isFile() || ! fileinfo.isReadable())
	{
		std::cerr << "unable to open file" << std::endl;
		return -1;
	}

	m_points.clear();
	m_triangles.clear();

	if(filename.contains(".xyz", Qt::CaseInsensitive))
	{
		//  extension = xyz
		std::cout << "Read point set...";
		unsigned int nb = 0;
		Point point;
		while(ifs >> point)
		{
			m_points.push_back(point);
			nb++;
		}
		std::cout << "done (" << nb << " points)" << std::endl;
	}

	reset_bbox();
	return 0;
}


void Scene::render()
{
	::glDisable(GL_LIGHTING);

	if(m_view_points) 
		render_points();

	if(m_view_edges)
		m_dt.render_edges(1.0f, 128, 128, 128);

	if(m_view_alpha_shape)
		render_alpha_shape();
}

void Scene::render_points()
{
	::glDisable(GL_LIGHTING);
	::glColor3ub(0,0,0);
	::glPointSize(2.0f);

	::glBegin(GL_POINTS);
	std::list<Point>::const_iterator it;
	for(it = m_points.begin();
		it != m_points.end();
		it++)
	{
		const Point& p = *it;
		::glVertex3d(p.x(), p.y(), p.z());
	}
	::glEnd();
}

void Scene::render_alpha_shape()
{
	// render facet edges
	::glEnable(GL_CULL_FACE);
	::glCullFace(GL_BACK);
	::glColor3ub(128, 128, 128);
	::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	::glEnable(GL_LIGHTING);

	::glBegin(GL_TRIANGLES);
	std::list<Triangle>::const_iterator it;
	for(it = m_triangles.begin();
		it != m_triangles.end();
		it++)
	{
		const Triangle& triangle = *it;
		const Point a = triangle[0];
		const Point b = triangle[1];
		const Point c = triangle[2];

		// compute normal
		Vector n = CGAL::cross_product(c-a, b-a);
		n = n / std::sqrt(n*n);

		// draw one front facing
		::glNormal3d(-n.x(), -n.y(), -n.z());
		::glVertex3d(a.x(), a.y(), a.z());
		::glVertex3d(b.x(), b.y(), b.z());
		::glVertex3d(c.x(), c.y(), c.z());

		// and the other back facing
		::glNormal3d(n.x(), n.y(), n.z());
		::glVertex3d(a.x(), a.y(), a.z());
		::glVertex3d(c.x(), c.y(), c.z());
		::glVertex3d(b.x(), b.y(), b.z());

	}
	::glEnd();

	// restore polygon mode
	::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

}

void Scene::set_opacity(const float gamma)
{
	float ambient[]   = {0.0f,0.0f,0.0f,1.0f};
	float diffuse[]   = {0.0f,0.0f,0.0f,1.0f};
	float specular[]  = {0.0f,0.0f,0.0f,1.0f};
	float emission[]  = {0.3f,0.3f,0.3f,1.0f};
	float shininess[] = {0.0f};

	// Ambient
	ambient[0] = 0.19225f;
	ambient[1] = 0.19225f;
	ambient[2] = 0.19225f;
	ambient[3] = 1.0f-gamma;
	// Diffuse
	diffuse[0] = 0.9f;
	diffuse[1] = 0.9f;
	diffuse[2] = 0.9f;
	diffuse[3] = 1.0f-gamma;
	// Specular
	specular[0] = 0.508273f;
	specular[1] = 0.508273f;
	specular[2] = 0.508273f;
	specular[3] = 1.0f;
	// Shininess
	shininess[0] = 50.0f;

	// apply
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,   ambient);
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,   diffuse);
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,  specular);
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION,  emission);
}   


int Scene::compute_alpha_shape(const FT alpha)
{
	// clear and construct Delaunay triangulation
	m_dt.clear();
	std::cout << "Construct Delaunay triangulation...";
	m_dt.insert(m_points.begin(), m_points.end());
	std::cout << "done" << std::endl;

	// compute alpha shape
	m_triangles.clear();
	m_dt.compute_alpha_shape(alpha, std::back_inserter(m_triangles));

	return m_triangles.size(); // return #triangles in alpha shape
}