// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz?","Czego chciałbyś się dowiedzieć?"),"Czego potrzebujesz, "+GetAddress_Form(NPChar)+"?","To już trzeci raz, gdy próbujesz mnie zapytać...","Mam cię dosyć, zjeżdżaj!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Przepraszam, zmieniłem zdanie.","Nic takiego, przepraszam."),"Zapomniałem, przepraszam...","Do trzech razy sztuka, co? Przepraszam...","Przepraszam, przepraszam! Już wychodzę...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Słuchaj - czy był tu człowiek o imieniu Joachim Merriman? To mężczyzna w średnim wieku, portugalski Señor, z wąsami, cesarską brodą i przenikliwymi oczami? Może wysiadł w zatoczce lub w pobliżu latarni morskiej? Widziałeś kogoś takiego?";
				link.l1.go = "merriman";
			}
		break;
		
		// калеуче
		case "merriman":
			dialog.text = "Nie, kamracie, nie widziałem nikogo takiego jak on. Zauważyłbym.";
			link.l1 = "Rozumiem, co za szkoda. Dziękuję za poświęcony czas, będę kontynuować poszukiwania.";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
