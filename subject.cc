#include "subject.h"

void Subject::attach(shared_ptr<Observer> o) {
    observers.push_back(o);
}
