#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector> 
#include <memory> 

using std::vector; 
using std::shared_ptr; 

class Observer;

class Subject{
	protected: 
		vector<shared_ptr<Observer>> observers; 
		virtual void notifyObservers() = 0;
	
	public: 
		void attach(shared_ptr<Observer> o); 
}; 

#endif 
