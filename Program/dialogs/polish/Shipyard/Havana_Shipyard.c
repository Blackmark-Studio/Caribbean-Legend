// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania masz?","Jak mogę ci pomóc?"),"Chciałeś mi zadać pytanie chwilę temu...","Nie spotkałem nigdy ludzi z taką ciekawością w mojej stoczni ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moim zadaniem jest budować statki. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do omówienia."),"Gdzież to podziała się moja pamięć...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Słuchaj, czy był tu ostatnio człowiek o imieniu Joachim Merriman? Średniego wieku señor, Portugalczyk, z wąsami, bródką cesarską i przenikliwymi oczami? Może chciał kupić statek?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Nie, Señor. Nie widziałem takiego klienta.";
			link.l1 = "Widzę. Szkoda. Będę kontynuować poszukiwania...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
