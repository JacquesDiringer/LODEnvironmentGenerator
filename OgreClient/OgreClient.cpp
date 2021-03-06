// OgreClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "OgreClient.h"
#include "Displayable.h"
#include "SimpleObjectDisplayable.h"
#include "Item.h"
#include "SceneGraphManager.h"
#include "Matrix4.h"
#include "LevelFactory.h"
#include "SimpleObjectFactory.h"
#include "ComplexObjectFactory.h"
#include "RandomObjectFactory.h"
#include "TransformationFactory.h"
#include "NeighborDensityFactory.h"
#include "ArrayFactory.h"

#include "FloatExpression.h"
#include "LinearFunctionExpression.h"
#include "LinearCombinationExpression.h"
#include "MultiplicationExpression.h"
#include "CosExpression.h"
#include "AABExpression.h"
#include "BooleanOperatorExpression.h"

#include "DependenceTreeDataModel.h"

using std::vector;

OgreClient::OgreClient(void)
{
	_timeSinceLastUpdate = 0;

	_threadInitialized = false;

}

OgreClient::~OgreClient(void)
{

}

void InitializeQuaternionTestScene(SceneGraphManager* sceneManager)
{
	SimpleObjectFactory* subLevelFactory = new SimpleObjectFactory("building0_topFloor.mesh", "building0_topEdge.PNG", 5.0f, NULL);
	SimpleObjectFactory* subLevelFactory2 = new SimpleObjectFactory("road0.mesh", "road0_tex0.PNG", 2.0f, NULL);
	//SimpleObjectFactory* subLevelFactory3 = new SimpleObjectFactory("A_Brick.mesh", "debug_texture.png", 2.0f, NULL);
	SimpleObjectFactory* subLevelFactory3 = new SimpleObjectFactory("Arrows_1_unit.mesh", "RGB.jpg", 2.0f, NULL);

	// Test factories

	SimpleObjectFactory* BBrickFactory = new SimpleObjectFactory("B_Brick.mesh", "debug_texture.png", 3.0f, subLevelFactory2);

	ComplexObjectFactory* fourSplitFactory = new ComplexObjectFactory();
	fourSplitFactory->AddComposerFactory(new TransformationFactory(subLevelFactory3, Math::Matrix4(Math::Vector3(0, 0, 0))));
	fourSplitFactory->AddComposerFactory(new TransformationFactory(subLevelFactory3, Math::Matrix4(Math::Vector3(0, 1, 0))));


	SimpleObjectFactory* ABrickFactory = new SimpleObjectFactory("A_Brick.mesh", "debug_texture.png", 5.0f, fourSplitFactory);

	ComplexObjectFactory* eightSplitFactory = new ComplexObjectFactory();
	eightSplitFactory->AddComposerFactory(new TransformationFactory(subLevelFactory3, Math::Matrix4(Math::Vector3(0, 0, 0))));
	eightSplitFactory->AddComposerFactory(new TransformationFactory(subLevelFactory3, Math::Matrix4(Math::Vector3(0, 1, 0))));
	eightSplitFactory->AddComposerFactory(new TransformationFactory(subLevelFactory3, Math::Matrix4::Multiply(Math::Matrix4::CreateRotationY(90.0f), Math::Matrix4(Math::Vector3(0, 2, 0)))));

	RandomObjectFactory* randomFactory = new RandomObjectFactory();
	randomFactory->AddAlternativeFactory(0.3f, subLevelFactory2);
	randomFactory->AddAlternativeFactory(0.2f, eightSplitFactory);
	randomFactory->AddAlternativeFactory(0.2f, fourSplitFactory);

	// Flat array
	vector<Item*> itemsToAdd = vector<Item*>();
	for (int i = 0; i < 1; i += 1)
	{
		for (int j = 0; j < 1; j += 1)
		{
			for (int k = 0; k < 5; k += 5)
			{
				shared_ptr<SimpleObjectDisplayable> object0 = make_shared<SimpleObjectDisplayable>("building0_topFloor.mesh", "building0_topEdge.PNG");
				Item* item0 = new Item(Math::Matrix4(Math::Vector3(i, k, j)), shared_ptr<Item>(), 60.0f, object0, randomFactory);
				item0->SetId(10 * i + j);
				itemsToAdd.push_back(item0);
			}
		}
	}

	shared_ptr<SimpleObjectDisplayable> object0 = make_shared<SimpleObjectDisplayable>("building0_topFloor.mesh", "building0_topEdge.PNG");
	shared_ptr<Item> item0 = std::make_shared<Item>(Math::Matrix4(Math::Vector3(0, 0, 0)), shared_ptr<Item>(), 60.0f, vector<Math::ParametricPlane*>(), false, object0, eightSplitFactory);
	item0->SetId(10);
	sceneManager->QueueAddItem(item0);
}


