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


### Experiment results

<table>
	<tr>
		<th>Classifier</th>
		<th>Accuracy</th>
		<th>Precision</th>
		<th>Recall</th>
		<th># test files</th>
		<th># wrong classifications</th>
		<th># true positives</th>
		<th># false positives</th>
		<th># true positives</th>
		<th># false positives</th>
		<th># false negatives</th>
	</tr>
	<tr>
		<td>10-NN Classifier using Euclidean distances metric</td>
		<td>91.3495 %</td>
		<td>65.7534 %</td>
		<td>100 %</td>
		<td>289</td>
		<td>25</td>
		<td>48</td>
		<td>25</td>
		<td>216</td>
		<td>0</td>
	</tr>
	<tr>
		<td>1-NN Classifier using Euclidean distances metric</td>
		<td>88.9273 %</td>
		<td>60 %</td>
		<td>100 %</td>
		<td>289</td>
		<td>32</td>
		<td>48</td>
		<td>32</td>
		<td>209</td>
		<td>0</td>
	</tr>
	<tr>
		<td>10-NN Classifier using Cosine similarity metric</td>
		<td>93.0796 %</td>
		<td>71.875 %</td>
		<td>95.8333 %</td>
		<td>289</td>
		<td>20</td>
		<td>46</td>
		<td>18</td>
		<td>223</td>
		<td>2</td>
	</tr>
	<tr>
		<td>1-NN Classifier using Cosine similarity metric</td>
		<td>78.2007 %</td>
		<td>37.2881 %</td>
		<td>45.8333 %</td>
		<td>289</td>
		<td>63</td>
		<td>22</td>
		<td>37</td>
		<td>204</td>
		<td>26</td>
	</tr>
	<tr>
		<td>Naive Bayes Classifier</td>
		<td>95.8477 %</td>
		<td>82.1429 %</td>
		<td>95.8333 %</td>
		<td>289</td>
		<td>12</td>
		<td>46</td>
		<td>10</td>
		<td>231</td>
		<td>2</td>
	</tr>
	<tr>
		<td>Baseline Classifier (Most Frequent label strategy)</td>
		<td>83.391 %</td>
		<td>65.7534 %</td>
		<td>0 %</td>
		<td>289</td>
		<td>48</td>
		<td>0</td>
		<td>0</td>
		<td>241</td>
		<td>48</td>
	</tr>
	<tr>
		<td>Baseline Classifier (Random labels strategy)</td>
		<td>46.7128 %</td>
		<td>13.6986 %</td>
		<td>41.6667 %</td>
		<td>289</td>
		<td>154</td>
		<td>20</td>
		<td>126</td>
		<td>115</td>
		<td>28</td>
	</tr>
</table>
