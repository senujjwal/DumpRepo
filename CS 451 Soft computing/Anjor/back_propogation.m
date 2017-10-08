clc;

i=1;
j=3;
k=1;

%X = [0.1 1.0; 0.2 1.1; 0.3 1.2; 0.4 1.3; 0.5 1.5];
%T = [1.2; 1.4; 1.6; 1.8; 2.0];
X = (0:0.1:2*pi)'
T = sin(X);

Wij = rand(i+1,j)
Wjk = rand(j+1,k)

eta  = 0.02;
iter = 0;
Etot = 100;

while Etot > 1e-10 && iter < 100
    
    iter = iter+1;
    Etot = 0;    
    
    for n = 1:size(T)/k
        
        X(n,:)
        horzcat(X(n,:),1)
        
        % Forward propogation - layer 1
        netj = horzcat(X(n,:),1) * (Wij)
        yj = 1./(1+exp(-netj))
        
        %yj(size(yj,2)+1) = 1
        %horzcat(yj,1)

        % Forward propogation - layer 2
        netk = horzcat(yj,1) * (Wjk)
        yk = 1./(1+exp(-netk));
        %yk = netk
                
        % Error Computation
        Etot = Etot + 0.5 * sum((yk-T(n)).^2)
        
        % Updating Wjk
        % dedxk = yk * (1 - yk) * (yk-T(n));
        % dedwjk = dedxk * yj;
        %(yk-T(n))
        %(1 - netk .^ 2)
        
        dWjk = ((yk-T(n)) .* (1 - netk .^ 2)) * horzcat(yj,1);
        %dWjk = ((yk-T(n)) .* (1)) * horzcat(yj,1)
        Wjk = Wjk - eta * dWjk'
        
        % Updating Wij
        % dedxj = sum((dedxk * Wjk),2) * yj * (1-yj)';
        % dedwij = dedxj * (X(n,:));
        % Wij = Wij - eta * dedwij;
        
        dWij = ((1 - netj .^ 2) .* sum(yk-T(n) .* Wij ,1))' * horzcat(X(n,:),1)
        Wij = Wij - eta * dWij'
        
    end

    % Plotting
    %hold on;
    %clf;
    %plot(X(:,1),D,'red');
    %plot(X(:,1),X * W','blue');
    %pause(0.001);
    
end

iter
display(Wij);
display(Wjk);

% Final Computation
%X
%ones(size(X,1),1)
%horzcat(X,ones(size(X,1),1))

%net = horzcat(X,ones(size(X,1),1)) * (Wij);
%yj = 1./(1+exp(-net));

%yj
%size(yj,1)
%ones(size(yj,1),1)

%net = horzcat(yj,ones(size(yj,1),1)) * (Wjk);
%yk = 1./(1+exp(-net));

       % Forward propogation - layer 1
        netj = horzcat(X,ones(size(X,1),1)) * (Wij);
        yj = 1./(1+exp(-netj));
        
        % Forward propogation - layer 2
        netk = horzcat(yj,ones(size(yj,1),1)) * (Wjk);
        yk = 1./(1+exp(-netk));

display(yk)
display(T)