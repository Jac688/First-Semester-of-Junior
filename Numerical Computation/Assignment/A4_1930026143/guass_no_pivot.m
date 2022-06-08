function x = guass_no_pivot(A, b)
AA=[A b];
[n,m] = size(A);
x=zeros(n,1);
if n ~= m
    error(1);
elseif n ~= size(b)
    error(1);
else
    for k=1:n-1
        if A(k,k) == 0
            error(1);
        end
        
        for i=k+1:n
            m = AA(i, k)/AA(k,k);
            a=cell(1);
            for j=k:n+1
                AA(i,j)=AA(i,j)-m*AA(k,j);
            end
            % displace the result
            a{1}=AA;
            disp(a{1});
        end
    end
    x(n)=AA(n,n+1)/AA(n,n);
    for i = n-1:-1:1
        s=0;
        for j=i+1:n
            s=s+AA(i,j)*x(j);
        end
        x(i)=(AA(i, n+1)-s)/AA(i,i);
    end
end

