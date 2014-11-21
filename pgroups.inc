//------------------------------------------------------------------------------

/*
	SA-MP Groups include

	Description:
		This include provide code to create player groups in SA-MP Pawn.

	License:
		The MIT License (MIT)
		Copyright (c) 2014 WiRR-
		Permission is hereby granted, free of charge, to any person obtaining a copy
		of this software and associated documentation files (the "Software"), to deal
		in the Software without restriction, including without limitation the rights
		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
		copies of the Software, and to permit persons to whom the Software is
		furnished to do so, subject to the following conditions:
		The above copyright notice and this permission notice shall be included in all
		copies or substantial portions of the Software.
		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
		SOFTWARE.

	Author:
		WiRR

	Contributors:
		-

	Version:
		1.0
*/

//------------------------------------------------------------------------------

#include <a_samp>

#if defined _inc_groups_included
	#endinput
#endif
#define _inc_groups_included

//------------------------------------------------------------------------------

/*
native CreateGroup(groupname[], type = INVALID_GROUP_TYPE);
native SendGroupTypeMessage(grouptype, color, message[]);
native RemovePlayerFromGroup(playerid, groupid);
native AddPlayerToGroup(playerid, groupid);
native SendGroupMessage(color, message[]);
native IsPlayerInGroup(playerid, groupid);
native SetGroupName(groupid, groupname[]);
native SetGroupType(groupid, grouptype);
native GetGroupIDbyName(groupname[]);
native GetGroupName(groupid);
native GetGroupType(groupid);
*/

//------------------------------------------------------------------------------

#if !defined MAX_GROUPS
	#define MAX_GROUPS 32
#endif

//------------------------------------------------------------------------------

#if !defined MAX_GROUP_NAME
	#define MAX_GROUP_NAME 32
#endif

//------------------------------------------------------------------------------

#define INVALID_GROUP_TYPE 	-1
#define INVALID_GROUP_ID 	-1

//------------------------------------------------------------------------------

enum E_GROUP_DATA
{
	E_GROUP_TYPE,
	E_GROUP_NAME[MAX_GROUP_NAME]
}
static g_eGroupData[MAX_GROUPS][E_GROUP_DATA];

//------------------------------------------------------------------------------

stock CreateGroup(const groupname[], type = INVALID_GROUP_TYPE)
{
	new nGroupCounter = GetFreeGroupID();
	if(nGroupCounter == INVALID_GROUP_ID)
	{
		print("ERROR: Limit of groups exceeded! Increase the limit or reduce the created groups.");
		return 0;
	}

	g_eGroupData[nGroupCounter][E_GROUP_TYPE] = type;
	format(g_eGroupData[nGroupCounter][E_GROUP_NAME], MAX_GROUP_NAME, groupname);
	return nGroupCounter;
}

//------------------------------------------------------------------------------

stock SetGroupName(groupid, const groupname[])
{
	format(g_eGroupData[groupid][E_GROUP_NAME], MAX_GROUP_NAME, groupname);
	return 1;
}

//------------------------------------------------------------------------------

stock GetGroupName(groupid)
{
	new groupName[MAX_GROUP_NAME];
	format(groupName, sizeof(groupName), g_eGroupData[groupid][E_GROUP_NAME]);
	return groupName;
}

//------------------------------------------------------------------------------

stock GetGroupIDbyName(const groupname[])
{
	for (new i; i < MAX_GROUPS; i++)
	{
		if((strcmp(g_eGroupData[i][E_GROUP_NAME], groupname, true, strlen(groupname)) == 0))
			return i;
	}
	return INVALID_GROUP_ID;
}

//------------------------------------------------------------------------------

stock SetGroupType(groupid, grouptype)
	return g_eGroupData[groupid][E_GROUP_TYPE] = grouptype;

//------------------------------------------------------------------------------

stock GetGroupType(groupid)
	return g_eGroupData[groupid][E_GROUP_TYPE];

//------------------------------------------------------------------------------

stock IsPlayerInGroup(playerid, groupid)
{
	new playerGroup[16];
	format(playerGroup, 16, "p_group_%i", groupid);
	if(GetPVarInt(playerid, playerGroup))
		return 1;
	return 0;
}

//------------------------------------------------------------------------------

stock AddPlayerToGroup(playerid, groupid)
{
	new playerGroup[16];
	format(playerGroup, 16, "p_group_%i", groupid);
	SetPVarInt(playerid, playerGroup, true);
	return 1;
}

//------------------------------------------------------------------------------

stock RemovePlayerFromGroup(playerid, groupid)
{
	new playerGroup[16];
	format(playerGroup, 16, "p_group_%i", groupid);
	DeletePVar(playerid, playerGroup);
	return 1;
}

//------------------------------------------------------------------------------

stock SendGroupMessage(groupid, color, const message[])
{
	for(new i; i < GetMaxPlayers(); i++)
	{
		if (!IsPlayerConnected(i))
			continue;

		if(IsPlayerInGroup(i, groupid))
			SendClientMessage(i, color, message);
	}
	return 1;
}

//------------------------------------------------------------------------------

stock SendGroupTypeMessage(grouptype, color, const message[])
{
	for(new i; i < GetMaxPlayers(); i++)
	{
		if(!IsPlayerConnected(i))
			continue;

		for(new g; g < MAX_GROUPS; g++)
			if(IsPlayerInGroup(i, g) && g_eGroupData[g][E_GROUP_TYPE] == grouptype)
				SendClientMessage(i, color, message);	
	}
	return 1;
}

//------------------------------------------------------------------------------

stock GetFreeGroupID()
{
	for(new i; i < MAX_GROUPS; i++)
		if(strlen(g_eGroupData[i][E_GROUP_NAME]) < 2)
			return i;
	return INVALID_GROUP_ID;
}

//------------------------------------------------------------------------------
