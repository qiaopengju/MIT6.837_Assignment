# MIT 6.837

### Assignment0:

#### Hint:

* 依概率选择变换矩阵：

```c++
float sum(0), t(drand48());
for (int k = 0; k < num_trans; k++){
  sum += probability[k];
  if (sum > t) break;
}
do_transform[k]_to_Vec();
```

* 需要特判仿射变换后点左边是否在图像内

#### 结果：

fern:

![0_fern](src/0_fern.png)

dragon:

![0_dragon](src/0_dragon.png)

giant x:

![0_dragon](src/0_giant_x.png)

triangle iters 30 times:

![0_dragon](src/0_sierpinski_triangle_30.png)

