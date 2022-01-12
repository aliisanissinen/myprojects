This program is a group project and is part of the Software Design course, at Tampere University. <br />
The code has been made with Lari Lantonen (@lantonen), Joel Järvilehto and Arttu Turtiainen. <br />


**Dependencies:** <br />
Using QT 5.15.2 (MSVC 2019), minGW 8.1.x <br /> 
QT: quick, widgets, network, quick charts (.pro file includes) <br />
OpenSSL 1.1.1d or newer <br />

**Instructions:** <br />
This app is best scaled for full hd screen (1920x1080) <br />
As an environment we use the readily installed QT Creator in the remote desktop. <br />
The design documentation is under: Documentation/finalDoc. <br />
Open .pro file in QT Creator <br />
**Change run directory to powerweatherapp/**<br />
Compile the code<br />
To start using the app the user must choose start and end dates.<br /> Then depending on the datatype user can either type a city (for weather) or not (for power).<br /> User then proceeds to choose data type from checkboxes.<br /> User then fetches the data by clicking draw graph for desired data type.<br /> Multiplotting powerdata can be done by first plotting one data type and then proceeding to pick another checkbox and drawing the data by clicking draw extra power.<br /> User has the ability to zoom into the graph by clicking mouse left and dragging a square on the area user wishes to zoom into. <br /> User can unzoom the graph by double clicking left mouse button on the graph. <br /> User can clear all graphs by clicking on clear all graphs.<br /> User has the option to save the data by save buttons either as .txt or .png files.<br /> User can then import the data into the app whenever needed.<br /> Under the draw and clear button user can see instructions about the different stages the program is in or what the user needs to change in order to get the data plotted.
