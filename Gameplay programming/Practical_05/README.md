# README #
This project is a **Makefile** starter kit for SFML, this works on Linux
For windows the includes, libraries and paths will need to be set manually
SFML is not supported on Cgwin or MSys2 on Windows so it requires a custom install.
  
## Installation Linux
* Download Repository to your Project Workspace
* Install **SFML** on **debian** based distro using `sudo apt-get install libsfml-dev`
* Navigate to root of project
* type `make`

## Installation Windows
* Download and install [MSYS64](https://www.msys2.org/)  
![MSYS64](./images/MsysWebsite.png)
* Open MSYS Bash
	* **STEP 1** of Updating msys `pacman -Syu` this will shutdown bash when complete.  
	![Pacman Update Step 1](./images/PacmanUpdateStep1.png)
	* **STEP 2** of Updating msys after this has complete restart MSYS Bash and run `pacman -Su`  
	![Pacman Update Step 2](./images/PacmanUpdateStep2.png)
	* **STEP 3** (Note this there are multiple commands below, to get toolchain up and running) Open MSYS Bash and install
>   * **STEP 3.1** **gcc** `pacman -S gcc`  
![Install GCC](./images/InstallGCC.png)
>   * **STEP 3.2** **mingw gcc** `pacman -S mingw-w64-x86_64-gcc`  
![Install MinGW GCC](./images/InstallMinGWGCC.png)
>   * **STEP 3.3** **mingw gdb** `pacman -S mingw-w64-x86_64-gdb`  
![Install GDB](./images/InstallMinGWGDB.png)
>   * **STEP 3.4** **make** `pacman -S make`  
![Install Make](./images/InstallMake.png)
>   * **STEP 3.5** **git** `pacman -S git`  
![Install Git](./images/InstallGit.png)
>   * **STEP 3.6** **SFML** `pacman -S mingw-w64-x86_64-sfml`see [MSYS Website Packages](https://packages.msys2.org/package/mingw-w64-x86_64-sfml).  
![Install SFML](./images/InstallSFML.png) 

* **STEP 4** Setup a Windows Environment Variable which points to where `MYSYS2` is located, also set the location of DLLs in Windows Path.
![Set Environment Variable](./images/EnvironmentVariableMYSYS2.png)
> Restart MSYS64 Bash and check that enviroment variable exists by typing `echo {MYSYS2}` in terminal. Also check that you can see includes, libs and DLLs
* **STEP 5** Create a directory e.g. `Projects` for repository, then `cd c:/Projects' and Clone repository  
![Create Directory and Clone](./images/CloneRepo.png)

* **STEP 6** Ensure Windows SDK is installed, SFML depends on OpenGL libs. Windows SDK can be downloaded from [Microsoft Developer Website](https://developer.microsoft.com/en-us/windows/downloads/sdk-archive/) . Tested with version 19041.0.  
![Windows SDK](./images/Window10SDK.png)

* **STEP 7** Navigate to cloned project folder `sfml_game_collision`
>   * Type `make` in MSYS Bash Terminal  
![Install GCC](./images/GameRunning.png)

## What is this repository for? ##
* Getting started with Visual Studio Code, SFML and Makefiles on Linux and Windows (Note Makefile will work on both as long as toolchain is setup correctly)
* This is a great Tutorial to get this project running on [Windows](https://www.youtube.com/watch?v=Ljhpsdz8Ouo)

## Who do I talk to? ##
* philip.bourke@itcarlow.ie