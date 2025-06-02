// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Śmiało, czego chcesz?"," Właśnie o tym rozmawialiśmy. Musiałeś zapomnieć...","To już trzeci raz dzisiaj, kiedy mówisz o jakimś pytaniu...","Słuchaj, to jest sklep. Ludzie tu kupują rzeczy. Nie przeszkadzaj mi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Racja, z jakiegoś powodu zapomniałem...","Tak, to naprawdę już trzeci raz...","Hm, nie będę...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "Słuchaj, potrzebuję eleganckich ubrań. Drogich, chcę wyglądać jak prawdziwy szlachcic. Masz coś w tym guście?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "Galeron o nazwie 'Admirable' przywiózł ci niedawno ładunek skór. Czy to pamiętasz?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "Szlacheckie ubranie? Jasne, mam tu zestaw: spodnie, kaftan, jedwabną koszulę i buty. Kosztuje to 20 000 pesos. Ubranie jest bardzo wysokiej jakości, wygodne i ma niezwykły wygląd, więc nie wezmę za nie mniej.";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "Świetnie! Daj to tutaj.";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "Hm... W tej chwili nie mam tyle pieniędzy.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "Wróć, gdy będziesz miał pieniądze.";
			link.l1 = "W porządku. Wrócę!";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("You've received expensive clothing");
			PlaySound("interface\important_item.wav");
			dialog.text = "Oto jesteś.";
			link.l1 = "Dziękuję!";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "Tak. Przybył na czas, rozładował towar, a ja zapłaciłem za niego zgodnie z umową. Dlaczego pytasz?";
			link.l1 = "Kapitanem tamtego statku jest Gaius Marchais, mój stary znajomy. Więc próbuję go znaleźć. Czy mógłbyś mi powiedzieć, co zrobił potem? Może dostarczałeś mu dodatkowy ładunek albo wspomniał, dokąd miał się udać?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Nothing of that. I didn't offer him any freight; he didn't even ask for it. He didn't share his plans for the future with me. I don't even remember all the details, do you know how many people have come in and out of here since that time? He unloaded and sailed off and that's all I can say about him.";
			link.l1 = "Dobrze. W każdym razie, dzięki. Wszystkiego najlepszego!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
