function w = Newton_Q6(f, fp, x0, N, tol)
% Newton method
% eliminate the abnormal case
if fp(x0) == 0
    error(1)
end

cnt = 0;
xnext = x0 - f(x0)/fp(x0);

% for terminal condition f(x_k) < tol and the the limited number of iteration
while (abs(f(xnext)) > tol) && (cnt <= N)
    % means that the next derivative will be zero
    if isa(fp, 'numeric')
        xnext = xnext - f(xnext)/fp;
        cnt=cnt+1;
        w = [xnext cnt];
    else
        if fp(xnext) == 0
            error(1)
        end
        xnext = xnext - f(xnext)/fp(xnext);
        cnt=cnt+1;
        w = [xnext cnt];
    end
end

    