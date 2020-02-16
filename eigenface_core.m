function [m A eigenfaces pr_img] = eigenface_core(database_path)
  T = [];
  i = 1;
  while i <= 10
    image_path = strcat(database_path,'/',int2str(i),'.jpg');
    image_matrix = double(rgb2gray(imread(image_path)));
    [row col] = size(image_matrix);
    temp = reshape(image_matrix, row*col,1);
    T = [T temp];
    ++i;
  endwhile
    m = mean(T,2);
    A = T - m;
    
    AUX = A' * A;
    [V D] = eig(AUX);
    AUX_VECT = []; 
    i = 1;
    while i <= size(V,2) 
      if( D(i,i) > 1 )
        AUX_VECT = [AUX_VECT V(:,i)];
      endif
      ++i;
    endwhile
  
    eigenfaces = A * AUX_VECT;
    pr_img = [];
    i = 1;
    while i <= 10
      temp = eigenfaces'*A(:,i);
      pr_img = [pr_img temp];
      ++i;
    endwhile
    
end