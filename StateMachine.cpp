// =============================================================================
// Filename         : StateMachine.cpp
// Version          :
//
// Original Author  : Peter Metz
// Date Created     : 02-Jun-2020
// Revision History :
//
// Purpose          : Defines a base class that can be used on more resource-
//                    constrained embedded systems to impliment simple state
//                    machines. Application-specific states and transition
//                    tests need to be defined in the derived class; the base
//                    class itself tracks changes in these states, simplifying
//                    the process of implementing state-entry and -exit logic.
//
// Licensing        : Copyright (C) 2020, Peter Metz
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ----------------------------------------------------------------------------
// Notes:
// =============================================================================
#include "StateMachine.h"


// =============================================================================
// Class            : Flag
//
// Purpose          : This class implements a 'tri-state' boolean datatype
//                    that can be used to track whether or not a flag variable
//                    has been initialised, and whether a rising or falling
//                    transition has occurred.
// =============================================================================
class Flag {
Flag::Flag() {
  p_uninitialised = true;
}


Flag& Flag::operator=(const bool& val) {
  if (p_uninitialised) {
    p_previous = val; p_current = val; p_uninitialised = false;
  } else {
    p_previous = p_current; p_current = val;
  }
  return *this;
}


Flag::operator bool() {
  return p_current;
}




// =============================================================================
// Class            : StateMachine
//
// Purpose          : This class implements the state machine base class.
// =============================================================================
StateMachine::State::State() {
  p_state = UNDEFINED;
  p_changed = true;
}


StateMachine::State& StateMachine::State::operator=(const unsigned& val) {
  if (p_state != val)
    p_changed = true;
  p_state = val;
  return *this;
}


StateMachine::State::operator unsigned() {
  return p_state;
}


// Note that we assume changed() will only be called once per test-cycle
// (i.e. it will automatically reset its internal [p_changed] flag after
// returning true)
bool StateMachine::State::changed() {
  if (p_changed) {
    p_changed = false;
    return true;
  } else
    return false;
}


StateMachine::StateMachine() {
  state = UNINITIALISED;
}
