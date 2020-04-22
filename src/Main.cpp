#include "instancepool.h"
#include "knnclassifier.h"
#include "nbclassifier.h"
#include "baselineclassifier.h"
#include "classifierevaluator.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void printResults(const string& headerMessage, const ClassifierEvaluator& evaluator) {
   cout << headerMessage << endl 
        << "accuracy: " << evaluator.getAccuracy() << endl
        << "precision: " << evaluator.getPrecision() << endl
        << "recall: " << evaluator.getRecall() << endl;
}

int main() {

   ifstream trainingFile("training_data.txt");
   ifstream testFile("test_data.txt");
   // ifstream testFile("test_data_small.txt");
   InstancePool trainingPool, testPool;
   trainingFile >> trainingPool;
   testFile >> testPool;
   
   KNNClassifier kNN;
   kNN.setK(10);  // the k is 1 by default
   // By default, the metric is Euclidean distances.
   // kNN.setMetric("euclidean_distances");
   // kNN.setMetric("cosine_similarity");
   ClassifierEvaluator kNNEvaluator(kNN, trainingPool, testPool);
   printResults("kNN evaluation:", kNNEvaluator);

   cout << "\n";
   
   NaiveBayesClassifier nb;
   ClassifierEvaluator nbEvaluator(nb, trainingPool, testPool);
   printResults("Naive Bayes evaluation:", nbEvaluator);

   cout << "\n";

   BaselineClassifier base;
   // By default, the strategy is the Most Frequent label in the training set.
   // base.setStrategy("most_frequent");
   // base.setStrategy("random");
   ClassifierEvaluator baseEvaluator(base, trainingPool, testPool);
   printResults("Baseline evaluation:", baseEvaluator);

}
