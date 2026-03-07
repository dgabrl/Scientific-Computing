% Velocity Potential (Phi) for a Rankine Half-Body
% Represents equipotential lines perpendicular to streamlines
clc
clear

% Grid definition
X = -20:0.01:20;
Y = X;
[x, y] = meshgrid(X,Y);

% Flow parameters
q = 10; % Source strength
U = 1;  % Free-stream velocity

% Coordinate transformation and Velocity Potential calculation
r = sqrt(x.^2 + y.^2);
theta = atan(y./x);
z = U.*x + (q / (2*pi)).*log(r);

% Visualization of equipotential lines
contour(z, 15);
