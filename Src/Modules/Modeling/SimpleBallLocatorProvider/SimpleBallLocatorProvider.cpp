#include "SimpleBallLocatorProvider.h"

MAKE_MODULE(SimpleBallLocatorProvider, modeling)

void SimpleBallLocatorProvider::update(SimpleBallModel& simpleBallModel)
{
  for(const auto& teammate : theTeamData.teammates)
  {
    float posXBall = abs(teammate.theBallModel.estimate.position.x());
    float posYBall = abs(teammate.theBallModel.estimate.position.y());
    float posXRobot = abs(theRobotPose.translation.x());
    float posYRobot = abs(theRobotPose.translation.y());
      
    float distanciaX = posXRobot - posXBall;
    float distanciaY = posYRobot - posYBall;
      
    if(distanciaX && distanciaY < 1000)
    {
      simpleBallModel.estaCerca = true;
    }
  }
}
