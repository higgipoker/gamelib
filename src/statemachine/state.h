#pragma once

#include <iostream>
#include <vector>

namespace GameLib{

/** \brief base state */
class State {
 public:
  /**
   * \brief constructor
   */
  State();

  /**
   * \brief destructor
   */
  virtual ~State();

  /**
   * \brief onStart
   */
  virtual void OnStart() = 0;

  /**
   * \brief onStep
   * \param _dt time delta
   */
  virtual void OnStep(const float _dt) = 0;

  /**
   * \brief onEnd
   */
  virtual void OnEnd() = 0;

  /**
   * \brief stateOver
   */
  virtual bool StateOver() = 0;

  /**
   * \brief changeToNextState
   */
  virtual void ChangeToNextState() = 0;

  /**
   * \brief stateName
   */
  std::string StateName() const { return name; }

 protected:
  // identifier
  std::string name;
};
}// GameLib
