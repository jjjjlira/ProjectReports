#! /usr/bin/env python3

# v. 2022-03-30 00:11
# This is the one presented as Capstone Project!!!
# Dataframe grid with pack
# with logo
# Things to do:

# - Why are less values in TP, TN, FP, FN in neural Networks than in Deep Learning
# - Scroll in data grid
# - Reformulate data grid with other kind of widget


# - DISABLED Logic for "Select File"
# - FIXED! First letter cut in definitions (workaround with a space at the beginning)
# - FIXED! Plot/Draw AUC-ROC curve for the algorithms
# - FIXED! Introduce Deep Learning (hidden layers)
# - FIXED! Add TP, FP, TN, FN to Neural networks and Deep Learning

# Program: Artificial Intelligence Intrusion Detection System
# CBER710 Capstone Project
# Centennial College
# Student: Jose Lira

""" Intrusion Detection System using Machine Learning """

import gc
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)
import numpy as np
import os
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.linear_model import *
from sklearn.metrics import accuracy_score
from sklearn.metrics import auc
from sklearn.metrics import confusion_matrix
from sklearn.metrics import f1_score
from sklearn.metrics import precision_score
from sklearn.metrics import recall_score
from sklearn.metrics import roc_curve

from sklearn.metrics import RocCurveDisplay
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import *
from sklearn.neighbors import *
from sklearn.preprocessing import StandardScaler
from sklearn.tree import *
import tensorflow as tf
#from tensorflow.keras import layers
from tkinter import *
import tkinter as tk
import tkinter.messagebox as msgbox
from PIL import ImageTk, Image
from tkinter import messagebox
from tkinter import filedialog


default_algorithm_value = 0
data_full = np.array([])
data_set = pd.DataFrame()

# Dictionary of description and general information of the pre-defined datasets
dataset_dict = {1: ["Canadian Institute for Cybersecurity",
                    "The Canadian Institute for Cybersecurity CICIDS2017 dataset contains benign and the most up-to-date common attacks, which resembles the true real-world data (PCAPs).It also includes the results of the network traffic analysis using CICFlowMeter with labeled flows based on the time stamp, source, and destination IPs, source and destination ports, protocols and attack (CSV files)."],
                0: ["UNSW Sydney",
                    "This dataset has nine types of attacks, namely, Fuzzers, Analysis, Backdoors, DoS, Exploits, Generic, Reconnaissance, Shellcode and Worms. The Argus, Bro-IDS tools are used and twelve algorithms are developed to generate totally 49 features with the class label."]
                }

# Dictionary of the implemented algorithms in the following format:  {key: ["Algorithm name", "Algorithm Description"]
algorithm_dict = {0: ["Naïve-Bayes",
                      "Naive Bayes is a simple technique for constructing classifiers: models that assign class labels to problem instances, represented as vectors of feature values, where the class labels are drawn from some finite set."],
                  1: ["Random Forest",
                      "The random forest is a classification algorithm consisting of many decisions trees. It uses bagging and feature randomness when building each individual tree to try to create an uncorrelated forest of trees whose prediction by committee is more accurate than that of any individual tree."],
                  2: ["Decision Tree",
                      "Decision Tree is a Supervised learning technique that can be used for both classification and Regression problems, but mostly it is preferred for solving Classification problems."],
                  3: ["Logistic Regression",
                      "Logistic regression is a statistical model that in its basic form uses a logistic function to model a binary dependent variable, although many more complex extensions exist. In regression analysis, logistic regression (or logit regression) is estimating the parameters of a logistic model (a form of binary regression)."],
                  4: ["Support Vector Machines",
                      "Support-Vector Machines (SVMs) are supervised learning models with associated learning algorithms that analyze data for classification and regression analysis. Given a set of training examples, each marked as belonging to one of two categories, an SVM training algorithm builds a model that assigns new examples to one category or the other, making it a non-probabilistic binary linear classifier."],
                  5: ["K-Nearest Neighbors",
                      "The k-nearest neighbors (KNN) algorithm is a simple, easy-to-implement supervised machine learning algorithm that can be used to solve both classification and regression problems."],
                  6: ["Neural Networks",
                      "Neural networks are a set of algorithms, modeled loosely after the human brain, that are designed to recognize patterns. They interpret sensory data through a kind of machine perception, labeling or clustering raw input."],
                  7: ["Deep Learning",
                      "Deep learning is a subset of machine learning, which is essentially a neural network with two or more layers. These neural networks attempt to simulate the behavior of the human brain—albeit far from matching its ability—allowing it to “learn” from large amounts of data."]
                  }

metrics_dict = {0: ["Accuracy (AC):", " AC = ( TP + TN ) / ( TP + TN + FP + FN )"],
                1: ["Precision (PR):", "PR = TP / ( TP + FP )"],
                2: ["Recall (RC):", "RC =TP / ( TP + FN )"],
                3: ["F1 Score (F1):", "F1 =  2TP / ( 2TP + FP + FN )"]}

