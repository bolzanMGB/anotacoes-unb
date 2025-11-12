# Rede Neural de Classificação de Dígitos (MNIST)

Objetivo: criar uma rede neural capaz de classificar imagems de dígitos (0-9) com base em pixels de imagens 28x28;

---

## 1. Estrutura dos dados
- Cada imagem tem dimensão de 28x28 (784 pixels);
- Cada pixel é um número entre 0 (preto) e 255 (branco);
- Como entrada da rede, cada imagem é formatada em um vetor de 784 valores (28x28)

## 2. Estrutura da rede neural
- Entrada: 784 nerurônios (um por pixel);
- Camada oculta: 10 neurônios com função de ativação ReLu;
- Camada de saída: 10 neurônios com função de ativação Softmax, que dá uma probabilidade para cada classe (0-9);


## Implementação

``` python title="Rede Neural MNIST:"

# bibliotecas básicas
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

# acessa o google drive
from google.colab import drive
drive.mount('/content/drive')

# le o arquivo das imagens
data = pd.read_csv('/content/drive/MyDrive/TEMA - 2.25/códigos/2.aula_03_(09_09_25)_data_tema_2_25.csv')

data = np.array(data)
m, n = data.shape
print(data.shape)

np.random.shuffle(data)

# teste
data_dev = data[0:4200].T
Y_dev = data_dev[0]
X_dev = data_dev[1:n]

# treino
data_train = data[4200:m].T
Y_train = data_train[0]
X_train = data_train[1:n]
_, m_train = X_train.shape

Z = X_train.reshape((28,28,m_train))
print(Z[:,:,0])  # mostra matriz da primeira imagem

fig, ax = plt.subplots(1, 1, figsize=(4,4))
ax.imshow(Z[:,:,0], cmap='gray')
ax.set_title(f"Rótulo: {Y_train[0]}")
ax.get_xaxis().set_visible(False)
ax.get_yaxis().set_visible(False)

X_dev = X_dev / 255.
X_train = X_train / 255.

def ReLU(Z):
    return np.maximum(Z, 0)

def ReLU_deriv(Z):
    return Z > 0  # retorna 1 se Z>0 e 0 se Z<0

def softmax(Z):
    A = np.exp(Z) / np.sum(np.exp(Z), axis=0)
    return A

def forward_prop(W1, b1, W2, b2, X):
    Z1 = W1.dot(X) + b1
    A1 = ReLU(Z1)
    Z2 = W2.dot(A1) + b2
    A2 = softmax(Z2)
    return Z1, A1, Z2, A2

# definição dos parâmetros iniciais
def init_params():
    W1 = np.random.rand(10, 784) - 0.5
    b1 = np.random.rand(10, 1) - 0.5
    W2 = np.random.rand(10, 10) - 0.5
    b2 = np.random.rand(10, 1) - 0.5
    return W1, b1, W2, b2

# faz o one-hot encoding do vetor de rótulos
def one_hot(Y): # one-hot encoding
    Y = Y.astype(int)
    one_hot_Y = np.zeros((Y.size, Y.max() + 1))
    one_hot_Y[np.arange(Y.size), Y] = 1
    one_hot_Y = one_hot_Y.T
    return one_hot_Y


# cálculo das derivadas

def backward_prop(Z1, A1, Z2, A2, W1, W2, X, Y):
    one_hot_Y = one_hot(Y)
    # aqui dividimos pelo número de imagens m, pois a loss calculada é a média das amostras
    dZ2 = (1 / m) * (A2 - one_hot_Y)

    dW2 = dZ2.dot(A1.T)
    db2 = np.sum(dZ2, axis=1).reshape(-1, 1)
    dZ1 = W2.T.dot(dZ2) * ReLU_deriv(Z1)
    dW1 = dZ1.dot(X.T)
    db1 = np.sum(dZ1, axis=1).reshape(-1, 1)
    return dW1, db1, dW2, db2


# atualização dos parâmetros
def update_params(W1, b1, W2, b2, dW1, db1, dW2, db2, alpha):
    W1 -= alpha * dW1
    b1 -= alpha * db1
    W2 -= alpha * dW2
    b2 -= alpha * db2
    return W1, b1, W2, b2


# vamos fazer a mágica acontecer!

def get_predictions(A2):
    return np.argmax(A2, 0)

def get_accuracy(predictions, Y):
    print(predictions, Y)
    return np.sum(predictions == Y) / Y.size

def gradient_descent(X, Y, alpha, iterations):
    W1, b1, W2, b2 = init_params()
    for i in range(iterations):
        Z1, A1, Z2, A2 = forward_prop(W1, b1, W2, b2, X)
        dW1, db1, dW2, db2 = backward_prop(Z1, A1, Z2, A2, W1, W2, X, Y)
        W1, b1, W2, b2 = update_params(W1, b1, W2, b2, dW1, db1, dW2, db2, alpha)
        if i % 50 == 0:
            print("Iteração: ", i)
            predictions = get_predictions(A2)
            print(get_accuracy(predictions, Y))
    return W1, b1, W2, b2


# vamos treinar
W1, b1, W2, b2 = gradient_descent(X_train, Y_train, 0.10, 750)

# vamos testar se o trem ficou bom!
def make_predictions(X, W1, b1, W2, b2):
    _, _, _, A2 = forward_prop(W1, b1, W2, b2, X)
    predictions = get_predictions(A2)
    return predictions

def test_prediction(index, W1, b1, W2, b2):
    current_image = X_dev[:, index, None]
    prediction = make_predictions(X_dev[:, index, None], W1, b1, W2, b2)
    label = Y_dev[index]
    print("Previsão: ", prediction)
    print("Rótulo: ", label)

    current_image = current_image.reshape((28, 28))
    plt.imshow(current_image,cmap="gray")
    plt.axis('off')
    plt.show()


a, b = X_dev.shape

test_prediction(np.random.randint(1, b), W1, b1, W2, b2)
```