// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Ośmielasz się pokazywać swoją twarz w biurze generała-gubernatora?! Naprawdę jesteś szalony...","Jak to się stało, że te leniwe siermięgi pozwoliły wrogowi wtargnąć do mojej rezydencji? To przekracza ludzkie pojęcie...","Z pewnością, moi strażnicy nie są warci grosza, jeśli jakiś włóczęga biega po mojej rezydencji..."),LinkRandPhrase("Czego potrzebujesz, "+GetSexPhrase("łotrze","cwaniaro")+"?! Moi żołnierze już ruszyli za twoim śladem, "+GetSexPhrase("brudny piracie","gówniaro")+"!",""+GetSexPhrase("Brudny","Brudny")+" morderco, natychmiast opuść moją rezydencję! Strażnicy!","Nie boję się ciebie, "+GetSexPhrase("łajdaku","cwaniaro")+"! Niedługo będziesz wisieć w naszym forcie, daleko nie uciekniesz..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Żołnierze nie są warci twojej plugawej kasy...","Nigdy mnie nie dostaniesz."),RandPhraseSimple("Zamknij się, kumplu, albo wyrwę ten twój brudny język!","Mówię ci, kumplu: siedź cicho, albo odetnę ci głowę i wrzucę przez te drzwi do twoich stróżujących psów..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Słyszałem, że byłeś bardzo natarczywy w żądaniu audiencji. Nazywam się "+GetFullName(npchar)+". Jestem gubernatorem generalnym kolonii "+NationNameGenitive(sti(NPChar.nation))+", zastępca Korony "+NationKingsName(npchar)+" na tych wodach. Teraz, proszę, bądź tak miły i powiedz mi, jaki jest cel twojej wizyty, "+GetAddress_Form(NPChar)+".";
				link.l1 = "Mam na imię "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("O, to znowu ty? No dobrze, czego chcesz od gubernatora-generalnego "+NationNameGenitive(sti(NPChar.nation))+" tym razem?","I znowu, przeszkadzasz mi w ważnych sprawach państwowych? Czego chcesz, "+GetAddress_Form(NPChar)+"?");
				link.l1 = "Chcę porozmawiać z tobą o pracy w imieniu Korony "+NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "Muszę z tobą porozmawiać o jednej ważnej sprawie.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "Przybyłem na zaproszenie, aby wziąć udział w regatach. Oto moje zaproszenie.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "Przykro mi, ale mam trochę spraw do załatwienia.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "Więc jaki był powód, dla którego przyszedłeś tutaj i odciągnąłeś mnie od ważnych spraw państwowych?";
			link.l1 = "Chciałem porozmawiać z tobą o pracy w imieniu Korony "+NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "Miałem z tobą rozmawiać o jednej ważnej sprawie.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "Przybyłem tutaj, aby wziąć udział w regatach. Oto moje zaproszenie.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "To tylko wizyta z uprzejmości, nic więcej, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "W takim razie poproszę cię o opuszczenie mojego biura i przestanie przeszkadzać mi w pracy.";
			link.l1 = "Tak, tak, oczywiście. Przepraszam za kłopot.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "Jeśli szukasz pracy, rozmawiaj z gubernatorami kolonii. Często potrzebują mądrych i odważnych kapitanów.";
			link.l1 = "Zapamiętam to. Dziękuję Ci.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "Och, świetnie, cieszę się, że cię widzę, kapitanie! Przybyłeś w samą porę - regaty zaczynają się za kilka dni. Czy przeczytałeś zasady regat w liście, który powinien zostać ci przekazany przez posłańca?";
			link.l1 = "Tak, panie, zrobiłem.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "A czy przygotowałeś 50000 peso - twoją opłatę za wejście, która przyczyni się do puli nagród?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Tak, oczywiście. Proszę przyjąć moją opłatę.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "W tej chwili trochę mi brakuje pieniędzy. Ale na pewno przyniosę je tak szybko, jak tylko mogę.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Dobrze. Jeśli wygrasz - twoje pieniądze wrócą do ciebie pięciokrotnie. Teraz powinieneś wiedzieć, jak nie złamać zasad regaty.\nOmów szczegóły z Henry Stevensonem, powinien być w pokoju rezydencji. Spotkaj się z nim, on wszystko ci wyjaśni.";
			link.l1 = "Dobrze. Zrobię jak mówisz.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Dobrze, ale proszę, nie zasypiaj gruszek w popiele, kapitanie. Regata zaraz się zacznie.";
			link.l1 = "Rozumiem. Spróbuję przynieść ci pieniądze przed rozpoczęciem regat.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "I oto mamy zwycięzcę regat! Witaj, kapitanie "+GetFullName(pchar)+"! Pozwól mi pogratulować ci tego zasłużonego sukcesu! Zwycięzcy regat są zawsze popularni w angielskich koloniach, zasłużenie popularni.";
			link.l1 = "Dziękuję, panie!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Teraz przejdźmy do najbardziej przyjemnej części dla ciebie - ceremonii wręczenia nagród. Pierwsza nagroda w pieniądzach to 250000 pesos. Proszę bardzo!";
			link.l1 = "Dzięki!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Ponadto, masz prawo do zestawu cennych nagród: "+sAdd+". Teraz to wszystko twoje.";
			link.l1 = "Jestem bardzo zadowolony, panie! Naprawdę, nie mogłem tego oczekiwać.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "W imieniu wszystkich angielskich kolonii, z przyjemnością dziękuję Ci za udział w regacie i ponownie gratuluję Ci zwycięstwa! Jeśli obstawiałeś, teraz jest idealny czas, aby odwiedzić Sir Henry'ego Stevensona i odebrać swoje wygrane, jeśli jeszcze tego nie zrobiłeś. Powodzenia, kapitanie!";
			link.l1 = "Dziękuję za te miłe słowa, panie! Z kolei pozwól mi podziękować za możliwość uczestnictwa w tak wielkim wydarzeniu. A teraz, proszę pozwól mi pożegnać się i odejść.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
