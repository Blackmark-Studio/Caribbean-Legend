// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania masz do żołnierza?","Żołnierz ma całe swoje życie zaplanowane - strzeżenie, krzątanina... Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Nie powinieneś zawracać głowy żołnierzowi głupimi pytaniami, "+GetAddress_Form(NPChar)+"...","To już trzeci raz dzisiaj, kiedy próbujesz zadać mi pytanie...","Los żołnierza nie jest łatwy, a teraz ty, łajdaku, doprowadzasz mnie do szału...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz o czym rozmawiać."),"Zrozumiano...","Tak, masz rację, już trzeci raz...","Przepraszam...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
