// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania masz do żołnierza?","Żołnierz ma całe swoje życie zaplanowane - straż, krzątanina... Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Nie powinieneś zawracać głowy żołnierzowi głupimi pytaniami, "+GetAddress_Form(NPChar)+"...","To już trzeci raz dzisiaj, kiedy próbujesz mnie o coś zapytać...","Los żołnierza nie jest łatwy, a teraz ty, łajdaku, doprowadzasz mnie do szaleństwa...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz o czym rozmawiać."),"Zrozumiałem...","Tak, masz rację, to już trzeci raz...","Przepraszam...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Czy imię Juan coś dla ciebie znaczy?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Nie. To wszystko?";
			link.l1 = "Tak. Przepraszam, że cię niepokoję, żołnierzu...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
