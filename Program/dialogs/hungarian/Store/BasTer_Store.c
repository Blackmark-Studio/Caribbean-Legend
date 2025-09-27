// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Gyerünk, mit akarsz?",
                          "Épp errôl beszéltünk. Biztos elfelejtetted...", "Ma már harmadszor beszélsz valami kérdésrôl...",
                          "Figyelj, ez egy bolt. Az emberek itt vásárolnak. Ne zavarjon!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Hm, nem fogom...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Köszönöm, kapitány, hogy teljesítette a kérésemet. Most, hogy a "+pchar.questTemp.Shadowtrader.Guardername+" itt van, legalább egy kicsit nyugodtabb lehetek.";
					link.l1 = "Hmm... Nem akarok tolakodónak tûnni, de úgy tûnik, hogy gondjaid vannak. Elmondanád, hogy mi a baj - talán tudnék segíteni neked?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Szóval? Átadta a levelemet?";
					link.l1 = "Igen, átadtam. A parancsnok szóban azt válaszolta, hogy a leveledben szereplô bizonyítékok nem elegendôek ahhoz, hogy a városôrség bármilyen intézkedést tegyen."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "Már hallottam a híreket - ma este az ôrök felfedeztek egy illegális csempészkereskedelmet, és mindannyiukat letartóztatták. Egy ritka söpredék parancsnoksága alatt állt, most már minden rendben, egy ideig nem fog tudni rosszat tenni senki mással\nCommandant mesélt nekem a te szerepedrôl az egészben, hálás vagyok neked! Megtartotta a szavát! Tessék, itt a pénz - 15 000 pezó. Megmentettél engem. Most már semmi sem fenyegeti az üzletemet!";
					link.l1 = "Szívesen. Könnyû volt."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Szóval, van valami jó hír, " + pchar.name + "?";
					link.l1 = "Megtaláltam a riválisodat. Nem fog többé a nyakadon lenni - sikerült meggyôznöm... hogy hagyja el ezt a szigetet. A 'boltja' egy házban volt a városkapuk közelében. Rajtad múlik, hogy mit kezdesz a hátrahagyott rakománnyal. Átadhatod a hatóságoknak, vagy megpróbálhatod magadnak begyûjteni."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Már hallottam a híreket - ma este az ôrök felfedezték az egyik ház alatt a csempészek kijáratát. Két gazembert holtan találtak. Szép munka, " + pchar.name + ", csodállak! Tessék, itt a jutalom - 15 000 pezó. Most mentettél meg engem! Most már tényleg cserélni fogok!\nKíváncsiságom kielégítése - a vezetôjük... szintén a két halott között van?";
					link.l1 = "Nem. De soha többé nem fog felbukkanni a városodban. Azt hiszem, több tucat mérföldre van ettôl a szigettôl, amíg beszélgetünk."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Már hallottam a híreket - ma éjjel az ôrök egy titkos csempészboltot találtak az egyik házban. Három gazembert találtak holtan. Kiváló munka, " + pchar.name + ", csodállak! Tessék, itt a jutalom - 15 000 pezó. Most mentettél meg! Most már tényleg cserélek!\nKíváncsiságomnak eleget téve - a vezetôjük... szintén a két halott között van?";
					link.l1 = "Igen. Örökre megszabadultál a riválisodtól. Soha többé nem fog zavarni téged."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Megtenné, hogy elmegy a kocsmába, megkeres egy "+pchar.questTemp.Shadowtrader.Guardername+" nevû embert, és megmondja neki, hogy jöjjön ide, amilyen gyorsan csak lehet. Nem tudok kimenni a boltból, ez a tökfej pedig a kocsmában ül, rummal töltekezik, és biztosan eszébe sem jut, hogy idejöjjön, hiába van szolgálatban.";
			link.l1 = "Mindig szívesen segítek, pajtás - annál is inkább, mert amúgy is a kocsmába készültem.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Most gúnyolódsz velem? Úgy nézek ki, mint a kifutófiúja? A kocsma csak pár lépésre van innen - odamehetsz magad is.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Köszönöm! Kérem, mondja meg neki, hogy azonnal jöjjön ide. Ó, miért kell ilyen kellemetlenkedônek lennie...";
			link.l1 = "Ne aggódjon. Majd én elküldöm magához.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "Ó, kapitány, nagyon szeretném, ha segítene. Megtenné, hogy minél hamarabb eljuttatja ezt a levelet a parancsnoknak? 300 érmét fizetnék önnek ezért a triviális üzletért - mint már mondtam, nem hagyhatom el a boltomat.";
			link.l1 = "Nem probléma. Add ide azt a levelet.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "Nem, jóember, nincs több idôm erre a baromságra.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Tessék, tessék. Kérem, adja át neki még ma, és adja át nekem a válaszát.";
			link.l1 = "Ne aggódjon, megcsinálom.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Nos, úgy tûnik, hogy valaki mást kell megkérnem. Elnézést a zavarásért, kapitány.";
			link.l1 = "Semmi gond. Viszontlátásra!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "Ezt mondta? Akkor milyen bizonyítékra van szüksége tôlem?! A holttestemre? Hát, hamarosan lesz egy, ha ez így megy tovább!...";
			link.l1 = "Hé, hé, " + npchar.name + ", nyugodj meg, vagy agyvérzést kapsz. Tessék, igyál egy kis vizet... Most mondd meg, mi a baj - talán tudnék segíteni neked?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Ó, kapitány! Kérem, vegye el a 300 pezót - majdnem elfelejtettem... Természetesen elmondom, de nem vagyok benne biztos, hogy ön hogyan tudna segíteni nekem. Az üzletem majdnem tönkrement - mindez azok miatt az átkozott csempészek és az ismeretlen fattyú miatt, aki vezeti ôket.";
			link.l1 = "Csempészek?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "Ez az! Ezek a gazemberek nyilván úgy döntöttek, hogy kirúgnak a városból! Addig minden a szokásos módon zajlott - tiltott tárgyakat adtak el újra, és amikor a járôrök elkapták ôket, elbújtak vagy lefizették ôket. De nemrégiben valahol egy mellékutcai boltot nyitottak, és hihetetlenül alacsony áron kezdték el árulni a legkeresettebb árukat!\nNem engedhetem meg magamnak ezt a luxust - sôt, adót kell fizetnem -, fokozatosan elszegényedtem, és a tengerészek szinte nem is akarják az árumat - minden árut ezektôl a gazemberektôl vesznek.";
			link.l1 = "De a hatóságokhoz kellett volna fordulni! Elvégre ez a dolguk - megállítani az ilyen törvénytelenségeket.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "A legutóbbi fellebbezés eredményét maga is látta. A kormányzó túl elfoglalt, a parancsnok pedig nem hitte el, hogy a csempészek hátsó utcai üzleteket szerveztek, vagy úgy tesz, mintha nem hinné el - és gondolom, ez a helyzet\nOm persze, miért is tennének ilyet? Én meg azt mondom: Biztos vagyok benne, hogy valami gazember gazember, aki tönkre akar tenni és ki akar ûzni a városból, találta ki az egészet, aztán majd szép csendben rendbe teszi az üzletemet, hogy tisztára mossa a mocskos kis kezüket.";
			link.l1 = "Hm... a véleményed nem alaptalan. Ez a kereskedôk természetébôl fakad - macskamancsot csinálni valakibôl... Ó, bocsánat, természetesen nem rád gondoltam. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Ó, semmi... Nemrég pedig odajött hozzám valami rongyrázó, és szemtelenül azt mondta, hogy ha továbbra is hangoskodom, felgyújtják a boltomat\nSzóval felfogadtam egy testôrt. "+pchar.questTemp.Shadowtrader.Guardername+" nem olcsó mulatság, de profi, és a védelme alatt kicsit nyugodtabb vagyok.";
			link.l1 = "Értem... Kellemetlen történet, valóban. Úgy tûnik, igazad volt - semmit sem tehetek érted. De azért biztos vagyok benne, hogy a dolgok maguktól megoldódnak - az ilyen kétes intézmények általában nem tartanak sokáig. Nos, sok szerencsét!";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "Értem. Nos, talán még mindig tudnék segíteni...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "Egyébként is felajánlja a segítségét? De mit fogsz csinálni?";
			link.l1 = "Megpróbálom megkeresni azt a 'kollégádat' és... meggyôzni, hogy szálljon le rólad. Tudod, van némi képességem az emberek meggyôzésében.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Komolyan mondod? Áldja meg az Úr az igaz ügyedet! Ha megszabadítasz ettôl a mocsoktól, az adósod leszek.";
			link.l1 = "Rendben, megegyeztünk. Akkor elkezdem a keresést.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "Igaz ez? Most már félelem nélkül üzletelhetek? Ó, nagyon szépen köszönöm! Itt a jutalmad - 15000 pezó. Ami a házukban lévô árukat illeti, azt hiszem, a legjobb, ha átadják a parancsnoknak. Még egyszer köszönöm!";
			link.l1 = "Szívesen. Nem volt túl nehéz. Mondtam, hogy jó vagyok a meggyôzésben.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Látogasson meg máskor is, kapitány úr - mindig örülök, ha látom.";
			link.l1 = "Hát persze! És most engedjék meg, hogy távozzak - dolgom van! Viszontlátásra és sok sikert a kereskedelemben, " + npchar.name + "!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}
