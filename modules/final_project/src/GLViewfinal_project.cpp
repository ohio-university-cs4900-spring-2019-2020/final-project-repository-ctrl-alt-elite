#include "GLViewfinal_project.h"

#include "WorldList.h" //This is where we place all of our WOs
#include "ManagerOpenGLState.h" //We can change OpenGL State attributes with this
#include "Axes.h" //We can set Axes to on/off with this
#include "PhysicsEngineODE.h"

//Different WO used by this module
#include "WO.h"
#include "WOStatic.h"
#include "WOStaticPlane.h"
#include "WOStaticTrimesh.h"
#include "WOTrimesh.h"
#include "WOHumanCyborg.h"
#include "WOHumanCal3DPaladin.h"
#include "WOWayPointSpherical.h"
#include "WOLight.h"
#include "WOSkyBox.h"
#include "WOCar1970sBeater.h"
#include "Camera.h"
#include "CameraStandard.h"
#include "CameraChaseActorSmooth.h"
#include "CameraChaseActorAbsNormal.h"
#include "CameraChaseActorRelNormal.h"
#include "Model.h"
#include "ModelDataShared.h"
#include "ModelMesh.h"
#include "ModelMeshDataShared.h"
#include "ModelMeshSkin.h"
#include "WONVStaticPlane.h"
#include "WONVPhysX.h"
#include "WONVDynSphere.h"
#include "AftrGLRendererBase.h"
#include <WOGUILabel.h>
#include <WOFTGLString.h>
#include <MGLFTGLString.h>

#include "box.h"
#include "target.h"
#include "gun.h"

//If we want to use way points, we need to include this.
#include "final_projectWayPoints.h"

using namespace Aftr;

std::string overwatch(ManagerEnvironmentConfiguration::getLMM() + "/fonts/overwatch.ttf");
//WOGUILabel* testText;
WOFTGLString* testText;
WOWayPointSpherical* wayPt;

GLViewfinal_project* GLViewfinal_project::New( const std::vector< std::string >& args )
{
   GLViewfinal_project* glv = new GLViewfinal_project( args );
   glv->init( Aftr::GRAVITY, Vector( 0, 0, -1.0f ), "aftr.conf", PHYSICS_ENGINE_TYPE::petODE );
   glv->onCreate();
   return glv;
}


GLViewfinal_project::GLViewfinal_project( const std::vector< std::string >& args ) : GLView( args )
{
   //Initialize any member variables that need to be used inside of LoadMap() here.
   //Note: At this point, the Managers are not yet initialized. The Engine initialization
   //occurs immediately after this method returns (see GLViewfinal_project::New() for
   //reference). Then the engine invoke's GLView::loadMap() for this module.
   //After loadMap() returns, GLView::onCreate is finally invoked.

   //The order of execution of a module startup:
   //GLView::New() is invoked:
   //    calls GLView::init()
   //       calls GLView::loadMap() (as well as initializing the engine's Managers)
   //    calls GLView::onCreate()

   //GLViewfinal_project::onCreate() is invoked after this module's LoadMap() is completed.

    //WOGUILabel* testText = WOGUILabel::New(nullptr);
}


void GLViewfinal_project::onCreate()
{
   //GLViewfinal_project::onCreate() is invoked after this module's LoadMap() is completed.
   //At this point, all the managers are initialized. That is, the engine is fully initialized.

   if( this->pe != NULL )
   {
      //optionally, change gravity direction and magnitude here
      //The user could load these values from the module's aftr.conf
      this->pe->setGravityNormalizedVector( Vector( 0,0,-1.0f ) );
      this->pe->setGravityScalar( Aftr::GRAVITY );
   }
   this->setActorChaseType( STANDARDEZNAV ); //Default is STANDARDEZNAV mode
   //this->setNumPhysicsStepsPerRender( 0 ); //pause physics engine on start up; will remain paused till set to 1
   //testText = WOGUILabel::New(nullptr);
   total_hit = 0;

   testText = WOFTGLString::New(overwatch, 90);
   testText->setText("Total targets hit: " + std::to_string(wayPt->isTriggered()));
   testText->getModelT<MGLFTGLString>()->setFontColor(aftrColor4f(1.0f, 0.0f, 0.0f, 1.0f));
   testText->getModelT<MGLFTGLString>()->setSize(30, 10);
   testText->setPosition(Vector(50, 50, 25));
   testText->rotateAboutGlobalX(45);
   testText->rotateAboutGlobalY(-45);
   //testText->setPosition(FONT_ORIENTATION::foLEFT_TOP);
   //testText->getModelT<MGLFTGLString>()->setF
   testText->rotateAboutGlobalX(Aftr::PI / 2);
   worldLst->push_back(testText);

   //this->gun = Gun::New();
   //worldLst->push_back(this->gun->get_world_object());
   //this->gun->set_position(cam->getPosition());
   //std::cout << "Look direction" << cam->getLookDirection() << std::endl;
}


