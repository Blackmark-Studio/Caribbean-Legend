// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek rád, mi a kérdés?"), "Már másodszor próbálsz kérdezni...", "Ez a harmadik alkalom, hogy megpróbálod megkérdezni...",
                          "Mikor lesz ennek vége?! Elfoglalt ember vagyok, gyarmati ügyekkel foglalkozom, és te még mindig zaklatsz!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Ne most. Rossz helyen és rossz idôben."), "Igaz... De késôbb, nem most...",
                      "Megkérdezem... De egy kicsit késôbb...", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Beszélni akarok a foglyáról.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Helló " + NPChar.name + ", a fogoly miatt vagyok itt.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Beszélni akarok a foglyáról.";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Úgy hallottam, hogy ön egy foglyokkal kapcsolatos üzletet folytat...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
		
		case "CapComission1":
			dialog.text = "Ha-ha. Azt hiszi, hogy csak egy foglyom van itt? Nevezze meg.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Itt van?";
			link.l1.go = "CapComission2";
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Itt volt. Eladtam annak a barbadosi ültetvénytulajdonosnak - Bishop ezredesnek, amikor egy hete itt járt.";
				link.l1 = "A fenébe...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "Á, végre. Arra gondoltam, hogy eladom annak a barbadosi ültetvényesnek, aki egy-két héten belül itt lesz... Van váltságdíja"+ GetSexPhrase("","") +"?";
				link.l1 = "Nézd, "+ NPChar.name +" , van egy kis probléma... Valójában nincs annyi pénzem. De kész vagyok dolgozni.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150.000 pezó. Hol kaphatom meg?"
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Túl lassú voltál... És miért érdekel téged? Csak a rokonaival tárgyaltam.";
			link.l1 = "Ôk kértek meg, hogy jöjjek ide.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Hát, elkéstél. Nem tehetek semmit.";
			link.l1 = "Figyelj, mennyiért adtad el ôt, ha nem titok?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, ez nem az. De nem mondom meg... Nevetni fogsz, ha megteszem. Ha-ha-ha-ha-ha! Viszontlátásra.";
			link.l1 = "Viszlát.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Nocsak, nocsak... Van egy üzletem... Még azt sem tudom, hogyan kezdjem el. El kell süllyesztenem egy kalózt, aki túl messzire ment.";
				link.l1 = "Nem lehet egyszerûen megölni a dzsungelben?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Nos, " + pchar.name + ", tudod, ez nem így mûködik. Gyere vissza a pénzzel, és megkapod a gyengébbik feledet, ha-ha.";
				link.l1 = "Rendben, akkor viszlát.";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}	
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Az üzlet nem így mûködik, tudod... Nem kell a halála, meg kell tanítanom néhány embert, hogy ne vegyék el a zsákmányom egy részét. De ha a cápákat eteti, nem leszek mérges.";
			link.l1 = "Miért nem küldöd utána a saját embereidet?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Hm... Nos " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " meggyôzött néhány kalózt, hogy a zsákmányuk egy részét a mi rejtekhelyünkön tartjuk, nem messze " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Két hajójuk '" + pchar.GenQuest.CaptainComission.ShipName1 + "' és '" + pchar.GenQuest.CaptainComission.ShipName2 + "' nemrég vetett horgonyt és elhajózott " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl") + ". Most már érted, miért nem bízhatom az embereimre ezt a munkát?";
			link.l1 = "Értem. Mennyi idôm van még?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12-15 nap, nem több. Nekem fontos, hogy ne jussanak el a rejtekhelyre, ostobaság lenne elsüllyeszteni ôket értékes rakománnyal. Ebben az esetben jobb lenne, ha ide hoznák...";
			link.l1 = "Rendben, én benne vagyok. Megpróbálom elkapni ôket.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);	
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
		break;
		
		case "CapComission2_3":
			dialog.text = "Ne aggódjatok. Az embereim majd átadják a hajódnak. És miért érdekel téged?";
			link.l1 = "Nem érdekel. A rokonai kértek meg, hogy szállítsam le.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Á, rendben van. Már majdnem megbántam, hogy ilyen alacsony árat adtam az emberedért. Ha-ha-ha-ha-ha-ha. Viszontlátásra.";
			link.l1 = "Viszlát.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission3":
			dialog.text = "Nos, " + GetFullName(pchar) + ", elsüllyesztetted a haveromat? Hé, hé, hé...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nem. Nem sikerült elkapnom ôket. És nem találkoztam velük, amikor visszatértem.";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
				{
					link.l1 = "Én igen. Elküldtem ôket, hogy etessék a cápákat.";
					link.l1.go = "CapComission5";
				}
			}	
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "A francba! Mindegy, most már nem számít! Mi lesz a következô javaslatod?";
			link.l1 = "Talán van egy könnyebb munkád számomra?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Figyelj, " + NPChar.name + ", csökkentsd a fogoly árát...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nem.";
			link.l1 = "Akkor viszlát...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");			
		break;
		
		case "CapComission4_2":
			dialog.text = "Lejjebb vinni az árat?! Épp most vesztettem el a készletemet a hozzá nem értésed miatt! Most már emelhetem az árat! Elviheted 200.000 pezóért, ha akarod, vagy elhúzhatsz innen a pokolba!";
			link.l1 = "Ez túl drága... Viszlát...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "A francba, rendben, vigye a pénzét.";
				link.l2.go = "CapComission4_5";
			}	
		break;
				
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Elviheted ezt a gyengét...";
			link.l1 = "Ég veled!";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
				
		case "CapComission5":
			dialog.text = "Ho-ho! Szép munka! Fogd a gyengédet és sok szerencsét.";
			link.l1 = "Köszönöm. Viszlát.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;
				
		case "CapComission6":
			dialog.text = "Elhoztad a pénzt, Charles? Nem vicceltem azzal, hogy eladom azt az embert az ültetvénynek.";			
			link.l1 = "Figyelj, "+ NPChar.name +", van egy probléma... Nincs annyi pénzem. De kész vagyok dolgozni.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150.000 pezó. Hol kaphatom meg?"
				link.l2.go = "CapComission2_3";
			}			
		break;
		
		//Захват пассажиров
		case "Marginpassenger":
			dialog.text = "És miért érdekel téged, hogy mit csinálok? Tudod, jobb lenne, ha elmennél...";
			link.l1 = "Tshh, nyugodj meg. Van egy üzleti ajánlatom a számodra. A foglyodról van szó.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Á, rendben. Kiért akar váltságdíjat kérni?";
			link.l1 = "Várj. Nem azért jöttem, hogy kivásároljam, hanem azért, hogy felajánljam neked, hogy vegyél egy foglyot. Nos, és lesz lehetôsége váltságdíjat kapni érte.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "A foglyáról van szó. És miért van szüksége az ügynökségemre? Nem akarja közvetlenül magának megszerezni a pénzt?";
			link.l1 = "Ez elég kockázatos lenne számomra. Lehet, hogy gondjaim lesznek a hatóságokkal.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... akkor rendben. Nézzük meg. Ki a foglya?";
			link.l1 = "Ez a "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Értem. Ez egy jó üzlet lenne, ha nem hazudik. Feltételezem, hogy ezért az emberért "+iTemp+" pezót fizethetek önnek, vagy adhatok helyette valami érdekes információt. A választás a tiéd.";
			link.l1 = "Inkább az érmét választom. Elegem van ebbôl az üzletbôl...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Mesélj még. Biztos vagyok benne, hogy valami érdekeset fogsz mondani.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Akkor pénzt. Fogd ôket. Ez nem a te problémád. Hozza ide az eladás tárgyát.";
			link.l1 = "Már a város kapujának közelében kell lennie. Köszönöm. Nagyon sokat segítettél nekem.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Szívesen, hozzon még... Viszlát!";
			link.l1 = "Sok szerencsét...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_SANDAL - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Jó egy okos emberrel üzletelni. Most figyelj: néhány nap múlva a " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat") + " egy spanyol expedíció érkezik Mainból, értékes árukkal megrakodva. Várni fognak egy hajóra, amelynek elvileg a rakományt kell átvennie. Ha egy héten belül odaérsz, akkor lesz esélyed, hogy magadhoz vedd a rakományt.\nA helyedben én már indulnék is a hajómhoz. És idehoznám a foglyot.";
					link.l1 = "Köszönöm. Köszönöm. Az áru szép kárpótlás lesz a fáradozásaimért. Az utasomnak pedig már a város kapujának közelében kell lennie. El fogjuk hozni hozzád.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Jó egy okos emberrel üzletelni. Most figyelj: körülbelül egy hét múlva egy spanyol brigantin '"+pchar.GenQuest.Marginpassenger.ShipName1+"' értékes árukkal megrakodva "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" elhajózik "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Ha sietsz, könnyen elkaphatod.\nMég mindig itt vagy? A helyedben én már elindultam volna a hajóm felé. És idehoznám a foglyot.";
					link.l1 = "Köszönöm! Köszönöm! Az áru szép kárpótlás lesz a fáradozásaimért. Az utasomnak pedig a város kapujának közelében kell lennie. Majd elhozzuk neked.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "part37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "parton47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "part48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "part25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "part21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "parton19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
