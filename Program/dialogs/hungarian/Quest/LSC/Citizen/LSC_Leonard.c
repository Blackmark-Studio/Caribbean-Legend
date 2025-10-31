// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nem akarok veled beszélgetni. Ok nélkül békés civileket támadtok meg, és harcra provokáljátok ôket. Tûnjetek el!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "Haver, épp idôben jöttél... Beszélni akarok veled... egy üzletrôl. Egy fontos ügyrôl.";
				link.l1 = "Tényleg? Úgy tûnik, nem vagy részeg. Történt valami? Szokatlan, hogy józanul látlak.";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A-a... hic! Helló, haver...";
				link.l1 = TimeGreeting()+". Úgy tûnik, már eleget ittál, haver.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Hic! Mit akarsz?";
				link.l1 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Csak tudni akartam, hogy vagy. Viszlát!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Igen! Elég volt? N-ope! Én egy ôrült részeges vagyok, hi-hic! Igen, Leonard Musket részeg, és ez így van rendjén!";
			link.l1 = "Szereted az italokat, mi? Igen, a nevem "+GetFullName(pchar)+". Örülök, hogy találkoztunk.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Ha te mondod. Mi itt mindannyian... hic, találkozunk egymással.";
			link.l1 = "Rendben, úgy tûnik, nincs kedved beszélgetni. Viszlát!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "Igen, haver, már majdnem józan vagyok. És ez azért van, mert van egy üzletem a számodra, egy fontos üzlet. És úgy tûnik, hogy meg tudod csinálni...";
			link.l1 = "Mi az? Mi az? Mi jár a fejedben? Beszélj, és ne vesztegesd az idômet a semmiért!";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "Haver, akarsz pénzt keresni? Ezüst pezót, arany dublont? Megmondom, hogyan. De osztoznod kell velem - együtt fogunk dolgozni.";
			link.l1 = "Mindig is ezt akartam. De minden a te javaslatodtól függ: Nem vállalok semmilyen munkát, még akkor sem, ha az nagyon jövedelmezô.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "Az üzlet nem igazán legális, az biztos, de nyereséges... és megbüntethetünk egy embert, aki túl válogatós lett. Nem fog elszegényedni, túl sok pénze van. Mindenki osztozik vele, így most rajta a sor, hogy ô is ezt tegye. Mondd csak, tudod kezelni a rumot? Mennyit tudsz meginni, mielôtt az asztal alá kerülsz?";
			link.l1 = "Attól függ. Nem vagyok benne biztos, hogy szokásom az ôrült ivás... Elmondja végre a részleteket?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "Eljutottam a lényeghez, csak te még nem látod. Rendben. Konkrét leszek. Van egy kövér, csúnya fattyú a szigeten - Giuseppe Fazio. Egy ritka söpredék. Élve nyúzza a narválokat, a rivadókat és a helyieket. Már egy ideje figyelem ôt, és végre találtam valamit\nKét láda van a karolinai kunyhójában: az elsôben papírok, a másodikban arany és ezüst. Mindkettô különbözô kulcsokkal van lezárva. Kövér mindig magánál tartja a kulcsokat.";
			link.l1 = "Nos, úgy tûnik, hogy ki akarod rabolni Faziót? Én ebben nem veszek részt. És örüljetek, hogy senkinek sem szólok róla. Ha meg akarod nézni a kövér ember mellkasát, akkor keress egy másik társat.";
			link.l1.go = "facio_exit";
			link.l2 = "Ha! Érdekes! Folytasd...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "Rossz, nagyon rossz... Rengeteg arany van, mindkettônknek elég. Rendben, majd találkozunk...";
			link.l1 = "Ég veled!";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "Két ajtó vezet a kabinjába. Az egyik mindig zárva van. De a kulcs, amelyik az aranyat tartalmazó ládát nyitja, az ajtót is kinyitja. Nem tudom, mi értelme van ennek az egésznek, de tény. Csak egy kulcsra van szükséged, hogy kinyisd a kunyhót és megszerezd az aranyat. Egy logikus kérdés következik - hogyan lehet megszerezni a kulcsot? Szóval, van egy tervem\nEgy kiváló terv, ha jól sikerül, Fazio soha nem fog rájönni, mi történt, és kit kell hibáztatni. Azt fogják hinni, hogy a titokzatos tolvaj volt az. A gond csak az, hogy egy vasfejû társra van szükségem, hogy véghezvigyem. Tudsz követni?";
			link.l1 = "Hallgatlak. Folytasd.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "Fazio szeret a Sanchónál ülni és egy jót inni, de az ô tömege túl nehézkes ahhoz, hogy a rum elvégezze a dolgát. Ezért kitalált egy ivójátékot - azt a játékot, amikor az emberek megpróbálják túlitatni ôt. Ha felajánlod neki ezt a játékot, kétségtelenül beleegyezik\nÉs aztán jön a mókás rész. Fogadsz vele, elmész a kocsmába, fogsz rumot, és addig iszol, amíg egyikôtök meg nem csókol egy asztalt. Ha kiborulsz, akkor az egész terv kudarcba fullad, egyedül nem fogom tudni megcsinálni\nEzért kérdeztem a fejedrôl. Ha Fazio nyikorogni és vicsorogni fog, mint egy disznó, akkor tekintsd úgy, hogy megtörtént. Én végig itt leszek a közelben. Ha végzett, elveszem a kulcsait\nAztán átvisszük a kövér embert az emeleti ágyba, és besurranunk a kabinjába, amíg alszik. A kulcsot rögtön azután visszaadom, hogy kifosztottuk a ládáját, észre sem fogja venni, hogy kirabolták\nA kulcs megszerzését és visszaadását én végzem, a ti feladatotok az, hogy leitatjátok Faziót, és beosonjatok a birtokára. Én ôrködni fogok, hátha felbukkan valaki, így lesz elég idôtök elmenekülni a hátsó ajtón keresztül\nA láda belsejét felezzük el, az lenne a tisztességes. Szóval, benne vagy?";
			link.l1 = "Szép terv! Persze, próbáljuk meg!";
			link.l1.go = "facio_6";
			link.l2 = "Nem, haver. Én passzolok. Félek, hogy nem fogok tudni annyit inni, hogy talpon maradjak, és túlhajtom Fazio-t. Keress egy másik partnert, aki kicsit erôsebb nálam.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "Örülök, hogy igazam volt veled kapcsolatban. Most menj el Fazióhoz, és beszéljetek meg egy találkozót a kocsmában este kilenc óra után. Remélem, hogy túlissza azt a disznót. Sok szerencsét és este találkozunk!";
			link.l1 = "Megpróbálom... Viszlát!";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "Pajtás, számítok rád. Igyál túl sokat abból a kövér emberbôl...";
			link.l1 = "Persze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "Kész, az a dagadt disznó fent alszik. Megvan a kulcs. Jól csinálod, úgy tûnik, elég józan vagy!";
			link.l1 = "Tényleg? Régen voltam már ilyen részeg. Kicsit szédülök... Menjünk?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "Kész, az a dagadt disznó fent alszik. Megvan a kulcs. Jól csinálod, tényleg sikerült túlitatnod azt a malacot...";
			link.l1 = "Igen, de már régen voltam ilyen részeg. Kavarog a fejem... Akkor menjünk?";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "Eh, haver, nem sikerült túlitatnod a kövér embert... Kár érte. Hát, legalább megpróbáltuk...";
			link.l1 = "A francba, olyan, mint egy... bot-t-tomless hordó. Argh, pihennem kell... Vége van, tûnjetek el! Hic!";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "Igen. Gyerünk! Kövess engem 'Carolina'! És ne kóvályogj, nincs sok idônk!";
			link.l1 = "Gyerünk!";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "Tessék. Fogd a kulcsot. A láda, amire szükséged van, a bejárattól balra van. Vigyél el annyit, amennyit csak tudsz gyorsan. Ne felejtsd el visszazárni. Ha meglátok valamit, háromszor kopogok az ajtón. Ebben az esetben fussatok el a hátsó galérián keresztül.";
			link.l1 = "Rendben. Légy résen!";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable loot... And were we risking for it? Eh... Fine, let's share what we have got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there will be much more... Risk wasn't worth it. Eh... Fine, let's share what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought that we will get more. Fine, let's share it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We have done well, partner! This is a whole lot of coins! Let's share!";
						else
						{
							sTotalTemp = "Wow! I haven't ever thought that the fat man's stash is so huge. Well done, partner! Let's share!";
						}
					}
				}
			}
			dialog.text = "Végre! Mit sikerült kivenned annak a gazembernek a ládájából? Mutasd meg, türelmetlenül várok!";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "Semmi sem volt benne. Csak néhány darabka, amulettek és ilyesmik.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "A mellkasból vettem "+sPeso+" és "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "Ez lehetetlen! Úgy tûnik, hogy minden hiába volt... Talán az a szemétláda egy másik ládába tette a cuccát. Eh! Rendben, add ide a kulcsot, és visszaadom a tulajdonosának, amíg nem hiányzik neki. Viszlát, haver...";
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "Osszuk meg...";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveDublonsFromPCharTotal(iDubl);
			Log_Info("Adtál "+iDubl+" dublont.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Rendben, add ide a kulcsot, és visszaadom a tulajdonosának, amíg nem hiányzik neki. Viszlát, haver...";
			link.l1 = "Sok szerencsét, haver...";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio panaszkodott, hogy valaki kitakarította a ládáját. Úgy tûnik, hogy a titokzatos tolvaj tette.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Hallottad? Fazio-t kirabolták! Kirabolták, miközben részegen játszott veled.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Erôs fejed van! Ennyi rumot inni és talpon maradni! That 's something...", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Tényleg?... hic! Figyelek...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Mindig iszol? És honnan szerzel érméket az italokhoz?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Mit tudsz mondani a helyiekrôl?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Szeretnéd elhagyni ezt a helyet és a szárazföldre menni?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Igen! Esküszöm, nem emlékszem. Igen, igen, nem emlékszem! Régen volt már. Valahol vitorláztam valahol, és végül itt kötöttem ki. Hic!";
			link.l1 = "Hm... Jól van, jól van.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Igen, részeges vagyok... Iszom, a fenébe is, mert már nincs mit tennem... Látod, pajtás, én végeztem. Csak a rumosüveg az egyetlen, amit akarok. Úgyhogy folytatom az ivást. És a pénz... he-he, a rum nem kerül sokba. Különben is, nem is kell megvennem\nVan egy hely, ami tele van rummal, de úszni kell, ha meg akarod szerezni, ezért csak akkor veszek rumot, amikor már túl részeg vagyok az úszáshoz... hic! Jizjezezejizze, nem, nem mondom meg, hol kell úszni, he-he, ne is kérdezd...";
			link.l1 = "Csodálatos.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Mit is mondhatnék, hic... róluk? Jó emberek beszélgetni és inni. Giuseppe Fazio olyan fontos ember, helyi nagyágyú, a ládája tele van arannyal... és mégis tiszteli az öreg Leót, meghívja egy italra a kocsmában. Bár néha ô is kér cserébe valamit, de az semmi, hic!\nHeh, nem tudod, mennyi dublont birtokol Fazio, aha-ha-ha-ha! Elég ahhoz, hogy élete hátralévô részét a Karib-tenger legjobb házában töltse, nem dolgozva és a világ legjobb rumját iszogatva. De ô itt marad, a Szigeten. Úgy tûnik, még mindig nem elég neki a pénz...";
			link.l1 = "Megvan...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "Hogy elmenjen? Hic! Miért? Nem, nem akarok sem a szárazföldre, sem a szegény szigetre menni. Van itt ingyen rum? Nincs! Nincs ingyen rum, hic! És ez azt jelenti, hogy ott nincs semmi keresnivalóm... Pajtás, én jól érzem magam itt. Megkérdezem az embereket, hogy el akarnak-e menni innen. Senki sem akar, kivéve kettôt vagy hármat, hic!";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, ah? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat!", "Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!");
			link.l1 = "Basszus!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Mi?! Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!";
			link.l1 = "Ostoba lány!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Figyeljen, jobb, ha elveszi a fegyverét. Ideges leszek tôle.", "Tudod, a pengével való rohangálást itt nem tolerálják. Vidd el.", "Figyelj, ne játszd a középkori lovagot, aki karddal rohangál. Vidd el, nem illik hozzád...");
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérnélek, hogy tartsd vissza a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, haver, amikor fegyverrel futsz. Ideges tudok lenni...", "Nem szeretem, ha a férfiak fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
				link.l1 = RandPhraseSimple("Megvan.", "Elviszem.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
