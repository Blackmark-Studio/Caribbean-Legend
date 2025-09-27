//Jason общий диалог индейцев на улицах
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
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Sápadtarcú","Fehér squaw") +" akar beszélni?", 
				"Már megint te, "+ GetSexPhrase("sápadtarcú","fehér squaw") +".", 
				""+ GetSexPhrase("sápadtarcú szeret beszélgetni. Mint a squaw.","fehér squaw szeret beszélni.") +"",
                "Nagy Szellem elhozta hozzám a sápadtarcú" + GetSexPhrase("testvért","nôvért") + " .", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Igen.", 
				"Igen, megint én.",
                "Nagyon költôi.", 
				"Én is örülök, hogy látlak.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hogy vagy, fehér testvér? Beszélni akarsz az indiánnal?";
				link.l1 = "Üdvözletem, a dzsungel fia. Örülök, hogy látlak, de mennem kell.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Ne kísértsd a szellemeket, sápadtarcú! Tedd el a hosszú kést!", "Ne rohanj a halálba, sápadtarcú! Tedd el a hosszú kést!");
			link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod.", "Ahogy mondod.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
