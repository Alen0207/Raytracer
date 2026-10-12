# RayTracer

A raytracer project written in C++20 that renders scenes described in a `.cfg` file and outputs a PPM image to stdout.

## Dependencies

- CMake 3.10+
- C++20 compiler (g++ or clang++)
- [libconfig++](https://hyperrealm.github.io/libconfig/) — scene file parsing

```bash
# Ubuntu / Debian
sudo apt install libconfig++-dev
```

## Build

```bash
mkdir build && cd build
cmake ..
make
```

The binary is output to the project root as `raytracer`.

```bash
# Type from the project root
mkdir -p build && cd build && cmake .. && make && cd ..
```

## Usage

```bash
./raytracer <SCENE_FILE> > output.ppm
```
SCENE_FILE - .cfg file

The renderer writes a PPM image to stdout. Redirect it to a file and open with any image viewer that supports PPM.

```bash
display output.ppm
```

## Coordinate System

The camera always looks in the **+Y direction** when rotation is `(0, 0, 0)`.

| Axis | Role |
|------|------|
| +Y | depth — forward into the scene |
| +X | right on screen |
| +Z | up on screen |

All primitives must have a **higher Y value than the camera** to be visible.

## Scene Configuration

Scenes are described in [libconfig](https://hyperrealm.github.io/libconfig/) format.

### Full example

```
camera:
{
  resolution = { width = 800; height = 450; };
  position   = { x = 0.0; y = 0.0; z = 0.0; };
  rotation   = { x = 0.0; y = 0.0; z = 0.0; };
  fieldOfView = 72.0;
};

primitives:
{
  spheres = (
    { x = 0.0; y = 5.0; z = 0.0; r = 1.0; color = { r = 255; g = 64;  b = 64;  } },
    { x = 2.0; y = 6.0; z = 0.0; r = 1.0; color = { r = 64;  g = 255; b = 64;  } },
    { x = -2.0; y = 7.0; z = 1.0; r = 1.0; color = { r = 64;  g = 64;  b = 255; } }
  );
  planes = (
    { axis = "Y"; position = 15.0; color = { r = 180; g = 180; b = 180; } }
  );
};

lights:
{
  ambient = 0.3;
  diffuse = 0.6;
  point = (
    { x = 0.0; y = -5.0; z = 10.0; }
  );
};
```

### Camera

| Field | Type | Description |
|-------|------|-------------|
| `resolution.width` | float | Image width in pixels |
| `resolution.height` | float | Image height in pixels |
| `position.x/y/z` | float | Camera position in world space |
| `rotation.x/y/z` | float | Camera rotation in degrees. `x` = pitch, `y` = yaw |
| `fieldOfView` | float | Horizontal field of view in degrees |

**Rotation notes:**
- `rotation = { x=0; y=0; z=0; }` → looks straight in +Y
- `rotation.y` rotates left/right (yaw)
- `rotation.x` tilts up/down (pitch). Positive pitch tilts upward (+Z)

### Primitives

Primitive lists use libconfig array syntax `( ... )`. Items are groups `{ }` separated by commas.

#### Spheres

```
spheres = (
  { x = 0.0; y = 5.0; z = 0.0; r = 1.5; color = { r = 255; g = 0; b = 0; } }
);
```

| Field | Description |
|-------|-------------|
| `x`, `y`, `z` | Center position |
| `r` | Radius |
| `color.r/g/b` | Color in 0–255 range |

#### Planes

Axis-aligned infinite planes. `axis` sets which axis the plane is perpendicular to and `position` sets its coordinate on that axis.

```
planes = (
  { axis = "Y"; position = 0.0; color = { r = 200; g = 200; b = 200; } }
);
```

| Field | Description |
|-------|-------------|
| `axis` | `"X"`, `"Y"`, or `"Z"` |
| `position` | Coordinate along that axis |
| `color.r/g/b` | Color in 0 - 255 range |

**Plane placement guide:**

| Goal | Config |
|------|--------|
| Floor (below scene) | `axis = "Z"; position = -2.0` |
| Back wall | `axis = "Y"; position = 20.0` |
| Left wall | `axis = "X"; position = -10.0` |

### Lights

```
lights:
{
  ambient = 0.3;
  diffuse = 0.7;
  point = (
    { x = 0.0; y = -5.0; z = 10.0; }
  );
};
```

| Field | Description |
|-------|-------------|
| `ambient` | Ambient light multiplier (0.0 - 1.0). Minimum brightness on all surfaces |
| `diffuse` | Diffuse multiplier |
| `point` | List of point light positions |

Multiple point lights are supported:

```
point = (
  { x = 5.0; y = -10.0; z = 8.0; },
  { x = -5.0; y = 0.0; z = 4.0; }
);
```
