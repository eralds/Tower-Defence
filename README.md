# Tower-Defence
Tower Defence game implemented in C++ and SFML

![Screenshot (14)](https://github.com/eralds/Tower-Defence/assets/94328315/5bb33043-6f79-4e69-a9c0-d854abf12b89)





## Overview

This project is a UI-based Tower Defence game constructed using the C++ SFML library. It features all standard gameplay elements with additional options. The game offers three levels, each with an increasing degree of difficulty and multiple waves of progressively challenging enemies. 

### Features:


- **Fixed Game Window Size:** Resizing might cause disruptions in the game due to its fixed-button layout.
- **Levels & Enemies:** Three levels with 5-10 enemy waves. As waves progress, enemies become stronger and faster.
- **Player Stats:** Start with 10 hitpoints, each hitpoint corresponding to one enemy reaching the game's end. The game concludes if 10 enemies reach the finish.
![Screenshot (15)](https://github.com/eralds/Tower-Defence/assets/94328315/eaae2d1e-9fac-4820-a751-086447aa18c9)

- **Towers:** Four distinct towers, each with unique capabilities and costs. 
  - **Basic Tower:** Shoots a bullet every 2 seconds and costs 100.
  - **Freeze Tower (Sniper):** Halves enemy speed within range.
  - **Bazooka Tower:** Costs 300 and shoots larger bullets that affect multiple enemies and inflict greater damage than the Basic Tower.
  - **Boat:** Exclusively placed on water tiles, grants the player 50 coins every 10 seconds.
![Screenshot (16)](https://github.com/eralds/Tower-Defence/assets/94328315/4240ded3-0742-4717-8ed7-8021760a2185)

The game relies on strategic tower placement as once a tower is placed, it's permanent.

![video](https://github.com/user-attachments/assets/3b143c9b-5fac-4ffd-bb64-8bd6037c49bd)


## Software Structure

- **External Libraries Used:** SFML

## Instructions for Building and Running

1. **Compilation:** Use the `make` command.
2. **Execution:** Use the `./main` command.
3. **Gameplay:** The user interface is intuitive. Follow on-screen instructions and button descriptions.
