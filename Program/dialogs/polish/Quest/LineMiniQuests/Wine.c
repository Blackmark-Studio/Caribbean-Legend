void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "To jest błąd. Poinformuj o tym deweloperów.";
			link.l1 = "Pewnie!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "Przyniosłeś butelkę?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Tak. Zapłaciłem 700 pesos, więc oczekuję od ciebie 1000 pesos.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "Nie, pracuję nad tym.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "Chwała Bogu, już zaschło mi w gardle. Dziękuję uprzejmie, panie! Tu masz swoje tysiąc, a ja wezmę twoją butelkę, haha! Hej, skoro już robimy tu taki dobry interes, mam dla ciebie kolejną prośbę\nCzy mógłbyś zdobyć dla mnie i moich przyjaciół więcej wina na nasz... przyszły użytek? Właśnie obrobiliśmy bandę przemytników, więc mamy trochę grosza do wydania, hehe...";
			link.l1 = "Przykro mi, żołnierzu, nie mam czasu na kolejną wyprawę po gorzałę dla ciebie.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "Pieniądze zawsze się przydadzą. Ile butelek potrzebujesz?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "Jak sobie życzysz. Dzięki za pomoc mimo wszystko! Na zdrowie i na twoje zdrowie!";
			link.l1 = "Rób dalej dobrą robotę, żołnierzu!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "Przy cenie 1000 pesos za butelkę, możemy sobie pozwolić na zakup sześćdziesięciu butelek, ale nie więcej. Ale też nie przynoś nam mniej niż dziesięć - to tylko sprawi, że będziemy spragnieni!";
			link.l1 = "Zrozumiano, nie więcej niż 60 butelek i nie mniej niż dziesięć. Przywiozę twoje wino.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Błogosławione są stopy, które niosą radosne wieści o dobrym trunku! Liczę na ciebie, kapitanie. Ach, prawie zapomniałem! Musisz dostarczyć alkohol tutaj w ciągu tygodnia, bo moja kompania morska za siedem dni zostanie przeniesiona do floty i wyjedziemy na kilka miesięcy.";
			link.l1 = "Rozumiem. Postaram się być szybki.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
	
		case "Wine_fort_check":
			dialog.text = "Więc, kapitanie, czy przyniosłeś wino?";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Tak, mam.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "Nie. Wciąż nad tym pracuję.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "Święty Arnulfie módl się za nami! Toż to mnóstwo wina! Doskonale! Niestety, jak już mówiłem, możemy sobie pozwolić tylko na sześćdziesiąt butelek, niestety nie mamy wystarczająco pieniędzy, by kupić więcej. Weź swoje pesos, a ja dobrze się zatroszczę o te sześćdziesiąt butelek. Proszę, zatrzymaj resztę.";
				link.l1 = "Dziękuję. Upewnij się, że ty i twoi żołnierze wzniesiecie toast za moje zdrowie!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Witaj z powrotem. Zobaczmy... Przyniosłeś "+sti(pchar.questTemp.Wine.Qty)+" butelek. Ładnie! Wezmę je. Zapłata wynosi "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "Dziękuję. Upewnij się, że ty i twoi żołnierze wzniesiecie toast za moje zdrowie!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "Z pewnością tak, "+GetAddress_Form(NPChar)+" ! Bęben wzywa do zbiórki, muszę teraz iść. Żegnaj!";
			link.l1 = "Pomyslnych wiatrów i spokojnych mórz, kamracie!";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("Przekazałeś wino");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
