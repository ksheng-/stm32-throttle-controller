# Embedded Coder Project Generation
Embedded Coder will generate project files inside the current working directory of Matlab.

As far as I can tell, there are two parts of this opaque process: C/C++ model generation and STM32 project generation.

Embedded Coder first generates C or C++ code from the Simulink model into a `<Model name>_stm32` directory under the current Matlab directory. A `slprj/` directory is also created.

This results in several .c/.h files that implement ONLY the Simulink model, based on the algorithmic and STM32-MAT/TARGET blocks.

There is a `<Model name>.c/.h` pair that implements the algorithm, as well `<Model name>_<Peripheral>.c/.h` pairs that initialize the 'high' level data structures for the control system.

Also generated is a skeletal `main.c/.h` that that implements the main loop only, as well as several Matlab build files which we don't (?) seem to need.

Embedded Coder then independently runs the STM32CubeMX code generator to generate 'low' level code that integrates with the STM32 HAL to initialize the clock and peripherals based on the .ioc configuration.

The STM32CubeMX tool should open, hit the project generation button.

This results in an STM32 project structure based on the configured toolchain. In our case, we'll choose the SW4STM32 toolchain, since that's basically identical to the GNU MCU Eclipse toolchain we're actually using (Eclipse, GCC, GDB, make).

STM32CubeMX generates the SW4STM32 project with the MCU properly configured into the `Src/`, `Inc/`, and `Drivers/` directories.
`Drivers/` contains the HAL and ARM drivers for the project. In our case, we won't need these since GNU MCU Eclipse already includes these when creating the project.

`Src/` and `Inc/` contain a `main.c/.h` and a few other necessary HAL files.
`main.c/.h` contains the MCU initialization code, as well as the previously generated Simulink code, mashed in through STM32CubeMX's 'user code' functionality.

The other previously generated `<Model name><_<Peripheral>>.c/.h` pairs needed for the main loop to run are dumped into the `<Model name>` directory (NOT `<Model name>_stm32`).


## TLDR
Link the peripheral code from <Model name>
Link the main and HAL setup files from Src and Inc

Replace RT_MODEL_<Model name> with RT_MODEL
If you encounter undefined macros in the HAL msp file, include main.h

Remove any of the example driver files provided by GNU ARM Eclipse from the build if they conflict.

This can also be automated using eclipse linked resources and include paths, but things get really hairy with linking the includes in the right place, since everything is outside the workspace.

## Possible Issues
There were some issues with the ST provided target compiler and Matlab R2017a.
* See https://community.st.com/thread/41709-many-problems-with-stm32-mat

Theres a setting somewhere that causes STM32CubeMX  to launch and do nothing, closing the program allows the build to continue.
