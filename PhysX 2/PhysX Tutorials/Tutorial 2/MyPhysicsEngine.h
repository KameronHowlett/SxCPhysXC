#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f)};

	//pyramid vertices
	static PxVec3 pyramid_verts[] = {PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1)};
	static PxVec3 wedge_verts[] = {PxVec3(-1,0,1),PxVec3(1,0,1), PxVec3(-1,1,1), PxVec3(1,1,1), PxVec3(-1,0,-1), PxVec3(1,0,-1) };
	static PxVec3 rectangle_verts[] = { PxVec3(-1,0,1),PxVec3(-1,0,-2), PxVec3(-1,1,1), PxVec3(1,1,1), PxVec3(-1,1,-2), PxVec3(1,0,-2), PxVec3(1,0,1), PxVec3(1,1,-2) };
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxReal density=1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), pose, density)
		{
		}
	};

	class rectangle : public ConvexMesh
	{
	public:
		rectangle(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(rectangle_verts), end(rectangle_verts)), pose, density)
		{
		}
	};

	class wedge : public ConvexMesh
	{
	public:
		wedge(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(wedge_verts), end(wedge_verts)), pose, density)
		{
		}
	};

	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose=PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs),end(pyramid_trigs)), pose)
		{
		}
	};

	///Custom scene class
	class MyScene : public Scene
	{
		Plane* plane;
		Box* box[2];
		Sphere* sphere[6];
		CompoundObject* boxs;
		wedge* pyr;
		rectangle* rec[2];

	public:
		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			GetMaterial()->setDynamicFriction(.2f);

			plane = new Plane();
			plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));
			Add(plane);

			sphere[3] = new Sphere(PxTransform(PxVec3(-5.f, 20.f, .0f)));
			sphere[3]->Color(PxVec3(0.01, 0.46, 0.35));
			sphere[3]->Material(GetMaterial(0));

			sphere[1] = new Sphere(PxTransform(PxVec3(.0f, 20.f, .0f)));
			sphere[1]->Color(PxVec3(0.60, 0.01, 0.35));
			sphere[1]->Material(GetMaterial(1));

			sphere[2] = new Sphere(PxTransform(PxVec3(5.f, 20.f, .0f)));
			sphere[2]->Color(PxVec3(0.60, 0.46, 0.01));
			sphere[2]->Material(GetMaterial(2));

			box[1] = new Box(PxTransform(PxVec3(.1f,10.f,.0f)));
			box[1]->Color(PxVec3(0.233f, 0.225f, 0.206f));
			
			box[2] = new Box(PxTransform(PxVec3(.2f, 5.f, .0f)));
			box[2]->Color(PxVec3(0.138f, 0.146f, 0.163f));
			
			boxs = new CompoundObject(PxTransform(PxVec3(5.f, .0f, .0f),PxQuat(1.5708f, PxVec3(.1f, .1f, 1.f))));
			boxs->Color(PxVec3(0.1f, 0.5f, 0.1f));

			pyr = new wedge(PxTransform(PxVec3(-3.f, .0f, .0f),PxQuat(3.f, PxVec3(.1f, 1.f, .1f))));
			pyr->Color(color_palette[3]);

			rec[0] = new rectangle(PxTransform(PxVec3(.0f, 1.f, -4.f), PxQuat(0.785398f, PxVec3(.1f, .1f, 1.f))));
			rec[0]->Color(color_palette[4]);

			rec[1] = new rectangle(PxTransform(PxVec3(.0f, .0f, -4.f)));
			rec[1]->Color(color_palette[4]);

			Add(sphere[1]);
			Add(box[1]);
			Add(box[2]);
			Add(boxs);
			Add(pyr);
			Add(rec[0]);
			Add(rec[1]);
			Add(sphere[3]);
			Add(sphere[2]);
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
		}
	};
}
