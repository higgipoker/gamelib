#pragma once

#include "state.h"

namespace GameLib {

/** @brief base state machine */
class StateMachine {
public:
    /**
     * @brief constructor
     */
    StateMachine();

    /**
     * @brief destructor
     */
    virtual ~StateMachine();

    /**
     * @brief set initial state
     * @param _s the initial state
     */
    void InitState(State *_s);

    /**
     * @brief on step
     * @param _dt time delta
     */
    void Step(float _dt);

    /**
     * @brief change state
     * @param _s state to change to
     */
    void ChangeState(State *_s);

protected:
    /// current state
    State *current_state;

    /// track if state has changed
    bool state_changed;

    /// track if we have been initialized
    bool inited;

    /**
     * @brief derived states can do extra stuff on a state change
     */
    virtual void on_change_state() {};
};

}// GameLib
