// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham cię, jakie masz pytanie?"),"To już drugi raz, kiedy próbujesz zapytać...","To już trzeci raz, gdy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracuję nad sprawami kolonii, a ty wciąż mi przeszkadzasz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie teraz. Niewłaściwe miejsce i czas."),"Prawda... Ale później, nie teraz...","Zapytam... Ale trochę później...","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"... ",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "Wasza Ekscelencjo, jestem tu z powodu uwięzionego oficera, Lope Montoro...";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Zabrałeś już wszystko. Czego jeszcze chcesz?","Czy zostało coś, czego nie pochwyciłeś?");
            link.l1 = RandPhraseSimple("Tylko się rozglądam..."," Tylko sprawdzam, mogłem zapomnieć coś zabrać...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "Przeklęci łotrzy! Śmiecie atakować Hawanę?! Czego chcecie?!";
			link.l1 = "Pomyśl trochę, zrozumiesz.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "Złoto, oczywiście! Czym innym moglibyście się, łotry, interesować, jeśli nie złotem?! A my go nie mamy... Tylko kilka miar w magazynie.";
			link.l1 = "Ha-ha... Nie, nie interesuje nas złoto. Przybyliśmy tu po kość słoniową... tę czarną. Rozumiesz mnie?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "Ha! Podejrzewałem, że przybyłeś tutaj po niewolników. Ale oni znajdują się w fortecy. Nasze posiłki już tu nadciągają i twoja banda zostanie zniszczona w mgnieniu oka.";
				link.l1 = "Cholera! Dobra, siedź tutaj i się nie ruszaj... Wynośmy się stąd! Kurwa...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "Ale jak... Jak się o tym dowiedziałeś?";
				link.l1 = "Ha! Tylko idiota mógłby zebrać 5000 niewolników w jednym miejscu i mieć nadzieję, że nikt się nie dowie. Śmierdzą aż do cholerniej Tortugi... Mam nadzieję, że rozumiesz, że zabieramy ich od ciebie.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "Dobrze, i tak wygrałeś, musimy poddać się twojej przemocy. Ale nie licz na to, że unikniesz sprawiedliwości po tym rabunku i zatopieniu dwóch hiszpańskich okrętów wojennych.";
			link.l1 = "Nie nadym się tak, bo dostaniesz zawału. Siądź tutaj i nie ruszaj się...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдёт
            Log_SetStringToLog("Slaves have been put onto your ship");
			Log_SetStringToLog("You've got 30 days to deliver the slaves to your employer");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "Mtraxx":
            dialog.text = "Jakie to ciekawe... kolejne skargi?";
			link.l1 = "Nie, nie, wręcz przeciwnie, Wasza Ekscelencjo. Lope to stary przyjaciel z armii, walczyliśmy razem w Europie... Chciałbym mu pomóc i przyszedłem prosić o Waszą pomoc.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_1":
            dialog.text = "Hm.. Cóż, zakładam, że skoro przyszedłeś do mnie, to już znasz tę... absurdalną historię?";
			link.l1 = "Tak, Wasza Ekscelencjo.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Proponuję skontaktować się z donem Rosario Gusmanem. On, podobnie jak ty, chce pomóc donowi Lope Montero. Próbował nawiązać kontakt z ofiarą, jednak negocjacje nie przyniosły owoców. Spotkaj się z nim, wyjaśni szczegóły. Możesz znaleźć dona Rosario na ulicach od czwartej do ósmej po południu. Codziennie dokonuje pełnej inspekcji posterunków straży miejskiej.";
			link.l1 = "Dziękuję, Wasza Ekscelencjo!";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_7";
			AddQuestRecord("Roger_1", "17");
			Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
