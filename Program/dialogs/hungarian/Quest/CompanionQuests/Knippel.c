void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
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
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "Ó, micsoda hôség van ma. Akár egy láncos lövést is köthetnél a lábad köré, és beugorhatnál a tengerbe, csak hogy megszabadulj ettôl a fülledtségtôl!";
			link.l1 = "Ha-ha, Charlie! Ezek aztán a szélsôséges intézkedések, ha engem kérdezel. De nem bánnám, ha megnedvesíteném a fütykömet - ma tényleg túl meleg van. Benne vagy?";
			link.l1.go = "DTSG_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "Egy-két italra, kapitány? Mindig!";
			link.l1 = "Ezt szeretem hallani. Gyerünk, menjünk!";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_1");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "Hé, matróz, úgy nézel ki, mint aki már mindent látott! Igyunk egyet és meséljünk? Én fizetek!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "Nem, köszönöm, haver. A kapitányommal jöttem ide. Keressen valaki mást.";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "Ha, egy ilyen rongybaba, mint te, ilyen nagyra tartja magát, és csak a kapitányokkal iszik?";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "Magasröptû?! Évtizedekig szolgáltam a Királyi Haditengerészetnél! És nem az urakért harcoltam, hanem az olyan egyszerû emberekért, mint te és én, hogy biztosítsam a törvényt és a rendet mindenhol!...";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "Nagyot beszélsz, de csak kapitányokkal és nemesekkel iszol! Úgy látszik, a haditengerészet megtanított téged, hogyan kell az ágyúkat rendesen fényezni, ha!";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "Lenyomom a torkodon a láncos lövést, te kölyök!";
			link.l1 = "Charlie, ne borulj ki így, nem éri meg.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "Hadd intézzem én, kapitány. A haditengerészet becsülete forog kockán, nekem kell megvédenem, és nem bújhatok senki mögé...";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_1");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "Köszönöm, hogy megvárt, kapitány. Remélem, nem tartott túl sokáig.";
			link.l1 = "Ne aggódjon emiatt. Nem sérült meg? Az a gazember elég jó volt.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "Ne fáradjon, kapitány. A lényeg, hogy azt kapta, amit megérdemelt. Valamiféle kulcsot találtam a testében...";
			link.l1 = "...";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "Felszedtem valamilyen kulcsot a testébôl... Vajon mire lehet?";
			link.l1 = "Elemi, Charlie... Egy ajtóért vagy egy ládáért, ha-ha. Beszélnünk kéne a fogadósnak errôl a gazemberrôl, még hasznos lehet.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie adta neked a kulcsot.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "Hihetetlen...";
			link.l1 = "Te is arra gondolsz, amire én, Charlie?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "Nem tudom, ön hogy van vele, uram, de engem meglep, hogy mennyi pénz van itt - nézett ki a férfi egy egyszerû embernek, nem pedig kereskedônek vagy nemesnek.";
			link.l1 = "Igazából nem olyan sok, de igaza van. Ami engem meglep, az ez a furcsa, elégetett levél.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "Igen, ez nem volt túl okos dolog tôle - olyan, mintha láncos lövést lône egy erôs hajótestre. Teljesen meg kellett volna semmisítenie a levelet.";
			link.l1 = "Igen, azt. De ez nem segít rajtunk - nem tudjuk, hogy ki volt, vagy kivel levelezett. Menjünk, Charlie, itt már nincs semmi keresnivalónk.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2_1");
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "Ennyit a dicsôített királyi haditengerészetrôl, pfft!";
			link.l1 = "Charlie jó és tisztességes ember volt. És ágyús volt, nem tengerészgyalogos.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "Egy ágyús?! Szóval, pontosan úgy van, ahogy mondtam, ha-ha-ha-ha! És ne bámulj - tudnod kellett volna, hogy kit veszel fel a legénységedbe.";
			link.l1 = "Tudnod kellett volna, hogy kivel szórakozol.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "Csak azért vagy még életben, mert tisztességesen nyertél, úgyhogy fogd be a rohadt nyelved, és húzz innen!";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "Azt hittem, hogy legközelebb veled kell megküzdenem. Jó hallani, hogy a becsület jelent neked valamit.";
			link.l1 = "Charlie-nak sem csak üres szavak voltak. De ami magát illeti, kétségeim vannak. Mindegy, most már nem számít.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_2");
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "És kivel kezdtem ki, egy elkényeztetett gyengével?! Láttad egyáltalán a saját vékony bajuszodat?...";
			link.l1 = "Te aztán tudod, hogy kell megnyomni a gombokat... Még nagyobb öröm lesz rajtad levezetni a dühömet.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_3");
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "Várjon, kapitány. Látom, hogy méltó és nemes ember vagy, tudnál nekem segíteni valamiben? Ez becsületbeli ügy.";
			link.l1 = "Talán igen, de mi a baj? És miért jöttél hozzám? Sok nemes ember van errefelé. Egyébként kivel van szerencsém beszélni?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "Peter. Peter Adams. Látom, hogy nem egy régi család tipikus elkényeztetett leszármazottja vagy, hanem egy megbízható, biztos kezû ember.";
			link.l1 = "Ó, látnia kellett volna, amikor elôször érkeztem a Karib-tengerre, uram. De folytassa, miben van szüksége segítségre?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "Tudna... párbajozni a nevemben, uram? Egy helyi bajkeverô, Ralph Faggle, megsértette a feleségemet. És nyilvánosan zaklatta ôt. A szemem láttára. El tudja ezt képzelni?";
			link.l1 = "Nem túl nagy becsület, ha valaki kihívja a párbajt, és aztán valaki más mögé bújik. Fôleg, ha nem csak a személyes becsületed forog kockán, hanem egy nôé, méghozzá a feleségedé. Nem gondolja, Adams? Miért nem tudsz te magad harcolni a nôdért?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "És igazad van, teljesen igazad van. De nemrég súlyos lázban szenvedtem, és alig tudok lábra állni\nAz igaz, nem könnyû ilyesmit kérnem. Ha sértegetett volna, akkor is elviseltem volna. De nem akkor, amikor a feleségem becsülete forog kockán! Nem vagyok gyáva, uram. Egykor a királyi haditengerészetnél szolgáltam, és egy hajón hajóztam magával Robert Blake-kel!";
			link.l1 = "Én...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "Segíteni fogunk.";
			link.l1 = "Charlie?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "Méltó ember, kapitány. És átkozott legyek az örökkévalóságig ágyúgolyókkal, ha ez nem igaz! Nagyszerû emberek szolgáltak Blake admirális mellett. Együtt harcoltak azért, hogy senki ne nyomja el a köznépet\nés neki köszönhetôen Jamaika felszabadult a spanyolok zsarnoksága alól!";
			link.l1 = "Még ha ez így is van, nem engedem, hogy a legénységem tagjai megzavarjanak, vagy döntéseket hozzanak helyettem. Világos?";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "Értem, tényleg. Viszont még esélyem sem volt arra, hogy válaszoljak. Próbáljon meg nem elhamarkodottan közbeszólni a jövôben, rendben?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "Megmondom önnek, kapitány - ha nem segít ezen az emberen, az öreg Charlie mindent eldob, és maga fog párbajozni érte, lehet, hogy helyben átkozott leszek!";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Csönd legyen, nem mondtam, hogy nem vagyok hajlandó segíteni. Igaz, Mr. Adams?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "Ôszintén, Charlie, gyávának állítasz be. Pedig sosem voltam az. Ezt tudnod kell.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "Sajnálom, kapitány, elragadtattam magam.";
			link.l1 = "Semmi baj. De tartsd magad kordában, rendben?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "Párbajozom önért, Mr. Adams.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "Köszönöm, uram! Isten áldja meg!";
			link.l1 = "És áldja meg a Lord Protector-t is, igaz, Mr. Adams? Ne aggódjon, Charles de Maure sosem hagyja bajban a becsületes embereket.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "Nagyra értékeljük, Mr. de Maure, uram! Szeretne átjönni és együtt vacsorázni velem és Jane-nel?";
			link.l1 = "Nos, én...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "Ragaszkodom hozzá!";
			link.l1 = "Nos, csak ha ragaszkodik hozzá. Köszönöm, Peter. Menjünk elôre.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "Természetesen igaz, uram! Szeretne átjönni Jane-nel, hogy kipihenje az útját?";
			link.l1 = "Köszönöm, de helyes lenne kihasználni a vendégszeretetét?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "Ó, épp ellenkezôleg, kapitány, megsértôdnénk, ha nem jönne át.";
			link.l1 = "Hogy utasíthatnám vissza? Csak utánad, Peter!";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_3");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "Mi vagyunk azok! Kérem, jöjjenek be.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Köszönöm, uram. Beszélhetnék Jane-nel? Kérdezd meg tôle, hogyan történt - minden részletre szükségem van.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "Mélységesen sajnálom, de gondolkodás után vissza kell utasítanom. Fel kell készülnöm egy párbajra. Egyébként, hol és mikorra van kitûzve?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "Természetesen, uram. Mindketten szívesen beszélgetünk önnel és válaszolunk minden kérdésére. Kérem, kövessen.";
			link.l1 = "Köszönöm, Peter.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "Milyen kár! De igaza van, természetesen alaposan fel kell készülnie. Két óra. A városkapun kívül.";
			link.l1 = "Értettem, köszönöm. Szívesen átjövök, ha vége. Viszlát akkor!";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_4");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "Üdvözöllek! Kedvesem, nem mondtad, hogy vendégeket hozol - rendesen felkészültem volna.";
			link.l1 = "Köszönöm, asszonyom, nem maradunk sokáig. Charles de Maure, szolgálatára. Beleegyeztem, hogy meghallgatom a történetét a férjével. Mondja el, hogyan történt.";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "Ó, szörnyû volt! Ralph teljesen részeg volt. Elkezdett zaklatni a szomszédok elôtt, még Peter elôtt is, obszcén dolgokat mondott...";
			link.l1 = "Pontosan mit mondott önnek?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "Túlságosan zavarban vagyok ahhoz, hogy beszéljek róla. Aztán kijózanodott, és...";
			link.l1 = "Bocsánatot kért, és megkérte, hogy mondjuk le a párbajt?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "Egyszer sem.";
			link.l1 = "Sajnálom magát. Még egy dolgot szeretnék tudni, ha megengedi, asszonyom.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "És mi lenne az, uram?";
			link.l1 = "Milyen életkörülmények és megpróbáltatások kényszerítették önt és a férjét, hogy itt éljenek? Bármelyik angol városban, a férje érdemeit tekintve, már rég a helyére tette volna Ralphot.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "Elnézését kérem, uram, de hogy merészeli?! Ha nem lenne a kapitányom, megragadnék egy láncos lövést, és jól elpáholnám!\nNem elég, hogy nem bízik egy olyan méltó emberben, mint Mr. Adams, de még egy bajba jutott hölgyet is kigúnyol...";
			link.l1 = "Hallotta, hogy kigúnyoltam egy hölgyet? Nem? Akkor ne rágalmazzon engem. A mi embereink segíthettek volna nekik, ezért kértem.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "Nyugodj meg, Charlie! Hogy tehetted... Én csak többet akartam megtudni Jane és Peter nehézségeirôl, és együtt érezni velük. Az angol gyarmatokon már biztosan segítettek volna rajtuk.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "Az élet sokféleképpen alakulhat... A hajótörés. Vagy valakinek a rágalma, ami néha még az ilyen becsületes embereket is arra kényszerítheti, hogy szégyenszemre elbújjanak\nHa ennyire bizalmatlan és gyanakvó vagy - beszélhetsz a szomszédokkal. Biztos vagyok benne, hogy minden szavukat megerôsítik. De az öreg Charlie nem süllyedne le odáig, hogy a hátuk mögött megbeszélje az emberek bánatát!";
			link.l1 = "Nem hallottad, amit mondtam? Azt mondtam, hogy segítek ezeknek az embereknek.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "Az élet sokféleképpen alakulhat... A hajótörés. Vagy valakinek a rágalma, ami néha még az ilyen becsületes embereket is arra kényszerítheti, hogy szégyenszemre elbújjanak\nHa ennyire bizalmatlan és gyanakvó vagy - beszélhetsz a szomszédokkal. Biztos vagyok benne, hogy minden szavukat megerôsítik. De az öreg Charlie nem süllyedne le odáig, hogy a hátuk mögött megbeszélje az emberek bánatát!";
			link.l1 = "Nem hallottad, amit mondtam? Azt mondtam, hogy segítek ezeknek az embereknek.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "Szívbôl köszönjük. Imáinkban emlékezni fogunk rátok.";
			link.l1 = "Ez így jó. Egyébként, ami a mi ügyünket illeti. Hol és mikor rendezte meg a párbajt, Mr. Adams?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "A városkapun kívül, uram. Két óra múlva.";
			link.l1 = "Megcsinálom. Várjon jó hírekkel. És eszébe ne jusson elôre gyertyát gyújtani a nyugalmamért!";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "Valami bántja, kapitány? Nagyon elgondolkodtatónak tûnik.";
			link.l1 = "Tudod, igen. Valami nem stimmel Adams' történetében, és...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "Meddig fog ez így menni, uram?! Mindig így reagál, ha valakinek segítségre van szüksége?";
			link.l1 = "Az Isten szerelmére, beszéljen halkan. Az egész utcára kiabálnád. Azt mondtam, hogy elmegyek a párbajra. Ez nem elég neked? Most jól figyelj rám.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "Rendben, kapitány. Elnézést a kirohanásomért - érdekel azoknak a sorsa, akik a Királyi Haditengerészetnél szolgáltak. Sokan közülünk tisztességes emberek voltak, akik jobb sorsot érdemeltek volna, mint amit a legtöbben kaptak.";
			link.l1 = "Megértem magát, Charlie. Ne feledje, mit kell tennie. Azt akarom, hogy a legénység egy részét küldje a város kapujához. Ahogy közeledik a párbaj ideje, csendben gyülekezzenek, és álljanak készen a jelemre.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "Egy tisztességes párbajból gyilkosságot akarsz csinálni?";
			link.l1 = "Gyanítom, hogy nem lesz teljesen ôszinte. Csak akkor adok jelet, ha szükséges. Ha tényleg minden rendben van, örülök, ha tévedek. Most már érted? Emlékszel, mi történt egy hónapja?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "Megértettem, uram. Ôszintén szólva, nem vagyok túl boldog, de megteszem, amit kell. Ne aggódjon.";
			link.l1 = "Ezt akartam hallani.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_5");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "Szóval, de Maure. Korán jöttél. És még mindig a városban vagyunk. Bár ez nem számít. Kár, hogy nem hoztad magaddal azt a vén bolondot. De ne aggódj, elôbb-utóbb elkapjuk.";
			link.l1 = "Bármikor állok rendelkezésedre. Zsoldosok vagytok? Kinek tettem keresztbe?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "Ez az, senkit. Azt a vén szivar Charlie-t keressük, és rajtad keresztül könnyebben megtaláljuk, mivel megtudtuk, hogy most a te hajódon van. Ez nem a dzsungel, úgyhogy gyorsan kell cselekednünk, hogy ne vonzzuk a tömeget. De itt legalább nem fogsz elszökni.";
			link.l1 = "Gondolom ez az egész párbaj dolog egy csapda volt?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "Kicsit késôn jöttél rá, barátom. Úgyis harcoltunk volna - Ralph Faggle vagyok, szolgálatodra.";
			link.l1 = "Valójában én is ezt gyanítottam, ezért úgy döntöttem, hogy beszélek a szomszédokkal. Egyébként Adams is benne van ebben az ügyben? És mi van Jane-nel? Lehet, hogy ô...";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "A kíváncsiság megölte a macskát, nem hallottad? Azt mondták, hogy a párbajra jelenjen meg, ne szaglásszon. Lehet esélyed arra, hogy túléld ezt a zûrzavart\ntermészetesen. Provokálni az öreg katonát, és párbajra kényszeríteni a parancsnokát - tökéletes terv, amit Péter talált ki, azt hiszem. És Jane is jól tette a dolgát.";
			link.l1 = "Mondd csak, ki akart megszabadulni Charlie-tól?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "Ha, mintha én mondtam volna neked? Védd magad.";
			link.l1 = "Kár. Akkor majd késôbb megkérdezem Petert.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "Ó, látom, a szívére vette a történetemet, és már meg is büntette Ralphot, kapitány.";
			link.l1 = "Persze, hiszen, mint megjegyezte, én egy méltó és nemes ember vagyok. És most meg kell büntetnem téged is ezért az áruló csapdáért.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "Nyugodtan megpróbálhatja, kapitány - bizonyára már kimerült és megsebesült.";
			link.l1 = "Akkor tartsunk egy kis szünetet. Addig is mondd meg, kinek dolgozol?";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "Sajnálom, de a patrónusomnak ez nem tetszene, még akkor sem, ha utána sikeresen elbánnék veled. Ami egyébként most fog megtörténni.";
			link.l1 = "A francba!";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "Nem hiszem el, hogy ezek... ezek a gazemberek nemcsak becsaptak minket, hanem hazudtak a Királyi Haditengerészetrôl is! Hogy merészelték! Ha nem lennének halottak, lenyeletnék velük pár láncos lövést ezért az árulásért!...";
			link.l1 = "Az emberek mindenfélét hazudnak, Charlie. Azt hittem, ezt te is tudod. De azt biztosan tudod, hogy ki küldte ôket. Nem ez az elsô csapda, amit mostanában állítottak neked. Volt egy levelük, amiben részletes leírást adtak rólad. Kit dühítettél fel ennyire?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "Nos, én... Talán találunk valami mást az Adams' házban, uram?";
			link.l1 = "Kitér a kérdés elôl? De igaza van, úgyis alaposan át akartam kutatni. Gyerünk, menjünk.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "Szent ég, mennyi arany!";
			link.l1 = "Kár, hogy itt nincs semmi más. 'Jane' sehol sem található. Szerinted él még?";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "Nem tudom, uram, az ilyen gazemberek bármire képesek...";
			link.l1 = "Ez igaz, de nekem úgy tûnik, maga többet tud, mint amit mond. Nem ez az elsô alkalom, hogy vadásznak rád. És minden alkalommal egy halom pénzt találunk náluk.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "Nem vagyok benne biztos, kapitány, de talán egy St. John's-i uzsorás volt.";
			link.l1 = "Hogy szúrtad ki?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "Nos... nemrég kölcsönkértem tôle pénzt, hogy kifizessem a többi adósságomat. Richard megígérte, hogy kifizeti, de...";
			link.l1 = "Gondolja, hogy nem tette?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "Korábban nem hittem volna el, de azok után, amit veled tett, és sietve elhagyta a Karib-térséget Abival... Talán elfelejtette az adósságot. Vagy nem, de mégis elment... Richard úgy viselkedett, mint egy igazi pöcs, uram. Nem lepôdnék meg, de azért csalódott lennék, ha ez ismét kiderülne.";
			link.l1 = "Ne légy ilyen kategorikus, Charlie. Szóval, a St. John's lesz az.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "Á, hát itt van, uram - úgy tûnik, mindenki úgy döntött, hogy korábban jön. A megjelenésébôl ítélve elég könnyednek tûnik, ennyire bízik a képességeiben?";
				link.l1 = "Természetesen ez messze nem az elsô párbajom.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "Féltem, hogy nem jön el, uram. A többiek már itt vannak.";
				link.l1 = "Egy igazi nemes csak a halálával késhet el.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "Csodálatos szavak, uram! Bemutatom az ellenfelünket, Ralph Faggle-t. Ô pedig a második, Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "Találkozás...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "Az ellenfelünk, Ralph Faggle.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "És ô a második, Frederick Stokes.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "Szóval ô Ralph? Nem úgy néz ki, mint egy tipikus részeg szomszéd.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "Sosem tudhatod, ki lehet a szomszédod, gondolt már erre, Mr. de Maure? Heh-heh-heh.";
			link.l1 = "Szóval ez egy csapda... Látom, már nem is remegsz. Belefáradtál a lázas szerepbe?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "Az egyetlen dolog, amitôl most remegni tudnék, az a nevetés a naivitásán.";
			link.l1 = "Nocsak, nocsak. Csak azt sajnálom, hogy Charlie is elkísért - könnyebb és csendesebb lett volna egyedül elintézni téged...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "Hát ez csodálatos!";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "Engedd meg, hogy bemutassam...";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "Mr. Stokes, a második emberünk.";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "Ô pedig Ralph Faggle.";
			link.l1 = "Szóval ô Ralph? Be kell vallanom, én másképp képzeltem el. De nem számít, volt már dolgom rosszabbal is.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "Hmm, csodálkozom, naiv vagy, nem értesz semmit? Vagy túlságosan magabiztos?";
			link.l1 = "És mit nem értek, Mr. Adams? Gyerünk, lepjen meg.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "Általában az emberek meglepve vagy megijedve viselkednek az ilyen helyzetekben, de úgy tûnik, maga más típus. Annál kellemesebb lesz letörölni azt az önelégült vigyort az arcáról, Mr. de Maure.";
			link.l1 = "Micsoda fenyegetés! Nem ugyanazon az oldalon állunk, Peter?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "Ne mondja, hogy azt reméli, hogy mindannyiunkat legyôzhet azzal az öregemberrel. Túlerôben vannak, kedves uram.";
			link.l1 = "Ahogy mondtam, maga az, aki nem érti. Charlie morgott egy kicsit, de azért mondtam neki, hogy a biztonság kedvéért hozza ide a fiúkat. Mint kiderült, nem hiába. SRÁCOK, GYERTEK IDE!!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "Mi?..";
			link.l1 = "Meglepôdött és megijedt, Adams úr? Jó tudni.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "Így kell bánni az ilyen hazug gazemberekkel. Még mindig nem hiszem el, hogy volt pofájuk hazudni a Királyi Haditengerészetrôl! Én megfojtanám ôket egy lángszóróval!...";
			link.l1 = "Mostanra már tudnod kellene, hogy vannak, akiknek nincsenek skrupulusai, Charlie. Mondtam, hogy elintézem, maradhattál volna a hajón. Biztos akartál lenni benne, hogy segítek ezeknek a 'méltó embereknek'? És kinek volt igaza megint, hogy nem volt olyan egyszerû, mint gondoltad?";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "Magának, uram...";
			link.l1 = "Pontosan. De mondd csak, miért akarná bárki is levadászni téged? Nem ez az elsô alkalom.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "Nem tudom, kapitány. Az öreg Charlie csak egy egyszerû ágyús.";
			link.l1 = "Hmm, nos, nos. Rendben, mivel szegény párbajozóinknak nem volt semmi hasznos náluk... Nem, nézzük meg, hátha találunk valamit Adams' házban.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "Szóval ez a nô is eltûnt... Lehet, hogy rögtön utána menekülni készültek a városból 'duel'? És sietve - annyi arany van itt!";
			link.l1 = "Igazad van, mert nem csak aranyat hagytak hátra. Egy másik levél. Annyira siettek, hogy elfelejtették elégetni. Nézd, tetszeni fog a tartalma.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(olvassa) Nos, én vitatkoznék a 'oldról.'.";
			link.l1 = "Most nem ez a lényeg. Ez a második alkalom, hogy zsoldosokat küldtek utánad, és pénzzel és információkkal látták el ôket. És kifejezetten téged akarnak. Mondd csak, te egyszerû ágyús, kit tudtál ennyire feldühíteni?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "Csak egy tippem van, uram, csak egy, és nagyon nem szeretném, ha igaz lenne.";
			link.l1 = "Szóval, a legvalószínûbb, hogy igaz. Beszéljen hangosabban.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "Egyszer adósságom volt különbözô embereknek St. John's-ban, és...";
			link.l1 = "...és most azt hiszi, hogy vadásznak magára? Hányan engedhetnek meg maguknak zsoldosokat és ilyen összegeket?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "Jól gondolkodik, uram. Végül majdnem minden adósságomat úgy fizettem ki, hogy kölcsönkértem egy uzsorástól. Ô persze mindezt megengedheti magának. De...";
			link.l1 = "De mit? Kifizetjük az adósságát, és ennyi. Mi aggasztja magát?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "Tudja, kapitány, Richard megígérte, hogy kifizeti helyettem.";
			link.l1 = "Gondolja, hogy nem tette meg?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "Már nem tudom, mit gondoljak, uram. Amióta csak ismerjük egymást, mintaszerû úriembernek ismertem. De miután elhagyta magát, és elmenekült Abigail-lel... Nem lennék meglepve. Ezért mondtam, hogy nem szeretném, ha igaz lenne.";
			link.l1 = "A találgatásokat elôbb ellenôrizni kell, aztán fel lehet háborodni, Charlie. Menjünk, majd újra meglátogatod St. John's-t.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "Kapitány!!!";
			link.l1 = "Mi az, Charlie, mi történt?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "Történt?! Ne mondja, hogy elfelejtette a párbajt, uram! Lehet, hogy Adamset máris darabokra vagdossák, amíg maga itt heverészik!";
			link.l1 = "Rendben!... Azonnal elhagyom a várost.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "Charles de Maure kapitány? Az ott Charlie Knippel?";
			link.l1 = "Nem, ez...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "Ne tagadja, uram - a kolónián mindenki ismeri Charlie-t.";
			link.l1 = "Akkor miért kérdezi? Miben segíthetek?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "Nem segíthet. Kérem, ne álljon ellen - Charlie-t keresik itt. Ôrizetbe kell vennünk.";
			link.l1 = "Tudhatnám, hogy milyen vádakkal vádolják az emberemet? Az adóssága miatt? Ki tudom fizetni neki. Menjünk a bankárhoz, most azonnal, az ön jelenlétében.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "Adósság? Most hallok róla elôször. Nem ismerem a részleteket, de kérem, ne bonyolítsa a dolgokat - csak parancsot teljesítek.";
			link.l1 = "Ó, ez nagyszerû...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "Kapitány...";
			link.l1 = "Charlie, ha most elfutunk, még nagyobb lesz a vérdíj a fejünkre. És nem tudjuk kivívni a kiutat? Megpróbálom kihozni magukat, csak ne csináljanak semmi hülyeséget!";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "Azonnal hagyja abba a lármázást és a fenyegetést, uram. Adják át a fegyvereiket, és azonnal kövessenek!";
			link.l1 = "Én nem fenyegettem senkit, itt valami tévedés történt. Ez egy üzleti ügy, nem gyilkossági kísérlet.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "Nekem nem úgy tûnik. A törvény elôtt kell felelnie.";
			link.l1 = "És ha bocsánatot kérek és elmegyek?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "Hogy visszalopakodjon és befejezze, amit félbeszakítottam? Azt hiszi, hülye vagyok?";
			link.l1 = "Biztos az vagy, ha nem akarod ezt békésen rendezni. Isten tudja, nem akartam, hogy idáig fajuljon a dolog...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "Megölted ôt!";
			link.l1 = "Tekintse úgy, hogy saját kezûleg tette, uram. Válaszolhatott volna a kérdéseimre ahelyett, hogy hisztériázik. Esküszöm, még egy sikoly és szétlövöm az agyadat.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "Igen, én öltem meg. Ô kényszerített rá. De maga nem olyan agyatlan, mint ô, és nem követi a példáját, igaz?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "Mit akarsz?!";
			link.l1 = "Nemrég Charlie Knippel pénzt kért kölcsön tôled. A barátja megígérte, hogy visszafizeti a tartozását, de úgy tûnik, nem tette. Követelem, hogy azonnal hagyja abba a zsoldosok utánunk küldését. Kész vagyok kifizetni Charlie adósságát most azonnal, ha megengedhetem magamnak.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "Mit akarsz?!";
			link.l1 = "Nemrég Charlie Knippel pénzt kért kölcsön tôled. A barátja megígérte, hogy visszafizeti a tartozását, de úgy tûnik, nem tette. Követelem, hogy azonnal hagyja abba a zsoldosok utánunk küldését. Kész vagyok kifizetni Charlie adósságát most azonnal, ha megengedhetem magamnak.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "Charlie?! Soha nem tennék ilyet vele, ô egy jó, becsületes ember. Különben is, az adósságát már régen kifizette. Mr. Fleetwood, a Valkyrie kapitánya az utolsó pesóig rendezte.";
			link.l1 = "Tényleg? Tudom, ki ô. Ezt rögtön meg kellett volna mondania. Elnézést a kellemetlenségért, viszlát.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "Csak így?! Megfenyegettél! És megöltél egy embert!";
			link.l1 = "Elfelejtetted, mit mondtam? Még egy sikoly és csatlakozol hozzá. Viszontlátásra.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "Még mindig itt van, és még nem akasztották fel? Nos, üdvözletem a Sussexbôl, Charlie.";
			link.l1 = "Üdvözlöm, akárki is maga.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "Á, Charles de Maure. Kedves öntôl, hogy meglátogatja szegény Charlie-t. Számítottunk rá.";
			link.l1 = "Kik vagyunk mi?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "Nem számít. Jelentôs idôbe és pénzbe került nekünk, Mr. de Maure. Azt hiszem, nem bánják, ha itt és most Charlie-val és magával is foglalkozom.";
			link.l1 = "Nos, mivel úgyis mindketten halottak vagyunk, szíves jóindulatból megmondaná, kit haragítottunk meg ennyire? Megígérjük, hogy nem tesszük újra. És ki az a Sussex?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "Nem lehet. A kötelesség hív, és veled ellentétben én a tettek embere vagyok, nem a szavaké.";
			link.l1 = "Az isten szerelmére, elmagyarázná nekem valaki, hogy mi folyik itt?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Killer_5");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "Nos, átkozott legyek, kapitány, micsoda mészárlást rendezett itt!";
			link.l1 = "Tiltakozik? Inkább a bitófát választanád? Vagy talán a végtelenségig itt rohadni?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "Nem, uram. Köszönöm, hogy megmentett. Hogy ôszinte legyek, meglepett, hogy eljöttél, tekintve, hogy milyen könnyen hagytad, hogy elvigyenek. És meglepett, hogy milyen könnyen elbántál az ôrrel - ô egy tengeri róka volt. Egy tengerészgyalogos.";
			link.l1 = "Mondtam, hogy kihozlak, nem kellett volna kételkedned. Most pedig kifelé ebbôl a cellából, mielôtt az egész helyôrség ideér.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "Igenis, kapitány.";
			link.l1 = "...";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "A francba, uram, alig hiszem el...";
			link.l1 = "Mellesleg, mondd csak, mivel vádoltak meg téged? És ki az a Sussex?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "Nem tudom, uram. Fogalmam sincs, hogy kire gondoltak...";
			link.l1 = "Rendben, majd késôbb kiderítjük. Most pedig el kell tûnnünk innen.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "Mi a következô lépés, uram? Kockázatos dolog fényes nappal kiverni a vérszopóból az értelmet.";
			link.l1 = "Most adtál egy ötletet. Miért verjük ki belôle az értelmet nappal, ha most, az éjszaka leple alatt is megtehetjük?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "A fenébe is, ez egy zseniális ötlet, kapitány!";
			link.l1 = "Pontosan. Mondd csak, Charlie, te itt éltél egy ideig. Tudod, hol lakik az uzsorás?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "Régebben tudtam, uram, de amikor legutóbb itt jártam, éppen eladta a házát. Fogalmam sincs, hol van az új.";
			link.l1 = "Nos, ez probléma...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "Biztos vagyok benne, hogy kitalálsz valamit, kapitány, elvégre legyôzted a nagy, félelmetes Lucas Rodenburgot!";
			link.l2 = "Rendben, majd én elintézem. Bár, ha tudnád, hol van az uzsorás háza, az még jobb lenne!";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "Igen, legyôztem. De a reggel bölcsebb, mint az este, Charlie. Pihenjük ki az utat, és menjünk nappal - végül is nem azért vagyunk itt, hogy megöljük az embert.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "Biztos ebben, uram? Elveszítenénk a meglepetés erejét.";
			link.l1 = "Biztos vagyok benne, és fáradt vagyok. Különben is, én csak beszélgetni akarok. Megijeszteni egy kicsit, ha szükséges.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "Amit nem tudok... Nem tudom, sajnálom, uram.";
			link.l1 = "Á, mindegy, keressük meg.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "Arra gondol, amire én, uram?";
			link.l1 = "Attól tartok, igen, Charlie. Nincs más híres kapitány ezzel a névvel a Karib-tengeren. És Richard valóban Londonba ment. Tehát nem valószínû, hogy véletlen egybeesés.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "Szörnyû... Bár sok kemény szót mondtam róla, de ilyesmit soha nem kívántam neki! És szegény Abi! Gyermeket várt. Remélem, hogy életben van...";
			link.l1 = "Valóban, nem kívánom senkinek. Reméljük, Abi jól van. Van ötleted, ki tehette ezt Dickkel? Valami nagyhatalmú ellenség, akit valaha is említett?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "Biztos csak viccel, kapitány. Nem tudom, hogy Európában hogy van, de itt minden holland Richárdot akarta megölni.";
			link.l1 = "Ez igaz. Talán valaki itt nagyot költött, és bérgyilkosokat küldött utána az Óvilágba. Lehet, hogy nem ez a piti pénzkölcsönzô áll az ön elleni támadások mögött, hanem valami titokzatos Richárd ellensége?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "Nem tudom, uram. Jelenleg bármi lehetséges. De ez mindannyiunk számára bonyolítaná a dolgokat...";
			link.l1 = "Igen, igaza van, nekem sem tetszik ez a lehetôség.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "Mi, ki... MICSODA?! Mi folyik itt? Ki vagy te?!";
			link.l1 = "Ó, ugyan már. Ha meg akarnálak ölni, álmodban tenném. Szóval ne bonyolítsuk vagy rövidítsük meg az életünket. Bólintson, ha megértette.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "Mm-hmm...";
			link.l1 = "Nagyon jó. Nyugodjon meg - nem azért vagyok itt, hogy kiraboljam, elraboljam vagy bántsam.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "Akkor... miért vagy itt? Miért nem tudtál reggel jönni?";
			link.l1 = "Mert valami gazdag, befolyásos ember vadászik a barátomra. Okunk van feltételezni, hogy maga az, így valószínûleg nem biztonságos neki fényes nappal sétálgatni az utcákon.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "De tényleg nem értem, mirôl beszél, uram...";
			link.l1 = "Charlie Knippel. A városban mindenki ismeri ôt. Gondolkodjon erôsen. Tartozik neked pénzzel.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "A mi öreg Charlie-nk? Ez igaz, de az adósságát már régen kifizette, bár nem ô személyesen.";
			link.l1 = "És ki volt ez a jótevô?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "A kapitánya, Lord Richard Fleetwood. Ha nem hisz nekem, megmutathatom a feljegyzéseimet.";
			link.l1 = "Fleetwood, azt mondja? Akkor hiszek magának. Szóval nem küldött zsoldosokat Charlie után?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "Persze, hogy nem, miért tenném? És mondja, mi értelme lenne?";
			link.l1 = "Valóban. Nos, elnézést a késôi látogatásért. Jó éjszakát.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "Mi az, Charlie, azt remélte, hogy ma este a volt pártfogójával bujkál? Nincs ott. De hamarosan találkozni fogsz vele. Üdvözlettel a Sussexbôl.";
			link.l1 = "Ezt már tudtuk. És ki az a Sussex? És te ki vagy?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "Ez nem tartozik magára, Mr. de Maure. Kár, hogy jobban belekeveredett ebbe a zûrzavarba, mint szeretnénk. Maga csak bosszantó.";
			link.l1 = "Kinek a bosszúságára? Kérem, ne mondja, hogy lefeküdtem egy nagyon befolyásos és nagyon dühös angol feleségével.";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "Nagyon vicces. Találtam idôt a viccelôdésre. Úgy tûnik, igaz, amit hallottam rólad\nMit akarunk? Charlie feje is elég lenne. De tekintve, hogy mennyi bajt okoztál nekünk, ezúttal téged is érint - dugod az orrod oda, ahová nem való.";
			link.l1 = "Gondolom, le vagyunk tartóztatva.";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "Letartóztatva? Nem, kedves uram, a félmegoldások ideje lejárt. Ez egy kivégzés, de Maure kapitány.";
			link.l1 = "Egyetértek. A kérdés csak az, hogy kié.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "Nem gondoltam volna, hogy a Tengeri Rókák is benne vannak...";
			link.l1 = "Nos, mindennek megvan az elsô alkalom. Mondja, Charlie, ki az a Sussex?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "Én...";
			link.l1 = "Nem látod, hogy ez milyen messzire ment? És úgy tûnik, egy csónakban evezünk, Charlie. Szóval jogom van tudni a részleteket.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "Természetesen, kapitány. De nem itt, igaz? Hagyjuk el a szigetet, és beszéljünk a hajón.";
			link.l1 = "Igaza van. Rendben, siessünk.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "Hívott, kapitány?";
			link.l1 = "Igen, Charlie. Beszélnünk kell. Azt hiszem, már kitaláltad, mirôl van szó.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "Igen, uram...";
			link.l1 = "Rendben, uram. Mondja el, miért vadásznak magára a honfitársai, beleértve az elit alakulatokat is, amikor nem bûnözô vagy, vagy ilyesmi.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "Tényleg nem tudom, uram...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Ez nem vicc, Charlie. Bárki is vadászik rád, parancsokat adhat a tengeri rókáknak. Valószínûleg ô áll Richard meggyilkolása mögött is. Szóval, ha van valami ötleted, oszd meg velünk. Milyen üdvözlet Sussexbôl, ki az?";
			}
			else
			{
				link.l1 = "Ne nézz félre, Charlie. Látom, tudsz valamit. Mint a kapitányod, megparancsolom, hogy mondj el mindent. Ki az a Sussex?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "Rendben, kapitány. Sussex nem egy személy. Hanem... egy hajó.";
			link.l1 = "Üdvözlet egy hajóról? Ez badarság.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "Hadd magyarázzam meg. Leülhetek, uram? A történet hosszú és nem túl kellemes.";
			link.l1 = "Természetesen, Charlie. Mondja csak.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
			LaunchFrameForm();
			//DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "Hé, Charlie, Fleetwood kapitánytól jöttem. Látni akar téged.";
			link.l1 = "Köszönöm, pajtás. Történt valami? Általában mindent azonnal átküld rajtad keresztül.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "Nem is tudom... Azt mondja, hogy ezt közvetlenül veled akarja megbeszélni. Ez a te dolgod, oldjátok meg magatok.";
			link.l1 = "Ó, rossz érzésem van ezzel kapcsolatban...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Kurier_3");
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "Jó éjt, uram!";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "Jó éjt, uram! Hadd menjek el.";
			link.l1 = "Persze, menjen csak, elnézést kérek, uram.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Cortny_3");
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "Á, te vagy az, Charlie. Gyere be, gyere be. Csukd be az ajtót magad mögött.";
			link.l1 = "Jó éjt, kapitány. Mi folyik itt? És ki volt az a férfi? Egy nagyképû páva...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "Azt nem tudom megmondani. És azt sem engedhetem meg, hogy bárki meghallgassa a beszélgetésünket. Ne beszélj errôl senkinek, megértetted?";
			link.l1 = "Igenis, uram. Történt valami? Szokatlanul aggódónak tûnsz, ez nem vall rád.";
			link.l1.go = "DTSG_Fleetwood_3";
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "Neked úgy tûnik. Te sem nézel ki a legjobban, elvégre éjszaka van. De attól tartok, ma éjjelre vége az alvásnak, barátom - sürgôs és titkos küldetésünk van.";
			link.l1 = "És mi lesz a feladata, kapitány?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "Egy áruló likvidálása. A sajátjaink közül. Hamarosan egy diplomáciai hajó jelenik meg az Óvilágból Dominika partjainál - a fregatt 'Sussex'. hivatalosan azért, hogy jó üzletrôl tárgyaljanak a hollandokkal. De a valóságban...";
			link.l1 = "...információkat fognak átadni az ellenségeinknek, uram?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "Még rosszabb. Teljesen átállnak az ô oldalukra. És bár az Atlanti-óceánon való átkelés után kimerültek lesznek, végül is egy jó fregatt biztosan megpróbál majd elmenekülni, ha nehézhajóval támadunk\nSzóval gyorsan és határozottan kell cselekednünk. Csak a 'Valkyrie' -ra támaszkodhatunk - ô az egyetlen, aki képes egy ilyen küldetésre.";
			link.l1 = "Vajon a régi 'Valkyrie' elbír egy fregattal?...";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "Ha-ha, Charlie, kételkedsz a kapitányodban? Különben is, ahogy mondtam, kimerültek lesznek. Ha hirtelen támadunk, minden elôny a miénk.";
			link.l1 = "Soha nem tenném! De remélem, tudja, mit csinál, uram...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "Biztos vagyok benne. És még valami. Ez a disszidens magas pozíciót tölt be a Parlamentben, érti? Mindenütt lehet szeme és füle - nemcsak otthon, hanem már itt, a Karib-tengeren is. Szóval ne említse a Sussexet, vagy bármilyen részletet a városi küldetésünkrôl.";
			link.l1 = "Nem kellett volna elmondania, uram. Az öreg Charlie-ra mindig számíthat.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "Tudom, tudom. Csak a tét most nagyobb, mint valaha. Szedje össze a holmiját és készüljön fel - hajnalban indulunk.";
			link.l1 = "Igenis, uram. Jó éjt, uram.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_9");
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "Még sosem láttam Richardot ilyennek... Annyira aggódott, sôt... megijedt?";
			link.l1 = "De miért? Még velem sem osztotta meg. Nos, nem számít. Ô egy nagyszerû kapitány, úgyhogy biztosan elbánunk ezzel a fregattal és a fáradt legénységével.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Knippel_SamSoboi_2");
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "A 'Sussex' a láthatáron van, Charlie, készülj fel.";
			link.l1 = "Mindig készen áll, kapitány.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "Nagyon jó. Számítok rád és a láncdobásodra. Próbáld meg a lehetô leggyorsabban széttépni a vitorláikat, vagy még jobb, ha leszedsz egy árbocot. Kockázatos harcba bocsátkozni, hogy elsüllyesszük ôket, nincs értelme, ezért megpróbálok a fedélzetre lépni\nMellett meg kell gyôzôdnünk arról, hogy az áruló halott - ha elsüllyesztjük ôket, akkor is közel kell kerülnünk hozzájuk, és gondoskodnunk kell arról, hogy senki se élje túl.";
			link.l1 = "És ennyi honfitársat megölni egy árulóért...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "Szomorúan. Nekem is fáj, Charlie. De a parancs az parancs. Legalább nem szórakozásból csináljuk. Szóval essünk túl rajta gyorsan.";
			link.l1 = "Igen, uram...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_13");
		break;
		
		case "DTSG_Graf_Sheffild_1":
			dialog.text = "Elég! Kész vagyok átadni a kardomat és megvitatni a követeléseidet. De elôbb mutatkozz be! Ki vagy te, és hogy mersz megtámadni minket?! Ez árulás!";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "Richard Fleetwood kapitány. És ön bizonyára Earl Sheffield? És teljesen igaza van, ez árulás.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "Tudja, hogy ki vagyok? A fenébe! Tudtam, hogy valami ilyesmi fog történni, patkányok mindenütt, ezért kértem, sôt könyörögtem egy hadihajóért...";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "Nem mentett volna meg, csak meghosszabbította volna az elkerülhetetlent, mert más megoldást találtam volna. És igen, az árulás alatt a te árulásodat értem, Sheffield gróf.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "Akkor semmit sem tud rólam, uram! Mindenki tudja, hogy nincs nálam hûségesebb ember Angliához! Meg fogja bánni ezt a hibát, higgye el, amit mondok.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "Nincs mit megbánnom, hiszen nem én vagyok az, aki átáll a hollandokhoz.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "Mi?! Miféle ostobaságot beszélsz?! Félrevezettek, és úgy követtél egy hamis nyomot, mint egy veszett kopó\nAhem, igaz, a holland Nyugat-indiai Társasággal való tárgyalásokra indulok. De a mi Angliánk érdekében, kapitány. Ez egy szörnyû hiba, de még mindig kijavíthatjuk.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "Attól tartok, ez nem rajtam múlik. És fôleg nem magán múlik. Rossz oldalt választottak, uraim. Viszontlátásra.";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "Végeztünk. Azt hittem, az a kövér ember sosem hagyja abba a visítást. Ó, ezek a grófok, igaz, Charlie?";
			link.l1 = "Csak azon tûnôdöm, uram, mi van, ha az ezredes tévedett? Vagy, Isten ments, hazudott nekünk, hogy megszabaduljon a gróftól?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "Figyelj rám, barátom. És jól figyelj. A mi szolgálatunk nagyon veszélyes és nehéz, minden értelemben. Bármi megtörténhet - egy szomorú hiba, egy nevetséges véletlen, vagy egy áruló árulás\nA haza szolgálata nem csak ágyúgolyókkal való ágyútöltés, Charlie. A hatalmon lévôk számára nehéz döntések meghozatala. És a hozzánk hasonló katonáknak - végrehajtani ezeket a döntéseket.";
			link.l1 = "De mi van, ha egy nap ártatlan vért ontunk, százados? Az a mi kezünkön, a mi lelkiismeretünkön fog száradni.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "Akkor az ô kezükön is ugyanannyi vér fog száradni, mint a miénken, ha nem több. Hadd vigasztaljon ez. A lényeg az, hogy a szándékaink tiszták voltak - a haza ellenségének likvidálása\nNe segíts, Charlie, még mindig úgy kell beállítanunk, mintha holland támadás történt volna.";
			link.l1 = "Igen, uram...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Graf_Sheffild_25");
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "Tehát hamis bizonyítékokat hagytunk, hogy úgy tûnjön, mintha a hollandok tették volna. Richard és én soha többé nem beszéltünk arról a napról.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Nos, most már sok minden érthetô. Szerintem a gróf egyik rokona vagy támogatója áll Richard halála mögött. De miért pont téged? Te csak egy ágyús vagy, és nem hoztál semmilyen döntést azon a szomorú napon.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Kapott tapasztalati bónusz");
			}
			else
			{
				link.l1 = "Ez így van. Ez rossz üzlet, és bûzlik. Talán valaki rájött, és úgy döntött, hogy megbosszulja a grófot. De vajon egy ágyús megér ennyi pénzt? Pénz, zsoldosok, tengeri rókák alkalmazása... Kizárt dolog, Charlie.";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "Talán ez a személy mindenkire vadászik Richard korábbi legénységébôl. Mit gondol, uram?";
			link.l1 = "Szerintem el kellene távolodnunk Antiguától, és minél elôbb, annál jobb.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "Én is feltettem magamnak ezt a kérdést, kapitány, de nem találtam választ.";
			link.l1 = "Bassza meg. Valaki jön. Kértem, hogy ne zavarjanak!";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_103");
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Charles!..";
				link.l1 = "Mi a baj, Helen?";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "Charles, emlékszem, megkértél, hogy ne engedjek be senkit, és ne zavarjalak téged és Charlie-t, de...";
				link.l1 = "...úgy döntöttél, hogy te magad jössz. Rendben, minden rendben, Helen.";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Egy angol hadihajó! Nemrég látták. Elôször nem figyeltem oda, de bármelyik percben elérhet minket! Még sosem láttam ilyen gyors hajót.";
				link.l1 = "Akkor köszönöm, hogy szóltál. Remélem, van idônk felkészülni, mielôtt bezár. Helen, Charlie, csaták!";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "...késôbb folytathatják a titkos megbeszélést. Egy angol hadihajó tart felénk. Azt hittem, hogy fontos.";
				link.l1 = "Megyek, megnézem. Köszönöm, Helen.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "Kapitány, egy gyors hajó közeledik felénk. Nagyon gyors. A szellemek azt suttogják nekem, hogy gonosz szándékkal érkeznek.";
			link.l1 = "Köszönöm neked és a szellemeknek a figyelmeztetést. Készüljetek fel a harcra a biztonság kedvéért. És add át ezt az üzenetet a többieknek tôlem.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "Elnézést a zavarásért, kapitány, de sürgôs.";
			link.l1 = "Remélem, tényleg fontos, Alonso. Jelentést.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "Egy angol hajó közeledik. Ez... a 'Mirage', kapitánya.";
			link.l1 = "Mi az? Teljesen biztos benne? Megint ittál, mi?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "Biztos vagyok benne, kapitány - nincs még egy ilyen hajó a Karib-tengeren, ezt maga is tudja.";
			link.l1 = "Valóban. Megyek, megnézem magam - lássuk, hogy ez 'Mirage' a valóságos-e.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "Ó... De még nincs vége! Brian, hát itt vagy! Hol a fenében voltál?";
			link.l1 = "Ez csak késlelteti az elkerülhetetlent.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "Charles de Maure. Ha belegondolok, milyen messzire jutottál. Kár. Reméltem, hogy meglephetlek ezen a hajón.";
			link.l1 = "Tudja, hogy ki vagyok? Szóval, maga áll a mostani gondjaink mögött - úgy néz ki, mint egy magasan szálló madár, aki kénytelen elhagyni a kényelmes fészkét, és személyesen elôbújni, ahelyett, hogy egy másik keselyût küldött volna.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "Így van, mindkét esetben. Gondolom, egy nemes messzirôl felismeri a másikat. Thomas Lynch ezredes. Úgy tûnik, itt az ideje, hogy úriemberként beszélgessünk, ahelyett, hogy megpróbáljuk elpusztítani egymást. Talán kölcsönösen elônyös megállapodásra juthatunk.";
			link.l1 = "Nem ígérhetek semmit, de nemesemberként a szavamat adom, hogy legalább civilizált emberek módjára fogunk beszélgetni, ezredes.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "Rendben van. Fleetwooddal nem tudtam volna ilyen beszélgetést folytatni. Mégis, találtunk rá befolyást, és nem fog többé zaklatni minket. Kár, hogy magával nem jött össze, de mindegy.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Az egész Karib-térség Richard haláláról beszél. Szóval te voltál az! És feltételezem, hogy az általad említett befolyásoló tényezô Abigail volt? Egyébként mi történt vele?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Kapott tapasztalati bónusz");
			}
			else
			{
				link.l1 = "Nem fenyegetés, azt mondod? Szóval maga ölte meg? A gróf támogatója vagy?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Abigail? Á, a fiatal zsidó lány, a menyasszonya. Ismét bebizonyosodott, hogy ön igen éleslátó egyéniség. Él és virul - ezt ígértük és teljesítettük Fleetwood együttmûködéséért cserébe.";
				link.l1 = "Meg kell mondjam, eléggé együttmûködô volt. De miért tették ezt? Ön a gróf támogatója?";
			}
			else
			{
				dialog.text = "Támogató? Ó, épp ellenkezôleg. De látja, néhány kártyát nem lehet többé kijátszani, mert teherré válik a játékos számára. Sajnos Richard is ilyen lett.";
				link.l1 = "Értem. Minden tanút kiiktatsz. Mi történt Abigail-lel? Ôt is megölted?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Egyáltalán nem. Épp ellenkezôleg. De Richard túl sokat tudott, és azzal, hogy visszatért az Óvilágba, veszélyessé vált. Itt kellett volna maradnia, és akkor nem vettük volna el az életét.";
				link.l1 = "Mindenkit kiiktat, aki valaha is magának dolgozott, ezredes?";
			}
			else
			{
				dialog.text = "Kiket? Á, a menyasszonyát, gondolom. Ô volt az eszköz. A férfi élete az övéért. Jól van, esküszöm a becsületemre.";
				link.l1 = "Kétlem, hogy tudja, mi az a becsület, figyelembe véve, amit tett, ezredes.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Nem válaszolok erre a provokációra, uram.";
				link.l1 = "Akkor válaszolj erre - hogyan jutottál ehhez a hajóhoz? Ez... a 'Mirage'?";
			}
			else
			{
				dialog.text = "Elnézem ezt a sértést, mert olyasvalakitôl jön, akinek soha nem kellett hatalmat gyakorolnia és befolyásolnia a dolgok rendjét.";
				link.l1 = "Ha már itt tartunk, honnan szerezted a 'Mirage'? Ô az?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "Nem egészen. Csodálatos hajó, mi? Kár, hogy nem töltötte be a célját ellened. Ismeri ennek a hajónak a történetét, de Maure kapitány?";
			link.l1 = "A szellemhajóra és az angol kereskedôkre való vadászatra gondol?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "Ez? Ó, dehogy. Nem a jól ismert dolgokról beszélek. Olyan dolgokra gondolok, amik rejtve vannak a szemünk elôl. Ezt a ketchet Johan van Merden és Lucas Rodenburg tervezte\nEz az édes páros sémák láncolatát alkotta meg, és a hajót végül a havannai hajógyárból bocsátották vízre. Szerencsénk volt, hogy hozzájutottunk az eredeti tervrajzokhoz. És végül teljes pompájában újraalkottuk a Mirage-t, sôt, még továbbfejlesztettük is, kijavítva néhány hibát a tervezésében.";
			link.l1 = "Kár, hogy ahogy maga is megjegyezte, ez nem sokat segített magán, ezredes.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "Nevetô hangulatban van? Ne legyen. Elismerem, hogy mind kapitányként, mind harcosként felülmúlt engem. De itt még mindig én vagyok fölényben.";
			link.l1 = "Ez egy haldokló blöff? Vagy csak a magadfajta emberek szokásos önbizalomhiánya? Mi rejlik e szavak mögött?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "Kiváló kérdés. Nekem úgy tûnik, ön több, mint egy kurvapecér és párbajozó, ahogy a kutatásom sugallta. A találkozó minden kimenetelét figyelembe vettem. Még arra is, amikor a pengéd, golyód vagy eltévedt ágyúgolyód által halok meg. Ha ma meghalok, te és Charlie megbánjátok, hogy nem csatlakoztatok Fleetwoodhoz.";
			link.l1 = "Még több fejvadász? Még több fejvadászt? Kérem. Kellemetlen és unalmas volt, de nem halálos. Akkor is visszavertük ôket, és újra visszavertük ôket.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "Ebben nem kételkedem. Most már látom a gondtalan párbajozót újra beszélni. Nem csak fejvadászok. A Tengeri Rókák és az angol haditengerészeti hírszerzés teljes ereje úgy csapódik a fejedre, mint viharhullám a halászhajóra.";
			link.l1 = "Mit akarsz tôlem? Csak nem azt várod, hogy megadjam magam?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "Persze, hogy nem. Jól tanulmányoztuk önt ez idô alatt. Egy kölcsönösen elônyös üzletet akarok ajánlani. Amit nem lenne bölcs dolog visszautasítani. És mint két nemes, remélem, hogy meg tudunk egyezni.";
			link.l1 = "Akkor megismétlem a kérdést, ezredes, mit akar? Gondolom, Charlie... És úgy gondolja, hogy tud nekem valamit ajánlani cserébe? Nem árulok el néhány aranypénzért.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "Ismét helyes. Nem csak néhány aranypénzrôl van szó, ahogyan te fogalmaztál, hanem egy egész hegyrôl - 10 000 dublonról. A letét a Port Royal-i bankárnál várja önt, ha megegyezünk\nDe a legfontosabb, amit felajánlok, az az élete, de Maure kapitány. Hallotta, amit mondtam. Abbahagyunk minden üldözést, ha most mindannyian letesszük a fegyvert, és átadod nekünk Charlie-t\nHallottad már a kifejezést 'ember a társadalom ellen'? A te esetedben, ha visszautasítod, akkor 'ember az állam ellen'. Dönts, Charles. Itt és most.";
			link.l1 = "Könnyen felhasználhatja a címét és befolyását, hogy megfélemlítsen egy-két bolondot. De én nem vagyok bolond. És már mérföldekrôl érzem a kétségbeesést. Kifelé! És örüljön, hogy nem öltem meg - több mint megérdemli.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "Nincs szüksége Charlie-ra, ezredes. A hallgatására van szüksége.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "A magam és az embereim biztonsága érdekében egyeztem bele, nem pedig a pénzére való mohóságból, csak hogy tudja.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "Életének egyik legrosszabb döntését hozta meg, de Maure kapitány. Nem irigylem önt. Ôszintén. Magadat hibáztathatod - senki sem fog még egyszer hasonló ajánlatot tenni neked. Fôleg én nem. Viszontlátásra.";
			link.l1 = "Várjon, ezredes.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "Mi az, meggondolta magát? A szavaim végre hatottak?";
			link.l1 = "Igen, pont az ellenkezôje.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "Hogy érti ezt? Magyarázza meg magát.";
			link.l1 = "A szavaid csak megerôsítettek az elhatározásomban veled szemben. Ne nézz így - nem foglak megölni. És ahogy mondtam, még el is engedlek. De azt hiszem, hajó nélkül is boldogulni fogsz.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "Nincs rá szükségem, mert van hajóm.";
			link.l1 = "Igazad van. De csak abban, hogy nincs rá szükség. Lehet, hogy befolyásos ember vagy. De nincs érzéked a mértékletességhez. És tapintat. Azt teszem, amit te szoktál - a helyzet ura leszek.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "Maga nem az, de Maure kapitány. Ne áltassa magát.";
			link.l1 = "Teljesen? Talán nem. De maga sem az - az élete most az én kezemben van, ezredes. Nem számít, mi történik velem késôbb - most azt teszek, amit akarok. És én... elviszem ezt a hajót. Szabad vagy. A part nincs messze.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "Nem merné megtenni. De a tekintetedbôl ítélve... Élvezd a kis gyôzelmedet. Megcsináltad...";
			link.l1 = "Igen, igen, életem egyik legrosszabb döntését. Már hallottam. Le a hajóról. Az én hajómról. Magától ugrik, vagy dobjuk ki a fedélzetre?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_7");
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "Soha nem gondoltam volna, hogy így fogom látni - megalázva, kiugrik az ablakon, és négykézláb úszik a partra.";
			link.l1 = "Látod? Elégedett? Csodálatos. Te következel.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "Mit akar mondani, uram? Nem vagyunk ellenségek, csak parancsot teljesítettem... Legalább egy hajót kérhetek? Soha többé nem fogsz látni!";
			link.l1 = "Akkor sem kímélne, ha a maga helyében lennék, és elvesztettem volna egy csatát maga ellen. Örülj, hogy nem öltelek meg. Ki az ablakon. És most... Talán utoléri a patrónusát.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "Inkább meghalok, minthogy ilyen megaláztatással nézzek szembe, monsieur!";
			link.l1 = "Ahogy óhajtja.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "Az ezredes volt az, igaz, kapitány?";
			link.l1 = "Jól van, jól van. Nézzen ki az ablakon, Charlie, nem fogja megbánni.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_13");
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "Az ezredes? Soha nem gondoltam volna, hogy ilyet fogok látni, uram. Hogy valaki egy ilyen címmel rendelkezô embert a fedélzetre merészel dobni, mint egy közönséges matrózt! Richard soha nem tenne ilyet - a rang tisztelete a lényege volt.";
			link.l1 = "A kiképzés évei alatt beléje verték. Katonai ember, a megfelelô gondolkodásmóddal. Én nem vagyok az, és azt hiszem, szélesebb körben, ilyen... korlátozások nélkül.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "És nem kerülünk bajba, ha ezt tesszük vele?";
			link.l1 = "Heh, Richardot hibáztatja, de úgy gondolkodik, mint ô. Ellenállni mertünk, ezért egy ideig vadászni fognak ránk. De elôbb-utóbb még az angol haditengerészet is lemond rólunk. És Lynch számára ez személyes ügy lesz. De gondoskodtunk róla, hogy legközelebb ne álljanak mögötte állami források.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "Tudja, kapitány, ettôl a naptól kezdve még jobban tisztelem magát. Soha nem fogom megbánni, hogy nem Dickkel együtt indultam el a Valkûrrel, és úgy döntöttem, hogy csatlakozom önhöz.";
			link.l1 = "Köszönöm, barátom! Legyetek készenlétben - a vihar közeleg. De tudod mit? Valami azt súgja, hogy ismét gyôztesen fogunk kikerülni. Gyerünk, ideje visszamenni a fedélzetre.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "Ez nem teljesen igaz, bár engem személy szerint nem érdekel Charlie, ha mostantól tartja a száját. De a kollégáim szeretnék látni a testét. És tudják, hogy néz ki\nEz egy olvasott élet, Charles, nem egy gyerekmese vagy egy lovagias vers, amit a dadusok olvasnak nekünk gyerekkorunkban, és nem látok olyan megoldást, ami mindenkinek tetszik.";
			link.l1 = "De én igen. Mindig lehet találni egy hasonló testet. És hasonló ruhákat vehetsz. Megzsírozni néhány kereket. Én pedig beszélek Charlie-val. És a szavamat adom rá, mint garanciát.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				dialog.text = "Ez... nagy kockázat. És nem csak arról van szó, hogy bízhatok-e a szavadban. Hanem arról is, hogy a kollégáim hinni fognak-e nekem, amikor meglátnak egy Charlie-éra hasonlító testet. És ezt a kockázatot nem fogom vállalni... csak úgy.";
				link.l1 = "Mennyibe kerül?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				Notification_Reputation(false, 71, "low");
				dialog.text = "Egy olyan ember szavára, akinek a maga hírneve van? Maga viccel. A nemesi származás önmagában nem elég a bizalomhoz.";
				link.l1 = "Ha ezt egy másik embertôl hallja, akinek hasonló a származása és a tettei, bocsásson meg, ezredes.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "Természetesen igazad van. De ebben az esetben az én bizalmamról van szó, nem máséról. És te mint kezes nem felelsz meg nekem\nMég egyszer mondom neked. Add ide Charlie-t. Persze csak ha nem akar osztozni Fleetwood sorsában.";
			link.l1 = "Könnyen felhasználhatja a címét és befolyását, hogy megfélemlítsen egy-két bolondot. De én nem vagyok bolond. És már mérföldekrôl érzem a kétségbeesést. Kifelé! És örüljön, hogy nem öltem meg - több mint megérdemli.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "Végül, egyenesen a lényegre térve. Egy millió pezó. Utolsó ajánlat.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "Kifizetem a pénzt. Ne higgye, hogy szegény vagyok, vagy hogy nem becsülöm meg az embereim életét. Egyik sem igaz. Fogadja el.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = " Jó étvágyad van, bár nem is vártam kevesebbet. De most nincs annyi pénzem, és...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "Nincs ezüst - nincs alku. Azt hitted, hogy kegyelmezek? Úgy nézek ki, mint egy szent, uram?";
			link.l1 = "De talán várhatna egy kicsit? Hol és mikor lenne alkalmas, hogy újra találkozzanak? Kölcsönkérhetem a dublont egy uzsorástól.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "Akkor azt hiszed, még naivabb vagyok, mint gondoltam\nNem vagyok vidéki lány, aki kész örökké várni valakire, aki egyszer már megjárta vele\nNincs pénz? Amúgy sem kértem. Csak Charlie-t akarom. Nem vagy hasznomra, annak ellenére, hogy annyi bajt okoztál.";
			link.l1 = "Könnyen felhasználhatja a címét és befolyását, hogy megfélemlítsen egy-két bolondot. De én nem vagyok bolond. És már mérföldekrôl érzem a kétségbeesést. Kifelé! És örüljön, hogy nem öltem meg - több mint megérdemli.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "Tényleg ennyire ragaszkodsz szegény Charlie-hoz? Mindenesetre a nemességed tiszteletet érdemel. Gondoskodj róla, hogy az ágyúsod olyan csendben legyen, mint a sír. Különben mindketten ott végzitek.";
			link.l1 = "Megígérem. És tartsd be a szavad, és hagyj fel minden üldözéssel.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "Én is megígérem. És még valami. A becsületes gyôzelmed ellenére, magammal viszem a hajómat. Ez egy egyedi készítésû darab, tudod. És nagyon drága.";
			link.l1 = "És mi van a gyôztes jogával? De nem fogom a szerencsémet próbára tenni. Ezúttal.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_FadeLong("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "Szinte sajnálom, hogy ezt kell mondanom, Brian, de attól tartok, hogy az együttmûködésünk itt véget ér.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "Én... szabad vagyok, ezredes? Feloldja a fejemre kitûzött vérdíjat, és újrakezdhetem, mint törvénytisztelô ember?";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "Azt mondanám, hogy túl sokat láttál - akárcsak a néhai Fleetwood. Lényegében épp az orrod elôtt kaptam megvesztegetést.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "I... Nem mondok el senkinek semmit, Istenre esküszöm!";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "Persze, hogy nem fog.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "Nem!..";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "Ne nézz így rám, Charles. Ha állandóan azon aggódom, hogy Brian vajon kiborítja-e a bilit, nem fogok tudni aludni.";
			link.l1 = "Nem is tudom, hogy meg kellene-e lepôdnöm azon, amit láttam, vagy sem.";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "Nem kellene. Elkötelezett vagyok. Csak annyit kérek tôletek, hogy ne beszéljetek arról, ami történt. Megpróbálok találni egy hasonló holttestet, rendbe hozom az arcát rendesen, jó helyre teszem a pénzt, és meggyôzöm a kollégáimat.";
			link.l1 = "Köszönöm, ezredes úr.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "Egyelôre nincs mit megköszönnie. Mindig fennáll a veszélye, hogy nem hisznek nekem, és akkor a vadászat újraindul. Egyelôre viszontlátásra, de Maure kapitány. Elhajózom a hajómon. Nincs ellenvetés - már így is nagy szívességet tettem önnek és Charlie-nak.";
			link.l1 = "Nos, akkor viszlát.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_LT_25");
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "Tudja egyáltalán, hogy kivel beszélt, kapitány? Egy ezredessel! Ô volt az, aki ezt a zûrzavart szervezte?";
			link.l1 = "Tudom, ô mutatkozott be. És igaza van - ô volt.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "Furcsa, uram, mert valaha Richard feletteseként ismertem. Hogy lehetséges ez? És miért távozik, mintha mi sem történt volna? Mit akart egyáltalán?";
			link.l1 = "Igazából nincs ebben semmi különös. Azok, akik kétes parancsokat hajtanak végre, gyakran nem annyira az ellenség, mint inkább a feletteseik miatt kockáztatják az életüket. És a fejedet akarta, Charlie.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "Nem értem, kapitány. Akkor miért megy el? Elfogadta a vereséget?";
			link.l1 = "Ez egyáltalán nem vall rá. Aranyat kellett adnom neki, ami nagyjából annyit nyom, mint a maga feje. Talán egy kicsit többet is. Egy millió pezót, hogy pontos legyek.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "És te... kifizetted neki ezt a hatalmas összeget? Értem?";
			link.l1 = "Nos, nem csak magának. Hanem magamnak is. És az összes fiúért is. De igen, Charlie, elsôsorban érted. Ha megöltük volna, örökké tartó büntetôexpedíciókkal kellett volna szembenéznünk.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "Ezt... nem tudom elhinni, uram. Csak... köszönöm. Nem gondoltam, hogy Fleetwood ezt tenné a maga helyében.";
			link.l1 = "Túlságosan elfogult vele szemben a szökése után. Richard csak egy nyugodt és békés életet akart Abigail-lel. Sajnálom, hogy nem jött össze neki. Ráadásul megtartotta a szavát, és kifizette az adósságodat. Heh, én, Fleetwood - neked aztán tényleg szerencséd van a kapitányokkal, mi, Charlie?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "Nem viccelek, kapitány. Szóval, most már mindennek vége?";
			link.l1 = "Igen, drága barátom. Legalábbis egyelôre. A harcnak vége - szólhat a fiúknak, hogy tegyék el a fegyvereiket. És hadd készüljenek felhúzni a vitorlákat.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "Nem érdekel, hogy miért értesz egyet - akár kapzsiságból, akár félelembôl, akár az embereid iránti kötelességbôl. A lényeg, hogy egyetértesz. Elküldöm az emberemet Port Royalba a bankárnak szóló utasításokkal.";
			link.l1 = "Rendben. Nem hiszem el, hogy végre vége van.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "Tudod mit, a pokolba a pénzzel. Mindig lehet találni még. Van még valami más is, amit Charlie-ért cserébe kérek, ezredes.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "Ó? Be kell vallanom, meglepett, de Maure százados. És mi lenne ön szerint az öreg ágyús kopasz fejével egyenértékû, ha egy hegynyi arany nem felel meg önnek?";
			link.l1 = "Maga mondta - egy csodálatos hajó, a tervezési hibákat kijavítva. Alig várom, hogy én is kipróbálhassam. A tervrajzok még mindig nálad vannak. De csak egy Charlie van. Ráadásul a maga érdeke, hogy elégedett legyek.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				Notification_Perk(true, "Trustworthy");
				dialog.text = "Maga kemény tárgyalófél. Van fogalmad róla, mennyibe került nekünk, hogy csak egy ilyet építsünk?";
				link.l1 = "(megbízható) (becsület) Tökéletesen tudom, ezért kérdezem. A kezed könyékig az állkapcsomban van. Megpróbálhatod lelôni ezt a farkast. De akkor elveszíted a kezed. És nem csak azt.";
			}
			else
			{
				dialog.text = "Attól tartok, egy ilyen építése sokkal többe kerül, mint az arany, amit elôkészítettünk önnek. De szórakoztatott, Charles. A jó értelemben.";
				link.l1 = "Egy próbát megért.";
				if (!IsCharacterPerkOn(pchar, "Megbízható")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Látom, tudod, mit akarsz, és követed a céljaidat az életben\nHát, rendben. A ketch a tiéd. De felejtsd el a pénzt - a pénzkölcsönzô azt fogja mondani, hogy nem tud semmit.";
				link.l1 = "Ez nekem megfelel.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "Határozottan. Az életem a lehetôségek megragadásának és a kockázatoktól való megóvásnak a története\nSzóval hozd ide Charlie-t, és békében válunk el. Utána még a foglalót is elviheted. De én elmegyek ezzel a hajóval.";
				link.l1 = "Akkor rendezzük le a dolgot.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "Nem mondhatom, hogy teljesen elégedett vagyok. De gyorsan véget akarok vetni ennek. Most pedig add meg, amit akarok.";
			link.l1 = "Nem 'milyen', hanem 'ki'. De ahogy akarod.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "Én sem. Kezdem azt hinni, hogy nem csak arról van szó, hogy egy ember milyen, hanem arról is, hogy kivel veszi körül magát - egy egyszerû munka, egy öreg ágyús elfogása fejfájássá vált a kapitánya miatt, vagyis miattad, Charles\nCall Charlie itt. Ez a zûrzavar végleg véget ér - horgonyt vetünk, és a hajóink elválnak.";
			link.l1 = "Azt mondod, elválnak?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "Meglepettnek tûnsz? Biztos azt hitted, hogy a ketch a jogos zsákmányod? Nem vagyunk kalózok, de Maure kapitány. A civilizált emberek más, sokkal bonyolultabb szabályok szerint élnek. A hajó velem marad.";
			link.l1 = "Nos, akkor...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "Jól van, uram? Az ott... az ezredes?";
			link.l1 = "Igen, Charlie, az ezredes az. Épp idôben jöttél - épp magam akartam érted menni.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "Hívjon ide, kapitány? Most rögtön? Miért beszélgetett ilyen sokáig ezzel a... férfival? Azt hittem, bajban van, ezért jöttem ide.";
			link.l1 = "Igen, így van. A gyôzelem ellenére még mindig bajban vagyunk. És továbbra is azok lennénk, ha az ezredes és én nem találtunk volna megoldást.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "Sikerült meggyôznie, hogy hagyjon minket békén, uram?";
			link.l1 = "Sajnos, csak én. Nem mi. Te... vele mész, Charlie.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "Mi? De miért? Mi nyertünk!";
			link.l1 = "Hát nem érted? Nem gyôzhetünk folyamatosan - nem hagyják abba, amíg nem kapják el a fejedet.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "Nem hiszem el, hogy ezt teszi az öreg Charlie-val, kapitány. Olyan vagy, mint Dick. Mindketten azt mondtátok, hogy a barátaim vagytok. És mindketten elhagytak engem és mindenkit, aki közel állt hozzájuk.";
			link.l1 = "Ez a kapitány terhe, a felelôssége. Látom, ezt nem tudod megérteni, mert neked csak ágyúgolyókat kellett töltened ágyúgolyókkal.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "Nem érted? Talán csak nem vagyok olyan áruló, mint te? Tudod, hova kéne menned?";
			link.l1 = "A pokolba? Talán igazad van. Mindannyian megérdemeljük.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "A magáé, uram.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "Fergeteges. Majdnem felnevettem. Hallottad ezt, Brian?\nNéha az egyszerû parasztok beszédét hallgatni olyan, mintha egy kis szellô lenne, és egyáltalán nem irritáló. Jól döntöttél, Charles. Megértem, milyen nehéz ez neked. De vigasztaljon a tudat, hogy most már sem te, sem más embereid közül senki sem fog szenvedni.";
			link.l1 = "Remélem, megtartja ezt az ígéretét, ezredes úr.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "Én állom a szavam. Abigail sorsa a bizonyíték erre. Nézze meg Briant is. Egy francia kalóz, de helyesen döntött, amikor eljött az ideje, hogy a jó oldalra álljon. És senki sem nyúl hozzá, amíg hûségesen szolgál minket. Hozzá hasonlóan ön is a helyes irányba halad, de Maure kapitány.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "Ha már a mozgásnál tartunk. Minél hamarabb el akarok innen tûnni. Ezen a kétségtelenül gyors hajón, amit ígért nekem, ezredes.";
			}
			else
			{
				link.l1 = "Nem vagyok kalóz. És még nem tervezem, hogy csatlakozom az angol flottához. De szándékomban áll igényt tartani az ígért jutalomra.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "Nem titkolom - olyan érzés, mintha kitépném a szívembôl. Újra kell majd költenem, de talán megéri - túl régóta gyötör a gondolat, hogy Charlie esetleg kiborítja a bilit\nHa nem beszélsz, vagy nem követsz el súlyos bûnöket Anglia ellen, vedd figyelembe, hogy már nem vagyunk ellenségek. Élvezze az új hajót; valóban gyönyörû. Viszlát, Charles. Brian - készíts nekünk egy hajót. Charlie - kövess engem, mivel neked nincs beleszólásod a dologba.";
				link.l1 = "Viszontlátásra. Mindannyiótoknak.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "Kár, mindig szükségünk van rátermett emberekre, nemzetiségtôl függetlenül. De persze a jutalmat még így is megérdemled. Nyugodtan mehettek Port Royalba - én elôbb odaérek, mint bármelyik másik hajó ezen a ketch-en.";
				link.l1 = "Remélem is. És remélem, hogy Port Royalban nem fog fegyveres kíséret várni rám.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "Megint kételkedik a szavamban? Szégyellje magát. Kiérdemelte az egész angol haditengerészet háláját. Ha bármikor szüksége van valamire, vagy úgy dönt, hogy csatlakozik hozzánk, keressen meg, de Maure kapitány.";
			link.l1 = "Egyszer megpróbáltam támogatást és kapcsolatokat szerezni az angol hírszerzéssel. Nem sikerült. Szóval viszlát, ezredes.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 
