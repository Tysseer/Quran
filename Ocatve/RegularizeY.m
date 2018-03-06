function yS = RegularizeY(y,dMeanRatio)
  [m,n] = size(y);
  yS = y;
  for iChnl = 1:n
    mu = mean(y(:,iChnl));
    dCutoff = mu*dMeanRatio;
    for i=1:m
      dDiv = y(i,iChnl)/dCutoff;
      yS(i,iChnl) = floor(dDiv+0.5)*dCutoff;
    endfor
  endfor
end