# pwnadv3hack
simple hotkey hack for Pwn Adventure 3

Original goal for this "project" was to be able to spawn any enemy (eg: Bear, AngryBear, TownRat, GiantRat, etc) at my own will. Unfortunately, it requires a deeper dive into the client and I don't think doing so warrants the effort needed. Nevertheless, working on this exposed me to concepts that are essential to reversing c++ programs.

Example concepts:
----------------------------------------------------------------------------------------------

  C-style casts & reinterpret_cast<..>
  Function pointers
  Virtual tables/functions & 
  Multi-level pointers
  Class Informer plugin (IDA) 
  Reclass
  RTTI & analyzing x86 in C++ 

----------------------------------------------------------------------------------------------

Features include:
  speed hack,
  jump hack,
  health/mana hack 
  teleport to a specified region.
  
  
Original client site:
https://www.pwnadventure.com/ 

Walkthrough of solving the actual challenges in game by LiveOverflow:
https://liveoverflow.com/lets-playhack-pwn-adventure-3-pwnie-island/

Reversing C++ guide/help:
https://www.blackhat.com/presentations/bh-dc-07/Sabanal_Yason/Paper/bh-dc-07-Sabanal_Yason-WP.pdf
