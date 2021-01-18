#include "Representations/BehaviorControl/FieldBall.h"
#include "Representations/BehaviorControl/Skills.h"
#include "Representations/Communication/TeamData.h"
#include "Representations/Configuration/FieldDimensions.h"
#include "Representations/Modeling/BallModel.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Modeling/SimpleBallModel.h"
#include "Representations/Modeling/TeamBallModel.h"
#include "Tools/BehaviorControl/Framework/Card/Card.h"
#include "Tools/BehaviorControl/Framework/Card/CabslCard.h"

CARD(TeamBallPositionCard,
{,
  CALLS(Activity),
  CALLS(LookAtAngles),
  CALLS(LookForward),
  CALLS(PathToTarget),
  CALLS(Stand),
  CALLS(WalkToTarget),
  CALLS(WalkAtRelativeSpeed),
  REQUIRES(BallModel),
  REQUIRES(FieldBall),
  REQUIRES(FieldDimensions),
  REQUIRES(RobotPose),
  REQUIRES(SimpleBallModel),
  REQUIRES(TeamBallModel),
  REQUIRES(TeamData),
  DEFINES_PARAMETERS(
  {,
    (float)(0.8f) walkSpeed,
    (float)(2000) tiempo,
  }),
});

class TeamBallPositionCard : public TeamBallPositionCardBase
{
  bool preconditions() const override
  {
    return true;
  }

  bool postconditions() const override
  {
    return true;
  }

  option
  {
    theActivitySkill(BehaviorStatus::teamBallPosition);
    
    initial_state(start)
    {
      transition
      {
        if(state_time > tiempo)
          goto leftTurn;
      }

      action
      {
        theLookForwardSkill();
        theStandSkill();
      }
    }
    
    state(leftTurn)
    {
      transition
      {
        if(state_time > tiempo)
          goto rightTurn;
      }
      
      action
      {
        theLookAtAnglesSkill(1.f, 0.f, 70_deg);
        theStandSkill();
      }
    }
    
    state(rightTurn)
    {
      transition
      {
        if(state_time > tiempo)
          goto lookForward;
      }
      
      action
      {
        theLookAtAnglesSkill(-1.f, 0.f, 70_deg);
        theStandSkill();
      }
    }
    
    state(lookForward)
    {
      transition
      {
        if(theTeamBallModel.contributors == TeamBallModel::oneOther)
          goto walkToBall;
      }
      
      action
      {
        theLookForwardSkill();
        theStandSkill();
      }
    }
    
    state(walkToBall)
    {
      transition
      {
        if(theSimpleBallModel.estaCerca == true)
          goto turnAround;
      }
      
      action
      {
        for(const auto& teammate : theTeamData.teammates)
        {
          //Esta es la posición del balón vista por el robot. Se pone negativa para que el que está de espaldas camine hacia atrás.
          Vector2f ubicacion = -teammate.theBallModel.estimate.position; 
          float angulo = (theRobotPose.inversePose * ((Vector2f){ubicacion})).angle();
          theLookForwardSkill();
          theWalkToTargetSkill(Pose2f(walkSpeed, walkSpeed, walkSpeed), Pose2f(-angulo, ubicacion));
        }
      }
    }
    
    state(turnAround)
    { 
      transition
      {
        if(theTeamBallModel.contributors == TeamBallModel::onlyMe)
          goto girar;
      }
         
      action
      {
        theLookForwardSkill();
        theWalkAtRelativeSpeedSkill(Pose2f(100_deg, 0.f, 0.f));
      }
    }
    
    state(girar)
    {
      action
      {
        theLookForwardSkill();
        theStandSkill();
      }
    }
  }
};

MAKE_CARD(TeamBallPositionCard);
