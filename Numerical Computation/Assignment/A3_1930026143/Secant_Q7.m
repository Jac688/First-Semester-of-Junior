function u = Secant_Q7(f, x0, x1, N, tol)

% Secant method
cnt = 0;
xprev = x0;
xnext = x1;
while (cnt <= N) && (abs(f(xnext))> tol)
    xtmp = xnext;
    xnext = xnext - ((xnext-xprev)/(f(xnext)-f(xprev)))*f(xnext);
    xprev =xtmp;
    cnt = cnt+1;
end
u = [xnext cnt];