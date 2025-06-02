void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Nie mamy o czym rozmawiać.";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem tego miasta i proszę cię, schowaj swoją szablę.","Słuchaj, jestem obywatelem tego miasta i proszę cię, abyś opuścił swoją klingę.");
				link.l1 = LinkRandPhrase("Dobrze.","Z pewnością.","Dobrze...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, "+GetSexPhrase("kamracie","dziewczyno")+", biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy "+GetSexPhrase("facet","kobieta")+" idzie przede mną z gotową bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Rozumiem.","Łapie.");
			}
			
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "Chodź, kumplu, pokaż mi swoje kieszenie.";
			link.l1 = "Co?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "Słyszałeś mnie. Szybko, mniej gadania. Nie lubię rozmawiać...";
			link.l1 = "Do diabła! A czy "+pchar.questTemp.different.FackWaitress.Name+" pracuje z tobą?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "Jasne, że pracuje... a teraz daj mi swoje pieniądze, albo cię wypatroszę!";
			link.l1 = "Nie! To ja ciebie wypatrosze!";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "Bierz moje monety, łajdaku! Ale nie uciekniesz od tego...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "Jasne, nie ma co się z tym kłócić. Żegnaj, druh. I pamiętaj, nie jesteś aż tak przystojny, by rozmiękczyć kelnerki. Następnym razem bądź mądrzejszy!";
			link.l1 = "...Idź już.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "Zła decyzja.";
			link.l1 = "Dla ciebie jak najbardziej.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "Oto jestem! Chcesz mnie, przystojniaku?";
			link.l1 = "Cholera, to się szybko rozkręciło...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "Nie traćmy czasu!";
			link.l1 = " Heh, nie mógłbym się bardziej zgodzić! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "Dzień dobry. Nazywam się "+GetFullName(npchar)+". Jestem kapitanem "+GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName+"Acc"))+" '"+npchar.Ship.name+" '."; 
			link.l1 = "Znakomicie! Nareszcie cię znalazłem.";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "Znalazłeś mnie?!";
			link.l1 = "Tak. Cóż, przyniosłem twój dziennik pokładowy, który zapomniałeś w biurze portowym "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Kapitan")+".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "Do diabła! Teraz rozumiem, gdzie to zgubiłem. Ta strata prawie sprowokowała bunt na moim statku...";
			link.l1 = "Wszystko dobre, co się dobrze kończy. Weź swój dziennik pokładowy i porozmawiajmy o moich pieniądzach.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Świetne wyczucie czasu, jeszcze nie zacząłem nowego, więc zapłacę ci tyle, ile będę mógł. "+FindRussianMoneyString(sti(npchar.quest.money))+" i przyjmij kilka sztuk mojej prywatnej biżuterii.";
				link.l1 = "Miło. Weź to.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Hm, wiesz, już zacząłem nowy dziennik okrętowy. Niemniej jednak, stary wciąż ma dla mnie wartość. Więc zapłacę ci "+FindRussianMoneyString(sti(npchar.quest.money))+" i przyjmij kilka sztuk mojej prywatnej biżuterii.";
					link.l1 = "Zgoda zatem. Weź swój dziennik.";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "Już zacząłem nowy dziennik pokładowy. I przeniosłem wszystkie notatki ze starego. Nie potrzebuję go już, więc nie ma dla ciebie pieniędzy.";
					link.l1 = "Wspaniale. Więc cały ten pościg był na nic.";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "Dziękuję. Żegnaj, "+GetSexPhrase("kumplu","dziewczyno")+".";
			link.l1 = " Nawzajem...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "Ha, następnym razem popracuj nad wyczuciem czasu.";
			link.l1 = "Dość prawdziwe.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "Pozdrawiam cię na pokładzie mojego statku. Szczerze mówiąc, przestraszyłeś mnie na śmierć - myślałem, że Jednooki Łowca Rumaków mnie ściga...";
				link.l1 = "Nie, kapitanie, dziś mam dobry humor. Jestem tu, aby ci pomóc.";
			}
			else
			{
				dialog.text = "Witam cię na pokładzie mojego statku!";
				link.l1 = "Ahoy, kapitanie! Szukałem cię.";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "Dlaczego?";
			link.l1 = "Zapomniałeś swojego dziennika w portowej administracji "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Cholera jasna, więc to było to miejsce! Ta strata już narobiła mi mnóstwo kłopotów.";
				link.l1 = "Co powiesz na nagrodę?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Cholera, teraz widzę, gdzie go zgubiłem! Dziękuję, ale szukałeś mnie za długo. Już zacząłem nowy dziennik pokładowy. Niemniej jednak stare notatki wciąż muszą być przeniesione do nowego...";
					link.l1 = "Ile to kosztuje?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "Już zacząłem nowy dziennik. I przeniosłem wszystkie notatki ze starego. Nie potrzebuję go już więcej.";
					link.l1 = "Więc nie potrzebujesz starego dziennika? Naprawdę?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "Mogę ci zapłacić "+FindRussianMoneyString(sti(npchar.quest.money))+" i trochę moich klejnotów. To wszystko, na co mnie stać.";
			link.l1 = "Zgoda. Weź swój dziennik.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "Dzięki jeszcze raz. Żegnaj, kolego.";
			link.l1 = "Trzymaj się.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "To pewne. Jeśli kogoś gonisz, musisz być szybszy.";
			link.l1 = "Nie zgub swoich dzienników pokładowych na samym początku. Dobrze.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(100/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "Miałem nadzieję, że wszystko już ustaliliśmy.";
			link.l1 = "Tak, to prawda.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "Witaj. Czego chcesz?";
			link.l1 = "To nic, po prostu chciałem usłyszeć jakieś nowiny. Masz coś na sprzedaż?";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "Nie mam nic do sprzedania ani żadnych nowin. A tak przy okazji, twoja obecność tutaj jest niepożądana. Czy jestem jasny?";
			link.l1 = "Jesteś... a z resztą... żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "Powiedziałem ci, że nie masz tu nic do roboty!";
			link.l1 = "Widzę...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = " Dlaczego mnie zaatakowałeś, ty korsarzu?!";
			link.l1 = "Muszę zwrócić statek jego właścicielowi.";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "Jakiemu właścicielowi? Ja jestem właścicielem!";
			link.l1 = "Nie, nie jesteś. Nie wiem, kto jest prawdziwym właścicielem tego statku. Ale został skradziony i muszę go zwrócić.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "Cholera! Ale to jeszcze nie koniec dla mnie. Przynajmniej spróbuję cię zabić...";
			link.l1 = "Próbowanie to wszystko, co możesz zrobić.";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------поисковый генератор горожан--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "SCQ_exit":
			DialogExit();
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_exit_clear":
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		
//--------------------------------------------поисковые квесты дворян---------------------------------------------
		
		case "SCQ_Nobleman":
			dialog.text = "Pozdrawiam cie, "+GetAddress_Form(NPChar)+"Widzę, że jesteś kapitanem własnego statku? Nazywam się "+GetFullName(npchar)+" i chcę ci zaproponować interes.";
			link.l1 = RandPhraseSimple("Przepraszam bardzo, ale muszę iść.","Tak mi przykro, ale nie mam czasu, by z tobą rozmawiać.");
			link.l1.go = "SCQ_exit";
			link.l2 = "Zamieniam się w słuch.";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "Słuchaj więc. "+SelectNB_battleText()+"\nNie mam ani czasu, ani szansy, by go znaleźć. Bo nigdy się tu nie pojawia. Domyślam się, że teraz to widzisz, widzisz co zamierzam ci zaproponować?";
						link.l1 = LinkRandPhrase("Przypuszczam, że muszę kogoś odnaleźć i przyprowadzić go do ciebie?","Może, znaleźć drania i przyprowadzić go do ciebie?","Chcesz, żebym znalazł tego człowieka i przyprowadził go tutaj?");
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "Słuchaj zatem."+SelectNB_battleText()+"\nNie mam ani czasu, ani sposobności, aby go znaleźć. Bo on nigdy się tu nie pojawia. Domyślam się, że teraz to widzisz, widzisz, co zamierzam ci zaproponować?";
						link.l1 = LinkRandPhrase("Przypuszczam, że chcesz, abym kogoś odnalazł i przyprowadził go do ciebie?","Może, znaleźć drania i przyprowadzić go do ciebie?","Chcesz, żebym znalazł tego człowieka i przyprowadził go tutaj?");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = "Słuchaj zatem. Właściwie, "+npchar.quest.text+" służy w marynarce jako kapitan. Nawet nie wie, że ja też tu jestem!\nChciałbym się z nim spotkać, lecz nie mam ani czasu, ani możliwości, by go znaleźć...";
					link.l1 = "Rozumiem, że chcesz, abym znalazł tego kapitana i powiedział mu o tobie?";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //вариант А
			dialog.text = "Nie całkiem tak. Znajdź go, ale nie ma potrzeby go tu przyprowadzać. Zabij go i to wystarczy. Zatop go z jego plugawym statkiem, zastrzel go, przebij go swoim ostrzem - nie obchodzi mnie to, po prostu spraw, by ten drań przestał zatruwać ten świat swoją obecnością. Nagroda będzie hojna.";
			link.l1 = "Ha! To proste. Powiedz mi jego imię i nazwę jego statku.";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			dialog.text = ""+npchar.quest.SeekCap.capName+" z "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nazwany "+npchar.quest.SeekCap.shipName+"  Jest częstym gościem w porcie  "+XI_ConvertString("Colony"+npchar.quest.Qcity)+"Zapłacę ci "+FindRussianMoneyString(sti(npchar.quest.money))+" w złotych dublonach.";
			link.l1 = "To wszystko, co muszę wiedzieć. Będę czujny na morzu. A gdy znajdę twojego przyjaciela, sprawię, że będzie... 'zniżając głos' ...nie całkiem żywy.";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "To nie wystarczy na taką robotę.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "Cieszę się, że doszliśmy do porozumienia. Będę czekać na twój powrót.";
			link.l1 = "Gdzie będę mógł cię znaleźć? Wyjaśnijmy to teraz, nie chcę tracić czasu na szukanie ciebie.";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "Każdego ranka uczestniczę w nabożeństwie w lokalnym kościele. Możesz mnie tam znaleźć codziennie od 8 do 9 rano.";
			link.l1 = "Zgoda! Spodziewaj się wkrótce rezultatów.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_prisoner": //вариант В
			dialog.text = "Dokładnie. Znajdź go i przyprowadź do mnie. Żywego. Chcę się z nim rozprawić osobiście. Hojnie cię wynagrodzę.";
			link.l1 = "Cóż, mogę spróbować go znaleźć, ale potrzebuję szczegółów.";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "Imię tego bękarta to "+npchar.quest.SeekCap.name+". Służy na "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nazwany "+npchar.quest.SeekCap.shipName+", która jest pod dowództwem "+npchar.quest.SeekCap.capName+". Statek często można zobaczyć w porcie "+XI_ConvertString("Colony"+npchar.quest.Qcity)+"Zapłacę ci za tę robotę "+FindRussianMoneyString(sti(npchar.quest.money))+" w złotych dublonach.";
			link.l1 = "To dla mnie wystarczy. Będę czujny na otwartym morzu.";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "To za mało na taką robotę.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "Cieszę się, że zawarliśmy umowę. Będę czekał na twój powrót.";
			link.l1 = "Gdzie będę mógł cię znaleźć? Wyjaśnijmy to teraz, nie chcę tracić czasu na szukanie ciebie.";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "Każdego ranka uczestniczę w nabożeństwie w lokalnym kościele. Możesz mnie tam znaleźć codziennie od 8 do 9 rano.";
			link.l1 = "Zgoda! Wkrótce spodziewaj się wyniku.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_peace": //вариант С
			dialog.text = "Dokładnie! Znajdź go i powiedz mu, że mieszkam w tym mieście. Zapłacę za twoje usługi.";
			link.l1 = "Cóż... Mogę spróbować. Opowiedz mi szczegóły.";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = "Jego imię to "+npchar.quest.SeekCap.capName+". I służy na "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" "+npchar.quest.SeekCap.shipName+"'. Często odwiedza "+XI_ConvertString("Colony"+npchar.quest.Qcity)+"Zapłacę ci za tę robotę "+FindRussianMoneyString(sti(npchar.quest.money))+" w złotych dublonach.";
			link.l1 = "Zgoda! Przypuszczam, że wkrótce znajdę twojego przyjaciela.";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "To dla mnie za mało.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "Cieszę się, że zawarliśmy umowę. Będę oczekiwał twojego powrotu.";
			link.l1 = "Gdzie będę mógł cię znaleźć? Wyjaśnijmy to teraz, nie chcę tracić czasu na szukanie ciebie.";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "Zawsze chodzę na wieczorne nabożeństwo w lokalnym kościele. Możesz mnie tam znaleźć codziennie od 18 do 20.";
			link.l1 = "Zgoda zatem! Spodziewaj się wkrótce rezultatów.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		//--> разговор на суше, вариант А
		case "NM_battleCap":
			dialog.text = "I co? Czego pan chce?";
			link.l1 = "Czy jesteś kapitanem "+GetFullName(npchar)+"?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "Tak, jestem. O co chodzi?";
			link.l1 = "Jeden człowiek ma wielkie zainteresowanie tobą, jego imię to "+GetFullName(&characters[GetCharacterIndex("ZadanieObywatela_"+npchar.quest.cribCity)])+"Pamiętasz?";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "Słyszałem, że masz dużo mahoniu w ładowni. Chcę go kupić. Sprzedasz mi go?";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "To pierwszy raz, kiedy słyszę to imię. Musiałeś się pomylić, kapitanie. Skończyliśmy?";
			link.l1 = "Hm. Dobrze, wybacz mi...";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "„Doprawdy? Ale on pamięta cię całkiem dobrze. Wspomniał o twoim długu wobec niego...”";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "Jaki dług? O czym ty mówisz?";
			link.l1 = "Dług honorowy!";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "Jesteś w błędzie. Nie handluję drewnem. Czy skończyliśmy?";
			link.l1 = "Hm. Dobrze, przepraszam...";
			link.l1.go = "NM_battleCap_exit";
		break;
		
		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;
		
		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант В
		case "NM_prisonerCap":
			dialog.text = "I? Czego chcesz, panie?";
			link.l1 = "Czy jesteś kapitanem "+GetFullName(npchar)+"?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Tak, to ja. Jaki interes?";
			link.l1 = "Czy człowiek o imieniu "+sld.quest.SeekCap.name+" służyć pod twoim dowództwem?";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Tak. On jest jednym z moich oficerów. Teraz powiedz mi, dlaczego pytasz?";
			link.l1 = "Jasne, powiem ci. Szukam tego człowieka na rozkaz władz "+XI_ConvertString("Colony"+sld.city+"Generał")+", a ja mam prawo go aresztować i dostarczyć do "+XI_ConvertString("Colony"+sld.city)+" Proszę cię o pomoc w tej sprawie, abyśmy mogli rozwiązać ją pokojowo.";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "Naprawdę? I taki człowiek służy w mojej załodze? Jesteś poważny?";
				link.l1 = "Nie zawracaj sobie tym głowy, "+GetAddress_FormToNPC(NPChar)+". Wyślę szalupę na twój statek i sami go zabierzemy.";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "Nie mów! Wiesz co, panie, nie obchodzi mnie jego przeszłość. To mnie nie dotyczy. A kim ty w ogóle jesteś? Władze? Naprawdę? Ha! Nie wydaję moich ludzi ani tobie, ani nikomu innemu. Ta rozmowa jest skończona. Wynocha!";
				link.l1 = "Zły wybór... Straszny!";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "Rób, co musisz zrobić.";
			link.l1 = "Już się robi.";
			link.l1.go = "NM_prisonerCap_good_1";
		break;
		
		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_"+(rand(9)+21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(sld.quest.SeekCap.name+" is under arrest");
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
		break;
		
		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "NM_prisonerDeck_exit":
			dialog.text = "Zrobione, kapitanie?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = "Dzień dobry. Czego sobie życzysz, kapitanie?";
			link.l1 = "Jesteś kapitanem "+GetFullName(npchar)+", czy mam rację?";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = "Masz rację. Masz coś dla mnie?";
			link.l1 = "Mam. Człowiek imieniem "+GetFullName(sld)+" szuka ciebie. Chce, żebyś go odwiedził jak najszybciej. Mieszka w "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+".";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "Ha! Więc on też przeniósł się do Nowego Świata? W takim razie naprawdę powinienem go odwiedzić... Dzięki za informację, panie!";
			link.l1 = "Nie ma za co. Moja praca zostanie opłacona przez twego przyjaciela. Powodzenia, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "NM_peaceCap_3";
		break;
		
		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		
		case "NM_peaceCap_exit":
			dialog.text = "To była przyjemność, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "Przyjemność była po mojej stronie, kapitanie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = "Ahoy, "+GetAddress_Form(NPChar)+"  Czego chcesz?";
			link.l1 = "Słyszałem, że masz dużo czerwonego drewna w swoim ładunku i chcę je kupić. Czy je sprzedasz?";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "Jesteś w błędzie. Nie handluję drewnem, a twoja wizyta tutaj wydaje mi się dość podejrzana. Myślę, że lepiej będzie, jeśli opuścisz mój statek!";
			link.l1 = "W porządku, tylko pytałem. Żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "Chcesz kłopotów, panie? Powinienem powtórzyć?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = " Dlaczego zaatakowałeś mój statek, łajdaku?";
			link.l1 = "Przychodzę, by przekazać ci najlepsze pozdrowienia od "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" , od człowieka zwanego "+GetFullName(&characters[GetCharacterIndex("ZadanieObywatela_"+npchar.quest.cribCity)])+" Mam nadzieję, że teraz rozumiesz sytuację.";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "Niemożliwe! Nic do stracenia dla mnie wtedy...";
			link.l1 = "Jak tam twoje życie?";
			link.l1.go = "NM_battleBoard_2";
		break;
		
		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		 //--> абордаж, вариант В
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];//квестодатель
			dialog.text = "Czemu zaatakowałeś mój statek, łotrze?";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "Masz jakieś pomysły? Poprosiłem cię, abyś oddał mi swojego oficera po dobroci. Teraz biorę jego, ciebie i twój kocioł!";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "Pod twoim dowództwem służy jeden łotr. Jego imię to "+sld.quest.SeekCap.name+". Władze "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" są naprawdę chętni, aby go zobaczyć. Zostanie aresztowany i umieszczony w moim ładowni.";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "I dlatego dokonałeś rzezi na moim statku? Drań! Wciąż mam trochę siły... Zabiję cię!";
			link.l1 = "Silniejsi mężczyźni próbowali...";
			link.l1.go = "NM_prisonerBoard_2";
		break;
		
		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завершения квеста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+21); //модель для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;
		
		//--> результаты квестов дворян
		case "SCQ_NM_result":
			dialog.text = "Co powiesz, kapitanie? Masz jakieś postępy w mojej sprawie?";
			link.l1 = "Jeszcze nie. Ale pracuję nad tym.";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = "Co powiesz, kapitanie? Czy masz jakieś postępy w mojej sprawie?";
					link.l1 = "Tak. I to ci się spodoba."+npchar.quest.SeekCap.capName+"jest martwy, a jego "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" jest na dnie morza.";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = "Co powiesz, kapitanie? Masz jakieś postępy w mojej sprawie?";
					link.l1 = "Tak. I polubisz to."+npchar.quest.SeekCap.Name+" siedzi w kabinie mojego statku pod aresztem.";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = "Aha, oto jesteś. Cieszę się, że cię widzę. Zostałem poinformowany, że udało ci się w twojej misji!";
					link.l1 = "Czy twój przyjaciel cię odwiedził?";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "Wspaniale! Wiedziałem, że mogę na ciebie liczyć. Oto twoje złoto. Zasłużyłeś na nie.";
			link.l1 = "Dzięki. Porozmawiaj ze mną ponownie, jeśli trafisz na kolejnego wroga.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "SCQ_NM_result_B1":
			dialog.text = "Wspaniale! Zaraz każę moim ludziom zdjąć go z twojego statku. Teraz już mu się nie wymknie! Oto twoje złoto. Zasłużyłeś na nie.";
			link.l1 = "Dzięki. Zwracaj się do mnie, gdy potrzeba roboty tego rodzaju.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		break;
		
		case "SCQ_NM_result_C1":
			dialog.text = "Tak, był tutaj i opowiedział mi o tobie. Proszę, weź swoje złoto. Zasłużyłeś na nie.";
			link.l1 = "Mam wdzięczność. Żegnaj, panie!";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