void InitializeAsianBuildingsTestScene(SceneGraphManager* sceneManager)
{
	// Level 5

	// Sustainers
	SimpleObjectFactory level5_sustainer0test = SimpleObjectFactory("level5_sustainer0.mesh", "metal_atlas.jpg", 0, NULL);
	SimpleObjectFactory* level5_sustainer0 = new SimpleObjectFactory("level5_sustainer0.mesh", "metal_atlas.jpg", 0, NULL);
	SimpleObjectFactory* level5_sustainer1 = new SimpleObjectFactory("level5_sustainer1.mesh", "metal_atlas.jpg", 0, NULL);

	RandomObjectFactory* bool_sustainer1 = new RandomObjectFactory();
	bool_sustainer1->AddAlternativeFactory(1.0f, level5_sustainer1);
	bool_sustainer1->AddAlternativeFactory(3.0f, NULL);

	RandomObjectFactory* random_sustainer = new RandomObjectFactory();
	random_sustainer->AddAlternativeFactory(1.0f, level5_sustainer0);
	random_sustainer->AddAlternativeFactory(1.0f, level5_sustainer1);


	//Climatisers
	SimpleObjectFactory* level5_climatiser0 = new SimpleObjectFactory("level5_climatiser0.mesh", "metal_atlas.jpg", 0, NULL);
	SimpleObjectFactory* level5_climatiser1 = new SimpleObjectFactory("level5_climatiser1.mesh", "metal_atlas.jpg", 0, NULL);

	RandomObjectFactory* randomClimatiser = new RandomObjectFactory();
	randomClimatiser->AddAlternativeFactory(1.0f, level5_climatiser0);
	randomClimatiser->AddAlternativeFactory(1.0f, level5_climatiser1);

	ComplexObjectFactory* level5_complex_climatiser = new ComplexObjectFactory();
	level5_complex_climatiser->AddComposerFactory(randomClimatiser);
	level5_complex_climatiser->AddComposerFactory(new TransformationFactory(random_sustainer, Math::Matrix4(Math::Vector3(-0.17123f, -0.19159f, 0.00415f))));
	level5_complex_climatiser->AddComposerFactory(new TransformationFactory(random_sustainer, Math::Matrix4(Math::Vector3( 0.17123f, -0.19159f, 0.00415f))));


	// Antena
	SimpleObjectFactory* level5_antena = new SimpleObjectFactory("level5_antena.mesh", "metal_atlas.jpg", 0, NULL);
	ComplexObjectFactory* level5_complex_antena = new ComplexObjectFactory();
	level5_complex_antena->AddComposerFactory(level5_antena);
	level5_complex_antena->AddComposerFactory(bool_sustainer1);
	level5_complex_antena->AddComposerFactory(new TransformationFactory(random_sustainer, Math::Matrix4(Math::Vector3(0.0f, -0.36388f, -0.38716f))));

	// Grid
	SimpleObjectFactory* level5_grid = new SimpleObjectFactory("level5_grid.mesh", "metal_atlas.jpg", 0, NULL);
	ComplexObjectFactory* level5_complex_grid = new ComplexObjectFactory();
	level5_complex_grid->AddComposerFactory(level5_grid);
	level5_complex_grid->AddComposerFactory(new TransformationFactory(random_sustainer, Math::Matrix4(Math::Vector3(-0.88259f, 0.0f, 0.0f))));
	level5_complex_grid->AddComposerFactory(new TransformationFactory(random_sustainer, Math::Matrix4(Math::Vector3(0.88259f, 0.0f, 0.0f))));


	// Level 4 //
	// Base SimpleObjects
	SimpleObjectFactory* level4_single_window = new SimpleObjectFactory("level4_single_window.mesh", "level4_single_window2.PNG", 0, NULL);
	SimpleObjectFactory* level4_climatiser = new SimpleObjectFactory("level4_climatiser.mesh", "metal_atlas.jpg", 20, level5_complex_climatiser);
	SimpleObjectFactory* level4_antena = new SimpleObjectFactory("level4_antena.mesh", "metal_atlas.jpg", 20, level5_complex_antena);
	SimpleObjectFactory* level4_grid = new SimpleObjectFactory("level4_grid.mesh", "metal_atlas.jpg", 20, level5_complex_grid);

	// Random Climatiser
	RandomObjectFactory* bool_climatiser = new RandomObjectFactory();
	bool_climatiser->AddAlternativeFactory(1.0f, level4_climatiser);
	bool_climatiser->AddAlternativeFactory(1.0f, NULL);

	// Random Antena
	RandomObjectFactory* bool_antena = new RandomObjectFactory();
	bool_antena->AddAlternativeFactory(1.0f, level4_antena);
	bool_antena->AddAlternativeFactory(1.0f, NULL);

	// Random Grid
	RandomObjectFactory* bool_grid = new RandomObjectFactory();
	bool_grid->AddAlternativeFactory(1.0f, level4_grid);
	bool_grid->AddAlternativeFactory(10.0f, NULL);

	// Randow window filler
	RandomObjectFactory* random_window_filler = new RandomObjectFactory();
	random_window_filler->AddAlternativeFactory(3.0f, level4_climatiser);
	random_window_filler->AddAlternativeFactory(1.0f, bool_antena);
	random_window_filler->AddAlternativeFactory(30.0f, NULL);

	ComplexObjectFactory* level4_single_complexWindow = new ComplexObjectFactory();
	level4_single_complexWindow->AddComposerFactory(new TransformationFactory(level4_single_window, Math::Matrix4(Math::Vector3(0, 0, 0))));
	level4_single_complexWindow->AddComposerFactory(new TransformationFactory(random_window_filler, Math::Matrix4(Math::Vector3(0.70094f, 0.06841f, 0.09186f))));
	level4_single_complexWindow->AddComposerFactory(new TransformationFactory(random_window_filler, Math::Matrix4(Math::Vector3(0.70094f, 0.5f, 0.09186f))));
	level4_single_complexWindow->AddComposerFactory(new TransformationFactory(random_window_filler, Math::Matrix4(Math::Vector3(0.70094f, 1.0f, 0.09186f))));
	level4_single_complexWindow->AddComposerFactory(new TransformationFactory(random_window_filler, Math::Matrix4(Math::Vector3(-0.6281f, 0.76699f, 0.36626f))));
	level4_single_complexWindow->AddComposerFactory(new TransformationFactory(bool_grid, Math::Matrix4(Math::Vector3(0.0f, -0.63684f, 0.12538f))));

	// Corners
	SimpleObjectFactory* level4_single_corner = new SimpleObjectFactory("level4_single_corner.mesh", "level4_single_corner2.png", 0, NULL);



	// Level 3
	// Walls
	ComplexObjectFactory* level4_25_windows_batch = new ComplexObjectFactory();
	float width = 2.0f;
	float height = 2.5f;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Math::Matrix4 currentMat = Math::Matrix4(Math::Vector3((i - 2.0f)*width, (j - 2.0f)*height, 0));
			level4_25_windows_batch->AddComposerFactory(new TransformationFactory(level4_single_complexWindow, currentMat));
		}
	}

	SimpleObjectFactory* level3_25_windows = new SimpleObjectFactory("level3_25_windows.mesh", "25_windows.PNG", 30, level4_25_windows_batch);

	// Corners
	ComplexObjectFactory* level4_5_corners_batch = new ComplexObjectFactory();
	width = 2.0f;
	height = 2.5f;
	
	for (int j = 0; j < 5; j++)
	{
		Math::Matrix4 currentMat = Math::Matrix4(Math::Vector3(0, (j - 2.0f)*height, 0));
		level4_5_corners_batch->AddComposerFactory(new TransformationFactory(level4_single_corner, currentMat));
	}

	SimpleObjectFactory* level3_5_corners = new SimpleObjectFactory("level3_5_corners.mesh", "5_corners.png", 30, level4_5_corners_batch);

	ComplexObjectFactory* level3_2_5_corners_batch = new ComplexObjectFactory();
	level3_2_5_corners_batch->AddComposerFactory(new TransformationFactory(level3_5_corners, Math::Matrix4(Math::Vector3(0, -6.25f, 0))));
	level3_2_5_corners_batch->AddComposerFactory(new TransformationFactory(level3_5_corners, Math::Matrix4(Math::Vector3(0, 6.25f, 0))));

	// Level 2
	ComplexObjectFactory* level3_25_25_windows_batch = new ComplexObjectFactory();
	width = 10.0f;
	height = 12.5f;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Math::Matrix4 currentMat = Math::Matrix4(Math::Vector3((i - 2.0f)*width, (j - 2.0f)*height, 0));
			level3_25_25_windows_batch->AddComposerFactory(new TransformationFactory(level3_25_windows, currentMat));
		}
	}

	ComplexObjectFactory* level3_4_25_windows_batch = new ComplexObjectFactory();
	width = 10.0f;
	height = 12.5f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Math::Matrix4 currentMat = Math::Matrix4(Math::Vector3((i - 0.5f)*width, (j - 0.5f)*height, 0));
			level3_4_25_windows_batch->AddComposerFactory(new TransformationFactory(level3_25_windows, currentMat));
		}
	}

	
	Math::Matrix4 quarterRotation = Math::Matrix4::CreateRotationY(90);
	Math::Matrix4 halfRotation = Math::Matrix4::CreateRotationY(180);
	Math::Matrix4 threeQuarterRotation = Math::Matrix4::CreateRotationY(270);

	ComplexObjectFactory* level3_smallBuilding = new ComplexObjectFactory();
	float floorHeight = 20.0f;
	for (float floorLevel = 0; floorLevel < 3; floorLevel++)
	{
		// Add the walls to the small building
		level3_smallBuilding->AddComposerFactory(new TransformationFactory(level3_4_25_windows_batch, Math::Matrix4(Math::Vector3(0, floorHeight * floorLevel, 12))));
		level3_smallBuilding->AddComposerFactory(new TransformationFactory(level3_4_25_windows_batch, Math::Matrix4::Multiply(quarterRotation, Math::Matrix4(Math::Vector3(0, floorHeight * floorLevel, 12)))));
		level3_smallBuilding->AddComposerFactory(new TransformationFactory(level3_4_25_windows_batch, Math::Matrix4::Multiply(halfRotation, Math::Matrix4(Math::Vector3(0, floorHeight * floorLevel, 12)))));
		level3_smallBuilding->AddComposerFactory(new TransformationFactory(level3_4_25_windows_batch, Math::Matrix4::Multiply(threeQuarterRotation, Math::Matrix4(Math::Vector3(0, floorHeight * floorLevel, 12)))));
		// Add the corners to the small building
		level3_smallBuilding->AddComposerFactory(new TransformationFactory(level3_2_5_corners_batch, Math::Matrix4(Math::Vector3(12, floorHeight * floorLevel, 12))));
		level3_smallBuilding->AddComposerFactory(new TransformationFactory(level3_2_5_corners_batch, Math::Matrix4::Multiply(quarterRotation, Math::Matrix4(Math::Vector3(12, floorHeight * floorLevel, 12)))));
		level3_smallBuilding->AddComposerFactory(new TransformationFactory(level3_2_5_corners_batch, Math::Matrix4::Multiply(halfRotation, Math::Matrix4(Math::Vector3(12, floorHeight * floorLevel, 12)))));
		level3_smallBuilding->AddComposerFactory(new TransformationFactory(level3_2_5_corners_batch, Math::Matrix4::Multiply(threeQuarterRotation, Math::Matrix4(Math::Vector3(12, floorHeight * floorLevel, 12)))));
	}


	SimpleObjectFactory* level2_5_25_windows = new SimpleObjectFactory("level2_5_25_windows.mesh", "25_windows.PNG", 100, level3_25_25_windows_batch);

	ComplexObjectFactory* buildingsBlock = new ComplexObjectFactory();
	width = 50.0f;
	height = 50.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			buildingsBlock->AddComposerFactory(new TransformationFactory(level3_smallBuilding, Math::Matrix4(Math::Vector3((i - 5) * width, 0, (j - 5) * height))));
		}
	}

	shared_ptr<SimpleObjectDisplayable> object0 = make_shared<SimpleObjectDisplayable>("building0_topFloor.mesh", "building0_topEdge.PNG");
	shared_ptr<Item> item0 = std::make_shared<Item>(Math::Matrix4(Math::Vector3(0, 0, 0)), shared_ptr<Item>(), 1000.0f, vector<Math::ParametricPlane*>(), false, object0, buildingsBlock);
	item0->SetId(10);
	sceneManager->QueueAddItem(item0);

	// Level 1
	//SimpleObjectFactory* level1_mainFrame = new SimpleObjectFactory("level1_mainFrame.mesh", "");

}

