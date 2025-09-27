// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Mit akarsz? A-ha, te vagy a regatta résztvevôje! Igazam van?";
				link.l1 = "Pontosan, uram. Be kell regisztrálnom magam a szabályok szerint.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Már próbáltál kérdezni " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Nézze, ha nincs mondanivalója a kikötô ügyeirôl, akkor ne zavarjon a kérdéseivel.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam.", "Nincs mirôl beszélnem."), "Nevermind.", "Valóban, már harmadszor...", "Sajnálom, de egyelôre nem érdekelnek a kikötô ügyei.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "Azt beszélik, hogy valaki merényletet követett el ellened, és te próbálod megtalálni a tettest?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "Az ember, aki megpróbálta az életed, elesett, Mr. "+npchar.lastname+". Már semmi sem fenyegeti önt.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Hm... Megszegted a regatta szabályait, ezért ki kell, hogy zárjalak. Sajnálom. Nem vehetsz részt a következô hajón. Már elôkészítettem egy küldeményt Kikötô-Royalba.";
			link.l1 = "Hoppá... milyen kár! De itt nem tehetek semmit, túlságosan éber voltál. Viszontlátásra!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "Regisztráljunk: kapitány "+ GetFullName(pchar) +", hajó "+pchar.Ship.Name+"... a regatta ideje órákban "+sti(pchar.questTemp.Regata.FirstTransitionTime)+". Kész, az eredményed regisztrálva, folytathatod az utadat.";
			link.l1 = "Mondd meg a rangomat.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Itt vagy, de nem látom a hajódat. Hol van?";
			link.l1 = "Sajnálom, uram. Azonnal átviszem a hajómat a kikötôbe.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Te vezetsz. Gratulálok! Csak így tovább!";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Te vagy az utolsó. Sietned kellene.";
				link.l1 = "Már úton vagyok!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Te vagy a második. A vezetô "+sName+" a hajón "+sShip+". Feltételezem, hogy még mindig le tudod ôt elôzni.";
					link.l1 = "Köszi! Köszi! Megpróbálom!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "A rangod: "+n+". A legközelebbi ellenfeled "+sName+" a "+sShip+"hajón .";
					link.l1 = "Köszönjük!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "Az ellenem elkövetett merénylet megtörtént, ez igaz. Ami a keresést illeti... ez nem egészen az. Nem egy szökevényt kell elkapni, hanem a fejét. Csak akkor tér vissza a béke hozzám.";
			Link.l1 = "Van fogalma arról, hogy ki támadta meg és miért?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "I... Nem tudom, ki ô! Nem tudom, honnan jött, vagy miért támadt rám. De egy dolog világos - a halálomat akarta. És most... most ugyanolyan dühösen vágyom a halálára! Megértettél?\nSzóval kímélj meg az értelmetlen kérdéseidtôl. A kíváncsiságod semmit sem jelent nekem - most már csak a cselekvés segíthet. Kétszáz dublon a fejéért, ez az én áram. Kezdjétek el a vadászatot, vagy ne vesztegessétek tovább az idômet.";
			Link.l1 = "Megértem, hogy a félelem és a düh elhomályosítja az elmédet, és még a hangnemedet is megbocsátom. De szedd össze magad. Nem látok egy sor önkéntest, aki megoldaná a problémáidat, úgyhogy mérsékeld a tüzet. Kétszáz dublon elfogadható, de mielôtt elvállalnám a munkát, mindent tudnom kell.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "A szavaid csak üres fecsegés, és nincsenek nyomok. Egy ismeretlen személyt keresni a dzsungelben olyan, mint tût keresni a szénakazalban. Nem fogom az idômet értelmetlen vadászatra pazarolni. Sok szerencsét! Biztosan szükséged lesz rá.";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "Argh... Bocsáss meg, "+GetAddress_Form(NPChar)+", az idegeim fáradtak... Pontosan mit akarsz tudni?";
			Link.l1 = "Észrevettél valamilyen jellemzôt, ami segíthet azonosítani ôt? Egyedül volt, vagy valaki erôsebb támogatta? Minél többet mondasz, annál hamarabb tudsz majd nyugodtan aludni.";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "Milyen ellenség?! Nekem nincsenek ellenségeim! Soha nem is voltak! Semmit sem tettem, amiért megérdemelném a halált az utca közepén, fényes nappal\nAz a gazember... ô csak egy megkeseredett ôrült, az a fajta, akit mindenhol megtalálsz ezekben a gyarmati városokban\nAmint hogy hol keressük... Szerintem a dzsungelben rejtôzik. Könnyû eltûnni azokban az elátkozott erdôkben, de biztos vagyok benne, hogy a barlangok vagy öblök felé veszi az irányt - ott könnyebb elrejtôzni\nAmi a külsejét illeti, az arcát kendô takarta, kalap volt a fején, és több fegyvert hordott magánál, mint Ôfelsége saját ôrsége. Nem volt idô arra, hogy bármi mást észrevegyünk.";
			Link.l1 = "Nos, ez nem sok, de elég ahhoz, hogy elkezdjük a keresést. Azonnal indulok. Tartsd közel azt az aranyat - hamarosan visszajövök.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddQuestRecord("GS", "2");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
			
			PChar.quest.GS_Peshera.win_condition.l1 = "location";
			PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
			PChar.quest.GS_Peshera.function = "GS_Peshera";
			locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
			
			PChar.quest.GS_Peshera_pusto.win_condition.l1 = "location";
			PChar.quest.GS_Peshera_pusto.win_condition.l1.location = "Beliz_Cave_2";
			PChar.quest.GS_Peshera_pusto.function = "GS_Peshera_pusto";
		break;
		
		case "GS_Portman_6":
			dialog.text = "Csodálatos, "+GetFullName(pchar)+"! Teljesen csodálatos! Páratlanul bizonyítottad a rátermettségedet. Itt van a jutalmad - kétszáz dublon. Kérlek, vedd el!";
			Link.l1 = "Köszönöm neked! De mondd csak, van valami okod gyanítani, hogy a gyilkost az egyik korábbi ügyfeled bérelte fel?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "Korábbi ügyfelek?... Micsoda ostobaság!... Én egy becsületes ember vagyok, és az ügyleteim mindig is tisztességesek voltak! De ha már segített nekem, megosztok önnel valamit. Nem is olyan régen kalózok jöttek hozzám\nPénzt ajánlottak a kereskedelmi hajókra vonatkozó tippekért. Visszautasítottam, mire ôk fenyegetôztek és átkozódtak, mielôtt elviharzottak. Azt hiszem, a merénylô az ô mûvük volt. Nem veszik 'nem' kedvesen.";
			Link.l1 = "Ebben az esetben vigyázzon magára. Ki tudja, hogy ezek a 'kalózok' még hány bérkést küldhetnek? Ezzel búcsút kell vennem - az üzlet hív.";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "Várjon, kapitány. Szeretném még egyszer megköszönni. Az aranyon túl, kiérdemelte a kegyeimet. Amíg én vagyok itt a kikötôfônök, addig bármelyik hajótokat itt hagyhatjátok kikötve, bármilyen hosszú idôre, ötven százalékos kedvezménnyel. Hogy hangzik?";
			Link.l1 = "Nagyon nagylelkû ajánlat! Még egyszer köszönöm!";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "Én pedig még egyszer köszönöm az erôfeszítéseit. Biztos vagyok benne, hogy amíg arra koncentrálnak, ami számít, addig az ügyeik ugyanúgy fognak virágozni, mint ma. Viszlát, kapitány.";
			Link.l1 = "Viszontlátásra.";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddQuestRecord("GS", "4");
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_NaemnikMertv");
			pchar.questTemp.GS_BelizSkidka = true;
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
