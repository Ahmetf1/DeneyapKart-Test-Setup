# DeneyapKart-Test-Setup
A test setup for testing deneyap kart input output pins and sensor written in C and Labview. The user can select which tests to perform, see which tests are completed succesfully and which ones have encountered with errors.  

## How to use ?
- First upload deneyap_tester.ino to deneyap kart.
- Turn on the reset switch and run the VI, this will reset all values to default.
- Configure port setting from port settings menu, then choose parameters for the test.
- Run the VI, then select the tests desired to be performed. After the selection click "Run Selected Test" button.
- Follow the instructions on the instructions box.
- The green LEDs show which tests are completed and Red LEDs show the tests resulted with errors.
- In Gyro and Accelometer tests graphs appear on the side of the screen.
- At the end of the desired tests, a path to save a report will be asked.

## Screenshots

![alt text](https://github.com/Ahmetf1/DeneyapKart-Test-Setup/blob/main/image/image_app.png?raw=true)
![alt text](https://github.com/Ahmetf1/DeneyapKart-Test-Setup/blob/main/image/image_report.png?raw=true)
