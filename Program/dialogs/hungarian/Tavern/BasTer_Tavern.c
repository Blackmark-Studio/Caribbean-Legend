// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Mi az, " + GetAddress_Form(NPChar) + "...", "Most már harmadszor zaklatsz...",
                          "Újabb kérdések, gondolom?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Igen, ez tényleg a harmadik alkalom...", "Nem, milyen kérdések?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "A régi cimborámat, Fernand Luc-ot keresem. Van néhány kérdésem hozzá. Hallottam, hogy egy hete nagyon jól érezte magát itt...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "A barátommal megbeszéltük, hogy itt találkozunk, de nem látom sehol. Nem tudja, hová ment? Még mindig a városban van, vagy legalábbis a szigeten? A neve Longway - kínai.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l2 = "Jó hír, "+npchar.name+". Pontosan tudom, mi fogja megmenteni a helyzetét. Száz üveg kiváló bor és száz üveg rum. Egy ilyen szállítmánnyal a vásárlói ismét a pia folyóiban fognak fürdeni. Készen állsz fizetni?";
				link.l2.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l2 = "Nos, akkor, "+npchar.name+", készen állsz arra, hogy megbeszéljük az üzlet feltételeit?";
				link.l2.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l2 = "Tehát, "+npchar.name+". Részemrôl minden el van intézve, és az áru már úton van a kocsmába. Folytathatjuk a fizetést?";
				link.l2.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Lehet, hogy még mindig jól érzi magát, amíg a pokolban van. A társa meghalt, szóval egy kicsit elkésett, kapitány. Az a férfi ott, aki a legtávolabbi asztalnál ül, kifizette a temetését, bár az az érzésem, hogy ugyanaz az ember, aki ezt okozta. Lógó arca van, ahogy mondani szokták. A neve Robert Martene. Ha akarod, odasétálhatsz és megkérdezheted tôle. ";
			link.l1 = "Kösz, haver. Megyek, beszélek Robert úrral. Igyunk szegény öreg Luc lelkére, hogy a lelke békében nyugodjon...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "Mit kell megbeszélni? Megtámadott téged és a barátodat, te visszavágtál, szinte minden nap látok ilyet. Szép munka. Most már csak fel kell takarítanom a mocskot...";
			Link.l1 = "Majd te feltakarítod, biztos vagyok benne, hogy már hozzászoktál. Mit tudsz róla?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "Igazából nem sokat. Pár napja jelent meg. Tetszett neki itt, még egy házat is bérelt a város szélén. Gyakran jött, rendszeresen fizetett. És ami a legfontosabb, mindvégig jól viselkedett, soha senkire nem szólt egy rossz szót sem. Még mindig meg vagyok döbbenve, hogy megtámadta magát és a barátját\nAzt hittem, talán végleg letelepedik itt.";
			Link.l1 = "Bizonyos értelemben így is lett. Hát, ez nem sok, de azért köszönöm, barátom. Még találkozunk.";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_BasTerTavern_3");
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "Ez a név nem mond nekem semmit, és általában nem engedem be az ilyen embereket a létesítményembe, és nem is érdeklôdöm irántuk.";
			Link.l1 = "Ez így van. Rendben, viszlát késôbb.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Ó, "+GetAddress_Form(NPChar)+", ez még ennél is rosszabb. Az antiguai beszállítóm elvesztette a szeszfôzdéjét - kalózok rabolták el, minden porig égett. Most azt mondja, hogy legalább két hónapig nem számíthatunk rumra vagy borra.";
			link.l1 = "Akkor keressünk új beszállítót. Ugye nem fog két hónapig csak ülni és várni?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "Nem könnyû megbízható szállítót találni. Próbáltam kis kereskedôkkel üzletelni, de ôk megbízhatatlanok. Néha megérkezik az áru, néha nem. Egy nagy beszállítóval minden úgy megy, mint a karikacsapás - stabil szállítások és kiváló minôség.";
			link.l1 = "Nos, ha a normál beszállítók problémásak, talán keresnie kellene valakit az árnyékban? Ôk ritkán hagyják cserben, és az áru mindig van raktáron.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "Megérti, "+GetAddress_Form(NPChar)+", hogy ez a kocsma nyilvános ellenôrzés alatt áll. Nem akarok semmi gondot a hatóságokkal. Ha valaki, akinek jó híre van, hozná az árut, nemcsak megvennék egy adagot, hanem szívesen szemet hunynék afölött, hogy honnan származik\nEzek után, amikor ilyen szörnyû a helyzet, kit érdekelnek az ilyen apróságok? A lényeg, hogy elkerüljük a gyanút. De hosszú távon csak komoly és becsületes kereskedôkkel fogok üzletelni.";
			link.l1 = "Megértem. Nos, talán késôbb újra benézek. Okos megközelítéssel minden probléma megoldható.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "Kapitány, ez hihetetlen! Hogy csinálta ezt? Nem számít, tényleg. Csak mondja, mit akar cserébe egy ilyen fényûzô alkoholszállítmányért? És minden rendben lesz a papírmunkával?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "A papírmunkával? Természetesen minden tökéletesen rendben van. Ugye nem akarja ellenôrizni, ugye?";
				link.l1.go = "TPZ_Tavern2_2";
				notification("A becsületellenôrzés átment.", "None");
			}
			else
			{
				link.l1 = "Papírmunka?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				notification("A becsület szintje túl alacsony! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Kapitány, kérem, értse meg, létfontosságú számomra, hogy megkapjam ezt az alkoholszállítmányt. De a szabadságom és a hírnevem ugyanolyan értékes. A kormányzó könyörtelenül bánik a feketepiaci kereskedôkkel, még a legkisebbekkel is. Ha az emberek jót beszélnének rólad, szemet tudnék hunyni a papírmunka hiánya felett, de most... túl sok nem kívánt figyelmet vonzol...";
			link.l1 = "Úgy tûnik, itt az ideje, hogy jót cselekedj. Várjatok meg, hamarosan visszajövök.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "Ezúttal, azt hiszem, elhiszem, amit mondasz. Szóval, mennyit kérsz a tételért?";
			link.l1 = "Harminc dublont kérek minden tíz üveg borért, és öt dublont minden tíz üveg rumért. A teljes tétel - száz üveg mindkettôbôl - háromszázötven dublonba kerül.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "Várjon, kapitány! Ez rablás! Igen, a helyzetem kétségbeejtô, de nem fogom veszteséggel mûködtetni az üzletemet!";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Talán adhatok önnek kedvezményt. De ez még nem minden. Szeretnék a rendszeres beszállítója lenni. Garantálom a zökkenômentes és idôben történô szállítást. Basse-Terre-ben bérelek egy raktárat, és Ön onnan közvetlenül, késedelem nélkül megkapja a készletét. Mindig lesz elegendô alkohol raktáron, hogy elkerüljük a hiányt. A kedvezménnyel együtt az ár kétszáznegyven dublon lesz. Mit szól hozzá?";
				link.l1.go = "TPZ_Tavern2_4";
				notification("A csekk átadva", SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Rendben, hajlandó vagyok csökkenteni az árat kétszáznegyven dublonnára szállítmányonként - hosszú távú partnerségre törekszem. A jövôben minden igényét ki tudom elégíteni, és megbízható ellátást tudok biztosítani. Mit szólsz hozzá?";
				link.l1.go = "TPZ_Tavern2_7";
				notification("Túl alacsony képzettség (50)", SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "Ez még mindig több, mint amit eddig fizettem. De megtanultam a leckét - a stabilitás megéri az árát. Elfogadom a feltételeit, de tudnia kell: egy hiba, és keresek másik beszállítót. Meg kell értenem, hogy miért fizetek többet. És még valami - hogyan tervezi kezelni a hatóságokat?";
			link.l1 = "Ezt most rögtön elintézem. Amint mindent elrendeztem, visszajövök az áruval.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "Kérem, ne késlekedjen. Alig várom, hogy újra tele lássam a vásárlóim' bögréit.";
			link.l1 = "Ne aggódjon, nem fogom megvárakoztatni.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
	    case "TPZ_Tavern2_7":
			dialog.text = "Még mindig túl drága, kapitány. Ez az ár magasabb, mint amit az elôzô szállítómnak fizettem. Még ha most bele is egyezem, néhány hónap múlva vissza kell mennem hozzá, amint újraindul a termelés. Nem látom okát, hogy túlfizetjek.";
			link.l1 = "Megértem. Rendben. Az utolsó ajánlatom - kétszáz dublon. Ha ez nem elfogadható, akkor nincs értelme folytatni ezt a beszélgetést.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "Rendben, megegyeztünk. Kétszáz elfogadható. De mondd csak, hogyan tervezed kezelni a sziget hatóságait? Ahogy már mondtam, a kormányzó szigorúan ellenôrzi a szigetet a csempészet miatt. Nem fogja eltûrni, hogy az orra elôtt történjen az üzlet.";
			link.l1 = "Ha-ha, nos, ezzel vitatkoznék. De megnyugodhat - gyorsan elintézem az összes bürokratikus akadályt.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "Kérem, ne késlekedjen. Alig várom, hogy újra tele lássam a vásárlóim’ bögréit.";
			link.l1 = "Ne aggódjon, nem fogom megvárakoztatni.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Természetesen, kapitány! Szóval, mennyit kér a szállítmányáért?";
				link.l1 = "Minden tíz üveg borért harminc dublont kérek, és minden tíz üveg rumért öt dublont. Az egész szállítmány - száz palack mindegyikbôl - háromszázötven dublonnába kerül.";
				link.l1.go = "TPZ_Tavern2_3";
				notification("A becsületellenôrzés átment.", "None");
			}
			else
			{
				dialog.text = "Sajnálom, kapitány, de a hírneve még mindig hagy kívánnivalót maga után.";
				link.l1 = "A fenébe...";
				link.l1.go = "exit";
				notification("Túl alacsony a becsület! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "Természetesen, kapitány, természetesen! 240 dublont, ahogy megbeszéltük. Tessék!";
				link.l1 = "Öröm veled üzletelni! Most a kocsma ismét elárasztja a rum és a bor.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "Természetesen, kapitány, természetesen! 200 dublont, ahogy megbeszéltük. Tessék, tessék!";
				link.l1 = "Öröm veled üzletelni! Most a kocsma ismét elárasztja a rum és a bor.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "Maga a megmentôm, kapitány! Kéthetente hasonló szállítmányokat várok. Remélem, szigorúan betartja a kötelezettségeit. Még egy ilyen száraz idôszak, és a kocsmám nem fogja túlélni...";
			link.l1 = "Nem kell aggódni, "+npchar.name+". A városi képviselôm Christian Deluce. Ô gondoskodik arról, hogy a kocsmádban soha ne legyen hiány borból vagy rumból.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "Christian? Ismerem ôt. Egy felelôsségteljes ember, bár... nos, mindegy. Mivel tisztáztad a dolgokat a hatóságokkal, azt hiszem, megbízhatok benne.";
			link.l1 = "Remek. Most, ha megbocsátanak, még egy ügyet kell elintéznem ebben a városban.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "Látogasson meg minket gyakrabban!";
			link.l1 = "Úgy lesz.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
