# embedded-statemachine

Defines a base class that can be used on more resource-constrained embedded systems to impliment simple state machines. Application-specific states and transition tests need to be defined in the derived class; the base class itself tracks changes in these states, simplifying the process of implementing state-entry and -exit logic.

Also included is a class which implements a 'tri-state' boolean datatype that can be used to track whether or not a flag variable has been initialised, and whether a rising or falling transition has occurred.
