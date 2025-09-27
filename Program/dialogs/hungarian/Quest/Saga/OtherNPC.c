// диалог прочих НПС по квесту Саги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

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
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "Mit akarsz? Nem látod, hogy bánatomban vagyok! Tûnj el, mielôtt lerúglak a lépcsôn!";
			link.l1 = "Nos, vegyél magadnak egy nagyobb házat, ahol van lépcsô. Aztán majd beszélünk a lépcsôn való lerúgásokról, hôs...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Miért vagy ilyen ideges, Jimmy? Nincs rum nekem az egész rohadt életemben, ha nincs köze valami gyönyörû nôhöz! Csak egy nô képes arra, hogy egy ilyen vén tengeri farkas, mint te, megfenyegesse a régi barátaidat...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "Utálom az ilyen igényes embereket, mint te! Mindig te kapod a jobb szeletet a tortából. Nem hagyták, hogy megöljem az egyik felkapaszkodottat, ezért rajtad fogom kitölteni a haragomat!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_KillJimmy");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Igen?! Ismerlek én téged? Nem emlékszem rád, az istenit...";
			link.l1 = "Én vagyok az, "+pchar.name+"! Jól éreztük magunkat Blueweldben, miután majdnem kibelezted azt a szemtelen kabátos fickót. Mi is volt a neve? Már elfelejtettem... Mindenesetre a korvettjének ágyúira fütyülök, ha valaha is találkozom vele a tengeren!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "Arthurnak hívták! Arthur Donovan, a 'Arbutus' corvette kapitánya! Mocskos szemétláda! Tehát egyetértesz azzal, hogy közel álltam ahhoz, hogy az ördöghöz küldjem?";
			link.l1 = "Hát persze! Egyáltalán nem volt esélye, de a haverjai közbeléptek. Bocsásson meg nekik, nem akarták, hogy felakasszák egy tengerésztiszt meggyilkolásáért.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Argh! Bárcsak lenne egy hajóm! Ezt a fattyút könnyû megtalálni Antigua közelében... ha! Tartozom neked, ha a fenébe küldöd!";
			link.l1 = "Áll az alku, ha-ha! Egyébként, Rumba tényleg megéri a szenvedésedet?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "Mindenképpen! Soha nem találkoztam még nála jobb emberrel. De ô csak nevet rajtam. Mindenki azt a sellôt akarja. Néhány matróz titokban azt mondta nekem, hogy a mi Jacobunk keres egy olyan lányt, aki pont úgy néz ki, mint az én Rumbám. Ô is ôt akarja! Hogy követhetném most a parancsait?";
			link.l1 = "Maradj csendben, haver! A falaknak füle van... És mit gondolsz, miért keresi Jackman Rumbát?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Biztos, hogy ô az! Valami Hóhér Henriket és egy húszéves, szôke hajú, kék szemû lányt keres. Valami Gladys Chandler Belize-bôl lehet a gondnoka.";
			link.l1 = "Várj! Gladysnek más a vezetékneve. És ô az anyja!";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Jackman ravasz! Nem lehet felkészületlenül elkapni! Egy ideje már udvarolok Rumbának, és megtudtam, hogy Gladys pontosan húsz évvel ezelôtt ment hozzá Sean McArthurhoz. Azelôtt pedig Belize-ben élt. Az elsô férjét Pete Chandlernek hívták.\nSzegény Pete-et megölték egy részeg verekedésben. Azt mondják, hogy maga McArthur volt a felelôs, mivel akkoriban érzéseket táplált a duci Gladys iránt. A nô özvegy lett egy kisbabával a kezében. A gyerek nem sokkal élte túl az apját, és nem sokkal késôbb lázban meghalt.\nÉs alig pár hónappal azután, hogy Gladys és Sean felbukkantak Blueweldben egy lánnyal, akirôl azt állították, hogy McArthur lánya. Hogyan szülhetett Gladys ilyen hamar újabb gyereket? Tudja követni?";
			link.l1 = "Beszéltél errôl másnak is?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Még nem. Tartsd a szádat, vagy.... nos, ismersz engem!";
			link.l1 = "Igen, követem. Rohadt a nyelved, hogy bárkinek elmondja a titkait. Rumba jól tette, hogy elküldött, te fecsegô...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "Persze! Szûkszavú leszek! És most mennem kell. Viszlát, Jimmy.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "Mit... mit mondtál?!";
			link.l1 = "Nem fogod tudni elmondani senki másnak...";
			link.l1.go = "Jimmy_fight";
			pchar.questTemp.Saga.Jimmysecret = "true";
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			pchar.questTemp.Saga = "jackman";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "4_1");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "Te szörnyeteg!";
			link.l1 = "Magadban beszélsz, Mister?! Hol van Rumba?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "Milyen Rumba? Nekem nincs becenevû söpredék a hajómon. Ez egy angol hadihajó!";
			link.l1 = "Ne játszd a hülyét, Donovan. Tökéletesen érti, hogy kirôl beszélek. Hol van a lány? Hol van Helen? Válaszolj, te mocskos szemétláda...";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Helen? Az én hajómon nincsenek szárazföldi kurvák, te szarházi!";
			link.l1 = "Nincsenek szárazföldi kurvák? Nehéz elhinni, hiszen az egyikük épp elôttem áll ebben a pillanatban... Gondolom, nincs értelme folytatni a beszélgetésünket. Dögölj meg, te szánalmas féreg!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Kapitány, átkutattunk minden kabint és a raktérben, ahogy mondta. Találtunk egy leláncolt lányt a raktérben...";
			link.l1 = "Micsoda szemétláda! Ahogy gondoltam... Eloldoztátok a lányt?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Persze, kapitány. Biztonságosan a hajójukra hoztuk.";
			link.l1 = "Szép munka! Vigyék a kabinomba, beszélni akarok vele, amint végeztünk.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Kérsz valamit?";
			link.l1 = "Helló, Hóhér! Mészáros kapitány üdvözletét küldi.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "A nevem Charles de Maure. Enrique-et keresem, Senora Gonzales fiát, régi barátja nevében. Azt hiszem, te vagy az...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "Mi a fene! Nem ismerek semmilyen Mészárost!";
			link.l1 = "Gyerünk, Henry. Mondd el, miért keresnek téged Jackman kalózai, és nem foglak bántani.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "Segítség! Kalózok! Gyilkosság!";
			link.l1 = "Pofa be, idióta! A fél város ide fog futni a kiabálásod miatt. Á, ezt akarod?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Hm... Uram, biztos tévedsz. Idegen családban nôttem fel, nem emlékszem a szülôanyámra. A gondnokom vezetéknevét vettem fel. Nem tudom az anyám nevét, de kétlem, hogy Gonzales lett volna. Érdeklôdhetsz rólam, és bármelyik régi lakos megerôsítheti a szavaimat. A mostohaapám híres ember volt, saját gyermeke nem volt, ezért örököltem ezt a házat és...";
			link.l1 = "Sajnálom. Úgy tûnik, tévedtem. Viszontlátásra.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "Nem hinném.";
			link.l1 = "Elnézést?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "Tudja, nemrégiben kalózok támadták meg kegyetlenül a kolóniánkat. Azt hiszem, hallott róla. A támadás következtében számtalan ember szenvedett. Nekem nem esett bajom, de az örökölt vállalkozásom most nehéz idôket él át. És mindennek a szerencsétlenségnek a felelôse a kalózok vezetôje, egy Charlie Prince nevû gazember.";
			link.l1 = "Nagyon sajnálom, de mi köze van ennek hozzám?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "Ha-ha, csak nézzétek ezt az ártatlan bárányt! Javaslom, hogy fedezd a veszteségeimet, hiszen te vagy a felelôs értük. Tizenötezer pezó összeggel megelégszem. Én pedig úgy teszek, mintha soha nem járt volna a házamban.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Milyen bosszúállóak vagytok... Itt a pénze. És ne feledjétek, ha bárki rájön, hogy a városban jártam, visszajövök értetek.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "Tizenötezer? Hm... nem hiszem, hogy az élete ennyit ér. Szóval, azt hiszem, olcsóbb, ha csak leváglak, hogy ne fecsegj.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "Ôrség! Kalózok! Gyilkosság!";
			link.l1 = "Pofa be, idióta!";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "Látom, tetszik a kardom. Eladhatom neked, ha akarod. Nem kérek érte sokat, már alig várom, hogy igyak egy kis rumot, és a zsebem üres.";
			link.l1 = "És mi a fenének lenne rá szükségem? Az Erdei Ördög megkért, hogy adjam át üdvözletét.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Nos, igen. Valóban szép kardod van. Mennyiért?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "Jobb lett volna, ha inkább pár száz pezót ad helyette!";
			link.l1 = "Szóval ismeri Svensont?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Baszd meg te és a te Svensonod, küldd az ördögbe. Az erdei ördöghöz vagy a tengeri ördöghöz, leszarom. Ha nem vagy hajlandó segíteni egy beteg emberen azzal, hogy megveszed a bicskáját, akkor én ingyen a seggedbe dugom.";
			link.l1 = "Tényleg? Lássuk, hogy fogod ezt csinálni, te faszfej!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "Látom, tapasztalt ember vagy! Ezer pezó és a tiéd.";
			link.l1 = "Áll az alku!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Cartagenában csak két ilyen bicska van - az enyém és az öreg Alvares' a világítótoronyból. De ô nem adja el az övét. Képmutató, egy mérföldrôl kiszagolom a volt kalóz szagát. A penge valamiféle talizmán számára.\nÚgy tûnik, szegény lélek olyan dolgokat sirat, amiket el akar felejteni. Biztos ezért jár havonta templomba, mert a bûnök nem hagyják aludni.";
			link.l1 = "És látom, hogy neked is van egy kis történeted. Biztosan rólad beszélt Svenson. Azt mondta, adjam át üdvözletét, ha esetleg Cartagenában találkoznánk.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Svenson? Soha nem hallottam róla. A nevem Enrique Gallardo. De ha a te Svensonodnak van egy üveg rumja a számomra, akkor hajlandó vagyok Henrynek lenni. Hívjon, ahogy akar, csak ne hívjon késôn vacsorázni. Szóval, megyünk?";
			link.l1 = "Ma nem. Svenson messze van, de a kocsma a közelben van. A zsebeid már nem üresek, úgyhogy vigyázz magadra, Enrique.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "De nem teljesen tele. Többet akarok. És te fogsz fizetni nekem.";
			link.l1 = "Össze vagyok zavarodva... Nem becsülöd meg az életed? Ki akarsz rabolni a város közepén? És mindezt azután, hogy te magad adtad el nekem a fegyveredet?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "Nem, magad fogsz fizetni nekem. És tudod miért?";
			link.l1 = "Kíváncsi vagyok.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "Felismertelek. A tömlöcben voltam egy részeg verekedés miatt a kocsmában, amikor a fiaid berontottak a börtönbe, és lekaszabolták az összes ôrt. Sikerült elérnem az ôr holttestét a kulcsokkal, és kijutottam az utcára. A város lángokban állt, hullák, vér és lôporfüst mindenütt... Pont mint egy beszálláskor! És a füstön keresztül megláttalak téged kijönni a kormányzó rezidenciájából. Költôi, nem igaz? Yo-ho-ho, helló, Charlie Prince!";
			link.l1 = "Ne kiabálj így! Tudva, amit tudsz, különösen nem kellene megpróbálnod pénzt kicsikarni belôlem. Tudod egyáltalán, hogy mit tehetek veled?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "A város közepén, amit egyszer már kiraboltál? Nem tehetsz semmit. Szóval, hogy befejezzem... így fogjuk csinálni: adsz nekem... mondjuk, tízezer pezót most rögtön. Azt hiszem, ez elég lesz egy hónapra. És te menj a saját utadon! Akár a szeretett Henry-hez, akár Svensonhoz, vagy bármelyik másik ördöghöz, akit csak akar... Ha pedig nem, csak kiáltanom kell, és máris berángatnak egy külön erre a célra elôkészített, kínzóeszközökkel teli személyes kamrába.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "A fenébe is, fogd a tízezredet, és tûnj a szemem elôl! És Isten ments, hogy még egyszer lássalak!";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Elég volt, elegem van ebbôl. A fegyvered az enyém, úgyhogy esélyed sincs, söpredék.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "Haha, te jó vagy! Tudod mit? Én már bárki mást is felvágtam volna a hasától a torkáig. De az olyan emberekre, mint te, szükségem van. Mit szólsz ehhez? Adok neked tízezer pezót, visszaadom a 'Hanged Man,' és minden hónapban adok még háromezret - elégnek kell lennie a piára - és a hajóm fedélzetese leszel.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "Jól van, jól van, már el is mentem! Sok szerencsét a kereséshez, Charlie Prince!";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "Ôrség! Ôrség! Ez Charlie Prince!";
			link.l1 = "Te szemétláda!";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "Azt akarod, hogy csatlakozzak a csapatodhoz?";
			link.l1 = "Pontosan. De ez egy egyszeri ajánlat. Szóval, mit mondasz? Egyezz bele, vagy kiöntöm a beled. Ugye nem gondolja komolyan, hogy ilyen könnyen megzsarolhatja Charlie Prince-t?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "Ördög! Charlie Prince maga ajánlotta fel, hogy csatlakozzak a csapatához! A fenébe is, beleegyezem! Add vissza a pengémet és tízezer pezót. Soha nem gondoltam volna, hogy ez így fog alakulni!";
				link.l1 = "Tessék. És tartsd a szádat: senkinek sem kell tudnia a városban, hogy ki vagyok, megértetted?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "Nem. Lehet, hogy rendes kapitány vagy, de nekem úgy tûnik, hogy egy kicsit túlságosan feszült vagy. Igen, egyszer megtanítottad a spanyolokat félni, amikor végrehajtottál egy merész rajtaütést Cartagenán - de mindezt csak Marcus Tyrex segítségével. Egyedül nincs merszed tisztességes fosztogatáshoz. Szóval, adjátok oda a dohányt!";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "Nem, te bizonyára hírhedt kalóz vagy, de kapitányként nem tûnsz olyan lenyûgözônek. Csak Marcus Tyrex segítségével sikerült kifosztanod a kolóniát - egyedül még egy romos csónak fedélzetére sem mernél felszállni. Szóval, adjátok ide a dohányt!";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "A fenébe is, fogd a tízezredet, és tûnj a szemem elôl! És Isten ments, hogy még egyszer lássalak!";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Elég volt, elegem van ebbôl. A fegyvered az enyém, úgyhogy esélyed sincs, söpredék.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "Értettem, nem vagyok bolond.";
			link.l1 = "Jó.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "Nem várok vendégeket, sem ma, sem máskor. Mit akarsz?";
			link.l1 = "Helló, Hóhér. Az Erdei Ördög küldött. Jó, hogy Jackman emberei elôtt megtaláltalak. Az emberei az egész Karib-tengeren keresnek téged. Szerencsédre, Henry, csak Svenson tudja, hol születtél. Ô kért meg, hogy figyelmeztesselek.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "Most már értem... Úgy tûnik, hogy Svenson még mindig él, és nem felejtette el régi barátját. Sok vér folyt azóta, hogy elôször láttam ôt újoncként egy sérült brigg fedélzetén állni... Az élet túl gyorsan elrepült, és már nincs sok idôm hátra\nA természetes halált akartam halni ezen a pusztaságon, távol az emberiségtôl és közel a tengerhez. De ha Jackman újra a Karib-tengeren van, nem hagy békén. Nem az én hibám volt, de tartozom az urának. Különben is, ki fog most hinni nekem.\nNem a haláltól félek, hanem a fájdalomtól. És Jackman sokat tud a fájdalomról. Már a gondolatától is megáll a szívem, és minden elsötétül.";
			link.l1 = "Mészárost húsz évvel ezelôtt felakasztották, úgyhogy nem kell adósságot törlesztenie senkinek. Nekem adhatod az adósságodat, ha félsz Jackmantól. Szerintem úgyis találkozni fogsz vele.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "Az olyan embereket, mint Butcher, nem könnyû felakasztani. A Szent János egykori hóhéra sok érdekes történetet tudna mesélni a pokolból visszatért halottakról. Jacobot pedig jól megtanította a kapitánya, úgyhogy nem vagyok benne biztos, hogy kitôl félek a legjobban.";
			link.l1 = "Miért van szüksége Jackmannak rád?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "Aranyat kellett szállítanom egy özvegynek, fizetségül azért, mert biztonságban tartotta Butcher lányát. Miért nézel így rám? Igen, nem sokkal azelôtt született, hogy a 'Neptun' elsüllyedt. Nem tudott idôben visszajönni érte, ezért engem küldött, hogy vigyázzak a babára és a gondozójára.";
			link.l1 = "Gladys Chandler volt a gondnok neve?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Ne játssza az idiótát. Ha Jackman engem keres, akkor azért, mert szüksége van Butcher lányára. Biztosan tudja már, hogy egy Gladys nevû belize-i nôt és a nevelt gyermekét keresi. Légy ôszinte velem, és talán megbízom benned.";
			link.l1 = "Mit kellett volna mondania Gladysnek?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Semmi. Meg kellett volna mutatnom neki Mészáros gyûrûjét, abból tudta volna meg, hogy a kapitány által küldött futár vagyok. Egy láda dublont is oda kellett volna adnom neki a baba szükségleteire. Meg kellett ölnöm egy fattyút, hogy elvehessem a gyûrût. Emiatt további egy hónappal meghosszabbítottam az Antiguán való tartózkodásomat.\nAmikor pedig végre elértem Belize-t, Gladys már eltûnt, a várost pedig a spanyolok felgyújtották és kifosztották. Sikerült eladnia a házát, és elmenekülnie az új barátjával és a kis Helenével. Remélem, vigyázott rá, és nem adta el a lányt a cigányoknak vagy a bordélyháznak.";
			link.l1 = "Mészáros lányát Helen-nek hívták, ugye?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Pontosan. Mészáros édesanyja tiszteletére. Ha nem félsz az élôholtaktól és a kalózoktól, akik halott szemmel néznek rád, akkor odaadhatom a gyûrût és az aranyat. Sosem nyúltam hozzá. Éhen haltam, de nem nyúltam hozzá. Tégy velük, amit akarsz. És cserébe azt kérem...";
			link.l1 = "Mi történik, Henry?";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "Te...te... Én...k.... oh!";
			link.l1 = "Nem!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "Ott van a mi kíváncsi barátunk! Végre megtaláltad Gonzales-t? Szép munka, elhoztál minket hozzá... nincs többé szükségünk rád. Fiúk, öljétek meg ezt a bolondot!";
			link.l1 = "Ideje meghalni, rákbél!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "U-ah! U-ah! Nagy Kukulcan új áldozatot követel! O-eh! A múlt hatalmas harcosának szelleme eljött a falunkba, hogy feláldozza magát a nagy Kukulcan-nak! O-eh! Mindenki hajoljon meg a hatalmas harcos szelleme elôtt!";
			link.l1 = "(Halványan) Mi a fasz, hol vagyok?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A komancsok bájitalt használnak", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("Úgy érzed, hogy az egészséged helyreállt!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "O-eh! A nagy harcos azt akarja, hogy a nagy Kukulcan megegye! A nap felkel, az árnyékok rövidülnek! Nagy Kukulcan hamarosan életre kel! Elviszünk hozzá, ó, hatalmas harcos, és te tovább haladsz az ôsök földjén!";
			link.l1 = "(halványan) Nonsense... Kukulcan megint? Hé, fônök, békével jöttem! Azért vagyok itt, hogy...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "O-eh! A nagy harcos azt mondja, hogy azonnal fel akarja áldozni magát Kukulcannak. Ó, nagy harcos! Most azonnal Kukulcanhoz megyünk és várjuk a látogatását! Harcosok! Nagy megtiszteltetés számunkra, hogy elvisszük az ôsök szellemét Kukulcanhoz!";
			link.l1 = "(halkan) Idióta Rendben, velük kell mennem. Még jó, hogy nem támadtak még rám, nem tudnék védekezni ebben az izében...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "Jövünk Kukulcanhoz, nagy ôsszellem. Hamarosan lemegy a nap, az árnyékok megnônek, és Kukulcan meglátogat minket. Várj, nagy harcos...";
			link.l1 = "(halványan) Most már értem, indián hadvezér...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Kukulcan él! Kukulcan velünk van! A nagy harcos feláldozható Kukulcan-nak! Harcosok, hajoljatok meg a nagy ôsök szelleme elôtt!";
			link.l1 = "(halkan) Maradjon távol, fônök. Majd én megcsinálom. Nem ez az elsô alkalom...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "Miben segíthetek, Mynheer?";
			link.l1 = "Nocsak, nocsak... mondd csak, haver, mit keresel itt?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "Mit keresek itt? Halász vagyok, és itt horgászom. És mi a fenének kérdezel ki ilyen hangon?";
			link.l1 = "Ne hazudj nekem, haver. Lehet, hogy tényleg halász vagy, de nem halat fogtál itt. Értékes hajóselymet dobtak a tengerbe, itt, ezen a helyen. És már a jelenléted is elég gyanús nekem.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "Miféle ostobaság? Milyen selyemrôl beszélsz egyáltalán?";
			link.l1 = "Milyen selyemrôl? Kínai... Ne játszd az idiótát! Figyelj rám: vagy azonnal elôveszed a selymet a raktérbôl és ideadod nekem, vagy én magam viszem el. De elôbb a fedélzeti csapatom elintézi magát és az embereit. És? Hívjam az embereimet?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "Nem! Mynheer, nem tudtam... Azok a bálák csak úgy lebegnek itt, úgyhogy úgy döntöttem...";
			link.l1 = "Hozd a selymet a hajómra. Siessetek!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Igen, igen, persze. Azonnal megtesszük, csak a hajómat ne vegyétek el!";
			link.l1 = "Mozgás! Nincs sok idôm...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Tessék, elhoztunk mindent, amit találtunk - mind a kilenc bálát. Ez minden, esküszöm...";
			link.l1 = "Jól van. Folytathatjátok a halászatot, de a jövôben ne vessetek szemet mások holmijára!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "Már megkaptátok, amit akartatok. Nekem már nincs semmim! Mi kell még?";
			link.l1 = "Nyugi, haver. Elmegyek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "Ha Barbazon küldött, akkor mondd meg neki, hogy én magam nem akarom elhagyni a börtönt. Jobb, ha megvárom a tárgyalást. Még a holland kender a nyakamon is jobb, mint az ô kedvessége.";
			link.l1 = "Még ne törjön ki a szél. A navigátorod azt mondta Jacques-nak, hogy meghaltál. Azért küldött, hogy megtaláljam a selymet, amit a tengerbe dobtál. Mennyi volt belôle a brigantineden?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "Az én hibám volt, a fenébe is. A futár kilenc bála selymet hozott Barbazon számára. Megparancsoltam, hogy keressék meg. Hangoskodott, ezért el kellett vágnunk a torkát. Volt még három bála a rejtekhelyén, amit elvettem magamnak, és elrejtettem a saját rejtekhelyemen. De úgy látszik, nem kívánt figyelmet keltettünk.\ngyorsan ránk találtak, és egy holland ôrjárat várta a 'Sóskutyát' a nyílt tengeren. Nem sikerült elmenekülnünk. A selymet magadnak viheted, ha nem szólsz Barbazonak rólam. A rejtekhely a Grand Case Beachen van a kövek között, közel a zsákutcához. Nem valószínû, hogy még egyszer szükségem lesz rá.";
			link.l1 = "Rendben. Nem mondom el Barbazon-nak, hogy még életben vagy. Ha igaz, amit róla mondanak, akkor jobb, ha a hollandok felakasztanak. Vagy talán szerencséd lesz, és büntetômunkára ítélnek.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "Várom azt az embert, aki tudja, mikor kezdôdik a vadászat a fehér cápára.";
			link.l1 = "A vadászat már elkezdôdött.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Végre! Most jól figyeljetek. Meg kell látogatnod Marcus Tyrexet La Vegában, és el kell mondanod neki, hogy a brigantine 'Separator' t megtámadták a Turks-sziget közelében, és most a déli öbölben rejtôzik. A kapitánya súlyosan megsebesült, és a legénység segítségre vár. Felvetted a 'Separator' egyik matrózát, és ô mindent elmondott neked. Most már halott. Ez minden, amit tudsz. Megértetted?";
			link.l1 = "És miért van rám szükséged ehhez? Túl sokáig vártam csak erre...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "Azért fizetnek, hogy végezd a munkádat, és ne kérdezôsködj. De igaza van. Figyelmeztetnem kell, hogy Tyrex addig nem engedi el, amíg meg nem bizonyosodik róla, hogy az igazat mondja. De ha egyszer mindent megtud, jól meg fog fizetni. Ha képes lesz rá...";
			link.l1 = "Maga átver engem, uram... Miért nem akarja maga is megkapni a köszönetét?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Carramba! Nem tetszik a kíváncsiságod! A buborékos beszéded egy nap egyenesen a sírba fog vezetni.";
			link.l1 = "Igen, néha elviselhetetlen vagyok. Fôleg, ha látom, hogy valaki át akar verni. Nem, haver, most az én szabályaim szerint fogunk játszani. Ki a mestered, az istenit! Válaszolj, vagy én kényszerítelek!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "Te... szemétláda! Barbazon megfizet ezért, és vége lesz az életednek, szarevô!";
			link.l1 = "Ha! Erre számítottam. Készülj fel, gazember!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Charlie Prince? Mit keresel itt? A fenébe, te voltál az! Ez mind a te mûved!";
				link.l1 = "Nyugi Bernie. A te oldaladon állok. A csapdát felszámoltuk, te és a hajód biztonságban vagytok.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Ki vagy te, a fenébe is? Hogy kerültél ide? Menjetek el most, a hajóm alá van aknázva, és a parton lévô szemetek egy lövéssel felrobbanthatják.";
				link.l1 = "Ne aggódjon, uram. A parton lévô csapdát kiiktattuk. A hajója most már biztonságban van, feltéve persze, hogy nem fog pipára gyújtani a fedélzeten. Mi a neve?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Vincent. Bernard Vincent. És mi a neve?";
			link.l1 = "Kapitány "+GetFullName(pchar)+". Elvágom azokat a köteleket és kiszabadítalak...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Ó... hálám. Hogyan köszönhetném meg?";
			link.l1 = "Még nincs vége, uram. Él még valaki a legénységébôl?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Három tucat emberemet bezárták a raktérbe...";
			link.l1 = "Engedje el ôket, és azonnal tûnjön el innen. ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "De...";
			link.l1 = "Ne vesztegesse az idejét, Bernard. Késôbb megköszönheti nekem La Vegában... Tyrex is megköszönheti nekem.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "Szóval nem véletlenül van itt? Tudtál mindenrôl?";
			link.l1 = "Igen, tudtam. Sikerült felfednem Jackman ármánykodását és a terveit Marcus megölésére. Ó, kérd meg Tyrexet, hogy maradjon nyugton, a beavatkozása elijesztheti Jackmant.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "Biztosan elmondom neki! Most elmész?";
			link.l1 = "Igen, uram. És neked is sietned kellene.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Tényleg? - Igen. Nézd, sajnálom, testvér...";
			link.l1 = "Felejtsd el. Csak hadd vágjam el a köteleket és engedjelek szabadon.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Baszd meg... Nem érzem a kezem...";
			link.l1 = "Bernie, vannak még túlélôk a hajón?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Harminc ember van bezárva a raktérbe...";
			link.l1 = "Engedd el ôket, és tûnjünk innen a pokolba. Azonnal!";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "De...";
			link.l1 = "Azonnal hajózzanak La Vegára. Mondj el Marcusnak mindent errôl a zûrzavarról, minden részletre kiterjedôen.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Marcus küldött téged?";
			link.l1 = "Nem küldött. Sikerült lelepleznem egy szemétláda összeesküvését. Azt tervezte, hogy ezzel az intrikával likvidálja Marcust. Kérd meg, hogy maradjon nyugton, és egyelôre ne avatkozzon bele... Késôbb majd én magam magyarázok el neki mindent. És kérlek, mondd meg neki, hogy ne haragudjon rám.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "Mit akar a hajómon, uram?";
			link.l1 = "Jó napot, Paul. A neve Paul Molligan, igaz?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Igen, én vagyok. Miben segíthetek?";
			link.l1 = "A nevem "+GetFullName(pchar)+" és Jan Svenson küldött.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Jan? Emlékszem magára. Persze! Mostanában állandóan látogatja a házát. Szóval, mit akar tôlem Jan?";
			link.l1 = "Annyira sietett, hogy elhajózzon Blueweldbôl. Jan meg akarta rakodni a hajódat kétszáz centi mahagónival, hogy Bridgetownba szállítsa lord Willoughbynak. Készítsd elô a hajódat, az embereim beteszik a mahagónit a rakteredbe.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Mahagóni? Ezt Jan mondta? Hm. És miért nem szállítja maga Barbadosra? Miért én?";
			link.l1 = "Mert te ott hajózol, én meg nem. Azonnali megbízást kaptam Svensontól, így nem vesztegethetem az idômet azzal, hogy én is elhajózom Bridgetownba. Különben is, Jan nem bízik bennem, hogy üzletet kössek Lord Willoughbyval, és azt akarja, hogy te intézd ezt. Sajnálom. Most pedig pakoljunk be, nekem mennem kell.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Figyelj, nincs szabad helyem a rakteremben. Nem fogom tudni megtenni, amit Jan kér tôlem, bár szeretném.";
			link.l1 = "Nincs hely? Furcsa... Jan azt mondta, hogy van egy kis szabad helyed.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "Ez igaz, de Jan nem tudta, hogy a 'Oyster' nehezebb ágyúkkal szereltem fel. Nem tudok több rakományt felpakolni, mint amennyit már felraktam. Akkor szállítsd el te magad a fát Barbadosra, haver. Mondd meg Jan-nak, hogy nem tudtam megtenni. Willoughbyval könnyû dolgod van: csak keresd fel, add át neki a rakományt, és vedd át a nyugtát. Elég egyszerû.";
			link.l1 = "Hm. Nem ez volt a tervem... Ellenôrizzük a rakteret, rendben? A szállásmesterem nagyon tehetséges a pakolásban, képes lesz betenni az árut a rakterébe, és még egy kis szabad helyet is hagy magának...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Pajtás, nem tudok más árut felvenni. Azt akarod, hogy dobjam el az ágyúimat, és hagyjam a 'Oyster' védtelenül?";
			link.l1 = "Nos, ha ilyen biztos vagy benne... De Jan nem fog örülni neki, gondolj bele!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "Elmagyarázom Svensonnak, ne aggódjon. Végül is az ô hibája, hogy nem kérdezte meg tôlem a hajóm ûrtartalmát.";
			link.l1 = "Eh, és most el kell vitorláznom azokkal a rönkökkel Barbadosig, a fenébe is... Viszlát, haver.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "A gazember még mindig nem sejt semmit. Közelebb kéne mennem, és lôni rá grapeshot-tal. Egy hirtelen csapás mindig gyôzni fog minden csatában. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "Tiszta a terep, ugye?";
			link.l1 = "Igen, igen. Megyek a hajómhoz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "Mit akarsz tôlem? Nem szeretem a pletykát és a szerencsejátékot. És egyedül iszom a rumot. Különben is, rossz kedvem van a legutóbbi hajóutam után.";
			link.l1 = "És milyen különleges dolog történt a legutóbbi hajóútja során?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "Egy jó ember bízott bennem, és én dobtam ki a fedélzetre, mert a legénységem ezt követelte.";
			link.l1 = "És mi volt a hibája?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "Újonnan jöttem, és nem sok embert ismerek itt. Ezért vettem fel sebésznek azt a jószívû kövér embert anélkül, hogy tudtam volna a múltjáról. A kalózok üldöztek minket, mióta elhagytuk Barbadost. Miért lenne szükségük a tojáshéjamra?\nAz erôs szélviharnak köszönhetôen alig tudtunk elmenekülni. Egy ilyen alkalomra megittunk egy italt. És a kövér bolondnak nem jutott jobb ötlet, minthogy mindenkinek elmondja, hogy a kalózok valószínûleg azért üldözik, mert ô az egykori hóhér, és olyan dolgokat tud, amiket nem szabadna tudnia.\nA legénységem tagjai persze nagyon dühösek lettek. Tényleg?! Egy hóhér a fedélzeten, aki sebészként szolgál! És a kalózokkal sem akart senki ujjat húzni... Szóval ki kellett tennem a partra szegényt. Az egész az ô hibája, csak ki kellett nyitnia a száját. De sajnálom a fajankót, kiváló orvos volt. Csak egy perc kellett neki, hogy meggyógyítsa a másnaposságomat.";
			link.l1 = "A francba! Az orvosod neve Raymond Baker volt, igaz?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Igen. Pontosan. És honnan tudja? Üldözött engem?";
			link.l1 = "Nem, az nem én voltam. Csak szükségem van arra az emberre, ô egy nagyszerû orvos. Hol találtad meg?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Szélességi fok 15 fok 28' északi, hosszúsági fok 63 fok 28' nyugati. Siessen, uram! Még életben kell lennie, és ha megmenti, akkor magára hárítom a felelôsséget!";
			link.l1 = "Már emelem is a horgonyaimat!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "Kapitány, siessen! Még életben kell lennie!";
			link.l1 = "Igen, igen, már úton vagyok...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hé! Maradj ott! Ne mozduljatok! Ez a terület biztosítva van!";
				link.l1 = "Ne légy túl szigorú, haver! Barátaim! Jackman küldött minket. El kell jutnunk a bányához. A mester parancsa...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hé! Maradj ott! Ne mozduljatok! Ez a terület biztosítva van!";
				link.l1 = "Hm. De én át akarok menni... Mi a fenéért állítottál meg?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Már megint te? Látom, hogy nem érted... Fiúk, tûz!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Gyerünk, mozgás!";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "Mert a mögöttem lévô bánya magántulajdon, és azért vagyok itt, hogy megakadályozzak minden hozzátok hasonló idegent, hogy átmenjen. Jobb, ha megfordulsz és elmész innen, idegen. Az ágyúink tele vannak grapeshot-tal, még egy lépés és vizes pocsolyává változik.";
			link.l1 = "Heh, értem. Az enyémnek komoly ôre van. Rendben, én elmegyek.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "Te szemétláda! Nos, majd meglátjuk, ki válik pocsolyává!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "Adtam neked egy esélyt... Fiúk, tûz!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Hé! Menjetek innen! Ez a terület biztosítva van!";
				link.l1 = "Hé, nyugi, haver! Jackman küldött minket. El kell jutnunk a bányához. A mester parancsa...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hé! Menjetek innen! Ez a terület biztosítva van!";
				link.l1 = "Hm. És mi van ott?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Már megint te? Látom, hogy nem érted... Fiúk, tûz!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "Semmi közöd hozzá. Tûnj el, vagy lelôlek, esküszöm!";
			link.l1 = "Nyugodj meg. Elmegyek.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "Te szemétláda! Majd meglátjuk, ki lô le kit!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "Adtam neked egy esélyt... Muskéták készenlétbe! Tûz!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Tényleg? Akkor biztos tudod a jelszót. Beszélj, de meg fogod bánni, ha hazudsz...";
			link.l1 = "Triton";
			link.l1.go = "mine_wrongx_password";
			link.l2 = "Neptunusz";
			link.l2.go = "mine_attackx_1";
			link.l3 = "Centurio";
			link.l3.go = "mine_wrongx_password";
			link.l4 = "Szigony";
			link.l4.go = "mine_wrongx_password";
		break;
		
		case "mine_attackx_1":
			dialog.text = "Helyes. De te, haver, rossz oldalról jöttél ide. Nem figyelmeztettek? Menj vissza, és a száraz kúttól balra menj az ösvényen. Aztán menj körbe a dombon, és ott meglátod a fôkaput.";
			link.l1 = "Itt nem mehetek be?";
			link.l1.go = "mine_attackx_2";
		break;
		
		case "mine_wrongx_password":
			dialog.text = "Srácok, van egy nyomozónk! Muskéták készenlétbe! Tûz!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_attackx_2":
			dialog.text = "Nem. Csak a központi bejáraton keresztül.";
			link.l1 = "Rendben, haver... Hé! Nézd! Mi a fasz az a palánk tetején?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Tényleg? - Igen. Akkor tudnod kéne a jelszót. Beszélj hangosabban, hogy halljam. És ha megpróbálsz átverni, ez lesz az utolsó tréfa, amit életedben valakivel eljátszol.";
			link.l1 = "Triton";
			link.l1.go = "mine_wrong_password";
			link.l2 = "Neptunusz";
			link.l2.go = "mine_attack_1";
			link.l3 = "Centurio";
			link.l3.go = "mine_wrong_password";
			link.l4 = "Szigony";
			link.l4.go = "mine_wrong_password";
		break;
		
		case "mine_attack_1":
			dialog.text = "Ez az. Menjünk tovább. A tábor vezetôje a bánya bejáratától balra lévô házban van. Menjetek és keressétek fel.";
			link.l1 = "Rendben, haver...";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_wrong_password":
			dialog.text = "Srácok, van egy nyomozónk! Ágyúk, tüzet nyitni!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_attack_2":
			DialogExit();
			locCameraFollowEx(true);
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "Mi van még? Elfelejtettél valamit?";
			link.l1 = "Igen. Megkértek, hogy adjam át a legjobbakat.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Nekem? Ha-ha! Kitôl?";
			link.l1 = "Jan Svensontól, te szemétláda!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			AddDialogExitQuestFunction("Saga_MineAttack");
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("Szét fogjuk tépni azokat a szemeteket!","Alig várom, hogy legyôzzük azokat a söpredékeket!","Jackman csatlósainak nincs joguk a Nyugati fôutcán lenni! Elverjük ôket innen!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("Készen állunk a harcra!","Megmutatjuk nekik!","Azt sem tudják, kivel szórakoznak!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "Parancsnok, az ágyú készen áll. Megtöltöttük bombával, ahogyan azt maga parancsolta.";
			link.l1 = "Gondolom, senki sem vár minket itt... Ideje bemutatkoznunk. Jan azt mondta, hogy a táboruk a domb mögött van. El tudod érni?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Elég könnyû, parancsnok. Emeljük meg egy kicsit a csövet, ez megteszi... kész.\nKészüljetek!... Tûz!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Hm. Randolf, gondolod, hogy eltaláltunk valamit? Szeretném hallani a véleményed.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Parancsnok, tényleg eltaláltunk valamit vagy valakit, de nem tudok pontosabbat mondani... ez az átkozott domb eltakarja a kilátást. Megváltoztatom a szöget.\nKészen állunk! Tûz!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ha! Nézze, parancsnok! Füst van! A fenébe, biztos valami bandita pajtába csapódtunk! Hurrá-ah!";
			link.l1 = "Igen, látom a füstöt... Ez máris egy epikus gyôzelem, semmi kétség. Töltsd újra a fegyvert, és irányítsd az ösvényre, úgy tûnik, jönnek a vendégeink. Megfelelôen fogjuk ôket köszönteni!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Igenis, parancsnok! Töltsd be a bombát! Lövészcsapat készenlétbe! Gyutacs készenlétben! Parancsomra tûz!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "Ha-ha, ez biztos fájt!";
			link.l1 = "Még ne lazíts! Töltsd meg a fegyvert! Nem hiszem, hogy elég volt nekik. Jönnek még!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "Igenis, parancsnok! Bombát tölts! Készen állunk! Parancsomra tûz!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "Ha-ha-ha-ha, a rohadékok megmutatták a hátukat! Kutyahús! A grapeshot szétzúzza ôket ilyen távolságból! Úgy látszik, nem elég bátrak ahhoz, hogy újra megtámadjanak minket!";
			link.l1 = "Most rajtunk a sor. Randolph, te itt maradsz az ágyú mellett. Lôj néhányszor az ösvényre, majd célozz a füstre - égesd fel a búvóhelyüket! Csak ne lôjetek ránk!";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Igenis, parancsnok! Készítsétek az ágyút! Töltsetek bombát!";
			link.l1 = "Emberek! Fegyverbe! Kövessetek, támadás! Hurrá!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Ne bántsatok, én nem tartozom közéjük! Öljétek meg a banditákat!","Szabadíts ki minket, haver! És öljétek meg mindet!","Vágd el ôket, barátom, vágd el ôket! Haldokljatok!");
				link.l1 = "Ha! Ne aggódj, pontosan ezt tesszük most is.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Vége a rabszolgaságunknak? Felszabadítasz minket?","Heh, tényleg sikerült túlélnem ezt a napot?","A rohadékok minden vért kiszívtak belôlünk....");
				link.l1 = "Azt hiszem, hamarosan élvezheted a szabadságodat, haver...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Jobb, ha elhagyja ezt a helyet, uram. Nem fedezzük a bûnözôket, és nincs szükségünk konfliktusokra a kolónia hatóságaival.";
				link.l1 = "Rendben, elmegyek...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "Ah, Helen. Egy kicsit tisztességesebben is felöltözhettél volna, mielôtt eljöttél volna Janhoz, ahelyett, hogy megmutatod neki, milyen is vagy valójában. Kár, hogy nem hisz nekem.";
					link.l1 = "És pontosan milyen vagyok? Gyerekkorom óta segít nevelni, és jobban ismer engem, mint bárki más. Nincsenek titkaim elôtte. Gyerekkorom óta szenvedek ettôl a hôségtôl, úgyhogy a magam módján kellett megbirkóznom vele, ennyi az egész.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", uram. Akarja látni Jant?";
				link.l1 = "Jó napot! Örülök, hogy megismerhettem, kisasszony...";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "Jan bent van. Menj csak, nincs itt semmi látnivaló, és az idegeimre mész.";
					link.l1 = "Amúgy sem volt hozzá kedvem.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Grr!";
					link.l1 = "És jó egészséget önnek is, Svensson asszony.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", Kapitány "+GetFullName(pchar)+". Ha Jan miatt vagy itt, akkor csalódást kell okoznom neked - ô nincs itt. Fontos üzleti ügyeket intéz.";
					link.l1 = "A francba! És szükségem van rá! Mondja, Mrs. Svenson, mondta már, hogy mikor jön vissza?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "A-ah, már megint te, kapitány "+GetFullName(pchar)+"... menj tovább, Jan fent van, mint mindig.";
				link.l1 = "Köszönöm, Mrs. Svenson...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Mrs., Mrs. Johanna Svenson.";
			link.l1 = "Kapitány "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Kapitány úr? Örülök, hogy a házamban üdvözölhetem. De ha Jant keresi, akkor ki kell ábrándítanom: nincs itt. Elutazott valami fontos ügyet intézni.";
				link.l1 = "A francba! És szükségem van rá! Mondja, Mrs. Svenson, mondta már, hogy mikor jön vissza?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Kapitány úr? Nos, örülök, hogy a házamban üdvözölhetem. A férjem a második emeleten van az irodájában. Menjen fel az emeletre.";
			link.l1 = "Értem, Mrs. Svenson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "Nem. Még a visszatérésének pontos dátumát sem mondta meg, mert ô maga sem tudja, meddig tart a keresés.";
			link.l1 = "Sajnálom, hogy közbeavatkozom, de nagy szükségem van rá... Milyen keresést folytat?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Elmondom neked. A bájos Helen, más néven Rumba, néhai barátja, Sean McArthur lánya eltûnt. Jan úgy bánik az ifjú ördöggel, mintha a saját lánya lenne. A lány a régi szerelmére emlékezteti, aki ugyanilyen vakmerô természetû volt. Legalábbis szerintem ez a vonzalom oka.\nA lány mindenesetre egy hete eltûnt a szkúnárral 'Rainbow' és az egész legénységgel együtt. Sean McArthur tanította ôt tengerészmesterségre, és a 'Rainbow' végrendeletében rá szállt. És most azt játssza, hogy ô a kapitány...";
			link.l1 = "Mi történhetett vele?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Ki tudja... Egy hét nem olyan hosszú idô, de McArthur özvegye biztos benne, hogy valami történt a lányával, és errôl sikerült meggyôznie Jant is. Összeterelte az embereit, és maga is keresni kezdte a lányt, egyelôre eredménytelenül. Személy szerint úgy gondolom, hogy Helen jól van, Jan pedig csak kínozza magát ok nélkül.\nTúl sokat hallgatott annak az öreg, kövér nônek a hülyeségeire, és pánikba esett. A lány valószínûleg most éppen egy másik barátjával szórakozik, távol az emberek tekintetétôl, biztonságos helyen. Vissza fog jönni, amint csillapodik az éhsége.";
			link.l1 = "Johanna, hol találom Gladyst? Beszélni akarok vele...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "A háza a móló mellett van, balra. De valószínûleg nincs ott. Minden napját az erôd falán állva pazarolja, és a drága lányát keresi.";
			link.l1 = "Értem. Köszönöm szépen az információt!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Jan még nincs itt, kapitány, úgyhogy gyere vissza késôbb.";
			link.l1 = "Értem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "Mindig tüzes vagy, azt mondanám. El kéne menned a templomba, alig láttalak ott.";
			link.l1 = "A lelkiismeretem tiszta - nincs miért bocsánatot kérnem. Még mindig keserû, hogy segített ellátni a hajómat ahelyett, hogy egy másik ruhát vett volna neked, Johanna?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "Én? Keserûség? Nem éri meg. Túl könnyen megy neked minden, és nem érdemled meg.";
			link.l1 = "De amint megkaptam azt a hajót, elkezdtem magam keresni. És mióta felszedett téged, mint egy kóbor macskát, egy napot sem dolgoztál. Szóval ki él valójában belôle?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "Ha továbbra is így beszélsz, egy nap megkapod, amit megérdemelsz. Jannak és Gladysnek meg kellett volna tanítania téged egy kis jó modorra. Rendben, menj, mondd, amit mondani akartál - és tûnj a szemem elôl, Helen. Bent van.";
			link.l1 = "Hülye tyúk. Persze, megteszem.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Hé! Mit keresel itt?";
			link.l1 = "Én is ezt kérdezném tôled - mit keresel te és a haverjaid itt, a börtönömben?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Há! A börtönödben? És mióta a tiéd, buzi?";
			link.l1 = "Aznap, amikor apád elkövette azt a hibát, hogy megdugta anyádat.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Keresed a bajt?";
			link.l1 = "Figyelj, haver, adok egy utolsó esélyt, hogy elhagyd ezt a helyet. Ez az én börtönöm, és nem engedek be ide senkit szabadon, érted? Csak egyszer kell fütyülnöm, és Isla Tesoro fél kalózai egy percen belül itt lesznek.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "Akkor megpróbáljuk befogni a szádat!";
			link.l1 = "Ha-ha! Szánalmasak vagytok, söpredék!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "Várj egy kicsit, sólyom!";
			link.l1 = "Nem a legjobb idôzítés, édesem.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Ó, tévedsz, szépfiú. Ez a lány kedvel téged, és ez az érzés kölcsönös, ahogy látom.";
			link.l1 = "Nem a legjobb ajánlólevél... Rendben, mit akarsz? Egy kis alamizsnát?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "Szeretnék támogatást nyújtani a kihívásokkal teli vállalkozásodhoz. Nézd csak! Egy mágikus bögre és egy tiltott kenôcs. A bögre segít az ivásban, a kenôcs pedig a szerelemben. Mit fogsz választani? Csak kétezret!";
			link.l1 = "Nincs szükségem semmire - már egy csomó ezüstöt adtam a fajtádnak.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "Tiltott kenôcsöt mondtál? Hát, nem vagyok szent, elismerem. Add ide.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "Egy bögrét? Úgy nézek ki, mint egy részeges? Nos, kit akarok átverni... Elveszem!";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Jóképû, de bolond. Akkor repülj el, sólyom.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "Ó, ne rejtsd el a feneketlen zsebeidbe! Repülj el, sólyom, és ne vétkezz!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talizmán 'Egy öntöttvas torkát' megszerezted!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "Ó, ne rejtsd el a feneketlen zsebeidbe! Repülj el, sólyom, és ne vétkezz!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talizmán 'Cupids Balm' megszerezve!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen helyteleníti.", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "Tûnj innen, te gazember! Hányszor mondtam már, hogy ne mássz be a házamba! És ki ez itt?";
			link.l1 = "Asszonyom, már ismerjük egymást.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Monsieur de Maure? Hát ez nagyon kedves! Így üzletelsz a férjemmel?! Tudtam! Figyelmeztettem Jant: egy nap ez a ribanc félre fogja vezetni a férfiakat! És mit tart a kezében?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "Mi-mi-mi-mi?! Hogy merészeled, te nyomorult?! Nem mész sehova; a férjem bármelyik pillanatban itt lehet, és megtanít, hogyan kell beszélni az öregekkel!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "Mi történik itt? Miss MacArthur! Nagyon tiszteltem az apját, és Mr. Svensson a barátunk... De nem emlékszik, hogyan végzôdött a múltkor?\nCsalódást keltô, tiszteletes úr, csalódást keltô! Meghívhattál volna minket!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Köszönjük a vendégszeretetét, Miss MacArthur. Hadd mondjam el, hogy mindannyian nagyon örülünk a visszatérésének. Hogy mi történt, az nagy rejtély, de nem meglepô, hogy a város tud róla. Mégis, megígérhetem, hogy senki sem fog pletykálni. Ôszintén elnézést kérek az egyik kapitányunk közelmúltbeli viselkedéséért. És külön köszönetet szeretnék mondani önnek, Mr. de Maure.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Minden rendben lesz, kisasszony. Mr. de Maure, ôszinte leszek - annak ellenére, hogy Donovan igazi gazemberként és banditaként viselkedett, a flotta soha nem fogja nyíltan elítélni. Sôt, inkább meg fogják védeni. Az ön kis expedíciója bekerült a jelentésekbe, és jelentôsen megnehezítette az országaink közötti kapcsolatokat. Mindazonáltal, figyelembe véve Svensson úr befolyását, valamint a Capsterville által önnek tett figyelemre méltó engedményeket, nincs mitôl tartania.";
			link.l1 = "Ez nagyszerû. Azt mondom, erre igyunk!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Bocsásson meg kedvesen, de mi a helyzet a munkával?";
			link.l1 = "Még mindig itt van?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Kedves uram, hova máshova mehetnék? Csak könnyíteni mentem, meghallottam az ön szentimentális beszélgetését, és egy kicsit felmelegedtem. Mármint érzelmileg!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "Te jó ég! Hát, mivel a szavamat adtam, ezen nem lehet segíteni. Menj, vedd át a parancsnokságot.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "Nincs munkám önnek, uram.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "Kár! Mindenesetre, köszönöm a vendéglátást, kapitány!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "In nomine Patris et Filii et Spiritus Sancti... gyere be, fiam.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Szervusz, Amelia anya. Te is kiabálni fogsz velem?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "Tûnj el! Miféle rémálom ez? Mi történik? Álmodom?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "Nem, kis sólymom. És bocsáss meg Jannak - háborgott szegény. De igen, meg akarlak szidni. Miért jöttél a templomba? Hogy megbánd a bûneidet? Vagy a vörös hajú után mentél?";
			link.l1 = "Én magam sem tudom...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Te is láttad ôt? Megakadt a szemem rajta.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Tûnj el te magad. Már találkoznunk kellett volna, de te mindent elnyújtasz. Miért jöttél a templomba? Hogy megbánd a bûneidet? Vagy a vörös hajú után mentél?";
			link.l1 = "Én magam sem tudom...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Te is láttad ôt? Megakadt a szemem rajta.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Jó reggelt, sólymom. A fogadás még nem kezdôdött el, várjon a sorban, kérem.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Üdvözlöm, excellenciás uram. Te is kiabálni fogsz velem?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "Tûnj el! Miféle rémálom ez? Mi történik? Álmodom?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "Nem, sólymom. És bocsásson meg Jan-nak, szegény ember felhúzta magát. Nem kell szidni, mindent jól csináltál - nem mentél a vörös hajú után a templomba. Jó fiú!";
			link.l1 = "Szép dolog, hogy megdicsérnek. Fôleg, ha világos, hogy miért.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Te is láttad ôt? Megakadt a szemem rajta.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Tûnj el te is. Már találkoznunk kellett volna, de te mindent elnyújtasz. Gyere ide, megdicsérlek - nem mentél a vörös hajú után a templomba. Jó fiú!";
			link.l1 = "Szép dolog, hogy megdicsérnek. Fôleg, ha világos, hogy miért.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Te is láttad ôt? Megakadt a szemem rajta.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "Nem foglak részletekkel fárasztani, butuska, de annyit elárulok: a sors úgy hozta, hogy nagyszerû emberré válj. Sok rosszat, de még több jót fogsz hozni. De a boldogság nem garantált számodra. A boldogság, sólymom, csak azoknak adatik meg, akik járják az útjukat, és nem térnek el. És egy hûséges nô segít neked abban, hogy ne térj félre.\nKettô lesz belôlük, és mindkettô boldogságot hoz, de neked a szôke hajút kell választanod.";
			link.l1 = "Miért is lenne az? Majd én eldöntöm magam!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Persze, válassz magadnak, de a szôke hajú a jobb. Mi így döntöttünk.";
			link.l1 = "Kik vagyunk mi?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "A szerencsétlen még a valódi nevét sem tudja. Mondd ki, és a tiéd lesz. Így mondják.";
			link.l1 = "Már semmit sem értek.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "Hallod ezt a kopogást? Nyisd ki, és ne tévedj.";
			link.l1 = "Valóban, valaki kopogtat... Jöjjön be!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Monsieur, Svensson úr kérte, hogy szánjon rá egy kis idôt.";
			link.l1 = "A fenébe, ez nem sok jót ígér. Megpróbálom, de nem ígérek semmit.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "Szerencsés nap, fiúk! Mondtam, hogy elôbb-utóbb idejön, nem igaz? Rendben, édesem, add át a fegyvereket és gyere velünk.";
			link.l1 = "Rosszul látjátok, fiúk. Ô velem van.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Maradj ki ebbôl, vagy lelôlek, mint egy kutyát. A lányért jó pénzt ajánlottak fel, mi pedig éhes fickók vagyunk, elvtelenek.";
			link.l1 = "Ha továbbra is ilyen hangnemben beszéltek velem, akkor végleg megoldom az éhségproblémátokat.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "Teljesen megôrültél, Lucky? Mi találtuk meg elôbb! Jobb, ha jó okod van rá, hogy a hülye szádat rám röhögted!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "Te vagy itt a patkány! Épp most téptünk szét egy nagy kövér spanyolt, egy évig ülhetünk a seggünkön!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Nézd csak, ki van itt! Rendben, mindenki más, kifelé, és maga, asszonyom, jöjjön velünk.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "Túlerôben vagyunk, és keményebbek is, Dane. Milyen más ok kell még, te szemét patkány? Már hat hónapja nem láttál rendes fogást, és Vuazie asztaláról eszed a kenyérmorzsákat!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "Úgy tûnik, nem lesz békés megoldás.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "Mit mondtál? Szerencsés? Azt beszélik, hogy Vuazie és ô összeesküdtek, hogy gyenge borravalót adjanak neked. Ez megmagyarázza a szerencsétlenséged a tengeren.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "Elegem van ebbôl a bohózatból. Isla Tesoro, hallgass rám! Ki volt velem Cartagenában?! Ki gyújtotta fel velem Meridát?! Ezek a patkányok Charlie hercegre merészelnek támadni! Mutassuk meg' em, fiúk!";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "Még mindig itt vagy, medúza? Rendben, fiúk, gyerünk: kössétek le a kapitányt, a lányt majd késôbb elintézzük, értve?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Persze, legalább egy kis vért kiontunk. Hehe.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "Mi van?! Ördög, tudtam, hogy összejátszol azzal a szemüveges gazemberrel! Vágjátok le mindet, fiúk, a lányt majd késôbb elkapjuk!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "Mirôl fecsegsz, kapitány? Tûnjetek el, amíg a tisztességes emberek az üzletrôl beszélgetnek.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "Mirôl fecsegsz, kapitány? Láttam Charlie Prince-t, és te nem érsz fel hozzá. Tûnj el, amíg a tisztességes emberek az üzletrôl beszélgetnek.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "Charles de Maure? Henri de Monpe fia?";
			link.l1 = "Így van, monsieur. És ön kicsoda?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Francois de Tavanne ezredes. Tekintse ezt közvetlen kihívásnak, monsieur; a párbaj kesztyûjét letették. Nem kívánom bemocskolni a kezemet, de esküszöm, a pengém megízleli a vérét!";
			link.l1 = "Párbaj? Ebben az esetben sokkal jobban meg kell próbálnia, ezredes úr. Jelenleg csak egy banditával téveszthetnének össze, és ezen a vidéken rövid a beszélgetés a fajtájukkal! Magyarázkodj!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "Elcsábította a feleségemet, uram! Míg én vért ontottam a királyért és a hazáért, te... te a feleségemmel szórakoztál!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Csendet, asszonyom. Az ön szemtelen öltözéke minden nô becsületét megszégyeníti, bár ön igencsak helyénvalónak tûnik egy nemes asszony méltatlan csábítója mellett!";
			link.l1 = "Ez még mindig nem elég ok a párbajra, ezredes úr. És hadd jegyezzem meg, hogy ön itt is ugyanolyan méltatlanul viselkedik.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "Ez nem elég? Megkérdeztem - a helyemben most egy tucat nemes férj lehetne, uram. De ha a részletekre vagy kíváncsi, akkor szégyenemre bevallom, hogy egyik szenvedélyed Lulu de Tavann, a legszebb és legbecsületesebb nô volt!";
			link.l1 = "Lulu, azt mondja... És hogy van?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "Hallgasson! A feleségem, aki nem tudta elviselni az ön által okozott kínokat, nemrég elhunyt! Majdnem egy évet és egy vagyont költöttem arra, hogy megtaláljam magát, gazember! Elég a szavakból! Vagy elfogadod a kihívást, vagy megöllek, mint egy kutyát. Richard! Légy a tanúm!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "Csendet, uram! Fogadd el a kihívást, vagy veszítsd el a becsületed maradékát is!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "A párbaj az párbaj. Nem fogok hazudni, én élvezem azokat. Kapitány, mondja meg az ezredesnek, hogy itt az ideje, hogy rendeljen egy megfelelô koporsót.";
			} else {
				link.l1 = "Akarsz harcolni? Megkapod! Kapitány, adja át az ezredesnek, hogy ideje rendelnie egy megfelelô koporsót.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "Ez nem Európa, ezredes. A Karib-tengeren a becsületet nehezebb kiérdemelni, de nem is olyan könnyû elveszíteni. Visszautasítom a párbajt, mert egyszerûen nem akarom.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "Az apád már egy lépésre van a sírtól, te szemétláda! És gondoskodom róla, hogy tudjon a gyávaságodról!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Ezredes, megerôsítem a párbajhoz való jogodat, de nem engedem meg a puszta banditaságot! Monsieur de Maure, Richard Small kapitány vagyok. Hajlandó elégtételt adni de Tavann ezredesnek?";
			link.l1 = "Egy pillanat, kapitány. Jól ismertem Lulut... és ô... hajlamos volt gyakran váltogatni a hódolóit, és az egészsége jobb volt, mint az enyém... Hogyan halt meg, ezredes? A hazatérése elôtt vagy után?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Kérem, Francois, engedje meg. Monsieur de Maure, Önt kihívták. Blueweld tiszti társadalma elismerte, hogy de Tavann ezredes elégtétel iránti követelése jogos. Fogadja el a kihívást, vagy elveszti a becsületét.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Charles, kérlek, nemesek vagyunk itt. Ez nem helyénvaló. Az ezredes ilyen messzire utazott, hogy találkozzon veled! Ez botrány!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "Igen, természetesen, kisasszony. De én...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "De Maure kapitány, a nap az öné! Nem a legilletékesebb harc, de ma megvédte a becsületét.";
			link.l1 = "Mondott valamit, kapitány? Talán még egy párbajt be tudok szorítani a mai programba.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "Elnézést kérek, kapitány. Csak az idegek!";
			link.l1 = "Azt hiszem, a jelenlétedre itt már nincs szükség.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "Igazságos döntés! Még ha nem is a legméltóságteljesebben fogalmazott... Uraim! Kezdjük!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Kapitány, lehet, hogy nem értem az összes díszes szót, amivel ezek a méltóságok dobálóznak, de tudja, ha valakit gyávának neveznek, azt általában nem engedik el a felelôsség alól. Üsse meg a fickót, kapitány, vagy a legénységünk aggódni fog.";
			link.l1 = "Vért akarsz? Túl unalmas az élet, nincs izgalom? Megkapjátok a véreteket, ti állatok!";
			link.l1.go = "francois_duel";
			link.l2 = "Boo-hoo, annyira félek. Végeztek itt, uraim? Nekem dolgom van.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "Nem fog jól kinézni, ha a kapitányunk meghátrál egy nyilvános kihívás elôl. Csak adj egy jó kis ütést annak a nemesnek, tudjuk, hogy jól bánsz a karddal!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "Gyáva! Szabadelvû! Patkány! Félsz, gazember? Mindannyian tanúi voltatok ennek?! Richard, úgyis megölöm!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "Te gazember! Ez rendben van, hozzászoktam a sérülésekhez. Fel fogok épülni, és...";
			link.l1 = "Fenyegetésnek hangzik, ezredes. És én nem veszem jó néven a fenyegetéseket.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "Ha felépült, ne felejtsen el dicsekedni a sérülésének körülményeivel a tisztek elôtt.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen helyteleníti.", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("Helen helyesel", "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
