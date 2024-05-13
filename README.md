# Signal_Generator
<p align="center">
  <img src="" width="800" height="250">
</p>

# Story
This project has an univeristy purpose and describe a template of a signal generator with the help of a MSP430 microcontroller from Texas Instruments.

The user will have a console menu from where it can chose the specific signal, with the specific parameters that he want to see it with the osciloscope.

# What you will need to run this project?
- a IDE where you will run the code: [**Code Composer**](https://www.ti.com/tool/download/CCSTUDIO/12.7.0)
- a console for the UART communication: [TeraTerm](https://tera-term.en.lo4d.com/windows)

# The project workflow
First of all, after you have installed TeraTerm, open the application to make the necessary configurations.

First of all, after installing TeraTerm, connect the MSP board via USB to the computer, then open the application and select the communication port specific to the microcontroller as in the figure below. Attention: The port is different for each computer, select the one that contains the MSP Application UART1.

![Port_TerraTerm](https://github.com/SamiIonesi/Signal_Generator/assets/150432462/f8b7ec25-d59a-4716-b984-f9a952072250)"

After this step, the TeraTerm console will open. From Setup/Serial Port..., make the configurations as in the image below.

![Configuratii_SerialPort](https://github.com/SamiIonesi/Signal_Generator/assets/150432462/0e61a480-d153-46bf-bcae-e95a8f1589e6)

Then you will have to open the Code Composer IDE and you will have to create a new project from File/CCS Project and select the data as in the following figure and the click finish.

![Create_project](https://github.com/SamiIonesi/Signal_Generator/assets/150432462/4b857171-5b3c-4781-942f-986d0da4da2e)


