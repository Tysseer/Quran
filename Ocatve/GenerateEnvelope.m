function y = GenerateEnvelope(x,nWndSize)
  [m,n] = size(x);
  y = x;
  for iChnl = 1:n
    iIn=1;
    iOut=1;
    while (iIn<=m)
      dMax=0;
      for i=1:nWndSize
        if (dMax < x(iIn,iChnl))
          dMax = x(iIn,iChnl);
        endif
        iIn++;
        if(iIn>m)
          break;
        endif
      endfor %i = 1: nWndSize
      
      for i=1:nWndSize
        y(iOut,iChnl) = dMax;
        iOut++;
        if(iOut>m)
          break;
        endif
      endfor %i = 1: nWndSize
      
    endwhile
  endfor
end