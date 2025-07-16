// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Śmiało, czego chcesz?"," Właśnie o tym rozmawialiśmy. Musiałeś zapomnieć... ","To już trzeci raz dzisiaj, kiedy mówisz o jakimś pytaniu...","Słuchaj, to jest sklep. Ludzie tu kupują rzeczy. Nie przeszkadzaj mi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Racja, z jakiegoś powodu zapomniałem...","Tak, to naprawdę już trzeci raz...","Hm, nie będę...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Słuchaj, czy człowiek o imieniu Joachim Merriman kiedykolwiek przychodził tutaj do twojego sklepu? Starszy pan, Portugalczyk, z wąsami, cesarską brodą i przeszywającymi oczami? Może coś kupił?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Nie, żaden z moich klientów nie wygląda tak, jak opisałeś. Poza tym, nigdy wcześniej nie słyszałem tego imienia. Przykro mi, nie mogę ci bardziej pomóc.";
			link.l1 = "Rozumiem. Szkoda. Cóż, będę kontynuować poszukiwania...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
