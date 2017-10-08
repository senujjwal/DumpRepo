x= [1 1;5 1];
sum =  5;
if(sign(sum)==1)
    plot(x(1),x(2),'c+:')
    display('case1:above the line');
else
    plot(x(1),x(2),'c+:')
    display('case2:below the line');
end