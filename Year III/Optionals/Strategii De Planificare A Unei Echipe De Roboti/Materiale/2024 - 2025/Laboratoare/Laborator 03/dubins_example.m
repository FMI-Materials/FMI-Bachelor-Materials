
% Define waypoints with [x, y, heading]
pt1 = struct('x', 0, 'y', 0, 'psi', 0);
pt2 = struct('x', 6000, 'y', 7000, 'psi', 260);
Wptz = [pt1, pt2];

% Compute and plot the Dubins path
for i = 1:length(Wptz)-1
    param = calcDubinsPath(Wptz(i), Wptz(i+1), 90, 20);
    path = dubinsTrajectory(param, 1);
    plot(path(:,1), path(:,2), 'b-', 'LineWidth', 2);
    hold on;
    plot(Wptz(i).x, Wptz(i).y, 'kx', 'MarkerSize', 10);
    plot(Wptz(i+1).x, Wptz(i+1).y, 'kx', 'MarkerSize', 10);
end
grid on;
axis equal;
title("Dubins Path");
xlabel("X");
ylabel("Y");
hold off;


function param = calcDubinsPath(wpt1, wpt2, vel, phi_lim)
psi1 = headingToStandard(wpt1.psi) * pi / 180;
psi2 = headingToStandard(wpt2.psi) * pi / 180;

turn_radius = (vel^2) / (9.8 * tan(phi_lim * pi / 180));
dx = wpt2.x - wpt1.x;
dy = wpt2.y - wpt1.y;
D = sqrt(dx^2 + dy^2);
d = D / turn_radius;
theta = mod(atan2(dy, dx), 2 * pi);
alpha = mod(psi1 - theta, 2 * pi);
beta = mod(psi2 - theta, 2 * pi);

[tz, pz, qz] = deal(zeros(1, 6));
[tz(1), pz(1), qz(1)] = dubinsLSL(alpha, beta, d);
[tz(2), pz(2), qz(2)] = dubinsLSR(alpha, beta, d);
[tz(3), pz(3), qz(3)] = dubinsRSL(alpha, beta, d);
[tz(4), pz(4), qz(4)] = dubinsRSR(alpha, beta, d);
[tz(5), pz(5), qz(5)] = dubinsRLR(alpha, beta, d);
[tz(6), pz(6), qz(6)] = dubinsLRL(alpha, beta, d);

best_cost = inf;
best_word = -1;
seg_final = [0, 0, 0];

for x = 1:6
    if tz(x) ~= -1
        cost = tz(x) + pz(x) + qz(x);
        if cost < best_cost
            best_word = x;
            best_cost = cost;
            seg_final = [tz(x), pz(x), qz(x)];
        end
    end
end

param = struct('seg_final', seg_final, 'turn_radius', turn_radius, 'type', best_word);
end

function [t, p, q] = dubinsLSL(alpha, beta, d)
tmp0 = d + sin(alpha) - sin(beta);
tmp1 = atan2(cos(beta) - cos(alpha), tmp0);
p_squared = 2 + d^2 - (2 * cos(alpha - beta)) + (2 * d * (sin(alpha) - sin(beta)));

if p_squared < 0
    t = -1; p = -1; q = -1;
else
    t = mod(tmp1 - alpha, 2 * pi);
    p = sqrt(p_squared);
    q = mod(beta - tmp1, 2 * pi);
end
end

function [t, p, q] = dubinsRSR(alpha, beta, d)
tmp0 = d - sin(alpha) + sin(beta);
tmp1 = atan2(cos(alpha) - cos(beta), tmp0);
p_squared = 2 + d^2 - (2 * cos(alpha - beta)) + (2 * d * (sin(beta) - sin(alpha)));

if p_squared < 0
    t = -1; p = -1; q = -1;
else
    t = mod(alpha - tmp1, 2 * pi);
    p = sqrt(p_squared);
    q = mod(-beta + tmp1, 2 * pi);
end
end

function [t, p, q] = dubinsRSL(alpha, beta, d)
tmp0 = d - sin(alpha) - sin(beta);
p_squared = -2 + d^2 + 2 * cos(alpha - beta) - 2 * d * (sin(alpha) + sin(beta));

if p_squared < 0
    t = -1; p = -1; q = -1;
else
    p = sqrt(p_squared);
    tmp2 = atan2(cos(alpha) + cos(beta), tmp0) - atan2(2, p);
    t = mod(alpha - tmp2, 2 * pi);
    q = mod(beta - tmp2, 2 * pi);
end
end

function [t, p, q] = dubinsLSR(alpha, beta, d)
tmp0 = d + sin(alpha) + sin(beta);
p_squared = -2 + d^2 + 2 * cos(alpha - beta) + 2 * d * (sin(alpha) + sin(beta));

