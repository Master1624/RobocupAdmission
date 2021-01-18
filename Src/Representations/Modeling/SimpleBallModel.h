#pragma once

#include "Tools/Streams/AutoStreamable.h"
#include "Tools/Streams/Enum.h"
#include "Tools/Math/Eigen.h"

STREAMABLE(SimpleBallModel,
{
  void verify() const,
  (bool)(false) estaCerca,			/**< Cuando el robot está cerca, se convierte en true*/
});
