function [A_k S] = task4(image, k)
  A=double(imread(image));
  m = size(A, 1);
  n = size(A, 2);
  miu = [];
  
  for i = 1 : m
    s = sum(A(i,:));
    miu(i) = s / n;
  endfor
  
  for i = 1 : m
    A(i,:) = A(i,:) - miu(i);
  endfor 
  
  Z = (A*A') / (n-1);
  [V,S] = eig(Z);
  W = V(1:m, (end - k + 1):end);
  Y = W' * A;
  A_k = W*Y + miu';
endfunction