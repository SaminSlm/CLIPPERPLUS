function [c] = clipperplus(A)

%% Inputs:
%
%       A:  an nxn unweighted, symmetric adjacency matrix. 
%% Outputs:
%
%       c:  vertices that form maximal clique

sparse_A = sparse(A);
k = core_numbers(sparse_A);

[c,cmax] = PMC(A,k);% Degeneracy-ordered greedy clique

L = find(k >= length(c)); % Find vertices with core numbers equal or more than cmax

pruned_A = A(L ,L);

 u0 = ones(1, length(L));
  common_elements = L(ismember(L,c));

 for i = 1:length(common_elements)
 u0(common_elements(i)) = 0 ;%initial guess
 end
  
 if ~isempty(pruned_A)
   u = clipper(pruned_A, u0); %Continuous-relaxation clique
   u(u > 0) = 1;
   cprime = L' .*u';
   cprime = cprime(cprime ~= 0);%vertices that form maximal clique
   
   if (length(cprime) >= length (c))
     c = cprime;
   end
end
 


end

