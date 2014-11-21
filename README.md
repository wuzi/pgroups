SA-MP-Player-Groups
===================

A SA:MP library for creating and managing player groups.

Examples
========

```c
#include <pgroups>

enum
{
	GROUP_TYPE_GANG,
	GROUP_TYPE_ADMIN,
	GROUP_TYPE_POLICE
}

new
	gAdminGroup,
	gModsGroup,
	gLspdGroup,
	gArmyGroup,
	gGroveGroup,
	gBallasGroup;

main()
{
	gAdminGroup		= CreateGroup("Administrators",	GROUP_TYPE_ADMIN);
	gModsGroup		= CreateGroup("Moderators",		GROUP_TYPE_ADMIN);
	gLspdGroup		= CreateGroup("LSPD",			GROUP_TYPE_POLICE);
	gArmyGroup		= CreateGroup("Army",			GROUP_TYPE_POLICE);
	gGroveGroup		= CreateGroup("Grove",			GROUP_TYPE_GANG);
	gBallasGroup	= CreateGroup("Ballas",			GROUP_TYPE_GANG);
}

public OnPlayerConnect(playerid)
{
	AddPlayerToGroup(playerid, gAdminGroup);
	SendGroupTypeMessage(GROUP_TYPE_ADMIN, 0xffffffff, "* A player entered the server!");// Admin and Mods group will see this.
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp(cmdtext, "/gols", true))
	{
		if(!IsPlayerInGroup(playerid, gAdminGroup))
			return SendClientMessage(playerid, COLOR_ERROR, "* You are not an admin!");

		SetPlayerPos(playerid, 1548.54, 554.54, 23.45);
		return 1;
	}
	return 0;
}
```

***Check wiki for full details.***
