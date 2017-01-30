#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <list>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// CGAL
#include <CGAL/IO/Polyhedron_iostream.h>

#include "types.h"
#include "mesh.h"

#undef CGAL_CFG_NO_CPP0X_VARIADIC_TEMPLATES

class Scene
{

private:

		// input point set
		Bbox m_bbox;
    std::list<Point_d> m_points;

	Mesh   *m_mesh;


		// alpha shape stored as set of transparent facets
		std::list<Triangle> m_triangles;

    // rendering options
    bool m_view_edges;
    bool m_view_points;
	bool m_view_facets;
	bool m_view_vertices;
    
public: // life cycle
    Scene();
    virtual ~Scene();
	//~Scene(){}

	Cloud_segmentation M_original;

		// bbox
    const Bbox& bbox() const { return m_bbox; }
    FT bbox_diag() const;
	void update_bbox(int input_type = 0);
    void reset_bbox();

	void clear(){m_mesh->clear();}

    // file menu
    int open(QString filename);
	int load_mesh(const QString& filename)
	{
		if (filename.contains(".off", Qt::CaseInsensitive))
		{

			Polyhedron_Flo mesh_temp;

			std::ifstream input(qPrintable(filename));
			input >> *m_mesh;	
			input.close();

			cout << "("<<(*m_mesh).size_of_vertices() << " V, "
				<< (*m_mesh).size_of_halfedges() << " H, "
				<< (*m_mesh).size_of_facets() << " F"
				<< ")"<<endl;

			M_original.mesh = Polyhedron_Flo(*m_mesh);
			m_mesh->fit_to_unit_box();			 //m_mesh is for display only
			m_mesh->enumerate_vertices();
			m_mesh->set_grey_color();

			M_original.init();

			//try to also load parameters
			std::string nameini = filename.toStdString();
			nameini.erase(nameini.length() - 4);//remove extention

			return 0;
		}
	//	std::cout << red << "invalid format file (try OFF)" << white << std::endl;
	}
    
    // toggle rendering options
    void toggle_view_edges()    { m_view_edges = !m_view_edges; } 
    void toggle_view_points()  { m_view_points = !m_view_points; } 
   
    // rendering
    void render(); 
    void render_points();
	void set_opacity(const float gamma);

	// algorithms
	void toggle_Classification(double beta);
	void toggle_Plane_Extraction(double m_angle_max, double m_area_min);

};

#endif // SCENE_H
