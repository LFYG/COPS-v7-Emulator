/**
 * ****** COPS v7 Emulator - Open Source ******
 * Copyright (C) 2012 - 2014 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _COPS_V7_EMULATOR_WORLD_H_
#define _COPS_V7_EMULATOR_WORLD_H_

#include "common.h"
#include "env.h"
#include <map>

class Entity;
class AdvancedEntity;
class Player;
class Monster;
class Npc;
class NpcTask;
class Worker;

/**
 * Global world object containing all entities, tasks, etc.
 * It is a singleton and will be created when getting the instance.
 */
class World : public Environment::Global
{
    friend class Database; // loading entities, etc...
    friend class Worker; // entities, etc...

    PROHIBIT_COPY(World); // one world per server...

public:
    /**
     * Get the World singleton. If the object does not exist yet,
     * it will be created.
     *
     * @returns A reference to the singleton
     */
    static World& getInstance();

public:
    /* destructor */
    virtual ~World();

public:
    /**
     * Add a player to the world.
     *
     * @param[in]   aPlayer    a reference to the player to add
     *
     * @retval TRUE if the player is added
     * @returns FALSE otherwise
     */
    bool addPlayer(Player& aPlayer);

    /**
     * Remove a player from the world.
     *
     * @param[in]   aPlayer    a reference to the player to remove
     *
     * @retval TRUE if the player is removed
     * @returns FALSE otherwise
     */
    bool removePlayer(Player& aPlayer);

    /**
     * Search an entity based on its UID. If the entity is not found,
     * the output entity will be null.
     *
     * @param[in,out]   aOutEntity   a pointer to the object receiving the entity
     * @param[in]       aUID         the UID of the entity
     *
     * @retval TRUE if the entity is found
     * @returns FALSE otherwise
     */
    bool queryEntity(Entity** aOutEntity, uint32_t aUID) const;

    /**
     * Search a player based on its UID. If the player is not found,
     * the output player will be null.
     *
     * @param[in,out]   aOutPlayer   a pointer to the object receiving the player
     * @param[in]       aUID         the UID of the player
     *
     * @retval TRUE if the player is found
     * @returns FALSE otherwise
     */
    bool queryPlayer(Player** aOutPlayer, uint32_t aUID) const;

    /**
     * Search a player based on its name. If the player is not found,
     * the output player will be null.
     *
     * @param[in,out]   aOutPlayer   a pointer to the object receiving the player
     * @param[in]       aName        the name of the player
     *
     * @retval TRUE if the player is found
     * @returns FALSE otherwise
     */
    bool queryPlayer(Player** aOutPlayer, const char* aName) const;
    bool queryPlayer(Player** aOutPlayer, const std::string& aName) const;

    /**
     * Search a NPC based on its UID. If the NPC is not found,
     * the output NPC will be null.
     *
     * @param[in,out]   aOutNpc      a pointer to the object receiving the NPC
     * @param[in]       aUID         the UID of the NPC
     *
     * @retval TRUE if the NPC is found
     * @returns FALSE otherwise
     */
    bool queryNpc(Npc** aOutNpc, uint32_t aUID) const;

private:
    /* constructor */
    World();

private:
    static World* sInstance; //!< static instance of the singleton

private: // aliases
    std::map<uint32_t, Player*>& AllPlayers;
    std::map<std::string, Player*>& AllPlayerNames;

    std::map<uint32_t, Npc*>& AllNPCs;
    std::map<uint32_t, NpcTask*>& AllTasks;

private:
    std::map<uint32_t, Player*> mAllPlayers; //!< internal map
    std::map<std::string, Player*> mAllPlayerNames; //!< internal map

    std::map<uint32_t, Npc*> mAllNPCs; //!< internal map
    std::map<uint32_t, NpcTask*> mAllTasks; //!< internal map

    Worker* mWorker; //!< separate thread for timer
};

#endif // _COPS_V7_EMULATOR_WORLD_H_
