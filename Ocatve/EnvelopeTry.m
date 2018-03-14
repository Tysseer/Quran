pkg load signal
%[x,fs] = audioread('D:\Audio\Trials\TrySoundFile\001006 - copy (4).wav');
%[x,fs] = audioread('C:\Data\MachineLearning\Quran\TrySoundFile\001006 - copy (4).wav');
strPaths = ['C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (1).wav' 
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (2).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (3).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (4).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (5).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (6).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (7).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (8).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (9).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (10).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (11).wav' 
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (12).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (13).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (14).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (15).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (16).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (17).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (18).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (19).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (20).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (21).wav' 
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (22).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (23).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (24).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (25).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (26).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (27).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (28).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (29).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (30).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (31).wav'
            'C:\Data\MachineLearning\Quran\Data\Ihdina-WAV\001006 - copy (32).wav'];
[nNumPaths,nDontCare] = size(strPaths);
for iPath = 1:nNumPaths
  strCurPath = strPaths(iPath,:);
[x,fs] = audioread(strCurPath);
[m,n] = size(x);
totalT = m/fs;
nWndSize = floor(m*(0.009/totalT));%90 msec is the chosen window size = 
y = GenerateEnvelope(x,nWndSize);
y = RegularizeY(y,0.15);
dMeanFactor = 0.5;

meanY = mean(y);
L=[1, m];
strTitle = strCurPath(60:length(strCurPath)-5);
for i = 1:1 % for now use first channel only
  hf = figure();
  title (strTitle);
  hold on;
  plot(x(:,i),'r');
  plot(y(:,i),'b');
  
  LL1 = [meanY(i) meanY(i)];
  plot(L,LL1,'k-.');
  LL1 *= dMeanFactor;
  plot(L,LL1,'k-.');
  

 endfor
%soundsc(x,fs);
%plot(y1,'k');
%plot(L,LL,'k-.');

%plot(L,LL2,'k-.');
 endfor
 
 soundsc(x,fs);
