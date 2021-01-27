#pragma once

#include "Representations/BehaviorControl/FieldBall.h"
#include "Representations/Communication/TeamData.h"
#include "Representations/Infrastructure/FrameInfo.h"
#include "Representations/Modeling/BallModel.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Modeling/SimpleBallModel.h"
#include "Representations/Modeling/TeamBallModel.h"
#include "Representations/Perception/BallPercepts/BallPercept.h"
#include "Tools/Module/Module.h"

MODULE(SimpleBallLocatorProvider,
{,
  REQUIRES(BallPercept),
  REQUIRES(FrameInfo),
  REQUIRES(BallModel),
  REQUIRES(RobotPose),
  REQUIRES(TeamBallModel),
  REQUIRES(TeamData),
  REQUIRES(FieldBall),
  PROVIDES(SimpleBallModel),
  DEFINES_PARAMETERS(
  {,
    (Vector2f) position,
    (Vector2f) positionB,
    (Vector2f) positionB2Prime,
  }),
});

class SimpleBallLocatorProvider : public SimpleBallLocatorProviderBase
{
public:
  void update(SimpleBallModel& simpleBallModel) override;
}; 

