import numpy as np
import copy     
from sklearn.datasets import make_moons
import sklearn
import matplotlib.pyplot as plt

#1. Make a dataset of 400 points, of 2 classes
X, Y = make_moons(n_samples = 400, noise = 0.2)

#2. Pre-process the Data
X = X.T
Y = Y.reshape(1, -1)

#Visualize the Data
'''plt.scatter(X[0,:], X[1,:], c = Y, s = 40, cmap = plt.cm.Spectral)
plt.show()
#c = Y means the color is given to the points of X dataset based on their Y-label class'''
#X_shape = (2, 400), Y_shape = (1, 400), training_examples = m = 400

'''clf = sklearn.linear_model.LogisticRegressionCV()
clf.fit(X.T, Y.T)
LR_predictions = clf.predict(X.T)
print ('Accuracy of logistic regression: %d ' % float((np.dot(Y,LR_predictions) + np.dot(1-Y,1-LR_predictions))/float(Y.size)*100) +
       '% ' + "(percentage of correctly labelled datapoints)")
#Accuracy = 87%'''

#3. Defining the Helper Functions and Neural Network Structure

#a. layer_sizes
def layer_sizes(X, Y):
    n_x = X.shape[0]
    n_h = 4
    n_y = Y.shape[0]
    return (n_x, n_h, n_y)

#b. Initialize Parameters
def initialize_parameters(n_x, n_h, n_y):
    W1 = np.random.randn(n_h, n_x) * 0.01
    b1 = np.zeros((n_h, 1))
    W2 = np.random.randn(n_y, n_h) * 0.01
    b2 = np.zeros((n_y, 1))
    parameters = {"W1": W1, "b1": b1, "W2": W2, "b2": b2}
    return parameters

#The Neural Network Loop Starts Here

#c. Forward Propagation
def forward_propagation(X, parameters):
    W1 = parameters["W1"]
    b1 = parameters["b1"]
    W2 = parameters["W2"]
    b2 = parameters["b2"]

    Z1 = np.dot(W1, X) + b1
    A1 = np.tanh(Z1)
    Z2 = np.dot(W2, A1) + b2
    A2 = 1 / (1 + np.exp(-Z2)) # sigmoid

    cache = {"Z1":Z1, "A1":A1, "Z2":Z2, "A2":A2}
    return A2, cache

#d. compute the cost
def compute_cost(A2, Y):
    m = Y.shape[1]
    logprobs = np.multiply(np.log(A2), Y) + np.multiply(np.log(1-A2), 1-Y)
    cost = - np.sum(logprobs) / m
    return cost

#e. backward propagation
def backward_propagation(parameters, cache, X, Y):
    m = Y.shape[1]
    W1 = parameters["W1"]
    b1 = parameters["b1"]#not needed
    W2 = parameters["W2"]
    b2 = parameters["b2"]#not needed
    A1 = cache["A1"]
    A2 = cache["A2"]

    #compute gradients
    dZ2 = A2 - Y
    dW2 = np.dot(dZ2, A1.T) / m
    db2 = np.sum(dZ2, axis = 1, keepdims = True) / m
    dZ1 = np.dot(W2.T, dZ2)*(1-np.power(A1, 2))
    dW1 = np.dot(dZ1, X.T) / m
    db1 = np.sum(dZ1, axis = 1, keepdims = True) / m

    grads = {"dW2":dW2, "db2":db2, "dW1":dW1, "db1":db1}
    return grads

#f. update parameters
def update_parameters(parameters, grads, learning_rate = 1.2):
    W2 = copy.deepcopy(parameters["W2"])
    b2 = parameters["b2"]
    W1 = copy.deepcopy(parameters["W1"])
    b1 = parameters["b1"]
    dW2 = grads["dW2"]
    db2 = grads["db2"]
    dW1 = grads["dW1"]
    db1 = grads["db1"]

    #implement gradient descent
    W2 = W2 - learning_rate*dW2
    W1 = W1 - learning_rate*dW1
    b2 = b2 - learning_rate*db2
    b1 = b1 - learning_rate*db1

    parameters = {"W1":W1, "W2":W2, "b2":b2, "b1":b1}
    return parameters

#g. Predict
def predict(parameters, X):
    A2, cache = forward_propagation(X, parameters)
    predictions = (A2 > 0.5).astype(int)
    return predictions

#4. Build the Neural Network Model
def neural_network_model(X, Y, n_h, num_iterations=10000, learning_rate = 1.2, print_cost = False):
    #set the random seed
    np.random.seed(3)
    n_x = layer_sizes(X, Y)[0]
    n_y = layer_sizes(X, Y)[2]

    parameters = initialize_parameters(n_x, n_h, n_y)

    for i in range(num_iterations):
        A2, cache = forward_propagation(X, parameters)
        cost = compute_cost(A2, Y)
        grads = backward_propagation(parameters, cache, X, Y)
        parameters = update_parameters(parameters, grads, learning_rate)

        if(print_cost and i % 1000 == 0):
            print("Cost after iteration %i: %f" %(i, cost))
    
    return parameters

#5. Call the Model Function Using Our Dataset
parameters = neural_network_model(X, Y, n_h = 4, num_iterations=10000, learning_rate=1.2, print_cost=True)
predictions = predict(parameters, X)

#Finally, output the accuracy
print("Accuracy: %d" %float((np.dot(Y, predictions.T) + np.dot(1-Y, 1 - predictions.T)) / float(Y.size)*100)+"%")
    