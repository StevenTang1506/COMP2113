# Mini-baseball Game

## Team Members

- Tang Yun Kuen 3035685457

## Demo Video
<iframe width="560" height="315" src="https://www.youtube.com/embed/hCzKy_ZhkiM?si=fX6eIS9RBx-K4jGz" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

## Game Description and Rules

Mini-baseball Game is a text-based baseball game where players take turns to pitch and hit. The aim of the game is to score as many runs as possible before the game ends.

The game operates on an inning-by-inning basis. As the pitcher, the player selects a pitch location from 1 to 9 representing different parts of the strike zone. The batter then selects a swing location from 1 to 9. If the swing location matches the pitch location, it's a hit! Otherwise, it's a strike or out!

## Features and Coding Elements 

**Feature 1** - Pitching and Hitting Mechanics: The game incorporates pitching and hitting mechanics that allow players to choose different types of pitches and hits. This feature is supported by a series of if-else statements that determine the outcome of the pitch or hit based on the player's choice and a randomized element.

**Feature 2** - Scoring System: The game includes a scoring system that tracks runs, hits, and outs, and determines the winner at the end of the game. This feature is supported by variables that keep track of these statistics and functions that update these variables based on the outcomes of the pitches and hits.

**Feature 3** - Game Progression: The game progresses inning by inning, with each inning divided into two halves. This feature is supported by a while loop that continues until the set number of innings is reached.

**Feature 4** - Player Input: The game allows for player input to choose pitches, hits, and strategic decisions. This feature is supported by the use of standard input functions.

**Feature 5** - Randomization: The game includes a randomization element to simulate the unpredictability of a real baseball game. This feature is supported by the use of random number generator functions.

## Non-Standard Libraries

1. **Library 1** - random: This library is used to generate random numbers that add an element of unpredictability to the outcomes of pitches and hits.

## Compilation and Execution Instructions

1. Download the source code files and make sure they are in the same directory.
2. Open your terminal and navigate to the directory containing the files.
3. Compile the game using the command ```make```.
4. Run the game using the command ```./game```.

We hope you enjoy playing my game!
