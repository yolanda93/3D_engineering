#ifndef CLOUD_SEGMENTATION_H
#define CLOUD_SEGMENTATION_H

#include "Polyhedron_Flo.h"
#include "GCoptimization.h"



typedef unsigned char byte;
const double PI = 3.141592;

class Cloud_segmentation
{
	
 
public:

	Polyhedron_Flo mesh;
	double zmin;
	double zmax;
	std::vector < CGAL::Color> vector_colors_classification;
	std::vector < CGAL::Color> vector_colors_plane_extraction;
	std::vector<std::vector<Facet_handle> > list_neighborg_facet;
	std::vector<Facet_iterator> list_facets;



bool init()
{
	int count=0;
	
	zmin=1e7;
	zmax=-1e7;
	for( Polyhedron_Flo::Vertex_iterator vi = mesh.vertices_begin(); vi != mesh.vertices_end(); ++vi, ++count){
		vi->index()=count;
		double z= vi->point().z();
		if(zmin > z) zmin=z;
		if(zmax < z) zmax=z;
	}

	//computation FACET normals
	count = 0;
	list_facets = std::vector<Facet_iterator>(mesh.size_of_facets());

	for (Facet_iterator f = mesh.facets_begin() ; f != mesh.facets_end() ; ++f, ++count)
	{
		list_facets[count] = (f);
		Halfedge_handle
			h1 = f->halfedge(),
			h2 = h1->next(),
			h3 = h2->next();

		//calcul des normals
		Polyhedron_Flo::Vertex_handle
			v1 = h1->vertex(),
			v2 = h2->vertex(),
			v3 = h3->vertex();

		f->center() = Point_Flo(1 / 3 * (v1->point().x() + v2->point().x() + v3->point().x()), 1 / 3 * (v1->point().y() + v2->point().y() + v3->point().y()), 1 / 3 * (v1->point().z() + v2->point().z() + v3->point().z()));
		f->normal() = CGAL::orthogonal_vector(v1->point(), v2->point(), v3->point()) / float(2);
		f->area() = std::max<float>( CGAL::sqrt(f->normal() * f->normal()), 1e-7 );
		f->normal() = f->normal() / f->area();
		f->index()=count;
		f->z()=(v1->point().z() + v2->point().z() + v3->point().z())/3;
	} 


	//Compute neighboring facets
	list_neighborg_facet = std::vector<std::vector<Facet_handle> >(mesh.size_of_facets());

		for (int i = 0; i < mesh.size_of_facets(); i++){
			Facet_iterator f = list_facets[i];
			//get neighbors
			Halfedge_handle
				h1 = f->halfedge(),
				h2 = h1->next(),
				h3 = h2->next();

			//calcul des normals
			std::vector<Polyhedron_Flo::Vertex_handle> vert(3);
			vert[0] = h1->vertex(); vert[1] = h2->vertex(); vert[2] = h3->vertex();

			std::vector<int> index_facet_neighborg;
			std::set<int> index_neighborg_facet;

			bool  is_max_local = false;
			bool  is_min_local = false;
			Halfedge_around_vertex_circulator h0, h;
			for (int j = 0; j < vert.size(); j++)
			{

				h0 = vert[j]->vertex_begin(); h = h0;
				do {
					Facet_handle f1 = h->facet();
					Facet_handle f2 = h->opposite()->facet();
					if (!h->is_border_edge() && f != f1 && f != f2)
					{
						index_neighborg_facet.insert(f1->index());
						index_neighborg_facet.insert(f2->index());
					}
				} while (++h != h0);
			}

			if (!h1->is_border_edge())
				list_neighborg_facet[i].push_back(h1->opposite()->facet());

			if (!h2->is_border_edge())
				list_neighborg_facet[i].push_back(h2->opposite()->facet());

			if (!h3->is_border_edge())
				list_neighborg_facet[i].push_back(h3->opposite()->facet());

			//then the remaining
			for (std::set<int>::iterator it = index_neighborg_facet.begin(); it != index_neighborg_facet.end(); it++)
			{
				list_neighborg_facet[i].push_back(list_facets[(*it)]);
			}
		}
	
	return true;
}
	
bool labeling(double beta)
{


	//Graph creation
	//------------------------------------------------------------------------
	int number_of_class = 3 ;
	int number_nodes = mesh.size_of_facets();
	GCoptimizationGeneralGraph *gc = new GCoptimizationGeneralGraph(number_nodes,number_of_class);
	//------------------------------------------------------------------------




	//Graph adjacency setup
	//------------------------------------------------------------------------
	for (Facet_iterator f = mesh.facets_begin() ; f != mesh.facets_end() ; ++f)
	{
		int index_facet=f->index();
		float weight=beta;

		Halfedge_handle
			h1 = f->halfedge(),
			h2 = f->halfedge()->next(),
			h3 = f->halfedge()->next()->next();

		float
			l1 = h1->length(),
			l2 = h2->length(),
			l3 = h3->length();
			
		if ( !h1->is_border_edge() ){
			int f1_index=h1->opposite()->facet()->index();
			weight=beta;
			gc->setNeighbors(index_facet, f1_index, weight);
		}

		if ( !h2->is_border_edge() ){
			int f2_index=h2->opposite()->facet()->index();
			weight=beta;
			gc->setNeighbors(index_facet, f2_index, weight);
		}

		if ( !h3->is_border_edge() ){
			int f3_index=h3->opposite()->facet()->index();
			weight=beta;
			gc->setNeighbors(index_facet, f3_index, weight);
		}
	}
	//------------------------------------------------------------------------





	//Data term
	//------------------------------------------------------------------------
	float *data = new float[number_nodes*number_of_class];
	Vector_Flo vz(0.,0.,1.);

	for (Facet_iterator f = mesh.facets_begin() ; f != mesh.facets_end() ; ++f)
	{
		int index_facet = f->index();
		
		//-------------- TO FILL IN (START)---------------------
		
		//random :(
		data[index_facet*number_of_class + 0] = (double) rand() / RAND_MAX; //yellow //sol
		data[index_facet*number_of_class + 1] = (double)rand() / RAND_MAX; //blue //roof
		data[index_facet*number_of_class + 2] = (double)rand() / RAND_MAX; //facade white
		//-------------- TO FILL IN (END)---------------------
	}
	gc->setDataCost(data);
	//------------------------------------------------------------------------




	//Potential (pairwise interaction)
	//------------------------------------------------------------------------
	float *smooth = new float[number_of_class*number_of_class];
	for ( int l1 = 0; l1 < number_of_class; l1++ )
	for (int l2 = 0; l2 < number_of_class; l2++){

		//-------------- TO FILL IN (START)---------------------

		// :(
		smooth[l1 + l2*number_of_class] = 0;
		
		//-------------- TO FILL IN (END)---------------------
	}

	gc->setSmoothCost(smooth);
	//------------------------------------------------------------------------





	//Alpha-expansion
	//------------------------------------------------------------------------
	for (int i = 0; i < 2; i++)
		for (int next = 0; next < number_of_class; next++){
			gc->alpha_expansion(next);
			std::cout<<"Cycle "<<i+1<<" : expansion label "<<next+1<<std::endl;
		}
	//------------------------------------------------------------------------





	//Save results and clear strutures
	//------------------------------------------------------------------------
		vector_colors_classification.clear();
		for (Facet_iterator f = mesh.facets_begin() ; f != mesh.facets_end() ; ++f){
		
		int index_facet=f->index();
		f->label() = gc->whatLabel(index_facet); 

		if(f->label()==0) f->color()=CGAL::Color(255,255,150);
		else if(f->label()==1) f->color()=CGAL::Color(120,127,250);
		else f->color()=CGAL::Color(250,230,230);

		vector_colors_classification.push_back(f->color());
	}

	delete gc;
	delete [] smooth;
	delete [] data;
	//------------------------------------------------------------------------
	
	

	return true;
}



void plane_extraction(float angle_max, float area_min)
{

	std::cout << "Region growing:  ";

	std::vector<int> label_region(mesh.size_of_facets(), -1);
	int class_index = -1;

	for (Facet_iterator f = mesh.facets_begin(); f != mesh.facets_end(); ++f)
	{
		if (label_region[f->index()] == -1)
		{
	
			class_index++;
			label_region[f->index()] = class_index;
			double area = f->area();

			//characteristics of the seed
			Vector_Flo normal_seed = f->normal();
			Point_Flo pt_seed = f->center();
			Plane optimal_plane(pt_seed, normal_seed);

			//initialization containers
			std::vector < int > index_container; index_container.push_back(f->index());
			std::vector < int > index_container_former_ring; index_container_former_ring.push_back(f->index());
			std::list < int > index_container_current_ring;

			//propagation
			bool propagation = true;
			do{

				propagation = false;

				for (int k = 0; k<(int)index_container_former_ring.size(); k++){
					
					int point_index = index_container_former_ring[k];
					int count = 0;

					for (std::vector<Facet_handle>::iterator it = list_neighborg_facet[point_index].begin(); it != list_neighborg_facet[point_index].end() && count < 3; it++, count++)
					{
						int neighbor_index = (*it)->index();
						
						//-------------- TO FILL IN (Start)---------------------

						//-------------- TO FILL IN (end)---------------------
					}
				}
			
				//update containers
				index_container_former_ring.clear();
				for (std::list < int >::iterator it = index_container_current_ring.begin(); it != index_container_current_ring.end(); ++it){
					index_container_former_ring.push_back(*it);
					index_container.push_back(*it);
				}
				index_container_current_ring.clear();

			} while (propagation);


			//Test the number of inliers -> reject if inferior to Nmin
			if (area < area_min) {
				class_index--;
				label_region[f->index()] = -1;
				for (int k = 0; k<(int)index_container.size(); k++) label_region[index_container[k]] = -1;
			}

		}
	}
	std::cout << class_index + 1 << "planes detected" << std::endl;

	//display
	vector_colors_plane_extraction.clear();
	std::vector<CGAL::Color> list_colors;
	for (int i = 0; i < class_index + 1;i++){
		int red = (int)floor((double)186 * rand() / RAND_MAX) + 50;
		int green = (int)floor((double)196 * rand() / RAND_MAX) + 40;
		int blue = (int)floor((double)166 * rand() / RAND_MAX) + 70;
		CGAL::Color col(red,green,blue);
		list_colors.push_back(col);
	}

	for (int k = 0; k < label_region.size(); k++){
		if (label_region[k] == -1) vector_colors_plane_extraction.push_back(CGAL::WHITE);
		else vector_colors_plane_extraction.push_back(list_colors[label_region[k]]);
	}

}




};





#endif 