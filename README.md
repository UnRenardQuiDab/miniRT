# MiniRT

MiniRT is a project developed in C as part of the 42 common core. This project aims to display 3D objects using the ray tracing method, a rendering technique that simulates the propagation of light in a scene to create realistic images.

## Table of Contents

- Features
- Usage
- Contributors

## Features

- **3D Rendering**: Generation of 3D images using ray tracing.
- **Basic Objects**: Support for spheres, planes, cylinders, and other basic geometric shapes.
- **Light Management**: Simulation of different light sources (ambient, directional, point).
- **Materials**: Handling of object colors and reflections.
- **Multithreading**: Improved performance by utilizing multiple CPU cores.
- **Camera Movement**: Ability to move and adjust the camera position within the scene.

### Prerequisites

- A C compiler (GCC recommended)
- `make` installed on your machine

### Compilation

1. Clone the project repository:
```bash
git clone git@github.com:UnRenardQuiDab/miniRT.git --recursive
cd miniRT
```

2. Compile the project:
```bash
make
```

## Usage

To run MiniRT and display a scene, execute the following command:
```bash
./miniRT scenes/reflect.rt
```

## Contributors

- [**lcottet**](https://profile.intra.42.fr/users/lcottet) - Developer
- [**bwisniew**](https://profile.intra.42.fr/users/bwisniew) - Developer
