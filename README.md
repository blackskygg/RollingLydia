# RollingLydia
The program randomly picks up a name and a problem from a name list and a problem list, respectively.

It's written to assist questioning in classrooms.

# Usage
The program is splitted into 3 tabs, namely, the Rolling Tab, the Name List Tab and the Problem List Tab.

So it's natural to explain the 3 tabs one by one.

##1. the Rolling Tab
It looks like this.

![image](https://github.com/blackskygg/RollingLydia/blob/master/screenshots/rollingtab.png)

Once you click the "Let's Roll" button, the program will start picking random names and problems from a preloaded list.

When you click on the "Stop" button, the name and problem will stop changing, thus producing a result for you.

Once the roll is stoped, you can click on the problem title, and the description of the problem will popup.(See 3. the Problem List Tab for more information about the poped-up window).

The speed can be adjusted according to your need, and the unit is Hz(the number of names displayed within 1s).

And you can also choose to roll the name only, which is useful when asking a question that's not in the problem list.

##2. the Name List Tab
It looks like this.

![image](https://github.com/blackskygg/RollingLydia/blob/master/screenshots/namelist.png)

There are two lists, one containing the names that haven't been picked up yet, and the other containing the rest.

The function of the button should be quite clear, and you can use them to move names between the two lists.

### the Name List Format
The name list file should follow the following format and should be saved using the ``UTF-8 encoding``, this is very important.

If you don't konw how. Use your favorite search engine.

The file should look like:

  name1
  
  name2
  
  name3
  
  name4
  
  ...

  

See https://github.com/blackskygg/RollingLydia/blob/master/namelist.txt for an example.

##3. the Problem List Tab
It looks like this.

![image](https://github.com/blackskygg/RollingLydia/blob/master/screenshots/problem_list.png)

It's almost the same with the Name List Tab, except that you can double-click on the list items to see the description of a program.

When you double-click on an item, a window will pop up for you, and it looks like this.

![image](https://github.com/blackskygg/RollingLydia/blob/master/screenshots/problem.png)

### the Name List Format
The problem list file should follow the following format and should be also be saved using ``UTF-8 encoding``.

The file should look like:

  BEGIN
  
  problem title 1
  
  problem description 1
  
  END
  
  
  （arbitary contents)
  
  
  BEGIN
  
  problem title 2
  
  problem description 2
  
  END
  
  ...
  
See https://github.com/blackskygg/RollingLydia/blob/master/problemlist.txt for an example.
