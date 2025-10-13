# MCU_OscilloGen

**MCU_OscilloGen** is a modular real time RTOS firmware project designed to run on microcontrollers, providing oscillograph and signal generation capabilities. The repository is structured to facilitate robust development, testing, and deployment. It comprises three main components:

- **Project/** – Core source code (C/C++)
- **Bootloader/** – Bootloader implementation (C)
- **UnitTests/** – Automated unit tests (Google Test, C++)

---

## Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Features](#features)
- [Getting Started](#getting-started)
- [Build & Flash Instructions](#build--flash-instructions)
- [Running Unit Tests](#running-unit-tests)

---

## Overview

MCU_OscilloGen is tailored for embedded systems, enabling real-time signal generation and waveform acquisition. The project emphasizes code quality and maintainability, leveraging modern C++ for application logic, a C-based bootloader for reliable firmware upgrades, and a comprehensive suite of unit tests.

---

## Repository Structure

```plaintext
MCU_OscilloGen/
├── project/        # Main application (C/C++)
├── Bootloader/     # Bootloader (C)
├── UnitTests/      # Google Test unit tests (C++)
├── docs/           # Documentation (DataSheet and RM)
├── .github/        # GitHub workflows and actions
└── README.md       # Project overview
```

---

## Features

- **Modular C++ Firmware**: Clean, extensible codebase for MCU signal generation and oscillograph.
- **Robust Bootloader**: Secure and efficient bootloader for firmware updates.
- **Automated Unit Testing**: Extensive test coverage with Google Test to ensure reliability.
- **CI Integration**: Ready for continuous integration and automated builds via GitHub Actions.
- **Documentation**: Well-documented code and usage instructions.

---

## Getting Started

### Prerequisites

- **Toolchain**: ARM GCC or your MCU's specific compiler.
- **CMake**: For cross-platform build management.
- **Google Test**: For running unit tests.
- **Hardware**: Supported microcontroller (see `docs/` for compatibility).

### Clone the Repository

```sh
git clone https://github.com/ShayanEram/MCU_OscilloGen.git
cd MCU_OscilloGen
```

---

## Build & Flash Instructions

1. Build the Bootloader
2. Build the Main Project
3. Flash to MCU

Use your preferred flashing tool, e.g., `st-flash`, `openocd`, or vendor-specific utilities:

## Running Unit Tests

```sh
cd UnitTests
mkdir build && cd build
cmake ..
make
./runUnitTests
```

Unit tests are designed using [Google Test](https://github.com/google/googletest). Results are output to the terminal.


## TroubleShoot
### Create the Project
1. Install STM32IDE using your account.
2. Open STM32IDE.

#### IF HAVING CONNECTION PROBLEMS:
3. On the top bar, select: Window -> Preferences -> (search) Network Connections and configure network type to manual -> Apply.
4. Window -> Preferences -> STM32CubeIDE -> Firmware Updater and click on "Check Connection".
5. Ensure the connection status is green.
6. Help -> Configuration Tool -> Manage Embedded Software Packages -> STM32H7 1.12.1 -> Install.
7. Sign in with your account and download the necessary packages.
#### END PROBLEM
8. Create a new STM32 project -> Choose STM32H7 (NUCLEO-H723ZG) -> Target Language: C++.
9. Leave the rest as default.
10. Finish.

### Create the Project
1. Add the source and header files in Core++.
2. Project -> C/C++ General -> Paths and Symbols: <br>
    a. Source Location -> Add Folder -> ``Core++`` <br>
    b. Includes -> GNU C/C++ -> Add ``Core++/Inc`` -> apply and Close <br>
3. Apply and Close
4. IF NOT PRESENT: Project -> C/C++ Build -> Settings -> GCC/G++ Compiler -> Add ../Core++/Inc

## Run the project
1. Click build
2. Click run
