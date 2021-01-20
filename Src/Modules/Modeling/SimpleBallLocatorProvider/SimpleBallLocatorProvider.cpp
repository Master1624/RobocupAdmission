#include "SimpleBallLocatorProvider.h"

MAKE_MODULE(SimpleBallLocatorProvider, modeling)

void SimpleBallLocatorProvider::update(SimpleBallModel& simpleBallModel)
{
  for(const auto& teammate : theTeamData.teammates)
  {
    float posXBallTeam = abs(teammate.theBallModel.estimate.position.x());
    float posYBallTeam = abs(teammate.theBallModel.estimate.position.y());
    float posXBall = abs(theFieldBall.positionRelative.x());
    float posYBall = abs(theFieldBall.positionRelative.y());
    float posXRobot = abs(theRobotPose.translation.x());
    float posYRobot = abs(theRobotPose.translation.y());
      
    float distanciaX = posXRobot - posXBallTeam;
    float distanciaY = posYRobot - posYBallTeam;
    
    float distanciaXR = posXRobot - posXBall;
    float distanciaYR = posYRobot - posYBall;    
    
    float distanciaRV = sqrt(pow(distanciaX, 2.0) + pow(distanciaY, 2.0));			// distanciaRV es la distancia del balón con respecto a la posición que el compañero ve
    float distanciaR = sqrt(pow(distanciaXR, 2.0) + pow(distanciaYR, 2.0));			// distanciaR es la distancia del balón con respecto a la posición propia del robot
    
    simpleBallModel.ownRobotDistance = distanciaR;
    simpleBallModel.teamRobotDistance = distanciaRV;
      
    if(distanciaRV < 1000 || distanciaR < 1000)
    {
      simpleBallModel.estaCerca = true;
    }
  }
}
