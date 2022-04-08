#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Cell;

class Observer {
  public:
    virtual void notify(Cell &s) = 0;  // s is the Subject that called the notify method
};

#endif

