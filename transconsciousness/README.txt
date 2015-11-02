******************************************
*           Transconsciousness           *
*         MiniLD 55 - Preparation        *
*                 ReadMe                 *
******************************************

 About:
-------

You play as a robot that can precompute it's actions before executing them.
Your goal is to destroy the other bots before they destroy the data.

There are three commands that can be executed: MOVE, SLASH, and SHOOT.

Each of these commands takes time to execute.
As you plan your actions, the projected positions of where enemies will move is displayed.
Use this to see where enemies will be when you attack.

MOVE - 
You move much faster than the other bots but they will still be advancing towards their
target as you move.

SLASH - 
Deals AoE damage to enemies over three adjacent tiles next to the player.
This attack is strong enough to kill anything at full health but you must be standing next to them.

SHOOT - 
Deals ranged damage to one target and has a longeer cool down time than SLASH.
Takes three shots to kill an enemy with full health.
Can defeat weaken enemies (with a red health bar) in one shot.


 Controls:
----------

Left click  - select your next action
Right click - undo last action / cancel current action
Click DONE to execute commands

You win when all enemies are defeated.
Failing to defeat all enemies in one go or letting a bot destroy the data results in defeat.

Most importantly:

HAVE FUN!

There are currently 6 levels.
The first two serve mainly to let you get use to the controls (SHOOT the first one, MOVE and SLASH the second one)
All feedback is welcome.

P.S.: I have discovered a bug that sometimes crashes the game and I believe it's related to SDL_mixer
Running the game with -m (or with runmuted.bat) will disable audio and should fix the problem.
If anyone experiances this bug or knows how to fix it please let me know. Thank you.
