#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>
#include <cmath>
#include <cstdlib> 
using namespace std::chrono;
using namespace std;

// The struct that contains the data on the current bullets path
struct bulletCaliberStats{
    //**************************************
    // Set variables before flight
    string name;
    double initialVelocity;
    double initialHeight;

    //Static Bullet details
    double projectileMass; // in kg
    double projectileArea; // in m^2
    double projectileDragCoefficient;

    // Calculated on launch:
    double horizontalLaunchAngle; // In Radians
    double verticleLaunchAngle; // In Radians
    double launchHeight;
    double launchX;
    double launchY;
    

    // ************************************
    // Calculated Values in flight
    double flightTime;
    double currentVelocityInMPS; //Velocity in meters per second

    //This stores the last time the location was calculated:
    long double LastCalcTime;
    long double FlightStartTime;
};


// The struct that contains the statistics for the environment the bullet is currently in.
struct environmentStatistics{
    float airPreassure; // In Kg/cb meter 
    float windspeed; //set to one for rn because it is not implemented
    float gravity;  // In meters/sec^2
};


// This class is used to generate a bunch of different calibers of ammunition and add helper methods to the bullet caliber struct:
class projectileCalibers{
    public: 
        static bulletCaliberStats get_AK_762x39_PS(){
            struct bulletCaliberStats caliber;
            caliber.name = "762x39 (SP)";
            caliber.projectileDragCoefficient = 0.275;
            caliber.projectileMass = 0.010; //kg
            caliber.projectileArea = 0.0000484; // m^2
            caliber.initialVelocity = 783; // m/s
            return caliber;
        };

        static bulletCaliberStats get_762x51_308_M80(){
            struct bulletCaliberStats caliber;
            caliber.name = ".308 (M80)";
            caliber.projectileDragCoefficient = 0.393;
            caliber.projectileMass = 0.016; //kg
            caliber.projectileArea = 0.000048; // m^2
            caliber.initialVelocity = 850; // m/s
            return caliber;
        };
};

class BalisticsCalculater {
    public:
        static void fireBullet(double vertAngle, double horizAngle, struct bulletCaliberStats &bState, vector <long double > &bulletVector){
            // Gets the current horizontal nd verticle angle of the barrell
            bState.horizontalLaunchAngle = horizAngle;
            bState.verticleLaunchAngle = vertAngle;
            // Sets the start time of both the flight and last calc to now
            bState.FlightStartTime = duration_cast <milliseconds>(system_clock::now().time_since_epoch()).count();
            bState.LastCalcTime = duration_cast <milliseconds>(system_clock::now().time_since_epoch()).count();
            bState.launchHeight = bulletVector[2];
            bState.launchY = bulletVector[1];
            bState.launchX = bulletVector[0];
            //cout << "Start time:" << to_string(bState.FlightStartTime) << endl;
        };

        static long double getFlightTime(uint64_t FlightStartTime){
            long double flightTime = (duration_cast <milliseconds>(system_clock::now().time_since_epoch()).count() -  FlightStartTime)/1000;
            if (flightTime == 0)
            {
                flightTime = 1.00000000;
            }
            return flightTime;
        }

        // Get's current height at this time
        static long double getNextHeight(struct environmentStatistics &eState, struct bulletCaliberStats &bState, vector <long double > &bulletVector){
            /*if (bState.verticleLaunchAngle == NULL)
            {
                cout << "Error!!! No verticle launch angle specified!" << '\n';
                return -1;
            }*/
            // First ill need to calculate the verticle distance of the velocity given the angle:
            double verticleVelocity = sin(bState.verticleLaunchAngle) * bState.initialVelocity;
            //cout << "verticleVelocity: " << verticleVelocity << '\n';
            // Then I calculate Current Flight Time:
            long double flightTime = BalisticsCalculater::getFlightTime(bState.FlightStartTime);
            //cout << "Flight Time: " << flightTime << '\n';
            // Current Height = Initial verticle velocity * time - 0.5 * gravity *timeSquared
            long double currentHeight = bState.launchHeight + ((verticleVelocity*flightTime) - ((0.5 * eState.gravity) * (flightTime * flightTime)));
            //cout << "Current Height: " << to_string(currentHeight) << '\n';
            if (currentHeight <= 0)
            {
                currentHeight = 0;
            }
            return currentHeight;
        };


