#include "state_machine.h"

namespace GameLib {

//  --------------------------------------------------
//  constructor
//  --------------------------------------------------
StateMachine::StateMachine() : current_state (NULL) {
    inited = false;
    state_changed = false;
}

//  --------------------------------------------------
//  destructor
//  --------------------------------------------------
StateMachine::~StateMachine() {
    delete current_state;
}

//  --------------------------------------------------
//  first time initialization
//  --------------------------------------------------
void StateMachine::InitState (State *_s) {
    if (!inited) {
        current_state = _s;
        inited = true;
    }
}

//  --------------------------------------------------
//  Step
//  --------------------------------------------------
void StateMachine::Step (float dt) {
    // step the current state
    current_state->OnStep (dt);

    //  check for state change
    if (current_state->StateOver()) {
        current_state->ChangeToNextState();
    }
}

//  --------------------------------------------------
//  change state
//  --------------------------------------------------
void StateMachine::ChangeState (State *_s) {
    current_state->OnEnd();

    delete current_state;
    current_state = _s;
    current_state->OnStart();

    on_change_state();
}

} // GameLib
