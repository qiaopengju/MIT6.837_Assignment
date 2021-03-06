# MIT 6.837

<img src="src/6.837.png">

## Assignment0:

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

* fern:

```shell
./ifs -input src/fern.txt -points 50000 -iters 30 -size 400 -output fern.tga
```

![0_fern](src/0_fern.png)

---

## Assignment1:

原理：相机从每个像素发出射线，显示最早击中物体的贴图

#### Hint:

* Orthographic Camera：

![](src/1_orthographic_camera.png)

* 在坐标运算时，最好在[0,1]标准化空间坐标进行，在遇到实际的屏幕时，可以用x = x' * widht;  y = y' * height来换算
* Image类中颜色坐标范围是[0,1]
  * 输出t在[depth_min, depth_max]之间的灰度，要在Clamp之后，作如下变换：

```c++
if (t >= depth_min && t <= depth_max){
  //离摄像机越近的物体，t越小，越应该是白色，但是白色对应1，所以应该用1减去t变换
	float grey = 1 - (t - depth_min) / (depth_max - depth_min);
  Vec3f color(grey, grey, grey);
}

```

* 隐式表示的球体求交点：

  ![1_sphere_intersection](src/1_sphere_intersection.png)

  * Ray: direction is an unit vector

![1_tp](src/1_tp.png)

![1_d2](src/1_d2.png)

如果d比球半径要大，说明Ray与Sphere不相交，反之Ray与Sphere相交

相交在参数t时刻,射线原点在球内：

![1_t](src/1_t.png)

射线原点在球外：

![1_t2](src/1_t2.png)

判断物体射线交点，如果得到t比hit的t小，那么同时更新t和Material

```c++
bool Sphere::intersect(const Ray &r, Hit &h, float tmin){
    Vec3f o2c = center - r.getOrigin();     //射线原点指向球心向量
    float tp = o2c.Dot3(r.getDirection());
    float o2c2 = o2c.Dot3(o2c);             //ray, sphere中心距离的平方
    float d2 = o2c2 - tp*tp;
    if (d2 > radius*radius) return false;   //不相交
    float t = sqrt(radius*radius - d2);
    
    if (tp - t < tmin){
        if (tp + t > tmin){ //射线在球内部，且相交
            if (h.getMaterial() == NULL || h.getT() > tp+t){ //如果t比hit中的t小，则更新h
          		h.set(tp + t, material, r);
            }
            return true;
        } else return false;//不相交

    } else { //射线在球外部，且相交
        if (h.getMaterial() == NULL || h.getT() > tp+t){ //如果t比hit中的t小，则更新h
      		h.set(tp - t, material, r);
        }
        return true;
    }
}
```

---

* 类Group中的ObjectList应该用Object3D**类型，因为ObjectList应当是存Object3D的指针的数组，赋予ObjectList内存空间：

```c++
ObjectList = new Object3D*[n];	//Group中有n个Objects
```

* std::numeric_limits\<float\>::max 返回float最大值
* 三个向量定义相机：Up, Right, LookAt，当Up和LookAt不垂直时要修正Up:
  * Right = LookAt x Up: 通过叉乘得到Right向量
  * Up = Right x LookAt: 通过上一步得到的Right向量和LookAt向量，修正Up向量
  * 相机的三个向量需要标准化

#### Result:

```shell
./raytracer -input src/scene1_02.txt -size 200 200 -output output1_02.tga -depth 9 10 depth1_02.tga
```

![1_output1_02](src/1_output1_02.png)

![1_depth1_02](src/1_depth1_02.png)



## Assignment2 Transformations & Additional Primitives

#### Task

* [x] Implement the new rendering mode, normal visualization:

![](src/2_normal.png)

读取射线击中点的法向量，取法向量分量的绝对值作为rgb分量的值

```c++
Vec3f normal = h.getNormal();
float r = abs(normal.r()); 
float g = abs(normal.g()); 
float b = abs(normal.b()); 
image_normal->SetPixel(i, j, Vec3f(r, g, b));
```

* [x] Add diffuse shading

任务要求加入diffuse(依赖光线与法线向量)与ambient，物体在该点最终的颜色为diffuse color + ambient color:

* 漫反射颜色计算:

  ![diffuse](src/2_diffuse_color.png)

  * 光线在物体背面时n dot I 为负，这时我们diffuse设为0
  * 作业要求加入shade back选项，故当光线在物体背面，并要求shade back时，diffuse = - n dot I
  * 多束光线作用物体，diffuse为这些作用的总和

