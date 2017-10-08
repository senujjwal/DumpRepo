% Region boundries: 0,0 - 10,10
M = 5; % No. of clusters
m = 10; % No. of centroids
n = 100; % No. of points
r = 0.5; % Radius of region
eta = 0.1; % Learning constant


% Please rewrite this to ensure region spacing!
mids = 8 * rand(M,2) + 1;

for i = 1:n
    dest = randperm(M);
    x(i,:) = mids(dest(1),:) + ((rand(1,2) * 2) - 1) * r;
end

w = 10 * rand(m,2);

clf;
hold on;
plot(x(:,1),x(:,2),'xr');
plot(w(:,1),w(:,2),'ob');
axis([0 10 0 10]);

%pause;

for epoch = 1:5
    epochorder = randperm(n);
    
    for i = 1:n
        
        point = x(epochorder(i),:);
        c = 1;
        cdist = sqrt( (point(1)-w(1,1))^2 + (point(2)-w(1,2))^2 );
        
        for j = 2:m
            if cdist > sqrt((point(1)-w(j,1))^2 + (point(2)-w(j,2))^2)
                c = j;
                cdist = sqrt((point(1)-w(j,1))^2 + (point(2)-w(j,2))^2);
            end
        end
        
        pause(0.01);
        
        w(c,:) = w(c,:) + eta * (point - w(c,:));
        
        clf;
        hold on;
        plot(x(:,1),x(:,2),'xr');
        plot(w(:,1),w(:,2),'ob');
        axis([0 10 0 10]);
    end
        
end