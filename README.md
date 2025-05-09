# MCU_OscilloGen

## Getting Started

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