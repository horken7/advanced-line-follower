# advanced-line-follower
## Line following Zumo robot for Arduino

Automated Guided Vehicles (AGV) are unmanned vehicles used widely within the industry to perform monotonous tasks including, but not limited to, transportation of goods. These vehicles are commonly operated by a computer, either with or without guidance. A modern technique for autonomous guidance is to follow a coloured line on the floor. Such an AGV robot would require a minimal amount of sensors for efficient traversal. In a warehouse this can be used for cost efficient transportation of goods in a known environment.

The main aim of this project is to investigate how to efficiently implement such a system. This project models a simple warehouse environment using a small Zumo robot, controlled using an Arduino Uno. The intended outcomes are to investigate how to implement a simple line following control function in the Zumo, such that it can traverse in a model of a warehouse environment. Investigation of how the Zumo can efficiently find it’s way between two points in the warehouse model and localise in a previously unknown environment will also be underetaken. Furthermore; stability, reliability and speed limitations will be investigated.

The results show that it is possible to traverse a modelled warehouse environment using the Zumo robot, model the environment using data structures and efficiently find a path between two points in the environment. There is still room for improvement in the stability and reliability testing in order to help achieve the most efficient traversal. Although the hardware somewhat limits efficient implementation of some processes and gives inconsistent inputs and outputs, the principles suggested in this project could be applied to larger scale applications.
F
uture areas of interest are to optimise stability and reliability, to find most efficient traversal, and application of these for larger scale systems. Also rethinking warehouse layouts and how to efficiently represent them, as well as considering systems with more then one AGV present.

The robot used in this model is Pololu Zumo robot for Arduino https://www.pololu.com/product/2506

The Arduino sketch use the Pololu Zumo Shield Libraries, available at https://github.com/pololu/zumo-shield

The result of this project is described in the report, found complete with latex files in /LatexReport/.

The files used to program the Arduino can be found under /AdvancedLineFollower/, where the sketch AdvancedLineFollower.ino needs to be opened with the Arduino IDE (https://www.arduino.cc/en/main/software). The sketch by default run a navigator function that calculates the shortest path between given start and goal nodes then traverse between those points in a given network, printing clarifying behaviour to serial. The file /AdvancedLineFollowerFunctions.cpp/ contains the main driver functions to communicate with the hardware. By removing the serial prints in the navigator function, and uncommenting printSensorReadingsToSerial(sensors, position, millis_curr) in the follow_segment function, sensor data will be printed to serial, enabling analysis described in next section. The graph files contain the data structures used for mapping and navigation. The pathPlanning files contain the modified Dijkstra's algoritm applied to the graph format for calculating a MST for path finding.

Inside /AnalyseSerial/ the script readSerial.py can be used to recieve serial readings from the Arduino on appropriate connected port, i.e. the USB. The script will output a .csv file, that can be used by the analyseSerial.m script in Matlab to plot stability behaviour (provided the stability behaviour is what is being printed to serial). Example .csv readings can be found in /AnalyseSerial/readings/, and example stability plots can be found in /AnalyseSerial/images/.
