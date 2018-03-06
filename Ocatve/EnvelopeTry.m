pkg load signal
%[x,fs] = audioread('D:\Audio\Trials\TrySoundFile\001006 - copy (4).wav');
%[x,fs] = audioread('C:\Data\MachineLearning\Quran\TrySoundFile\001006 - copy (4).wav');
[x,fs] = audioread('C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (4).wav');
[m,n] = size(x);
totalT = m/fs;
nWndSize = floor(m*(0.009/totalT));%90 msec is the chosen window size = 
y = GenerateEnvelope(x,nWndSize);
y = RegularizeY(y,0.15);
dMeanFactor = 0.5;

meanY = mean(y);
L=[1, m];

for i = 1:min(1,n-1)
  figure(i);
  hold on;
 % plot(x(:,i),'r');
  plot(y(:,i),'b');
  LL1 = [meanY(i) meanY(i)];
  plot(L,LL1,'k-.');
  LL1 *= dMeanFactor;
  plot(L,LL1,'k-.');
 endfor
soundsc(x,fs);
%plot(y1,'k');
%plot(L,LL,'k-.');

%plot(L,LL2,'k-.');
