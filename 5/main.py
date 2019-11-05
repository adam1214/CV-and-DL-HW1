from mlxtend.data import loadlocal_mnist
from mnist import MNIST
import matplotlib.pyplot as plt
import numpy as np
import cv2
import sys
import random
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import QtGui
from PyQt5 import QtWidgets
import tensorflow as tf
import pylab
import chainer
from chainer import backend
from chainer import backends
from chainer.backends import cuda
from chainer import Function, FunctionNode, gradient_check, report, training, utils, Variable
from chainer import datasets, initializers, iterators, optimizers, serializers
from chainer import Link, Chain, ChainList
import chainer.functions as F
import chainer.links as L
from chainer.training import extensions
from chainer.datasets import mnist
from chainer import optimizers
from chainer.dataset import concat_examples
from chainer.backends.cuda import to_cpu
import math
textboxValue = -1
X, y = loadlocal_mnist(
        images_path='samples/train-images-idx3-ubyte', 
        labels_path='samples/train-labels-idx1-ubyte')
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()

def button_1_clicked(self):
    print("button_1_clicked")
    mndata = MNIST('samples')
    
    for i in range(10):
        images, labels = mndata.load_training()
        index = random.randrange(0, len(images))  # choose an index ;-)
        #print(mndata.display(images[index]))
        #print('Label: %s' %labels[index])
        plt.figure()
        plt.title(y_train[index])
        print(y_train[index])
        plt.imshow(x_train[index], cmap='Greys')
    plt.show()

def button_2_clicked():
    print("button_2_clicked")
    print('hyperparameters:')
    print('batch size: 32')
    print('learning rate: 0.001')
    print('optimizer: SGD')

class MyNetwork(Chain):

    def __init__(self, n_mid_units=100, n_out=10):
        super(MyNetwork, self).__init__()
        with self.init_scope():
            self.l1 = L.Linear(None, n_mid_units)
            self.l2 = L.Linear(n_mid_units, n_mid_units)
            self.l3 = L.Linear(n_mid_units, n_out)

    def forward(self, x):
        h = F.relu(self.l1(x))
        h = F.relu(self.l2(h))
        return self.l3(h)

def button_3_clicked():
    print("button_3_clicked")

    train, test = mnist.get_mnist(withlabel=True, ndim=1)
    print('Download finished!')
    batchsize = 32
    train_iter = iterators.SerialIterator(train, batchsize)
    test_iter = iterators.SerialIterator(test, batchsize, repeat=False, shuffle=False)
    
    model = MyNetwork()
    gpu_id = 0  # Set to -1 if you use CPU
    if gpu_id >= 0:
        model.to_gpu(gpu_id)
    
    # Choose an optimizer algorithm
    optimizer = optimizers.MomentumSGD(lr=0.001, momentum=0.9)

    # Give the optimizer a reference to the model so that it can locate the model's parameters.
    optimizer.setup(model)

    # ---------- 600 iterations of the training loop ----------
    num = 0
    losses = []
    while num < 600:
        train_batch = train_iter.next()
        image_train, target_train = concat_examples(train_batch, gpu_id)

        # Calculate the prediction of the network
        prediction_train = model(image_train)

        # Calculate the loss with softmax_cross_entropy
        loss = F.softmax_cross_entropy(prediction_train, target_train)

        # Calculate the gradients in the network
        model.cleargrads()
        loss.backward()

        # Update all the trainable parameters
        optimizer.update()
        # --------------------- until here ---------------------

        # Check the validation accuracy of prediction after every epoch
        #if train_iter.is_new_epoch:  # If this iteration is the final iteration of the current epoch

        # Display the training loss
        print('epoch:{:02d} train_loss:{:.04f} '.format(train_iter.epoch, float(to_cpu(loss.array))))
        losses.append(float(to_cpu(loss.array)))
        num = num + 1
    r = range(600)
    r = list(r)
    plt.plot(r, losses)
    plt.xlabel('Iteration')
    plt.ylabel('loss')
    plt.show()

