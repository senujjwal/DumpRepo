i=2;
j=2;
k=1;

X = [0.1 1.0; 0.2 1.1; 0.3 1.2; 0.4 1.3; 0.5 1.4];
Tk = [1.2; 1.4; 1.6; 1.8; 2.0];

Wij = rand(i+1,j);
Wjk = rand(j+1,k);
Etot = 10000;

eta  = 1;
iter = 0;

while Etot > 1e-10 && iter < 500
    
    iter = iter+1;
    Etot = 0;    
    
    for n = 1:size(D)
        
        %forward propogation 1st layer
        net = horzcat(X(n,:), 1) * (Wij);
        yj=1./(1+exp(-net))
        
        %forward propogation 2nd layer
        net = horzcat(yj,1) * (Wij);
        yk=1./(1+exp(-net));
        
        Etot= Etot + 0.5 * (yk-Tk(n));
        
        %updating Wjk
        dexk=yk(n) * (1-yk(n)) * (yk(n)-D(n));
        dewjk= dexk * yj(n);
        Wjk=Wjk - C * dewjk;
        
        %updating Wij
        dexj=yj(n) * (1-yj(n)) * sum(dexk*Wjk,2);
        dewjk= dexj * X;
        Wij=Wij - C * dewjk(n);
        
        %net = (X(i,:)) * (W');
        %E = 0.5 * ((D(i)-net)^2);
        %dW = eta * (D(i)-net) * X(i,:);

        %net = (X(i,:)) * (W');
        %E = 0.5 * ((D(i)-(1/(1+exp(-net))))^2);
        %dW = eta * (exp(-net)/(1+exp(-net))^2) * X(i,:);
        
        W = W + dW;
        
        Etot = Etot + E;
        
    end
    
    % Plotting
   % hold on;
   % clf;
    %plot(X(:,1),D,'red');
    %plot(X(:,1),X * W','blue');
    %pause(0.001);

    
end

iter
display(Wij);
display(Wjk);