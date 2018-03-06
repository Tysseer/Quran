function y = GenerateChunks(x,nWndSize,dMeanRatioBound,dUpScale)
  y = GenerateEnvelope(x,nWndSize);
  dMaxMax = max(max(y))*dUpScale;
  [m,n] = size(y);
  for iChnl = 1:n
    mu = mean(y(:,iChnl));
    dBound = dMeanRatioBound*mu;
    for i=1:m
      if (y(i,iChnl)>dBound)
        y(i,iChnl) = dMaxMax;
      else
        y(i,iChnl) = 0;
      endif
    endfor
  endfor
end