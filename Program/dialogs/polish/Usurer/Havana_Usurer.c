// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś już zadać mi to pytanie niedawno...","Tak, pozwól mi zgadnąć... Znów krążysz w kółko?","Słuchaj, zajmuję się tu finansami, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do omówienia."),"Umph, gdzież to podziała się moja pamięć...","Zgadłeś, przykro mi...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Słuchaj, czy był tutaj człowiek o imieniu Joachim Merriman? Starszy senor, Portugalczyk, z wąsem, bródką i przenikliwym spojrzeniem? Może chciał wziąć pożyczkę?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Obawiam się, że nie mogę ci pomóc, młodzieńcze. Nie mam pojęcia, o kim mówisz.";
			link.l1 = "Rozumiem. Szkoda. Będę kontynuować swoje poszukiwania...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
