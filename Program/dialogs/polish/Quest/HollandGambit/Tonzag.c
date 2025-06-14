// Эркюль Тонзаг, он же Плешивый Гастон
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Cóż, witaj, "+pchar.name+" Cieszę się, że żyjesz.";
				link.l1 = "Gaston! Czy to ty?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Witaj, "+pchar.name+"  Już wiem o twoich interesach - John mi wszystko opowiedział.  Nie wiem nawet, co powiedzieć.  Podziwiam cię!";
				link.l1 = "Jestem zaszczycony słysząc takie pochwały od ciebie, Hercule!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Dzień dobry. Czy masz dla mnie jakieś zadanie?";
			link.l1 = "Nie. Mój błąd. Przepraszam. Żegnaj. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "Znałeś mnie pod tym imieniem. Ale moje prawdziwe imię to Hercule. Hercule Tonzag.";
			link.l1 = "Święty Panie! Również się cieszę, że cię widzę... Nie rozpoznałem cię w ferworze walki. Przybyłeś w samą porę ze swoją pomocą.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "Zaraz po twoim wyjeździe dostałem wiadomość, że Fleetwood wzmocnił ochronę swojego domu. Zasugerowałem, że za tym może kryć się pułapka. Natychmiast wypłynąłem na Antiguę na moim statku 'Zmierzch' - i, jak teraz widzisz, z dobrego powodu.";
			link.l1 = "Prawda. Ledwo udało mi się poradzić sobie ze strażnikami w domu, ale byłem zbyt wyczerpany, by dalej walczyć na ulicy...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "Po tej walce Fleetwood umieścił holenderskiego szpiega na liście poszukiwanych. Myśleli, że to ty jesteś holenderskim szpiegiem. On jest z nimi w nieprzejednanej waśni. Najgorsze było to, że żołnierz w domu przeżył i zapamiętał twoją twarz. Ale, w każdym razie, teraz to nie problem. Zakończyłem to, co zacząłeś. Ten żołnierz już nikogo nie rozpozna, a nikt nie rozpozna jego...";
			link.l1 = "Zabiłeś go? Rozumiem...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Tak. Gdy leżałeś nieprzytomny w domu Johna, zraniłem Fleetwooda, ale ten drań zdołał przeżyć. Oślepiłem go - sypnąłem mu pieprzem w oczy, a potem zaatakowałem, zanim zdążył dobyć miecza. Ale łajdak miał na sobie kolczugę pod mundurem - to uratowało mu życie. Sprytnie. Teraz leży w domu w łóżku pod zwiększoną ochroną. To bardzo niefortunne, że przeżył.";
			link.l1 = "Więc twoim głównym zadaniem na Antigui było wyeliminowanie Fleetwooda?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Ogólnie rzecz biorąc, tak. Teraz jednak wydaje się to niemożliwe - dom jest zawsze zamknięty, na straży stoi pół tuzina starannie wybranych strażników przez całą dobę, a do niego dopuszczają tylko jego zaufanego człowieka - starego kanoniera Charliego, zwanego Knippel.";
			link.l1 = "To już coś...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Poczekaj chwilę... Zamierzasz wmieszać się w tę sprawę?";
			link.l1 = "Czemu nie? Nie potrzebujesz pomocy? Uratowałeś mnie, a ja chcę pomóc. Poza tym nadal potrzebuję monety.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "Dlaczego nie? Jesteście poważnymi ludźmi. A poważni ludzie płacą hojnie. Szukam tylko pracy.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "Wierz mi, przyjacielu, nie zdołasz tego dokonać. Jesteś wspaniałym człowiekiem, prawdziwym talentem, a dziennik pokładowy, który przyniosłeś, pomógł mi zaplanować zamach na życie Fleetwooda, dobrze się spisałeś przy cięciu strażników - ale teraz nigdy nie będziesz w stanie dostać się do Fleetwooda. Nawet ja nie mam najmniejszego pojęcia, jak to zrobić.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Przemyślę to. Wciąż mam czas. Szkoda, że mój statek został zatrzymany, a ja nie mam załogi.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Zastanowię się nad tym. Mam czas i statek.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Wierz mi, przyjacielu, nie uda ci się to. Jesteś świetnym facetem, prawdziwym talentem, a dziennik pokładowy, który zdobyłeś, pomógł mi zaplanować zamach na życie Fleetwooda, dobrze poradziłeś sobie z pokrojeniem strażników - ale teraz nigdy nie zdołasz dotrzeć do Fleetwooda. Nawet ja nie mam najmniejszego pojęcia, jak to zrobić.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Przemyślę to. Wciąż mam czas. Szkoda, że mój statek został zatrzymany, a ja nie mam załogi.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Zastanowię się nad tym. Mam czas i statek.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Nie martw się o to. Kiedy twój stary statek został aresztowany, zabrałem wszystkich twoich oficerów i kilku marynarzy na pokład mojego 'Zmierzchu'. Wiedzą, że żyjesz i zgodzili się pozostać w służbie. A w nagrodę za dziennik, oddaję ci mój statek 'Zmierzch'.";
			link.l1 = "Dziękuję! Zapamiętam to!";
			link.l1.go = "SJ_talk_9";
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			}
			else
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_SCHOONER, 16, 1900, 50, 1350, 25000, 13.5, 55.0, 1.10);
			}
			pchar.Ship.name = "Twilight";
			SetBaseShipData(pchar);
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46) pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			else pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Tak, chciałbym zapłacić za dziennik. 15000 pesos - niestety, w tej chwili nie mam więcej. Rozliczymy się za dzień.";
			link.l1 = "Nie trzeba. To wystarczy. Gdybyś nie przybył na czas, i tak nie potrzebowałbym żadnych pieniędzy.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "Dobrze, "+pchar.name+", muszę iść. Jeszcze nie wracam do Bridgetown. Jeśli kiedykolwiek będziesz mnie potrzebować - zapytaj Johna. Powodzenia!";
			link.l1 = "Powodzenia, Hercul!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "SJ_talk_11":
			dialog.text = "Chciałbym wręczyć ci tę zbroję za wyeliminowanie Fleetwooda. Będzie cię chronić w przyszłych bitwach. Chodźmy teraz do Johna. Chce z tobą porozmawiać i zaproponować... jedną interesującą sprawę.";
			link.l1 = "Dziękuję za prezent. Dobrze, ruszajmy...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "Ja również chciałbym z tobą porozmawiać, kapitanie. Zamierzałem nauczyć cię mojego rzemiosła, ale teraz widzę, że to ja powinienem uczyć się od ciebie. Zatrudnij mnie jako oficera na swoim statku - nie pożałujesz tego.";
			link.l1 = "Z przyjemnością, Hercule! Witaj na pokładzie!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Hercule, nie mogę sobie wyobrazić, że jestem twoim zwierzchnikiem. Dziękuję za twoją propozycję, ale po prostu nie mogę cię widzieć jako mojego podwładnego.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1"://Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "Jak sobie życzysz, "+pchar.name+"Do zobaczenia. Być może spotkamy się ponownie. Praca z tobą była przyjemnością.";
			link.l1 = "Powodzenia, przyjacielu!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "Słucham cię, kapitanie. Co masz do powiedzenia?";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hercule, wybieram się do starego indiańskiego miasta Tayasal i, co jeszcze bardziej niezwykłe, moja droga prowadzi przez teleportacyjną statuę. Czy dołączysz do mnie?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Hercule, daj mi pełny raport o statku.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Chcę, abyś za każdym razem, gdy jesteśmy w porcie, kupował określone towary.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Przybyłem na wasze rozkazy, kapitanie.";
				Link.l2 = "Muszę wydać ci kilka rozkazów.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Słuchaj mojego rozkazu!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nic w tej chwili. Spocznij!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Kapitanie, bardzo przepraszam, ale nie zajmuję się liczbami i obliczeniami. Zapytaj van Merdena - on ma talent do takich rzeczy, jednak wątpię, by chciał opuścić swoje gniazdo.";
			Link.l1 = "Masz rację, Hercule. Meh, muszę znaleźć sobie kwatermistrza...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Kapitánie, kiedy byłem karczmarzem na Barbados, kupowałem tylko rum i zapasy. A przez zapasy rozumiem prawdziwe jedzenie, a nie jakieś krakersy i peklowaną wołowinę. Przepraszam, ale to nie moja działka.";
			link.l1 = "Może powinniśmy przekształcić mój statek w tawernę... Żartuję tylko, Hercule. Nieważne, sam się tym zajmę.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Słucham cię.";
			Link.l1 = "Chodzi o abordaż.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Chodzi o twój statek.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Nic do tej pory.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Więc jakie jest twoje życzenie.";
			Link.l1 = "Nie abordażuj wrogich statków. Zadbaj o siebie i załogę.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Chcę, abyś abordażował wrogie statki.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Więc jakie jest twoje życzenie.";
			Link.l1 = "Chciałbym, abyś nie zamieniał swojego statku na inny po abordażu. Jest zbyt cenny.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Kiedy abordujesz wrogie statki, możesz je wziąć dla siebie, jeśli są przyzwoite.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Oczywiście.";
			Link.l1 = "Spocznij.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Zostanie to zrobione.";
			Link.l1 = "Spocznij.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Tak jest.";
			Link.l1 = "Zostanie to zrobione.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "To będzie zrobione.";
			Link.l1 = "Spocznij.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		
		case "stay_follow":
            dialog.Text = "Jakie są twoje rozkazy? ?";
            Link.l1 = "Zostań tutaj!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Chodź za mną i nie zostawaj w tyle!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Zmień rodzaj amunicji.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wybór rodzaju amunicji:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Aj!";
            Link.l1 = "Spocznij.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Aj!";
            Link.l1 = "Spocznij.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Masz szczęście, sukinsynu, kapitanie. Cieszę się, że dołączyłem do ciebie, kiedy ja, ty i John pracowaliśmy razem. Niech mnie rekin połknie, jeśli cię nie wesprę w tym przedsięwzięciu!";
			link.l1 = "Dziękuję, Hercule! Cieszę się, że miałem rację co do ciebie.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Kiedy wyruszamy?";
			link.l1 = "Trochę później. Teraz powinniśmy przygotować się do podróży.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Niewiele, Kapitanie. Gdyby to miało związek z naszym interesem, już by nas mieli na stole tortur.\nSkoro nie wzięli nas od razu na przesłuchanie, sprawa najwyraźniej nie jest pilna.\nAlbo pułapka, albo wymuszenie.\nBędą nas tu trzymać przez kilka dni bez wyjaśnień. A potem przyjdą z propozycją, którą przyjmiemy.";
			link.l1 = "Osobiste doświadczenie?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Więc czy jest jakiś sposób, by skłonić ich do przyjęcia takiej oferty właśnie teraz?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Oczywiście. Gruoh raz otrzymała zapłatę od krewnych zmarłego, by oszczędzić go pożegnalnych pieszczot kata z Trinidadu.\nOpłaciła komendanta, by móc przechadzać się po celach aresztu. Zwyczajna praktyka - wielu płaci żołnierzom za możliwość dręczenia ludzi, którzy nie mogą się bronić bez świadków.\nCzłowiek zmarł cicho i bez cierpienia. Czysta i przyzwoita robota.";
			link.l1 = "Gruoh? Kto to?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "Przykro mi, kapitanie. Złe miejsce i zły czas.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "„Możemy spróbować. Poczekajmy na czas karmienia, a ja zamienię kilka słów ze strażnikiem. Widzisz, oni wciąż nie nauczyli się dobrze przeszukiwać. Eh...”";
			link.l1 = "Co się dzieje?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "Dziwne uczucie, Kapitanie. Nazwałbym to nawet przeczuciem. Wybacz, porozmawiajmy później.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "Czy coś przeoczyłem, kapitanie?";
			link.l1 = "Och, nic specjalnego, po prostu kolejny dzień na morzu. Spójrz na siebie, stary diable! Narobiłeś tu dla mnie niezłego bałaganu.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "Krew zmywa się zimną wodą, Kapitanie. Musimy porozmawiać.";
			link.l1 = "Co myślisz? Nie zaszkodziłoby przetrwać ten dzień na początek.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "Cieszę się, że cię widzę, Rumba. Kapitanie, nie będę ci przeszkadzał, porozmawiamy później.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "Hej, Rudy. Kapitanie, nie będę przeszkadzał, porozmawiamy później.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "Kapitanie, nie będę ci przeszkadzać, porozmawiamy później.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "Gotów mnie wysłuchać, Kapitanie?";
			link.l1 = "Najwyższy czas, byśmy porozmawiali, Hercule. Właśnie zdałem sobie sprawę, że prawie nic o tobie nie wiem.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "Więc czas się zapoznać. Pominiemy wczesne lata, choćby dlatego, że nie ma o czym mówić - zwycięski żołnierz, pokonany żołnierz, dezerter, maruder... wiesz, jak to leci.";
			link.l1 = "Właściwie nie, ale jak dotąd brzmi to całkiem zwyczajnie.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "Kariera po takiej wojskowej ścieżce była dla mnie ograniczona - bandyta, wisielec, albo strażnik godzien Holenderskiej Kompanii Zachodnioindyjskiej. Wybrałem to ostatnie, jak rozumiesz.";
			link.l1 = "Czy też stamtąd zdezerterowałeś?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "Wręcz przeciwnie, zrobiłem tam karierę. Otrzymałem propozycję dołączenia do bojowego skrzydła działu wywiadu Kompanii, gdzie poznałem moją przyszłą żonę.";
			link.l1 = "Na razie historia jest dość spokojna... zwłaszcza jeśli nie zastanawiasz się zbytnio nad metodami Holendrów.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "Nie zarobisz wielkich pieniędzy będąc uczciwym, a z konkurencją można walczyć na różne sposoby. Tak, działaliśmy specjalnymi metodami...";
			link.l1 = "Chyba wiem, co masz na myśli...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "Tak, to mogło być cokolwiek: od piractwa po podpalanie magazynów z towarami. W końcu schemat został zdemaskowany, a my zostaliśmy rozwiązani... na papierze, oczywiście. Tak narodziła się Liga, znana i kontrolowana jedynie przez wybranych przywódców wyższych szczebli Kompanii. Dla karaibskiego wyrzutka, który jest coś wart, były tylko dwie opcje: piractwo lub Liga. I zwykle Liga płaciła lepiej.\nPrzeważnie Liga nadal pracowała dla Holendrów, ale mogła również przyjmować zlecenia poboczne...";
			link.l1 = "Sprawy zaczynają się rozjaśniać...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "Liga stała za tą farsą na Tortudze. A potem ta desantowa ekipa...";
			link.l1 = "Domyśliłem się. Ale dlaczego?";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "Ponieważ nikt nie opuszcza Ligi żywy, i nie można uciec bezkarnie za to, co tam zrobiliśmy, Kapitanie. Chciałem przejść na emeryturę, więc i tak spróbowałem. Jak widzisz, niezbyt skutecznie.";
			link.l1 = "Chcesz powiedzieć, że twoi dawni koledzy ponieśli ogromne wydatki finansowe, stracili prawie setkę ludzi, spalili brander i zaryzykowali swój okręt wojenny tylko po to, by... zabić cię za dezercję?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "Byłem kimś więcej niż tylko popychadłem w Lidze, Kapitanie. Wiem o niej za dużo. Nie mogą mnie po prostu puścić wolno, muszą to jasno pokazać, aby nikt inny nie pomyślał o opuszczeniu interesu... Próbowali mnie dorwać wcześniej... całkiem dawno temu... Zabili moją żonę i oszpecili mnie, choć kosztowało ich to wiele. Nie ma szczęśliwego zakończenia tej historii, Kapitanie. Wystarczy, że wydasz rozkaz, a opuszczę statek i zajmę się nimi sam, po raz ostatni.";
			link.l1 = "Nie gadaj bzdur, Hercule... A jaką rolę odegrał Lucas Rodenburg we wszystkim? Musiał być zamieszany w te sprawy! Twoja, a raczej jego, 'organizacja', Liga...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "Różne agencje, Kapitanie. Co prawda, często podporządkowywały się tej samej osobie i ściśle współpracowały. Ale specjaliści Rodenburga przeprowadzali precyzyjne, skuteczne ataki, podczas gdy Liga przeprowadzała masowe operacje. A teraz co się stało z Ligą? Organizacja już nie istnieje, jak widzisz: jestem tutaj z tobą, John Murdock odszedł, Longway uciekł, Van Berg leży na dnie morza, Rodenburg został stracony... Jednak byłem dłużny temu zmarłemu łajdakowi. Zauważył mnie w Lidze, a kiedy próbowałem ją opuścić, wyciągnął mnie z poważnych kłopotów i uczynił swoim zastępcą. Oczywiście, inni tego nie lubili, ale nikt nie odważył się mu sprzeciwić... A potem, w znanych okolicznościach, postanowił pozbyć się Murdocka i mnie, ale ty interweniowałeś i wziąłeś mnie do swojej służby\nI wtedy pomyślałem: 'Oto moja druga szansa na zerwanie z przeszłością...' Pograłeś Rodenburga, Liga straciła swojego patrona, nie było już niebezpieczeństwa... Ale, oczywiście, myliłem się... Stary głupiec... Ale dosyć tego, Kapitanie. Pomyślmy, co robić dalej, jeśli oczywiście naprawdę nie planujesz mnie wypuścić w pierwszym porcie.";
			link.l1 = "Nie mam. Przypuszczam, że masz jakiś plan?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "Właściwie nic szczególnego. Nigdy ich wszystkich nie zlikwidujemy, ale możemy zadać im takie straty, że nie będzie im się opłacało dalej na mnie... na nas polować.";
			link.l1 = "A jak to zrobimy? Mają obóz?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "Duża forteca? Trudno powiedzieć. Byłaby zbyt zauważalna i niebezpieczna dla Ligi. I mówiąc o stratach, nie mam na myśli strat ludzkich - nie obchodzi ich los ludzi, ale nie będą się cieszyć z utraty złota. Pieniądze od Kompanii już do nich nie płyną, prawda? Wątpię, aby Liga znalazła nowego patrona, więc muszą wyciskać złoto z innego miejsca.";
			link.l1 = "A jakież to miejsce byłoby?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "Nie wiem, kapitanie.";
			link.l1 = "Herkulesie, ale przecież właśnie powiedziałeś, że ścigają cię właśnie dlatego, że wiesz zbyt dużo!";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "Niech pomyślę... Być może Liga obecnie działa przeciwko Hiszpanom. Są oni głównymi kandydatami do porządnego wstrząsu. A propos, Rodenburg zawsze miał dobre relacje z kastylijskimi grubasami. Czasami kierował chłopaków z Ligi do nich na różne zlecenia i zawsze zabraniał wyrządzania im jakiejkolwiek krzywdy, co, nawiasem mówiąc, chłopakom niezbyt się podobało...";
			link.l1 = "Dobre warunki, powiadasz? A co z tym jednym Hidalgo i jego palcem, które kazałeś mi zaciągnąć do swojej tawerny?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "To była wyjątkowa sytuacja, dodatkowe zlecenie. Jeśli czujesz się winny, Kapitanie, możesz być spokojny - ten Don dostał, na co zasłużył... Ale mówię o czymś innym: po zniknięciu ich pracodawcy, agenci Ligi mogli po prostu ulec swoim pragnieniom i spróbować uszczknąć solidny kawałek hiszpańskiego ciasta. Dzięki współpracy z Hiszpanami pod kierunkiem Rodenburga, wiedzą, gdzie i co zabrać.";
			link.l1 = "Hm... możesz mieć rację. Ale z tego, co wiem, nikt naprawdę nie włamuje się do hiszpańskich banków, działając przeciwko Hiszpanom na morzu - to zależy od fortuny... Może powinniśmy poszukać jakiegoś hiszpańskiego przedsięwzięcia? Fabryki?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "Rozsądne założenie, kapitanie... Czy mamy jakieś inne tropy?";
			link.l1 = "Hm... statek, który nas dziś zaatakował, popłynął na południe...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "Mało prawdopodobne, że jego kapitan znów nas niepokoi, ale musi ostrzec innych, że sprawy nie poszły zgodnie z planem, a być może przetransportować załogę w inne miejsce. Coś jeszcze?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "Tak, miałem przyjacielską rozmowę z komendantem więzienia w Tortudze... Wspomniał coś o kontynencie.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "Nie, nic więcej.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "Doskonałe, Kapitanie! Południe, kontynent, Hiszpanie - to znaczy, że szybko ich znajdziemy. Czy wyruszamy w rejs? I dziękuję za wysłuchanie mojej opowieści.";
			link.l1 = "Tak, mieliśmy naprawdę szczerą rozmowę... Podnieśmy żagle!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "Niewiele informacji. Ale dla takich jak my, to wystarczy. Ruszamy na południe? Szukać hiszpańskiego przedsiębiorstwa handlowego? I dzięki za wysłuchanie mojej opowieści.";
			link.l1 = "Tak, całkiem szczerą rozmowę mieliśmy... Wypływajmy w morze!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "Spójrz, kapitanie. Tak właśnie działają.";
			link.l1 = "I ty tak pracowałeś?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Chodźmy, zobaczmy co jest w środku.";
			link.l1 = " ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "Plugawa sprawa, Kapitanie. Wyczyściliśmy tę norę, ale to z pewnością nie ostatnia taka...";
			link.l1 = "A co z kopalnią, Hercule?! Wszyscy ci ludzie na zewnątrz?! Oni też zostali 'oczyszczeni'! A co ten łotr miał na myśli?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "Let's discuss this later, Captain. Their commander survived; we need to interrogate him.";
			link.l1 = "A jeśli on nic nie wie?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "He knows something. Think about it - they were waiting for us, carried out all the gold, and eliminated witnesses. That means they had a plan. I want to take a look around here, and later I'll bring the scoundrel to the ship myself. You should also keep an eye out; perhaps they were too hasty and missed something.";
			link.l1 = "Dobrze, ale kiedy wrócimy na statek, czeka nas poważna rozmowa!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "Dobre wieści, kapitanie.";
			link.l1 = "W naszej sytuacji nie widzę nic dobrego, Hercule. Chodźmy, musimy porozmawiać na osobności.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "Więc tak to jest, co? Aye, Kapitanie.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "Widzę, że czeka nas poważna rozmowa, kapitanie.";
			link.l1 = "Tak, a ja będę tym, który będzie gadał. Po pierwsze, nie sądzisz, że wyłania się tu pewna tendencja? Stosy trupów podążają za nami, gdziekolwiek pójdziemy! Najpierw dostajesz porcję kartaczy w brzuch, a następnego dnia ginie ponad sto osób, dobrych i mniej dobrych, w... nawet nie mogę tego nazwać bitwą morską! Osada została zrównana z ziemią zaledwie kilka dni temu, a dziś dołożyliśmy swoją cegiełkę do rosnącego stosu, zarzynając grupę ludzi w kopalniach.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "Naturalnie, martwię się, że stos może jutro stać się górą, ale to, co mnie naprawdę przeraża, to fakt, że cała ta krew leje się z powodu jednej osoby. A ta osoba zajmuje znaczącą pozycję w mojej załodze!";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = " ";
			link.l1 = "Po drugie, okłamałeś mnie, Hercule. Żaden dezerter nie jest wart wysiłku, jaki twoi byli koledzy wkładają w to, by cię wyeliminować. Co krzyczał nasz więzień w kopalniach? Zdrajca? Porto Bello? Gruoh? Coś zrobiłeś, Hercule, i tym razem chcę prawdy.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "Truth? The truth is, Captain, that I did desert, along with my wife Gruoh. Madame Tonzag didn't want to leave the League; she loved that life, but she loved me even more. We were supposed to take care of a Spanish hidalgo, but he made a better offer. It was our chance, and we both agreed to go into his service. Of course, the League thought we perished on a mission and sent a second group to Porto Bello to finish the job and seek revenge.";
			link.l1 = "I zabiłeś ich wszystkich?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "Najpierw zabili Gruoha i oszpecili mnie. Hidalgo nie chciał mieć już ze mną nic wspólnego i wyrzucił mnie. Wtedy właśnie znalazł mnie Rodenburg...";
			link.l1 = "A jak mam ci teraz ufać? Zdezerterowałeś z armii, porzuciłeś Ligę i zabiłeś własnych partnerów! Gdy przyjdzie odpowiednia chwila, czy zdradzisz i mnie?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "Tak, zdezerterowałem, złamałem kontrakt, zabiłem parę tuzinów członków Ligi. Ale nauczyłem się tej lekcji, Kapitanie. A poza tym, martwy człowiek nikogo nie zdradzi, a ja jestem martwy od dawna, od Porto Bello. I może dlatego tak trudno mnie teraz zabić.";
			link.l1 = "To wystarczy na dziś. Czuję, że wciąż nie mówisz mi wszystkiego.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "Zajmę się więźniem sam, czy może chcesz się przyłączyć?";
			link.l1 = "Chodźmy. Przesłucham go osobiście.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "Nie, takie sprawy nie są dla mnie. Do zobaczenia w mojej kajucie za pół godziny!";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "Kto teraz dowodzi? Arno?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "Ta hołota zdobyła władzę? Nie zajęło wam długo, by zdegenerować się do zwykłej bandy bandytów...";
			link.l1 = "Kim jest Austin?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "Banda Austina była znana z wabienia wolnych kapitanów w dzicz, rozczłonkowywania ich i całkowitego ogołacania ich zwłok z pieniędzy lub błyskotek. Dobry interes, a poszukiwaczy przygód nie brakowało, więc nikt się nie przejmował. Ale natrafili na przeszkodę z jednym kapitanem, więc musiał wziąć swoją załogę pod skrzydła Kompanii. Trzymaliśmy go na smyczy i wypuszczaliśmy tylko wtedy, gdy potrzebowaliśmy rozwiązać problemy w szybki i prosty sposób.";
			link.l1 = "Wątpię, że mogę wynegocjować umowę z taką osobą.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "To pewne. Jeśli on i jego ludzie teraz rządzą, wkrótce Liga zamieni się w kolejną bandę.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "Mieliśmy interesującą rozmowę.";
			link.l1 = "Chciałbym wiedzieć, ile z tego jest prawdą... A co z masakrą w Porto Bello? Jeśli nie kłamał, to oznacza, że ostatnim razem, gdy rozmawialiśmy, znów pominąłeś kilka ważnych faktów ze swojej świetlanej biografii.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "Było gorąco w Porto Bello, kapitanie. Walczyłem o swoje życie, o życie mojego pracodawcy, o życie mojej żony. Nie miałem czasu liczyć zabitych i opłakiwać każdego kmiecia, który pojawił się na ulicy w nieodpowiednim czasie.";
			link.l1 = "W tej kolejności priorytetów?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "Nie, oczywiście, że nie. Najpierw jej. Zawsze.";
			link.l1 = "Co sądzisz? Powinniśmy ruszyć do Caracas?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "Osobiście bym nie poszedł, Kapitanie. I radziłbym ci również tego nie robić. Dla Ligi nie jesteś już wrogiem, a ja nie jestem dla nich interesujący, przynajmniej na razie, dopóki jestem w twojej służbie. Poza tym, mam to paskudne przeczucie głęboko w środku.\nBędzie źle, jeśli tam pójdziemy. Bardzo źle. Ta historia nie ma szczęśliwego zakończenia. Ale będę z tobą do końca, Kapitanie.";
			link.l1 = "Rozważę to.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "A tak przy okazji, miałeś rację - nie zdołali wystarczająco dobrze oczyścić kopalni. Spójrz.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "Dziennik oficera... zaszyfrowany, ale to stary szyfr, znam go\nNic interesującego, jak się zdaje. To był dziennik naszego więźnia. Teraz jasne, dlaczego był tak skory do rozmowy. Spójrz tutaj - wskazówki dotyczące ukrytego skarbu! Drań wyraźnie planował przejść na emeryturę i był gotów wymknąć się w każdej chwili!";
			link.l1 = "I gdzie jest to ukryte miejsce?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "Znasz tę wyspę, Kapitanie. W jej wodach zakończyłeś Van Berda.";
			link.l1 = "Dobrze, to niedaleko, więc sprawdźmy to. Co do Caracas, jeszcze nie zdecydowałem, ale myślę, że mamy miesiąc.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "Jak sobie życzysz, Kapitanie. Jestem z tobą do końca.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "It's done, Captain. Austin is currently in Caracas; I think we have a month.";
			link.l1 = "Najpierw najważniejsze. Co powiedział więzień? Kim jest ten Austin? I dlaczego powinniśmy jechać do Caracas?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "Banda Austina była sławna z wabiących wolnych Kapitanów w dzicz, ćwiartowania ich i całkowitego ograbienia ich zwłok z pieniędzy czy błyskotek. Dobry interes, a poszukiwaczy przygód nigdy nie brakowało, więc nikomu to nie przeszkadzało. Ale natknęli się na przeszkodę z jednym Kapitanem, więc musiał wziąć swoją załogę pod skrzydła Kompanii. Trzymaliśmy go na smyczy i wypuszczaliśmy tylko wtedy, gdy potrzebowaliśmy rozwiązać problemy w szybki i prosty sposób.";
			link.l1 = "Wątpię, że mogę wynegocjować umowę z taką osobą.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "To pewne. Jeśli on i jego ludzie teraz rządzą, wkrótce Liga stanie się po prostu kolejną bandą. Ale ja bym nie szedł do Caracas, Kapitanie.";
			link.l1 = "Serio? Boisz się?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "To nie tak, kapitanie. Przed śmiercią z powodu ran, więzień wyjawił, że nie jesteś już wrogiem Ligi, a ja nie interesuję ich, przynajmniej na razie, dopóki jestem w twojej służbie. Wygląda na to, że Liga ma nowego wpływowego protektora, który nakazał zostawić nas w spokoju.\nA Caracas... Mam to paskudne przeczucie w głębi... Będzie źle, jeśli tam pójdziemy. Bardzo źle. Ta historia nie ma szczęśliwego zakończenia. Ale będę z tobą do końca, kapitanie.";
			link.l1 = "Pomyślę o tym. Oczywiście, chciałbym rozwiązać tę sprawę raz na zawsze, ale może masz rację. Wątpię, by po wydarzeniach z zeszłego tygodnia odważą się znowu się do nas zbliżyć.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "A propos, miałeś rację - nie udało im się wystarczająco dobrze oczyścić kopalni. Spójrz.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "Dziennik oficera... zaszyfrowany, ale to stary szyfr, znam go\nNic interesującego, jak się zdaje. To był dziennik naszego więźnia. Spójrz tutaj - wskazówki dotyczące ukrytego skarbu! Drań wyraźnie planował przejść na emeryturę i był gotów zniknąć w każdej chwili!";
			link.l1 = "A gdzie jest to ukryte miejsce?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "Wiesz, ta wyspa, Kapitanie. W jej wodach zakończyłeś Van Berda.";
			link.l1 = "Dobrze, to niedaleko, więc sprawdźmy to. Jeśli chodzi o Caracas, jeszcze nie zdecydowałem, ale myślę, że mamy miesiąc.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "Jak sobie życzysz, kapitanie.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "Trzymaj się, kapitanie. Idę tam sam.";
			link.l1 = "And why is that? Feeling heroic now? It's too late; you've made this mess, but we have to clean it together.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "Nie musisz płacić za moje błędy, Kapitanie. Miałeś rację - gdziekolwiek pójdę, ludzie umierają, a niewinna krew płynie. Jeśli wejdziemy razem do tego kościoła, to będzie jak kolejne Porto Bello, a ja tego nie chcę.";
			link.l1 = "Co tam się naprawdę wydarzyło?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "Masakra. Chciałem przejść na emeryturę, Kapitanie. Chciałem zabrać złoto, moją żonę i wrócić do domu w Carcassonne. Wiedziałem, że Liga wyśle więcej ludzi, by dokończyć moją robotę, i wziąłem hojną zaliczkę od nowego mecenasa. Potem pozostało tylko napuścić straż miejską na moich dawnych wspólników i nowego pracodawcę. W tym całym zamieszaniu miałem zniknąć z pieniędzmi, a jeśli czas pozwoli, obrabować kilka tłustych kotów z Porto Bello.";
			link.l1 = "Dobry plan, choć zrobiłbym to inaczej. Zbyt wiele rzeczy może pójść nie tak.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "Sam nie jestem aniołem, ale twoje podejście sprawia, że nawet ja drżę. Jestem zaskoczony, że jeszcze mnie nie zdradziłeś, jak to zrobiłeś z Ligą, Hidalgiem, a nawet własną żoną.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "Everything that could go wrong, did go wrong. Shooting a three-pounder towards the governor's palace was a mistake. It barely scratched the governor himself, but his beautiful daughter, as I hear, had to have both her legs amputated below the knees to save her life. The response was horrific - a blood bath; great many people perished, Captain. Now you're looking at the last living witness to those events, and not long ago, you cut down another one yourself.";
			link.l1 = "Wyjaśnij.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "Gdyby Madame Tonzag wciąż żyła, zdradziłbym cię bez wahania, kapitanie. Jestem żywym trupem, podążającym za tobą, bo nie mam innego miejsca na tym świecie. Teraz patrzysz na ostatniego żyjącego świadka tamtych wydarzeń, a niedawno sam skróciłeś o głowę innego.";
			link.l1 = "Wyjaśnij.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "Przebacz mi, Kapitanie, że nie powiedziałem ci wszystkiego po drodze. Kiedy się spotkaliśmy, myślałem, że jesteś tylko kolejnym łajdakiem jak ja. I wiesz, co zrobiłem najpierw? Wysłałem cię, żebyś po mnie posprzątał - zabić tego hiszpańskiego Don, którego początkowo nie chciałem zabić, a potem zdecydowałem się zdradzić. Tego Hidalgo, Rodrigueza...";
			link.l1 = "A po cóż ci był jego palec?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "Bez sztuczek. To tylko próba, Kapitanie. Zatrudniamy tuziny młodych rzezimieszków jak ty każdego roku. Tylko nieliczni przechodzą podstawowy test uczciwości, a nawet oni giną w pierwszych operacjach. Nie miałeś przetrwać operacji z dziennikiem Fleetwooda. Planowałem po prostu wejść do domu, wykończyć ocalałych i zabrać dziennik.";
			link.l1 = "Jeśli mnie pamięć nie myli, historia potoczyła się nieco inaczej.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "Tak było, Kapitanie. Nie wiem, co skłoniło mnie do pomocy, ale walczyłeś z Lisami z taką żądzą życia, że nawet mnie tym zaraziłeś, choćby na chwilę. W końcu, nieświadomie, uratowałeś mnie. Nic mi nie jesteś winien, Kapitanie. I nie wpuszczę cię tam. To moje sprawy, moje odkupienie.";
			link.l1 = "Jak sobie życzysz, Hercule. Boli tracić takiego wojownika, ale ty zgubiłeś się dawno temu i nie jesteś wart więcej przelanej krwi. Nie jesteś mi też nic dłużny, i mam nadzieję, że znajdziesz odkupienie w tym małym kościele.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "Ładna przemowa, Hercul. Idź do diabła! Jeśli nie zauważyłeś, twoje problemy ostatnio stały się moimi. Jesteś moim oficerem i tylko ja zdecyduję, czy zasługujesz na przebaczenie czy nie. Więc będziesz musiał zostać z nami trochę dłużej i zasłużyć na swoje odkupienie odwagą jako część mojej załogi!";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "Dziękuję za wszystko, kapitanie. Żegnaj!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "Tak jest, Kapitanie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "Widziałem w swoim czasie wielu łajdaków, kapitanie, ale po raz pierwszy poczułem wewnętrzny dreszcz grozy. Jak myślisz: jeśli mniejszy potwór zabije większego potwora, czy to liczy się jako odkupienie?";
			link.l1 = "Czy oni rozcieńczają rum wodą? Powiedz mi, kiedy się dowiesz. Chodźmy, skończyliśmy tutaj.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;

	}
}