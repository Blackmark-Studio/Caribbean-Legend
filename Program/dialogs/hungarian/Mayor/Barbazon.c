// Жак Барбазон в Ле Франсуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
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
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            dialog.text = NPCStringReactionRepeat("Van valami mondanivalója? Nincs? Akkor tûnj el innen!",
                         "Azt hiszem, világosan fejeztem ki magam, ne idegesítsen tovább.", "Bár világosan fejeztem ki magam, te továbbra is idegesítesz!",
                         "Rendben, kezdek belefáradni ebbe a bunkóságba.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Én máris elmegyek.",
                                               "Persze, Jacques...",
                                               "Sajnálom, Jacques...",
                                               "Aúú...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Megôrültél? Mészárost akartál játszani? Minden kalóz haragszik rád, fiú, jobb, ha elhagyod ezt a helyet...", "Úgy tûnik, hogy megharagudtál, fiú. Ki akartad nyújtani a kezed egy kicsit? Ne vedd sértésnek, de nincs itt semmi keresnivalód. Tûnj innen!");
				link.l1 = RandPhraseSimple("Figyelj, én helyre akarom hozni a helyzetet...", "Segítsen megoldani ezt a problémát...");
				link.l1.go = "pirate_town";
				break;
			}
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "Beszélnem kell veled, Jacques... Négyszemközt.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "Saint Martinból jöttem, Jacques...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "És mikor hagyod abba az ugatást és kezdesz el úgy beszélni, mint egy férfi, Jacques? Nem számítottál rám?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "A foglyod miatt vagyok itt.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Helló, Jacques, a küldetésed miatt vagyok itt.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "A foglyod miatt vagyok itt.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Úgy hallottam, hogy a foglyokkal kapcsolatos üzletet folytatsz...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + "! Ezúttal mire van szükséged?",
                         "Elfelejtettél valamit mondani? Hallgatlak.", "Meddig fog ez tartani... Ha nincs semmi dolgod, akkor ne zavarj másokat!",
                         "Arra kértél, hogy legyek udvarias. De én ugyanezt követelem tôled!", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Semmiség. Csak egy látogatás.",
                                               "Semmi...",
                                               "Rendben...",
                                               "Igazad van. Sajnálom.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Megôrültél? Mészárost akartál játszani? Minden kalóz haragszik rád, fiú, jobb, ha elhagyod ezt a helyet...", "Úgy tûnik, hogy megharagudtál, fiú. Ki akartad nyújtani a kezed egy kicsit? Ne vedd sértésnek, de nincs itt semmi keresnivalód. Tûnj innen!");
				link.l1 = RandPhraseSimple("Figyelj, én helyre akarom hozni a helyzetet...", "Segítsen megoldani ezt a problémát...");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "A foglyod miatt vagyok itt.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Hello, Jacques, a küldetésedrôl van szó.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "A foglyod miatt vagyok itt.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Úgy hallottam, hogy a foglyokkal kapcsolatos üzletet folytatsz...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "Tudod, hogy kockázatos engem zavarni? Rendben, figyelek rád.";
			link.l1 = "Van egy kis adósságom. Nagy adósságom van. Hamarosan fizetnem kell, és nincs nálam pénz. A kedves emberek azt suttogták, hogy neked van tehetséged a tervezgetéshez, és mindig tudod, hol lehet megragadni egy nagy jackpotot...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "Figyelj, fiú! Én vagyok Jacques, a Gyermekember, csak azok számára, akik hûségesek hozzám. Másoknak Barbazon vagyok, és néha maga Lucifer. Honnan tudhatnám, hogy megbízhatok benned?";
			link.l1 = "Próbáld ki. Esküszöm, hogy nem fogod megbánni!";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Hm... Gondolom, tudod, mit tesz Jacques, a Gyermekes azokkal, akik megcsalják ôt, ugye? Akárhogy is, nem akarlak összezavarni szörnyû részletekkel. Van egy kis küldetésem. Ha sikerül, akkor minden anyagi gondja megszûnik.";
			link.l1 = "Ne kételkedjen bennem, sokszor voltam már harcban és...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Fogd be és figyelj rám! Néhány héttel ezelôtt egy holland járôr elkapta az egyik alkalmazottamat Saint Martintól nem messze. Holland selymet szállított nekem. Ez nagyon ritka, a hollandok csak kis tételeket hoznak ide a Társaság haditengerészetének szükségleteire.\nSikerült tehát hat bála selymet harapnom, és Simon Morelnek kellett volna elhoznia nekem a brigantiján 'Sóskutya', , de véletlenül szembejött egy holland járôrrel. Vagy nem véletlenül. Ezt Morel navigátora mondta, aki elmondta nekem, hogy ô volt az egyetlen, aki túlélte a harcot.\nÔ adta nekem Morel hajónaplóját is, ami megerôsíti a történetet. A napló szerint Morel egy menekülési kísérlet során eldobta a selymet. Furcsa, nem igaz? A selyem könnyû. El kellett volna dobniuk az ágyúikat, amúgy sem volt esélyük az ôrjárat ellen.";
			link.l1 = "Valami nagyon nem stimmel itt.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "Minden lehetséges. Sok bátor ember dolgozik nekem, és sokkal kevesebb okos. Ne vedd sértésnek, heh. Ellenôriznie kell a helyet, ahol Morel megszabadult a rakománytól. A kapitány naplója szerint 21 fok 10' észak és 61 fok 30' nyugat.\nA hollandok parafa rudak köré tekerik a selymet, így a báláknak még mindig a víz felett kell maradniuk. Hat bálának kell lennie. Azonnal vitorlát bontani, az idôzítés kritikus.";
			link.l1 = "Már úton vagyok!";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "Remek! Megtaláltad a selymet?";
			link.l1 = "Igen, hatot, ahogy mondtad.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "Igen. De több volt, mint amennyit mondtál, kilenc, nem hat. Mindet idehoztam, a te feladatod, hogy kitaláld, hogyan történhetett ez.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "Rossz válasz. Kilenc bálának kellett volna lennie. És ha hatot megtaláltál, akkor a többit is meg kellett találnod. Szóval vagy patkány vagy csak egy lusta idióta. Tartozol nekem három bála selyemmel és még hárommal, mint.. 'morális kárpótlás' azért, hogy megpróbáltál átverni.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "Micsoda okostojás! Ezt megjegyzem. Itt van a selyem, és felejtsük el az én hibámat.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "Nekem azt mondták, hogy hat bála volt, nem egy bálával több. Odaadtam neked mindent, amit találtam, és leszarom a gondolataidat. Nincs több selymem.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "Jól van. Remélem, hogy ez nem fog még egyszer elôfordulni, mert egy fontos feladatot akarok adni neked. Mennyi pénzt akarsz keresni?";
			link.l1 = "A pénzt mindig szívesen fogadom, egyelôre ötvenezer pezó is megfelel.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "Ó, most már így beszélsz! Ezt nem fogod megúszni. Figyelmeztettelek - ne próbálj átverni, az istenit! Ôrség! Egy kibaszott patkány van a rezidencián!";
			link.l1 = "Basszus!";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "Szép munka. Ellenôriztem a kapzsiságodat, és átmentél a teszten. Kilenc bála lehetett. Az egyik a tiéd. Most már komolyan beszélhetünk. Mennyi pénzre van szükséged?";
			link.l1 = "A pénzt mindig szívesen fogadom, egyelôre ötvenezer pezó is megfelel.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "Van egy lehetôséged, hogy még többet keress. Egy komoly ember megkért, hogy keressek egy hozzád hasonló megbízható fickót egy kényes és veszélyes küldetésre. Ez az ember nagyon gazdag, és ennek megfelelôen megjutalmaz téged, ha nem hagyod cserben.";
			link.l1 = "Én készen állok.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "Jól van. Most hallgassa meg. Meg kell találnod az ügynökét, akit úgy hívnak 'Knave'. Ô a polák kapitánya 'Marlin', ennyit tudok róla. Kapsterville-ben találjátok meg. A jelszó 'a vadászat megkezdôdött'. Ô majd megmondja, mit kell tenned. Nem tartozol nekem semmivel. Csak segíteni akarok neked. Ha elég szerencsés leszel, akkor újra találkozunk.";
			link.l1 = "Köszönöm a segítségedet. Már úton vagyok!";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "Micsoda?! Kitépem a...";
			link.l1 = "Nem fogsz, Barbazon. Lássuk a kártyáinkat! Jan Svensonnak dolgozom. Felfedtem az összeesküvésedet Jackmannel. Mindent tudok, hogy mit terveztél és milyen szerepet játszottál. Jackman és a testvére halottak, az elsô megölte Blaze Sharpot, és ez meghatározta a sorsát, a második nem volt elég beszédes, attól tartok...";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "A francba! Tyrex ezt soha nem fogja megbocsátani nekem, de azért mégis...";
			link.l1 = "Ne csinálj semmi hülyeséget, Jacques. Tudtam, hogy nem lesz könnyû beszélgetés, ezért megôriztem magam. Nézz ki az ablakon... a kunyhódat körülveszik a muskétásaim. Az embereim körülveszik a faludat, és egy csapásmérô csoport áll a kapuk elôtt. Mészárlásba akarsz kezdeni? Könnyen megteheted!";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "A fenébe veled! Mit akarsz?";
			link.l1 = "Nem fogsz hinni nekem, Barbazon, de én csak annyit akarok... Békét! Békét akarok. Ezért nem fogom elmondani Tyrexnek, hogy részt vettél az ellene irányuló összeesküvésben. De csak akkor, ha megteszed, amit én akarok...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "Mit akarsz tôlem? Pénzt? Mennyit?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Ó, nem, hagyd ezt a te agyatlan ügynökeidre! Nekem valami másra van szükségem. Szükségem van a szavazatára Steven Dodsonra.";
			}
			else
			{
				link.l1 = "Ó, nem, hagyja ezt az agyatlan ügynökeire. Valami másra van szükségem. Szükségem van a szavazatára Marcus Tyrexre.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "És Steven Dodson a mi oldalunkon áll.";
			else sTemp = "";
			dialog.text = "Dodson Dodson a mi oldalunkon áll. Hadd gondolkozzak... és mi van, ha nemet mondok?";
			link.l1 = "Akkor egyedül fogsz állni. Teljesen egyedül. Svenson, Tyrex és Sólyom ellened fog menni."+sTemp+"Én csak megmutatom nekik a Knave levelét, Jackman testvérét, és az én szavamban is megbíznak. Na, mit gondolsz, meddig fogsz ezek után a kényelmes helyeden ülni?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "Sólyom? Életben van?!";
			link.l1 = "Hát ô. Megmentettem ôt a Jackman által állított csapdából. Így lesz Jákob legközelebbi barátja a véres ellensége. És én is csatlakozom hozzájuk, ezt ne feledd, Barbazon.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "Jackman nem a barátom! A francba veled! Sarokba szorítottál!";
			link.l1 = "Ez badarság. Szavazz arra az emberre, akire mondtam, és semmi sem fog változni a számodra. Már mondtam neked, Jacques, békét akarok. Minden báró megutáltathatnám magát, de nem fogom... még nem.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "Jól van, rendben. Rendben. A szavamat adom. Tessék, fogd a kôszilánkomat, szükséged van rá, igazam van?";
			link.l1 = "Pontosan. Örülök, hogy megegyeztünk, Jacques. És vidd el 'Knave' levelét, mint egy édes emléket. Vagy még jobb, ha elégeted, nem akarod, hogy megtalálják. Ó, és még egy utolsó dolog...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Még egy utolsó dolog?! Mit akarsz még tôlem?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "Hadd emlékeztessem önöket valamire. Nem is olyan régen a kutyádat, Ignacio Marcót küldted, hogy megöljön engem. Én voltam az, aki megölte. Én voltam az, aki eltemette a tervét, hogy kifosszon egy spanyol arany gályát. Én voltam az, aki elküldte a barátaidat a Saint Martin melletti spanyol csapdába. A nevem Charlie Prince! Most már végeztünk, Jacques, és légy udvariasabb velem, ha legközelebb találkozunk. Hidd el, 'boy', még találkozunk, és gondolom, nem is egyszer.";
				link.l1.go = "terrax_8_1";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Hadd emlékeztessem önöket valamire. Nem is olyan régen a kutyádat, Ignacio Marcót küldted, hogy megöljön engem. Én voltam az, aki megölte. Én voltam az, aki eltemette a tervét, hogy kifosszon egy spanyol arany gályát. A nevem Charlie Prince! Most már végeztünk, Jacques, és légy udvariasabb velem, ha legközelebb találkozunk. Hidd el, 'boy', még találkozunk, és gondolom, nem is egyszer. Ne felejtsd el, hogy minden kalózbáró az én oldalamon áll. Isten veled, Barbazon...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "Legyél udvariasabb velem, ha legközelebb találkozunk. Hidd el, 'boy', még találkozunk, és gondolom nem is egyszer. Ne felejtsd el, hogy minden kalózbáró az én oldalamon áll. Isten veled, Barbazon...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_8_1":
			dialog.text = "";
			link.l1 = "Ne felejtsd el, hogy minden kalózbáró mellettem áll. Isten veled, Barbazon...";
			link.l1.go = "terrax_9";
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetCitizenType(sld);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			bDisableFastReload = false;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Azt hiszed, hogy csak egy foglyom van itt? Nevezd meg.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Itt van?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Itt volt. Eladtam annak a barbadosi ültetvénytulajdonosnak - Bishop ezredesnek, amikor egy hete itt járt.";
				link.l1 = "A fenébe...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Á, végre. Arra gondoltam, hogy eladom annak a barbadosi ültetvényesnek, aki egy-két héten belül itt lesz... Van váltságdíja?";
				link.l1 = "Nézze, van egy kis probléma... Valójában, nincs annyi pénzem. De kész vagyok dolgozni.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150.000 pezó. Hol kaphatom meg?";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Túl lassú voltál... És miért érdekel téged? Csak a rokonaival tárgyaltam.";
			link.l1 = "Ôk kértek meg, hogy jöjjek ide.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Hát, elkéstél. Nem tehetek semmit.";
			link.l1 = "Figyelj, mennyiért adtad el ôt, ha nem titok?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, ez nem az. De nem mondom meg... Nevetni fogsz, ha megteszem. Ha-ha-ha-ha-ha! Viszontlátásra.";
			link.l1 = "Viszlát.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "Nos, " + pchar.name + ", tudod, ez nem így mûködik. Gyere vissza a pénzzel, és megkapod a gyengébbik feledet, ha-ha.";
				link.l1 = "Jól van. Viszlát.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Nocsak, nocsak... Van egy kis dolgom... Nem is tudom, hogy kezdjem. El kell süllyesztenem egy kalózt, aki átlépte a határt.";
				link.l1 = "Nem lehet egyszerûen megölni a dzsungelben?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Az üzlet nem így mûködik, tudod... Nem a halálára van szükségem, hanem arra, hogy megtanítsak néhány embert, hogy ne vegyék el a részemet a zsákmányból. De ha a cápákat eteti, nem leszek mérges.";
			link.l1 = "Miért nem küldöd utána a saját embereidet?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Nos, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " meggyôzött néhány kalózt, hogy a zsákmányuk egy részét a mi rejtekhelyünkön tartják, nem messze " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Két hajójuk '" + pchar.GenQuest.CaptainComission.ShipName1 + "' és '" + pchar.GenQuest.CaptainComission.ShipName2 + "' nemrég vetett horgonyt és elhajózott " + sLoc + ". Most már érted, miért nem bízhatom az embereimre ezt a munkát?";
			link.l1 = "Én igen. Mennyi idôm van?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12-15 nap, nem több, nekem fontos, hogy ne jussanak el a rejtekhelyre, különben ostobaság lenne elsüllyeszteni ôket értékes rakománnyal. Ebben az esetben jobb lenne, ha ide hoznák...";
			link.l1 = "Rendben, én benne vagyok. Megpróbálom elkapni ôket.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Ne aggódjatok. Az embereim majd átadják a hajódnak. És miért érdekel téged?";
			link.l1 = "Nem érdekel. A rokonai kértek meg, hogy szállítsam le.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Á, rendben van. Már majdnem sajnáltam, hogy ilyen alacsony árat adtam az emberedért. Ha-ha-ha-ha-ha-ha! Viszontlátásra.";
			link.l1 = "Viszlát.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Szóval, , " + GetFullName(pchar) + ", elsüllyesztetted a haverjaimat? He-he-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nem. Nem sikerült elkapnom ôket. És nem találkoztam velük, amikor visszatértem.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Én igen. Elküldtem ôket, hogy etessék a cápákat.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "A francba! Találkoztál velük vagy sem, most már mindegy! És mi lesz a következô javaslatod?";
			link.l1 = "Talán van egy könnyebb munkád számomra?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Figyelj, "+ NPChar.name +", csökkentsd a fogoly árát...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nem.";
			link.l1 = "Akkor viszlát...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Hozd le az árat?! Épp most vesztettem el a készletemet a hozzá nem értésed miatt! És most felemelhetem az árat! Elviheted 200.000 pesoért, ha akarod, vagy elhúzhatsz innen a pokolba.";
			link.l1 = "Ez túl drága... Viszlát...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "A francba, vedd el az érméidet.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Elviheted ezt a gyengét...";
			link.l1 = "Ég veled!";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Szép munka! Fogd a gyengédet és sok szerencsét.";
			link.l1 = "Köszönöm. Viszlát.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Elhozta a váltságdíjat"+ GetSexPhrase("","la") +"? Mert én nem vicceltem, amikor mondta, hogy eladom az ültetvényeseknek.";			
			link.l1 = "Figyelj, "+ NPChar.name +", a helyzet a következô... Amúgy nekem nincs ilyen pénzem. De hajlandó vagyok"+ GetSexPhrase("","és") +" megoldani.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150000 pezó. Hol kaphatom meg?"
				link.l2.go = "CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Elhoztad a pénzt? Nem vicceltem azzal, hogy eladtam azt az embert az ültetvénynek.";			
			link.l1 = "Nincs rá pénzem, "+ NPChar.name +", de dolgozom rajta.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150.000 pezó. Hol kaphatom meg?"
				link.l2.go = "CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "És miért érdekel téged, hogy mit csinálok? Tudod, jobb lenne, ha elmennél...";
			link.l1 = "Tshh, nyugodj meg. Üzleti ügyben jöttem. A foglyodról van szó.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Á, rendben. Kiért akar váltságdíjat kérni?";
			link.l1 = "Várjon. Nem azért jöttem, hogy kivásároljam, hanem azért, hogy felajánljam, hogy megveszek egy foglyot. És nos, lesz lehetôsége váltságdíjat kérni érte.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. És miért van szüksége az ügynökségemre? Miért nem akarja közvetlenül magának megszerezni a pénzt?";
			link.l1 = "Ez elég kockázatos lenne számomra. Lehet, hogy gondjaim lesznek a hatóságokkal.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... akkor rendben. Nézzük meg. Ki a foglya?";
			link.l1 = "Ez a "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Értem... ez egy jó üzlet lenne, ha nem hazudik. Feltételezem, hogy fizethetek neked ezért az emberért "+iTemp+" pezót, vagy adhatok helyette valami érdekes információt. A választás a tiéd.";
			link.l1 = "Inkább a pezót választom. Elegem van ebbôl az üzletbôl...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Mesélj még. Biztos vagyok benne, hogy valami érdekeset fogsz mondani.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Akkor pénzt. Fogd ôket. Ez nem a te problémád. Hozza ide az eladás tárgyát.";
			link.l1 = "Már a város kapujának közelében kell lennie. Köszönöm. Nagyon sokat segítettél nekem.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Szívesen, hozzon még... Viszlát!";
			link.l1 = "Sok szerencsét...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Jó egy okos emberrel üzletelni. Most figyelj: néhány nap múlva a " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat") + " egy spanyol expedíció érkezik Mainból, értékes árukkal megrakodva. Várni fognak egy hajóra, amelynek elvileg a rakományt kell átvennie. Ha egy héten belül odaérsz, akkor lesz esélyed, hogy magadhoz vedd a rakományt.\nA te helyedben én már indulnék is a hajómhoz. És idehoznám a foglyot.";
					link.l1 = "Köszönöm. Köszönöm. Az áru szép kárpótlás lesz a fáradozásaimért. Az utasomnak pedig már a város kapujának közelében kell lennie. El fogjuk hozni hozzád.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Jó egy okos emberrel üzletelni. Most figyelj: körülbelül egy hét múlva egy spanyol brigantin '"+pchar.GenQuest.Marginpassenger.ShipName1+"' értékes árukkal megrakodva "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" elhajózik "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Ha sietsz, könnyen elkaphatod.\nMég mindig itt vagy? A helyedben én már elindultam volna a hajóm felé. És idehoznám a foglyot.";
					link.l1 = "Köszönöm. Köszönöm. Az áru szép kárpótlás lesz a fáradozásaimért. Az utasomnak pedig már a város kapujának közelében kell lennie. El fogjuk hozni hozzád.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rablás!!! Ez elfogadhatatlan! Készülj fel, "+ GetSexPhrase("fiú","lány") +"...", "Hé, mi a fenét csinálsz ott?! Azt hitted, hogy kirabolhatsz? Végeztél... ", "Várj, mi a fene? Vedd le a kezed! Kiderült, hogy te egy tolvaj vagy! Vége a sornak, te szemétláda...");
			link.l1 = LinkRandPhrase("A francba!", "Carramba!!", "A francba!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = "Takarodj innen!";
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne zavarj engem az olcsó dumáiddal. Legközelebb nem fog tetszeni az eredmény...";
        			link.l1 = "Megvan.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Vége, nincs beszéd.", "Nem akarok veled többet beszélni, úgyhogy jobb, ha nem zavarsz.");
			link.l1 = RandPhraseSimple("Ahogy kívánod...", "Hm, akkor jó...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Remélem, hogy több tiszteletet fogsz mutatni, és nem leszel többé bunkó?";
        			link.l1 = "Biztos lehetsz benne, Jacques, hogy megteszem.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "Megoldani a problémát? Érted, hogy mit tettél? Mindegy, hozz nekem egymillió pezót, és én meggyôzöm a srácokat, hogy felejtsék el a 'feats'. Ha nem tetszik az ötlet, akkor mehetsz a pokolba.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Rendben, kész vagyok fizetni.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Megvan. Elmegyek.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Jól van. Tekintsd magad újra tisztának. De remélem, hogy nem fogsz többé ilyen undorító dolgokat csinálni.";
			link.l1 = "Nem fogok. Túl drága nekem. Viszlát...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "part37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "parton47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "part48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "part25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "part21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "parton19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
