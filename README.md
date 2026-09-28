# VBST
A simple Binary Search Tree implementation that is built to handle any abstract data type that can be ordered by numeric keys. It uses normal ints in the node keys, but this can be changed depending on the application.

## Usage
You can use it as a module for other projects or simply as a tree simulator with a GUI. The tree runs entirely on RAM so if you need to store it on a persistent drive you have two options:
1- The function print_tree puts out the tree in text format, you can redirect the exit for a file an save it as you wish. This is what I've done in the script to run the GUI. Note that this option saves the tree "in-clear" so it is not secure for storing sensitive data!
2- Whatever you want to do!

## GUI
If you use the function print_tree in your main, you can run the *automatic_gui_show.sh* script to open it on a PyGame GUI, which is very useful, but you should use print_tree only in the end of your code or change the way *automatic_gui_show.sh* script runs. 
