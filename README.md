# todo_cli
This is a lightweight CLI to keep track of pending tasks using the .csv file format.

# Commands
 
------
+ todo : **prints current registered tasks**
+ todo -add "task title" : **adds an incomplete task to the list**
+ todo -complete n : **marks task number n as completed**
+ todo -delete n : **deletes task number n from the list**
------
# Instalation

Clone this repo and run ``make release``. Then add ./todo to PATH.  
This was only tested on a linux system so it might not work on other operating systems
