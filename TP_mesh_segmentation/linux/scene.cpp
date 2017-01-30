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
	m_mesh = new Mesh();

	// view options
	m_view_edges = false;
	m_view_points = true;
	m_view_facets = true;
	m_view_edges = false;
	m_view_vertices = false;
}

Scene::~Scene()
{
	m_mesh->clear();
	delete m_mesh; m_mesh = NULL;
}

FT Scene::bbox_diag() const
{
	double dx = m_bbox.xmax() - m_bbox.xmin();
	double dy = m_bbox.ymax() - m_bbox.ymin();
	double dz = m_bbox.zmax() - m_bbox.zmin();
	return FT(std::sqrt(dx*dx + dy*dy + dz*dz));
}

void Scene::update_bbox(int input_type)
{
	if (input_type == 0){
		reset_bbox();
		if (m_points.size() == 0)
		return;

		std::list<Point_d>::const_iterator it;
		for (it = m_points.begin(); it != m_points.end(); it++)
			m_bbox = m_bbox + it->bbox();
	}
	else{
		m_bbox = Bbox(-1., -1., -1., 1., 1., 1.);
	}

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
		Point_d point;
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

	float line_width = 1.;
	float point_size = 1.;

	if(m_view_points) 
		render_points();

	if (m_view_facets)
		m_mesh->draw_facets();
		//m_mesh->draw_facets_fromCGALColor();

	if (m_view_edges)
		m_mesh->draw_edges(line_width, 0.0f, 0.0f, 0.0f);

	if (m_view_vertices)
		m_mesh->draw_points(point_size, 0.0f, 0.0f, 0.0f);
}



void Scene::render_points()
{
	::glDisable(GL_LIGHTING);
	::glColor3ub(0,0,0);
	::glPointSize(2.0f);

	::glBegin(GL_POINTS);
	std::list<Point_d>::const_iterator it;
	for(it = m_points.begin();
		it != m_points.end();
		it++)
	{
		const Point_d& p = *it;
		::glVertex3d(p.x(), p.y(), p.z());
	}
	::glEnd();
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

void Scene::toggle_Classification(double beta){
	M_original.labeling(beta);
	m_mesh->set_colors(M_original.vector_colors_classification);
}

void Scene::toggle_Plane_Extraction(double angle_max, double area_min){
	M_original.plane_extraction(angle_max,area_min);
	m_mesh->set_colors(M_original.vector_colors_plane_extraction);

}

