noload_rpm = 290; % RPM
noload_speed = noload_rpm / 60 / 1000 * 360; % degrees / second
stall_torque = 33; % oz-in
stall_torque_nm = 33 * 0.2780139 / 39.3701

spring_max_torque = .230; % in-lbs, from 120 deg to parallel
k = spring_max_torque / 120 * 16; % oz-in / degree

syms theta
speed = (stall_torque - k * theta) * noload_speed / stall_torque;

t = eval(int(1/speed, theta, 0, 90))
