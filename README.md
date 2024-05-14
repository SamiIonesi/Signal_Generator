# Signal_Generator
<p align="center">
  <img src="" width="800" height="250">
</p>

# Story
This project has an univeristy purpose and describe a template of a signal generator with the help of a MSP430 microcontroller from Texas Instruments.

The user will have a console menu from where it can chose the specific signal, with the specific parameters that he want to see it on the osciloscope.

# What you will need to run this project?
Software
- a IDE where you will run the code: [**Code Composer**](https://www.ti.com/tool/download/CCSTUDIO/12.7.0)
- a console for the UART communication: [**TeraTerm**](https://tera-term.en.lo4d.com/windows)

Hardware
- the [**MSP430 LaunchPad**](https://www.ti.com/tool/MSP-EXP430FR2355)
- an oscilloscope with a probe

# The project workflow

First of all, after installing TeraTerm from the upper link, connect the MSP board via USB to the computer, then open the TeraTerm application and select the communication port specific to the microcontroller as in the figure below. Attention: The port is different for each computer, select the one that contains the *MSP Application UART1*.

![Port_TerraTerm](https://github.com/SamiIonesi/Signal_Generator/assets/150432462/f8b7ec25-d59a-4716-b984-f9a952072250)"

After this step, the TeraTerm console will open. From Setup/Serial Port..., make the configurations as in the image below and then click New Open.

![Configuratii_SerialPort](https://github.com/SamiIonesi/Signal_Generator/assets/150432462/0e61a480-d153-46bf-bcae-e95a8f1589e6)

Then you will have to open the Code Composer IDE and you will have to create a new project from File/CCS Project and select the data as in the following figure and then click finish.

![Create_project](https://github.com/SamiIonesi/Signal_Generator/assets/150432462/4b857171-5b3c-4781-942f-986d0da4da2e)

Now you have a new project created in Code Composer. From the Project Explorer window, right-click on the name of the created project, then press New/Source File and create a new file with the extension .c as in the figure below.

![Source_file](https://github.com/SamiIonesi/Signal_Generator/assets/150432462/35f90115-f333-4286-9cfb-15e64eb70c70)

And in this created source file, enter the code you find above under the name Signal_generator.c or from this [link]()

After you put the code in the source file, you cand flash the project to be uploaded on the microcontroller as you can see in the following image. Be sure that youre MSP430 is connected to the computer.

![Flash](https://github.com/SamiIonesi/Signal_Generator/assets/150432462/bc862d73-dade-43de-88bc-a1b0c0cf3ae9)

After flashing, if you don't have any errors, the project should compile and at this moment you can use the application. Press the P4.1 button on the microcontroller and the application menu will appear in TeraTerm as in the image below.

![signal_menu](https://github.com/SamiIonesi/Signal_Generator/assets/150432462/871b19ac-aa1d-4e62-8dda-fdc53b1775d4)

From this moment with the help of a probe that you connect to the oscilloscope, you can see any signal that you choose from the menu at the pin specified in the console and you can also change some signal parameters (number of samples, frequency, duty cycle).