        // Get's current Distance at this current time.
        static long double getNextDistance(struct environmentStatistics &eState, struct bulletCaliberStats &bState, vector <long double> &bulletVector){
            /*if (bState.verticleLaunchAngle == NULL)
            {
                cout << "Error!!! No verticle launch angle specified!" << '\n';
                return -1;
            }*/
            // First ill need to calculate the horizontal distance of the velocity given the angle:
            double horizontalVelocity = cos(bState.verticleLaunchAngle) * bState.initialVelocity;
            //cout << "horizontalVelocity: " << horizontalVelocity << " eState.airPreassure: " << eState.airPreassure << " bState.projectileDragCoefficient: " << bState.projectileDragCoefficient << endl;
            // Then I calculate Current Flight Time:
            long double flightTime = BalisticsCalculater::getFlightTime(bState.FlightStartTime);
            //cout << "Flight Time: " << flightTime << '\n';
            // Distance Covered = StartingVelocity*FlightTime - (drag*airpreassure*bulletAread*velocitySquared*timeSquared)/(2*bulletNass)
            long double currentLocation = bState.launchX + ((horizontalVelocity*flightTime) - (eState.airPreassure * bState.projectileDragCoefficient * bState.projectileArea * (horizontalVelocity*horizontalVelocity) * (flightTime * flightTime)) / (2 * bState.projectileMass));
            //cout << "Current Distance Covered: " << to_string(currentDistanceCovered) << '\n';
            return currentLocation;
        };


        // Calculates and manages the bullet struct's current coordinates given the current time
        static void calculateBulletLocation(struct environmentStatistics &eState, struct bulletCaliberStats &bState, vector <long double> &bulletVector)
        {
            //Runs until the bullet has hit the ground
            if (bulletVector[2] == 0){
                //cout << "Flight Time: " << BalisticsCalculater::getFlightTime(bState.FlightStartTime) << '\n';
                return;
            }
            //cout << "Flight Time: " << BalisticsCalculater::getFlightTime(bState.FlightStartTime) << '\n';
            // Prints the current status:
            //BalisticsCalculater::printCurrentBulletInfo(bState, bulletVector);
            // Finds the new values of the bullet
            //Height finding:
            
            // Vector <X, Y, Z>
            // sets the bullet's vector to the equation results.
            // initially this will only modify the x value and z value
            long double nextHeight = getNextHeight(eState, bState, bulletVector);
            long double nextDistance = getNextDistance(eState, bState, bulletVector);
            bulletVector[0] = nextDistance;
            bulletVector[2] = nextHeight;

            // Update current times in application
            bState.LastCalcTime = std::chrono::system_clock::to_time_t(chrono::system_clock::now());

            // Prints the current status:
            //BalisticsCalculater::printCurrentBulletInfo(bState, bulletVector);
        };

        static void printCurrentBulletInfo(struct bulletCaliberStats &curState, vector <long double> &bulletVector)
        {
            cout << "CALIBER: " << curState.name << " ";
            cout << "Bullet Coords <X,Y,Z>: " << to_string(bulletVector[0]) << "," <<  to_string(bulletVector[1]) << "," <<  to_string(bulletVector[2]) << "\n";
            //cout << "Bullet Velocity: " << to_string(curState.initialVelocity) << "    " << '\n';
        }

        static float calculateDragCoeffecient()
        {
            return 1.0;
        };
};

// This class is used to generate and handle the statistics in the environment
class environmentGenerator{
    public: 
        // Default environment settings on earth at sea level
        static environmentStatistics get_earth_DefaultCond(){
            struct environmentStatistics environment;
            environment.airPreassure = 1.2;
            environment.gravity = 9.8;
            return environment;
        };
};
