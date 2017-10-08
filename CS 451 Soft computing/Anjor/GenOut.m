function [ Out ] = GenOut( dim )

    Out = -ones(2^dim,dim);

    for i = 0:(2^dim)-1

        t=i;
        k=dim+1;

        while t > 0
            k=k-1;

            if mod(t,2) == 1
                Out(i+1,k)=-Out(i+1,k);
            end

            t = floor(t/2);
        end

    end

end