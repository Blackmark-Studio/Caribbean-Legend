// Вильям Патерсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Van valami, amit szeretnél?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "Jó napot, uram. Az isten verje meg, szóval te vagy az, aki itt a katonai viszályt szította?!";
			link.l1 = TimeGreeting()+", ...uram. Igen, az én hajóm volt az, amelyik leszállt. Mi a baj egyébként? Maga kicsoda? Egy angol, gondolom?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "Egy skót, Monsieur. William Paterson, az angol haditengerészet kapitánya, ô pedig az elsô tisztem és jobbkezem, Archibald Calhoun. A helyzet az, hogy van egy spanyol erôd a dzsungelben. Az a feladatom, hogy kirúgjam az átkozott fattyakat az erôdbôl, amelyet veszélyesen közel építettek az angol területhez.\nA közelmúltban megpróbáltuk megrohamozni, de a fattyaknak a veszteségeik ellenére sikerült kitartaniuk. Elindultam erôsítésért és...";
			link.l1 = "Erre most nincs szükség. Befejeztem a befejezetlen ügyeteket, a dzsungel erôdje üres. Diego de Montoya spanyol parancsnok halott, és a századát is kiirtották.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "Miféle önbíráskodás ez? Mi a motivációd, hogy ilyen katonai akciót indítasz angol területen?";
			link.l1 = "Emlékeztetem Paterson kapitány, hogy ez nem Belize. Miféle angol birtok? Ez az egész felhajtás Don Diego de Montoya és az ô kockázatos döntése miatt kezdôdött, hogy megtámadott engem és a hajóimat.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "És mi oka volt Don Diegónak arra, hogy megtámadja önt, kapitány?";
			link.l1 = "Neki és nekem régi viszályunk van... Azóta a nap óta, amikor az általa vezetett század megtámadta St. Pierre-t, és nem sokkal késôbb az én közvetlen közremûködésemmel likvidálták.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "Reszkessetek! Élve kellett az a tiszteletreméltó caballero! Ki akartam kérdezni, hogy miért hozott létre katonai bázist a dzsungelben. Nem lehetett ok nélkül...";
			link.l1 = "Sajnálom, de most már nem tud semmit sem mondani. Mindenesetre az erôdben lehetnek sebesült katonák a helyôrségbôl. Van rá esély, hogy tudnának beszélni?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "Katonák... Ó, mi haszna van néhány keményfejû kosnak!... Hol van Don Diego holtteste? Fontos iratok lehettek volna nála!";
			link.l1 = "Don Diegót a fegyveres erôd földjén hagytam. Ha olyan nagy szükséged van rá, ott megtalálod. Nem hiszem, hogy el tudna szökni.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "Eh... és ki kérte meg, hogy más dolgába avatkozz... Elég nagy fejfájást okoztál nekem...";
			link.l1 = "Kapitány, nem értem, miért dorgál engem. Elvégeztem a munkádat, csatába küldtem a saját embereimet, kockáztattam az életemet, és mégis elégedetlen vagy. Most már csak annyit kell tennie, hogy tájékoztatja a Port Royal-t a küldetés sikerérôl és minden ügyérôl. Biztosíthatlak, hogy nem fogok dicsôséget követelni a dicsôségedért.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "Elismerést követel? Mit ért dicsôség alatt?! Egyáltalán nem érti... Eh, rendben. Viszlát, uram.";
			link.l1 = "Minden jót önnek is!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\English\sharlie\Willie Paterson.wav");
			dialog.text = "Ember, a pletykák nem hazudnak, hogy kilenc életed van, mint egy macskának! "+TimeGreeting()+", Monsieur de Maure. Nem néz ki túl jól...";
			link.l1 = TimeGreeting()+", Mr. Paterson. Meg kell mondjam, ön és a barátja, Archibald, jól játszották a szerepüket, és jól átvertek, baszódjanak meg mindannyian! Nem is láttam, hogy ez lesz...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "Hé, ne káromkodj a Szentföld kapuja elôtt. Nem láttad, hogy ez lesz? Ez hízelgô: Átvertem a szigetvilág egyik leghíresebb intrikusát. A napló ötlete zseniális volt, nem gondolja?\nMeg kellett csalogatnom valami homályos helyre, a nyílt terepen való megölése botrányos lett volna, ön Philippe de Poincy közeli barátja, igazam van? Most nyom nélkül fog eltûnni, és senki sem fogja megtudni, hogyan.";
			link.l1 = "Tehát minden, amit Calhoun mondott nekem... hazugság volt?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "Egyáltalán nem. Tényleg ezen a helyen találtam szegény Archibaldot. Bár nem írt emlékiratokat, a naplót, amit a szobájában talált, az én kérésemre írta, kifejezetten önnek, Monseniour de Maure.\nA Catoche-foknál történt találkozásunk óta szemmel tartom önt. Ön volt az, aki elvitte a Két Megjelenés térképét don Diego holttestérôl? Ne tagadd, tudom, hogy te voltál.";
			link.l1 = "Az Igazság Ôrzôjérôl is tudsz?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "Ez egy hülye kérdés. Persze, hogy tudom. És azt is tudom, hogy nálad van a Fônök karma is. És hamarosan vissza fogod adni azokat a tárgyakat, amelyek nem hozzád tartoznak.";
			link.l1 = "Örülök, hogy nem ingadozol úgy, mint Don Diego. Értékelem az ôszinteséget és a közvetlenséget. Ha jól tudom, nálad van az iránytû, az Út Nyila?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "Haw-haw! Nos, ôszinték leszünk a végsôkig... Tényleg azt hiszi, uram, hogy olyan idióta vagyok, mint ön és Don Diego, hogy egy ilyen értékes tárgyat magammal hordok? Az iránytû a Jamaicán van, és még csak nem is Port Royalban, hanem egy olyan helyen, ahol senkinek eszébe sem jutna megnézni, és biztonságos zár alatt. De erre az információra nem lesz szüksége.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "Ha jól tudom, már el is temetett, Paterson úr? Ki merem jelenteni, hogy a macskának még egy élete van!... Hol vannak a tisztjeim?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "Ha jól tudom, már el is temetett, Paterson úr? Ki merem jelenteni, hogy a macskának még egy élete van!...";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "Aggódik a barátnôje miatt, kapitány? Az asszonya ott fekszik a bokrok között, lyukas homlokkal. Megfektette az utat önnek, és ön hamarosan csatlakozik hozzá. Mondom, milyen szép lány volt! Remélem, többször is megdugtad.";
				link.l1 = "C'est un fils de pute! Megfizetsz ezért, te bûnözô!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "A tisztjei már lefektették önnek az utat, Monsieur de Maure. Ott fekszenek a bokrok között. Hamarosan csatlakozik hozzájuk.";
				link.l1 = "Majd meglátjuk!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "Biztosra megyünk, hogy ez lesz az utolsó.";
			link.l1 = "Majd meglátjuk!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "Megnevettetsz. Egy ember egy egész csapat ellen! Na mindegy, elég a csevegésbôl... Célozzatok a muskétákkal! Tûz!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
