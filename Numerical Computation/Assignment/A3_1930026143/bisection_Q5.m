function v = bisection_Q5(f, a, b, N, tol, eps)
% bisection method 
% check the sign of the two point 
if sign(f(a)) == sign(f(b))
    error(1);
end

cnt = 0;
x = (a+b)/2;
%|a-b|/|b| < esp and the the limited number of iteration
while (abs(b-a)/abs(b) > eps) && (cnt <= N) && (abs(f(x))>tol)
    x = (a+b)/2;
    % terminal condition f(x_k)<tol,
    if sign(f(x)) == sign(f(b))
        b=x;
    else
        a=x;
    end
    cnt = cnt+1;
    root = x;
    v = [root cnt];
end