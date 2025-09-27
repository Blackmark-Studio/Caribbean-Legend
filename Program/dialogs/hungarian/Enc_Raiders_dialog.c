void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Banda" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Hallottad? A helyi rabló " + GetFullName(npchar) + " új áldozatot talált. Az egyik kapitány megijedt és lefizette. Azt mondják, odaadta neki " + FindRussianMoneyString(iMoney) + ", ô-ô... ", 
				"Igen, kapitány " + GetFullName(pchar) + ", már hallottam, hogy fizetnie kellett " + FindRussianMoneyString(iMoney) + ", hogy megvásárolja a helyi rablót, " + GetFullName(npchar) + ". Na ezt nevezem én balszerencsének! Ha-ha-ha-ha!", 
				"Hallottad, hogy a helyi banditák megtámadtak egy kapitányt? Teljesen kirabolták, elvesztette " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Hallottad? A bandita " + GetFullName(npchar) + " végre igazságot szolgáltatott. Ô és a fiai megpróbáltak kirabolni "+ GetSexPhrase("valami kapitányt, de kiderült, hogy","valami kapitányasszony, de kiderült, hogy") +" egy kemény dió. Szóval a mi kedves rablótársunk összeszarta magát, ha-ha! Ez lesz neki lecke! A helyi gazdákat kirabolni egy dolog, de egy bátor kapitányt kirabolni már más tészta!", 
				"Köszönöm, kapitány " + GetFullName(pchar) + ", hogy végre leszámoltál annak a banditának a bandájával " + GetFullName(npchar) + ". Azok a gazemberek tényleg mindenkinek a nyakára mentek. Még a futárokat is féltünk elküldeni a farmra tejért, mert elfoghatták volna ôket, és kirabolhatták volna az összes pénzt."), 
				"Hallottad, "+ GetSexPhrase("végre valami kapitány","végre valami kapitányasszony") +" megállította azt a gazembert " + GetFullName(npchar) + ", aki a 'dzsungelben' az összes helyi gazdát terrorizálta. Remélem, hogy ez elég sokáig megállítja ôket a mocskos tetteiktôl...", 
				"Hallottad, hogy a helyi bandita " + GetFullName(npchar) + " és az emberei megpróbáltak kirabolni "+ GetSexPhrase("valami kapitányt","valami kapitánynôt") +"? Bah! Semmi ilyesmi! Az a kapitány kemény diónak bizonyult. Azt mondják, úgy üldözte a rablókat az egész dzsungelben, mint cápa a szardíniákat. Hála Istennek, hogy vannak még emberek, akik ki tudnak állni értünk, amikor a hatóságok nem tesznek semmit, túlságosan el vannak foglalva a sötét tetteikkel..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Maradjon ott, ahol van, és dobja el a fegyvert! A pénzed vagy az életed!",
				"Állj ott, ahol vagy, "+ GetSexPhrase("utazó","lass") +"!) Ne nyúlj a fegyveredhez és ne csinálj hirtelen mozdulatokat!",
				"Állj ott, ahol vagy, "+ GetSexPhrase("utazó","lass") +"! Ez egy fizetôs út. Ha át akarsz menni rajta, fizeted az útdíjat."),
				LinkRandPhrase("Hé, "+ GetSexPhrase("haver","lass") +"! Ne olyan gyorsan! Látni akarom, milyen nehéz a pénztárcád.",
				"Gyere közelebb, barátom. Hallani akarom az arany csilingelését az erszényedben.",
				"Várj, "+ GetSexPhrase("pajtás","lány") +". Én és a srácok fogadunk, hogy mennyi arany fér a pénztárcádba. Most ellenôriznünk kell, mielôtt a dolgok erôszakossá válnak."),
				"Ne siess, "+ GetSexPhrase("utazó","drágám") +"! Beszélgessünk egy kicsit a szívünkkel, jó?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Miért mondod ezt a hülyeséget?","Mi a helyzet?", "Mirôl beszélsz?"), "Hogy érted ezt?", "Pontosan mire célzol?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Brigádok?! Kitûnô, már nagyon vágytam egy kis harcra!", 
				"Ó, ti rablók vagytok! Az igazságszolgáltatás elôl bujkáltok, ugye? Nos, úgy tûnik, hogy az igazságszolgáltatás épp most jött értetek...",
				"Nem tanították nektek, hogy idegeneket zavarni a hülyeségeiddel a rossz modor jele? Úgy tûnik, hogy meg kell tanítanom neked ezt a leckét..."),
				LinkRandPhrase("Ó, te aztán szemtelen vagy, nem igaz?! Remélem, hogy a pengéd olyan éles, mint a nyelved.",
				"Látom, hogy a nyelved mestere vagy, remélem, a kardodnak is mestere vagy.",
				"Ó, banditák! Oly sokakat felakasztottak már a fajtádból, de ti még mindig nem tudtok megállni, hogy ne sétáljatok egyenesen az akasztófa felé."),
				LinkRandPhrase(RandPhraseSimple("Ó, rablók! Tudjátok, általában nem vesztegetem a szót a fajtátokra!",
				"Micsoda szemtelen fickó! Bûzlik, mint egy gôzölgô kupac szar, és még egy tisztességes "+ GetSexPhrase("fickót","lányt") +"mer megszólítani."),
				"Nem fogok veled szót vesztegetni, de a pisztolyomat nagyon ékesszólónak fogod találni!",
				"megint brigantik! Nos, akasztófát nem ígérek neked, de pár lyukat biztosan tudok a hasadba vágni!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("És tudod, hogy egy járôrözô csapat szorosan követ engem? Csak füttyentek nekik, és kész.", 
				RandPhraseSimple("Tudod, hívhatom a járôrt, nem félsz tôle? A közelben vannak. Gondolom, téged keresnek.", 
				"Nemrég küldtek ki egy járôrcsapatot, hogy megkeressenek, és bármelyik pillanatban itt lehetnek. Nagy kockázatot vállalsz."),
				RandPhraseSimple("Azt tanácsolnám, hogy fuss, amilyen gyorsan csak tudsz. Egy járôrcsapat erre tart, épp most beszéltem a tisztjükkel.",
				"Szívesen folytatnám a beszélgetésünket, de attól tartok, hogy a járôrözô egység, akivel most találkoztam, nem engedi, hogy az ismeretségünkbôl szoros barátság legyen."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("Ne játszd a hülyét! Készpénzt a szögre, és akkor talán elengedlek!",
				"Nem hallottál még az utazófizetésrôl? Ha nem válsz meg az aranyadtól, egy fejedtôl fogsz megválni!",
				"Heh, ez a hétköznapi kaland egy erszénybe fog kerülni... ha nem haragszom meg."),
				RandPhraseSimple("Ez nagyon egyszerû. Odaadod nekünk az összes aranyadat, aztán szabadon távozhatsz, vagy itt maradsz, és úgyis elveszünk minden aranyadat. De azt hiszem, hogy az utóbbit nem szeretnéd, he-he.",
				"Ne tegyen úgy, mintha nem értené! Add ide az erszényedet, ha nem akarod, hogy elvegyem a holttestedrôl!"),
				"Megmagyarázom, ha már ilyen lassú az eszed. Add ide az összes pénzed, ha becsülöd az életed.");
			Link.l1 = "Az istenit, gazember! Csak " + makeint(makeint(Pchar.money)/20)*10 + " pesóm van.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("A pénzemet akarod? Gyere és vedd el, és meglátom, mennyit érsz!",
				"Hogy merészeled, te fajankó! Majd én megtanítalak jó modorra!",
				"Micsoda önbizalom! Nos, lássuk, hogyan állsz ki egy igazi "+ GetSexPhrase("tengeri farkassal szemben","Louve des mers") +"!"),
				LinkRandPhrase("Ilyen felháborodásért meg kéne korbácsolni!",
				"gazemberek! Imádkozzatok az ördögeitekhez egy meleg helyért a pokolban!",
				"Már rég fel kellett volna akasztani titeket, akasztófamadarak! Nos, úgy tûnik, hogy a szablyámat a véretekkel kell bemocskolnom!"),
				RandPhraseSimple("És mibôl gondoljátok, hogy nektek adom a pénzemet?",
				"És nem vettétek észre, hogy jól fel vagyok fegyverezve, és nem egy egyszerû sétára jöttem ide?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("A francba! Rendben, elmehetsz. De eszedbe ne jusson zajt csapni, amíg itt vagy!", 
					"Ezúttal szerencséd volt, de legközelebb kétszer annyival tartozol nekünk! Ne felejts el emlékeztetni minket, he-he.");
				Link.l1 = RandPhraseSimple("De természetesen.", "Fuss már, amíg még lehet.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("Csendben megölünk, még egy nyikkanást sem fogsz kiadni.", 
						"A francba! Gyorsan meg kell ölnünk téged, mielôtt riadót fújnál.");
					Link.l1 = "Nos, ez a te temetésed. Figyelmeztettelek.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("És miért érdekelne az ôrjáratod? Én fizetem ôket. Szóval, adja ide a pénztárcáját, és ne járassa a száját.", 
						"Azt hiszi, megijeszthet? Én magam vagyok 'az ôrjárat' az olyanokért, mint te ebben a dzsungelben. Még senki sem távozott díj nélkül!");
					Link.l1 = "Az istenit, gazember! Csak " + makeint(makeint(Pchar.money)/20)*10 + " pesóm van.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("Nem fogok engedelmeskedni egy ilyen nyápicnak, mint te.", 
						"csinálok pár új lyukat a koponyádba 'ilyen szemtelenség miatt! Csak hogy egy kicsit kiszellôztessem az agyadat.",
						"Az ilyen szemtelenség nem marad büntetlenül!"),
						"Nem kellett volna ezt tenned...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Hé, ne izgulj annyira, "+ GetSexPhrase("haver","lass") +"! Csak vicceltem! Folytathatod az utadat!",
					"Rendben, meggondoltam magam. Mehetsz, ha már ilyen félelmetes vagy."),
					"Mi, egy "+ GetSexPhrase("'gáláns kapitány'","'militáns lány'") +"? már megint? Rendben, menjetek békében...",
					"Nyugi, "+ GetSexPhrase("haver","lass") +". Látod, tévedtünk, "+ GetSexPhrase(" azt hittük, hogy kereskedô vagy"," azt hittük, hogy kereskedô vagy") +". Elmehetsz.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("Rendben, amíg újra találkozunk!",
					"Abba kéne hagynod az emberek kirablását, amíg még lehet.",
					"Rendben, de ha még egyszer találkozunk..."),
					RandPhraseSimple("Legközelebb figyelj oda, hogy kit fenyegetsz, cur.",
					"Hála Istennek, hogy ma jó kedvem van."),	
					RandPhraseSimple("Ez a bûnözôi mesterség a végén biztosan megöl téged. Búcsúzom.",
					"Ez egy bölcs döntés. Nos, sok szerencsét!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("Nem, haver. Most megtanítalak egy kis jó modorra!",
					"Ó, megijedtél? Nos, az embernek felelnie kell a tetteiért, nem igaz?",
					"Nem! Nem nyugszom, amíg meg nem nyúzlak élve!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("És nyugodtan elmehettél volna! Most már csak magadat hibáztathatod!",
								"Nem kellett volna elkezdened, te gazember! Most úgy fogsz meghalni, mint egy kutya!",
								"Áh jól van! Darabokra téplek! Kivágom a májad és megetetem a kutyákkal!");
				Link.l1 = RandPhraseSimple("Visszatömöm a szavaidat a torkodba!","Kit fenyegetsz, te szemétláda?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Jól van! Add ide és tûnj el!",
					"Nem sok, de még mindig jobb, mint a semmi. Jó egy okos emberrel foglalkozni! Szabadon távozhatsz."),
					"Na ez már más tészta! Ahogy egy barátom mondta 'mindig jó hallgatni valakit, aki okos, de a bolonddal beszélgetni sokkal jobb'! He-he!",
					"Az aranyadért cserébe adok egy tanácsot, nem kellene a dzsungelben sétálnod, ha "+ GetSexPhrase("ilyen nyápic vagy. Igya meg a rumot a kocsmában, hogy maga és az erszénye biztonságban maradjon!","egy lány. Ha kirabolnak, az nem a legrosszabb, ami történhetett veled.") +".");
				Link.l1 = "A francba veled!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "Azt hiszem, meg akarsz csalni! Ne aggódj, megcsiklandozlak a késemmel, és talán leesik valami.";
				Link.l1 = "A fenébe!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("Már megint te? Fuss haza anyukádhoz, mielôtt megharagszom rád!",
				"Mi az? Még nem adtad oda az összes aranyadat? Ha-ha!",
				"Nézd, "+ GetSexPhrase("pajtás","lány") +", elegem van belôled! Tûnj a szemem elôl, amíg még élsz!");
			Link.l1 = "Igen, már megyek is.";
			Link.l1.go = "Exit";
			Link.l2 = "Azt hittem, hogy ez nem lenne fair. Ezért úgy döntöttem, hogy tisztázom a dolgokat...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("Mi másra van még szüksége? Már megegyeztünk, hogy elmész!",
				"Hagyj békén, "+ GetSexPhrase("barátom","lány") +". Én a saját dolgaimmal törôdöm, neked meg a sajátoddal, és nem kéne próbálnunk kijönni egymással!",
				"Távozz most, "+ GetSexPhrase("pajtás","lass") +"! Az istenit, tényleg hajlandó vagy minden pénzed odaadni?");
			Link.l1 = "Igen, már megyek is.";
			Link.l1.go = "Exit";
			Link.l2 = "Emlékszem, hogy nem köszöntél el! Szóval búcsúzzunk el rendesen...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Hagyjatok békén! Segítség! Élni akarok!",
				"Segítség! "+ GetSexPhrase("Ô egy ôrült","Ô egy ôrült") +"! Ne öljetek meg!",
				"Kímélj meg! Én csak egy szerény rabló vagyok! Túl fiatal vagyok a halálhoz!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Ha otthon maradtál volna, tovább éltél volna!",
				"Elôbb kellett volna gondolkodnod!",
				"Tudhattad volna, hogy ennek mindig vannak következményei!"),
				"Elôbb vagy utóbb ennek meg kellett történnie.",
				"Túl késô megbánni, most harcolj a söpredék ellen!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
