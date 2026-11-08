/**
 * @file observer.h
 *
 * @brief Declaration of the Observer class, which is a base class for observers observing the state of a subject.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const Subject& subject) = 0;
};

#endif // OBSERVER_H