void InitializerArrayVoxelTestScene(SceneGraphManager* sceneManager)
{
	SimpleObjectFactory* testCubeA = new SimpleObjectFactory("A_Brick.mesh", "1d_debug.png", 0, NULL);

	ArrayFactory* arrayFactory = new ArrayFactory(10, 4, 10, Math::Vector3(1.1f, 2, 1.1f), true, testCubeA);

	shared_ptr<SimpleObjectDisplayable> object0 = make_shared<SimpleObjectDisplayable>("A_Brick.mesh", "debug_texture.png");
	shared_ptr<Item> item0 = std::make_shared<Item>(Math::Matrix4(Math::Vector3(0, 0, 0)), shared_ptr<Item>(), 1000.0f, vector<Math::ParametricPlane*>(), false, object0, arrayFactory);
	item0->SetId(10);
	sceneManager->QueueAddItem(item0);
}

void InitializerVoxelTestScene(SceneGraphManager* sceneManager)
{
	SimpleObjectFactory* testCubeA = new SimpleObjectFactory("A_Brick.mesh", "1d_debug.png", 0, NULL);
	SimpleObjectFactory* testCubeB = new SimpleObjectFactory("B_Brick.mesh", "1d_debug.png", 0, NULL);


	SimpleObjectFactory* building0_wall0 = new SimpleObjectFactory("building0_wall.mesh", "building0_wall_tex1.PNG", 0, NULL);
	SimpleObjectFactory* building0_wall1 = new SimpleObjectFactory("building0_wall1.mesh", "building0_corner_tex1.PNG", 10, testCubeA);
	SimpleObjectFactory* building0_wall2 = new SimpleObjectFactory("building0_wall2.mesh", "building0_wall_tex1.PNG", 0, NULL);

	RandomObjectFactory* building0_wall = new RandomObjectFactory();
	building0_wall->AddAlternativeFactory(5.0f, building0_wall0);
	building0_wall->AddAlternativeFactory(1.0f, building0_wall1);
	building0_wall->AddAlternativeFactory(5.0f, building0_wall2);


	SimpleObjectFactory* building0_corner = new SimpleObjectFactory("building0_corner.mesh", "building0_corner_tex1.PNG", 0, NULL);
	SimpleObjectFactory* building0_innerCorner = new SimpleObjectFactory("building0_innerCorner.mesh", "building0_corner_tex1.PNG", 0, NULL);

	SimpleObjectFactory* building0_topFloor = new SimpleObjectFactory("building0_topFloor.mesh", "building0_topEdge.PNG", 0, NULL);
	SimpleObjectFactory* building0_topEdge = new SimpleObjectFactory("building0_topEdge.mesh", "building0_topEdge.PNG", 0, NULL);
	SimpleObjectFactory* building0_topCorner = new SimpleObjectFactory("building0_topCorner.mesh", "building0_topEdge.PNG", 0, NULL);
	SimpleObjectFactory* building0_topInnerCorner = new SimpleObjectFactory("building0_topInnerCorner.mesh", "building0_topEdge.PNG", 0, NULL);

	SimpleObjectFactory* building0_specificCorner1 = new SimpleObjectFactory("building0_specificCorner1.mesh", "building0_topEdge.PNG", 0, NULL);
	SimpleObjectFactory* building0_specificCorner1Symetry = new SimpleObjectFactory("building0_specificCorner1Symetry.mesh", "building0_topEdge.PNG", 0, NULL);
	SimpleObjectFactory* building0_specificCorner0 = new SimpleObjectFactory("building0_specificCorner0.mesh", "building0_topEdge.PNG", 0, NULL);
	SimpleObjectFactory* building0_specificCorner0Symetry = new SimpleObjectFactory("building0_specificCorner0Symetry.mesh", "building0_topEdge.PNG", 0, NULL);

	SimpleObjectFactory* building0_floorToWall = new SimpleObjectFactory("building0_floorToWall.mesh", "building0_topEdge.PNG", 0, NULL);
	SimpleObjectFactory* building0_floorToWallCorner = new SimpleObjectFactory("building0_floorToWallCorner.mesh", "building0_topEdge.PNG", 0, NULL);
	SimpleObjectFactory* building0_floorToWallInnerCorner = new SimpleObjectFactory("building0_floorToWallInnerCorner.mesh", "building0_corner_tex1.PNG", 0, NULL);
	
	

	SimpleObjectFactory* single_window = new SimpleObjectFactory("level4_single_window.mesh", "level4_single_window2.PNG", 0, NULL);
#pragma region Rules declaration

	Math::LinearFunctionExpression* xExpression = new Math::LinearFunctionExpression(Math::Vector3(0.1f, 0.05f, 0));
	Math::LinearFunctionExpression* yExpression = new Math::LinearFunctionExpression(Math::Vector3(0.0f, 1, 0.4f));
	Math::CosExpression* cosExpression = new Math::CosExpression(xExpression);
	Math::LinearCombinationExpression* combinationExpression = new Math::LinearCombinationExpression(yExpression, cosExpression, -1, 10);

	Math::AABExpression* boxExpression = new Math::AABExpression(Math::Vector3(0, 0, 0), Math::Vector3(8, 15, 16), true);
	Math::AABExpression* boxExpression2 = new Math::AABExpression(Math::Vector3(0, 0, 0), Math::Vector3(40, 5, 3), true);

	Math::BooleanOperatorExpression* boolExpression0 = new Math::BooleanOperatorExpression(boxExpression, boxExpression2, Math::BooleanOperatorType::Xor);

	Math::LinearCombinationExpression* boxCombinationExpression = new Math::LinearCombinationExpression(boxExpression, boxExpression2, 1, -1);

	NeighborDensityFactory* testVoxelFactory = new NeighborDensityFactory(Math::Vector3(1.0f, 1.0f, 1.0f), boolExpression0, 0.5f);
	vector<bool> conditionsWall = vector<bool>();
	conditionsWall.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsWall.push_back(true);			 //(-0.5f, 0.5f, -0.5f),
	conditionsWall.push_back(true);		 //(0.5f, -0.5f, -0.5f),
	conditionsWall.push_back(true);		 //(0.5f, 0.5f, -0.5f),

	conditionsWall.push_back(false);			 //(-0.5f, -0.5f, 0.5f),
	conditionsWall.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsWall.push_back(false);		 //(0.5f, -0.5f, 0.5f),
	conditionsWall.push_back(false);		 //(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsWall, building0_wall);


	vector<bool> conditionsCorner = vector<bool>();
	conditionsCorner.push_back(false);			 //(-0.5f, -0.5f, -0.5f),
	conditionsCorner.push_back(false);			 //(-0.5f, 0.5f, -0.5f),
	conditionsCorner.push_back(false);			//(0.5f, -0.5f, -0.5f),
	conditionsCorner.push_back(false);			//(0.5f, 0.5f, -0.5f),
	
	conditionsCorner.push_back(true);			 //(-0.5f, -0.5f, 0.5f),
	conditionsCorner.push_back(true);			 //(-0.5f, 0.5f, 0.5f),
	conditionsCorner.push_back(false);			//(0.5f, -0.5f, 0.5f),
	conditionsCorner.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsCorner, building0_corner);


	vector<bool> conditionsInnerCorner = vector<bool>();
	conditionsInnerCorner.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsInnerCorner.push_back(true);			 //(-0.5f, 0.5f, -0.5f),
	conditionsInnerCorner.push_back(true);			//(0.5f, -0.5f, -0.5f), V
	conditionsInnerCorner.push_back(true);			//(0.5f, 0.5f, -0.5f), V

	conditionsInnerCorner.push_back(false);			 //(-0.5f, -0.5f, 0.5f),
	conditionsInnerCorner.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsInnerCorner.push_back(true);			//(0.5f, -0.5f, 0.5f),
	conditionsInnerCorner.push_back(true);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsInnerCorner, building0_innerCorner);


	vector<bool> conditionsFloor = vector<bool>();
	conditionsFloor.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsFloor.push_back(false);			 //(-0.5f, 0.5f, -0.5f),
	conditionsFloor.push_back(true);			//(0.5f, -0.5f, -0.5f),
	conditionsFloor.push_back(false);			//(0.5f, 0.5f, -0.5f),

	conditionsFloor.push_back(true);			 //(-0.5f, -0.5f, 0.5f),
	conditionsFloor.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsFloor.push_back(true);			//(0.5f, -0.5f, 0.5f),
	conditionsFloor.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsFloor, building0_topFloor);


	vector<bool> conditionsTopEdge = vector<bool>();
	conditionsTopEdge.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsTopEdge.push_back(false);			 //(-0.5f, 0.5f, -0.5f),
	conditionsTopEdge.push_back(true);			//(0.5f, -0.5f, -0.5f),
	conditionsTopEdge.push_back(false);			//(0.5f, 0.5f, -0.5f),

	conditionsTopEdge.push_back(false);			 //(-0.5f, -0.5f, 0.5f),
	conditionsTopEdge.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsTopEdge.push_back(false);			//(0.5f, -0.5f, 0.5f),
	conditionsTopEdge.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsTopEdge, building0_topEdge);


	vector<bool> conditionsTopCorner = vector<bool>();
	conditionsTopCorner.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsTopCorner.push_back(false);			 //(-0.5f, 0.5f, -0.5f),
	conditionsTopCorner.push_back(false);			//(0.5f, -0.5f, -0.5f),
	conditionsTopCorner.push_back(false);			//(0.5f, 0.5f, -0.5f),
	
	conditionsTopCorner.push_back(false);			 //(-0.5f, -0.5f, 0.5f),
	conditionsTopCorner.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsTopCorner.push_back(false);			//(0.5f, -0.5f, 0.5f),
	conditionsTopCorner.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsTopCorner, building0_topCorner);


	vector<bool> conditionsTopInnerCorner = vector<bool>();
	conditionsTopInnerCorner.push_back(true);			 //(-0.5f, -0.5f, -0.5f), V
	conditionsTopInnerCorner.push_back(false);			 //(-0.5f, 0.5f, -0.5f),
	conditionsTopInnerCorner.push_back(true);			//(0.5f, -0.5f, -0.5f), V
	conditionsTopInnerCorner.push_back(false);			//(0.5f, 0.5f, -0.5f),

	conditionsTopInnerCorner.push_back(false);			 //(-0.5f, -0.5f, 0.5f),
	conditionsTopInnerCorner.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsTopInnerCorner.push_back(true);			//(0.5f, -0.5f, 0.5f),
	conditionsTopInnerCorner.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsTopInnerCorner, building0_topInnerCorner);


	//vector<bool> conditionsBottonEdge = vector<bool>();
	//conditionsBottonEdge.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	//conditionsBottonEdge.push_back(true);			 //(-0.5f, 0.5f, -0.5f),
	//conditionsBottonEdge.push_back(true);			//(0.5f, -0.5f, -0.5f),
	//conditionsBottonEdge.push_back(true);			//(0.5f, 0.5f, -0.5f),
	//
	//conditionsBottonEdge.push_back(true);			 //(-0.5f, -0.5f, 0.5f),
	//conditionsBottonEdge.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	//conditionsBottonEdge.push_back(true);			//(0.5f, -0.5f, 0.5f),
	//conditionsBottonEdge.push_back(false);			//(0.5f, 0.5f, 0.5f),

	vector<bool> conditionsBottonEdge = vector<bool>();
	conditionsBottonEdge.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsBottonEdge.push_back(true);			 //(-0.5f, 0.5f, -0.5f),
	conditionsBottonEdge.push_back(true);			//(0.5f, -0.5f, -0.5f),
	conditionsBottonEdge.push_back(false);			//(0.5f, 0.5f, -0.5f),

	conditionsBottonEdge.push_back(true);			 //(-0.5f, -0.5f, 0.5f),
	conditionsBottonEdge.push_back(true);			 //(-0.5f, 0.5f, 0.5f),
	conditionsBottonEdge.push_back(true);			//(0.5f, -0.5f, 0.5f),
	conditionsBottonEdge.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsBottonEdge, building0_floorToWall);


	vector<bool> conditionsSpecificCorner1 = vector<bool>();
	conditionsSpecificCorner1.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsSpecificCorner1.push_back(false);			 //(-0.5f, 0.5f, -0.5f),
	conditionsSpecificCorner1.push_back(true);			//(0.5f, -0.5f, -0.5f),
	conditionsSpecificCorner1.push_back(true);			//(0.5f, 0.5f, -0.5f),
	
	conditionsSpecificCorner1.push_back(false);			 //(-0.5f, -0.5f, 0.5f),
	conditionsSpecificCorner1.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsSpecificCorner1.push_back(false);			//(0.5f, -0.5f, 0.5f),
	conditionsSpecificCorner1.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsSpecificCorner1, building0_specificCorner1);


	vector<bool> conditionsSpecificCorner1Symetry = vector<bool>();
	conditionsSpecificCorner1Symetry.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsSpecificCorner1Symetry.push_back(true);			 //(-0.5f, 0.5f, -0.5f),
	conditionsSpecificCorner1Symetry.push_back(true);			//(0.5f, -0.5f, -0.5f),
	conditionsSpecificCorner1Symetry.push_back(false);			//(0.5f, 0.5f, -0.5f),

	conditionsSpecificCorner1Symetry.push_back(false);			 //(-0.5f, -0.5f, 0.5f),
	conditionsSpecificCorner1Symetry.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsSpecificCorner1Symetry.push_back(false);			//(0.5f, -0.5f, 0.5f),
	conditionsSpecificCorner1Symetry.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsSpecificCorner1Symetry, building0_specificCorner1Symetry);


	vector<bool> conditionsSpecificCorner0 = vector<bool>();
	conditionsSpecificCorner0.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsSpecificCorner0.push_back(false);			 //(-0.5f, 0.5f, -0.5f),
	conditionsSpecificCorner0.push_back(true);			//(0.5f, -0.5f, -0.5f),
	conditionsSpecificCorner0.push_back(true);			//(0.5f, 0.5f, -0.5f),

	conditionsSpecificCorner0.push_back(false);			 //(-0.5f, -0.5f, 0.5f),
	conditionsSpecificCorner0.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsSpecificCorner0.push_back(true);			//(0.5f, -0.5f, 0.5f),
	conditionsSpecificCorner0.push_back(true);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsSpecificCorner0, building0_specificCorner0);


	vector<bool> conditionsSpecificCorner0Sysmetry = vector<bool>();
	conditionsSpecificCorner0Sysmetry.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsSpecificCorner0Sysmetry.push_back(true);			 //(-0.5f, 0.5f, -0.5f),
	conditionsSpecificCorner0Sysmetry.push_back(true);			//(0.5f, -0.5f, -0.5f), V
	conditionsSpecificCorner0Sysmetry.push_back(false);			//(0.5f, 0.5f, -0.5f),
	
	conditionsSpecificCorner0Sysmetry.push_back(true);			 //(-0.5f, -0.5f, 0.5f),
	conditionsSpecificCorner0Sysmetry.push_back(true);			 //(-0.5f, 0.5f, 0.5f),
	conditionsSpecificCorner0Sysmetry.push_back(false);			//(0.5f, -0.5f, 0.5f), V
	conditionsSpecificCorner0Sysmetry.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsSpecificCorner0Sysmetry, building0_specificCorner0Symetry);
	

	vector<bool> conditionsFloorToWallCorner = vector<bool>();
	conditionsFloorToWallCorner.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsFloorToWallCorner.push_back(false);			 //(-0.5f, 0.5f, -0.5f),
	conditionsFloorToWallCorner.push_back(true);			//(0.5f, -0.5f, -0.5f),
	conditionsFloorToWallCorner.push_back(false);			//(0.5f, 0.5f, -0.5f),
	
	conditionsFloorToWallCorner.push_back(true);			 //(-0.5f, -0.5f, 0.5f),
	conditionsFloorToWallCorner.push_back(true);			 //(-0.5f, 0.5f, 0.5f),
	conditionsFloorToWallCorner.push_back(true);			//(0.5f, -0.5f, 0.5f),
	conditionsFloorToWallCorner.push_back(false);			//(0.5f, 0.5f, 0.5f),

	testVoxelFactory->AddRule(conditionsFloorToWallCorner, building0_floorToWallCorner);
	

	vector<bool> conditionsFloorToWallInnerCorner = vector<bool>();
	conditionsFloorToWallInnerCorner.push_back(true);			 //(-0.5f, -0.5f, -0.5f),
	conditionsFloorToWallInnerCorner.push_back(true);			 //(-0.5f, 0.5f, -0.5f), V
	conditionsFloorToWallInnerCorner.push_back(true);			//(0.5f, -0.5f, -0.5f),
	conditionsFloorToWallInnerCorner.push_back(true);			//(0.5f, 0.5f, -0.5f), V

	conditionsFloorToWallInnerCorner.push_back(true);			 //(-0.5f, -0.5f, 0.5f),
	conditionsFloorToWallInnerCorner.push_back(false);			 //(-0.5f, 0.5f, 0.5f),
	conditionsFloorToWallInnerCorner.push_back(true);			//(0.5f, -0.5f, 0.5f),
	conditionsFloorToWallInnerCorner.push_back(true);			//(0.5f, 0.5f, 0.5f), V

	testVoxelFactory->AddRule(conditionsFloorToWallInnerCorner, building0_floorToWallInnerCorner);

