function BusActorsActors = getBusActorsActors(BusActorsActors)

    BusActorsActors.Description = '';
    BusActorsActors.DataScope = 'Auto';
    BusActorsActors.HeaderFile = '';
    BusActorsActors.Alignment = -1;
    saveVarsTmp{1} = Simulink.BusElement;
    saveVarsTmp{1}.Name = 'ActorID';
    saveVarsTmp{1}.Complexity = 'real';
    saveVarsTmp{1}.Dimensions = [1 1];
    saveVarsTmp{1}.DataType = 'double';
    saveVarsTmp{1}.Min = [];
    saveVarsTmp{1}.Max = [];
    saveVarsTmp{1}.DimensionsMode = 'Fixed';
    saveVarsTmp{1}.SamplingMode = 'Sample based';
    saveVarsTmp{1}.DocUnits = '';
    saveVarsTmp{1}.Description = '';
    saveVarsTmp{1}(2, 1) = Simulink.BusElement;
    saveVarsTmp{1}(2, 1).Name = 'Position';
    saveVarsTmp{1}(2, 1).Complexity = 'real';
    saveVarsTmp{1}(2, 1).Dimensions = [1 3];
    saveVarsTmp{1}(2, 1).DataType = 'double';
    saveVarsTmp{1}(2, 1).Min = [];
    saveVarsTmp{1}(2, 1).Max = [];
    saveVarsTmp{1}(2, 1).DimensionsMode = 'Fixed';
    saveVarsTmp{1}(2, 1).SamplingMode = 'Sample based';
    saveVarsTmp{1}(2, 1).DocUnits = '';
    saveVarsTmp{1}(2, 1).Description = '';
    saveVarsTmp{1}(3, 1) = Simulink.BusElement;
    saveVarsTmp{1}(3, 1).Name = 'Velocity';
    saveVarsTmp{1}(3, 1).Complexity = 'real';
    saveVarsTmp{1}(3, 1).Dimensions = [1 3];
    saveVarsTmp{1}(3, 1).DataType = 'double';
    saveVarsTmp{1}(3, 1).Min = [];
    saveVarsTmp{1}(3, 1).Max = [];
    saveVarsTmp{1}(3, 1).DimensionsMode = 'Fixed';
    saveVarsTmp{1}(3, 1).SamplingMode = 'Sample based';
    saveVarsTmp{1}(3, 1).DocUnits = '';
    saveVarsTmp{1}(3, 1).Description = '';
    saveVarsTmp{1}(4, 1) = Simulink.BusElement;
    saveVarsTmp{1}(4, 1).Name = 'Roll';
    saveVarsTmp{1}(4, 1).Complexity = 'real';
    saveVarsTmp{1}(4, 1).Dimensions = [1 1];
    saveVarsTmp{1}(4, 1).DataType = 'double';
    saveVarsTmp{1}(4, 1).Min = [];
    saveVarsTmp{1}(4, 1).Max = [];
    saveVarsTmp{1}(4, 1).DimensionsMode = 'Fixed';
    saveVarsTmp{1}(4, 1).SamplingMode = 'Sample based';
    saveVarsTmp{1}(4, 1).DocUnits = '';
    saveVarsTmp{1}(4, 1).Description = '';
    saveVarsTmp{1}(5, 1) = Simulink.BusElement;
    saveVarsTmp{1}(5, 1).Name = 'Pitch';
    saveVarsTmp{1}(5, 1).Complexity = 'real';
    saveVarsTmp{1}(5, 1).Dimensions = [1 1];
    saveVarsTmp{1}(5, 1).DataType = 'double';
    saveVarsTmp{1}(5, 1).Min = [];
    saveVarsTmp{1}(5, 1).Max = [];
    saveVarsTmp{1}(5, 1).DimensionsMode = 'Fixed';
    saveVarsTmp{1}(5, 1).SamplingMode = 'Sample based';
    saveVarsTmp{1}(5, 1).DocUnits = '';
    saveVarsTmp{1}(5, 1).Description = '';
    saveVarsTmp{1}(6, 1) = Simulink.BusElement;
    saveVarsTmp{1}(6, 1).Name = 'Yaw';
    saveVarsTmp{1}(6, 1).Complexity = 'real';
    saveVarsTmp{1}(6, 1).Dimensions = [1 1];
    saveVarsTmp{1}(6, 1).DataType = 'double';
    saveVarsTmp{1}(6, 1).Min = [];
    saveVarsTmp{1}(6, 1).Max = [];
    saveVarsTmp{1}(6, 1).DimensionsMode = 'Fixed';
    saveVarsTmp{1}(6, 1).SamplingMode = 'Sample based';
    saveVarsTmp{1}(6, 1).DocUnits = '';
    saveVarsTmp{1}(6, 1).Description = '';
    saveVarsTmp{1}(7, 1) = Simulink.BusElement;
    saveVarsTmp{1}(7, 1).Name = 'AngularVelocity';
    saveVarsTmp{1}(7, 1).Complexity = 'real';
    saveVarsTmp{1}(7, 1).Dimensions = [1 3];
    saveVarsTmp{1}(7, 1).DataType = 'double';
    saveVarsTmp{1}(7, 1).Min = [];
    saveVarsTmp{1}(7, 1).Max = [];
    saveVarsTmp{1}(7, 1).DimensionsMode = 'Fixed';
    saveVarsTmp{1}(7, 1).SamplingMode = 'Sample based';
    saveVarsTmp{1}(7, 1).DocUnits = '';
    saveVarsTmp{1}(7, 1).Description = '';
    BusActorsActors.Elements = saveVarsTmp{1};
    clear saveVarsTmp;
end
