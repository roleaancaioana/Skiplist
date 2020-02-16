function [min_dist output_img_index] = face_recognition(image_path, m, A, eigenfaces, pr_img)
  %TODO
  input_image = double(rgb2gray(imread(image_path)));
  [row col] = size(input_image);
  
  test_image = reshape(input_image, row*col, 1);
  pr_img_test = eigenfaces' * (test_image - m);
  
  min_dist = [];
  i = 1;
  while i<=10
    x = pr_img(:,i);
    temp = norm(pr_img_test - x);
    min_dist = [min_dist temp];
    ++i;
  endwhile
  
  [min_dist output_img_index] = min(min_dist);
end