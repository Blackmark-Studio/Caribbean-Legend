// NOTE: this file must be included after all native declarations
// in seadogs.c but BEFORE it imports script libraries...
// otherwise the compiler WILL complain and refuse to load the segments...

// sApplicationId:   Discord Client ID from Discord Developers
// bAutoRegister:    Whether to automatically register this game in the client?
// sOptionalSteamId: Steam App ID, if this is a Steam game launched through Steam
// Returns true if the DLL is loaded and the service was created
// Returns false if the DLL is missing or can't be loaded
native bool DiscordInitialize(string sApplicationId, bool bAutoRegister, string sOptionalSteamId);
// state:            value = string, short state of the gameplay
// details:          value = string, longer description of the gameplay
// largeimagekey:    value = string, ID of the larger icon within the rich presence
// largeimagetext:   value = string, text to show when mouse is hovering over the image
// smallimagekey:    value = string, ID of the smaller icon within the larger icon in the rich presence
// smallimagetext:   value = string, text to show when mouse is hovering over the smaller image
// partyid:          value = string, unused deprecated old multiplayer stuff
// partysize:        value = int32 as string, ditto
// partyprivacy:     value = int32 as string, ditto
// instance:         value = int8 as string, ditto
// matchsecret:      value = string, ditto
// joinsecret:       value = string, ditto
// spectatesecret:   value = string, ditto
// buttonname0:      value = string, name of the first button in the list (must be short)
// buttonurl0:       value = string, URL to open when the button is pressed (must be https://)
// buttonname1:      value = string, ditto but for the second button
// buttonurl1:       value = string, ditto but for the second button
// starttimestamp:   value = int64 as string, beginning timestamp
// endtimestamp:     value = int64 as string, end timestamp of the session (multiplayer only)
// commit:           value = empty string, commit this rich presence to library right now
// reset:            value = empty string, only resets the cached state, not the library state
// clear:            value = empty string, clear the current rich presence (plz use this, not reset)
// shutdown:         value = empty string, shutdown the entire presence library (CAUTION!)
native bool DiscordSetRichPresence(string sKey, string sValue);
// Returns current system UTC time for starttimestamp and endtimestamp
// Does not actually rely on any Discord state (calls std::time), here for convenience :)
native string DiscordGetSystemTime();

#libriary "DISCORD_SCRIPT_LIBRARY"
// ya potratil primerno chas shtoby ponyat
// chto snachala nado declare native funkcii, a potom uzhe
// importirovat libriary (lol), inache ono rugaetsya
// na undeclared function.... >:(((( -nik

#event_handler("DiscordRichPresence","ProcessDiscordRichPresence"); // nkrapivindev 03112025 =^-^=

void InitializeRichPresence()
{
	// These IDs are only for use with Caribbean Legend,
	// if you use these in your own game... shame on you!
	// TODO: read these from engine.ini instead...???
	DiscordInitialize("1434603077457018983", true, "2230980");
	//                 ^ discord client id   ^ reg  ^ steam app id
	DiscordSetRichPresence("state", "Sailing the Caribbean");
	DiscordSetRichPresence("details", "Pirate Open World RPG");
	DiscordSetRichPresence("starttimestamp", DiscordGetSystemTime());
	DiscordSetRichPresence("buttonname0", "Get the game!");
	DiscordSetRichPresence("buttonurl0", "https://store.steampowered.com/app/2230980/");
	DiscordSetRichPresence("buttonname1", "Join the server!");
	DiscordSetRichPresence("buttonurl1", "https://discord.gg/caribbeanlegend");
	DiscordSetRichPresence("largeimagekey", "chdm");
	DiscordSetRichPresence("largeimagetext", "This is Charles de Maure!");
	SteamSetRichPresence("steam_display", "#JoinThePlayTest");
}

// external events from libdiscord-rpc will go here
void ProcessDiscordRichPresence()
{
	// event subtype (always a lowercase english string)
	string sEventType = GetEventData();
	// for "ready" and "joinrequest", matches struct DiscordUser*
	string sUserId, sUsername, sDiscriminator, sAvatarHash;
	// for "disconnected" and "errored"
	int iErrorCode; string sMessage;
	// for "joingame"
	string sJoinSecret;
	// for "spectategame"
	string sSpectateSecret;
	if (sEventType == "ready")
	{
		sUserId = GetEventData();
		sUsername = GetEventData();
		sDiscriminator = GetEventData();
		sAvatarHash = GetEventData();
		// commit the current state now, good practice.
		DiscordSetRichPresence("commit", "");
	}
	else if (sEventType == "disconnected")
	{
		iErrorCode = GetEventData();
		sMessage = GetEventData();
		// TODO: log this?
	}
	else if (sEventType == "errored")
	{
		iErrorCode = GetEventData();
		sMessage = GetEventData();
		// TODO: log this!!!!
	}
	else if (sEventType == "joingame")
	{
		sJoinSecret = GetEventData();
		// not actually used, but process this event anyway
	}
	else if (sEventType == "spectategame")
	{
		sSpectateSecret = GetEventData();
		// ditto.
	}
	else if (sEventType == "joinrequest")
	{
		sUserId = GetEventData();
		sUsername = GetEventData();
		sDiscriminator = GetEventData();
		sAvatarHash = GetEventData();
		// ditto.
	}
	else
	{
		// unknown event type?!
		// TODO: log this!!!!
	}
}
