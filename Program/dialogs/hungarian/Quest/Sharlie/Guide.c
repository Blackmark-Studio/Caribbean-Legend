// гид
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
			dialog.text = "Kérsz valamit?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "Örömmel üdvözlöm a kolóniákon, uram! Engedje meg, hogy bemutatkozzam: "+GetFullName(npchar)+". A jó öreg otthonból érkezik?";
			link.l1 = "Jó napot, uram. A nevem "+GetFullName(pchar)+". Igen, most szálltam le a hajóról.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "Megláttam egy úriembert, és úgy gondoltam, segítenem kell. Az Újvilágnak megvannak a maga szabályai, és ha nem ismerjük ôket, az sokba kerülhet. A rangos embereknek össze kell tartaniuk. Rengeteg csôcselék van itt, akik egy maréknyi érméért eladnának téged\n"+
			"Megmutathatom a környéket, és megadhatom az alapokat?";
			link.l1 = "Nagyon kedves öntôl, monsieur! Örömmel megteszem.";
			link.l1.go = "guide_2";
			link.l2 = "Köszönöm, uram, de megtalálom a saját utamat.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "Ahogy óhajtja, Monsieur. Mindenesetre, örültem a találkozásnak. A tiszteletreméltó urak ritka vendégek itt. Sok szerencsét kívánok!";
			link.l1 = "Neked is, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "Kitûnô! A karibi városok ugyanazt az elrendezést követik. Tanulja meg Saint-Pierre-t és minden más kikötônek lesz értelme.";
			link.l1 = "";
			link.l1.go = "guide_tavern";		
		break;
		
		case "guide_tavern":
			dialog.text = "Kocsma - a kikötô központja. Szerezz ágyat, rumot, pletykát, és bérelj matrózokat vagy tiszteket. Kártyázhatsz, felvehetsz munkát, vagy üzletelhetsz csempészekkel és kincses térképek árusítóival.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Piac. Szükséged van ellátmányra? A kovácsnál pengék, páncélok és lövedékek vannak; a gyógynövényes asszony tonikokat árul. A cigányok és a szerzetesek bûbájokkal kereskednek, az ócskavas-kereskedô pedig apróságokat kínál azoknak, akik tudnak kézmûveskedni.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Bordélyház. Semmi sem dobja fel jobban a hangulatot, mint egy ügyes hölgy társaságában eltöltött idô. Ha az életerôd alacsony, ugorj be, és hagyj itt egy új embert.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Bank. Kölcsönvehetsz vagy befektethetsz pénzt, pezót válthatsz dublonnákra, és ez a legjobb hely ékszerek eladására.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Börtön. Kevés igazi gazember van bent - leginkább csavargók. Akarsz tôlük munkát? Beszéljen a parancsnokkal; egy kis kenôpénzért kinyílnak a cellák.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Kormányzói palota. Kereskedôk és kapitányok járnak ide komolyabb üzleteket kötni. Tartsd barátságosan a kormányzót - az ô szava határozza meg, hogyan bánik veled a népe.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "Téged is megtartalak, barátom?";
			link.l1 = "Monsieur, a bátyámat jöttem megkeresni. Azt mondják, Saint-Pierre-ben van. Egy fontos ember, a kormányzó biztosan ismeri ôt...";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "Á, értem. A kormányzó Jacques Dyel du Parquet. Biztos vagyok benne, hogy gyorsan fogadni fogja.";
			link.l1 = "Kit kérdezhetek még? Inkább nem zavarnám Ôexcellenciáját azonnal.";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "Ha a bátyja ismert Martinique-on, kérdezze meg a városlakókat - valaki tudni fogja. És a neve?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "Hallottam a nevét, bár még sosem találkoztunk. Kérdezôsködjön - vagy menjen egyenesen a kormányzóhoz. Sok szerencsét, monsieur. Még beszélünk!";
			link.l1 = "Köszönöm, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "Á, már megint te vagy az! Hallom, hogy betetted a lábad a lovagok' erôdítményébe. Nyilvánvalóan magas körökben mozogsz. Megtaláltad a bátyádat?";
			link.l1 = "Megtaláltam... bizonyos értelemben.";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Bocsásson meg, de nem hallok sok örömöt ebben a válaszban...";
			link.l1 = "Ez igaz. Reméltem, hogy a következô hajóval haza tudok hajózni, de a sors kinevetett. Itt ragadtam - ki tudja, meddig -, és ráadásul meg kell tanulnom tengerésznek lenni.";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "Nem vagyok meglepve. Elterjedt a híre az Ulysses-en tett utazásodnak. Ne csüggedjen - egy hajó tulajdonlása és a kapitányi cím nem kis dolog. Tervezi, hogy vesz egy hajót, ugye?";
			link.l1 = "Igen, a fenébe is, muszáj. De nem tudom, hol van a hajógyár, hogyan kell hajózni, vagy hogyan kell felvenni a pénzt. Semmit sem tudok!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "A pénz hiányzik, de minden másban a rendelkezésére állok. Folytassuk a túrát?";
			link.l1 = "Igazad van, a tudás hatalom.";
			link.l1.go = "guide_25";
			link.l2 = "Köszönöm, uram, de innen már boldogulok.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "Örömömre szolgál. A pénzeszközökért beszéljen a város költöztetôivel - talán a bolti kereskedôvel\n"+
			"Sok szerencsét, "+pchar.name+"- legyen bátor, és sikerülni fog.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "Akkor kövessetek! Elôször is, a hajók.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Hajógyár. Itt vásárolhatsz vagy javíthatsz hajókat. Többnyire kis hajótestek, de néha-néha felbukkan egy-egy jó hajó. Ágyúk és díszes vitorlák is.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "Móló - az ajtód a tengerre. Ha egyszer már van hajód, a hajód itt vár. Egyelôre bérelj fel egy navigátort, egy tiszttartót és egy ágyúöntôt - ôk megkönnyítik az életed a tengeren.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Kikötôiroda. Itt kötheted ki a hajódat, vagy vehetsz fel becsületes munkát - teherszállítás, kíséret, postai szállítás. Minél több munkát végzel, annál jobb a fizetés.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Bolt. A kapitányok ide járnak élelemért, rumért, gyógyszerért, lôporért és lôszerért. Ha ez hiányzik, keress csempészeket a kocsmában. Jó pénztáros nélkül a kereskedelem idô- és pénzpocsékolás.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Kapuk a vadonba. Veszélyesek, de hasznosak, ha erôdökbe akarsz eljutni, kincsre vadászni, vagy átkelni egy másik településre.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "Nem minden település fogadja szívesen az idegeneket. Ha nem akarod megvárni az éjszakát, húzz fel egy másik zászlót a tengeren, majd hagyatkozz a lopakodásra - vagy vegyél kereskedelmi engedélyt.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "Jól figyelsz, barátom. Van kedved egy kis szórakozáshoz? Egy gyakorló párbaj a kapukon túl.";
			link.l1 = "Persze, hogyne! Tökéletesen hangzik.";
			link.l1.go = "guide_47";
			link.l2 = "Köszönöm, uram, de innen átveszem.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "Barátom, gondolom, nem idegen önnek a vívás?";
			link.l1 = "Ha! Már átéltem egy deszkás akciót, és még...";
			link.l1.go = "guide_50";
			if (FindCharacterItemByGroupWithout_knife_03(pchar, BLADE_ITEM_TYPE) == "")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Kitûnô. Mehetünk?";
			link.l1 = "Táncoljunk!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "Te... te egy olyan ember vagy, aki tudja, hogyan kell tartani a kardját. Szép munka, Monsieur. Több gyakorlásra van szükséged, de megvan benned a lehetôség, hogy igazi kardforgatóvá válj.";
			link.l1 = "Nagyon szépen köszönöm. És most?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "Még több gyakorlás, azt mondja? Komolyan mondod? Elegem van ebbôl a lekezelô hangnembôl, mióta betettem a lábam erre a nyomorult helyre!";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Sokkal jobb! Látod, csak koncentrálnod kell. Több gyakorlásra van szükséged, egy nap rendes vívó leszel.";
			link.l1 = "Nagyon szépen köszönöm. És most?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "Nyertem, Monsieur. Mozogj gyorsabban, hárítsd a szúrásaimat, ugorj hátra. Visszavágó?";
			link.l1 = "Oui! Nincs kegyelem, Monsieur!";
			link.l1.go = "guide_56";
			link.l2 = "Nem, elég volt. Fejezzük be a leckét. Most mi lesz?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "Ismét nyertem, "+pchar.name+"! Ne veszítsd el a kezdeményezôkészséged! Kapd el a találataimat, cselezd ki ôket. Ha látod, hogy keményen fogok ütni - ugorj el vagy parálj, ne csak védekezz. Megint!";
			link.l1 = "Gyerünk, Monsieur, ezúttal megverem magát!";
			link.l1.go = "guide_56";
			link.l2 = "Nem, elég volt. Fejezzük be a leckét. Most mi lesz?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "Sokat kell még tanulnod, "+pchar.name+". Ne aggódj, még sok idôd van arra, hogy elsajátítsd a vívást. De légy óvatos, ne kockáztass, amíg nem tudod, hogyan kell tartani a fegyvert.";
			link.l1 = "Megfontolom, Monsieur, de azt kell mondanom, hogy önnek túl nagy szerencséje volt! Ez az átkozott hôség... az egyetlen ok, amiért nem vertem ki magából a poklot. Merde, fejezzük be a vívóleckét. Most mi lesz?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "Itt az ideje, hogy búcsút vegyünk, Monsieur. Örömömre szolgált. Remélem, hogy az elôadásom és a képzésem jót tett Önnek, és hasznosnak bizonyul a jövôben. Talán egyszer még találkozunk.\nA pénzrôl pedig, amire szüksége van - beszéljen városunk fontos embereivel. Látogassátok meg az összes helyet, amit ma mutattam nektek, és beszéljetek a tulajdonosaikkal. Kérdezôsködjetek. Sétálj el a dzsungelbe és az erôdbe. Keress munkát, vagy... nos, nem vagyok pap vagy bíró, nézz be az emberek házaiba, és nézd meg, milyen csecsebecséket találsz a nyitva hagyott ládáikban. Csak akkor tedd, amikor hátat fordítanak, különben az ôrök elkapnak.\nSok szerencsét, "+pchar.name+", erôs az érzésem, hogy benned van az igazi nagyság szikrája. Tegyél meg mindent, hogy lángra lobbanó tûzzé gyújtsd!";
			link.l1 = "Köszönöm, Monsieur. Részemrôl a megtiszteltetés. Isten éltessen!";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "Tartsa a száját, Monsieur! Nem tûröm tovább ezt a szemtelenséget. Megértem azonban, hogy az új környezetre reagál, ezért ezúttal megbocsátom a kirohanását. De mostantól vigyázzon a szavaira. Viszlát, Monsieur de Maure.";
			link.l1 = "Ne vegye sértésnek, Monsieur Valinnie. Ha most a Louvre-ban lennénk, vigyázna a hangjára! Itt az ideje, hogy egy provinciát megleckéztessünk. Védekezzen!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Guide_DlgExit_64");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string FindCharacterItemByGroupWithout_knife_03(ref chref, string groupID)
{
	ref refItm;
    string resultItemId;

	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(refItm.id == "knife_03") continue;
		if (groupID == BLADE_ITEM_TYPE)
		{
			resultItemId  = refItm.id;
		}
	}
	
	if (resultItemId != "")
	{
        return resultItemId;
	}

	return "";
}