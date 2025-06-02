void OZ_Kuznets_NoAgree()
{
	CloseQuestHeader("OZ");
	sld = CharacterFromID("OZ_Blacksmith");
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
}

void OZ_Kuznets_Agree()
{
	AddQuestRecord("OZ", "2");
	AddQuestUserData("OZ", "sSex", GetSexPhrase("ся","ась"));
	
	sld = GetCharacter(NPC_GenerateCharacter("OZ_Shuler", "citiz_27", "man", "man", 5, SPAIN, -1, false, "quest"));
	//FreeSitLocator("PortSpein_tavern", "sit", "sit_base6");
	ChangeCharacterAddressGroup(sld, "PortSpein_tavern", "sit", "sit_base6");
	LAi_SetSitType(sld);
}

