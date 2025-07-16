// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania do żołnierza?","Żołnierz ma całe swoje życie zaplanowane - stróżowanie, krzątanie się... Jak mogę Ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Nie powinieneś zawracać głowy żołnierzowi głupimi pytaniami, "+GetAddress_Form(NPChar)+"...","To już trzeci raz dzisiaj, kiedy próbujesz mi zadać pytanie...","Los żołnierza nie jest łatwy, a ty, łobuzie, doprowadzasz mnie do szału...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz o czym rozmawiać."),"Zrozumiałem...","Tak, masz rację, to już trzeci raz...","Przepraszam...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
