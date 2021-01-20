#include "SimpleBallModel.h"

void SimpleBallModel::verify() const {
  ASSERT(std::isfinite(ownRobotDistance));
  ASSERT(std::isfinite(teamRobotDistance));
}
