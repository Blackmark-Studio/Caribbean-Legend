// Чад Каппер - боцман Акулы и тюремщик
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Kérsz valamit?";
			link.l1 = "Nem, semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "Nos, nos, nos... Szóval te vagy a titokzatos tolvaj? Hm... Nem úgy nézel ki, mint egy szerencsétlen tolvaj.";
			link.l1 = "Figyeljen, uram, téved. Újonnan jöttem ide, honnan tudhattam volna, hogy a raktér, ahol az emberei elfogtak, az ön privát zónája?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "Tényleg? Szép próbálkozás, haver... Akkor honnan jött ide?";
			link.l1 = "Mainbôl... Egy furcsa szobron keresztül. Én magam sem tudom, hogy magyarázzam el, mi történt.";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "Szobor? Ha-ha! Vicces fiú vagy, nem igaz... Rendben, majd én magam elmagyarázom neked: átúsztál a hajón lévô lyukon, és be akartál lopózni a raktárunkba. Hogyhogy nem ismerem fel az arcodat? Ismerem az összes Rivadót...";
			link.l1 = "Milyen Rivados? Nem tudom, mirôl beszélsz! Figyelj, egy órája jöttem ide...";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "Ne kiabálj, nem vagyok hülye. Igen, hallottam már eleget a szoborról szóló baromságaidat, és elég mulatságosnak találom. Kurvára viccesnek találom. Mi lenne, ha együtt nevetnénk rajta? Ha-ha-ha!... Miért nem nevetsz? Ez egy jó vicc volt... Rivados. De a vicceknek már vége. Hagylak a börtönben rohadni, haver.";
			link.l1 = "Nem vagyok Rivados! A nevem Charles de Maure!";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "Elsô alkalom, mi? Hm... talán igazat beszélsz. Válaszolj, te is közülük való vagy?!";
			link.l1 = "Esküszöm neked, soha nem hallottam még ezt a nevet, nem tartozom közéjük!";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "Tényleg? Hát persze. Bizonyítsd be. Menj le a földszintre, ott egy Rivados ül egy ketrecben. Ô egy veszélyes varázsló. Öld meg, csak akkor gyôzhetsz meg. Azt is elfelejtem, hogy illegálisan behatoltál a raktárunkba\nSo? Készen állsz? Ne félj, a varázsló fegyvertelen és gyenge. Hát, lehet, hogy porrá változtat valami varázslattal, mint amilyen a San Augustine raktárába juttatott...";
			link.l1 = "Ha láttad volna azt a varázslatot mûködés közben, akkor nem lennél ilyen szkeptikus. Kétlem, hogy egyáltalán túlélted volna...";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "Elég a beszédbôl! Megcsinálod vagy sem? Ha igen, akkor fogd ezt a bozótvágó kést és intézd el a varázslót. Különben életed hátralévô részét egy ketrecben fogod tölteni. Megértetted?";
			link.l1 = "Két rossz közül a kisebbik rosszat választom. Add ide a macsétát.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "Jó fiú. Fogd, menj és öld meg a feketét. A ketrece nyitva van. Ne próbálkozz semmi hülyeséggel, nem fogunk habozni, hogy végezzünk veled, ha csak eszedbe jut! Most menjetek!";
			link.l1 = "Miért? Miért? Attól féltek, hogy kibelezlek titeket ezzel a rozsdás fémszarral?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "A türelmem fogytán van. Menjetek a raktérbe, és tegyétek, amit mondtam!";
			link.l1 = "Rendben, rendben, nyugi. Elmegyek...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "Próbára teszed a türelmemet, te szemétláda! Nem akarsz felbosszantani...";
			link.l1 = "Jól van, jól van, nyugi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "Megölted azt a néger varázslót? Jó... Örülök. Bebizonyítottad, hogy nem vagy Rivados.";
			link.l1 = "Mikor szabadulok végre ebbôl az átkozott kádból? Azonnal találkoznom kell Sharkkal.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "Találkozni fogsz vele, persze... A pokolba vezetô úton fogsz vele találkozni!";
			link.l1 = "Micsoda?!";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Ha! Ezt nézd meg. Mit keresel itt a börtönömben?";
			link.l1 = "A neved Chad Kapper, ugye? A nevem "+GetFullName(pchar)+" és Shark Dodson nevében vagyok itt. Ô adta nekem a kulcsokat.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Az admirálistól? Hm, értem. Maga az új kifutófiúja?";
			link.l1 = "Mutasson némi tiszteletet, uram. Nem szolgálok senkit, sem Sharkot, sem magát, és nem tûröm az ilyen beszédet.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Ha-ha, kedvellek, haver! Felejtsd el, amit mondtam... Szóval, mi a dolgod itt?";
			link.l1 = "Shark parancsot adott Chimiset kiszabadítására, itt van bebörtönözve.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "A Rivados varázsló? Hm. Ez furcsa, nagyon meglepôdtem, hogy ezt hallom...";
			link.l1 = "Cápa parancsot adott. Békét akar kötni Rivadosszal.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "A-ah, most már értem. Rendben, küldök egy embert Rivadosba. Idejönnek és elviszik a bolondjukat.";
			link.l1 = "Miért nem tudod csak úgy elengedni?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Megtehetném, de ez túl veszélyes lenne számára. Chimiset errefelé ismerik, az élete semmit sem ér majd, ha egyszer rálép az 'Esmeralda' - ellenségei, a narválok területére. Nincs más út a Tartaroszból, nem hagyhatjuk, hogy az öreg körbeússza a szigetet!\nÉs ha valaki megöli, Rivados minket fog hibáztatni, pontosabban engem! Látod, nem akarok olyan problémákat, amiket el lehet kerülni. Ezért csak a klánja harcosainak védelme alatt fogom kiengedni. Talán te magad szeretnél beszélni Chimiset-tel? Ô egy vicces típus...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "Már beszéltem vele, tényleg furcsa ember. Mindegy, mennem kell. Viszlát, Chad!";
			else link.l1 = "Ez volt a szándékom. Megyek és beszélek vele.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Küldök egy futárt Rivadosba, és elviszik a varázslójukat. Ne aggódj, pajtás, elmehetsz.";
			link.l1 = "Rendben.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "... Biztos vagyok benne, hogy már kinyitotta a hordót. Ez a kedvenc whiskyje, átkozott ír. Hamarosan vége lesz, annyi arzént tettem bele, hogy egy egész csordát megölhetnék vele...";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "Aha... A fenébe, mit keresel itt? Tûnjetek el!";
			link.l1 = "Már régóta kerestelek, te méregkeverô! Ez furcsa, nem látom a küklopszot. Te akartad elfoglalni Shark helyét, igaz?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "Ha-ha, Shark már biztos halott! És te is hamarosan követni fogod, kém!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_2":
			dialog.text = "... ez egy pokoli jó ital lesz. Az átkozott ír már régóta álmodik errôl a whiskey-rôl, úgyhogy egy pillanat alatt elnyeli az egészet. Hol van az arzén? Önts még belôle, csak a biztonság kedvéért... Aztán Fazio barátunk átadja ezt a hordót az admirálisnak, mint a Narwhals ajándékát, ha-ha! Igazam van, kedves Giuseppe? Élni akarsz?\nArgh! Nézd, vendégeink vannak! Mit akarsz, seggfej? Tûnj el, mielôtt elkapunk!";
			link.l1 = "A terved kudarcot vallott, Kapper. A nyomodban jártam, és tudom, hogy te és a haverod, a Küklopsz mit fogtok csinálni. Dobd ki az arzént! Nem fogod megmérgezni Cápát!";
			link.l1.go = "Aeva_attack_3";
		break;
		
		case "Aeva_attack_3":
			dialog.text = "Á, nyomozó! Hát, akkor te halsz meg elôbb! Fiúk, fegyverbe!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
