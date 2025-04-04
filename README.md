# Ray-Tracing-Engine
Ray Tracing engine with basic materials

This repository includes the code and images of a basic Ray Tracing Engine made form scratch. This project is being developed by following the book series [Ray Tracing in One Weekend](https://raytracing.github.io/).

![Bouncing balls image - sample image](https://github.com/Satoniou/Ray-Tracing-Engine/blob/main/Images/bouncing_balls.png)

The engine takes a scene defined in `raytracerNextWeek.cpp` and passes the color values for each pixel into a `.ppm` file.

# Build and Run the program
This project uses CMake. To build, navigate to the root of the project directory and run the following command:
```
$ cmake -B build
$ cmake --build build --config release
```
This creates the Release version of every executable. To generate the image file from the executable, run:
```
$ build/Release/raytracerNextWeek.exe > image.ppm
```
This creates (or overwrites) an `image.ppm` file. To view this as an image, you can use an online ppm viewer or a program that supports `.ppm` files (such as Gimp).

# Objects
The engine currently supports only spheres. Other basic objects, such as rectangles and parallelepipeds, will be added soon.

![Picture of four spheres](https://github.com/Satoniou/Ray-Tracing-Engine/blob/main/Images/four_spheres.png)

# Materials
There are currently three different material types: 
- Lambertian: used for solid colors; no reflection/refraction
- Metal: used for metal-like objects; reflective surface
- Dielectric: used for transparent objects with refraction index different from ambient; refractive surface (e.g. glass)

![Materials Sample](https://github.com/Satoniou/Ray-Tracing-Engine/blob/main/Images/materials_sample_spheres.png)

To create a new material object, use `std::make_shared` with type `lambertian`, `metal` or `dielectric`, and with the appropriate parameters.

# Textures
There are currently 2 different textures that the engine can work with:
- Solid Color
- Checkered

![Checkered Spheres](https://github.com/Satoniou/Ray-Tracing-Engine/blob/main/Images/checkered_spheres.png)

There is currently work being done to display the checkered pattern as a texture map, as it is currently dealt with as a spacial texture, and thus exhibits the behaviour that can be seen in the picture.

# Camera
The camera object currently has no movement. The following are customizable attributes of the camera:
- Field of view
- Image width and height
- Aspect ratio
- Number of samples per pixel
- Max depth of searching for each sample
- Position and rotation
- Relative orientation
