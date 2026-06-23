// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie to pytania, "+GetSexPhrase("młody człowieku","młoda damo")+"?","Czego potrzebujesz, "+GetSexPhrase("przystojniaku","ślicznotko")+"Proszę pytać."),"Znowu pytania","Hee-hee, jeśli to dla ciebie bez różnicy - jakie pytania..."," "+GetSexPhrase("Hm, czemu nie wybierzesz sobie jakiejś piękności? Zaczynam nabierać podejrzeń co do ciebie...","Hm, czemu nie wybierzesz sobie jakiejś piękności? Obawiam się, że nie mamy tutaj chłopców, hi-hi...")+" ","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam.","Właściwie, nieważne."),"Przepraszam, jednak nie mam pytań, do widzenia.","Masz rację, to już trzeci raz. Wybacz mi.","Może następnym razem, Droga Pani.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Słuchaj, Aurora, potrzebuję dziewczyny na noc. I chcę ją zabrać ze sobą do domu. Możesz to zorganizować?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Oczywiście, kochanie. Czy już znalazłeś odpowiednią Panienkę, czy ja mam to zrobić?";
			link.l1 = "Oczywiście, już wybrałem. Mam oko na dziewczynę o imieniu Lucille.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "Czy masz na myśli Lucille Montaigne?";
			link.l1 = "Prawdę mówiąc, nie zapytałem o jej nazwisko. Wiem tylko, że jest młodą, piękną i blondwłosą dziewczyną o imieniu Lucille.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Tak, to ją doskonale opisuje. Dobrze. Ale powiedz mi, czemu właśnie ona? Czy inne dziewczęta ci się nie podobają?";
			link.l1 = "Widzisz... ona dopiero zaczęła tu pracować, więc sądzę, że nie ma jeszcze wystarczającego doświadczenia w 'Rzemiośle', by zbytnio obciążać moją sakiewkę.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "Widzisz, uwielbiam blondynki o jasnej cerze. Lucille idealnie się w tym wpasuje.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (int(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "Teraz Monsieur, to nieprawda! Ona jest młoda, piękna i doświadczona, moi klienci ją podziwiają. Będzie cię kosztować naprawde dużo. Pięć tysięcy pesos za noc z nią, i ani peso mniej.";
				if (int(pchar.money) >= 5000)
				{
					link.l1 = "Dosyć drogo, ale bardzo dobrze. Masz swoją monetę.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "To za drogo! Nie mam tyle. Porozmawiamy później.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "*Westchnienie* Masz rację, Monsieur, jest ładna i młoda, ale brakuje jej doświadczenia. Moi klienci zazwyczaj jej nie zauważają, dlatego zapytałam. Ale jeśli naprawdę lubisz skromne dziewczęta, powiem, że to dobry wybór. Będzie cię kosztować dwa tysiące pięćset pesos.";
				if (int(pchar.money) >= 2500)
				{
					link.l1 = "Cudnie, nada się. Oto twoje monety.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "To za drogo! Nie mam tyle. Porozmawiamy później.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (int(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "Nie byłbyś pierwszy, przystojniaku. Czasami moi klienci ustawiają się w kolejce po jej uwagę, gdyż jest bardzo odmienna od ciemnoskórych córek naszych wysp. Będzie cię kosztować cztery tysiące pięćset pesos.";
				if (int(pchar.money) >= 4500)
				{
					link.l1 = "Drogo, ale bardzo dobrze. Oto twoje monety.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "To za drogo! Nie mam tyle. Porozmawiam z tobą później.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Naprawdę, monsieur? Już tęsknisz za domem? Moje kreolki, a zwłaszcza mulatki, są bardziej namiętne niż ta wyluzowana paryska kocica. Ale cóż, to twój wybór. Kosztować cię to będzie trzy tysiące pesos.";
				if (int(pchar.money) >= 3000)
				{
					link.l1 = "Drogo, ale bardzo dobrze. Oto twoje monety.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "To za drogo! Nie mam tyle. Porozmawiamy później.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -int(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Jak sobie życzysz, drogi. Lucille będzie oczekiwać na ciebie z niecierpliwością o jedenastej wieczorem. Dodatkowo, musi wrócić najpóźniej o siódmej rano. Jeśli nie przybędziesz przed północą, obsłuży innego klienta, a wtedy będziesz musiał poczekać do następnego wieczoru, by ją wziąć.\nI nie myśl nawet o... skrzywdzeniu jej w jakikolwiek sposób, bo tego pożałujesz. Radze nie lekceważyć mojego ostrzeżenia, drogi.";
			link.l1 = "Nie martw się, będe ją traktował jak kochanek, nie jak brutal. Wezmę ją o jedenastej. Co mam robić do tego czasu?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "Cóż, nawet nie wiem, kochanie. Zajrzyj do tawerny, pogadaj z barmanem...";
			link.l1 = "Nie głupi pomysł. Tak właśnie zrobię. Miłego dnia!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
