% Stream Function (Psi) for a Rankine Half-Body
% Superposition of Uniform Flow and a Point Source
clc
clear

% Grid definition
X = -20:0.01:20;
Y = X;
[x, y] = meshgrid(X,Y);

% Flow parameters
q = 10; % Source strength
U = 1;  % Free-stream velocity

% Coordinate transformation and Stream Function calculation
r = sqrt(x.^2 + y.^2);
theta = atan(y./x);
z = U.*y + (q / (2*pi)).*theta;

% Visualization of streamlines
contour(z, 15);
