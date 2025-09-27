// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("A "+ GetCityName(npchar.city) +" összes pletykája az Ön rendelkezésére áll. Mit szeretnél megtudni?",
                          "Éppen errôl beszéltünk. Biztos elfelejtette...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Ismétled, mint egy papagáj...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Igen...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Francois Gontier nem járt véletlenül a városukban? Van egy Corvette '" + pchar.questTemp.Slavetrader.ShipName+ "', csak a biztonság kedvéért... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "Mondja, pajtás, hol találom Don Diego de Montoyát? Elkéstem? Már elindult Main felé?";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Figyeljen, nem járt itt egy Joachim Merriman nevû férfi? Egy középkorú orvos, portugál, bajusszal, császári szakállal és szúrós szemekkel? Talán szobát akart bérelni?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "Aha, az a komor fickó? Igen, megállt nálam. Elmondok valamit: találkozója volt az Oregon és Haskonnal. Szabadalmat kért. De nem jött össze neki, és eljött onnan.";
			Link.l1 = "És hová hajózott el, tudja? Porto Bello óta üldözöm, de nem találom.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "Mit akarsz tôle? Fél az idegenektôl, mindig elbújik mindenki elôl, amint meglát egy fegyveres idegent, kardot ragad. Csak négy ôrrel körülvéve járkál. Véletlenül nem te vagy az, akitôl ôrizkedik?";
			Link.l1 = "Uramisten, az emberek újra és újra ezt mondják! Mi van, gyilkosnak nézek ki? Ô a régi cimborám, sietek átadni neki néhány hírt, egészen megörül majd, ha megtudja, hogy nem kell tovább bujkálnia, senki sem keresi.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "Nem kell bujkálnia? Ha-ha-ha-ha! Egy nappal Havannából való távozása elôtt egy egész csapat gengszter próbálta megölni a dzsungelben... Persze, ott voltak a saját emberei, és azok egy pillanat alatt darálták ôket. És most azt mondod...";
			Link.l1 = "Ó, ugyan már. Valószínûleg csak néhány helyi bandita próbálta megszerezni a pénztárcáját. Te magad is tudod, mennyi gazember mászkál a dzsungelben. Szóval, hova ment?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "Nos, miután messzire és hosszú idôre elküldték a rezidenciától, folyton azt hajtogatta, hogy feladja magát a frodzsóknak, a honfitársainak. Elindult Tortugára, valami d'Ogeronhoz... A szeretôjérôl is motyogott valamit, de nem egészen értettem.";
			Link.l1 = "Szóval, Tortuga? Nagyszerû! Remélem, ott elkapom. Köszönöm, " + npchar.name + ", rengeteget segítettél. Viszlát.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "Hm... És miért érdekelne egy franciát Don Diego, hm?";
			link.l1 = "Az a tény, hogy francia vagyok, lényegtelen. Ami számít, az ez a dokumentum, amit az inkvizítor írt alá. Nézze meg... látja már? Sürgôs üzenetem van Diego számára.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "A-ha, szóval Ôfelsége, Vincento atya számára dolgozik? Ez megváltoztatja a dolgokat. Don Diego de Montoya két napja távozott a századával, de hamarosan visszatért a futárhajóján. Az egyik hajója elsüllyedt a Kubától délre lévô zátonyokon, ezért éppen ma vásárolt javítási anyagot\nNézzétek meg a déli öblöt, ott találjátok a hajót és magát az embert. Kétlem, hogy már sikerült kijavítaniuk a lyukakat.";
			link.l1 = "Köszi, haver! Sokat segítettél!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Nincs mit, bármikor. Mindig örömmel segítek egy jezsuita testvérnek.";
			link.l1 = "Igen, pax vobiscum meg minden.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Az ördög tudja, haver. Lehet, hogy megérkezett, de én nem tudok róla. Bocsánat. Bocsánat.";
			link.l1 = "Értem, értem. Kár. Folytatom a keresést...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
