function [critic,actor] = createNetworks(obsInfo,actInfo)
rng(0);

% Number of neurons in hidden layers
hiddenLayerSize = 64;

% Extract dimensions of observation and action spaces.
numObs = prod(obsInfo.Dimension);
numAct = prod(actInfo.Dimension);

obsInput = featureInputLayer(numObs,Name=obsInfo.Name);
actInput = featureInputLayer(numAct,Name=actInfo.Name);
catPath = [
    concatenationLayer(1,2,Name="concat")
    fullyConnectedLayer(hiddenLayerSize)
    reluLayer
    fullyConnectedLayer(hiddenLayerSize)
    reluLayer
    fullyConnectedLayer(1,Name="Q-Value")
    ];

% Create dlnetwork object and add layers.
net = dlnetwork();
net = addLayers(net,obsInput);
net = addLayers(net,actInput);
net = addLayers(net,catPath);

% Connect layers.
net = connectLayers(net,obsInfo.Name,"concat/in1");
net = connectLayers(net,actInfo.Name,"concat/in2");

% Initialize network.
net = initialize(net);

% Create the critic object.
critic = rlQValueFunction(net,obsInfo,actInfo);


% Define scale and bias for the output layer
scale = (actInfo.UpperLimit - actInfo.LowerLimit)/2;
bias  = actInfo.LowerLimit + scale;


obsPath = [
    featureInputLayer(numObs,Name=obsInfo.Name)
    fullyConnectedLayer(hiddenLayerSize)
    reluLayer
    fullyConnectedLayer(hiddenLayerSize)
    reluLayer
    fullyConnectedLayer(numAct,WeightsInitializer=@(sz) 1e-4.*(rand(sz)-0.5))
    tanhLayer
    scalingLayer(Scale=scale,...
        Bias=bias,...
        Name=actInfo.Name)
    ];

% Create dlnetwork object and add layers.
net = dlnetwork();
net = addLayers(net,obsPath);

% Initialize network.
net = initialize(net);

% Create the actor object.
actor = rlContinuousDeterministicActor(net,obsInfo,actInfo);

end