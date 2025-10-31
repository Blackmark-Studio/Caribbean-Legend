void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
			dialog.text = "Mit akarsz?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "Mit akartál, "+GetAddress_Form(NPChar)+"? Bocsánat, de most nem vállalok új megrendeléseket. Egyszerűen... túl sok a dolgom...";
			link.l1 = "Valóban? Úgy hallottam, nemrég elveszítettél valami nagyon értékeset egy kártyajátékban, igaz ez?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "Nos, ha hencegni jöttél, állj be a sorba – így is elég ember vár erre nélküled is. De egyikük sem ajánlott fel segítséget. A sorsom egy hajszálon függ, teljesen Javier Castillo kegyétől, miközben mindenki csak a balszerencsémen akar gúnyolódni.";
			link.l1 = "Nem vagyok az a fajta, aki mások balszerencséjén nevet. Mondd el, mi történt. Talán tudok segíteni.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "Segítség? És ugyan miért adná ezt bárki is neked? Én biztosan nem fogok. Te kovácsolod a saját boldogságodat... és a szerencsétlenségedet is. Szóval ne játszd az áldozatot – fogadd el a tetteid következményeit, hiszen ezek teljesen természetesek.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "Az az este nem kellett volna végzetes legyen. Csak egy korsó rumért tértem be a kocsmába, miután maga Eugenio de la Torre admirális adott le nálam egy nagy rendelést. De aztán, kissé kapatosan, leültem egy asztalhoz kártyázni. Ekkor szemelt ki magának Javier\nEleinte nekem kedvezett a szerencse – még egy tisztességes összeget is nyertem, de ahogy elhittem, hogy mellém állt a Fortuna, minden megfordult. Javier folyamatosan töltötte a rumot a korsómba, én meg csak veszítettem: előbb az összes készpénzem elment, aztán az anyagra félretett pénz, végül minden megtakarításom\nMire felfogtam, mennyit veszítettem már, késő volt kiszállni. Csak egy gondolat járt a fejemben – visszanyerni mindent, bármi áron. És ekkor feltettem a könyvemet. Az a gazember Javier csak ötezer pesóra értékelte\nPersze, sokkal többet ér, de annyira elvakított az izgalom, hogy belementem. És aztán... azt hiszem, a többit már tudod. Elvesztettem. Tudod, velem ilyen még sosem fordult elő. Azt hiszem, az a gazfickó valamit belekevert az italomba.";
			link.l1 = "És mégis, hadd kérdezzem meg, hogyan segíthetnék én neked? Te magad ültél le az asztalhoz, te magad tetted fel a vagyonodat, és te magad veszítetted el mindent. Most meg egyszerűen nem akarod elfogadni a következményeket? És mi olyan értékes ebben a könyvben, hogy ennyire bánkódsz miatta?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "Ez a könyv volt a legértékesebb dolog, ami valaha az enyém volt. Évszázadokon át mesterről tanítványra szálló titkokat rejt. Ez a kovácsműhelyem szíve, a mesterségem lelke. Már beletörődtem a veszteségbe, "+GetAddress_Form(NPChar)+", de hogyan tudnék beletörődni, hogy elveszítettem a könyvet? Váltságdíjat ajánlottam fel Javiernek érte – ötezer pesót\nKészen álltam eladósodni is, csak hogy visszaszerezzem. De tudod, mit mondott? Azt mondta, százezret akar érte! Százezret, "+GetAddress_Form(NPChar)+"! Nekem nincs ennyi pénzem. És ő nem hajlandó csökkenteni az árat, vagy elfogadni részletekben. Könyörögtem neki... de csak kinevetett. Látom, te is "+GetSexPhrase("egy bátor ember, egy tengerész... talán még kapitány is. És a fegyvered sem csak dísznek lóg ott","nem egy hétköznapi nő, és biztosan megtalálja az utat bármelyik férfihoz")+"\nKérlek, beszélj Javierrel. Talán rád hallgat, és beleegyezik, hogy elhalassza az adósság kifizetését. E könyv nélkül... az életemnek nincs értelme. Cserébe, ha talpra állok, mindig jó áron tudok neked minőségi anyagokat adni, sőt, talán még valami különlegeset is készítek neked, kapitány.";
			link.l1 = "Nos, a beszélgetés nem okoz gondot. Majd meglátjuk, mi sül ki belőle. De először engedje meg, hogy bemutatkozzam: a nevem "+GetFullName(pchar)+", a saját hajóm kapitánya.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("És én vagyok Sebastian Cordoba...","Egy nő – saját hajó kapitánya? Hallottam már ilyesmiről, de még sosem találkoztam eggyel sem, és nem is beszélgettem vele.")+" Örülök, hogy megismerhetem, kapitány "+pchar.lastname+". És köszönöm. Manapság könnyebb találni olyanokat, akik mások balszerencséjén gúnyolódnak, mint akik segíteni hajlandóak. Tudja, ha a könyvem visszakerül hozzám, esküszöm: soha többé nem játszom szerencsejátékot.";
			link.l1 = "Még nincs miért megköszönnöd. Először a saját dolgaimat intézem, aztán, ha marad időm, beszélek Javierrel.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "Attól tartok, talán elkéstél. Javier sokkal gyorsabbnak bizonyult, mint gondoltam\nMár talált is vevőt a könyvre – Etienne Renoir-t, egy francia mesterfegyverkészítőt. Ha az admirális megtudja, hogy miattam ilyen kincs került a franciákhoz... fejemet veszik. A börtön még könnyű büntetés lenne.";
			link.l1 = "Hmm... Rendben. Azonnal foglalkozom a problémáddal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Kapitány "+pchar.lastname+"! Beszéltél Javierrel? Van valami hír?";
			link.l1 = "Még nem, de épp most indulok a kocsmába.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "Beszéltem"+GetSexPhrase("","")+". És igen sikeresen. Javier sietve távozott erről a világról, de előtte még visszaadta a könyvedet. Tessék, itt van.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", el sem tudod képzelni, mennyit jelent ez nekem! Neked köszönhetően most már minden megrendelést teljesíthetek, még magának az admirálisnak is dolgozhatok! Sajnos pénzem nincs, de azért készítettem neked egy jutalmat\nNesze, vedd ezt a páncélt – eredetileg egy bizonyos donnak készítettem, de biztos vagyok benne, hogy tud várni egy kicsit. Van még néhány anyagom is, ami jól jöhet, ha magad akarsz valamit készíteni.";
			link.l1 = "Köszönöm, "+npchar.name+", nagyon nagylelkű vagy!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "És ha szükséged van anyagokra, ugorj be hozzám. Havonta egyszer kapok utánpótlást, így mindig lesz nálam valami hasznos – ráadásul jó áron. Amit ígérek, azt be is tartom.";
			link.l1 = "Biztosan megteszem! Nos, "+npchar.name+", vigyázz magadra. Indulok, dolgom van.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Kapitány "+pchar.lastname+"! Beszéltél már Javierrel? Van valami hír?";
			link.l1 = "Látod... a könyv nálam volt. De... úgy alakultak a dolgok, hogy eladták.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "Mi?! Te... eladtad?! Az én könyvemet?!";
			link.l1 = "A könyv, amit elveszítettél a kártyajátékban. Annak a franciának adták el, akinek Javier megígérte.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "De... most már vége mindennek. A könyv a franciáknál van, az admirális parancsa nem teljesül... az életem tönkrement... én... én elvesztem!";
			link.l1 = "Sarokba szorítottad magad. Azt hiszem, ez jó lecke lesz számodra. Ég veled.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\English\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "Szia, "+GetSexPhrase("tengerész","cukorfalat")+", szeretnéd kipróbálni a szerencsédet kártyában? Ülj le, itt a tétek barátságosak... legalábbis a kezdőknek.";
			link.l1 = "Az az érzésem, pont téged kereslek. Pontosan így csábítottad el Sebastiant is, mielőtt teljesen kiforgattad a vagyonából, igaz? Azért vagyok itt, hogy visszaszerezzem a könyvét.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "Nos, nagyszerű. Adj százezeret – és viheted is. Semmi szükségem arra a könyvre, még a fogót sem tudom megkülönböztetni a kalapácstól.";
			link.l1 = "Adok neked ötezeret – ezt az árat te magad szabtad meg, amikor legyőzted a kovácsot.";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "Ha! Bolondnak nézel? Pontosan tudom, mennyit ér az a könyv valójában. Százezer, és egy garassal sem kevesebb. Különben megy a franciáknak – náluk nincs gond a pénzzel.";
			link.l1 = "Azt hiszed, a hatóságok szemet hunynak afölött, hogy spanyol tervrajzokat adsz el a franciáknak? Az admirális dühöngeni fog, ha rájön.";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "Ugyan már. A hatóságokat nem érdekli valami könyv, így is elég bajuk van. És az admirális? Persze, szívből gyűlöli a franciákat, de én nem fogok itt maradni, hogy megvárjam – ilyen pénzzel bármelyik gyarmaton szívesen látnak majd az Újvilágban.";
			link.l1 = "Akkor kössünk üzletet. Megkapod a pénzed, de nem azonnal. A kovács részletekben fogja törleszteni az adósságot, és a könyv ma visszakerül hozzá, a kapitányi becsületem zálogaként. Neked semmi sem változik – ő továbbra is fizetni fog, és te egyetlen pesót sem veszítesz.";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "Úgy tűnik, nem hallasz engem. Teljesen világosan megmondtam – most kell a pénz. Nem egy hét múlva, nem egy hónap múlva, és nem akkor, amikor a kovács végre összekaparja, hanem most azonnal. Azt tervezem, hogy minél előbb lelépek erről a nyomorult szigetről. Szóval vagy most azonnal a teljes összeget a kezembe adod, vagy a könyv megy a franciáknak, és a kapitányi becsületedet zálogba adhatod az admirális hóhéránál.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "Mit szólnál ehhez: játsszunk. Az én százezerem a könyv ellenében. Ha nyersz, gazdagon hagyod el a szigetet. Ha veszítesz – én viszem a könyvet. Vagy csak olyanokkal játszol, akik még sosem láttak kártyapaklit?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "Ha! Nem kell meggazdagodnom – már most is gazdag vagyok! Miért kockáztatnék valamit, ami úgyis egy rakás pénzt hoz nekem?";
			link.l1 = "Nos, nos, maga Javier Castillo fél játszani? És én azt hittem"+GetSexPhrase(""," te")+", te egy tapasztalt játékos voltál, nem csak egy szélhámos, aki részeg balekokat húz le a pénzükről.";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "Nem félek, csak nem látom értelmét az asztalnál ülni, amikor már mindent megvan, amire szükségem van.";
			link.l1 = "Ugyan már, látom, hogy remegsz attól a gondolattól, hogy most először nem valaki helyett játszol. Hadd találjam ki, azért sietsz annyira el innen, mert szégyelled magad? Mindenki rájött már, hogy senkit sem tudsz legyőzni, aki nem egy részeg együgyű?";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "Hogy merészeled?! Olyanokat is legyőztem már, akik még egy asztalhoz sem ülnének veled! Volt már akkora kassza, hogy hajót vehettünk volna belőle, és minden játékosnak jutott egy ilyen beképzelt kapitány! Játsszunk. Ötezer egy lap, százezer mindenkinek, aki kifogy a pénzből, veszít. Lássuk, ki kit ver meg.";
			link.l1 = "Kevesebb beszéd, több tett. Áll az alku.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "Az ördögbe! Ez nem lehet...";
			link.l1 = "Mi az, már nem olyan szórakoztató, ha éppen más nyer?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "Te egy csaló vagy! Azt hiszed, nem vettem észre semmit? Eszem ágában sincs hagyni, hogy átverj! Inkább darabokra váglak.";
			link.l1 = "Csaló? Ha-ha! Úgy tűnik, csak nem tudsz veszíteni, barátom. De ha ennyire sietsz a vesztedbe – segítek neked ebben. Fegyvert rántani!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "Ha! Nos, "+GetSexPhrase("cimbora","cukorfalat")+", milyen érzés, amikor lehúznak"+GetSexPhrase("","")+"? Azt mondják, a gőg a második boldogság, de nálad ez nem így van.";
			link.l1 = "Ne hízelegj magadnak. Csak szerencséd volt.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "A vesztesek mindig ezt mondják. Nos, játszottál"+GetSexPhrase("","")+" – vesztettél"+GetSexPhrase("","")+", ne vedd magadra. Ha egyszer találsz még százezerrel többet, újra próbálkozhatsz... De kétlem, hogy más lesz az eredmény...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "Szia, "+GetAddress_Form(NPChar)+". Minek köszönhetem a látogatását?";
			link.l1 = "Üdvözlöm. A nevem kapitány "+GetFullName(pchar)+", és beszélni akarok veled Javier Castillo-ról.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "Hmm... Ha az a gazember neked is tartozik, attól tartok, hosszú sorban kell majd várnod. Javier sosem siet visszafizetni a kölcsönöket. De ha mégis pénzhez jut, először nekem fog fizetni – már gondoskodtam róla, hogy ne legyen más választása.";
			link.l1 = "Szerencsére én nem vagyok a hitelezője. Mennyi pénzzel tartozik neked? És pontosan milyen lépéseket tettél eddig?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "Az ő teljes tartozása százötvenezer peso. Eddig csak tízezret fizetett, úgy tűnik, azt gondolta, ennyi elég lesz. De gyorsan világossá tettem számára, hogy téved. Az embereim még húszezret kiszedtek belőle. A többit egy héten belül kell visszaadnia, és a határidő már közeleg. Szerencsére hallottam, hogy hamarosan szép összeget kap egy könyv eladásából.";
			link.l1 = "Tényleg azt hiszed, hogy vissza fogja fizetni? Szerintem erre nem kéne komolyan számítanod. Javier még csak nem is titkolja, hogy amint megkapja a pénzt, azonnal lelép innen.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "Tisztában vagyok vele, kapitány. Megnyugtathatom, már gondoskodtam róla, hogy ne tudjon fizetés nélkül meglógni.";
			link.l1 = "Látom, uralod a helyzetet. Azonban, ahogy a tapasztalat mutatja, egy kis plusz óvatosság sosem árt. Tudod, én afféle szakértő vagyok"+GetSexPhrase("","ess")+"   adósságbehajtásban. Ha megengedi, hogy az ön nevében eljárjak, visszaszerezhetem a pénzét.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "Sajnos, Kapitány, ennek a tartozásnak a behajtása már így is túl sokba kerül nekem, és nem engedhetem meg magamnak, hogy még a maga szolgálataiért is fizessek...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", emiatt ne aggódj. Nekem is megvan a magam érdeke ebben az ügyben, úgyhogy ingyen segítek neked.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "Megkérdezhetem, pontosan mi érdekli?";
			link.l1 = "Mondjuk úgy, hogy néhány kártyatrükkjét nem hagyhatom büntetlenül.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "Nos, ha ez nem kerül nekem semmibe, nem látom okát, hogy visszautasítsam. Egyetlen dolgot kérek, Kapitány – ne menjen túl messzire. Ha az a gazember feldobja a talpát, mielőtt visszafizetné az adósságot, azzal én semmire sem megyek.";
			link.l1 = "Ne aggódj, Felipe, óvatosan fogok eljárni.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! Lehetséges, hogy ilyen gyorsan elintézted?";
			link.l1 = "Sajnos, még nem. De dolgozom rajta.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "Ah, "+GetSexPhrase("kapitány","cukorfalat")+"   Felkapaszkodott! Megint te? Mi van, még pár ezrest akarsz elbukni?";
			}
			else
			{
				dialog.text = "Megint te? Világosan megmondtam: pénz az asztalon – vagy tűnj el.";
			}
			link.l1 = "Változtass a hangnemen, Javier. És vedd elő a pénztárcádat – nem véletlenül vagyok itt. Ugye nem felejtetted el az adósságodat Felipe Alarconnak? Mostantól én képviselem az ő érdekeit. Szóval válassz: vagy most azonnal kifizeted a tartozást, vagy kénytelen leszek a zsebeidben keresni a pénzt, miután találkoztál a teremtőddel.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "A pokolba veled! Látod, épp üzletet kötök? Gyere vissza pár óra múlva – akkor majd beszélünk.";
			link.l1 = "Úgy tűnik, nem hallottad, amit mondtam. Teljesen világosan fogalmaztam: most kell a pénz. Nem egy hét múlva, nem egy hónap múlva, vagy amikor épp összekaparod, hanem most. Százhúszezer peso, egy fillérrel sem kevesebb. A könyvet hajlandó vagyok ötezernek beszámítani.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("Te mocskos gazember","Te nyomorult")+"! Ha azt hiszed, ilyen könnyen elbánhatsz velem – ez lesz életed legnagyobb tévedése, te semmirekellő.";
			link.l1 = "Meglátjuk.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "Micsoda látvány... Be kell vallanom, "+GetAddress_Form(NPChar)+", nagy örömet szereztél nekem. Remekül forgatod a kardot. Engedd meg, hogy bemutatkozzam – "+GetFullName(npchar)+". És ha nem tévedek, ez a szerencsétlen fickó Javier Castillo?";
				link.l1 = "Pontosan, ő az. És én vagyok a kapitány "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "Micsoda látvány... Be kell vallanom, "+GetAddress_Form(NPChar)+", nagy örömet szereztél nekem. Remekül forgatod a kardot. Furcsa, hogyan alakul néha az élet – a könyv, amiért ilyen messzire utaztam, egészen váratlan módon cserélt gazdát. De remélem, hogy azért nem távozom innen üres kézzel.";
				link.l1 = "Hmm... És mennyire tartod ezt a könyvet?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "Látja, Kapitány, elég messzire utaztam egy bizonyos könyvért... És úgy tűnik, most az ön kezében van. Őszintén remélem, hogy meg tudunk egyezni – nem szeretnék üres kézzel távozni innen.";
			link.l1 = "Hmm... És mennyire tartod ezt a könyvet?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "Ó, "+GetAddress_Form(NPChar)+", tudom, mennyit érnek az igazán ritka dolgok. Nyolcvanezer peso. Ez több mint nagylelkű ajánlat, és hidd el, aligha kapsz még egyszer ilyen lehetőséget.";
			link.l1 = "Nos, a könyv valóban értékes, és be kell vallanom, én kértem"+GetSexPhrase("","")+" pusztán kíváncsiságból. Nem áll szándékomban üzletelni egy ember sorsával. Attól tartok, uram, nem lesz alku – ennek a könyvnek vissza kell kerülnie jogos tulajdonosához.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "Nevetséges összeg. Ez a könyv a kovácsmesterség legnagyobb mestereinek titkait rejti. Százötvenezer peso – vagy elfogadod, vagy visszakerül a gazdájához. Alkudozásnak helye nincs.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "Kérem, ne utasítsa el ilyen gyorsan. Hosszú utat tettem meg ezért. Készen állok százezer aranyat ajánlani, pusztán tiszteletből azért az ügyességért, amivel elbánt azzal az emberrel.";
			link.l1 = "Mindet elmondtam, amit akartam. Most pedig, ha megbocsát, mennem kell.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", Értékelem a bizalmát, de százötvenezer – ez nem ár, ez nevetséges. Ne csináljunk bohózatot ebből az üzletből. Százezer peso egy ésszerű összeg, egyezzen bele – ennél többet senki sem fog adni ezért a könyvért.";
			link.l1 = "Úgy tűnik, nem találtunk közös nevezőt. Nos, nem látom értelmét folytatni ezt a beszélgetést. Viszlát, monsieur.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "Várj! Rendben, győztél. Százötvenezer. Megállapodtunk?";
			link.l1 = "Örülök, hogy jól döntöttél. A könyv a tiéd. Szerintem ezzel te leszel a legkiválóbb mester a Karib-térségben.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", még e könyv nélkül is páratlan voltam. De be kell vallanom, kellemes érzés egy ilyen ritka trófeát megszerezni. És most, engedj meg – alig várom, hogy megtudjam, valóban megfelel-e a róla hallott dicsérő szavaknak.";
			link.l1 = "Nos, akkor nem tartalak fel tovább. Viszlát.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Nocsak, nocsak, miféle szemét ez? Azt hitted, kifosztod a ládánkat és meglógsz? Nagy hiba volt, pajtás. Most mi tuszkolunk bele abba a ládába, és jól rá is szögeljük a fedelet!";
			}
			else
			{
				dialog.text = "No lám, no lám... Ki tévedt ide hozzánk? Elvesztél, édesem? Azt hitted, kisöpröd a ládát, aztán szépen lelépsz? Nagy hiba volt, drágám. Most alaposan átkutatunk – meglátjuk, mi lapul a zsebeidben... és máshol is.";
			}
			link.l1 = "Túl sok szó egy ilyen nyomorult féregnek, mint te. Rántsd elő a kardod, hadd lássuk, mire vagy valójában képes.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "Kapitány! Már tudom, hogy Javier a túlvilágra került, hála neked. Pedig kértelek, hogy ne öld meg túl hamar! Remélem, azért jöttél, hogy visszaadd a pénzem?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "Pontosan. Megtaláltam a rejtekhelyét, ahol százezer pesót tartott. Ez volt minden pénze.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "Igen, meg kellett ölnöm. De ő támadt rám először, és védekeznem kellett. A zsebei üresek voltak – egyetlen fillér sem volt nála. Sajnos nem sikerült visszaszereznem a tartozást.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "Százezer... Persze, ez nem a teljes összeg, de ismerve Javiert, kétlem, hogy bárki többet ki tudott volna csikarni belőle. Nos hát, köszönöm, Kapitány. Úgy tűnik, rossz embereket fogadtam fel. Ön valóban mestere a szakmájának.";
			link.l1 = "Nem volt nehéz. Nos, azt hiszem, most mennem kell"+GetSexPhrase("","")+". Az üzlet vár.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "Viszlát, Kapitány.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "Te "+GetSexPhrase("gazember","nyomorult")+"! Az arcomba hazudsz, miközben a szemembe nézel?! Ezt nem úszod meg!";
			link.l1 = "Argh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			dialog.text = "Szia, "+pchar.name+"! Szeretne anyagokat vagy árut vásárolni?";
			link.l1 = ""+TimeGreeting()+". Lássuk, mid van.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "És neked is szervusz, "+npchar.name+"! Köszönöm az ajánlatot, de csak szerettem volna"+GetSexPhrase("","")+" köszönni. ";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", végül mégis úgy döntött, hogy vásárol valamit?";
			link.l1 = "Pontosan. Mutasd, mid van ma.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Sajnálom, már indulok is.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}