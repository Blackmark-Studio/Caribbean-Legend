void Ship_OnDead()
{
	int charIndex = GetEventData();

	if (charIndex != nMainCharacterIndex) // fix crash
	{
		SendMessage(&Seafoam, "la", MSG_SHIP_DELETE ,&Characters[charIndex]);
		SendMessage(&Sailors, "la", MSG_SHIP_DELETE ,&Characters[charIndex]);
		SendMessage(&SinkEffect, "la", MSG_SHIP_DELETE ,&Characters[charIndex]);
		SendMessage(&Telescope, "la", MSG_SHIP_DELETE ,&Characters[charIndex]);

		PostEvent("evntQuestsCheck",10);   // boal bug fix 24/07/05
	}
}

#event_handler("Event_DeleteShipSailors", "Ship_DeleteSailors");
void Ship_DeleteSailors()
{
	int charIndex = GetEventData();
	SendMessage(&Sailors, "la", MSG_SHIP_DELETE, &Characters[charIndex]);
}

#event_handler("Event_DeleteShipFoam", "Ship_DeleteFoam");
void Ship_DeleteFoam()
{
	int charIndex = GetEventData();
	SendMessage(&Seafoam, "la", MSG_SHIP_DELETE, &Characters[charIndex]);
}