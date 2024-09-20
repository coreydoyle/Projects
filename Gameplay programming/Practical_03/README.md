# README #
This project is a **Makefile** starter kit for Orc's vs Trolls

## What is this repository for? ##
* Getting started with Visual Studio Code and a multi-file simple game project
### How do I get set up? ###
* Download Visual Studio Code
* Install C/C++ for Visual Studio Code
> `ctrl+shift+x`
search for `@ext:ms-vscode.cpptools` or `C/C++ IntelliSense, debugging, and code browsing.`
Install this plugin,
* Ensure build tools are installed one linux run terminal command `sudo apt install build-essential gdb`. This installs essential build tools and gdb debugger. For Windows see [Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw).
* Create Makefiles and Source (see Parts 1 to 10 below for introduction to **make**)
* Try out various Makefiles and Makefile syntax

## Configuration guidelines ##
* Ensure Visual Studio Code is setup correcly. A typical error is that 'Tab's is set to spaces instead of being stored as tabs.
* Makefile should be indented using tabs, if you receive an error message similar to this `Makefile:2: *** missing separator. Stop.` check your VSC tabs settings
* Stackoverflow has entry on this specific error message [Stackoverflow](https://stackoverflow.com/questions/23927212/makefile2-missing-separator-stop).
*  [Makefile execution success](./images/MakeFileSuccess.png)

### Classes

[![](https://mermaid.ink/img/pako:eNp9UcFqwzAM_RXhSxJoYeewHUY2dhqDbUdfFEdeTB27yM5K6frvs93QwDbmi6X3nqSHdBLKDyRaoSyG8GDwg3GSzvlIIMULqyoAugHe2Vub4iecCOrexxG8hsNo1AjIBFXnnWLCVNblThSqRoqlkfYM3YiMKhKntvd9iDm5SLNMujJ_VUkH6a1Ft1_bLSQ7f-LF3A-mBW3Nvm5-wZ-G44wWDmh3_9DaHuvm7ma1loafLuoemcm-ppm5_rxKio9FFHF2sfBiIybiCc2Q1lxYKeJIE0nRpnAgjbONeQtZinP0b0enRBt5po2Y90Na6nIY0Wq04Yo-DiZ6voJU0uflnvk7fwOMPaL3?type=png)](https://mermaid-js.github.io/mermaid-live-editor/edit#pako:eNp9UcFqwzAM_RXhSxJoYeewHUY2dhqDbUdfFEdeTB27yM5K6frvs93QwDbmi6X3nqSHdBLKDyRaoSyG8GDwg3GSzvlIIMULqyoAugHe2Vub4iecCOrexxG8hsNo1AjIBFXnnWLCVNblThSqRoqlkfYM3YiMKhKntvd9iDm5SLNMujJ_VUkH6a1Ft1_bLSQ7f-LF3A-mBW3Nvm5-wZ-G44wWDmh3_9DaHuvm7ma1loafLuoemcm-ppm5_rxKio9FFHF2sfBiIybiCc2Q1lxYKeJIE0nRpnAgjbONeQtZinP0b0enRBt5po2Y90Na6nIY0Wq04Yo-DiZ6voJU0uflnvk7fwOMPaL3)


## Useful Resources ##
* [GNU Make Manual](http://www.gnu.org/software/make/manual/make.html)
* [Makefile Tutorial](https://makefiletutorial.com/)
* [GDB GNU Debugger Project](https://www.gnu.org/software/gdb/)
* [Enabling build and debugging in Visual Studio Code](https://dev.to/talhabalaj/setup-visual-studio-code-for-multi-file-c-projects-1jpi)
* Debugging with VSC beyond return point may result in the following error message being displayed [pop up](https://github.com/Microsoft/vscode-cpptools/issues/1123)

## Who do I talk to? ##
* philip.bourke@setu.ie