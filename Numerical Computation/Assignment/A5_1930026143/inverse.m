function Inv = inverse(A);
if det(A)==0
    erroe("The matrix is not consistent!");
[n, m] = size(A);
% The number of rows should be equal to columns 

if n ~= m  
    error("error");
end

A_I = [A eye(n)];
[r c] = size(A_I);
for k = 1:n-1
    if A_I(k, k) == 0
        error(1)
    end
    for i = k+1:n
        a = A_I(i, k)/A_I(k, k);
        for j=k:c
            A_I(i, j) = A_I(i, j)-a*A_I(k, j);
        end
    end
end

for k = r:-1:1
    if A_I(k, k) == 0
        error(1)
    end
    a = 1/A_I(k, k);
    for i = k:c
        A_I(k, i) = A_I(k, i)*a;
    end
    for j = k-1:-1:1
        tmp = A_I(j, k)/A_I(k,k);
        for l=k:c
            A_I(j,l)=A_I(j,l)-tmp*A_I(k,l);
        end
    end
end

Inv=A_I(:, c/2+ 1:c);
end