GLViewfinal_project::~GLViewfinal_project()
{
   //Implicitly calls GLView::~GLView()
}


void GLViewfinal_project::updateWorld()
{
   GLView::updateWorld(); //Just call the parent's update world first.
                          //If you want to add additional functionality, do it after
                          //this call.
   //this->gun->set_position(cam->getPosition());
   //std::cout << "Look direction" << cam->getLookDirection() << std::endl;
   ////Vector temp = cam->getLookDirection();
   //std::cout << "Cam position" << cam->getPosition() << std::endl;
   //this->gun->set_direction(cam->getLookDirection());
   //std::cout << "Gun position: " << this->gun->get_postion() << std::endl;

   testText->setText("Total targets hit: " + std::to_string(wayPt->isTriggered()));
   worldLst->push_back(testText);
}


void GLViewfinal_project::onResizeWindow( GLsizei width, GLsizei height )
{
   GLView::onResizeWindow( width, height ); //call parent's resize method.
}


void GLViewfinal_project::onMouseDown( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseDown( e );
}


void GLViewfinal_project::onMouseUp( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseUp( e );
}


void GLViewfinal_project::onMouseMove( const SDL_MouseMotionEvent& e )
{
   GLView::onMouseMove( e );
}


void GLViewfinal_project::onKeyDown( const SDL_KeyboardEvent& key )
{
   GLView::onKeyDown( key );
   if( key.keysym.sym == SDLK_0 )
      this->setNumPhysicsStepsPerRender( 1 );

   if( key.keysym.sym == SDLK_RETURN )
   {
       std::cout << "Enter pressed" << std::endl;
   }

   if (key.keysym.sym == SDLK_1)
   {
       //this->cam->moveInLookDirection(2);
       total_hit++;
       testText->setText("Total targets hit: " + std::to_string(wayPt->isTriggered()));
       worldLst->push_back(testText);
       //updateWorld();
       //total_hit++;
   }
   //if (key.keysym.sym == SDLK_s)
   //{
   //    //this->cam->moveOppositeLookDirection(2);
   //}
   //if (key.keysym.sym == SDLK_a)
   //{
   //    //this->cam->moveLeft();
   //}
   //if (key.keysym.sym == SDLK_d)
   //{
   //    //this->cam->moveRight();
   //}
}


void GLViewfinal_project::onKeyUp( const SDL_KeyboardEvent& key )
{
   GLView::onKeyUp( key );
}


