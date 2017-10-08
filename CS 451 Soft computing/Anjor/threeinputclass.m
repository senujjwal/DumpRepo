Out = GenOut(8);
Ques = GenOut(3);

SepCount = 0;
NonSepCount = 0;

for i = 0:255
   
    OutSet = (Out(i+1,:))'
    
    w=-ones(4);
    Satisfy = 0;
    
    while w(1) <= 1
        if isequal(sign(Ques(:,1)*w(1) + Ques(:,2)*w(2) + Ques(:,3)*w(3)+ 1*w(4)) , OutSet);
               Satisfy = 1;
               break;
        end
        
        for j = 4:-1:1
           w(j) = w(j) + 0.1;
           if w(j) <= 1
               break;
           else
               w(j) = -1;
           end
        end
    end
    
    if Satisfy == 1
        % Function is linearly separable
        SepCount = SepCount + 1;
        
        w
        display('Linearly Separable');
    else
        % Function is linearly nonseparable
        NonSepCount = NonSepCount + 1;
        
        w
        display('Linearly Nonseparable');
    end
    
end


display('Separable Count')
SepCount
display('Nonseparable Count')
NonSepCount