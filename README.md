# MLClassifiersInCPP
3 classifiers for the LingSpam dataset, using tf-idf features, written in C++.
1) k-NN classifier
2) Naive Bayes classifier
3) Baseline classifier

The k-NN classifier either uses Euclidean distances or cosine similarity as the metric measure.

For the Naive classifier with tf-idf features, I used the following formula:

P(word|class) = word_count_in_class / total_words_in_class

where 

word_count_in_class:
sum of (tf-idf_weights of the word for all the documents belonging to that class) 
Basically replacing the counts with the tf-idf weights of the same word calculated for every document within that class.

total_words_in_class: 
sum of (tf-idf weights of all the words belonging to that class)
	
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