void Aftr::GLViewfinal_project::loadMap()
{
   this->worldLst = new WorldList(); //WorldList is a 'smart' vector that is used to store WO*'s
   this->actorLst = new WorldList();
   this->netLst = new WorldList();

   ManagerOpenGLState::GL_CLIPPING_PLANE = 1000.0;
   ManagerOpenGLState::GL_NEAR_PLANE = 0.1f;
   ManagerOpenGLState::enableFrustumCulling = false;
   Axes::isVisible = true;
   this->glRenderer->isUsingShadowMapping( false ); //set to TRUE to enable shadow mapping, must be using GL 3.2+

   this->cam->setPosition( 15,15,10 );

   std::string shinyRedPlasticCube( ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl" );
   std::string wheeledCar( ManagerEnvironmentConfiguration::getSMM() + "/models/rcx_treads.wrl" );
   std::string grass( ManagerEnvironmentConfiguration::getSMM() + "/models/grassFloor400x400_pp.wrl" );
   std::string human( ManagerEnvironmentConfiguration::getSMM() + "/models/human_chest.wrl" );
   //std::string box(ManagerEnvironmentConfiguration::getLMM() + "/models/WOOD_PLANTER_BOXES_10K.dae");
   //std::string target1(ManagerEnvironmentConfiguration::getLMM() + "/models/shtfrtr.dae");
   //std::string overwatch(ManagerEnvironmentConfiguration::getLMM() + "/fonts/overwatch.ttf");

   //SkyBox Textures readily available
   std::vector< std::string > skyBoxImageNames; //vector to store texture paths
   skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_mountains+6.jpg" );

   float ga = 0.1f; //Global Ambient Light level for this module
   ManagerLight::setGlobalAmbientLight( aftrColor4f( ga, ga, ga, 1.0f ) );
   WOLight* light = WOLight::New();
   light->isDirectionalLight( true );
   light->setPosition( Vector( 0, 0, 100 ) );
   //Set the light's display matrix such that it casts light in a direction parallel to the -z axis (ie, downwards as though it was "high noon")
   //for shadow mapping to work, this->glRenderer->isUsingShadowMapping( true ), must be invoked.
   light->getModel()->setDisplayMatrix( Mat4::rotateIdentityMat( { 0, 1, 0 }, 90.0f * Aftr::DEGtoRAD ) );
   light->setLabel( "Light" );
   worldLst->push_back( light );

   //Create the SkyBox
   WO* wo = WOSkyBox::New( skyBoxImageNames.at( 0 ), this->getCameraPtrPtr() );
   wo->setPosition( Vector( 0,0,0 ) );
   wo->setLabel( "Sky Box" );
   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   worldLst->push_back( wo );

   ////Create the infinite grass plane (the floor)
   wo = WO::New( grass, Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
   wo->setPosition( Vector( 0, 0, 0 ) );
   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   ModelMeshSkin& grassSkin = wo->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
   grassSkin.getMultiTextureSet().at( 0 )->setTextureRepeats( 5.0f );
   grassSkin.setAmbient( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Color of object when it is not in any light
   grassSkin.setDiffuse( aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object)
   grassSkin.setSpecular( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
   grassSkin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
   wo->setLabel( "Grass" );
   worldLst->push_back( wo );
   
   this->box1 = Box::New();
   worldLst->push_back(this->box1->get_world_object());
   this->box1->set_position(Vector(47, 40, 0));

   this->box2 = Box::New();
   worldLst->push_back(this->box2->get_world_object());
   this->box2->set_position(Vector(43, 43, 0));

   this->box3 = Box::New();
   worldLst->push_back(this->box3->get_world_object());
   this->box3->set_position(Vector(38, 45, 0));

   this->box4 = Box::New();
   worldLst->push_back(this->box4->get_world_object());
   this->box4->set_position(Vector(33, 50, 0));

   
   //Need to fix target scaling
   this->target1 = Target::New();
   worldLst->push_back(this->target1->get_world_object());
   this->target1->set_position(Vector(35, 55, 0));

   this->target2 = Target::New();
   worldLst->push_back(this->target2->get_world_object());
   this->target2->set_position(Vector(43, 50, 0));

   this->target3 = Target::New();
   worldLst->push_back(this->target3->get_world_object());
   this->target3->set_position(Vector(45, 45, 0));

   this->target4 = Target::New();
   worldLst->push_back(this->target4->get_world_object());
   this->target4->set_position(Vector(50, 40, 0));

   //this->gun = Gun::New();
   //worldLst->push_back(this->gun->get_world_object());
   //this->gun->set_position(cam->getPosition());

   // Create a waypoint with a radius of 3, a frequency of 5 seconds, activated by GLView's camera, and is visible.
   WayPointParametersBase params(this);
   params.frequency = 1000;
   params.useCamera = true;
   params.visible = true;
   //WOWayPointSpherical* wayPt = WOWP1::New(params, 3);
   wayPt = WOWP1::New(params, 3);
   wayPt->setPosition(Vector(35, 55, 3));
   worldLst->push_back(wayPt);
   //wayPt->isTriggered();

   //createfinal_projectWayPoints();
}


void GLViewfinal_project::createfinal_projectWayPoints()
{
   // Create a waypoint with a radius of 3, a frequency of 5 seconds, activated by GLView's camera, and is visible.
   WayPointParametersBase params(this);
   params.frequency = 100;
   params.useCamera = true;
   params.visible = true;
   WOWayPointSpherical* wayPt = WOWP1::New( params, 3 );
   wayPt->setPosition( Vector( 35, 55, 3 ) );
   worldLst->push_back( wayPt );
}
