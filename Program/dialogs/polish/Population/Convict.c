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
			dialog.text = NPCStringReactionRepeat("Znowu ty, senor?","Słuchaj, panie, lepiej żebyś sobie poszedł...","Nie zawracaj mi głowy, panie! Uprzejmie proszę.","Och, nie mogę tego znieść... Nawet wiosłowanie na galerze było lepsze.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tak, to znowu ja.","Nie mów mi, co mam robić.","A jeśli będę dalej przeszkadzał?","Wróć do kuchni wtedy!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Czego chcesz, señor?";
				link.l1 = "Od ciebie? Niczego, jak sądzę. Chciałem tylko powiedzieć cześć.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Nie igrać z losem, kumplu! Schowaj broń!","Słuchaj, jestem obywatelem tego miasta i proszę cię, abyś schował swoją broń.");
			link.l1 = LinkRandPhrase("Dobrze...","Jak sobie życzysz...","Jak mówisz...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