#pragma endregion

	Math::Vector3 voxelFactorySize = Math::Vector3(5, 5, 5);
	int multiplicator = 1;
	//SimpleObjectFactory* object1 = new SimpleObjectFactory("A_Brick.mesh", "1d_debug.png", 20, testVoxelFactory);

	ArrayFactory* smallArray = new ArrayFactory(voxelFactorySize.X() * multiplicator, voxelFactorySize.Y() * multiplicator, voxelFactorySize.Z() * multiplicator, Math::Vector3(1, 1, 1), true, testVoxelFactory);
	SimpleObjectFactory* voxelCube = new SimpleObjectFactory("B_Brick.mesh", "1d_debug.png", 30, smallArray);

	ArrayFactory* worldArray = new ArrayFactory(10, 10, 10, voxelFactorySize * multiplicator + Math::Vector3(0, 0, 0), true, voxelCube);

	shared_ptr<SimpleObjectDisplayable> object0 = make_shared<SimpleObjectDisplayable>("A_Brick.mesh", "debug_texture.png");
	shared_ptr<Item> item0 = std::make_shared<Item>(Math::Matrix4(Math::Vector3(0, -10, 0)), shared_ptr<Item>(), 1000.0f, vector<Math::ParametricPlane*>(), false, object0, worldArray);
	item0->SetId(10);
	sceneManager->QueueAddItem(item0);
}