def button_4_clicked():
    print("button_4_clicked")

    train, test = mnist.get_mnist(withlabel=True, ndim=1)
    print('Download finished!')
    batchsize = 32
    train_iter = iterators.SerialIterator(train, batchsize)
    test_iter = iterators.SerialIterator(test, batchsize, repeat=False, shuffle=False)
    
    model = MyNetwork()
    gpu_id = 0  # Set to -1 if you use CPU
    if gpu_id >= 0:
        model.to_gpu(gpu_id)
    
    # Choose an optimizer algorithm
    optimizer = optimizers.MomentumSGD(lr=0.001, momentum=0.9)

    # Give the optimizer a reference to the model so that it can locate the model's parameters.
    optimizer.setup(model)

    max_epoch = 50
    cnt = 0
    epoch_record = 0
    Train_Acc = []
    Test_Acc = []
    Train_Loss = []
    while train_iter.epoch < max_epoch:

        train_accuracies = []
        while cnt < 600:
            # ---------- 600 iterations of the training loop ----------
            train_batch = train_iter.next()
            image_train, target_train = concat_examples(train_batch, gpu_id)

            # Calculate the prediction of the network
            prediction_train = model(image_train)

            # Calculate the loss with softmax_cross_entropy
            loss = F.softmax_cross_entropy(prediction_train, target_train)

            # Calculate the gradients in the network
            model.cleargrads()
            loss.backward()

            # Calculate the accuracy
            accuracy = F.accuracy(prediction_train, target_train)
            accuracy.to_cpu()
            train_accuracies.append(accuracy.array)

            cnt=cnt+1
            # Update all the trainable parameters
            optimizer.update()
        cnt = 0
        # --------------------- until here ---------------------

        # Check the validation accuracy of prediction after every epoch
        if train_iter.epoch != epoch_record:  # If this iteration is the final iteration of the current epoch
            epoch_record = train_iter.epoch
            # Display the training loss
            print('epoch:{:02d} train_loss:{:.04f} train_accuracy:{:.04f}'.format(train_iter.epoch, float(to_cpu(loss.array)), np.mean(train_accuracies)), end=' ')
            Train_Loss.append(float(to_cpu(loss.array)))
            Train_Acc.append(100*np.mean(train_accuracies))

            test_losses = []
            test_accuracies = []
            for test_batch in test_iter:
                image_test, target_test = concat_examples(test_batch, gpu_id)

                # Forward the test data
                prediction_test = model(image_test)

                # Calculate the loss
                loss_test = F.softmax_cross_entropy(prediction_test, target_test)
                test_losses.append(to_cpu(loss_test.array))

                # Calculate the accuracy
                accuracy = F.accuracy(prediction_test, target_test)
                accuracy.to_cpu()
                test_accuracies.append(accuracy.array)

            test_iter.reset()

            print('test_loss:{:.04f} test_accuracy:{:.04f}'.format(np.mean(test_losses), np.mean(test_accuracies)))
            Test_Acc.append(100*np.mean(test_accuracies))

    r = range(50)
    r = list(r)
    plt.subplot(211)
    plt.plot(r, Train_Acc, label = "Training", color = "blue")
    plt.plot(r, Test_Acc, label = "Testing", color = "red")
    plt.xlabel('epoch')
    plt.ylabel('%')
    plt.title('Accuracy')
    plt.legend () 

    plt.subplot(212)
    plt.plot(r, Train_Loss)
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.title('Training Loss')

    plt.show()

    serializers.save_npz('my_mnist.model', model)
def softmax(x):
    #Compute the softmax of vector x
    exp_x = np.exp(x)
    softmax_x = exp_x / np.sum(exp_x)
    return softmax_x 
class Frame(QWidget):
    def __init__(self):
        super(Frame, self).__init__()

        self.button_1 = QPushButton("5.1 Show Train Images")
        self.button_1.setMaximumWidth(200)
        self.button_2 = QPushButton("5.2 Show Hyperparameters")
        self.button_2.setMaximumWidth(200)
        self.button_3 = QPushButton("5.3 Train 1 Epoch")
        self.button_3.setMaximumWidth(200)
        self.button_4 = QPushButton("5.4 Show Training Result")
        self.button_4.setMaximumWidth(200)
        self.button_5 = QPushButton("5.5 Inference")
        self.button_5.setMaximumWidth(200)
        self.text = QTextEdit(self)
        self.text.setMaximumWidth(200)
        self.text.setMaximumHeight(35)

        self.init_ui()

    def init_ui(self):
        layout = QVBoxLayout()
        layout.addWidget(self.button_1)
        layout.addWidget(self.button_2)
        layout.addWidget(self.button_3)
        layout.addWidget(self.button_4)
        layout.addWidget(self.text)
        layout.addWidget(self.button_5)

        self.button_1.clicked.connect(button_1_clicked)
        self.button_2.clicked.connect(button_2_clicked)
        self.button_3.clicked.connect(button_3_clicked)
        self.button_4.clicked.connect(button_4_clicked)
        self.button_5.clicked.connect(self.button_5_clicked)

        self.setLayout(layout)
        self.setWindowTitle('5')
        self.setGeometry(50, 50, 600, 400)

        self.show()

    def button_5_clicked(self):
        print("button_5_clicked")
        textboxValue = int(self.text.toPlainText())
        self.text.clear()

        # Create an instance of the network you trained
        model = MyNetwork()

        # Load the saved parameters into the instance
        serializers.load_npz('my_mnist.model', model)

        train, test = mnist.get_mnist(withlabel=True, ndim=1)
        print('TextboxValue: %d' % textboxValue)
        x, t = test[textboxValue]
        #plt.figure()
        #plt.imshow(x.reshape(28, 28), cmap='gray')
        
        print('label:', t)

        # Change the shape of the minibatch.
        # In this example, the size of minibatch is 1.
        # Inference using any mini-batch size can be performed.
        print(x.shape, end=' -> ')
        x = x[None, ...]
        print(x.shape)
        # Forward calculation of the model by sending X
        y = model(x)

        # The result is given as Variable, then we can take a look at the contents by the attribute, .array.
        y = y.array
        print(y)
        # Look up the most probable digit number using argmax
        pred_label = y.argmax(axis=1)
        print('predicted label:', pred_label[0])
        softmax_arr = softmax(y)
        X_bar = [0,1,2,3,4,5,6,7,8,9]
        Y_bar = [0,0,0,0,0,0,0,0,0,0]
        i=0
        while i < 10:
            Y_bar[i] = softmax_arr[0][i]
            i = i + 1
        plt.bar(X_bar, Y_bar)
        plt.xlim((0, 9))
        plt.show()

def main():

    #print('Dimensions: %s x %s' % (X.shape[0], X.shape[1]))
    #print('\n1st row', X[0])
    print('Digits:  0 1 2 3 4 5 6 7 8 9')
    print('labels: %s' % np.unique(y))
    print('Class distribution: %s' % np.bincount(y))
    app = QApplication(sys.argv)
    frame = Frame()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()