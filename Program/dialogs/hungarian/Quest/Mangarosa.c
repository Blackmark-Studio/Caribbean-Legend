// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "Mit akarsz a házamban?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "A neved Amelia, ugye? Azért jöttem, hogy egy növényrôl kérdezzem. Rózsaszín Mangó.";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "Még nincs mit mondanom. De egy nap visszajövök...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "Érdekes! És ki beszélt neked rólam, bátor fiatalember?";
			link.l1 = "Az egyik embered. Azt mondta, hogy te ismered ennek a növénynek a titkait, és megtaníthatod nekem, hogyan készítsek belôle különleges fôzeteket...";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "Elôször is, mutassa meg a növényt, amirôl beszél. Lehet, hogy semmit sem tudsz róla, és csak az idômet vesztegeted. Hol van a Rózsaszín Mangó?";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Tessék, nézd meg.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "Hm...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "És mit akartál mutatni nekem? Nincs is Rózsaszín Mangó. Úgyhogy takarodj, haver, amíg nem leszek dühös. Ennek a beszélgetésnek vége.";
			link.l1 = "De...";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "Már megint te? Ne keveredj bajba, fiú...";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Nyugodj meg, Amelia. Legutóbb valahol elejtettem. Tessék, elhoztam neked Manga Rosát. Nézd meg.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "Lássuk csak... Úgy tûnik, tudsz róla valamit. És azt akarod, hogy eláruljam neked a bájitalaim titkát?";
			link.l1 = "Pontosan. És nem ingyen, ha jól tudom...";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "Jól érti, fiatalember! Nem nézel ki teljesen idiótának. Nos, én taníthatok egy olyan embert, aki a tudásra törekszik, és aki nem pazarolja ezt a ritka növényt haszontalan füstölgô cuccra...";
			link.l1 = "Amelia, mielôtt elkezdenénk alkudozni... lennél szíves elmondani néhány alapvetô tudnivalót a bájitalokról, amiket a Manga Rosából készíthetek?";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "Nincs alku, haver. Megmondom az árat, és a te döntésed lesz, hogy kifizeted-e vagy sem. Ne számítson semmilyen alkura vagy kedvezményre, ez nem egy piac. És ami a kérdésedet illeti... Készíthetsz speciális Rózsaszín Mangó fôzeteket, amelyek megerôsítik a fizikai képességeidet. Erôsebbé, kitartóbbá vagy gyorsabbá tehetnek, vagy teljesen megváltoztathatják a testedet, így minden szempontból erôsebb leszel, de egy ilyen fôzetnek gyengébb hatása lenne, mint az elôzô kettônek.";
			link.l1 = "Nagyon érdekes. Nevezd meg az árat.";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "Három receptet is megtaníthatok neked. Minden receptért egy növényt és ötszáz aranyat kérek.";
			link.l1 = "Mesélj még ezekrôl a bájitalokról. Mire képes mindegyik?";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "Az alkímia mûvészetének mestere kell lenned, ha egyetlen bájitalt akarsz készíteni. Minden bájital legfeljebb két napig tart, attól függ, mikor iszod meg, ha éjfélkor iszod meg, akkor közel két teljes nap lesz\nAz elsô bájital erôt és kitartást ad. Jobban fogsz harcolni, kevesebb sérülést fogsz szenvedni és nagyobb súlyt fogsz cipelni\nA második bájital gyorsabbá, fürgébbé, fáradhatatlanabbá tesz, és a célzásodat is javítja\nA harmadik bájital kétszer gyengébb hatással bír, mint az elôzô két bájital. De bájt, önbizalmat és szerencsét is ad neked\nMinden Rózsaszín Mangó alapú bájital pozitív hatással van az egészségedre. Egyszerre csak egy bájitalt szabad meginnod, soha ne keverd ôket, különben nem tesznek jót, ellenkezôleg, erôs mérgezést kapsz\nSzóval, szépfiú, kész vagy most azonnal fizetni a tudásért, vagy gondolkodási idôre van szükséged?";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "Igen, készen állok.";
				link.l1.go = "amelia_8";
			}
			link.l2 = "Egy kicsit gondolkodnom kell. Ez egy nagy döntés, amit meg kell hoznom.";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11")) {
				if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total")) {
					link.chickengod = "Amelia, úgy látszik, neked van érzéked az ilyesmihez. Meg tudod mondani, hogy van-e kereslet az ilyen kövekre a néped körében? Mindenhol találok ilyeneket - mintha mindenki a megszállottja lenne!";
					link.chickengod.go = "chickengod";
				}
			}
			
			if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.chickengod = "Tessék, Amelia. Ahogy rendelted: száztizenhárom Vipera-kô.";
				link.chickengod.go = "chickengod_collected";
			}
		
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "Á, maga az, fiatalember! Szóval, segítettek a bájitalaim?";
				link.l1 = "Tényleg így volt, Amelia. Köszönöm, Amelia.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Á, te vagy az, fiatalember! Akarsz venni néhány receptet?";
				if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
				{
					link.l1 = "Pontosan. Ezért vagyok itt.";
					link.l1.go = "amelia_8";
				}
				
				link.l2 = "Még nem, Amelia. Csak meglátogatlak.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "Rendben. Milyen receptet akarsz venni?";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "Az erô és kitartás bájitalának receptjét.";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "A mozgékonyság és fáradhatatlanság fôzetének receptjét.";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "Egy összetett bájital receptjét.";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "Jól van. ATidal Wave nevet adtam neki 'Tidal Wave'. Tessék, vegyen egy utasítást. Olvasd el figyelmesen. És ne felejtsd el, hogyan kell helyesen használni!";
			link.l1 = "Köszönöm, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "Jól van. Én a 'Squall'. nevet adtam neki, itt egy utasítás. Olvassa el figyelmesen. És ne felejtsd el, hogyan kell helyesen használni!";
			link.l1 = "Köszönöm, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "Jól van. A 'Tengeri ölelés'. nevet adtam neki, itt egy utasítás. Olvasd el figyelmesen. És ne felejtsd el, hogyan kell helyesen használni!";
			link.l1 = "Köszönöm, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveDublonsFromPCharTotal(500);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("500 dublont és egy Rózsaszín Mangó-t kaptál...");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
		
		case "chickengod":
			dialog.text = "Bax de adder, valóban! Nem sokat ér, de hasznát veheti az, aki ért hozzá. Hozzatok nekem száztizenháromat, és kinyitom nektek az egyik ládámat.";
			link.l1 = "Az egy egész rakás kô! Miért nem mondod el elôbb, miért van szükséged rájuk?";
			link.l1.go = "chickengod_1";
		break;
		
		case "chickengod_1":
			dialog.text = "Nem, kedvesem, ha kérdezned kell, akkor ez a tudás még nem használ neked.";
			link.l1 = "És mi van a ládában, amit olyan nagylelkûen megígértél, hogy kinyitsz?";
			link.l1.go = "chickengod_2";
		break;
		
		case "chickengod_2":
			dialog.text = "Nagyon sok minden, ami hasznos a kapitányok számára, akik nem vetik meg a kétkezi munkát. Ne vesztegesd az idômet, kedvesem, ennyi kavicsot úgysem tudsz összegyûjteni.";
			link.l1 = "Majd meglátjuk!";
			link.l1.go = "exit";
			
			npchar.quest.ChickenGod = true;
		break;
		
		case "chickengod_collected":
			dialog.text = "Ha-ha-ha-ha! Csak vicceltem, kedvesem!";
			link.l1 = "Majd akkor viccelôdsz, ha megégetnek, boszorkány, a saját kunyhódban!";
			link.l1.go = "chickengod_collected_1";
		break;
		
		case "chickengod_collected_1":
			dialog.text = "Ez nem az én sorsom, kedvesem... Büszkévé tetted ezt a cigányt! Tessék, ez a láda a tiéd, fosztogassátok.";
			link.l1 = "Köszönöm, Amelia. De nagyon remélem, hogy van benne valami hasznos a régi alsónemûdön kívül...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			npchar.quest.ChickenGod.Complete = true;
			AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
} 
