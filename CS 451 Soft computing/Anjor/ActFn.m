function [ Y ] = ActFn( X )
    Y = 1 / (1 + exp(-X));
end