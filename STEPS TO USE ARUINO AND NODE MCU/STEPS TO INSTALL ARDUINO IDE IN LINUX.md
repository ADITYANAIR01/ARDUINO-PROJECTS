* 	How to install arduino ide in linux 

     ** MODULE 1 (terminal)

1. Download the linux appimage from official arduino page.
2. write these commands in terminal " sudo add-apt-repository universe " & " sudo apt install libfuse2  ".
3. Change directory to the downloaded image type ls .
4. Now type chmod +x appimage name (chmod +x arduino-ide_2.3.2_Linux_64bit.AppImage).
5. Now type ./arduino-ide_2.3.2_Linux_64bit.AppImage // the arduino application will open but will not be able to upload the code. 
6. To see the port permissions use ( ls -la /dev | grep ttyACM0
7. Now type ( sudo usermod -a -G dialout username ) eg,(sudo usermod -a -G dialout rog)
8. To set the permissions use this command ( sudo chmod a+rw /dev/ttyACM0 ) // read & write permissions
9. Use ( ls -la /dev | grep ttyACM0 ) to see the updated permissions 

     ** MODULE 2 (SHORTCUT)
1. Write ( sudo apt install gedit )
2. Copy ( cd ~/.local/share//applications/ )
3. Copy ( gedit arduino.desktop )
4. Copy this and edit according to your machine  //making shortcut for arduino ide
{

[Desktop Entry]
Type=Application
Name=Arduino IDE 2.3.2
Exec=/home/rog/Downloads/arduino-ide_2.3.2_Linux_64bit.AppImage  

}
5. Now you can open the terminal and search for arduino ide 

6. CONGRATULATIONS YOU HAVE SUCESSFULLY INSTALLED THE ARDUINO IDE WITH PROPER FUNCTIONALITIES :) 