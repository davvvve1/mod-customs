# Mod Customs

[English](README.md)


## Description

This module introduces a set of custom enhancements for your AzerothCore server:

* **Custom Login Buff:** Automatically applies a permanent custom 300% buff (Spell ID 80870) to players upon login, and removes it cleanly on logout.
* **Quest 52 (Protect the Frontier) Enhancement:** Updates the quest to allow players to kill Gray Forest Wolves for Prowler kill credit. Includes an SQL update for the quest description to match this behavior.

## Installation

1. Place the module inside the `modules` directory of your AzerothCore source repository.
2. Re-run CMake and compile the server.
