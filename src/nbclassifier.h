#ifndef _NAIVEBAYESCLASSIFIER_H_
#define _NAIVEBAYESCLASSIFIER_H_

#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */

#include "classifier.h"
#include "instancepool.h"

using namespace std;

class NaiveBayesClassifier : public Classifier {
    
    public:
        // Constructor
        NaiveBayesClassifier();

        // Copy Constructor
        NaiveBayesClassifier(const NaiveBayesClassifier& original);

        // Destructor
        virtual ~NaiveBayesClassifier();

        virtual bool* classify(InstancePool trainingPool, InstancePool testPool);

        virtual NaiveBayesClassifier& operator=(const NaiveBayesClassifier& right);

};

#endif
