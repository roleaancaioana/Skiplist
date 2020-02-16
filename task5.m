function task5(image, k)
  A = double(imread(image));
  A_temp = A;
  m = size(A, 1);
  n = size(A, 2);
  [A_k S] = task3(image, k);
  %graficul 1
  figure(1);
  x = diag(S);
  plot(1:k, x);
  
  %graficul 2
  miu = [];
  
  for i = 1 : m
    s = sum(A(i,:));
    miu(i) = s / n;
  endfor
  
  for i = 1 : m
    A(i,:) = A(i,:) - miu(i);
  endfor 
  
  Z = A' / sqrt(n-1);
  [U,S,V] = svd(Z);
  
  s_k = 0;
  suma_k=[];
  for i = 1 : k
    s_k += S(i,i);
    suma_k(i) = s_k;
  endfor
  
  suma_min = sum(diag(S));
  
  figure(2);
  plot(1 : k, suma_k / suma_min);  
  
  %graficul 3
  figure(3);
  aproximation_error = [];
  i = 1;
  while i <= k 
    [Ak] = task3(image, i);
    aux = (A_temp - Ak).^2;
    s = sum(aux(:));
    aproximation_error(i) = s;
    i++;
  endwhile
  plot(1 : k, aproximation_error/ (m * n));

  %graficul 4
  figure(4);
  compress = [];
  i = 1;
  while i <= k
    compress(i) = (2 * i + 1) / n;
    ++i;
  endwhile 
  plot(1:k, compress);
  end