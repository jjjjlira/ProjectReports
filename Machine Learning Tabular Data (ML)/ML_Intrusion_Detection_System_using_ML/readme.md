# Machine Learning Applied to an Intrusion Detection System
## Abstract
This research and implementation pretend to provide the reader with an analysis and comparison of the most used Machine Learning models applied to an Intrusion Detection System. In terms of Machine Learning, I defined the IDS problem as a binary classification model that catalogues packets as malicious or not. I used two datasets with totally different features and seven Machine Learning models to run the classification and compare the results obtained using Python 3 on a Jupyter notebook. Additionally, I developed aa Graphical User Interface from scratch using the Tkinter Python library and integrated it with the Machine Learning Python code deployed originally in the Jupyter Notebook. The GUI was introduced to aid students who are not entirely familiar with the python language and the machine learning libraries.

- The following Machine Learning algorithms for the Intrusion Detection System (IDS) were written in Python:
  - Naive Bayes
  - Decision Tree
  - KNN
  - Logistic Regression
  - RandomForest
  - Support Vector Machine
  - Neural Networks
- The GUI was developed in Python using TKinter toolkit library

![image](https://user-images.githubusercontent.com/104345634/218298277-a87fd973-6862-4113-9aaa-d80fcdf8ad15.png)

## Main assumptions:

a) The main assumptions are the following:
b) The malicious traffic is generated using one of the following known attacks:
   1. Password Brute force attack
   2. DoS attack
   3. XSS (Cross-Site Scripting)
   4. Infiltration (using Metasploit to run commands using a backdoor )
   5. DDoS attack
   6. Port Scan
c) The attacker has not used any additional technique to trick the Intrusion Detection System to obfuscate the threat.
d) The dataset has not been manipulated to generate good metrics when predicting the packet’s label.
e) The data set accurately represents the typical network traffic in a corporate environment, and the attacks are performed as a real hacker would do in a real-life situation.