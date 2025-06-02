// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz?","Czego chciałbyś się dowiedzieć?"),"Czego potrzebujesz, "+GetAddress_Form(NPChar)+"?","To już trzeci raz, kiedy próbujesz mnie zapytać...","Mam cię dość, wynoś się!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Przepraszam, zmieniłem zdanie.","Nic takiego, przepraszam."),"Zapomniałem, przepraszam...","Do trzech razy sztuka, co? Przepraszam...","Przepraszam, przepraszam! Już wychodzę...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
