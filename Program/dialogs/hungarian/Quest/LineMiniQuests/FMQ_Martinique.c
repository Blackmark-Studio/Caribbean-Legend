// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Egy nyilvánvaló bogár. Szólj róla a fejlesztôknek.";
			link.l1 = "Ó, meg fogom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "carpenter":
			DelMapQuestMarkCity("Fortfrance");
			LAi_SetImmortal(npchar, false);
			npchar.lifeday = 0;
			DelLandQuestMark(npchar);
			dialog.text = TimeGreeting()+", kapitány. Engedje meg, hogy bemutatkozzam - "+GetFullName(npchar)+". Bár nemrég már találkoztunk, kétlem, hogy emlékezne rám.";
			link.l1 = "Üdvözlöm, uram. És hol láthattam önt korábban?";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugger 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "sloop 'Fekete Kutya'";
			dialog.text = "Hajógyárunk. Ön megvásárolta "+sTemp+". Emlékszel? Én ott vagyok ács.";
			link.l1 = "Igen, tényleg megvettem azt a hajót. Szóval mit akar, monsieur "+GetFullName(npchar)+"?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			AddLandQuestMark(sld, "questmarkmain");
			dialog.text = "Hajóépítônk "+GetFullName(sld)+" szeretne beszélni veled. Azt hiszem, valamilyen üzleti ajánlata van. Látta a hajóját a kikötônkben, és elküldött, hogy keressem meg. Lenne szíves elfogadni a meghívást?";
			link.l1 = "Rendben. Meglátogatom a fônökét, amint befejeztem az üzletet a városban.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("Voice\English\soldier_arest_4.wav");
			dialog.text = "Nos, nos, nos... Új csempészek a hálómban!";
			link.l1 = "Eh...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "Hagyd a szarságot! Több hordó gyanta van a hajógyárban. Kapitány, átadta ôket a bûntársának. Mindketten le vannak tartóztatva, és a törvény nevében elkobzom a rakományt!";
			link.l1 = "...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "Ne játszd a hülyét, mester! Milyen hordókat? Tudja, hogy éppen azokról a hordókról beszélek, amelyeket nemrég rakodtak ki ennek a matróznak a hajójáról! Mindketten a tömlöcben fogtok megrohadni! Mozgás, rohadékok...";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\soldier\soldier arest-02.wav");
			dialog.text = "Ez a gyanta, kedves hajóépítô mesterem, stratégiai értékû áru, ami a kormányzó közvetlen irányítása alatt áll! Mivel azt állítod, hogy a tiéd - legyen, ahogy akarod. Le vagy tartóztatva, ezt az éjszakát a kényelmes börtönünkben töltöd, holnap pedig részletes jelentést adsz arról, hogyan és milyen célból szerezted meg. Ne aggódj, elôbb-utóbb mindent megtudunk. Ön, kapitány, szabadon távozhat. Ez a te szerencsenapod.";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("Voice\English\soldier_arest_2.wav");
			dialog.text = "Tudtam, hogy valami baj van ezzel a hajóval... Úgy tûnik, alábecsültem magát, kapitány.";
			link.l1 = "Pontosan, hadnagy. Ennyire nem vagyok hülye. A hajóépítôvel való vidám együttmûködése most veszélybe került.";
			link.l1.go = "officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "officer_8":
			dialog.text = "Értem, értem. Gratulálok, biztos tehetséges lehet, hiszen sikerült lenyomoznia és meglepnie engem. Most pedig mondja el, mit akar.";
			link.l1 = "Nem világos? Vissza akarom kapni a gyantámat. A gyantát, amit te és a haverod elloptatok tôlem.";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "Rendben. Megkaphatod, de csak a tételed felét. Ennyi van itt elrejtve. Remélem, elégnek találja, mivel csak ennyit tudok felajánlani.";
			link.l1 = "Még mindig megpróbálsz átverni? Kárpótolj engem a másik feléért arannyal vagy a mögötted elrejtett áruval.";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "Ez nem lehetséges. A másik feléért fordulj a közös barátunkhoz.";
			link.l1 = "Te most szórakozol velem, baszd meg? Tényleg azt hiszed, hogy "+GetFullName(characterFromId("FortFrance_shipyarder"))+" visszaadja a hordóimat? Ez nevetséges.";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "Kapitány, vegye el az összes gyantát, ami nálam van, élje az életét és tûnjön el innen a pokolba. Ehhez az alkuhoz hozzáadhatom az ígéretemet, hogy nem okozok gondot önnek St. Pierre-ben. Ez az utolsó ajánlatom.";
			link.l1 = "Az életem mióta része az alkunak? Ha!";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "Úgy tûnik, még mindig legyôzhetetlennek érzi magát a harc után, kapitány. Hadd magyarázzam meg: azok újoncok voltak, kiképzetlenek és motiválatlanok, semmi esélyük az én csapatom ellen. Megölhetnélek itt és most, mindenféle alku nélkül, de nekem fontos az embereim élete. Valaki közülük megsérülhet, vagy akár meg is halhat, miközben megölöm magát. Szóval vagy elfogadod a nagylelkû ajánlatomat, vagy örökre itt maradsz. Ideje választani.";
			link.l1 = "Csessze meg, hadnagy, de kénytelen vagyok elfogadni a feltételeit. Túl nagy a túlerô.";
			link.l1.go = "officer_13";
			link.l2 = "Túlságosan magabiztos, hadnagy? Azt hiszem, meg kell leckéztetnem magát és a zsoldosait. Te kibaszott gyantás kutya!";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "Maga egy értelmes ember, kapitány. Fogjátok a hordótokat és tûnjetek el. Figyelmeztetnem kell, hogy a kormányzó elôtt ujjal mutogatni rám nem segít. Még ma megváltoztatom a rejtekhelyemet. Spórolj az idôddel.";
			link.l1 = "Nem is akartam. Megértem, hogy hiábavaló a hatóságokhoz fordulni.";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "Siessen, nincs sok idôm.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_02.wav");
			dialog.text = "Ó! Micsoda találkozó! Üdvözlöm, uram! Jól érzi magát?";
			link.l1 = "Jó éjt... ah, te vagy az! Emlékszem rád, találkoztunk a Karib-tengerre érkezésem elsô napján. Monseniour Gregoire Valinnie.";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "Örülök, hogy még emlékszel. Látom, hogy most már kapitány vagy. Kapitány "+GetFullName(pchar)+". Gratulálok.";
			link.l1 = "Köszönjük...";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "Zaklatottnak tûnik, kapitány. Mi történt itt? Valami baj van?";
			link.l1 = "Valami baj van...";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "Monsieur, ahelyett, hogy az utca közepén álldogálnánk, menjünk inkább egy kocsmába. Jól esne egy-két korsó. Ott beszélgethetünk. Jöjjön!";
			link.l1 = "...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "Töltse ki, kapitány...";
			link.l1 = "Gyerünk...";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "Uhh... Kérem, mondja el, mi a baj? Úgy nézel ki, mint az a fickó, akit múlt héten felakasztottak. Ugyanilyen arccal állt az akasztófán.";
			link.l1 = "Látja, Gregoire úr... Mondjuk úgy, hogy gondjaim vannak a munkával.";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "Kapitány, mindent megoszthat velem. Nem fogom elárulni a kormányzónak vagy a parancsnoknak, ebben megbízhat bennem. Nem bízik bennem?";
			link.l1 = "Bízom magában, uram.";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "Akkor valljon, és nyugtassa meg a lelkét. Talán tudok segíteni neked.";
			link.l1 = "Egy helyi hajóépítô felbérelt, hogy fosszam ki a Trinidadból kihajózó spanyol karavánt. Nagy szüksége volt gyantára, ez volt a célpontom, és azt ígérte, hogy hordónként tizenöt dublont fizet. Felkutattam a karavánt, kifosztottam, és idehoztam az árut. A hajómat javítás alá helyezték, és a hordókat kirakodták a hajógyárba. Éppen befejeztük volna az üzletet, amikor megjelent az a tiszt... Vajon honnan tudhatta meg?";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "Ennyi volt, elkaptak minket. Azt hiszem, elismerésemet kell adnom a hajóépítônek - minden felelôsséget magára hárított, azt mondta nekik, hogy a gyanta az ô tulajdona, és nekem semmi közöm hozzá. A végén letartóztatták, és az én érmémnek annyi. A spanyol karavánnal való balhé idô- és pénzpocsékolás volt, bár szerencsém volt, hogy nem kerültem börtönbe. Töltse ki újra, Gregoire úr.";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "Szóval, a hajóépítô le van tartóztatva?";
			link.l1 = "Nos, igen. Az a tiszt vitte börtönbe, akirôl beszéltem. Látnia kellett volna ôket.";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "Igen, mindkettôjüket láttam, bár fogalmam sem volt róla, hogy Felicien Gronier hadnagy letartóztathatja régi barátját.";
			link.l1 = "Mit... mit mondott az elôbb?";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Jól hallottad. Felicien Gronier hadnagy és a hajóépítô "+GetFullName(characterFromId("FortFrance_shipyarder"))+" régi barátok. Együtt szolgáltak a hadseregben még Európában. Gronier a katonaságnál maradt, és "+GetFullName(characterFromId("FortFrance_shipyarder"))+" sikerült saját vállalkozást indítania.";
			link.l1 = "Szóval ismerik egymást... Most már értem...";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "Kedves "+pchar.name+", úgy néz ki, mintha becsapták volna. Ön még újonc itt, és ôk kihasználták. Fogadok száz dublonnal, hogy monsieur "+GetFullName(characterFromId("FortFrance_shipyarder"))+" három nap múlva vagy kevesebb, de újra a hajógyárában fog sétálgatni.";
			link.l1 = "Úgy tûnik, igaza van, uram. Átvertek engem. Kizárt, hogy az a tiszt tudott a gyantáról. Tökéletes idôzítés.";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "Ez a Karib-tenger, monseniour "+pchar.name+". Szokj hozzá. Felejtsd el a kinézetet, a legrosszabb söpredék itt mindig úgy néz ki, mint egy kitüntetett nemes.";
			link.l1 = "Ezt a mondatot már hallottam valahol... Mit csináljak velük? Beszéljek a kormányzóval?";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "Attól tartok, hogy ebben az esetben "+GetFullName(characterFromId("FortFrance_shipyarder"))+" egy másik történetet fog nekik mesélni, és börtönbe kerülsz.";
			link.l1 = "Az biztos. Rendben van! Mivel a törvény nem az én oldalamon áll, a saját módszeremmel fogom csinálni, a fenébe is! Nem fogom csak úgy feladni.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "Kérem nyugodjon meg "+pchar.name+". A düh és a rum beszél belôled, nem te. Aludj egyet, aztán gondolkodj el újra. Talán az lenne a legjobb, ha elengednéd. Felicien Gronier hadnagy és "+GetFullName(characterFromId("FortFrance_shipyarder"))+" nagyhatalmú emberek itt, ôk jóval a te súlycsoportod felett állnak. Ne csinálj semmi hülyeséget.";
			link.l1 = "Majd meglátjuk. Köszönöm, hogy felvilágosítottál. Jó, hogy találkoztunk.";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "Légy óvatos. Tartsd észben, amit mondtam neked.";
			link.l1 = "Úgy lesz. Most pedig igyunk még egyet!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			PlaySound("Voice\English\LE\Greguar\Greguar_03.wav");
			dialog.text = "Kapitány "+GetFullName(pchar)+"!";
			link.l1 = "Ó, Gregoire úr! Már megint te!";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "Igen. A kocsmai beszélgetésünk után érdeklôdtem Felicien Gronier hadnagyról. Kiderült, hogy nemrég tíz nap szabadságot kért. A kérelmét jóváhagyták. Ma találkoztam vele, egy hosszúhajóval ment egy tartánba, amely hamarosan Guadeloupe-ra hajózott. A hajó neve Topáz\nMindent elmondtam, most már a te döntésed. Biztos vagyok benne, hogy látod a mintát Gronier hirtelen hívásában, hogy szabadságot vesz, és egy frissen épített tartánon elhajózik a szigetrôl.";
			link.l1 = "A pokolba is, nekem most már kristály, az biztos! Ennek a tartánnak a raktérben tárolják a gyantámat! Monseniour Gregoire köszönöm, tényleg jól jöttél! Tehetek valamit önért cserébe?";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "Ó, ugyan már, barátom. Nemesek vagyunk, segítenünk kell egymásnak. Mi így élünk. Hiszem, hogy te is ezt tetted volna, ha én lennék a helyedben. Ne vesztegess egy percet sem, hajózz északra és keresd meg a tisztet. Ne keveredjetek harcba, csak találjátok meg és derítsétek ki, mire készül. Siessen, kapitány!";
			link.l1 = "Még egyszer köszönöm!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "Mit nézel? Mit akarsz itt?";
			link.l1 = "Hé, haver, a cuccaimért jöttem. Látod azokat a hordókat ott? Az az én gyantám, amiért egy fillért sem fizettek nekem.";
			link.l1.go = "pirate_1";
			DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;
		
		case "pirate_1":
			dialog.text = "Idióta vagy, vagy mi? Tûnj el, amíg még tudsz!";
			link.l1 = "Túl sok energiát fektettem abba, hogy megszerezzem ezt a gyantát ahhoz, hogy hagyjam, hogy néhány mocskos söpredék megállítson.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Itt fogjuk eltemetni a díszes öltönyöd!";
			link.l1 = "Ó, milyen kedves tôled, hogy temetést javasolsz, de attól tartok, hogy itt kell hagynunk a parton, és hagynunk kell, hogy a sirályok felfalják a beleidet!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
