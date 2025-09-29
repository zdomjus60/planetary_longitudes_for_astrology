# Planetary Longitudes for Astrology

This project is a C++ command-line tool that calculates the **tropical** geocentric ecliptic longitudes of the planets for a given date and time.

## Core Functionality

The program takes a single date-time argument from the command line and computes the celestial longitude for the Sun, Moon, and all planets in the solar system.

### Tropical Geocentric Ecliptic Longitudes

The calculated values represent the **tropical geocentric ecliptic longitudes** of the celestial bodies. This is the angular position of a planet on the ecliptic (the plane of Earth's orbit) as seen from the center of the Earth.

The longitudes are *tropical*, meaning they are measured from the vernal equinox (the point where the Sun crosses the celestial equator moving north), which is the starting point of the tropical zodiac.

### Date/Time Input

The input date must be provided in the **ISO 8601 format**: `YYYY-MM-DDTHH:MM:SS`. This standard is used to ensure that the date and time are interpreted unambiguously.

Example:
```bash
./calculator_static 2025-07-01T19:19:00
```

## Astronomical Library

This project relies on the **AA+ (Astronomical Algorithms Plus)** library, a freeware C++ framework developed by **PJ Naughter**. The library provides a comprehensive implementation of the algorithms presented in Jean Meeus's seminal book, "Astronomical Algorithms".

The source code for the AA+ library is included in the `aaplus/` directory.

## Building the Project

This project requires a C++ compiler (like g++) and `make` (though compilation is handled by shell scripts).

### Prerequisites

*   **C++ Compiler:** `g++` (version supporting C++17 or newer)
*   **Git:** For cloning the repository.

The AA+ library source code is already included in the `aaplus/` directory, so no separate installation is required for it.

### Compilation

The repository includes two shell scripts to compile the project:

#### Static Build (`compile_static.sh`)

To create a standalone executable:

```bash
./compile_static.sh
```
This script compiles the AA+ library into a static archive (`libaastro.a`) and then links it directly into the final executable (`calculator_static`). The result is a single, self-contained executable with no external library dependencies.

#### Dynamic Build (`compile_dynamic.sh`)

To create an executable that links against a shared library:

```bash
./compile_dynamic.sh
```
This script compiles the AA+ library into a shared object (`libaastro.so`) and links the main executable (`calculator_dynamic`) against it. This approach results in a smaller executable, but it requires the `libaastro.so` file to be present in the same directory (or in the system's library path) at runtime. The `-rpath` linker option is used to ensure the executable can find the library in its own directory.

### Running the Executables

After successful compilation, you can run the executables:

```bash
./calculator_static 2025-07-01T19:19:00
./calculator_dynamic 2025-07-01T19:19:00
```
