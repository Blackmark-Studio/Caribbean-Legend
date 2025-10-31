#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			dialog.text = NPCharSexPhrase(npchar, "Szeretne felszerelést vásárolni magának vagy a tisztjeinek, kapitány úr? Ha igen, akkor éppen a megfelelô személyhez jött!", "Ó, kapitány úr, tudtam, hogy meg fog szólítani! Sok más hasznos dolog mellett felszerelést is tudok ajánlani önnek és a tisztjeinek.");
			link.l1 = "Mutasd meg, mid van.";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "I came on a different business.";
			link.l2.go = "quests";*/
			// --> Мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "Hé, találtam egy érdekes növényt errefelé. Meg tudnád mondani, hogy lehet-e belôle fôzeteket vagy fôzeteket fôzni? Csak érdekesnek tûnik nekem. Megnéznéd?";
				link.l4.go = "mangarosa";
			}
			// <-- Мангароса
			

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Mondja, el tudna adni nekem egy üveg finom európai bort?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Figyeljen, tudom, hogy európai bort árul. Hatvan üvegre van szükségem.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Ez megint én vagyok. Mit jelent ez az egész?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Sinistra --> мини-квест "Знакомство с индейцами"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "Két pisztolyra van szükségem, valamint töltényekre és puskaporra húsz lövéshez.";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <-- мини-квест "Знакомство с индейцами"
			
			// --> Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "Figyelj, nem ismerôs a név 'Juan' ?";
				link.l4.go = "Consumption";
			}
			// <-- Цена чахотки
			
			//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Jó kereskedô, valami kivételes minôségû dolgot keresek. Nem a közönséges csecsebecséket, amelyek a legtöbbeket kielégítik, hanem egy valódi, kifinomult darabot - talán egy pár finoman megmunkált fülbevalót vagy egy elegáns medált, amely méltó az arisztokrata ízléshez. Olyan ajándékra van szükségem, ami egy elôkelô származású hölgynek is tetszene.";
				link.l4.go = "UV_Lavochniki_1";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Kíváncsi lennék, hogy a készletei között van-e valami jelentôs értékû? Olyan darabot keresek, amely még a legkülönlegesebb nemes hölgyek ízlésének is megfelelne - valami különlegeset és kifinomultat, ami messze túlmutat azon, ami az egyszerû polgároknak tetszene. Talán egy nem mindennapi mûvészetû medál vagy egy kifinomult tervezésû karkötô?";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Mondd csak, jó kereskedô, jártas vagy a finom ékszerek terén? Valami különlegeset keresek, amit egy elôkelô hölgynek ajándékozhatok. Hadd legyek ôszinte, nem érdekelnek a közönséges csecsebecsék. Amire szükségem van, az egy igazi pompás darab: talán egy drágakövekkel díszített bross vagy egy páratlan kézmûvességû gyûrû.";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "Figyelj, te mindenféle áruval kereskedsz... Tegnap vagy ma - valaki felajánlotta, hogy eladja neked  "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			link.l9 = "Köszönöm, nem érdekel.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = "Persze. Hétszáz pezó egy üveg.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "700 pezó. Fogja a pénzt és adja ide nekem.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "Kitûnô! Visszajövök, amint eldöntöttem, hogy veszek belôle.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "Kérem, vigye az üvegét.";
			link.l1 = "Köszönöm!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "Ha! Én csak egy kiskereskedô vagyok, nem nagykereskedô. Ennyi palackot több mint fél éven keresztül adnék el - ez a bor ritka és drága, és nem bárki engedheti meg magának, tudja. Nekem nincs ennyi.";
			link.l1 = "Rendben, nincs neked - nem probléma. De azért valahol beszerezheted magadnak, nem igaz? Talán megmondhatnád a beszállítód nevét, és én közvetlenül tôle venném meg. Vagy Európából szállítják neked a bort?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "Nem, dehogyis. Én innen szerzem be. De nem fogom csak úgy megnevezni a beszállítómat. De ezer pezóért... talán, megtenném...";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "Rendben. Itt van az ezres - és most mondja meg, ki a beszállítója.";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "Most már túl szemtelenek vagytok! Nem lenne túl jó neked? Megoldom a beszállítója nélkül is, köszönöm.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "Azt hiszem... akkor rendben. Itt a cetlije, és remélem, a jövôben viszonozza a szívességet.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "A borszállítóm neve "+pchar.questTemp.Wine.Name+", ô a helyi bolt tulajdonosa.";
			link.l1 = "Megvan! Köszönöm!";
			link.l1.go = "exit";
			//pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "A borszállítóm neve "+pchar.questTemp.Wine.Name+", ô a helyi bolt tulajdonosa.";
			link.l1 = "Megvan! Köszönöm!";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "Ahogy óhajtja, kapitány. Minden jót neked.";
			link.l1 = "Viszlát.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "Ezt hogy érti? Magyarázza meg.";
			link.l1 = "Átvertél, te gazember! Épp most voltam a boltban, "+pchar.questTemp.Wine.Name+" soha nem kereskedik borral, hiszen ô maga mondta ezt nekem! Adja vissza a pénzemet!";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "Félreértés történt... Elmentem a boltoshoz, és "+pchar.questTemp.Wine.Name+" azt állította, hogy ô soha nem kereskedett borral. Hogy tudod ezt megmagyarázni?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "Heh! Ô borral kereskedik, az biztos. Csak éppen bort nem ad el akárkinek - mint ahogy kevés más árut is. És ennek több oka is van... Ha bort akarsz venni tôle, írhatok neki egy üzenetet. Ismer engem és a kézírásomat, így miután elolvasta, eladja neked azt a bort. Természetesen ez a szívesség sem ingyenes.";
			link.l1 = "Ez felháborító! Éppen most vettél el tôlem egy ezrest!";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "Ezret vettem el tôled információért. A levélért pedig külön kétezer pezót kell fizetnie, és semmiképpen sem kevesebbet.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "Ó... Ti kereskedôk olyan átkozottul kapzsik vagytok. Nem csoda, hogy senki sem kedveli a fajtátokat. Hát jó, itt a pénzed, úgyhogy csak rajta, írd meg a levelet.";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Megbízható", "Trustworthy");
				link.l2 = "(Megbízható) kössünk kompromisszumot. Ön most ingyen ad egy ajánlást, én pedig viszonzom egy ajánlással, amit késôbb szintén ingyen adok át önnek. Ez a borüzlet csak a kezdet.";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "Na, ez már teljesen túlzás! Inkább lemondanék az egész ügyrôl, nem fogok ilyen ravasz fösvényt gazdagítani. És ez alatt a fösvény alatt magát értem. Viszontlátásra.";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "Azt hiszem... akkor rendben. Itt a cetlije, és remélem, a jövôben viszonozza a szívességet.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6_1");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Maga egy furcsa madár, kapitány! Persze, tudom, hogy a pénztárosod intézi a pénzügyeket, de néha a saját fejedet is használhatnád. Lehetôsége lesz arra, hogy az én árfeláram nélkül vásároljon egy tisztességes mennyiségû bort nagykereskedésben, és jelentôs nyereséget termeljen. Szóval ne akadályozzuk meg egymást a pénzkeresésben, mert most ön az, aki kapzsinak tûnik.\nRendben...(írás) Tessék, vegye el ezt a levelet - "+pchar.questTemp.Wine.Name+"  kérdés nélkül eladja önnek a bort.";
			link.l1 = "Remélem, hogy így lesz... Ha valami megint rosszul sülne el, visszajövök. Viszlát!";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "Ahogy óhajtja, kapitány. Viszontlátásra.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "Ó, szóval azért jöttél ide, hogy megfenyegess és gorombáskodj? Akkor hívom az ôrséget! Hé, ôrök! Itt vagyok!";
			link.l1 = "Ó, fogd be! Te nyertél, én elmegyek! Átkozott legyél "+ NPCharSexPhrase(npchar, "","") +", kormorán, menj tönkre!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
			DelLandQuestMark(npchar);
		break;
		// <-- мини-квест Дефицитный товар
		
		//Sinistra --> мини-квест "Знакомство с индейцами"
		case "ZsI_PokupaemPistolety":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Á, értem. Alkut kötöttél a bennszülöttekkel? Úgy hallottam, ez már így is sokba került neked, ha-ha-ha!";
			}
			else
			{
				dialog.text = "Bajra számít, kapitány? Vagy dzsungelkalandot tervez? Ha-ha!";
			}
			link.l1 = "Szóval, köthetünk egy üzletet?";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "Persze, hogyne! A vendégeket mindig szívesen látjuk. Háromezer pezóért megbízható pisztolyokat, töltényeket és puskaport kapnak, ahogy kérik.";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "Drága, de rendben van. Elfogadom.";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "Az ár igazságtalannak tûnik. Mit szólna egy kis kedvezményhez Fadey Muscovite barátjának?";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "Háromezer? Ez rablás! Viszlát, Monsieur!";
			link.l3.go = "ZsI_NetDeneg";
		break;
		
		case "ZsI_NetDeneg":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			PChar.quest.ZsI_Timer.over = "yes";
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;
		
		case "ZsI_PokupaemPistolety_2":
			dialog.text = "Jó utat, kapitány!";
			link.l1 = "Viszontlátásra, uram.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -3000);
			Log_info("Megszerezted a szükséges pisztolyokat a Kakaólevélhez.");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_PokupaemPistolety_3":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
			PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
			PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;
		
		case "ZsI_Torg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
			{
				Notification_Skill(true, 19, SKILL_COMMERCE);
				dialog.text = "Valóban, kapitány. Fadey barátait mindig szívesen látjuk itt. Kétezer-háromszáz a tételért?";
				link.l1 = "Ez jobban hangzik. Elfogadom.";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				Notification_Skill(false, 19, SKILL_COMMERCE);
				dialog.text = "Fadey úr barátai mindig szívesen látottak, de az áraknak nincsenek barátai. Háromezer pezó lesz, kapitány.";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "Drága, de rendben van. Elfogadom.";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "Háromezer? Ez rablás! Viszlát, Monsieur!";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("Trading skill is not sufficient");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "Jó utat, kapitány!";
			link.l1 = "Viszontlátásra, uram.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("Megszerezted a szükséges pisztolyokat a Kakaólevélhez.");
			PlaySound("Interface\important_item.wav");
		break;
		// <-- мини-квест "Знакомство с индейцами"
		
		// --> Цена чахотки
		case "Consumption":
			dialog.text = "Nem, ez nem... Kérem, ne zavarjon, nagyon elfoglalt vagyok... Micsoda idióta kérdés...";
			link.l1 = "Értem, értem. Elnézést, hogy az idejét vesztegetem...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <-- Цена чахотки
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Még sosem hallottam róla... Mi is ez tulajdonképpen? Én még soha nem hallottam ilyesmirôl"+ NPCharSexPhrase(npchar, "","") +".";
			link.l1 = "Nos, ez egy hajóépítô szerszám, "+pchar.GenQuest.Device.Shipyarder.Describe+". Ajánlott valaki ilyesmit neked?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "Hmm... Igen, volt egy furcsa fickó. De nem mondta el, hogy mi az a dolog, csak megpróbálta eladni nekem. De minek kellett volna nekem, ha fogalmam sincs, mire való? Hogyan adnám el? Szóval visszautasítottam"+ NPCharSexPhrase(npchar, "","") +", és ô elment.";
				link.l1 = "És hogy nézett ki és hova ment? Nekem nagyon kell az a hangszer.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nem, semmi ilyesmi. Sajnálom, nem tudok segíteni. Kérdezôsködjön.";
				link.l1 = "Értem. Nos, itt az ideje, hogy kérdezôsködjünk!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "Mutasd meg nekem... Igen, ez egy érdekes növény. És nagyon, nagyon ritka. A neve Manga Rosa. Nem tudom, mire használják, de volt egy érdekes tény, amihez kapcsolódik...";
				link.l1 = "Hogy érti ezt?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Mutasd meg nekem... Igen, ez egy érdekes növény. De sajnos ennél többet nem tudok mondani. Ha valóban használják valamilyen célra, az számomra ismeretlen.","Lássuk csak... Hmm... Gyógynövénynek tûnik, de nem tudok róla semmit. Sajnálom, nem tudok segíteni.","Hol van? Hmm... Nem, ezt még sosem láttam. Nagyon érdekesnek tûnik, de fogalmam sincs, hogy mire használják...");
				link.l1 = "Értem. Hát, majd kérdezôsködöm még egy kicsit. Bocsánat.";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "A nomád cigányok és vademberek nagy érdeklôdést mutatnak ezek iránt a növények iránt. Egyszer láttam egy cigányt, aki egy maréknyi aranyat fizetett egyetlen ilyen szárért. De fogalmam sincs, miért lenne rá szükségük.";
			link.l1 = "Értem... Hát, ez legalább valami! Most már tudom, hol kell tovább kérdezôsködnöm. Köszönöm szépen!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> Украденное воспоминание
		case "UV_Lavochniki_1":
			dialog.text = "Sajnálatos módon, "+GetAddress_Form(NPChar)+", az én létesítményem már hónapok óta nem látott ilyen finom árut. A luxus iránti étvágy ezekben a nehéz idôkben csökkent. A boltomat látogató egyszerû emberek csak szerény csecsebecséket engedhetnek meg maguknak, míg az elôkelôk ritkán nézegetik szerény portékáimat.";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_2":
			dialog.text = "Sajnálom, kapitány, de ilyen gyönyörû darabok már jó ideje nem díszítik a boltomat. A kikötô gazdag vendégei ritkán kedveskednek jelenlétükkel szerény boltomnak, és a törzsvásárlóim csak azt keresik, amit a szûkös pénztárcájuk megengedhet magának.";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_3":
			dialog.text = "Kapitány, az idôzítése nagyon szerencsétlen... Néhány órával ezelôtt váltam meg egy igazán pompás nyaklánctól, amit egy másik, jelentôs vagyonnal rendelkezô kapitánytól vettem. Az üzletem rendszeresen szerez be olyan darabokat, amelyek még a legigényesebb hölgyek szívét is képesek megolvasztani\nHátha holnap visszatérne? Giselle... vagyis... a beszállítóim... valószínûleg tudnának szerezni egy olyan kincset, amely örökre megkedveltetné önt csodálatának tárgyával.";
			link.l1 = "Az idô olyan luxus, amivel nem rendelkezem; egy ilyen darabra késedelem nélkül szükségem van. Kérem, mondja, mi a neve annak a szerencsés kapitánynak, aki megszerezte a nyakláncot, amirôl beszél?";
			link.l1.go = "UV_Lavochniki_3_1";
		break;

		case "UV_Lavochniki_3_1":
			dialog.text = "Tristan Renier, a 'Golden Seagull'. kapitánya hajója továbbra is a kikötônkben horgonyoz. Bár be kell vallanom, megkérdôjelezem, hogy lemondana-e egy ilyen zsákmányról. Ha nem akarja, holnap térjen vissza hozzám. Becsületemre legyen mondva, kapitány, a megállapodást a legmegfelelôbbnek fogja találni.";
			link.l1 = "...";
			link.l1.go = "UV_Lavochniki_exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
		break;
		
		case "UV_Lavochniki_exit":
			DialogExit();
			AddQuestRecord("UV", "3");
			/*AddQuestUserData("UV", "sSex", NPCharSexPhrase(NPChar,"ца","ки"));
			AddQuestUserData("UV", "sSex1", NPCharSexPhrase(NPChar,"ец","ка"));
			AddQuestUserData("UV", "sSex2", NPCharSexPhrase(NPChar,"","а"));*/
		break;
		//<-- Украденное воспоминание
		
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
