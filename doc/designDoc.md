## CS 6613 Artificial Intelligence Project Checker Game Design
Name : Kai Chen
NetId: kc3443

### How to compile and run

- Command line version (cmake is required to compile)

```
cd checker-game-commandline

mkdir release

cd release

cmake ..

make

./checker-game-cmd
```
![Snip20180331_14](/assets/Snip20180331_14.png)

- GUI version (Using QT, C++ GUI Library, qmake is required to compile)

```
cd checker-game-ui

mkdir release

cd release

qmake ..

make

# For Mac, use this command, if you use windows or linux, 
# please go to corresponding folder to run app. 
# since QT is a cross platform library, different OS 
# will generate different code

./checker-game-ui.app/Contents/MacOs/checker-game-ui
```


![Snip20180331_12](/assets/Snip20180331_12.png)


### OOAD Desigin

- Class Design
![Snip20180331_16](/assets/Snip20180331_16.png)

- Game Flow

![Snip20180331_17](/assets/Snip20180331_17.png)

### Terminal state

- WIN: 200
- LOSR:  200
- DRAW: 0
- Evaluation value for cut off: (-200, 200)

### Evaluation function

when search depth reaches Max Depth, cut off happens and evaluation function will be returned. Function is as below:

$$f = w_1 * cost_1 + w_2 * cost_2$$

$cost_1$ is the difference between pieces left on the board, that is the number of AI pieces - the number of human pieces. $w_1$ is the weight of $cost_1$.

$cost_2$ is the difference between safe pieces left on the board. $w_2$ is the weight of $cost_2$. Here safe means the piece is on the leftmost column or the rightmost column since these positions will never be captured and it's safe to stay.

If the evaluation function $f$ is higher, then means this status is more likely to win for AI.

### Difficulty set

I implement diffetent difficulty by setting different **Max Search Depth**

- Easy: 3 Max Search Depth
- Medium: 6 Max Search Depth
- Hard: 15 Max Search Depth


### Code structure (c++)

- include: header file
- src: source file
- checker-game-ui: QT UI class, main ui program
- checker-game-commandline: main command line program
- doc: documentation
![Snip20180331_20](/assets/Snip20180331_20.png)

### Alpha-Beta Algorithm Implementaion
in the class `AIStrategy`, file location
- include/Strategy.h
- src/Strategy.cpp



