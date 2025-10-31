void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ez egy hiba. Vedd fel a kapcsolatot a fejlesztôkkel, és tudasd velük, hogyan és hol találtad meg.";
					link.l1 = RandSwear() + "Tudatni fogom velük!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "Nem vagyok felhatalmazva, hogy veled foglalkozzak. Beszélj a tisztviselônkkel.";
					link.l1 = LinkRandPhrase("Persze...", "Értem.", "Természetesen!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "Mutatkozzon be! Tudni akarom, kivel beszélek!";
					link.l1 = "A nevem " + GetFullName(PChar) + ". Mi folyik itt?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "Cap, a neved " + GetFullName(PChar) + ", ugye?";
					link.l1 = "Igen, igazad van.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "Nem. Összetéveszt valakivel.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name + ", Köszönöm szépen! Ha nem te lennél, a sorsom nem lenne irigylésre méltó... Hogyan köszönhetném meg?";
					link.l1 = "Nincs szükségem semmire...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "Nem utasítanék vissza egy kis jutalmat.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, ez valóban ô... Köszönöm, "+ GetSexPhrase("társam","lass") +", a segítséged nélkül nehéz dolgunk lett volna, nem tudtunk volna kijutni a városból. Tessék, fogd " + FindRussianMoneyString(iMoney) + " és eltûnhetsz. Mi pedig 'beszélgetünk' barátunkkal...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, ez valóban ô... Köszönöm, "+ GetSexPhrase("társam","lass") +", a segítséged nélkül nehéz dolgunk lett volna, nem tudtunk volna kijutni a városból. Tessék, fogd " + FindRussianMoneyString(iMoney) + " és eltûnhetsz. Most azonnal kibelezzük ezt a mocskos árulót!";
						link.l1 = "Hát persze. A viszontlátásra, uraim...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "Micsoda?! Nem, nem engedem, hogy megöljetek egy embert, nem számít, ki az... És nincs szükségem a rohadt pénzedre!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "Szóval... Mi van itt? Kalózok?! Velünk kell jönnöd a parancsnoki irodába, hogy kivizsgáljuk...";
					link.l1 = "Egyáltalán nem vagyunk kalózok! Nem is ismerem ezt az embert! Most bérelte ki és költözött be ebbe a szobába, és nekem nem volt idôm összepakolni a holmimat és elmenni!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "Szóval, mit is mondtál? Van valami üzenete számomra?! Várok!";
					link.l1 = "Tessék...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Hé, te! Igen, te. Látom, hogy maga egy tisztességes és gazdag ember.";
					link.l1 = "Ezt nem mondhatom el rólad.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Várjatok! Hé, "+ GetSexPhrase("haver","csaj") +", mutasd meg, milyen nehéz a pénztárcád!";
					link.l1 = "Szóval, már elpazaroltad az összes templomi pénzt?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Hé, egy csónakban! Hic... Tisztítsátok meg a hajóutat - beszélnem kell a srácokkal...";
					link.l1 = "Nem vagy egy kicsit szédült, haver? Menj, aludd ki magad.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "Hé, sapka! Dobd le a horgonyt!";
					link.l1 = "És mi a fenének kellene nekem....";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "Nem vagy te egy kicsit túl durva?!";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("Üdvözlet neked! Végre az Úr meghallgatta imáinkat, és egy bátor kapitányt küldött erre az elhagyatott partra!",
					"Hála a Gondviselésnek! Most már a helyi dögevôk nem fognak a rothadó csontjainkkal táplálkozni!");
				link.l1 = "Hello, jó ember, én vagyok a kapitány " + GetFullName(PChar) + ". Látom, hogy elég nagy bajban vagy.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "Jóember, nekem is van egy kis dolgom, és nincs idôm a te gondjaidra.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("Ó, kapitány! Micsoda szerencse, hogy Isten jó szelet küldött neked, és erre az elhagyatott helyre vezetett!",
					"Kapitány! Hála a Gondviselésnek, hogy úgy döntöttél, ezen a sivatagos parton vetsz horgonyt!");
				link.l1 = "Hello, jó ember, én vagyok a kapitány " + GetFullName(pchar) + ". Látom, hogy komoly bajban vagy.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "Jóember, nekem is van egy kis dolgom, és nincs idôm a te gondjaidra.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Várj, "+ GetAddress_Form(pchar) +"! Szánna ránk egy percet a drága idejébôl?","Egy nemes mis"+ GetSexPhrase("ter","s") +" meghallgatná e méltatlan emberek alázatos kérését?","Nemes mis"+ GetSexPhrase("ter","s") +", kérem, adjon csak egy keveset drága idejébôl, hogy beszélhessen a szerencsétlenekkel.");
				link.l1 = LinkRandPhrase("Erre nincs idôm.", "Tûnj el, sok dolgom van nélküled is.", "Hagyj békén, nincs idôm rád.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("Mit akarsz?", "Mire van szükséged?", "Mi a baj?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "Szia, sapka! Érdekelnek az indiai csecsebecsék és áruk, amiket nem lehet megvenni a hétköznapi boltokban. Vagy esetleg készpénz?";
					link.l1 = "A magadfajta rágcsálók általában követelnek - nem kínálnak semmit. Miért vagy ilyen furcsán udvarias?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "A pisztolyom általában a magafajta fattyúkkal beszél!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "Hallgatom magát, kapitány. Üzleti ügyben van itt?";
			link.l1 = "Keresem az urat " + pchar.GenQuest.Hold_GenQuest.Name + "?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("Én vagyok mister " + pchar.GenQuest.Hold_GenQuest.Name + ". Kinek köszönhetem a megtiszteltetést?","Megtalálta ôt. Mit tehetek önért?");
			link.l1 = "Kapitány vagyok " + GetFullName(pchar) + ", a " + pchar.GenQuest.Hold_GenQuest.CapName + "kapcsán szeretnék beszélni önnel.";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "És ki az?";
					link.l1 = "Várj egy kicsit... Te vagy " + pchar.GenQuest.Hold_GenQuest.Name + ", és nem tudsz " + pchar.GenQuest.Hold_GenQuest.CapName + "-rôl?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "Hûha! Régen hallottam utoljára arról a vén rókáról? Mi történt vele ezúttal?";
					link.l1 = "Ezúttal komoly bajban van... Fogságban tartják, és szüksége van a segítségedre.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Rendben, csupa fül vagyok.";
					link.l1 = "A hajóját megtámadták a kalózok, és most fogságban van. Azt tanácsolta, hogy találkozzunk a váltságdíjjal kapcsolatban.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Igen, örülök, hogy hallok egy régi barátomról. Hogy van?";
					link.l1 = "A helyzete olyan szörnyû, hogy azt még elképzelni is nehéz.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "Valóban, én vagyok " + pchar.GenQuest.Hold_GenQuest.Name + "! De miért kellene tudnom bármit is errôl a " + pchar.GenQuest.Hold_GenQuest.CapName + "?!";
			dialog.text = "Így van, én vagyok " + pchar.GenQuest.Hold_GenQuest.Name + "! De a " + pchar.GenQuest.Hold_GenQuest.CapName + " név nem mond nekem semmit."; // belamour gen
			link.l1 = "Sajnálom. Talán tévedtem...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "Hûha! És hogyan várják el tôlem, hogy segítsek neki? Szabadítsam ki ôt az összes ellenségének megölésével, vagy mi? Ha-ha-ha-ha!";
			link.l1 = "Nem, nem, erre nincs szükség. Csak át kell adnia " + pchar.GenQuest.Hold_GenQuest.RansomSum + " pezót váltságdíjként.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "Micsoda arcátlanság! És miért kellene váltságdíjat fizetnem érte?! Ô nem a rokonom és nem is a barátom!";
			link.l1 = "Hmm... Azt mondta nekem, hogy te vagy az egyetlen reménye. És említette az adósságodat is...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("Micsoda szemtelen fickó! Ô az, aki tartozik nekem pénzzel, csak hogy tudd! De ez nem ok arra, hogy váltságdíjat kérjek érte, abban a reményben, hogy kifizeti mindkét adósságát.",
				"Micsoda gazember! Átvert, amikor megosztottuk az üzletünket, és most van képe arra kérni, hogy fizessek váltságdíjat érte!",
				"Na ez aztán a meglepetés! Miért kellene váltságdíjat fizetnem érte?! Nem állunk olyan közel egymáshoz.");
			link.l1 = "Tehát elmondhatom neki, hogy nem voltál hajlandó kifizetni a váltságdíját, és nem ismerted el az adósságodat?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "Ó, te jó ég! Milyen adósságról beszélsz? Már mindent elmagyaráztam neked! És ha nincs más kérdése ezen az ostoba történeten kívül, akkor engedje meg, hogy távozzam.";
			link.l1 = "Értem. Nos, nincs több kérdésem hozzád, de a haverodhoz van egy csomó kérdésem.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Hmm... És te, ha jól értem, te vagy az, aki fogva tartja ôt... Nos, azt hiszem, segítek neki.";
			link.l1 = "Nagyon jó. A váltságdíj " + pchar.GenQuest.Hold_GenQuest.RansomSum + " pezó lesz.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "Félreértettél: A városi tanács tagja vagyok. Az alapszabály betartására figyelünk.\n" + 
				"Ôrség!!! Ôrség! Tartóztassátok le a rabszolga-kereskedelem és a hajók kifosztásának gyanújával " + NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation)) + "!";
			link.l1 = "Nos, 'pajtás', csak hadd jussak el hozzád...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "Mit akarsz ezzel mondani?! És hogyan segíthetnék neki?";
			link.l1 = "Fogságban tartják, és megkért, hogy beszéljek veled a váltságdíjról.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Persze, persze. Mindent megteszek, amit tudok. Hol tartják fogva ôket? És mennyi a váltságdíj összege?";
			link.l1 = "A kalózok " + pchar.GenQuest.Hold_GenQuest.RansomSum + " pesót követelnek. A pénzt el kell vinnem a kikötôbe, és akkor a barátodat szabadon engedik.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "Itt a pénz. Szerencsére volt nálam elég.";
			link.l1 = "Igen, ez valóban szerencse. Akkor menj a kikötôbe, és hamarosan újra láthatod a társadat.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "Jó napot, kapitány úr, sajnálom, hogy nem volt szerencsém bemutatkozni. Azt mondták, hogy keresett engem.";
			link.l1 = "Valóban, ha Ön mister " + pchar.GenQuest.Hold_GenQuest.Name + ". Én vagyok a kapitány " + GetFullName(pchar) + ", beszélni akartam önnel.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "És miféle üzlet ez, kapitány " + GetFullName(pchar) + "?";
			link.l1 = "Hallottam, hogy van valamije, amitôl nem bánná, ha megválna.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "Mire céloz ezzel?";
			link.l1 = "Ne legyen ilyen makacs, jóember, nagyon jól ismerem az árnyékos múltját, és egy rögtönzött térképet, amelyen a kincs helye" + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC) + " van feltüntetve.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "Az istenit! Mindig is tudtam, hogy az a gazember" + pchar.GenQuest.Hold_GenQuest.CapName + " elôbb-utóbb ezt is ki fogja fecsegni! Mit gondoltam, amikor felajánlottam neki ezt az üzletet?";
			link.l1 = "Hagyd már abba a nyafogást. Nem akartam bántani... Csak add el nekem ezt a térképet és élj olyan életet, amilyet megszoktál.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "Bárcsak olyan biztos lehetnék ebben... És mennyit ajánlasz érte? Bizonyára tudod, hogy sok arany volt a ládában. Négy férfi vitte, az Úr nyugtassa ôket...";
			link.l1 = "De a " + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_NOM) + " már követelhette a kincsét...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "Ez is igaz... Rendben, hajlandó vagyok eladni neked " + pchar.GenQuest.Hold_GenQuest.Sum + " pezóért. Úgysem merem megzavarni a halottakat.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "Rendben. Megegyeztünk.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "Nem, jóember, az a papírdarab nem ér ennyi pénzt. Viszontlátásra...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "Hogy lehetséges ez, kapitány?! Isten soha nem bocsát meg neked egy ilyen bûnt.";
			link.l1 = "Ez az Ô döntése.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Helló, én vagyok " + pchar.GenQuest.ShipWreck.Name + ", a " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "kapitánya, a hajóm a parttól nem messze lévô zátonyoknál ütközött." + 
					"egész legénységbôl csak néhány matróznak sikerült túlélnie. A dagály kimosott minket erre a kietlen partra. Már hetek óta éheztünk és szomjaztunk " + (5 + hrand(7)) + " mostanra",
					"Helló, én vagyok " + pchar.GenQuest.ShipWreck.Name + ", a " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "kapitánya. A hajónk nem messze innen lezuhant." + 
					"hajóroncsokon sikerült eljutnunk erre a partra, de ez a hely lakatlannak tûnik. Kagylókon és pálmagyümölcsökön voltunk kénytelenek túlélni már " + (5 + hrand(7)) + " hetek óta.");
				link.l1 = RandPhraseSimple("És hányan maradtatok?", "És hányan maradtatok életben?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "Ó, kapitány, a veszteségeink tényleg szörnyûek... Jó napot, én vagyok " + pchar.GenQuest.ShipWreck.Name + ", a " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen")) + " kapitány és a" + pchar.GenQuest.ShipWreck.ShipTypeName + " ' tulajdonosa. Vagy mondhatnám úgy is, hogy volt kapitány és tulajdonos. " + 
					"Ez a szemétláda " + pchar.GenQuest.ShipWreck.BadName + " , akit felbéreltem a " + XI_ConvertString("Colony" + pchar.GenQuest.ShipWreck.City + "Voc") + " , lázadásra provokálta a legénységemet. Végül ezen az elveszett helyen kötöttünk ki. Ez " + (5 + hrand(7)) + " hetekkel ezelôtt történt.";
				link.l1 = "És aztán? Az egész legénységed csatlakozott a lázadókhoz?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("Az egész legénységbôl csak " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " maradt életben. A többiek elpusztultak; többen közülük már itt meghaltak a sebek és a láz miatt.",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " were lucky enough. Others have met their end... either in the deep or in the dunes of this coast.");
			link.l1 = LinkRandPhrase("Igen, ez egy irigylésre méltó sors. De ilyen a tengerészek sorsa - bárki kerülhet a helyedbe.",
				"Értem... Isten minden életet megtart, csak túl elfoglalt ahhoz, hogy mindenkire emlékezzen.",
				"Valóban. Az ember javasol, de Isten rendelkezik.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "Persze, hogy nem! Sokan voltak, akik nem voltak hajlandók csatlakozni a lázadókhoz, de ezek a gazemberek elfoglalták az arzenált, és még jó, hogy nem tanúsítottunk ellenállást, különben egyenesen megöltek volna minket. Itt már sokan meghaltak a lázban és a mérges rovarok mérgezésében, csak " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " maradtak életben. Hála Istennek, végre vége a megpróbáltatásainknak.";
			link.l1 = RandPhraseSimple("Igen, ez biztosan balszerencse volt.","Hát igen, sok furcsa dolog történhet ezeken az isten háta mögötti helyeken.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Tarts ki, barátom. És honnan tudhatnám, hogy nem lázadásra buzdítóként tettek ki benneteket a partra?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Kapitány, remélem, hogy van néhány szabad szekrény a hajóján. Mindannyiunknak van családja, és valószínûleg gyászolják a veszteségünket, miközben beszélgetünk. Nagyon hálásak lennénk önnek.",
				"Kapitány, teljesen kétségbe vagyunk esve, ön az egyetlen reményünk. Kérem, ne tagadja meg tôlünk a segítségét, vigyen el minket errôl az isten háta mögötti földrôl.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... és hova szeretnéd, hogy elvigyelek?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("Nagyon sajnálom, de még egy ingyenes függôágy sincs, a kabinokról nem is beszélve. A matrózok a fedélzeten alszanak, még egy ôrség után sem tudnak rendesen kipihenni magukat...",
				"Nagyon nem szeretnék csalódást okozni, de a hajó túlterhelt, és az embereknek a rossz idôben kell aludniuk. Ha járvány törne ki, a legénység felét elveszíteném."), 
				RandPhraseSimple("Nagyon sajnálom, de a hajómon egyáltalán nincs szabad hely a legénységnek. Nem tudok több utast felvenni a fedélzetre.",
				"Csalódást kell okoznom, de a hajóm túlterhelt. Félek a járványtól."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Ön tapasztalt tengerész, és tudnia kell, hogy egy hajótörést szenvedett ember jelenléte nagyon rossz jel. A tengerészeim egyszerûen kidobnak titeket a fedélzetrôl.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "Mirôl beszélsz, " + GetAddress_Form(npchar) + " " + pchar.lastname + "?! Legyen szíved! Tárgyaló vagyok, jól ismert a Karib-térségben! Hát... Azt hiszem, régen az voltam. Most már nem, hajó és pénz nélkül...";
			link.l1 = "Hogyhogy... Fogadok, hogy ti voltatok a lázadás tényleges felbujtói, és most megkaptátok, amit megérdemeltetek.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "De micsoda gazember az a " + pchar.GenQuest.ShipWreck.BadName + "! Tényleg hagyod, hogy ezt megússza és aláveted magad a sorsodnak?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "A " + NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)) + "bármely településére.";
					link.l1 = "Nos, van elég szabad szekrényem és függôágyam. Pakoljatok be a csónakba.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Hmm... Csaták állnak elôttünk, és nem tudom, hol lennél nagyobb biztonságban, a hajóm fedélzetén vagy ebben a hangulatos öbölben.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "Dunkerque-re! Anyám ott él...";
					link.l1 = "Megôrültél, vagy mi?! Gondolom, túl sok ütést kaptál a fejedre...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Akárhová akarsz, nekünk mindegy. Úgysincs mibôl fizetnünk...";
				link.l1 = "Nos, van elég szabad szekrényem és függôágyam. Pakoljatok be a csónakba.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Hmm... Csaták állnak elôttünk, és nem tudom, hol lennél nagyobb biztonságban, a hajóm fedélzetén vagy ebben a hangulatos öbölben.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "De ha megtagadod, akkor biztosan halálra ítélsz minket! Nos, megpróbálunk utat törni magunknak a hajóhoz, még ha az életünkbe kerül is!";
					link.l1 = "Micsoda? Nézzetek magatokra, alig álltok a lábatokon...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "Megpróbálhatod...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "De nem hagyhattok itt minket! A segítségetek nélkül hamarosan mindannyian elpusztulunk!";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "Az egyetlen dolog, amit tehetek értetek, hogy hagyok nektek elég élelmet és gyógyszert, és adok nektek egy hajót. Legalább nem fogtok éhen és szomjan halni. Ami a hajózást illeti, azt nem kell megtanítanom nektek.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "Az egyetlen dolog, amit tehetek értetek, hogy hagyok nektek elég élelmet és gyógyszert, és adok nektek egy hajót. Legalább nem fogtok éhen és szomjan halni. Ami a hajózást illeti, azt nem kell megtanítanom nektek.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "Egy hónapra elegendô gyógyszert, lôszert, rumot és élelmiszert hagyhatok nektek. Vagy magam jövök vissza, vagy küldök értetek valakit.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "De ha megtagadod, akkor biztosan halálra ítélsz minket! Nos, megpróbálunk utat törni magunknak a hajóhoz, még ha az életünkbe kerül is!";
						link.l1 = "Micsoda? Nézzetek magatokra, alig álltok a lábatokon...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "Megpróbálhatod...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "Az egyetlen dolog, amit tehetek értetek, hogy elegendô élelmiszert és gyógyszert hagyok nektek, és adok nektek egy hajót. Legalább nem fogtok éhen és szomjan halni; ami a tengerészetet illeti, arra nem kell megtanítanom titeket.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "De ha megtagadod, akkor biztosan halálra ítélsz minket! Nos, megpróbálunk utat törni magunknak a hajóhoz, még ha az életünkbe kerül is!";
							link.l1 = "Micsoda? Nézzetek magatokra, alig álltok a lábatokon...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "Megpróbálhatod...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "Hogy tehetted ezt velünk?!... Nemcsak a Tengeri Szabályzatot hagytátok figyelmen kívül, hanem a becsületeteket is bemocskoltátok!";
							link.l1 = "Bizonyára nem te vagy az, aki a becsületemrôl beszél, garnélarák!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "Az egyetlen dolog, amit tehetek értetek, hogy hagyok nektek elég élelmet és gyógyszert, és adok nektek egy hajót. Legalább nem fogtok éhen és szomjan halni. Ami a hajózást illeti, azt nem kell megtanítanom nektek.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "Igazad van, nincs esélyünk. Rendben, az Isten legyen a bírátok, és mindenki megkapja, ami jár neki.";
			link.l1 = "Nos, én meg tudok birkózni vele...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Hát... Nem hagysz nekünk más választást... Imádkozunk, hogy a viharok és a szomjúság ne vegyék el az életünket, mielôtt lakott területre érünk...";
			link.l1 = "Viszontlátásra. Az Úr vigyázzon rátok...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Úgy tûnik, nincs más választásunk... De könyörgöm, kapitány, kérem, térjen vissza, amint tud, vagy küldjön egy expedíciós hajót.";
			link.l1 = "Majd kitalálok valamit. Csak várjon.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Kapitány, kérem, ne feledje, hogy ön az egyetlen reményünk...","Miért maradsz még? Minden itt töltött perc elviselhetetlen számunkra...");
			link.l1 = "Mindent megteszek, amit tudok. Viszontlátásra...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Viszlát, kapitány... Fel kell készülnünk az útra.","Farewell... És gyújtsd meg a gyertyákat, hogy megmentsd a lelkünket...");
			link.l1 = "Viszontlátásra. Az Úr vigyázzon rátok...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "Hogy tehetted ezt velünk?! Nem csak a Tengeri Szabályzatot hagytad figyelmen kívül, de a becsületedet is bemocskoltad!";
			link.l1 = "Bizonyára nem te vagy az, aki a becsületemrôl beszél, garnélarák!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "Köszönöm, kapitány! A berakodás nem fog sok idôt igénybe venni. Istenem, mennyire imádkoztunk, hogy eljöjjön ez a pillanat!";
			link.l1 = "Ez nagyszerû. Remélem, hogy a megpróbáltatásoknak hamarosan vége lesz.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "hajótörött");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "hajótörött");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "Köszönöm, kapitány! A berakodás nem fog sok idôt igénybe venni. Istenem, mennyire imádkoztunk, hogy eljöjjön ez a pillanat!";
			link.l1 = "Ez nagyszerû. Remélem, hogy a megpróbáltatásoknak hamarosan vége lesz.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "hajótörött");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "hajótörött");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "Gyerünk, gyerünk! Tényleg, kapitány?! Félünk a haláltól?! Egyszer már átvertük, meg tudjuk csinálni újra. Csak nem akarjuk így elveszíteni az életünket. Hogy itt rohadjunk meg, egyedül\nÖrömmel csatlakoznánk a legénységéhez, és bátran harcolnánk a zászlaja alatt. Csak ne hagyjanak itt minket...";
			link.l1 = "Látom, hogy készek vagytok bármit megtenni, csak hogy kijussatok innen. De nézzétek csak meg magatokat, miféle tengerészek lehettek?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "Ez egy jó ötlet. Gondolom, felbérelhetlek titeket.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "Nem-nem, nem viccelek! Kérem, vigyenek ki ebbôl a karibi mészárszékbôl, ebbôl a pokolból! Tudja, én egy gazdag ember vagyok... egy nagyon gazdag ember. Még maga a pápa sem látott ennyi aranyat egész életében. Aranyat fogok önnek adni...";
			link.l1 = "Ó, te jó ég... Rendben, szálljatok be a csónakba...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "hajótörött");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "hajótörött");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("Miért húzza az idôt, kapitány? Parancsot kaptam a horgony felhúzására.","Sajnáljuk, kapitány úr, de fel kell készülnünk a kihajózásra.","Olyan szerencsések vagyunk, hogy úgy döntöttek, idejönnek!");
			link.l1 = "Siessetek. A hajó nem fog senkire sem várni.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Kapitány, nincs vesztenivalónk. A halál már a nyomunkban jár... Inkább halunk meg egy tisztességes küzdelemben, minthogy felfaljanak minket a büdös prérifarkasok...";
			link.l1 = "Ó, akkor ez egy kihívás?! Rendben, rendezzük vitáinkat"+ GetSexPhrase(", mint a férfiak","") +"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "Esküszöm, kapitány, nem fogod megbánni. Mi leszünk a legjobb hajósok az egész szigetvilágban.";
			link.l1 = "Nagyszerû! Szálljatok be a hajóba...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("A csapatod nôtt " + pchar.GenQuest.ShipWreck.Qty + " emberrel" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("Esküszöm, kapitány, nem fogja megbánni.", "Jól döntött, kapitány.", "Kapitány, nyugodt lehet, hogy önnek is ugyanolyan szerencséje volt, mint nekünk!");
			link.l1 = RandPhraseSimple("Remélem is.", "Siess. A hajó nem fog senkire sem várni.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Kapitány, miért sérti meg a becsületes embereket ilyen bizalmatlansággal? Csak nézd meg az arcukat, tényleg azt hiszed, hogy lázadók lehetnek?";
			link.l1 = "Rendben, de most mit csináljak veled?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "És mit tehetnék? Most legalább élek... és hálát adok Istennek, hogy megúsztam! De ha segítesz visszaszerezni a hajómat, és bosszút állni a megaláztatásomért, hajlandó vagyok neked adni bármit, amit ez a gazember kirabolt és elrejtett a raktérben.";
			link.l1 = "Rendben, megegyeztünk.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "Nem vagyunk abban a helyzetben, hogy parancsokat adjunk ki. Rajtatok múlik, csak hozzatok el minket bármelyik településre, vagy vegyetek be a legénységetekbe.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "Rendben, felveszlek titeket a legénységembe. De semmi hülyéskedés! Szigorú fegyelem van a hajómon!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "Nem viszem magukat sehova. Már így is van elég gengszter a legénységemben.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "Rendben, szállj be a hajóba, és elviszlek valahova.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "Ó, hát... Nem hagysz nekünk más választást... Imádkozni fogunk, hogy a Gondviselés kegyes legyen hozzánk, és engedjen ki minket errôl a veszélyes helyrôl. Ha Isten is úgy akarja, talán még eljutunk a lakott földre...";
			link.l1 = "Viszontlátásra. Az Úr vigyázzon rátok...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Köszönöm szépen, kapitány " + GetFullName(pchar) + "! Annyi mindent tettél értünk, hogy semmilyen hála nem lenne elég, hogy megháláljuk. És bár minden vagyonunk egy rézpénzt sem ér, engedd meg, hogy átadjam neked ezt az amulettet. Nagyon hasznos lenne egy kapitánynak, aki gyakran vesz részt tengeri csatákban.";
				link.l1 = "Köszönjük az ajándékot! Ez a csecsebecse valóban nagyon hasznos! Isten veled, kapitány " + pchar.GenQuest.ShipWreck.Name + " és sok szerencsét az utazásaidhoz.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Kapitány, köszönöm szépen. Sokat tettél értünk, és bármilyen jutalom alantas lenne a hálánkhoz képest. Kérem, fogadja el ezt a szerény ajándékot hálánk jeléül.";
				link.l1 = "Tényleg, nem kellett volna fáradnia... Nektek sokkal nagyobb szükségetek van a pénzre, mint nekem. Mégis, ez nagyon kedves tôletek. Köszönöm, és viszlát.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Kapitány, tudja, hogy vannak emberek, akik a világ végéig elmennének önért, mostantól kezdve. Kár, hogy nincs mit megköszönnöm. Mégis... Kérem, fogadja el ezt a csecsebecsét, abban a szerencsétlen öbölben találtam. Remélem, szerencsét hoz neked.";
			link.l1 = "Bárki megtette volna ugyanezt a helyemben. Viszlát.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Kapitány, máris Dunkirk van?","Tényleg Dunkerque-ben vagyunk, kapitány?"),RandPhraseSimple("Kapitány, ez már Európa?","Ilyen gyorsan elhajóztunk Európába?"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "A-ha...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Még nem...","Mi az a Dunkirk? Milyen Európa? Nézz körül!","Ó, Istenem!");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("De kapitány, ígéretet tettél!","Hogy szeghette meg a szavát, kapitány?","És mikor érünk Európába?");
			if(rand(100) < 70)
			{
				link.l1 = "Rendben. Uram, szedje össze az embereit és a holmiját, és menjen, ahová akar.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("Biztos vagy benne, hogy tényleg el kell jutnunk Dunkerque-be?","Tudod, a hajóm nem arra való, hogy átvitorlázzon az óceánon.","Kapitány, és mi a baj a Karib-tengerrel?"), 
					LinkRandPhrase("De nekem más terveim voltak...","Miért akarsz egyáltalán Európába menni...","Gondolj csak arra a sok csábító mulatt nôre! Európában sosem fogsz velük találkozni..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "De hogyan? Hogy merészeled?! Miféle árulás ez?! Majd én megtanítalak, hogyan maradj hû a szavadhoz!";
			link.l1 = "Nos, te akartad...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Nem! El kell jutnom Dunkirkbe!","Ahelyett, hogy földrajzot tanítasz nekem, inkább teljesítsd a kötelességedet!"), 
				RandPhraseSimple("Nem akarok hallani róla! Megígérted, hogy elviszel Európába!","Nem, kapitány úr, ez nem fog menni. Európába hajózunk."),"Nem fogok nyomorult életet élni hátralévô napjaimig ebben a lyukban!");
			link.l1 = "Ó, nem tudom, hogy ennek vége lesz-e...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "Nézd! Ez egy tisztességes ember! Európa! Az átkozott öreg Európa! Yes-yes-yes!\nOh, yes! Te teljesítetted az alku rád esô részét, és én is teljesíteni fogom. Tessék, fogd a térképnek ezt a felét. A másik fele a társamé volt. Nyugodj békében, vagy nyugodj vízben? Mindegy. Ô volt az, aki rábeszélt, hogy vegyek részt ebben a kalandban.";
			link.l1 = "Várjon, szóval maga nem tengerész? A társa kapitány volt?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "Ó, te jó ég!... Persze, hogy nem! Nos, igen, nem vagyok tengerész. És ôt egy hatalmas hullám a fedélzetre sodorta, amikor úgy döntött, hogy távolabb hajózik a parttól. Akkor átvettem a parancsnokságot, és megparancsoltam, hogy hajózzanak be az öbölbe... És jól haladtunk a zátonyok között, amíg egy végzetes baleset el nem döntött mindent. A hajó egy szikladarabnak ütközött, és elsüllyedt...";
			link.l1 = "Ez aztán a hozzá nem értés igazi bizonyítéka...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Figyelj, ez tényleg Dunkirk? Gondolj csak bele, még csak hat hónap telt el, és az egész hely megváltozott\nTessék, vegyük a térképet, pontosabban annak egy részét. A kincs egy barlangban van! Fogalmam sincs, hogy mi a sziget, de te tapasztalt tengerész vagy, egyszer majd megtalálod a pontos helyet... Garantálom, hogy számtalan gazdagsága van az aaarrrrrhg nevû kalóznak...";
			link.l1 = "Köszönöm, jóember. Még ha nincs is kincs, nem leszek túlságosan elkeseredve. Viszontlátásra, és remélem, hogy soha többé nem látjuk egymást...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("Azt mondják, valami ôrült bukkant fel nemrég a szigeten. Mindenkinek azt mondja, hogy elvesztette az iratait, és nem, megpróbál kapitánynak jelentkezni egy Dunkerque-be tartó hajóra.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine, recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught, he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("Kapitány úr, nagyszerû, hogy nem feledkezett meg rólunk! Mindannyian imádkoztunk érted!","Kapitány, közel van a megváltásunk? Hogy imádkoztunk érte, hogy eljöjjön! Néhányan már kezdtek kétségbeesni...");
			link.l1 = "Üdvözlet, " + pchar.GenQuest.ShipWreck.Name + "! Hogy hagyhattam ilyen állapotban a kollégáimat? Hová?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Üdvözlet, " + pchar.GenQuest.ShipWreck.Name + "! Attól tartok, rossz hírem van számodra. Változott a terv, és nem tudlak felvenni a fedélzetre.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "Nem érdekel minket, hogy hova megyünk, amíg elég messze van ettôl az átkozott helytôl... Megengedné, hogy elkezdjük a berakodást?";
			link.l1 = "Igen, csak rajta. Hamarosan vége a próbatételeknek.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Köszönöm, kapitány. Már kezdtünk kétségbeesni, de ön szó szerint visszahozott minket az életbe.";
			link.l1 = "Nem volt semmi... Viszlát.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "Mi a fenét akarsz tôlem?";
			link.l1 = "Azért jöttem"+ GetSexPhrase("","") +" , hogy üdvözletet küldjek egy" + pchar.GenQuest.ShipWreck.Name + "nevû személytôl. Ismeri ôt?"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "Kár, hogy nem fojtottam meg azt a gazembert korábban. Nos, akkor, azt hiszem, eljött az idô, hogy megfizessek a jóindulatomért...";
			link.l1 = "Valóban... És az idô épp kifutott...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "Szép munka, kapitány! Minden a megbeszéltek szerint? Mi megkapjuk a hajót, te pedig a rakományt?";
			link.l1 = "Persze. Fogjátok a hajót és használjátok ki.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "Üdvözlöm, kapitány " + GetFullName(pchar) + ".";
			link.l1 = "Szóval, hogy tetszik a hajód?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Heh, nyikorog és nyikorog, akárcsak én magam. Azt hiszem, mindkettônknek nincs már sok ideje hátra, hogy a nyílt tengeren hajózzunk...";
			link.l1 = "Sok szerencsét, akkor...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Kapitány, kérem, segítsen nekünk, hogy szerezzünk egy hajót vagy egy hosszú csónakot, egy tartánt, bármit, igazán nem számít. Olyan körülmények között vagyunk, hogy menekülnünk kell errôl a barátságtalan helyrôl, de nem jelenhetünk meg a településen.";
					link.l1 = "És miféle körülmények azok?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Kapitány, kölcsönadna nekünk pár száz pezót? Nem kérnénk, de tényleg nagy szükségünk van rá.";
					link.l1 = "Azt mondja, nagy szükségünk van rá? Lefogadom, hogy elfogyott a rum, és ez bizonyára nagy szükség.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Kapitány úr, lenne olyan kedves, és elvinné szerény társaságunkat a " + XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen") + "világítótoronyhoz.";
					link.l1 = "Ahogy elnézlek, nem mondanám, hogy túl szerény vagy.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("Péntekenként nem adok alamizsnát.","Nincs idôm erre az ostobaságra.","Nem segítek idegen embereknek.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "Szökevények vagyunk... a " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Gen")) + ". Hamarosan a volt gazda észreveszi... és akkor biztosan halottak vagyunk.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "Szóval tudod, hogy kell kezelni a vitorlákat?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "És mivel fogsz fizetni?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "Nem a legjobbkor gondolkodunk a rumon. Már egy hete szöktünk meg, most pedig a dzsungelben bujkálunk és éhezünk.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Nos, tegyük fel, adhatok nektek pénzt... és aztán mi lesz? Addig bujkáltok, amíg végül egy ôrjárat fel nem fedez titeket?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "Rendben, mennyi kell?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "Rövid beszélgetés a magadfajtákkal, fejeket a hóhérpadra, és ennyi!";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "És mi mást tehetnénk még? Szívesen kapnánk munkát matrózként, de tekintve, hogy szökevények vagyunk, ki vesz fel minket?";
				link.l1 = "Felveszlek, ha tudsz bánni a vitorlákkal, és nem mutatod a gyávaság jeleit.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "A helyi hajósokkal már megegyeztünk. Ahhoz, hogy kijussunk innen, csak háromezer hiányzik.";
				link.l1 = "Nos, itt van a háromezer, ha ez tényleg segíteni akar.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Hát, nem is tudom... Ezek a saját problémáitok, és én nem fogok segíteni a megoldásukban.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Kérem, kapitány úr, béreljen fel minket, biztosan nem fogja megbánni! Kalózkodtunk a " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " Adriai-tengeren, míg végül felakasztották, és minket, " + pchar.GenQuest.Convict.ConvictQty + " embereket ide számûztek.";
			link.l1 = "Jól van, rendben. Van egy hely a közelben, a " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + ". Éjfél körül felveszlek ott. Remélem, nem fogsz eltévedni.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "Persze, ez nagy segítségünkre lesz! Ma fogunk vitorlát bontani, ha a szél kedvezô és a halászok nem hagynak cserben minket. Köszönöm, kapitány, és Isten segítsen...";
				link.l1 = "Sok szerencsét neked is.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "Ez aztán a szerencse! Nem is remélhettük, hogy ilyen gyorsan megkapjuk a pénzt. Kapitány, engedje meg, hogy bemutassak egy csecsebecsét, amit a volt fônökünktôl vettünk el. Talán önnek is szerencsét hoz.";
				link.l1 = "Köszönöm, ez egy tisztességes dolog, az biztos. Sok szerencsét.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Most van egy nagylelkû ember, aki nem fél költeni az érmét, mert tudja, hogyan kell keresni!\nA múlt éjjel láttuk a helyi csempészek rakodását " + MerPrm.QuestGoodsIdx + ". Sötét volt, de sikerült kivenni a hajó nevét az egyik csónak oldalán, '" + MerPrm.ShipName + "'... és az a hajó a " + MerPrm.nation + "zászló alatt hajózik. Talán hasznosnak találod ezt az információt, he-he.";			
				link.l1 = "Hmm... Nos, talán igen. Isten veletek, nyomkeresôk.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "Ó, nem vagyunk abban a helyzetben, hogy követeléseket támasszunk. Bármit is tudtok nélkülözni, bármiért hálásak leszünk.";
			link.l1 = "300 pezó.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 pezó.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 pezó.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Köszönjük, kapitány, és Isten vigyázzon önre...";
			link.l1 = "Sok szerencsét neked is.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "Ez aztán a szerencse! Nem is remélhettük, hogy ilyen gyorsan megkapjuk a pénzt. Kapitány, engedje meg, hogy bemutassak egy csecsebecsét, amit a volt fônökünktôl vettünk el. Talán önnek is szerencsét hoz.";
				link.l1 = "Köszönöm, ez egy tisztességes dolog, az biztos. Sok szerencsét.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Köszönjük, kapitány, és Isten vigyázzon önre...";
				link.l1 = "Sok szerencsét neked is.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "Ez aztán a szerencse! Nem is remélhettük, hogy ilyen gyorsan megkapjuk a pénzt. Kapitány, engedje meg, hogy bemutassak egy csecsebecsét, amit a volt fônökünktôl vettünk el. Talán önnek is szerencsét hoz.";
				link.l1 = "Köszönöm, ez egy tisztességes dolog, az biztos. Sok szerencsét.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Most van egy nagylelkû ember, aki nem fél költeni az érmét, mert tudja, hogyan kell keresni!\nMúlt éjjel láttuk a helyi csempészek rakodását " + MerPrm.QuestGoodsIdx + ". Sötét volt, de sikerült kivenni a hajó nevét az egyik hajó oldalán '" + MerPrm.ShipName + "'... és ez a hajó a " + MerPrm.nation + "zászló alatt hajózik. Talán hasznosnak találod ezt az információt, he-he.";
				link.l1 = "Hmm... Nos, talán igen. Isten veletek, nyomkeresôk.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "Ne bûvöljön el minket, kapitány! Van egy tisztességes csecsebecsénk, kérem, fogadja el váltságdíjként és engedjen el minket...";
				link.l1 = "Adjátok át, és tûnjetek el, amíg még lehet.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Most már nincs más választásunk, az ember mégsem hal meg kétszer. Az utolsó csatára, fiúk!";
				link.l1 = "Az már egy másik történet!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Hát, mi bizony nem vagyunk szentek, de nem akarunk semmiért veszekedni... Szökevények vagyunk, és minél elôbb el kell tûnnünk innen.";
			link.l1 = "Van valami, amivel fizetni tudnának az átkelésért?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "Ó, értem... Nem, nem fogom bemocskolni a hírnevem miattad. Viszontlátásra.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Persze! Mi már hozzászoktunk a beszálláshoz meg ilyesmihez. Majdnem két éven át mi és a néhai " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " terrorizáltuk a helyi kereskedôket, de sajnos ôt felakasztották, és " + pchar.GenQuest.Convict.ConvictQty + " embereinket büntetômunkára ítélték.";
			link.l1 = "Mi lenne, ha csatlakoznál a csapatomhoz? Nagylelkû vagyok"+ GetSexPhrase("","") +", de nem ígérek neked békés életet.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "Igen, megragadtunk valamit " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Gen")) + ", így duplán fizethetünk. SO bízom benne, hogy az ár megegyezik. És ne merészelj ôröket hozni. Nem bocsátjuk meg az árulást..."; // belamour gen
			link.l1 = "Rendben, várj meg a parton " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen") + ". Éjfélhez közeledve ott lesz egy hajó ... És nem akarok trükköket látni!"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "Nem, barátaim. Mi van, ha odaadom nektek a hajót, és ti hátba szúrtok? Nem, én nem segítek neked ebben az ügyben.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "Nagy örömmel, "+ GetSexPhrase("mister","miss") +" kapitány. Ezt már jól ismerjük, és ilyen ajánlásokkal amúgy sem biztos, hogy felvesznek minket a haditengerészethez, he-he.";
			link.l1 = "Jól van, rendben. Van egy hely a közelben, a " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + ". Éjfél után felveszlek ott. Remélem, nem fogsz eltévedni.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "De, "+ GetSexPhrase("mister","miss") +" kapitány, még nagyobb kockázatot vállalunk? Mi van, ha úgy dönt, hogy felad minket a parancsnoknak?";
			link.l1 = "Ez igaz... Rendben, ha nem leszek ott hajnalig, akkor az alku érvényét veszti.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "Ó, kapitány, számítottunk magára...";
				link.l1 = "Nem probléma. Ha van pénzed, akkor találsz átjárót. Viszontlátásra.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Maga okos, kapitány, ahogy látom. Biztos vagyok benne, hogy egyenesen a parancsnokhoz fogsz szaladni, ugye? És azt hiszi, hogy ezt megússza?";
				link.l1 = "És azt tervezi, hogy megállít engem, ahogy látom?! Akkor azt kapod, amit megérdemelsz!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "Van valami. A fônökünk pénztárában turkáltunk, de aztán felhördült a dolog, és harcosan kellett áttörnünk. Csak " + PChar.GenQuest.Convict.ConvictQty + " embernek sikerült túlélnie.";
			link.l1 = "A körülményeket figyelembe véve nem adok olcsóbb utat, mint " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + " pezó személyenként.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Látom, hogy nem vagytok gyávák. Csatlakoznátok a legénységemhez?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "És van választásunk? Rendben, " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + "...";
			link.l1 = "Ezután menjen a " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat") + ". Éjfél után küldök neked egy hajót."; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "És miért is ne? Ismerjük ezt a cuccot, mi már kalózkodtunk " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " a " + RandPhraseSimple("Gibraltárban","La Manche csatorna") + " mielôtt itt ragadtunk volna.";
			link.l1 = "Jól van, rendben. Van egy hely a közelben, a " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + ". Éjfél körül felveszlek ott. Remélem, nem fogsz eltévedni.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Eh, kapitány, te is voltál egyszer szegény, üres zsebeid voltak. És most megveted az olyan egyszerû embereket, mint mi.", "Kapitány, nem helyes így bánni az egyszerû emberekkel. Mindannyian egy Isten alatt állunk."), 
											RandPhraseSimple("Heh, az emberek manapság tényleg túl önzôek. Úgy élnek, mintha még két évszázad lenne elôttük.","Ó, látom, hogy csak most érkeztél Európából, még nem érezted a trópusi szemétdombunk bûzét."));
			link.l1 = LinkRandPhrase("Szégyent akarsz rám hozni? A nyelved pár centivel rövidebb lesz!","Megfélemlítesz? Kapaszkodj a kalapodba!","Filozófus vagy, vagy mi? Majd én beléd verek egy kis értelmet!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("Szóval, kapitány? Hozott nekünk egy hajót?","Üdvözletem, kapitány. Szóval, mi a helyzet az üzletünkkel?","Üdvözlöm, kapitány. Már kezdtünk aggódni. Gondolom, minden rendben ment?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Igen, itt a kád. És ne feledkezz meg a fizetésrôl. Fizettem érte " + pchar.GenQuest.Convict.ShipPrice + " érméket, szóval tartozol nekem " + sti(pchar.GenQuest.Convict.ShipPrice) * 2 + ", ahogy megegyeztünk.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "Nem, meggondoltam magam. Keress magadnak egy másik segédet. Viszlát...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "De hát persze! Elvették a szabadságunkat, de a lelkiismeretünket nem! Kérem, fogadja el a pénzét, határtalan hálánkkal együtt. Nagyon sokat segítettél nekünk. Nem bánjátok, ha ezüstrudakban fizetünk nektek?";
					link.l1 = "Persze, hogy nem. Sok szerencsét az utatokhoz. És imádkozzatok, hogy ne a nyílt tengeren találkozzunk, mert akkor rövidre zárlak titeket.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Kapitány, tudja, úgy gondoltuk, hogy a pénz nem olyan fontos az életben. És ôszintén szólva, nekünk sokkal nagyobb szükségünk van rá, mint neked. De van egy dolog, amit az elôzô fônökünktôl loptunk. Talán ez sokkal jobban érdekelné önt, mint az arany. Akarod megnézni?";
					link.l1 = "Igen, igazad van. Ez valóban egy csodálatos dolog. Rendben van, megegyeztünk, köszönöm és viszlát.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "Egyáltalán miért kell ennyi pénz, kapitány? Úgyis gazdag vagy, és nekünk végünk, ha nem kapjuk meg ezt a hajót. Úgyhogy... egyszerûen elveszünk tôled. Nem haragszunk.";
					link.l1 = "Ez volt az utolsó hibája. Hajó nélkül még el tudtatok úszni, de most vagy úsztok, vagy elsüllyedtek.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("Szóval, kapitány? Elkezdhetjük a berakodást?","Végre! Már kezdtünk aggódni, azt hittük, hogy meggondolta magát.");
			link.l1 = "Sajnálom, de megváltozott a tervem. Mostantól más kapitányt kell keresniük.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Pakoljatok fel a hajóra, nincs sok idôm.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Pakoljatok fel a hajóra, nincs sok idôm.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "A francba veled! Biztos, hogy már küldtél utánunk egy ôrjáratot?! Ezt nem úszod meg!";
				link.l1 = "Mirôl beszélsz?! Meg akarsz halni, vagy mi?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Kapitány "+ GetSexPhrase(", állja a szavát, vagy mi?","?") +" Vagy csak egy kibaszott fecsegô...";
				link.l1 = "Jobb, ha vigyázol a nyelvedre...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("Ó, köszönöm, "+ GetSexPhrase("kedves ember","szép lány") +".","Köszönöm, kapitány úr, tényleg elvitt a huroktól.","Nagyon köszönöm ezt a szép utazást.");
			link.l1 = LinkRandPhrase("Ez mind szép és jó, de én a pénzre várok.","Itt az ideje fizetni, tudod.","Készpénz a szögre, ahogy megbeszéltük.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Persze, micsoda kérdések! Itt van a pénze aranyrudakban, és kérem fogadja ôszinte hálánkat.";
					link.l1 = "Sok szerencsét neked is. Viszontlátásra.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Kapitány, tudod, azt gondoltuk, hogy a pénz tényleg nem olyan fontos az életben. És ôszintén szólva, nekünk sokkal nagyobb szükségünk van rá, mint önöknek. De van egy dolog, amit elloptunk a korábbi fônökünktôl. Talán ez sokkal jobban érdekelné önt, mint az arany. Akarod megnézni?";
					link.l1 = "Igen, igazad van. Ez valóban egy csodálatos dolog. Rendben van, megegyeztünk, köszönöm és viszlát.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Miért van szükségetek ennyi pénzre? Úgyis gazdagok vagytok. Segítettél nekünk, mi is segítünk neked egy másik alkalommal.";
					link.l1 = "Nem lesz ilyen alkalom. Imádkozzatok, gazemberek, nem nézem el az adósságot.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "Engem maga a "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " küldött ide...";
			link.l1 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " már néhány órája várja a válaszodat. Azonnal utánad küldött.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "Már jó ideje követlek a nyomodban, de túl gyors vagy.";
			link.l1 = "És akkor mi van?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Jobb, ha megmondod, mennyit fizet a kormányzó a beosztottjainak?";
			link.l1 = "A fenébe!";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "Nem ittam! A bosunt kerestem...";
			link.l1 = "Most menj... Elmondom a "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ", hogy eltévedtél a dzsungelben.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Járôr" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "És te okos vagy. Imádkozz az Istenhez, hogy a trükkjeid ne váljanak ismertté " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			link.l1 = "Nem fogja megtudni, ha nem mondod el neki... És te nem fogod, ugye?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "Miért nem? Persze, hogy elmondom, és nagy örömmel!";
			link.l1 = "Ô úgyis felakasztja magát ezért az ostobaságért. Úgyhogy ne vesztegessük az idôt, és én segítek neked megmenekülni az akasztófától.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Hmm... És hogy fogod ezt megtenni?";
			link.l1 = "Én magam öllek meg...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "Van itt dolga, "+ GetSexPhrase("monsieur","mademoiselle") +"?";
			link.l1 = "Nem-nem, a kormányzó bájos feleségének meghívására vagyok itt, hogy körülnézzek ebben a valóban fényûzô rezidenciában.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "Üzenetet hoztam az ön ismerôseitôl.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Igen. Bíróság elé akarom állítani!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Ó, igen, igazán szerencsés voltam, hogy egy ilyen gyönyörû házban szolgálhattam.";
			link.l1 = "Nem csoda...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Ne felejtse el megnézni a kertünket!";
			link.l1 = "Köszönöm, jóember!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Ehh... " + pchar.questTemp.ReasonToFast.password + "?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "Ezt nem úszod meg, áruló!";
			link.l1 = "Maradj nyugton, gazember!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Gyorsan! Fogjatok minden értékeset és fussatok!";
				link.l1 = "Szerintem neked is menekülnöd kéne.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "Mmm, bocsásson meg, mennem kell.";
				link.l1 = "Maradj nyugton, gazember!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Te "+ GetSexPhrase("tolvaj vagy, látom! Ôrök, fogjátok el","tolvaj, látom! Ôrség, fogjátok el") +"!", "Nem hiszem el! Egy pillanatra elfordultam, erre te a mellkasomnak ugrottál! Állítsátok meg a tolvajt!", "ôrök! Rablás! Állítsák meg a tolvajt!");
			link.l1 = "Aaaah, ördög!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Szia, "+ GetSexPhrase("haver","lass") +"! Készítettem neked egy meglepetést, meggyújtottam a zsinórt a puskaporos kamrába. Fel fog robbanni a mennyországba!","Miért állsz ott? Tûz van a puskaporos kamrában! Fel fog robbanni, és a tûzijátékot Európában is látni fogják!");
			link.l1 = RandPhraseSimple("Te gazember, engem nem fogsz átverni! Harcolj, te gyáva!","Látom, hogy a patkányok elhagyják a hajót, és te az elsôk között vagy?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Neked is futnod kellene, ha becsülöd az életed... Ó, hát nincs idôm, egy hajó vár rám. Kellemes horgászatot!","Nincs idôm hôst játszani, a fiúk a csónakban várnak rám. Jó szórakozást a horgászathoz, gyôztes!");
			link.l1 = RandPhraseSimple("A francba! Vágd le a sárvédôket! Gyerünk!","Ó, Istenem, hogy kerülhettünk ekkora bajba! Nyissátok ki a tengeri bejáratokat! Húzódjatok le!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "Na és?! Azt hiszed, megnyerted a harcot?! Kizárt dolog. Felgyújtottam egy lôporraktárt, nem fogsz élve kijutni a hajóról.";
			link.l1 = RandPhraseSimple("Te gazember, engem nem fogsz átverni! Harcolj, te gyáva!","Látom, hogy a patkányok elhagyják a hajót, és te az elsôk között vagy?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("Engem egy eskü köt, de ez nem jelenti azt, hogy meg kell halnom a semmiért. Sajnálom, hogy nem ajánlok helyet a hajóban, a matrózok nem fogják megérteni.","A hajók egymáshoz vannak kötve a beszállásnál, így a sorsod megpecsételôdött. Elnézést, de az én hajóm már vár...");
			link.l1 = RandPhraseSimple("A francba! Vágd le a sárvédôket! Gyerünk!","Ó, Istenem, hogy kerülhettünk ekkora bajba! Nyissátok ki a tengeri bejáratokat! Húzódjatok le!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("Gyôztes vagy! Isten hozott a pokolban! Felgyújtottam egy porkamrát.","Tessék, jóember! És végeztél, felgyújtottam egy puskaporos szobát.");
			link.l1 = RandPhraseSimple("Te gazember, engem nem fogsz átverni! Harcolj, te gyáva!","Látom, hogy a patkányok elhagyják a hajót, és te az elsôk között vagy?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("Már jó ideje követtelek téged. Kár, hogy fel kellett áldoznom a hajómat, de a fejed amúgy is megér két újat. Jó szórakozást a horgászathoz!","Látod, hogy fogsz menni? Tûzijátékkal, mint egy indiai prin"+ GetSexPhrase("ce","cess") +". De nem fogok vesztesként kijönni, a fejed sokkal többet ér, mint a hajóm. Most pedig viszlát, a hajóm nem várhat sokáig...");
			link.l1 = RandPhraseSimple("A francba! Vágd le a sárvédôket! Gyerünk!","Ó, Istenem, hogy kerülhettünk ekkora bajba! Nyissátok ki a tengeri bejáratokat! Húzódjatok le!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("A hajó felrobbanhat"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Tartson ki, kapitány! Csak néhány szóra.","Várjon, kapitány! Azt hiszem, ez érdekes lehet a számodra.");
			link.l1 = LinkRandPhrase("Miért beszélsz harc közben?!","És mi az, amirôl egy halott emberrel kellene beszélgetnem?","Mi a helyzet? Végrendeletet akarsz írni a nevemre?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "Betegség van a fedélzeten. A legénységem egynegyedét elvesztettem az út során. Mindannyian halálra vagytok ítélve...";
			link.l1 = RandPhraseSimple("Te rohadt szemétláda! Miért nem jelezted, hogy katasztrófa van a hajódon?!","Elfelejtetted a tengeri kódot? Ki kellett volna jelezned az árbocon, hogy katasztrófa van a hajódon!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "Úgyis meg akartunk halni. Ezért nem adtuk fel, magunkkal akartunk vinni téged és az ördögeidet a túlvilágra! Most már teljesen elégedett vagyok. Befejezhetitek a gonosz tetteteket.";
			link.l1 = RandPhraseSimple("Erre még felelni fogsz!...","Tetszik az ötlet, hogy te halsz meg elôször. És meg fogom nézni.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("Nem szennyezem be a pengémet a te mocskos véreddel, életben maradhatsz, bár... minek? Elviszem a legénységemet attól a rohadt öreg kádtól.","Ezért akasztófára kéne juttatni, de erre most nincs szükség. Elviszem az embereimet... Élhetsz, bár az idôd rövid lesz...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "Helló, kapitány, azt mondták, hogy keres engem.";
			link.l1 = "Én vagyok - ha te vagy " + pchar.GenQuest.EncGirl.sLoverId + ".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "Az vagyok. Van valami fontos?";
			link.l1 = "Nem tudom, hogy ez fontos-e neked, de elhoztam a " + pchar.GenQuest.EncGirl.name +". Elszökött otthonról, és most a kocsmától nem messze vár rád.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "Ó, te jó ég... Tudtam, hogy így fog végzôdni... És miért szökött el? Elmondta neked?";
			link.l1 = "Az apja hozzá akarja adni az uzsorás fiához.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "Ó, nem, ezt nem engedhetjük meg! Kapitány, tudod, olyan hülye helyzetben vagyok... Meg akartam kérni, hogy vigyen el minket " + XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland + "Acc") + " a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + "nevû városba, de most nincs pénzem, és még mindig nem találtam munkát. Gazdag családom van és ígéretes karrierem " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + "...\nbiztosíthatlak, a szüleim örülni fognak, ha egy fiatal menyasszonyommal látnak, és jól megjutalmaznak majd. Szóval, benne vagy?";
			link.l1 = "...Figyelj, nekem teljesen más terveim vannak. Azt a tanácsot tudom adni, hogy helyezkedj el matrózként, és bérelj egy kabinost a menyasszonyodnak a fizetésedért. Az emberek így jutnak el Európába, és az a településed madáréjszakai repülésben van.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Ó, a fiatalság... Felfogtad, hogy mire kérsz engem? Elvenni egy lányt a szüleitôl az áldásuk nélkül? ... És miféle férfi utasítaná vissza az ilyesmit, persze, hogy benne vagyok!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Hallottad, " + pchar.GenQuest.EncGirl.name + " megszökött a szeretôjével. Úgy döntött, nem köti az életét egy rokkanthoz. Ez bizonyára a szülei hibája, nem kellett volna elcsábulniuk a vôlegénye pénzével, és egy ilyen szépséget megpróbálni férjhez adni egy rémnek.",  
				"Hallottad?" + pchar.GenQuest.EncGirl.name + " becsapta az apját és a leendô vôlegényét is. Állítólag egy nemes kapitány segített neki és szerelmének eljutni egy másik szigetre, ahol a szerelme szülei éltek... Képzeld, még mindig vannak emberek, akik még nem felejtették el a szenvedély ízét!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Köszönöm, kapitány. Napjaink végéig emlékezni fogunk a segítségére.";
			link.l1 = "Semmiség volt. Remélem, hogy minden jól fog alakulni.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "a bolt";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "a hajógyár";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "a kikötôi iroda";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "a kocsma";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "a bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "Megígértem, hogy bemutatlak a szüleimnek. Ha véletlenül van egy szabad perce, kérem, jöjjön el a " + sTemp + ", apám ott dolgozik, és elmondom neki, mit tett értünk. Biztos vagyok benne, hogy örülni fog, hogy láthat téged.";
			link.l1 = "Rendben, beugrom, amint lesz egy kis idôm. Legyetek boldogok és vigyázzatok egymásra, mindketten...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Várjatok! Tartson ki, kapitány! Kérem, kérem.","Kapitány, kérem, várjon, könyörgöm...");
			link.l1 = LinkRandPhrase("Mi az? Elvesztetted a lélegzeted?","Emeld fel a pengédet, te gyáva!","Mi a helyzet? Elfelejtettél végrendeletet írni?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Várj csak... Megsebesültem és túl gyenge vagyok, hogy tovább harcoljak... Nem kérek kegyelmet, de van egy befejezetlen ügyem. Kérlek, ígérd meg, hogy teljesíted egy haldokló ember utolsó akaratát.";
			link.l1 = RandPhraseSimple("Ne légy tejfelesszájú, kapitány, fogadd el a halált, ahogy egy férfinak kell!","Kapitány, micsoda szentimentalizmus? Körülöttünk dúl a csata, fejezzük be, amit elkezdtünk.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Beszélj most és gyorsan.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Mondja meg " + pchar.GenQuest.CaptainComission.Name + " a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City) + "településrôl, hogy nem teljesítettem a kérését... mielôtt még volt idôm... Bocsásson meg nekem...";
				link.l1 = RandPhraseSimple("És ennyi?! Rendben, meg tudom csinálni. Hé, barátom...","Rendben, megmondom neki, ha lesz idôm. Hé, barátom...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "Nem hiszem. Nincs idôm ilyen ostobaságokra. Fejezzük be, amit elkezdtünk.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "Kérem, mondja meg a járôrkapitánynak " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "név") + "Gen")) + " '" + pchar.GenQuest.CaptainComission.ShipTypeName + "' " + pchar.GenQuest.CaptainComission.Name + ", hogy ne mutatkozzon " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc") + "... " +
							"A hatóságok tisztában vannak a halála valódi körülményeivel " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "név") + "Gen")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "... az idô szorít, le fogják tartóztatni... elhajózik " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc") + " a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") +", az út majdnem tizenöt napig tart... ahh ... sietni kellene..."; // belamour gen
				link.l1 = RandPhraseSimple("Nem ígérek semmit, de alkalomadtán megpróbálom. Hé, barátom...","Rendben, megmondom neki, ha lesz idôm. Hé, barátom...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "Micsoda kegyetlenség! Remélem, felelni fogsz érte.";
			link.l1 = "És még sok minden másért is...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("Figyelek rád, " + GetAddress_Form(pchar) + ".", "Mit akartál?", "Miben segíthetek?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "Ön " + pchar.GenQuest.CaptainComission.Name + "? Üzletet akarok kötni veled. A kapitány " + pchar.GenQuest.CaptainComission.CapName + " megkért, hogy adjak át egy fontos információt.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "Nem, semmi...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "Tényleg? Igen, persze. Szóval, mit akart a kapitány " + pchar.GenQuest.CaptainComission.CapName + "tudni?";
			link.l1 = "Megkért, hogy mondjam meg, hogy nem tudja teljesíteni a kérését.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "Mirôl beszélsz?! Régóta ismerem ôt, ô egy nagyon becsületes ember. Egyszerûen nem mondhatta ezt magának!";
			link.l1 = "Mondjuk, hogy ez olyan okokból történt, amiket nem tudott befolyásolni. Más szóval - ez volt az utolsó kívánsága.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Ah, ez teljesen oda nem illô! Ennyi idô elvesztegetése\n"
					+ "Kapitány, ebben az esetben meg kell kérnem, hogy segítsen nekem. A  " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Gen") + " kalózok elfogták a rokonom " + pchar.GenQuest.CaptainComission.SlaveName + " és váltságdíjat követelnek érte. El tudná vállalni ezt a küldetést? A jutalom elég nagylelkûnek kellene lennie.";
				link.l1 = "Sajnos, más terveim vannak.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "Megpróbálok segíteni, ha részletesebben elmagyarázza.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Ah, ez teljesen oda nem illô! Mennyi idôt elpazaroltam\nÉs mi van a ládákkal?";
				link.l1 = "Umm... milyen ládák?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "Kár, kapitány... Kár, hogy nem hajlandó segíteni nekem.";
			link.l1 = "Ez nem az én akaratom kérdése, barátom. Meg kell értened. Viszontlátásra.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "Tegnap kaptam egy levelet a " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC) + ", amelyben értesít, hogy a váltságdíj magasabb lesz, és azzal is fenyeget, hogy eladja ôt rabszolgának. A néhai kapitánynak értesítenie kellett volna " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC) + ", hogy egyetértek az elôbbi feltételekkel, és elôleget fizetek. De most már értem, miért emelték a kalózok a tétet.";
			link.l1 = "És mit javasolsz?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "Ó, "+ GetSexPhrase("pajtás","lass") +", én úgy érzem, hogy itt valami nem stimmel. Figyelmeztetlek, hogy ez nagyon veszélyes és súlyos következményekkel járhat. A kapitány " + pchar.GenQuest.CaptainComission.CapName + " három láda tele volt arannyal, amit át kellett volna adnia " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT) + " a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + " váltságdíjként egy emberért -  " + pchar.GenQuest.CaptainComission.SlaveName + ". És ha azt akarta, hogy hozzánk jöjjetek, akkor nem felejthette el elmondani nektek a ládákat.";
			link.l1 = "Miközben az utolsót mondta, nem úgy tûnt, mintha befejezte volna a mondatát. Reméltem, hogy többet fogsz mondani.";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "Nem maradt más választásom... Már összegyûjtöttem a szükséges összeget, 150 000 pesót. Kérem, hogy szállítsa el a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + " címre, és hozza ide a rokonomat. Amint ez megtörtént, kifizetek 40 000-et.";
			link.l1 = "Rendben, készen állok.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Sajnos, más terveim vannak.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "Akkor fogadd el a pénzt, és áldjon meg téged az Úr. De kérem, siessenek. Attól tartok, hogy " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM) + " nem fog várni, és eladja a szegény lelket rabszolgának.";
			link.l1 = "Várjatok meg itt. Nem hiszem, hogy túl sokáig fog tartani.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "Nem számít\nAzokat, akik a váltságdíjat összegyûjtötték, nem fogja érdekelni. Nekik csak az eredmény kell, lélegzôen és egyben - " + pchar.GenQuest.CaptainComission.SlaveName + ". Szóval ne vesztegesd az idôt.";
			link.l1 = "És mi van, ha visszautasítom?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "Valójában nincs szükségem a beleegyezésére. Csak értesítelek, hogy ha nem szállítod " + pchar.GenQuest.CaptainComission.SlaveName + " élve és egészségesen a kocsmába, fejvadászokat küldök utánad...";
			link.l1 = "Hmm... Ez komoly. És ha megteszem?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "Akkor majd megbeszéljük a továbbiakat.";
			link.l1 = "Rendben... Lássuk, hogy alakul.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hello, kapitány " + GetFullName(pchar) + ". Van valami hír?","Szóval, kapitány, átadta már a váltságdíjat?","Helló, remélem, jó hírekkel érkezett?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Sajnos a terveim megváltoztak, így fel kell bontanom az alkut.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Még nem. Még mindig elfoglalt vagyok.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("Ó, örülök, hogy üdvözölhetem, kapitány " + GetFullName(pchar) + ". Van valami jó hír?","Szóval, kapitány, megmentette szenvedô barátunkat?","Örülök, hogy élve látom, kapitány. Mi a helyzet a közös viszonyunkkal?");
					link.l1 = "Eddig semmi hír, de rajta vagyok.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Figyelj, barátom, és miért akarsz engem felelôssé tenni ezért az üzletért?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hello, kapitány " + GetFullName(pchar) + ". Van valami hír?","Szóval, kapitány, átadta már a váltságdíjat?","Helló, remélem, jó hírekkel érkezett?");
					link.l1 = "Igen. A kérésed teljesült, " + pchar.GenQuest.CaptainComission.SlaveName + " a hajóm fedélzetén van, és készül a partra szállni.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ó, örülök, hogy üdvözölhetem, kapitány " + GetFullName(pchar) + ". Van valami jó hír?","Szóval, kapitány, megmentette szenvedô barátunkat?","Örülök, hogy élve látom, kapitány. Mi a helyzet a közös viszonyunkkal?");	
					link.l1 = "Hoztam egy embert, akirôl beszéltünk. A hajóm fedélzetén van.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Hello, kapitány " + GetFullName(pchar) + ". Van valami hír?","Szóval, kapitány, átadta már a váltságdíjat?","Helló, remélem, jó hírekkel érkezett?");
					link.l1 = "Üdvözlöm, " + pchar.GenQuest.CaptainComission.Name + ", fel kell, hogy zaklassalak.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ó, örülök, hogy üdvözölhetem, kapitány " + GetFullName(pchar) + ". Van valami jó hír?","Szóval, kapitány, megmentette szenvedô barátunkat?","Örülök, hogy élve látom, kapitány. Mi a helyzet a közös viszonyunkkal?");
					link.l1 = "Az ember, akiért közbenjártál, meghalt.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Köszönöm, kapitány, nagy szívességet tett a családunknak. Itt a jutalmad... Három láda van - ez pontosan 40 000 pezó. Kérem, bocsásson meg, most találkoznom kell vele.";
			link.l1 = "Természetesen, kellemes találkozást és sok szerencsét mindkettôjüknek.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "Tökéletesen megértem a türelmetlenségét, de olyan elôre nem látható körülmények adódtak, amelyek miatt kénytelen voltam többletköltségeket vállalni.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("Kaptál kreditládát");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("Kaptál kreditládát");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nem értem... Ugye már megegyeztünk az önök fizetésének összegében?";
			link.l1 = "Megvan, de 150000 pezó helyett 200000-et kellett fizetnem, nem is beszélve a Barbadosra való utazásról.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Kapitány, ez csak a saját lassúságának az eredménye. A kalózok nem támasztottak velem szemben további követeléseket. Micsoda furcsa fickó, aki mások' kárán próbál valamit nyerni?";
			link.l1 = "Rendben, látom, hogy hiába próbálok magyarázkodni...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "Kitûnô! És önnek is voltak kétségei, hogy jól tudnánk együtt dolgozni.";
			link.l1 = "De sokat kellett költenem erre az ügyre.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "Tudom, tudom... De ebben a te hibád is benne van. Hogy süllyeszthettél el három ládát arannyal, amit szó szerint ki kellett ráznunk a kincstárból, hogy " + NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)) + " egy ilyen szakember " + pchar.GenQuest.CaptainComission.SlaveSpeciality + "?";
			link.l1 = "Tudd meg, hogy nem adom ôt neked megfelelô kárpótlás nélkül.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "Nos, ön okos ember, bizonyára megérti, hogy már túl késô az alkudozáshoz. Letartóztathattuk volna a hajóját a rakományával együtt.\nDe a kártérítésrôl már korábban gondoskodtunk. Ezért a " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + " kormány gratulál önnek a sikeres akcióhoz, és átadja önnek ezt az értékes ajándékot és szerény jutalmat.";
			link.l1 = "Hmm... Hát, még mindig jobb, mint a semmi. Vigye a drága szakemberét.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "Ó, milyen kár! Már így is túl sok idôt vesztettem. Tényleg lehangolt, kapitány!";
			link.l1 = "Megértem, de a körülményeket nem lehetett volna leküzdeni. Itt a pénze.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "Nem tudna sietni, kérem? Attól tartok, hogy a kalózok ismét megváltoztatják az alku feltételeit.";
			link.l1 = "Ne aggódjon, megoldjuk.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "Remélem, tisztában van vele, hogy az idô ellen dolgozik?";
			link.l1 = "Már megint! Rajta vagyok. Legyen türelemmel.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "Isten óvjon minket! Nincs nyomás, egyszerûen csak egy segítség a szerény puritán\nA te hibád. Megölted a kapitányt " + pchar.GenQuest.CaptainComission.CapName + ", elvesztetted az aranyunkat, és nem fizettél váltságdíjat egy nagyon értékes emberért. Ez most a fájdalom a seggedben és a te felelôsséged. Ne is gondolj arra, hogy megbocsátanak neked... Mindenért meg fogsz fizetni.";
			link.l1 = "Baszódj meg!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Helló, akartok valamit?";
			link.l1 = "Beszélhetnék az ültetvény tulajdonosával?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "Nincs itt, egy szökött rabszolgát keres, Pengét, vagy Vért, nem emlékszem... És én vagyok a helyi intézô " + npchar.name + " és én vagyok felhatalmazva, hogy minden ügyet elintézzek, amíg a fônök szabadságon van.";
			link.l1 = "Tényleg? Az jó... És a rabszolgák eladása is a te ügyed?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Persze, hogy az. Mennyit akarsz venni?";
			link.l1 = "Csak egyet.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Ehh... Biztos, hogy csak egy rabszolgára van szüksége?";
			link.l1 = "Persze, hogy az vagyok. A neve " + pchar.GenQuest.CaptainComission.SlaveName + ".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "De biztosan tisztában vagy vele, hogy az egy rabszolga ára magasabb lesz, mint egy nagyobb tételben lévô rabszolga ára?";
				link.l1 = "Persze, hogy tudom. Meg tudja mondani az árát?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Hmm... Remélem, tudod, hogy kiért jársz közben?";
					link.l1 = "Hogy érti ezt?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Ó, az a cipô. Egy garast sem adnék érte. Mióta idehozták, soha nem végzett semmilyen munkát. Fogalmam sincs, hogy az ezredes miért pazarolja a pénzt ezekre az állami elítéltekre. A feketék már más tészta. Ôk nagyszerû munkások, a vérükben van az erô és az engedelmesség. És higgye el, bármilyen munkát el tudnak végezni. Cukornádszüret vagy intézôi szolgálat - a lehetô legjobban fogják csinálni, csak adj nekik egy kis 'meggyôzô'....";
					link.l1 = "Barátom, engem a legkevésbé sem érdekelnek a fekete fickóid. Engem csak az a naplopó érdekel, akirôl beszéltél, úgysem fog sokáig élni, ágyúöntônek kell, és többet fizetek érte.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Persze, persze. Hadd lássam az árakat\nOh!!! 150000 pezó.";
			link.l1 = "Hûha...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "Az árnak benne kellene lennie az árlistában. Tessék. Tudod, nem igazán értem. A többi rabszolgát elfogadható áron adják, de ezt az egyet egy vagyonért adják...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "Azt hiszem, értem, hogy mi a helyzet... Rendben, itt a pénz, és magammal viszem.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Hmm... De én nem egy túszt akarok kiváltani, hanem egy közönséges rabszolgát akarok venni. Nem gondolja, hogy ennyiért egy tisztességes, teljesen felszerelt hajót is lehetne venni?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "Ez nem egy közönséges rabszolga. Bishop ezredes még az ôrzését is elrendelte.";
			link.l1 = "Szóval még csak meg sem vehetem?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Hát persze, hogy megteheti. Az ezredes megszabott érte egy árat - 200000 pezó, az árlista szerint.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "Hûha! Nos, az ezredes biztosan tisztában van vele, hogy milyen ember az a rabszolga...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Hmm... De én nem egy túszt akarok kiváltani, hanem egy közönséges rabszolgát akarok venni. Nem gondolja, hogy ennyiért egy tisztességes, teljesen felszerelt hajót is lehetne venni?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Á, igen. Bocsásson meg. Hadd nézzem meg, milyen árakat hagyott hátra Bishop.\nAha, itt is van. Hát... Oh!... 150 000 pezó!";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Úgy tûnik, ez valami tévedés. Bizonyára tisztában van vele, hogy egy rabszolga sem kerülhet ennyibe. Gondolom, van egy plusz nulla, és az összegnek 15000 pezónak kellene lennie. És ez még mindig túl sok, tekintve, hogy egy semmirekellô és egy idióta.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Hmm... De én nem egy túszt akarok kiváltani, hanem egy közönséges rabszolgát akarok venni. Nem gondolja, hogy ennyiért egy tisztességes, teljesen felszerelt hajót is lehetne venni?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "Nagyszerû! Ez nagyszerû! Azonnal ide fogják hozni... Talán teát?";
			link.l1 = "Nem, köszönöm... Üdvözlöm Bishop ezredest...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "És kitôl, ha megkérdezhetem?";
			link.l1 = "Mmm... Mindegy, ne is törôdj vele. Viszontlátásra.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "Sajnálom, de nem tehetek semmit. Itt az árlista.";
			link.l1 = "Ó, hagyjátok már abba, 'árlista, árlista...' Egy egyszerû dolgot sem tudtok eldönteni Bishop nélkül. Mondd meg neki... Nem érdekes, ne mondjatok neki semmit.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "Szóval nem fogjátok megvenni azt a rabszolgát.";
			link.l1 = "Nem. Viszlát.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "Nem tudok róla semmit. Csak konkrét utasításaim vannak a rabszolga eladásával kapcsolatban.";
			link.l1 = "Ostobaság... Rendben, mindegy. Itt a pénz. Hozd a rabszolgát.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Hát persze. Egy pillanat alatt ide leszállítjuk.";
			link.l1 = "Ég veled!";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Hmm... Igen, talán igazad van. Tévedésnek kellene lennie.";
			link.l1 = "Nos, ha megegyeztünk az árban, akkor most már magammal vihetem?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Igen, természetesen. Mindjárt idehozzák.";
			link.l1 = "Nagyon jó. Itt a pénze... Viszontlátásra.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "Kér egy kis teát, kapitány?";
			link.l1 = "Nem, köszönöm.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "Úgy döntöttél, hogy megveszed.";
			link.l1 = "Nem. Viszlát.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Jó napot, kapitány. Miben segíthetek? Nem hiszem el, hogy végre vége ennek a kínzásnak.";
				link.l1 = "Nem nekem kellene köszönetet mondanod, hanem a rokonodnak " + pchar.GenQuest.CaptainComission.Name + " a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". Összegyûjtötte a váltságdíjat.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Üdvözlöm, kapitány. Azt mondták, hogy te fizetted ki a váltságdíjat értem. Meg kell köszönnöm ezt, bár tudom, hogy ön csak egy futár volt.";
				link.l1 = "Nem tûnik túl boldognak a frissen visszanyert szabadsága miatt. Aggódik valami miatt?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "Kérem, ha nem zavarja túlságosan a terveit, vigyen el hozzá. Szeretném személyesen megköszönni neki.";
			link.l1 = "Persze, hogy fogom. Gyere, elviszlek a hajóra.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "Ahhoz, hogy biztos legyek a szabadságomban, tudnom kell azoknak a nevét, akik fizettek érte.";
			link.l1 = "Nos, én voltam az, aki fizetett, bár nem a saját akaratomból.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "A gyanúm tehát beigazolódott. Erre kényszerített a " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "Igen, ez " + pchar.GenQuest.CaptainComission.Name + " a  -bôl " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Értem. Fogalmam sincs, mit ígértek neked, de itt az alku: vigyél el a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + "kocsmába, ott tényleg biztonságban leszek. Cserébe megosztom veletek néhány információmat, aminek birtokában vagyok.";
			link.l1 = "Ez rendben van, annál is inkább, mert eddig nem ígértek semmit. Gyere velem, elviszlek a hajómra.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "Nem kockáztatom meg, hogy bajokat idézzek magamra néhány megkérdôjelezhetô információ miatt.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "Sajnos egyelôre nem tudom elárulni neked. Ez mindkettônk számára bajt jelenthet.";
			link.l1 = "Annál is inkább... Kövess engem, és ne csinálj hülyeségeket, kérlek. Tekintse magát ismét letartóztatva.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "Micsoda?! A kalózok megint megváltoztatták az alkut? De nem vehetek el több pénzt az üzletbôl! Így hamarosan csôdbe megyek!";
			link.l1 = "Nem... A rokonod elpusztult Barbados ültetvényein egy sikertelen szökési kísérlet során.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Ó... teljesen összetörtem... Hogy történhetett ez?";
			link.l1 = "A kalózok nem várták meg a váltságdíjat, és eladták ôt rabszolgának. Elmentem érte Barbadosra, de nem sikerült megmentenem...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "Jézusom! Mi folyik itt?\nJó, kapitány, köszönöm a részvételét. És kérem, adja vissza a pénzt, amit adtam.";
			link.l1 = "A kiadásaim minden várakozásomat felülmúlták, így megtartom a pénzét... Viszontlátásra.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Persze, vegye el... Sajnálom, hogy nem tudtam segíteni... Viszontlátásra.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "Nagyon sajnálom. Fogalmad sincs, milyen rossz ez valójában...";
			link.l1 = "Nem tehetek semmit. Még örülök is, hogy mindez így történt. Búcsúzom.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Igyál... kapitány, hozzon egy kis vizet...";
			link.l1 = "Hé, haver, te nem " + pchar.GenQuest.CaptainComission.SlaveName + "vagy?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "Igen... Én vagyok...";
			link.l1 = "Figyeljen! Figyeljen! Ha nem akarsz itt elpusztulni, mint egy laposhal a zátonyon, szedd össze magad és hallgass meg. Tudod, hol van Barbados világítótornya?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "Én igen...";
			link.l1 = "Amint lehetôséged lesz rá, fuss oda. Megpróbálok neked ilyen lehetôséget biztosítani.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Kérdezzen csak, kapitány, de gyorsan, szolgálatban vagyok.","Beszéljen, de gyorsan, és ne zaklasson kicsinyes dolgokkal.");
			link.l1 = RandPhraseSimple("Meg tudná mondani, hogyan találhatok meg egy bizonyos rabszolgát? A neve " + pchar.GenQuest.CaptainComission.SlaveName + ".","Valahol ezen az ültetvényen kell lennie egy " + pchar.GenQuest.CaptainComission.SlaveName + "nevû rabszolgának. Meg tudnád mondani, hogyan tudnék vele beszélni?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Ma büntetésben van és ôrzik.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Köszönöm... kapitány, megmentette az életemet...";
			link.l1 = "Fussatok a barbadosi világítótoronyhoz, és ott várjatok rám.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Kapitány, hogyan köszönhetném meg? Még mindig nem tudom elhinni, hogy végre vége ennek a kínzásnak.";
				link.l1 = "Már megköszönte a rokonod " + pchar.GenQuest.CaptainComission.Name + " a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". Az ô utasításai szerint cselekszem.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Köszönöm, kapitány. Nem tudom, kinek a nevében cselekszel, de még a rossz szabadság is jobb, mint a jó rabszolgaság.";
				link.l1 = "Hogy érti ezt?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "Ha ez nem árt a terveinek túlságosan, kérem, vigyen el hozzá. Túlságosan belefáradtam már ebbe az egészbe.";
			link.l1 = "Természetesen... ha sikerül élve kijutnunk innen.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "És megtudhatom azoknak a nevét, akik fizettek a szabadságomért?";
			link.l1 = "Nos, valójában nem fizettek. Nem hagytak más választást.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "A gyanúm tehát beigazolódott. Erre kényszerített a " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "Igen, ez " + pchar.GenQuest.CaptainComission.Name + " a  -bôl " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Fogalmam sincs, mit ígértek neked, de itt az alku: vigyél el a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + "kocsmába, ott tényleg biztonságban leszek. Cserébe megosztok veletek néhány információt, aminek a birtokában vagyok.";
			link.l1 = "Ez rendben van, annál is inkább, mert eddig nem ígértek semmit. Gyere velem, elkísérlek a hajómra.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "Nem kockáztatom meg, hogy bajokat idézzek magamra néhány megkérdôjelezhetô információ miatt.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "Sajnos egyelôre nem tudom elárulni neked. Ez mindkettônk számára bajt jelenthet.";
			link.l1 = "Annál is inkább... Kövess engem, és ne csinálj hülyeségeket, kérlek. Tekintse magát ismét letartóztatva.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Köszönöm, kapitány. Most már végre biztonságban vagyok. Nem kínálok pénzt, mert biztos vagyok benne, hogy a tudás és annak ügyes alkalmazása sokkal többet ér, mint a romlandó fém.";
			link.l1 = "Várom az információt.";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "A helyzet az, hogy én tudós vagyok, a " + pchar.GenQuest.CaptainComission.SlaveSpeciality + " specialistája, és a " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation)) + " már jó ideje együttmûködést ajánlott nekem," + 
				"de én hadmérnök vagyok, és megtartom a hûségesküt. Megpróbáltak ellopni, bár az igazi problémák akkor kezdôdtek, amikor a kalózok megtudták a valódi kilétemet és fontosságomat\n"+
				"Végül sikerült elfogniuk, mégis csak az aranyat akarták, a tudásomra nem volt szükségük. Barátaim és ellenségeim nem tudtak idôben váltságdíjat kérni értem, és eladtak ültetvényekre. A többit már tudjátok.";
			link.l1 = "Igen, jaj az észnek, ahogy mondani szokták, valóban.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "a hajó és a legénység védelme a harc során.";
				break;	
				case 1:
					sTemp = "ágyúid gyors újratöltése és célzott lövés leadása porosodási körülmények között. ";
				break;					
				case 2:
					sTemp = "a vitorlák gyors kezelése és a manôverezés a harcban.";
				break;					
			}
			dialog.text = "Hát, mondhatni, hogy. Tehát, ha odafigyelsz arra, amit elmondhatok neked, akkor sokkal gyakorlottabb leszel a készségben. " + sTemp;
			link.l1 = "Köszönöm, ez az információ valóban nagyon hasznos.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Nos, viszlát és köszönök mindent.";
			link.l1 = "Neked is köszönöm. Viszontlátásra, és próbálj meg legközelebb nem lebukni.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Ahoj, én vagyok a kapitány " + GetFullName(NPChar) + ", mi szél hozta a hajóm fedélzetére '" + pchar.GenQuest.CaptainComission.ShipTypeName + "'?","Ahoj, mindig örülök, ha vendégeket fogadok a hajómon. Kapitány " + GetFullName(NPChar) + " szolgálatára.");
			link.l1 = "Hello, én vagyok kapitány " + GetFullName(pchar) +", nevében eljáró néhány kapitány " + pchar.GenQuest.CaptainComission.CapName +". Megkért, hogy közöljem önnel, hogy letartóztatják " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc") + ". A hatóságok tudnak a " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"névrôl") + "Gen")) + "."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "Mi a fenét keresel itt? Mindent elintéztünk! Menj vissza a hajódra!";
			link.l2 = "Uhh...Igen, persze!";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "Ó, milyen kár! Hadd gondolkozzam\nÉs hol van a kapitány " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "Meghalt.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "A francba! A dolgok egyre rosszabbak... Figyelj, " + GetFullName(pchar) + ", nem állok készen arra, hogy szembenézzek az események ilyen fordulatával. A kapitány " + pchar.GenQuest.CaptainComission.CapName + " és én megegyeztünk, hogy találkozunk a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc") + ". Az volt a terv, hogy rakományt rakodunk a hajójára. Most, hogy a kapitány meghalt, nem tudok megjelenni a településen\nÚgy tûnik, nem maradt más hátra, minthogy szívességet kérjek tôled.";
			link.l1 = "A beleegyezésem attól függ, hogy milyen segítségre van szükséged.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Segítsetek nekem emberekkel és hosszúhajókkal. A rakományt el kell vinni a " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + ". Megtarthatod a néhai kapitány részesedését a rakományból.";
			link.l1 = "Hmm... Úgy tûnik, többet haraptál le, mint amit meg tudtál rágni. Több információra van szükségem.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Sajnos, nem vagyok abban a helyzetben, hogy erre vesztegessem az idômet.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Rendben, elmondom a részleteket\n" +
				"egyik rendszeres járôrözésem során találkoztam egy " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + "zászló alatt közlekedô hajóval. Figyelmen kívül hagyták a megadásra vonatkozó parancsomat." +
				"Amikor rövid üldözés után utolértük " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "' és így kitûzték a fekete zászlót. Az erôd elég messze volt, így egyedül kellett harcolnunk. Elpusztították a fock-boomunkat, ezért nem tudtuk elkerülni a partraszállást.\n" + 
				"Közel volt, de Szent Máriának és egy muskétás egységnek köszönhetôen sikerült mindet megölnünk. Képzeljétek el a boldogságunkat, amikor megtudtuk, hogy " + sTemp + " tele van. " +
				"Úgy döntöttünk, hogy ez méltó jutalom a sebesüléseinkért és bajtársaink haláláért\nMár sötét volt, elvittük " + sTemp +" a legközelebbi öbölbe, és elrejtettük a rakományt a parton. Aztán felrobbantunk " + sTemp +" és jelentettem az elsüllyedt kalózhajóról. Természetesen a rakományt nem említettem.";
			link.l1 = "Úgy tûnik, valaki mégis elkotyogta...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "Kár, kapitány... Kár, hogy nem hajlandó segíteni nekem.";
			link.l1 = "Ez nem az én akaratomon múlik, kedvesem. Meg kell értenie. Viszontlátásra.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "Nem hiszem, hogy az én embereim voltak. Valószínûleg a rakomány tulajdonosa szeretné enyhíteni a veszteség okozta fájdalmat\nSo? Számíthatok a segítségére?";
			link.l1 = "Igen, jól hangzik.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "Nem, barátom. Elôször is: nem tudom, mennyi rakomány kerül a rakterembe. Másodszor: nincs rá garancia, hogy a hatóságok még nem találták meg, és nem vitték el, miközben lesben álló csapatot hagytak a rejtekhelyen.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Akkor találkozzunk a " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + " , rögtön éjfél után. A jelenlegi helyzetem megköveteli a titkolózást. El kell kerülnünk az ôrjáratokat."; // belamour gen
			link.l1 = "Rendben, várjatok meg ott.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Kár, de nem hagysz más választást. Egy hajó nem elég az összes rakományhoz. A karrieremet és a saját életemet kockáztattam érte. A legénységed biztosan szívesen segít nekem egy tisztességes részesedésért cserébe.";
			link.l1 = "És mit javasolsz?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "Elveszem a hajódat és elhagylak a " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + "."; // belamour gen
			link.l1 = "A sikere nem tûnik valószínûnek. Még akkor is visszatérek a hajóra, ha az egész legénységedet le kell vágnom.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "Úgy tûnik, nincs más választásom. Nos, alávetem magam az erôszaknak...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Kapitány, sietnünk kell. Félek, hogy egy ôrjárat kiszúrhat minket.";
			link.l1 = "Rendben, siessünk.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Kapitány, parancsot kérek minden mentôcsónak vízre bocsátására. Többször kell mennünk, és félek, hogy egy ôrjárat jön az öbölbe. ";
			link.l1 = "Ne aggódjon, minden rendben lesz. A csónakok már jönnek a partra.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "Ó, a fenébe is. Most már társaságunk van...";
			link.l1 = "Valóban, ha valami bolondot említesz, azonnal felbukkan...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Kapitány, háborús bûnözôt keresünk " + pchar.GenQuest.CaptainComission.Name + ", aki értékes szállítmányt rejteget a hatóságok elôl. Az iratait, kérem.";
			link.l1 = "Milyen iratokat, tiszt úr? Kiszálltunk, hogy feltöltsük a készleteinket friss vízzel.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "És itt van ô maga, " + pchar.GenQuest.CaptainComission.Name + " . Adjátok át a fegyvert és kövessetek engem, mindketten!";
			link.l1 = "Ez nagyon rossz idôzítés volt, tiszt úr...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "Sietnünk kell, mielôtt az erôsítés ideér. A rakodás hamarosan befejezôdik, és a te részed " + pchar.GenQuest.CaptainComission.GoodsQty + " egység " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +".";
			link.l1 = "Kitûnô. Ideje indulni. Örülök, hogy üzletet kötöttünk.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "És még egy kérés. A hatóságok biztosan üldözni fognak minket, el tudnátok kísérni a hajómat a " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", ami a " + XI_ConvertString(GetIslandByCityName(sTemp) + "Voc") + "oldalon van ?"; // belamour gen
			link.l1 = "Nem, barátom, mostantól mindenki magáért felel. Viszontlátásra...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Persze, jó jutalomért megtehetem.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Természetesen. A kísérôért hajlandó vagyok fizetni  " + pchar.GenQuest.CaptainComission.ConvoyMoney + " pezó. De van még egy feltétel, nem tarthat tovább " + pchar.GenQuest.CaptainComission.iDay + " napnál. Ez fontos.";	
			link.l1 = "Megegyeztünk. Induljunk azonnal.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Kapitány, csak az idôt vesztegetjük. Bármelyik pillanatban ránk találhatnak.","Kapitány, versenyt futunk az idôvel. Ne felejtse el, hogy engem keresnek.","Kapitány, nem szabad késlekednünk. A hajóm túl nagy ahhoz, hogy elkerüljük a járôrök figyelmét.");
			link.l1 = LinkRandPhrase("Igen, igazad van. Sietnünk kell.","Akkor haladéktalanul pakoljatok be a csónakokba.","Ez az... Gyûjtsétek össze az embereiteket. Indulunk.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Kapitány, beszélnem kell az embereimmel.";
			link.l1 = "Menjen csak.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Üdvözlöm, kapitány " + pchar.CaptainComission.Name + ". Szóval, elhozta az egész rakományt? És hol van a kapitány " + pchar.CaptainComission.CapName + "?";
			link.l1 = pchar.CaptainComission.CapName + " meghalt. Meg kellett kérnem "+ NPCharSexPhrase(sld, "ezt az urat","ezt a hölgyet") +" segítséget. Bemutatom, ô itt a kapitány " + pchar.CaptainComission.FullName + ".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "És "+ NPCharSexPhrase(sld, "ki ô? Ô","ki a nô? Ô") +" tud a mi ügyeinkrôl?";
			link.l1 = "Általában igen. De van egy probléma -"+ NPCharSexPhrase(sld, "a férfi biztos","a nô biztos") +", hogy a rakomány fele a "+ NPCharSexPhrase(sld, "férfié","a nôé") +". Meg kell gyôznünk "+ NPCharSexPhrase(sld, "férfit","ôt") +", hogy ez nem egészen így van.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "Barátom " + GetFullName(pchar) +", már mindent hallottál, amit tudnod kellett. Hozzá kell férnünk a fogdájához.";
			link.l1 = "És azt hiszed, hogy a fiaim csak állni fognak és nézni, ahogy néhány rongybetyár kiüríti a raktárukat?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Igazad van. Készpénz, mondjuk " + pchar.GenQuest.CaptainComission.GoodsSum + " pezó összegben, felszabadít minket attól, hogy összeütközésbe kerüljünk a legénységeddel. Ne feledje, hogy ez a rakományunk felét fedezi, így minden fair. Ha ebbe beleegyeznek, akkor senkinek sem esik bántódása.";
			link.l1 = "És mi van, ha visszautasítom?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "Ebben az esetben az erôszak elkerülhetetlen. Te leszel az elsô áldozat, és ebben a hangulatos öbölben találsz majd nyugalmat, a legénységed pedig csak nem lesz képes a segítségedre sietni... Hogy tetszene ez neked?";
			link.l1 = "Nem hagysz nekem más választást. Nos, akkor egyszerûen megöllek titeket.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "Azt hiszem, nincs más választásom. Rendben, itt a pénzed.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Nos, ez egy méltó döntés "+ GetSexPhrase("egy nemes úriember","egy gáláns hölgy") +".";
			link.l1 = "Hagyd abba a filozofálást! Térjünk a tárgyra!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "Bölcs döntés. Sok szerencsét.";
			link.l1 = "Fojtsd meg magad...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Kapitány " + GetFullName(pchar) + ", elkéstünk. Remélem megérti, hogy most már nem jogosult jutalomra.";
			link.l1 = "Persze, hogy értem. Már így is jó pénzt kerestem, hála neked. Viszontlátásra...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "Vennél egy kis rumot egy öreg katonának, aki sokat szenvedett a csatákban a korona dicsôségéért?";
			link.l1 = "Csapos! Tölts nekünk egy kis rumot!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Ó, köszönöm, " + GetAddress_Form(pchar) + ", nagyon kedves tôled, hogy kezelsz egy fogyatékost, aki teljesen elvesztette az emlékezetét...";
			link.l1 = "Teljesen, azt mondod?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Abszolút, mis"+ GetSexPhrase("ter","s") +" kapitány... teljesen. Nem emlékszem másra, csak arra, hogy egy knippel egyenesen a fejembe repült. Nézd, mekkora lyukat ütött rajta, gondolom, az összes emlékem kiszivároghatott rajta keresztül.";
			link.l1 = "Haver, tartsd meg a szánalmas történeteidet a háziasszonyoknak. Láttam olyan embereket, akiket egybôl elkapott a szôlôlövés, az emlékezetük teljesen elmosódott... a fejükkel együtt... Te meg itt beszélsz valami képzeletbeli láncdobásról. Beszéljünk inkább a kapitányról " + pchar.GenQuest.CaptainComission.Name +". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Ó, hát, tudod. Valahogy meg kell keresnem a kenyerem. Ami a kapitányt illeti " + pchar.GenQuest.CaptainComission.Name + ", nincs hasznom a fecsegésbôl... Ha minden vele kapcsolatos kérdésért száz érmét kérnék, már most több aranyam lenne, mint amennyit a kormányzó egy év alatt beszed az alattvalóitól... ";
			link.l1 = "És próbáltad már eladni a rakományt, amit az a kapitány elrejtett?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "Mi az? Még egy kopó? Még egyszer mondom, nem emlékszem egyetlen kapitányra sem " + pchar.GenQuest.CaptainComission.Name + "! Megsérültem, és ezt az orvosi igazolás is megerôsíti! Mi másra van szüksége?!";
			link.l1 = "Ne izgulj ennyire. Tudod... Túl késôn jött. Kapitány " + pchar.GenQuest.CaptainComission.CapName + " megkért, hogy mondjam meg, hogy " + pchar.GenQuest.CaptainComission.Name + " ne mutatkozzon azon a településen, a hatóságok tudnak a " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"név megsemmisítésének körülményeirôl") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + ", és le fogják tartóztatni.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Fúú. Ezt rögtön el kellett volna mondanod, és nem beszélni körbe-körbe. Én voltam az, aki megkérte a " + pchar.GenQuest.CaptainComission.CapName + " kapitányt, hogy a visszatéréskor tartóztassa fel a hajónkat. " +
				"a dokkokba szállították, rögtön a véres harc után. Mit keresett ott az az átkozott kalóz az árujával?! Olyan sok legény halt meg miatta.";
			link.l1 = "És hogy sikerült túlélned?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "Tévedésbôl. Ôszintén szólva, a saját hibámból. Nem voltam elég gyors, így a hosszúhajónk nem jutott ki a veszélyzónából. De csak én voltam az egyetlen, aki szenvedett. Elütött valami roncs és a vízbe dobott. Már nem is emlékszem, hogyan értem ki a partra.";
			link.l1 = "És hogy sikerült kihúznod magad a vizsgálat alól?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "Elmondtam nekik, hogy a beszállás során zúzódást szenvedtem, és nem tudtam semmit a rakomány nélküliségrôl. Én is úgy tettem, mintha gyengeelméjû lennék, tudják, nemrég álltam talpra, közvetlenül a " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + "megérkezése elôtt. Nem tudtam rendesen mozogni, a koordinációm elszállt.";
			link.l1 = "Hé, de ki fecsegte ki egyébként a titkot a rakományról?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "A kalózok levelet küldtek a kormányzónak, állítólag a sérült kereskedô nevében. Úgy döntöttek, hogy bosszút állnak a kapitányon a kitartásáért. Az ô hibája volt, az ô ostoba makacssága vezetett minket ebbe a zûrzavarba.";
			link.l1 = "De hogyan találkozott egyáltalán azzal a kalózzal?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "Nem tudom. Ez egy közönséges járôrözés volt, és egy közönséges hajó közlekedett a " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + "zászló alatt. Fogalmam sincs, hogy a kapitány miért döntött úgy, hogy ellenôrzi, de nem törôdtek a figyelmeztetô lövéssel, és ahogy utolértük ôket, felemelték a 'Jolly Roger'. " +
				"Az erôd nem támogatott minket, így nem volt könnyû a harc. Aztán jött a beszállás. Még mindig nem tudom, hogyan sikerült legyôznünk ôket.\n" + 
				"Hát, és láttuk azt a sok értékes rakományt. Maga az ördög adhatta nekünk. El kellett rejtenünk a rakományt a parton, és fel kellett robbantanunk az elfoglalt hajót az égbe. Túlságosan megrongálódott.";
			link.l1 = "Nem félsz, hogy minden erôfeszítésed és áldozatod hiábavaló lenne, ha a kormányzó emberei felfedeznék a rejtekhelyet?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "Nem fogják megtalálni. Jól felrobbantottam a barlang bejáratát, elvégre én voltam a legjobb robbantási szakértô az egész században. Csak a csempészek találhatják meg a rejtekhelyemet, ôk ismerik ennek a helynek minden centiméterét.\n" + 
				"Nézd, nekem magamnak fogalmam sincs, mit kezdjek a zsákmánnyal. Egyedül sem eladni, sem elszállítani nem tudom. Különben is, senki sem fog üzletet kötni egy betört koponyával. Nem akarok pénzt keresni a legénységi társaim halálán, de a " + pchar.GenQuest.CaptainComission.Sum + "  pezóért meg tudom mondani a rejtekhely helyét, ha elvisznek a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity) + ".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "Egyetértek. Itt a pénzed. Most beszélj.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "A francba! Rendben, várj itt, hozom a pénzt.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "Ez túl sok, haver. Különben sincs megfelelô hajóm. Nos, sok szerencsét és viszlát...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Nos, rendben. Találkozzunk ma este éjfél után a " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + "környékén. És gyôzôdjetek meg róla, hogy van hely a rakodótérben " + pchar.GenQuest.CaptainComission.GoodsQty + " db. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ". Kár lenne kidobni belôle valamennyit..."; // belamour gen
			link.l1 = "Majd én gondoskodom róla. Találkozunk az öbölben...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "És itt vagy végre. Már kezdtem aggódni. Azt hittem, hogy csak úgy átadsz a hatóságoknak.";
				link.l1 = "Még nem ôrültem meg. Itt a pénzed. Most pedig a szavad.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "Szóval, hol van a pénz?";	
				link.l1 = "A francba! Rendben, várj itt, hozom.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Kapitány, úgy tûnik, elkéstünk. A csempészek megtalálták a rejtekhelyet.";
			link.l1 = "Nem fogok lemondani a zsákmányomról, még maga az ördög sem venné el tôlem.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Kilépek, foglalkozz a versenytársaiddal egyedül.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "Kapitány, komoly ügyünk van. Azt tanácsolom, hogy vigye el a századát, mielôtt a hajóink megérkeznek.";
			link.l1 = "Uraim, úgy tûnik, hogy megpróbálják elvenni azt, ami nem az önöké.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "Ó, tényleg?! Van fogalma arról, hogy kivel beszél?";
			link.l1 = "Hozzád beszélek, barátom. Annak a rakománynak van egy jogos tulajdonosa, és én ôt képviselem.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "Nem engedjük, hogy beleszólj az ügyeinkbe, még akkor sem, ha te lennél Istenünk Messiása! Hagyd el a hajóutat, ha fontos az életed?";
			link.l1 = "Nem fejeztem ki magam világosan? Az a rakomány az enyém, és nem megyek el nélküle!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "A pokolba is! Ha annyira akarod, akkor itt fogsz várni rá, örökké!";
			link.l1 = "A sors dönti el, hogy ki marad itt örökre.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Kapitány, utasítsa az embereit, hogy siessenek, bármikor megérkezhet egy ôrjárat. Különben is, a csempészek nyilván szintén a szállítóhajójukra vártak.";
			link.l1 = "Igen, sietnünk kell... Pakoljátok be a rakományt a raktérbe, és tûnjünk el innen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Köszönöm, kapitány " + GetFullName(pchar) + ". Ha maga nem lett volna, a csempészek megszerezték volna a rakományunkat, és azok a srácok, akik elestek a védelmében, hiába haltak volna meg...";
			link.l1 = "És köszönöm, hogy bíztál bennem.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "Van egy csecsebecsém, itt, ennek köszönhetem az életemet. Kérem, fogadja el, lehet, hogy ez lesz a szerencsehozója. És még egyszer köszönöm, barátom. A szelek mindig a te oldaladon álljanak.";
			link.l1 = "Köszönöm az ajándékot, nem számítottam rá. És jobb, ha vigyázol az egészségedre, amíg van pénz a zsebedben.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Úgy tûnik, ma van a látogatási napom. Szükséged van rám?";
			link.l1 = "Ha ön a kapitány " + pchar.GenQuest.CaptainComission.Name + ", akkor igen.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...volt kapitány" + pchar.GenQuest.CaptainComission.Name + "...";
			link.l1 = "A nevem " + GetFullName(pchar) + ", és lenne néhány kérdésem önhöz.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "És miért gondolja, hogy válaszolnék rájuk?";
			link.l1 = "Kapitány " + pchar.GenQuest.CaptainComission.CapName + " megkért, hogy figyelmeztessem, hogy a " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"név") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + " megsemmisülésének körülményei a hatóságok tudomására jutottak, " +
				"de nem értem el a hajóját az út során a " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + ".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "És hol van a kapitány " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "Meghalt.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "Értem... Szóval így állunk, mi? Sok minden a helyére került. Szóval, valaki elkotyogta, hogy kifosztottuk " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"nevet") + "Gen")) + ". " +
				"Elôbb-utóbb megtalálják a rakományt és felakasztanak. A kapitány " + pchar.GenQuest.CaptainComission.CapName + " halott, ez azt jelenti, hogy senki sem segíthet rajtam\nKivéve téged\n " + GetFullName(pchar) + ", juttass ki innen, és megéri neked.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "A kormányzó üzenetet kapott a rakomány tulajdonosától. És a benne lévô számok elég lenyûgözôek, tudod.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "De ugye nem gondolja, hogy bekötött szemmel fogok segíteni?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "A kormányzó üzenetet kapott a rakomány tulajdonosától. És a benne lévô számok elég lenyûgözôek, tudod.";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "A kolónián azt pletykálják, hogy önnek a csempészekkel van kapcsolata...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Úgy tûnik, el kell mesélnem az egész történetet.\n" +
				"Az egyik rendszeres járôrözés során találkoztam egy " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + "zászló alatt közlekedô hajóval. Figyelmen kívül hagyták a megadásra vonatkozó parancsomat. " +
				"rövid üldözés után elértük " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "' és felhúzták a fekete zászlót. Az erôd elég messze volt, így egyedül kellett harcolnunk. Elpusztították a fock-boomunkat, ezért nem tudtuk elkerülni a beszállásukat.\n" + 
				"Közel volt, de Szent Máriának és egy muskétás egységnek köszönhetôen sikerült mindet megölnünk. Képzeljük el a boldogságunkat, amikor kiderült, hogy " + sTemp + " tele van értéktárgyakkal. " +
				"Úgy döntöttünk, hogy ez méltó jutalom a sebesüléseinkért és embereink haláláért\nMár sötét volt, sikerült " + sTemp +" a legközelebbi öbölbe vinnünk, és a rakományt a partra rejteni. Aztán felgyújtottuk " + sTemp +" és jelentettem egy elsüllyedt kalózhajóról. Persze a rakományt nem említettem.";		
			link.l1 = "Azt hiszem, nincs értelme átverni engem. Ezért alkut ajánlok, megmutatod a rejtekhelyet, és én elviszlek a szigetvilág bármelyik helyére, ahová csak akarod.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "Ha-ha-ha-ha... Nem, kapitány, nem hagyom el a települést a részem nélkül, még ha akasztófára is kell akasztani.";
			link.l1 = "Jól van, rendben. Megkapod a részed.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Hmm... Tudod, nem vagyok hajlandó kockáztatni a fejemet a jólétedért. Viszontlátásra...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "Most már beszélsz. Készen állok\nElôször is el kell rejtened engem a hajód fedélzetén. Megmutatom az öblöt, ahol a rejtekhely van elrejtve.";
			link.l1 = "Aztán cselekedjünk gyorsan és összehangoltan. Én kinyitom a celládat, te pedig követsz engem. Ne hátrálj meg, és ne kérdezôsködj, amíg ki nem jutunk az erôdbôl.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Köszönöm a mentést. Lépjünk át a " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat") + ", megmutatom a rejtekhelyet. Sietnünk kell, amíg a vadak meg nem találják a helyet.";	// belamour gen	
			link.l1 = "Biztos vagy benne, hogy fel tudjuk venni az egész rakományt?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Igazad van, gyôzôdj meg róla, hogy elegendô helyed van a " + pchar.GenQuest.CaptainComission.GoodsQty + " darab " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ". Kár lenne elveszíteni ilyen értékes zsákmányt, amin ennyi vér van. Nem adnak nekünk második esélyt.";
			link.l1 = "Majd én gondoskodom róla.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Kapitány, nincs szükségünk tanúkra. Kérem, próbálja meggyôzni ezeket az embereket, hogy hagyják el az öblöt.";
			link.l1 = "Rendben, tegyük meg.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Kapitány, sajnálom, de ez nem a legjobb hely a gyakorlatozásra. Az a dokk már foglalt.";
			link.l1 = "Uraim, nem városnézésre jöttem ide. Nekem dolgom van itt.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Nos, itt sem fogunk medúzát, fordítsák meg a hajóikat és tûnjenek innen a fenébe.";
			link.l1 = "Nem akarom az idômet vesztegetni arra, hogy meggyôzzem magukat, hogy távozzanak. Vagy megteszik önként és életben maradnak, vagy itt maradnak örökre.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "Látom, hogy nehezen érti a szavaimat. Rendben, ha ez a te temetésed...";
			link.l1 = "Így már jobb!";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Itt vagyunk. A rejtekhely a szikla egyik fülkéjében van. A bejárat sziklákkal van eltorlaszolva. A rejtekhelyen van " + pchar.GenQuest.CaptainComission.GoodsQty +" egységnyi " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +". Emlékszel, hogy az egyik fele az enyém?";
			link.l1 = "Persze, hogy emlékszem. Van egy kis idônk, amíg az embereim felpakolják az árut. Beszéljük meg, hogy hova kell téged és a rakományodat vinni.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "Rendben. Most mondja, van valami okom arra, hogy megosszam?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Kapitány " + pchar.GenQuest.CaptainComission.Name + ", valami kellemetlen dolgot kell mondanom. A kormányzónak dolgozom. És szándékomban áll leszállítani neki az összes rakományt, amit elrejtett. Vissza kell térnie a börtönbe, és ott várnia kell a sorsára.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "Rendben van. De van itt egy dolog... Elôször fel akartalak adni a hatóságoknak, de miért tenném ezt most? És miért osztanám meg veled?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "El kell jutnom a " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", a " + XI_ConvertString(GetIslandByCityName(sTemp) + "Voc") + " a " + pchar.GenQuest.CaptainComission.iDay + " napokra. Az ottani embereim biztosan elôkészítették a rakományt az eladásra."; // belamour gen
			link.l1 = "Rendben. Akkor itt az ideje indulni.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Rendben. Mindig az elmében kell bízni, nem a szívben. Élni és tanulni\nMég ha nem is számítottam erre, mindig készen állok a harcra. Felelni fogsz az árulásodért.";
			link.l1 = "Nos, ha szerencsés vagy...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Rendben. Mindig az elmében kell bízni, nem a szívben. Élni és tanulni\nMég ha nem is számítottam erre, mindig készen állok a harcra. Felelni fogsz az árulásodért.";
			link.l1 = "Szolgálatodra állok...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Úgy tûnik, elkéstünk... A vevôk nem vártak, és nekem nincs lehetôségem egyedül megszervezni a rakomány tárolását és értékesítését...";
			link.l1 = "Van valami konkrét javaslata ezzel kapcsolatban?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Kapitány " + GetFullName(pchar) + ", tudom, hogy ez egy kicsit kínos, de... meg tudná adni a részem pénzbeli ellenértékét? Gondolom, " + pchar.GenQuest.CaptainComission.GoodsPrice + " pezó jó kompromisszum lenne.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Igen, ez egy tisztességes ár. Nem bánom. Itt a pénze, és viszlát.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Ó, nem, barátom, ez nem lesz jó. Nem ápolhatlak örökké. Ha nem akarja átvenni a rakományát, akkor megtartom. Biztos lehetsz benne, hogy megtalálom a módját, hogy tároljam és végül eladjam.";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Várjon, kapitány. Szeretném megköszönni a megmentésemet. Tudja, már majdnem elvesztettem a reményt... Tessék, biztos vagyok benne, hogy ezt a csecsebecsét nagyon hasznosnak fogja találni sok nehéz helyzetben... Viszontlátásra.";
			link.l1 = "Köszönöm. Nem számítottam rá. Öröm volt önnel üzletelni.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "Ezt nem vártam tôled... Úgy tûnik, nincs más választásom, mint kihívni téged egy párbajra.";
			link.l1 = "Szolgálatodra állok...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Kapitány, beszélnem kell az embereimmel.";
			link.l1 = "Menjen csak.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Üdvözlöm, kapitány " + GetFullName(pchar) + ". Szóval, elhozta az egész rakományt? És hol van a kapitány " + pchar.CaptainComission.CapName + "?";
			link.l1 =  pchar.CaptainComission.CapName + " meghalt, engem pedig letartóztattak egy feljelentés miatt. És ha a " + pchar.CaptainComission.FullName + " kapitány nem segít ki, akkor sem engem, sem a rakományt nem láttad volna.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "És "+ NPCharSexPhrase(sld, "ki ô? Ô","ki a nô? Ô") +" tud a mi ügyeinkrôl?";
			link.l1 = "Természetesen. "+ NPCharSexPhrase(sld, "kihúzta","engem") +" a börtönbôl, és vállalta, hogy a rakomány felét ide szállítja; a másik felét én "+ NPCharSexPhrase(sld, "neki","neki") +" kárpótlásul megígértem.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Eh, kapitány, kizárt dolog. Ez a te problémád! Javasoltam, hogy vigyük el a hajót, de te túl sokat törôdtél a rohadt karriereddel. És most itt van, a szeretett kormányzója börtönben tartja magát." +
				" A vágásod sokkal kisebb volt, mint egy fél! Nem azért dugtuk a fejünket a szôlôlövés alá, hogy az egész felét ellophasd magadnak!";
			link.l1 = "Figyelj, csónakos, nem emlékszel, hogy a hajó teljesen összetört? Hogy majdnem a víz alatt volt? Hát nem érti, hogy ha nem adom oda ennek az embernek a felét, akkor soha többé nem látta volna a rakománynak még egy kis darabját sem?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "Nem fogsz engem felültetni! Honnan tudhatnánk, hogy nem játszottatok össze? Mi van, ha egyáltalán nem volt letartóztatás? Mi van, ha csak túl kapzsi voltál, és úgy döntöttél, hogy ellopod a holminkat? Vagy azt hiszed, hogy elfelejtettük, hogyan kell bánni a pengével?!";
			link.l1 = "Látom, hogy megôrültél. Nem hall mást, csak érmék csilingelését a fülében.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Fiúk! Nézzétek, hogy beszél most a kapitányunk! Valóban, a kapzsiság teljesen felemésztette! Eladta a részünket "+ NPCharSexPhrase(sld, "egy gazembernek","egy kalandorlánynak") +"!!!";
			link.l1 = "Fogjátok be a mocskos szátokat, vagy elhallgattatlak benneteket!";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "Sajnálom, kapitány, hogy szemtanúja voltál ennek a nevetséges jelenetnek, és még részt is vettél benne. Nehéz elhinni, hogy alig egy hónappal ezelôtt még egységes legénység voltunk, és mindegyikünk szívesen feláldozta volna az életét egy barát megmentéséért.";
			link.l1 = "Be kell vallanom, nem tudom ezt elképzelni, ne vegye sértésnek.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "Sajnos, nincs lehetôségem arra, hogy egyedül szervezzem meg a rakomány tárolását és értékesítését...";
			link.l1 = "Van valami konkrét javaslata ezzel kapcsolatban?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Kapitány " + GetFullName(pchar) + ", tudom, hogy ez egy kicsit kínos, de... meg tudná adni a részem pénzbeli ellenértékét? Gondolom, " + pchar.GenQuest.CaptainComission.GoodsPrice + " pezó jó kompromisszum lenne.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "Rendben, nem bánom. Itt a pénze, és viszlát.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "Nem, ez nem fog menni. Elviheti a rakományát, vagy a raktérben hagyhatja, de egyetlen érmét sem adok érte.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Várjon, kapitány. Szeretném megköszönni a megmentésemet. Tudja, már majdnem elvesztettem a reményt... Tessék, biztos vagyok benne, hogy ezt a csecsebecsét nagyon hasznosnak fogja találni sok nehéz helyzetben... Viszontlátásra.";
				link.l1 = "Köszönöm, uram. Nem számítottam rá. Öröm volt önnel üzletelni.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Várjon... Csak arra gondoltam... Tudja, a karrieremnek vége, nincs stábom, és számûzött vagyok a hazámban. Bizonyára szüksége lenne megbízható, biztos kezû emberekre, akik tudják tartani a szájukat. Kérem, vegyen fel a legénységébe, ígérem, nem fogja megbánni.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "Hogy ôszinte legyek, már egy ideje várom a beleegyezését. Persze. Találkozunk a fedélzeten.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Hmm... tudod, nekem úgy tûnik, hogy túl okos vagy ahhoz, hogy bárki alatt szolgálj. Viszontlátásra...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Nos, úgy tûnik, a mai nap nyilvánvalóan nem a szerencsenapom... Rendben kapitány, húzzuk ki a pengét, és végezzünk egyszerre...";
			link.l1 = "Szolgálatodra állok...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "Semmi közöd hozzá. Most mondd meg, mit szaglászol itt? Nem egy olyan embert keres, akit épp most tartóztattak le?!";
				link.l1 = "Egy embert?! Nem...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "Jó magának. Különben maga is börtönbe kerülne vele együtt. Szóval ne szórakozz itt, tengerész. Tûnj el!";
				link.l1 = "Igen, jobb, ha megyek...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Remek! Most már indulnunk kellene a kocsmába ahhoz a csempészhez. Nem szeretnék itt idôzni!";
				link.l1 = "Nem probléma. Menjünk...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "He-he-he... Úgy tûnik, "+ GetSexPhrase("barátom","lány") +", nagyon hamar a pokolra jutsz vele... Hé, haver - zsigereljük ki mindkettôt!";
				link.l1 = "Te mocskos disznó! Védd magad!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Még egyszer köszönöm, " + PChar.name + ". Viszontlátásra...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "Jutalom?! Ó, persze. Tessék - fogd a " + FindRussianMoneyString(iMoney) + " és viszlát...";
				link.l1 = "Viszontlátásra...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Heh! Azt várod, hogy elhiggyük ezt a baromságot?! Srácok, fogjátok el ezt a két akasztófamadarat!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Biztos úr, súlyos hibát követ el, amikor két ártatlan embert próbál ôrizetbe venni. Higgye el, nem ismerem ezt az embert, és nem is érdekel."
				+ " Biztos vagyok benne, hogy a parancsnoka eléggé elégedetlen lesz magával, ha két törvénytisztelô polgárt ôrizetbe vesz...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Hmm... Igen, talán igazad van. A parancsnok biztosan nem fog örülni ennek. Tudjátok mit - felejtsük el ezt a kis incidenst.";
				link.l1 = "Köszönjük, biztos úr, idôt spórolt nekünk. Szeretném megkérni, hogy legközelebb legyen óvatosabb, biztosan nem akarja, hogy lefokozzák, ugye?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "Nem, semmiképpen sem. Ebben az esetben, kérem, oszoljanak. Viszlát...";
				link.l1 = "Így már jobb!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "Kitûnô! És most eltûnhettek!";
					link.l1 = "Tessék?! És mi lesz a pénzzel? Volt egy megállapodásunk...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Köszönöm a szállítást. Most már elveszhetsz... várj, valaki jön...";
						link.l1 = "Micsoda?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Remek. Köszönöm a szállítást. Itt, vegye " + FindRussianMoneyString(iMoney) ". És ne feledd, hogy a csempészek mindig emlékeznek a jó emberekre...";
					link.l1 = "Remélem is. Viszlát.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Figyelj... köztünk nem volt semmilyen megállapodás. Követeld a pénzed attól, aki megkötötte veled az üzletet.";
				link.l1 = "Hát, ez bizony nem az én szerencsenapom, mi mást mondhatnék?! Rendben, viszlát...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear() + "Ezért felelni fogsz! Készülj a halálra!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "Ki mertél hívni engem, "+ GetSexPhrase("kölyök","mocsok") +"? Hát, neked biztosan fogalmad sincs, mi a jó neked. Kibelezlek!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("Félezer ember! És egy halott ember mellkasa! Hic!", "Igyál! Hic! És az ördög tette a - Hic! - pihenés!");
						link.l1 = "Ohh... Nos. Hello, mister " + GetFullname(NPChar) + ".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "Rendben, lássuk csak... Három darab vitorlavászon, deszkák a hajóbôrhöz, a fogadás és a kötelek cseréje a merevítôkön...";
							link.l1 = "Hello, mister " + GetFullName(NPChar) + ". Én vagyok " + PChar.name + "kapitány.";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Azonnal hagyjátok el a hajómat, sok dolgom van nélkületek!", "Megkaptad a könyveidet, mit akarsz még?!", "Mindent megtettem, amit akartál, mit akarsz még tôlem?!");
							link.l1 = "Ne izgulj annyira, mert szívrohamot kapsz!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Rum, rum! Adjatok rumot... Hic!", "Régen volt már... hic... amikor utoljára így berúgtam...");
					link.l1 = "Igen, a raktér megtelt... talán itt az ideje, hogy egy öböl felé vegyük az irányt?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Kérem, foglaljon helyet, cap-hic-tain! Mi a méreg?", "Foglalj helyet, sapka! Mit szeretnél inni? Hic...");
					link.l1 = "Köszönöm, de inkább egy kellemes beszélgetést szeretnék egy rendes emberrel.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Megpróbálod - hic! - sértegetni engem? Egyetlen tisztességes ember sincs abban a kocsmában! Hic! Csak banditák és gyilkosok! Mindegyik zsaroló, és ez az egy... az elsô közöttük! A fôkolomposuk, a torkában egy mórával!";
				link.l1 = "Rád gondoltam. Te vagy az, akivel beszélni szeretnék. És ki az a bandita vezér, és miért...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Mis"+ GetSexPhrase("ter","s") +"! Kedvesem! Mi is volt a neved, még egyszer? Tisztellek téged! Egy lélek sem nevezett eddig egy vén sót tisztességes embernek! Bármit megtennék érted! Odaadnám neked az összes pénzemet, az utolsó pezóig... Ó, csak elfelejtettem. Elfogyott a pénzem. Még egy rozsom sincs már. Az a szemét, az a zsaroló most vette el tôlem az utolsó gurigát, a pokolban töltsék meg az ágyúikat az imbolygók a belével!";
				link.l1 = "Kapitány úr? Jól van? Felfogta, hogy félrebeszél? Milyen görgeteg?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "Ne, ne, ne! Lehet, hogy ez a vén csirkefogó részeg, de az esze még mindig megvan. A könyveket és a tekercseket az atya adta nekem " + PChar.GenQuest.ChurchQuest_1.ToName + ", én vittem ôket " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + ". Reggel pedig elmentem a helyi templomba, és említettem ezeket a könyveket a helyi atyának. Természetesen látni akarta ôket, tudod, az ô fajtájuk, ôk egyszerûen megôrülnek a szentek' életükért, meg minden ilyesmiért. Így hát elküldtem egy kabinos fiút, hogy hozza el a ládát velük együtt. És amíg vártam, úgy döntöttem, hogy játszom egy kicsit... és valahogy elvesztettem az összes pénzemet. Mindent! Semmit, amivel ki tudtam volna fizetni a piát! Így hát a kocsmáros elvette a könyveket zálogba, majd odaadtam neki a tekercseket is...";
				link.l1 = "Tehát könyveket árultál, a pap által rád bízott szent könyveket  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + "?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "Tudom, tudom... A pokolban fogok égni az örökkévalóságig. Most már nem mutathatom az arcom sem az Atyának, aki ezt a megbízást adta nekem, sem annak, aki a papírokat kézbesítette, sem a helyi... Ki fog most imádkozni a lelkemért? És mi lesz, ha kiátkoznak? Ó, jaj nekem... Innom kell valamit... ";
				link.l1 = "Woah nyugi, nem olyan vészes. A tetteid pocsék és istentelenek voltak, mégis kész vagyok segíteni neked. Kifizetem az adósságodat, és megveszem ezeket a kéziratokat. Emellett, mivel már ismerem mindkét említett papot, egyenesen a  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " hajózom, hogy ott átadjam a papírokat. Megegyeztünk?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Megváltó! Isten Angyala... Természetesen, egyetértek! Mindent megadnék neked... mindent! Ha csak még egy italt kaphatnék...";
				link.l1 = "Azt hiszem, már eleget ittál... Ó, mindegy. Veszek még egy kis rumot a csapostól.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...és a lepedô! A lepedôket is ki kell cserélnünk!... Ó, szia. Kérem, ne vegye sértésnek, mis"+ GetSexPhrase("ter","s") +" akárhogy is hívják, de most, mint látja, eléggé elfoglalt vagyok, úgyhogy ha dolga van velem, kérem, siessen.";
				link.l1 = "Amennyire én tudom, atya " + PChar.GenQuest.ChurchQuest_1.ToName + " adott neked néhány szent papírt " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Voc") + ". Megígérted, hogy átadod ôket a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " , mert úgyis arrafelé hajózol."; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "Én is abba az irányba tartottam, amíg az az átkozott vihar majdnem el nem pusztította a régi kádamat, és itt ragadtam a fene tudja, mennyi idôre! Ezek a csalók a dokkokban folyton megpróbálnak nekem rothadt deszkákat csúsztatni, amiket a dagály sodort partra a hajótestért, és a vitorlákért valami régi zsákvászon, amin a nagymamáik aludtak, amikor még fiatalok voltak.";
				link.l1 = "Uram, legközelebb szívesen meghallgatom a csodálatos történeteit, de most szeretnék többet megtudni a könyvek és kéziratok sorsáról, amelyeket a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + "címen kapott.";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Senki, hall engem? Senki ne merészeljen engem hibáztatni ezeknek az átkozott papíroknak a késedelmes kézbesítéséért!";
				link.l1 = "Ó, nem, természetesen nem úgy értettem. Csak könnyíteni akartam a terheit. A helyzet az, hogy " + PChar.GenQuest.ChurchQuest_1.ToName + " eléggé aggódik a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + "szállítandó könyvek és papírok miatt. Tulajdonképpen épp most fogok oda hajózni.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "Nekem úgy tûnik, mis"+ GetSexPhrase("ter","s") +", hogy minden kikötôben van egy lelki tanácsadó. Bár ez nem tartozik rám. Ha érdekel ez a szarság, akkor fogd a könyveidet és tûnj el! Jó, hogy megszabadultál tôle!";
				link.l1 = "Köszönöm, kapitány úr. Sok szerencsét a javításokhoz.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "Ne aggódjatok emiatt, mis"+ GetSexPhrase("ter","s") +", és utazzatok " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " könnyedén, hiszen én voltam az, aki vállaltam, hogy azokat a papírokat kézbesítem, és én leszek az, aki ezt mindenáron megteszem, hogy senki ne kiabáljon minden sarkon, hogy a kapitány " + NPChar.name + " nem maradt hû a szavához!";
				link.l1 = "De kapitány úr, a lényeg valójában az...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "Valójában a lényeg az, hogy egyáltalán nincs dolgom veled. A Szentatya adott nekem egy feladatot, szállítsam el a könyveket a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " és adjam át a helyi papnak. És ott nem látlak téged. Egyáltalán nem! Sok szerencsét!";