//<-- поисковые квесты дворян

		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("Pozdrowienia, kapitanie. Chciałbym prosić o twoją pomoc.","Kapitanie! Czy możesz mi pomóc? Proszę.","Kapitanie, proszę o twoją pomoc!");
			link.l1 = RandPhraseSimple("Jestem zajęty.","Śpieszę się.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Co się stało?","Powiedz, co cię trapi. Być może będę w stanie ci pomóc.");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Rok temu jeden kapitan obiecał mnie zabrać do "+XI_ConvertString("Colony"+SelectNotEnemyColony(NPChar)+"Przyjęto")+". Ale gdy byłem na jego statku, wrzucono mnie do ładowni, a potem sprzedano do niewoli. Ledwo udało mi się przetrwać. Kilkakrotnie byłem bliski śmierci... W każdym razie chcę przypomnieć mojemu 'przyjacielowi', że wciąż żyję."; // belamour gen
					link.l1 = "Co masz na myśli? Powiedz mi dokładnie, czego chcesz.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "Moja żona została porwana. Jeden kapitan, pirat jak mówią, zalecał się do niej. Moja żona musiała pozostawać w domu przez dni z powodu jego prześladowań. Próbowałem nakłonić władze miasta do pomocy, ale bezskutecznie. A teraz...";
					link.l1 = "Co teraz?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "Wiesz, szukam mego krajana. Trzy lata temu przybyliśmy tu razem z Europy, aby znaleźć lepsze życie. Zgubiliśmy się nawzajem. Ale niedawno słyszałem, że teraz jest kapitanem handlowym! Próbowałem go znaleźć sam, lecz nie udało się.";
					link.l1 = "Więc?";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "Chcę, żebyś go znalazł i zabił. Chcę, żeby był martwy tak bardzo, że nawet nie mogę jeść...";
			link.l1 = "Widzę... Przypuszczam, że mogę ci w tym pomóc. Powiedz mi jego imię i nazwę jego statku.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "Przykro mi, ale nie jestem zainteresowany.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = ""+npchar.quest.SeekCap.capName+" z "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nazwany "+npchar.quest.SeekCap.shipName+" Zapłacę ci  "+FindRussianMoneyString(sti(npchar.quest.money))+", plus wszystkie moje klejnoty."; // belamour gen
			link.l1 = "Widzę. Będę czujny na morzu. Jeśli znajdę cel... Uważaj go za martwego wtedy.";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "Nie zrobię nic za takie pieniądze. Znajdź innego głupca, który dokona twojej zemsty.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "To właśnie chciałem usłyszeć! Oh, teraz mogę jeść! W końcu! Muszę zdobyć coś do jedzenia...";
			link.l1 = "Smacznego. Znajdę cię, gdy robota będzie skończona.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "Będę na ciebie czekał w lokalnym kościele.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "Byłem zbyt leniwy, a drań złapał moją żonę i zabrał ją na swój statek. Proszę cię, znajdź tego łotra!";
			link.l1 = "Hm, i czemu miałbym walczyć z innym łajdakiem?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "Nie jestem bogaty, ale z przyjemnością oddam ci wszystkie moje kosztowności! Jeśli uwolnisz moją żonę i przyprowadzisz ją do mnie, zapłacę ci "+FindRussianMoneyString(sti(npchar.quest.money))+", plus wszystkie moje klejnoty.";
			link.l1 = "Zgoda, wchodzę w to. Powiedz mi szczegóły. Jego imię, jego statek i jak się nazywa twoja żona.";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "Nie, kumpel, nie chcę tego robić za taką małą sumę. Przykro mi...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "Jej imię to "+npchar.quest.SeekCap.name+". A imię tego bękarta to "+npchar.quest.SeekCap.capName+", on pływa dalej "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Okaleczenie"))+" nazwany "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Gówno pływa, kumplu. Kapitanowie żeglują...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "Tak, tak, bardzo przepraszam! Nie jestem żeglarzem, mam nadzieję, że to zrozumiesz...";
			link.l1 = "To w porządku, nie martw się. Nieważne, wrócę, jak tylko to będzie zrobione.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "Dziękuję bardzo! Będę czekał na ciebie w lokalnym kościele. Ale błagam cię, pośpiesz się. Naprawdę martwię się o moją żonę...";
			link.l1 = "Tak, też jej nie zazdroszczę.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "Problem w tym, że mój przyjaciel nie ma żadnej posiadłości. Jego statek to jego dom. Więc nie mogę go znaleźć, bo zawsze jest na morzu. A mnie nie stać na bezużyteczne podróże, muszę zarabiać na życie.";
			link.l1 = "Nie mogę ci pomóc, jeśli nie masz pieniędzy...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Mogę ci zapłacić "+FindRussianMoneyString(sti(npchar.quest.money))+" a dam ci wszystkie moje klejnoty. To wszystko, na co mnie teraz stać.";
			link.l1 = "Ta suma mi pasuje. Wchodzę w to. Właściwie możesz dołączyć do mnie jako pasażer, więc zobaczysz swojego przyjaciela, jak tylko go znajdziemy.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "To dla mnie za mało. Poszukaj kogoś innego, kto to zrobi.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "Nie, przypuszczam, że zostanę tutaj. Nie wiemy, jak długo potrwają te przeszukiwania i mogę stracić wszystkie swoje pieniądze. Mam tu pracę.";
			link.l1 = "Rozumiem. Teraz powiedz mi, kim jest twój przyjaciel i na jakim statku się znajduje.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "Jego imię to "+npchar.quest.SeekCap.capName+"Z tego co wiem, dowodzi "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Acc"))+" nazwany "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Rozumiem. Cóż, powiem twojemu przyjacielowi o tobie, jeśli go zobaczę.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "Dziękuję. Będę czekał na twój przybycie w miejscowym kościele. Dostaniesz swoje monety, gdy robota będzie skończona.";
			link.l1 = "Pewnie. Żegnaj zatem, wkrótce spodziewaj się wyników.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "Dzień dobry, kapitanie. Masz już jakieś wyniki?";
			link.l1 = "Przypomnij mi swój problem...";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "Rozumiem, że pomściłem. Czy tak jest?";
					link.l1 = "Dokładnie. "+npchar.quest.SeekCap.capName+" nie żyje, a jego "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" jest na dnie morza.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "Znalazłeś moją żonę! Nie mogę w to uwierzyć! Czy mogę?";
					link.l1 = "Możesz. Ona jest moją pasażerką. Możesz ją zabrać z powrotem, jeśli "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+" naprawdę jest twoją żoną...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "Dzień dobry, kapitanie. Czy znalazłeś mojego towarzysza?";
					link.l1 = "Opowiedziałem mu o tobie.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Co? Naprawdę zapomniałeś, że prosiłem cię o pomszczenie kapitana "+npchar.quest.SeekCap.capName+" za rok mojej niewoli?";
					link.l1 = "Nie, nie mam.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "Nie mogę uwierzyć własnym uszom! Zapomniałeś, że prosiłem cię o odnalezienie i uwolnienie mojej żony? Została pojmana przez pirata o imieniu "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Nie mam.";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "Poczekaj chwilę... Zapomniałeś o swojej obietnicy znalezienia mojego znajomego o imieniu "+npchar.quest.SeekCap.capName+"?";
					link.l1 = "Nie mam.";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "Doskonale, miałem co do ciebie rację! Zatem, jak ci obiecałem, oto twoje "+FindRussianMoneyString(sti(npchar.quest.money))+" i klejnoty. Dzięki za twoją pomoc.";
			link.l1 = "Proszę bardzo...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "O mój Boże! Uratowałeś nas! Proszę, weź swoje "+FindRussianMoneyString(sti(npchar.quest.money))+" i klejnoty. I wiedz, że będziemy modlić się za ciebie na wieki!";
			link.l1 = "Módl się, jeśli chcesz. Nie mam z tym problemu.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "Wspaniale!... Proszę, weź "+FindRussianMoneyString(sti(npchar.quest.money))+" i klejnoty. I dziękuję, kapitanie.";
			link.l1 = "Jesteś mile widziany, przyjacielu. Żegnaj...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("Witaj, kapitanie. Czy możesz mi pomóc?","Kapitanie! Czy możesz pomóc kobiecie? Byłbyś tak uprzejmy...","Kapitana, pomocy "+GetSexPhrase("dziewczyna","ja")+".");
			link.l1 = RandPhraseSimple("Jestem zajęty.","Przepraszam, "+GetAddress_FormToNPC(NPChar)+", ale nie mam żadnego czasu do stracenia...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Jaki masz problem, "+GetAddress_FormToNPC(NPChar)+"?","Powiedz, co cię trapi, "+GetAddress_FormToNPC(NPChar)+"  Spróbuję ci pomóc.");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Mój mąż jest kupcem, dostarcza towary do każdej kolonii w okolicy. Trzy miesiące temu wypłynął na morze. Jeszcze nie wrócił!";
					link.l1 = "Czy myślisz, że coś mu się stało?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+GetSexPhrase("Kapitanku, widzę, że jesteś odważnym kapitanem, doskonałym łajdakiem","Kapitanko, widzę, że jesteś silną kobietą, która poradzi sobie z każdym mężczyzną")+"...";
					link.l1 = "A dlaczego to mówisz, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "Kapitanie, proszę, pomóż mi, błagam cię! Mój mąż został pojmany! Czy możesz go uratować?";
					link.l1 = "Chwila, nie rozumiem. Kto kogo pojmał?";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "Nie wiem, ale wciąż mam nadzieję, że jest po prostu zbyt zajęty, by do mnie napisać. Mógłby mi przecież przysłać list, wie, że się o niego martwię!";
			link.l1 = "Nie jest bezpiecznie na morzu, wszystko może się zdarzyć...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Dokładnie! Rozumiesz, o czym mówię. Wyglądasz jak "+GetSexPhrase("dzielny kapitan","dzielna dziewczyna")+", więc chcę cię poprosić, abyś znalazł mojego męża. Jestem gotowa ci zapłacić "+FindRussianMoneyString(sti(npchar.quest.money))+", a do tego dam ci wszystkie moje klejnoty.";
			link.l1 = "Dobrze. Powiem twojemu mężowi o twoich zmartwieniach, jeśli spotkam go na morzu lub gdziekolwiek indziej. Powiedz mi jego imię i nazwę jego statku.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "Nie interesuje mnie tak mała suma.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "Jego imię to "+npchar.quest.SeekCap.capName+"  Pływa na  "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" nazwany "+npchar.quest.SeekCap.shipName+".";  // belamour gen
			link.l1 = "Rozumiem. Teraz musisz poczekać. Spróbuj spędzać większość czasu w kościele, żebym mógł cię znaleźć.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+GetSexPhrase("Powiadam to, dobry panie, ponieważ chcę cię zatrudnić do pracy, do której jesteś przyzwyczajony... że tak powiem.","Chcę, żebyś mi pomógł. Mam nadzieję, że zrozumiesz mnie jako kobietę.")+"Jeden kapitan mnie zirytował i chcę, żeby zdechł.";
			link.l1 = "A cóż ten biedny człowiek ci uczynił?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "Ten drań mnie oszukał. Udawał, że mnie kocha, nawet mnie adorował. A wszystko to robił, by zdobyć coś cennego od mojego męża! A kiedy pies dostał swoją kość, powiedział mi, że to nic nie znaczyło... że jesteśmy tylko przyjaciółmi!";
			link.l1 = "Hm, może miał rację?";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "Czy wyglądam jak idiota?! Myślisz, że nie widzę różnicy między zalotami a prostą paplaniną?";
			link.l1 = "Na pewno chcesz...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "On mnie wykorzystał, ten łajdak! Nigdy mu tego nie wybaczę!";
			link.l1 = "Tak, mężczyźni są właśnie tacy. Ale może uda ci się uspokoić? Nie ma w tym nic strasznego...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "Nic strasznego?! "+GetSexPhrase("Jesteś jakimś moralistą, nie jesteś prawdziwym piratem!","Zdaje się, że nigdy nie byłeś w takiej sytuacji! Och, tak, kto by zaryzykował... a ja jestem tylko słabą kobietą...");
			link.l1 = "Dobrze. Wystarczy. Chcę tylko wiedzieć, jak bardzo poważne są twoje zamiary.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "Cholera, "+GetSexPhrase("  po prostu nie wiesz, jak wygląda zemsta odrzuconej kobiety ","jesteś kobietą i musisz zrozumieć, jak to jest być odrzuconą! Chcę zemsty ")+"!";
			link.l1 = ""+GetSexPhrase("To prawda, nigdy nie miałem takiego doświadczenia","Cóż, wiesz, po prostu trochę by popłakała, potłukła szkło i to by było na tyle")+"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+GetSexPhrase("Uważaj się za szczęściarza. Odrzucona i zawiedziona w swoich oczekiwaniach kobieta to furia, diabeł w spódnicy! Nic na świecie nie mogłoby złagodzić jej gniewu","A ja nie jestem jak ona. Nic nie mogłoby złagodzić mojego gniewu")+"!\nWięc chcę, żebyś osobiście go zabił. A zanim umrze, musi się dowiedzieć, kto płaci za jego śmierć...";
			link.l1 = "Hm, nawet nie wiem, co powiedzieć... A ile płacisz?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = " Wszystko, co mam. Dam ci moje klejnoty i "+FindRussianMoneyString(sti(npchar.quest.money))+"Interes?";
			link.l1 = "Jestem zainteresowany. Powiedz mi jego imię i nazwę jego statku.";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "Nie jestem zainteresowany. Do widzenia.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "Imię tego łajdaka to "+npchar.quest.SeekCap.capName+" a płynie na "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Generał"))+" nazwany "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Uznaj to za zrobione, "+GetAddress_FormToNPC(NPChar)+". Poczekaj na mnie w miejscowym kościele. Mam nadzieję, że się trochę uspokoisz...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("",""));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "Wyjaśnię. Problem w tym, że mój mąż, który jest zwykłym człowiekiem, został schwytany przez piratów! Zabijali wszystkich i nikogo nie oszczędzili...";
			link.l1 = "Wygląda na to, że kapitan ośmielił się stawić opór. Inaczej oszczędziliby załogę.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Być może, ale mój mąż to niewinna dusza. Był tam tylko pasażerem. Musiał im powiedzieć, że jest bogaty, aby ocalić swoje życie. Piraci go oszczędzili, nawet nie wsadzili go do ładowni.";
			link.l1 = "A skąd to wiesz?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "Udało mu się wysłać do mnie list. Napisał, że ma się dobrze i jest przetrzymywany w kajucie, nie jak reszta więźniów.";
			link.l1 = "A co zamierzasz zrobić? Nie może tak dalej być. Prędzej czy później, piraci go przejrzą.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "Czy ty też jesteś piratem? Tak-tak, wiem... Błagam cię, pomóż nam, ratuj mojego męża! Opisał ten piracki statek i zapisał imię kapitana. Nie będzie ci trudno ich znaleźć!";
			link.l1 = "To nie jest takie łatwe, jak myślisz. Wszyscy więźniowie są prawowitą nagrodą kapitana, który pojmał twego męża, a do tego to zajmie trochę czasu.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "Ale możesz przynajmniej spróbować! Poza tym, masz wystarczająco czasu na poszukiwania. Mój mąż nie jest głupcem i udaje kupca ze Starego Świata, więc ci piraci na razie nie żądają od niego monet. Jeśli go uwolnisz, dam ci wszystko, co mam!";
			link.l1 = "A co masz?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Niewiele, "+FindRussianMoneyString(sti(npchar.quest.money))+" i wszystkie moje klejnoty... Ale będę modlić się za twoją duszę na wieki!";
			link.l1 = "Tak, to naprawdę niewiele... Dobrze, jestem gotów ci pomóc.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "Przepraszam, ale to dla mnie za mało.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Dziękuję, dziękuję bardzo!";
			link.l1 = "Podziękujesz mi, jeśli mi się uda, więc przestań. Lepiej powiedz mi imię twego męża i wszystko, co wiesz o tych piratach.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "Jego imię to "+GetFullName(forName)+" Kapitana "+npchar.quest.SeekCap.capName+",  żegluje na "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Mat"))+" nazwany "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Widzę. Cóż, teraz powinieneś czekać i mieć nadzieję, że uda mi się w poszukiwaniach. Zostań w kościele, czekaj i módl się ...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Oh, kapitanie, tak się cieszę, że cię widzę! Powiedz mi teraz, co masz mi do powiedzenia w sprawie mojego zadania?";
			link.l1 = "Hm, przypomnij mi, "+GetAddress_FormToNPC(NPChar)+", o jakim zadaniu mówisz?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "Ach, kapitanie, otrzymałam list od mojego męża! Napisał, że go odnalazłeś.";
					link.l1 = "Tak, to prawda, "+GetAddress_FormToNPC(NPChar)+". Twój mąż, "+npchar.quest.SeekCap.capName+",  ma się dobrze i jest zdrów. Po prostu jest zbyt zajęty...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "Co powiesz, kapitanie? Czy zrobiłeś to, o co cię prosiłem? Czy kapitan "+npchar.quest.SeekCap.capName+" martwy?";
					link.l1 = "Tak, on nie żyje, "+GetAddress_FormToNPC(NPChar)+" . Powiedziałem mu, kto był powodem jego śmierci. Ostatnią rzeczą, którą usłyszał w swoim życiu, było twoje imię.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "Ocaliłeś mojego męża! Błagam, powiedz mi, że to prawda!";
					link.l1 = "Tak, jest. Teraz jest na moim statku. Możesz go zobaczyć, jeśli "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+"jest naprawdę twoim mężem...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Naprawdę zapomniałeś, że obiecałeś mi znaleźć mojego męża? Nazywa się "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Oh, tak, oczywiście... Nie zapomniałem.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "Nie rozumiem! Zapomniałeś, że musisz zabić mojego oprawcę, kapitana o imieniu "+npchar.quest.SeekCap.capName+"?!";
					link.l1 = "Oh, błagam, oczywiście, że nie. Twoje zamówienie jest w trakcie realizacji, proszę czekać...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "Jezu, kapitanie, czy zapomniałeś o swojej obietnicy uwolnienia mojego męża?";
					link.l1 = "Nie pamiętam. Czy pamiętasz ... 'Czekaj i módl się!'. Po prostu czekaj, "+GetAddress_FormToNPC(NPChar)+" "+npchar.lastname+".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "Oh, Boże, jestem tak wdzięczny! I tak, weź swoje "+FindRussianMoneyString(sti(npchar.quest.money))+"Dzięki raz jeszcze!";
			link.l1 = "Ach, witaj...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "Doskonale! Cóż, weź swoje "+FindRussianMoneyString(sti(npchar.quest.money))+" i klejnoty. Żegnaj...";
			link.l1 = "Żegnaj. ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			TakeNItems(pchar, "jewelry47", rand(3));
			TakeNItems(pchar, "jewelry43", rand(3));
			TakeNItems(pchar, "jewelry41", rand(3));
			TakeNItems(pchar, "jewelry48", rand(3));
			TakeNItems(pchar, "jewelry51", rand(3));
			TakeNItems(pchar, "jewelry46", rand(3));
			TakeNItems(pchar, "jewelry49", rand(3));
			TakeNItems(pchar, "jewelry40", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "Oczywiście, że to on! O mój Boże, kapitanie, jestem tak wdzięczny. Weź swoje "+FindRussianMoneyString(sti(npchar.quest.money))+"  Będę modlić się za ciebie każdego dnia mojego życia!";
			link.l1 = "Brzmi dobrze...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Witaj, kolego. Chcesz czegoś"+GetSexPhrase(", kumplu ",",  dziewczyno")+"?";
					link.l1 = "Twoje imię to "+GetFullName(npchar)+", mam rację?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "Tak, jesteś!";
			link.l1 = "Za późno dla ciebie. Powiem ci jedno imię i lepiej, żebyś je znał."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"  Pamiętasz go?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "Hm, ja tak...";
			link.l1 = "Teraz słuchaj, jest na ciebie bardzo wściekły, kumplu. Czas zapłacić za sprzedanie wolnego człowieka w niewolę.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "Zapłacić?! Co ty, do cholery, wygadujesz?";
			link.l1 = "Chcę powiedzieć, że zabiję cię dokładnie tam, gdzie stoisz.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "Pomyśl o tym, dla kogo ty pracujesz?! Ten człowiek jest nędzny i jego miejsce jest na plantacji cukru!";
			link.l1 = "Cóż, to nie twoja sprawa. Teraz musisz odpowiedzieć za to, co zrobiłeś!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "Ho! Odpowiem tak, jak zwykle odpowiadam!";
			link.l1 = "Idź dalej...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "Czego chcesz?";
			link.l1 = "Chcę cię zapytać, czy przewozisz pasażerów? ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "A co cię to obchodzi?";
			link.l1 = "Po prostu pytam.";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "Po prostu pytam... Słuchaj, lepiej stąd wyjdź, póki jeszcze daję ci tę możliwość. Nie lubię cię!";
			link.l1 = "Dobrze, dobrze, uspokój się. Już odchodzę...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "Już rozmawialiśmy, więc mnie nie testuj!";
			link.l1 = "Nie będę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Witaj, kolego! Czy chcesz coś?";
			link.l1 = "Chciałbym wiedzieć, czy nie zabrałeś kobiety z "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" nazwany "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "Heh, masz rację, jest w mojej kajucie! Gorąca dziewczyna, a przy okazji świetne nogi... Dlaczego pytasz?";
			link.l1 = "Przyjacielu, ta kobieta jest zamężna. To jest złe.";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "A co z tego? Lubię ją i tyle. Nie pozwolę, aby jakiś obdarty idiota mieszał się w nasz związek tylko dlatego, że jest jej mężem!";
			link.l1 = "Pozwól mi powiedzieć, że Bractwo nie pochwala takich rzeczy, a jeśli pewne osoby dowiedzą się, co zrobiłeś, czarny znak zostanie wysłany w twoją stronę.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "Czy zamierzasz mnie zaczynać kazanie?";
			link.l1 = "Spokojnie, tylko się interesowałem... Żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "Już rozmawialiśmy o tej kobiecie. Nie chcę ponownie omawiać tej sprawy!";
			link.l1 = "Cokolwiek...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Jestem rad powitać kolegę na moim pokładzie! Czego chcesz?";
			link.l1 = "Chciałbym wiedzieć, czy porwałeś kobietę z "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Generał")+"o imieniu"+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "Heh, masz rację, ona jest w mojej kajucie! Gorąca dziewczyna, nawiasem mówiąc, ładne nogi!... Dlaczego pytasz?";
			link.l1 = "Kolego, ta kobieta jest zamężna. To jest złe.";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "Więc co z tego? Podoba mi się i tyle. Nie pozwolę, żeby jakiś obdarty gość wtrącał się w nasz związek tylko dlatego, że jest jej mężem!";
			link.l1 = "Pozwól, że ci powiem, iż Bractwo nie pochwala takich rzeczy, a jeśli pewne osoby dowiedzą się, co zrobiłeś, czarna plama zostanie wysłana w twoją stronę.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "Czy zamierzasz mnie pouczać?";
			link.l1 = "Spokojnie, po prostu się interesowałem... Żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Czego ode mnie chcesz, łajzo?!";
			link.l1 = "Jestem tu po kobietę, którą ukradłeś jej mężowi. Pamiętasz "+XI_ConvertString("Colony"+npchar.quest.cribCity)+"? Jej imię to "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "Do diabła! Nigdy jej nie zobaczysz, tak samo jak nigdy nie zobaczysz własnych uszu!";
			link.l1 = "Idiota. Widzę je w lustrze. I zamierzam odciąć twoje!";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_"+(hrand(3)+7); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "Kim jesteś?";
			link.l1 = "Witaj. Przyszedłem po ciebie, ponieważ twój mąż mnie o to poprosił. Teraz jesteś wolna i mogę cię do niego zabrać.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "Czy to sen?! Czy to prawda?!";
			link.l1 = "Tak jest, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "Chwała Panu! Jestem gotowy, uciekajmy stąd!";
			link.l1 = "Pewnie, "+GetAddress_FormToNPC(NPChar)+", przygotuj się na bezpieczny powrót do twego męża.";
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "Witaj! Cieszę się, że mogę powitać kolegę na lądzie...";
			link.l1 = TimeGreeting()+", mam z tobą pewne sprawy.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "Słucham.";
			link.l1 = "Twój towarzysz cię szuka. Płynęliście razem i przybyliście tutaj ze Starego Świata."+GetFullName(&characters[GetCharacterIndex("ZadanieObywatela_"+npchar.quest.cribCity)])+", pamiętasz?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "Ha, pewnie, że wiem! A gdzie on teraz mieszka?";
			link.l1 = "W "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = " Dziękuję! Wiesz, myślałem, że jesteś piratem!";
			link.l1 = "Jestem. W pewnym sensie. Albo nie jestem. Ale w każdym razie, mam dziś dobry nastrój, więc nie masz się czym martwić. Żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "Czy jest jakiś problem? Przepraszam, jestem trochę zdenerwowany...";
			link.l1 = "W porządku, kumplu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting()+". Czego ode mnie chcesz? Jestem tylko zwykłym kupcem i...";
			link.l1 = "Znam to, kumplu. Nie martw się tak bardzo, mówią, że to niezdrowe. Mam z tobą interes do załatwienia.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "Jaki interes?";
			link.l1 = "Twój przyjaciel cię szuka. Nazywa się "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"  Znasz go?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "Och, nareszcie! To wspaniale... Bardzo przepraszam za tak niegrzeczne powitanie, ale myślałem, że jesteś piratem.";
			link.l1 = "Jestem. Tak jakby. Albo nie jestem. Ale w każdym razie, dzisiaj mam dobry nastrój, więc nie masz się czym martwić. Poproszono mnie, abym przekazał ci wiadomość i wykonałem zadanie. Twój kompan mieszka w "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voce")+"."; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "Czyż to nie coś! Jesteś honorowym człowiekiem. Dziękuję!";
			link.l1 = "Nie ma za co. Żegnaj i uważaj na siebie, kumplu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "Cześć. Chcesz coś?";
			link.l1 = "Twoje imię to "+GetFullName(npchar)+", mam rację?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "Tak, to ja.";
			link.l1 = "To pewnie brzmi głupio, ale twoja żona poprosiła mnie, abym powiedział ci, że się o ciebie martwi.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "Ha! Widzę... Właściwie byłem zbyt zajęty, jest wiele dochodowych ofert i nie mogę tracić możliwych dochodów tylko dlatego, że moja żona za bardzo się martwi.";
			link.l1 = "Ale mógłbyś przynajmniej napisać do niej list i powiedzieć, że masz się dobrze.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "Tak, masz rację. Natychmiast do niej napiszę! Dziękuję za udział w naszych rodzinnych sprawach!";
			link.l1 = "Nie ma za co, kumplu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "Dzień dobry. Jak mogę ci pomóc?";
			link.l1 = "Twoje imię to "+GetFullName(npchar)+", mam rację?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Tak, to ja.";
			link.l1 = "To pewnie brzmi głupio, ale twoja żona poprosiła mnie, bym ci powiedział, że się o ciebie martwi.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Fuh, cholera jasna! Bałem się, że to słynny łowca nagród przyszedł po mnie, Jednooki Steve to jego imię. No cóż, dobrze, że się myliłem\nWidzisz, jestem tak zajęty swoją pracą, że nie mogę poświęcić jej żadnego czasu. Mam cały czas dochodowe oferty i nie mogę ich odrzucić z powodu zmartwień mojej żony.";			
			link.l1 = "Masz rację, no pewnie. Ale mógłbyś przynajmniej napisać do niej list i powiedzieć, że masz się dobrze.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Tak, masz rację. Zrobię to w pierwszym porcie... Dziękuję za udział w naszych rodzinnych sprawach!";
			link.l1 = "Proszę bardzo, kumplu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Masz moje podziękowania, kapitanie...";
			link.l1 = "Nie ma za co.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "Miło cię widzieć w tym mieście, kapitanie. Potrzebujesz ode mnie czegoś?";
			link.l1 = ""+GetSexPhrase("Wiesz, kapitanie... Fuh, nawet nie wiem, jak to powiedzieć!","Tak, mam.")+"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+GetSexPhrase("Mów tak, jak jest.","Interesujące, a co to takiego?")+"";
			link.l1 = " Mam do ciebie pytanie. Czy znasz kobietę o imieniu "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "Heh, znam ją. Miałem pecha ją poznać. Głupia dziewczyna, mogę ci powiedzieć...";
			link.l1 = "Hm... Tak, a ta głupia dziewczyna poprosiła mnie, żebym cię zabił. To wszystko....";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "Nonsens.";
			link.l1 = ""+GetSexPhrase("Zgadzam się. Wybacz, ale jest nagroda za twoją głowę","Nie jest. Jest nagroda")+"I ja zamierzam to wziąć.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "Ho-ho!... Żartujesz sobie ze mnie, kapitanie?";
			link.l1 = ""+GetSexPhrase("Nie, przyjacielu.","Nie miałem nawet zamiaru!")+"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+GetSexPhrase("Nie jesteś moim przyjacielem, idioto! Nie możesz nawet nazywać się kapitanem. Jesteś zabawką tej głupiej furii!","Cholera! Jedna furia wynajęła drugą! Co się do diabła dzieje z tym światem?")+"!";
			link.l1 = ""+GetSexPhrase("Uważaj na język, łajdaku.","Użyłeś jej, więc nie bądź zaskoczony, że postanowiła się zemścić.")+"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+GetSexPhrase("Uderzyłem w czuły punkt?","Solidarność kobiet?!")+"";
			link.l1 = "Zakończmy to!";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "Już z tobą rozmawiałem. Zjeżdżaj, kretynie!";
			link.l1 = "Idioto?! Dobrze więc...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "Cieszę się, że jesteś na pokładzie, kapitanie. Czego chcesz?";
			link.l1 = "Mam do ciebie pytanie. Czy znasz kobietę o imieniu "+GetFullName(&characters[GetCharacterIndex("ZadanieObywatel_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "Heh, znam ją. Miałem pecha ją poznać. Głupia dziewczyna, powiem ci...";
			link.l1 = "Tak, a ta głupia dziewczyna poprosiła mnie, bym cię zabił.";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "Kapitanie, nie rozśmieszaj mnie. Jeśli nie masz do mnie żadnej poważnej sprawy, to żegnam cię.";
			link.l1 = "Żegnaj zatem. Lecz rozważ to, co ci powiedziałem.";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "Pewnie, kapitanie, jakżeby inaczej?!";
			link.l1 = "Żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "Nie chcę już więcej rozmawiać na ten temat, kapitanie. To jest zbyt absurdalne.";
			link.l1 = "Cokolwiek powiesz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "Co do cholery się tu dzieje?! Czemu zaatakowaliście mój statek?";
			link.l1 = "Na prośbę damy imieniem "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"  Znasz ją?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "Co do diabła!!! Nie mogę w to uwierzyć...";
			link.l1 = "Musisz! Nie znasz się na kobietach, kumplu? Potrafią kąsać.";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "Cóż, nie zamierzam tak po prostu umrzeć. Dzięki za pogawędkę, teraz odzyskałem trochę sił.";
			link.l1 = "To ci nie pomoże.";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Cieszę się, że jesteś na pokładzie. Czy mogę ci pomóc?";
			link.l1 = "Możesz. Szukam człowieka o imieniu "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "Ten człowiek jest moim więźniem i planuję żądać za niego okupu.";
			link.l1 = "Chcę go zabrać.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "Niestety, to niemożliwe. Jeśli to wszystko, proszę opuścić mój statek.";
			link.l1 = "Jak sobie życzysz, kapitanie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "Już rozmawialiśmy o moim więźniu. Nic się nie zmieniło.";
			link.l1 = "Widzę...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Miło cię poznać. Czy mogę ci pomóc?";
			link.l1 = "Możesz. Szukam człowieka o imieniu "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "Ten człowiek jest moim więźniem i planuję go wykupić.";
			link.l1 = "Chcę go zabrać.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "Przykro mi, ale to niemożliwe.";
			link.l1 = "Jaka szkoda...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Cholera! Co do diabła?!";
			link.l1 = "Potrzebuję twojego więźnia o imieniu "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ha! Nie ma mowy, tylko po moim trupie!";
			link.l1 = "Odkąd zapytałeś...";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+11); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "Kim jesteś?";
			link.l1 = "Jestem kapitanem "+GetFullName(pchar)+"   Nie martw się, jestem tutaj, by zabrać cię do twojej żony.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Cholera, muszę śnić!";
			link.l1 = "Mogę cię zapewnić, że tak nie jest... Cóż, to już koniec, zabierzmy cię stąd.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Jestem wyczerpany, pomóż mi.","Nie mam już siły, by tak żyć!"),RandPhraseSimple("Ta praca nas pożera żywcem.","Cholerne straże nie zostawiły kawałka skóry na moich plecach!"));				
				link.l1 = RandPhraseSimple("Jaka szkoda.","Tak, życie to suka.");
				link.l1.go = "exit";				
    		} 
		break;
		
		//=====================================================================================================================================
		// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);
			
			if(LoadedLocation.type == "tavern")
			{
				// "Честь мундира".
				if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = "O, kapitanie, usiądź ze mną. Ja stawiam!";
					link.l1 = "Z przyjemnością.";
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if(NPChar.sex == "man")
				{
					// "Невольник чести".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
					{
						dialog.text = "Cześć, kapitanie. Jesteś kapitanem, prawda? Może nawet kapitanem marynarki?\nTak, musisz być dobry w posługiwaniu się szablą, w przeciwieństwie do mojego nic niewartego syna, który umrze jutro... Przez tego lubieżnego drania, który pożądliwie patrzy na damę mojego syna!";
						link.l1 = "Tak, jestem kapitanem, a mój miecz już wiele razy mnie ocalił, ale co z resztą twojej depresyjnej mowy? Chcesz wyjaśnić?";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "Красотка и пират".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "Witaj, kapitanie. Pozwól, że zapytam, czy przypadkiem nie jesteś piratem? Och, oczywiście nie! Nie jesteś. Piraci wyglądają źle, zachowują się jak zwierzęta i ten smród...";
						link.l1 = "Czy masz urazy do piratów?";
						link.l1.go = "AffairOfHonor_BeautifulPirate_1";
						PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;
					}
					
					// "Заносчивый нахал".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
					{
						//if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
						//{
						// Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
							dialog.text = "Hej, ty! Tak, ty, powiedz mi, gdzie są twoje maniery? Dlaczego, do diabła, stoisz tu i przeszkadzasz mi? Nie, tylko na niego popatrz, taki głupiec! Mówię do ciebie! Zrób miejsce! Zbyt wielu obcych tutaj!";
							link.l1 = "Spokojnie, nie chciałem ci przeszkadzać. Proszę o wybaczenie.";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "Uważaj na język, bo ci go utnę, mój dobry panie.";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "Волки и овцы".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "Witaj, kapitanie. Mam coś, o co chcę cię zapytać. Nie pozostaniesz obojętny, jeśli jesteś człowiekiem honoru.\nPrzejdźmy do sedna: pewien szlachcic zatrzymał się w naszej tawernie miesiąc temu. Okazał się rozpustnikiem i łajdakiem! Co więcej, jest mordercą!";
						link.l1 = "Z tego co pamiętam, karą za zamordowanie niewinnego jest szubienica. Bycie rozpustnikiem i bękartem również niewiele pomoże w sądzie. Czy mam rację?";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "Трусливый фехтовалщик".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "Kapitanie, zaczekaj, błagam cię. Wyglądasz na zręcznego szermierza, znacznie lepszego ode mnie. Więc chcę cię prosić, byś mnie zastąpił.";
						link.l1 = "Intrygujące. Mów dalej.";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "Божий суд".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "Proszę, błagam cię, nie odchodź! Poczekaj... Czyżbyś nie pomógł biednej duszy w jednej sprawie, która wymaga ingerencji tak odważnego oficera wojskowego jak ty?\nRzecz w tym, że miałem kłótnię dotyczącą lokalnych plantacji winogron z moim sąsiadem, przy okazji, podejrzanym o współpracę z przemytnikami. Tak, tak, i może nawet ma jakieś interesy z piratami, jak inaczej mógłby zdobyć taką fortunę w tak krótkim czasie?\nRok temu miał tylko barkę, a teraz chce zabrać moje winnice, słuchasz?! Moje winnice!";
						link.l1 = "Czuję się źle z powodu twoich winnic. Szczerze mówiąc. Żegnaj.";
						link.l1.go = "exit";
						link.l2 = "Przepraszam, ale czy nie możesz zwrócić się do lokalnych władz?";
						link.l2.go = "AffairOfHonor_GodJudgement_1";
						PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "Навязчивый кавалер".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = "Kapitanie, kapitanie, błagam cię! Broń honoru niewinnej dziewczyny!";
						link.l1 = "Nie mam na to czasu, ślicznotko. Poszukaj kogoś innego...";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "Witaj, moja pani. Nie drżyj tak! Co się stało?";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "Pech. Powiadom deweloperów.";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "Kapitanie, byłem śledzony w najbardziej jednoznaczny sposób przez oficera naszego garnizonu. Mogłeś słyszeć te paskudne plotki, które o mnie rozpowiada, próbując mnie zawstydzić!\nAch, nie mam przyjaciół zdolnych chronić me uczciwe imię! Jestem zrozpaczony! O Boże, to on! Pomóż mi!";
			link.l1 = "Nie martw się, doprowadzę to do końca.";
			link.l1.go = "exit";
			int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_14"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
			float Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;
		
		case "AffairOfHonor_Cavalier_2":
			dialog.text = "Аha, oto jesteś, moja pani! Kolejny kawaler, jak sądzę? Kiedy się uspokoisz? Może nigdy... Idź pracować w burdelu, to najbardziej odpowiednie miejsce dla ciebie...";
			link.l1 = "Oficerze, zamknij swą gębę przed wybuchem obelg, albo sprawię, że zamkniesz ją w mój własny, szczególny sposób!";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "Hm... Kimże jesteś? A-ach, samym morzem zasolony dzielny kapitan małej łajby, czyż nie? I co zamierzasz zrobić, morski... szczeniaku?";
			link.l1 = "Ta dama jest moją przyjaciółką! I rzucę dla ciebie rękawicę!";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "Co?! Nie zamierzasz mnie wyzwać z tego powodu...";
			link.l1 = "Dosyć! Będę na ciebie czekać przy latarni w ciągu dwóch godzin. I nie zapomnij zabrać swojej szabli!";
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;
		
		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;
		
		case "AffairOfHonor_Cavalier_5":
			dialog.text = "Ach, wiem wszystko, panie! Nawet nie rozumiecie, jak jestem wam wdzięczny! Niech Pan was chroni!";
			link.l1 = "Cieszę się, że mogłem ci pomóc. Powodzenia!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar, "nobility", 7);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Cavalier_6":
			dialog.text = "Ach, jesteś taki jak wszyscy inni, zostaw mnie!";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "or in the brothel ";
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+"... Nie śmiem mieć nadziei, ale być może tym razem twój miecz mógłby ochronić moją rodzinę?\nJak mówiłem, mój syn nie jest szermierzem, ale idzie na pojedynek już następnego ranka. Ach, gdyby nie jego dama i to cholerne honor\nAle nie mógł się wycofać i teraz jest zgubiony, nie widzisz tego? Jestem zrozpaczony, to mój jedyny syn i dziedzic, dlatego proszę cię, byś zabił łajdaka, który wyzwał mojego chłopca, zanim nadejdzie świt. Wynagrodzę ci to, możesz na to liczyć!\nZnajdziesz tego człowieka w tawernie "+sTemp+" - tam, gdzie dranie tacy jak on spędzają wolny czas... Błagam cię...";
			link.l1 = "Nie obchodzi mnie ani ty, ani twój syn. Puść mnie!";
			link.l1.go = "exit";
			link.l2 = "Hm ... Ot tak po prostu? Dobrze, zobaczymy, jak to się skończy.";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "Czy naprawdę pomożesz mojemu synowi? Och, "+GetAddress_Form(NPChar)+"Niechaj cię Bóg ma w opiece i niech fortuna ci sprzyja!";
			link.l1 = "Nie widzę w tym nic złego... Czekaj na mnie!";
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;
		
		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
			Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04","blade_06"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			if(rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;
		
		case "AffairOfHonor_HonorSlave_3":
			dialog.text = "Czego do diabła ode mnie chcesz? Odpoczywam tutaj i nie chcę, by mi przeszkadzano. Jest tu mnóstwo wolnych miejsc i wolnych uszu, więc zostaw mnie w spokoju, panie!";
			link.l1 = "Niestety, będziesz musiał przerwać swój odpoczynek do lepszych czasów.";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "Co?! A kim ty jesteś, żeby mi mówić, co mam robić?!";
			link.l1 = "Zapomniałeś mnie, co? Ale ja ciebie pamiętam! A moja uwaga jest taka, że łajdacy tacy jak ty zatruwają nasz świat samą swoją obecnością!";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "Ah?! Żeglarzu, zdaje się, że jesteś zbyt pijany! To pierwszy raz, gdy cię widzę! Ale nie zamierzam ignorować twojego zachowania! To twoja ostatnia szansa, by ocalić swoje nędzne życie! Przeproś teraz, ty napęczniały śledziu, a zapomnę twą zuchwałą mowę!";
			link.l1 = "Usprawiedliwiam się tylko przed honorowymi ludźmi, a nie przed plugawymi świniami!";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "Co do cholery?! Szukasz kłopotów, gnido latrynowa?";
			link.l1 = "Zamknę ci pieprzone gardło twoimi słowami, szczurze! Będę czekał na ciebie przy latarni za dwie godziny i nie zapomnij przynieść tego zardzewiałego gówna, które nosisz na pasku!";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "Ha! Będę tam!";
			link.l1 = "Do zobaczenia wkrótce!";
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;
		
		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
		break;
		
		case "AffairOfHonor_HonorSlave_7":
			dialog.text = "O, to ty! Żyjesz, co oznacza, że...";
			link.l1 = "Tak, jestem, a twój syn nie musi pojedynkować się jutro rano...";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "Taki piękny dzień! Powinienem pójść i powiedzieć mojej żonie dobre wieści!\nKapitanie, los sam zesłał cię, byś mi pomógł. Oto monety, przyjmij wdzięczność naszej rodziny!";
			link.l1 = "Dziękuję!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(iTemp)+"");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_9":
			dialog.text = "Spieprzaj, dzieciaku morderco!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "Ja? Dzięki Bogu, mam się dobrze, ale moja siostra nie ma tyle szczęścia. Służy w tawernie\nJest tam korsarz, który często odwiedza to miejsce, bardzo niebezpieczny typ. Pirat! Jego statek jest w rejsie od tygodnia, nie mniej. Człowiek ten pije, grozi ludziom i obiecuje zabić każdego, kto spróbuje przemówić mu do rozsądku. Najgorsze jest to, że moja siostra powiedziała mi, że chwali się, że ją porwie i zabierze, diabeł wie gdzie, jeśli nie spełni jego plugawych życzeń!\nNie wiem, co robić! Władze nie interesują się jakąś służącą, a pokojowi obywatele, tacy jak ja, boją się tego korsarza. Pomóżcie nam z nim się rozprawić, proszę!";
			link.l1 = "Nie mam czasu uspokajać pijaków w tawernach. Porozmawiaj z komendantem, płacą mu za rozwiązywanie takich spraw.";
			link.l1.go = "exit";
			link.l2 = "Hm, groźny korsarz? Dobrze, poradzę sobie z tym.";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "Ach, dziękuję, kapitanie! Jestem pewien, że posłucha ciebie jak marynarz słucha marynarza! Spraw, by zostawił moją siostrę w spokoju na zawsze! Nie jesteśmy bogaci, ale zapłacimy ci wystarczająco za twoje kłopoty!";
			link.l1 = "Dobrze, dobrze... Już idę rozwiązać wasze problemy. Czekajcie na mnie!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 25+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;
		
		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = "Więc co z tego? Rozmawiałeś z tym piratem? Czy zostawi nas w spokoju?";
			link.l1 = "Poczekaj chwilę. Już się tym zajmuję.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "Czego chcesz? Nie widzisz, że odpoczywam tutaj?";
			link.l1 = "Cóż, cóż... Oto wielki władca kielichów piwa, złodziej dziewcząt i burza tego małego miasteczka w ciele, czyż nie? A czy byłbyś tak odważny poza miastem? Przy latarni, pojedynek, za dwie godziny?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "Oh-ho-ho! Udajesz bohatera? Nieważne, kolego, dziś mam dobry humor, więc ci wybaczam. Idź i kup mi kilka kufli piwa!";
			link.l1 = "Nie jestem twoim kumplem. Powtórzyć to dla takiego głupka jak ty? Czy miałbyś tyle odwagi, by stawić się na pojedynek, jak masz odwagę pojawić się w tawernie?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "Czy chcesz mnie wyzwać?! Co z tobą nie tak? Znudzony życiem, chcesz zginąć, psie? Dobrze, jeśli naprawdę tego chcesz, pójdę do latarni, wyrwę ci flaki, a potem zniszczę tę przeklętą tawernę również!";
			link.l1 = " Gadanie jest tanie, miecze nie, więc pamiętaj, żeby przynieść jeden! ";
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;
		
		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = "Więc co? Rozmawiałeś z tym piratem? Czy zostawi nas w spokoju? Moja siostra mi powiedziała, że opuścił tawernę i nie wrócił...";
			link.l1 = "Mam. Facet był trochę niegrzeczny, ale moje argumenty były całkiem rozsądne i przekonujące. Twoja siostra nie ma się teraz czego obawiać.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "To... to już koniec? Czy możemy teraz swobodnie oddychać? Dziękuję, kapitanie! A gdzie... gdzie jest ten łotr??";
			link.l1 = "On... jest na swoim statku. Zdecydował się opuścić to miasto tak szybko, jak to możliwe.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "Oddałeś wielką przysługę obywatelom tej kolonii! Oto, weź tę nagrodę za swoją pomoc! Jest dość skromna, ale zyskasz szacunek od wszystkich moich przyjaciół, a uwierz mi, mam ich wielu!";
			link.l1 = "Moje podziękowania! Powodzenia tobie i twojej siostrze. Życzę jej, by wyszła za mąż za honorowego mężczyznę. Żegnaj!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Jackanapes_1":
			dialog.text = "O, naprawdę? A jak zamierzasz mnie powstrzymać?";
			link.l1 = "Oczywiście moim mieczem, to jedyny odpowiedni sposób na takiego bezczelnego wieprza jak ty.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "Wspaniale! Będę czekać na ciebie w pobliżu latarni morskiej za dwie godziny.";
			link.l1 = "Świetnie! Na pewno tam będę.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;
		
		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // Еще успеем.
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
		break;
		
		case "AffairOfHonor_Jackanapes_2":
			dialog.text = "Zejdź mi z drogi, tchórzu!";
			link.l1 = "O...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "Kapitanie, drań nie jest taki prosty, Tom, mój stary przyjaciel, zginął w pojedynku przeciwko niemu, oskarżony o oszustwo w kartach! Był niewinny, przysięgam. Ale gubernator powiedział, że w tym przeklętym pojedynku nie było przestępstwa.";
			link.l1 = "Hm... To wszystko wina twego przyjaciela. Oszustwa w kartach mogą źle skończyć się dla twego zdrowia.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "Tak? Już czterech szulerów było w naszym mieście przez ostatnie dwa tygodnie. I wszyscy próbowali oszukać naszego szlachcica? Co byś na to powiedział? Moim zdaniem ten szlachcic sam jest szulerem. Jeśli mi nie wierzysz, to idź i sprawdź sam.";
			link.l1 = "Chcesz się z nim hazardzić? Nie, nie lubię hazardu. Nie ma mowy.";
			link.l1.go = "exit";
			link.l2 = "Przypuszczam, że tak zrobię... Coś tu jest bardzo nie w porządku.";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "Kapitanie, ja i moi przyjaciele zebraliśmy sumę, by zapłacić człowiekowi, który ujawni tego szlachcica, i zemścić się na nim za wszystkie jego czyny. Będę czekał w mieście, by wręczyć ci nagrodę, gdy zadanie zostanie wykonane.";
			link.l1 = "Zrobię to, jeśli to, co mówisz, jest prawdą.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = "Moje uszanowanie, sir! Widzę szlachetnego człowieka, a może... hazardzistę? Masz ochotę na grę?";
			link.l1 = "Pewnie! Porozmawiajmy o stawce. Co powiesz na 50 monet?";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "Chyba sobie ze mnie żartujesz? Nie masz ich!";
				link.l1 = "Masz rację...";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "Stawka jest bez znaczenia, będziemy grać w hazard, to najlepsza część. Prawie zapomniałem, jak wyglądają karty, z powodu miejscowych idiotów.";
				link.l1 = "No cóż, zaczynajmy.";
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = "Więc, stawka to 50 monet.";
			link.l1 = "...";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
            PChar.GenQuest.Cards.SitType = true;
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = "Poczekaj chwilę, co to jest?.. Niemożliwe! Panie, jesteś oszustem! Oddaj mi moje monety!";
			link.l1 = "Musisz mieć mocne powody, by mnie obwiniać,  "+GetAddress_FormToNPC(NPChar)+" Lepiej od razu do nich strzel, albo to będzie pojedynek!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "Ach, tak po prostu? Dobrze, więc pojedynek! Dziś, za dwie godziny, koło latarni morskiej!";
			link.l1 = "Umowa stoi!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = "Jakieś nowiny, kapitanie?";
			link.l1 = "Miałeś rację, mnie też oskarżono o oszustwo, więc musiałem pociachać drania w pojedynku.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "Widzisz teraz? Wiedziałem to! Wielkie dzięki ode mnie i moich przyjaciół! Oto twoja nagroda, kapitanie.";
			link.l1 = "Dziękuję.";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_1":
			dialog.text = "Czy mówiłem ci, że przybyłem tu, by ubiegać się o posadę nauczyciela szermierki? Nie? Otóż, lokalny gubernator szuka nauczyciela dla swojego bratanka i to mi idealnie pasuje. Znam podstawy tej sztuki, choć nigdy nie próbowałem jej w praktyce. Prawie miałem tę pracę w kieszeni, ale okazało się, że miejscowy kupiec ma kłopoty, jakiś groźnie wyglądający łobuz mu grozi. Gubernator dał mi rozkaz, aby zająć się tą sprawą, by sprawdzić moje umiejętności zawodowe.";
			link.l1 = "Zrób to zatem. Żegnaj.";
			link.l1.go = "exit";
			link.l2 = "A czego ten łotr chce od kupca i do czego potrzebujesz mnie?";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "Myślałem, że ten człowiek to najemnik i z najemnikami zawsze można się dogadać. Stare długi czy coś... Ale ten człowiek naprawdę zamierzał dalej naciskać na kupca. Chciałem cię prosić, abyś pomógł kupcowi i mi, ratując go przed najemnikiem i wypełniając rozkazy gubernatora.\nNaprawdę potrzebuję tej pozycji i nie mogę pozbyć się najemnika sam. Proszę, pomóż mi, a dam ci każdą monetę, jaką zaoszczędziłem, albo będę zmuszony opuścić miasto w hańbie!";
			link.l1 = "Dobrze, dobrze, pomogę ci... 'mistrzu szermierki'.";
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;
		
		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
			Scl = 30+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_"+(rand(7)+23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06","blade_10"), RandPhraseSimple("pistol4","pistol6"), "bullet", Scl*3+70);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;
		
		case "AffairOfHonor_CowardFencer_2":
			dialog.text = "Czego chcesz? Nie widzisz, że jestem zajęty?!";
			link.l1 = "Nękać jakiegoś szanownego kupca i robić hałas!?";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "Phi! Kolejny obrońca? Taniej będzie mi zapłacić, niż zatrudniać strażników każdego dnia. Nie przepadam za zabijaniem, w przeciwieństwie do ściągania długów, więc jeśli jesteś takim bohaterem, to przyjdź do latarni morskiej, a zmierzymy się w pojedynku. A jeśli nie jesteś, to nie zadzieraj ze mną ponownie.";
			link.l1 = "Umowa stoi! Będę tam na ciebie czekał.";
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;
		
		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = "Wygląda na to, że jesteś jeszcze większym tchórzem niż ja...";
			link.l1 = "Tak, jestem.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "Jakieś wieści, kapitanie?";
			link.l1 = "Najemnik nie żyje. Mam nadzieję, że stanowisko jest teraz twoje?";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "O, kapitanie, moje podziękowania! Weź swoją nagrodę, a ja zdam raport naszemu gubernatorowi!";
			link.l1 = "Żegnaj... mistrzu.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			GiveItem2Character(pchar, "chest"); 
			Log_Info("You have received a chest filled with doubloons");
			PlaySound("interface\important_item.wav");
		break;
		
		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "AffairOfHonor_CoatHonor_2":
			dialog.text = "Jeszcze jeden?";
			link.l1 = "Do dna.";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "I więcej!";
			link.l1 = "Zaczekaj chwilę! Dokąd się tak spieszysz?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "Piekło z pytaniami! Pij!";
			link.l1 = "Dobrze, ale może później opowiesz mi, co się z tobą stało?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "Naprawdę cię to interesuje? To słuchaj, póki jeszcze mogę mówić! Za kilka dni nie będę w stanie mówić, bo będę martwy... Tak, martwy! I to rum jest winny. Dużo rumu i ten oficer, najwyraźniej przyniesiony przez diabła nad moją głową!\nNa pewno nie walczyłbym z najlepszym szermierzem naszego garnizonu i całego miasta, gdybym był trzeźwy albo przynajmniej nie tak pijany. Ale co teraz? Jestem skazany, zmarnowany i jestem martwy! Jestem takim głupim głupcem...";
			link.l1 = "Tak, to było zbyt głupie. Ale prawdopodobnie zachowasz się mądrzej w przyszłości... jeśli oczywiście przeżyjesz pojedynek. Żegnaj.";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "Pijany to też nie najlepsza opcja, oficerze. Jestem pewien, że istnieje rozwiązanie tego problemu.";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "Jaki rodzaj rozwiązania? Zdezerterować i stracić swoją reputację i mundur oficerski? Albo popełnić samobójstwo, by nie dać się poćwiartować jak świnia? Jaką masz radę?";
			link.l1 = "Żaden z nich. Pomogę ci i spróbuję zapobiec, aby twój przeciwnik zadał ci jakiekolwiek obrażenia przed czasem waszego pojedynku. Gdzie mogę go znaleźć?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "Naprawdę? Zrobisz to?! Och, przysięgam, wynagrodzę ci to sowicie!\nMożna go znaleźć w mieście. Jego kochanka mieszka tutaj, wszyscy oficerowie o niej słyszeli, ale niestety jej adres jest nieznany... Więc obstawiam, że możesz go tam również znaleźć.";
			link.l1 = "Dość tego. Poczekaj tu na mnie. Pójdę i pogadam z tym... 'najlepszym szermierzem'.";
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;
		
		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
		break;
		
		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = "Masz jakieś wieści dla mnie, panie? Dobre czy... może nie tak dobre?";
			link.l1 = "Nie mam jeszcze żadnych wieści. Czekaj tutaj. Wszystko będzie dobrze.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "Masz dla mnie jakieś wieści, sir? Dobre czy... raczej nie za dobre?";
			link.l1 = "To koniec. Twój potencjalny przeciwnik nie będzie już nikomu szkodzić... Teraz jesteś bezpieczny. Ale mam nadzieję, że wyciągniesz z tej lekcji wnioski i nie będziesz agresywny wobec ludzi, których nie znasz.";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "Żartujesz sobie ze mnie, prawda? Ja... Ja jestem naprawdę wdzięczny, "+GetAddress_Form(NPChar)+"! Weź, zabierz wszystko, co mam. To moja płaca, bierz wszystko!\nLekcja, mówisz? Tak, do diabła, masz rację! To się nigdy więcej nie powtórzy! Obiecuję ci to, i dziękuję ci raz jeszcze za danie mi kolejnej szansy!";
			link.l1 = "Dobrze więc. Żegnaj, oficerze...";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("You have received a purse with doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "Dzięki raz jeszcze, "+GetAddress_Form(NPChar)+", za twoją pomoc!";
			link.l1 = "Zawsze jesteś mile widziany...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "Hej, co do diabła? Co robisz w komnatach mojej damy? Wynoś się stąd, bo cię siłą wyciągnę!";
			link.l1 = "Chodzę, gdzie chcę, i nie zamierzam zgłaszać cię za takie zachowanie! Przemocą? Spróbuj więc!";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "Co za bezczelność! Niesłychana zuchwałość! Panie, naprawdę się pan myli! Opuść ten dom natychmiast, albo przysięgam, że pożałujesz, że żyjesz!";
			link.l1 = "Rozmowy są tanie! To ty będziesz tego żałować, nie ja, "+GetAddress_FormToNPC(NPChar)+"! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "Naprawdę? Strzeż się więc! Jeśli cię zabiję w tym domu, będzie to morderstwo. Więc twoja śmierć nie zaszkodzi mojej reputacji, ludzie honoru załatwiają takie sprawy w pobliżu latarni morskiej!\nWyzwanie rzucam ci, "+GetAddress_Form(NPChar)+", ty bezczelny człowieku! Odpowiesz za swoje słowa! A więc, pojedynek za dwie godziny?";
			link.l1 = "Pewnie, "+GetAddress_FormToNPC(NPChar)+" śmiały facet.";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "W takim razie upewnij się, że będziesz tam na czas. Wciąż masz czas, by zamówić requiem u naszego księdza.";
			link.l1 = "Requiem dla ciebie? Nie jesteś wart nawet jednego peso. Do zobaczenia przy latarni!";
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;
		
		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
		break;
		
		case "AffairOfHonor_CoatHonor_9":
			dialog.text = "Zgiń, przepadnij!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Czy masz na myśli gubernatora? Ha! 'Sąd Boży' - to mi powiedział gubernator w odpowiedzi na moje skargi! Pojedynek! Jak ci się to podoba? Jestem tylko spokojnym, miłującym pokój plantatorem, a nie bandytą czy wojownikiem\nTo będzie morderstwo, a nie pojedynek! A ty, niewątpliwie, jesteś lepszy w takich rzeczach niż ja. Dlatego proszę cię, byś wystąpił jako mój przedstawiciel w nadchodzącym pojedynku. Wierz mi, nie pozostanę ci dłużny.";
			link.l1 = "Kiedy jest pojedynek?";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "Dziś przed północą koło latarni. Czy mi pomożesz?";
			link.l1 = "Dobrze, pomogę ci. Czekaj na mnie w mieście!";
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;
		
		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05","blade_07"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;
		
		case "AffairOfHonor_GodJudgement_2":
			dialog.text = "Powiedz mi, co tam się stało? Czy my... Przepraszam, czy wygrałeś?";
			link.l1 = "Jestem pewien, że będzie dla ciebie interesujące wiedzieć, że doszło do zasadzki. Być może twój sąsiad postanowił się przerejestrować, zapraszając kilku przedstawicieli zamiast jednego, a wszyscy oni byli doświadczonymi bandytami. Na szczęście, jestem doświadczonym szermierzem.";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "Co za drań! Teraz, jak sądzę, nasz gubernator nie będzie miał żadnych powodów, by odrzucić moją prośbę o aresztowanie tego łotra! Dziękuję! Weź swoją nagrodę, a ja muszę iść do rezydencji.";
			link.l1 = "Żegnaj.";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("You have received purses of doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		// Диалоги до боя -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = "Fajnie jest grać bez błędów, bo te sukinsyny trudno znaleźć.";
			link.l1 = "Spokojnie, poinformuję deweloperów.";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "Ach, oto jesteś. To są moi przyjaciele i sekundanci. Zaczynajmy?";
					link.l1 = "Jestem do twojej dyspozycji!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "Wszyscy są zebrani. Jesteś gotowy?";
					link.l1 = "Tak, możemy zacząć!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "Nareszcie! Już myślałem, że muszę iść tak długą drogę na marne... Skończmy to szybko, zostawiłem kubek rumu i gorącą dziewkę w karczmie!";
					link.l1 = "Jestem pewien, że już nie będziesz ich więcej potrzebować!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "Jackanapes":
					dialog.text = "Więc zdecydowałeś się przyjść? Wreszcie! Zaczynajmy zatem!";
					link.l1 = "Nie spiesz się tak, bo możesz się nadziać na ostrze.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "I to są moi sekundanci, panie. Teraz szykuj się na śmierć!";
					link.l1 = "Po tobie.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CowardFencer":
					dialog.text = "Jesteśmy na miejscu. Przygotuj swój miecz, panie!";
					link.l1 = "Chętnie, niech wygra lepszy człowiek!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CoatHonor":
					dialog.text = "Doskonale, wszyscy przybyli... Zaczynajmy, sir!";
					link.l1 = "Zatańczmy!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "GodJudgement":
					dialog.text = "A kimże ty jesteś? Nie wyglądasz na zwykłego obywatela, kumplu...";
					link.l1 = "Więc? Mam z tobą umówiony pojedynek?!";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1"
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "Ha! Pojedynek! Wygląda na to, że jesteś naszym klientem. Chłopaki, zadźgajmy go i po prostu idźmy po naszą nagrodę. Rozprujmy go!";
			link.l1 = "Zasadzka? Jak żałosne, będziecie potrzebować znacznie więcej, by mnie pokonać...";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;
		
		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if(hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("Seconds will fight");
			}
			// В квесте "Божий суд" всегда нападают.
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("Global massacre");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = hrand(3);
				if(AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for(i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги до боя.
		
		// Диалоги после боя -->
		case "AffairOfHonor_AfterFight_1":
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = "Nie myślisz, że pozwolimy ci zabić naszego przyjaciela i uciec ot tak sobie? Do broni!";
				link.l1 = "Powinienem był się tego spodziewać po takim nędznym łajdaku!";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "Kapitanie, honor został przywrócony, wygrałeś. Ale pozwól, że dam ci dobrą radę - opuść miasto i nie pokazuj się tu przez jakiś czas...";
				link.l1 = "I jaki jest problem??";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "To było wszystko dla honoru, a teraz chodźmy i zabierzmy naszego przyjaciela.";
				link.l1 = "Jasne, nie będę cię zatrzymywać...";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "Problem polega na tym, że zabiłeś ordynansa naszego komendanta. Był złym człowiekiem i nikt nie będzie żałował jego śmierci... ale komendant naprawdę go lubił i nigdy nie wybaczy ci śmierci swojego przyjaciela.";
			link.l1 = "Dzięki za radę, na pewno się do niej zastosuję. Żegnaj.";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;
		
		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				ChangeCharacterComplexReputation(PChar, "nobility", 5);
			}
		break;
		
		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = hrand(3);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for(i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги после боя.
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " has left from: " + sld.city + " and heading to:" + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. He got frightened and run away on his ship" break;
		case 1: sText = "One dishonourable bastard has lost a huge sum to me in gambling and has run away on his ship" break;
		case 2: sText = "One scoundrel has loaned money from me, and when I wasn't at home he has repaid the debt with false coins to my servant. Now he is hiding somewhere on his ship" break;
		case 3: sText = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed and this bastard had run away on his ship " break;
		case 4: sText = "It was my mistake, I have hired some rogue as an accountant. He has committed a great peculation, bought a ship and run away " break;
		case 5: sText = "My ex-guard has stolen a box filled with jewels from my wife's boudoir and run away. Now I see where has he got enough coins to buy a ship " break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. But he got hired as a ship master and sailed away";
			npchar.quest.text1 = " dishonoured a woman and cowardly run away";
		break;
		case 1:
			npchar.quest.text = "One dishonourable bastard had lost a huge sum to me in gambling but he didn't pay me yet, I heard that he got hired as a cannoneer and run away";
			npchar.quest.text1 = "lost all his money in gambling and didn't want to repay the debit ";
		break;
		case 2:
			npchar.quest.text = "One scoundrel has loaned money from me, and when I wasn't at home he had repaid the debt with false coins to my servant. Now he is serving on one ship as quartermaster and hiding from me ";
			npchar.quest.text1 = "counterfeiter who has committed a crime";
		break;
		case 3:
			npchar.quest.text = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed. Luckily for him bastard got hired as a doctor on one ship and run away";
			npchar.quest.text1 = "slanderer and intrigant who has tried to dishonour one good citizen";
		break;
		case 4:
			npchar.quest.text = "It was my mistake, I have hired some rogue as an accountant. He had committed a great peculation and now he is serving on one ship as quartermaster and hiding from me";
			npchar.quest.text1 = "is blamed in peculation and misappropriation";
		break;
		case 5:
			npchar.quest.text = "My ex-guard stole a box filled with jewels from my wife's boudoir and run away. He got hired as an officer for the boarding party on one ship";
			npchar.quest.text1 = "a common thief and his place is in jail. He has stolen jewels from his own employer";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "my old pal, who was my close friend in the Old World";
			npchar.quest.text1 = "he is your old friend";
		break;
		case 1:
			npchar.quest.text = "a man, who basically was my father";
			npchar.quest.text1 = "you were like a father for him";
		break;
		case 2:
			npchar.quest.text = "my stepbrother, who had left the old world in his youth";
			npchar.quest.text1 = "you are his stepbrother";
		break;
		case 3:
			npchar.quest.text = "a man who really helped me in the Old World";
			npchar.quest.text1 = "you have helped him a lot";
		break;
		case 4:
			npchar.quest.text = "my sister's husband who was my friend in the Old World";
			npchar.quest.text1 = "you are his sister's husband";
		break;
		case 5:
			npchar.quest.text = "my friend, my brother in arms in the Old World";
			npchar.quest.text1 = "you were brothers in arms";
		break;
	}
}
