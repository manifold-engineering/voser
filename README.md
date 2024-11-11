# VOSER
**Vojtův otevřený simulátor exteriérových reproduktorů** / 
**Vojta's open source exterior speaker simulator**

Voser is menat to be simple open-source application designed to simulate loudspeaker setups.

## User Guide
For instructions on how to use Voser, please see the [docs folder](./docs) in this repository.

## Installation
A pre-built version of Voser for Windows (64-bit) is available. You can download it as a `.zip` file from the [GitHub releases page](https://github.com/manifold-engineering/voser/releases). Just unzip, then run voser.exe.

## Building Voser
Voser is currently built with **C++11** and **Qt 6.4**, using **CMake**. 


To build Voser:
1. Clone this repository.
2. Open the project in Qt Creator (or your preferred IDE).
3. Use the provided `CMakeLists.txt` file to set up and compile the project.


If you are not interested in Voser as whole user GUI program but rather in calculations only, take a look at src/solver.cpp (and include/solver.h).
These files could be compiled with basic C++ compiler without Qt framework. Feel free to use the solver in your own code.


## TODO / Known issues
 - magnitude bar keeps autoscaling back
 - add save/load "voser project / list of sources"
 - virtual measurement microphones (plot magnitude/phase response for one point)
 - add basic parameters settings
   - sound velocity (now hardcoded at 330 m/s)
   - base amplitude (now hardcoded 90 dB @ 1m)
   - downsampling factor (now hardcoded 2)

Voser will likely never be able to compute sound wave reflections. Maybe there will be successor to voser (called "Vojtův otevřený modelovač reproduktorů dovnitř" / Vomrd) with such feature.

## Acknowledgments
Voser uses the [QCustomPlot](https://www.qcustomplot.com/) library for data visualization.

## Contributing
Contributions are welcome! Open issues, submit pull request or send me a message.

## License
This project is licensed under the GPLv3 License. See the [LICENSE](./LICENSE) file for details.
