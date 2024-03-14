function [C,cmax] = PMC(adjacency_matrix,core_numbers)

A = sparse(adjacency_matrix);
c_n = core_numbers;
 n = size(A, 1); % Number of vertices
 
    
    % Initialize variables
    C = []; 
    cmax = 0;
    
    % Sort vertices by core number in descending order
    [~, sorted_indices] = sort(c_n, 'descend');
    sorted_vertices = sorted_indices';
    
    % Loop over sorted vertices
    for i = 1:n
        vi = sorted_vertices(i);
        
        if c_n(vi) >= cmax
            % Neighbors of vi with core numbers >= cmax
            S = find(A(vi,:) & (c_n >= cmax)');
            
            % Sort neighbors in descending order by core number
            [~, sorted_neighbors] = sort(c_n(S), 'descend');
            sorted_neighbors = S(sorted_neighbors);
            
            % Initialize C'
            C_prime = [vi];
            
            % Loop over sorted neighbors
            for j = 1:length(sorted_neighbors)
                sj = sorted_neighbors(j);
                
                % Check if sj is connected to all vertices in C'
                
                if all(A(C_prime, sj))
                    C_prime = [C_prime, sj]; % Add sj to C'
                end
                
                % If C' forms a larger clique, update C and cmax
                if length(C_prime) > cmax
                    C = C_prime;
                    cmax = length(C_prime)-1;
                end
            end
        end
    end
  
    


end

