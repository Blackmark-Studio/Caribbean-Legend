// Куранай - индеец
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Mit akar a fehér testvér?";
				link.l1 = TimeGreeting()+". Fehér testvér? Mondd csak, miért hívtok ti, indiánok, minket fehér testvéreknek vagy sápadtarcú kutyáknak, mi?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Akarsz valamit?";
				link.l1 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Mutasd meg, mit találtál. Talán vennék valamit...";
					link.l3.go = "trade";
				}
				link.l5 = "Csak tudni akartam, hogy vagy. Viszlát!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Mi itt mindannyian békében élünk, fehér testvér. Curanai nem hívja fehér testvér a sápadtarcú kutyát. Nem minden sápadtarcú kutya. Sok indiait nevezhetek vörösbôrû kutyának.";
			link.l1 = "Hm. Gondolom, te filozófus vagy...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Curanai nem ért téged, fehér testvér. Mit jelent a filozófus?";
			link.l1 = "Nem számít, vörösbôrû testvér. Csak tetszik a gondolkodásod. Azt mondod, a neved Curanai? A nevem "+GetFullName(pchar)+". Örülök, hogy megismerhetlek.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Curanai örül, hogy tudja a fehér testvér nevét.";
			link.l1 = "Szép. Viszlát!";
			link.l1.go = "exit";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Kérdezd, sápadtarcú testvér, Curanai válaszol.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Mit csinálsz a szigeten?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Haza akarsz menni?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Békésen élsz a Szigeten? Történnek itt verekedések vagy veszekedések?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Én és törzsem néhány harcosa úgy döntünk, hogy elhajózunk a földünkhöz közeli, tiszta idôben látható kis szigetre. Bambuszból és vitorlából tutajt készítettünk. De a vihar hirtelen elragadott minket, és a nyílt tengerre sodort minket. Nem is tudtuk, milyen gyorsan eltûnt a földünk és a szigetünk\nSok-sok éjszakát és napot vitorláztunk a tengeren. Minden testvérem meghalt a szomjúságtól és az éhségtôl. Egyedül maradtam - a szellemek megsajnálták Curanai-t, és egy tutajon elhoztak erre a szigetre. Túléltem.";
			link.l1 = "Igen... Szomorú történet.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Curanai halászik. Curanai lecsapott a halra a szigonnyal. Ritkán-ritkán nagy rákot talál el. Akkor Curanai boldog - a rák finom, nagyon finom. Egy kapás elég néhány napra. És Curanai is merülni fenékig egy helyen. Ott nincsenek nagy rákok. Curanai sárga követ, kék követ, fekete követ és gyöngyöt szed. Nagyot és kicsit. Aztán Curanai eladja ôket a sápadtarcúaknak.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Curanai haza akar menni. De hol van az én otthonom? Curanai nem tudja, hol van a faluja és hogyan juthat oda.";
			link.l1 = "Hm. Mit is mondhatnék...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Narvál és Rivados gyakran harcolnak egymás ellen. Mi békében élünk és nem bántunk senkit. Néha a sápadtarcúak tûzvizet isznak és káromkodnak, de nem gyilkolnak. Van két tisztharcos, egyik gyûlöli a másikat. Egy nap az egyik megöli a másikat. Curanai tudja.";
			link.l1 = "Értem...";
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
			link.l1 = LinkRandPhrase("Jól van.", "Persze.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérnélek, hogy tartsd vissza a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Akkor mindegy.", "Ahogy mondod...");
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
