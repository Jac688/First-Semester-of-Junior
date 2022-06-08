function [L, U, z, x] = lu_guass(A, b)

[n, m] = size(A);
% The number of rows should be equal to columns 
if n ~= m  
    error(1)
end
for k = 1:n-1
    if A(k, k) == 0
        error(1)
    end
    for i = k+1:n
        m = A(i, k)/A(k, k);
        A(i, k) = m; % lower triangle
        for j=k+1:n
            A(i, j) = A(i, j)-m*A(k, j);
        end
    end
end
L = eye(n) + tril(A, -1); % replace the diagnose with identity matrix
U = triu(A); 

Z = [L b];
z = zeros(n, 1);
for i=1:n
    tmp = Z(i,n+1);
    for j = 1:i-1
        tmp = tmp-Z(i,j)*z(j,1);
    end
    z(i,1)= tmp/Z(i,i);
end

R = [U z];
x = zeros(n, 1);
for i=n:-1:1
    tmp = R(i,n+1);
    for j = n:-1:i+1
        tmp = tmp-R(i,j)*x(j,1);
    end
    x(i,1)= tmp/R(i,i);
end


        
    

    
