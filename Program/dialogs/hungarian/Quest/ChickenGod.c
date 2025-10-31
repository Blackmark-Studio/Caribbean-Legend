int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin,   
				float  DmgMax, 
				float  EnergyP,
				bool   MultiDamage, 
				int    MisFire,     
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Ezt nem szabadna látnod.";
			link.l1 = "Ideje hibabejelentést tenni.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "Uh-oh! Ta'kahi, fiatalember. Nem akarok udvariatlan lenni, de hogy kerültél ide? Erôsen tanácsoltam a hölgynek, hogy zárja be a létesítményt a tartózkodásom idejére.";
			link.l1 = "Valóban. Hogy engedtek be? Miért nem gyújtották még fel ezt a bordélyházat a feldühödött istenfélô emberek?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "Az aranydublonok minden utat megnyitnak, és boldogabbá teszik a fehér embereket. Hát nem tudod?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text + " Érzem Versailles már-már idôjárási szagát, ahová ilyen csikorogva engedtek be.";
			}
			link.l1 = "Ne beszélj így velem, vörös arcú. Igaz, hogy új vagyok itt, bár nem tudom, honnan tudtad meg. Lelôhetnélek ott, ahol állsz, és bármelyik lányt megkaphatnám éjszakára, hogy kárpótoljalak a kellemetlenségért.";
			link.l1.go = "native_var1";
			link.l2 = "Nem tudom, ki mondta magának ezt a badarságot, de maga elég simulékonyan beszél, azt meg kell hagyni. Ez az elsô alkalom, hogy ilyen mûvelt bennszülöttet látok.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2 + " Versailles, a seggem!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "Nem, kapitány, maga nem tud semmit. Tökéletesen biztonságban vagyok itt... egyelôre. De ha már ilyen gyorsan összebarátkoztunk, próbáljuk meg újra. Egy italt?";
			link.l1 = "Azt megtehetem, határozottan felkeltette az érdeklôdésemet.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "Bravó! Látom, máris a keresztnevünkön szólítanak minket, és szúrós szavakat váltunk. Most azt javaslom, igyunk a békére és beszéljünk az üzletrôl.";
			link.l1 = "Azt megtehetem, határozottan felkeltette az érdeklôdésemet.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "Tekintettel a helyszín céljára, a megjegyzése, kapitány, eléggé aggaszt engem! Már majdnem egy hónapja itt ragadtam. Mindent kipróbáltam, ami csak eszembe jutott, és kész vagyok unalmamban és értelmetlenségemben felmászni a falra.";
			link.l1 = "Akkor menjen el. Látogasson el egy templomba a változatosság kedvéért... ahová nem engedik be.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "Ez nem ilyen egyszerû, hiszen a... szerzôdésem szerint még huszonnégy órát vagyok köteles ebben a bordélyban tölteni.";
			link.l1 = "Persze szörnyen hangzik, de nem fogsz együttérzést kapni tôlem. Egy exkluzív bordélyházbérlés egy hónapra egy valóra vált álom!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Féljen a vágyaitól, kapitány. Nem tudom, hogy került ide, mert úgy volt, hogy ezt a hónapot egyedül töltöm. Egyedül squaw-val és borral, de csak a harmadik naptól kezdve bírtam a bort. És ma volt az a nap, amikor nekem is elegem lett belôle.";
			link.l1 = "És mit akarsz, mit csináljak? Osszam meg veled a lányokat és a bort?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Talán, de azt javaslom, elôbb játsszunk! Ezer ezüst kártyánként! A nevem egyébként Agueybana.";
			link.l1 = "Az enyém a " + GetFullName(pchar) + ". Persze, játsszunk.";
			link.l1.go = "native_accept";
			link.l2 = "Az enyém a " + GetFullName(pchar) + ". Ezer pezó? Nem rossz. Gondolkodom rajta, de nem ígérek semmit.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "Meggondolta magát, kapitány? Mehetünk?";
			link.l1 = "Persze, miért is ne.";
			link.l1.go = "native_accept";
			link.l2 = "Még nem.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Köszönöm a játékot, kapitány. Azt hittem, ettôl majd jobban érzem magam, de nem. Kérem, hagyjon békén - egy napot még kibírom egyedül is valahogy. Átkozott szemétláda!";
			link.l1 = "Ennyi? Bevallom, a csalódottságom nagyobb, mint az a keserûség, hogy egy csomó pénzt veszítettem.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "Nem is kellett volna itt lennie, kapitány. De ha arra vágyik, hogy megtudja, mi volt ez az egész... keressen egy ôsi templomot a kontinensen. És hozzon magával sok tuunich kaane'. Tessék, vegyen egyet.";
			link.l1 = "Egy viperakô? Egy lyukas kô határozottan illik a helyszínhez. Köszönöm, Agueybana.";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Viszlát, kapitány.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "Uh-oh! Köszönöm, kapitány! Kár a pénzért, de legalább újra megízleltem az életet!";
			link.l1 = "Igen, ez az elsô alkalom, hogy valakit ennyire izgatottnak látok egy ilyen útvonal miatt. Egyébként honnan van ennyi pénzed?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "Egy olyan bunkó kérdés, amit soha nem tennél fel az egyenrangú társaidnak, kapitány! De még fiatal az éjszaka, és van még egy jó adag pénzem. Mit szólna egy visszavágóhoz?";
			link.l1 = "Mi a fenéért ne? Csináljunk még egyet!";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "Javaslom, hogy ezúttal kockázzunk, és emeljük meg a tétet egy kicsit. Nekem is van egy mesélnivalóm, úgyhogy kérem, béreljen ki egy szobát az emeleten mindkettônknek. Túl sok itt a fül! Nagyra értékelném, ha elmennél a Madame-hoz és kifizetnéd a szobát. A hitelem sajnos nem vonatkozik rád.";
			link.l1 = "Bérelsz egy szobát? Kettôre? Itt? Baszd meg, Agueybana! Én lelépek innen!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "Ó, a pokolba is. Ennek a történetnek vagy egy jó anekdota lesz a vége, vagy egy nagyon drága vérfürdô. A kardom velem marad, úgyhogy semmi tréfa, ha-ha! Várjatok itt, majd én elintézem.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "Szóval?";
			link.l1 = "Ôszintén remélem, hogy csak piáért és szerencsejátékért hívtál ide.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "Ne aggódjon, kapitány, engem nem érdekelnek az ilyen ostobaságok! Bár, ha már az elsô napon megjelent volna itt... ha-ha-ha! Kezdhetjük?";
			link.l1 = "A bátraknak kedvez a szerencse.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "Uh-oh! Ez jó érzés! Gratulálok a gyôzelméhez, kapitány.";
			link.l1 = "Ne vigye túlzásba. Ideje, hogy felvilágosítson, mi a fene folyik itt?";
			link.l1.go = "native_dice_story";
			link.l2 = "Furcsa vagy, Agueybana. Nos, ha nem hagyom el ezt a helyet azonnal, nemesi és férfias hírnevem helyrehozhatatlanul megromlik. Add ide az ezüstöm, és váljanak el útjaink.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "Milyen kár, reméltem, hogy a napot másképp fejezzük be...";
			link.l1 = "Ez az elsô alkalom, hogy egy férfit ennyire feldúltnak látok, amiért megnyerte ezt a plebejus játékot. Legalább felvilágosítana, hogy mi a fene folyik itt?!";
			link.l1.go = "native_dice_story";
			link.l2 = "Baszd meg, Agueybana! Elegem van ebbôl!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "Amennyire csak tudok, kapitány. Nem vagyok benne biztos, hogy szabad-e, de azért feldobta az elmúlt napjaimat... Mármint ebben a bordélyházban.";
			link.l1 = "És mi volt ez az egész?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "Ne törôdj vele... Figyelj ide, fehér ember! Én vagyok a Taino nép nagy fônöke, Agueybana. Néha azt álmodom, hogy száz évvel korábban születtem, és elûztem a spanyol megszállókat a szigeteimrôl! De ehelyett háromezer törzsem tagját adtam el a bányászoknak fejenként tíz dublonnáért.";
			link.l1 = "Méltó életrajz. Hirtelen késztetést érzek arra, hogy lelôjelek, Agueybana, és hagyjalak megrohadni ezen a savanyú borszagú szeméttelepen.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Mindegy, kapitány. Mindig is csak olyan akartam lenni, mint te.";
			link.l1 = "Mint én?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "Láttam a hajóit - az emberi zsenialitás csodáit - és akartam egyet magamnak. Láttam a nôiteket szûk fûzôben, és arról álmodtam, hogy én is leveszek egyet. Láttam, hogy még a legpocsékabb parancsnokaitok is olyan hatalmat gyakorolnak, amirôl a mi vezetôink sem álmodnak. Hallottam történeteket Európáról és a hatalmas kôházakról, ahol az emberek túlélés helyett élnek. És nekem mindez megvolt! Sôt, még Európában is jártam, meg minden az elmúlt évben!";
			link.l1 = "Túl sok bort ittál, fônök. Neked csak láncok lennének a jegyek Európába, a Vatikán és az utcai mutatványosok örömére. Amirôl beszélsz, az egyszerûen lehetetlen abban a világban, amiben élünk.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "Ez az a világ, amiben élünk, kapitány. Nekem már elmagyarázták, hogy a mi világunk téves, képzeletbeli, és bármi lehetséges.";
			link.l1 = "És ki volt az az okostojás, aki ezt mondta? Úgy látszik, nem csak a bordélyházakba engednek be, hanem az elmegyógyintézetekbe is!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "Most pedig elérkeztünk a történetem lényegéhez. Tudod, hogy mûködnek itt a dolgok, ugye? A spanyolok és az angolok fegyverekkel, szerszámokkal és puskaporral fizetnek a hadifoglyainkért. Én a törzseimért a ti pénzetekbôl fizettem. Mit gondolsz, miért van ez így?";
			link.l1 = "Úgy érzem, hogy mindjárt felvilágosítasz.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Csak az istenek teljesíthetik legmélyebb és legszégyenletesebb vágyainkat. Ha nem tudsz olyan életet élni, amilyet szeretnél, akkor kérd meg ôket, hogy avatkozzanak bele a sorsba. Csak ôk teljesíthetik a legmélyebb és legszégyenteljesebb vágyainkat. Ez az út. De itt van a baj: szinte az összes istenünk már halott, és még ha nem is lennének, az arany úgysem érdekelte ôket soha. Szerencsére a természet irtózik a vákuumtól, és az egyik régi piramisban megjelent egy új isten. Nem érdekli, hogy ki vagy: helyi vagy európai, gazember vagy hôs - csak fizess, és megkapod, amit kértél! Az összes törzs tudja ezt, és néhányan a te népedbôl is. Aranyban fizettem az árát, és úgy éltem, mint egy közületek. Holnap lesz egy éve.";
			link.l1 = "Milyen isten? Európába és vissza egy év alatt? És az utazásod csúcspontja valami vacak bordélyház volt a Karib-tengeren? Ó, mi a fene. Úgy hangzik, mint egy részeges meséje, és én el is veszem. Igyunk egyet, és folytassuk a történetet.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Minden, amit mondtam, igaz. Nincs több mondanivalóm.";
			link.l1 = "Nem éltél elég régóta a mi világunkban, Agueybana. Minden piától ihletett mesének, különösen annak, amit részegen mesélnek egy bordélyban, erkölcsi tanulsággal kell végzôdnie. Mindenképpen filozofálnunk kell, mielôtt rendesen befejezzük a szalonunkat.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "Hogyan szoktak végzôdni?";
			link.l1 = "Nem tudod? Természetesen a résztvevô nemétôl függ! Ökölharc a férfiakkal, ágyba viszik a nôket. Néha azonban a divat diktál fordítva. És mi a meséd tanulsága? Pénzzel nem lehet boldogságot venni? Unalmas!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "Nem ez a mesém tanulsága, ahogy te fogalmaztál. De mivel te kezdted, úgy érzem, el kell mondanom, hogy nem értek egyet az álláspontoddal. Éppen ellenkezôleg, én úgy gondolom, hogy a pénz boldogságot vásárol, és jobbá teszi az embereket.";
			link.l1 = "Badarság! Úgy tûnik, hogy most ellentmondásba keveredsz magaddal. Jelentôs vagyonra tettél szert a saját néped kereskedelmével. Emlékszik arra, hogy mekkora összegbôl profitált? Közel harmincezer aranyat? Gondolkodj egy kicsit, de számomra világos, hogy a pénzzel nem vetted meg a boldogságot. Viszont ezt a szép lakosztályt igen.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "Rendben, korrigálom a kiindulási pontomat: a pénz jobbá teszi az életet és az embereket.";
			link.l1 = "Ez jobb, de mibôl gondolod, hogy jobbá teszi az embereket? Szóval most már az erény példaképe vagy? És mi van azokkal, akiknek nincs sok pénzük? Ôket is rossz embereknek fogjuk bélyegezni?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "Tudja, kapitány, igazán értékelem ezt a beszélgetést. Hadd igazítsam ki újra: a pénz jobbá teszi az életet és az embereket, de csak azokat, akikben már megvan az erény szikrája.";
			link.l1 = "Halljuk, halljuk! Szóval, neked nincs szikra, mi?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "Nem. Én voltam a népem fônöke, és a pénzzel ellentétben a hatalom határozottan megrontja az embert. Tudod mit, kapitány? Ránézek rád és rájövök, hogy egy nap te is ugyanezzel a dilemmával fogsz szembesülni.";
			link.l1 = "A te istened is megajándékozott a gondviselés képességével? Akkor menj el Santiagóba, úgy hallottam, ott különösen érdeklôdnek mindenféle médiumok és jósok iránt.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Fejezzük be a... khm, szalonunkat ökölharc és ágyazás nélkül, kérem. Nem sikerült kitalálnom egy morált a történetemhez, ezért inkább egy tósztot szeretnék mondani.";
			link.l1 = "Teljesen eltévedtél, fônök. De egy dologban igazad van. Igyunk egyet!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "Arra, hogy amit akarunk, az mindig megfelel annak, amire szükségünk van. Köszönöm, kapitány, ez méltó befejezése... az esténknek. Ha egy nap szeretnéd kipróbálni a mesém igazságát, menj a kontinensre, és keress meg ott egy ôsi templomot. Hozz magaddal száztizenhárom tuunich kaane'. Nekem kilencvenkilenc maradt - vidd ôket és viszlát!";
			link.l1 = "Egy halom lyukas kô? Jól illik a helyszínre. Köszönöm az estét, Agueybana. Találkozunk még?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "Nem, nem fogsz. Viszlát, kapitány.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "Értem, kapitány. Jóban-rosszban adok egy tippet a kincsre. Végül is feldobta az utolsó napjaimat... Úgy értem, ebben a bordélyban. Keress egy ôsi templomot a nagy földön, és hozz egy halom tuunich kaane' to. Tessék, vegyél egyet.";
			link.l1 = "Egy viperakövet? Milyen bájos, és egy lyukas kô határozottan illik a helyszínhez. Elegem van a bánásmódodból!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "Megértem, hogy feldúlt, kapitány. Jóban-rosszban adok egy tippet a kincsre. Végül is feldobta az utolsó napjaimat... Úgy értem, ebben a bordélyban. Keress egy ôsi templomot a nagy földön, és hozz egy halom tuunich kaane' to. Tessék, vegyél egyet.";
			link.l1 = "Egy viperakövet? Milyen bájos, és egy lyukas kô határozottan illik a helyszínhez. Elegem van a bánásmódodból!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Viszlát, kapitány.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "Még egyet? Ó, a kurva életbe, elegem van belôletek!";
			link.l1 = "A-a-ah! Tûnj el!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "Mi? Igen, persze. Hajolj meg elôttem, halandó! Íme a piramisom ereje!";
			link.l1 = "(kétségbeesetten sikoltozni)";
			link.l1.go = "joruba_2";
			link.l2 = "(megölni a szörnyeteget)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "Így van. Üdvözöllek szerény faktóriámban, kapitány.";
			link.l1 = "Mi vagy te?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "Elismerésem a kitartásodért. Mi a következô lépés, kapitány? Mit szólna egy kis kereskedelemhez?";
			link.l1 = "Mi vagy te?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "Nem számít, hogy mi vagyok, csak az számít, hogy milyen feladatot látok el. Jelen pillanatban kereskedelmi üzleteket kötök ennek a patkánylyuknak a lakosaival a kölcsönös elônyök érdekében.";
			link.l1 = "A patkánylyukkal? Úgy érted, ezzel a templommal?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "Az elsô és egyben utolsó figyelmeztetés, kapitány! Bár ez a piramis valóban elég szûkös, nyilvánvalóan kinôttem belôle.";
			link.l1 = "Mondott valamit a kereskedelemrôl. Miféle kereskedelemrôl beszélsz?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "Azt adom, amire az embereknek a legnagyobb szükségük van.";
			link.l1 = "Kívánságokat teljesítesz? Mint egy dzsinn a tündérmesébôl? Uramisten, mi folyik itt?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "Ne légy abszurd! Én csak abban segítek az embereknek, hogy a lehetô leggyorsabban és legkellemesebben megkapják azt, amiért erre a világra jöttek.";
			link.l1 = "Sámán vagy, vagy mi?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Hát, találkoztál Agueybanával, ez adhat neked néhány ötletet.";
			link.l1 = "Az a szegény, eltévedt és részeg indián a te mûved volt?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "Nem én adtam el a törzsét pár ezer font aranyért, nem én öntöttem le a torkán hordószámra a szeszt, és bizonyára nem én kényszerítettem arra, hogy szajhák százai közül szedjen ki minden ismert és ismeretlen betegséget. Ô kért meg, hogy fehér arisztokratát csináljak belôle, hát megtettem. Ahogy a sorsa megparancsolta nekem.";
			link.l1 = "Kívánságokat teljesítesz? Mint egy dzsinn a tündérmesébôl? Uramisten, mi folyik itt?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "Ne légy abszurd! Én csak abban segítek az embereknek, hogy a lehetô leggyorsabban és legkellemesebben megkapják azt, amiért a világra jöttek. Agueybanának meg kellett volna mentenie a népét az európai megszállók igájától, ehelyett azonban túlságosan is nyálcsorgatta a parancsnok lányának fûzôjét, és úgy döntött, hogy zálogba adja a sajátját\nAkortól kezdve az egyetlen értelme az életének az volt, hogy rájöjjön a hibája mélységére, és hamarosan újrakezdje. Egy év Európában, a májzsugor és a bordélyházban töltött idô biztosan segített. De elismerem, remekül nyaralt, ha-ha!";
			link.l1 = "Cirrho mi? Sámán vagy, vagy mi?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "Vagy ilyesmi. Az ajánlatom tetszeni fog. És a változatosság kedvéért, én tényleg szívesen segítek.";
			link.l1 = "Hát persze. Mennyibe kerül?";
			link.l1.go = "joruba_9A";
			link.l2 = "És miért? Különleges vagyok?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "Nem is olyan rossz, kapitány. Vagy okos vagy, vagy hülye, mint egy szamár, de az esélyeid most egy kicsit megnôttek. Az ár nem lesz probléma.";
			link.l1 = "Meg kell ölnie valakit? Nem szoktam ilyet csinálni.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Mert a maga célja ebben az életben az, hogy lyukat üssön egy jó barátomon, ha-ha!";
			link.l1 = "Meg kell ölnie valakit? Nem szoktam ilyet csinálni.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "Elôször is, te. Másodszor, négy nagyobb tranzakciót fogunk lebonyolítani, és még négy kisebbet. Mindegyik sokkal erôsebbé tesz téged, és növeli az esélyeidet ebben a kegyetlen és furcsa világban. Ha minden üzletet teljesítesz, garantálom, hogy egy nap képes leszel arra, hogy egyenlô feltételek mellett harcolj az istenekkel, nem is beszélve a közönséges halandókról.";
			link.l1 = "Jól hangzik. Mesélj róla.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "Okos választás! Általában a beszédeim ahhoz vezetnek, hogy az embereket szívroham gyanújával elviszik Blueweldbe, de te elég jól tartod magad. Itt a feladatlista: apró, cserekereskedelem jellegû megbízások, amiket elvárok tôled. Nincs határidô, hehe.";
			link.l1 = "Kíváncsi vagyok. Késôbb elolvasom a listát. Még valami?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Igen, az elsô nagyobb tranzakció. Kétezer dublon az ár.";
			link.l1 = "Talán ráharapok... De ez rengeteg pénz! Miért kell ennyi? Fizethetek pezóban?";
			link.l1.go = "joruba_13";
			link.l2 = "Megôrültél? Ennyi pénzbôl vehetek egy fregattot!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "A piramis javításra szorul - a falazat néha a vásárlók fejére esik, és ez nem tesz jót az üzletnek. Az embereim minden nap foltozgatják, de a szervezetünknek sürgôs pénzinjekcióra van szüksége kívülrôl, hogy végleg rendbe hozzuk a helyzetet. Ami a pesót illeti - nem nagyon kedvelem, mivel az árfolyamuk meglehetôsen ingadozó.";
			link.l1 = "Ön igazságtalan a becsületes pesókkal szemben... Várjunk csak, nem egyedül vagy itt?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "Nem, én egy komoly szervezet homlokzata vagyok. Szóval, benne vagy?";
			link.l1 = "Meggondolom, de elôbb szeretném tudni, hogy mit kapok egy ilyen vaskos összegért.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "Miért rontanám el a meglepetést? Különben is, csak kezeld azt a pénzt adóként. A legértékesebb szerzeményed a következô üzletek feloldása lesz. A jutalom isteni lesz. Egyedülállóak is, hiszen sehol máshol nem találod meg ôket!";
			link.l1 = "Rendben. Mi is a neved?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Aruba a csodálatos. Még egy utolsó dolog, " + pchar.name + ", a piramisba naponta csak egyszer lehet belépni. Ne tartsd fel a többi ügyfelet, és ne zavarj engem a semmiért.";
			link.l1 = "Nem látom, hogy sorban állnának... Viszlát, felség.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ahoy, kapitány. Mit hoztál nekem?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Itt vannak a dublonjaid. Elég nehéz cipelni azt az átkozott fémet... de még nehezebb megválni tôle!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "Én betartottam az alku rám esô részét. Itt a gyógynövényed, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' a tiéd!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Rózsaszín '" + chref.Ship.Name + "' a tiéd!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' a tiéd!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "Hajlandó vagyok áldozatot hozni.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "Hozok neked egy menyasszonyt és gondokat okozok a spanyol hatóságoknak, uram. A hölgy odakint sétálgat, jól védve az embereim által. Addig nem adom át neked, amíg meg nem gyôzöl szándékaid nemességérôl.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Itt a páncélod, Aruba. Gondoskodj róla, hogy a jutalmam kárpótoljon.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "Nálam vannak a foglyok, akiket kértél.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "Elhoztam neked a kacatjaidat. Tessék, száztizenhárom kô, ahogy kérted.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "Hajlandó vagyok áldozatot hozni.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec karakter statisztikái)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "Csak erre járok.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "Akkor legközelebb.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "Nem rossz, jól fogom használni azt az aranyat. Tessék, egy kis csecsebecse, ami korábban egy nagyon erényes Taino fônöké volt. Segít az aranyhalmok cipelésében. Biztosan segített neki, heh-heh...";
			link.l1 = "Köszönöm, és remélem, nem fogom megbánni. Mi a következô üzlet?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Várj egy percet. Adtam neked egy halom aranyat, és kaptam cserébe egy darab agyagot? Hát, vissza akarom kapni a pénzemet!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "Mi? Igen, a következô üzlet. Ez az arany egyelôre elég lesz, úgyhogy itt az ideje, hogy több spirituális árucikket fontolgassunk. Találnom kell egy gyógymódot.";
			link.l1 = "Miért, beteg vagy?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "A lelkem az. Látod, a papok az inkvizícióval történt incidens óta kerülik szerény piramisomat, úgyhogy hagyományosabb módszerekre kell hagyatkoznunk. Szükségem van, nos, a faktóriámnak tizenöt magarosa növényre, hogy mûködôképes maradjon.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "Az egy gyógynövény?";
			} else {
				link.l1 = "Tudom, hogy mi az, heh-heh.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "Ôszinte leszek - ez egy ritka, nagy értékû gyógynövény. Gondold meg alaposan, ha tényleg éveket akarsz tölteni azzal, hogy az egész szigetvilágban gyûjtsd?";
			link.l1 = "Nem ígérek semmit, de jó egészséget kívánok, és remélem, hogy a gyógynövényért kapott jutalmam megéri.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "Rendben, hivatalosan is szabadnaposnak nevezem a mai napomat! Egy ilyen üzlet, mint ez, igazi kincset ér. Íme!\nEz a machete egyszer ilyen közel volt ahhoz, hogy szétzúzza annak az idióta Kanek fejét! Ezért nagyon drága nekem, és alázatosan kérem, hogy vigyázzanak rá. Régi, de rendkívül jól megmunkált, ilyen acélt már nem gyártanak.";
			link.l1 = "Kanek? Ki az?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Ó, ti ketten találkozni fogtok. Nos, remélem, nem vagy egy olyan nagyképû seggfej, aki lenézi a kétkezi munkát? Ha igen, akkor szarsz a szerencsédre, mert a jutalom második része a dupla töltetû lôszerek tervrajzai.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "Ó, azokat imádom. De mi az egyedi bennük? A dupla lôpor töltet nem újdonság, ezért arra következtetek, hogy nyilván nem hagytad el a piramisodat a múzeumi macsétás idôk óta.";
			} else {
				link.l1 = "Ennyi? Hé...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "Ne légy okostojás és figyelj! Bármelyik idióta képes két halom puskaport beletenni egy hordóba, és kockáztatja, hogy megvakul, megégeti az arcát vagy eltörik az orra. Ajánlok neked egy kis bûvésztrükköt: gondosan ellenôrizd a lôpor minôségét, ôröld meg a megfelelô állagúra, tegyél bele egy golyót vagy sörétet, és fûszerezd meg egy apróra vágott dublonnal. A durranás még egy kurucot is darabokra szaggat!";
			link.l1 = "Pénzt lôni, mi? Ez annyira hasonlít rád.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "Elviselhetetlen vagy! Rendben, fogj egy kézi aknavetôt, és egy tucat gránátot is hozzá. Ha olyan átkozottul okos vagy, akkor a gránátok tervrajzát pillanatok alatt magadtól is megszerezheted!";
			link.l1 = "Köszönöm szépen, uram. Mi a következô lépés?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "Nem fogod szeretni. Szükségem van egy hajóra... nem, szükségem van a hajóra. Tudod, egy történettel a háta mögött.";
			link.l1 = "Egy történettel a hátterében. Még csak nem is vagy kapitány.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "Semmi közöd hozzá! Jobb, ha a jutalmadra koncentrálsz, mert követelhetem, hogy takarítsd ki ezt a piramist tetôtôl talpig ezért, és akkor is tartozol nekem!";
			link.l1 = "Maga biztosan nem kapitány, különben tudná, hogy egy hajónak szüksége van egy mólóra vagy egy öbölre, ahol kiköt. Hogy a fenébe várhatod el tôlem, hogy bejuttassak egy hajót a piramisodba?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "Nem vetted észre véletlenül, hogy a piramisom mögött van egy hatalmas tó? Igen, így van. Csak dokkolj a megfelelô hajóval a közeli hajórajban, a többit az embereim elintézik. Most pedig kifelé, feltartja a sort.";
			link.l1 = "De persze. Viszlát!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "Szép volt! Megvan!";
			link.l1 = "Hagyd abba a nagyokoskodást, és add ide a jutalmamat!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "Mi van a másik kettôvel? Nem tudtad megmenteni ôket magadnak? Heh-heh.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "Mi van a másik kettôvel? Nem tudtad megmenteni ôket magadnak? Heh-heh.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "Mi van a másik kettôvel? Nem tudtad megmenteni ôket magadnak? Heh-heh.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "A francba, le vagyok nyûgözve, hogy nem akartad megtartani magadnak. Na ezt nevezem én egy hajónak, aminek története van! A fenébe, William... Tényleg azt kívántam, bárcsak hazatérnél, és találnál egy nagy bankot, ahogy mindig is álmodtad.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "Ezt nézd meg! Szégyent hozol a bizottságodra, " + sTemp + "!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "Charlie Prince úgy döntött, hogy megszabadul a terhelô bizonyítéktól a régi piramisomban? Jóváhagyom!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Sok szerencsét a feletteseinek a zászlóshajó elvesztéséhez, admirális. Ó, bocsásson meg, kormányzó tábornok.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "Maga babonás bolond, vagy csak egy bolond? Egy vagyont ér! Nem vagyok benne biztos, hogy ez egy tisztességes csere, de mindegy.";
				break;
				
				case SHIP_FDM:
					dialog.text = "Maga babonás bolond, vagy csak egy bolond? Egy vagyont ér! Nem vagyok benne biztos, hogy ez egy tisztességes csere, de mindegy.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "Maga babonás bolond, vagy csak egy bolond? Egy vagyont ér! Nem vagyok benne biztos, hogy ez egy tisztességes csere, de mindegy.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "Jó döntés! Szeretem a kasztíliaiakat, tudod. Talán majd visszaadom nekik, ha végeztem.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "Valóban, nincs szíve, kapitány. Ez a hajó bûzlik az árulástól. Elviszem.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "Igen, ennek a hajónak lehet, hogy van múltja... de nem volt túl könnyû megszerezni? Á, rendben. A maga esete különleges, kedvesem, úgyhogy átveszem. Legalább felidéz néhány emléket a fiatalságomból.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "Igen, ennek a hajónak lehet, hogy van múltja... de nem volt túl könnyû megszerezni? Ó, a fenébe is. Rendben, Kapitány, ezt most elnézem, mivel remek munkát végeztél azokkal a feladatokkal a listámról. Elviszem. Legalább felidéz néhány emléket a fiatalságomból.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "És láttad a papot? Nos, találkozni fogsz vele. És jobb lesz, ha felpakolsz kétlövetû pisztoly töltényeket. Ha ez nem segít - próbáld meg a fakarót.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "És láttad a papot? Nos, találkozni fogsz vele. És jobb lesz, ha felpakolsz kétlövetû pisztoly töltényeket. Ha ez nem segít - próbáld meg a fakarót.";
				break;
				
				case SHIP_MEMENTO:
					dialog.text = "És láttad a papot? Nos, találkozni fogsz vele. És jobb lesz, ha felpakolsz kétlövetû pisztoly töltényeket. Ha ez nem segít - próbáld meg a fakarót.";
				break;
			}
		break;
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "Igen, ennek a hajónak lehet, hogy van múltja... de nem volt túl könnyû megszerezni? Nem lehet! Még mindig van egy csomó befejezetlen munkád a listáról. Ha ezt elvégezted, újra megbeszéljük ezt az áldozatot.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "Áldalak téged, " + GetFullName(pchar) + ". A tenger legyen kegyes hozzád. Most pedig beszéljünk a következô tranzakcióról...";
			link.l1 = "Várj, mit? A mi korunkban még a bunkó idióták sem dôlnek be ilyen ostobaságoknak! Nem egy centime-ot tettem az alamizsnás dobozodba, hanem egy teljes értékû hadihajót adtam neked!";
			link.l1.go = "joruba_insult";
			link.l2 = "Várj egy pillanatot. Pontosan mit jelent nekem az áldásod?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "Bármelyik hajó, amelynek te leszel a gazdája, mostantól erôsebb hajótesttel lesz megáldva, míg az ellenségeid az ellenkezôjét fogják elszenvedni. Továbbá, a tengeren töltött idô lassabban fog telni számodra. És ha ez nem elég ahhoz, hogy térdre kényszerítsd ezt az egész szarfészket, akkor jobb, ha elmész az apádhoz, és követeled a pénzed visszafizetését!";
			link.l1 = "Ha nem válik be, esküszöm, még ma este visszajövök ide, és felgyújtom a piramisodat! Mesélj a következô üzletrôl!";
			link.l1.go = "joruba_p3_3";
			notification("+10% burkolatvédelem", "None");
			notification("+10% sebzés az ellenséges hajók burkolatán", "None");
			notification("+5% sebesség a globális térképen", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "Kezdesz ráérezni az ízére, mi, kapitány? Szerencsétlenségére én is. Mit gondol, miért választottam ezt a piramist az irodámnak?";
			link.l1 = "Valószínûleg azért, mert a boszorkánytisztítás még mindig divatos dolog?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Nem, nem egészen. Azért végzem itt az üzletet, mert a legjobb üzlethez vér kell. Ehhez a piramishoz vér kell. Nekem vér kell. Így volt ez eddig is, és így is lesz ezután is.";
			link.l1 = "Ne is gondolj rá, te szörnyeteg. Nem fogok áldozatokat szállítani neked, hogy megölhess!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "És hányat öltél meg, mi? Várj, még a pontos számot is megmondom: te személyesen öltél meg " + (Statistic_AddValue(pchar, "Solder_s", 0) + Statistic_AddValue(pchar, "Citizen_s", 0) + Statistic_AddValue(pchar, "Warrior_s", 0) + Statistic_AddValue(pchar, "Solder_g", 0) + Statistic_AddValue(pchar, "Citizen_g", 0) + Statistic_AddValue(pchar, "Warrior_g", 0)) + " embert! Hullák hegyét tetted a becsvágyad és gazdagságvágyad oltárára! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text + "A bátyád adóssága már több embert ölt meg, mint egy átlagos európai háború! ";
			}
			dialog.text = dialog.text + "Ne is kezdj itt velem erkölcsösködni, fôleg, hogy nem fogok ítélkezni feletted. Egyesek sikerét mindig mások tragédiáival fizetik meg, és az istenek, ó, istenek, figyelik és beszedik a részüket!";
			link.l1 = "Nem tudok most választ adni... El kell mennem innen.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "Sürgôs szükséged van arra, hogy kiszellôztesd a fejed? Rendben, de elôbb hallgass meg! Hatalmat és teljes uralmat adok neked a tested és az elméd felett, ha elhozol nekem egy nagy értékû embert. Nem egy statisztát, nem egy arctalan szürke egeret az utcáról vagy egy patkányt a bûzös fenékbôl. Hozz nekem egy embert, aki követ téged, és fontos szerepet játszik a tragikomédiádban.";
			link.l1 = "Az egyik tisztem? Ennél lejjebb már nem mehetsz, Aruba! Ha ennek híre megy...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "Gondoskodom a titoktartásról, ahogy mindig is szoktam. És mielôtt megint nyafogni kezdenél, tudatom veled, hogy van más megoldás is.";
			link.l1 = "Mit akar ez jelenteni? Hogy ne kelljen a saját embereimet az oltár elé vonszolnom?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "Nem, de nem fog tetszeni az alternatíva. Ha nem akarsz vérrel fizetni, fizethetsz arannyal is. Háromezer dublonnal és tiszta lelkiismerettel. A pénz képes erre és még többre is - imádom!";
			link.l1 = "Viszlát, Aruba. Nem akarok többé beszélni veled.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "Tudod, hol találsz meg.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Csináljuk gyorsan, mielôtt a spanyol inkvizíció megjelenik. Sangre u oro?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Arany. Itt van a háromezred, bár el sem tudom képzelni, hogyan tudsz ilyen hatalmas összeget elkölteni ebben a vadonban.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Vér.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "Mindegy.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "Befejezted? Beszéljünk a díjamról.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "Hát legyen. Mondd ki a nevet.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand nem tiszt, hanem egy kegyetlen zsoldos, úgyhogy válasszon egy másik áldozatot.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Elfogadom a kitüntetését. Nem kell néznie.";
			link.l1 = "Nem, nem kell. Egy órán belül visszajövök a jutalmamért.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Remek választás. Utálom megtisztítani az oltárt a sok vértôl, úgyhogy az arany jobb választás. Tessék, fogadd el ezt a bájitalt - egy jó barátom bókja.";
			link.l1 = "Az íze egyáltalán nem rossz...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.T.E.S. pont", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "Befejezted? Beszéljünk a díjamról.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "Bármikor szólj hozzám, ha meg akarod változtatni a sorsodat.";
			link.l1 = "De mit is jelent ez pontosan számomra?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "Hatalmat önmagad felett! Próbáld ki néha, és imádni fogod. Addig is hadd meséljek a következô tranzakcióról. A legfontosabbról.";
			link.l1 = "Már nem biztos, hogy megéri!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Gyerünk már, bökd már ki!";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "Lehetôséged van arra, hogy ne csak a sorsodat változtasd meg, hanem korunk zsenijei és istenei mellé állj. Igen, most már annyit változtathatsz a tested és az elméd, amennyit csak akarsz, de soha nem fogsz a fejed fölé ugrani, mert egy átlagember nem lehet mindenben jó. Én azt javaslom, hogy törd át ezeket a határokat.";
			link.l1 = "Mibe fog ez nekem kerülni? Még több vér? Aranyat?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Igen. Vagy hozol nekem huszonötezer dublont, vagy az egyik társadat. Ha végeztünk, nem lesz több tranzakció.";
			link.l1 = "Meggondolom.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "Tudod, hol találsz meg. És ne habozz, bármikor felkereshetsz, ha szeretnéd megváltoztatni a sorsodat.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "Ahogy óhajtja.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "Elôször is, ô a feleségem, nem menyasszony. Másodszor, neked a kasztíliaiakkal van bajod, nem velem. És végül, már elvettem ôt és elbocsátottam az embereidet. És ami a becsületes szándékot illeti... Nézz rám, nem vagyok én egy tisztességes úriember mintaképe? Tlazolteotl, áldd meg ôt, hogy egy nap ô is megismerjen egy igazi nôt. Vagy egy férfit.";
			link.l1 = "Cseszd meg, Aruba!";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 energia!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "Nem rossz, köszönöm. Ôszintén szólva nincs rá szükségem, de talán majd viselem valamelyik szalonban, vagy ilyesmi. Ishtar nevében megáldalak. Most menj és vétkezz.";
			link.l1 = "Milyen furcsa érzés...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 energia!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "Majd én elviszem ôket. Mi van? - Nekem is szükségem van halottakra a csapatomban, mint neked, csakhogy veled ellentétben én nem járhatom a kocsmákat toborozni. Most pedig, Bast, áldd meg a hôst a jövôbeli törekvéseire.";
			link.l1 = "Milyen furcsa érzés...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 energia!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "Igen, vissza kell majd szórnunk ôket, mert az emberek folyton elveszítik ôket, nekünk pedig szükségünk van a vendégekre. Freya, védd meg ezt a nagyszerû kôgyûjtôt.";
			link.l1 = "Milyen furcsa érzés...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 energia!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Csináljuk gyorsan, mielôtt a spanyol inkvizíció megjelenik. Sangre u oro?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Itt az aranyad, te mohó szemétláda!";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Vér.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "Mindegy.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Mondd ki a nevét.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "jövendôbeli feleség";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "jelenlegi feleség";
				}
				
				dialog.text = "Ez nagyon csábító, de most az egyszer kivételt teszek - nem fogadom el az áldozatodat. Nem fogom ezt felfedni a " + sTemp + ", bár valószínûleg kellene. Ne feledd, hogy nélküle semmi vagy. Most pedig tûnj el, és ne zavarj ma engem.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand nem tiszt, hanem egy kegyetlen zsoldos, úgyhogy válasszon egy másik áldozatot.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Úgy legyen. Tessék, fogadd el ezt a bájitalt - egy jó barátom bókja.";
			link.l1 = "Az íze egyáltalán nem rossz...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.T.E.S. pont.", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "Viszlát legközelebb, kapitány.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "Ahoy-hoy! Végre vége!";
			link.l1 = "Hm?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "Itt végeztünk, kapitány. Az üzletet megkötöttük, mindenki elégedett, és nincs helye a visszatérítésnek. Az irodánk bezár és elköltözik.";
			link.l1 = "Várj egy pillanatot, Aruba. Rengeteg aranyat adtam neked, vérrel fizettem, nôket és foglyokat hoztam ebbe az ördögi búvóhelyre. Tudom kezelni a természetfeletti eseményeket, amelyek nyilvánvalóan a Karib-tengeren történnek. De a mi 'tranzakcióink' veled minden logikának ellentmondanak. Kérem, magyarázza meg.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "Tudod mit? Elmondom neked.\nNekem elegem van ebbôl a világból, és ki akarok szállni. Minden nap ugyanaz a régi rutin: egy ôsi piramis omladozó mennyezettel, azok az undorító egyforma pálmafák, és a kapitányok véget nem érô áradata, mindegyikük a saját zseniális ötleteivel. Igen, megadom az embereknek, amire vágynak; ez a hivatásom, és büszke vagyok rá. De az istenekre, mennyire utálom mindannyiukat!";
			link.l1 = "Valaki itt tartja magát? Ott van a kijárat, zsenikém!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "Teljesen igazad van, senki sem tart itt. Többé már nem. És ez mind neked köszönhetô, barátom.";
			link.l1 = "Ez aztán a hirtelen változás. Vártam egy történetet, de eddig csak egy aljas lil' isten értelmetlen szónoklatait hallottam egy poros piramisban.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Hát, mindenkinek szüksége van arra, hogy idônként kieressze a levegôt, nem igaz? Nagyon örülök, hogy idejöttél, mert neked köszönhetôen végre eltávozhatok ebbôl a világból. Arany, legénység, felszerelés és egy hajó, barátom. Emlékszel? Ismerôsen hangzik? Csak ennyire volt szükségem, és te mindezt biztosítottad.";
			link.l1 = "Szívesen. De ez még mindig nem tisztázza a különös beszédmódodat és a szinte isteni erôdet. Ha olyan mindenható vagy, már régen elôvarázsolhattad volna a saját hajódat, legénységedet és aranyadat!";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "Amit meg is tettem, mint láthatod. Mindenkinek megvannak a maga módszerei.";
			link.l1 = "De hogy a fenébe? Ki vagy te pontosan?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Hát... egyszerûen ezt csinálom. Találkozunk az új világban, " + GetPersonaName() + ". Remélem, legközelebb tényleg új. Köszönöm és viszlát.";
			link.l1 = "Nem, nem akarlak többé látni.";
			link.l1.go = "exit";
			link.l2 = "Akkor még találkozunk, Aruba... ez érdekes volt.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "Úgy tûnik, minden üzletnek vége. Ideje indulni, kapitány.";
			link.l1 = "Itt az ideje, hogy...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "A spanyol inkvizíció nevében, nevezd meg magad!";
			link.l1 = "Kapitány "+GetFullName(pchar)+". És igaz, amit mondanak, senki sem számít a spanyol inkvizícióra...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... Ez a vicc mindig a lényegre tör, még akkor is, ha jó néhány ártatlan keresztényt máglyára vitt.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Csak vicceltem, kapitány. Te is vicceltél, én is vicceltem. A nevem Padre Emilio Bocanegra, és ezek Krisztus katonái az én fegyveres ôrségem.";
			link.l1 = "Mit tehetek önért, atyám?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "Ismer egy bizonyos Senor Arubát?";
			link.l1 = "Igen, ebben az öreg piramisban élt a közelmúltig.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "Hogy érted, hogy ott élt? Lehetséges ott élni? And why 'until recently'?";
			link.l1 = "Ez a senor néhány perccel ezelôtt hagyott el minket egy hajóval.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "Honnan tudja ezt? A legközelebbi öböl napokra van!";
			link.l1 = "Ez a tó nagyobb lehet, mint amilyennek látszik. Nem tudok más magyarázatot adni, padre.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Furcsa dolgok történnek az alkirályság földjén.";
			link.l1 = "Ezek angol földek, padre.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "Hadd higgyék ezt az eretnekek továbbra is. Mi biztosan visszakapjuk a miénket. Bocsáss meg, fiam, hogy ennyit kérdezôsködöm: Santiago utasított, hogy folytassak hivatalos vizsgálatot a piramisról... és annak egykori lakójáról.";
			link.l1 = "Mi történt pontosan, padre?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Mivel az ügyet valószínûleg le fogják zárni, egy kis történettel szórakoztathatom Önöket.\nEzzel a hellyel kapcsolatos pletykák már egy ideje keringenek az egész Mainban. Megbízható híreket kaptunk arról, hogy a múltban több, a régió történelmében jelentôs nyomot hagyó egyéniség is rendszeresen megfordult itt\nMégis Santiago a panamai incidens után kezdett igazán figyelni ezekre a pletykákra.\nEgy bizonyos indián nagy port kavart abban a dicsô városban, sôt több, meglehetôsen filozofikus jellegû prédikációt is tartott. Sajnos Panama lakosai meglehetôsen felületes következtetéseket vontak le, és meggyôzték magukat arról, hogy ez a piramis mérhetetlen kincseket rejt, és minden kívánságot teljesít\nAz eretnekség a legtisztább fajtája, természetesen... ezért kellett eljárást indítani néhány panamai lakos és ez az indián, Aguebana ellen.";
			link.l1 = "Miért nem léptek fel a panamai hatóságok?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "Mint mindig az ilyen esetekben, azt állították, hogy megbabonázták ôket. Ezt a jogi kiskaput be lehetett volna zárni, ha kihallgatjuk Aguebanát, de ô hirtelen meghalt.";
			link.l1 = "Hogyan halt meg?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "Részegség végzett vele. Halála azonban nem oldotta meg a problémáinkat, mert az eretnekség az egész szigetvilágban gyökeret vert, és emberek százai indultak egyfajta zarándoklatra ehhez az ôsi templomhoz.";
			link.l1 = "Még soha nem láttam itt embertömegeket... És akkor mi volt, hogy megszállják Arubát, és bíróság elé állítják?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Természetesen nem, fiam. Az inkvizíció ítélete szigorú, de igazságos. Jó oknak kell lennie a tárgyalásra. Nem, én csak össze akartam gyûjteni Aruba tanúvallomását, és átadni Santiagónak.";
			link.l1 = "Nos, ez szerencsétlen önnek.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "Sosem tudhatod, fiam. Ez Isten akarata.";
			link.l1 = "Viszlát, atyám.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,    0.0,  0, 0,  20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,      0.0,  1, 0,  20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,    0.0,  1, 2,  20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,     0.0,  0, 2,  30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,     0.0,  0, 0,  20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,    5.0,   1, 0,  20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0,    0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,   40.0,   0, 0, 100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,    0.0,   0, 0,  20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  15.0,    0, 0,  30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,   5.0,    1, 0,  30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,   0.0,    0, 4,  34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		InitGunExt(		"mushket1", "t3",    "bullet_double",      			"", 240.0, 440.0,  0.0,    0, 0,  20, 0);
		InitGunExt(		"mushket2", "t3", 	 "bullet_double",      			"", 270.0, 470.0,  0.0,    0, 0,  15, 0);
		InitGunExt(		"mushket5", "t3", 	 "bullet_double",      			"", 400.0, 600.0,  15.0,   0, 0,  15, 0);
		InitGunExt(		"mushket7", "t3", 	 "bullet_double",      			"", 300.0, 440.0,   0.0,   0, 0,  18, 0); // Качественный мушкет cle
		InitGunExt(		"mushket8", "t3", 	 "bullet_double",      			"", 200.0, 400.0,  0.0,    0, 0,  20, 0); // Четырехзарядный штуцер cle
		InitGunExt(	  "mushket2x2", "t3", 	 "bullet_double",      			"", 360.0, 560.0,  15.0,   0, 0,  15, 0);
		
		InitGunExt(		"mushket3", "t2", "grapeshot_double",	            "", 140.0, 240.0,    0.0,    1, 0,  13, 0);
		InitGunExt(		"mushket6", "t3", "grapeshot_double",	            "", 180.0, 310.0,  20.0,   1, 0,  15, 0);
		InitGunExt(		"mushket9", "t3", "grapeshot_double",	            "", 140.0, 240.0,   0.0,   1, 0,  23, 0);
		InitGunExt(	  "mushket10",  "t3", 	 "bullet_double",      			"", 360.0, 440.0,   0.0,   0, 0,  21, 0);
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
	
	ref itm;
	
	makeref(itm, items[FindItem("mushket9")]);
	
	itm.type.t3.basedmg  = 3;
	itm.type.t3.shards  = 110;
	itm.type.t3.width   = 8.5;
	itm.type.t3.height  = 7.85;
	itm.type.t3.area    = XI_ConvertString("grapes_area_4");
		
	if(CheckAttribute(itm, "UpgradeStage"))
	{
		int iUpgradeStage = sti(itm.UpgradeStage);
		
		switch (iUpgradeStage)
		{
			case 2:	
				itm.type.t3.basedmg  = 3;
				itm.type.t3.shards  = 120;
				itm.type.t3.width   = 7.0;
				itm.type.t3.height  = 5.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_4");
			break;
			
			case 3:	
				itm.type.t3.basedmg  = 4;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 5.5;
				itm.type.t3.height  = 4.5;
				itm.type.t3.area    = XI_ConvertString("grapes_area_3");
			break;
			
			case 4:	
				itm.type.t3.basedmg  = 5;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 4.5;
				itm.type.t3.height  = 3.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_2");
				itm.type.t3.ChargeSpeed = 18;
			break;
		}
	}
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
