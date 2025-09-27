// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Figyeljen, uram, miért hagyta, hogy az öklével verekedjen, mi? Nincs semmi dolgod a mûhelyemben, amíg nem leszel az ellenségünk. Kifelé!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Hallottam a tetteidrôl. Jó, hogy Donald barátja és szövetségesünk lettél. A narválok tudják értékelni a barátságot, ezt biztosan állíthatom.";
					link.l1 = "Remélem is. Most már számíthatok a szolgálataira?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Szóval? Mit akarsz?";
					link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". És én csak sétálgatok, ismerkedem az emberekkel. Zavarlak?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Hallottam a tetteidrôl. Jó, hogy Donald barátja és szövetségesünk lettél. A narválok tudják értékelni a barátságot, ezt biztosan állíthatom.";
					link.l1 = "Remélem is. Most már számíthatok a szolgálataira?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Akarsz újra beszélgetni? Csalódást kell okoznom neked, erre nincs idôm és nincs is kedvem.";
					link.l1 = "Rendben, nem foglak zavarni.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Pontosan! Zavarsz engem, uram. Jürgen Schmidt vagyok, a Narwhal klán fegyver- és kovácsmestere. Én látom el a népünket fegyverekkel. De idôbe telik egy jó pengét, kulcsot, zárat készíteni, vagy a tornyos mousqueton mechanikáját megjavítani. Sok idô, türelem és odafigyelés kell hozzá. Éppen ezért, mert nem szeretem, ha az emberek zavarnak.";
			link.l1 = "Fegyvereket készítesz? Megrendelhetek tôled valamit?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Nem. Csak a Narvál klán tagjai számára készítek fegyvereket. Ez az elvem, és ezt be is tartom. Szóval ne is reménykedjen, uram. Csatlakozz a klánunkhoz, vagy legalább légy a szövetségesünk, és akkor majd beszélgetünk.";
			link.l1 = "Rendben. Akkor én most elmegyek. Elnézést a zavarásért!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "Megteheted. Narwhals barátja az én barátom is, ezért figyelek rád.";
			link.l1 = "Szeretnék rendelni egy pengét.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "Hallottam, hogy készítettél egy különleges pengét a néhai Alan Milrow-nak. Láttam azt a kardot, nagyszerû fegyver. Rendelhetek valami hasonlót?";
				link.l2.go = "narval";
			}
			link.l3 = "Még nincs ötletem. Gondolkodom rajta, aztán visszajövök!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ha, "+GetFullName(pchar)+"! Szóval nem fulladtál meg? Hát ez nem semmi! Tényleg életben vagy?";
				link.l1 = "Ne aggódj, Jürgen. Életben vagyok! Nem akartam megfulladni...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "Ah, "+GetFullName(pchar)+"! Mit akarsz?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "Elhoztam a három darab különleges vasat, ahogy kérted. Nézd meg, ez az, amit akarsz?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "Nézd meg, Jürgen. Találtam egy érdekes vasrudat az alján, de sokkal nehezebb, mint amennyit kértél. Öt font, nem kevesebb.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "Szeretnék rendelni egy pengét.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "Hoztam neked még több dublont, hogy kifizessem a pengét.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "Hallottam, hogy készítettél egy különleges pengét a néhai Alan Milrow-nak. Láttam azt a kardot, nagyszerû fegyver. Rendelhetek valami hasonlót?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "A rendelésemért jöttem. Már biztosan elkészült, igazam van?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "Nem, semmiség, csak üdvözölni akartam.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "Csak üdvözölni akartam. De van néhány különleges követelményem minden rendelésnél, úgyhogy elôbb jól figyeljen.";
			link.l1 = "Csupa fül vagyok.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Csak egy pengét rendelhet tôlem, és csak egyszer. Nem készítek konkrét fegyvert, csak típust lehet megnevezni - rapír, szablya vagy széles kard. Gondold át bölcsen, mielôtt választasz, a penge végleges tulajdonságai és minôsége a pillanatnyilag rendelkezésemre álló anyagoktól függ\n. A megrendelésed elkészítése húsz napot vesz igénybe. Csak dublont fogadok el. Ezer érme. Pénzt elôre.";
			link.l1 = "Tényleg! Drága...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "Ez drága. De kiváló pengéket készítek, így az ár elég korrekt. Amúgy is a te döntésed, nincs nyomás.";
			link.l1 = "Értem, Jürgen. Igen, szeretnék rendelni.";
			link.l1.go = "blade_3";
			link.l2 = "Hm. Idôre van szükségem, hogy átgondoljam, mielôtt bármit is rendelnék tôled. Majd késôbb megbeszéljük!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "Rendben. Akkor add ide a dublonjaidat.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "Tessék, kérem. Van egy "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "Hm. Sajnos most nincs nálam. De biztosan elhozom önnek, és folytatjuk a beszélgetést.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "Szóval ez a végsô választásod? Biztos vagy benne?";
			link.l1 = "Igen, biztos.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("Adtál "+sti(npchar.quest.blade_pay)+" dublont.");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Nagyszerû. Kifizette a munkámat és az anyagokat, így most már elkezdhetem.";
				link.l1 = "Megrendelhetem?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "Jól van. Elfogadom a dublonjaidat. Többet kell hoznod nekem "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" .";
				link.l1 = "Elhozom neked, ha lesz.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "Persze, hogyne! Melyik típus tetszik a legjobban? Rapiers, szablya vagy kard?";
			link.l1 = "A pengéket. Szeretem az elegáns és könnyû fegyvereket.";
			link.l1.go = "rapier";
			link.l2 = "A szablyákat. Véleményem szerint ezek az optimálisak.";
			link.l2.go = "sabre";
			link.l3 = "A kardok biztosan! Vágj és vágj!";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "Ahogy akarod. Húsz nap múlva jöjjön vissza a rendeléséért, nem korábban.";
			link.l1 = "Köszönöm! Húsz nap múlva találkozunk. Viszlát, Jürgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "Ahogy akarod. Húsz nap múlva jöjjön vissza a rendeléséért, nem korábban.";
			link.l1 = "Köszönöm! Húsz nap múlva találkozunk. Viszlát, Jürgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "Ahogy akarod. Húsz nap múlva jöjjön vissza a rendeléséért, nem korábban.";
			link.l1 = "Köszönöm! Húsz nap múlva találkozunk. Viszlát, Jürgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "Igen. A pengéd készen áll. Kérem, vegye el és használja. Meg fogod érteni, hogy mennyibe kerül, amint megérinted.";
			link.l1 = "Köszönöm, Jürgen.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "Sajnos, barátom, két dolgot utasítok el, két okból kifolyólag. Elôször is, egy ilyen széles kardot csak a Narwhal klán egy tagjának fogok készíteni, és csak egy különleges személynek. Másodszor, nincs hozzá anyagom.";
			link.l1 = "És mi az a különleges vas, amire szükséged van? Úgy hallottam, hogy a fenékrôl szerezték...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Pontosan. Ennek a fémnek a darabjai szétszóródtak a partjainkon. Nem tudom, hogy kerültek oda. De a vas egyedülálló, sosem rozsdásodik, és a belôle készült pengék sosem tompulnak el. Szóval ha sikerülne megszerezned a vasat, akkor talán megoldhatnánk a problémát. De van még egy probléma, te nem vagy narvál...";
			link.l1 = "Hm. Tényleg számít ez?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Igen. Tekintsd ezt az én szeszélyemnek, de én csak narváloknak fogok ilyen kardot készíteni.";
			link.l1 = "Nos... Rendben, elfogadom. De van egy ötletem. Megrendelhetem ezt a pengét a Narvál klán tagjának?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Hm. Feltételezem, hogy igen, abban az esetben, ha elhozod nekem a vasat. Ez nem sérti az elveimet... És kinek készítsem el a kardot?";
			link.l1 = "A Vörös Máriának. Ô a Narvál klánból származik, és megérdemli, hogy egy ilyen kiváló fegyvert birtokoljon.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Ha! Ezt magam is kitalálhattam volna. Kezdek túl öreg lenni... Nos, egyetértek. Mary nagyon fog örülni egy ilyen ajándéknak, biztos vagyok benne... Hozzátok ide a vasat, és én elkészítem a kardot. A pengéért... ah, mindegy, majd én megcsinálom ingyen. Nem csak tôled lesz ajándék, hanem mindkettônktôl.";
			link.l1 = "Köszönöm! Mennyi vasra lesz szükséged?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Azok a darabok, amiket az alján találtunk, eléggé egyformák voltak - egy-egy font. Nekem három ilyen darabra van szükségem.";
			link.l1 = "Jó lesz. Megpróbálom megtalálni ôket. És majd újra beszélünk.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Lássuk csak... Igen, ez az! Nehéz volt ilyen kis darabokat találni az alján?";
			link.l1 = "Hát, mit mondhatnék... Mária megér ennyi fáradságot, nem igaz?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Hadd nézzem... Hát nem nagyszerû? Igen, ez az alsó vas, de ilyen nagy darabokat még sosem láttam. Ez elég lesz a kard készítéséhez. Nehéz volt megtalálni?";
			link.l1 = "Hát, mit mondhatnék... Mária megér ennyi fáradságot, nem igaz?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "Egyre jobban kedvellek, "+pchar.name+"... Rendben. Most rajtam a sor, hogy a mi gyönyörû amazonunkért dolgozzak. Két napba telik, mire elkészül a széles kard, a többi megrendelést elrakom\nMár holnapután hozzám viszi Máriát. Ne mondd el neki, ez egy meglepetés. Boldog lesz, mint egy gyerek.";
			link.l1 = "Rendben, Jürgen. Rendben, Jurgen. Holnapután találkozunk!";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", Ne zavarj engem. Azt akarod, hogy idôben elkészítsem a kardot, ugye?";
			link.l1 = "Igen, persze. Elmegyek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, ah? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat!", "Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!");
			link.l1 = "A francba!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
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

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
