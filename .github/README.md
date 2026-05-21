# Mod Customs

[English](README.md)


## Description

This module introduces a set of custom enhancements for your AzerothCore server:

* **Season of Discovery (SoD) Login Buff:** Automatically applies a permanent custom Season of Discovery 300% buff (Spell ID 80870) to players upon login, and removes it cleanly on logout.
* **Quest 52 (Protect the Frontier) Enhancement:** Updates the quest to allow players to kill Gray Forest Wolves for Prowler kill credit. Includes an SQL update for the quest description to match this behavior.
* **Dungeon Respawn:** Automatically teleports and resurrects players back inside the dungeon or raid when they release their spirit after dying. It tracks player positions and saves them to the characters database (`dungeonrespawn_playerinfo`).

## Installation

1. Place the module inside the `modules` directory of your AzerothCore source repository.
2. Re-run CMake and compile the server.

## Configuration

You can configure the **Dungeon Respawn** feature via the module's `.conf` file or your server's configuration with the following variables:
* `DungeonRespawn.Enable` = 0 (Default: false)
* `DungeonRespawn.RespawnHealthPct` = 50.0 (Sets the health percentage upon respawn. Default: 50%)