void InitializeFileReadingTestScene(SceneGraphManager* sceneManager)
{
	DataModel::DependenceTreeDataModel dependenceTree = DataModel::DependenceTreeDataModel();
	LevelFactory* rootFactory = dependenceTree.Read("C:/Utils/GeneratorScenes/demo0/main.txt");
	//LevelFactory* rootFactory = dependenceTree.Read("C:/Utils/GeneratorScenes/test0/mainScene.txt");
	//LevelFactory* rootFactory = dependenceTree.Read("simpleScene.txt");

	//SimpleObjectFactory* testCubeA = new SimpleObjectFactory("A_Brick.mesh", "1d_debug.png", 0, NULL);
	
	shared_ptr<SimpleObjectDisplayable> object0 = make_shared<SimpleObjectDisplayable>("A_Brick.mesh", "debug_texture.png");
	shared_ptr<Item> item0 = std::make_shared<Item>(Math::Matrix4(Math::Vector3(0, 0, 0)), shared_ptr<Item>(), 100000.0f, vector<Math::ParametricPlane*>(), false, object0, rootFactory);
	item0->SetId(10);
	sceneManager->QueueAddItem(item0);
}

void OgreClient::createScene(void)
{
	Ogre::SceneNode* lRootSceneNode = mSceneMgr->getRootSceneNode();

	Ogre::MaterialManager& lMaterialManager = Ogre::MaterialManager::getSingleton();
	Ogre::ResourceGroupManager& ressourceGroupManager = Ogre::ResourceGroupManager::getSingleton();

	mCamera->setPosition(0, 2, 10);

	/// Some resource setup
	string textureGroupName = "Textures";

	// Create a material for each texture in the texture ressource group
	Ogre::MaterialPtr instancingMaterial = lMaterialManager.getByName("HW_VTFInstancing");

	/*for each (Ogre::MaterialPtr var in lMaterialManager.)
	{

	}*/

	Ogre::StringVectorPtr essentialListPtr = ressourceGroupManager.listResourceNames("Essential");

	Ogre::StringVectorPtr textureListPtr = ressourceGroupManager.listResourceNames(textureGroupName);
	Ogre::StringVector * textureList = textureListPtr.get();
	for (Ogre::StringVector::iterator textureIterator = textureList->begin(); textureIterator != textureList->end(); textureIterator++)
	{
		string textureName = *textureIterator;

		// Materials
		Ogre::MaterialPtr lMaterial = lMaterialManager.create(textureName, textureGroupName);
		Ogre::Technique* lFirstTechnique = lMaterial->getTechnique(0);
		Ogre::Pass* lFirstPass = lFirstTechnique->getPass(0);
		lFirstPass->setLightingEnabled(false);
		//lFirstPass->setVertexProgram("Instancing", false);
		//lFirstPass->setVertexProgram("HW_VTFInstancing");

		Ogre::TextureUnitState* lTextureUnit = lFirstPass->createTextureUnitState();
		lTextureUnit->setTextureName(textureName, Ogre::TEX_TYPE_2D);
		lTextureUnit->setTextureCoordSet(0);

		try
		{
			lMaterial->load();
		}
		catch (Ogre::Exception& e)
		{
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;

			std::cerr << "Texture name : " <<
				textureName << std::endl;
		}
	}


	// Initialize the procedural generator
	_ogreInstanciater = new OgreInstanciater(ressourceGroupManager, mSceneMgr, lMaterialManager);
	_sceneManager = SceneGraphManager(_ogreInstanciater);

	//InitializeQuaternionTestScene(&_sceneManager);
	//InitializeAsianBuildingsTestScene(&_sceneManager);
	//InitializerVoxelTestScene(&_sceneManager);
	InitializeFileReadingTestScene(&_sceneManager);
	//InitializerArrayVoxelTestScene(&_sceneManager);
}


