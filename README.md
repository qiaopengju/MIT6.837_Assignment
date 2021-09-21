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

* 需要特判仿射变换后点坐标是否在图像内
* int atoi(const char *str); 将字符串数字变为int

#### Result：

fern:

![0_fern](src/0_fern.png)

dragon:

![0_dragon](src/0_dragon.png)

giant x:

![0_dragon](src/0_giant_x.png)

triangle iters 30 times:

![0_dragon](src/0_sierpinski_triangle_30.png)

### Assignment1:

#### Hint:



#### Result:

```shell
./raytracer -input src/scene1_01.txt -size 200 200 -output output1_01.tga -depth 9 10 depth1_01.tga
```

![1_output1_01](src/1_output1_01.png)

![1_depth1_01](src/1_depth1_01.png)

```shell
./raytracer -input src/scene1_02.txt -size 200 200 -output output1_02.tga -depth 9 10 depth1_02.tga
```

![1_output1_02](src/1_output1_02.png)

![1_depth1_02](src/1_depth1_02.png)

```shell
./raytracer -input src/scene1_07.txt -size 200 200 -output output1_07.tga -depth -2 2 depth1_07.tga
```

![1_output1_07](src/1_output1_07.png)

![1_depth1_07](src/1_depth1_07.png)

