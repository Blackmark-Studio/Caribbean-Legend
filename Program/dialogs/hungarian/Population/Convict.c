// диалог освобожденных каторжников рудника
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("Már megint maga, senor?", 
				"Figyeljen, uram, jobb, ha elmegy...", 
				"Ne zavarjon, uram! Szívélyesen megkérem.",
                "Ó, én ezt nem bírom elviselni... Még a konyhai evezôvel való munka is jobb volt.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Igen, megint én vagyok.", 
				"Ne mondd meg, mit tegyek.",
                "És mi van, ha tovább zaklatlak?", 
				"Akkor menj vissza a konyhába!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Mit akar, senor?";
				link.l1 = "Magától? Semmit, gondolom. Csak köszönni akartam.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Ne kérdôjelezd meg a sorsodat, haver! Tedd el a fegyvered!", "Figyelj, én ennek a városnak a polgára vagyok, és arra kérlek, hogy tedd le a pengédet.");
			link.l1 = LinkRandPhrase("Jól van...", "Ahogy kívánod...", "Ahogy mondod...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
