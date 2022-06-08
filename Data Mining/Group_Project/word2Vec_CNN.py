#dependencies
from string import punctuation
from os import listdir
from gensim.models import Word2Vec
from string import punctuation
from os import listdir
from collections import Counter
from nltk.corpus import stopwords
import pandas as pd
import numpy as np
from numpy import array
from numpy import asarray
from numpy import zeros
import keras
from keras.preprocessing.text import Tokenizer
from keras.preprocessing.sequence import pad_sequences
from keras.models import Sequential
from keras.layers import Dense, Dropout
from keras.layers import Flatten
from keras.layers import Embedding
from keras.layers.convolutional import Conv1D
from keras.utils import np_utils
from keras.layers.convolutional import MaxPooling1D

def read_data(filename,encoding):
    data = pd.read_csv(filename,encoding=encoding)
    return data

# get th test set and trian test
def split_train_test(data,split):
    # random seed 
    np.random.seed(0)
    mask = np.random.rand(len(data)) < split
    train_data = data[mask]
    test_data = data[~mask]
    return train_data,test_data

def get_token(i):
    singe_word = i.split()
    token_temp = str.maketrans('','',punctuation)
    singe_word = [w.translate(token_temp) for w in singe_word]
    singe_word = [word for word in singe_word if word.isalpha()]
    stop_words = set(stopwords.words('english'))
    singe_word = [w for w in singe_word if not w in stop_words]
    singe_word = [word for word in singe_word if len(word)>2]
    return singe_word


training = read_data('train.csv','latin1')#read training file
test = read_data('test.csv','latin1')#read test file
data = training.copy()
data = training.append(test, ignore_index=True)
data

words = set()
words = {}
train_data = training.copy()
test_data = test.copy()


token = data['abstract'][0].split()
token_temp = str.maketrans('','',punctuation)
singe_word = [w.translate(token_temp) for w in token] 
#print(singe_word)
singe_word = [word for word in singe_word if word.isalpha()]
stop_words = set(stopwords.words('english'))
singe_word = [w for w in singe_word if not w in stop_words]
singe_word = [word for word in singe_word if len(word)>2]
#print(singe_word)

abstract = data['abstract']
for i in abstract:
    singe_word = get_token(i)
    for token in singe_word:
        if token in words:
            words[token] += 1
        else:
            words[token] = 1

for word in words:
    if words[word] > 2:
        words.add(word)


train_abstract = []
for i in train_data['abstract']:
    singe_word = i.split()
    final_singe_word = []
    #final_string = ''
    for token in singe_word:
        if token in words:
            final_singe_word.append(token)
    #final_string = ' '.join(final_singe_word)
    train_abstract.append(final_singe_word)

test_abstract = []
for i in test_data['abstract']:
    singe_word = i.split()
    final_singe_word = []
    for token in singe_word:
        if token in words:
            final_singe_word.append(token)
    #final_string = ' '.join(final_singe_word)
    test_abstract.append(final_singe_word)
#     print(test_abstract)

model = Word2Vec(train_abstract, vector_size = 100, window = 5, min_count=1)
words = list(model.wv.key_to_index)
filename = "embedding_vectors.txt"
model.wv.save_word2vec_format(filename, binary=False)

# Here we use the trainned model by load_abstract
def load_embedding(filename):
    #load embedding into memory
    file = open(filename,'r')
    lines = file.readlines()[1:] #skip first line
    file.close()
    # create a map of words to vectors
    embedding = dict()
    for line in lines:
        parts = line.split()
        # key is string word, value is numpy array for vector
        embedding[parts[0]] = asarray(parts[1:], dtype='float32')
    # {word: [vector]}
    return embedding

def embedding_matrix(embedding, word_indices):
    # total wordsulary size plus 0 for unknown words
    words_size = len(word_indices)+1
    # define weight matrix dimensions with all 0
    embedding_matrice = zeros((words_size, 100))
    # step words, store vectors using the Tokenizer's integer mapping
    for word, i in word_indices.items():
        embedding_matrice[i] = embedding.get(word)
    return embedding_matrice


tokenizer = Tokenizer()
tokenizer.fit_on_texts(train_abstract)
# 对测试集进行同样的操作
sequence_dic = tokenizer.texts_to_sequences(train_abstract)

# For simplicity of implementation, Keras can only accept sequences of the same length, so you need to fill the sequence 
# so that all the text in the text set is the same length
max_length = max(([len(s) for s in train_abstract]))
train_labels = train_data['label']
Xtrain = pad_sequences(sequence_dic, maxlen=max_length, padding='post')
ytrain = np_utils.to_categorical(train_labels, num_classes=5)

sequence_dic = tokenizer.texts_to_sequences(test_abstract)
test_labels = test_data['label']
Xtest = pad_sequences(sequence_dic, maxlen=max_length, padding='post')
ytest = np_utils.to_categorical(test_labels, num_classes=4)

#print(max_length)

words_size = len(tokenizer.word_index)+1
embedding = load_embedding('embedding_vectors.txt')

# Tranform to matrix 
embedding_matrice = zeros((words_size, 100))
for word,i in tokenizer.word_index.items():
    if word in embedding:
        embedding_matrice[i] = embedding[word]
# print(embedding_matrice)
# The maximum length of each list
embedding_layer = Embedding(words_size, 100, weights=[embedding_matrice], input_length=max_length, trainable=True)

model = Sequential()
model.add(embedding_layer)
# The convolution layer retains the main features while reducing the parameters and computation to improve the model generalization ability
# Sigmoid and other functions are used to calculate the activation function (exponential operation), which involves a large amount of calculation, and the derivation involves division
# The amount of calculation is relatively large, while using Relu activation function saves a lot of calculation in the whole process.
model.add(Conv1D(filters=32, kernel_size=8, activation='relu'))
# # kernel size

# Maximum pooling layer: Improve fault tolerance of the model
# Further feature sampling, dimensionality reduction, reduce model size, improve calculation speed
# Reduce the over-fitting probability and improve the robustness of feature extraction
model.add(MaxPooling1D(pool_size=2))
model.add(Flatten())
model.add(Dropout(0.1))

# Full connection, 4 layer categories and the activation function is softmax
# The last layer of activation functions are classified by software
model.add(Dense(5, activation='softmax'))
print(model.summary())

model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
model.fit(Xtrain, ytrain, epochs=3, verbose=2, validation_data = (Xtest,ytest))


