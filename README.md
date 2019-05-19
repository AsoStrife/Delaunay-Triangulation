Delaunay Triangulation
===================

Introduction
-------------
This is my personal project of Computational Geometry at University of Cagliari, Computer Science.
The goal of this project was to develop a 2D interactive and incremental Delaunay Triangulation Algorithm.
An optional feature was drawing the Voronoi complementary diagram of a given triangulation.

The Base Project (provided by @Alessandro Muntoni) is organized in modules. There are two main modules: the “common module” and the “viewer module”. Every module is organized inside a .pri file which is included inside the main .pro file of the project. I didn't edit or modify the folders and the files inside the folders associated to the modules. All my files and folders are organized in a subfolder "Andrea" in the main folder of the project.

For more detail about the base project you can check in `Extra/base_project_info.pdf`.

Delaunay Triangulation
-------------
In mathematics and computational geometry, a Delaunay triangulation for a given set P of discrete points in a plane is a triangulation DT(P) such that no point in P is inside the circumcircle of any triangle in DT(P). Delaunay triangulations maximize the minimum angle of all the angles of the triangles in the triangulation; they tend to avoid sliver triangles. The triangulation is named after Boris Delaunay for his work on this topic from 1934.
For a set of points on the same line there is no Delaunay triangulation (the notion of triangulation is degenerate for this case). For four or more points on the same circle (e.g., the vertices of a rectangle) the Delaunay triangulation is not unique: each of the two possible triangulations that split the quadrangle into two triangles satisfies the "Delaunay condition", i.e., the requirement that the circumcircles of all triangles have empty interiors.
By considering circumscribed spheres, the notion of Delaunay triangulation extends to three and higher dimensions. Generalizations are possible to metrics other than Euclidean distance. However, in these cases a Delaunay triangulation is not guaranteed to exist or be unique.
[Wikipedia: Delaunay Triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation)

Main Features about My Delaunay Triangulation Algorithm
-------
- Efficient way to find in which triangle a point lies.
- A point can be totaly inside on a triangle or can lie in one of three edges. 
- A point can be insert only once. Instead of using the vector of points to check if point already exist, I use the Dag, in order to save time and CPU clock.
- Iterative Dag navigation instead of recursive way to avoid some crash and segmentation faults.
- Access to the adjacent triangles and the corresponding Dag node in O(1)

For more detail about the  implementation check the code! It's all documented with the **Doxygen Standard**.

Installation
-------------

This project was developed with Ubuntu 17.04.  In order to install all dependencies and libraries run the following commands:

**From your terminal:**

```shell
sudo apt-get install qtcreator qt5-default 
sudo apt-get install libboost-all-dev libcgal-dev libgmp-dev libqglviewer-dev 
sudo apt-get install git doxygen libeigen3-dev 
    
sudo apt-get install libeigen3-dev
sudo apt-get install git doxygen
sudo apt-get install libboost-all-dev
sudo apt-get install libqglviewer-dev-qt5
```

**Cannot find -libQGLViewer-qt5 problem**

If you try to compile the solution you might receive the following message from the compiler:

```c++
Cannot find -libQGLViewer-qt5
Collect2:error: Id returned 1 exit status
```

To solve this problem check inside the directory `/usr/lib/x86_64-linux-gnu` if exist a file named: `libQGLViewer.so`. If doens't exist (very likely, as the project does not compile) check inside the folder all `.so` files of `libqglviewer`. If you find that file, change inside`viewver.pri` file at line 14 `LIBS += -lQGLViewer` with `LIBS += -libQGLViewer-qt5` (if file name is libQGLViewer-qt5.so)

------

It is also possible to compile and run the project on MacOs and Windows but I will not give instructions to do it.

Folder structure
-------------

My personal module, folder called "Andrea",  is structured as follow: 

**Andrea**
___
 **Headers**
  - **DataStructures**
    - dagNode.h
    - triangle.h
  - **Drawable**
      - drawabledelaunaytriangulation.h
      - drawablevoronoidiagram.h
  - **Static**
       - adjacencies.h
       - dag.h
- delaunaytriangulationcore.h

**Classes**
  - **DataStructures**
    - dagNode.cpp
    - triangle.cpp
  - **Drawable**
      - drawabledelaunaytriangulation.cpp
      - drawablevoronoidiagram.cpp
  - **Static**
       - adjacencies.cpp
       - dag.cpp
