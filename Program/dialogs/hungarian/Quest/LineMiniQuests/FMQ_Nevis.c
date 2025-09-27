// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
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
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", kapitány. (üdvözöl) Engedje meg, hogy bemutatkozzam - Leftenant "+GetFullName(npchar)+", Antigua Tengeri Gyalogezred, St. Johnsban helyôrségben. Egy szívességet szeretnék kérni.";
			link.l1 = "Üdvözlöm Gretton hadnagy. A nevem "+GetFullName(pchar)+". Miféle szívesség?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Hadd magyarázzam el röviden a helyzetet. Négy emberem és én St. Johnsból Sint-Maartenbe tartottunk, amikor vihar csapott le a hajónkra. A rossz idô nem tartott sokáig, de elég volt ahhoz, hogy az öreg kádunk léket kapjon. Meg kellett változtatnunk az irányt, és itt kellett megállnunk javítás céljából. Ez olyan szabadidôt vesz el, amivel nem rendelkezünk\nSietünk Sint-Maartenbe, pontosabban a Grand Case Beachre. Segítsen nekem, kapitány, és megéri a fáradozását. Két nap utazás bôkezû fizetésért!";
			link.l1 = "Nagylelkû fizetésnek kell lennie, hadnagy úr, ha azt akarja, hogy titokban angol tengerészgyalogosokat helyezzek el egy holland szigeten.";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = ""+UpperFirst(GetAddress_Form(PChar))+", ez ne aggasztja Önt. Semmilyen veszély nem fenyegeti. Csak tegyen ki minket az öbölnél, és kész. Nos, megegyeztünk?";
			link.l1 = "Rendben, benne vagyok. Nincs olyan messze innen. Halljuk a fizetést.";
			link.l1.go = "seafox_3";
			link.l2 = "Sajnálom, de sürgôs dolgom van egy másik irányban, és nem szeretném felzaklatni a hollandokat.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "Ahogy mondja, kapitány. Akkor tovább keresem. Viszontlátásra és Isten áldjon!";
			link.l1 = "Viszlát, hadnagy úr.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("Kaptál egy erszényt tele dublonnal.");
			dialog.text = "Tízezer darab pesó. Itt az elôleg.";
			link.l1 = "Ez az elôleg. Hívja az embereit a fedélzetre, ne vesztegessük az idôt.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Köszönöm a zökkenômentes utat, kapitány! Nagyon sajnálom, de ebben a pillanatban nem tudok fizetni... egy luggerünknek kellett volna itt lennie a környéken, de nincs itt. Ahogy azt ön is jól láthatja. Még egyszer kell kérnem a segítségét. Tudna várni ebben az öbölben két-három napot? El kell mennünk, hogy körülnézzünk. Amint visszatérünk, vigyen el minket Antiguára. Fox ezredes nagylelkûen meg fogja jutalmazni önöket.";
			link.l1 = "Hm... Ez nem egészen az, amiben megállapodtunk...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "Kérem, ne legyen csalódott kapitány. Tudom, hogy mit érezhet, de sajnos: Egyáltalán nincs pénzem. Megígérhetem, hogy kártérítést kap mindkét útért és azért, hogy itt várakozik ránk. Valamint magának Fox ezredesnek a köszönetét is!";
			link.l1 = "Nem hagyhatom önt cserben... Rendben, Gretton hadnagy. Három napig itt fogok várakozni, de nem tovább.";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Köszönöm, "+GetAddress_Form(NPChar)+"! A szárazföld belseje felé tartunk. Esküszöm, hogy 72 órán belül visszatérünk, egy perccel sem tovább.";
			link.l1 = "Isten éltessen, hadnagy úr. Ne hagyja magát elkapni.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Micsoda véletlen találkozás! Azt hittem, hogy a Grand Case Beach-en vár ránk, "+pchar.lastname+" kapitány!";
			link.l1 = "Üdvözlöm, hadnagy úr, a meglepetés kölcsönös. Nem számítottam rá, hogy holland katonának öltözve látom.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "Ez a mi álruhánk... Miért van itt, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Ez egy veszélyes álca, pajtás. A kémeket tárgyalás nélkül kivégzik. És ha már a kivégzésnél tartunk, ha el akarja kerülni a sajátját, jobb, ha figyel.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "Elragadtatottan figyelek magára.";
			link.l1 = "Elhajóztam Philipsburgba, és beszéltem a helyiekkel, miután partra szállt. A hollandok a nyomában vannak. Tudnak a küldetésedrôl, hogy megmentsd az elfogott magas rangú angol tiszteket.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "A francba, és a pokolba vele! Honnan a fenébôl tudtak errôl?";
			link.l1 = "Az egyik elfogott angol tiszt. Szabadságáért cserébe mindent elmondott a hollandoknak, amit a mentôakcióról tudott. Egész Philipsburg készen áll arra, hogy ön és az emberei megpróbáljanak behatolni a városba. A helyzetet tetézi, hogy egy holland korvett járôrözik a tengeren Sint-Maartin körül. Ez egy csapda, hadnagy úr.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"Az a becstelen gazember! Kiderítem, ki az az áruló, és feljelentem a Parlament elôtt!";
			link.l1 = "Azzal várnia kell, Mr. Gretton. Menjen vissza a Grand Case Beach-re még ma este, és szálljon vissza a hajómra, mielôtt elkapják.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "És angol úriembereket egy holland börtönben hagyni? Inkább meghalok, uram. Nem hagyom cserben Fox ezredest.";
			link.l1 = "Hm, gondolja, hogy a hollandok hagyják, hogy az akasztófát vagy a kivégzôosztagot válassza, miután elfogták?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Ne higgye, hogy hagyják, hogy csak úgy kihajózzon innen, de Maure kapitány. Mindketten nyakig benne vagyunk.";
			link.l1 = "A fenébe, valószínûleg igaza van. Az a korvett ránk zuhan, amint horgonyt vetünk...";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "A hollandok talán tudják, hogy jövünk, de nem tudják, hogy *hogyan* jövünk. Az álcázásról már gondoskodtunk - nézd meg ezt az egyenruhát. Csodás, nem? Ha nem árulták volna el a tervünket, egyszerûen csak elmentünk volna a helyi börtönbe, megleptük volna ôket, és mindenkit megöltünk volna odabent. De ott bizonyára lesben állnak. Így hát improvizálunk\nCaptain, elmegyünk Philipsburg templomába, és ott találunk egy Filippe Jacobsen nevû prédikátort. Reggel hattól tízig ott kell lennie. Filippe az egyik belsô emberünk\nmondja meg neki ezt a jelszót: 'Mióta gyóntak a fogságban lévô matrózok?'. Utána mondja el neki a helyzetet, és kérje a segítségét Fox ezredes nevében. Ezután a válaszát átadod nekem. Egyszerû és nem jelent kockázatot önnek.";
			link.l1 = "Átkozottul kockázatosnak hangzik gyónásról kérdezni egy holland kálvinista templomban, hadnagy. A lelkész megpróbálna felakasztani, mert pápista vagyok. Rendben, meséljen ezekrôl az egyenruhákról... egy holland ôrjáratról szedte le?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Igen, uram.";
			link.l1 = "És hol vannak most?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Túszként tartják fogva ôket a bokrokban, nem messze ettôl a barlangtól.";
			link.l1 = "Értettem. Vigyázzon rájuk, én a városba megyek. Várjatok meg itt, és maradjatok lent - a hollandok a dzsungelt és a tengert is átfésülik, és titeket keresnek.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "Csendben leszünk, mint a templom egere, kapitány. Kérem, siessenek!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Visszajöttél? Kapitány, mit keres itt? Menj a városba, felhívod a figyelmet a rejtekhelyünkre!";
			link.l1 = "Visszajöttem a városból. Miféle játékokat játszanak maguk angolok?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "Tessék?";
			link.l1 = "Elmentem a templomba. Nagy épület, szép és szigorú, pont olyan, amilyennek a holland ikonosztázok szeretik. Tudja mit, hadnagy? Nincs olyan prédikátor, akit Filippe Jacobsennek hívnak.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "Az lehetetlen, minden reggel meglátogatja ezt a helyet...";
			link.l1 = "Fogd be és figyelj rám! Ha a maga Jacobsenje egyáltalán létezik, akkor nem jár templomba! Soha nem látták ôt! Sem reggel, sem este! A kurva életbe! Miért egyeztem bele ebbe a kibaszott munkába?! Egy hülye kurva, zöldfülû, idióta, fülig érô idióta hadnagy vezetésével...";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Uram, elégtételt követelek ezért a sértésért. Miután kijutottunk innen, párbajozni fogunk a szokásoknak megfelelôen...";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "Fogjátok be a pofátokat mindannyian!!! ... Most hallottam valamit.";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "Swounds, valaki van odakint! Te! Te hoztad ide a hollandokat, te gazember!";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Örülök, hogy látom uram, mi újság?";
			link.l1 = "Találkoztam az embereddel. Ma este némi 'ízesített' bort fog szállítani a börtönôrségnek. Egy cigánytól kapott valami bájitalt, nem halálos, de úgy fognak aludni, mint a holtak. Még ma éjjel be kell mennie, és ki kell hoznia a foglyul ejtett urakat. Egyébként ez a borszállítmány huszonöt dublonnába került nekem. Ezt feltétlenül említsd meg a jelentésben.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "Ne aggódj a pénz miatt. Kapitány, arra kérném, hogy csatlakozzon hozzánk ebben az akcióban, és mutassa meg az utat a börtönhöz. Ön már járt Philipsburgban, így jobban ismeri a várost, mint mi. Nem kell velünk jönnie a börtönbe, a szökést mi magunk fogjuk végrehajtani. Csak vigyél minket az ajtóhoz.";
			link.l1 = "A fenébe a szememmel, Mr. Gretton, ez a munka egyre jobb és jobb lesz. Remélem, a fizetés is arányosan emelkedik.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "Az biztos, kapitány. Nem fogja megbánni, hogy segít nekünk. A hajója a Grand Case Beach-en van?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Igen.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "Nem.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Igen. Akkor készüljön, és találkozzunk a város kapujánál este tizenegy órakor.";
			link.l1 = "Ott találkozunk.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Ne felejtsék el oda vinni a hajót, mert az embereinket ki kell juttatnunk a dzsungelen keresztül. A kikötôbôl vagy a Simpson-öbölbôl nem lehet kihajózni az erôd miatt. Készítsenek elô mindent, és este tizenegy órakor találkozzunk a város kapujában.";
			link.l1 = "Ott találkozunk.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "Készen áll, kapitány?";
			link.l1 = "Igen.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "Akkor induljunk.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Hushhhh... Kapitány! Végeztünk, tûnjünk innen a pokolba!...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "Nem tudom, hogy csináltuk, de megcsináltuk! Semmi sem lett volna lehetséges az ön segítsége nélkül, "+GetAddress_Form(NPChar)+". Most jön a viszonylag könnyû rész - élve és egyben kell kijutnunk Sint-Maartinból. Irány a Grand Case Beach!";
			link.l1 = "Gyerünk, mozgás!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = ""+pchar.lastname+" kapitány... "+GetAddress_Form(NPChar)+", köszönöm a segítségét! Kérem, ne hagyja el azonnal a kikötôt, hanem maradjon itt még egy napig, amíg jelentést teszek Fox ezredesnek. Holnap látogassa meg, az irodája a kormányzói palotában van.";
			link.l1 = "Rendben, Gretton hadnagy. Kérem, tegyen róla, hogy megérje. Hosszú idôbe fog telni, mire helyrehozom a hírnevemet a hollandoknál az ön szökése miatt.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Köszönjük a segítségét, kapitány! Ön "+GetSexPhrase("igazi hősként viselkedett","nagyon bátor fiatal hölgy")+", "+GetAddress_Form(NPChar)+"! Tragédia, hogy Gretton hadnagy nem élte túl. Igazi úriemberként és Anglia fiaként halt meg. Kérem, maradhatok még egy napot, amíg jelentek Fox ezredesnek. Látogassa meg holnap, az irodája a kormányzói palotában van.";
			link.l1 = "Rendben van. Kérem, tegyen róla, hogy megérje. Hosszú idôbe fog telni, mire helyrehozom a hírnevemet a hollandoknál az ön szökése miatt.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Ne aggódjon, "+GetAddress_Form(NPChar)+". A lehetô legnagyobb elismerést fogom adni önnek a jelentésemben. (üdvözöl) Örömömre szolgált, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Kapitány "+GetFullName(pchar)+"?";
			link.l1 = "Hm... Igen, mit tehetek önért?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "A kikötôi hivatal tájékoztatott minket a hajójuk nemrégiben történt érkezésérôl. Ôexcellenciája Mynheer Martin Thomas, Philipsburg kormányzója látni kívánja önt.";
			link.l1 = "Miért? Le vagyok tartóztatva?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "Ó, nem, nem, nem, "+GetAddress_Form(NPChar)+" kapitány, ön nincs letartóztatva. A kormányzó elrendelte, hogy minden újonnan érkezett kapitányt meghívjon a palotájába egy kávéra és bemutatkozásra. Kövessenek!";
			link.l1 = "Úgy hangzik, mint egy visszautasíthatatlan ajánlat. Menjetek elôre.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", mutassa meg, hol látta ezeket az angol katonákat.";
			link.l1 = "Egy barlangban bujkálnak a dzsungelben, mint a közönséges banditák.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Menjetek elôre, követünk titeket!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "Várj, kapitány! Említetted, hogy ott találkoztál a kémekkel - a barlang bejáratához közel?";
			link.l1 = "Igen. Rövid ideig láttam ôket bemenni, miután beszéltek velem.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "Valószínûleg még mindig ott vannak. Ha egyszerre támadunk, akkor a barlangba húzódnak vissza. Rémálom lesz onnan elôkeríteni ôket... Játsszunk okosan. Kapitány, menj oda egyedül és tereld el a figyelmüket. Én és az embereim a sarkon lévô száraz kúthoz megyünk. Az egyenesen a barlangba vezet. A rohadékok nem fogják észrevenni, hogy hátulról jövünk\nTe bemész, és ha a kémek még mindig ott vannak, beszélgetsz velük, hülye kérdéseket teszel fel nekik, és lefoglalod ôket. Ha már abszolút a figyelmüket élvezed - káromkodj olyan mocskosan, amennyire csak tudsz. Tengerész vagy, úgyhogy ez természetesnek kell lennie számodra. Ez lesz a jelünk. Két emberem fogja ôrizni a fôbejáratot, hogy megakadályozza a szökésüket. Elkapjuk ôket.";
			link.l1 = "A terve szörnyen veszélyesnek hangzik az egészségemre nézve. Ahogy én látom, elôbb megpróbálnak megölni engem.";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Ne aggódjon, kapitány. A célod az, hogy olyan hangosan kiabálj, ahogy csak tudsz, amint meglátod az ellenséges rajtaütô csapatot. Ha megtámadnak - akkor fuss és kiabálj tovább. Az embereim jól képzettek, úgyhogy ne aggódj, le fogják szedni ezeket a kémeket, mielôtt neked baja esne.";
			link.l1 = "Jobb is lenne nekik. Megyek befelé.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "Kemény fattyúk voltak... Szép munka, kapitány, az angol kutyákat kiiktattuk. A szabotőröket kiiktatták, a parancsnok és a kormányzó elégedettek lesznek.";
			link.l1 = "Nem sietted el a dolgot, mynheer...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "A kötelet hibáztatom, egy vödör volt a végén, ami nagy zajt csapott. Óvatosnak kellett lennünk.";
			link.l1 = "Igen... a kötél. Mindegy. Az egyik eltûnt ôrjáratod ott van megkötözve a bokrok között. Még mindig életben kellene lennie.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "Majd én megnézem ôket. Menjetek a városba, és pihenjetek egy kicsit. Holnap látogasson el a kormányzóhoz, addigra megkapja a jelentésemet, amiben egy dicsérô dicséretet fog írni magáról.";
			link.l1 = "Majd én. Isten éltessen, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "Mit tehetek érted, fiam?";
			link.l1 = "Üdvözlöm pásztor, csak kíváncsiságból, mikor vallottak a fogságban lévô matrózok?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Tegnap este a fiam... (suttogás) Gondolom, tudja, hogy a terv elárulták?";
			link.l1 = "Különben nem állnék itt. Casper Gratton hadnagy és az emberei jelenleg a dzsungelben vannak. Mindannyian holland katonának vannak öltözve, de szükségünk van extra segítségre, mivel a börtönôrök már várnak rájuk.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(hangosan) imádkoztam minden nap, hogy megmentsem az anglikán lelkét a kárhozattól! (suttogás) Van egy tervem, de két tucat aranydublonra van szükségem, hogy mindent megszerezzek, amire szükségem van.";
			link.l1 = "Drága terv. Mire kell a pénz?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Börtönôrnek lenni unalmas kötelesség. Hogy fenntartsák a morált, a vezetô tiszt minden este rendel egy kis bort a vacsorához. A bort egy raktárból hozzák, amihez hozzáférésem van. Van egy cigányasszony a városban, aki az adósom, ô majd készít nekünk altatót. Csak néhány üveg jó bort kell vennem, hozzáadni a bájitalt, és kicserélni az üvegeket a raktárban. Ezért van szükségem az aranyra.";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "A dublonok nálam vannak. Vedd el.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Hadd menjek vissza a hajómra, és hozzak neked is.";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Ah fiam, nálad van az 'adomány' , amirôl beszéltünk?";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Igen, itt van.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Hamarosan megszerzem...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "Nagyszerû. Holnap ugyanekkor gyere el hozzám - elmondom az eredményt.";
			link.l1 = "Rendben...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Üdvözletem, fiam.";
			link.l1 = "Neked is, lelkész úr. Van valami hír?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Igen. Megtörtént. A bor 'ízesített' és az ôrök különleges élvezetet kapnak ma este. Este kilenckor vacsoráznak, éjfélre mind aludni fognak. Ez az egyetlen lehetôséged, hogy elvégezd a munkát, nincs második esély. Légy óvatos, nem hagyatkozhatsz teljesen a holland álruhádra.";
			link.l1 = "Megvan. Ne vesztegessük az idôt. Viszlát.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