if p_squared < 0
    t = -1; p = -1; q = -1;
else
    p = sqrt(p_squared);
    tmp2 = atan2(-cos(alpha) - cos(beta), tmp0) - atan2(-2, p);
    t = mod(tmp2 - alpha, 2 * pi);
    q = mod(tmp2 - beta, 2 * pi);
end
end

function [t, p, q] = dubinsRLR(alpha, beta, d)
tmp_rlr = (6 - d^2 + 2 * cos(alpha - beta) + 2 * d * (sin(alpha) - sin(beta))) / 8;

if abs(tmp_rlr) > 1
    t = -1; p = -1; q = -1;
else
    p = mod(2 * pi - acos(tmp_rlr), 2 * pi);
    t = mod(alpha - atan2(cos(alpha) - cos(beta), d - sin(alpha) + sin(beta)) + p / 2, 2 * pi);
    q = mod(alpha - beta - t + p, 2 * pi);
end
end

function [t, p, q] = dubinsLRL(alpha, beta, d)
tmp_lrl = (6 - d^2 + 2 * cos(alpha - beta) + 2 * d * (-sin(alpha) + sin(beta))) / 8;

if abs(tmp_lrl) > 1
    t = -1; p = -1; q = -1;
else
    p = mod(2 * pi - acos(tmp_lrl), 2 * pi);
    t = mod(-alpha - atan2(cos(alpha) - cos(beta), d + sin(alpha) - sin(beta)) + p / 2, 2 * pi);
    q = mod(beta - alpha - t + p, 2 * pi);
end
end


function path = dubinsTrajectory(param, step)
total_length = sum(param.seg_final) * param.turn_radius;
length = floor(total_length / step);
path = zeros(length, 2);  % Ensure it only has X and Y columns

for i = 1:length
    dubins_point = dubinsPath(param, i * step);
    path(i, :) = dubins_point(1:2);  % Extract only X and Y
end
end

function end_pt = dubinsPath(param, t)
tprime = t / param.turn_radius;
p_init = [0, 0, headingToStandard(param.type) * pi / 180];

% Dubins segment types
L_SEG = 1;
S_SEG = 2;
R_SEG = 3;
DIRDATA = [L_SEG, S_SEG, L_SEG; L_SEG, S_SEG, R_SEG; R_SEG, S_SEG, L_SEG;
    R_SEG, S_SEG, R_SEG; R_SEG, L_SEG, R_SEG; L_SEG, R_SEG, L_SEG];

types = DIRDATA(param.type, :);
param1 = param.seg_final(1);
param2 = param.seg_final(2);
mid_pt1 = dubinsSegment(param1, p_init, types(1));
mid_pt2 = dubinsSegment(param2, mid_pt1, types(2));

if tprime < param1
    end_pt = dubinsSegment(tprime, p_init, types(1));
elseif tprime < (param1 + param2)
    end_pt = dubinsSegment(tprime - param1, mid_pt1, types(2));
else
    end_pt = dubinsSegment(tprime - param1 - param2, mid_pt2, types(3));
end

end_pt(1) = end_pt(1) * param.turn_radius + param.seg_final(1);
end_pt(2) = end_pt(2) * param.turn_radius + param.seg_final(2);
end_pt(3) = mod(end_pt(3), 2 * pi);
end

function seg_end = dubinsSegment(seg_param, seg_init, seg_type)
L_SEG = 1;
S_SEG = 2;
R_SEG = 3;
seg_end = zeros(1, 3);

if seg_type == L_SEG
    seg_end(1) = seg_init(1) + sin(seg_init(3) + seg_param) - sin(seg_init(3));
    seg_end(2) = seg_init(2) - cos(seg_init(3) + seg_param) + cos(seg_init(3));
    seg_end(3) = seg_init(3) + seg_param;
elseif seg_type == R_SEG
    seg_end(1) = seg_init(1) - sin(seg_init(3) - seg_param) + sin(seg_init(3));
    seg_end(2) = seg_init(2) + cos(seg_init(3) - seg_param) - cos(seg_init(3));
    seg_end(3) = seg_init(3) - seg_param;
elseif seg_type == S_SEG
    seg_end(1) = seg_init(1) + cos(seg_init(3)) * seg_param;
    seg_end(2) = seg_init(2) + sin(seg_init(3)) * seg_param;
    seg_end(3) = seg_init(3);
end
end

function angle = wrapTo360(angle)
angle = mod(angle, 360);
if angle == 0 && angle > 0
    angle = 360;
end
end

function angle = wrapTo180(angle)
angle = mod(angle + 180, 360) - 180;
end

function thet = headingToStandard(hdg)
thet = wrapTo360(90 - wrapTo180(hdg));
end