- delaunaytriangulationcore.cpp

___
Inside **DataStructures** folder there are the classes that manage the main definition of the data structures of the all project as Triangles and Dag Nodes. A triangle has a pointer to is corrispective dag node and vice versa.

**Drawable** folder contains two classes that implements Drawable Interface. Their task is to draw points and lines inside the canvas.

**Static** folder contains two complete static class that manage the dag navigation and the triangles adjacencies (find adjacencies, set pointers, override pointers etc.).

At last *delaunaytriangulationcore* class manage all previous classes and data structures. It take from the canvas one by one the clicked point, or a entire vector from a file, and perform a delaunaytriangulation legalizing edge and performing an edge flip when necessary.

___

Benchmark
-------------
At `/Extra/input_files/` there are a lot of files to test the triangulation efficienty.
Below you will find the results I obtained using my PC (Dell XPS 15 9550, with Intel i7 6700HQ Skylake @ 2.60GHz) 

> - 100 Points:  ≈ 0,00063 seconds
> - 500 Points: ≈ 0,0032 seconds
> - 1.000 Points: ≈ 0,0114 seconds
> - 1.500 Points: ≈ 0,0120 seconds
> - 2.000 Points: ≈ 0,0200 seconds
> - 2.500 Points: ≈ 0,0220 seconds
> - 3.000 Points: ≈ 0.0259 seconds
> - 3.500 Points: ≈ 0,0336 seconds
> - 4.000 Points: ≈ 0,037 seconds
> - 4.500 Points: ≈ 0,043 seconds
> - 5.000 Points: ≈ 0,050 seconds
> - 50.000 Points: ≈ 0,55 seconds
> - 100.000 Points: ≈ 1,2 seconds
> - 200.000 Points: ≈ 2,4 seconds
> - 300.000 Points ≈ 3,90 seconds

My algorithm does not allow the insertion of two equal points (with the same coordinates), so if we try to insert the same input file twice, the triangulation will be faster. For example if we add twice the 200k points file, the second time the triangulation will take only ≈ 1.20 seconds.

Voronoi Diagram
-------------

The Delaunay triangulation of a discrete point set **P** in general position corresponds to the dual graph of the Voronoi diagram for **P**.  
The bonus point of the project was to draw the dual graph of the delaunay triangulation: Voronoi Diagram, but without any data structure. 
To perform the Voronoi Diagram, I took all Triangles of triangulation, I've calculated the circumcentre of that triangle and connected it with the circumcentre of the three adjacent triangles.

Check triangulation problem
-------------
To be sure my algorithm works fine, there's a function (linked to the *"Check triangulation"* button) to check if the triangulation is a valid triangulation.
The function 

```c++
bool isDeulaunayTriangulation(const std::vector<Point2Dd>& points, const Array2D<unsigned int>& triangles)
```


has been provided by @Alessandro Muntoni and it checks if the triangulation is a Delaunay triangulation with a brute force approach in O(n^2).  With a small triangulation there's no problem with that, but using a big triangulation (like 100k, 200k points) it's probably the program freeze or crash. 

HIgh DPI monitor support
-------------
I'm working on Dell XPS 15 9550 with 4k monitor. To be able to work smoothly I had to make some fixes to the base project that was provided to us.
In the main.cpp file I've add at 24 & 25 lines:

```c++
qputenv("QT_SCREEN_SCALE_FACTORS",QByteArray("1"));
QApplication app(argc, argv);
```

But it works good with my QT version, using different version of QT it could be necessary to change with: 

```c++
qputenv("QT_DEVICE_PIXEL_RATIO", "2");
```

I didn't test this project with other pc's or other system so for other fix or workaround please check the official forum at: [QT Forum](https://forum.qt.io/).

Screenshots
-------------
This is the result with 100 points files.
![Delaunay 100 Points](https://i.imgur.com/mUWwlLs.png)

This is the corresponding Voronoi Graph.

![Voronoi Graph](http://i.imgur.com/Cr6TyvH.png%20%22Voronoi%20100%20Points)

Here are the two graphs together.

![Delaunay Voronoi 100 Points](http://i.imgur.com/Nbpxpox.png)


