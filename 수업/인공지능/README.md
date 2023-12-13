# Linear regression
지도학습(supervised learning)으로 정답을 학습하여 입력에 대한 예측을 보여주며 집값 예측, 키에 따른 몸무게 예측에 사용 가능하다.
## Cost function
예측값에 대한 오차를 Loss function으로 보여주며 값을 감소하는 방향으로 나아간다.
![Alt text](image-26.png)
![Alt text](image.png)
## Epoch, Iteration, SGD, Batch GD, Nimi-Batch-GD
![Alt text](image-32.png)
## Gradient descent 
![Alt text](image-27.png)
- 앞에서 구한 Cost function를 미분하여 기울기를 구하고 세타(learnable parameters)를 오차가 감소하는 방향으로 업데이트한다.
- ![Alt text](image-2.png)
- ![Alt text](image-4.png) 
- 깔끔한 글씨를 쓴 원본이 없어서 다른 자료에서 가져오다 보니 여기선 w(weight, varience)와 b(bias)를 사용한다. w = 세타1, b= 세타0 
## Learning rate
![Alt text](image-28.png)
learning rate가 너무 크면 발산하고, 너무 작으면 시간이 오래 걸린다. 그래서 적절한 크기를 골라서 잘 사용해야 하고, dynamic하게 초반엔 크게, 후반엔 작게 하는 방식도 있다.
#   Logistic regression
분류의 문제로, 지도학습이며, 스팸문자 고르기, 종양의 양성 혹은 음성 고르기 에서 사용된다.
## Sigmoid function
![Alt text](image-29.png)
![Alt text](image-31.png)

## Decision boundary
Logistic regression은 Decision boundary를 그리는 것으로 이해해도 된다. 이 boundary를 그리는 것은 Linear regression과 똑같다.
![Alt text](image-5.png)

## predict
![Alt text](image-6.png)

## Cost function
![Alt text](image-7.png)
![Alt text](image-30.png)
## Forward propagation
![Alt text](image-8.png)



# Neural network
![Alt text](image-9.png)
계산하는 방식은 Logistic regression과 비슷하다. 그러나 Cost function은 마지막에서 구한다는 것, Decision boundary가 비선형적이라는 차이 정도가 있다.

### Forward propagation
![Alt text](image-10.png)

### Backward propagation
![Alt text](image-12.png)
![Alt text](image-13.png)
![Alt text](image-14.png)
![Alt text](image-15.png)
![Alt text](image-16.png)
### over fitting
![Alt text](image-11.png)

### Zero initialization (theta= 0)
![Alt text](image-17.png)
![Alt text](image-18.png)

# Improve a learning algorithm
ex) data 더 모으기, features 줄이거나 늘리기, 차수의 변화, 정규화 시 람다의 증감
### Diagnostic
test set만 테스트 하기엔 우연의 일치를 확인할 수 없다. 즉 교차 검증(cross validation set)를 만든다.
### Cross validation
![Alt text](image-19.png)
![Alt text](image-20.png)
![Alt text](image-22.png)
![Alt text](image-23.png)
### Recap
![Alt text](image-24.png)

# Activation function and Hyperparameter

### Softmax
Softmax는 Multiclass classfication문제에서 사용한다.
![Alt text](image-25.png)
### Hyperparameters
num of(iteraters, layer, node, learning rate), type of (activation function, optimizer)
### Learnable parameters
theta

# CNN
![Alt text](image-33.png)
![Alt text](image-34.png)
![Alt text](image-35.png)
![Alt text](image-36.png)
![Alt text](image-37.png)
![Alt text](image-39.png)
![Alt text](image-38.png)
![Alt text](image-40.png)
![Alt text](image-41.png)
![Alt text](image-42.png)
![Alt text](image-43.png)
![Alt text](image-44.png)
![Alt text](image-45.png)
![Alt text](image-46.png)
![Alt text](image-47.png)
![Alt text](image-48.png)
![Alt text](image-49.png)
![Alt text](image-50.png)
![Alt text](image-51.png)



# CAM
판단내리는 데 중요한 곳을 강조 = 설명 가능한 DNN
![Alt text](image-52.png)
![Alt text](image-53.png)


# Autoencoder
![Alt text](image-54.png)
![Alt text](image-55.png)
![Alt text](image-56.png)
![Alt text](image-57.png)
![Alt text](image-58.png)
![Alt text](image-59.png)
![Alt text](image-60.png)
![Alt text](image-61.png)
![Alt text](image-62.png)
![Alt text](image-63.png)
![Alt text](image-64.png)
![Alt text](image-65.png)
![Alt text](image-66.png)
![Alt text](image-67.png)
![Alt text](image-68.png)

# segmentation, object detection

![Alt text](image-69.png)
![Alt text](image-70.png)
![Alt text](image-71.png)
![Alt text](image-72.png)
![Alt text](image-73.png)
![Alt text](image-74.png)
![Alt text](image-75.png)

