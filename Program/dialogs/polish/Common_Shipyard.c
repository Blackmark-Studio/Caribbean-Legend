// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
	if(!CheckAttribute(NPChar, "ExpMeeting"))
	{
		NPChar.ExpMeeting = true;
		notification("Pierwsza wizyta w stoczni " + XI_ConvertString("Colony" +NPChar.City + "Gen"), "Carpenter");
		AddCharacterExpToSkill(pchar, SKILL_REPAIR, 10.0);
	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Alarm został podniesiony w mieście i wszyscy cię szukają. Gdybym był tobą, nie zostawałbym tutaj.","Wszyscy strażnicy miasta przeczesują miasto w poszukiwaniu ciebie. Nie jestem głupcem i nie będę z tobą rozmawiał!","Uciekaj, "+GetSexPhrase("kamracie","dziewczyno")+"...zanim żołnierze zamienią cię w sito..."),LinkRandPhrase("Czego potrzebujesz, "+GetSexPhrase("łotrze","śmierdziel")+"?! Strażnicy miasta już cię wyczuli, daleko nie uciekniesz, plugawy piracie!","Morderco, natychmiast opuść mój dom! Strażnicy!","Nie boję się ciebie, "+GetSexPhrase("draniu","szczur")+" ! Wkrótce zostaniesz powieszony w naszym forcie, daleko nie uciekniesz... "));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, alarm nie stanowi dla mnie problemu...","Nie złapią mnie nigdy."),RandPhraseSimple("Zamknij gębę, "+GetWorkTypeOfMan(npchar,"")+", albo wyrwę ci język!","Heh, "+GetWorkTypeOfMan(npchar,"")+", a tam też - by złapać piratów! To ci mówię, kumplu: bądź cicho, a nie zginiesz!"));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "Czy chce pan coś, monsieur?";
					Link.l1 = "Przyszedłem obejrzeć twoje statki... Ale teraz jestem trochę zajęty - mam jeszcze niedokończoną sprawę. Przyjdę później, jak tylko się z nią uporam.";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = "Czy czegoś pan sobie życzy, monsieur?";
					Link.l1 = "Słuchaj, chciałbym kupić od ciebie statek.";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "Czy chce pan jeszcze czegoś, monsieur?";
				Link.l1 = "Nie, chyba nie.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "To już wszystko, Kapitanie. Robota skończona. Teraz ta przyjemniejsza część - brzęk monet. Daj mi chwilę...";
					link.l1 = "... ";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "Oficerze, zaczekaj! Proszę! To musi być jakaś pomyłka. Monsieur, kapitan nie ma z tym nic wspólnego, on tylko zacumował tutaj, by naprawić swój statek. Właśnie miał odpłynąć. A jakie beczki? O czym ty mówisz?";
					link.l1 = " ";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "Oficerze, powtarzam: Kapitan przyszedł tutaj, aby zapłacić za naprawy statku. Te beczki są moją własnością i służą wyłącznie do celów produkcyjnych. Jestem mistrzem budowy statków, a ta żywica jest dla statków, które buduję.";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "O, Monsieur Kapitanie! Nie masz pojęcia, jak źle mi się wiodło. Dwa dni w lochach w towarzystwie szczurów, myszy i nędznych postaci! Musiałem użyć wszystkich swoich znajomości, by się stamtąd wydostać. Ach, to świeże powietrze!";
					link.l1 = "Masz moje współczucie, mistrzu. Co z naszą żywicą? A moje monety?";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "O, to znowu ty! Rozpoznaję cię, młodzieńcze! To ty niedawno pytałeś o... zwiększenie prędkości swojego statku za pomocą jedwabnego żaglowca, prawda?";
				link.l1 = "Twoja pamięć przynosi ci chwałę, mistrzu."; 
				link.l1.go = "mtraxx_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Ha! Prawdziwy stary wilk morski przyszedł do mego pokornego warsztatu! Czy jesteś nowy na tych wodach, kapitanie?","Witaj, Panie! Jeśli nie jesteś obcy morzu i masz statek - trafiłeś we właściwe miejsce!","Witaj, Panie! Masz szczęście - to najlepsza stocznia w całym brytyjskim Nowym Świecie."),LinkRandPhrase("Monsieur, przypuszczam, że jesteś dzielnym kapitanem, prawda? Jeśli tak, to dobrze zrobiłeś, odwiedzając mój skromny warsztat!","Pierwszy raz tutaj, Monsieur Kapitanie? Wejdź i poznaj tego starego szkutnika.","Pozwólmy sobie na przyjemność poznania się, Monsieur! Statek trzeba pieścić, jak kobietę - a my, Francuzi, jesteśmy w tym ekspertami! Zaufaj mi, nie pożałujesz, że tu przyszedłeś!"),LinkRandPhrase("Nie widziałem cię tu wcześniej, Senor. Miło cię poznać!","Witam dzielnego zdobywcę mórz! Jesteś żeglarzem, prawda? A ja jestem miejscowym szkutnikiem, powinniśmy się poznać.","Witaj, Caballero! Z radością witam cię w moim warsztacie!"),LinkRandPhrase("Dzień dobry, Panie. Nie mieliśmy jeszcze przyjemności się spotkać, prawda? Czy ma Pan do mnie jakąś sprawę?","Witaj, Mynheer Kapitanie. Nie bądź zdziwiony, spotkałem już wielu Kapitanów, więc od razu zorientowałem się, że i ty jesteś Kapitanem.","Wejdź, mości panie. Jestem miejscowym szkutnikiem. Miło cię poznać."));
				Link.l1 = LinkRandPhrase("Również cieszę się, że mogę cię poznać. Nazywam się "+GetFullName(pchar)+", a ja jestem nowy w tych stronach. Więc postanowiłem wpaść.","Po prostu nie mogłem przejść obok - wiesz, ten zapach świeżo struganych desek... Jestem "+GetFullName(pchar)+", Kapitan statku '"+pchar.ship.name+".'","Pozwól, że się przedstawię - "+GetFullName(pchar)+", Kapitan statku '"+pchar.ship.name+"Miło mi cię poznać. Więc, budujesz i naprawiasz tu statki, prawda?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "Witaj, kapitanie MacArthur.";
					link.l1 = "Możesz mnie po prostu nazywać Helen, panie "+npchar.lastname+". "+TimeGreeting()+".";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh! Postrach tutejszych wód, Kapitanie "+GetFullName(pchar)+"! Co mogę dla ciebie zrobić?","Przejdźmy od razu do interesów, "+GetAddress_Form(NPChar)+", nie mam czasu na pogawędki. Potrzebujesz naprawy, czy chcesz tylko wymienić swoją wannę?","O, czyż to nie "+GetFullName(pchar)+" ! Co słychać, "+GetAddress_Form(NPChar)+"Coś złego stało się z twoją łajbą?"),LinkRandPhrase("Czego tam potrzebujesz, Kapitanie? Ani chwili spokoju - zawsze ci wszyscy łajdacy, co za przeklęty dzień...","Witaj, "+GetAddress_Form(NPChar)+"Muszę powiedzieć, że twoja wizyta odstraszyła wszystkich moich klientów. Mam nadzieję, że twoje zamówienie pokryje moje straty?","Na interesy ze mną, "+GetAddress_Form(NPChar)+"Cóż, zabieraj się do tego, i to szybko."),LinkRandPhrase("Co cię do mnie sprowadza, panie "+GetFullName(pchar)+"? Rozumiem, że twój statek może mieć trudności, zważywszy na twój styl życia...","Cieszę się, że mogę powitać szlachetnego... och, przepraszam, "+GetAddress_Form(NPChar)+", Wziąłem cię za kogoś innego. Czego chciałeś?","Nie przepadam za twoim typem, kapitanie, ale nie wyrzucę cię stąd. Czego chciałeś?")),LinkRandPhrase(LinkRandPhrase("Bardzo się cieszę, że cię widzę, panie "+GetFullName(pchar)+"! Jak się sprawuje? Potrzebujesz naprawy czy dokowania?","Witaj, "+GetAddress_Form(NPChar)+"! Kapitanie "+GetFullName(pchar)+" jest zawsze mile widzianym gościem w moim warsztacie!","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Znowu mnie odwiedzasz! Mam nadzieję, że twoja piękność ma się dobrze, prawda?"),LinkRandPhrase(" "+GetAddress_Form(NPChar)+", tak się cieszę, że znów cię widzę! Jak tam twój piękny statek? Potrzebujesz pomocy?","Oh, "+GetAddress_Form(NPChar)+", witaj! Jak się masz? Może maszty skrzypią albo trzeba oczyścić zęzę? Moi ludzie zrobią wszystko, co w ich mocy, aby Ci pomóc!","Dzień dobry, Kapitanie "+GetFullName(pchar)+" . Cieszę się, że znowu wpadłeś, i zawsze jestem gotów ci pomóc."),LinkRandPhrase("Miło mi Cię widzieć, Kapitanie! Jesteś bardzo miłym klientem, "+GetAddress_Form(NPChar)+", i życzę, abyś taki pozostał.","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Naprawdę cieszę się, że jesteś tutaj! Co mogę dla ciebie zrobić?","Kapitanie, znów odwiedziłeś "+XI_ConvertString("Colony"+npchar.City+"Acc")+"Wierz mi, z przyjemnością ci pomożemy.")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Zbierz swoje narzędzia, mistrzu, i milcz, dobrze? Nie jestem w nastroju.","Przestań paplać, kumplu! Potrzebuję twojej pomocy, a nie twojej gadaniny."),RandPhraseSimple("Ja płacę - a ty pracujesz. W ciszy. Jasne?","„Hej, kumplu, przegoń ich wszystkich – to ja, twój ulubiony klient!”")),RandPhraseSimple(RandPhraseSimple("Cieszę się, że cię widzę, mistrzu. Niestety, nie mam zbyt wiele czasu, więc przejdźmy do interesów.","Ja też się cieszę, że cię widzę, kumplu. Chcesz pomóc swojemu ulubionemu klientowi?"),RandPhraseSimple("Dzień dobry, kamracie. Przejdźmy od razu do interesów. Obiecuję, następnym razem na pewno usiądziemy nad butelką.","Cieszę się, że cię widzę, mistrzu. Zawsze przyjemnie cię widzieć, ale teraz potrzebuję twojej pomocy.")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "Potrzebuję dział dla mojego statku.";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "Czy możesz mi zaoferować coś specjalnego, czego nie znajdę w żadnej innej stoczni?";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "Nie masz pracy, do której potrzebna jest pomoc obcego?";
			    link.l15.go = "Tasks";
				// Jason Исла Мона 
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "Chcę kupić zestaw narzędzi do budowy, kucia i mierzenia europejskiej jakości. Czy możesz mi pomóc?";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "Przyniosłem dukaty na zestaw narzędzi budowlanych.";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "Przyniosłem ci "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+" , jak prosiłeś.";
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "Zdołałem odnaleźć złodzieja i odzyskać "+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Chcę zmienić wygląd moich żagli.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Chciałem tylko porozmawiać.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Chciałbym z tobą porozmawiać o sprawach finansowych.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Jestem tutaj na prośbę jednego człowieka. Jego imię to Gubernator "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" przysłał mnie do ciebie. Mam odebrać coś...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Przyniosłem rysunek statku z "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "Witam, przyszedłem na zaproszenie twojego syna."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "Chodzi o twoją córkę...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "Muszę iść.";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "Jestem bardzo zadowolony, że mogę poznać nowego klienta. Moja stocznia jest do Twojej dyspozycji.";
				Link.l1 = "Doskonale, "+GetFullName(NPChar)+" Spójrzmy, co możesz mi zaoferować.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Potrzebuję dział na mój statek.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Czy nie masz pracy, która wymaga pomocy obcego?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Chcę zmienić wygląd moich żagli.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Chciałem tylko porozmawiać.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Chciałbym porozmawiać z tobą o sprawach finansowych.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Jestem tu na prośbę pewnego człowieka. Jego nazwisko to Gubernator "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" wysłał mnie do ciebie. Mam coś odebrać...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = " Dostarczyłem rysunek statku z miasta "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Witaj, przyszedłem na zaproszenie twojego syna."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "To dotyczy twojej córki...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Co możesz mi powiedzieć o właścicielu tych dokumentów?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Muszę odejść, dziękuję.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "Oczywiście, Kapitanie MacArthur, jak sobie życzysz. Czego dziś potrzebujesz?";
				Link.l1 = "Wspaniale, "+GetFullName(NPChar)+"Zobaczmy, co możesz mi zaoferować.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Potrzebuję armat dla mojego statku.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Nie masz roboty, do której potrzebna jest pomoc obcego?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Chcę zmienić wygląd moich żagli.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Chciałem tylko porozmawiać.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Chciałbym porozmawiać z tobą o sprawach finansowych.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Jestem tu na prośbę pewnego człowieka. Jego imię to Gubernator "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" wysłał mnie do ciebie. Mam odebrać coś...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Dostarczyłem rysunek statku z miasta "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Cześć, przyszedłem na zaproszenie twojego syna."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "To dotyczy twojej córki...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Co możesz mi powiedzieć o właścicielu tych dokumentów?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Muszę iść, Dziękuję.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "Nasza stocznia słynie z ulepszania statków. Czy jesteś zainteresowany, Kapitanie?";
			Link.l1 = LinkRandPhrase("Doskonale! Może mógłbyś spojrzeć na mój statek i powiedzieć mi, jak można go ulepszyć?","To bardzo interesujące, mistrzu! A co możesz zrobić dla mojego statku?","Hmm... Wiesz, przyzwyczaiłem się do mojego statku, ale jeśli zaoferujesz mi coś naprawdę interesującego, mogę się nad tym zastanowić. Co powiesz?");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 7)
				{
					dialog.Text = "Errr... Nie zajmuję się łajbami. Stary kocioł nadal będzie starym kotłem, bez względu na to, ile wysiłku w to włożysz.";
					Link.l1 = "Widzę...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour legendary edition -->
				if(!TuningAvailable())
				{
					dialog.Text = "Tak sobie... zobaczmy, co tu mamy... Tak - "+XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName)+"Twoja łajba ma już maksymalną liczbę ulepszonych cech, obawiam się, że dalsza praca nad nią nie ma sensu i może tylko zaszkodzić.";
					Link.l1 = "Widzę...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// <-- legendary edition							
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "Zanim ulepszymy statek, musi być w pełni naprawiony. To również można zrobić tutaj, w mojej stoczni.";
					Link.l1 = "Zrozumiano...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "Alright, let's see what we've got here... Aha " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				// belamour legendary edition -->
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " Our shipyard is famous for improving the ship's performance we can increase either the maximum speed or the angle to the wind.";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " At our shipyard we can increase the maximum number of cannons or the ship's carrying capacity.";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " My guys can reinforce the hull of your ship or increase the maximum number of sailors in your crew.";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " At this shipyard you can improve the maneurability or decrease the minimum number of sailors in the crew.";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour legendary edition -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "Zwiększ prędkość.";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "Zwiększ kąt do wiatru.";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "Poczekaj! Zmieniłem zdanie.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "Zwiększ prędkość.";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "Chwileczkę! Zmieniłem zdanie.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "Zwiększ kąt względem wiatru.";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "Zaczekaj! Zmieniłem zdanie.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("O! Mój statek jest już w ten sposób ulepszony. No cóż, dziękuję za czas!","Dziękuję, mistrzu, ale już mam ulepszenie, i to dokładnie takie, o którym mi wspomniałeś. Powodzenia z innymi statkami i ich kapitanami!","Heh! Sądzę, że mój statek został już wcześniej przebudowany przez poprzedniego właściciela - musiało to być w tej właśnie stoczni. Cóż, muszę mu podziękować za jego przezorność, a tobie i twoim chłopakom za doskonałą robotę!");
						Link.l1.go = "ship_tunning_not_now_1";					
					}
						// <-- legendary edition
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "Zwiększ maksymalną liczbę dział.";
							Link.l1.go = "ship_c_quantity";
						}	
							Link.l2 = "Zwiększ nośność.";
							Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "Chwila! Zmieniłem zdanie.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "Zwiększ maksymalną liczbę dział.";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "Zaczekaj! Zmieniłem zdanie.";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}	
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "Zwiększ nośność.";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "Trzymaj się! Zmieniłem zdanie.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("O! Mój statek jest już ulepszony w ten sposób. Cóż, dziękuję za Twój czas!","Dziękuję, mistrzu, ale już mam ulepszenie, które dokładnie mi wspomniałeś. Powodzenia z innymi statkami i ich Kapitanami!","Heh! Zakładam, że mój statek już wcześniej został przebudowany przez poprzedniego właściciela - musiało to być w tej właśnie stoczni. Cóż, muszę podziękować mu za jego przewidywalność, a tobie i twoim ludziom za doskonałą robotę!");
						Link.l1.go = "ship_tunning_not_now_1";	
					// <-- legendary edition
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "Zwiększ trwałość kadłuba.";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "Zwiększ przestrzeń dla załogi.";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "Poczekaj! Zmieniłem zdanie.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "Zwiększ wytrzymałość kadłuba.";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "Chwila! Zmieniłem zdanie.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "Zwiększ przestrzeń dla załogi.";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "Trzymaj się! Zmieniłem zdanie.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("O! Mój statek został już w ten sposób ulepszony. Cóż, dziękuję za poświęcony czas!","Dziękuję, mistrzu, ale już posiadam ulepszenie, i to dokładnie to, o którym mi wspominałeś. Powodzenia z innymi statkami i ich Kapitanami!","Heh! Przypuszczam, że mój statek był już przebudowany wcześniej przez poprzedniego właściciela - musiało to być właśnie w tej stoczni. Cóż, muszę mu podziękować za jego przezorność, a tobie i twoim ludziom za doskonałą robotę!");
						Link.l1.go = "ship_tunning_not_now_1";	
						// <-- legendary edition
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "Zwiększ manewrowość.";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "Zmniejsz minimalną liczebność załogi.";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "Zaczekaj! Zmieniłem zdanie.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "Zwiększ manewrowość.";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "Chwila! Zmieniłem zdanie.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "Zmniejsz minimalną liczebność załogi.";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "Trzymaj się! Zmieniłem zdanie.";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// <-- legendary edition				
					}
					Link.l1 = LinkRandPhrase("O! Mój statek jest już w ten sposób ulepszony. Cóż, dziękuję za twój czas!","Dziękuję, mistrzu, ale już mam ulepszenie i jest dokładnie takie, o jakim mi wspominałeś. Powodzenia z innymi statkami i ich kapitanami!","Heh! Domyślam się, że mój statek został już wcześniej przystosowany przez poprzedniego właściciela - musiało to być właśnie w tej stoczni. Cóż, muszę podziękować mu za jego dalekowzroczność, a tobie i twoim ludziom za doskonałą robotę!");
					Link.l1.go = "ship_tunning_not_now_1";	
				}								
			}
			else
			{
				dialog.Text = "Gdzie jest statek? Czy ty sobie ze mnie żartujesz, czy co?";
			    Link.l1 = "Och, to moja wina, rzeczywiście... Przepraszam.";
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Well, let's see what we can do. At the moment the deadweight of your vessel is " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + ". For lighter bulkheads I will require: ironwood - " + Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";			
            dialog.Text = s2;
			Link.l1 = "Zgoda. Akceptuję twoje warunki. Przyniosę ci, czego tylko potrzebujesz.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "Nie. To mi nie odpowiada.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "Doskonale. Będę czekał na materiał.";
			    link.l1 = LinkRandPhrase("Zapewniam cię, że nie będziesz musiał długo czekać. Mogę rozwiązać takie kwestie, dobrze?","Uznaj, że już je masz i trzymaj mi dok dla mnie. Będę szybki jak wiatr.","Oczywiście. Muszę tylko odwiedzić kilka osób, które mają rzeczy, o które prosiłeś, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the tonnage of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nie widzę zaliczki...";
				link.l1 = "Odwiedzę cię później.";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Czas mija, a statek czeka. Czy przyniosłeś wszystko, o co prosiłem?";
			    Link.l1 = "Tak, udało mi się coś znaleźć.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = "Nie, nadal nad tym pracuję.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = "Misja"+GetSexPhrase("ter","s")+"czy zmieniłeś swój statek odkąd zawarliśmy nasze porozumienie? Nie powinieneś był tego robić.";
			    Link.l1 = "Ach, to wszystko okoliczności! Szkoda, że depozyt przepadł...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Doskonale, teraz mam wszystko, czego potrzebuję. Zabieram się do pracy, zatem.";
			    link.l1 = "Czekam.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Wciąż potrzebuję: żelaznego drewna - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Dobrze.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)* 0.65);
				}
				else
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
			}
			else
			{
				
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.35 + sti(shTo.Bonus_Capacity));
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}
			}
	        shTo.Tuning.Capacity = true;

	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "...Na tym chyba koniec... Teraz możesz w pełni załadować swój ładunek, gwarantuję jakość mojej pracy.";
			Link.l1 = "Dzięki! Przetestuję to.";
			Link.l1.go = "Exit";
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "Let's see what we can do, then. At the moment the speed of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " knots. In order to replace the sails I will require: sail silk - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
            dialog.Text = s2;
			Link.l1 = "Zgoda. Akceptuję twoje warunki. Przyniosę ci, co tylko potrzebujesz.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "Nie. To mi nie pasuje.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "Doskonale. Będę czekał na materiały.";
				link.l1 = LinkRandPhrase("Zapewniam cię, że nie będziesz musiał długo czekać. Mogę rozwiązać takie kwestie, dobrze?","Uważaj, że już je masz i trzymaj dla mnie dok. Będę szybki jak wiatr.","Oczywiście. Będę musiał tylko odwiedzić kilku ludzi, którzy mają rzeczy, o które prosiłeś, ha-ha!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the speed at " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". As the deposit was paid for " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nie widzę zaliczki...";
				link.l1 = "Odwiedzę cię później.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Czas leci, a statek czeka. Czy przyniosłeś wszystko, o co prosiłem?";
			    Link.l1 = "Tak, udało mi się coś znaleźć.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = "Nie, wciąż nad tym pracuję.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ter","s")+", czy zmieniłeś swój statek od czasu, gdy zawarliśmy umowę? Nie powinieneś.";
			    Link.l1 = "Ach, to wszystko okoliczności! Szkoda, że zaliczka przepadła...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Świetnie, teraz mam wszystko, czego potrzebuję. Zabieram się do pracy.";
			    link.l1 = "Czekam.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Wciąż potrzebuję: jedwab dla statku - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Dobrze.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) * 0.65);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.35 + stf(shTo.Bonus_SpeedRate);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}
			}
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Wszystko gotowe, Kapitanie. Łap wiatr w pełne żagle. Sprawdź, jeśli chcesz!";
			Link.l1 = "Dzięki! Przetestuję to.";
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "Let's see what we can do, then. At the moment the maneurability of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + " In order to add new sails to shake it up I shall require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";										
            dialog.Text = s2;
			Link.l1 = "Zgoda. Akceptuję twoje warunki. Przyniosę ci wszystko, czego potrzebujesz.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "Nie. To mi nie odpowiada.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "Doskonale. Będę czekał na materiał.";
				link.l1 = LinkRandPhrase("Zapewniam cię, że nie będziesz musiał długo czekać. Mogę takie sprawy rozwiązać, dobrze?","Uznaj, że już je masz i trzymaj dla mnie dok. Będę szybki jak wiatr.","Oczywiście. Muszę tylko odwiedzić kilka osób, które mają rzeczy, o które prosiłeś, ha-ha!");			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase agility by " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of  " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nie widzę zaliczki...";
				link.l1 = "Odwiedzę cię później.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Czas ucieka, a statek czeka. Czy przyniosłeś wszystko, o co prosiłem?";
			    Link.l1 = "Tak, udało mi się coś dostarczyć.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = "Nie, wciąż nad tym pracuję.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Misja"+GetSexPhrase("ter","s")+", czy zmieniłeś swój statek, odkąd zawarliśmy naszą umowę? Nie powinieneś tego robić.";
			    Link.l1 = "Niestety, to wszystko okoliczności! Szkoda, że depozyt przepadł...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Doskonale, teraz mam wszystko, czego potrzebuję. Zacznę pracować, więc.";
			    link.l1 = "Czekam.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Potrzebuję jeszcze: liny - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Dobrze.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	

	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
			dialog.Text = "... Wszystko powinno być już gotowe... Sprawdź teraz ster, Kapitanie!";
			Link.l1 = "Dzięki! Przetestuję to.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the maximum number of sailors in your crew, including overloading, is " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " men.";			
			s2 = s2 + " I will require: ironwood - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Zgoda. Przyjmuję twoje warunki. Przyniosę ci, czego tylko potrzebujesz.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "Nie. To mi nie odpowiada.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "Doskonale. Będę czekał na materiał.";
				link.l1 = LinkRandPhrase("Zapewniam cię, że nie będziesz musiał długo czekać. Mogę rozwiązać takie problemy, dobrze?","Uważaj, że już je masz i trzymaj dla mnie dok. Będę szybki jak wiatr.","Oczywiście. Muszę tylko odwiedzić kilka osób, które mają rzeczy, o które prosiłeś, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For their efforts to increase the crew of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nie widzę zaliczki...";
				link.l1 = "Odwiedzę cię później.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Czas płynie, a statek czeka. Czy przyniosłeś wszystko, o co prosiłem?";
			    Link.l1 = "Tak, udało mi się coś znaleźć.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = "Nie, wciąż nad tym pracuję.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ter","s")+", czy zmieniłeś swój statek, odkąd zawarliśmy nasze porozumienie? Nie powinieneś był tego robić.";
			    Link.l1 = "Ach, to wszystko okoliczności! Szkoda, że depozyt przepadł...";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Doskonale, teraz mam wszystko, czego potrzebuję. Zaczynam pracę, zatem.";
			    link.l1 = "Czekam.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Wciąż potrzebuję: żelaznego drzewa - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Dobrze.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew) * 0.65);
			}
			else
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
			}
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Zrobione, Kapitanie. Teraz możesz zatrudnić więcej marynarzy, będzie wystarczająco miejsca dla wszystkich.";
			Link.l1 = "Dzięki! Przetestuję to.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the minimum number of required sailors in your crew is " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " men.";			
			s2 = s2 + " To improve the controllability of the ship and to reduce the required number of sailors in the crew I will require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Zgoda. Akceptuję twoje warunki. Przyniosę ci, czego tylko potrzebujesz.";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "Nie. To mi nie pasuje.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = "Doskonale. Będę czekał na materiał.";
				link.l1 = LinkRandPhrase("Zapewniam cię, że nie będziesz musiał długo czekać. Mogę rozwiązać takie problemy, dobrze?","Uważaj, że już je masz i trzymaj dla mnie dok. Będę szybki jak wiatr.","Oczywiście. Będę musiał tylko odwiedzić kilka osób, które mają to, o co prosiłeś, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to reduce the minimum required number of crew on " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nie widzę zaliczki...";
				link.l1 = "Odwiedzę cię później.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Czas ucieka, a statek czeka. Czy przyniosłeś wszystko, o co prosiłem?";
			    Link.l1 = "Tak, udało mi się coś znaleźć.";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = "Nie, wciąż nad tym pracuję.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Misja"+GetSexPhrase("ter","s")+", czy zmieniłeś statek od czasu naszego układu? Nie powinieneś był tego robić.";
			    Link.l1 = "Niestety, to wszystko okoliczności! Szkoda, że depozyt został utracony...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Doskonale, teraz mam wszystko, czego potrzebuję. Zaczynam pracę.";
			    link.l1 = "Czekam.";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Wciąż potrzebuję: liny - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Dobrze.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	       if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.65);
			}
			else
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			}
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Gotowe, Kapitanie! Teraz mniejsza liczba marynarzy może obsługiwać statek z takim samym ogólnym wynikiem.";
			Link.l1 = "Dzięki! Przetestuję to.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what we can do, then. At the moment the ship's hull is " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + ". To reinforce the hull, I will require: resin - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Zgoda. Akceptuję twoje warunki. Dostarczę ci wszystko, czego potrzebujesz.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "Nie. To mi nie odpowiada.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "Doskonale. Będę czekał na materiał.";
				link.l1 = LinkRandPhrase("Zapewniam cię, że nie będziesz musiał długo czekać. Mogę rozwiązać takie sprawy, dobrze?","Uważaj, że już je masz i trzymaj dla mnie dok. Będę szybki jak wiatr.","Oczywiście. Muszę tylko odwiedzić kilka osób, które mają rzeczy, o które prosiłeś, ha-ha!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his efforts to increase the strength of the hull " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nie widzę zaliczki...";
				link.l1 = "Odwiedzę cię później.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Czas płynie, a statek czeka. Czy przyniosłeś wszystko, o co prosiłem?";
			    Link.l1 = "Tak, udało mi się coś znaleźć.";
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = "Nie, wciąż nad tym pracuję.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ter","s")+", czy zmieniłeś swój statek odkąd zawarliśmy naszą umowę? Nie powinieneś był tego robić.";
			    Link.l1 = "Niestety, to wszystko okoliczności! Szkoda, że depozyt przepadł...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Doskonale, teraz mam wszystko, czego potrzebuję. Zacznę pracować, zatem.";
			    link.l1 = "Czekam.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Wciąż potrzebuję: żywicy - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Dobrze.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP) * 0.65);
				}
				else
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.35 + sti(shTo.Bonus_HP));
				}
				else
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
				}
			}
	        shTo.Tuning.HP = true;
			shTo.BaseHP = sti(shTo.HP);

			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            NextDiag.TempNode = "First time";
			
			dialog.Text = "... To powinno załatwić sprawę... Gwarantuję, że od teraz twoi wrogowie będą mieli znacznie trudniejszy czas, by rozszarpać kadłub twojego statku na kawałki!";
			Link.l1 = "Heh, uwierzę na słowo! Dziękuję, mistrzu.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_REPAIR, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (acos(1 - stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed)) * 180.0/PI);
			s2 = "Let's see what we can do, then. At the moment the point of sail by the wind is " + makeint(fTmp) + " degrees.";
			// belamour legendary edition если спускать курс по ветру, то это даунгрейд
			s2 = s2 + " To accelerate the ship upwind, I will require: ship silk - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Zgoda. Akceptuję twoje warunki. Przyniosę ci, czego potrzebujesz.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "Nie. To mi nie pasuje.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "Doskonale. Będę czekał na materiał.";
				link.l1 = LinkRandPhrase("Zapewniam cię, że nie będziesz musiał długo czekać. Mogę rozwiązać takie sprawy, dobrze?","Uważaj, że już je masz i trzymaj dla mnie molo. Będę szybki jak wiatr.","Oczywiście. Wystarczy, że odwiedzę parę osób, które mają to, o co prosiłeś, ha-ha!");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work on changing the wind angle of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nie widzę zaliczki...";
				link.l1 = "Odwiedzę później.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "Czas mija, a statek czeka. Czy przyniosłeś wszystko, o co prosiłem?";
			    Link.l1 = "Tak, udało mi się coś dostarczyć.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = "Nie, wciąż nad tym pracuję.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Przewinienie"+GetSexPhrase("werft","s")+", czy zmieniłeś statek odkąd zawarliśmy naszą umowę? Nie powinieneś był.";
			    Link.l1 = "Niestety, to wszystko okoliczności! Szkoda, że depozyt przepadł...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Doskonale, teraz mam wszystko, czego potrzebuję. Zaczynam pracę.";
			    link.l1 = "Czekam.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "Wciąż potrzebuję: jedwab okrętowy - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Dobrze.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
			// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
			if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.35 * stf(shTo.WindAgainstSpeed);	
			}
			else
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);
			}
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;

			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Gotowe, Kapitanie!.. Teraz twoja łajba będzie płynąć pod wiatr znacznie szybciej.";
			Link.l1 = "Dzięki! Przetestuję to.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what can be done there. Right now, the number of cannons on your ship is " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", and the maximum possible number is - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + " I can tell you right away that it's not going to be cheap. I will require: resin - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
			dialog.Text = s2;		
			Link.l1 = "Zgoda. Akceptuję twoje warunki. Przyniosę ci wszystko, czego potrzebujesz.";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "Nie. To mi nie odpowiada.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "Doskonale. Będę czekał na materiał.";
				link.l1 = LinkRandPhrase("Zapewniam cię, że nie będziesz musiał długo czekać. Mogę rozwiązać takie problemy, dobrze?","Zważ, że już je masz i trzymaj dla mnie dok. Będę szybki jak wiatr.","Oczywiście. Muszę tylko odwiedzić parę osób, które mają rzeczy, o które prosiłeś, ha-ha!");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the number of cannons on the " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "Nie widzę zaliczki...";
				link.l1 = "Odwiedzę cię później.";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Czas ucieka, a statek czeka. Czy przyniosłeś wszystko, o co prosiłem?";
				Link.l1 = "Tak, udało mi się coś znaleźć.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "Nie, wciąż nad tym pracuję.";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ter","s")+", czy zmieniłeś swój statek odkąd się umówiliśmy? Nie powinieneś.";
			    Link.l1 = "Ach, to wszystko okoliczności! Szkoda, że depozyt przepadł...";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "Doskonale, teraz mam wszystko, czego potrzebuję. Zaczynam pracę, więc.";
				link.l1 = "Czekam.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Wciąż potrzebuję: żywicy - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Dobrze.";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "... To wszystko, Kapitanie. Możesz użyć dodatkowych dział - o ile je masz, he-he.";
			Link.l1 = "Dzięki!";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_CANNONS, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (hrand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "Mam problem, który trzeba rozwiązać. Mam zamówienie na statek - "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+". Jednakże na moim podwórzu nie ma teraz takiego statku i przez najbliższe dwa miesiące również nie mam możliwości zdobycia go.\nJeśli możesz mi dostarczyć taki statek - będę bardzo wdzięczny i zapłacę ci sumę półtora raza większą od jego ceny sprzedaży.";
					link.l1 = "Interesująca oferta. Zgadzam się!";
					link.l1.go = "Findship";
					link.l2 = "To mnie nie interesuje.";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (hrand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (hrand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "inside gage";
							pchar.GenQuest.Device.Shipyarder.Describe = "two hammered strips, connected with a joint unriveted on both ends";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "Swedish broad axe";
							pchar.GenQuest.Device.Shipyarder.Describe = "an axe on a long straight handle with a thin semicircular blade";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "groover";
							pchar.GenQuest.Device.Shipyarder.Describe = "a small axe, looking like a farmer's mattock";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "stockpile level";
							pchar.GenQuest.Device.Shipyarder.Describe = "two wooden bars of equal length, linked by the same third one, which has in the middle a rotating liquid-filled plate with an air bubble";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "barsik";
							pchar.GenQuest.Device.Shipyarder.Describe = "an ordinary flail, but the chain is rod-shaped and only moves in one direction";
						break; 
					}
					dialog.text = "Jesteś w samą porę. Być może będziesz w stanie mi pomóc. Ktoś ukradł mi wczoraj bardzo cenne narzędzie - "+pchar.GenQuest.Device.Shipyarder.Type+". Nie mam możliwości zrobić drugiego i nie mogę sobie pozwolić na czas ani koszt, aby zamówić to z Europy. A bez tego nie mogę normalnie budować statków, wiesz?\nA najbardziej irytujące jest to, że ta rzecz nie jest potrzebna nikomu poza stoczniowcami, a ja jestem jedynym stoczniowcem w kolonii. Ten złodziej nie sprzeda tego nikomu i po prostu wyrzuci. Może spróbujesz wytropić złodzieja, popytaj w mieście, ale ja po prostu nie mam czasu, aby być z dala od stoczni - pilnie muszę ukończyć specjalne zamówienia.";
					link.l1 = "Dobrze, spróbuję. Powiedz mi, jak wyglądało to... twoje urządzenie?";
					link.l1.go = "Device";
					link.l2 = "To mnie nie interesuje.";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = "Nie mam niczego takiego.";
			link.l1 = "Jak powiadasz.";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "Doskonale! Bardzo się cieszę, że udało ci się tak szybko. Gdzie jest ten statek?";
			link.l1 = "At the moment the vessel is at the roadstead; her name is '"+pchar.GenQuest.Findship.Shipyarder.ShipName+"'.";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "Oto twoje pieniądze - "+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+"   Dziękuję za robotę. Nie zapomnij odwiedzić mnie ponownie. Do widzenia!";
			link.l1 = "Do widzenia, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 5) iType = sti(RandPhraseSimple(its(SHIP_BARKENTINE), its(SHIP_SLOOP)));
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 11) iType = sti(RandPhraseSimple(its(SHIP_SHNYAVA), its(SHIP_BARQUE)));
			if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 16) iType = sti(RandPhraseSimple(its(SHIP_BRIG), its(SHIP_FLEUT)));
			if (sti(pchar.rank) >= 16) iType = sti(LinkRandPhrase(its(SHIP_CORVETTE), its(SHIP_POLACRE), its(SHIP_GALEON_L)));
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "Oczywiście, spróbuję wyjaśnić to prostymi słowami. Wygląda na to, że "+pchar.GenQuest.Device.Shipyarder.Describe+". To jedyny taki egzemplarz, więc rozpoznasz go bez trudu. Jeśli przyniesiesz mi ten instrument, sowicie ci zapłacę.";
			link.l1 = "Zrozumiano. Rozpocznę poszukiwania natychmiast!";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "Udało się! Nie masz pojęcia, jak bardzo jestem wdzięczny! Już straciłem wszelką nadzieję na odzyskanie mojego instrumentu.";
			link.l1 = "Oto proszę.";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "Za twoje wysiłki zapłacę ci "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+"Mam nadzieję, że to będzie zasłużona nagroda.";
			link.l1 = "Dzięki!";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "Oprócz tego chciałbym złożyć ci ofertę, jako dodatkowe podziękowanie.";
				link.l1 = "To ciekawe. Cóż, śmiało - lubię miłe niespodzianki.";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "Właśnie zwodowałem nowy statek - "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType,"Imię")+"Przyjęte"))+". Jest już kilku klientów na ten statek, ale dam ci pierwszeństwo. Jeśli podoba ci się ten statek i nie przeraża cię cena - możesz go kupić.";
			link.l1 = "Heh! Pewnie, spójrzmy na to!";
			link.l1.go = "Device_complete_4";
			link.l2 = "Dziękuję, ale mój obecny statek mi odpowiada i nie zamierzam go wymieniać.";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста		   
		break;
		
		case "Device_complete_5":
			dialog.text = "Cóż, jak sobie życzysz. Jeszcze raz dziękuję - i powodzenia!";
			link.l1 = "Powodzenia i Tobie!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Pozwól, że spojrzę... Nie, nie było tu nikogo takiego. Myślę, że powinieneś udać się do kapitana portu w tej sprawie.";
				link.l1 = "Oczywiście...";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Let me take a look, Captain! A-ha! Those are the ship documents of a good friend of mine, my favorite customer! I am sure he will be extremely happy because of your find and will reward you deservedly.";
				sTemp = sTemp + "I guess I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos on his behalf";
				dialog.text = sTemp;
				link.l1 = "Nie, nie sądzę...";
				link.l1.go = "exit";
				link.l2 = "Dziękuję, "+GetFullName(NPChar)+"Proszę przekazać moje wyrazy szacunku Pańskiemu przyjacielowi.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "Słucham cię uważnie.";
			link.l1 = "Przyprowadziłem twojego uciekiniera.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "O, Kapitanie, bardzo ci dziękuję! Jak się ma? Czy jest ranna? Dlaczego uciekła? Dlaczego?\nCzy ona tego nie rozumie? Pan młody to bogaty i ważny człowiek! Młodość jest naiwna i głupia... nawet okrutna. Pamiętaj o tym!";
			link.l1 = "Cóż, jesteś jej ojcem i ostateczna decyzja należy do ciebie, ale nie spieszyłbym się z tym ślubem...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Cóż ty wiesz? Masz własne dzieci? Nie? Jak już będziesz miał, przyjdź do mnie, porozmawiamy.\nObiecałem nagrodę każdemu, kto ją odprowadzi do rodziny.";
			link.l1 = "Dzięki. Powinieneś mieć na nią oko. Mam przeczucie, że na tym nie poprzestanie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "O, więc to ty jesteś tym Kapitanem, który przywiózł mojemu synowi marnotrawnemu młodą pannę?";
				link.l1 = "Tak, to byłem ja.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "O, tam "+GetSexPhrase("jest, nasz dobroczyńca","jest, nasza dobrodziejka")+"Spodziewam się nagrody, czyż nie?";
				link.l1 = "Cóż, obejdę się bez nagrody, dobre słowo od was wystarczy.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Jestem ci bardzo wdzięczny, że nie porzuciłeś mojego dziecka w trudnej sytuacji i pomogłeś mu znaleźć wyjście z delikatnej sytuacji. Pozwól mi podziękować ci i, proszę, przyjmij tę skromną sumę i prezent ode mnie osobiście.";
			link.l1 = "Dzięki. Pomoc tej młodej parze była dla mnie przyjemnością.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Dzięki? Jakie dzięki?! Już pół roku ten matoł wałęsa się bez roboty - i spójrz na niego, ma czas na miłosne romanse! Kiedy ja byłem w jego wieku, już prowadziłem własny interes! Pff! Gubernator ma córkę na wydaniu - a ten gamoń przyprowadził do mojego domu ladacznicę bez rodu i śmiałość miał prosić o moje błogosławieństwo!";
			link.l1 = "Hmm... Najwidoczniej, nie wierzysz w szczere uczucia?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Jakie uczucia? O jakich uczuciach mówisz? Uczucia... jak można być tak lekkomyślnym w twoim wieku?! Wstydź się, że pobłażasz młodym w ich kaprysach i zachowujesz się jak stręczyciel! Nie tylko zabrałeś dziewczynę z domu, ale także zrujnowałeś życie mojego żółtodzioba. Nie będzie ci za to podziękowań. Żegnaj.";
			link.l1 = "Dobrze, i to samo dla ciebie...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Żartujesz sobie ze mnie? Gdzie jest twój statek? Nie widzę go w porcie!","Przysięgam na diabła, nie oszukasz mnie! Twój statek nie jest w porcie!"),pcharrepphrase("Nie widzę twojego statku w porcie, kapitanie "+GetFullName(pchar)+" Mam nadzieję, że to nie jest 'Latający Holender'?","Kapitanie, dużo łatwiej jest załadować towar z nabrzeża. Przyprowadź swój statek do portu i wróć."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(" "+RandSwear()+"Co za kłopot! Dobrze, stary chytrusie, do zobaczenia wkrótce!","Nie chciałem cię oszukać, "+GetFullName(npchar)+", statek po drugiej stronie wyspy."),pcharrepphrase("Nie. Mój statek nazywa się 'Czarna Perła'! Co się stało z twoją twarzą? Jest blada... Haha! Żart!","Dzięki za radę, na pewno to zrobię."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Żartujesz sobie ze mnie? Gdzie jest twój statek? Nie widzę go w porcie!","Przysięgam na diabła, nie oszukasz mnie! Twój statek nie jest w porcie!"),pcharrepphrase("Nie widzę twojego statku w porcie, kapitanie "+GetFullName(pchar)+" Mam nadzieję, że to nie jest 'Latający Holender'?","Kapitanie, znacznie łatwiej załadować ładunek z nabrzeża. Przyprowadź swój statek do portu i wracaj."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Co za kłopot! Dobrze, stary spryciarzu, do zobaczenia wkrótce!","Nie chciałem cię oszukać, "+GetFullName(npchar)+", statek po drugiej stronie wyspy."),pcharrepphrase("Nie. Mój statek nazywa się 'Czarna Perła'! Co się stało z twoją twarzą? Jest blada... Haha! Żartuję!","Dzięki za radę, na pewno to zrobię."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "Zmiana koloru żagli kosztuje "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+", zmiana herbu kosztuje "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSGERALD_PRICE_RATE))+", wymiana żagli - zależy od twojego statku.";
							  
			    link.l1 = "Wybierz nowy kolor.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "Odwzoruj nowy herb.";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "Zamontuj unikalne żagle."; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = "Zmieniam zdanie.";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Żartujesz sobie? Gdzie jest twój statek? Nie widzę go w porcie!","Przysięgam na diabła, nie oszukasz mnie! Twój statek nie jest w porcie!"),pcharrepphrase("Nie widzę twojego statku w porcie, kapitanie "+GetFullName(pchar)+" Mam nadzieję, że to nie jest 'Latający Holender'?","Kapitanie, o wiele łatwiej jest załadować ładunek z nabrzeża. Przyprowadź swój statek do portu i wróć."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Co za kłopot! Dobrze, stary chytrusie, do zobaczenia wkrótce!","Nie chciałem cię oszukać, "+GetFullName(npchar)+", statek po drugiej stronie wyspy."),pcharrepphrase("Nie. Mój statek nazywa się 'Czarna Perła'! Co się stało z twoją twarzą? Jest blada... Haha! Żart!","Dzięki za radę, na pewno tak zrobię."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "Jakie żagle chcesz zamontować? W tej chwili masz "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = "Chcę zainstalować "+GetSailsType(6)+".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "Chcę zainstalować "+GetSailsType(7)+".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "Chcę zainstalować "+GetSailsType(8)+".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "Chcę zainstalować "+GetSailsType(9)+".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "Chcę zainstalować "+GetSailsType(10)+".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "Chcę zainstalować "+GetSailsType(11)+".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = "Zmieniam zdanie.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "Na chwilę obecną masz "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+", wybrałeś "+GetSailsType(sti(NPChar.SailsTypeChooseIDX))+"Koszt wymiany to "+FindRussianMoneyString(sti(NPChar.SailsTypeMoney))+"Kontynuować?";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "Tak.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "Nie.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "Świetnie! Wszystko będzie w porządku.";
		    Link.l9 = "Dzięki.";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "Jaki kolor wybierzemy? Cena to "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "Zmieniam zdanie.";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "Przyjdź, gdy będziesz miał pieniądze.";
			    Link.l9 = "Dobrze.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "Zgoda. Pomalujemy żagle na "+GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name))+" kolor.";
		    Link.l9 = "Dzięki.";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "Niestety, twój statek nie może nosić herbu.";
				    Link.l9 = "Szkoda.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "Wróć, gdy będziesz miał pieniądze.";
			    Link.l9 = "Dobrze.";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "Przykro mi, że muszę cię rozczarować, monsieur, ale w tej chwili nie mam żadnych statków na sprzedaż.";
			link.l1 = "To naprawdę dziwne, bo powiedziano mi, że masz zupełnie nowy lugier na swojej stoczni.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "Wiecie, to prawdopodobnie chodzi o lugier, za który kaucja wynosi trzy tysiące pesos od Michela de Monpera? Otóż ten statek został już sprzedany, ponieważ zgodnie z umową cała kwota miała być zapłacona nie później niż tydzień po wodowaniu statku.\nWszystkie terminy minęły, a pieniędzy nie otrzymałem, więc lugier został sprzedany. Bardzo mi przykro, panie.";
				link.l1 = "Tak, to było rzeczywiście pechowe... Ale czy jesteś pewien, że nie masz innych statków na sprzedaż?";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "Hmm. Tak, rzeczywiście. Ale...";
			link.l1 = "A na nią już jest zaliczka - pięć tysięcy peso. Michel de Monper, który wpłacił pieniądze, przekazał mi wszelkie prawa do tego statku.";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "Zostały ci "+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = "Today is the last day";
			dialog.text = "A zatem, skoro tak, wróćmy do naszej rozmowy, Panie. Jak słusznie zauważyłeś, mam zaliczkę pięciu tysięcy pesos na statek. Ale pełna wartość statku to, jak sądzę, piętnaście tysięcy pesos, wraz z amunicją. Więc zapłać mi dziesięć tysięcy, a statek będzie twój.\nZgodnie z umową, musisz zapłacić pieniądze najpóźniej tydzień po spuszczeniu statku na wodę. "+sTemp+", a potem mogę sprzedać ten statek innemu klientowi. I, proszę mi wierzyć, już jest taki, więc lepiej się pośpiesz.";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "Nie ma potrzeby się spieszyć. Mam przy sobie wymaganą sumę. Proszę bardzo.";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "Dobrze, dobrze. Będziesz miał swoje pieniądze, Monsieur. Nie każę ci długo czekać.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "Czy mogę ci pomóc, monsieur?";
				Link.l1 = "Wpadłem tylko rzucić okiem na dostępne statki... Ale teraz jestem trochę zajęty – mam niedokończoną sprawę do załatwienia. Wrócę, jak tylko się z nią uporam.";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "Monsieur, ostrzegałem cię, że masz tylko trzy dni do dyspozycji. Czas minął, a ty nadal nie przyniosłeś mi pieniędzy, więc nasza umowa wygasła, i sprzedałem statek innemu klientowi. Bez urazy.";
					link.l1 = "Tak, to było rzeczywiście dość pechowe... Ale czy jesteś pewien, że nie masz innych statków na sprzedaż?";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "Czy przyniosłeś mi dziesięć tysięcy, monsieur?";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "Oczywiście, że mam. Proszę bardzo.";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "Nie, wciąż nad tym pracuję.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "W takim razie pozwól mi pogratulować tego udanego zakupu. Statek jest twój. Mam nadzieję, że będzie ci dobrze służył.";
			link.l1 = "Dzięki!";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = "Adeline";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "Hmm... Cóż, mam jedną, właściwie, ale nie jestem pewien, czy by ci odpowiadała.";
					link.l1 = "Cóż, teraz nie mogę sobie pozwolić na zbytnią wybredność. Pokaż mi, co masz!";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "Słuchaj, monsieur, najpierw zarób fortunę, a potem pytaj o statki, dobrze? Nikt tutaj nie da ci nic za darmo. Czy wyraziłem się jasno?";
					link.l1 = "Doskonale jasne, chociaż nie było potrzeby być niegrzecznym. Dobrze, wrócę, gdy będę miał pieniądze.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "W takim razie, spójrz. Niedawno nabyłem w rozsądnej cenie jedną slup. Był to dawny statek piracki, a jego dawni właściciele zostali już bezpiecznie powieszeni za liczne zbrodnie. Statek, szczerze mówiąc, nie jest tak dobry jak lugier i ma również poważne uszkodzenia, ale nadal można go wypuścić na morze.\nNie mam teraz czasu na jej naprawę - wszyscy moi ludzie są zajęci budową brygu, który został zamówiony, więc możesz go ode mnie kupić w takim stanie, w jakim jest. Biorąc to pod uwagę, sprzedam go taniej niż zwykle, wliczając również zawartość ładowni - piętnaście tysięcy pesos.";
			link.l1 = "Zgoda. Jest zdolna do żeglugi, i to jest wszystko, co się liczy. Gwadelupa jest rzut beretem - naprawię ją tam, jeśli nie masz takiej możliwości.";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "W takim razie pozwól, że pogratuluję ci tego udanego zakupu. Statek jest twój. Mam nadzieję, że będzie ci dobrze służył.";
			link.l1 = "Dzięki!";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipExt(SHIP_SLOOP, true, pchar);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew"); */
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "Więc, Monsieur, wróciłeś z pieniędzmi?";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "Tak, myślę, że mam wystarczająco, by pozwolić sobie na podniszczony statek.";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "Jeszcze nie mam wystarczająco. Wpadłem tylko rozejrzeć się...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "Niestety, mój przyjacielu, ale obaj tutaj ucierpieliśmy. Skonfiskowali żywicę, a do tego zmarnowałem ogromne sumy pieniędzy na kaucję. I jakim cudem dowiedzieli się o naszej operacji? Musi to być jeden z moich pracowników... Zajmę się tym, niech Bóg zlituje się nad winowajcą!";
			link.l1 = "Wszystkie moje wysiłki poszły na marne...";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "Bardzo mi przykro, Kapitanie. Nic tu nie możemy zrobić, los bywa czasem sukinsynem.";
			link.l1 = "Rozumiem. Dobrze, w takim razie się pożegnam. Żegnaj!";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = "Chciałbym wrócić do tej rozmowy. Jestem gotów dać porządną zniżkę... bardzo znaczną zniżkę na jakiekolwiek prace na twoim statku... jeśli dostarczysz mi trochę dodatkowego jedwabiu...";
			link.l1 = "Mistrzu, przejdźmy od razu do sedna. Obiecuję, że nie jestem szpiegiem, ani jednym z ludzi pułkownika D'Oyleya. Co więcej, współpracuję z Marcusem Tyrexem, a to nazwisko powinno być ci znajome. Więc, połóżmy karty na stół. Wiem, że potrzebujesz stałych dostaw jedwabnego żaglowego płótna, a Marcus Tyrex jest gotów ci je dostarczać. Również regularnie. Jednak tylko pod warunkiem, że zgodzimy się na cenę. Czy możemy od razu do tego przejść, mistrzu?";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = "Dobrze. Wygląda na to, że nie mam wyboru - albo pracujesz dla D'Oyleya i poślesz mnie do więzienia, albo zbankrutuję, jeśli pilnie nie znajdę dużej dostawy jedwabiu. Jestem gotów zapłacić 25 dublonów za sztukę, ale tylko za duże dostawy, nie mniej niż 100 bel.";
			link.l1 = "W takim razie mamy umowę. Jestem pewien, że Tyrex jest w stanie dostarczać ci przesyłki po 100 bel miesięcznie.";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = "To byłoby doskonałe! Mógłbym od razu zakupić pierwszą partię.";
			link.l1 = "Nie mogę tego zrobić teraz, ale to nie potrwa długo. Statek z potrzebnym ładunkiem jest obecnie w Capsterville, natychmiast tam zmierzam i wyślę go do ciebie. Gdzie mamy przeprowadzić rozładunek?";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = "Zróbmy to tak. Między 10 a 15 każdego miesiąca, nocą, moi ludzie będą czekać na twoich gości w zatoce... nie, czekaj, lepiej na Cape Negril. To pewnie będzie długa droga, ale jest dużo mniej patroli... Hasło będzie: 'Kupiec z Lyonu'.";
			link.l1 = "Umowa stoi, mistrzu. Wyruszam do Capsterville od razu.";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = "Mam nadzieję, że twój statek przybędzie szybko, bardzo potrzebuję nowego jedwabiu.";
			link.l1 = "Nie martw się, wszystko będzie dobrze. Szczęść Boże!";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "Nie, "+pchar.name+"Nie mam nic przeciwko tobie, ale najpierw rozwiąż swoje problemy z moim krajem. Sprzedaż tak cennego inwentarza wrogowi Korony mogłaby zostać źle zrozumiana.";
					link.l1 = "Tak, a kiedy przemycasz przemycane towary o niejasnym pochodzeniu na statki, to jesteście najlepszymi przyjaciółmi? Poczekaj, aż rozwiążę to nieporozumienie.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Powiedzmy. Dlaczego? Budujesz coś?";
					link.l1 = "Nie, wykonuję bardzo specjalny czarter. Dla zarządcy plantacji.";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "Nie mogę ci pomóc.";
				link.l1 = "To wstyd!";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
            dialog.text = "Widzę. Mam nadzieję, że ten zarządca dostarczył ci wystarczająco, bo za taki zestaw policzyłbym sporo. Masz szczęście, że niedawno przybył import z metropolii.";
			link.l1 = "Ile?";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
            dialog.text = "Jeden tysiąc złotych dublonów.";
			link.l1 = "Widzę, że jesteś przegrzany. Jestem w porządku. Wezmę to.";
			link.l1.go = "IslaMona_7";
			link.l2 = "To zbyt wiele. Wątpię, aby znalazł się inny kupiec na cały zestaw, jak ja. Część się wyprzeda, część zostanie skradziona przez miejscowych włóczęgów. Co powiesz na zniżkę?";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				notification("Skill Check Failed (60)", SKILL_COMMERCE);
				dialog.text = " Gwarantuję, że się znajdzie. Cena bez zmian. Co ty na to? Nie będę czekał długo. ";
				link.l1 = "Dobrze, dobrze, dobrze. Wezmę to.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "Dobrze, weźmiemy sto. Dziewięćset. Nie zejdę niżej. Nie proś mnie o to.";
				link.l1 = " I nie będę. Zgadzam się.";
				link.l1.go = "IslaMona_7";
				link.l2 = "Może dacie mi trochę więcej? Jako hurtownik. A wtedy zamówię u was naprawy i farby, a także najwspanialszą galionową figurkę.";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				notification("Skill Check Failed (85)", SKILL_COMMERCE);
				dialog.text = "Nie obchodzi mnie, czy zamawiasz żywą dziewkę. Dziewięćset.";
				link.l1 = "Dobrze, dobrze, dobrze. Wezmę to.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "Jesteś pewien? Nie zapomnisz? Dobrze, zetnijmy kolejną setkę. Ale to już wszystko!";
				link.l1 = "Nie zapomnę. Umowa stoi!";
				link.l1.go = "IslaMona_7";
				link.l2 = "Cóż, jakby to ująć...";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
            dialog.text = "Niewyobrażalne! "+pchar.name+", zapomnieli wyjąć śrut z twojej czaszki? Chciwy jak skorpion! Wszyscy słyszeliśmy o twoich ostatnich eskapadach! Już zarobiłeś swoją kupę złota, więc nie przeszkadzaj innym w zarabianiu swoich. Jeszcze jedno słowo i nie sprzedam za mniej niż tysiąc.";
			link.l1 = "Dobrze, dobrze! Spokojnie. Zgadzam się.";
			link.l1.go = "IslaMona_7";
			link.l2 = "Ale, "+npchar.name+", mam małe dzieci! Muszę o nich też myśleć! Nie płacą wystarczająco za uczciwy fracht, wiesz o tym!";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				notification("Skill Check Failed (100)", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "Dzieci dziewcząt z burdelu się nie liczą, "+pchar.name+"Rzygam tobą. Tysiąc doublonów na beczce, albo się żegnamy.";
				link.l1 = "Co masz na myśli, że nie są? Uh-huh. Zgadzam się, jesteś oszustem.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "Nie wiedziałem, że masz dzieci. I że sprawy mają się tak źle. Dobrze, nie narzekaj. Siedemset. To prawie strata.";
				link.l1 = "Nie zapomnę. Umowa stoi!";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
            dialog.text = "Więc jesteś mi winien "+sti(pchar.questTemp.IslaMona.Shipyarder.Money)+"  дублоны.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "Oto, daję ci ostatnie, nic już nie mam.";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (GetCharacterItem(pchar, "gold_dublon") < 1)
				{
					link.l1 = "Poczekaj, idę do lichwiarza, by zaciągnąć dług.";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "To wszystko, co mam przy sobie "+FindRussianDublonString(GetCharacterItem(pchar,"złoty dublon"))+"Weź to, a ja pójdę do lichwiarzy.";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-GetCharacterItem(pchar, "gold_dublon");
			Log_Info("You gave "+FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon"))+"");
			RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
			PlaySound("interface\important_item.wav");
            dialog.text = "Nie współczuj mi, masz w kajucie skrzynię pełną złota. Będziesz mi winien "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+".";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("You gave "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+"");
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
            dialog.text = "To świetnie. Cała kwota jest gotowa. Narzędzia zostaną dostarczone na twój statek. To są jakieś ciężkie skrzynie.";
			link.l1 = "Dziękuję, "+npchar.name+"!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) <= 27) iRank = 3;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = iShip;
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (8 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + hrand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 2;
			break;
			case 6: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
    }
}