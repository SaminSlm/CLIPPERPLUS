function [u] = clipper(A)
%% Inputs:
%
%       A:  an nxn unweighted, symmetric adjacency matrix. 
%% Outputs:
%
%       u:      final iterate of the gradient ascent scheme

I = eye(size(A));
M = A + I;
n = length(M); % input size

Mc = ones(size(M)) - M; % binay complement of constraint matrix M

u0 = rand(n,1);

%% Set parameters
tolu = 1e-8; 
tolF = 1e-8;  
sigma = 0.01;
beta = 0.5;  % for reduction of alpha based on backtracking line search
maxlsiters = 99; % maximum number of line search iterations
maxiniters = 200; % maximum number of gradient ascent steps for each d
maxoliters = 1000; % maximum number of outer loop iterations
epsilon = 1e-9; % numerical threshold to replace 0 with 100x machine epsilon



% One step of power method to have a good scaling of u
u = M * u0;
u = u / norm(u);

% Initial d 
mcu = Mc * u;
idxD = (mcu > epsilon) & (u > epsilon); % indices where mcu>0 and u>0
   if any(idxD)
   Mu = M * u;
   d = mean( Mu(idxD)./mcu(idxD) ) ;% smallest d that makes ?u= Mu - dmcu  hit the positive orthant boundaries (for indices where mcu>0 and u>0)
   else
   d = 0; % in this case matrix Mc is all zeros (or there%s no active constraint)
   end
   
Md = M - d * Mc;


%% Projected gradient ascent loop

i = 1;
outerloop = true;
 while outerloop && i<maxoliters
    F = u.' * Md * u; % object value
    j = 1;
    innerloop = true;
    while innerloop && j<maxiniters
        gradF = Md * u; % gradient
        gradFop = gradF - gradF.'*u * u; %
        alpha = 1;
        k = 1;
        armijo = false;
        while ~armijo && k<maxlsiters
            unew = u + alpha * gradFop;    % gradient step
            unew = max(unew/norm(unew), 0); 
            Fnew = unew.' * Md * unew;     % new objective value
            gradfopnew = 2*Md*unew -unew*unew'*2*Md*unew;
            deltau = u - unew;
            deltaF = Fnew - F;             % change in objective value
            
            if (deltaF < norm(sigma * gradFop*u'*deltau)) % armijo steps
                alpha = alpha * beta; 
            else
                alpha = alpha / beta ^ 0.5;
                armijo = true;
            end
            
            k = k + 1;
        end

        deltau = norm(unew - u); % change in vector u
        if ( (deltau < tolu) || (abs(deltaF) < tolF) ) 
            innerloop = false; % if desired accuracy reached break from inner loop
        end
        
        % update values
        F = Fnew;
        u = unew;
        
        j = j + 1;
    end
    
    % Increase d
    mcu = Mc * u;
   idxD = (mcu > epsilon) & (u > epsilon); % indices where mcu>0 and u>0 
     if any(idxD)
       Mu = M * u;
       deltad = mean(abs( Mu(idxD)./mcu(idxD) )); % Find smallest deltad that makes gradF=Mu-dmcu  hit the positive orthant boundaries (for indices where mcu>0 and u>0)
        
        d = d + deltad; % increase d
        Md = M - d * Mc; % update matrix Md
     end
       if (all(u == 0) || (numel(unique(u)) == 2 && ismember(0, unique(u))))
            outerloop = false;
       end

    i = i + 1;
end


 
end

