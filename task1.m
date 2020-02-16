function A_k = task1(image, k)
  %TODO
  A = double(imread(image));
  [U,S,V] = svd(A);
  m = size(A, 1);
  n = size(A, 2);
  [U,S,V] = svd(A);
  U(m+1:end, :) = 0;
  U(:, k+1:end) = 0;
  S(k+1:end, :) = 0;
  S(:, k+1:end) = 0;
  V(n+1:end, :) = 0;
  V(:, k+1:end) = 0;
  A_k = U*S*V';
end