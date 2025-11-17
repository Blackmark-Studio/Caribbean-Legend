int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "Örülök, hogy látlak, fiam.  Azért jöttél, hogy eltöröld az adósságodat?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Igen, apám. Igen, itt vagyok.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "Elnézést a késésért, de nem ezért vagyok itt. De hamarosan itt leszek, ne aggódj.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Szükséged van valamire, fiam?";
				link.l1 = "Igen, atyám. Szeretném látni a bátyámat, Michel de Monper-t. Azt mondta...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Szükséged van valamire, fiam?";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Igen, pater. Szükségem van a segítségedre. A nevem "+GetFullName(pchar)+". Michel de Monper tanácsolta, hogy beszéljek veled.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Igen, atyám. Szükségem van a segítségedre. A nevem "+GetFullName(pchar)+". A bátyám, Michel de Monper tanácsolta, hogy beszéljek veled.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Igen, atyám. Szükségem van egy hajóra, hogy segítsek Michelnek, pedig csak nemrég érkeztem a Karib-tengerre, és a pénztárcám üres. A bátyám azt mondta, hogy tudnál kölcsönadni egy kis pénzt...";
				link.l1.go = "FastStart_2";
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "Greetings, Father. We need your help – in a rather unusual matter.";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "Father, I have gathered the required sum. Eight hundred in gold.";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "Greetings, my son. I suppose you have come to hear the results of your... ahem, your affair?";
				link.l1 = "As perceptive as ever, Father. Do not keep me waiting – tell me, what has your man discovered?";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Дикая Роза
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Igen, atyám. Szükségem van a segítségedre.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Igen, atyám. Én vagyok az.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "Nem, semmi, apa.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "Mi szél hozott hozzám, fiam?";
			link.l1 = "Jó napot, atyám. Azt tanácsolták, hogy beszéljek veled. A nevem Charles de Maure. Michel de Monper-t keresem. Amennyire tudom, valahol Martinique-on kellene lennie. Én... a testvére vagyok.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Michel de Monper testvére? De Maure? Milyen különös...";
			link.l1 = "Megértem a kételyeit, atyám. Egyszerûen csak más a vezetéknevünk. Az apám Henri de Monper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "Most már értem. Henri de Monper-t személyesen ismertem. Forduljon a fény felé, fiatalember. Jól van! Pont úgy nézel ki, mint ô. Ugyanaz a kinézet, ugyanazok a nemes vonások! Örülök, hogy Henri de Monper egyik fiát látom a plébániánkon.\nA kérdéseddel kapcsolatban pedig elmondom, hogy Michel a Máltai Lovagrend magas rangú tisztje, de... bajban van. Szerencsére a rend egyik lovagja éppen most látogat meg engem. Azt hiszem, ô talán hajlandó lenne elkísérni önt a szerencsétlenül járt testvéréhez, az Úr kegyelmezzen a sorsának...";
			link.l1 = "Ki ez az ember, szent atyám?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "Fiam, gyere vissza holnap reggel. Jelenleg nincs több mondanivalóm számodra.";
			link.l1 = "Rendben van.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "Szia, fiam. Ahogy ígértem, a tegnap említett személy már itt vár rád. Készen áll, hogy elvigyen a bátyádhoz, aki, mint hallottam, szerencsétlen. Az Úr legyen irgalmas a lelkéhez...";
			link.l1 = "Ki ez az ember, szent atyám?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "Igen, Charles, tisztában vagyok vele. De csalódást kell okoznom neked. Michel nincs itt.";
			link.l1 = "Hogy érted, hogy nincs itt? Azt mondta, hogy a templomban fog várni rám! Atyám, mi történt? Hol van a bátyám?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "Fiam, a bátyád itt volt, és tegnap késô este elhagyta szerény tabernákulumomat. Hogy hová ment, nem tudom. De ezt a levelet itt hagyta neked.";
			link.l1 = "Nem tudom elhinni... azok után, amit érte tettem! Add ide azt a levelet!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Ne dühöngj ennyire, Charles. Itt a levél. Olvasd el, és aztán... aztán szeretnék beszélni veled. De elôbb olvasd el a bátyád üzenetét.";
			link.l1 = "Lángolok a türelmetlenségtôl!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "Látom, elolvastad a levelet. Szeretnék mondani valamit, Charles...";
				link.l1 = "De... hogyan lehetséges ez? Miféle ostobaság ez? Tudom, hogy a bátyám különös, de nem ôrült!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "Fiam, olvasd el a levelet. Majd késôbb beszélünk.";
				link.l1 = "Igen, apám...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "A bátyád tettei engem is megleptek, Charles. Még mindig érzem a zavarodottság pillanatait. A Rend és a Szentháromság hûséges szolgája, és úgy viselkedik, mint egy dezertôr.";
			link.l1 = "Van valami ötleted, hogy mi lehet az oka egy ilyen furcsa viselkedésnek?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Sajnos, nincs. De feltételezem, hogy saját indítékai vannak, mély indítékok. Az egész múltjának eltörlése rendkívül fontos okot sejtet. El sem tudom képzelni, mi lehet az. De úgy érzem, hogy valami rendkívül rossz, sôt szörnyû dologról van szó.";
			link.l1 = "Mi lehet az, atyám?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "Fiam, egy pap nem a szemével lát, hanem a szívével. Nem tudom szavakkal elmagyarázni neked, de... a bátyád valami tisztátalan, mocskos dologra indult. Soha nem gondoltam volna, hogy a szám ezt kimondja. Azonban...";
			link.l1 = "Nos, nem kétlem, hogy a bátyám valami mocskos dolgot tervezett. Még az is mögé tudok állni, hogy pontosan mit tervez. Ez 'valami' valami sárga és szépen csilingelô hangot ad.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "Nem hiszem, hogy az arany utáni vágy hajtja a bátyádat. Azt mondanám, hogy valami nagyobbra van szüksége.";
			link.l1 = "Sokat tanultam Micheltôl és felfogtam a filozófiáját, így azt hiszem, képes vagyok feltételezni, hogy mi fontos neki és mi nem. De észben fogom tartani értékes szavait, atyám.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "Isten áldjon meg, fiam. Menj, menj most. Az Úr vigyázzon rád!";
			link.l1 = "Köszönöm, atyám. Viszontlátásra!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Michel de Monper testvére? De Maure? Milyen különös...";
			link.l1 = "Megértem a kételyeit, atyám. Egyszerûen csak más a vezetéknevünk. Az apám Henri de Monper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "Most már értem. Személyesen ismertem Henri de Monper-t. Forduljon a fény felé, fiatalember... Jól van! Úgy nézel ki, mint ô. Ugyanúgy néz ki, ugyanolyan nemes oldalnézetbôl! Örülök, hogy Henri de Monper egyik fiát látom a plébániánkon.\nHallottam már, hogy Michelhez látogatóba érkezett valami férfi, aki Európából érkezett, de azt nem is tudtam elképzelni, hogy a saját testvére volt az. Remélem, hogy tudnak majd segíteni Michelnek, nehéz idôszakot él át. Egyébként hogyan tudok segíteni?";
			link.l1 = "Michel azt mondta nekem, hogy ön tudna segíteni, ha valaha is bajba kerülnék a hatóságokkal.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "Ezt mondta neked Michel? Értem. Nos, ilyen ügyekben tudok segíteni. Van némi befolyásom a Szent Római Egyházban és a holland gyarmatokon. Ezért talán tudnék közbenjárni ön és a spanyol, valamint a holland hatóságok között. Bizonyára nem sokat tudok majd tenni, ha az ön helytelen viselkedése túlságosan elhatalmasodott - ebben az esetben csak egy kis enyhítés érhetô el.\nA teljes megbékéléshez több közbenjárásra lesz szükség. Emellett minden esetben aranydublonnal kell majd ellátnod engem jótékonysági célokra és útiköltségekre. Továbbá, egyszerre csak egy nemzetnél tudok segíteni nektek. Ha ezeket a feltételeket elfogadhatónak találod, ne habozz hozzám fordulni, és meglátjuk, mit tehetünk.";
			link.l1 = "Köszönöm! Ezt észben fogom tartani.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "Mit tehetek érted, fiam? Beszélj, hallgatlak.";
			link.l1 = "Michel azt mondta, hogy ön tudna segíteni, ha valaha is bajba kerülnék a hatóságokkal.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "Miben segíthetek, fiam?";
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Gondjaim vannak a spanyol hatóságokkal.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Nekem a holland hatóságokkal van bajom.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Sajnálom, azt hiszem, ezúttal magam intézem a dolgokat.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "Szóval, a nemes szenátorok alig várják, hogy Havanna tömlöcébe zárjanak...";
			link.l1 = "Pontosan így van, atyám...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "Szóval, az okos kereskedôk szeretnének téged Willemstad tömlöcébe zárni...";
			link.l1 = "Pontosan így van, atyám...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Igen, ezek a pletykák a mi templomunkba is eljutottak. Segíthetek neked a dilemmádban. Ez egy olyan dolog, amit meg lehet oldani. " + sTemp + " kérek, hogy elsimítsam a helyzetét.";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "Remek! Itt van az arany.";
					link.l1.go = "agree";
				}
				link.l2 = "Akkor itt az ideje, hogy megtaláljam a dublont.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Igen, a pletykák a 'feats' gyülekezetünkbe is eljutottak. Beáztattad a hírnevedet, fiam. Óvatosabbnak kellene lenned. De én segíthetek neked. " + sTemp + " kérek, hogy elsimítsam a helyzetedet.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Remek! Itt van az arany.";
						link.l1.go = "agree";
					}
					link.l2 = "Akkor itt az ideje, hogy megtaláljam a dublont.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Igen, fiam. Ugyanolyan kétségbeesett vagy, mint a bátyád... Ez valószínûleg családi vonás. Nem tudom teljesen helyrehozni a helyzetet, de mégis, azt hiszem, el tudom tompítani a nyomorúságos helyzetedet. És késôbb még több felajánlást is tehetünk, ha szeretnéd. " + sTemp + " van szükségem, és azonnal elkezdem megoldani a dilemmádat.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Remek! Itt van az arany.";
						link.l1.go = "agree";
					}
					link.l2 = "Akkor itt az ideje, hogy megtaláljam a dublont.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Most legalább két hetet kell várnia. Úgy gondolom, hogy ennyi idô alatt találkozhatok és beszélhetek a megfelelô emberekkel.";
			link.l1 = "Köszönöm, atyám! Várni fogok...";
			link.l1.go = "agree_1";
		break;
		
        case "agree_1":
            DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
            SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
            pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
            npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? És te Michel de Monper testvére vagy? Furcsa...";
			link.l1 = "Megértem a kételyeit, atyám. Az apám Henri de Monper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "Aha, értem. Személyesen ismertem Henri de Monper-t. Forduljon a fény felé, fiatalember. Jól van! Ugyanazok a szemek, ugyanazok a nemes vonások! Örülök, hogy Henri de Monper fiát látom a templomomban. Remélem, tudsz majd segíteni a bátyádnak. Sok balszerencséje volt mostanában.";
			link.l1 = "Igen, atyám. Szükségem van egy hajóra, hogy segítsek Michelnek, pedig csak nemrég érkeztem a Karib-tengerre, és a pénztárcám üres. A bátyám azt mondta, hogy tudnál kölcsönadni egy kis pénzt...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "Michel mondta?";
			link.l1 = "Atyám, lehet, hogy nem hangzik túl megbízhatónak, mégis igaz. Minél hamarabb szerzek egy hajót, annál hamarabb tudom kihozni a bátyámat a börtönbôl.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "Értem, fiam. Hallom, hogy igazat beszélsz. Nos, Michel és az apád érdekében segítek neked. Van némi megtakarításom, vedd el. Gondolom, 50 000 pezó és 100 dublon elég lesz.";
			link.l1 = "Köszönöm, atyám. Mik a feltételek?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Ne erôltessük meg magunkat. Fél év a visszafizetésre elég lesz.";
			link.l1 = "Nagyon jó, szent atyám. Még egyszer köszönöm!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Menj áldásommal, fiam.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Nagyszerû, fiam. Remélem, a pénz jót tett neked.";
			link.l1 = "Valóban! Köszönöm!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, nem hiszek a szememnek! Mi szél hozott ide?!";
			link.l1 = "Áldjon meg, Szentatya, mert jó hírekkel jövök - férjhez megyek, és szeretném, ha Ön lenne az esküvôm papja.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "Fiam, ez csodálatos! Tehát megkaptad azt a levelet apádtól, és úgy döntöttél, mint általában, hogy a saját értelmed szerint cselekszel? Ôszintén örülök neked! De attól tartok, nem tudok segíteni, hacsak nem döntesz úgy, hogy itt, ebben a templomban házasodsz.";
			link.l1 = "Úgy tudom, hogy a küldetésed zsákutcába jutott, Szentatya? Segíthetek valamiben? Mivel a házasságkötésre egy spanyol kápolnában kerül sor, természetesen szívesen vállalkoznék erre a kalandra, de elhatároztam, hogy az ünnepséget Martinique-on tartom meg. Mérsékelten pompásan, és tekintélyes tanúk és tiszteletreméltó vendégek jelenlétében.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "Sajnálom, fiam, de minden tekintélyed semmit sem ér a katolikus egyház legmagasabb hierarcháinak makacsságával szemben, különösen a spanyol gyarmatokon. Nem értettünk egyet abban a kérdésben, hogy a katolikus missziók befolyását megosszuk országaink között, és most itt vagyok, mint megtisztelt vendég és mint megtisztelt túsz. A spanyolok jobb ajánlatot várnak tôlünk. Üzenetet küldtem Európába, remélhetôleg két hónapon' idôn belül megérkezik a válasz, és folytathatjuk a tárgyalásokat. Ha két hónap múlva még nem is, de a következô hat hónapban biztosan meglesz.\nÉs igen, bár a pápa és Mazarin az elmúlt hetekben kompromisszumra jutott, még korai lenne igazi szívmelengetô kapcsolatról beszélni. Ôszintén szólva nem vagyok benne biztos, hogy valaha is meg fogunk állapodni. Nekem úgy tûnik, hogy Palotti egyszerûen csak érvként tart engem a saját politikai hatalmi játszmáiban. Azt azonban meg kell mondanom, hogy az inkvizítornak kiváló kávéja van!";
			link.l1 = "Nekem nincs sem hat hónapom, sem két hónapom! Teljesítenem kell apám kívánságát, különben a beleegyezésem nélkül kényszerít a házasságra. Az egészsége pedig már nem olyan jó, mint régen, mégis szeretnék idôt kapni arra, hogy bemutassam neki választottamat és Monper leendô úrnôjét.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "Attól tartok, akkor más papot kell keresned az esküvôdre, fiam. Sajnos, én még sokáig itt maradok.";
			link.l1 = "Mit szólnál, ha elválnék az inkvizítor kávéjától?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "Szívesen elfogadnám a segítségét. Gyanítom, hogy nem véletlenül választottak ki erre a küldetésre. A legrosszabb esetben egyszerûen elfelejtik Benoit atyát. És bár az Úr megparancsolta nekem, hogy tûrjek, a végkövetkeztetésem minden... áldása ellenére is terheli a szívemet. De, ismétlem - Nem valószínû, hogy Palotti atya meghallgatja a kérését.";
			link.l1 = "Akkor megspórolok magamnak egy kis idôt, és nem próbálom meggyôzni ôt. Egyszerûen csak elhagyjuk a templomot, amint az istentisztelet véget ér, és átmegyünk a hajómra. Ne habozzon, Szentatya - látták a találkozásunkat, és felismernek majd, és sokkal nehezebb lesz segíteni önnek, ha ki kell juttatnom önt a kormányzói kúriából.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "Ez kockázatos, fiam, nagyon kockázatos. Egy csapat ôr vár odakint, hogy elkísérjenek a kúriába, és a város tele van katonákkal.";
			link.l1 = "A meglepetés erejével fogunk menni, Benoit atya. Csak bíznod kell bennem, és minden rendben lesz. Van némi... tapasztalatom ezekben a dolgokban.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "Ahogy óhajtja. De kérem, tegye felesleges vérontás nélkül! Nekem is volt már néhány ilyen tapasztalatom... Vezess minket, fiam. Mögötted leszek. De nem fogok fegyvert ragadni, úgyhogy ne is kérdezd.";
			link.l1 = "Nem is gondoltam rá, apám. Meg tudom oldani. Kövessetek, de legyetek óvatosak, lehet, hogy ránk lônek.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "Fiam, nem volt idôm megköszönni a szabadulásomat. Úgy látszik, a spanyol püspök és Palotti inquisitior meg akarta zavarni a bíborosunk és a Szentszék között alig kialakult kapcsolatokat, ezért te teljesen hazánk érdekeinek megfelelôen cselekedtél. Még egyszer. De senki sem fogja önnek 'köszönni', , csak én.";
			link.l1 = "Közös dolog, Szentatya. Örülök, hogy sikerült segítenem. De kérdeznem kell valamit, emlékszik?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Hát persze! Térjünk tehát a kellemes dolgokra - Charles, hogyan haladnak a legfontosabb napod elôkészületei?";
			link.l1 = "Lassan formálódik. Ismerek olyan hadjáratokat, amelyek könnyebben és gyorsabban készültek, de megéri!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Persze, fiam! És ebbôl az alkalomból szeretnék valamit tisztázni - hogyan képzeled el az esküvôi szertartásodat?";
			link.l1 = "Úgy érted, mennyire nagyképûnek?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Hát persze! Mert nekem kell elôkészítenem a templomot, és lehet, hogy meg akarsz majd hívni néhány fontos embert.";
			link.l1 = "Semmi különöset, Szentatya. Azok, akiket én a barátainknak tartok, máshol várnak majd ránk. Itt csak néhány hivatalnok, az embereim és néhány egyszerû bámészkodó lesz jelen.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Nos, akkor azt hiszem, megleszünk egy kis adománnyal.";
			link.l1 = "Ez nem hangzik túl ijesztôen. És mennyi egy ilyen adomány aranyban?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "A kórusra, az ünnepélyes szertartásra és egyéb kiadásokra - százötven, nem több. Plusz az ifjú pár szokásos adománya, összesen - kétszáz dublon.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Tessék, Szentatya.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "A hadjáratokról... El kell sétálnom a bankba, és vissza kell térnem.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "Mi lesz az adományoddal, fiam?";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Tessék, Szentatya.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Igen, igen, hamarosan hozom...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "Egy kérdés még megválaszolásra vár - ki fogja átadni a menyasszonyt és tanúskodni a házasságról az ô részérôl?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson , Blueweldtôl. Angol, de köztiszteletben álló ember, és úgy ragaszkodik Helenhez, mintha a saját lánya lenne, és a nevelôanyja Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Noel Forget báró, biztos vagyok benne, hogy megtisztel.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Chevalier Philippe de Poincy, biztos vagyok benne, hogy megtisztel.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Nos, és ki fog tanúskodni a vôlegény mellett? Ne feledje, nemes származású és jó hírû embernek kell lennie.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Noel Forget báró, biztos vagyok benne, hogy megtisztel.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Chevalier Philippe de Poincy, biztos vagyok benne, hogy megtisztel.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey - egy tekintélyes kereskedô Guadeloupe-ról. Csak a kedvenc italát kell feltöltenem.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey - egy tekintélyes kereskedô Guadeloupe-ról. Csak a kedvenc italát kell feltöltenem.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Remek, kiküldöm a meghívókat, de a vendégeknek idôre lesz szükségük, hogy ideérjenek. Azt hiszem, egy hónap múlva minden készen lesz, és a jelzett személyek is megérkeznek a városba.";
			link.l1 = "Jól van! Akkor lesz idôm elintézni néhány dolgot. Hamarosan találkozunk, Szentatya, és sok szerencsét kívánok!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Remek, kiküldöm a meghívókat, de a vendégeknek idôre lesz szükségük, hogy ideérjenek. Azt hiszem, egy hónap múlva minden készen lesz, és a jelzett személyek is megérkeznek a városba.";
			link.l1 = "Jól van! Akkor lesz idôm elintézni néhány dolgot. Hamarosan találkozunk, Szentatya, és sok szerencsét kívánok!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Remek, kiküldöm a meghívókat, de a vendégeknek idôre lesz szükségük, hogy ideérjenek. Azt hiszem, egy hónap múlva minden készen lesz, és a jelzett személyek is megérkeznek a városba.";
			link.l1 = "Jól van! Akkor lesz idôm elintézni néhány dolgot. Hamarosan találkozunk, Szentatya, és sok szerencsét kívánok!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "Eljött tehát a nap, fiam! Minden készen áll - néhány órán belül elkezdhetjük. Sápadtnak tûnsz!";
			link.l1 = "Egy kicsit ideges vagyok, Szentatya.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "Ez gyakori. Ez a legfontosabb nap az életedben, és ôszintén örülök neked, mint mindenki, aki eljött. Remélem, legalább az alapimákra emlékeztek - ugye nem nagyon rontottátok el a templomot a figyelmetekkel? Ettôl függetlenül mindenképpen segítek nektek.\nÉs még valami - ha jól értem, a menyasszony nem változtat az elvein, és nem fogjuk ôt ruhában látni? Nos, a felsôbb körökben újabb meglepetés vár rád - tele vagy velük. Mindenesetre menj fiam, hozd magad megfelelô formába, és kezdjük.";
			link.l1 = "Igen, Szentatya. Gyerünk, csináljuk.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Pater noster, qui es in caelis, sanctificetur nomen tuum, ad...";
			link.l1 = "...adveniat regnum tuum...";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...requiem aeternam dona eis";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...fiat voluntas tua, sicut in caelo et in terra. Panem nostrum quotidianum da nobis hodie, et dimitte nobis debita nostra si...";
			link.l1 = "...sicut et nos dimittimus debitoribus nostris";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...sicut erat in principio, et nunc et semper, et in saecula saeculorum. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "E-e... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Ámen.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Drága szeretteim, azért gyûltünk itt össze Isten színe elôtt és e gyülekezet színe elôtt, hogy ezt a férfit és nôt szent házasságban egyesítsük. Szeretett "+sld.name+" és Charles, ti hallgattátok Isten szavát, aki emlékeztetett benneteket az emberi szeretet és a házasság értelmére. Most a szent egyház nevében szeretném kihívni szándékotokat.\n"+sld.name+" és Charles, van-e önkéntes és ôszinte vágyatok arra, hogy a házasság kötelékével összekapcsolódjatok egymással a mi Urunk színe elôtt?";
			link.l1 = "Igen.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Szándékotok-e hûségesek lenni egymáshoz egészségben és betegségben, boldogságban és boldogtalanságban, életetek végéig?";
			link.l1 = "Igen.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Van-e szándékotok szeretni és elfogadni a gyermekeket, akiket a mi Urunk küld nektek, és keresztény hitre nevelni ôket?";
			link.l1 = "Igen.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Akkor forduljatok egymás felé, és tegyetek fogadalmat.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Ha bárki, aki itt jelen van, tud bármi okot, ami miatt ez a pár ne kötôdjön össze szent házasságban, akkor szóljon most, vagy tartsa vissza örökre a lélegzetét.\nEz esetben az Úr színe elôtt és az itt összegyûlt emberek elôtt férjnek és feleségnek nyilvánítalak benneteket! In nomine Patris, et Filii, et Spiritus Sancti. Ámen.";
			link.l1 = "Ámen.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Suttogás) Károly, fiam, csak mozgasd az ajkad, könyörgöm - ne próbálj hangot adni...";
			else sTemp = "";
			dialog.text = "Újdonsült házasok, térdeljetek le és imádkozzatok együtt. Oratio fidelium. "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Eltelt egy kis idô...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Gratulálok, fiam. Apád büszke lehet rád, és én is büszke vagyok rád. Legyetek boldogok, és vigyázzatok egymásra nehéz idôszakunkban.";
			link.l1 = "Köszönöm, Szentatya. Csodálatos szertartás volt, és örülök, hogy Ön tartotta.";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "So you have come to me for counsel, my children? Well then, I am all ears.";
			link.l1 = "Rather for assistance, Father. Assistance from a man who has connections and knows all manner of people...";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "Forgive me for interrupting you, my son, but I must remind you that I am but a humble abbot, not some secret agent.";
			link.l1 = "Yet a humble abbot might know a secret agent, might he not? Or at least suggest how one might reach him?";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "The matter that brought us here truly concerns certain long-forgotten secrets... We are only trying to drag them back into the light.";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Now, young man, this I do not like. Get to the point, and then we shall see how – or if – I may help you.";
			link.l1 = "Yes, Father. I shall try to be brief...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+", do not speak in riddles – it is, I confess, wearisome.";
			link.l1 = "Yes, Father. I shall try to be brief...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "Go on, my son.";
			link.l1 = "My companion, Mary Casper, is seeking her father – or at least some scrap of information about him. We have discovered that he was an officer in the English Navy and served aboard the brig 'Wrangler', which wrecked at Cape Catoche in 1638.";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "And you hope that he yet lives? After so many years?";
			link.l1 = "Even if he did not survive the wreck, Mary wishes to know where her father came from, what manner of man he was, the life he led... Official papers are sparse in detail – yet even in them one may find something of value, do you not agree, Father?";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "You are right in your reasoning, my son. Yours is a good and godly endeavor. But I still fail to grasp what exactly you expect of me.";
			link.l1 = "You have long dwelt in the Archipelago, Father. Perhaps you know someone with access to colonial archives concerning officers of the English Navy?";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "We need a man with access to the colonial archives where records of English naval officers are kept. Surely you know of such a one, Father.";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "Do you understand what you are asking, my son? The point is not merely that such information may be a military secret...";
			link.l1 = "And what else then, Father? I shall speak plainly...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Do you understand what you are asking, my son? The point is not merely that such information may be a military secret...";
			link.l1 = "And what else then, Father? I shall speak plainly...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_9":
			dialog.text = "The problem lies with those very colonial archives. Twenty years ago Jamaica was under the Spaniards, and St. John’s and Bridgetown under constant threat of raids. It is unlikely any Royal Navy ships were stationed there...";
			link.l1 = "You mean the Admiralty archives in London, Father?";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "Perhaps. The papers should have been sent to the Admiralty. To obtain them will not be easy.";
			link.l1 = "But it can be done, can it not, Father?";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "Nothing is impossible, my son. But it will require effort... and payment.";
			link.l1 = "Of course, Father. Shall I give the money to you, or must I meet with someone else?";
			link.l1.go = "WildRose_Abb_12";
		break;

		case "WildRose_Abb_12":
			dialog.text = "I will meet someone else myself, my son. What I need from you is... eight hundred doubloons.";
			link.l1 = "Very well, Father. How long will it take?";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "I reckon two months. And, by the way, you have not told me the name of the one you seek.";
			link.l1 = "That man’s name is Joshua Casper.";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "I shall remember it. If you are ready to give me the full sum now — I will send word as soon as tomorrow.";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Of course, Father. Here, take it. Eight hundred in gold.";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "No, Father, I do not have such money on me. But I shall return soon and bring it.";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Very well, "+pchar.name+". Return in two months – I am certain by then I shall have one answer or another for you.";
			link.l1 = "Thank you, Father. Until we meet again!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "As you say, my son.";
			link.l1 = "I will return soon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;
		
		case "WildRose_Abb_16":
			dialog.text = "He learned both of Joshua Casper and of his ship – which, however, was not the 'Wrangler'. No brig of that name ever belonged to the Royal Navy.";
			link.l1 = "Hm... I am absolutely certain the vessel Joshua Casper served on bore that name. And what of Joshua himself?";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "That man was a fine officer with many merits and awards – all recorded in his personal file. Though he did not belong to the true faith, he was a worthy captain. Mademoiselle may well be proud of such roots.";
			link.l1 = "That is good news, Father. But if you permit, let us return to the ship. If it was not the 'Wrangler', then what was its name?";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "'Cornwall'. He left Plymouth in January of 1638 with orders to deliver wages to the garrisons of Antigua and Providence.";
			link.l1 = "Incredible...";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "Whether the ship reached its final destination, I do not know. But it did put in at St. John’s. In the port office there remains a report by Captain Casper dated June 2 of that year.";
			link.l1 = "I knew you were not as simple as you try to appear, Father! This document, I presume, contains some important details?";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "We are forever in your debt, Father. Since you mentioned this document – it must contain something important, then?";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Only a report of a battle with the Spanish galleon 'Toro' near the Azores, in which a third of the crew perished – read the report, it tells all.";
			link.l1 = "One more question: since you had access to the records of Antigua’s port authority, did you by chance come across Joshua Casper’s name anywhere else?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Only a report of a battle with the Spanish galleon 'Toro' near the Azores, in which a third of the crew perished – read the report, it tells all.";
			link.l1 = "One more question: since you had access to the records of Antigua’s port authority, did you by chance come across Joshua Casper’s name anywhere else?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "You ask much of me, my son. If you mean to suggest that he may have survived that shipwreck and later returned to the fleet – I very much doubt it.";
			link.l1 = "The Lord works in mysterious ways, Father.";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "Indeed, my son. But you see, his personal file states that Joshua Casper was born in 1586...";
			link.l1 = "Perhaps you are right, Father.";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "You know, Father, in my years in the Caribbean I have seen such things that I could believe even the most unlikely of tales.";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Surely such an officer was worthy of dying in battle. But if one is to speak philosophically, in a sense that too was a battle...";
			link.l1 = "I am no philosopher, Father. But thank you for everything...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Surely such an officer was worthy of dying in battle. But if one is to speak philosophically, in a sense that too was a battle...";
			link.l1 = "I am no philosopher, Father. But thank you for everything...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "The Lord leads you on this path, my children, and to aid you is my humble duty. But I fear there is nothing more I can do for you in this matter...";
			link.l1 = "I understand, Father. Well then, allow us to take our leave.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
