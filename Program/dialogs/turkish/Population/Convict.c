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
			dialog.text = NPCStringReactionRepeat("Yine sen misin, señor?","Dinleyin, efendim, en iyisi buradan uzaklaşsanız iyi olur...","Beni rahatsız etmeyin, efendim! Rica ediyorum.","Ah, buna dayanamam... Kürek çekmek bile bundan iyiydi.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Evet, yine benim.","Bana ne yapacağımı söyleme.","Ya seni rahatsız etmeye devam edersem?","Öyleyse hemen mutfağa geri dön!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ne istiyorsun, señor?";
				link.l1 = "Senden mi? Hiçbir şey sanırım. Sadece merhaba demek istedim.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Kaderini zorlama, dostum! Silahını indir!","Dinle, ben bu kasabanın bir vatandaşıyım ve senden kılıcını kınına koymanı istiyorum.");
			link.l1 = LinkRandPhrase("Pekâlâ...","Nasıl istersen...","Dediğiniz gibi...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