void RefreshGenerator(Generator::SceneGraphManager* sceneManager, Math::Vector3 cameraPos)
{
	sceneManager->Update(cameraPos, Math::Vector3(0, 0, 0));
	//sceneManager->Flush();
}


bool OgreClient::frameStarted(const Ogre::FrameEvent& evt)
{
	_timeSinceLastUpdate += evt.timeSinceLastFrame;

	// Flush refresh
	//if (_timeSinceLastUpdate > 0.5 && _ogreInstanciater->IsFlushCompleted())
	{
		Ogre::Vector3 cameraPosition = mCamera->getPosition();
		Math::Vector3 cameraPos = Math::Vector3(cameraPosition.x, cameraPosition.y, cameraPosition.z);

		if (_threadInitialized)
		{
			_proceduralGeneratorThread.join();
		}

		std::chrono::high_resolution_clock::time_point tpSceneManager0 = std::chrono::high_resolution_clock::now();

		_sceneManager.Flush();

		high_resolution_clock::time_point tpSceneManager1 = high_resolution_clock::now();
		auto sceneManagerDuration = duration_cast<microseconds>(tpSceneManager1 - tpSceneManager0).count();
		std::cout << "Scene manager" << sceneManagerDuration << std::endl;

		_proceduralGeneratorThread = std::thread(RefreshGenerator, &_sceneManager, cameraPos);

		//_proceduralGeneratorThread.join();

		_threadInitialized = true;
		_timeSinceLastUpdate = 0;

	}

	//std::chrono::high_resolution_clock::time_point tpOgreInstanciater0 = std::chrono::high_resolution_clock::now();

	_ogreInstanciater->Flush(30000000, 30000000);

	/*high_resolution_clock::time_point tpOgreInstanciater1 = high_resolution_clock::now();
	auto ogreInstanciaterDuration = duration_cast<microseconds>(tpOgreInstanciater1 - tpOgreInstanciater0).count();
	std::cout << "Instanciater : " << ogreInstanciaterDuration << std::endl;*/

	return true;
}


#ifdef __cplusplus
extern "C" {
#endif
int main(int argc, _TCHAR* argv[])
{
	// Create application object
	OgreClient app;

	try {
		app.go();
	}
	catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		//MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		std::cerr << "An exception has occured: " <<
			e.getFullDescription().c_str() << std::endl;
#else
		std::cerr << "An exception has occured: " <<
			e.getFullDescription().c_str() << std::endl;
#endif
	}

	return 0;
}

#ifdef __cplusplus
}
#endif
