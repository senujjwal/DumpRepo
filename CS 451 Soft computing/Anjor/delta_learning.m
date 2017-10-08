X = [0.1 1; 0.2 1; 0.3 1; 0.4 1; 0.5 1];
D = [1.2; 1.4; 1.6; 1.8; 2.0];

W = rand(1,2)
Etot = 10000;

eta  = 1;
iter = 0;

while Etot > 1e-10 && iter < 500
    
    iter = iter+1;
    Etot = 0;    
    
    for i = 1:size(D)
        
        %net = (X(i,:)) * (W');
        %E = 0.5 * ((D(i)-net)^2);
        %dW = eta * (D(i)-net) * X(i,:);

        net = (X(i,:)) * (W');
        E = 0.5 * ((D(i)-(1/(1+exp(-net))))^2);
        dW = eta * (exp(-net)/(1+exp(-net))^2) * X(i,:);
        
        W = W + dW;
        
        Etot = Etot + E;
        
    end
    
    % Plotting
    hold on;
    clf;
    plot(X(:,1),D,'red');
    plot(X(:,1),X * W','blue');
    pause(0.001);

    
end

iter
display(W);
