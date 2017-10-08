function [V,W] = ErrorBackPropagation(X,D,M,ETA,Threshold)
%ErrorBackPropagation : This functions enables us to train (bi)layered 
%architectures of neural networks.
% Input Parameters :
%   X : List of training (points) vectors : LxP Array (P Lx1 Vectors)
%   D : List of Desired Outputs : NxP  Array (P Nx1 Vectors)
%   M : The number of neurons to use in the first layer.
% Returns :
%   V : Weight Array of First Layer : Mx(L+1) Array
%   W : Weight Array of Second Layer : Nx(M+1) Array

SIZE_X=size(X);
L=SIZE_X(1);
P=SIZE_X(2);

SIZE_D=size(D);
N=SIZE_D(1);

count=0;
TotalError=1e23;

v=2*rand(M,L+1)-1;
w=2*rand(N,M+1)-1;

while TotalError>Threshold
    for p=1:P
        x=[X(:,p);1];
        net_y=v*x;
        y=tanh(net_y/2);   % ? is Bipolar Sigmoid
        net_z=w*[y;1];
        z=net_z;           % ? is Linear
        Error_Vector=D(:,p)-z;
        delta_vector=ETA*Error_Vector;
        delta_w=delta_vector*[y',1];
        temp=w'*delta_vector;
        w=w+delta_w;
        delta_v=((1-y.^2).*temp(1:M)/2)*x';
        v=v+delta_v;
    end
    TotalError=0;
    for p=1:P
        net_y=v*[X(:,p);1];
        y=tanh(net_y/2);   % ? is Bipolar Sigmoid
        net_z=w*[y;1];
        z=net_z;           % ? is Linear
        Error_Vector=D(:,p)-z;
        TotalError = TotalError + Error_Vector'*Error_Vector;
    end
    count=count+1;
    disp(TotalError)
end
disp(count)
V=v;
W=w;
end