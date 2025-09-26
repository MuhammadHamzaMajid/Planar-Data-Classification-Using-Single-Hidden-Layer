#importing libraries
import numpy as np
import copy
import matplotlib.pyplot as plt
import h5py
import scipy
from scipy import ndimage

#Problem Statement
#A training set of m_train_images
#A test set of m_test_images
#Each image is of shape(num_px, num_px, 3) where 3 is for the 3 channels (RGB)
#We have to build a simple image classification model
#That can simply classify unknown pictures as cat(1) or non-cat(0)


#1. Loading the DataSet
train_set_x_orig = h5py.File('E:\\Deep Learning Specialization\\Logistic Regression from Scratch\\train_catvsnoncat.h5', 'r')['train_set_x'][:]
train_set_y = h5py.File('E:\\Deep Learning Specialization\\Logistic Regression from Scratch\\train_catvsnoncat.h5', 'r')['train_set_y'][:]
test_set_x_orig = h5py.File('E:\\Deep Learning Specialization\\Logistic Regression from Scratch\\test_catvsnoncat.h5', 'r')['test_set_x'][:]
test_set_y = h5py.File('E:\\Deep Learning Specialization\\Logistic Regression from Scratch\\test_catvsnoncat.h5', 'r')['test_set_y'][:]
classes = h5py.File('E:\\Deep Learning Specialization\\Logistic Regression from Scratch\\train_catvsnoncat.h5', 'r')['list_classes'][:]

#Example of a picture
'''index = 25
plt.imshow(train_set_x_orig[index])     
print("y = " + str(train_set_y[index]) + ", it's a '" + classes[np.squeeze(train_set_y[index])].decode("utf-8") +  "' picture.")
plt.show()'''

#train_set_x_orig structure is (m_train, num_px, num_px, 3)

#finding values for m_train, m_test, num_px
m_train = train_set_x_orig.shape[0]
m_test = test_set_x_orig.shape[0]
num_px = train_set_x_orig.shape[1]
'''print ("Number of training examples: " + str(m_train))
print ("Number of testing examples: " + str(m_test))
print ("Height/Width of each image: " + str(num_px))
print ("Each image is of size: (" + str(num_px) + ", " + str(num_px) + ", 3)")'''

#2. Pre-processing the Data
#General Steps:
#a. Figure out the dimensions and shapes of the data
#b. Reshape the datasets such that each example is now a vector of size (num_px * num_px * 3, num_examples)
#c. Standardize the data(/255.)

#Reshape the images to 1-D arrays
train_set_x_flatten = train_set_x_orig.reshape(m_train,-1).T
test_set_x_flatten = test_set_x_orig.reshape(m_test, -1).T
#Note: Here, we use the Transpose function to get the images in the shape (num_px * num_px * 3, m)
#instead of (-1, m_train) because each column is a flattened version of the same image and we want to preserve this structure
#Also, -1 is used to automatically calculate the size of this dimension based on the other given dimension

#Standardize the Dataset
train_set_x = train_set_x_flatten / 255.
test_set_x = test_set_x_flatten / 255.
#Note: We divide by 255 to convert the value of each pixel from the range 0-255 to the range 0-1

#3. Building the Neural Network
#General Steps:
#a. Initialize the parameters of the model
#b. Learn the parameters for the model by minimizing the cost
#c. Use the learned parameters to make predictions
#d. Analyze the results and conclude

#Helper Functions

#a. sigmoid
def sigmoid(z):
    s = 1 / (1 + np.exp(-z))
    return s

#b. initialize_with_zeros
def initialize_with_zeros(dim):
    w = np.zeros((dim,1))
    b = 0
    return w, b 

#c. propagate
def propagate(w, b, X, Y):
    m = X.shape[1] #number of examples
    #Forward Propagation
    Z = np.dot(w.T, X) + b
    A = sigmoid(Z) #activation
    cost = (-1 / m) * (np.dot(Y, np.log(A).T) + np.dot((1-Y), np.log(1-A).T))

    #Backward Propagation
    dz = A - Y
    dw = np.dot(X, dz.T) / m
    db = np.sum(dz) / m
    #Note: dw is of shape (num_px * num_px * 3, 1) and db is a scalar

    cost = np.squeeze(np.array(cost)) #to make sure cost is a scalar
    grads = {"dw": dw,
             "db": db}
    return grads, cost
     
#d. optimize(update w, b using gradient descent)
def optimize(w, b, X, Y, num_iterations = 100, learning_rate = 0.009, print_cost = False):
    w = copy.deepcopy(w)
    b = copy.deepcopy(b)
    #deep-copy ensures the new object is created independently
    costs = []
    for i in range(num_iterations):
        grads, cost = propagate(w, b, X, Y)
        #retrieve gradients
        dw = grads["dw"]
        db = grads["db"]
        #apply gradient descent
        w = w - learning_rate*dw
        b = b - learning_rate*db

        #record the costs
        if i % 100 == 0:
            costs.append(cost)
            # Print the cost every 100 training iterations
            if print_cost:
                print ("\nCost after iteration %i: %f\n" %(i, cost))
        params = {"w":w, "b":b}
        grads = {"dw":dw, "db":db}

    return params, grads, costs

#e. predict
def predict(w, b, X):
    m = X.shape[1]
    Y_prediction = np.zeros((1, m))
    w = w.reshape(X.shape[0], 1) #not necessary

    #apply a final sigmoid function on updated weights
    A = sigmoid(np.dot(w.T, X) + b)
    
    #now, find the predictions for each image
    for i in range(A.shape[1]):
        if A[0, i] > 0.5:
            Y_prediction[0, i] = 1
        else:
            Y_prediction[0, i] = 0
    return Y_prediction

#4. Final Step: Merge all Functions to a Logistic Regression Model
def model(X_train, Y_train, X_test, Y_test, num_iterations = 2000, learning_rate = 0.005, print_cost = False):
    w, b = initialize_with_zeros(X_train.shape[0])
    params, grads, costs = optimize(w, b, X_train, Y_train, num_iterations, learning_rate, print_cost)
    w = params["w"]
    b = params["b"]
    Y_prediction_test = predict(w, b, X_test)
    Y_prediction_train = predict(w, b, X_train)

    if print_cost:
        print("Train Accuracy {}%".format(100 - np.mean(np.abs(Y_prediction_train - Y_train))*100))
        print("Test Accuracy: {}%".format(100-np.mean(np.abs(Y_prediction_test - Y_test))*100))

    d = {"costs": costs,
         "Y_prediction_test": Y_prediction_test,
         "Y_prediction_train": Y_prediction_train,
         "w":w, "b":b, 
         "learning rate": learning_rate,
         "num_iterations": num_iterations}
    return d

#now, test the model
logistic_regression_model = model(train_set_x, train_set_y, test_set_x, test_set_y, 
                                  num_iterations=2000, learning_rate = 0.005, print_cost = True)
