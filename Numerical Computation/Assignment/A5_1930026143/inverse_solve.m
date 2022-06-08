function x = inverse_solve(A, b)
if det(A)==0
    error('A is not consistent!')
end
[n m] = size(A);
if n~=m
    error(1)
end
inv = inverse(A);
x = inv*b
end