class IDS(tk.Tk):
    def __init__(self):
        super().__init__()
        self.geometry("1670x1050")
        #self.resizable(0,0)
        #self.resizable(width=None, height=None)
        self.title("Intrusion Detection System Dataset Analizer using Machine Learning")

        # Correct this to reference the dictionary of datasets!!!!!!!!!!!!!!!!!!!!
        self. mainpath = tk.StringVar()
        self.mainpath.set(r"C:\Users\jlira\Training\_Classes\CBER 710 Capstone Project\Data\UNSW-NB15 - CSV Files\Datasets")
        # self.mainpath.set(r"D:\TrainingNew\_Classes\CBER 710 Capstone Project\Data\UNSW-NB15 - CSV Files\Datasets")

        self.algorithm = IntVar()

        self.TP = IntVar()
        self.TP.set(0)
        self.TN = IntVar()
        self.TN.set(0)
        self.FP = IntVar()
        self.FP.set(0)
        self.FN = IntVar()
        self.FN.set(0)

        self.dataset_description = tk.StringVar() #dataset_dict[0][1]

        self.status_bar_text = tk.StringVar()
        self.status_bar_text.set("Algorithm selected: " + algorithm_dict[default_algorithm_value][0])

        self.label_algorithm_description_text = tk.StringVar()
        self.label_algorithm_description_text.set(algorithm_dict[default_algorithm_value][1])

        self.label_status_frame_text = tk.StringVar()
        self.label_status_frame_text.set("Please, select a Dataset and click run... ")
        #self.label_status_frame_text.set("Database " + dataset_dict[0][1] + " selected. \nAlgorithm" + algorithm_dict[self.algorithm.get()][0] +" selected.")

        self.drop_down_clicked = StringVar()

        self.label_accuracy_text = tk.StringVar()
        self.label_accuracy_text.set("")

        self.label_precision_text = tk.StringVar()
        self.label_precision_text.set("")

        self.label_recall_text = tk.StringVar()
        self.label_recall_text.set("")

        self.label_f1_text = tk.StringVar()
        self.label_f1_text.set("")

        self.label_confusion_text = tk.StringVar()
        self.label_confusion_text.set("")

        # Frame 00 (in main window, contains other frames just for organization purpose)
        frame_00 = LabelFrame(self, padx=5, pady=5, width=1665, height=280)
        frame_00.grid(row=0, column=0, sticky=W+E+N+S)
        frame_00.grid_propagate(False)

        # Frame 01 (inside Frame 00)
        frame_01 = LabelFrame(frame_00, text="Select a Dataset or choose a CSV file:", padx=20, pady=60,width=300, height=265)
        frame_01.grid(row=0, column=0, sticky=W+E+N+S)
        frame_01.grid_propagate(False)
        self.drop_down_clicked.set(dataset_dict[0][0])
        drop = OptionMenu(frame_01, self.drop_down_clicked, dataset_dict[0][0], dataset_dict[1][0], command=self.drop_down_clicked_changed)
        drop.configure(width=30, justify= LEFT)
        drop.grid_propagate(False)
        drop.grid(row=0, column=0, sticky=W)
        # mybutton_04 = Button(frame_01, text="Select File...", command=lambda: self.click_button_file_dialog(), anchor=W)
        # mybutton_04.grid(row=1, column=0, sticky=W+E)

        # frame_14 (contains the logo of the application)
        frame_14 = Frame(frame_01, width=120, height=120)
        frame_14.place(anchor='center', relx=0.46, rely=0.9)
        self.img = (Image.open("LOGO_JOSE_LIRA_2.png"))
        self.logo = ImageTk.PhotoImage(self.img.resize((105, 96), Image.ANTIALIAS))
        label_45 = Label(frame_14, image=self.logo)
        label_45.grid(row=2, column=0)


        # Frame 02 (inside Frame 00)
        frame_02 = LabelFrame(frame_00, text="Select Machine Learning Algorithm:", padx=20, pady=10, width=270, height=265)
        frame_02.grid_propagate(False)
        frame_02.grid(row=0, column=1, sticky=W+E+N+S)
        for i in range(len(algorithm_dict)):
            Radiobutton(frame_02, text=algorithm_dict.get(i)[0], variable=self.algorithm, value=i,
                        command=self.radio_button_clicked).grid(row=i, column=0, sticky=W)
        mybutton_03 = Button(frame_02, text="Run", command=lambda: self.run_button_clicked(), anchor=W)
        mybutton_03.grid(row=8, column=0)

        # Frame 07 (inside Frame 00)
        self.frame_07 = LabelFrame(frame_00, text="Status:", padx=10, pady=10, width=360, height=265)
        self.frame_07.grid_propagate(False)
        self.frame_07.grid(row=0, column=2, sticky=W+E+N+S)
        self.label_08 = Label(self.frame_07, textvar=self.label_status_frame_text, justify=LEFT, wraplength=320)
        self.label_08.grid(row=0, column=0, sticky=W)

        # Frame 05 (inside Frame 00)
        frame_05 = LabelFrame(frame_00, text="Evaluation of AI Algorithm:", padx=10, pady=10, width=295, height=265)
        frame_05.grid_propagate(False)
        frame_05.grid(row=0, column=3, sticky=W+E+N+S)
        #num_temp = 0.00
        label_01 = Label(frame_05, text=metrics_dict[0][0], justify=LEFT).grid(row=0, column=0, sticky=W)
        label_02 = Label(frame_05, text=metrics_dict[1][0], justify=LEFT).grid(row=1, column=0, sticky=W)
        label_03 = Label(frame_05, text=metrics_dict[2][0], justify=LEFT).grid(row=2, column=0, sticky=W)
        label_04 = Label(frame_05, text=metrics_dict[3][0] + '\n', justify=LEFT).grid(row=3, column=0, sticky=W)

        label_09 = Label(frame_05, text="Definitions:", justify=LEFT).grid(row=4, column=0, sticky=W)
        label_37 = Label(frame_05, text=metrics_dict[0][1], justify=LEFT).grid(row=5, column=0, sticky=W)
        label_38 = Label(frame_05, text=metrics_dict[1][1], justify=LEFT).grid(row=6, column=0, sticky=W)
        label_39 = Label(frame_05, text=metrics_dict[2][1], justify=LEFT).grid(row=7, column=0, sticky=W)
        label_40 = Label(frame_05, text=metrics_dict[3][1], justify=LEFT).grid(row=8, column=0, sticky=W)

        label_10 = Label(frame_05, textvar=self.label_accuracy_text, justify=LEFT).grid(row=0, column=1, sticky=W)
        label_11 = Label(frame_05, textvar=self.label_precision_text, justify=LEFT).grid(row=1, column=1, sticky=W)
        label_12 = Label(frame_05, textvar=self.label_recall_text, justify=LEFT).grid(row=2, column=1, sticky=W)
        label_13 = Label(frame_05, textvar=self.label_f1_text, justify=LEFT).grid(row=3, column=1, sticky=W)
        label_14 = Label(frame_05, textvar=self.label_confusion_text, justify=LEFT).grid(row=5, column=0, sticky=W)

        # Frame 13 (inside Frame 00, next to frame 5)
        frame_13 = LabelFrame(frame_00, text="Confusion Matrix:", padx=10, pady=10, width=340, height=265)
        frame_13.grid_propagate(False)
        frame_13.grid(row=0, column=4, sticky=W + E + N + S)
        label_15 = Label(frame_13, width=20, height=4, text="", justify=LEFT).grid(row=0, column=0, columnspan=2,rowspan=2, sticky=W)
        label_16 = Label(frame_13, width=20, height=2,text="ACTUAL VALUES", justify=LEFT).grid(row=0, column=2, columnspan=2, sticky=W)
        label_17 = Label(frame_13, width=10, height=2,text="Positive", justify=LEFT, bg='ORANGE',relief=RIDGE).grid(row=1, column=2, sticky=W)
        label_18 = Label(frame_13, width=10, height=2,text="Negative", justify=LEFT,bg='ORANGE',relief=RIDGE).grid(row=1, column=3, sticky=W)
        label_19 = Label(frame_13, width=10, height=4,text="PREDICTED \nVALUES", justify=LEFT).grid(row=2, column=0, rowspan=2, sticky=W)
        label_20 = Label(frame_13, width=10, height=2,text="Positive", justify=LEFT, bg='ORANGE',relief=RIDGE).grid(row=2, column=1, sticky=W)
        label_21 = Label(frame_13, width=10, height=2,text="TP", justify=LEFT,relief=RIDGE,bg='GREEN').grid(row=2, column=2, sticky=W)
        label_22 = Label(frame_13, width=10, height=2,text="FP", justify=LEFT,relief=RIDGE,bg='RED').grid(row=2, column=3, sticky=W)
        label_23 = Label(frame_13, width=10, height=2,text="Negative", justify = LEFT, bg='ORANGE',relief=RIDGE).grid(row=3, column=1, sticky=W)
        label_24 = Label(frame_13, width=10, height=2,text="FN", justify=LEFT,relief=RIDGE,bg='RED').grid(row=3, column=2, sticky=W)
        label_25 = Label(frame_13, width=10, height=2,text="TN", justify = LEFT,relief=RIDGE,bg='GREEN').grid(row=3, column=3, sticky=W)

        label_41 = Label(frame_13, text="TP = ", justify = LEFT).grid(row=5, column=0, sticky=W)
        label_42 = Label(frame_13, text="FP = ", justify = LEFT).grid(row=6, column=0, sticky=W)
        label_43 = Label(frame_13, text="FN = ", justify = LEFT).grid(row=7, column=0, sticky=W)
        label_44 = Label(frame_13, text="TN = ", justify = LEFT).grid(row=8, column=0, sticky=W)

        label_41 = Label(frame_13, textvariable=self.TP, justify = LEFT).grid(row=5, column=1, sticky=W)
        label_42 = Label(frame_13, textvariable=self.FP, justify = LEFT).grid(row=6, column=1, sticky=W)
        label_43 = Label(frame_13, textvariable=self.FN, justify = LEFT).grid(row=7, column=1, sticky=W)
        label_44 = Label(frame_13, textvariable=self.TN, justify = LEFT).grid(row=8, column=1, sticky=W)

        # Frame 12 (inside Frame 00, contains buttons)
        frame_12 = LabelFrame(frame_00, text="Utilities:", padx=10, pady=10, width=82, height=265)
        frame_12.grid_propagate(False)
        frame_12.grid(row=0, column=5, sticky=W+E+N+S)

        # Clear Button (inside Frame 00)
        clear_button = tk.Button(frame_12, text="Clear", command=self.clear_data, padx=10, pady=5)
        clear_button.grid(row=0, column=0)#, sticky=W+E)

        # Exit Button (inside Frame 00)
        exit_button = tk.Button(frame_12, text="Exit", command=self.say_goodbye, padx=10, pady=5)
        exit_button.grid(row=1, column=0, sticky=W+E)

        # Frame 03 (in main window just below Frame 00)
        frame_03 = LabelFrame(self, text="Dataset Description:", padx=5, pady=5, width=1210, height=70,relief=RIDGE)
        frame_03.grid_propagate(False)
        self.dataset_description.set(dataset_dict[0][1])
        frame_03.grid(row=1, column=0, columnspan=1, sticky=W+E)
        label_06 = Label(frame_03, textvar=self.dataset_description, anchor="w", justify=LEFT,wraplength = 1400)
        label_06.grid(row=0, column=0, sticky=W)

        # Frame 04 (in main window just below Frame 03)
        frame_04 = LabelFrame(self, text="AI Algorithm Description:", padx=5, pady=5, width=1210, height=60,relief=RIDGE)
        frame_04.grid_propagate(False)
        frame_04.grid(row=2, column=0, columnspan=1, sticky=W+E)
        label_07 = Label(frame_04, textvar=self.label_algorithm_description_text, anchor=W, justify=LEFT,wraplength = 1400)
        label_07.grid(row=0, column=0, sticky=W)

        # Frame 10 contains frame 09 and 10. Plot and data grid
        frame_10 = LabelFrame(self, text="Plotting and Data Information:", padx=5, pady=5,width=1220, height=50)
        frame_10.grid(row=4, column=0, sticky=W+E)

        # Frame 09 (inside frame 10. Contains the canvas that contains figure that contains the subplot)
        frame_09 = LabelFrame(frame_10, text="Plot:", padx=5, pady=5)# ,width=610, height=50)
        frame_09.pack(side=LEFT)
        self.fig = plt.figure(figsize=(5, 5), dpi=100)  # the figure that will contain the plot
        self.plot1 = self.fig.add_subplot(111)
        self.canvas = FigureCanvasTkAgg(self.fig, master=frame_09)
        #self.canvas.draw()
        self.canvas.get_tk_widget().grid(row=0, column=0, sticky=W+E)

        # Frame 11 (inside Frame 10, next to frame 09. Contains the dataframe grid)
        frame_11 = LabelFrame(frame_10, text="Dataframe grid:", padx=5, pady=5)#,width=610, height=50)
        frame_11.pack(expand=1, fill=BOTH)
        scrollbar_x = Scrollbar(frame_11, orient="horizontal")
        scrollbar_x.pack(side=BOTTOM, fill=X)
        scrollbar_y = Scrollbar(frame_11)
        scrollbar_y.pack(side=RIGHT,  fill=Y)

        # list=[1,2,3,4]
        # listbox = Listbox(frame_11, listvariable=list)
        # listbox.pack(side=LEFT, expand=1, fill=BOTH)
        # listbox.config(yscrollcommand=scrollbar_x.set)
        # scrollbar_x.config(command=listbox.xview)
        #
        # listbox.config(xscrollcommand=scrollbar_y.set)
        # scrollbar_y.config(command=listbox.yview)

        self.frame_12 = LabelFrame(frame_11, padx=5, pady=5)

         # Status bar (at the BOTTOM of the main window)
        status = Label(self, textvar= self.status_bar_text , bd=1, relief=SUNKEN, anchor=W)
        status.grid(row=5, column=0, columnspan=3, sticky=W + E)

    def show_data_in_grid(self, my_list_of_headers, my_cell_list):
        for i in range(len(my_list_of_headers)):
            label = Label(self.frame_12, width=20, height=2, text=my_list_of_headers[i], bg='blue', fg='white', relief=RIDGE)
            label.grid(row=0, column=i)
        for i in range(len(my_cell_list)):
            for j in range(len(my_cell_list[i])):
                label = Label(self.frame_12, width=20, height=2, text=my_cell_list[i][j], relief=RIDGE,
                              bg='white' if i % 2 else '#F0F0F0')
                label.grid(row=i+1, column=j)
        self.frame_12.pack(side=LEFT, expand=1, fill=BOTH)

    def show_data_in_grid_0(self):
        #data_to_show = data_full.head()
        for iy, ix in data_full.ndindex(data_full.shape):
            print(data_full[iy, ix])

    def show_data_in_grid_1(self):
        for rowIndex, row in data_full.iterrows():  # iterate over rows
            for columnIndex, value in row.items():
                print(value, end="\t")
            print()

    def clear_status_frame_text(self):
        self.label_status_frame_text.set("Jose's Testing")
        self.label_08 = self.Label(self.frame_07, textvar=self.label_status_frame_text, justify=LEFT, wraplength=290)
        self.label_08.grid(row=0, column=0, sticky=W)

    def radio_button_clicked(self):
        self.status_bar_text.set("Algorithm selected: " + algorithm_dict[self.algorithm.get()][0])
        self.label_algorithm_description_text.set(algorithm_dict[self.algorithm.get()][1])

    def drop_down_clicked_changed(self, option_clicked):
        if option_clicked == dataset_dict[0][0]:
            self.dataset_description.set(dataset_dict[0][1])
            self.update_idletasks()
        elif option_clicked == dataset_dict[1][0]:
            self.dataset_description.set(dataset_dict[1][1])
            self.update_idletasks()

    def click_button_file_dialog(self):
        file_name = filedialog.askopenfilename(initialdir=r"C:\Users\jlira\Training\_Classes\CBER 710 Capstone Project\Data",
                                               title="Select a File",
                                               filetypes=(("csv files", "*.csv"), ("all files", "*.*")))
        print(file_name)

    def say_goodbye(self):
        if msgbox.askyesno("Close Window?", "Would you like to close this window?"):
            self.after(10, self.destroy)
        else:
            return

    def clear_data(self):
        self.label_status_frame_text.set("                                                                                ")
        self.update_idletasks()
        self.plot1.cla()
        self.canvas.draw()
        self.update_idletasks()
        self.label_status_frame_text.set("")
        self.update_idletasks()
        self.TP.set(0)
        self.TN.set(0)
        self.FP.set(0)
        self.FN.set(0)
        self.update_idletasks()
        self.label_accuracy_text.set("")
        self.label_precision_text.set("")
        self.label_recall_text.set("")
        self.label_f1_text.set("")
        self.label_confusion_text.set("")
        self.update_idletasks()
        for widget in self.frame_12.winfo_children():
            widget.destroy()
        self.update_idletasks()

    def run_button_clicked(self):
        self.label_status_frame_text.set("                                                                            ")
        self.plot1.cla()
        self.canvas.draw()
        self.update_idletasks()
        self.label_status_frame_text.set("")
        #self.label_status_frame_text.delete(0, END)
        #self.clear_status_frame_text()
        self.update_idletasks()
        if (self.drop_down_clicked.get()) == dataset_dict[1][0]:
            self.mainpath.set(r"C:\Users\jlira\Training\_Classes\CBER 710 Capstone Project\Data\MachineLearningCVE\Data")
            self.loading_databases()
            self.clean_data_0()
            #self.show_data_in_grid()
        elif (self.drop_down_clicked.get()) == dataset_dict[0][0]:
            self.mainpath.set(r"C:\Users\jlira\Training\_Classes\CBER 710 Capstone Project\Data\UNSW-NB15 - CSV Files\Datasets")
            self.loading_databases()
            self.clean_data_1()
            #self.show_data_in_grid()
        else:
            # error, abort the program
            self.mainpath.set(r"C:\Users\jlira\Training\_Classes\CBER 710 Capstone Project\Data\UNSW-NB15 - CSV Files\Datasets")
        training_samples, testing_samples, training_targets, testing_targets = self.process_data()
        if self.algorithm.get() == 0:
            self.run_Naive_Bayes(training_samples, testing_samples, training_targets, testing_targets)
        elif self.algorithm.get() == 1:
            self.run_random_forest(training_samples, testing_samples, training_targets, testing_targets)
        elif self.algorithm.get() == 2:
            self.run_Decision_Tree(training_samples, testing_samples, training_targets, testing_targets)
        elif self.algorithm.get() == 3:
            self.run_logistic_regression(training_samples, testing_samples, training_targets, testing_targets)
        elif self.algorithm.get() == 4:
            self.run_SVM(training_samples, testing_samples, training_targets, testing_targets)
        elif self.algorithm.get() == 5:
            self.run_knn(training_samples, testing_samples, training_targets, testing_targets)
        elif self.algorithm.get() == 6:
            self.run_Neural_Network(training_samples, testing_samples, training_targets, testing_targets)
        elif self.algorithm.get() == 7:
            self.run_Deep_Learning(training_samples, testing_samples, training_targets, testing_targets)

    def loading_databases(self):
        global data_full
        mainpath = self.mainpath.get()
        # Loading all the datasets in the working directory
        path, dirs, ds_file_names = next(os.walk(mainpath))
        file_count = len(ds_file_names)
        #self.label_status_frame_text.set("")
        #self.update_idletasks()
        self.label_status_frame_text.set(
            self.label_status_frame_text.get() + "[+] Loading dataset file(s). Please, wait...                          \n")
        self.update_idletasks()
        #print(r"[+] Loading dataset file(s). Please, wait...")
        dataset_list = []
        for i in range(file_count):
            fullpath = os.path.join(mainpath, ds_file_names[i])
            dataset_list.append(pd.read_csv(fullpath, encoding='utf8', low_memory=False))  # iso-8859-1 #utf8
            self.label_status_frame_text.set(
                self.label_status_frame_text.get() + "File loaded: " + str(ds_file_names[i]) + "\n")
            self.update_idletasks()
            #print("File loaded: " + str(ds_file_names[i]))
        self.label_status_frame_text.set(
            self.label_status_frame_text.get() + "[+] " + str(file_count) + " files(s) uploaded successfully" + "\n")
        self.update_idletasks()
        #print("[+] " + str(file_count) + " files(s) uploaded successfully")
        # Merge all the datasets loaded
        data_full = pd.concat(
            dataset_list,
            axis=0,
            join="outer",
            ignore_index=False,
            keys=None,
            levels=None,
            names=None,
            verify_integrity=False,
            copy=True)
        del dataset_list
        gc.collect()
        data_to_show = data_full.head(12)
        list_of_headers = list(data_to_show.columns.values)
        mylist = data_to_show.values.tolist()
        #print(mylist)
        self.show_data_in_grid(list_of_headers,mylist)
        # for rowIndex, row in data_to_show.iterrows():  # iterate over rows
        #     for columnIndex, value in row.items():
        #         print(value, end="\t")
        #     print()
        return

    def ip_to_int(sel, ip_ser): # Auxiliary fucntion to convert IP to integers
        ips = ip_ser.str.split('.', expand=True).astype(np.int64).values
        mults = np.tile(np.array([24, 16, 8, 0]), len(ip_ser)).reshape(ips.shape)
        return np.sum(np.left_shift(ips, mults), axis=1)

    def clean_data_0(self):  # Cleaning the Data before processing
        global data_full
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Cleaning the Data... " + "\n")
        self.update_idletasks()
        # Delete all blank spaces in the columns titles
        data_full.columns = data_full.columns.str.replace(' ', '')
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "Blanks spaces in columns deleted. " + "\n")
        self.update_idletasks()
        # data_full.columns.values
        # Cleaning the NaN's deleting the rows if a NaN is found in any column            ## data1 = data[np.isfinite(data).all(1)]
        data_full = data_full.replace([np.inf, -np.inf], np.nan).dropna(axis=0)
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "Nulls replaced by zeros. " + "\n")
        self.update_idletasks()
        # Create a dictionary for the values of the Label
        # Commented as only 2 states will be used in the labels in this Dataset (not 6)
        values_label = data_full['Label'].unique()
        values_label_dict = {}
        counter = 0
        for value in values_label:
            if value not in values_label_dict.keys():
                values_label_dict[value] = counter
                counter += 1
        # print(values_label_dict)
        # converting to 2 states BENIGN : 0, MALIGN: 1
        values_label_dict = {'BENIGN': 0, 'DDoS': 1, 'PortScan': 1, 'Bot': 1, 'Infiltration': 1,
                             'Web Attack ï¿½ Brute Force': 1, 'Web Attack ï¿½ XSS': 1,
                             'Web Attack ï¿½ Sql Injection': 1,
                             'FTP-Patator': 1, 'SSH-Patator': 1, 'DoS slowloris': 1, 'DoS Slowhttptest': 1,
                             'DoS Hulk': 1,
                             'DoS GoldenEye': 1, 'Heartbleed': 1, 'NeedManualLabel': 1}
        # print(values_label_dict)
        # Replace strings in the Label vector with the integer values in the dictionary
        data_full.Label = [values_label_dict[item] for item in data_full.Label]

        # eliminates nulls
        data_full = data_full.dropna(how='any', axis=1)

    def clean_data_1(self):  # Cleaning the Data before processing
        global data_full
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Cleaning the Data... " + "\n")
        self.update_idletasks()
        # Delete all blank spaces in the columns titles
        data_full.columns = data_full.columns.str.replace(' ', '')
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "Blanks spaces in columns deleted. " + "\n")
        self.update_idletasks()
        # Replacing all nulls with '0's
        data_full = data_full.fillna(0)
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "Nulls replaced by zeros. " + "\n")
        self.update_idletasks()
        # Delete Attack category column: 'attack_cat' (The name of each attack category)
        # Nine categories e.g. Fuzzers, Analysis, Backdoors, DoS Exploits, Generic, Reconnaissance, Shellcode and Worms
        data_full.drop(['attack_cat'], axis=1, inplace=True)
        # Converting IP addresses to integers in both 'srcip' and 'dstip' columns
        data_full['srcip'] = self.ip_to_int(data_full.srcip)
        data_full['dstip'] = self.ip_to_int(data_full.dstip)
        # Convert 'dsport' column from object to int
        data_full['dsport'] = pd.to_numeric(data_full.dsport, errors='coerce').fillna(0).astype(int)
        # Convert 'sport' column from object to int
        data_full['sport'] = pd.to_numeric(data_full.dsport, errors='coerce').fillna(0).astype(int)
        # Replace null values in 'ct_ftp_cmd' to zero
        # ct_ftp_cmd = No of flows that has a command in ftp session.
        # Replace with '0's
        data_full['ct_ftp_cmd'] = pd.to_numeric(data_full.dsport, errors='coerce').fillna(0).astype(int)
        # Replace categorical columns (strings) with integer values generated in a dictionary (one dictionary per column)
        # Create a list of dictionaries for the values of the categorical columns
        list_of_dict = []
        for col in data_full.columns:
            if (data_full[col].dtype == object):
                values_label = data_full[col].unique()
                values_label_dict = {}
                counter = 0
                for value in values_label:
                    if value not in values_label_dict.keys():
                        values_label_dict[value] = counter
                        counter += 1
                list_of_dict.append(values_label_dict)
                # Replace strings in the iterated column with the integer values taken from the respective generated dictionary
                data_full[col] = [values_label_dict[item] for item in data_full[col]]
                data_full[col].unique()
        self.label_status_frame_text.set(
            self.label_status_frame_text.get() + "Number of categorical columns modified: " + str(len(list_of_dict)) + "\n")
        self.update_idletasks()
        # print(list_of_dict)
        # eliminates nulls in the dataframe
        data_full = data_full.dropna(how='any', axis=1)
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "Infinitys and NaNs dropped. " + "\n")
        self.update_idletasks()
        # data_full.shape
        return

    def process_data(self):
        global data_full
        # Creates "samples" Dataset taken all the columns except the Label
        samples = data_full.iloc[:, [i for i in range(0, data_full.shape[1] - 1)]].values
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Standardizing the data. " + "\n")
        self.update_idletasks()
        # Standardizes the "samples"
        samples_standardized = StandardScaler().fit_transform(samples)
        # data_full.shape
        # Creates the dataset for the "Label" column
        targets = data_full['Label'].values
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Splitting the data in Training (70%) and Testing (30%)." + "\n")
        self.update_idletasks()
        # spliting the samples (features) and the targets (Labels) in 70% training and 30% testing
        training_samples, testing_samples, training_targets, testing_targets = train_test_split(
            samples_standardized,
            targets, test_size=0.3,
            random_state=0)
        return training_samples, testing_samples, training_targets, testing_targets


    def plot_curve_ROC(self, roc_curve, fpr, tpr, roc_auc):
        """Plot a Receiver operating characteristic (ROC) curve."""
        self.plot1.cla()
        lw = 2
        self.plot1.plot(
            fpr,
            tpr,
            color="darkorange",
            lw=lw,
            label="ROC curve (area = %0.2f)" % roc_auc,
        )
        self.plot1.plot([0, 1], [0, 1], color="navy", lw=lw, linestyle="--")
        self.plot1.set_xlim([0.0, 1.0])
        self.plot1.set_ylim([0.0, 1.05])
        self.plot1.set_xlabel("False Positive Rate")
        self.plot1.set_ylabel("True Positive Rate")
        self.plot1.set_title("Receiver operating characteristic (ROC)")
        self.plot1.legend(loc="lower right")
        # self.plot1.show()
        self.plot1.legend()
        self.canvas.draw()


    def run_Naive_Bayes(self, training_samples, testing_samples, training_targets, testing_targets):
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Training the dataset using Naive-Bayes. Please wait...")
        self.update_idletasks()
        gnb = GaussianNB()
        gnb.fit(training_samples, training_targets)
        gnb_prediction = gnb.predict(testing_samples)
        gnb_accuracy = 100.0 * accuracy_score(testing_targets, gnb_prediction)
        gnb_precision = 100.0 * precision_score(testing_targets, gnb_prediction)
        gnb_recall = 100.0 * recall_score(testing_targets, gnb_prediction)
        gnb_f1_score = 100.0 * f1_score(testing_targets, gnb_prediction)
        gnb_confusion_matrix = confusion_matrix(testing_targets, gnb_prediction)
        self.label_accuracy_text.set("{:.2f}".format(gnb_accuracy) + "%")
        self.label_precision_text.set("{:.2f}".format(gnb_precision) + "%")
        self.label_recall_text.set("{:.2f}".format(gnb_recall) + "%")
        self.label_f1_text.set("{:.2f}".format(gnb_f1_score) + "%")
        self.TP.set(gnb_confusion_matrix[0][0])
        self.FP.set(gnb_confusion_matrix[0][1])
        self.FN.set(gnb_confusion_matrix[1][0])
        self.TN.set(gnb_confusion_matrix[1][1])
        # roc_curve = RocCurveDisplay.from_estimator(gnb, testing_samples, testing_targets)
        fpr, tpr, thresholds = roc_curve(testing_targets, gnb_prediction, )
        roc_auc = auc(fpr, tpr)
        self.plot_curve_ROC(roc_curve, fpr, tpr, roc_auc)
        # self.label_confusion_text.set("\n\n" + str(gnb_confusion_matrix))


    def run_Decision_Tree(self, training_samples, testing_samples, training_targets, testing_targets):
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Training the dataset using Decision Tree. Please wait..." )
        self.update_idletasks()
        dtc = DecisionTreeClassifier(random_state=0)
        dtc.fit(training_samples, training_targets)
        dtc_prediction = dtc.predict(testing_samples)
        dtc_accuracy = 100.0 * accuracy_score(testing_targets, dtc_prediction)
        dtc_precision = 100.0 * precision_score(testing_targets, dtc_prediction)
        dtc_recall = 100.0 * recall_score(testing_targets, dtc_prediction)
        dtc_f1_score = 100.0 * f1_score(testing_targets, dtc_prediction)  # , average="macro")
        dtc_confusion_matrix = confusion_matrix(testing_targets, dtc_prediction)
        self.label_accuracy_text.set("{:.2f}".format(dtc_accuracy) + "%")
        self.label_precision_text.set("{:.2f}".format(dtc_precision) + "%")
        self.label_recall_text.set("{:.2f}".format(dtc_recall) + "%")
        self.label_f1_text.set("{:.2f}".format(dtc_f1_score) + "%")
        self.TP.set(dtc_confusion_matrix[0][0])
        self.FP.set(dtc_confusion_matrix[0][1])
        self.FN.set(dtc_confusion_matrix[1][0])
        self.TN.set(dtc_confusion_matrix[1][1])
        # roc_curve = RocCurveDisplay.from_estimator(dtc, testing_samples, testing_targets)
        fpr, tpr, thresholds = roc_curve(testing_targets, dtc_prediction, )
        roc_auc = auc(fpr, tpr)
        self.plot_curve_ROC(roc_curve, fpr, tpr, roc_auc)


    def run_SVM(self, training_samples, testing_samples, training_targets, testing_targets):
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Training the dataset using Suppport Vector Machine. Please wait..." )
        self.update_idletasks()
        svmcl = SVC(random_state=0)
        svmcl.fit(training_samples, training_targets)
        svmcl_prediction = svmcl.predict(testing_samples)
        svmcl_accuracy = 100.0 * accuracy_score(testing_targets, svmcl_prediction)
        svmcl_precision = 100.0 * precision_score(testing_targets, svmcl_prediction)
        svmcl_recall = 100.0 * recall_score(testing_targets, svmcl_prediction)
        svmcl_f1_score = 100.0 * f1_score(testing_targets, svmcl_prediction)  # , average="macro")
        svmcl_confusion_matrix = confusion_matrix(testing_targets, svmcl_prediction)
        self.label_accuracy_text.set("{:.2f}".format(svmcl_accuracy) + "%")
        self.label_precision_text.set("{:.2f}".format(svmcl_precision) + "%")
        self.label_recall_text.set("{:.2f}".format(svmcl_recall) + "%")
        self.label_f1_text.set("{:.2f}".format(svmcl_f1_score) + "%")
        # self.label_confusion_text.set("\n\n" + str(svmcl_confusion_matrix))
        self.TP.set(svmcl_confusion_matrix[0][0])
        self.FP.set(svmcl_confusion_matrix[0][1])
        self.FN.set(svmcl_confusion_matrix[1][0])
        self.TN.set(svmcl_confusion_matrix[1][1])
        fpr, tpr, thresholds = roc_curve(testing_targets, svmcl_prediction, )
        roc_auc = auc(fpr, tpr)
        self.plot_curve_ROC(roc_curve, fpr, tpr, roc_auc)

    def run_logistic_regression(self, training_samples, testing_samples, training_targets, testing_targets):
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Training the dataset using Logistic Regression. Please wait...")
        self.update_idletasks()
        logr = LogisticRegression(solver='lbfgs', max_iter=2000)  # "Limited-memory Broyden–Fletcher–Goldfarb–Shanno Algorithm"
        logr.fit(training_samples, training_targets)
        logr_prediction = logr.predict(testing_samples)
        logr_accuracy = 100.0 * accuracy_score(testing_targets, logr_prediction)
        logr_precision = 100.0 * precision_score(testing_targets, logr_prediction)
        logr_recall = 100.0 * recall_score(testing_targets, logr_prediction)
        logr_f1_score = 100.0 * f1_score(testing_targets, logr_prediction)  # , average="macro")
        #print("Logistic Regression f1: {:.2f}%".format(logr_f1_score))
        logr_confusion_matrix = confusion_matrix(testing_targets, logr_prediction)
        self.label_accuracy_text.set("{:.2f}".format(logr_accuracy) + "%")
        self.label_precision_text.set("{:.2f}".format(logr_precision) + "%")
        self.label_recall_text.set("{:.2f}".format(logr_recall) + "%")
        self.label_f1_text.set("{:.2f}".format(logr_f1_score) + "%")
        # self.label_confusion_text.set("\nConfusion Matrix: \n\n" + str(logr_confusion_matrix))
        self.TP.set(logr_confusion_matrix[0][0])
        self.FP.set(logr_confusion_matrix[0][1])
        self.FN.set(logr_confusion_matrix[1][0])
        self.TN.set(logr_confusion_matrix[1][1])
        fpr, tpr, thresholds = roc_curve(testing_targets, logr_prediction, )
        roc_auc = auc(fpr, tpr)
        self.plot_curve_ROC(roc_curve, fpr, tpr, roc_auc)

    def run_random_forest(self, training_samples, testing_samples, training_targets, testing_targets):
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Training the dataset using Random Forest. Please wait...")
        self.update_idletasks()
        rndf = RandomForestClassifier(random_state=0)
        rndf.fit(training_samples, training_targets)
        rndf_prediction = rndf.predict(testing_samples)
        rndf_accuracy = 100.0 * accuracy_score(testing_targets, rndf_prediction)
        rndf_precision = 100.0 * precision_score(testing_targets, rndf_prediction)
        rndf_recall = 100.0 * recall_score(testing_targets, rndf_prediction)
        rndf_f1_score = 100.0 * f1_score(testing_targets, rndf_prediction)
        rndf_confusion_matrix = confusion_matrix(testing_targets, rndf_prediction)
        self.label_accuracy_text.set("{:.2f}".format(rndf_accuracy) + "%")
        self.label_precision_text.set("{:.2f}".format(rndf_precision) + "%")
        self.label_recall_text.set("{:.2f}".format(rndf_recall) + "%")
        self.label_f1_text.set("{:.2f}".format(rndf_f1_score) + "%")
        # self.label_confusion_text.set("\n\n" + str(rndf_confusion_matrix))
        self.TP.set(rndf_confusion_matrix[0][0])
        self.FP.set(rndf_confusion_matrix[0][1])
        self.FN.set(rndf_confusion_matrix[1][0])
        self.TN.set(rndf_confusion_matrix[1][1])
        fpr, tpr, thresholds = roc_curve(testing_targets, rndf_prediction, )
        roc_auc = auc(fpr, tpr)
        self.plot_curve_ROC(roc_curve, fpr, tpr, roc_auc)

    def run_knn(self, training_samples, testing_samples, training_targets, testing_targets):
        ##### ATENTION!!!  Takes 5 hours (4 Cores, 32Gb RAM) with full data set: 4 files loaded.  #####
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Training the dataset using KNN. Please wait...")
        self.update_idletasks()
        knc = KNeighborsClassifier(n_neighbors=2)
        knc.fit(training_samples, training_targets)
        knc_prediction = knc.predict(testing_samples)
        knc_accuracy = 100.0 * accuracy_score(testing_targets, knc_prediction)
        print("K-Nearest Neighbours accuracy: {:.4f}%".format(knc_accuracy))
        knc_precision = 100.0 * precision_score(testing_targets, knc_prediction)
        print("KNN precision: {:.2f}%".format(knc_precision))
        knc_recall = 100.0 * recall_score(testing_targets, knc_prediction)
        print("KNN recall: {:.2f}%".format(knc_recall))
        knc_f1_score = 100.0 * f1_score(testing_targets, knc_prediction)  # , average="macro")
        print("KNN f1: {:.2f}%".format(knc_f1_score))
        # K-Nearest Neighbours accuracy: 99.5840224055033
        knc_confusion_matrix = confusion_matrix(testing_targets, knc_prediction)
        self.label_accuracy_text.set("{:.2f}".format(knc_accuracy) + "%")
        self.label_precision_text.set("{:.2f}".format(knc_precision) + "%")
        self.label_recall_text.set("{:.2f}".format(knc_recall) + "%")
        self.label_f1_text.set("{:.2f}".format(knc_f1_score) + "%")
        # self.label_confusion_text.set("\n\n" + str(knc_confusion_matrix))
        self.TP.set(knc_confusion_matrix[0][0])
        self.FP.set(knc_confusion_matrix[0][1])
        self.FN.set(knc_confusion_matrix[1][0])
        self.TN.set(knc_confusion_matrix[1][1])
        fpr, tpr, thresholds = roc_curve(testing_targets, knc_prediction, )
        roc_auc = auc(fpr, tpr)
        self.plot_curve_ROC(roc_curve, fpr, tpr, roc_auc)

    def plot_curve(self, epochs, hist, list_of_metrics):
        """Plot a curve of one or more classification metrics vs. epoch."""
        self.plot1.cla()
        self.plot1.set_xlabel("Epoch")
        self.plot1.set_ylabel("Value")
        for m in list_of_metrics:
            x = hist[m]
            self.plot1.plot(epochs[1:], x[1:], label=m)
        self.plot1.legend()
        self.canvas.draw()


    def run_Neural_Network(self, training_samples, testing_samples, training_targets, testing_targets):
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Training the dataset using Neural Network. Please wait...")
        self.update_idletasks()
        number_of_labels = 1  # dimensionality of the output space.
        learning_rate = 0.001
        batch_size = 1000#1000
        n_epochs = 30
        METRICS = [
            tf.keras.metrics.BinaryAccuracy(name='accuracy'),
            tf.keras.metrics.Precision(name='precision'),
            tf.keras.metrics.Recall(name="recall"),
            tf.keras.metrics.TruePositives(name="TP"),
            tf.keras.metrics.FalsePositives(name="FP"),
            tf.keras.metrics.TrueNegatives(name="TN"),
            tf.keras.metrics.FalseNegatives(name="FN")
        ]
        model = tf.keras.models.Sequential()
        model.add(tf.keras.layers.Dense(units=number_of_labels,
                                        input_shape=(training_samples.shape[1],),
                                        activation=tf.sigmoid,
                                        name="Output_One_Layer_Model"))
        model.summary()
        model.compile(optimizer=tf.keras.optimizers.RMSprop(learning_rate=learning_rate),
                      loss=tf.keras.losses.BinaryCrossentropy(),
                      metrics=METRICS)
        history = model.fit(training_samples,
                            training_targets,
                            epochs=n_epochs,
                            batch_size=batch_size)
        loss_and_metrics = model.evaluate(training_samples, training_targets, batch_size=batch_size)
        print("The train accuracy is: " + str(loss_and_metrics[1]))
        self.label_accuracy_text.set("{:.2f}".format(loss_and_metrics[1]*100) + "%")
        loss_and_metrics = model.evaluate(testing_samples, testing_targets, batch_size=batch_size)
        print("The test accuracy is: " + str(loss_and_metrics[1]))
        # The list of epochs is stored separately from the rest of history.
        epochs = history.epoch
        # Isolate the classification metric for each epoch.
        hist = pd.DataFrame(history.history)
        # Plot a graph of the metric(s) vs. epochs.
        list_of_metrics_to_plot = ['accuracy', 'recall', 'precision']
        self.plot_curve(epochs, hist, list_of_metrics_to_plot)
        self.label_accuracy_text.set("{:.4f}".format(loss_and_metrics[1]) + "%")
        self.label_precision_text.set("{:.4f}".format(loss_and_metrics[2]) + "%")
        self.label_recall_text.set("{:.4f}".format(loss_and_metrics[3]) + "%")
        self.label_f1_text.set("{:.4f}".format(2*loss_and_metrics[4] / (2*loss_and_metrics[4]+loss_and_metrics[5]+loss_and_metrics[7]) ) + "%")
        self.TP.set(int(loss_and_metrics[4]))
        self.FP.set(int(loss_and_metrics[5]))
        self.TN.set(int(loss_and_metrics[6]))
        self.FN.set(int(loss_and_metrics[7]))


    def run_Deep_Learning(self, training_samples, testing_samples, training_targets, testing_targets):
        self.label_status_frame_text.set(self.label_status_frame_text.get() + "[+] Training the dataset using Deep Learning. Please wait...")
        self.update_idletasks()
        classes = 1
        input_size = training_samples.shape[1]
        hidden_neurons = 3
        batch_size = 1000
        n_epochs = 40
        learning_rate = 0.001
        METRICS = [
            tf.keras.metrics.BinaryAccuracy(name='accuracy'),
            tf.keras.metrics.Precision(name='precision'),
            tf.keras.metrics.Recall(name="recall"),
            tf.keras.metrics.TruePositives(name="TP"),
            tf.keras.metrics.FalsePositives(name="FP"),
            tf.keras.metrics.TrueNegatives(name="TN"),
            tf.keras.metrics.FalseNegatives(name="FN")
        ]
        model = tf.keras.models.Sequential()
        model.add(tf.keras.layers.Dense(hidden_neurons,
                                        input_dim=input_size,
                                        activation=tf.keras.activations.relu,
                                        # kernel_regularizer=tf.keras.regularizers.l2(0.04),
                                        name="HiddenLayer1"))
        model.add(tf.keras.layers.Dense(classes,
                                        input_dim=hidden_neurons,
                                        activation=tf.keras.activations.sigmoid,
                                        name="Output"))
        model.summary()
        model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=learning_rate),
                      loss=tf.keras.losses.BinaryCrossentropy(),
                      metrics=METRICS)
        history = model.fit(training_samples,
                            training_targets,
                            epochs=n_epochs,
                            batch_size=batch_size)
        # The list of epochs is stored separately from the rest of history.
        epochs = history.epoch
        loss_and_metrics = model.evaluate(training_samples, training_targets, batch_size=batch_size)
        # Isolate the classification metric for each epoch.
        hist = pd.DataFrame(history.history)
        # Plot a graph of the metric(s) vs. epochs.
        list_of_metrics_to_plot = ['accuracy', 'recall', 'precision']
        self.plot_curve(epochs, hist, list_of_metrics_to_plot)
        self.label_accuracy_text.set("{:.4f}".format(loss_and_metrics[1]) + "%")
        self.label_precision_text.set("{:.4f}".format(loss_and_metrics[2]) + "%")
        self.label_recall_text.set("{:.4f}".format(loss_and_metrics[3]) + "%")
        self.label_f1_text.set("{:.4f}".format(2*loss_and_metrics[4] / (2*loss_and_metrics[4]+loss_and_metrics[5]+loss_and_metrics[7]) ) + "%")
        self.TP.set(int(loss_and_metrics[4]))
        self.FP.set(int(loss_and_metrics[5]))
        self.TN.set(int(loss_and_metrics[6]))
        self.FN.set(int(loss_and_metrics[7]))


if __name__ == "__main__":
    ids = IDS()
    ids.iconbitmap("logojose1x1.ico")
    ids.geometry("1670x1050") #("widthxheight")
    #ids.resizable(0, 0)
    ids.mainloop()
