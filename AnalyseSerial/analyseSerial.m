M = csvread('arduinoReadings.csv',2,0);
sensors = M(:,1:6);
weightedAverage = M(:,7);
time = M(:,8);
figure
imagesc(sensors)
figure
plot(time,weightedAverage)

