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
   InstancePool trainingPool, testPool;
   trainingFile >> trainingPool;
   testFile >> testPool;
   
   KNNClassifier kNN;
   // By default, the number of neighbours, k is 1.
   kNN.setK(10);
   // By default, the metric is Euclidean distances.
   kNN.setMetric("euclidean_distances");
   ClassifierEvaluator kNNEvaluator1(kNN, trainingPool, testPool);
   printResults("10-NN Classifier using Euclidean distances metric evaluation:", kNNEvaluator1);

   cout << "\n";
   
   kNN.setK(1);
   kNN.setMetric("euclidean_distances");
   ClassifierEvaluator kNNEvaluator2(kNN, trainingPool, testPool);
   printResults("1-NN Classifier using Euclidean distances metric evaluation:", kNNEvaluator2);

   cout << "\n";
      
   kNN.setK(10);
   kNN.setMetric("cosine_similarity");
   ClassifierEvaluator kNNEvaluator3(kNN, trainingPool, testPool);
   printResults("1-NN Classifier using cosine similarity metric evaluation:", kNNEvaluator3);

   cout << "\n";
      
   kNN.setK(1);
   kNN.setMetric("cosine_similarity");
   ClassifierEvaluator kNNEvaluator4(kNN, trainingPool, testPool);
   printResults("1-NN Classifier using cosine similarity metric evaluation:", kNNEvaluator4);

   cout << "\n";

   NaiveBayesClassifier nb;
   ClassifierEvaluator nbEvaluator(nb, trainingPool, testPool);
   printResults("Naive Bayes evaluation:", nbEvaluator);

   cout << "\n";

   BaselineClassifier base;
   // By default, the strategy is the Most Frequent label in the training set.
   base.setStrategy("most_frequent");
   ClassifierEvaluator baseEvaluator1(base, trainingPool, testPool);
   printResults("Baseline (Most Frequent label strategy) evaluation:", baseEvaluator1);
   
   cout << "\n";

   base.setStrategy("random");
   ClassifierEvaluator baseEvaluator2(base, trainingPool, testPool);
   printResults("Baseline (Random labels strategy) evaluation:", baseEvaluator2);

}
