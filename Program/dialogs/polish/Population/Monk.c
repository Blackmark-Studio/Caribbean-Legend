//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "Dobry dzień tobie, synu mój. Proszę cię o okazanie łaski i ofiarowanie kilku srebrnych monet na dobro biednych, twojej duszy i Świętej Matki Kościoła.";
					link.l1 = "Cóż, ojcze, przypuszczam, że wszyscy musimy sobie nawzajem pomagać, jak nas uczy Chrystus i Jego Kościół. Czy możesz mi powiedzieć, na co zostaną przeznaczone te pieniądze?";
					link.l1.go = "donation";
					link.l2 = "Przebacz mi, ojcze, ale jestem teraz biedny jak mysz kościelna.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "Dzień dobry, mój synu. Chciałbym cię prosić o przysługę. Oczywiście zapłacę.";
					link.l1 = "Słucham cię, ojcze. Czego potrzebujesz?";
					link.l1.go = "passenger";
					link.l2 = "Przepraszam, ojcze, ale muszę iść.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Witaj, mój synu. Zakładam, że jesteś kapitanem. Mam więc dla ciebie propozycję.";
					link.l1 = "Słucham, ojcze.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Witaj, synu. Co cię trapi?","Witaj, synu. Zobacz się z pastorem, jeśli chcesz się wyspowiadać.","Pozdrowienia, synu mój. 'Pamiętaj o Stwórcy swoim za dni młodości swojej.'"),LinkRandPhrase("Witaj, mój synu. Co cię trapi?","Miłego dnia, mój synu, niech Bóg cię błogosławi!","Dzień dobry, mój synu, niech oblicze Boga zajaśnieje nad tobą!"));
				link.l1 = LinkRandPhrase("To samo dla ciebie, ojcze. Jak się masz?","Dobry dzień, ojcze. Jak się ma twoja parafia?","Jak się masz, ojcze?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Mam do ciebie pytanie, ojcze.","Potrzebuję informacji.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Ojcze, mam ludzi na moim statku. Są to niewolnicy, zarówno chrześcijanie, jak i nieochrzczeni poganie. Chcę, abyś ochrzcił pogan i udzielił komunii chrześcijanom. Potem uwolnię ich wszystkich na chwałę Boga i naszego Kościoła.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Ojcze, chcę, abyś pobłogosławił mój statek i odprawił mszę za moją załogę. Ile to by kosztowało?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Przepraszam, ojcze, ale muszę iść.","Przepraszam, że niepokoję cię, ojcze.","Muszę wrócić na mój statek, ojcze. Żegnaj!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("Znowu ty, mój synu? Czego chcesz?","Masz mi coś jeszcze do powiedzenia, synu mój?","Dobrze cię znów widzieć, mój synu.");
				link.l1 = LinkRandPhrase("To samo dla ciebie, ojcze. Jak się miewasz?","Dzień dobry, ojcze. Jak się ma twoja parafia?","Jak się masz, ojcze?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Mam do ciebie pytanie, ojcze.","Potrzebuję informacji.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Ojcze, mam ludzi na moim statku. Są to niewolnicy, zarówno chrześcijanie, jak i nieochrzczeni poganie. Chcę, abyś ochrzcił pogan i udzielił komunii chrześcijanom. Następnie uwolnię ich wszystkich na chwałę Boga i naszego Kościoła.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Ojcze, chcę, abyś pobłogosławił mój statek i odprawił mszę za moją załogę. Ile by to kosztowało?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Przepraszam, ojcze, ale muszę iść.","Przepraszam, że cię niepokoję, ojcze.","Muszę wracać na mój statek, ojcze. Żegnaj!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "  Mam dla ciebie pilną sprawę, mój synu. Muszę dostarczyć te dokumenty pastorowi do "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Rodzaj")+"Żeglujesz w tamtym kierunku? Dokumenty muszą być dostarczone w ciągu dwóch tygodni...";
				link.l1 = "Łatwo, ojcze. Daj mi te dokumenty, a dostarczę je do "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Rodzaj")+".";
				link.l1.go = "Monkletter";
				link.l2 = "Byłbym zadowolony, ojcze, ale żegluję w innym kierunku.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "Mój synu, czy zgodzisz się pomóc mi w pilnej sprawie? Naszemu kościołowi kończą się Biblie i modlitewniki, które dajemy wszystkim potrzebującym\nCzy mógłbyś popłynąć do najbliższej kolonii "+NationNameGenitive(sti(npchar.nation))+", aby odebrać kilka Biblii i modlitewników z lokalnego kościoła i przynieść je tutaj? I postaraj się to zrobić w ciągu jednego miesiąca, bo niewiele ich nam zostało.";
				link.l1 = "Z przyjemnością pomogę waszemu kościołowi. Czy mogę dostać te książki od dowolnego pastora?";
				link.l1.go = "Churchbooks";
				link.l2 = "Byłbym zadowolony, ojcze, ale nie mogę tego zrobić teraz.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("W porządku, mój synu. Dziękuję za miłe słowa.","Nasza parafia ma się dobrze, mój synu. Dziękuję za twoją troskę.");
			link.l1 = "Muszę już iść, ojcze.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Oczywiście, mój synu. "+sTemp+" ";
			link.l1 = "Jaka darowizna byłaby uznana za wystarczającą?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "Wszystko zależy od twojej sakiewki i osobistego życzenia, mój synu. 'Bóg kocha radosnego dawcę.' Jesteśmy głęboko wdzięczni za każdą darowiznę.";
			link.l1 = "100 pesos";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 peso";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 pesos";
			link.l3.go = "donation_rate_3";
			link.l4 = "10000 pesos";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Dziękuję za monety, mój synu! Pójdą na szczytny cel!";
				link.l1 = "Proszę bardzo, święty ojcze.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "„Nie łudźcie się, Bóg nie dozwala z siebie szydzić. Co człowiek sieje, to i żąć będzie. Kto sieje w ciele swoim, z ciała też zbierać będzie zgniliznę. Ale kto sieje w duchu, z ducha zbierać będzie życie wieczne.”";
				link.l1 = "Ha-ha! Oszczędź kazanie, nie zajmuję się dobroczynnością. Zjeżdżaj!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Dziękuję ci, mój synu. Ta suma naprawdę pomoże naszej misji parafialnej. Niech cię Bóg błogosławi!";
				link.l1 = "Powodzenia, ojcze!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "Boża odpłata czeka na ciebie, łotrze! Szydzenie z sługi świętego Kościoła Chrystusowego to bluźnierstwo!";
				link.l1 = "Ha-ha! Nie zajmuję się charytatywnością. Zjeżdżaj!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Nie mogłem nawet sobie wyobrazić, że będziesz tak hojny, mój synu! Wspomnę o tobie w moim następnym liście do naszego biskupa i będziemy się za ciebie modlić każdego dnia! Błogosławię cię i z wdzięcznością przyjmuję twoje pieniądze!";
				link.l1 = "Pieniądze są niczym, jeśli nie są używane dla Bożego celu! Powodzenia, ojcze!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "Kara Boża czeka na ciebie, łotrze! Szydzenie z sługi świętego Kościoła Chrystusa to bluźnierstwo!";
				link.l1 = "Ha-ha! Nie zajmuję się dobroczynnością. Zmykaj!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "Cóż... Czy dobrze cię usłyszałem? Naprawdę ofiarujesz dziesięć tysięcy pesos!? Błogosławię cię i z wdzięcznością przyjmuję twoje pieniądze. Wspomnę o tobie w moim następnym liście do naszego biskupa i będziemy modlić się za ciebie każdego dnia! To ogromna pomoc dla Kościoła!";
				link.l1 = "'Komu wiele dano, od tego wiele wymagać się będzie', prawda? Powodzenia, święty ojcze.";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "Boża kara czeka na ciebie, łotrze! Szydzenie z sługi świętego kościoła Chrystusa to bluźnierstwo!";
				link.l1 = "Ha-ha! Nie prowadzę działalności charytatywnej. Zjeżdżaj!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Oczywiście, mój synu. To nasz święty obowiązek pomagać tym biednym nieszczęśnikom. Zrobię to, o co prosisz.";
			link.l1 = "Dziękuję, ojcze. Przekażę dziesięć sztuk srebra za każdego ochrzczonego i obsłużonego więźnia.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "Choć to nie jest konieczne, z wdzięcznością przyjmuję twoją opłatę za skradzioną rzecz. Twoje pieniądze pójdą na różne misje w naszej parafii. Czy mógłbyś mnie zaprowadzić do swojego statku?";
			link.l1 = "Tak, ojcze. Chodź za mną.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 7;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(7-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(7-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(7-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(7-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
				case 6:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
			}
			dialog.text = "To wszystko zależy od całkowitej liczby statków w twojej eskadrze i ich rozmiaru.";
			link.l1 = " "+sTemp+"Got it. Please provide the text you want translated.";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "To będzie cię kosztować "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", mój synu.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "Mogę zapłacić ci tę sumę, ojcze. Weź pieniądze.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "Niestety, nie mam przy sobie tyle pieniędzy.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Dobrze, synu mój. Pozwól, że zbiorę święte naczynia i udamy się do portu.";
			link.l1 = "Chodź za mną, ojcze.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"The priest has held mass aboard your ship and blessed it", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "Cześć kapitanie, pozwól mi się przedstawić. Jestem księdzem i mam spore doświadczenie jako kapelan na pokładzie okrętów wojennych. Opuściłem swój ostatni statek, ponieważ kapitan i ja mieliśmy pewne... moralne nieporozumienia. Chcesz mnie przyjąć do swojej załogi?";
			link.l1 = "Kapłan na pokładzie? Powiedz mi ojcze, czym zajmuje się kapelan na statku?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "Ach, to całkiem oczywiste. Modlę się do Boga za ciebie i twą załogę, codziennie odprawiam mszę, błogosławię twoich ludzi i wysłuchuję spowiedzi przed bitwą. Słowo Boże daje siłę rękom i duchom twojej załogi. Twoja załoga będzie miała możliwość regularnie przystępować do komunii i spowiedzi. Wierz mi, żeglarz w stanie łaski wytrwa w sytuacjach, w których bezbożnik się załamie\nNie proszę o wiele dla siebie: jednorazową wpłatę pięćdziesięciu tysięcy pesos dla mojej parafii, prostą koję w kabinie i wyżywienie takie, jakie mają twoi oficerowie. To wszystko.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "Interesujące... Masz rację, dobry kapitan musi troszczyć się nie tylko o ciała swojej załogi, ale i o ich dusze. Witaj na pokładzie, ojcze!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "Nie, ojcze. Przykro mi, ale nie stać mnie na twoje usługi.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Dziękuję za twoje zaufanie, mój synu. Mądrze wydałeś swoje pieniądze. Ale ostrzegam cię, służę tylko godnym kapitanom, czy to kupcom, czy kaprom, to nie ma znaczenia. Ale nigdy nie będę głosił na pokładzie pirackiego statku!\nZatem jeśli kiedykolwiek wciągniesz diabelską Jolly Roger, natychmiast opuszczę twój statek w pierwszym porcie.";
			link.l1 = "Rozważę to, ojcze, i postaram się cię nie zawieść. Proszę, wejdź na pokład i przedstaw się załodze!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
			pchar.questTemp.ShipCapellan.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.ShipCapellan.Yes = "true";//капеллан в команде
			Achievment_Set("ach_69");
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			npchar.reputation = 60;
		break;
		
		case "capellan_4":
			dialog.text = "Potrzebujesz czegoś, mój synu?";
			link.l1 = "Nie, to nic, ojcze.";
			link.l1.go = "exit";
			link.l2 = "Padre, chciałbym, abyś opuścił statek w następnym porcie. Nie będę się więcej tłumaczyć.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "Zgoda, mój synu. Ty tu dowodzisz. Opuzczę twój statek w następnej osadzie.";
			link.l1 = "Dziękuję za zrozumienie, ojcze.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "Phi, kapitanie! Ostrzegałem cię, że opuszczę twój statek, jeśli podniesiesz piracką flagę! Opuszczam twój statek w następnym porcie. Będę się modlił o twoje natychmiastowe nawrócenie i powrót na łono Świętej Matki Kościoła.";
			link.l1 = "No do diabła...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "Mój "+GetSexPhrase("synu","córka")+", Muszę się dostać do "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" zaczyna się "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"To")+", dla "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+"Zapłacę ci "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" za to. Co powiesz?";
			}
			else
			{
				dialog.text = "Mój "+GetSexPhrase("synu","córka")+", Pan działa w tajemniczy sposób, dlatego szukam niezawodnego kapitana. Czy możesz pomóc mi dotrzeć do "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+", który jest na "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Ta")+"? Rozumiem, że to jak wyprawa do ognistej Gehenny, ponieważ nasi wrogowie nigdy nie śpią. I rozumiem, że nie jesteś Jezusem Chrystusem, ale ja również nie jestem apostołem, dlatego mam pewne oszczędności. Czy "+FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money))+" wystarczy dla ciebie?";
			}
			link.l1 = "Zgadzam się, ojcze.";
			link.l1.go = "passenger_1";
			link.l2 = "Przepraszam, ojcze, ale płynę w innym kierunku. Nie mogę ci pomóc.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "To jest wola Boża dla wszystkich, mój synu. Poczekam na inny statek. Pokój z tobą!";
			link.l1 = "Żegnaj, ojcze.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Niech Bóg cię błogosławi! Dostaniesz swoją zapłatę, gdy dotrzemy do celu.";
			link.l1 = "Udaj się na mój statek, ojcze. Wkrótce wypływamy.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Dziękuję, mój "+GetSexPhrase("synu","córka")+"Spełniłeś swoją obietnicę i teraz moja kolej. Weź swoje pieniądze, jak obiecałem.";
			link.l1 = "Dziękuję. Powodzenia, ojcze.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Proszę. Weź tę paczkę, synu mój. Pamiętaj, że masz tylko dwa tygodnie na dostarczenie jej. Pastor czeka na nią. Idź, i niech Bóg będzie z tobą!";
			link.l1 = "Nie zawiodę cię, ojcze. Żegnaj.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Tak. Możesz je dostać w każdej kolonii "+NationNameGenitive(sti(npchar.nation))+"Przynieś wszystkie książki, które znajdziesz, naszemu pastorowi w kościele. Niech Bóg cię błogosławi!";
			link.l1 = "Dzięki! Wkrótce otrzymasz swoje książki.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","a hospital")+". The local citizens give little in alms so I must ask prosperous men like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit the house of God, but everyone must do his best in saving his own soul." break;
		case 2: sText = "I am gathering money to buy food and medicines for our poorhouse for the sick, widows, orphans, and infirm. Please donate sir, because there but for the grace of God go all of us." break;
		case 3: sText = "I am gathering money for new sacred vessels, the ones which we brought from Europe are battered with continual use. It's a duty for every Christian to take care of our Church." break;
		case 4: sText = "I am gathering money for our church's renovation, the roof is leaking terribly and the pews have to be repaired too. It's a duty for every Christian to take care of our Church." break;
		case 5: sText = "I am gathering money to pay the good artist who is able to paint the walls of our church and draw scenes from the Bible on them for those of our parish who cannot read. It's a duty for every Christian to take care about his Church." break;
		case 6: sText = "I am gathering money for a new high altar for our church. Our parish is poor and we would like a noble seat for the Blessed Sacrament. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from pirate raids in our hospital. They need medicines and bandages. Pray help them, for you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for clothes and food for our poorest citizens. The only hope they have is our holy church. Please help them." break;
		case 9: sText = "I am going to go deep in our island for missionary work to bring the light of Christ's Gospel to the lost souls of the pagan Indians. I am gathering funds for this expedition. Please help our good deed!" break;
	}
	return sText;
}
