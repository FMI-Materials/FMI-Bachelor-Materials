% material for lab 2 of SPER, computing the velocity map of a cluttered
% environment

clc; close all; clear all

%% initialize data

Vertices={...
    [-8.3290   -6.9309;....
    -2.7235   -4.4919;....
    1.3612   -9.5388;....
    0.4809   -6.8762;....
    -6.4501   -3.0096;....
    -7.9117   -2.9355],...
    [10.0188   -1.8142;....
    12.1472   -3.5173;....
    13.9495    0.2420;....
    13.9586   -4.7233;....
    14.3124   -4.2778;....
    9.2882   -0.3991;....
    10.6225    3.3276],...
    [0.2389    7.2554;....
    6.6464   -3.3750;....
    -0.3225    3.7266;....
    2.6028    6.6424;....
    -0.4003    2.9961;....
    1.0930   -2.5740]};

ubar= 1; % lower/upper bound for the control action
% construct the control action bounding set
U=Polyhedron([eye(2);-eye(2)],ones(4,1)*ubar);

% construct the polyhedral sets from their vertex representation
for i=1:length(Vertices)
    P(i)=Polyhedron(Vertices{i});
end

% continuous double integrator dynamics
Ac=[zeros(2) eye(2); zeros(2) zeros(2)];
Bc=[zeros(2);eye(2)];
Cc=[eye(2) zeros(2)];

% sampling time
T=0.1;

% construct the discrete equivalent system
A=eye(4)+T*Ac;
B=T*Bc;
C=Cc;

% number of steps to iterate for the backwards reachable set
R=5;

%% compute the velocity map polyhedrons (in the space of initial position + sequence of admissible inputs)

for i=1:length(P)
    for r=1:R
        VM{i}(r)=Polyhedron([P(i).A*[eye(2) -T*kron([(0:r)-(r+1)*T],eye(2))];...
            [zeros(2*(r+1),2) eye(2*(r+1))];...
            [zeros(2*(r+1),2) -eye(2*(r+1))]],...
            [P(i).b; ones(2*(r+1),1)*ubar; ones(2*(r+1),1)*ubar]);
    end
end

%% plot the environment plus the velocity map contours

plot(P,'Color','b','Alpha',.4)
hold on

for i=1:length(P)
    for r=1:R
        % from the 4D polyhedron we project into the position subspace and
        % the result is the set containing the obstacle and from which we
        % can still safely stop (zero velocity at the end of the
        % trajectory)
        plot(VM{i}(r).projection([1:2]),'Wire',1,'WireColor','r','Alpha',.4)
    end
end

figure; hold on; grid on

for i=1:length(P)
    subplot(1,3,i); hold on; grid on
    for r=1:R
        % we make an affine projection to retrieve the initial velocity
        % which guarantees safe stop
        plot(-T*repmat(eye(2),1,r+1)*VM{i}(r).projection(3:(2+(r+1)*2)),'Alpha',.4)
    end
    axis equal
end


