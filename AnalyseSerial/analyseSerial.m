M = csvread('P10I0.csv',2,0);
sensors = M(:,1:6);
weightedAverage = M(:,7);
time = M(:,8);
figure
imagesc(sensors)
title('Kp=1/10, Ki=0')
figure
plot(time,weightedAverage)
title('Kp=1/103, Ki=0')
