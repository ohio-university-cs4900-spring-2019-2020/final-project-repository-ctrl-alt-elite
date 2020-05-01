#include "GLViewfinal_project.h"
//#include "SoundManager.h"

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

//If we want to use way points, we need to include this.
#include "final_projectWayPoints.h"
using namespace Aftr;
using namespace std;
//using namespace irrklang;

GLViewNewModule* GLViewNewModule::New( const std::vector< std::string >& args )
{
   GLViewNewModule* glv = new GLViewNewModule( args );
   glv->init( Aftr::GRAVITY, Vector( 0, 0, -1.0f ), "../aftr.conf", PHYSICS_ENGINE_TYPE::petODE );
   glv->onCreate();
   return glv;
}


GLViewNewModule::GLViewNewModule( const std::vector< std::string >& args ) : GLView( args )
{
   //Initialize any member variables that need to be used inside of LoadMap() here.
   //Note: At this point, the Managers are not yet initialized. The Engine initialization
   //occurs immediately after this method returns (see GLViewNewModule::New() for
   //reference). Then the engine invoke's GLView::loadMap() for this module.
   //After loadMap() returns, GLView::onCreate is finally invoked.

   //The order of execution of a module startup:
   //GLView::New() is invoked:
   //    calls GLView::init()
   //       calls GLView::loadMap() (as well as initializing the engine's Managers)
   //    calls GLView::onCreate()

   //GLViewNewModule::onCreate() is invoked after this module's LoadMap() is completed.
}


void GLViewNewModule::onCreate()
{
   //GLViewNewModule::onCreate() is invoked after this module's LoadMap() is completed.
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
}


GLViewNewModule::~GLViewNewModule()
{
   //Implicitly calls GLView::~GLView()
}


void GLViewNewModule::updateWorld()
{
   GLView::updateWorld(); //Just call the parent's update world first.
                          //If you want to add additional functionality, do it after
                          //this call.
   //sManager->updateListenerPosition(*this->cam->getPosition, *this->cam->getLookDirection, *this->cam->getCameraVelocity, *this->cam->getNormalDirection);
   for (int x = 0; x < ExistingBulletIDs.size(); x++)
   {
	   WO* currentBullet = this->worldLst->getWOByID(ExistingBulletIDs[x]);
	   MoveBullet(currentBullet);
   }

   // Here is where we would put the update on target hit stuff!
}


void GLViewNewModule::onResizeWindow( GLsizei width, GLsizei height )
{
   GLView::onResizeWindow( width, height ); //call parent's resize method.
}


void GLViewNewModule::onMouseDown( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseDown( e );
   
}


void GLViewNewModule::onMouseUp( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseUp( e );
}


void GLViewNewModule::onMouseMove( const SDL_MouseMotionEvent& e )
{
   GLView::onMouseMove( e );
}


void GLViewNewModule::onKeyDown( const SDL_KeyboardEvent& key )
{
   GLView::onKeyDown( key );
   if( key.keysym.sym == SDLK_0 )
      this->setNumPhysicsStepsPerRender( 1 );

   if( key.keysym.sym == SDLK_1 )
   {
	   
   }

   if (key.keysym.sym == SDLK_a)
   {
	   cout << "Toggling ADS..." << endl;
	   WO* playerWeapon = this->worldLst->getWOByID(this->PlayerWeaponWOIndex);

   }

   if (key.keysym.sym == SDLK_f)
   {
	   WeaponFiring(this->worldLst->getWOByID(this->PlayerWeaponWOIndex));
   }
   //SoundManager* sManager = SoundManager::New(5);
   
   //sManager->PlaySound2D(ManagerEnvironmentConfiguration::getSMM() + "/sounds/sound2.wav");
   //World Ambiance Sound manager:
   //Generates new manager for the ambiant sounds
   //SoundManager* AmbianceSoundManager = SoundManager::New(1);
   //Runs the space sound for 10 seconds
   //AmbianceSoundManager->LoopSound2DWithDurationInMilliSec(ManagerEnvironmentConfiguration::getSMM() + "/sounds/sound2.wav", 10000);
}


void GLViewNewModule::onKeyUp( const SDL_KeyboardEvent& key )
{
   GLView::onKeyUp( key );
}


