M = csvread('arduinoReadings.csv',50,0);
a = linspace(1,size(M,1),size(M,1));
figure
hold on
V1 = M(:,1);
plot(a,V1)

V2 = M(:,2);
plot(a,V2)

V3 = M(:,3);
plot(a,V3)

V4 = M(:,4);
plot(a,V4)

V5 = M(:,5);
plot(a,V5)

V6 = M(:,6);
plot(a,V6)

figure
V7 = M(:,7);
plot(a,V7)