* 环境光计算：ambient color = ambient coefficient * material

```c++
if (group->intersect(r, h, camera->getTMin())){             //光线与物体相交
	assert(h.getMaterial() != NULL);
	Vec3f ambient_color = sceneParser.getAmbientLight();    //读取环境光
	/*caculate diffuse color*/
	Vec3f diffuse_color;                                    //(0, 0, 0)
	Vec3f hit_pos = r.pointAtParameter(h.getT());
	/*diffuse shading*/
	for (int i = 0; i < num_light; i++){                    //读取光线数据
  		sceneParser.getLight(i)->getIllumination(hit_pos, light_dir[i], light_color[i]);
    	float diffuse = light_dir[i].Dot3(h.getNormal());
    	if (diffuse < 0){ //点积为负，光在物体背面
        	if (shade_back) diffuse = -diffuse;             //渲染背面
        	else diffuse = 0;                               //不渲染背面，diffuse为0
    	}
    	diffuse_color += diffuse * light_color[i];
	}
	/*pixel color = diffuse + ambient + specular*/
	Vec3f pixel_color = (diffuse_color + ambient_color) * h.getMaterial()->getDiffuseColor();
	image->SetPixel(i, j, pixel_color);
}
```

* [x] **Perspective Camera**

![](src/2_perspective_camera.png)

* 通过up, direction, center三个向量可以确定一个透视投影相机

  * 三个向量必须标准化
  * up可能不与direction垂直，要利用horizontal向量使up和direction垂直

  ```c++
  PerspectiveCamera::PerspectiveCamera(Vec3f _center, Vec3f _direction, Vec3f _up, float _angle_radius):
          center(_center), direction(_direction), up(_up), angle_randians(_angle_radius){
      direction.Normalize();	//标准化方向向量
      Vec3f::Cross3(horizontal, direction, up);	//通过叉乘direction, up向量得horizontal向量
      Vec3f::Cross3(up, horizontal, direction);	//通过叉乘horizontal, direction向量使up与direction向量垂直
      up.Normalize();	//标准化up向量
      horizontal.Normalize();	//标准化horizontal向量
  }
  ```

* **透视投影相机如何打出射线？**

```c++
Ray PerspectiveCamera::generateRay(Vec2f point){
    Vec3f pos = center;
    Vec3f ray_dir = direction + up * (point.y()-0.5) * tan(angle_randians/2) *2 + 
    		horizontal * (point.x()-0.5) * tan(angle_randians/2) * 2;
    ray_dir.Normalize();
    return Ray(pos, ray_dir);
}
```

* [x] Plane

通过平面一点和平面法向量可以确定平面方程，我们可以这样定义平面：P dot n = d，故通过normal和d可以唯一确定一个平面

* 射线相交判断：
  * 射线方向向量与平面法向量垂直：射线与平面平行，不相交
  * 将Ray的方程带入平面，得到t
    * t >= tmin，相交;
    * t < tmin，不相交;

```c++
bool Plane::intersect(const Ray &r, Hit &h, float tmin){
    if (dir_nor.Dot3(normal) == 0) return false; //光线方向与平面平行
    float t = (d - r.getOrigin().Dot3(normal)) / (dir_nor.Dot3(normal));
    if (t < 0) return false; //在光线背面
    //与射线相交
    if (t < tmin) return false;
    if (h.getMaterial() != NULL && h.getT() < t) return true;
    h.set(t, material, normal, r);
    return true;
}
```

* [x] Triangle

射线与三角形求交判断：

* 方法1：利用重心坐标 Barycentric

  * 根据克拉默法则，若|A|=0，则方程无解，Ray不与三角形所在平面相交
  
    * 若t<tmin，Ray与三角形不相交
    * 若方程有解，且t>=tmin，0<α<1, 0<β<1, 0<γ<1，则Ray与三角形相交

* 方法2：先与三角形所在平面求交点，再判断交点是否在三角形内部

  * 如何判断三角形平面上的点是否在三角形内部？

    * 从这一点随机射出射线，与三角形有奇数个交点，则在内部，偶数个交点，在外部
      * 需要特判顶点

    * 通过重心坐标判断是否在三角形内部

* [x] **Derive a subclass `Transform` from `Object3D`**

对物体做变换后与Ray求交，可以通过对射线做变换实现

![](src/2_transform1.png)

---

![](src/2_transform2.png)

是否要标准化变换后的方向向量：

