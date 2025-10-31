// брат Юлиан - священник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

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
				dialog.text = "Nem akarok beszélgetni veled. Ok nélkül támadsz békés helyiekre, és harcra provokálod ôket. Tûnj el, ateista!";
				link.l1 = "Ahogy akarod...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Nem vagyok meglepve, hogy túlélted. Rejtélyesek az Úr útjai. Élet és halál az Ô kezében van.";
				link.l1 = "Teljesen egyetértek veled, Julian testvér.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Üdvözöllek a szigetünk szent templomában, fiam. Az ajtók mindig nyitva állnak elôtted. Julian testvér vagyok, és örülök, hogy láthatom nagyszerû Urunk minden szolgáját.";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". Örülök, hogy megismerhetlek, Julian testvér.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Akarsz valamit?";
				link.l1 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "Vehetek tôled néhány bájitalt?";
				link.l2.go = "potion";
				link.l3 = "Van valami szent tárgyad, amit eladhatsz?";
				link.l3.go = "amulet";
				link.l5 = "Csak imádkozni akartam itt, és látni, hogy vagy. Viszlát!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Remélem, hogy gyakrabban látogatsz majd el a templomunkba. Vigyázz a lelkedre, fiam! A testedet is meg tudom gyógyítani, nemcsak lelkészként, hanem orvosként is dolgozom itt.";
			link.l1 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "Vehetek tôled néhány bájitalt?";
			link.l2.go = "potion";
			link.l3 = "Van valami szent tárgyad, amit eladhatsz?";
			link.l3.go = "amulet";
			link.l4 = "Mennem kell, Julian testvér. Viszlát!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "Persze, fiam. Milyen bájitalra van szükséged?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Egy egyszerû gyógyító fôzetre.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Egy gyógyító elixír.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Egy ellenszer.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Egy gyógynövénykeverék.";
				link.l4.go = "potion4";
			}
			link.l5 = "Sajnálom, Julian testvér, de meggondoltam magam.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Egy bájital? 90 pezó, fiam.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Vedd el, Julian testvér.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Most nincs elég pénzem... Késôbb visszajövök.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Egy elixír? 500 pezó, fiam.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Vedd el, Julian testvér.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Most nincs elég pénzem... Késôbb visszajövök.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Egy ellenszert? 200 pezó, fiam.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Vedd el, Julian testvér.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Most nincs elég pénzem... Késôbb visszajövök.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Egy keverék? 900 pezó, fiam.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Vedd el, Julian testvér.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Most nincs elég pénzem... Késôbb visszajövök.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Tessék. Vedd be a gyógyszered. Isten vezessen téged!";
			link.l1 = "Köszönöm, Julian testvér.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "Igen, adhatok neked néhány szent amulettet, amelyek megvédik az embereket a sebektôl és betegségektôl. Az ár bármelyik amulett esetében ugyanaz - tíz aranydublon. Még ma fel tudom ajánlani "+XI_ConvertString(npchar.quest.amulet)+" .";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "Igen, meg akarom venni ezt az amulettet. Itt van az aranyad.";
					link.l1.go = "amulet_pay";
					link.l2 = "Nincs szükségem erre az amulettre, Julian testvér. Megvárom, amíg megkapom, amire szükségem van.";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "Most nincs elég pénzem... Késôbb visszajövök.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Nem, fiam, sajnos semmi másom nincs. Gyere el hozzám máskor is, talán találok neked valamit.";
				link.l1 = "Megegyeztünk, Julian testvér.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("Kaptál egy amulettet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Köszönöm, fiam. A pénzed jó szolgálatot tesz. Fogd az amulettedet, és az Isten áldjon meg téged!";
			link.l1 = "Köszönöm, Julian testvér.";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Hallgatlak.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide, Julian testvér?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Hányan vannak a plébániádon?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Ki árul itt dolgokat?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Van-e veszélye a sziget pusztulásának? Viharok, talán?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdésem. Sajnálom...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ugyanúgy, mint sok helybéli, fiam. A hajómat elsüllyesztette egy vihar, amikor Havannából Új-Spanyolországba utaztam. Hála Istennek, túléltem, és most itt szolgálom Ôt, segítve a szegény lelkeket, hogy megtalálják az igazi útjukat.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Kevesebbet, mint amennyit szeretnék. A legtöbb narvál inkább az erôszakot kedveli, mint a kegyelmet, a rivadók pedig szegény és elveszett bárányok. Vakon végzik pogány rituáléikat, és kockára teszik halhatatlan lelküket. Van közöttük egy veszélyes varázsló, akit a Szent Inkvizíciónak kell megtisztítania.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sancho Carpentero saját kocsmája a Fleron, ott találsz ételt, italt és egy meleg ágyat. Axel Yost nagy választékban árul a 'Esmeralda'. Kérdezd meg az utcán az embereket, fiam, sokan találnak érdekes dolgokat a külsô gyûrûn.";
			link.l1 = "Köszönöm!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Minden az Úr kezében van, fiam. Hiszünk benne, és bízunk benne. A komoly bajok mindig is távol maradtak a mi szigetünktôl - a viharok gyakran történnek a szigeten kívül, de itt mindig csend van.";
			link.l1 = "Köszönöm. Megnyugtattál engem.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, mi? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a ládáimat!", "Úgy döntöttél, hogy megnézed a ládáimat? Ezt nem úszod meg!");
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
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én ennek a városnak a polgára vagyok, és arra kérem, hogy tegye hüvelybe a pengéjét.", "Figyelj, e város polgára vagyok, és arra kérnélek, hogy tedd hüvelybe a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, haver, amikor fegyverrel futsz. Ideges tudok lenni...", "Nem szeretem, ha az emberek fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
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

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}
