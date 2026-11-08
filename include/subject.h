/**
 * @file subject.h
 *
 * @brief Declaration of the Subject class representing the subject in the observer pattern.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"

class Subject {

public:

    void attach(Observer observer);
    
    void detach(Observer observer);

    void notify();
};

#endif // SUBJECT_H