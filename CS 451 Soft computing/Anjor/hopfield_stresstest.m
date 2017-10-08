l=100; %Image Width
m=75; %Image height
n=8; %number of images

%Loading Images
test = imread('C:\Users\STUDENT\try1.jpg');

%test(:,:,1) = test(:,:,1) / 3  + test(:,:,2) / 3 + test(:,:,3) / 3;
%test(:,:,2) = test(:,:,1);
%test(:,:,3) = test(:,:,1);
max(test(:,:,2) - test(:,:,1))
max(test(:,:,3) - test(:,:,1))

exit

imwrite(test, 'C:\Users\STUDENT\try1_edit.jpg');

pause;



imwrite(test, 'C:\Users\STUDENT\try1_edit.jpg');

pause


x(:,1)=reshape(imread('C:\Users\STUDENT\try1.jpg'),l*m,1);

x
pause

x(:,2)=reshape(imread('C:\Users\STUDENT\2.bmp'),l*m,1);
x(:,3)=reshape(imread('C:\Users\STUDENT\3.bmp'),l*m,1);
x(:,4)=reshape(imread('C:\Users\STUDENT\4.bmp'),l*m,1);
x(:,5)=reshape(imread('C:\Users\STUDENT\5.bmp'),l*m,1);
x(:,6)=reshape(imread('C:\Users\STUDENT\6.bmp'),l*m,1);
x(:,7)=reshape(imread('C:\Users\STUDENT\7.bmp'),l*m,1);
x(:,8)=reshape(imread('C:\Users\STUDENT\8.bmp'),l*m,1);
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