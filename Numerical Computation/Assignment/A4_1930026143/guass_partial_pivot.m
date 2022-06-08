function x = guass_partial_pivot(A, b)
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
        max_value=abs(AA(k,k));
        max_row=k;
        % Select the row which contains the maximum number in the rows
        for a=k:n
            if abs(AA(a,k))>max_value
                max_value=abs(AA(a,k));
                max_row=a;
            end
        end
        AA([max_row k], :) = AA([k max_row], :);
        disp(max_row);
        % Exchange the two rows to pivot
        %for b=1:n+1
        %    temp = AA(k,b);
        %    AA(k, b) = AA(max_row, b);
        %   AA(max_row, b) = temp;
        %end
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
