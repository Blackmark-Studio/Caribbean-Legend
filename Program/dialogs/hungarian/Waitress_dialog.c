// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "Mit kíván, senor? Sajnálom, én csak...'zokog'... ó... sajnálom.";
					link.l1 = "Miért vagy ennyire feldúlt, úrnôm? Könnyek egy ilyen gyönyörû arcon? Mi történt?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! "+UpperFirst(GetAddress_Form(NPChar))+", segítsen! Gyilkosság!";
				link.l1 = "Huh? Kit gyilkol? Hol? Ez valami vicc, kedvesem?";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Örülök, hogy újra látlak... Köszönöm, hogy beugrottál... de attól tartok, ez nem a legjobb alkalom, hogy beszélgessünk. Gyere vissza, ha egyedül vagy. Akkor megbeszélhetünk... több személyes dolgot.";
							link.l1 = "Mindig öröm beszélgetni, de most mennem kell. Talán még találkozunk.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"... Már kezdtem azt hinni, hogy elfelejtetted az utat a kocsmánkhoz. Kár, hogy nem vagy egyedül. Reméltem, hogy négyszemközt beszélhetünk.";
							link.l1 = "Azt hiszem, a sors még ad egy esélyt, hogy négyszemközt beszélgessünk.";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Tudtam, hogy nem váratsz meg túl sokáig. Nem akarok még egy percet elvesztegetni. Az emeleti szoba szabad... csak nekünk. Ugye nem fogsz nemet mondani?";
							link.l1 = "Tudod, hogy kell engem magadhoz vonzani... Nos, nincs okom ellenállni. Mehetünk?";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Attól tartok, ma tényleg fontos dolgom van. De ígérem, legközelebb kárpótollak.";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"! Már kezdtem azt hinni, hogy élvezed, hogy várakoztatsz. Ugye nem fogsz csak úgy ott állni, mint egy szobor? Sokkal jobban is el lehetne tölteni ezt az idôt.";
							link.l1 = "Senki sem tud ellenállni a bájodnak... Nincs értelme vesztegetni az idôt - most felmegyek az emeletre.";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Maga aztán a csábító, Betsy... De sajnos most máshol kell lennem.";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "Szeretnék feltenni néhány kérdést.";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "Megkértelek, hogy menj fel az emeletre. Ne maradj itt és ne hívd fel magadra a figyelmet.";
					link.l1 = "Rendben, megyek, nem akarlak bemártani...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "Új vagyok itt, úgyhogy kérem, ne vonja el a figyelmemet a munkámról. Még mindig nem tudok hozzászokni...";
					link.l1 = "És hol van a pincérnô, aki elôtted itt dolgozott? " + pchar.questTemp.different.FackWaitress.Name + ", ha jól emlékszem...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Gyere vissza, édesem. Talán újra jól fogunk szórakozni. Ha több szabadidôm lenne...";
					link.l1 = "Persze, hogy fogok, nagyszerû voltál!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "Nem ismerlek, úgyhogy ne zavarj...";
					link.l1 = "Hol a pénzem?!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Bocsánat, "+ GetSexPhrase("jóképû","csinos") +", most túl elfoglalt vagyok. A kocsmának jó az idô, de a beszélgetéseknek nem!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Kérem, kapitány, ne verekedjen itt! Nehéz munka kitakarítani ezt a helyet.";
					link.l1 = ""+ GetSexPhrase("Hm... Nem is akartam.","Úgy nézek ki, mint egy részeges, aki verekedni akar? Én is csak egy lány vagyok, akárcsak te, ne aggódj.") +"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+ GetSexPhrase("Ó, kapitány! Szeretne ma velem egy ágyban aludni? Nem szeretek dicsekedni, de...","Foglaljon helyet, kapitány. Mindig öröm egy ilyen igazi tengeri farkassal találkozni, mint te.") +"";
						link.l1 = "Kár, hogy most sietek. Majd legközelebb!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "Nagy örömmel, bébi!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Foglaljon helyet, kapitány. Kóstolja meg a rumunkat, játsszon egy kis kártyát vagy kockajátékot. Érezze magát otthon! Mindig öröm egy olyan igazi tengeri farkassal találkozni, mint te.";
						link.l1 = "Köszönöm, szépségem.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Beszéljen a mesterrel, ha rendelni akar valamit. A pult mögött van.";
					link.l1 = "Köszönöm a tanácsot.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Ha pihenni akarsz és rendbe akarod hozni az egészségedet - akkor bérelj ki egy szobát. Ha egész éjjel a folyosón maradsz, az nem sokat segít.";
					link.l1 = "Köszönöm.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "Szeretnék feltenni néhány kérdést.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "Akkor hallgasson ide. Vegyél ki egy szobát itt a kocsmában. Menj oda és várj meg. Kicsit késôbb odalopakodom...";
			link.l1 = "Ha! Majd én megcsinálom, drágám! Várni fogok rád!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "Már nem dolgozik itt, nyugdíjba ment... Sajnálom, de nekem dolgom van.";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "Jól figyelj, te buja idióta! Nem tudom, hol van a pénzed! És ha tovább nyomulsz rám, akkor hívom az ôröket, és börtönben találod magad!";
			link.l1 = "Rendben, nincs szükség ôrökre... Micsoda bolond...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Pontosan, egy ilyen bolond. Legközelebb okosabb és tisztességesebb leszel.";
			link.l1 = "Megpróbálom... (suttogás) Kibaszott kurva...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Hallasz engem?";
			link.l1 = "Ughh...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Rosszul érzed magad? Fáj a fejed?";
			link.l1 = "A francba... hol vagyok?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "Nem emlékszel? Kiraboltak téged.";
			link.l1 = "Mi az? Mi az? Oh... A fejem... Ki merne?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "Honnan tudjam? Berontottak, megfenyegettek, hogy megölnek, megnézték a zsebeidet és elmentek.";
			link.l2 = "Értem... A francba... Kérnék egy kis vizet... Köszönöm.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "Nem, semmi baj, senor... köszönöm a kedvességét, de én... (sírás)";
			link.l1 = "Valaki megsértette? Nyugodjon meg, szépségem, mondjon el mindent.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Nem, nem, senor, ez semmiség. Bocsásson meg a visszafogottságomért, csak... A bátyámról van szó, azt mondják, hogy meghalt, de ne higgye el! Nem tudom, mit higgyek, de a saját szívemmel érzem, hogy nagy bajban van. És nincs senki másom, csak Angelo, miután a szüleink elmentek... (sírva)";
			link.l1 = "Megértem, de arra kérlek, hogy nyugodj meg, kérlek. Mi történt a bátyáddal?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Senor... kérem, ne értsen félre, de miért törôdik egy ilyen kapitány egy közönséges és szerény kocsmai lánnyal? Még csak ígérni sem tudok semmit a segítségéért... ";
			link.l1 = "Valójában igaza van. Az önzetlenség nem nekem való, úgyhogy légy erôs, mindannyian elveszítjük a rokonainkat. C'est la vie, ahogy Franciaországban mondják...";
			link.l1.go = "exit";
			link.l2 = "Egy nô mindig megtalálja a módját, hogy megköszönje a férfinak..... Ha-ha. Most pedig hagyd abba a sírást, és mesélj a problémádról.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Fiatal senorita, nem tudja, hogy az egyházunk azt tanítja, hogy segítsünk egymáson? Megpróbálok segíteni, ha természetesen képes vagyok rá.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				Notification_Reputation(false, 36, "high");
				dialog.text = "Volt egy 'hint'? Elnézést, az én hibám volt, hogy beszéltem veled! Farewell 'caballero'...";
				link.l1 = "Ahogy óhajtja, édesem.";
				link.l1.go = "exit";
			}
			else
			{
				Notification_Reputation(true, 36, "high");
				dialog.text = "Nos, akkor... Legalább ôszinte vagy a kívánságaiddal kapcsolatban. Ígérem, hogy ha megtalálod Angelót, vagy elmondod, mi történt vele, megkapod, amit kértél...";
				link.l1 = "Kedves senorita, örülök, hogy üzletelhetek önnel... Most pedig térjünk rá a bátyja történetére.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "Most viccelsz velem? Tényleg ingyen akar segíteni nekem?";
			link.l1 = "Csak egy rossz ember nem segítene egy síró lánynak. Ne aggódj, tényleg segíteni akarok neked. Mi történt pontosan Angelóval?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Rendben, senor. A bátyám, ô... ó, nem könnyû visszatartani a könnyeit, annyira sajnálom... Nagyon szegények voltunk az én... szerénységem miatt... talán a munkában... És Angelo a helyi csempészekkel kezdett el dolgozni. Úgy gondolta, hogy az ô kis halászhajójával több pénzt lehet keresni, ha a vámot elkerülve szállít valamit.";
			link.l1 = "Egyszerûbben fogalmazva, a bátyja bûnözô lett, igaz?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Nem, senor, nem érti... ô nem ilyen! Értem tette! Hogy megkíméljen attól, hogy pénzt keressek itt... tudja, mire gondolok. Adósok voltunk, és ô a becsületemért és a lelkemért tette. És aztán... elkapták. Nem volt nagy baj, még több pénzt is kölcsönkértem, hogy kifizessem a szabadulását... De azt mondták, hogy meghalt.";
			link.l1 = "Azt mondták? Ki mondta? És miért nem hiszel nekik? Egy börtönben halt meg?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Igen. Amikor pénzt hoztam, hogy kifizessem a szabadulását, a parancsnok azt mondta, hogy Angelo meghalt a fogyasztásban. Gondolj csak bele! Jó egészségben került oda, és két hét múlva meghalt azokban a kamrákban. Még azt sem engedték, hogy lássam a holttestét. Azt mondták, hogy a foglyokat közvetlenül az erôd melletti öbölben temették el, hogy elkerüljék a járványt.";
			link.l1 = "Járványt? Nagyon igaznak hangzik. Szóval csak nem akarsz hinni benne, vagy komolyabb okod van rá?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "Nem... Nem! (sírás) Tudom, hogy hülyén hangzik, de biztos vagyok benne, hogy tudnám, ha meghalna. Látod, Angelo mindig is erôs volt - egy igazi tengerész. De van még valami\nA nagyapám meghalt tüdôvészben, amikor gyerek voltam, és ô, egy öregember, évekig küzdött ellene! Tudom, hogyan mûködik, a fogyasztás nem napok alatt öli meg az embert, higgye el!";
			link.l1 = "Hm... Engem is kétségbe ejtettél, valami nagyon nem stimmel itt. Nem ígérhetek semmit, de megpróbálok többet megtudni.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "Még egy egyszerû ígéret is sokkal több, mint amire számítottam! Ön olyan kedves, senor! Itt fogok várni!";
			link.l1 = "Ó, ifjúság! Olyan ingatagok az érzelmeim... lennél szíves visszaadni a kezemet, szépségem, még mindig szükségem van rá, ha-ha... Rendben, akkor megyek és körülnézek.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "Ne, ne viccelj! Az emeleten! Két gengszter megöl egy nemes urat! Segítsen, kapitány! Rajtad kívül senki sincs itt felfegyverkezve!";
			link.l1 = "Fusson ki, hívja az ôrséget! Felmegyek az emeletre!";
			link.l1.go = "FMQP_1";
			link.l2 = "Kedvesem, biztos ôrnek nézett. Gyilkosság esetén hívjon járôrt.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "Ôrség! Segítség!";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