//				link.l1 = "Fine, then. You're a very responsible man, although it's your only merit. Good luck to you, my discourteous friend";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "Elegem van a pimasz viselkedésedbôl. A buta szád még egy angyalt is képes erôszakra kényszeríteni. Teljesítenem kell szent atyám akaratát, és ha kell, használom a fegyveremet!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Csend, csend, kapitány " + PChar.name + "! Mi van veled? Ó, hát látom, ha nem hozod el ezeket a papírokat, akkor az összes szentatya eléggé megharagudna rád, nem beszélve a mi mennyei Atyánkról. Rendben, fogd a teológiai értéktárgyaidat és menj Isten áldásával.";
				link.l1 = "Örülök, hogy nemcsak megértetted a helyzetemet, hanem a nevemet is megjegyezted. Javaslom, hogy idézd fel mindig, amikor valami ostobaságot készülsz tenni.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Tûnj el...", "Ne zavarj!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear() + "Nem kellett volna ezt mondanod! Most el kell küldenem az Úrhoz, hogy imádkozzon a bûneim bocsánatáért!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear() + "Nem kellett volna ezt mondanod! Most el kell küldenem téged az Úrhoz, hogy imádkozz a bûneink bocsánatáért!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear() + "Nem kellett volna ezt mondanod! Most el kell küldenem téged az Úrhoz, hogy imádkozz mindannyiunk bûneinek bocsánatáért!";
			}
			
				link.l1 = "Aligha, haver. Mindenki magáért felel majd az Isten elôtt!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "Hé, miért káromkodsz? Mi van, ha üzletet akarok kötni veled?";
				link.l1 = "Na, ez aztán a hír! Tudod, hogy a magadfajtákkal rövid beszélgetéseket folytatok!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "Hát én sem fogok veled hosszasan beszélgetni. De talán érdekelné, ha jó pénzért vennél pár csecsebecsét?";
				link.l1 = "Úgy nézek ki, mint egy átkozott lopott áru átvevôje?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Nyugi, nyugi, köztünk nincsenek tolvajok! Ezt a vázát becsületes munkáért kaptuk! Nézd csak... tiszta arany, gyöngyökkel díszítve. De a lényeg az, hogy nincs rá szükségünk. Ezért csak el akarjuk adni, és osztozunk a pénzen.";
					link.l1 = "Hadd nézzem meg közelebbrôl... Ó, te jó ég! Ez az úrvacsorakehely!!! Szóval, ti vagytok azok az istenkáromlók, akik kifosztották a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "templomát?! Hát itt vagytok!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Csend, mis"+ GetSexPhrase("ter","s") +" képmutató! Tudod, kicsit kevés a pénzünk, ezért úgy döntöttünk, hogy eladunk valamit. Nézd meg ezt a vázát... tiszta arany, gyöngyökkel díszítve. Különleges ára neked, mondjuk ezer érme.";
				link.l1 = "Hadd nézzem meg közelebbrôl... Ó, te jó ég! Ez az úrvacsorakehely!!! Szóval, ti vagytok azok az istenkáromlók, akik kifosztották a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "templomát?! Hát itt vagytok!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Nyugalom, mis"+ GetSexPhrase("ter","s") +"!.. A francba, mondtam annak a tökfejnek, hogy ne csináljon felhajtást, amíg nem jön el az ideje...";
				link.l1 = "Mit fecsegsz? Rendben, válasszatok: vagy önként átadjátok a lopott zsákmányt, vagy hívom az ôrséget.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Figyelj, "+ GetSexPhrase("jóember","ifjú hölgy") +", nincs szükségünk veszekedésre, oldjuk meg békésen ezt az ügyet. Higgye el nekünk, valójában nem mi fosztottuk ki azt a templomot, és pénzünk sincs. Igen, kaptunk néhány pezót és azt az arany csecsebecsét a rablás imitálásáért. És ez az aranypohár volt az egyetlen dolog, ami megmaradt, miután kifizettük a csempészeket...";
				link.l1 = "Szóval azt akarod mondani, hogy...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "Az az átkozott pap bérelt fel minket, ezt mondom! De miért kellett téged elküldenie hozzánk... Hát, most már kvittek vagyunk. Fogd ezt a vázát, és mutasd meg annak a képmutatónak, meglátnád magad, hogy úgy vonaglana, mint a tintahal a zátonyon!";
				link.l1 = "Add ide a kupát és tûnj el, mielôtt meggondolom magam.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "Simán beszélsz, de engem nem olyan könnyû becsapni. Ha meg akarsz gyôzni, akkor elôbb a pengémet gyôzd meg.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear() + "Hát nem megmondtam azoknak a szajkóknak: fogd a markos mancsodat, és ne vegyél el semmit, csak pénzt a paptól!";
			}
			else
			{
				dialog.text = RandSwear() + "Nem én mondtam azoknak a telhetetlen szajháknak: fogjátok meg a markotokat, és ne fogadjatok el mást, csak pénzt a paptól!";
			}
			
					link.l1 = "Mit fecsegsz? Rendben, válasszatok: vagy önként átadjátok a lopott zsákmányt, vagy hívom az ôrséget.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "Én másképp döntök, fogd be a fecsegô szádat, add ide a pénztárcádat, és megkímélem az életed.";
				link.l1 = "Segítek neked, hogy most már audienciát kapj az urunknál!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "Rendben, adok neked egy kis pénzt, de csak magamtól, hogy te és a barátaid becsületes életet élhessetek, és ne kelljen rablással lealacsonyítani magatokat.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Ehh... Rendben, tegyük félre a nézeteltéréseinket és térjünk vissza a beszélgetésünk elejére. Szóval, mennyit akartál azért az izéért?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "Nekem sincs szükségem semmilyen problémára, " + GetAddress_Form(pchar) + ", de most az ár felment. Azért a drága csészéért mindenedre szükségem lesz, ami nálad van.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "Te kapzsi söpredék! Csak " + FindRussianMoneyString(iMoney) + " van nálam. Fogd és tûnj el!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "Rossz választás, kapzsi patkány. Nem fogsz semmi jót csinálni az én költségemen!"+ GetSexPhrase(" Szabad vagyok, mint a szél - most itt, másnap ott, ma szegény vagyok - holnap gazdag leszek...","") +"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "Nem azt akarod mondani, hogy különösen ma "+ GetSexPhrase("szegény vagy","nincs pénzed") +"?!";
				link.l1 = "Pontosan, kapzsi barátom, nagy csalódásodra. És most elnézést kell kérnem, sok dolgom van.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Hagyd abba! Ezt még ellenôrizzük, és ha nem mondtál igazat, akkor a hazug nyelvedet egy hangyabolyba dugom!";
				link.l1 = "Miután ezt kimondtad, neked véged!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "Ó, nincs mit eldönteni. Mindent el tudunk dönteni magunk is. De a hajódat elvisszük, és eltûnünk innen.";
			link.l1 = "Van egy feltétel, elôször is el kell venned tôlem a pengémet...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "Helló, kapitány! Úgy tûnik, maga a Gondviselés küldött téged, hogy megmentsd " + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + " és a fiúkat. Nagy szükségünk van rájuk. A" +
					"hajónk " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name)) + " a viharban a helyi zátonyoknak ütközött, és a hullámok partra mosták a legénység túlélôit." +
					"hetek óta " + (5 + hrand(7)) + " a horizontot kémleltük, abban reménykedve, hogy meglátjuk egy hajó vitorláját, amelyik majd jön, hogy megmentsen minket.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("Igen, ez egy irigylésre méltó sors. De ilyen a tengerészek sorsa' élet, bárki kerülhet a helyedre.", "Értem... Isten minden életet megtart, csak túl elfoglalt ahhoz, hogy mindenkire emlékezzen."),
					RandPhraseSimple("Valóban. Az ember javasolja, de Isten rendelkezik.", "Igen, ez biztosan balszerencse volt."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "Nagyon komoly volt! Az a gazember " + PChar.GenQuest.PiratesOnUninhabited.BadPirateName + " nem tudott más büntetést kitalálni, minthogy otthagyja " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + " egy lakatlan szigeten, mint egy rühes görényt! " +
					"Remélte, hogy a nap és a szomjúság majd felszárít minket, mint a kiszáradt makrélát a halászállványon! De tévedett, mert maga a Gondviselés állt mellénk, hiszen téged küldött ide, hogy megments minket...";
				link.l1 = RandPhraseSimple("Ne olyan gyorsan, barátom. Amennyire én tudom, önök szabad foglalkozású emberek, és nem véletlenül kerültek ide.", "Már az üdvösségrôl beszéltek? Amennyire én tudom, ti valami különleges teljesítmény miatt vagytok itt.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("Kapitány, kérem, legyen jó lélek, és segítsen  " + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + " nincstelen embereken. Ön az egyetlen reményünk, kivéve a mi kegyelmes Urunkat.",
				"kapitány, lennének ingyenes szekrények a hajón a " + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + " nincstelen férfiak számára?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... és hova szeretnéd, hogy elvigyelek?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("Nagyon sajnálom, de még egy szabad függôágy sincs, a kabinokról nem is beszélve. A matrózok a fedélzeten alszanak, még egy ôrség után sem tudnak rendesen kipihenni magukat...",
				"Nagyon nem szeretnék csalódást okozni, de a hajó túlterhelt, és az embereknek a rossz idôben kell aludniuk. Ha járvány törne ki, a legénység felét elveszíteném."),
				RandPhraseSimple("Nagyon sajnálom, de a hajómon egyáltalán nincs szabad hely a legénységnek. Nem tudok több utast felvenni a fedélzetre.", "Csalódást kell okoznom, de a hajóm túlterhelt a legénység embereivel. Félek, hogy a járvány..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Ön tapasztalt tengerész, és tudnia kell, hogy egy hajótörést szenvedett ember jelenléte nagyon rossz jel. A tengerészeim egyszerûen kidobnak titeket a fedélzetrôl.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "Hmm... Tudja, több okból is szeretnénk minél távolabb maradni a hatóságoktól... Kérem, szállítson el minket valamelyik lakott sziget vagy a Main valamelyik öblébe, és akkor el tudnánk látni magunkat.";
			link.l1 = "Nos, van elég szabad szekrényem és függôágyam. Pakoljatok be a csónakba.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Hmm... balszerencse... Harcok állnak elôttünk, és nem tudom, hol lennétek nagyobb biztonságban, a hajóm fedélzetén vagy ebben a hangulatos öbölben.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "Ó, kapitány! Ezek azok az idôk, amikor az ember még az ágyban sem érezheti magát biztonságban a feleségével, ha-ha, még kevésbé a tengeren... Nézd ezeket a gengsztereket, mindegyikük kész puszta kézzel harcolni az ágyúk ellen. Egyáltalán nem vágynak biztonságra és kényelemre, ez leolvasható az arcukról!";
			link.l1 = "Az arcukról csak a hajlandóságot olvasom le, hogy hátba szúrják ostoba jótevôjüket.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Hmm... Ez valójában egy jó ötlet. Mondd barátom, a te banditáid hajlandóak a legénységemben szolgálni?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "Kár, kapitány... Úgy látom, hogy nem tudjuk barátságos módon megoldani a dolgot. Azt hiszem, emlékeztetnem kell téged a tengeri kódexre. És ne feledje, ha a beszállásról van szó, mi vagyunk a másodikak...";
			link.l1 = "Nos, most végre láthatom, hogy ki is vagy valójában...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "Hát persze! Örömmel lennének a fedélzeti csapatod részei! Egyikük sem lenne jobb náluk egy harcban, kivéve talán Davy Jones-t magát! Ha-ha-ha-ha!";
			link.l1 = "Rendben, akkor. Pakoljatok be a csónakokba...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("A legénységedet " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " emberrel növelték.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "Köszönöm, kapitány! A berakodás nem fog sok idôt igénybe venni. Istenem, mennyire imádkoztunk, hogy eljöjjön ez a pillanat!";
			link.l1 = "Nagyon jó, akkor.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("A legénységedet " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " emberrel növelték.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "roncsolt kalóz");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "roncsolt kalóz");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "roncsolt kalóz");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "roncsolt kalóz");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("Miért húzza az idôt, kapitány? Parancsot kaptam a horgony felhúzására.", "Sajnáljuk, kapitány úr, de fel kell készülnünk a kihajózásra.", "Olyan szerencsések vagyunk, hogy úgy döntöttek, idejönnek!");
			link.l1 = "Siessetek. A hajó nem fog senkire sem várni.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Köszönöm, kapitány. Valóban, jól tettük, hogy hittünk a szerencsénkben... Kérem, fogadják el ezt a drágakövet, abban a szerencsétlen öbölben találtam. Remélem, szerencsét hoz.";
				link.l1 = "Nem számítottam ilyen ajándékra.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Kapitány, kérem, ne gondolja, hogy túl szemtelenek vagyunk, de tényleg kevés a pénzünk. Tudja, mindent elvesztettünk, amink volt. Tudna nekünk kölcsönadni pár marék pezót? Biztosan visszafizetjük... ha alkalom adódik rá...";
				link.l1 = "Hûha! Valóban, a szemtelenség nem ismer határokat. Nos, az egyetlen dolog, amit most megtehetek értetek, azok után, amit már megtettem, az az, hogy nem szólok rólatok a hatóságoknak.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "Nem mondod... És mennyit akarsz?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Köszönöm, kapitány.", "Kapitány, nagyon hálásak vagyunk önnek.", "Imádkozni fogunk önért, kapitány " + PChar.name + "!");
			link.l1 = "Sok szerencsét. Viszontlátásra...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Heh, kapitány... Tudja, jól kijöttünk egymással... Tényleg kár lenne megölni téged...";
			link.l1 = "Megpróbálhatod!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "Nos, mondjuk, " + iMoney + " pezó mindannyiunknak jól jönne... Persze, ha nem gondoljátok, hogy ez a kártérítés minden fájdalmunkért és szenvedésünkért túl kevés, he-he...";
			link.l1 = RandPhraseSimple("Épp ellenkezôleg, biztos vagyok benne, hogy ez túl sok... Egy hurok a nyakatokon mindannyiótoknak a legjobb lenne.", "Ilyen pénzért magam akasztalak fel titeket, mint majmokat a tenyérre!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "Rendben, fogd meg. Remélem, nem tartozom mással?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "Micsoda nagylelkûség! Ôszintén szólva arra gondoltam, hogy már volt esélyed megtapasztalni, hogy mindig megkapjuk, amire vágyunk. És ezúttal sem fogunk visszalépni...";
			link.l1 = "Megpróbálhatod!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "Ó, ne, kapitány, mit beszél?! Mindenképpen gyertyát fogunk gyújtani az ön nevében, ha valaha is belépünk egy templomba... hah!";
			link.l1 = "Remélem is...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "Jaj, ne, kapitány, mit beszélsz?! Mindenképpen gyertyát gyújtunk a nevedben, ha valaha is belépünk egy templomba... hah!";
				link.l1 = "Remélem is...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Heh, kapitány, tudja, ez nem olyan nagy probléma. Én és a fiaim hajlandóak vagyunk felszabadítani egy tucat függôágyat a hajóján azoktól, akik jelenleg elfoglalják ôket...";
				link.l1 = "Hmm... ez fenyegetésnek hangzik...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "Nos, valójában ez egy fenyegetés. Szükségem van a hajójára, és el fogom hagyni ezt a helyet, a beleegyezésével vagy anélkül!";
			link.l1 = "Nos, most végre láthatom, hogy milyen is vagy valójában...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "Megértem magát, kapitány. Tökéletesen megértem magát... Ki akarná ápolni szegény kalózokat, akik hurkot kértek... De... mi lenne, ha felajánlanék egy cserét? Te elszállítasz minket egy lakott sziget vagy a Main bármelyik öblébe, én pedig adok neked érte egy kincses térképet. Megegyeztünk?";
			link.l1 = "Hmm... És hogyan tudja garantálni, hogy ez a térkép nem hamisítvány?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ha, biztos vagyok benne, hogy a térképed annyiba kerül, mint a papírdarab, amire rajzolták...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Hát... Választás nélkül hagysz minket... Akkor is, ki fogunk jutni errôl a helyrôl, akár beleegyezéseddel, akár anélkül!";
			link.l1 = "Nos, most végre láthatom, hogy ki is vagy valójában...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "És hogyan tudja garantálni, hogy nem ad fel minket a hatóságoknak a legközelebbi kikötôben? Mindketten úgy játszunk, hogy nem látjuk egymás kártyáit...";
			link.l1 = "Rendben, megegyeztünk.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Köszönöm, kapitány " + PChar.name + ". Ön teljesítette"+ GetSexPhrase("","") +" ígéretét, itt az ideje " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_DAT) + " , hogy teljesítsem az enyémet. Nincs nálam a térkép, de megmondom, hol van a kincs. Menj az öbölbe...";
			link.l1 = "Ó, szóval most már így fogalmazol! Látom, hogy már az elejétôl fogva át akartál verni...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "Rögtön tudtam, hogy nem lehet benned' megbízni...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "Ez történik, ha megbízol egy kalózban. Miféle emberek vagytok ti? Semmi sem szent nektek!";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "Ne csinálj felhajtást... Nem vagyok szent, de tartom a szavam!";
			link.l1 = "És azt várod, hogy megint higgyek neked? Hogy holnap az egész szigetvilág gúnyt ûz belôlem?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Hmm... Úgy tûnik, nem lesz békés megoldás. De, Isten tudja, én nem akartam...";
			link.l1 = "Vedd le a pengédet, vagy szétzúzlak, mint egy patkányt, aki vagy!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "És mi mást tehettem volna? Maradni abban a büdös pocsolyában a fiaimmal és halálra rohadni? Jobb, ha meghallgatsz..." + XI_ConvertString(sTitle + "Gen") + " kapitány " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " van egy rejtekhely, ahol a zsákmányát tartja. De légy óvatos"+ GetSexPhrase("","") +", gyakran látogatja ott. A rejtekhely megtalálása nem lesz nehéz, ha észben tartjátok..."; // belamour gen
			link.l1 = "És azt várod, hogy megint higgyek neked? Hogy holnap az egész szigetvilág gúnyt ûz belôlem?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "Rendben. De ha még egyszer átadsz, akkor megtalállak.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Hallgassa meg a " + sTemp + ", ô értelmesen beszél.", "Ne haragudjon " + sTemp + ", egyszerûen nem volt más választása.", "Köszönöm, kapitány úr.");
			link.l1 = "Sok szerencsét...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "És mi mást tehettem volna? Maradni abban a büdös pocsolyában a fiaimmal és halálra rohadni? Jobb, ha meghallgatsz..." + XI_ConvertString(sTitle + "Gen") + " kapitány " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " van egy rejtekhely, ahol a zsákmányát tartja. De légy óvatos, gyakran megfordul ott. Nem lesz nehéz megtalálni a rejtekhelyet, ha megmarad az eszed..."; // belamour gen
			link.l1 = "És azt várod, hogy megint higgyek neked? Hogy holnap az egész szigetvilág gúnyt ûz belôlem?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "Ki vagy te,"+ GetSexPhrase(" haver"," lass") +"? És mi szél hozott erre az elhagyatott helyre?";
			link.l1 = "Megálltam, hogy feltöltsem a friss vízkészletemet.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "A " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + "nevében vagyok itt.";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "Rossz helyet választottál erre... Rendben, csak nyugodtan.";
			link.l1 = "A-ha...";
			link.l1.go = "exit";
			link.l2 = "És ki vagy te, hogy megmondd, mit tegyek?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "Én mondom meg mindenkinek, hogy mit tegyen. És aki túl okosnak tartja magát, az a pálmafára fog lógni.";
			link.l1 = "Elvágom a nyelved, te csavargó.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "És miért nem jött egyedül?";
			link.l1 = "Nem akart, maradt a " + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Gen")) + " és várt rám."; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "Az a vén gazember! Megint megpróbál átverni minket, ugye? Ez nem fog menni. Mondd meg neki, hogy csak velünk együtt gyûjtheti be a pénzt!";
			link.l1 = "Azt mondta, hogy ne jöjjek vissza pénz nélkül, és ne vegyek fel senkit a fedélzetre...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Nos, ha ennyire megbízol benne, akkor itt maradhatsz. De mi elvisszük a hajóját, a pénzét, és elindulunk a " + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Gen")) + ". Meghalunk, hogy megnézzük az arcát " + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + "."; // belamour gen
			link.l1 = "Ha annyira hiányzik, akkor úszhatsz oda... vagy meghalhatsz itt.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "Te egy ravasz ember vagy. De hadd biztosítsam arról, hogy a konfliktusunk a " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL) + " kapitánnyal pusztán ideológiai jellegû. Figyelmeztettem ôt, hogy a piszkos mûveletei egy napon megbûnhôdnek, és most én és a  " + iBanditsCount + " haverjaim szenvedünk az Isten és az igazság iránti szeretetünk miatt.";
			link.l1 = "Hogy is van ez... Fogadok, hogy ti voltatok a lázadás tényleges felbujtói, és azt kaptátok, amit megérdemeltetek.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Persze... Jó lenne azonban hallani magának a " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " kapitánynak a véleményét is a nézeteltéréseiddel kapcsolatban.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Kapitány úr, miért sérti meg a becsületes embereket a bizalmatlanságával? Csak nézd meg az arcukat... tényleg azt hiszed, hogy lázadók? Ôk olyan szerények, amilyenek csak lehetnek... De egy jó parancsnokság alatt, az igaz ügyért folytatott harcban felülmúlhatatlanok! Személyesen kezeskedem mindannyiukért.";
			link.l1 = "Rendben, de most mit csináljak veled?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "Amit csak akarsz. Rajtad múlik, vigyél minket egy településre, vagy fogadj be minket a legénységedbe, nekem jó kapitánynak tûnsz.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "Rendben, felveszlek titeket a legénységembe. De semmi hülyéskedés! Szigorú fegyelem van a hajómon!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "Nem viszem magukat sehova. Már így is van elég gengszter a legénységemben.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "Rendben, szállj be a hajóba, és elviszlek valahova.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("Esküszöm, kapitány, nem fogja megbánni.", "Jól döntött, kapitány.", "Kapitány, nyugodt lehet, hogy önnek is ugyanolyan szerencséje volt, mint nekünk!");
			link.l1 = RandPhraseSimple("Remélem is.", "Siess. A hajó nem fog senkire sem várni.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "Ez könnyen megoldható. A  " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name + "Voc")) + " '" + sTitle + " hajón hajózik és rabszolgakereskedelemmel foglalkozik... Csináljuk így: Ha megtaláljuk, ti megkapjátok a rakományt, mi pedig a hajót. Ja, és azt is megkérdezheted tôle, hogy tud-e a " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + ". Remélem, nem kakil be a gatyájába, ha meghallja ezt a nevet, mert az az én hajóm..."; // belamour gen
			link.l1 = "Rendben, megegyeztünk.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("A legénységedet " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " emberrel növelték.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "Mi a fenét akarsz tôlem?";
			link.l1 = "Azért jöttem, hogy üdvözöljem a " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + "nevében. Gondolom ismeri ôt?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "Kár, hogy nem fojtottam meg azt a gazembert korábban. Nos, akkor azt hiszem, eljött az idô, hogy megfizessek a jóindulatomért...";
			link.l1 = "Valóban... És az idô épp kifutott...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "Szép munka, kapitány! Minden a megbeszéltek szerint? Mi megkapjuk a hajót, te pedig a rakományt?";
			link.l1 = "Persze. Fogjátok a hajót és használjátok ki.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "Üdvözlöm, kapitány " + PChar.name + ".";
			link.l1 = "Szóval, hogy tetszik a hajód?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Heh... nyikorog és nyikorog, akárcsak én. Azt hiszem, mindkettônknek nincs sok ideje hátra, hogy a nyílt tengeren hajózzunk...";
			link.l1 = "Sok szerencsét, akkor...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "Miért süllyesztetted el a hajómat?! Emlékszel egyáltalán az egyezségünkre?";
			link.l1 = "Nem akartam, hogy ô süllyesszen el engem. Nem látod, hogy épphogy sikerült?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "Ki harcol így? Elvesztettél egy ilyen hajót! Mi a fene! Miféle gyerek, mint te, mit keres itt?";
				link.l1 = "Elvágom a nyelved, te csavargó.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "Ki harcol így? Egy ilyen hajót elvesztettél! Van fogalmad róla, mennyibe került ez nekem? " + FindRussianMoneyString(iMoney) + "! Most már tartozol nekem...";
				link.l1 = "Nem lenne túl sok neked? Ne felejtsd el, hogy már tettem neked egy szívességet.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "Az Isten verjen meg azzal az átkozott hajóval! Fogd a pénzed és ne kerülj többé a szemem elé!";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "És most mit ér nekem ez a szívesség?! Ha a " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM) + " kapitány most a tengerfenéken van a hajómmal! Most már sem a részemet, sem a hajóm nem kapom vissza! Micsoda sors, hogy a csatornában haljak meg, mint egy csavargó!!!";
			link.l1 = "De miért? Látványos temetést szervezhetek neked. Itt és most, ha ez megfelel neked...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Arra gondoltam, hogy talán... megegyezhetnénk? Ha megteszel nekünk egy szívességet, mi viszonozzuk, he-he-he.";
			link.l1 = "Szívességet? És mi az alku, és mit ajánlanak cserébe?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Kapitányunkat " + PChar.GenQuest.JusticeOnSale.SmugglerName + " a helyi járôrök  " + XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen") + "elfogták. Börtönbe zárták, de nincs elég bizonyítékuk ahhoz, hogy felakasszák. Mi magunk nem tudjuk kihúzni ôt\n" +
				"Ön egy köztiszteletben álló ember. Az emberek ismerik magát. Esetleg tárgyalhatna, letehetné az óvadékot, vagy egyszerûen kivásárolhatná ôt? Bízz bennünk, elhagyjuk a szigetet, amint megvan az emberünk, így a hírneved nem fog szenvedni!"; // belamour gen
			link.l1 = "Mondjuk úgy, hogy tudok segíteni. De mi lesz a fizetségemmel?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "Menj a pokolba, ördögi ivadék! Nem állok veled szóba!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Szeretnél néhány indiai csecsebecsét és talizmánt? Elég ritkák... Vagy inkább készpénzzel a szögre? Néhány ezer pezó, mondjuk?";
			link.l1 = "Menj a pokolba, ördögi ivadék! Nem állok veled szóba!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "Engem az indiai csecsebecsék érdekelnek. Azt hiszem, beleegyezem.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "A készpénz a tengerész legjobb barátja. A pénznek nincs szaga, mint tudjuk. Egyetértek.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Köszönöm, Cap. A jutalmadon felül az óvadék összegét is megtérítjük. Azt hiszem, beszélnie kellene a parancsnokkal a kapitányunkról. Talán sikerül meggyôznie ôt. Amint kiszabadította, jöjjön a " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ", ott vetett horgonyt a hajónk - " + LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)) + " '" + PChar.GenQuest.JusticeOnSale.ShipName + "'. A parton várni fogjuk önöket."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Köszönöm, Cap. A jutalmadon felül az óvadék összegét is megtérítjük. Azt hiszem, beszélnie kellene a parancsnokkal a kapitányunkról. Talán sikerül meggyôznie ôt. Amint kiszabadította, jöjjön a " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ", ott vetett horgonyt a hajónk - " + LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name)) + " '" + PChar.GenQuest.JusticeOnSale.ShipName + ". A parton várni fogunk rád."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "Itt vagyunk, kapitány! Nagyszerû munkát végeztél, hogy átverted ezeket a fazékhasú bürokratákat! Itt a jutalmad. Fiúk, hozzátok a csecsebecséket!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "Itt vagyunk, kapitány! Nagyszerû munkát végeztél, hogy átverted ezeket a cserepes bürokratákat! Itt a jutalmatok. Fiúk, hozzátok a ládát!";
				}
				
				link.l1 = "Adjátok ide a részemet és tûnjetek el!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "Megérkeztünk, kapitány! Látom, mindent szépen elrendeztél. De tudod... nincs szükségünk tanúkra, szóval... Köszönjük meg a kapitánynak, fiúk!";
				link.l1 = RandSwear() + "Rögtön le kellett volna lônöm, amikor találkoztunk!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("Ki vagy te? És miért rontasz be a szobámba?","Wow. Ki vagy te? Ez persze az én szobám, de nem bánom, ha ilyen társaságban vagyok. Ez a szerelmi szállítmány?")+"";
			link.l1 = ""+GetSexPhrase("Már nem a tiéd. A fogadós bérbe adta nekem a szobát, és mivel te nem fizetsz érte, mindjárt kikerülsz innen. Most vagy a könnyebbik, vagy a nehezebbik utat választjuk. A választás a tiéd.","Álmodik. A mi esetünkben ez a takarítás. Szóval takarítsd ki magadból ezt a helyet. Ez most az én szobám, mivel veled ellentétben én mindig fizetek a fogadósoknak.")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("Azt hiszem, hallottam rólad. Rendben, te nyertél, én elmegyek, én még mindig élni akarok...","Hmm, sokat hallottam rólad. Gondolom, nem csak a nyelved éles. Oké, ne haragudj, a szoba a tiéd.")+"";
				link.l1 = ""+GetSexPhrase("Jó döntést hoztál.","Jó fiú.")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("Így megy ez, mi? Nos, én a nehezebb utat választottam.","Te kurva! Szépen akartam viselkedni veled...")+"";
			link.l1 = ""+GetSexPhrase("Ahogy kívánod...","És te ezt 'nemesnek'? nevezed, sajnállak. Bár talán nem.")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("Jól van, rendben, állj! Ne ölj meg! Elmegyek.","Állj! Most mit csináljunk, öljük meg egymást ezért a szobáért?! Fojtsd meg, ez mind a tiéd. Büdös...")+"";
			link.l1 = ""+GetSexPhrase("Helyes döntés. Máskor gondolkodj el a fejeddel: nem mindenki olyan kedves, mint én, akaratlanul is ölhetnek.","férfiak.")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("Nos, kilakoltattál? Tûnj innen, mielôtt megváglak.","Szóval csak fecsegni tudsz. Örülj, hogy még mindig jó kedvem van, különben még rosszabbat tettem volna veled. Takarodj innen!")+"";
			link.l1 = ""+GetSexPhrase("A fenébe...","A fenébe, alábecsültelek... Oké, oké, most már megyek.")+"";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "Ah?... Kifelé, zöldfülû, én nem iszom.... hic!... senkivel.";
			link.l1 = "Olyan keményen megütlek most rögtön, hogy egy hétig nem fogsz inni.";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "Mi?! Tudod, hogy kivel beszélsz? Én egy tengerész vagyok a hajóról '"+pchar.ship.name+"'! Csak szólnom kell a kapitánynak, és még arra sem lesz idôd, hogy elhagyd a várost! Tûnjetek el innen, amíg még egyben vagytok!"; 
			link.l1 = "...";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "Kapitány?..";
			link.l1 = "Egy hónapig fogod sikálni a fedélzetet.";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "Sajnálom, kapitány!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "Üdvözlöm, kapitány! Tudom, hogy maga a kapitány, igen.";
			link.l1 = "Üdvözletem. Honnan tudja, hogy én vagyok a kapitány?";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "Ha, én egy tapasztalt tengeri farkas vagyok, több mint egy évtizede hajózom a tengeren. Fôleg vitorlázással foglalkoztam: vitorláztam szélcsendben, viharban, luggeren, sôt csatahajón is. Igaz, a múlt hónapban egy kemény csata után megsérültem, erôs vihar volt, és senki nem mert a vitorlára mászni, így én megtettem, de megfizettem érte az árát, szerencsére csak a bokámat csavartam ki, és pár hétig nem tudtam járni. Így aztán kiírtak a partra. Most már jobban vagyok és itt ülök, várom a lehetôséget.";
			link.l1 = "Érdekes. Nem bánnám, ha lenne egy szakember ebben a kérdésben. Szeretne csatlakozni a csapatomhoz?";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "Miért ne? Már most hiányzik a hajó fedélzete és a friss széllel teli vitorlák zaja. Ha szükséges, én is edzhetném a csapatát. De rögtön kérek tôled ezer pezót, különben máris üres a zsebem. Akkor viszont, mint a csapat többi tagja. Én becsületes ember vagyok.";
			link.l1 = "Nem, valószínûleg visszautasítom. Ha minden matróznak ezer pezót fizetnek a felvételért, akkor tönkremegyek. Ne engem hibáztasson.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Megegyeztünk. Nem bánom, ha egy jó szakemberért ezer pezó jár. Várjon... itt. Én pedig a hajón várlak.";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "Ha, én egy tapasztalt tengeri farkas vagyok, több mint egy évtizede hajózom a tengeren. Többnyire ágyúk mellett álltam: lôttem falconetbôl, carronádból, culverinbôl, sakerbôl... szolgáltam luggeren, sôt csatahajón is. Igaz, a múlt hónapban egy kemény csata után megsebesültem, egy szôlôlövés gellert kapott, semmi komoly, csak egy karcolás a lábamon, úgyhogy kiírtak a partra. Most már jobban vagyok, és itt ülök, várom a lehetôséget.";
			link.l1 = "Érdekes. Nem bánnám, ha lenne egy szakember ebben a kérdésben. Szeretne csatlakozni a csapatomhoz?";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "Miért ne? Már most hiányzik a gundeck, az égô puskapor szaga és az ágyúlövések dübörgése. Ha szükséges, edzeni is tudnám a csapatát. De rögtön kérek tôled ezer pezót, különben máris üres a zsebem. Akkor, mint a csapat többi tagja, én is becsületes ember vagyok.";
			link.l1 = "Nem, valószínûleg visszautasítom. Ha minden matróznak ezer pezót fizetnek a felvételért, akkor tönkremegyek. Ne engem hibáztasson.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Megegyeztünk. Nem bánom, ha egy jó szakemberért ezer pezó jár. Várjon... itt. Én pedig a hajón várlak.";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "Ha, én egy tapasztalt tengeri farkas vagyok, több mint egy évtizede hajózom a tengeren. Fôleg partraszállási csatákban harcoltam: Harcoltam kalózokkal, és reguláris seregekkel, mindenféle fegyverrel tudok bánni, voltam már luggeren, és még csatahajón is. Igaz, a múlt hónapban egy kemény csata után megsebesültem, csak egy kis szablyakarmolás volt a hátamon, a gyáva nem tudott szembe nézni velem, de cserébe megöltem, ó, látnod kellett volna az arcukat, amikor meglátták a karcolást, ha-ha. Így hát kiírtak a partra. Most már jobban vagyok, és itt ülök, és várom a lehetôséget.";
			link.l1 = "Érdekes. Nem bánnám, ha lenne egy szakember ebben a kérdésben. Szeretne csatlakozni a csapatomhoz?";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "Miért ne? Már most hiányzik a szablyák hangja, az oldalról közeledô hajók ropogása, és a csata adrenalinja. Ha szükséges, edzeni is tudnám a csapatodat. De rögtön kérek tôled ezer pezót, különben máris üres a zsebem. Akkor, mint a csapat többi tagja, én is becsületes ember vagyok.";
			link.l1 = "Nem, valószínûleg visszautasítom. Ha minden matróznak ezer pezót fizetnek a felfogadásért, akkor tönkremegyek. Ne hibáztasson.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Megegyeztünk. Nem bánom, ha egy jó szakemberért ezer pezó jár. Várjon... itt. Én pedig a hajón várlak.";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "Sok szerencsét a tengeren, kapitány úr!";
			link.l1 = "Neked is.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Ki maga?";
			link.l1 = "Kapitány vagyok "+ GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Sajnálom, pajtás, sietek.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "Kapitány?... hic! Kapitány... kísérjen el a t-tavernhez... hic!... huh? Kérem, kérem. Úgy tûnik... ...elvesztem ebben a kolóniában, igen... hic! ..";
			link.l1 = "Szállj le rólam, nincs idôm!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Rendben, menjünk. Nem úgy nézel ki, mint aki egyedül el tudna jutni oda.";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "Csak... hic! ...lassan, kérem! Én... hic!... nem... tudok... állni...";
			link.l1 = "Rendben, menjünk, lassan.";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "Kapitány? Kapitány... segítsen!";
			link.l1 = "Szállj le rólam, nincs idôm!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Mi bajod van?";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "Ott... a kocsmában... hic!... a Kártyavetô!";
			link.l1 = "Nos, mi a baj vele? Bármelyik kocsmában, bármelyik kolónián vannak kártyavárók, mint a mocsok.";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "Kapitány, maga... nem érti... hic!.... Itt hagyott engem... egyetlen pezó nélkül! Hic! És aztán... elzavart engem... hic!...";
			link.l1 = "Szóval, most mit akarsz tôlem?";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "Gyere velem... hic!.... Beszélj vele! K-kényszerítsd... hic!... hogy adja vissza a pénzem! hic!...";
			link.l1 = "Nem kell ahhoz kártyavetônek lenni, hogy egy részeg embert legyôzzön a táblánál. Legközelebb kevesebbet igyál.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Nos, mire kell ez nekem, mi? ... Rendben, menjünk, nézzük meg a kártyavetôdet.";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "Csak... hic! ...lassan, kérem! Én... hic!... nem... tudok... állni...";
			link.l1 = "Rendben, menjünk lassan.";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "C-kapitány... hic!... köszönöm szépen... segítettél nekem! Én... tessék... hic!... Ez a tiéd.";
			link.l1 = "Gyerünk, nem érdekes... Ne igyál többet. Vagy legalábbis ne keress kalandot.";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "C-kapitány! A... Hic! Kártyaváró!...";
				link.l1 = "Ki, én? Cardsharper?";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "Ott van, kapitány! Hic!... Az asztalnál ül...";
				link.l1 = "Gyerünk, gyerünk...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "Nem... hic!... Sharper!... Eltûnt!";
			link.l1 = "Hát, elment, szóval nem várt meg téged.";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "És mi lesz... a következô? Hic!...";
			link.l1 = "Nos, most már semmit sem tehetsz. Én biztosan nem fogom keresni ôt éjszaka az egész telepen. Többé ne igyál így. Vagy legalábbis ne játssz részegen.";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "Javaslom a kockajátékot. Benne vagy?";
			link.l1 = "Kizárt dolog. Én vagyok a hajó kapitánya, és nem játszom kártyavárókkal. De könnyen szétverhetem az oldaladat, ha nem adod vissza a pénzt annak a jóembernek ott.";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "Cardsharpers-szel?! Én egy Cardsharper vagyok? Kinek adjam vissza a pénzt, annak a részegesnek?! Megsértettél, kapitány...";
			link.l1 = "Többet is meg tudok sérteni. Add vissza a pénzt.";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "Igen, nem vagyok kártyás! Tisztességes játékos vagyok. A szerencse gyôz, és a barátodnak nem volt szerencséje, ennyi az egész.";
			link.l1 = "Szerencse, mi? Add ide a kockádat, és meglátom, milyen szerencsésen fog kiesni.";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "Jól van, jól van, nyugalom, kapitány. Hát, legyôztem a részeget, és csaltam egy kicsit, és minden második játékos ezt teszi. Itt a pénze.";
				link.l1 = "Így már jobb. És, remélem, megérti, hogy ha a barátom most azt mondja, hogy ez nem a teljes összeg, akkor visszaadom önnek?";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "Igen, kérem, itt vannak a kockáim. Mindkét készlet. Megvan. Nincs mit rejtegetnem.";
				link.l1 = "Szóval... Pár... Semmi... Pár... Teljes... Semmi... Semmi... Két pár... Készlet... Semmi... Pár...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "Igen, kérem, itt vannak a kockáim. Mindkét készlet. Megvan. Nincs mit rejtegetnem.";
				link.l1 = "Szóval... Négy egyforma... Négy egyforma... Full... Full... Négy egyforma... Póker... Full... Póker... Négy egyforma... Full... Hmm, és ezt hogyan magyarázza meg nekem?";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "Mindent értek, itt a teljes összeg. Sok szerencsét neked és a barátodnak.";
			link.l1 = "Neked is.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "De... nem akarta beismerni! Hic!...";
			link.l1 = "Igen, megpróbáltam kitérni elôle. Tessék, tartsa meg a pénzt.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "C-kapitány... hic!... köszönöm szépen... segítettél nekem! I...'pukes on the side'... tessék... hic!... Ez a tiéd.";
			link.l1 = "Gyerünk... nem érdekes... Ne igyál többet így. Vagy legalább ne játssz részegen.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "Na, mit szólsz? Meggyôztél?";
			link.l1 = "Hmm, ez tényleg úgy tûnik, hogy közönséges kocka ...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "Mondtam neked. És a barátod csak részeg. Nem tudta beismerni a vereségét, ezért hozott ide téged.";
			link.l1 = "Rendben, sajnálom az incidenst. Sok szerencsét.";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "Szóval... hic!... mi az?... Ô... hic!... nem egy s-sharper?...";
			link.l1 = "Nos, úgy tûnik, tisztességesen játszott.";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "És mi lesz... a következô? Hic!...";
			link.l1 = "Nos, most már semmit sem tehetsz. Ôszintén legyôzött téged. Többé ne igyál így. Vagy legalábbis ne játssz részegen.";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "Szerencse. Csak szerencséd volt, ennyi az egész. A szerencse egy szeszélyes hölgy.";
			link.l1 = "Hmm, tényleg. Hát akkor játsszunk veled, de vigyázz, hogy ezekkel a kockákkal játsszak!";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "Ezekkel? Ez... Nem, nem akarok veled játszani! Megsértettél. És különben is, le vagyok égve...";
			link.l1 = "Talán azt akarod, hogy elmondjam mindenkinek a kocsmában a kockáidat? Vagy talán mutassam meg nekik? És aztán mesélj nekik a szerencsérôl. Mit gondolsz?";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "Mit?! Mit gondolsz, ki vagy te?! Megpróbálsz megzsarolni?! Kilyukasztalak, ha nem szállsz ki!";
			link.l1 = "Inkább itt maradok és megmutatom mindenkinek a kockáidat.";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "Hát gyere ide, te dög!";
			link.l1 = "Ne veszítsd el a nadrágodat!";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "C-kapitány? Te... hic!... verekedésbe keveredtél? És ez itt... hic!... s-sharper?";
			link.l1 = "Ôt magát is megütötték. Nem fog mással játszani.";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "De... nem akarta beismerni! Hic!...";
			link.l1 = "Igen, megpróbált kitérni elôle. Csak nem volt nála a pénzed. Valószínûleg elköltötte.";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "Igen, megpróbált kitérni elôle. Tessék, a pénzed.";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "És mi lesz... a következô? Hic!...";
			link.l1 = "Nos, most már semmit sem tehetsz. Ôszintén legyôzött téged. Többé ne igyál így. Vagy legalábbis ne játssz részegen.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "C-kapitány... hic!... köszönöm szépen... segítettél nekem! I...'pukes on the side'... tessék... hic!... Ez a tiéd.";
			link.l1 = "Gyerünk... nem érdekes... Ne igyál többet így. Vagy legalább ne játssz részegen.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "Kapitány? C-kapitány... kísérjen el a p-p-pillérhez... hic!... huh? Kérem, kérem. Nekem... hic!... a hajóra kell mennem... a hajóra... A botswain... megesküszik... hic!... ha elkésem...";
			link.l1 = "Szállj le rólam, nincs idôm!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Rendben, menjünk. Úgy tûnik, nem tudsz egyedül odaérni.";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "Csak... hic! ...lassan, kérem! Én... hic!... nem... tudok... állni...";
			link.l1 = "Rendben, menjünk lassan.";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "C-kapitány... hic!... köszönöm szépen... segítettél nekem! I...'pukes on the side'... tessék... hic!... Ez a tiéd.";
			link.l1 = "Gyerünk... nem számít... Ne igyál többet. Vagy legalábbis ne keress kalandot.";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "C-kapitány!... Hajó!";
			link.l1 = "What 'ship'?";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "S-hajó!... Hol van?... hic!...";
			link.l1 = "Nyilvánvalóan elment. Kevesebbet kéne inni a kocsmákban. Az egész hajó nem fog várni egy részeg matrózra.";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "De én... hic!... nem vagyok részeg... majdnem... talán...";
			link.l1 = "Ah, igen, valóban. Sok szerencsét.";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "Várjon, kapitány! Vigyetek... hic!... a hajójára! Én nem fogok... hic!... többet inni...";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "Rendben, mit tehetsz ellene. De hogy azonnal menjen a hajóra. És isten ments, hogy valahol részegen meglássam, a következô kikötôi megállóig súrolja a fedélzetet.";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "Úgy, hogy a fizetésembôl rúgsz be, és aztán kereslek a telep összes kocsmájában és kapualjában? Nem, nekem nincs szükségem ilyen boldogságra.";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "Igen, kapitány!... hic!...";
			link.l1 = "...";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "Kapitány?... hic!... Maga... szárazföldi patkány... hic!... nem kapitány!...";
				link.l1 = "Több száz ilyen embert vágtam le a fedélzeti harcokban, mint te, úgyhogy kifelé, részeges!";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "Kapitány... hic! A kapitány, aki a rajtaütésen volt... hic!";
				link.l1 = "Ha a tengeren látod ezt a vályút a horizonton, jobb, ha azonnal a vízbe merülsz: a cápákkal nagyobb esélyed lesz a túlélésre, mint a hajóm ellen. Most pedig tûnjetek el!";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "Kapitány?... hic!... Te egy tejivó vagy, nem kapitány!... Az anyád még lány volt... hic!... amikor én még a tengeren hajózgattam...";
				link.l1 = "De anyád valószínûleg örülne, ha tudná, hogy egy olyan kisfiúból, mint én, kapitány lett, te pedig egy részeges matróz maradtál, aki csak a fedélzetet súrolhatja.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "Kapitány? Vigyázz... hic!... kapitány... Kiverem a fogaidat... hic!... nem lesz idôd pislogni!...";
				link.l1 = "A visszapattanás ölni fog. Kifelé! Üsd ki a fogaimat, ha mered...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "Kapitány? Úgy néz ki... hic! ...mint valami rongybaba...";
				link.l1 = "Úgy tûnik, még nem néztél tükörbe...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "Kapitány? Én még csak bele sem egyeztem, hogy a maga hajóján szolgáljak... hic!...";
				link.l1 = "És senki sem ajánlotta fel, hogy a hajómra menj, hogy beleegyezz. Tûnj az utamból.";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "Hic!..";
			link.l1 = "Menj aludni.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "Hic!... Igen... még mindig messze?";
			link.l1 = "Közel vagyunk, légy türelmes.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Ki... hic!... te vagy?...";
			link.l1 = "Kapitány vagyok "+ GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Sajnálom, pajtás, sietek.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "Kapitány?... hic!... Kapitány... segítsen! Nekem... úgy értem... hic!... a barátomnak... tényleg szüksége van a segítségedre! Kérem...";
			link.l1 = "Nem fogom megoldani minden részeges problémáját, akivel az éjszaka közepén találkozom...";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Rendben, mondd el, mi történt a barátoddal.";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "A barátom... ô, általában... berúgott. Csak úgy általában... hic! ...berúgott...";
			link.l1 = "Természetesen kijózanítottam a szolgálatban ivó tengerészeket, de elég radikális módszerekkel. Nem hiszem, hogy a barátjának szüksége lenne rá.";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "Nem! Ô... ô a gárdával van! Ô arrr... vele van. És verekedésbe keveredett. És ôt... hic!... börtönbe vitték... ô csak... részeg!";
			link.l1 = "És most mit akarsz tôlem? Ô maga a hibás: kevesebbet kellene innia. Vagy legalábbis ne keress magadnak kalandot...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "Beszélj az igazgatóval, kapitány... hic! ...kapitány! El fogja engedni... engedje el! Hmm... itt van... hic!... milyen szerencsés vagy... A barátom csak... vitatkozott... nos... és pofán akart vágni... de... hic!... nem kapott fegyvert...";
			link.l1 = "Most már nincs más dolgom, mint éjszaka kihúzni a börtönbôl a részegeket, akik összevesztek az ôrökkel. Nem, hagyd állni pár napig. Talán legközelebb meggondolod.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Igen, a pokolba veled. Rendben, beszélek az igazgatóval.";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "Nem vagyok benne biztos, hogy az igazgatónak tetszene az akcentusom. Majd késôbb jelenteni fogja a kormányzónak. Szóval menjetek nélkülem.";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "Attól tartok, barátom, hogy a helyi kazamatákhoz vezetô út el van zárva elôttem. A börtönigazgató ikonként ôrzi az arcképemet, és én nem fogok letelepedni ezekben a vendégszeretô lakásaikban. Úgyhogy sajnálom, de nem tudok segíteni neked.";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "Köszönöm... kapitány. És a barátomnak is. Tessék... ez a tiéd.";
			link.l1 = "Legközelebb tartsd szemmel a barátodat, amikor berúg és úgy dönt, hogy harcolni fog az ôrökkel. Nem minden éjjel járkálnak kapitányok az utcán, készen arra, hogy néhány részegesért tárgyaljanak az ôrrel. Sok szerencsét!";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("You've received amulet 'Gunpowder tester'");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("You've received amulet 'Jade turtle'");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("You've received amulet 'Monkey's fist'");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("You've received amulet 'Merchant's beads'");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("You've received amulet 'Baldo'");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("You've received amulet 'Gypsy's fan'");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("You've received amulet 'Cimaruta'");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "Oh!... Szóval tudom, hogy... hic!... hogy kiszabadítsam a... f-barátomat... hic!... Ôrség! Egy kém a városban!... hic!...";
				link.l1 = "Nagyon rossz lehetôséget választottál, hogy kiszabadítsd a barátodat.";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ah, f-idegen... hic! ...neked... neked gondjaid lesznek... hic! ...Rendben... Nekem itt van... hic! ...mindent kézben tartok.";
				link.l1 = "Persze, persze. Ha bármi történik, azonnal jövök hozzád.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "Ah... szóval te... hic! ...bûnözô vagy! Ôrség!";
				link.l1 = "Ah, szóval így beszélsz most!";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ó, hogy... hic! ...bocsánat. És mi lenne, ha... hagynád, hogy... tárgyaljak helyetted... hic!... az igazgatóval, és te... hic!... a barátomért?...";
				link.l1 = "Nem, nem kell tárgyalnod helyettem, köszönöm. Sok szerencsét!";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Ki... hic!... vagy te?...";
			link.l1 = "Kapitány vagyok "+ GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Sajnálom, pajtás, sietek.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "Kapitány?... hic!... Kapitány... figyelj, kísérj el a város melletti barlangba... hic!... huh? K-kérem.";
			link.l1 = "A barlanghoz? Nem értem. Miért mész a barlangba? És miért van rám szükséged?";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "Látod... kapitány... hic!... Elfogyott a pénzem az italokra... És... hic!... egy barlangban van... egy rejtekhelyem, szóval... hic! ...de én... ez... Félek egyedül menni a dzs... dzs... dzsungelben... hic!... éjszaka... Szóval...";
			link.l1 = "Szállj le rólam, nincs idôm!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Rendben, menjünk. Úgy tûnik, nem tudsz egyedül odajutni.";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "Csak... hic! ...lassan, kérem! Én... hic!... nem... tudok... állni...";
			link.l1 = "Rendben, menjünk lassan.";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cave "+NACave+" on the island " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("Kaptál egy alkoholt")
				dialog.text = "C-kapitány... hic!... köszönöm szépen... segítettél! Én... tessék... hic!... Ez a tiéd.";
				link.l1 = "Gyerünk... nem számít... Ne igyál többet.";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "Kitûnô, kapitány! Örülök, hogy beleegyezett.";
				link.l1 = "Nos, hol van a rejtekhelyed? Várj egy percet, úgy tûnik, hogy nem vagy részeg.";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "Igen, nem ittam sokat, ne aggódj miattam. És ami a rejtekhelyet illeti... Srácok!";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "Srácok, hoztam ide egy rejtekhelyet. Ki kell nyitnotok. Kivéve persze, ha ez a rejtekhely maga is kinyílik, jó értelemben. Kapitány, mit gondolsz?";
			link.l1 = LinkRandPhrase("Szerintem jobb lenne, ha emlékezetkiesésig berúgnád magad. Legalább életben maradnál. És most már csak egy út van... "," Szerintem egyáltalán nem vagy jó fej, hiszen úgy döntöttél, hogy kirabolod egy hadihajó kapitányát ... "," Szerintem valószínûleg belefáradtál az életbe, hiszen úgy döntöttél, hogy megpróbálod ezt ...");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "Rendben, azt hiszem, jobb, ha jó úton haladunk. És mennyi kell?";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "Szóval, jó úton haladva nem fogjuk kinyitni a rejtekhelyet?";
			link.l1 = "Attól tartok, ez volt életed utolsó rejtekhelye.";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "Ó, mi nem vagyunk kapzsik. Csak " +FindRussianMoneyString(iMoney)+ "."; 
			link.l1 = "Attól tartok, ez volt életed utolsó rejtekhelye.";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "Rendben, ahogy akarjátok. Soha többé nem segítek egy részeg embernek...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "Kapitány, meglepett a nagylelkûségével. Szeretne még többet megosztani velünk?";
			link.l1 = "Már mindent odaadtam. Elmegyek...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Ki... hic!... vagy te?...";
			link.l1 = "Kapitány vagyok "+ GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Sajnálom, pajtás, sietek.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "Kapitány?... hic!... oh, "+GetAddress_Form(NPChar)+" ... Annyira sajnálom... hic!... a... k-kondíciómat. Szeretnél csatlakozni hozzám? hic!... P-kérlek."; 
			link.l1 = "Sajnálom, "+GetAddress_Form(NPChar)+", de nem érek rá."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Csatlakozol? Sajnálom, de ma nem iszom..."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "Ó, nem kell... hic!... inni! Itt van egy dolog... Hát... Ittam egy italt a barátommal... Szóval... máris be vagyok állva... látod?";
			link.l1 = "Jól van, rendben. Segítsek kijózanodni?";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "Nem igazán! Nem, nem igazán. Most szeretnék kártyázni... kártyázni, általában szeretnék játszani... hic!... De nem a nyomorult... p-pesóknak... ezekkel a ragamaffinokkal a... hic!... t-tavern... hanem egy igazi nemessel! hic!... Igazi fogadásokért!..."; 
			link.l1 = "Bocsánat, "+GetAddress_Form(NPChar)+", mit is mondhatnék... Nem vagyok szerencsejáték rajongó. Szükség van a tengerészek fizetésére, a hajó fenntartására, tudod..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Hmm, rendben, játszunk. Menjünk a kocsmába?"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "Rendben! Csak... hic!... lassan, kérem. Én... hic!... nem... tudok... állni..."; 
			link.l1 = "Rendben, menjünk lassan."; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "Az asztalhoz... hic!... menjünk!"; 
			link.l1 = "Rendben, menjünk."; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "Fogalma sincs, kapitány úr, mennyire... hic! ...örülök, hogy egy igazi nemessel találkozhatok! hic! ...hic! ... Ebben a vadonban... általában csak... hic!... szemét..."; 
			link.l1 = "Igen, a helyi kolóniákon ez egy tucatnyian vannak. Nos, játszunk?"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "Igen, játsszunk! hic!... Milyen fogadások?"; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "1000 pezóért játszunk."; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "Játszunk 2000 pezóért."; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "Hmm, sajnálom, úgy tûnik, hogy a zsebem jelenleg üres..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "M-micsoda?... Nincs... hic!... nincs pénzed játszani... velem?..."; 
			link.l1 = "Hát, megesik. Majd legközelebb játszunk, ne aggódj."; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "Hic!... Jól éreztem magam, kapitány! Hic!..."; 
			link.l1 = "Egyetértek veled. Legalább egy kis szünetet tartsatok az üzletben."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "Hic!... Jól éreztem magam, kapitány! Hic!..."; 
			link.l1 = "Egyetértek veled. Legalább egy kis szünetet tartsatok az üzletben."; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "Néha csak arra van szükséged, hogy... hic!... s-idôt tölts egy kedves... hic!... társasággal. Köszönöm szépen... hic!... a társaságot!"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "Igen, épp most vesztettem el. És hogy történt, hogy akkor is nyertél, amikor minden esélyem megvolt a gyôzelemre?"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "Kölcsönösen köszönöm a játékot és a beszélgetést."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "Néha csak arra van szükséged, hogy... hic!... s-idôt tölts egy kedves... hic!... társasággal. Köszönöm szépen... hic!... a társaságot!"; 
			link.l1 = "Kölcsönösen köszönöm a játékot és a beszélgetést."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "Csak szerencse, c-kapitány... hic!..."; 
			link.l1 = "Nem úgy néz ki, hogy csak szerencse...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "Mire akarsz utalni? Azt akarod mondani, hogy tisztességtelenül játszottam? Te magad is láttál mindent, ugyanabból a pakliból vettünk lapokat!"; 
			link.l1 = "Igen, láttam. És azt is láttam, hogy egy perce még alig mozgott a nyelved, most pedig úgy beszélsz, mintha nem is lennél részeg."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "Á, a fenébe! És jól elkaptál! Rendben, elismerem, nem fogok rejtôzködni. Nem voltam részeg. De tudod, milyen jól bedôlnek az emberek azoknak az állítólag gazdag és részeg embereknek, akik kártyázni akarnak? Mindenki, akinek van mire fogadnia, szinte elsôként szalad a kocsmába, hogy gyorsan megszerezzen egy kétségtelenül gazdag, de részeg nemestôl egy kétségtelenül nagy nyereményt. Hadd mondjam azt, hogy te vagy az elsô, aki eljutott a lényemig."; 
			link.l1 = "És most mi lesz? Visszaadod a pénzemet jó úton-módon?"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "Ha ha ha ha, ne nevettessen meg, kapitány. Természetesen nem fizetek vissza semmit! És ne hidd, hogy kényszeríthetsz. Könnyedén eljátszhatok egy tisztelt nemest, akit néhány kóbor kapitány lecsap. Szóval azt tanácsolom neked: fogadd el a vereségedet, és csak sétálj el."; 
			link.l1 = "Hát, ôszintén kívánom, hogy ne érjen téged kevésbé szerencsés körülmények között utol, mert akkor már nem fogsz így nevetni. Viszontlátásra!"; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "Én pedig azt tanácsolom neked, hogy próbálj idôt szakítani egy kard beszerzésére."; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "Nem mernéd... Ez egy kocsma, tele emberekkel..."; 
			link.l1 = "Szóval én csak egy kóbor kapitány vagyok, mit érdekelnek az illemszabályok. És a kikötôi kocsmában éjjel, mi történhet... Én minden tekintetben jobban bánok a karddal, mint te."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "Á, szóval így van ez?! Nos, akkor most megnézzük, kié a jobb!"; 
			link.l1 = "Szolgálatodra..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "Kapitány?... hic!... ó, "+GetAddress_Form(NPChar)+" ... annyira sajnálom... hic!... a... k-kondíciómat. Tudna segíteni? hic!... K-kérem."; 
			link.l1 = "Sajnálom, "+GetAddress_Form(NPChar)+", de nem érek rá."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Ó... figyelek."; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "Ez olyan dolog... Általában... Én... máris részeg vagyok... Látod... hic!... igen?"; 
			link.l1 = "Hogy ôszinte legyek, igen. Segítsek kijózanodni?"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "Nem igazán! Jól vagyok. Egy hölgyet akarok. De olyan részeg vagyok... hic!... A-hölgyem ki fog rúgni, szóval... Tudnál... hic!... tárgyalni helyettem? Adok pénzt."; 
			link.l1 = "Sajnálom, "+GetAddress_Form(NPChar)+", de hogyan mondhatnám el neked... Nem járok bordélyházakba. Becsület, hírnév... tudod..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Ó, rendben, segítek."; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "Csak... hic! ...lassan, kérem! Én... hic!... nem... tudok... állni..."; 
			link.l1 = "Rendben, menjünk lassan."; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "Itt van a pénz... hic!.... Itt fogok várni rád."; 
			link.l1 = "Jó, hamarosan visszajövök."; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "Csak... csak... hozd... hic!... a... legjobbat!... Igen..."; 
			link.l1 = "Rendben, rendben, értem."; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "Hic! Meddig tart még?"; 
			link.l1 = "A kolónia legjobb lánya vár rád odafent."; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "Igen!... Ez az este... nagyszerû... Köszönöm, "+GetAddress_Form(NPChar)+". A maradék pénzt... hic!.... vedd el. És belesüllyedek... az én..... gyönyörû... fekvô hölgyembe...";
			link.l1 = "Nos, érezzétek jól magatokat."; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "Hic! Meddig tart még?";
			link.l1 = "Hamarosan tárgyalok, legyetek türelmesek.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "Hic!..";
			link.l1 = "Aludnod kell.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "Hic! Igen... még messze van?...";
			link.l1 = "Mindjárt itt vagyunk, légy türelmes.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "Huh? Ki vagy te? Mit keresel itt?";
			link.l1 = "Én is kérdezhetném ugyanezt.";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "Mi? Ó, mi... ööö... Virágokat gyûjtünk itt...";
			link.l1 = "Sírvirágokat? Nos, hogy áll a herbárium?";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "Ô... A gyógynövényekkel kapcsolatos?";
			link.l1 = "Szóval... Azt hiszem, értem, mi folyik itt.";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "Nem vagyunk fosztogatók! Ne beszélj így rólunk! Mi csak...";
			link.l1 = "Csak mi?";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "Nos, mi... Apám megtiltotta, hogy találkozzunk! És az ô apja is! Szóval... egy olyan helyet kerestünk, ahol nincsenek szemtanúk. Hogy egyedül legyünk. A zár az ajtón amúgy is elromlott, így könnyû bejutni ide...";
			link.l1 = "Most már értem, mik voltak azok a nyugtalan lélek ijesztô nyögései...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "Hát, ha már mindent kitaláltál, talán békén hagysz minket?";
			link.l1 = "Nem félsz attól, hogy egy kriptában rendezd a randidat? Nem a legjobb hely...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "Nem vagyunk babonásak! És még ha ijesztô is lenne - mi más választásunk van? A városban a szülôk rögtön rájöttek volna. De itt senki sem fog rólunk beszélni. Úgyhogy egyelôre ez a legjobb megoldás.";
			link.l1 = "Nagyon sajnálom, de nem tudnátok más helyet keresni? Ne értsetek félre, mindent megértek - fiatalság meg minden -, de a randevúitok halálra rémítették a temetôôrt, a kriptából minden éjjel hallatszó zajok és nyögések miatt.";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "Hát... Az ôrök megijesztése nem volt a tervünk része. De akkor hol máshol találkozhatnánk? Vagy azt javaslod, hogy a szabad ég alatt randizzunk?";
			link.l1 = "A szerelem nem ismer határokat. Találjatok egy másik helyet, ahol biztosan nem fogtok senkit sem zavarni. Akkor senki sem fog zavarni titeket. Valószínûleg. És jobb, ha a szüleiddel is megbeszéled a dolgokat - ugye nem tervezed, hogy örökké bujkálsz?";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "Rendben, majd kitalálunk valamit... Nem fogjuk többé megijeszteni az ôrséget, a szavamat adom.";
			link.l1 = "Csodálatos. Sok szerencsét nektek!";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "Micsoda?!";
			link.l1 = "Ó, semmit...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérnélek, hogy tartsd vissza a pengédet.");
			link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod...", "Ahogy mondod...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "öt"; break;
		case 6: retValue = "hat"; break;
		case 7: retValue = "hét"; break;
		case 8: retValue = "nyolc"; break;
		case 9: retValue = "kilenc"; break;
		case 10: retValue = "tíz"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "kettô"; break;
		case 3: ConvictStr = "három"; break;
		case 4: ConvictStr = "négy"; break;
		case 5: ConvictStr = "öt"; break;
		case 6: ConvictStr = "hat"; break;
		case 7: ConvictStr = "hét"; break;
	}
	
	return ConvictStr;
}
// <-- gen
