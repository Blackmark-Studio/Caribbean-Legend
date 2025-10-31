// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("A "+ GetCityName(npchar.city) +" összes pletykája az Ön rendelkezésére áll. Mit szeretnél megtudni?",
                          "Éppen errôl beszéltünk. Biztos elfelejtette...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Ismétled ugyanazt, mint egy papagáj...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Igen...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Figyelj, hol találom Francois Gontier-t? Már meg kellett volna érkeznie Tortugára.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Henri Thibaut-t keresem. Hol találom?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Henri Thibaut-t keresem. Hol találom?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Mondd csak, megállt mostanában a kolóniádnál egy 'Santa Margarita' nevû gálya? Esetleg magánhajós zsákmányként?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Nézd, haver, Gaspard Parmentier-t keresem. Hol találom?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "Segítenél egy kicsit, haver? Egy Joep van der Vink nevû embert keresek. Ismeri ôt?";
				link.l1.go = "PZ_1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier? Ki az a Francois Gtiertier? Nem ismerek ilyen nevû embert.";
			link.l1 = "Ô a korvett kapitánya '" + pchar.questTemp.Slavetrader.ShipName + "'.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "A leghalványabb fogalmam sincs, pajtás. És egy ilyen nevû korvett sem kötött ki a kikötônkben, ezt biztosan állíthatom.";
			link.l1 = "Rendben, akkor láttál mostanában idegeneket a városban?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "Jó kérdés! Ez egy kikötôváros, nem egy falu. Idegenek jönnek át minden nap. Bár hallottam már öt furcsa legényrôl, mindig szorosan egymás mellett maradnak, és készenlétben tartják a pengéjüket\nA járôr még kérdezôsködött is utánuk, eredménytelenül. De abban biztos vagyok, hogy nem egy korvettán érkeztek ide, ilyen hajót nem láttak a környéken, érted?";
			link.l1 = "Hm... Rendben, értem. Köszönöm, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Monsieur Thibaut egy híres ember Tortugán. A kastélya a kikötôi hatóság közelében van. Amikor elhagyod a tavernát, menj egyenesen a kikötô felé. Közelítsd meg a kikötôbe vezetô boltívet, fordulj balra a keresztezôdésben, és menj végig az utca végéig, ahol egy kétszintes, vörös tetejû kôépületbe botlasz. Ez Monsieur Thibaut kúriája.";
			link.l1 = "Köszönöm! Meglátogatom...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Monsieur Thibaut ma nagyon keresett, a kormányzó küldönce éppen most futott át ide. Ô is érdeklôdött. Túl nehéz megtalálni ôt? Már jó ideje bérel tôlem egy szobát a második emeleten, bár neki egy egész kastélya van. Nem tudom, mire kell neki, de sokkal gyakrabban jön be, mint ahányszor elmegy. És csak esténként van ott.";
			link.l1 = "Lehet, hogy most is itt van.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "Nem. Azt mondta, hogy ma este nyolcig nem jön vissza. Megpróbálhatod otthon keresni a kúriájában, de nem hiszem, hogy ott megtalálod. Láttam ôt egy ôrhajón a tengeren hajózni.";
				link.l1 = "Köszönöm! Késôbb beugrom hozzá.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Igen. Ha akarod, feljöhetsz.";
				link.l1 = "Köszönöm. Köszönöm. Meglátogatom...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "A hajó nevérôl fogalmam sincs, hogy 'Santa Margarita' vagy 'Castilian Whore' volt-e, de egy zsákmányolt spanyol gályát hoztak ide. Méghozzá egy sloop által foglyul ejtett gályát! Na ez aztán a kibaszott jó vitorlázás! Gaius Marchais, a kapitánya két napja henceg a kocsmában - az elsô útja, és ilyen zsákmány!\nIgen, nagyon hôsies tett, egy templomi patkányokkal teli gályára szállni, anélkül, hogy katonák ôriznék ôket. Úgy látszik, azok a pápista gazemberek elfelejtették, mit mondanak azokról, akik segítenek magukon...";
			link.l1 = "Igen, Isten megsegíti azt, aki önmagán segít, ez egy hugenotta mondás, az biztos. Hogyan tudnék egy pillantást vetni arra a szerencsés kapitányra? Itt van, a Tortugán?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ki a fene tudja. Már régen nem láttam a kocsmámban. Amint kijózanodott, a nyereménybôl vett egy csillogó új hajót, és úgy rohangált a fedélzetén, mint egy ôrült. Fogalmam sincs, hol lehet most Marchais. Talán Tortugán, vagy talán a tengeren.";
			link.l1 = "Jól van, rendben. Nos, köszönöm a történetet, haver!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "Bármikor, Monsieur. Mindig szívesen segítek szeretett kapitányunknak "+pchar.name+", St. Pierre megmentôjének! Ugorjon be késôbb!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "Úgy tûnik, Gaspard egyre népszerûbb a fajtád körében. A háza a fal mellett van. A tavernától balra fordulj a kikötô felé, de ne menj oda, hanem fordulj megint balra, menj egyenesen, majd fordulj jobbra. Egy kétszintes ház.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ_1":
			dialog.text = "Soha nem hallottam róla.";
			link.l1 = "Talán más néven fut. Talán úgy hallottál róla, mint a brigg kapitánya 'Banten'?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Arról a briggrôl sem hallottam még.";
			link.l1 = "Úgy hallottam, nemrég járt itt. Talán egy kis ezüst felfrissíti a memóriáját?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "Nos, kérdezd meg, hol hallottad. De nem bánom, ha elveszem az ezüstjét.";
			link.l1 = "Akkor ezúttal nincs ezüst. Viszontlátásra.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
