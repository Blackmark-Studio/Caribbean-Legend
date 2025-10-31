
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"! Elnézést, ön vitorlás"+GetSexPhrase("vagy","oress")+"?";
			link.l1 = "Kapitány vagyok "+GetFullName(pchar)+", szolgálatára.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "Lea vagyok. Lea Carno... "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitány úr, nemrég érkezett? Ugye nem látott egy halászhajót, a 'Cormorant' a tengeren? Tudja, a férjem... a férjem, Pierre... két napja kihajózott, és nem tért vissza.";
			link.l1 = "A 'Cormorant'? Nem, én még nem találkoztam ilyen hajóval. Az a név nekem is eszembe jutott volna. Sajnálattal hallom ezt, asszonyom. Remélem, hogy a férje jól van és csak késik az útja során.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "The 'Cormorant'? Ha! Ez a hajó neve vagy a tulajdonos beceneve? Akárhogy is, még egyiket sem láttam.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "Nem tudom, mit gondoljak... Még sosem volt ilyen sokáig távol. Mindig délben tért vissza, kivétel nélkül. És most... valami történt. Érzem.";
			link.l1 = "Menj a hatóságokhoz. Küldhetnek egy járôrhajót, hogy átfésülje a part menti vizeket.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "Nem tudom, mit gondoljak... Még sosem volt ilyen sokáig távol. Mindig délben tért vissza, kivétel nélkül. És most... valami történt. Érzem.";
			link.l1 = "Menj a hatóságokhoz. Küldhetnek egy járôrhajót, hogy átfésülje a part menti vizeket.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "Ó, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitány úr, természetesen már beszéltem a parancsnokkal. De mire volt jó? Csak a vállát vonogatta... Azt mondta, nincs szabad hajója, hogy megkeresse a férjemet.\nÉs én? Csak állok itt, bámulom a horizontot, várok... és reménykedem.";
			link.l1 = "Na, na, Madame Lea. Még ne essen kétségbe. Azt hiszem, tudok egy napot szánni arra, hogy segítsek a keresésben.";
			link.l1.go = "Agree To Help";
			link.l2 = "Miért aggódik ennyire? Talán a reggeli szellô egy bájos hölgy karjaiba sodorta. Majd sétál egyet, szívja a friss levegôt, és visszajön.";
			link.l2.go = "bad joke";
			link.l3 = "Adhatok egy tanácsot? Ne erôltesse tovább a szemét a horizonton. Menj a Le François-i kocsmába, és ott keresd meg a kedves férjedet. Ne vedd sértésnek, de valószínûleg csak egy kis szünetre volt szüksége a háztartási gondoktól, te pedig tragédiát csinálsz belôle. Sok szerencsét!";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitány úr, én... Nem is tudom, hogyan köszönjem meg... Fogalma sincs, mit jelent ez nekem! Mindenki csak a vállát vonogatja... De maga... maga hajlandó segíteni. Köszönöm!";
			link.l1 = "Még nem kell megköszönnöd. Csak mondja meg, hol szokott a férje horgászni? Volt egy állandó helye, vagy szeretett kóborolni?";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "Egy bájos hölgy?! Tényleg azt hiszed, hogy ez a megfelelô pillanat a viccelôdésre? Tudom, hogy bajban van... és te nevetsz a bánatomon! (weeps) A világon most minden ellenem van. Senki sem akar segíteni... Senki sem érti, milyen nehéz a szívem.";
			link.l1 = "Madame Lea, az ég szerelmére, bocsássa meg meggondolatlanságomat. Nem akartam megbántani! Esküszöm, megkeresem a férjét. Csak mondja meg, hol kezdjem.";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "Maga...? Tényleg segíteni akar nekem?";
			link.l1 = "Hát persze, hogy segíteni akar. Ez a legkevesebb, amit tehetek, hogy jóvá tegyem megbocsáthatatlan és rosszul idôzített viccemet.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "Köszönöm, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitány. Köszönöm... Tényleg, nagyon meglepett, nem is tudom, mit mondjak...";
			link.l1 = "Egyelôre nincs szükség köszönetre. Mondja inkább, hol szokott a férje halászni? Van egy állandó helye, vagy szokott mozogni?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "Hát... Pierre... Ritkán mondta meg, hogy pontosan hol horgászik. Úgy hívta, hogy 'az ô titka'. De ha ez segít megtalálni ôt... Talán... Nem tudom... Maga tényleg segíteni akar, ugye, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitány? Tényleg?";
			link.l1 = "Meg akarja osztani a férje titkos horgászhelyét? Biztosíthatom, hogy a családja titka nálam marad - kapitányi szavamat adom. Tudnom kell, hol kezdjem a keresést.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "Igaza van, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitány... Bocsásson meg. Az a hely olyan sokat jelentett Pierre-nek. Mindig azt mondta, hogy ez volt az egyetlen igazi titka, az ô kis kincse.\nDe én tudom, hogy hol van. Ha ez segít hazahozni ôt... A Le Marin-öböl közelében horgászott. A déli parton van, nem messze a várostól. Kérem, könyörgöm, találják meg!";
			link.l1 = "Ne aggódj, Lea. Mindent megteszek, ami tôlem telik. Voltak ellenségei? Megfenyegette valaki mostanában?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "Ellenségek? Pierre? Ô a legkedvesebb lélek a világon! Egy légynek sem ártana... Ô csak egy egyszerû halász. Kit bánthatott volna meg? Egyszerûen nem értem, mi történhetett... Ez az egész olyan furcsa... és félelmetes...";
			link.l1 = "Ne féljen, Lea asszony. Azonnal indulok. Biztos vagyok benne, hogy a férje biztonságban van. Visszahozom ôt a szeretô karjaiba. Maradjon erôs.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitány úr, kérem, van valami híre? Megtudott valamit? Bármit is?";
			link.l1 = "Attól tartok, még nem. De még mindig keresem, Lea!";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
			LocatorReloadEnterDisable("FortFrance_Town", "gate_back", true);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "Mit akar még? Nem volt még elég szórakozásod egy szegény nô kigúnyolásából?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitány! Pierre! Ó, mennyire örülök, hogy látom! Megtalálta ôt!";
			link.l1 = "Madame Lea, hadd mutassam be Pierre Carno-t, személyesen. Nem mondhatom, hogy sértetlenül megúszta, de nincs kétségem afelôl, hogy az ön gondoskodása rövid idôn belül meggyógyítja.";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "Pierre! Áldott Szûz Mária! Betegre aggódtam magam miattad! Hol voltál? Nincs szín az arcodon... olyan sápadt vagy... Ó! És mi ez?! Ezek a szörnyû sebek?! Vágások... és égési sérülések...";
			link.l1 = "Hallgass most, szívem kincse. Csak karcolások, idôvel elhalványulnak. Újra látni az arcodat... ez minden, amit kívántam. Ha nem lett volna a kapitány... Tartozom "+GetSexPhrase("neki","neki")+" az életemet.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Captain... I... Nem is tudom, hogyan köszönjem meg... hogy megtalálta ôt! Megmentette az én Pierre-emet! Köszönöm... köszönök mindent! Az Úr vigyázzon önre, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitány!";
			link.l1 = "Na, na, ebbôl elég volt. Amire Pierre-nek igazán szüksége van, az egy meleg étel és egy kis pihenés.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			dialog.text = "Robbantsd fel az egészet! Végre megmutatod magad, "+GetSexPhrase("te rühes kurva","te nyomorult szajha")+"! Hol az ördögben voltál? Már három napja ezen az átkozott parton süttetjük magunkat! Hol van a rakományunk?!";
			link.l1 = "Úgy tûnik, a mulatozás nem kezdôdhet nélkülem, ugye, uraim? Hát, lehet, hogy egy kicsit késtem, de jobb a dagállyal érkezni, mint egyáltalán nem!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "Hozzám beszélsz, ugye? Talán tanuljatok meg viselkedni, mielôtt úgy ugatjátok a kérdéseket, mint a patkányok!";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-3.53, 2.35, 6.35, true, 1.93, -0.60, 11.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Megszerzett tapasztalat", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Megszerzett tapasztalat", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+"Te elkényeztetett kagyló! Nyisd ki a lámpáidat, te ostoba bolond - ez egyáltalán nem a mi kapcsolatunk!";
			link.l1 = "Argh... A kormányzó újabb ölebje! Biztos, mint a dagály! Mivel "+GetSexPhrase("ez a feketerigó","ez a bolond lány")+" idevonszolta "+GetSexPhrase("magát","magát")+" , hurcoljuk "+GetSexPhrase("ôt","ôt")+" a barlangba a másik patkánnyal. Majd megmutatjuk "+GetSexPhrase("neki","neki")+" , hogyan szedjük ki a titkokat - elég gyorsan elárulnak minden mocskos tervet, amit a gazdájuk valaha is megálmodott!";
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.53, 2.35, 6.35, false, -0.03, 0.40, 7.77);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_2"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = "Miféle mocskos fantáziák bujkálnak a fejedben, te sóval átitatott szörnyeteg? Hagyd abba a nyáladat! Jobb, ha eladjuk ôt... tudod kinek. Egy láda pénzt adna egy ilyen szép lányért, mi pedig egy hónapig iszogatnánk és kurváznánk vasárnaponként!";
			if (pchar.sex == "man")
			{
				dialog.text = "Mi a fenének van szükségünk Davy Jones' lockerre, hogy egy újabb tampon zsúfolja a briggünket? Nyomd erôsebben a párját - úgy fog énekelni, mint egy sirály napfelkeltekor. Ami ezt az egyet illeti, zsigereljük ki itt és most, megkímélve magunkat attól, hogy az arcát nézzük!";
			}
			link.l1 = "Ezer éhes cápa rágja a beleidet, "+sld.name+"! Te vagy a legravaszabb csempész az egész szigetcsoportban!";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
					notification("Nincs pisztolyom.", "NONE");
					link.l2 = "Ha ez a patkányagyú a legélesebb kardod, el sem merem képzelni, miféle ôrült ostobaságok zörögnek a többiek fejében!";
					link.l2.go = "Kontr Le Maren3";
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
					sld = CharacterFromID("VPVL_contr_1");
					CharacterTurnByChr(sld, CharacterFromID("Blaze"));
					CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
				}
				else
				{
					link.l1 = "(magamnak)(Pisztolyok) Míg ezek a tengeri patkányok csak fecsegnek az értéktelen fecsegésükkel, nekem van esélyem gyorsan és igazul lecsapni, mint villám a tiszta égbôl.";
					link.l1.go = "murder";
					notification("A csekk átadva", SKILL_PISTOL);
					locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
				notification("Túl alacsony képzettség (20)", SKILL_PISTOL);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
				CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
			}
			link.l2 = "Ha ez a patkányagyú a legélesebb kardod, el sem merem képzelni, miféle ôrült ostobaságok zörögnek a többiek fejében!";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "Kivágom a fejedbôl azt a csóváló nyelvet, te szemtelen kúrva"+GetSexPhrase("","-mocskos kurva")+ ", és megetetem a sirályokkal, hogy soha többé ne szólalj meg!";
			link.l1 = "Kivágod, ugye? Akkor gyere, ha van merszed táncolni az ördöggel.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			//locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... Bocsásson meg... Szétszóródott az eszem... Azért jöttél, hogy befejezd, amit elkezdtek?";
			link.l1 = "Ön Pierre Carno?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "Ayou, én vagyok. Tudod a nevem?";
			link.l1 = "Persze, hogy ismerem. Különben mit keresnék itt?";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "Bocsásson meg, nem értek semmit... A fájdalom és az éhség megfosztott az érzékeimtôl... Miért jöttél?";
			link.l1 = "Egyszerû. Amióta eltûntél, hûséges feleséged a rakparton ôrködik, szemei mindig a Kormorán vitorláját keresik. Szomorúsága olyan mélyen áthatott, hogy nem tudtam elmenni mellette érintetlenül - elhatároztam, hogy megkereslek.";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "Feleségem... drága Léa... Biztos voltam benne, hogy soha többé nem látom ôt...";
			link.l1 = "Ez a dagály elmúlt. A kikötôben vár rád, még mindig a reménybe kapaszkodva. Menjünk innen. Fogd meg a karom.";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "Irgalom... "+GetSexPhrase("Monsieur","Mademoiselle")+"... Szükségem van egy pillanatra... a lábaim olyanok, mint az uszadékfa... Köszönöm, igazán. Ha te nem lennél... úgy érzem, mintha maga a Mindenható küldött volna téged... Nem mondtad meg a neved. Hogyan szólítsam meg a megmentômet?";
			link.l1 = "Kapitány "+GetFullName(pchar)+". Amíg összeszeded az erôdet, meséld el, hogyan kerültél erre a helyre. Üzleteltél ezekkel az emberekkel?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "Az ég szerelmére, nem, kapitány. Én csak egy szerény halász vagyok. A nap olyan jól indult. A nyugati part mentén horgásztam - a fogás hihetetlen volt.\nLelkesen hordtam a halakat és dobtam ki újra a hálómat, de nem vettem észre, hogy az áramlat a zátony felé húzza a csónakomat. A hajótest vékony volt, mint a tojáshéj - egy csapás elég volt ahhoz, hogy a tenger bejusson. A kormorán, a reggeli fogással megterhelve, gyorsan elsüllyedt.";
			link.l1 = "Aztán partra szálltál, de a csempészek összekevertek a kormányzó egyik kémjével?";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "Pontosan. Alig értem ki a partra, az átkozott hullámok által megrázva. Csak meg kellett szárítkoznom és pihennem, mielôtt a városba indulok. Aztán a semmibôl megjelentek azok az ördögök.\nElég egy pillantást vetettek rám, és úgy döntöttek, hogy kém vagyok. Egy szót sem tudtam szólni, mielôtt megkötöztek és idevonszoltak. Két napig éheztettek és kínoztak, próbáltak rávenni, hogy valljak be olyan dolgokat, amikrôl semmit sem tudok - ügynökök, tervek... de én semmit sem tudtam!";
			link.l1 = "Agyakból nem volt sok - ezért etetik most a rákokat. De ez már mind a múlté. Szabadok vagytok. Ideje újra találkozni a feleségeddel - ô már biztosan a feje tetejére állt’ end.";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "Csak azt akarom, hogy újra a karjaimban legyen. Azt hiszem... Azt hiszem, most már tudok járni.";
			link.l1 = "Akkor ne vesztegessünk el több idôt.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Kapitány, könyörgöm, jöjjön a kocsmába holnap este hat órakor. A lelkiismeretem sosem nyugodna meg, ha nem tudnám megfelelôen megköszönni. De most... Nem találom a szavakat, hogy kifejezzem, ami a szívemben van. Kérem, jöjjön. Nagyon sokat jelentene nekem.";
			link.l1 = "Rendben, Pierre. Ne aggódj, ott leszek.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "Kapitány! Hát eljött! Kérem, csatlakozzon hozzám!";
			link.l1 = "Örömmel!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // Just in case
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "Emeljük poharainkat a további szerencséjére és egészségére!";
			link.l1 = "Nem csak az enyémre, Pierre, hanem a tiédre is. Sokkal jobban nézel ki, mint amikor abban a nyomorult barlangban találtam rád. Egészségünkre!";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "Capitaine, nem tudom kifejezni végtelen hálámat! Nem ment el mellettem, nem fordult el - segített egy vadidegennek, egy szerény halásznak. Az ilyen nemeslelkûség méltó jutalmat érdemel, és én mindent, amim van, önnek kívánok adni.\nTessék - húsz darab naparany borostyán és öt ritka kék kô, amelyeket egy elsüllyedt roncsból mentettek ki. Ezek mostantól a tiéd.\nMég a navigációs eszközeimet és a felszerelésemet akarom neked adni. Nem maradt hajóm, így nem szolgálnak nekem semmi célt.";
			link.l1 = "Köszönöm, Pierre. Ezeknek biztosan hasznát veszem. De a legfontosabb, hogy újra otthon vagy, és a feleségednek nem kell többé félelemben élnie. A dolgok mindkettôjük számára meg fognak változni.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Pierre, értékelem a gesztust, de tartsa meg ôket. Minden érmére szükséged lesz, hogy megjavítsd a hajódat, felszerelést, hálókat, hordókat vegyél... A köszönet, és hogy újra együtt látlak a feleségeddel - ez elég jutalom. Vigyázzanak egymásra.";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "Még mindig nem tudom elhinni, hogy mindez tényleg megtörtént... Igyunk a családom életének új fejezetére - és az Ön nemes szívére, kapitány úr!";
			link.l1 = "És a szerencsére, Pierre. Mindannyiunknak jól jönne egy kis belôle!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;

		case "PierWontGift1":
			dialog.text = "Kapitány, nem hagyhatom, hogy a dolgok így nyugodjanak... Megmentette az életemet, és mindent magának köszönhetek. Mivel visszautasítja a borostyánt és a többi ajándékot, engedje meg, hogy legalább megtanítsam a legénységét, hogyan kell halászni a sekély vizeken. Ez majd táplálja ôket, és megkönnyíti a pénztárcádat, ha ellátmányról van szó. Mit szólsz hozzá?";
			link.l1 = "Ez egy remek ötlet! Ahogy a régi mondás tartja - tanítsd meg a lelket hálót vetni, és soha nem marad éhen.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "Bölcsen mondta, kapitány! Örülök, hogy a hasznunkra lehetek. Most pedig - osztozunk még egy pohárral?";
			link.l1 = "Egészségedre és jólétedre, Pierre!";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Négy óra telt el...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
			int foodDays = CalculateShipFood(&pchar);
			dialog.text = "Neptunusz szakállára! Ez erôs grog! Még egy-két korty, és én... hic... Egy olyan dalocskát fogok zengeni, ami a krákent is felébreszti! Minden lélek innen a kikötôig hallani fogja a hangomat!";
			link.l1 = "Tegye el azt a dalocskát nyugodtabb vizekre, Pierre. Tartogasd a hangod a... hic... következô kikötônkig. Ha elkezdesz harsogni, hamarosan én is csatlakozom a kórushoz. És nekem... ööö... sürgôs dolgok követelik a figyelmemet. A dagály senkire sem vár... hic... még a széllel a csészéjükben sem! Vigyázz magadra... hic... és a jó asszonyodra is!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			notification("A hajó élelmiszer-felhasználása 15%-kal csökkent.", "None");
			}
			else
			{
			dialog.text = "Neptunusz szakállára! Ez erôs grog! Még egy-két korty, és én... hic... Egy olyan dalocskát fogok zengeni, ami a krákent is felébreszti! Minden lélek innen a kikötôig hallani fogja a hangomat!";
			link.l1 = "Tegye el azt a dalocskát nyugodtabb vizekre, Pierre. Tartogasd a hangod a... hic... következô kikötônkig. Ha elkezdesz harsogni, hamarosan én is csatlakozom a kórushoz. És nekem... ööö... sürgôs dolgok követelik a figyelmemet. A dagály senkire sem vár... hic... még a széllel a csészéjükben sem! Vigyázz magadra... hic... és a jó asszonyodra is!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "Arr, Capitaine... önnek egy igazi tengerész szíve van... hic...! Az adósságom önnek soha nem lesz kiegyenlítve, hallja? Ha a horgonytok újra a kikötônkben horgonyozna... a mi tûzhelyünk... a mi tûzhelyünk a tiéd lesz, mintha ugyanattól az anyától születtél volna... ugyanattól az anyától! Lelkemre és becsületemre! Majd újra összefûzzük a fôkötélzetet, ha Fortuna visszavezet téged e partokra!";
			link.l1 = "Csak nyugodtan, Pierre! Jobb lesz, ha... hic... lehorgonyzok, mielôtt a tengeri lábaim kocsonyává válnak, és a kocsma padlóján sodródom! Szép szelek töltsék meg a vitorláidat!";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
		break;

		case "Exit2":
			DialogExit();
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "Too-o-o-o, a mélykék tenger, és a passzátszelek szép... hic... a fishin' grounds mi sa-a-ail a hajnalban!... A fenébe ezekkel a rummal átitatott eszekkel! A versek nem jutnak eszembe! Kapitány! Még mindig itt horgonyozol? Kocsmáros! Hozzátok elô... hic... a legjobb nyugat-indiai pálinkát a pincébôl!";
			link.l1 = "Elmegyek, Pierre! Hic... amíg még vissza tudok navigálni a hajómhoz anélkül, hogy zátonyra futnék!";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+"! Egy látvány ezeknek a sófoltos szemeknek! Mit szólnátok egy kis karibi szeszes italhoz? Hogy megemlékezzünk az élet hatalmas óceánján való találkozásunkról!";
			link.l1 = "Az idôjárás által megviselt arcod az én szívemet is megörvendezteti, Pierre. Sajnos, a kötelességem megköveteli a mai napon a józanságomat. Útvonalam áruló vizeken halad, melyek tiszta elmét és biztos kezet követelnek. Talán amikor legközelebb a csillagok együtt állnak?";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "Ayou, ayou, kapitány! Egy hajót ki kell hajózni, mielôtt kikötne. A fôkönyvet a szabadidô elôtt, ahogy a kereskedôk mondják. De ha Fortuna újra felénk forgatja a kereket, olyan tósztot mondunk, amire maga az öreg Feketeszakáll is büszke lenne!";
			link.l1 = "Írd be a hajónaplóba, Pierre. Míg a dagály újra összehoz minket!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "Kapitány! A hajója biztonságos kikötôt talált a kötelezettségek viharából?";
			link.l1 = "A kereskedelem áradata még mindig a horgonyomat húzza, Pierre. A kötelességeim egy ideig a kormánykerékhez kötnek.";
			link.l1.go = "Exit";
		break;
	}
}   