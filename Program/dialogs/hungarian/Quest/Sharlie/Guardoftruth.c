// диалоги НПС по квесту 'В поисках Стража Истины'
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
			dialog.text = "Miben segíthetek?";
			link.l1 = "Sajnálom, semmiség.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "Mit akarsz? Még egy kihallgatás? Vete al diablo!";
			link.l1 = "Senor, mi a neve?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "Mi a fenét érdekli annak az embernek a neve, akit felakaszt vagy lelô? Bastardo! Elég óvatlan voltam ahhoz, hogy a kezébe kerüljek...";
			link.l1 = "Senor, azonosítsa magát. Nem tudok beszélni egy emberrel anélkül, hogy tudnám a nevét.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+". Tessék, boldog vagy? Most kivel van szerencsém beszélni?";
			link.l1 = "A nevem "+GetFullName(pchar)+". Hallottál már rólam?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "Nem, carajo! Úgy nézek ki, mint aki ismer minden csavargót Nyugat-Indiában, aki...";
			link.l1 = "Elég volt. Bántások nélkül, és viselkedjünk úriemberként. A sorsa attól függ, hogy mit tud mondani nekem. Ha valami érdekeset mond, akkor kérvényezem, hogy engedjék szabadon az ôrizetembe. Ez lehetôvé teszi, hogy megmeneküljön a muskétagolyó vagy a hurok elôl, ami most rögtön vár önre.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Dios mio, ezt az ajánlatot nem utasíthatom vissza. Mit szeretne tudni, senor?";
			link.l1 = "Ki szervezett ilyen nagyszabású támadást St. Pierre ellen és miért?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "Ramon de Mendosa y Riba báró, a Providence-sziget helyôrségparancsnoka. Ô küldött egy osztagot, hogy rajtaütésszerûen kifosszák a várost, és minden értéket elraboljanak, amit csak találunk.";
			link.l1 = "Mi volt a közvetlen feladata a támadás során? Konkrétan, mi volt a parancs?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "Én vagyok a tengerészzászlóalj parancsnoka. Az volt a parancsunk, hogy foglaljuk el az erôdöt, és biztosítsuk az ütegeit, hogy ne lôjenek a városhoz közeledô partraszálló hajóinkra. Ezután az embereim részt vettek magának St. Pierre-nek a megtámadásában.";
			link.l1 = "Tájékoztatták a városban található értéktárgyakról? A mennyiségrôl és a minôségrôl?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "Nem rendelkeztünk pontos információkkal a mennyiséget illetôen, de de Mendosa y Riba báró elmondta, hogy az erôd alatt ezüstöt tárolnak, és a kikötôi raktárakban stratégiai fontosságú nyersanyagok vannak, amelyek létfontosságúak a háborús erôfeszítésekhez: vasfa és hajóselyem.";
			link.l1 = "Megtalálták ezeket az értéktárgyakat?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "Nem, egyiket sem találtuk meg. A raktárak tele voltak tipikus gyarmati árucikkekkel, az erôd alatt pedig puskapor, fegyverek és ólom volt. De nem volt elég idônk alaposabb átkutatásra... a francia erôsítés dübörögve érkezett, és kénytelenek voltunk csatát adni.";
			link.l1 = "Nem találta furcsának, hogy nem találta meg az értéktárgyakat?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "Persze, hogy nem, de általában nem kérdôjelezem meg a parancsokat.";
			link.l1 = "Figyeljetek arra, amit most elmondok nektek. A St. Pierre erôdben soha nem volt ezüst, és azokban a raktárakban soha nem tároltak vasfát és selymet. Jól gondolja meg, senor, mielôtt válaszol, mert ha a válasza nem tetszik nekem, megfordulok és kisétálok innen, magára hagyva a sorsát... egy szomorú sorsot.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "Hallgatlak.";
			link.l1 = "Nem hiszem, hogy a rajtaütésed egyetlen célja egyszerû rablás volt. St. Pierre egy szerény és viszonylag szegényes kolónia ahhoz, hogy egy egész századot küldjön ide egy elsô osztályú hajóhad vezetésével. Bizonyára önnek vagy a parancsnokának, vagy valaki másnak további parancsai vagy utasításai voltak. Mit mondtak önnek? Jól gondolja meg, mielôtt válaszol...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "Nem fogsz hallgatni? Rendben, akkor... Gondolkodj egy kicsit, én várok.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Senor, az életem függ a válaszomtól?";
			link.l1 = "Helyes.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "Van valamim... De meg kell esküdnie, hogy kijuttat innen, és váltságdíjat kér értem Spanyolországba.";
			link.l1 = "Ha mond valamit, ami méltó a figyelmemre, a Szent Keresztre esküszöm, hogy váltságdíjért a hajóm fedélzetére adom, és megmenekül a kivégzéstôl.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "Rendben. Don Diego de Montoya utasította tengerészgyalogos zászlóaljunkat, hogy minden titoktartás és fontosság mellett találjunk meg és ejtsünk foglyul egy Miguel Dichoso nevû embert, aki valahol St. Pierre-ben tartózkodik a hatóságok védelme alatt.";
			link.l1 = "Menjünk tovább. Ki az a Diego de Montoya?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "A század parancsnoka. Nem sokkal az önök... drámai megérkezése után elmenekült.";
			link.l1 = "Ki ez a Don Diego?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "Csak annyit tudok, hogy ô de Mendosa y Riba báró meghatalmazott képviselôje, jobbkeze és ügynöke a kritikus feladatokban.";
			link.l1 = "Érdekes... És ki az a Miguel Dichoso, akinek az elfogására nyilvánvalóan ezt az egész katasztrófát szervezték? Biztos rossz ember lehet, mi?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Emlékszik az esküjére, senor?";
			link.l1 = "Emlékszik az emlékére, Senor? És megerôsítem, hogy ha tovább meséli a történetét, akkor mint koronatanút átadom a hajómon, és késôbb... nos, megtalálom a módját, hogy eljuttassam egy spanyol településre. De addig nem, amíg el nem mond nekem mindent, amit tud.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Miguel Dichoso a báró egykori fegyvertársa, bár egyesek szerint Miguel elárulta ôt. Senor de Mendosa y Riba élve akarja ôt, ezért azt a parancsot kaptuk, hogy Dichosót semmilyen körülmények között ne öljük meg.";
			link.l1 = "Dichoso is spanyol?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Igen. Don Diego de Montoya adott nekünk egy hozzávetôleges személyleírást, és elrendelte, hogy minden Dichosóra hasonlító férfit közvetlenül neki kell átadni. De mivel az ellentámadásuk elôtt csak kevés idônk volt, nem volt idônk átkutatni.";
			link.l1 = "Személyesen ismerte Dichosót?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "Nem, csak hírbôl. Soha nem láttam még ezt a férfit. Volt néhány tiszt társam, aki személyesen ismerte. Mindannyian halottak.";
			link.l1 = "Mennyire árulta el Dichoso az önök Don Mendosáját, hogy úgy döntött, egy egész századot küld utána?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "Elmondom neked. A báró csak nemrég érkezett a Karib-tengerre Spanyolországból. Az volt a parancsa, hogy gondoskodjon a spanyol kincses flotta konvojainak biztonságáról, de ehelyett inkább a szárazföld belseje felé nézett... indiai aranyat keresett. Elrejtett kincsekrôl szóló pletykák csavarták el a fejét. Úgy döntött, hogy valahol Yucatán dzsungelének mélyén létezik egy ôsi maja város - Tayasal, a legendás arany városa\nA báró több expedíciót is küldött a város felkutatására, de ezek mindegyike teljesen elpusztult a vad selvában. Nem kétséges, hogy mindegyiküket lemészárolta az ott élô harcias itza nép\nVégül Vincento inkvizítornak elege lett Don Mendosa fantáziálásából és a jó katonák értelmetlen halálából. Az inkvizítor tájékoztatta Madridot a helyzetrôl. Az alkirály megtiltotta Don Mendosának, hogy a mitikus várost keresse, és a kötelességeire koncentráljon. Ekkor jelent meg Miguel Dichoso\nÔ meggyôzte a bárót, hogy szervezzen egy újabb expedíciót, amely meglepô módon sikeres volt. Egy ôsi város romjait és egy halom ékszerekkel kirakott aranyat találtak. De visszatérésükkor megtámadta ôket a szúnyogtörzs\nMiguelt kivéve mindenki elpusztult, az indián dárdákat valamilyen helyi méregbe mártják, már egy kis karcolás is biztos, gyötrelmes halálhoz vezet néhány napon belül. Dichoso visszatért a Gondviselésre azzal a kincsével, amit magával tudott vinni\nCarajo! A báró kimondhatatlanul boldog volt, sürgôs leveleket küldött Madridba és Vincento atyának Santiagóba, nem kétséges, hogy sikerét a tisztelendô atya orra alá akarta dörgölni. Aztán egy fregatt készült, hogy a kincset visszaszállítsa Spanyolországba. Dichoso önként jelentkezett kísérônek.";
			link.l1 = "Hadd találjam ki. Nem ô szállította az aranyat?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Helyes, senor! A fregatt nyomtalanul eltûnt a teljes rakománnyal és legénységgel együtt, Dichosóval együtt. A báró dühös volt. Vincento atya nagy megelégedésére ismét megalázták az Escorial elôtt. Most Don Mendosa megszállottan igyekezett visszaszerezni sértett büszkeségét, elveszett kincsét és Miguel Dichosót.";
			link.l1 = "Nem lehetséges, hogy a fregatt csak úgy viharba került és elsüllyedt? Vagy kalózok fogságába esett?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "A báró a pillanat hevében megesküdött, hogy biztos benne, hogy Dichoso elárulta ôt. Nem ismerem a részleteket. Néhány hét múlva Don Diego de Montoya új információval érkezett, miszerint Miguel Dichoso St. Pierre-ben lehet.";
			link.l1 = "Hm. Érdekes. Megint azok az indián kincsek. Úgy tûnik, minden gyanúsan kapcsolódik hozzájuk... Szóval, nem találtad meg Dichosót?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "Nem. És ôszintén szólva meg lennék lepve, ha valaha is itt lett volna. A báró annyira megszállottja Dichoso elfogásának, hogy még a legképtelenebb fantáziákat is elhinné.";
			link.l1 = "Mondja, "+npchar.name+", hogyan szerzett tudomást Don Mendosa errôl a... ööö... Tayasal városról? Nem álmodta, ugye? Volt valami tény vagy valami más?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "Vincento atya volt az, aki elôször hallott Tayasal állítólagos létezésérôl és az arany városáról. Fogalmam sincs, honnan tudott róla...";
			link.l1 = "Ez egy érdekes fejlemény. Vincento atya maga állt elô Tayasal létezésének elméletével, saját maga tájékoztatta Spanyolországot, és kezdett legyeket szórni a báró kenôcsébe...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "Mint katolikus társadnak tudnod kellene, hogyan dolgoznak ezek a tisztelendô atyák a Szent Törvényszékben... Nem ok nélkül tájékoztatta Madridot. Valamiféle hátsó szándéka van, de a báró érkezése nyilvánvalóan nem szerepelt a tervei között. Mindenesetre errôl többet nem tudok. Soha nem volt kedvem az inkvizícióval foglalkozni.";
			link.l1 = "Jól van, rendben. Sok érdekes információt adtál nekem, "+npchar.name+", és az eskümhöz hûen kiviszlek innen. Késôbb visszatérek érted, de most... hadd gondolkodjak egy kicsit azon, amit elmondtál...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "Senor? Betartja az ígéretét?";
			link.l1 = "Mindig betartom az ígéreteimet. Ma van a szerencsenapod, "+npchar.name+". Velem jössz Santiagóba Kubába. Majd ha megérkeztünk, többet mondok a tervemrôl. De most, üdvözöllek a fedélzeten. Elkísérnek a kikötôbe, és átadják a hajómon.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "Köszönöm, kapitány. Örülök, hogy ön szavahihetô úriember.";
			link.l1 = "Késôbb is kifejezheti háláját. A vendégem lesz, de ôrizet alatt. Ne értse félre, még mindig szükségem van magára.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "Értem, senor. Spanyol tisztként szavamat adom, hogy nem teszek semmilyen szökési kísérletet.";
			link.l1 = "Isten kíméli az óvatosokat. Találkozunk a fedélzeten.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "Kapitány, mik a céljai Kubában? Azért jött, hogy kitegyen? Nem is merem remélni...";
			link.l1 = "Pontosan így van, azért vagyok itt, hogy visszaszállítsam a honfitársainak. Nos, az ideérkezésem oka ennél egy kicsit bonyolultabb. De ez már nem tartozik önre. Most azonnal elengedlek váltságdíj nélkül, de azzal a feltétellel, hogy két dolgot megesküszöl nekem.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "Mik azok?";
			link.l1 = "Az elsô, hogy adok egy lepecsételt levelet. Ezt a levelet személyesen fogod átadni a santiagói inkvizítornak, Vincento atyának. Ha megkérdezi, kitôl kaptad a levelet, és hogyan jutottál hozzá, mondd meg neki az igazat...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "A második, hogy legalább egy hétig nem segítesz vagy asszisztálsz semmilyen kísérlethez, hogy megtaláljanak és megtámadják a hajómat. Megegyeztünk?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "Ez minden?";
			link.l1 = "Igen, ez minden. Teljesítse a feltételeimet, és szabadon távozhat.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "Esküszöm önnek, senor, hogy személyesen adom át a levelet Vincento atyának, és hogy nem teszek semmiféle olyan cselekedetet, amely a santiagói helyôrség agresszióját provokálná ön vagy a hajója ellen. Biztos lehet benne, hogy megtartom a szavamat. Spanyol vagyok, és tisztelem az erôs és nemes ellenfeleket.";
			link.l1 = "Rendben, Don "+GetFullName(npchar)+", elfogadom az esküjét, és most azonnal elengedem. Tessék, fogd ezt a levelet az inkvizítornak. Most már szabad vagy.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("Átadtad a levelet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Viszlát, senor. Remélem, soha többé nem találkozunk a csatatéren. Szörnyen bántana.";
			link.l1 = "Ég veled...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "Dios mio, micsoda szerencsés találkozás! Hello, monsieur "+GetFullName(pchar)+"! Látom, szívesen látott vendég lett Santiagóban. A Szent Inkvizíciónak dolgozik?";
			link.l1 = "Üdvözlöm, senor "+npchar.name+". Azt hittem, hogy soha többé nem látjuk egymást, legalábbis nem baráti körülmények között! Nem, csak meglátogattam Vincento atyát. És mi a helyzet magával? Most Santiagóban szolgál?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "Miután kiszabadítottál a letartóztatásból, kénytelen voltam Santiagóban maradni, nem biztonságos visszatérnem a Gondviselésre... de mint látod, megtartottam a szavamat. Nem üldöznek téged spanyol hajók...";
			link.l1 = "Örülök, hogy mindketten álljuk a szavunkat.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Figyeljen, kapitány, megemelné a poharát egy pohár rummal, a találkozásunkra, hogy úgy mondjam? Soha nem gondoltam volna, hogy valaha is megkínálok egy franciát, de ön, senor, kivételes eset.";
			link.l1 = "Hát persze! Nem bánnám, ha egy kis rummal öblíteném ki a számat. Menjünk a kocsmába.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Ah, salud!";
			link.l1 = "Mire iszunk, senor officer?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Igyunk valami semlegesre, de ez mindkettônket érint. Például a nemzetünk bátor és sikeres szolgálatára! Mindannyiunknak megvan a sajátja!";
			link.l1 = "És igyunk arra is, hogy uralkodóink megegyeznek egymással, és hogy a franciák és a spanyolok abbahagyják a harcot mind otthon, mind a Karib-tengeren.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Jól mondta, kapitány! A békére! Megmutatom, hogyan kell spanyolul inni! Arriba, abajo, al centro y pa' dentro!";
			link.l1 = "A békére... (ivás)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Aha! A kubai rum valóban a legjobb a Karib-tengeren...";
			link.l1 = "Egyetértek. Mondja, megpróbálták megbüntetni, amiért elfogták St. Pierre-ben?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "Szerencsére csak egy pofont kaptam. Azt a katasztrófát már magam mögött hagytam. Végül is szükségük van tisztekre itt a gyarmatokon.";
			link.l1 = "És a parancsnokotok... hogy is hívták... Diego, igaz? Hogy sikerült neki a sikertelen rajtaütés? Lefokozták?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "Ó, nem! A mi drága Diego de Montoyánk érinthetetlen, amíg Don Ramon de Mendosa y Riba áll mögötte. Egyébként Don Diego épp tegnap járt Santiagóban. San Joséból érkezett.";
			link.l1 = "Nem mondod? Érdekes! Még jó, hogy nem az utcán találkoztunk. Attól tartok, hogy az a viszony párbajjal végzôdött volna, haha!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Don Diegónak most nincs ideje magára, kapitány. Túl sok minden forog most kockán ahhoz, hogy párbajban kockáztassa az életét. Valami tervet eszelt ki Mendosa báróval együtt a nyugati fôutcán. Összeállított egy hajóraj Havannában, és bármelyik nap visszahajózhat Spanyolországba.";
			link.l1 = "Ön is a legénységében van?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "Nem. Holnap indulok San Juanba, Puerto Ricóba, hogy ott helyôrséget állítsak. Don Mendosa mellett már nem látnak szívesen a Providence-en.";
			link.l1 = "Nos, akkor igyunk az új beosztásodra, és semmi más ne várjon rád ott, csak boldog idôk és gyönyörû lányok.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Muchos gracias, monsieur. Minden jót kívánok önnek is. Azt hiszem, itt az ideje, hogy elmenjek. Megiszom ezt az italt, és aztán búcsúzom önöktôl.";
			link.l1 = "Vaya con Dios, senor "+npchar.name+". Talán még találkozunk békében.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "Ahogy mondtam, Don Diego: a hal bekapta a csalit; horog, zsinór, és süllyedô... Ó, úgy tûnik, újra találkozunk, monsieur. Sajnos, nem olyan békés keretek között, mint szerettük volna.";
			link.l1 = ""+npchar.name+"? Hát ez az! Erre nem számítottam. Valamiért azt hittem, hogy ön egy becsületes, nemes tiszt. Kiderült, hogy tévedtem.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "Miért téved? Én megtartottam a szavamat, nem esküdtem örök barátságra veled. Semmi sem változott, monsieur. Ön még mindig Spanyolország ellensége és az én személyes ellenségem. Ez itt nem Santiago, itt nincs Vincento atya, és az ô kis irata a biztonságos átkelésrôl nem segít magán...";
			link.l1 = "Ó, ez így van? Történetesen úgy gondolom, hogy egy baráti beszélgetés egy kis rum mellett, miközben csapdába akarnak csalni, eléggé alattomos, nem gondolja, senor "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "Árulónak merészelsz nevezni, te maricon?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "Hé, te! Igen, igen, te! "+GetFullName(pchar)+"?";
			link.l1 = "Igen, haver. Én vagyok az.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "Levelet kaptam egy fontos személytôl. Már tudod, hogy ki az.";
			link.l1 = "Tudom, add ide.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "Tessék. Mit szólnál néhány érméhez a fáradozásomért?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Vegyen egy kis ezüstöt. Becsületesen megdolgoztál érte.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "Át akarsz verni, haver? Már kifizették a szállításért.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Kösz, fiú. Öröm volt egy nagylelkû úriemberrel üzletelni.";
			link.l1 = "Rendben, tûnj el, és egy szót se szólj arról, hogy idejöttél.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "A havannai farkas a barátod...";
			link.l1 = "A Havanna Havanna a barátja... Még mindig itt vagy...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "Üdvözöljük a 'Admirable', kapitány "+GetFullName(pchar)+"fedélzetén!";
			link.l1 = TimeGreeting()+"! Meglepô. Ismer engem?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Ki ne hallott volna a francia gyarmatokon a "+GetFullName(pchar)+"nevû nagykapitányról, aki kiverte a fogát a St. Pierre-t támadó csatahajó által vezetett spanyol hajórajnak, és megölte az egész ellenséges portyázó csapatot! Maga egy nemzeti hôs!";
			link.l1 = "Ó, ugyan már. 'A hôs'... Én csak egy katona vagyok, aki teljesíti a kötelességét Franciaországgal szemben.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Ne hidd, hogy sok katona nem tudta volna megtenni azt, amit te, kapitány úr... Eh, szívesen meghívnám egy kis rummal a kocsmában, de sajnos: a kapitány megtiltotta, hogy a férfiak egy csepp rumot is igyanak, és én nem akarok rossz példát mutatni...";
			link.l1 = "Hm... Szóval maga nem kapitány?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "Úgy nézek ki, mint egy kapitány? Hoho! Nem, én csak a hajóskapitány vagyok. A nevem Serge Degas. A kapitányunk, Gaius Marchais, egész nap a kocsmában tölti a napot, mi meg közben kint feküdtünk és vártunk valami 'kereskedôk' karavánra. A kapitány tartozik a matrózoknak, és nekünk is, az egész legénység teljesen zsebben van. ";
			link.l1 = "Mi a baj? A spanyol vanília karaván nem jön, hogy kitépjék a tollait?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "Kizárt dolog! A kapitányunk véget vetett a kalózkodásnak, miután elfoglalta ezt a gályát. Tudod, hallotta, hogy egy Európába tartó kereskedelmi karaván hamarosan megáll Guadeloupe-nál, és vaníliát fognak vásárolni. Így hát Bridgetownban megtöltötte a rakterünket vaníliával a tetejéig! Azt hitte, hogy háromszáz pezóért el tudja majd adni ládánként, igen, semmi esélye!\nAz érkezésünkkor persze nincs vaníliakaraván, és a vanília eladása a helyieknek veszteséges lenne. Szóval itt vagyunk, és várjuk a 'kereskedôket', Biztos vagyok benne, hogy egy nap vagy három év múlva felbukkannak itt... A kapitány egész nap a kocsmában ül, és királyi bosszúságot okoz, és mindenkit zaklat. Csak azért tér vissza a hajóra, hogy elájuljon. Most végre hajlandó kétszáz pezóért eladni, csakhogy nullszaldós legyen\nMinden pénzünket abba a rakományba fektettük. Egy nap a legénység meg fogja kötözni, és olcsón eladja a vaníliát, csak hogy fedezze az adósságainkat... Esküszöm, már látom, hogy bármelyik nap bekövetkezhet.";
			link.l1 = "Aye... mi eszi a kapitányodat?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Nos, ha egy munkát érdemes elvégezni, akkor azt jól kell csinálni. Ô egyiket sem csinálja. Szörnyû alkudozó. Más lett volna a helyzet, ha árut is szállít, de ô igazi kereskedônek akarta érezni magát. Remélem, hogy egy éjszaka leesik a hajóról...";
			link.l1 = "Megértettem, Serge. Ne aggódj, biztos vagyok benne, hogy egy nap majd felbukkan a... karavánod.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Ó, én nem hiszek a csodákban, kapitány. Talán egy nap újra találkozunk és elkortyolunk egy kis rumot... mit nem adnék most egy kis rumért...";
			link.l1 = "Sok szerencsét, pajtás.";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Eh, kapitány, biztos szeretnék egy korty rumot!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Ho! Maga nem a kereskedelmi hajóról jött? Nem? Ó, elnézést kérek. Természetesen nem... Az én hibám.", "Nincs hozzá kedvem, uram, úgyhogy keressen valaki mást, akivel beszélgethet.", "Á, már megint maga?!", "Ahem...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ne aggódj emiatt, haver. Megesik.", "Igyon egy kis rumot, kapitány. Az majd enyhíti a gondjait egy kicsit...", "Ne legyen ideges, pajtás. Nem tesz jót az egészségének.", "Rendben, rendben. Elmegyek.", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "A argh... Mm... Mi a fene, mi ez?...";
			link.l1 = "Csönd legyen, haver... Ne csapj zajt...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "Huh? Mi az? Bassza meg!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "Aaah! Ki vagy te? Mit akarsz tôlem?";
			link.l1 = "Ha nem fogod be a szád, kivertem a fogaidat, érted? Hol vannak a szent edények, amiket elhoztál, amikor elfoglaltad ezt a hajót?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "Milyen edények? Nem tudom, mirôl beszélsz! Ez az én hajóm!";
			link.l1 = "A hajója? Nem is olyan régen még 'Santa Margaritának' hívták, és spanyol zászló alatt hajózott... Kérdezem, hol vannak azok a szent hajók? Egy arany ostensor, egy lazuritba ágyazott kereszt és egy arany füstölô? Mit csináltatok velük? Ugye nem adtad el ôket?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "Ó, Istenem, nem hiszek a fülemnek... maga spanyol? Ó, nem... maga nem spanyol! Maga francia! Ez még rosszabb! Eladtad magad azoknak az aljas kasztíliaiaknak! Mennyiért veszik meg manapság a franciák lelkét? Nem mondok semmit, áruló! Nem fogsz hozzájutni azokhoz a csecsebecsékhez!";
			link.l1 = "Egy szót sem szólsz, mi? Nekem megfelel. Ez amúgy sem a legjobb hely a kihallgatásra... Befogjuk a szádat, hogy ne árulkodj, aztán bemegyünk a csónakomba... végül beszélni fogsz, pajtás. Ebben nem kételkedem.";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "Te spanyol köpönyegforgató! Jobb, ha...";
			link.l1 = "Hallgass, gazember... Jöjjön utánam, vagy leütöm és a lábánál fogva végigvonszolom a fedélzeten.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "Miben segíthetek, uram?";
			link.l1 = "Hogy állnak a dolgok, kapitány? Mi szél hozta Basse-Terre-be? Ha jól tudom, ön spanyol, aki holland zászló alatt hajózik?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "Mi a probléma, uram? Igen, spanyol vagyok. Ezt könnyû kitalálni a hajóm nevébôl és típusából, de teljesen legálisan vagyok itt. Van egy engedélyem a Holland Nyugat-indiai Társaságtól, így...";
			link.l1 = "Ne kezdjen ki, senor! Nagyon, nagyon örülünk, hogy ön spanyol... Mondja, importálni vagy exportálni jött?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "Havannából hoztam árut, és a helyi piacon árulom. Most valami jövedelmezô szállítmányra várok, hogy ne üres rakodótérrel hajózzak haza.";
			link.l1 = "Senor, van egy üzleti ajánlatom az ön számára! Jó pénzt kereshet, ha segít nekem. Megbeszéljük? Egyébként mi a neve?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Carlos. Carlos Guevara kapitány. Mi az ajánlata?";
			link.l1 = "Vásárolnom kell egy adag vaníliát, és el kell küldenem Kubába, egy "+pchar.questTemp.Guardoftruth.LMname+"nevû embernek, a Santiago-i világítótorony ôrének. Van azonban egy komoly problémám. Elôször is, egyetlen boltban sincs annyi vanília, amennyire szükségem lenne...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "Másodszor, azonnal el kell indulnom Szent Kristófba, és nem tudom, meddig leszek távol. Napról napra veszítem a pénzem, érted? Ez egy istenverte szégyen!";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "Megértem. Que lastima, senor. Végül is nem kereshetsz annyi pénzt, amennyit csak akarsz. Akkor mit akar tôlem?";
			link.l1 = "Nézzen oda. Látod azt a gályát? Tele van vaníliával, amire nagy szükségem van. A baj csak az, hogy a gálya kapitánya kitalált valami ostobaságot arról, hogy hamarosan egy fûszerkaraván érkezik ide, amely nyereséggel veszi meg a rakományát, majdnem háromszáz pezóért ládánként!";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Igen, sok a naiv ember manapság, a bolond és a pénze hamar elválik egymástól...";
			link.l1 = "A naivitás az egy dolog, de ô egyszerûen csak ostoba! Kétszáztíz pezóért ajánlottam a vaníliáját, itt még kétszázért sem lehet megvenni a boltban. És el tudod hinni, azt mondta, hogy húzzak el! Azt mondta, hogy csak kétszázötvenért adja el!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Haha! Micsoda idióta!";
			link.l1 = "Ez az! Alapvetôen ezt mondtam neki. Persze dühös lett rám... de nekem tényleg szükségem van arra a vaníliára! Itt az ajánlatom, senor. Nem vagyok kereskedô, de úgy gondolom, hogy ön igazi mestere az üzlet mûvészetének. És van egy tágas rakodótér...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Beszélje rá ezt az átkozott bolondot, hogy adja el magának a rakományt. Most nem fogja eladni nekem, miután szemtôl szembe sértegettem. Kétszáztíz pezót fizetek egy ládáért. Ha lejjebb adod az árat, a különbözetet hagyd meg magadnak. És ezért kibérelem a hajóját, hogy elszállítsa a vaníliát Santiagóba.";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "Mennyit hajlandó fizetni nekem a szállítmányért?";
			link.l1 = "Mennyit akar?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "Santiago elég messze van... harmincezer pezó.";
			link.l1 = "Ez túl sok, amigo. Találkozzunk félúton.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "Rendben, úgyis úton van... Huszonötezer és egy pesóval sem kevesebb.";
			link.l1 = "Rendben van. A gálya kapitányát Gaius Marchais-nak hívják. Egész nap a kocsmában duzzog. Remélem, sikerül meggyôznöd, hogy váljon meg a fûszereitôl.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "Volt már dolgom nagyobb idiótákkal is. Elmondok neki minden részletet arról, hogy ki terjeszti a pletykákat a karavánról, aki állítólag égbe szökô áron akarta megvenni az árut. Amint meggyôztem arról, hogy az egész csak a képzelete szüleménye, el fogja adni, ebben biztos vagyok.";
			link.l1 = "Szóval, megegyeztünk?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Weve van egy ajánlatunk, ha van készpénze, hogy kifizesse a vaníliát és a szállítást. Ahogy a bájos ír mondás tartja: 'Mutasd a pénzt'.";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Tessék, nézze meg. Minden itt van.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Az ezüst a hajómon van. Megyek érte, és mindjárt jövök!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Elhoztad a pénzt?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Tessék, nézze meg. Minden itt van.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Azonnal hozom!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "holnap";
				iTemp = 1;
			}
			else
			{
				sTemp = "ma";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Estupendo! Élvezem, hogy értelmes partnerekkel üzletelhetek. Jöjjön vissza "+sTemp+" reggel tízre. Azt hiszem, addigra közös barátunk, Gaius már észhez tér.";
				link.l1 = "Remek! Viszlát késôbb!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Estupendo! Szeretek értelmes partnerekkel üzletelni. Elmegyek a partra. Három óra múlva gyere vissza. Azt hiszem, addigra közös barátunk, Gaius, észhez tér...";
				link.l1 = "Remek! Viszlát késôbb!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Senor, jól emlékszem a szerepemre. Ne aggódj, lehet, hogy kemény dió, de én meg fogom törni.";
			link.l1 = "Köszönöm.";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "Megtörtént, senor. Szegény ember nagyon örült, hogy meg akartam venni a vaníliáját. Remegett a keze a boldogságtól, miközben elôleget számoltam - vagy talán csak a rumtól. A rakományt holnap délben rakodjuk fel a Capster Beachen, hogy elkerüljük a kikötôi vámosok nemkívánatos figyelmét\nAmint a rakományt a fedélzetre vettem, azonnal Santiagóba hajózom. A világítótoronynál felveszem a kapcsolatot a partnerével, és az ottani átadás után átírom neki a vaníliát. Szeretné, ha átadnék neki valamilyen üzenetet?";
			link.l1 = "Igen. Itt egy levél. Azt mondja, hogy az üzlet holnap délben lesz a Capster Beachen? Rendben, akkor horgonyra vetem magam a fejfánál, a szigetrôl megközelíthetetlenül, hátha történik valami.";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("Átadtad a levelet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bízhat bennem, senor. Becsületes ember vagyok. Különben is, nem akarok összeveszni önnel, és egy kereskedô semmit sem ér a hírneve nélkül. De ha szeretne figyelni és ellenôrizni, az nem jelent számomra nehézséget.";
			link.l1 = "Hálás vagyok, senor. Holnap figyelni fogom az üzletet, és amint ön elhajózik, megyek a dolgomra Szent Kristófba.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Kapitány, biztosíthatom: Nem hagyom cserben, és teljes mértékben teljesíteni fogom az egyezségünk feltételeit.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("Hiic! H-hurrá! A jó öreg' kapitány végre megadta a fizetségünket! Háromszoros hurrá a kapitánynak! Hic!","Pintben jön?! Hozok egyet!","Legyen kövér a pénztárcánk és kövérebbek a nôink! Hurrá!","És ott feküdtek, mind jó halottak, hic! Mint napszaktörés a piás kánban. Yo ho ho ho és egy üveg rum!","Yo ho ho ho és egy üveg rum!");
			link.l1 = LinkRandPhrase("Igen, haver.","Nem gondolod, hogy már elég rumot ittál?","Igyál és az ördög a többiért...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Állj! Ki megy oda? Riadó! Visszaszorítani a betolakodókat!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Har har! Te is Rollie, a kapitány kincséért jöttél, mi? Kerestük és kerestük és kerestük, de nem találtuk. Bárcsak legalább egy ilyen idióta kitalálná, hogy a vízesés mögé ússzon a párkányra!";
			link.l1 = "Maga Fox ezredes egyik embere, ugye?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "Lehet, hogy kapcsolatban állok a Tengeri Rókákkal. Nem kell tudnia, nincs értelme. Nem kell tudnod semmit sem most. Megtaláltad a kincsemet, amiért nagy köszönettel tartozunk neked...";
			link.l1 = "Értem. Nem vagy tengeri róka, inkább tengeri kutya... vagy sakál. Melyik illik hozzád jobban?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "Úgy látszik, egy természetes filozófussal van dolgunk, fiúk. Egy igazi szakértôje az állatvilágnak!";
			link.l1 = "Megvizsgálod a szablyám élességét, sakál?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", ...senor. Miben segíthetek?";
			link.l1 = "Hahó! Ön Donna Belinda de Ribero?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Igen, én vagyok. Kivel van szerencsém beszélni?";
			link.l1 = "Kapitány "+GetFullName(pchar)+", asszonyom. Kérem, ne vegye zokon a francia vezetéknevemet, jelenleg egy megbízást teljesítek Santiago nagytiszteletû inkvizítorától, Vincento atyától.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "Que interesante! Hallottam, hogy a Szent Törvényszék és a Jézus Társasága tele van rengeteg emberrel, minden osztályból és nemzetiségbôl, de személyesen még soha nem találkoztam olyan külföldivel, aki nekik dolgozik. Mit tehetek önért, senor?";
			link.l1 = "Ön rendelkezik egy olyan tárggyal, amely a tisztelendô atyát nagyon érdekli. Egy arany ostensor, egy monstrancia, amelyet nemrégiben szerzett meg a willemstadi bankártól.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "Ön nagyon tájékozott, senor. Nos, tudva, hogy kinek dolgozik, ez nem lep meg. Igen, én vettem a keszkenôt, bizonyára nem kellett volna otthagyni egy kereskedô boltjában a lopott csecsebecsék és zálogtárgyak mellett, mint valami jelentéktelen apróságot.";
			link.l1 = "Megvan a monstrancia, asszonyom?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Igen. A plébániatemplomnak akartam ajándékozni, de annyi minden történt itt velem... Nem tudtam... Ó, sajnálom...";
			link.l1 = "Sír, asszonyom? Szomorúságot okoztak önnek a szavaim? Ha igen, kérem, bocsásson meg nekem.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Ó, kérem, senor... Térjünk vissza a beszélgetésünkhöz. Ha jól értem, Vincento atyának szüksége van erre az érzékelôre? Szeretnéd, ha odaadnám neked?";
			link.l1 = "Ezt az értékes edényt a santiagói katedrálisnak szánták, de egy közönséges kalóz elrabolta, és eladta egy uzsorásnak több más szent tárggyal együtt. Az én feladatom, hogy visszaadjam azt, amit elloptak, és visszaadjam, ahová tartozik. Természetesen teljes mértékben megtérítem a költségeit.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Ó, nem szabad! Tényleg azt hiszi, hogy ez a pénz ennyit jelent nekem? Ezt a kegyképet a Szent Szûz Anyaszentegyház számára vettem, és nem fogok habozni, hogy átadjam a valódi tulajdonosának, nem is beszélve a Jézus Társaságának egyik tagjáról, aki Vincento atyát szolgálja. De egy másik dolog is mélyen nyugtalanít. Megtennéd, hogy segítesz az Egyház hûséges leányának a szükségben?";
			link.l1 = "Ön egy nemes asszony, asszonyom. Milyen gondok gyötrik önt? Hogyan segíthetnék?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "Ó, de senor... Nem mernék egy jezsuita testvértôl segítséget kérni. Ön mindig olyan elfoglalt...";
			link.l1 = "Már megtette. Mi a baj?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Megígéri nekem, mint a Szent Egyház képviselôjének, hogy soha senki nem fogja megtudni, hogy mit kérek öntôl?";
			link.l1 = "Esküszöm, senora. Ez nem a gyóntatószék pecsétje, de errôl egy szót sem szólok egy léleknek sem.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Nagyon jó. Bízom benned. Nagyon kedves barátom, Esteban Sosa bajba került. Utazás közben banditák fogták el, és százezer pezó váltságdíjat követelnek érte. Nincs ennyi pénzem, és csak az összeg felét sikerült összegyûjtenem a zsebpénzembôl. Nem kérhetek senkitôl segítséget ilyen ügyben, mert megesküdtek, hogy megölik, ha megteszem\nMellett aggódom a kedves... barátomért, és a legrosszabbtól tartok. Lehet, hogy megöletik, amint megkapják a pénzt, hogy biztosak legyenek benne, hogy nem fog beszélni róluk az ôröknek. Talán te, egy bátor kapitány, egy keresztény és a Társaság testvére, meg tudnád gyôzni a banditákat, hogy fogadják el a nálam lévô pénzt, és ne bántsák ôt...";
			link.l1 = "Mikor és hol lesz a csere?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "A fôkolomposuk egy Bartie, a bunkó nevû ember. Azt mondta, hogy minden este tizenegy órától éjfélig várja Esteban váltságdíját a barlang bejáratánál a dzsungelben...";
			link.l1 = "Ezek szokatlanul különleges feltételek...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "Nyilván azt akarták, hogy gyorsan rakjam össze az egész váltságdíjat, és nem akarták, hogy bárkitôl is segítséget kérjek... de én nem találok ilyen pénzt, soha nem is fogok tudni!";
			link.l1 = "Ne sírjon, asszonyom! Megpróbálok segíteni. Jézus Társaságának testvére soha nem hagyna magára egy igaz keresztény nôt, aki veszélyben van.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "Bíznom kell benned... De kapitány úr, Bartie, a bicskás azt is mondta, hogy ha a váltságdíjhordozó nem jön egyedül, vagy ha én megyek az ôrséghez, azonnal megöli szegény Estabant!";
			link.l1 = "Ezt észben fogom tartani.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Tessék, fogd ezt. Ez az az ötvenezer pezó, amit össze tudtam kaparni. Beszéld rá azokat a banditákat, hogy legalább ezt vegyék el. Mondd meg nekik, hogy nincs több pezóm! Hozd vissza Estebant! Ha megteszed, szívesen odaadom neked Vincento atyának az ostensory-t.";
			link.l1 = "Mindent megteszek, amit tudok, asszonyom. Reméljük a legjobbakat.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "Isten segítsen, bátor kapitány! Imádkozni fogok önért!";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "Van valami híre, kapitány úr?";
			link.l1 = "Még nem. Csak várjon, senora. Nem hagyom cserben.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "Van valami híre, kapitány úr?";
			link.l1 = "Igen, senora. Attól tartok, ez nem jó hír.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Mondja el, ne várakoztasson! Találkoztál a banditákkal?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Tessék, vedd vissza az ötvenezer dollárodat. Nem volt rá szükségem. Vidd ezt a gyûrût is. Azt hiszem, ismerôsnek fogod találni.";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Tessék, fogd ezt a gyûrût. Azt hiszem, ismerôsnek fogja találni.";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Ez... igen, ismerôs. Mi történt Estebannal?";
			link.l1 = "A barlangnál találtam a rablókat, ahogy mondtad. 'Bartie, a bunkó' és Esteban Sosa ugyanaz az ember. Azért rendezte meg az emberrablást, hogy megzsarolja magát. Ô mesélt nekem a... kapcsolatukról. Azt is mondta, hogy nem akar többé látni téged. Elvettem a gyûrût, amit tôled kapott bizonyítékként.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "Ez... igen, igen, tudom. Mi történt Estebannal?";
			link.l1 = "A barlangnál találtam a rablókat, ahogy mondtad. Megtámadtak, megkötöztek, és elvették a pénzedet. 'Bartie, a bunkó' és Esteban Sosa ugyanaz az ember. Ô rendezte meg az emberrablást, hogy megzsarolja magát. Mesélt nekem a... kapcsolatukról. Esteban elengedett, és ezt a gyûrût adta bizonyítékként. Azt mondta, hogy soha többé nem fogod látni ôt.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "Megtanítottam neki a leckét, de nem az ön iránti tiszteletbôl öltem meg.";
			dialog.text = "Dios mio! Nem hiszek a fülemnek! Miért történik mindez velem, miért?! Mit tettem érte, hogy....";
			link.l1 = "Senora, könyörgöm, ne ostorozza magát emiatt. Az a hitvány fickó egy könnycseppet sem ér. "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "És különben is, itt van egy ajándék, hogy bátorságodat megtartsd.";
			dialog.text = "Ó... Megpróbálok megnyugodni. Senor, meg kell köszönnöm a segítségét. Tessék, vegye el a szenzorát. "+sTemp+" Vaya con Dios.";
			link.l1 = "Gracias, senora. Ne aggódjon, senki sem fogja megtudni, mi történt a barlangban. Mi jezsuiták mindig megtartjuk a szavunkat. Most pedig, ha megkérhetem, mennem kell.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("Kaptál egy arany ostensort");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("Kaptál egy amulettet.");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "Állj meg, haver!";
			link.l1 = "Itt állok.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "Elhoztad a pénzt?";
			link.l1 = "Micsoda ostoba kérdés. Nem, én itt vagyok kint és Rózsaszín Mangós-t szedem... Mit gondol, mi másért jöttem volna ide?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "Oh ho ho! Egy komikus! Menj be a barlangba, Bartie már vár rád.";
			link.l1 = "Nyilvánvalóan tapasztalt ôr vagy... ezzel a hozzáállással alkalmas lennél arra, hogy magát Fülöp királyt ôrizd. Majd én bemegyek.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "Megvárattál... Nálad van a pénz?";
			link.l1 = "Te vagy Bartie, a bunkó? Nem úgy nézel ki, mint egy közönséges bandita.";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Miért érdekel, hogy nézek ki? Van nálad az a rohadt pénz, vagy nincs?";
			link.l1 = "Hol a túsz?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "Megkapod a túszodat. Gyerünk, add ide a pénzt. Ne dühíts fel, fiú.";
			link.l1 = "Bartie, bolondnak nézek ki? Amíg nem látom Esteban Sosa-t élve és virulva, addig egy pezót sem fogsz látni. Hol van?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "Ó, te most belevágsz' a sarkadba, mi? Jól van, most jól megleckéztetünk... Srácok, tépjük szét ezt a szarházit!";
			link.l1 = "Szemétláda!";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "Ennyi elég volt neked a táncból? Hol van Esteban Sosa? Gyerünk, mondd meg, vagy addig tartom a fejed a víz alatt, amíg a buborékok meg nem szûnnek!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "Ne... Ne bánts, kérlek! Esteban Sosa vagyok.";
			link.l1 = "Micsoda?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Igen, igen, igen. Nem vagyok Bartie, a bunkó. Én csak...";
			link.l1 = "Te gazember! Szóval úgy döntöttél, hogy kiszívsz százezer pezót Senora de Riberóból 'gyerekrablás' magaddal?!";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "Meg kell értenie engem, mint férfi a férfival. Belinda... Tényleg kikészített a megszállott szerelmével. Éjjel-nappal rám száll, ember! Még a férje is gyanakodni kezdett ránk, pedig félig vak!";
			link.l1 = "Na, mit szólsz ehhez! Szóval szeretôk vagytok?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Már nem. Csak elmenekültem elôle.";
			link.l1 = "És úgy döntöttél, hogy veszel néhány érmét az útra, mi? És most mit csináljak veled? Rejtsem el a holttestedet a dzsungelben, ahogy velem is megpróbáltad?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "Nem! Nem akartam vért, esküszöm!";
			link.l1 = "Ezért küldted rám a kutyáidat?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "Csak a zsebeidet akartuk kiforgatni, ennyi!";
			link.l1 = "És meztelenül hagytok a selva-ban? Fel kéne kötnöm és felakasztanom a hajóm legmagasabb árbocára, te gazember! De ezt nem teszem, pusztán a jó asszony iránti tiszteletbôl, akinek az a szerencsétlenség jutott, hogy összejött veled. Tudod mit? Elviszlek hozzá, és hagyom, hogy ô döntse el, mi legyen veled.";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "Nem, bármit, csak azt ne! Nem megyek vissza Cumanába!";
			link.l1 = "Inkább maradnál örökre ebben a barlangban?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Kíméljen meg, senor! Engedjen el, és elhajózom innen, és soha többé nem jövök vissza Cumanába! Nem fogom megvárni, hogy Belinda férje párbajban darabokra szeleteljen, vagy bérgyilkost küldjön értem!";
			link.l1 = "Jól van. Senora de Ribero kedvéért nem viszlek el hozzá. De egy pillanatig se higgye, hogy ezt az egészet a szônyeg alá söpörjük. Rá fog jönni arra a szánalmas szarházira, akivel úgy döntött, hogy flörtöl. Milyen jelek vannak nálad, amiket felismerhet?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Tessék. Ez a türkiz gyûrû itt. Ô maga adta nekem.";
			link.l1 = "Tökéletes. Add ide, és tûnj a szemem elôl!";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "Tökéletes. És tudod, Sosa, meggondoltam magam - most már Jézus Társaságát szolgálom. Ahogy a Szentírás mondja, 'meg kell tisztítanotok a gonosz embert magatok közül.' És te egy gonosz önimádó, egy bûnözô és egy haszontalan szarházi vagy. Azt hiszem, belefojtalak ebbe a barlangba. Requiesce ütemben.";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("Kaptál egy türkiz gyûrût.");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("Kaptál egy türkiz gyûrût.");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "Megvan, amire szükségünk van, haver...";
			link.l1 = "Tényleg? - Igen. És mi lenne az?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "Nem kérdeztem, gazdag fiú. Csak azt a parancsot kaptam, hogy vegyem el a holmidat, mindent, ami nálad van. A könnyebb vagy a nehezebb utat választjuk? A választás a tiéd.";
			link.l1 = "Harcosnak képzeled magad, mi? Fogalmad sincs, kivel van dolgod. Az ilyen söpredéket, mint te, megeszem reggelire.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "Igazi bolond vagy, nem igaz, béka? Nos, akkor lássuk, hogy néz ki a véred a földön!";
			link.l1 = "Ugyanúgy fog kinézni, mint a tiéd, idióta. Hadd adjak neked egy anatómia leckét!";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Haw haw, rendben, haver... Fordítsd ki a zsebeidet, de gyorsan! Ha jó kisfiú vagy és figyelsz, egy darabban maradsz, érted?";
			link.l1 = "Az istenit, már megint ti? Te is eljöttél idáig? Ki az ördög bérelt fel titeket?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "Semmi közöd hozzá. Most pedig adjátok meg magatokat és éljetek, vagy harcoljatok, és akkor a holttestetekrôl szedjük le a zsákmányt. Mit szóltok az alkuhoz?";
			link.l1 = "Van egy ellenajánlatom. Mi lenne, ha elvenném a zsákmányodat a holttestedrôl?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "Várom a parancsot, kapitány!";
			link.l1 = "Menjetek át a dzsungelen a San Antonio-fok felé. Az ösvényen balra, és menjetek egyenesen. Húzzátok le a fejeteket, és készüljetek fel a parton lesbôl támadásra. Legyetek készenlétben. Én a tengeren megyek oda, és ott találkozunk. Mennyi idô alatt érsz oda?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "Hat óra múlva ott leszünk, kapitány!";
			link.l1 = "Rendben. Mozgás!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "Szívós fattyú! Még életben van... Tudtam, hogy több puskaport kellett volna használnunk! Jól van, rendben, akkor én végzek veled, te rohadék...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
