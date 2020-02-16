function task2(image, k)
  A=double(imread(image));
  m = size(A, 1);
  n = size(A, 2);
  A_k = task1(image, k);
  [U_k,S_k,V_k] = svd(A_k);
  [U,S,V] = svd(A);
  %Cerinta 2.1
  y = diag(S_k);
  figure(1);
  plot(1:k, y);
  
  %Cerinta 2.2
  s = 0;
  suma_k = [];
  for i = 1 : k
    s = s + S_k(i,i);
    suma_k(i) = s;
  endfor
  
  min_sum = sum(diag(S));
  figure(2);
  plot(1:k, suma_k / min_sum);

  %Cerinta 2.3
  aproximation_error = [];
  for p = 1 : k 
  A_k = task1(image, p);
    s = 0;
    for i = 1 : m  
      for j = 1 : n
        s = s + ((A(i,j) - A_k(i,j)).^2);
      endfor
    endfor
    aproximation_error(p) = s;
  endfor
  figure(3);
  plot(1:k, aproximation_error/(m*n));
  
  %Cerinta 2.4
  figure(4);
  compress_ratio = [];
  i = 1;
  while i<=k
    compress(i) = m * i + n * i + i;
    i++;
  endwhile 
  plot(1:k, compress / (m * n));
end