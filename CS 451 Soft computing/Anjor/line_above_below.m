x = input('enter points on the 2d plane x,y');
x(3)=1;
w= [1 ; 1 ;-1];
sum = x*w;
if(sign(sum)==1)
    plot(x(1),x(2),'c+:')
    display('case1:above the line');
else
    plot(x(1),x(2),'c+:')
    display('case2:below the line');
end