void Aftr::GLViewNewModule::loadMap()
{
   this->worldLst = new WorldList(); //WorldList is a 'smart' vector that is used to store WO*'s
   this->actorLst = new WorldList();
   this->netLst = new WorldList();


   ManagerOpenGLState::GL_CLIPPING_PLANE = 1000.0;
   ManagerOpenGLState::GL_NEAR_PLANE = 0.1f;
   ManagerOpenGLState::enableFrustumCulling = false;
   Axes::isVisible = false;
   this->glRenderer->isUsingShadowMapping( true ); //set to TRUE to enable shadow mapping, must be using GL 3.2+

   this->cam->setPosition( 15,15,10 );
   
   //Creates the sound manager for the module:

   std::string shinyRedPlasticCube( ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl" );
   std::string wheeledCar( ManagerEnvironmentConfiguration::getSMM() + "/models/rcx_treads.wrl" );
   std::string grass( ManagerEnvironmentConfiguration::getSMM() + "/models/grassFloor400x400_pp.wrl" );
   std::string human( ManagerEnvironmentConfiguration::getSMM() + "/models/human_chest.wrl" );
   
   //SkyBox Textures readily available
   std::vector< std::string > skyBoxImageNames; //vector to store texture paths

   skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_Hubble_Nebula+6.jpg" );

   float ga = 0.02f; //Global Ambient Light level for this module
   ManagerLight::setGlobalAmbientLight( aftrColor4f( ga, ga, ga, 1.0f ) );
   WOLight* light = WOLight::New();
   light->isDirectionalLight( true );
   light->setPosition(Vector(0, 0, 100));
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
   wo = WO::New( grass, Vector( 100, 100, 1 ), MESH_SHADING_TYPE::mstFLAT );
   wo->setPosition( Vector( 0, 0, 0 ) );
   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   ModelMeshSkin& grassSkin = wo->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
   grassSkin.getMultiTextureSet().at( 0 )->setTextureRepeats( 500.0f );
   grassSkin.setAmbient( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Color of object when it is not in any light
   grassSkin.setDiffuse( aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object)
   grassSkin.setSpecular( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
   grassSkin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
   wo->setLabel( "Grass" );
   worldLst->push_back( wo );

   createPlayersAKModel();
   int BattleGroundDimension = 1000.0;
   int targetCount = 30;
   for (int x = 0; x < targetCount; x++)
   {
	   float newX = rand() % BattleGroundDimension;
	   float newY = rand() % BattleGroundDimension;
	   GenerateRandomTargetHuman(newX, newY);
   }
}

void Aftr::GLViewNewModule::MoveBullet(WO* Bullet)
{
	Bullet->moveRelative(Bullet->getModel()->getLookDirection() * 3.5);
}


void Aftr::GLViewNewModule::GenerateRandomTargetHuman(float xCoord, float yCord)
{
	cout << "Target at: " << xCoord << "  " << yCord << endl;
	string targetPath(ManagerEnvironmentConfiguration::getLMM() + "models/MaleTarget.obj");
	//string buildingPath(ManagerEnvironmentConfiguration::getLMM() + "models/TikTAkTiers.obj");
	//cout << "PATH: " << buildingPath << endl;
	WO* Target = WO::New(targetPath, Vector(.15, .15, .15));
	Target->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
	Target->setPosition(Vector(xCoord, yCord, 8));
	Target->setLabel("Enemy");
	//Target->getModel()->set(Vector(0, 0, 0));
	worldLst->push_back(Target);
}


void  Aftr::GLViewNewModule::createNewModuleWayPoints()
{
   // Create a waypoint with a radius of 3, a frequency of 5 seconds, activated by GLView's camera, and is visible.
   WayPointParametersBase params(this);
   params.frequency = 5000;
   params.useCamera = true;
   params.visible = true;
   WOWayPointSpherical* wayPt = WOWP1::New( params, 3 );
   wayPt->setPosition( Vector( 50, 0, 3 ) );
   worldLst->push_back( wayPt );
}

void Aftr::GLViewNewModule::createPirateShipModel()
{
    cout << "Loading Pirate Ship Model..." << endl;
    string buildingPath(ManagerEnvironmentConfiguration::getSMM() + "models/pirateship.wrl");
    //string buildingPath(ManagerEnvironmentConfiguration::getLMM() + "models/TikTAkTiers.obj");
    //cout << "PATH: " << buildingPath << endl;
    WO* BuildingModel = WO::New(buildingPath, Vector(.3, .3, .3));
    BuildingModel->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    BuildingModel->setPosition(Vector(300,300,50));
    //hospitalModel->getModel()->getModelDataShared()->getModelMeshes().at(0)->getSkins().at(0).getMultiTextureSet().at(0)->setTextureRepeats( 5.0f );
    BuildingModel->setLabel( "Pirate Ship" );
    worldLst->push_back(BuildingModel);
}

void  Aftr::GLViewNewModule::createRaceCarModel()
{
    cout << "Loading Racecar Model..." << endl;
    //Create formula one model 3d object
    string raceCar(ManagerEnvironmentConfiguration::getLMM() + "models/Formula 1 mesh.obj");
    //cout << "PATH: " << raceCar << endl;
    WO* RaceCar = WO::New(raceCar, Vector(.15, .15, .15), MESH_SHADING_TYPE::mstSMOOTH);
    RaceCar->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
    RaceCar->setPosition(Vector(-10, -10, 10));
    RaceCar->setLabel("Race Car");
    worldLst->push_back(RaceCar);
}

void  Aftr::GLViewNewModule::bulletFiredFromGun(WO* Shooter)
{
	//Object generation settings
	cout << "Shot Fired" << endl;
	//Create AK-47  model 3d object
	string bullet(ManagerEnvironmentConfiguration::getLMM() + "models/bullet_projectile.obj");
	WO* bulletInFlight = WO::New(bullet, Vector(.005, .005, .005), MESH_SHADING_TYPE::mstFLAT);
	bulletInFlight->renderOrderType = RENDER_ORDER_TYPE::roLIGHT;
	//bulletInFlight.setAmbient(aftrColor4f(0.4f, 0.4f, 0.4f, 1.0f)); //Color of object when it is not in any light
	//bulletInFlight.setDiffuse(aftrColor4f(1.0f, 1.0f, 1.0f, 1.0f)); //Diffuse color components (ie, matte shading color of this object)
	//bulletInFlight.setSpecular(aftrColor4f(4.0f, 4.0f, 4.0f, 4.0f)); //Specular color component (ie, how "shiney" it is)
	Vector startingLocation = Shooter->getPosition();

	//Bullets glow and flash:
	float ba = 0.3f; //Global Ambient Light level for this module
	WOLight* light = WOLight::New();
	light->setColor(aftrColor4f(255.0f, 255.0f, 8.0f, 1.0f));
	light->isPointLight(true);
	light->isDirectionalLight(false);
	light->setPosition(startingLocation);
	light->setParentWorldObject(bulletInFlight);
	light->lockWRTparent();
	//Vector startingDisplayMatrix = Shooter->getDisplayMatrix();
	// bullet gun offset:
	//startingLocation[0] = startingLocation[0] + 1.3;
	//startingLocation[0] = startingLocation[0] + 4;
	bulletInFlight->setParentWorldObject(Shooter);
	bulletInFlight->setPosition(startingLocation);
	
	bulletInFlight->getModel()->setLookDirection(Shooter->getModel()->getLookDirection());
	bulletInFlight->moveRelative(bulletInFlight->getModel()->getLookDirection() * 2);
	//bulletInFlight->getModel()->setDisplayMatrix(startingDisplayMatrix);
	ExistingBulletIDs.push_back(bulletInFlight->getID());
	worldLst->push_back(bulletInFlight);
}

void Aftr::GLViewNewModule::WeaponFiring(WO* Shooter)
{
	string shooterName = Shooter->getLabel();
	cout << shooterName << "  Is shooting!" << endl;
	bulletFiredFromGun(Shooter);
}

void  Aftr::GLViewNewModule::createPlayersAKModel()
{
	//Object generation settings
	cout << "Loading Player's AK-47 Model..." << endl;
	//Create AK-47  model 3d object
	string weapon(ManagerEnvironmentConfiguration::getLMM() + "models/Ak-47_V2.obj");
	WO* AK47 = WO::New(weapon, Vector(.01, .01, .01), MESH_SHADING_TYPE::mstFLAT);
	AK47->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
	// Weapon camera offset:
	Vector startingLocation = this->cam->getPosition();
	startingLocation[0] = startingLocation[0] + 1.3;
	startingLocation[1] = startingLocation[1] - 1;
	startingLocation[2] = startingLocation[2] - 1;
	// Weapon model orientation
	AK47->setPosition(startingLocation);
	// Weapon methods:
	// Connects the weapon to the camera:
	AK47->setParentWorldObject(this->cam);
	AK47->lockWRTparent();
	AK47->setLabel("AK-47");
	worldLst->push_back(AK47);
	this->PlayerWeaponWOIndex = AK47->getID();
}