* Normalize: tOS ≠ tWS
* Don't Normalize: tOS = tWS

纠正变换后物体的法向量：

![](src/2_transform5.png)

---

![](src/2_transform6.png)

---

![](src/2_transform7.png)

---

![](src/2_transform8.png)

纠正变换后的法向量需要用到法矩阵：

![](src/2_normal_matrix.png)

#### Hint

MIT提供的Transform相关的代码有点反人类，习惯上对向量做变换用矩阵M左乘向量v：Mv。例如对v先后做变换M1, M2, M3的M矩阵应为：

```
M = M3 * M2 * M1;
```

但scene_parser.C中解析变换矩阵时使用如下代码：

```c++
matrix *= new_transform; //matrix = matrix * new_transform
```

然后Matrix.C中的Transform(Vec4f)代码如下：

```c++
void Matrix::Transform(Vec4f &v) const {
  Vec4f answer;
  for (int y=0; y<4; y++) {
    answer.data[y] = 0;
    for (int i=0; i<4; i++) {
      answer.data[y] += data[y][i] * v[i];
    }
  }
  v = answer;
}
```

相当与Mv，还是左乘，相当于列表中的变换顺序与我们想要的变换顺序是相反的

---

对Ray进行变换时，若单位化了direction向量，则需要改变Object3D的intersect函数，以Plane为例：

```c++
bool Plane::intersect(const Ray &r, Hit &h, float tmin){
    //标准化方向向量
    Vec3f dir_nor = r.getDirection();
    float dir_len = dir_nor.Length();	//记录变换后的方向向量长度
    dir_nor.Normalize();	//标准化方向向量

    if (dir_nor.Dot3(normal) == 0) return false; //光线方向与平面平行
    float t = (d - r.getOrigin().Dot3(normal)) / (dir_nor.Dot3(normal));
  	t /= dir_len;	/*******得到的t是在单位长度下的t，除以dir_len得到实际的t*******/
    if (t < 0) return false; //在光线背面
    //与射线相交
    if (t < tmin) return false;
    if (h.getMaterial() != NULL && h.getT() < t) return true;
    h.set(t, material, normal, r);
    return true;
}
```

---

* **变换到世界坐标的法向量必须标准化**

#### Result

* scene 7 shade back:

```
./raytracer -input src/scene2_07_sphere_triangles.txt -size 200 200 -output output2_07.tga -depth 9 11 depth2_07.tga -normals normals2_07.tga -shade_back
```

![](src/2_output2_07.png)

![](src/2_depth2_07.png)

* scene 7 don't shade back:

```
./raytracer -input src/scene2_07_sphere_triangles.txt -size 200 200 -output output2_07_no_back.tga
```

![](src/2_output2_07_no_back.png)


* bunny 1k triangles:

```
./raytracer -input src/scene2_10_bunny_1k.txt -size 200 200 -output output2_10.tga
```

![](src/2_output2_10.png)

* scene 13:

```
./raytracer -input src/scene2_13_rotated_squashed_sphere.txt -size 200 200 -output output2_13.tga -normals normals2_13.tga
```

![](src/2_output2_13.png)

![](src/2_normals2_13.png)

![](src/2_output2_15.png)

* **scene 16:**

**some bugs in green sphere and purple sphere?**

```
./raytracer -input src/scene2_16_t_scale.txt -size 200 200 -output output2_16.tga -depth 2 7 depth2_16.tga
```

![](src/2_output2_16.png)

---

## Assignment 3

* 所有GLUT call都应该放在create window之后，不然会segmentation fault
* GLUT应该先初始化

```c++
glutInit(&argc, argv);
```

* 绘制时，normal设置应该放在最前面

```c++
void Triangle::paint(){
    material->glSetMaterial();
    glBegin(GL_TRIANGLES);
        glNormal3f(normal.x(), normal.y(), normal.z()); //应当放在前面，设置之后绘制点的法向量
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
        glVertex3f(c.x(), c.y(), c.z());
    glEnd();
}
```

* glBegin(GL_QUADS)：顶点逆时针顺序counter-clockwise
* OpenGL x z坐标顺序和惯用坐标系相反，利用参数方程计算球坐标也应该交换x z坐标

## Assignment4

* Light 返回的light direction是与光线方向相反的
* 内全反射要反向法向量
* 折射入射和出射计算方法不同

## Assignment5

* A\[nx\]\[ny\]\[nz]中，LOC{ A\[i]\[j]\[k] }=A\[i * ny * nz  + j * nz + k]
