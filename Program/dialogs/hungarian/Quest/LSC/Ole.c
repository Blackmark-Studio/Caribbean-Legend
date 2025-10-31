// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "Oups... Szervusz, bácsikám! Van egy fehér gyöngyöd? Add ide a fehér gyöngyöt...";
			link.l1 = "Hm. Szép napot. Te vagy... a Fehér Fiú?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "Gyöngy! Fehér gyöngyöt a fehér fiúnak! Van fehér gyöngyöd, bácsikám?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hm, nincs gyöngyöm, de ezt a gyöngyöt odaadhatom. Fehér, és olyan, mint a gyöngy. Nem bánod?";
				link.l1.go = "store_2";
			}
			link.l2 = "Nem, nincs gyöngyöm, se fehér, se piros. Nem vagyok olyan lány vagy indián, aki gyöngyöt visel. Mondd csak...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "Gyöngy! Fehér gyöngy! Nincs gyöngy - nincs beszéd. Rossz nagybácsi... Adj egy gyöngyöt!";
			link.l1 = "A francba! Micsoda ôrült fickó! Kígyószemnek és Chimisetnek igaza volt - gyenge fejû... Milyen gyöngyre van szüksége?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "Adj egy gyöngyöt, bácsikám. Jó bácsikám... Fehér gyöngyöt!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Tessék, itt a gyöngyöd. Ezt akarod?";
				link.l1.go = "store_2";
			}
			link.l2 = "Ó, a fenébe...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Igen, igen! Ez az! A bácsi adott egy gyöngyöt! Köszönöm, jó ember! Most Ole-nak van még egy gyöngye. Hamarosan meglátogatom a mamát...";
			link.l1 = "Örülök neked. Nos, beszélhetnénk most?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "Persze, jó ember. Jó ember vagy, bácsikám? Barátok leszünk. Ole szívesen beszélgetünk. Hogy hívnak?";
			link.l1 = "A nevem "+pchar.name+". Ole, egy ember mesélt nekem rólad, és ô már nincs itt. Azt mondta, hogy te segítettél neki, és te is tudsz nekem segíteni.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "A bácsi adott egy gyöngyöt Ole-nak - ô egy jó bácsi. Ole szeret segíteni a jó embereken. Nincs sok jó ember - rossz bácsik vannak mindenfelé. Segítek neked, persze. Szeretek segíteni.";
			link.l1 = "Szép volt! Nos, most már barátok vagyunk. Ole, mondd csak, emlékszel egy vörös bôrû emberre, akinek gyönyörû tollas kalapja volt? Azt mondta nekem, hogy te mentetted meg ôt régen.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "Emlékszem arra a bácsikára. Ô egy jó ember. Én mentettem meg. Elvittem a szoborhoz. És nemrégiben egy másik jó embert is megmentettem a rakterembôl az étellel. Megmentettem ôt a rossz admirális bácsikájától. Megölték volna. Ôt is el akartam vinni a szoborhoz, de visszautasította. Teljesen.";
			link.l1 = "A raktérbôl? Heh, azt hiszem, tudom, hogy kire gondolsz... És ismerem ezt a nagybácsit. Mondd, Ole, ki az az ember, akit megmentettél?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "A neve Nathan bácsi. Beteg, nagyon-nagyon beteg. Alig tudott járni, amikor Ole rátalált.";
			link.l1 = "Persze... Furcsa, hogy egyáltalán képes volt rá.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "Nem, ez nem furcsa. Megtaláltam és adtam neki egy kis tûz rumot. Beúsztam a lyukba, mert azon a hajón van étel. A rossz emberek bezárják az ajtót, de én mindig kinyitom. Hé, hé, hé... Buta rossz emberek. Tudom, hogy csalogatják a rákokat. Rossz emberek\nOdaértem és megtaláltam Nátánt. Nem érezte jól magát. Volt nálam tûz rum - adtam neki inni, így jobban lett. Aztán beadtam neki a tinktúrát, abból mindig hordok magamnál egyet, arra az esetre, ha félelmetes rák harapna Ole. A jó Chimiset bácsi mondta, hogy ezt tegyem...";
			link.l1 = "Adtál neki ellenszert és rumot? Heh, nem is vagy olyan bolond, mint ahogyan mindenki gondolja. Szép munka, Ole.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "A gonosz nagybácsik bolondnak tartják Ole-t, és ugratják ôt: Ole a bolond... Ole nem bolond, csak össze kell gyûjtenie az összes fehér gyöngyöt, különben az anyja elküldi. Adsz nekem még egy gyöngyöt késôbb?";
			link.l1 = "Hm... Persze, Ole, barátok vagyunk. Mondd csak, hogy akartad elküldeni Hawk... Nathan bácsit a szoborhoz? Chimiset bácsi azt mondta, hogy a hajóval együtt elsüllyedt...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "A szobor az alján van. Ole tudja. De nincs mélyen, és Henrik bácsi el tudja küldeni oda Nathan bácsit. Henrik bácsi tudja, hogy kell a víz alatt járni. De ott van egy csomó ijesztô rák. Ole fél tôlük. Fájdalmasan harapnak.";
			link.l1 = "Henrik bácsi? Ki az a Henrik?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "Henrik bácsi a gonosz Narwhals bácsik között él. Mindenki ismeri ôt. Tud a víz alatt járni, és megtanítja a narvál bácsikat, hogyan kell merülni. Henrik bácsi kedves, fehér gyöngyöt adott Ole-nak.";
			link.l1 = "És hogy engednek be a narválok? Vagy a területük nyitva áll elôtted?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "Tee-hee... A gonosz bácsik nem engedik be Ole-t, de Ole éjjel bemehet a hajóik bármelyik szobájába. Nagyok és zajosak, de Ole csendes és óvatos. Henrik bácsival pedig akkor találkoztam, amikor körbeúsztam a hajót, amelyrôl Henrik bácsi szokott lemerülni. Henrik bácsi adott egy fehér gyöngyöt Ole-nak, és most már barátok vagyunk.";
			link.l1 = "Érdekes... Én is szeretnék Henrik bácsi barátja lenni.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "Akarsz búvárkodni és elmenni a szoborhoz? Ott van, a régi hajótörésnél. Sok nagy és ijesztô rák van ott. Nem félsz tôlük? Meg tudnak harapni.";
			link.l1 = "Nem, nem félek tôlük. Egyet már megöltem, úgyhogy jobb, ha félnek tôlem.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "Ó, "+pchar.name+" nagyon bátor! Akkor menj Henrik bácsihoz, ô majd megtanít, hogyan kell a fenéken járni, és ott minden rákot megölsz. Ott is találsz még egy nagy gyöngyöt Ole-nak. ugye?";
			link.l1 = "Persze, hogy fogok. De elôbb meg kell találnom Henrik bácsit.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "És miért kell ôt megtalálni? A 'San Gabriel', nevû hajón él a mûhelyben. De a gonosz narvál bácsik nem biztos, hogy szívesen látnak.";
			link.l1 = "A gonosz bácsikkal majd én magam foglalkozom. És az utolsó kérdés, hol van most Nathan bácsi? Ôt kerestem, és ô az oka annak, hogy itt vagyok.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "Nathan bácsit a szentélyemben rejtegetem a 'Fernanda'. messze van, és senki sem lakik ott. Mindenki azt hiszi, hogy hamarosan elsüllyed, de Ole az ellenkezôjét tudja. Megmentettem Nátán bácsit, és odavittem\nMég mindig nagyon beteg, és állandóan tûz rumot iszik. Alig tud járni, és képtelen öt kilónál nehezebb dolgokat felemelni. Sajnálom Nathan bácsit, ládákból hozok neki tûz rumot és ételt az admirális rossz embereinek rakterébôl. Megfôzöm neki a patkányokat is, amiket én fogok. Nagyon finom patkányokat!";
			link.l1 = "Ízletes patkányok? Értem. Szóval Nathan azon a hajón van, amit... hogy is mondtad - a 'Fernanda'? Nem ismerem...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Bácsi "+pchar.name+", az elôbb mondtam, hogy nincs messze innen. Úszva kell eljutnod hozzá. Van egy ajtó a háta mögött, de Nátán bácsi nem nyitja ki. Ole mondta neki, hogy ne tegye. De ha Nátán bácsi barátja vagy, akkor elmondom, hogyan kell kinyitni. Kopogj az ajtón így: kop-kop... kop-kop... kop-kop. Akkor majd kinyitja.";
			link.l1 = "Emlékezni fogok rá. Köszönöm, Ole! Nagyon sokat segítettél nekem! Nem is tudom, hogyan köszönjem meg rendesen.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "Hozz nekem még egy fehér gyöngyöt. Ha megtalálod, természetesen.";
			link.l1 = "Ó, igen! Fehér gyöngyök! Jól van. Viszlát, Ole!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "Ah, bácsikám "+pchar.name+"! Örülök, hogy látlak! Hogy vagy?";
			link.l1 = "Köszönöm, Ole, jól vagyok. Én is örülök, hogy látlak.";
			link.l1.go = "exit";
			link.l2 = "Figyelj, Ole, azt mondtad, hogy az admirális kalózok bezárják a raktér ajtaját, te pedig mindig kinyitod... Minden láda zárva van, és azt mondtad, hogy rumot veszel tôlük Nathan bácsinak. Hogy tudod ezt megtenni?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "Ole-nak van egy szép kulcscsomója. Bármelyik ajtót vagy ládát kinyitják. Hát, nem mindet. Néhányat nem lehet kinyitni, de a legtöbbet igen. Ole a gonosz Jürgen bácsi kunyhójában találta. Minden nap a kalapácsával dolgozik a kemencéje mellett. Zárakat és kulcsokat készít. És nagy és félelmetes muskétákat is készít a gonosz narváloknak.";
			link.l1 = "Értem. Ole, el tudod adni nekem azokat a kulcsokat? Ki tudom fizetni ôket...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "Rendben, bácsikám "+pchar.name+", eladom neked a kulcsokat. Csak az egyiket hagyom meg magamnak. Ez nyitja az admirális szobáját. Van egy csomó étel és rum Nathan bácsinak. A ládákban amúgy sincs már több gyöngy és rum.";
			link.l1 = "Mennyit kérsz értük?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "Elôször is, mondd, bácsi "+pchar.name+", van egy nagy hajód?";
			link.l1 = "Igen, van. De nincs itt, a külsô gyûrûnél van. De hamarosan elhagyom a szigetet, és visszajövök ide a nagy hajómon Nathan bácsinak.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "Nathan bácsinak? Ó, ez csodálatos! Figyelj, akkor ígérd meg, hogy elviszel innen a nagy hajódon, és hagyod, hogy veled hajózzak, amíg szükségem van rá. Hasznos lehetek. Tudok patkányokat fogni és fôzni... És adj nekem öt fehér gyöngyöt is. És odaadom neked a kulcsokat.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Persze! Itt vannak a gyöngyök. Fogd ôket.";
				link.l1.go = "lock_4";
			}
			link.l2 = "Patkányokat fogni és fôzni? Heh! Érdekes képesség. Persze, Ole, megegyeztünk. Hozok neked öt gyöngyöt és a szavamat.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "Ah, bácsikám "+pchar.name+"! Örülök, hogy látlak! Hogy vagy?";
			link.l1 = "Köszönöm, Ole, jól vagyok. Én is örülök, hogy látlak.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Hoztam neked öt fehér gyöngyöt a kulcsaidért.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "Gyöngyök! Fehér gyöngyök! A "+pchar.name+"  bácsi gyöngyöket adott Ole-nak! Hamarosan találkozunk, anya!... Bácsi "+pchar.name+", megígéred, hogy elviszel innen, ha visszajössz?";
			link.l1 = "Igen, Ole. Még nem ettem patkányt. Magammal viszlek.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "Köszönöm, köszönöm, jó bácsi "+pchar.name+"! Fogd a kulcsaidat. Könnyû használni ôket, csak tedd be ôket egyesével és próbáld ki. Egyikük végül kinyitja a zárat, amire szükséged van. Ha nem, akkor a zár túl trükkös, és mindenképpen szükséged lesz egy speciális kulcsra.";
			link.l1 = "Értem. Gondolom, majd én elintézem.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "Várj, bácsikám "+pchar.name+"! Van még egy kulcsom. Szép és okos. A gonosz Jürgen bácsi nem csinál ilyen kulcsokat. Nem tudom, hogy mit nyit, de talán te rájössz. Nézd, ez egy nagyon szép kulcs, biztosan nem láttál még ehhez hasonlót.";
			link.l1 = "Mutasd meg... Igen, a kulcs nagyon érdekes. De mit ér, ha nem tudod, mit lehet kinyitni vele?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Bácsikám "+pchar.name+", , , nagyon furcsa vagy. Mi értelme? Ha van kulcs akkor valahol a zár. Ha ott a zár, akkor valahol az érme. Én megtaláltam a kulcsot a szigeten. Ez azt jelenti, hogy a zár is itt van. Efelôl nincs kétség. Ez egy okos kulcs, és csak nagyon értékes tárgyakat lehet ilyen kulccsal zárni. Ole tudja.";
			link.l1 = "Ôszintén szólva, vicces vagy, Ole. Rendben, megveszem. Akarsz érte gyöngyöket?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "Igen, Ole öt gyöngyöt akar. Odaadod ôket, bácsikám "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Tessék, itt vannak a gyöngyök.";
				link.l1.go = "key";
			}
			link.l2 = "Nincs nálam, de biztosan hozok neked gyöngyöket.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Gyöngyök! Fehér gyöngyök a fehér fiúnak! Az anyukájának! Tessék, bácsi "+pchar.name+", fogd a kulcsot. És meg fogod találni a zárat, Ole tudja. Bátor vagy, még a félelmetes rákoktól sem félsz.";
			link.l1 = "Ó, ne nevettess, Ole! Köszönöm a kulcsot. Még találkozunk!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "Ah, bácsikám "+pchar.name+"! Örülök, hogy látlak! Hogy vagy?";
			link.l1 = "Köszönöm, Ole, jól vagyok. Én is örülök, hogy látlak.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Hoztam neked öt fehér gyöngyöt a kulcsodért.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "Ah, bácsikám "+pchar.name+"! Örülök, hogy látlak! Hogy vagy?";
			link.l1 = "Köszönöm, Ole, jól vagyok. Én is örülök, hogy látlak.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "Ó, bácsi "+pchar.name+", visszatértél! Visszatértél a nagy hajóra! Elviszel innen? Bácsikám "+pchar.name+", megígérted nekem, emlékszel?";
			link.l1 = "Persze, Ole. Isten hozott a fedélzeten! Gondolom, a patkányok bajban vannak, ha-ha!";
			link.l1.go = "return_1";
			link.l2 = "Tényleg? És mikor ígértem meg neked? Nem emlékszem ilyen ígéretre...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "Köszönöm, bácsikám! Ole hasznos lesz, majd meglátod! Ó, talán meglátogatom anyát? Már úton vagyok!";
			link.l1 = "Ne siess így, Ole. Pakold össze a cuccaidat. Nem fogok azonnal elhajózni.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "Megígérted nekem, megígérted! Megígérted, hogy elviszed Ole-t innen! Gonosz nagybácsi! Átverted Ole-t! Rossz nagybácsi!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "Bácsikám, bácsikám... Kell még egy fehér gyöngy. Kérlek, adj egy fehér gyöngyöt Ole-nak!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Tudtam, hogy kérni fogod. Tessék, vedd el a gyöngyödet. Elégedett vagy?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Ó, és milyen idegesítô... Nincs több gyöngyöm, Ole, nincs!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "Köszönöm! Jó, jó bácsi "+pchar.name+"! Ole még egy gyöngyöt kapott, és már nem sok gyöngy maradt! Én meg megyek az anyukához...";
			link.l1 = "Ó, és miért vagy ilyen furcsa...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "Köszönöm a gyöngyöt, jó bácsi "+pchar.name+"!";
			link.l1 = "Szívesen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "Nincs gyöngy? De hogy is van ez, bácsikám "+pchar.name+"?! Már csak néhány gyöngy maradt... Össze kell gyûjtenem ôket. Abban az esetben leszállok. Gyöngyöket fogok keresni...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "És hová mész? Mit fogsz csinálni egyedül? Nem, nem akarok felelôs lenni a sorsodért. Várj, megnézem a zsebeimet... Tessék! Fogd a gyöngyödet és maradj velem. Elégedett vagy?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Ez a te jogod, Ole. Ha unod, hogy velem hajózz, akkor nem foglak megállítani. Megegyeztünk. Azért jól elkaptad azokat az árakat...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "Búcsúzz el, bácsikám "+pchar.name+". Ole-nak fehér gyöngyökre van szüksége, különben soha nem tér vissza az anyjához...";
			link.l1 = "Ó, annyira sajnálom, de mit tehetnék? Menj, Ole. Sok szerencsét, Ole.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Bácsi "+pchar.name+"! Kell még egy fehér gyöngy. Az utolsó. Kérlek, add oda Ole-nak!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Tudtam, hogy kérni fogod. Tessék, vedd el a gyöngyödet. Elégedett vagy?";
				link.l1.go = "mother_1";
			}
			link.l2 = "Ó, és milyen idegesítô... Nincs több gyöngyöm, Ole, nincs!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Köszönöm, köszönöm, jó bácsi "+pchar.name+"! Most Ole-nál van az összes gyöngy. Igen, az összes! Most már Ole elviheti ôket anyunak, és ô nem fogja elküldeni Ole-t...";
			link.l1 = "Figyelj, ki az az anya, akirôl mindig beszélsz? És magyarázd meg végre, miért van szükséged azokra a gyöngyökre... fehér gyöngyökre? És mit jelent az, hogy mind megvan?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "A jó bácsi "+pchar.name+" segített Ole-nak gyöngyöket gyûjteni a mamájának... Ole még kicsi volt, amikor elszakította a mama fehér gyöngyökbôl álló nyakláncát. Mind a vízbe hullott. A mama nagyon megharagudott Ole-ra, és addig nem mehet haza, amíg össze nem gyûjti az összes elveszett gyöngyöt\nEmlékszem, mennyi volt belôlük. Ötször tíz gyöngy. Most Ole-nál van az összes. Bácsi "+pchar.name+", kérlek, vigyél haza! Boldoggá akarom tenni a mamát, visszaadni a gyöngyöket. Vigyél haza!";
			link.l1 = "Jézusom, micsoda hihetetlen történet... Gyerekként jutottál el a Szigetre. Elüldöztek a tiédtôl, mert elszakítottad anyukád gyöngynyakláncát? Hátborzongató...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "Vigyél el anyukámhoz, jó bácsi "+pchar.name+". Látni akarom ôt. Örülni fog, ha gyöngyöket lát.";
			link.l1 = "Szeretnék, de tudod, hol van az otthonod? Hol lakik az édesanyád?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "A szigeten lakik, a piros tetejû házban.";
			link.l1 = "Tényleg? Tudod egyáltalán, hány sziget van itt, és hány piros tetejû ház van rajta? Mi a neve annak a szigetnek? Mondd el a részleteket...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "Nem tudom a nevét. Azt tudom, hogy egy sziget volt, mama azt mondta apának, hogy a szigeten voltunk! És a piros tetejû házban laktunk. Szép ház, egy nagy ház. Vigyél el anyához, bácsi "+pchar.name+". Kérlek...";
			link.l1 = "Ó, rendben. Minden szigeten keresni fogunk egy ilyen házat, és megkérdezzük anyádat. Hogy hívják?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "A neve? Olyan furcsa vagy, bácsikám "+pchar.name+". Anyám neve anya. A te anyádat máshogy hívják?";
			link.l1 = "Ó, Istenem, kérlek, küldj egy kis türelmet... Jól van, Ole. Megpróbáljuk megtalálni az otthonodat. Most menj a hajóra.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "Köszönöm, bácsi "+pchar.name+". Nagyon, nagyon kedves és jó vagy! Hamarosan Ole meglátogatja anyát!";
			link.l1 = "Ó...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "Anya... Anya, anya! Visszajöttem!";
			link.l1 = "Fiam...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "Mama, hoztam neked fehér gyöngyöket! Mindet összegyûjtöttem! Újra lesz egy nyakláncod. Még mindig haragszol rám?";
			link.l1 = "Istenem...(sír) Ole! Fiam, miért? Miért mentél el? Nem érdekelnek azok a gyöngyök!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "Mama, tessék... fogd ôket. Már régóta gyûjtöm ôket. A jó bácsik segítettek nekem, különösen a "+sld.name+"bácsi. Elvitt a nagy hajóján, segített a gyöngyök gyûjtésében, és hazahozott...";
			link.l1 = "Ole... Te tényleg felnôttél, de még mindig gyerek vagy... Hadd öleljelek meg, fiam! Sajnálom, kérlek, bocsáss meg nekem azért az átkozott nyakláncért! Soha nem hagylak magadra, soha! Együtt fogunk élni, és én törôdni fogok veled... Megbocsátok, ígérem!";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "Mama, hiányoztál... Veled akarok maradni. Még mindig haragszol rám? Miért sírsz?";
			link.l1 = "(sírva) Nem, nem... Annyira sajnálom, kérlek bocsáss meg, fiam!...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Bácsi "+pchar.name+"! Olyan jó, hogy eljöttél! Köszönöm, hogy elhoztál anyukámhoz. Olyan jó itt lenni vele... Ugye milyen jó itthon lenni, nem igaz, bácsi "+pchar.name+"?";
			link.l1 = "Miért sírsz? Ole. Ez az. Örülök, hogy boldog vagy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Figyeljen, jobb, ha elveszi a fegyverét. Ideges leszek tôle.", "Tudod, a pengével való rohangálást itt nem tolerálják. Vidd el.", "Figyelj, ne játszd a középkori lovagot, aki karddal rohangál. Vidd el, nem illik hozzád...");
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérnélek, hogy tartsd vissza a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, haver, amikor fegyverrel futsz. Ideges tudok lenni...", "Nem szeretem, ha a férfiak fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
				link.l1 = RandPhraseSimple("Megvan.", "Elviszem.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
