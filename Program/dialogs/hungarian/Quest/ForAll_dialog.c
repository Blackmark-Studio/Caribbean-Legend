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
			dialog.text = "Nincs mirôl beszélnünk.";
			link.l1 = "Rendben...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én ennek a városnak a polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyeljen, én ennek a városnak a polgára vagyok, és arra kérem, hogy tartsa vissza a pengét.");
				link.l1 = LinkRandPhrase("Jól van.", "Persze.", "Rendben...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, "+ GetSexPhrase("cimbora","lány") +", fegyverrel rohangál. Tudok ideges lenni...", "Nem szeretem, ha "+ GetSexPhrase("férfiak","emberek") +" fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
				link.l1 = RandPhraseSimple("Megvan.", "Megvan.");
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
			dialog.text = "Gyerünk, haver, mutasd a zsebeidet.";
			link.l1 = "Micsoda?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "Hallottad, amit mondtam. Gyorsan, kevesebb szóval. Nem szeretek beszélni...";
			link.l1 = "A francba! És a " + pchar.questTemp.different.FackWaitress.Name + " nálad mûködik?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "Igen, igen... Add ide a pénzed, vagy kibelezlek!";
			link.l1 = "Nem! Kibelezlek!";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "Vedd el az érméimet, te rohadék! De ezt nem úszod meg...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "Persze, ezzel nem lehet vitatkozni. Viszlát, haver. És ne feledd, nem vagy olyan jóképû, hogy a pincérnôk nedvesek legyenek. Legközelebb légy okosabb!";
			link.l1 = "...Menj már.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "Ahogy mondod...";
			link.l1 = "Igen...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "Itt vagyok! Akarsz engem, szépfiú?";
			link.l1 = "A fenébe, ez gyorsan eszkalálódott...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "Ne vesztegessük az idônket!";
			link.l1 = "Heh, nem tudnék jobban egyetérteni!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "Jó napot! A nevem " + GetFullName(npchar) + ". A " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Acc")) + " '" + npchar.Ship.name + "'kapitánya vagyok."; 
			link.l1 = "Nagyszerû! Végre megtaláltalak.";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "Megtaláltál?!";
			link.l1 = "Igen. Nos, elhoztam a hajónaplódat, amit a " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + "kikötôi irodában felejtettél.";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "A fenébe! Most már látom, hol vesztettem el. Ez az elvesztés majdnem zendülést váltott ki a hajón...";
			link.l1 = "Szóval minden jó, ha a vége jó. Fogd a naplódat és beszéljünk a pénzemrôl.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Remek idôzítés, én még nem kezdtem újat, úgyhogy fizetek neked, amennyit csak tudok. " + FindRussianMoneyString(sti(npchar.quest.money)) + " és elfogadok néhány darabot a magán ékszereimbôl.";
				link.l1 = "Szép volt. Vedd el.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Hm, tudod, már elkezdtem az új naplót. Mindazonáltal a régi még mindig értéket képvisel számomra. Szóval fizetek neked " + FindRussianMoneyString(sti(npchar.quest.money)) + " és elfogadok néhány darabot a magán ékszereimbôl.";
					link.l1 = "Akkor megegyeztünk. Fogd a naplódat.";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "Már elkezdtem az új naplót. És átvittem az összes jegyzetet a régibôl. Már nincs rá szükségem, így nincs pénzed.";
					link.l1 = "Remek. Szóval az egész hajsza a semmiért volt.";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "Köszönöm. Viszlát, "+ GetSexPhrase("haver","lány") +".";
			link.l1 = "Neked is...";
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
			dialog.text = "Ha, legközelebb dolgozz az idôzítésen.";
			link.l1 = "Ez igaz.";
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
				dialog.text = "Üdvözöllek a hajóm fedélzetén. Hogy ôszinte legyek, halálra rémítettél - azt hittem, hogy a félszemû paripa vadász vadászik rám...";
				link.l1 = "Nem, kapitány, ma jó kedvem van. Azért vagyok itt, hogy segítsek neked.";
			}
			else
			{
				dialog.text = "Üdvözöllek a hajóm fedélzetén!";
				link.l1 = "Ahoy, sapka! Már kerestelek.";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "Miért?";
			link.l1 = "A " + XI_ConvertString("Colony" + npchar.quest.firstCity + "Gen") + "kikötômester házában felejtette a hajónaplóját.";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "A fenébe, akkor ez volt az a hely! Ez az elvesztés már így is egy rakás gondot okozott nekem.";
				link.l1 = "Mit szólnál egy kis jutalomhoz?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "A fenébe, most már látom, hol vesztettem el! Köszönöm, de túl sokáig kerestél engem. Már elkezdtem az új naplót. Mindazonáltal a régi feljegyzéseket még át kell vinni az újba...";
					link.l1 = "És mennyit?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "Már elkezdtem az új naplót. És átvittem az összes feljegyzést a régibôl. Már nincs rá szükségem.";
					link.l1 = "Tehát nincs szükséged a régi naplóra? Tényleg?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "Fizethetek neked " + FindRussianMoneyString(sti(npchar.quest.money)) + " és néhányat az ékszereimbôl. Ez minden, amit megengedhetek magamnak.";
			link.l1 = "Akkor jó. Vidd a naplódat.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "Még egyszer köszönöm. Viszlát, haver.";
			link.l1 = "Csak így tovább.";
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
			dialog.text = "Az biztos. Ha üldözöl valakit, akkor gyorsabbnak kell lenned.";
			link.l1 = "Ne veszítsd el a naplódat az elsô helyen. Rendben.";
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
			dialog.text = "Azt hittem, hogy mindent elrendeztünk.";
			link.l1 = "Igen, ez igaz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "Üdvözletem. Mit akarsz?";
			link.l1 = "Semmit, csak hallani akartam néhány hírt. Van valami eladó?";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "Nincs mit eladnom neked, és nincs semmi újdonságom. Mellesleg, a jelenléted itt nem kívánatos. Világos?";
			link.l1 = "Maga... Akkor viszlát, haver.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "Megmondtam, hogy nincs itt semmi keresnivalója!";
			link.l1 = "Értem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "Miért támadtál rám?!";
			link.l1 = "Vissza kell adnom a hajót a tulajdonosának...";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "Milyen tulajdonosnak? Én vagyok a tulajdonos!";
			link.l1 = "Nem, nem vagy az. Nem tudom, kié ez a hajó. De ellopták, és vissza kell adnom.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "Bassza meg! De nekem még nincs vége. Legalább megpróbállak megölni...";
			link.l1 = "Csak próbálkozni tudsz.";
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
			dialog.text = "Üdvözlet, "+GetAddress_Form(NPChar)+". Látom, hogy ön a saját hajójának a kapitánya? A nevem "+GetFullName(npchar)+" és szeretnék egy üzletet ajánlani.";
			link.l1 = RandPhraseSimple("Nagyon sajnálom, de mennem kell.", "Nagyon sajnálom, de nincs idôm beszélgetni veled.");
			link.l1.go = "SCQ_exit";
			link.l2 = "Csupa fül vagyok.";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "Akkor hallgasson ide. "+SelectNB_battleText()+"\nNincs sem idôm, sem esélyem, hogy megtaláljam. Mert soha nem jelenik meg itt. Gondolom, most már érted, mit fogok javasolni neked?";
						link.l1 = LinkRandPhrase("Gondolom, fel kell kutatnom valakit, és el kell hoznom hozzád?","Talán, hogy megtaláljam a szemetet és elhozzam neked?","Azt akarja, hogy találjam meg ezt az embert és hozzam ide?");
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "Akkor hallgasson ide."+SelectNB_battleText()+"\nNincs sem idôm, sem esélyem, hogy megtaláljam. Mert soha nem jelenik meg itt. Gondolom, most már érted, mit fogok javasolni neked?";
						link.l1 = LinkRandPhrase("Gondolom, azt akarod, hogy felkutassak valakit, és elhozzam neked?","Talán, hogy találjam meg a szemetet és hozzam el magának?","Azt akarja, hogy találjam meg ezt az embert és hozzam ide?");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = "Akkor hallgasson ide. Valójában "+npchar.quest.text+" a haditengerészetnél szolgál kapitányként. Még azt sem tudja, hogy én is itt vagyok!\nSzeretnék találkozni vele, de nincs sem idôm, sem lehetôségem, hogy megtaláljam...";
					link.l1 = "Gondolom, azt akarod, hogy megkeressem ezt a kapitányt, és beszéljek neki rólad?";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //вариант А
			dialog.text = "Nem egészen. Találd meg, de nincs szükség arra, hogy idehozd. Ölje meg, és ez elég lesz. Süllyessze el a mocskos hajójával, lôje le, szúrja le a pengéjével - engem ez nem igazán érdekel, csak tegye meg, hogy ez a fattyú ne mérgezze tovább ezt a világot a jelenlétével. A jutalom nagylelkû lesz.";
			link.l1 = "Ha! Elég könnyû. Mondja meg a nevét és a hajójának a nevét.";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			dialog.text = "" + npchar.quest.SeekCap.capName + " a " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " nevû " + npchar.quest.SeekCap.shipName + ". Gyakran vendégeskedik a "+XI_ConvertString("Colony"+npchar.quest.Qcity)+"kikötôben . Fizetek neked "+FindRussianMoneyString(sti(npchar.quest.money))+" aranydublonokban.";
			link.l1 = "Ennyit kell tudnom. Figyelmes leszek a tengerben. És ha megtalálom a barátodat, akkor... 'leereszkedô hang' ...nem egészen élôvé teszem.";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "Ez nem elég az ilyen munkához.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "Örülök, hogy megegyeztünk. Várni fogom a visszatérésedet.";
			link.l1 = "Hol fogom megtalálni? Tisztázzuk ezt most, nem akarok idôt vesztegetni a keresésére.";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "Minden reggel részt veszek egy istentiszteleten a helyi templomban. Ott minden nap 8 és 9 óra között megtalálsz.";
			link.l1 = "Akkor megegyeztünk! Várja az eredményt hamarosan.";
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
			dialog.text = "Pontosan. Találd meg és hozd el nekem. Élve. Egyedül akarok vele foglalkozni. Nagylelkûen megjutalmazlak.";
			link.l1 = "Nos, megpróbálhatom megtalálni, de szükségem van a részletekre.";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "A fattyú neve "+npchar.quest.SeekCap.name+". Ô szolgál a " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc")) + " nevû " + npchar.quest.SeekCap.shipName + ", amely a " + npchar.quest.SeekCap.capName + "parancsnoksága alatt áll. A hajó gyakran látható a "+XI_ConvertString("Colony"+npchar.quest.Qcity)+"kikötôben . Ezért a munkáért "+FindRussianMoneyString(sti(npchar.quest.money))+" aranydublonokban fizetek neked.";
			link.l1 = "Ez elég nekem. Figyelmes leszek a nyílt tengeren.";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "Ez nem elég az ilyen munkához.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "Örülök, hogy megegyeztünk. Várni fogom a visszatérésedet.";
			link.l1 = "Hol fogom megtalálni? Tisztázzuk ezt most, nem akarok idôt vesztegetni a keresésére.";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "Minden reggel részt veszek egy istentiszteleten a helyi templomban. Ott minden nap 8 és 9 óra között megtalálsz.";
			link.l1 = "Akkor megegyeztünk! Várja az eredményt hamarosan.";
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
			dialog.text = "Pontosan! Keresd meg és mondd meg neki, hogy ebben a városban élek. Fizetek a szolgálataiért.";
			link.l1 = "Nos... Megpróbálhatom. Mondja el a részleteket.";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = "A neve " + npchar.quest.SeekCap.capName + ". És ô szolgál a " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " " + npchar.quest.SeekCap.shipName + "'. Gyakran látogat el a "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Ezért a munkáért "+FindRussianMoneyString(sti(npchar.quest.money))+" aranydublonokban fizetek neked.";
			link.l1 = "Megegyeztünk! Gondolom, hamarosan megtalálom a barátodat.";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "Nekem ez nem elég.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "Örülök, hogy megegyeztünk. Várni fogom a visszatérésedet.";
			link.l1 = "Hol fogom megtalálni? Tisztázzuk ezt most, nem akarok idôt vesztegetni a keresésére.";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "Mindig részt veszek egy esti istentiszteleten a helyi templomban. Ott találsz meg minden nap este hat és nyolc óra között.";
			link.l1 = "Akkor megegyeztünk! Várja az eredményt hamarosan.";
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
			dialog.text = "És? Mit akar, uram?";
			link.l1 = "Te vagy a kapitány "+GetFullName(npchar)+"?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "Igen, az vagyok. Mi a helyzet?";
			link.l1 = "Egy férfi nagyon nagy érdeklôdést mutat irántad, a neve "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Emlékszel?";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "Úgy hallottam, hogy sok mahagóni van a raktérben. Meg akarom venni. Eladod nekem?";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "Most hallom elôször ezt a nevet. Valahogy tévedett, kapitány. Végeztünk?";
			link.l1 = "Hm. Rendben, bocsásson meg...";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "Tényleg? De elég jól emlékszik magára. Említette az adósságodat...";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "Milyen adósságot? Mirôl beszélsz?";
			link.l1 = "A becsület adósságáról!";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "Tévedsz. Én nem kereskedem semmiféle fával. Végeztünk?";
			link.l1 = "Hm. Rendben, elnézést...";
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
			dialog.text = "És? Mit akar, uram?";
			link.l1 = "Te vagy a kapitány "+GetFullName(npchar)+"?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Igen, én vagyok. Mi a helyzet?";
			link.l1 = "Egy "+sld.quest.SeekCap.name+" nevû férfi szolgál az ön parancsnoksága alatt?";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Igen. Ô az egyik tisztem. Most mondja meg, miért kérdezi?";
			link.l1 = "Persze, hogy elmondom. A "+XI_ConvertString("Colony"+sld.city+"Gen")+"hatóságok utasítására keresem ezt az embert, és hatalmamban áll letartóztatni és átadni ôt a "+XI_ConvertString("Colony"+sld.city)+". Kérem, hogy segítsen nekem ebben az ügyben, hogy békésen elintézhessük.";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "Tényleg? És ez az ember a legénységemben szolgál? Ez most komoly?";
				link.l1 = "Ne foglalkozz ezzel, "+GetAddress_FormToNPC(NPChar)+". Küldök egy hosszúhajót a hajódhoz, és mi magunk visszük el.";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "Nem mondod. Tudja mit, uram, leszarom a múltját. Nem tartozik rám. És egyébként ki maga? A hatóságok? Tényleg? Ha! Nem adom ki az embereimet sem magának, sem másnak. Ennek a beszélgetésnek vége. Tûnjetek el!";
				link.l1 = "Rossz választás... Szörnyû választás!";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "Tedd, amit tenned kell.";
			link.l1 = "Rajta vagyok.";
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
			log_info(sld.quest.SeekCap.name+" le van tartóztatva");
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
			dialog.text = "Végeztünk, kapitány?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = "Szép napot. Mit akar, kapitány?";
			link.l1 = "Te vagy a kapitány "+GetFullName(npchar)+", igazam van?";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = "Igen, igaza van. Van valamije számomra?";
			link.l1 = "Nekem van. Egy "+GetFullName(sld)+" nevû férfi keres téged. Azt szeretné, ha minél hamarabb meglátogatnád. A "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+"lakik.";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "Ha! Szóval ô is az Újvilágba költözött? Akkor tényleg meg kéne látogatnom... Köszönöm az információt, uram!";
			link.l1 = "Szívesen látjuk. A munkámat a barátod fogja fizetni. Sok szerencsét, "+GetAddress_FormToNPC(NPChar)+"!";
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
			dialog.text = "Öröm volt, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "Az öröm az enyém volt, kapitány.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = "Ahoy, "+GetAddress_Form(NPChar)+". Mit akarsz?";
			link.l1 = "Hallottam, hogy sok vörösfenyô van a rakományodban, és meg akarom venni. Eladná?";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "Téved. Nem kereskedem fával, és az itteni látogatásod elég gyanús szagú számomra. Azt hiszem, jobb, ha elhagyja a hajómat!";
			link.l1 = "Rendben, csak kérdeztem. Viszontlátásra.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "Gondot akar, uram? Megismételjem magam?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Miért támadtad meg a hajómat, gazember?";
			link.l1 = "Azért vagyok itt, hogy átadjam üdvözletemet a "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" , a "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"nevû embertôl. Remélem, hogy most már érti a helyzetet.";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "Ez lehetetlen! Akkor nincs vesztenivalóm...";
			link.l1 = "Mi van az életeddel?";
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
			dialog.text = "Miért támadtad meg a hajómat, gazember?";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "Van valami ötleted? Arra kértem, hogy békésen adja át nekem a tisztjét. Most elviszem ôt, téged és a kádadat!";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "Egy gazember szolgál a parancsnokságod alatt. A neve "+sld.quest.SeekCap.name+". A "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" hatóságai nagyon kíváncsiak rá. Letartóztatják és a fogdámba zárják.";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "És ezért követtek el mészárlást a hajómon? Szemétláda! Még mindig maradt egy kis erôm... Megöllek!";
			link.l1 = "Erôsebb emberek is megpróbálták már...";
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
			dialog.text = "Mit mondasz, kapitány? Van valami elôrelépés az ügyemben?";
			link.l1 = "Még nem. De rajta vagyok.";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = "Mit mondasz, kapitány? Van valami elôrelépés az ügyemben?";
					link.l1 = "Én igen. És tetszeni fog neked." + npchar.quest.SeekCap.capName + " halott, és az ô " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + " a tenger fenekén van.";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = "Mit mondasz, kapitány? Van valami elôrelépés az ügyemben?";
					link.l1 = "Én igen. És tetszeni fog neked."+npchar.quest.SeekCap.Name+" a hajóm kabinjában ül, letartóztatva.";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = "Aha, hát itt vagy. Örülök, hogy látlak. Úgy értesültem, hogy sikeresen teljesítetted a küldetésedet!";
					link.l1 = "A barátod meglátogatott?";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "Nagyszerû! Tudtam, hogy számíthatok rád. Tessék, itt az aranyad. Megérdemelted.";
			link.l1 = "Köszönöm. Beszélj velem újra, hátha kapsz még egy ellenséget.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("Megkaptad "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
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
			dialog.text = "Nagyszerû! Megparancsolom az embereimnek, hogy azonnal szedjék le a hajóról. Most már nem fog elmenekülni! Tessék, itt az aranyad. Megérdemelted.";
			link.l1 = "Köszönöm, uram. Bármikor hívhatsz, ha ilyen munkáról van szó.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("Megkaptad "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
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
			dialog.text = "Igen, itt járt és mesélt magáról. Tessék, itt az aranyad. Megérdemelte.";
			link.l1 = "Köszönöm. Viszontlátásra, uram!";
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
			Log_Info("Megkaptad "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
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
			dialog.text = LinkRandPhrase("Üdvözlöm, kapitány. A segítségét szeretném kérni.", 
				"Kapitány! Tudna segíteni nekem? Kérem, segítsen!", 
				"Kapitány, a segítségét kérem!");
			link.l1 = RandPhraseSimple("Elfoglalt vagyok.", "Sietek.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Mi a baj?", "Mondd el, mi zavar. Talán tudok segíteni.");
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
					dialog.text = "Egy évvel ezelôtt egy kapitány megígérte, hogy elvisz a " + XI_ConvertString("Colony" + SelectNotEnemyColony(NPChar) + "Acc") + ". De amíg a hajóján voltam, bedobtak a raktérbe, és utána eladtak rabszolgának. Éppenhogy túléltem. Többször is közel voltam a halálhoz... Mindenesetre szeretném emlékeztetni 'barátomat' , hogy még mindig élek."; // belamour gen
					link.l1 = "Hogy érti ezt? Mondd el pontosan, mit akarsz.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "A feleségemet elrabolták. Egy kapitány, egy kalóz, ahogy mondják, udvarolt neki. A feleségemnek napokig otthon kellett maradnia a zaklatása miatt. Próbáltam rávenni a városi hatóságokat, hogy segítsenek nekünk, de nem sikerült. És most...";
					link.l1 = "Most mi lesz?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "Tudod, keresem a városlakótársamat. Három évvel ezelôtt együtt érkeztünk ide Európából, hogy jobb életet találjunk. Elvesztettük egymást. De nemrég hallottam, hogy ô most már kereskedelmi kapitány! Én magam is megpróbáltam megtalálni, de nem sikerült.";
					link.l1 = "Szóval?";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "Szeretném, ha megtalálnád és megölnéd. Annyira szeretném, ha meghalna, hogy még enni sem tudok...";
			link.l1 = "Értem... Azt hiszem, ebben segíthetek neked. Mondd meg a nevét és a hajójának a nevét.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "Sajnálom, de nem érdekel.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "" + npchar.quest.SeekCap.capName + " a " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " nevû " + npchar.quest.SeekCap.shipName + ". Fizetek neked  " + FindRussianMoneyString(sti(npchar.quest.money)) + ", plusz az összes ékszeremet."; // belamour gen
			link.l1 = "Aha, értem. Figyelmes leszek a tengeren. Ha megtalálom a célpontot... Akkor tekintsd ôt halottnak.";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "Ennyi pénzért nem teszek semmit. Keress egy másik bolondot, aki bosszút áll.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "Ezt reméltem hallani! Ó, most már ehetek! Végre! Ennem kell valamit...";
			link.l1 = "Jó étvágyat. Majd megkereslek, ha végeztem a munkával.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "A helyi templomban fogok várni rád.";
			link.l1 = "Jó.";
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
			dialog.text = "Túlságosan tétlen voltam, és az a szemétláda elkapta a feleségemet, és a hajója fedélzetére vitte. Arra kérlek, hogy találd meg ezt a gazembert!";
			link.l1 = "Hm, és miért kéne harcolnom egy gazembertársammal?";
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
			dialog.text = "Nem vagyok gazdag, de örömmel adok neked minden értéket, amivel rendelkezem! Ha kiszabadítod a feleségemet és elhozod hozzám, fizetek neked " + FindRussianMoneyString(sti(npchar.quest.money)) + ", plusz az összes ékszeremet.";
			link.l1 = "Rendben, benne vagyok. Mondd el a részleteket. A nevét, a hajóját és a feleséged nevét.";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "Nem, haver, nem akarok ilyen kis összegért. Sajnálom...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "A neve " + npchar.quest.SeekCap.name + ". A fattyú neve pedig " + npchar.quest.SeekCap.capName + ", úszik a " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " nevû " + npchar.quest.SeekCap.shipName + "."; // belamour gen
			link.l1 = "A szar úszik, haver. A kapitányok hajóznak...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "Igen, igen, nagyon sajnálom! Nem vagyok tengerész, remélem, hogy megérted...";
			link.l1 = "Semmi baj, ne aggódjon. Mindegy, visszajövök, amint végeztem.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "Köszönöm szépen! Várni fogom a helyi templomban. De kérem, siessen. Nagyon aggódom a feleségemért...";
			link.l1 = "Igen, én sem irigylem ôt.";
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
			dialog.text = "Az a baj, hogy a barátomnak nincs vagyona. A hajója az otthona. Szóval nem találom, mert állandóan hajózik. Én meg nem engedhetem meg magamnak a haszontalan utazásokat, pénzt kell keresnem a megélhetéshez.";
			link.l1 = "Nem tudok segíteni, ha nincs pénzed...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Fizethetek neked " + FindRussianMoneyString(sti(npchar.quest.money)) + " és odaadom az összes ékszeremet. Jelenleg csak ennyit engedhetek meg magamnak.";
			link.l1 = "Ez az összeg nekem megfelel. Benne vagyok. Tulajdonképpen csatlakozhatsz hozzám utasként, így láthatod a barátodat, amint megtaláljuk.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "Ez nekem nem elég. Keressen valaki mást, aki megcsinálja.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "Nem, azt hiszem, én itt maradnék. Nem tudjuk, meddig tartanak ezek a keresések, és lehet, hogy az összes pénzemet elveszítem. Nekem itt van munkám.";
			link.l1 = "Igen, értem. Most mondja meg, ki a barátja, és milyen hajón van.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "A neve " + npchar.quest.SeekCap.capName + ". Tudomásom szerint egy " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Acc")) + " nevû " + npchar.quest.SeekCap.shipName + "parancsnoknak parancsol."; // belamour gen
			link.l1 = "Értem. Nos, ha találkozom a barátoddal, mesélek neki rólad.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "Köszönöm. Várni fogom az érkezését a helyi templomban. Megkapod az érméidet, amint végeztél a munkával.";
			link.l1 = "Persze. Akkor viszlát, hamarosan meglesz az eredmény.";
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
			dialog.text = "Szép napot, kapitány. Van már eredmény?";
			link.l1 = "Emlékeztessen a problémájára...";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "Úgy veszem, hogy megbosszultam magam. Valóban?";
					link.l1 = "Pontosan. " + npchar.quest.SeekCap.capName + " halott, és az ô " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName)) + " a tenger fenekén van.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "Megtaláltad a feleségemet! Ezt nem hiszem el! Elhiszem?";
					link.l1 = "Megteheti. Ô az utasom. Visszaveheted, ha " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + " tényleg a feleséged...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "Jó napot, kapitány. Megtalálta a társamat?";
					link.l1 = "Igen, és meséltem neki magáról.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Mi? Tényleg elfelejtetted, hogy megkértelek, hogy bosszuld meg " + npchar.quest.SeekCap.capName + " kapitányt egy év rabszolgaságomért?";
					link.l1 = "Nem, nem felejtettem el.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "Nem hiszek a fülemnek! Elfelejtetted, hogy megkértelek, hogy találd meg és engedd el a feleségemet? A " + npchar.quest.SeekCap.capName + "nevû kalóz fogságba ejtette!";
					link.l1 = "Nem is.";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "Várj egy percet... Elfelejtetted az ígéretedet, hogy megtalálod a " + npchar.quest.SeekCap.capName + "nevû társamat?";
					link.l1 = "Nem is.";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "Kiváló, igazam volt veled kapcsolatban! Tehát, ahogy ígértem neked, itt vannak a " + FindRussianMoneyString(sti(npchar.quest.money)) + " és az ékszerek. Köszönöm a segítséget.";
			link.l1 = "Szívesen...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "Ó, Istenem! Megmentettél minket! Kérlek, vedd el a " + FindRussianMoneyString(sti(npchar.quest.money)) + " és az ékszereidet. És tudd, hogy örökké imádkozni fogunk érted!";
			link.l1 = "Imádkozz, ha akarsz. Nekem ezzel nincs problémám.";
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
			dialog.text = "Pompás!... Tessék, fogd a " + FindRussianMoneyString(sti(npchar.quest.money)) + " és az ékszereket. És köszönöm, kapitány.";
			link.l1 = "Szívesen, barátom. Viszontlátásra...";
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
			dialog.text = LinkRandPhrase("Üdvözlöm, kapitány. Tudna segíteni?", 
				"Kapitány! Tudna segíteni egy nônek? Lenne szíves...", 
				"Kapitány, segítsen "+ GetSexPhrase("egy lánynak","nekem") +".");
			link.l1 = RandPhraseSimple("Elfoglalt vagyok.", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + ", de nincs szabadidôm...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Mi a bajod, " + GetAddress_FormToNPC(NPChar) + "?", "Beszélj a problémáidról, " + GetAddress_FormToNPC(NPChar) + ". Megpróbálok segíteni neked.");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "A férjem kereskedô, minden kolóniára szállít árut. Három hónappal ezelôtt elment a tengerre. Még nem tért vissza!";
					link.l1 = "Gondolja, hogy történt vele valami?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+ GetSexPhrase("Kapitány, látom, hogy te egy bátor kapitány vagy, egy tökéletes gazember","Kapitány, látom, hogy te egy erôs nô vagy, hogy bármelyik férfival elbánsz") +"...";
					link.l1 = "És miért mondod ezt, " + GetAddress_FormToNPC(NPChar) + "?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "Kapitány, kérem, segítsen nekem, könyörgöm! A férjemet elfogták! Meg tudja menteni?";
					link.l1 = "Várjon egy pillanatra, nem értem. Kit fogott el ki?";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "Nem tudom, de azért remélem, hogy csak túl elfoglalt ahhoz, hogy írjon nekem. Küldhetett volna levelet, tudja, hogy aggódom érte!";
			link.l1 = "A tengeren nem biztonságos, bármi megtörténhet...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Pontosan! Érted, mirôl beszélek. Úgy nézel ki, mint egy "+ GetSexPhrase("bátor kapitány","bátor lány") +", ezért szeretném megkérni, hogy keresd meg a férjemet. Kész vagyok fizetni neked " + FindRussianMoneyString(sti(npchar.quest.money)) + ", plusz odaadom az összes ékszeremet.";
			link.l1 = "Rendben. Elmondom a férjednek a gondjaidat, ha találkozom vele a tengeren vagy bárhol máshol. Mondd meg a nevét és a hajójának a nevét.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "Engem nem érdekel egy ilyen kis összeg.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "A neve " + npchar.quest.SeekCap.capName + ". Egy " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " nevû " + npchar.quest.SeekCap.shipName + "hajón hajózik.";  // belamour gen
			link.l1 = "Értem. Most már várnia kell. Próbáld meg az idôd nagy részét a templomban tölteni, hogy megtaláljalak.";
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
			dialog.text = ""+ GetSexPhrase("Azért mondom ezt, jó uram, mert fel akarom venni, hogy a megszokott munkáját végezze... úgymond.","Azt akarom, hogy segítsen nekem. Remélem, hogy meg fog érteni engem, mint nôt.") +"Egy kapitány bosszantott engem, és holtan akarom látni.";
			link.l1 = "És mit tett veled az a szerencsétlen?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "Ez a fattyú átvert engem. Úgy tett, mintha szerelmes lenne belém, még udvarolt is nekem. És mindezt azért tette, hogy valami értékeset szerezzen a férjemtôl! És amikor a kutya megkapta a csontját, azt mondta nekem, hogy ez nem jelent semmit... hogy mi csak barátok vagyunk!";
			link.l1 = "Hm, talán igaza volt?";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "Idiótának nézek ki?! Azt hiszed, hogy nem látom a különbséget az udvarlás és egy egyszerû buborékos beszélgetés között?";
			link.l1 = "Dehogynem...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "Kihasznált engem, az a gazember! Ezt soha nem bocsátom meg neki!";
			link.l1 = "Igen, a férfiak ilyenek. De, talán le tudnád nyugtatni magad? Nincs ebben semmi szörnyû...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "Semmi szörnyûség?! "+ GetSexPhrase("Te valamiféle moralista vagy, nem vagy igazi kalóz!","Úgy tûnik, hogy te még sosem voltál ilyen helyzetben! Ó, igen, aki kockáztatna... és én csak egy gyenge nô vagyok...");
			link.l1 = "Jól van. Elég volt. Csak azt szeretném tudni, hogy mennyire komolyak a szándékaid.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "A fenébe is, "+ GetSexPhrase(" csak nem tudod, hogy néz ki egy visszautasított nô bosszúja ","te egy nô vagy, és meg kell értened, milyen érzés visszautasítva lenni! Bosszút akarok állni ") +"!";
			link.l1 = ""+ GetSexPhrase("Ez igaz, még sosem volt ilyen élményem","Hát, tudod, csak sírna egy kicsit, összetörne néhány üveget, és vége lenne") +"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+ GetSexPhrase("Tekintse magát szerencsésnek. A visszautasított és becsapott elvárásaiban a nô egy düh, egy ördög a szoknyában! Semmi a világon nem tudja csillapítani a haragját","És én nem vagyok olyan, mint ô. Semmi sem enyhítheti a dühömet") +"!\nSzóval azt akarom, hogy személyesen ölje meg. És mielôtt meghal, meg kell tudnia, ki fizet a haláláért...";
			link.l1 = "Hm, nem is tudom, mit mondjak... És mennyit fizetsz?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Mindent, amim van. Neked adom az ékszereimet és " + FindRussianMoneyString(sti(npchar.quest.money)) + "! Megegyeztünk?";
			link.l1 = "Engem érdekel. Mondd meg a nevét és a hajójának a nevét.";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "Nem érdekel. Viszlát.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "A gazember neve " + npchar.quest.SeekCap.capName + " és egy " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")) + " nevû " + npchar.quest.SeekCap.shipName + "hajón hajózik."; // belamour gen
			link.l1 = "Tekintse késznek, " + GetAddress_FormToNPC(NPChar) + ". Várj meg a helyi gyülekezetben. Remélem, hogy megnyugszol egy kicsit...";
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
			dialog.text = "Majd én elmagyarázom. A probléma az, hogy a férjemet, aki csak egy egyszerû ember, elfogták a kalózok! Mindenkit megöltek, és nem kíméltek senkit...";
			link.l1 = "Úgy tûnik, hogy a kapitány ellenállni mert. Máskülönben megkímélték volna a legénységet.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Lehet, de a férjem egy ártatlan lélek. Ô csak egy utas volt ott. Azt kellett mondania, hogy gazdag, hogy megmentse az életét. A kalózok megkímélték, még csak a raktérbe sem tették.";
			link.l1 = "És ezt honnan tudja?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "Sikerült neki levelet küldenie nekem. Azt írta, hogy jól van, és egy kabinban tartják fogva, nem úgy, mint a többi foglyot.";
			link.l1 = "És mit tervezel tenni? Ez így nem mehet tovább. Elôbb-utóbb a kalózok átlátnak rajta.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "Te is kalóz vagy? Igen-igen, tudom... Könyörgöm, segítsen nekünk, mentse meg a férjemet! Leírta azt a kalózhajót, és leírta a kapitány nevét. Nem lesz nehéz megtalálni ôket!";
			link.l1 = "Nem olyan egyszerû, mint gondolod. Minden fogoly a férjedet elfogó kapitány jogos zsákmánya, ráadásul idôbe telik.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "De legalább megpróbálhatod! Különben is, van elég idôd a keresésre. A férjem nem bolond, és az Óvilágból származó kereskedônek adja ki magát, így azok a kalózok egyelôre nem követelnek tôle érméket. Ha kiszabadítjátok, mindent odaadok nektek, amim csak van!";
			link.l1 = "És neked mid van?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Nem sok, " + FindRussianMoneyString(sti(npchar.quest.money)) + " és az összes ékszerem... De imádkozni fogok a lelkedért örökké!";
			link.l1 = "Igen, ez tényleg nem sok... Rendben, kész vagyok segíteni neked.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "Sajnálom, de ez nekem nem elég.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Köszönöm, nagyon köszönöm!";
			link.l1 = "Meg fogod köszönni, ha sikerül, úgyhogy hagyd abba. Jobb, ha elmondja a férje nevét, és mindent, amit azokról a kalózokról tud.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "A neve " + GetFullName(forName) + ". Kapitánya " + npchar.quest.SeekCap.capName + ", ô hajózik " + GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")) + " nevû " + npchar.quest.SeekCap.shipName + "."; // belamour gen
			link.l1 = "Értem. Nos, most várnod kell és remélni, hogy sikerrel járok a keresésben. Maradjatok a templomban, várjatok és imádkozzatok...";
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
			dialog.text = "Ó, kapitány, annyira örülök, hogy látom! Mondd csak, mit akarsz mondani nekem a feladatomról?";
			link.l1 = "Hm, emlékeztess, " + GetAddress_FormToNPC(NPChar) + ", milyen feladatról beszélsz?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "Ah, kapitány, kaptam egy levelet a férjemtôl! Azt írta, hogy ön megtalálta ôt.";
					link.l1 = "Igen, így van, " + GetAddress_FormToNPC(NPChar) + ". A férje, " + npchar.quest.SeekCap.capName + ", jól van és egészséges. Csak túlságosan elfoglalt...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "Mit szólna hozzá, kapitány? Megtette, amirôl kérdeztem? A kapitány " + npchar.quest.SeekCap.capName + " halott?";
					link.l1 = "Igen, meghalt, " + GetAddress_FormToNPC(NPChar) + ". Elmondtam neki, hogy ki volt a halála oka. Az utolsó dolog, amit életében hallott, a te neved volt.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "Megmentette a férjemet! Könyörgöm, mondd, hogy ez igaz!";
					link.l1 = "Igen, az. Most is a hajómon van. Találkozhatsz vele, ha " + npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname + "tényleg a férjed...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Tényleg elfelejtetted, hogy megígérted nekem, hogy megtalálod a férjemet? A neve: " + npchar.quest.SeekCap.capName + "!";
					link.l1 = "Ó, igen, persze... Nem felejtettem el.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "Nem értem! Elfelejtetted, hogy meg kell ölnöd az elkövetômet, egy " + npchar.quest.SeekCap.capName + "nevû kapitányt?!";
					link.l1 = "Ó, kérem, persze, hogy nem. A parancsa folyamatban van, kérem várjon...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "Jézusom, kapitány, elfelejtette az ígéretét, hogy kiszabadítja a férjemet?";
					link.l1 = "Én nem. Emlékszel ... 'Várj és imádkozz!'. Csak várj, " + GetAddress_FormToNPC(NPChar) + " " + npchar.lastname + ".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "Ó, Istenem, annyira hálás vagyok! És igen, vedd el a " + FindRussianMoneyString(sti(npchar.quest.money)) + ". És még egyszer köszönöm!";
			link.l1 = "Hm, szívesen...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "Kiváló! Nos, fogd a " + FindRussianMoneyString(sti(npchar.quest.money)) + " és az ékszereket. Viszontlátásra...";
			link.l1 = "Ég veled! ";
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
			dialog.text = "Persze, hogy ô az! Istenem, kapitány, annyira hálás vagyok. Fogd a " + FindRussianMoneyString(sti(npchar.quest.money)) + ". Imádkozni fogok érted életem minden napján!";
			link.l1 = "Jól hangzik...";
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
					dialog.text = "Üdvözlöm a fôiskolámat. Akarsz valamit"+ GetSexPhrase(", haver ",", lány") +"?";
					link.l1 = "A neved " + GetFullName(npchar) + ", igazam van?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "Igen, így van!";
			link.l1 = "Kár érted. Egy nevet mondok neked, és jobb, ha tudod." + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". Emlékszel rá?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "Hm, igen...";
			link.l1 = "Figyelj, nagyon mérges rád, haver. Itt az ideje, hogy megfizess, amiért eladtál egy szabad embert a rabszolgaságba.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "Fizetni?! Mi a faszról beszélsz?";
			link.l1 = "Úgy értem, hogy megöllek ott, ahol állsz.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "Gondolj bele, kinek dolgozol?! Ez az ember szerencsétlen, és a helye a cukorültetvényen van!";
			link.l1 = "Nos, ez már nem tartozik rád. Most felelned kell azért, amit tettél!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "Ho! Csak úgy fogok válaszolni, ahogy általában szoktam!";
			link.l1 = "Gyerünk...";
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
			dialog.text = "Mit szeretne?";
			link.l1 = "Azt akarom kérdezni, hogy szállít utasokat? ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "És mi köze van hozzá?";
			link.l1 = "Csak kérdeztem.";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "Csak kérdezem... Nézze, jobb, ha eltûnik innen, amíg még van rá lehetôsége. Nem szeretem magát!";
			link.l1 = "Rendben, rendben, nyugodj meg. Elmegyek...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "Már beszéltünk, szóval ne tegyél próbára!";
			link.l1 = "Nem fogom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Üdvözletem, kolléga! Akarsz valamit?";
			link.l1 = "Szeretném tudni, nem vitte el a nôt a " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " nevû " + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "Heh, igazad van, a kabinomban van! Dögös csaj, amúgy jó lábakkal... Miért kérdezed?";
			link.l1 = "Haver, ez a nô házas. Ez nem helyes.";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "És akkor mi van? Kedvelem ôt, és ennyi. Nem hagyom, hogy egy rongyos idióta beleszóljon a kapcsolatunkba, csak mert a férje!";
			link.l1 = "Hadd mondjam el neked, hogy a Testvériség nem helyesli az ilyesmit, és ha bizonyos emberek meghallják, amit tettél, akkor a fekete jelet fogják rád küldeni.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "Elkezdesz engem prédikálni?";
			link.l1 = "Nyugodj meg, csak érdeklôdtem... Viszontlátásra.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "Már beszéltünk a nôrôl. Nem akarom még egyszer megbeszélni a dolgot!";
			link.l1 = "Mindegy...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Örülök, hogy üdvözölhetek egy kollégát a fedélzeten! Mit akarsz?";
			link.l1 = "Szeretném tudni, hogy elraboltak-e egy nôt  a " + XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen") + " nevû" + GetFullName(sld) + "?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "Heh, igazad van, a kabinomban van! Dögös csaj, amúgy szép lábakkal!... Miért kérdezed?";
			link.l1 = "Haver, ez a nô házas. Ez nem helyes.";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "És akkor mi van? Kedvelem ôt és ennyi. Nem hagyom, hogy valami rongyos fickó beleszóljon a kapcsolatunkba, csak mert a férje!";
			link.l1 = "Hadd mondjam el neked, hogy a Testvériség nem helyesli az ilyesmit, és ha bizonyos emberek meghallják, amit tettél, akkor a fekete jelet fogják rád küldeni.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "Elkezdesz engem prédikálni?";
			link.l1 = "Nyugodj meg, csak érdeklôdtem... Viszontlátásra.";
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
			dialog.text = "Mit akarsz tôlem, te szemétláda?!";
			link.l1 = "Azért a nôért vagyok itt, akit elloptál a férjétôl. Emlékszel " + XI_ConvertString("Colony"+npchar.quest.cribCity) + "? A neve " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "A francba! Soha nem fogod látni ôt, ahogy a füleidet sem fogod látni!";
			link.l1 = "Idióta. A tükörben látom ôket. És én levágom a tiédet!";
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
			dialog.text = "Ki vagy te?";
			link.l1 = "Hahó! Azért jöttem, mert a férje megkért rá. Most már szabad vagy, és elvihetlek hozzá.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "Ez egy álom?! Ez igaz?!";
			link.l1 = "Ez az, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "Dicsértessék az Úr! Készen állok, tûnjünk el innen!";
			link.l1 = "Persze, " + GetAddress_FormToNPC(NPChar) + ", készülj fel a biztonságos visszatérésre a férjedhez.";
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
			dialog.text = "Hahó! Örülök, hogy üdvözölhetek egy kollégát a földön...";
			link.l1 = TimeGreeting() + ", Van egy kis dolgom veled.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "Hallgatlak.";
			link.l1 = "Az egyik társad keres téged. Együtt hajóztatok, és az Óvilágból érkeztetek ide." + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ", emlékszel?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "Ha, persze, hogy emlékszem! És hol él most?";
			link.l1 = "Be " + XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = " Köszönöm! Tudod, azt hittem, hogy kalóz vagy!";
			link.l1 = "Az is vagyok. Olyasmi. Vagy mégsem. De mindegy, ma jó kedvem van, úgyhogy nincs miért aggódnod. Viszlát.";
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
			dialog.text = "Valami gond van? Sajnálom, egy kicsit ideges vagyok...";
			link.l1 = "Semmi baj, haver.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting() + ". Mit akarsz tôlem? Én csak egy egyszerû kereskedô vagyok és...";
			link.l1 = "Tudom, haver. Ne aggódj ennyire, azt mondják, nem tesz jót az egészségnek. Van egy kis dolgom veled.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "Miféle üzlet?";
			link.l1 = "Egy barátod keres téged. A neve " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + ". Ismered ôt?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "Ó, végre! Ez nagyszerû... Elnézést a durva üdvözlésért, de azt hittem, hogy kalóz vagy.";
			link.l1 = "Én vagyok. Valahogy úgy. Vagy nem vagyok. De mindegy is, ma jó kedvem van, úgyhogy nincs miért aggódnod. Arra kértek, hogy adjak át neked egy üzenetet, és én elvégeztem a feladatot. A társad a " + XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc") + "címen él."; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "Ez nem semmi! Maga egy becsületes ember. Köszönöm!";
			link.l1 = "Szívesen. Viszlát és vigyázz magadra, haver.";
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
			dialog.text = "Jó napot, uram. Kérsz valamit?";
			link.l1 = "A neved " + GetFullName(npchar) + ", igazam van?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "Igen, én vagyok.";
			link.l1 = "Valószínûleg hülyén hangzik, de a feleséged megkért, hogy mondjam meg, hogy aggódik érted.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "Ha! Értem... Valójában túlságosan elfoglalt voltam, sok jövedelmezô ajánlat van, és nem veszíthetek el lehetséges jövedelmeket csak azért, mert a feleségem túl sokat aggódik.";
			link.l1 = "De legalább írhatnál neki egy levelet, hogy jól vagy.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "Igen, igazad van. Azonnal írok neki! Köszönöm, hogy részt vesz a családi ügyeinkben!";
			link.l1 = "Szívesen, haver.";
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
			dialog.text = "Szép napot neked is. Miben segíthetek?";
			link.l1 = "A neved " + GetFullName(npchar) + ", igazam van?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Igen, én vagyok.";
			link.l1 = "Valószínûleg hülyén hangzik, de a feleséged megkért, hogy mondjam meg, hogy aggódik érted.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Fuh, a fenébe is! Attól féltem, hogy egy híres fejvadász jön értem, Félszemû Steve a neve. Nos, jó, hogy tévedtem\nNézze, annyira lefoglal a munkám, hogy nem tudok idôt szakítani rá. Folyamatosan jönnek a jövedelmezô ajánlatok, és nem tudom visszautasítani ôket a feleségem aggodalmai miatt.";			
			link.l1 = "Igazad van, persze. De legalább írhatnál neki egy levelet, hogy jól vagy.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Igen, igazad van. Megteszem a legelsô kikötôben... Köszönöm, hogy részt veszel a családi ügyeinkben!";
			link.l1 = "Szívesen, haver.";
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
			dialog.text = "Köszönöm, kapitány...";
			link.l1 = "Szívesen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "Örülök, hogy a városban látom, kapitány. Szüksége van valamire tôlem?";
			link.l1 = ""+ GetSexPhrase("Tudja, kapitány... Fuh, nem is tudom, hogy mondjam!","Igen, tudom.") +"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+ GetSexPhrase("Mondd ki úgy, ahogy van.","Érdekes, és mi az?") +"";
			link.l1 = " Lenne egy kérdésem hozzád. Ismer egy " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "nevû nôt?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "Heh, tudom. Nem volt szerencsém megismerni ôt. Egy bolond lány, mondhatom...";
			link.l1 = "Hm... Igen, és ez a bolond lány megkért, hogy öljelek meg. Ez az....";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "Badarság.";
			link.l1 = ""+ GetSexPhrase("Egyetértek. Elnézést, de a fejére vérdíj van kitûzve","Nem az. Van vérdíj") +". És én el fogom venni.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "Ho-ho!... Viccel velem, kapitány?";
			link.l1 = ""+ GetSexPhrase("Nem, barátom.","Nem is akartam!") +"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+ GetSexPhrase("Nem vagy a barátom, te idióta! Még csak kapitánynak sem nevezheted magad. Ennek az ostoba dühnek a játékszere vagy!","A fenébe! Az egyik fúria felbérelt egy másikat! Mi a fene folyik ebben a világban?") +"!";
			link.l1 = ""+ GetSexPhrase("Vigyázz a szádra, te szemétláda.","Kihasználtad ôt, ezért ne lepôdj meg, hogy úgy döntött, bosszút áll.") +"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+ GetSexPhrase("Talán eltaláltam az ideget?","Nôi szolidaritás?!") +"";
			link.l1 = "Vessünk véget ennek!";
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
			dialog.text = "Már beszéltem veled. Tûnj el, te idióta!";
			link.l1 = "Idióta?! Rendben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "Örülök, hogy a fedélzeten látom, kapitány. Mit akarsz?";
			link.l1 = "Lenne egy kérdésem hozzád. Ismer egy " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "nevû nôt?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "Heh, tudom. Nem volt szerencsém megismerni ôt. Egy bolond lány, mondhatom...";
			link.l1 = "Igen, és ez a bolond lány megkért, hogy öljelek meg.";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "Kapitány, ne nevettessen! Ha nincs semmi komoly dolga velem, akkor búcsút mondok magának.";
			link.l1 = "Akkor viszlát. De fontolja meg, amit mondtam.";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "Persze, kapitány, mi más lehetne?!";
			link.l1 = "Ég veled!";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "Nem akarok többet beszélni errôl a dologról, kapitány. Ez már túl nevetséges.";
			link.l1 = "Bármit is mond...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "Mi a fene folyik itt?! Miért támadták meg a hajómat?";
			link.l1 = "A " + GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)]) + "nevû hölgy kérésére. Ismered ôt?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "Mi a fene!!! Ezt nem hiszem el...";
			link.l1 = "Muszáj volt! Nem ismered a nôket, haver? Harapni tudnak.";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "Hát, én nem fogok csak úgy meghalni. Köszönöm a beszélgetést, most már visszanyertem egy kis erôt.";
			link.l1 = "Ez nem segít rajtad.";
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
			dialog.text = "Örülök, hogy a fedélzeten látlak. Segíthetek?";
			link.l1 = "Megteheti. Keresek egy férfit, akit " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "Ez az ember a foglyom, és váltságdíjat akarok érte kérni.";
			link.l1 = "El akarom vinni.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "Sajnos ez lehetetlen. Ha ez minden, akkor megkérném, hogy hagyja el a hajómat.";
			link.l1 = "Rendben, kapitány, ahogy mondja.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "Már beszéltünk a foglyomról. Semmi sem változott.";
			link.l1 = "Értem...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Örülök, hogy találkoztunk. Segíthetek?";
			link.l1 = "Lehet. Keresek egy férfit, akit " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + ".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "Ez az ember a foglyom, és váltságdíjat akarok érte kérni.";
			link.l1 = "El akarom vinni.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "Sajnálom, de ez nem lehetséges.";
			link.l1 = "Sajnálom...";
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
			dialog.text = "A francba! Mi a fene?!";
			link.l1 = "Szükségem van a " + sld.quest.SeekCap.name + " " + sld.quest.SeekCap.lastname + "nevû foglyodra.";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ha! Kizárt, csak a holttestemen keresztül!";
			link.l1 = "Ha már megkérdezted...";
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
			dialog.text = "Ki vagy te?";
			link.l1 = "Kapitány vagyok " + GetFullName(pchar) + ". Ne aggódj, azért vagyok itt, hogy elvigyelek a feleségedhez.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "A fenébe, biztos álmodom!";
			link.l1 = "Biztosíthatlak, hogy nem errôl van szó... Nos, most már mindennek vége, menjünk el innen.";
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
				dialog.text = RandPhraseSimple(RandPhraseSimple("Kimerült vagyok, segítsetek.", "Nincs több erôm így élni!"), RandPhraseSimple("Ez a munka elevenen felemészt.", "Kibaszott ôrök egy darab bôrt sem hagytak a hátamon!"));				
				link.l1 = RandPhraseSimple("Milyen kár.", "Igen, az élet szar.");
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
					dialog.text = "Ó, kapitány, üljön le mellém. Én fizetek!";
					link.l1 = "Örömömre szolgál.";
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
						dialog.text = "Helló, kapitány. Maga kapitány, ugye? Talán még a haditengerészet kapitánya is?\nIgen, ön biztosan jól bánik a karddal, ellentétben az én semmirekellô fiammal, aki holnap meghal... Emiatt a kéjsóvár fattyú miatt, aki szemet vetett a fiam érdekeltségi körébe tartozó hölgyre!";
						link.l1 = "Igen, kapitány vagyok, és a kardom már sokszor megmentett, de mi a helyzet a depressziós beszéded többi részével? Megmagyaráznád?";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "Красотка и пират".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "Üdvözletem, kapitány. Hadd kérdezzem meg, nem vagy véletlenül kalóz? Ó, persze, hogy nem! Nem vagy az. A kalózok csúnyán néznek ki, úgy viselkednek, mint az állatok, és az a bûz...";
						link.l1 = "Neheztel a kalózokra?";
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
							dialog.text = "Hé, te! Igen, te, mondd csak, hol a jó modorod? Mi a fenéért állsz itt és zavarsz engem? Nem, csak nézz rá, micsoda idióta! Hozzád beszélek! Félre az útból! Túl sok itt a kívülálló!";
							link.l1 = "Nyugodj meg, nem akartalak zavarni. Elnézést kérek.";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "Vigyázzon a nyelvére, vagy levágom, jó uram.";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "Волки и овцы".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "Üdvözlöm, kapitány. Szeretnék kérni valamit. Nem maradsz félre, ha becsületes ember vagy.\nSzóval, térjünk a lényegre: egy nemesember egy hónapja szállt meg a kocsmánkban. Kiderült, hogy egy züllött és fattyú! Sôt, még gyilkos is!";
						link.l1 = "Ha jól emlékszem, egy ártatlan ember meggyilkolásáért a büntetés a bitófa. Ha valaki züllött és fattyú, az a bíróságon sem fog sokat érni. Igazam van?";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "Трусливый фехтовалщик".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "Kapitány, várjon, könyörgöm. Ügyes vívónak látszik, sokkal jobbnak, mint én. Ezért megkérnélek, hogy helyettesíts engem.";
						link.l1 = "Érdekes. Folytassa.";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "Божий суд".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "Kérem, könyörgöm, ne menjen el! Várjatok... Nem segítenél szegény léleknek egy olyan ügyben, amihez egy ilyen bátor katonatiszt, mint te, beavatkozása szükséges?\nAz a helyzet, hogy a szomszédommal volt egy vitám a helyi szôlôültetvények miatt, egyébként csempészekkel való üzérkedéssel gyanúsítják. Igen, igen, és talán még kalózokkal is üzletel, másképp hogyan tehetne szert ilyen vagyonra pillanatok alatt?\nEgy éve még csak egy bárkája volt, most meg el akarja venni a szôlôültetvényeimet, figyelsz rám?! A szôlôskertjeimet!";
						link.l1 = "Rosszul érzem magam a szôlôskertjeid miatt. Ôszintén. Viszlát.";
						link.l1.go = "exit";
						link.l2 = "Elnézést, de nem tudna a helyi hatóságokhoz fordulni?";
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
						dialog.text = "Kapitány, kapitány, könyörgöm! Védje meg az ártatlan lány becsületét!";
						link.l1 = "Erre nincs idôm, szépségem. Keressen valaki mást...";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "Üdvözletem, hölgyem. Ne reszkess így! Mi történt?";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "Bogár. Szólj a fejlesztôknek.";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "Kapitány, a legegyértelmûbb módon cserkészett be a helyôrségünk egyik tisztje. Hallhattad volna ezeket a mocskos pletykákat, amelyeket rólam terjeszt, és amelyekkel megpróbál szégyent hozni rám!\nIstenem, nincsenek barátaim, akik képesek lennének megvédeni a becsületes nevemet! Kétségbe vagyok esve! Ó, Istenem, ez ô! Segítség!";
			link.l1 = "Ne aggódj, végig fogom csinálni.";
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
			dialog.text = "Á, hát itt vagy, úrnôm! Egy újabb gavallér, ugye? Mikor fogsz végre megállapodni? Talán soha... Menj és dolgozz a bordélyházban, az a legmegfelelôbb hely számodra...";
			link.l1 = "Biztos úr, fogja be a száját a sértegetésektôl, vagy a magam módján leállítom!";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "Hm... Ki vagy te? A-ah, maga a tenger által elsózott bátor kis hajóskapitány, igazam van? És mit fogsz csinálni, tengeri... kölyök?";
			link.l1 = "Ez a hölgy a barátom! És én megkímélem a kesztyûmet!";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "Micsoda?! Nem fogsz kihívni engem emiatt...";
			link.l1 = "Elég legyen! Két óra múlva a világítótorony közelében várlak. És ne felejtsd el hozni a kardodat!";
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
			dialog.text = "Ah, én mindent tudok, uram! Még azt sem érted, mennyire hálás vagyok neked! Az Úr óvjon meg téged!";
			link.l1 = "Örülök, hogy segíthettem neked. Sok szerencsét!";
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
			dialog.text = "Ah, te is olyan vagy, mint a többiek, hagyj békén!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "vagy a bordélyházban. ";
			dialog.text = "Ó, "+GetAddress_Form(NPChar)+"... Nem merek reménykedni, de talán a kardod ezúttal meg tudná védeni a családomat?\nAmint mondtam, a fiam nem vívó, de már másnap reggel párbajozni megy. Ah, ha nem lenne a dámája és az átkozott becsülete\nDe nem tudott félreállni, és most el van ítélve, nem látod? Kétségbe vagyok esve, ô az egyetlen fiam és örökösöm, ezért arra kérlek, hogy még a hajnal beállta elôtt öld meg a fattyút, aki kihívta a kisfiamat. Meg fogom érni, hogy megérje az idôdet, erre számíthatsz!\nA férfit a kocsmában találod meg "+sTemp+" - ott, ahol a hozzá hasonló fattyúk töltik a szabadidejüket... Könyörgöm...";
			link.l1 = "Nem érdekel sem te, sem a fiad. Engedjetek el!";
			link.l1.go = "exit";
			link.l2 = "Hm ... Csak így? Rendben, majd meglátjuk, mi lesz a vége.";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "Tényleg segíteni fog a fiamon? Ó, "+GetAddress_Form(NPChar)+"! Imádkozni fogok érted és a szerencsédért!";
			link.l1 = "Nem látok semmi rosszat ebben... Várjatok meg!";
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
			dialog.text = "Mi a fenét akarsz tôlem? Itt pihenek, és nem akarom, hogy zavarjanak. Rengeteg szabad hely és szabad fül van, úgyhogy hagyjon békén, uram!";
			link.l1 = "Sajnos, a jobb idôkig szünetet kell tartania a pihenésben.";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "Micsoda?! És ki maga, hogy megmondja nekem, mit tegyek?!";
			link.l1 = "Elfelejtettél engem, mi? De én emlékszem rád! És a lényeg az, hogy a hozzád hasonló gazemberek csak a jelenlétükkel mérgezik a világunkat!";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "Ah?! Matróz, úgy tûnik, hogy túl részeg vagy! Most látlak elôször! De nem fogom figyelmen kívül hagyni a viselkedésedet! Ez az utolsó esélyed, hogy megmentsd a nyomorult életed! Most szabadkozz, te felfújt hering, és én elfelejtem a pimasz beszédedet!";
			link.l1 = "Én csak a becsületes embereknek mentegetôzöm, nem a mocskos disznóknak!";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "Mi a fasz?! Keresed a bajt, te latrinás tetû?";
			link.l1 = "Elcsukom a kibaszott torkodat a szavaiddal, te patkány! Két óra múlva a világítótorony mellett várlak, és ne felejtsd el azt a rozsdás szart, amit az öveden hordasz!";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "Ha! Ott leszek!";
			link.l1 = "Hamarosan találkozunk!";
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
			dialog.text = "Ó, te vagy az! Életben vagy, ami azt jelenti, hogy...";
			link.l1 = "Igen, és a fiadnak nem kell holnap reggel párbajoznia...";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "Micsoda szép nap! Mennem kell, hogy jó híreket mondjak a feleségemnek!\nKapitány, a sors maga küldött téged, hogy segíts nekem. Tessék, fogadd el ezeket az érméket, és fogadd el családunk háláját!";
			link.l1 = "Köszönöm!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("Megkaptad "+FindRussianDublonString(iTemp)+"");
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
			dialog.text = "Kopj le, gyilkos kölyök!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "Én? Hála Istennek, jól vagyok, de a nôvérem nem ilyen szerencsés. Ô egy kocsmában szolgál\nVan egy magánember, aki gyakran megfordul ott, egy nagyon veszélyes fajta. Kalóz! A hajója már egy hete úton van, nem kevesebb, mint egy hete. A férfi iszik, fenyegeti az embereket, és megígéri, hogy mindenkit megöl, aki megpróbál szóba állni vele. A legrosszabb az, hogy a nôvérem azt mondta, hogy azzal kérkedik, hogy ellopja ôt és az ördög tudja hova viszi, ha nem teljesíti a mocskos kívánságait!\nNem tudom, mit tegyek! A hatóságok nem törôdnek néhány szolgálólánnyal, és a hozzám hasonló békés polgárok félnek ettôl a magánembertôl. Segítsen nekünk, hogy elbánjunk vele, kérem!";
			link.l1 = "Nincs idôm arra, hogy a kocsmák részeges embereit nyugtassam. Beszélj a parancsnokkal, ôt fizetik, hogy megoldja az ilyen ügyeket.";
			link.l1.go = "exit";
			link.l2 = "Hm, egy fenyegetô kalóz? Rendben, majd én elintézem.";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "Ah, köszönöm, kapitány! Biztos vagyok benne, hogy hallgatni fog rád, ahogy egy matróz hallgat egy matrózra! Vegye rá, hogy örökre békén hagyja a húgomat! Nem vagyunk gazdagok, de eleget fizetünk a fáradozásaidért!";
			link.l1 = "Jól van, jól van... Már úton vagyok, hogy megoldjam a problémáitokat. Várjatok meg!";
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
			dialog.text = "És akkor mi van? Beszéltél azzal a kalózzal? Békén fog hagyni minket?";
			link.l1 = "Várj egy kicsit. Rajta vagyok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "Mit akarsz? Nem látod, hogy itt pihenek?";
			link.l1 = "Nocsak, nocsak... Íme, a söröskorsók nagy ura, a lányok ellopója és e kisváros hús-vér vihara, igazam van? És te ilyen bátor lennél a városon kívül? A világítótorony közelében, párbaj, két óra múlva?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "Oh-ho-ho! Hôsnek tetteted magad? Mindegy, haver, ma jó kedvem van, úgyhogy megbocsátok neked. Menj és vegyél nekem pár korsó sört!";
			link.l1 = "Nem vagyok a haverod. Megismételjem magam egy ilyen idióta miatt, mint te? Olyan bátor lennél, hogy megjelenj egy párbajra, mint amilyen bátor vagy, hogy megjelenj a kocsmában?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "Kihívsz engem?! Mi bajod van? Meguntad az életet, meg akarsz halni? Rendben, ha tényleg ezt akarod, akkor elsétálok a világítótoronyhoz, kitépem a beledet, aztán ezt az átkozott kocsmát is elpusztítom!";
			link.l1 = "A beszéd olcsó, a kardok nem, úgyhogy ne feledd, hogy hozz magaddal egyet!";
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
			dialog.text = "És akkor mi van? Beszéltél már azzal a kalózzal? Magunkra hagy minket? A nôvérem azt mondta, hogy elhagyta a kocsmát, és nem jött vissza...";
			link.l1 = "Én igen. A fickó egy kicsit goromba volt, de az én érveim eléggé ésszerûek és meggyôzôek voltak. A húgodnak most már nincs mitôl félnie.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "Ennek... vége? Most már szabadon lélegezhetünk? Köszönöm, kapitány! És hol... hol van az a gazember?";
			link.l1 = "Ô... a hajóján van. Úgy döntött, hogy a lehetô leghamarabb elhagyja ezt a várost.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "Nagy szolgálatot tettél a kolónia polgárainak! Tessék, fogadd el ezt a jutalmat a segítségedért! Elég szerény, de minden barátom tisztelni fogja, és higgye el, nekem sok barátom van!";
			link.l1 = "Köszönöm! Sok szerencsét neked és a húgodnak! Kívánom neki, hogy egy tisztességes férfihez menjen férjhez. Viszontlátásra!";
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
			dialog.text = "Ó, tényleg? És hogyan akarsz megállítani?";
			link.l1 = "Természetesen a kardommal, ez az egyetlen megfelelô módja egy ilyen szemtelen disznónak, mint te.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "Pompás! Két óra múlva a világítótorony mellett foglak várni.";
			link.l1 = "Szép volt! Biztosan ott leszek.";
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
			dialog.text = "Tûnj az utamból, gyáva!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "Kapitány, a fattyú nem ilyen egyszerû, Tom, a régi barátom, meghalt egy párbajban ellene, kardcsapásért vádolták! Ártatlan volt, esküszöm. De a kormányzó azt mondta, hogy abban az átkozott párbajban nem volt bûn.";
			link.l1 = "Hm... Az egész a barátod hibája. A kártyacsapkodás rossz hatással lehet az egészségedre.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "Igen? Az elmúlt két hétben már négy kártyavetô volt a városunkban. És mindannyian megpróbálták becsapni a nemesünket? Mit szólnál ehhez? A lényeg az, hogy ez a nemesember maga a kártyavetô. Ha nem hiszel nekem, akkor menj és ellenôrizd magad.";
			link.l1 = "Úgy érted, hogy szerencsejátékot akarsz játszani vele? Nem, nem szeretek játszani. Semmi esélye.";
			link.l1.go = "exit";
			link.l2 = "Azt hiszem, meg fogom tenni... Valami nagyon nem stimmel itt.";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "Kapitány, én és a barátaim összegyûjtöttünk egy összeget, hogy kifizessük azt az embert, aki leleplezi azt a nemest, és revansot veszünk rajta minden tettéért. A városban fogok várni, hogy átadjam a jutalmadat, amint a munka befejezôdött.";
			link.l1 = "Megteszem, ha igaz, amit mondasz.";
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
			dialog.text = "Tiszteletem, uram! Egy nemes embert látok, és talán... egy szerencsejátékost? Van kedved játszani?";
			link.l1 = "Szívesen! Beszéljünk a tétrôl. Mit szólna 50 érméhez?";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "Most biztos csak viccelsz velem? Nincs nálad!";
				link.l1 = "Igazad van...";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "A tét lényegtelen, játszani fogunk, ez a legjobb rész. Már majdnem elfelejtettem, hogy néznek ki a kártyák, a helyi idióták miatt.";
				link.l1 = "Nos, kezdjük.";
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
			dialog.text = "Szóval, a tét 50 érme.";
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
			dialog.text = "Várj egy kicsit, mi az?... Az lehetetlen! Uram, maga csaló! Adja vissza az érméimet!";
			link.l1 = "Biztos van rá nyomós okod, hogy engem hibáztass,  "+GetAddress_FormToNPC(NPChar)+". Jobb, ha most rögtön lelövöd ôket, különben párbaj lesz!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "Ah, csak így? Rendben, akkor párbaj! Ma, két óra múlva, a világítótorony közelében!";
			link.l1 = "Áll az alku!";
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
			dialog.text = "Van valami hír, kapitány?";
			link.l1 = "Igazad volt, engem is megvádoltak csalással, ezért párbajban kellett felszeletelnem a fattyút.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "Látod? Tudtam én ezt! Sok köszönet tôlem és a barátaimtól! Tessék, vegye el a jutalmát, kapitány.";
			link.l1 = "Köszönöm.";
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
			dialog.text = "Mondtam már, hogy azért jöttem ide, hogy jelentkezzek egy vívótanári állásra? Nem? Szóval, a helyi kormányzó korrepetitort keres az unokaöccsének, és ez tökéletesen illik hozzám. Ismerem ennek a mûvészetnek az alapjait, mégsem próbáltam ki soha a gyakorlatban\nMajdnem zsebemben volt az állás, ám kiderült, hogy a helyi kereskedô bajba került, valami veszélyes kinézetû gazember fenyegeti. A kormányzó megbízást adott, hogy foglalkozzak ezzel az üggyel, hogy próbára tegye a szakmai képességeimet.";
			link.l1 = "Akkor tegye meg. Viszontlátásra.";
			link.l1.go = "exit";
			link.l2 = "És mit akar ez a gazember a kereskedôtôl, és mire van rám szüksége?";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "Azt hittem, hogy az az ember zsoldos, és zsoldosokkal mindig lehet üzletet kötni. Régi adósságok vagy bármi... De a férfi komolyan gondolta, hogy továbbra is nyomást akar gyakorolni a kereskedôre. Arra akartam kérni, hogy segítsen a kereskedônek és nekem azzal, hogy megmenti ôt a zsoldostól, és teljesíti a kormányzó parancsát\nNekem tényleg szükségem van erre a pozícióra, és egyedül nem tudok megszabadulni a zsoldostól. Kérem, segítsen nekem, és minden megtakarított érmét odaadom, különben kénytelen leszek szégyenszemre elhagyni a várost!";
			link.l1 = "Rendben, rendben, segítek... 'vívómester'.";
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
			dialog.text = "Mit akarsz? Nem látod, hogy elfoglalt vagyok?!";
			link.l1 = "Valami tisztességes kereskedôt zavarsz és lármázol?!?";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "Bah! Még egy védelmezô? Olcsóbb lesz engem fizetni, mint minden nap ôröket alkalmazni. Nem igazán szeretem a gyilkos munkát, szemben az adósságok kiütésével, úgyhogy ha ilyen hôs vagy, akkor gyere a világítótoronyhoz, és párbajban próbára tesszük egymást. Ha pedig nem vagy az, akkor ne szórakozz velem többet.";
			link.l1 = "Megegyeztünk! Ott fogok várni rád.";
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
			dialog.text = "Úgy tûnik, te még nálam is gyávább vagy...";
			link.l1 = "Igen, az vagyok.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "Van valami hír, kapitány?";
			link.l1 = "A zsoldos halott. Remélem, hogy a pozíció most már a tiéd?";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "Ó, kapitány, köszönöm! Vedd el a jutalmadat, én pedig jelentem a kormányzónak!";
			link.l1 = "Isten veled... mester.";
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
			Log_Info("Kaptál egy ládát, tele dublonnal.");
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
			dialog.text = "Még egyet?";
			link.l1 = "Fenékig.";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "És még egyet!";
			link.l1 = "Várj egy kicsit! Hová rohansz?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "A pokolba a kérdésekkel! Igyál!";
			link.l1 = "Jó, de talán késôbb elmondod, mi történt veled?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "Tényleg érdekli? Akkor figyelj, amíg még tudok beszélni! Pár nap múlva nem tudok majd beszélni, mert meg fogok halni... Igen, halott! És a rum a hibás. A sok rum és ez a tiszt, akit nyilvánvalóan az ördög hozott a fejem fölé!\nNem verekednék a helyôrségünk és az egész város legjobb vívójával, ha józan lennék, vagy legalábbis nem lennék ennyire részeg. De most mi van? El vagyok ítélve, részeg vagyok, és halott vagyok! Olyan ostoba bolond vagyok...";
			link.l1 = "Igen, ez túl ostoba volt. De a jövôben valószínûleg okosabban fogsz viselkedni... persze abban az esetben, ha túléled a párbajt. Viszlát.";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "A részegség sem a legjobb megoldás, biztos úr. Biztos vagyok benne, hogy létezik megoldás erre a problémára.";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "Miféle megoldás? Hogy dezertáljak és elveszítsem a hírnevemet és a tiszti egyenruhámat? Vagy öngyilkosságot követek el, hogy ne vágjanak le, mint egy disznót? Mit tanácsol?";
			link.l1 = "Egyiket sem. Segíteni fogok neked, és megpróbálom megakadályozni, hogy az ellenfeled bármilyen kárt okozzon neked a párbaj ideje elôtt. Hol találom ôt?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "Komolyan mondod? Megteszed?! Ó, esküszöm, meg fogom érni, hogy megérje!\nA városban található. A szeretôje itt él, minden tiszt hallott róla, de sajnos a címe ismeretlen... Szóval az a tippem, hogy ott is megtalálod.";
			link.l1 = "Ennyi elég. Várjatok meg itt. Megyek, és elbeszélgetek ezzel a... 'legjobb vívóval'..";
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
			dialog.text = "Van valami hír a számomra, uram? Jók, vagy... nem is olyan jók?";
			link.l1 = "Még nincsenek híreim. Várjatok itt. Minden rendben lesz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "Van valami hír a számomra, uram? Jók, vagy... nem olyan jók?";
			link.l1 = "Vége van. A potenciális ellenfeled nem fog tudni többé ártani senkinek... Most már biztonságban vagy. De remélem, hogy tanulni fogsz ebbôl a leckébôl, és nem leszel agresszív olyan emberekkel, akiket nem ismersz.";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "Ugye nem viccelsz velem? Nagyon hálás vagyok, "+GetAddress_Form(NPChar)+"! Tessék, vegyél el mindent, amim van. Ez a fizetésem, vedd el mindet!\nEgy lecke, azt mondod? Igen, a fenébe is, igazad van! Soha többé nem fordul elô! Ezt megígérem neked, és még egyszer köszönöm, hogy adtál még egy esélyt!";
			link.l1 = "Rendben. Viszlát, biztos úr...";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("Kaptál egy erszényt dublonnal.");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "Még egyszer köszönöm, "+GetAddress_Form(NPChar)+", a segítséget!";
			link.l1 = "Mindig szívesen látunk...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "Hé, mi a fene? Mit keresel a hölgyem szobájában? Takarodj innen, vagy erôszakkal kirángatlak innen!";
			link.l1 = "Oda megyek, ahová akarok, és nem fogom jelenteni az ilyen viselkedésed! Erôszakkal? Akkor próbáld meg!";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "Micsoda szemtelenség! Hallatlan arcátlanság! Uram, ön tényleg téved! Azonnal hagyja el ezt a házat, vagy esküszöm, hogy meg fogja bánni az életét!";
			link.l1 = "A beszéd olcsó! Te fogod ezt megbánni, nem én, "+GetAddress_FormToNPC(NPChar)+"! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "Tényleg? Akkor vigyázz! Ha megöllek ebben a házban, az gyilkosság lesz. Hogy a halálod ne ártson a nevemnek, a becsületes emberek az ilyen ügyeket egy világítótorony közelében intézik!\nKihívlak, "+GetAddress_Form(NPChar)+", te szemtelen ember! Felelni fogsz a szavaidért! Szóval, párbaj két óra múlva?";
			link.l1 = "Persze, "+GetAddress_FormToNPC(NPChar)+" merész fickó.";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "Akkor gyôzôdj meg róla, hogy idôben ott leszel. Még mindig van idôd, hogy rendelj egy halotti beszédet a papunktól.";
			link.l1 = "Gyászmisét neked? Egy pezót sem érsz. Találkozunk a világítótoronynál!";
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
			dialog.text = "Tûnjetek el!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "A kormányzóra gondol? Ha! 'Isten ítélete' azt mondta nekem a kormányzó a panaszaimra válaszul! Párbaj! Hogy tetszik? Én csak egy csendes, békeszeretô ültetvényes vagyok, nem bandita vagy harcos\nEz gyilkosság lesz, nem párbaj! És te kétségtelenül jobb vagy az ilyen dolgokban, mint én. Ezért arra kérlek, hogy legyél a képviselôm a közelgô párbajban. Hidd el, nem maradok adósodva.";
			link.l1 = "Mikor lesz a párbaj?";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "Ma éjfél elôtt a világítótorony közelében. Segítesz nekem?";
			link.l1 = "Rendben, segítek. Várj meg a városban!";
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
			dialog.text = "Mondd el, mi történt ott? Mi... Bocsánat, te nyertél?";
			link.l1 = "Biztos vagyok benne, hogy érdekes lesz számodra, ha megtudod, hogy rajtaütés volt. Lehet, hogy a szomszédod úgy döntött, hogy visszabiztosítja magát azzal, hogy egy helyett több képviselôt hívott meg, és mindannyian tapasztalt banditák voltak. Szerencsére én tapasztalt vívó vagyok.";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "Micsoda szemétláda! Most már gondolom, a kormányzónak nem lesz oka elutasítani a kérésemet, hogy tartóztassam le a gazembert! Köszönöm! Vedd el a jutalmadat, nekem pedig a rezidenciára kell mennem.";
			link.l1 = "Ég veled!";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("Kaptál dubloonokkal teli erszényt");
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
			dialog.text = "Jó móka hibák nélkül játszani, mert azokat a szukákat nehéz megtalálni.";
			link.l1 = "Nyugalom, tájékoztatom a fejlesztôket.";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "Á, hát itt vagy. Ezek a barátaim és a másodhegedûseim. Kezdhetjük?";
					link.l1 = "Szolgálatodra állok!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "Mindannyian összegyûltek. Készen álltok?";
					link.l1 = "Igen, kezdhetjük!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "Végre! Már arra gondoltam, hogy ilyen hosszú utat kellett megtennem a semmiért... Fejezzük be gyorsan, hagytam egy pohár rumot és egy forró szajhát a kocsmában!";
					link.l1 = "Biztos vagyok benne, hogy egyikre sem lesz többé szükséged!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "Jackanapes":
					dialog.text = "Szóval úgy döntöttél, hogy eljössz? Végre! Akkor kezdjük el!";
					link.l1 = "Ne siess így, még a végén pengére esel.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "És ezek az én segédeim, uram. Most készüljetek a halálra!";
					link.l1 = "Csak utánad.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CowardFencer":
					dialog.text = "Itt is vagyunk. Készítse a kardját, uram!";
					link.l1 = "Örömmel, gyôzzön a jobbik!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CoatHonor":
					dialog.text = "Kiváló, mindenki megérkezett... Kezdjük, uram!";
					link.l1 = "Táncoljunk!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "GodJudgement":
					dialog.text = "És te ki vagy? Nem úgy nézel ki, mint egy átlagpolgár, haver...";
					link.l1 = "Na és? Párbajt rendeztem veled?!";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1"
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "Ha! Párbaj! Úgy tûnik, hogy te vagy az ügyfelünk. Srácok, szúrjuk le, és menjünk és vegyük el a jutalmunkat. Kibelezzük!";
			link.l1 = "Csapda? Milyen szánalmas, ennél sokkal többre lesz szükséged, hogy elintézz...";
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
				dialog.text = "Nem gondolod, hogy hagyjuk, hogy megöld a barátunkat, és csak úgy elmenekülj? Fegyverbe!";
				link.l1 = "Ezt kellett volna várnom egy ilyen szerencsétlen fattyútól!";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "Kapitány, a becsület helyreállt, gyôztél. De engedd meg, hogy adjak egy jó tanácsot - hagyd el a várost, és egy ideig ne jelenj meg itt...";
				link.l1 = "És mi a probléma?";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "Mindez a becsület miatt volt, és most menjünk, és vegyük el a barátunkat.";
				link.l1 = "Persze, nem foglak megállítani...";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "A probléma az, hogy megöltétek a parancsnokunk egyik rendtagját. Rossz ember volt, és senki sem fogja megbánni a halálát... de a parancsnok nagyon szerette ôt, és soha nem fogja megbocsátani neked a barátja halálát.";
			link.l1 = "Köszönöm a tanácsot, biztosan megfogadom. Viszlát.";
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
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
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
		case 0: sText = "Egy fattyú elcsábította a húgomat a naivitása miatt, majd elhagyta, miután elintézte a dolgát. Nem hagyhattam, hogy büntetlenül megússza, ezért kihívtam ôt. Megijedt, és elmenekült a hajóján." break;
		case 1: sText = "Egy becstelen fattyú hatalmas összeget vesztett nekem szerencsejátékon, és elmenekült a hajóján." break;
		case 2: sText = "Egy gazember pénzt adott kölcsön tôlem, és amikor nem voltam otthon, hamis pénzérmékkel törlesztette az adósságot a szolgámnak. Most valahol a hajóján bujkál." break;
		case 3: sText = "Egy gazember megpróbált meggyalázni engem a kormányzó szemében, de hazugsága leleplezôdött, és ez a fattyú elmenekült a hajóján. " break;
		case 4: sText = "Az én hibám volt, valami gazembert vettem fel könyvelônek. Nagy csalást követett el, vett egy hajót és elszökött. " break;
		case 5: sText = "A volt ôröm ellopott egy ékszerekkel teli dobozt a feleségem budoárjából és elszökött. Most már látom, honnan van elég pénze egy hajó megvásárlására. " break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "Egy fattyú elcsábította a húgomat a naivitása miatt, majd elhagyta, miután elintézte. Nem hagyhattam, hogy büntetlenül megússza, ezért kihívtam. De felfogadták hajóskapitánynak, és elhajózott.";
			npchar.quest.text1 = " Megbecstelenített egy nôt és gyáván elmenekült.";
		break;
		case 1:
			npchar.quest.text = "Egy becstelen fattyú hatalmas összeget vesztett nekem szerencsejátékon, de még mindig nem fizetett nekem, hallottam, hogy felfogadták ágyúsnak és elszökött.";
			npchar.quest.text1 = "elvesztette az összes pénzét a szerencsejátékban és nem akarta visszafizetni a tartozását. ";
		break;
		case 2:
			npchar.quest.text = "Egy gazember pénzt adott kölcsön tôlem, és amikor nem voltam otthon, hamis érmékkel fizette vissza az adósságot a szolgámnak. Most egy hajón szolgál szállásmesterként, és bujkál elôlem. ";
			npchar.quest.text1 = "Hamisító, aki bûncselekményt követett el";
		break;
		case 3:
			npchar.quest.text = "Egy gazember megpróbált meggyalázni engem a kormányzó szemében, de hazugsága leleplezôdött. Szerencséjére a gazembert orvosként alkalmazták az egyik hajón, és elmenekült.";
			npchar.quest.text1 = "rágalmazó és intrikus, aki megpróbált meggyalázni egy jó polgárt.";
		break;
		case 4:
			npchar.quest.text = "Az én hibám volt, hogy valami gazembert vettem fel könyvelônek. Nagy csalást követett el, és most egy hajón szolgál szállásmesterként, és bujkál elôlem.";
			npchar.quest.text1 = "...és a vádak szerint csalás és hûtlen kezelés miatt...";
		break;
		case 5:
			npchar.quest.text = "A volt ôröm ellopott egy ékszerekkel teli dobozt a feleségem budoárjából és elszökött. Egy hajóra felvették, mint fedélzeti tisztet.";
			npchar.quest.text1 = "egy közönséges tolvaj, és a börtönben a helye. Ékszereket lopott a saját munkaadójától.";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "a régi cimborámtól, aki közeli barátom volt az Óvilágban.";
			npchar.quest.text1 = "Ô a te régi barátod.";
		break;
		case 1:
			npchar.quest.text = "Egy férfi, aki tulajdonképpen az apám volt.";
			npchar.quest.text1 = "Olyan voltál neki, mintha az apja lettél volna.";
		break;
		case 2:
			npchar.quest.text = "A mostohatestvérem, aki fiatalon elhagyta az Óvilágot.";
			npchar.quest.text1 = "Te vagy a mostohatestvére.";
		break;
		case 3:
			npchar.quest.text = "Egy férfi, aki tényleg segített nekem az Óvilágban.";
			npchar.quest.text1 = "Sokat segítettél neki.";
		break;
		case 4:
			npchar.quest.text = "a nôvérem férje, aki a barátom volt az Óvilágban.";
			npchar.quest.text1 = "Te vagy a nôvére férje.";
		break;
		case 5:
			npchar.quest.text = "a barátom, a fegyveres testvérem az Óvilágban.";
			npchar.quest.text1 = "Fegyvertársak voltatok.";
		break;
	}
}
