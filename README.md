Delaunay Triangulation
===================

<i class="icon-info-circled"> Introduction
-------------
This is my personal project of Computational Geometry at University of Cagliari, Computer Science.
The goal of this project was to develop a 2D interactive and incremental Delaunay Triangulation Algorithm.
An optional feature was drawing the Voronoi complementar diagram of a given triangulation.

The Base Project (provided by @Alessandro Muntoni) is organized in modules. There are two main modules: the “common module” and the “viewer module”. Every module is organized inside a .pri file which is included inside the main .pro file of the project. I have not edit of modify the folders or the files inside the folders associated to the modules. All my files and folders are organized as subfolder "Andrea" in the main folder of the project.

Main Features
-------


- Efficient way to find where in what triangle lie.
- A point can be totaly inside on a triangle or can lie in one of three edges. 
- A point can be insert only once. Instead of using the vector of points to check if point already exist, I use the Dag in order to save time and cpu clock.
- Iterative Dag navigation instead of recursive way to avoid some crash and segmentation faults.


 <i class="icon-user-md"> Delaunay Triangulation
-------------
In mathematics and computational geometry, a Delaunay triangulation for a given set P of discrete points in a plane is a triangulation DT(P) such that no point in P is inside the circumcircle of any triangle in DT(P). Delaunay triangulations maximize the minimum angle of all the angles of the triangles in the triangulation; they tend to avoid sliver triangles. The triangulation is named after Boris Delaunay for his work on this topic from 1934.
For a set of points on the same line there is no Delaunay triangulation (the notion of triangulation is degenerate for this case). For four or more points on the same circle (e.g., the vertices of a rectangle) the Delaunay triangulation is not unique: each of the two possible triangulations that split the quadrangle into two triangles satisfies the "Delaunay condition", i.e., the requirement that the circumcircles of all triangles have empty interiors.
By considering circumscribed spheres, the notion of Delaunay triangulation extends to three and higher dimensions. Generalizations are possible to metrics other than Euclidean distance. However, in these cases a Delaunay triangulation is not guaranteed to exist or be unique.
[Wikipedia: Delaunay Triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation)


<i class="icon-download"></i> Installation
-------------

This project was developed with Ubuntu 17.04.  In order to install all dependencies and libraries run the following command:

> **From your terminal:**

>  sudo apt-get install qtcreator qt5-default 
>  sudo apt-get install libboost-all-dev libcgal-dev libgmp-dev libqglviewer-dev 
>  sudo apt-get install git doxygen libeigen3-dev 
>
> sudo apt-get install libeigen3-dev
> sudo apt-get install git doxygen
> sudo apt-get install libboost-all-dev 
> sudo apt-get install libqglviewer-dev-qt5

It is also possible to compile and run on MacOs and Windows but I will not give instructions to do it.

<i class="icon-folder"></i> Folder structure
-------------

My personal module, folder called "Andrea",  is structured as follow: 

> **Andrea**
> ___
> - **Headers**
>  - DataStructures
>    -- dagNode.h
>    -- triangle.h
>  - Drawable
>  -- drawabledelaunaytriangulation.h
>  -- drawablevoronoidiagram.h
>  - Static
>   -- adjacencies.h
>   -- dag.h
>
> delaunaytriangulationcore.h
>
> - **Classes**
>  - DataStructures
>    -- dagNode.cpp
>    -- triangle.cpp
>  - Drawable
>  -- drawabledelaunaytriangulation.cpp
>  -- drawablevoronoidiagram.cpp
>  - Static
>   -- adjacencies.cpp
>   -- dag.cpp
>
> delaunaytriangulationcore.cpp

Inside **DataStructures** folder there are the classes that manage the main definition of the data structures of the all project as Triangles and Dag Nodes. A triangle has a pointer to is corrispective dag node and vice versa.

**Drawable** folder contains to classes that implements Drawable Interface. Their task is to draw points and lines inside the canvas.

**Static** folder contain two complete static class that manage the Dag navigation and the triangles adjacencies (find adjacencies, set pointers, override pointers etc.).

At last *delaunaytriangulationcore* class manage all previus class and data structures. It take from the canvas one by one the clicked point, or a entire vector from a file, and perform a delaunaytriangulation legalizing edge and performing an edge flip when necessary.

___

<i class="icon-fire"></i>Benchmark
-------------
At `/Extra/input_files/` there are a lot of files to test the triangulation efficienty.
Below you will find the results I obtained using my PC (Dell XPS 15 9550, with Intel i7 6700HQ Skylake @ 2.60GHz 

> - 100 Points: 
> - 500 Points:
> - 1.000 Points:
> - 1.500 Points:
> - 2.000 Points:
> - 2.500 Points:
> - 3.000 Points:
> - 3.500 Points:
> - 4.000 Points:
> - 4.500 Points:
> - 5.000 Points:
> - 50.000 Points:
> - 100.000 Points:
> - 200.000 Points: 

<i class="icon-desktop"></i> HIgh DPI monitor support
-------------
I'm working on Dell XPS 15 9550 with 4k monitor. To be able to work smoothly I had to make some fixes to the base project that was provided to us.
In the main.cpp file I've add at 24 & 25 lines:

    qputenv("QT_SCREEN_SCALE_FACTORS",QByteArray("1"));
    QApplication app(argc, argv);

But it work good with my QT version, using different version of QT it could be necessary to change with: 

	qputenv("QT_DEVICE_PIXEL_RATIO", "2");

I didn't test this project with other pc's or other system so for other fix or workaround please check the official forum at: [QT Forum](https://forum.qt.io/).




