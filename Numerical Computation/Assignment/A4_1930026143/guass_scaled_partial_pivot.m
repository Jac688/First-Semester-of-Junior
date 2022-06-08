function x = guass_scaled_partial_pivot(A, b)
AA=[A b];
[n,m] = size(A);
x=zeros(n,1);
if n ~= m
    error(1);
elseif n ~= size(b)
    error(1);
else
    for k=1:n-1
        % Initialize the max information 
        scalar = abs(AA(k,k)/max(AA(k,:)));
        max_row=k;
        % Select the row which contains the max scalar in each rows
        for a=k:n
            if AA(a,k)/max(AA(k,:))>scalar
                scalar=abs(AA(a,k)/max(AA(a,:)));
                max_row=a;
            end
        end
        AA([max_row k], :) = AA([k max_row], :);
        % Exchange the scalared to the kth row
        %for b=1:n+1
        %   temp = AA(k,b);
        %    AA(k, b) = AA(max_row, b);
        %    AA(max_row, b) = temp;
        % end
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
