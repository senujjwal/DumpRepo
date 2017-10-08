l=5; %Image Width
m=6; %Image height
n=10; %number of images

%Loading Images

x(:,1)=reshape(imread('C:\Users\STUDENT\0.bmp'),l*m,1);
x(:,2)=reshape(imread('C:\Users\STUDENT\1.bmp'),l*m,1);
x(:,3)=reshape(imread('C:\Users\STUDENT\2.bmp'),l*m,1);
x(:,4)=reshape(imread('C:\Users\STUDENT\3.bmp'),l*m,1);
x(:,5)=reshape(imread('C:\Users\STUDENT\4.bmp'),l*m,1);
x(:,6)=reshape(imread('C:\Users\STUDENT\5.bmp'),l*m,1);
x(:,7)=reshape(imread('C:\Users\STUDENT\6.bmp'),l*m,1);
x(:,8)=reshape(imread('C:\Users\STUDENT\7.bmp'),l*m,1);
x(:,9)=reshape(imread('C:\Users\STUDENT\8.bmp'),l*m,1);
x(:,10)=reshape(imread('C:\Users\STUDENT\9.bmp'),l*m,1);
x = (x * 2) - 1;

% Calculating weights

w = zeros(l*m,l*m);
for i = 1:n
    w = w + x(:,i) * x(:,i)';
end

w = w - eye(30,30);

x1 = reshape(imread('C:\Users\STUDENT\4d.bmp'),l*m,1) * 2 - 1;
x2 = zeros(l*m,1);
iter = 0;

while ~isequal(x1,x2)
    iter = iter + 1;
    x2 = x1;
    x1 = sign(w * x1);
end

x2 = ((reshape(x2,6,5)) + 1) / 2;
x2
iter
imshow(x2)