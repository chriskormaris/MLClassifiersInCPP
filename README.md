# MLClassifiersInCPP
3 classifiers for the LingSpam dataset, using tf-idf features, written in C++.
1) k-NN classifier
2) Naive Bayes classifier
3) Baseline classifier

The k-NN classifier either uses Euclidean distances or cosine similarity as the metric measure.

The Baseline classifier is a dummy classifier that either classifies all the data 
with the most frequent label in the training set or with random labels altogether.

The program is tested on a Linux machine.


### How to compile
Run the script "compile.sh". Type:
```bash
./compile.sh
```

### How to run
1. First construct the dataset. Run:
```bash
./bin/construct_dataset.o
```

2. Then, classify the dataset, with the 3 classifiers. Run:
```bash
./bin/Main.o
```
