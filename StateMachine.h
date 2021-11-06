// =============================================================================
// Filename         : StateMachine.h
// Version          :
//
// Original Author  : Peter Metz
// Date Created     : 02-Jun-2020
// Revision History : 02-Jun-2020: Initial version
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
#ifndef StateMachine_h
#define StateMachine_h


// =============================================================================
// Class            : Flag
//
// Purpose          : This class implements a 'tri-state' boolean datatype
//                    that can be used to track whether or not a flag variable
//                    has been initialised, and whether a rising or falling
//                    transition has occurred.
// =============================================================================
class Flag {
  public:
    Flag();

    Flag& operator=(const bool& val);
    operator bool();

    bool TtoF() { return !p_uninitialised && (p_previous == true) && (p_current == false); }
    bool FtoT() { return !p_uninitialised && (p_previous == false) && (p_current == true); }
    inline bool HtoL() { return TtoF(); }
    inline bool LtoH() { return FtoT(); }

  protected:
    bool p_current, p_previous, p_uninitialised;
};




// =============================================================================
// Class            : StateMachine
//
// Purpose          : This class implements the state machine base class.
// =============================================================================
class StateMachine {
  public:
    enum { UNDEFINED = (unsigned) -1, UNINITIALISED = (unsigned) -2, FAULT = (unsigned) -3 };

    class State {
      public:
        State();

        State& operator=(const unsigned& val);
        operator unsigned();

        bool changed();

      protected:
        unsigned p_state;
        bool p_changed;
    };

    StateMachine();

    State state;
};

#endif
