// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham, o co chodzi?"),"To już drugi raz, kiedy próbujesz zapytać...","To już trzeci raz, gdy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, zajmującym się sprawami kolonii, a ty nadal mi przeszkadzasz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie, przepraszam.","Nie teraz. Złe miejsce i czas."),"To prawda, teraz nie mam nic do powiedzenia, przepraszam.","Zapytam, później.","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
			{
				link.l1 = "Wiem, że Holenderska Kompania Zachodnioindyjska wyznaczyła nagrodę za głowę pewnego pirata - Bartolomeo Portugalczyka. Udało mi się go pojmać. Obecnie znajduje się w mojej ładowni i jestem gotów przekazać go władzom.";
                link.l1.go = "Portugeze";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Już wszystko zabrałeś. Czego jeszcze chcesz?","Czy jest coś, czego jeszcze nie zgarnąłeś?");
            link.l1 = RandPhraseSimple("Po prostu się rozglądam...","Tylko sprawdzam, mogłem zapomnieć czegoś zabrać...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Португалец
		case "Portugeze":
			dialog.text = "Bart Portugalczyk?! Masz go żywego?!";
			link.l1 = "Wiem, że martwy na nic ci się nie przyda. Jest żywy i, niech bogowie mnie potępią, musiałem się powstrzymać, by go takim utrzymać!";
			link.l1.go = "Portugeze_1";
		break;
		
		case "Portugeze_1":
			dialog.text = "Najwspanialej! Teraz powie nam wszystko... Mynheer, przygotuj więźnia do transportu. Natychmiast wyślemy wojskową barkę na twój statek.";
			link.l1 = "Chciałbym najpierw porozmawiać o mojej nagrodzie, Mynheer, jeśli nie masz nic przeciwko.";
			link.l1.go = "Portugeze_2";
		break;
		
		case "Portugeze_2":
			dialog.text = "Nie martw się o swoją nagrodę, Sir. Otrzymasz ją. Wyznaczyliśmy cenę za głowę Bartolomeo Portugalczyka - tysiąc pięćset dublonów. Poruczniku! Przynieś kapitanowi jego nagrodę!";
			link.l1 = "Hm... Hugo powiedział mi, że to było dwa tysiące doublonów... No dobrze.";
			link.l1.go = "Portugeze_3";
		break;
		
		case "Portugeze_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "A teraz, sirze, czy byłbyś tak uprzejmy przekazać Portugalczyka Kompanii? Jesteśmy bardzo chętni, by z nim porozmawiać.";
			link.l1 = "Jasne, Mynheer, wyślij barkę na mój statek.";
			link.l1.go = "Portugeze_4";
		break;
		
		case "Portugeze_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
