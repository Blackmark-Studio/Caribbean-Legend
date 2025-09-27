// диалоги персонажей по квесту Долго и счастливо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			dialog.text = "Mire van szükséged?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "Monsieur de Maure, micsoda szerencse! Hónapok óta keresem önt!";
			link.l1 = "Kedvesem, én nem veszek hamis térképeket, kétes információkat és házi készítésû rumot - köszönöm! Vagy maga fejvadász? És mennyit kérnek most a fejemért?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Ó, uram, én... Én nem kereskedem ócskasággal és nem ölök embereket - ne nyúljon a kardhoz, nem lesz rá szüksége, nem akarok rosszat! Minden sokkal prózaibb - egy futárhajó kapitánya vagyok. Postát osztogatok. És neked fontos levelet hoztam!";
			link.l1 = "Egy levél? Ki a feladó, ha megkérdezhetem?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Egy apát adta át nekem, és megkért, hogy személyesen, kézrôl kézre adjam át de Maure kapitánynak. Már minden reményemet elvesztettem, hogy megtalálom önt, és a Saint Pierre-i kikötôi hivatalban akartam hagyni, de micsoda szerencse - itt van!";
			link.l1 = "Igen, itt vagyok, várom - adja ide a levelet.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Van egy kis gond... Az apát úr azt mondta, hogy a kézbesítést a címzett fizeti. Tehát kilencezer-kétszáz pezó az öné.";
			link.l1 = "Ennyi pénzért a nyílt tengeren kellett volna elhozni nekem egyenesen a kabinomba, a reggeli kávéval együtt! A levelet meghagyhatja magának.";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "És miért nem postai kézbesítést végeztem! Ez jövedelmezôbb, mint a kalózkodás! Itt van az ezüstje, kedvesem, adja ide a borítékot!";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "Örülök, hogy üzletet kötöttem önnel! Benoit apát úr a legjobb kívánságait küldi Önnek! Viszontlátásra, Monsieur de Maure!";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "Ahogy kívánja. A borítékot a kikötôi irodában hagyom. De ez hatással lesz az árra, figyelmeztetem. És igen - Benoit apát úr üdvözletét küldi.";
			link.l1 = "Benoit apát levele? Miért nem mondtad ezt már az elején! Biztos fontos lehet!";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "Akkor vegye fel a kikötôfônöknél. Ne felejtsen el elôre kölcsönt felvenni. Viszlát, de Maure kapitány.";
			link.l1 = "Ismertem nálad ôszintébb kalózokat. Sok szerencsét, kedvesem.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "Szentatya, ma korábban érkezett a szokásosnál. Kérem, a kísérete már vár. És ön, Senor de Maure - Vincento atya megtudta, hogy a városban van, és sürgeti, hogy csatlakozzon hozzá egy vacsorára.";
			link.l1 = "Attól tartok, az inkvizítor egyedül vacsorázik. Remélem, ettôl nem lesz rosszabb az étvágya. És Benoit apát is meg fogja fosztani a társaságától. Ön tudja, hogy ki vagyok, ezért ajánlom önnek. hagyja, hogy konfliktus nélkül menjünk el, és adja át üdvözletemet Palotti atyának.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				dialog.text = "Igen, sokat hallottam rólad, és világos utasításom van, hogy ne változtassuk vérfürdôvé a várost, ha megmakacsolod magad. Átmehetsz. De Vincento atya... elégedetlen lesz. Ezt tartsd észben.";
				link.l1 = "Ön ésszerûen cselekedett, monsieur. Túl fogom élni, valahogy, a szívemben lévô fájdalmat, amit az atya-inkvizítor elégedetlensége okozott. Kellemes estét!";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				dialog.text = "Igen, hallottam önrôl... sok érdekes dolgot. Az ilyen meghívások visszautasítása azonban veszélyes az egészségre, senor. Ahogy Vincento atya vendégeinek elrablása is. Tartsátok ôket!";
				link.l1 = "Mindenki meghozta a döntését. Sajnálom, hogy így alakult. Fegyverbe, caballero!";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, gratulálok! Tudod - mindig is kedveltelek, és Helénát úgy szerettem, mintha a lányom lennél, úgyhogy mindkettôtöknek örülök. A fenébe... egy könnycseppet ejteni egy templomban, ez minden, amire valaha is vágytam, öregszem vagy mi?";
			link.l1 = "Minden rendben van, Jan, majdnem elsírtam magam az oltárnál. Talán a füstölô miatt?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "Igen, kámfor, a fenébe is. Gondolkodtam - miért csíp a szemem és viszket az orrom! Jól van, beszélgetünk Sharptownban, megölelem Gladyst, és megyünk a többiekhez. Olyan arcot vágnak, mintha a westfáliai békét írnánk alá.";
			link.l1 = "Köszönöm, hogy eljöttél, Jan, örülök, hogy látlak, és ez sokat jelent Helennek.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Végre itt vagy, Charles! A corvette-em majdnem egy nappal megelôzött téged - ez elég büszkeségre ad okot.";
			link.l1 = "Szívesen, Jan, de hol van Gladys és a feleséged?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "Visszaküldtem Gladyst a Blueveldre egy kereskedelmi hajón - nem helyesli ezeket a fergeteges partikat. Joanna nem tudott megérkezni - ó, nem volt idôm elmondani neked Martinique-on! Képzeld csak el - öregkoromban törvényes apa leszek, mit szólsz hozzá? Nézd, ha sietsz, az utódaink majdnem egyidôsek lesznek, hahaha!";
			link.l1 = "Jan, gratulálok, ezek a jó hírek!!! Igyunk rá!";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "Határozottan! De elôször is, rád és a jobbik feledre! Hé, te ott, fogd be a szád!!! Az öreg erdei ördögnek beszédet kell tartania!\nKhe-khe... Szóval, kedves Monsieur és Madame de Maure... Baszd meg! Nem tudok így beszélni! Charles, Helen - ti ketten olyanok vagytok nekem, mint a saját gyermekeim, és tudom, hogy ebben a teremben nincs senki, aki ne örülne az egyesüléseteknek! Igyunk hát, Testvéreim, hûséges barátaink boldogságára, a szerencsés szélre a vitorláikban és Lady Fortune szerelmére, amely olyan erôs, mint az egymás iránti érzéseik!!! Egészségünkre!";
			link.l1 = "Egészségünkre! Köszönöm Jan... ó, ez a rum sokkal erôsebb, mint általában... Mit kevert bele Nathan?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "Fogalmam sincs, de úgy tûnik, hogy jogosan. Old Hawk általában szakértô az italok terén. Gyerünk, menjetek a többiekhez, nekem kell italt készítenem jó száz léleknek, akik mohón várják, hogy jóllakjanak.";
			link.l1 = "Az erdei ördög italokat töltöget - micsoda látvány! Köszönöm, hogy magadra vállaltad a buli szervezését. Mindenképpen visszajövök, amint mindenkit körbejárok - hátha, valakinek segítségre van szüksége.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "Minden rendben van, Charles?";
			link.l1 = "Tökéletes, Jan!";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "És itt vagy végre! Hogy ment Martinique-on? Úgy érzed, hogy örökre megváltozott az életed?";
			link.l1 = "Sokkal korábban megváltozott, Jan. De minden meglepôen jól ment. Hol van Joahnna és...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "Helen? A lány azonnal vitorlát bontott, amint megtudta, mire készülünk, és a horizont felé hajózott. Mindenféle meleg gratulációkat közvetített neked, de mégis... összetörted a szívét, ó, tényleg ezt tetted. Azonban minden rendben lesz, ez csak a fiatalság.";
			link.l1 = "Nos, a szív azt akarja, amit akar, ezt te is megérted.";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "De igen. Nos, Joahnna nem tudott megérkezni, képzeld csak el - öregkoromban törvényes apa leszek, mit szólsz hozzá? Nézd, ha sietsz, az utódaink majdnem egyidôsek lesznek, hahaha!";
			link.l1 = "Jan, gratulálok, ezek a jó hírek!!! Igyunk rá!";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "Határozottan! De elôször is, rád és a jobbik feledre! Hé, te ott, fogd be a szád!!! Az öreg erdei ördögnek beszédet kell tartania!\nCharles és Mary, az egész Testvériség most serlegeket emel a tiszteletetekre! Az igaz barátok boldogsága minden tengeri farkas lelkét gyönyörködteti, majdnem annyira, mint a spanyol arany pompája, ha-ha! Vitorlázzatok jól, és a szép szelek kövessenek benneteket családi utatokon!!! Egészségetekre!";
			link.l1 = "Egészségünkre! Köszönöm Jan... ó, ez a rum sokkal erôsebb, mint általában... Mit kevert bele Nathan?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "Fogalmam sincs, de srikes joggal. Az öreg Sólyom általában szakértôje az italoknak. Gyerünk, menjetek a többiekhez, nekem italokat kell készítenem jó száz léleknek, akik mohón várják, hogy jóllakjanak.";
			link.l1 = "Ezt a kocsmát mindenképpen át kell nevezni - 'Az erdei ördög maga állt itt a pult mögött'! Köszönöm, Jan, biztosan visszatérek, amint mindenkit megkerülök - talán, valakinek segítségre van szüksége.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "Hogy vagy, Charles? Hogy áll az esküvô?";
			link.l1 = "Nagyon szívmelengetô, Jan, örülök, hogy sikerült mindannyiunkat idehozni. Úgy tûnik, Hawk rumos hordói kezdik megmutatni a feneküket, nem igaz?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "Igen, így van! Szóval, itt az ideje, hogy kinyissuk, amit hoztál. És még valami - azok a srácok, akik elôször segítettek nekem, túlságosan berúgtak a hátsó szobában. Úgy tûnik, még talpon vagy, vôlegény - hoznál egy láda másik sherryt?";
			link.l1 = "Persze, csak mondd meg, hova menjek. Talán találok útközben néhány józan fejet, akik segítenek nekem. Bár a legtöbb emberem valószínûleg már úgyis részeg, mint a szar.";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "A bor a hajógyár alatti pincékben volt felhalmozva, emlékszel rájuk? Sólyom azt mondta, hogy tartsuk a távoli folyosón, 'hogy az ünnepekig megôrizzük' - mondja. Azt is mondja, hogy ott tökéletes a hômérséklet és a páratartalom, azt mondja, tökéletes hely lenne egy borospincének. Hát, ô egy nagy sznob.";
			link.l1 = "Jól döntött, Jan. Megyek, de elôbb mondd, láttad a feleségemet?";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "Ô és Dannie elmentek valahova. Hagyd a lányokat beszélgetni, Charles, és egy igazi partit kell indítanunk. Menjetek a pincébe, amíg én az étellel foglalkozom. Mert olyan szag van, hogy hamarosan szenet fogunk enni birkaborda helyett!";
			link.l1 = "Jól van, menjetek, tegyétek félre a húst, én hozom a bort.";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "Charles, Nathan, mi történt, részegen verekedni kezdtetek?!";
			link.l1 = "Nem, Jan, együtt harcoltunk néhány fegyveres vágó ellen a várbörtönben. Elbántunk velük, de ôk csak felderítôk voltak - a fôcsapat mögöttünk van!";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "Osztag? Mirôl beszélsz?! Marcus, gyere ide! Charles, gyerünk, mondj el mindent.";
			link.l1 = "Ahogy mondtam: van néhány szemétláda a hajógyár alatti börtönben. Jól felfegyverkezve. Nathan és én megküzdöttünk velük, és csodával határos módon mindenkit leterítettünk. De még többen vannak úton - hallottam, az egyiket segítségért küldték. És igen, az egyikük emlékezett néhány Jacques-ra.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "Felismerem az arcukat... ezt, és azt a szemetet, aki az ajtó mellett fekszik. Ôk Jacques, a Kindman gengszterei. Nem emlékszem a nevükre, de a nevüket biztosan tudom.";
			link.l1 = "Szóval ez Barbazon hibája? Elment az esze, vagy mi?!";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "Nem tudom, de úgy tûnik, a Kindman úgy döntött, hogy kihasználja az alkalmat, és radikális átrendezôdést rendez a Testvériség bárói között.";
			link.l1 = "Ebben az esetben remélem, hogy ô maga is megjelenik - álmodtam olyan régóta, hogy pár lyukat ütöttem a testén. Szemétláda, tönkretette az esküvômet, gondolj csak bele! Mozgás, irány az utcára! Megfelelô fogadtatásban részesítjük a vendégeinket!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "És itt van a mi fáradt hôsünk! Hah, Charles, ez volt valami! Jacques, micsoda patkány! Nézd, hogyan intézett el mindent - majdnem sikerült neki!";
			link.l1 = "Igen, valószínûleg meg kellett volna ölnünk azt a fattyút, amikor végeztünk Jackmannal. Azonban vége van. Barbazon halott.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "Hát, egyáltalán nem mondhatom, hogy vége - az életünk megy tovább! Bár én úgy érzem, hogy teljesen összetörtem. Túl öreg vagyok már ahhoz, hogy egy tûzzel borított szarból a tengerbe ugorjak, és egy egész órát ússzam a partig, cápák után kutatva. Remélem, még van egy kis rumunk...";
			else dialog.text = "Hát, egyáltalán nem mondhatom, hogy vége - az életünk megy tovább! A fenébe is, tíz évvel fiatalabbnak érzem magam! Régen volt már, hogy utoljára így küzdöttem! Remélem, a rum- és borkészleteidet nem lopták el a zûrzavar alatt - jól meg kell rá inni!";
			link.l1 = "Ja, én is innék, de elôbb meg kell néznem a rezidenciát, nem tudom, szóltak-e nektek vagy sem...";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "Az indiai fickóról van szó? Igen, hallottam, hogy történt?";
				link.l1 = "Felugrott, hogy megvédje a feleségemet és Dannielle-t egy golyótól, amit egy gazember lôtt ki. Mennünk kell, majd útközben elmondom.";
			}
			else
			{
				dialog.text = "Nathanrôl van szó? Igen, hallottam, csak nem értem, hogy történt?";
				link.l1 = "Azért ugrott, hogy megvédje a feleségeinket egy golyótól, amit egy szemétláda lôtt le. Mennünk kell, majd útközben elmondom.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Maradj erôs, Charles. Nagyon sajnálom a fiaidat. Ma sok jófiú ment el, és mindegyikükért a pokolban Barbazon több olajat fog kapni a kazánjába.";
				link.l1 = "Ennek semmi értelme... a fenébe is! Nehéz, Jan... Már elvesztettem a barátaimat, de nem tudok hozzászokni. Nem tudom, hogy tovább tudok-e élni.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Szóval az a csendes fickó-gyógyszerész? Sajnálom, Charles, ôszintén. Jó ember volt.";
					link.l1 = "Igen, Jan, én is. De attól tartok, a tudomány világa sokkal többet veszített, mint engem. Zseniális volt... kifinomult, mint mindannyian, de... bassza meg...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "az indiai fickó.";
					else sTemp = "Nathan";
					dialog.text = "Nos, úgy tûnik, ennek vége. Ma sok jó ember elment, és mindegyikükért a pokolban Barbazon több olajat fog kapni a kazánjába, de "+sTemp+" rendben lesz, és ez a lényeg.";
					link.l1 = "Igazad van, Jan, és ez nagy kô esett le a szívemrôl. Hogy van a többi báró? Jól vannak?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "Jacques Barbazon utolsó mocska. Igazad van, ha korábban megöltük volna, minden másképp alakulhatott volna.";
			link.l1 = "De mi értelme a múltat sajnálni? A múlton nem lehet változtatni. Hogy van a többi báró? Mindenki túlélte?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "Senki sem tud hozzászokni. Dinkeljünk a mieinkért? Találtam egy üveget az asztalon, csodával határos módon túlélte ezt a zûrzavart.";
			link.l1 = "Tölts, én... A francba... ezer átkozott!";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "Mesélj róluk. Ez az orvos okosnak tûnt. Olyan bölcsen fejezte ki magát.";
			link.l1 = "Tényleg. De attól tartok, a tudomány világa sokkal többet vesztett, mint én. Zseni volt... kifinomult, mint mindannyian. A csodák mestere!";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "Az indiai fickóról? Hol találtad meg?";
			link.l1 = "Guadeloupe-on mentettem ki a börtönbôl, szinte közvetlenül az érkezésem után. Nagyon vicces és hülye történet. Szóval, velem maradt. Ô döntött így, én adtam neki szabadságot, de ô mellettem maradt - én mentettem meg, és úgy gondolta, hogy élete végéig tartozik nekem. Szûkszavú, furcsán öltözködött, de hûségesebb volt, mint bármelyik lovag, ráadásul volt egy tehetsége is, a muskétával a levegôben, bármilyen távolságból el tudott találni egy érmét.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Hát, kifizette az adósságot, mit mondhatnék. Megmentette "+sld.name+" és Dannielle-t attól a szemétládától. Nekem úgy tûnik - ez méltó vég egy ilyen bátor harcosnak.";
			link.l1 = "Így van, Jan. Igyunk az elesettek emlékére... Találjanak békét. Hogy van a többi báró? Jól vannak?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "Ez az éjszaka sokba került nekünk. Nem is tudom, mikor épül fel a testvériség ebbôl a mészárlásból. Kindman tökéletesen választotta ki az idôt és a helyet a támadásra. Majdnem sikerült is neki - csak egy kicsit, és mindennek vége lett volna. De mi sokkal kevesebbet vesztettünk, mint amennyit elveszíthettünk volna.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "A Cápa a gyengélkedôn van, a hajója huszonnégy fontból kapott egy sortüzet. A fedélzetre repült, eltört néhány bordája, tengervizet nyelt, de él, néhány nap múlva olyan lesz, mint új korában.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard csak néhány karcolást kapott - ô a partot védte, és a katakombákat irtotta. Most a kikötôben van, kórházakat szervez a sebesülteknek és temetést azoknak, akiknek nem volt szerencséjük.";
			else dialog.text = "Bernardnak nem volt szerencséje, ô a katakombákból indított támadás után a házakat takarította ki, és a raktárakban összefutott egy csomó ilyen fattyúval. Elkapott egy golyót, egyenesen a fejébe. Kár, mert jó kapitány volt... Tyrex dühös lesz, ha megtudja.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard csak néhány karcolást kapott - ô a partot védte, és a katakombákat irtotta. Most a kikötôben van, kórházakat szervez a sebesülteknek és temetést azoknak, akiknek nem volt szerencséjük.";
			else dialog.text = "Bernardnak nem volt szerencséje, ô a katakombákból indított támadás után a házakat takarította ki, és a raktárakban összefutott egy csomó ilyen fattyúval. Elkapott egy golyót, egyenesen a fejébe. Kár, mert jó kapitány volt... Tyrex dühös lesz, ha megtudja.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "Sólyomról tudod. Dannie legalább egy hónapig nem engedi, hogy elhagyja a szigetet, az biztos. Egyetlen egy ügye volt a fejünkben... jaj, hát igen.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus jól van, mint mindig. Amint partra szállt, azonnal elkezdte kirázni a lelkét az ôrszemeknek, akik szemmel tartották ezt a sok mocskot. Még mindig sikerül neki parancsolnia a rend helyreállítását a városban. Vasember, nem másként.";
				link.l1 = "A vas puhább. Gondolom, a mi bárónk olyan fémbôl készült, amit még nem ismer a tudomány, haha!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "Egyedül Marcusszal érthetetlen, a hajóját megrohamozták, de a túlélôk azt állítják, hogy sikerült átugrania a fedélzetre. Már elküldtem a hosszúhajókat, hogy kutassák át az öblöt. Remélem kiderül, hogy a mi bárónk elég kemény ahhoz, hogy ne adja fel ilyen könnyen.";
				link.l1 = "Ez rossz, de korai lenne még sírni miatta, Marcus nem mondana le ilyen könnyen rólunk. Várjuk meg a kutatások eredményét.";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "Marcus kiúszott a partra, miután a hajója elsüllyedt. Nos, tudod, Tyrex nem tartozik azok közé, akik egy ilyen apróságtól megfulladnak. Most valahol a városban van. Valószínûleg az ôrök lelkét rázza ki, akik elnézték ezt a sok mocskot. Vasember, nem másképp.";
				link.l1 = "A vas elsüllyedne. Gondolom, a mi bárónk olyan anyagból készült, amit még nem ismer a tudomány, haha!";
			}
			else
			{
				dialog.text = "Marcus jól van, mint mindig. Amint partra szállt, azonnal elkezdte kirázni a lelkét az ôrszemeknek, akik szemmel tartották ezt a sok mocskot. Még mindig sikerül neki parancsolnia a rend helyreállítását a városban. Vasember, nem másként.";
				link.l1 = "A vas puhább. Gondolom, a mi bárónk olyan fémbôl készült, amit még nem ismer a tudomány, haha!";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "Ennyi az egész. Hát, lehetett volna rosszabb is. Még a te esküvôd, Charles, is... harcosan jött ki. A lényeg, hogy mindketten életben vagytok. Egy kis tanács, általánosságban... szeressetek... és ne merjétek feladni a harcot érte!";
			link.l1 = "Köszönöm Jan. Köszönöm mindannyiótoknak... Bevallom, elfelejtettem, hogy ünnepséggel kezdtük.";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "Szóval, itt van egy emlékeztetô.";
			link.l1 = "Igen, ez egy... vad buli volt.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "Ó, igen, az volt, várj egy percet. Van valami - úgy tûnt, hogy egy indiai srác van veled, aki mindig melletted van, vagy körülnéz, mintha valaki téged célozna. Viccesen öltözött, és nagyon feltûnô a nagy tömegben.";
			link.l1 = "Igen, Tichingitu, ô már a legelején eltûnt ebben a zûrzavarban, kezdek aggódni, hogy ôszinte legyek. Tudsz valamit?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "Úgy tûnik. A pultosunk hangoskodott, hogy az unokahúgát elrabolták, csak állítólag a támadás elôtt. Azt mondja, valami indián társaságában látták, a vállán vitte a parton a várostól keletre. Kindman söpredékei között nem vettem észre indiánt, de a tiédrôl eszembe jutott, amikor hallottam, így nem szóltam semmit. El kéne menned, megkeresni vagy valami, amíg nem kerül bajba. Mert a csapos megfenyegeti, hogy megöli, ha elôbb megtalálja. Jó fej fickó, de az unokahúgáért bármelyik fejét lecsavarja.";
			link.l1 = "Igen, ismerem a fajtáját, ne aggódj, és köszönöm Jan, azonnal megyek és megkeresem.";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "Hát általában valami ilyesmi... Bocsánat, béna vagyok a beszéddel. És most még rosszabb - ez az este mindenkit kiszipolyozott. Mindannyiunknak pihennünk kellene legalább egy napot - aztán majd eldöntjük, hogyan tovább.";
			link.l1 = "Igazad van, Jan, mennem kell, fel kell frissítenem az elmémet.";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "Jól nézel ki, Charles. Jól aludtál?";
			link.l1 = "Igen, kaptunk egy hangulatos házat a város szélén. Még azt hittem, hogy álmodtam a tegnapi ôrületet. És itt vagy te Jan, szörnyen nézel ki. Mi történt még?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "Ó, nem, semmi, csak még nem aludtam. Tudod... rendet tenni a városban mindazok után, ami itt történt, nehéz feladat.";
			link.l1 = "Hogy van Dannie és Nathan? Hol vannak a többiek?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "Pihennek. Ne zavarjátok ôket, Dannie figyelmeztetett mindenkit, hogy ma ágyba vitte a fegyvereket... Dodson a tengeren van, elindult, hogy több hajót keressen, hogy biztosítsa a szigetet, hogy ez ne történhessen meg újra, a többiek a sziget északi részén temetik el az elhunytakat.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "Marcust még nem találták meg, de megoldjuk, ne aggódj. Olyan sokat tettél mindannyiunkért, ne fáraszd magad. Tyrax elôbb-utóbb visszatér - meg fogjuk találni.";
			else dialog.text = "Marcus itt végzett, és elszáguldott valakinek a luggerén Hispaniola felé. Meg kell oldani néhány kérdést, amely Barbazon halála után merült fel. Üdvözletét és jókívánságait küldte neked és a feleségednek.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "Nos, a testvérek ellenálltak ennek a csapásnak. Hamarosan még erôsebbek leszünk, mint valaha is voltunk. Kindman és Jackman túl sokáig rengették egységünket, most már nincsenek, és a szívem úgy érzi - nem egyszer fogjuk megrázni a Karib-térséget. Az aranykor közeleg azok számára, akiknek a törvények és a királyok nem kedvesek, emlékezzetek a szavaimra.";
			link.l1 = "Ez lenne szép. Nem vagyok benne biztos, hogy a régi világot már nem fogom bírni. Soha nem gondoltam volna, amikor idejöttem, hogy beleszeretek a tenger szabadságába, a naplementék és napfelkelték ezen ôrült színeibe, hogy megtalálom a világ legjobb nôjét és... barátait, akikre az életemet is rábízom.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "Hát, tudod a pályát, csak döntsd el, hogy mit akarsz. Nálunk mindig szívesen látunk.";
			link.l1 = "Köszönöm, Jan, ez sokat jelent nekem.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "De elôbb van még valami fontos dolog. Charles, amíg aludtál, összeültünk, és úgy döntöttünk\nMiatt, hogy Barbazon meghalt, a Testvériségnek új báróra van szüksége. Mivel itt voltunk egyértelmû többségben, és a döntés egyhangúlag született, íme. Gratulálunk - te vagy Le Francois új bárója. De várjatok... Megértem - világi ember vagy, és nincs idôd ügyeket intézni ezen a szép helyen, ezért egy megbízható személyt helyezünk oda, és te azt csinálsz, amit akarsz. Csak ne feledd - a hangod most már a Testvériségben van.";
			link.l1 = "Jan, én... Elakadt a szavam... Ez egy nagy megtiszteltetés, nem is tudom...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "Gyerünk! Tökéletesen bizonyítottál akkoriban Tyrexszel, majd ezzel az egész történettel a Sharp örökségével. Maga Isten áldása vagy. Számodra semmi sem fog változni - tedd, amit elterveztél, és távollétedben az embered veszi át az ügyek irányítását\nVan egy ígéretes srác, Jan David, ô az egyik Buccaneer. Francia egy becsületes fickó, briliáns elmével, és tudja, hogyan kell használni, mint te. De eltart egy ideig, amíg megtalálom - úgy tûnik, a spanyolok fogságba ejtették, de ez megoldható, ne aggódj. Gondoskodom róla, hogy elküldje neked a részedet, amint megbarátkozik az üzlettel.";
			link.l1 = "Tényleg nem számítottam arra, hogy minden így alakul. Hát, ha már így döntöttél, akkor legyen. Charles de Maure kalóz báró!";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "Éljen sokáig a báró! Ha valaki megérdemli ezt a nevet, az te vagy. Viseld büszkén, és ne feledd - most már közénk tartozol, bármilyen szép is az egyenruha, amit viselsz, itt, közvetlenül alatta egy igazi kalóz szíve dobog.";
			link.l1 = "Nem tudom, talán túlzol... De mindent megteszek, hogy igazolni tudjam a bizalmadat.";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "Most mit fogsz tenni? Visszamész Európába, vissza az apádhoz, hogy bemutatkozz neki a feleségeddel?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "Igen, de elôbb el kell búcsúznom valakitôl... Tudja, mire gondolok.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "Talán nem olyan hamar. Még egyszer áthajózom a szigetvilágon, utoljára akarom belélegezni a Szabadság e levegôjét.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "Nos, van egy hajód, bármikor hazahajózhatsz, amikor csak akarsz.";
			link.l1 = "Remélem is. Köszönöm Jan, köszönöm mindannyiótoknak és viszlát késôbb, öreg barátom! Üdvözlöm a Sólymokat és a Cápát!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "Megérdemlik.";
			else sTemp = "Megérdemli.";
			dialog.text = "Igen, nehéz, de meg kell tennünk. A tengerre?";
			link.l1 = "Nem, Antiguára fogok hajózni. "+sTemp+" , hogy békében pihenhessek egy olyan helyen, amely egy idôre az otthonunkká vált.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "Mondj néhány kedves szót a nevemben is. És ne aggódj - mostantól egyedül is boldogulunk. Minden rendben lesz.";
			link.l1 = "Köszönöm Jan. Viszlát hamarosan öreg barátom! Üdvözlöm a Sólymokat és a Cápát!... Nos, akkor Antigua.";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "Fiatalember, ma még jobban megnôttél a szememben. Annyi mindent tettél Helenért, hogy a hála szavai sem elégségesek. Csak remélem, hogy továbbra is gondoskodni fogsz róla. Ha az apja élne és látná ezt, milyen boldog lenne... ó, sajnálom.";
			link.l1 = "Minden rendben, Gladys. Átkeltél a szigetvilágon, hogy támogasd Helent ezen a napon. Mindketten nagyra értékeljük, hogy meglátogattad Jant, köszönjük.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "Monsieur de Maure, elnézést kérek az ismerôsségért, de így fogalmazok - Charles, barátom, ôszintén örülök neked! Ha tehetek valamit önért vagy a menyasszonyáért, csak szóljon!";
			link.l1 = "Köszönöm, báró úr, nagyon boldog vagyok, és a szôlôskerteket, amelyeket apám kért truvájként, azt hiszem, kiválthatom - szerencsére anyagi helyzetem az Újvilágban való tartózkodásom alatt jelentôsen javult.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "Igen, gondolom, Charles, szinte bármit megengedhet magának, amit csak akar. Elnézést, de mint képviselô apa, én is hozzájárulok - Ma írok jó barátomnak, a pénzügyminiszternek. Az ön választottja nemesi címet kap, és azt hiszem, találunk neki valami jó birtokot, mondjuk Gascogne-ban, azok között, amelyeket adósságok miatt lefoglaltak, és visszamenôleg kiutaljuk neki. Így senki sem meri majd azt mondani, hogy a Chevalier de Monper alacsony rangú feleséget talált magának!";
			link.l1 = "Nem hiszem, hogy az ilyen pletykák miatt aggódnék, de köszönöm, báró úr. Mégis, nem kellene";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "Sôt, még jobban, mint kellene! Most menj, Charles, oszd meg a figyelmedet a többi vendéggel. És még egyszer, fogadd ôszinte gratulációmat!";
			link.l1 = "Én és a feleségem köszönjük. Viszlát, báró úr.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "Monsieur de Maure, elnézést kérek az ismerôsségért, de így fogalmazok - Charles, barátom, ôszintén örülök neked! Ha tehetek valamit önért vagy a menyasszonyáért, csak szóljon!";
			link.l1 = "Köszönöm, báró, de már így is sokat tett értem. Nekünk elég az, hogy ön eleget tett a meghívásnak.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "Hogy is ne válaszoltam volna, Charles! De figyelj - szeretnék neked és gyönyörû menyasszonyodnak méltó ajándékot adni, de nem tudok olyat kitalálni, amit pénzzel vagy karddal ne tudnál magadnak is megszerezni. Ezért írni fogok barátomnak, a párizsi pénzügyminiszternek, és mire megérkezel Európába, várni fognak, hogy aláírd a királyi rescriptumot a de Monper név báró de Monper címre való felemelésérôl! Nem, egy szót se, ez a legkevesebb, amit tehetek önért.";
			link.l1 = "Nem is tudom, mit mondjak, báró úr... Apám nagyon boldog lesz. Ôszintén köszönöm.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Károly, kérlek, fogadd ôszinte gratulációmat! Az Ön kiválasztottja egyszerûen egy csoda! Azt hiszem, ma a gyarmati divat egy erôs ... új irányt vett. Az eredetiséged mindig is lenyûgözött! Éljetek boldogan a szépséges feleddel, amíg meg nem halsz!";
			link.l1 = "Köszönöm, báró úr. Megtiszteltél minket a látogatásoddal.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "Hogy is maradhatnék távol barátom? Sok mindenen mentünk keresztül együtt, és büszke vagyok, hogy a barátomnak hívhatlak, Charles. Ne feledd - az ajtóim mindig nyitva állnak elôtted, bármi is történjék.";
			link.l1 = "Ahogy a de Monper család ajtajai is mindig nyitva állnak elôtted, báró úr.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "Charles, barátom, ez egy nagyon fontos nap, és örülök, hogy meghívtál, hogy megosszam veled. Hosszú és nehéz utat jártunk be, és hogy a mademoiselle reprezentatív apja legyek... kérem, bocsásson meg - Madame de Maure, ez megtiszteltetés számomra, higgye el. Teljes szívembôl kívánok önnek boldogságot!\nÉs kérem, tudassa velem, mikor utazik Európába - én, mint a választottja reprezentatív apja, elküldöm édesapjának a szükséges nászajándékokat. Higgye el, senki sem fogja azt mondani, hogy Monper lovag menyasszonya szegény vagy méltatlan!";
			link.l1 = "Ha megkérdezhetem, Chevalier, néhány mérföldre, a de Monper birtoktól északra vannak jó szôlôskertek, a La Brigne családé, és én...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "Egy szót se többet, barátom, egy szót se! Azonnal írok a Lyonban lévô meghatalmazott képviselômnek - az ön megérkezéséig ezeket a szôlôültetvényeket átadom az ön kiválasztottjának.";
			link.l1 = "Köszönöm, Chevalier. Igaza van - a mi... barátságunk... sok mindenen ment keresztül... De nagyon örülök, hogy megosztotta velünk ezt a napot. Viszlát és még egyszer köszönöm!";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "Charles, barátom, ez egy nagyon fontos nap, és örülök, hogy meghívtál, hogy megosszam veled. Hosszú és nehéz utat jártunk be, és megtiszteltetés számomra, hogy ma tanúskodhatok az esküvôdön. Teljes szívembôl kívánok nektek boldogságot! És szóljatok, ha Európába mentek - küldök édesapátoknak méltó nászajándékokat.";
			link.l1 = "Erre nincs szükség, Chevalier. Köszönöm, hogy válaszoltál a meghívásomra.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("Drágaköveket kaptál");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "Mint mondtam - ez megtiszteltetés számomra! De várj, barátom, szeretnék neked valamit ajándékozni ebbôl az alkalomból - biztos vagyok benne, hogy ez mind neked, mind a választottadnak tetszeni fog. Gyönyörû kövek az új-guyanai bányáinkból - válasszon nekik egy tisztességes keretet, és madame de Maure még a királyi fogadáson is ragyogni fog! Persze csak ha meggyôzi, hogy viseljen ruhát...";
			link.l1 = "Ó, igazán nem kellene, chevalier. Még egyszer köszönöm.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "Charles, barátom, hadd gratuláljak! Hosszú és nehéz utat tettünk meg, és ôszintén örülök, hogy ma itt lehetek. Urunk a tanú - megérdemled a boldogságodat! Tartsd meg és védd meg - sok boldog évet kívánok neked!";
			link.l1 = "Köszönöm, Chevalier, én és a feleségem nagyon hálásak vagyunk.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "Charles, micsoda ünnepség, és mennyi fontos ember! Hadd kívánjak szívbôl boldogságot és jó egészséget, és gyermeki örömöket! Ahogy mi mondjuk - 'gor'ko'!";
			link.l1 = "Köszönöm, Fadey, megtiszteltél azzal, hogy vállaltad, hogy eljössz.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "De, nem egészen értem, miért van itt ennyi ember, mintha nem házasságot kötnénk, hanem egy nagy kereskedelmi üzletet, és még mindig nincs itt elég sör és vodka az én ízlésemnek... haha! Hát, csak vicceltem, Charles, miért lettél teljesen sápadt? Ölelj meg, te házas kapitány!";
			link.l1 = "Hûha... Fadey, olyan erôs vagy, mint egy medve!";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("Kaptál három perzsa szablyát");
			PlaySound("interface\important_item.wav");
			dialog.text = "Várj, Charles, ne menj el - nem méltó, hogy a vendég ajándék nélkül jöjjön az esküvôre. Tessék, vedd el ôket. Tudom - próbáltad megtalálni ezeket a pengéket, és néhány, nyilván tetszett neked. Fogadd hát el ôket - akaszd fel a családi hagyatékban, és emlékezz meg Fadey Moskovitról egy kedves szóval!";
			link.l1 = "Ez egy igazi ajándék! Köszönöm, Fadey. Ezek valóban csodálatos fegyverek, és méltó helyük lesz a Monper birtokon, ígérem!";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, micsoda ünnepség, és mennyi fontos ember! Hadd kívánjak szívbôl boldogságot és jó egészséget, és gyermeki örömöket! Ahogy mi mondjuk - 'gor'ko'! Ölelj meg, te házas kapitány!";
			link.l1 = "Hûha... Fadey, olyan erôs vagy, mint egy medve!";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "Károly, nem hagyhattam ki, szívbôl gratulálok neked és választottadnak! Légy boldog! Tudod, pár hónapja én is összeházasodtam a lányommal, egy jó embernek és szerelmesnek, de ôszintén szólva, nagyon bántott, hogy nem te voltál az... Hát, rendben... mirôl is beszélek - gratulálok! Éljetek boldogan, míg meg nem halnak!";
			link.l1 = "Köszönöm, Prosper, örülök, hogy eljöttél.";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "Gratulálok, kapitány! Furcsa szertartás, de gyönyörû - tetszett Tichingitu-nak. Bár a kapitánynak csak el kellene rabolnia az asszonyt, és váltságdíjat küldeni a rokonainak.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Hát, bizonyos értelemben igen, és ez csak formalitás. Köszönöm, barátom!";
			else link.l1 = "Hát, bizonyos értelemben igen, és ez csak formalitás. Köszönöm, barátom! Sharptownban még fogunk beszélgetni - ott sokkal kevesebb hivatalos és több ôszinte szórakozás lesz, ígérem!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Már megint tûzivíz? Tichingitu nem mondhatja, hogy szereti. Talán az ünnepi deszkázás jobb lenne, vagy legalább a tábortûz körüli tánc?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Remélem, hogy nem lesz még sokáig máglyák körüli tánc, és inkább maradnék a beszállás nélkül. Rendben, legyen türelemmel - már csak egy kicsit maradt, és rögtön a kocsmába megyünk.";
			else link.l1 = "Attól tartok, hogy jóval a vége elôtt a tábortüzek körüli táncokra kerül sor, és én inkább maradnék a beszállás nélkül. Rendben, legyen türelemmel - már csak egy kicsit van hátra, és azonnal Sharptownba hajózunk.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Kapitány, még egyszer gratulálok! Tichingitu jobban szereti ezt az ünnepséget, mint az elôzôt. A kapitány tudja, hogyan kell barátokat választani - itt több az ôszinteség, kevesebb a képmutatás és a hamis haj.";
			link.l1 = "Köszönöm, barátom! Csak ne idd meg a tûz vizét - itt nagyon nehéz.";
			link.l1.go = "Tichingitu_4";
			link.l2 = "Köszönöm, barátom! Igyunk egyet? Tudom, nem szereted, de ma meg kell kóstolnod!";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "Tichingitu nem szereti a tüzes vizet, de ha a kapitány ragaszkodik hozzá, ma már lehet. A boldogságodra, és a squawra!";
			link.l1 = "És rád, Tichingitu! A barátságodra és a hûségedre!";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "Szép parti, kapitány.";
			link.l1 = "Örülök, hogy elégedett vagy.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Kapitány, kijöttél megnézni a csillagokat? Az éjszaka nagyon szépnek ígérkezik. Tichingitu szereti az éjszakát a tenger felett. Nagyon békés.";
			link.l1 = "Örülök, hogy még mindig talpon vagy, barátom! Nathanielnek és nekem szükségünk van a segítségedre - a srácok a kocsmában kifogytak az italokból, néhány láda italt kell hoznunk a hajógyár alatti raktárból.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "Vezess, kapitány. Tichingitu követ téged, mint mindig.";
			link.l1 = "Rendben, gyerünk!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "Kapitány, emberek vannak, és fegyveresek, Tichingitu hallja a fegyverek csörgését, és másodpercrôl másodpercre hangosabbak. Ez nem tetszik nekem. Bújjunk el.";
			link.l1 = "Gyerünk, pajtás - ez Sharptown, itt még a mosdóba is pisztollyal felfegyverkezve járnak az emberek. Hé Nathan... hát, a francba! Az egyik üveg elfogyott. Ha ez így megy tovább, akkor az összes üveget széttöröd! Állj a lábadra, a fenébe is! Ha-Ha!";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "Kapitány... te... Tichingitu feje úgy törik, mint árboc a viharban. Mi történt?";
			link.l1 = "Én is ezt akartam kérdezni tôled! Hol voltál egész idô alatt?!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Tichingitu egy órája ébredt fel ennek a lánynak a sírására. Majdnem meztelenül futott végig a parton, és valamit kiabált az elrablókról és a vademberekrôl... De rajtunk kívül senki sincs itt. Van víz? Már megint nem tüzes, Tichingitu most utálja?";
			link.l1 = "Volt valahol egy flaska, ha nem vesztettem el a csatában... tessék. Hogy sikerült ezt megcsinálnod? A nagybátyja, egy helyi csapos, indiánt keres, aki elrabolta az unokahúgát, és azzal fenyegetôzik, hogy letépi a tollas üres fejét. Szerinted kire gondol?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu emlékezett. A kocsmában segített az Erdei Ördögnek a lakodalomban. Tüzes vizet ittunk veled, és Tichingitu még többet akart. És akkor ez a squaw... olyan aranyos volt és... Kapitány, azt hiszem, emlékszem! Tichingitu feleségül akarta venni... Egy kenut akart építeni és elvinni ôt... A kegyelem szellemei! Nagyon rossz emberek jöttek fel a tûzzel-vízzel. Talán a démonok vagy gonosz szellemek! Tichingitu soha többé nem fog...";
			link.l1 = "Elvinni ôt? Egy kenut építeni?! Ahah, te egy romantikus vagy, barátom... Ha-ha... ha-ha-ha-ha-ha-ha-ha-ha-ha-ha ó, nem tudom abbahagyni... Nem tudom abbahagyni a nevetést!";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "Kapitány, Tichingitu ellopta a squaw-t, igen... de, nem lehetne, nos... nem házasodhatnánk most össze? Ô... hangos, mint egy papagalló madár, és... nem is olyan szép.";
			link.l1 = "Igen, barátom, a nôk, akik egész éjjel szórakoznak, reggelre szánalmas látványt nyújtanak. Ne aggódj, hôsszerelmes, majd kitalálunk valamit. Gyerünk, vissza kell mennünk Sharptownba, lemaradtál a nyaralási beszállásról...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "Panzió? A kapitány már említett egy csatát. A gondolatok még mindig nem engedelmeskednek Tichingitunak. Mi történt a városban?";
			link.l1 = "Igazi csata a szárazföldön és a tengeren. Az ágyúk egész éjjel lövöldöztek, azt hiszem, még San Joséban is hallották ôket. Viszont egy másik 'csata', minden rendben van, megértem... Gyere, majd útközben mindent elmondok.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "Köszönöm, kapitány... Tichingitu soha...";
			link.l1 = "Igen, 'a távoli síkságok csôdörének' már biztosan nem kellene többet innia. Menj, aludj egy kicsit. Már én is leesem a lábamról.";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "Kapitány, még egyszer gratulálok! Tichingitu jobban szereti ezt az ünneplést, mint az elôzôt. A kapitány tudja, hogyan kell barátokat választani - itt több az ôszinteség, kevesebb a képmutatás és a hamis haj.";
			link.l1 = "És sokkal több tûzivíz. Apropó, megiszol velem egy italt? Tudom, hogy nem szereted, de szokatlan alkalom van!";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "Tichingitu nem szereti a tüzes vizet, de ha a kapitány ragaszkodik hozzá, ma már lehet. A boldogságodra, és a squawra! Járjátok ugyanazt az utat, s ragyogjon rá mindig a nap és a hold.";
			link.l1 = "Köszönöm, barátom. Egészségedre, Tichingitu! A barátságunkra!";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "Nagyszerû ... ünnepség, nagyon örülök neked, Charles. Bár még mindig nem értelek... Hogy egy felbecsülhetetlen értékû rózsát tartasz a kezedben, és elcseréled... egy vadvirágra. De a szív azt akarja, amit akar... Légy boldog, barátom. Élj boldogan, amíg meg nem halsz!";
				link.l1 = "A virágban, amit tartasz, a legszebb dolog az érzésed iránta. Enélkül csak egy halványuló húsdarab. Örülök, hogy bejöttél, felség.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "Csodálatos napot, barátom, és csodálatos alkalmat! Fogadd ôszinte gratulációmat! Háromszor mentem férjhez, és minden alkalommal úgy reszkettem, mint az elsô, ah, ifjúkoromban...";
				link.l1 = "Monsieur, ön még messze van az öregkortól, ne csüggedjen! Köszönöm, hogy eljöttél, Jacques!";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "Várj, Charles. Félreértettél, ôszintén boldog vagyok, teljes szívembôl! És igen... tessék, fogd meg. A mi közös... Barátom, tényleg azt kérte, hogy pontosan ma kapja meg.";
			link.l1 = "Gyanítom, hogy tudom, kitôl van. Köszönöm és hamarosan találkozunk.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "Elragadó liturgia, nem igaz, Charles? Ôszintén örülök neked! Én személyesen és Basse-Terre minden lakója nevében gratulálok önnek és... bájos feleségének. Csodálatos pár vagytok! Éljenek boldogan, amíg meg nem halnak!";
			link.l1 = "Köszönöm, felség. Örülök, hogy tetszett.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "Micsoda csodálatos szertartás, Monsieur de Maure, egyszerûen csodálatos! És a menyasszony olyan... eredeti ebben a ruhában. Városunk minden lakója nevében - fogadják ôszinte gratulációmat! Sok boldog évet kívánok Önöknek!";
			link.l1 = "Köszönöm, kegyelmes uram.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "Olyan aranyos - ön és a menyasszonya, monsieur de Maure, olyan szokatlanul nézett ki! Ön azonban szokatlan ember. Hosszú és boldog családi életet kívánok. Éljenek boldogan, amíg meg nem halnak!";
			link.l1 = "Nagyon hálás vagyok Önnek, kegyelmes uram.";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "Az ön esküvôje kedvéért érdemes volt átkelni a Karib-tengeren! Gratulálok, kapitány, az összes angol gyarmat lakói nevében! Ön és menyasszonya, bocsánat, már feleség, csodálatos pár vagytok!";
			link.l1 = "Köszönöm a látogatást és a kedves szavakat, ezredes úr!";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "És mit keres ez a nôs piperkôc a kalózpartomon, mi?! Mondja, monsieur, mit csinált az én régi barátommal - a zord kalóz Charlie herceggel?";
					link.l1 = "Charlie Prince meghalt, emlékszel rá, Marcus... Ha-ha-ha-ha gyere ide te tengeri ördög! Örülök, hogy látlak! Hogy vagytok itt, mindenki összegyûlt már?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "És mit keres ez a nôs piperkôc az én kalózpartomon, mi?! Mondja, monsieur, mit csinált a régi barátommal - a zord Charles de Maure kapitánnyal?";
					link.l1 = "Ahoj, Marcus, én is örülök, hogy látlak! Hogy vagytok itt, mindenki összegyûlt már?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "És mit keres ez a nôs piperkôc az én kalózpartomon, mi?! Mondja, monsieur, mit csinált az én régi barátommal - a zord Charles de Maure kapitánnyal?";
				link.l1 = "Ahoj, Marcus, én is örülök, hogy látlak! Hogy vagytok itt, mindenki összegyûlt már?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "Igen, az erdei ördög éppen tegnap érkezett meg, és azonnal parancsolgatni kezdett - tehát a vendégek itt vannak, és minden készen áll az ünnepségre. Az ön hajóját észrevették a zátonyok közelében, és a fiúk nem bírták ki - berohantak a kocsmába, és valószínûleg már fel is bontották azt a sólyomhordót. Siessetek, talán még van esélyünk meginni egy pohárral - dicsekedett Nathaniel, hogy ez valami különleges rum!";
			link.l1 = "Na, így csináljuk - a hajóról egyenesen a buliba! Megvárom a legjobb felemet, mi pedig mindjárt utánad megyünk, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "Igen, az erdei ördög éppen tegnap érkezett meg, és azonnal parancsolgatni kezdett - tehát a vendégek itt vannak, és minden készen áll az ünnepségre. Az ön hajóját észrevették a zátonyok közelében, és a fiúk nem bírták ki - berohantak a kocsmába, és valószínûleg már fel is bontották azt a sólyomhordót. Siessetek, talán még van esélyünk meginni egy pohárral - dicsekedett Nathaniel, hogy ez valami különleges rum!";
			link.l1 = "Na, így csináljuk - a hajóról egyenesen a buliba! Megvárom a legjobb felemet, mi pedig mindjárt utánad megyünk, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Férjhez ment Charles de Maure - még mindig nem tudom megszokni... Elôször Svenson, most te - aztán mi lesz? Marlow pásztor, vagy Jacques, a Kindman?";
			link.l1 = "Elfelejtetted a Sólymokat. És mi van veled, Marcus? Nem unod még, hogy magányos tengeri farkas vagy?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "Dannie és Nathan régóta ügy - ezzel már megbékéltem, de te megleptél, nincs mit mondani! Az Erdei Ördög tanítványa azonban gyönyörû - nincs mit mondania, bármikor kész egy szóra és egy fegyverre, és bármilyen vihart elbír. Nem valószínû, hogy méltóbb nôt találhatna magának. Szerencsés vagy, kapitány - vigyázz rá!";
			}
			else
			{
				dialog.text = "Dannie és Nathan régóta ügy - ezzel már megbékéltem, de te megleptél, nincs mit mondani! Bár, ahogy hallottam, a maga Maryje sokat tud a kardokról, és nyilván tudja, hogyan kell használni ôket - tiszteletem! Egy igazi háborús barátnô. Elárulok egy titkot, egy ilyen lány kedvéért én magam is átgondolnám agglegényi meggyôzôdésemet. Szerencsés vagy, kapitány - vigyázz rá!";
			}
			link.l1 = "Tudom, ô egy csoda, és én megint a hetedik mennyországban vagyok a boldogságtól - mint azokban a napokban, amikor elôször találkoztunk!";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "Nos, akkor tósztot mondok!... A szerelemre! De nem arra, amelyik átvezet minket a küszöbön és a horizonton!... Hanem arra, aki vár ránk ezen a küszöbön! A szerelemre, arra, amely a világ végérôl és az aranyhegyekbôl is visszavezet minket hozzá! Élj vele és légy boldog!";
			link.l1 = "Nagyszerû köszöntô, Marcus, köszönöm!";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "Egészségedre, a násznépedre!";
			link.l1 = "Köszönöm, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "Jacques? Ez határozottan nem jó...";
			link.l1 = "Marcus, szerinted...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "Nincs idônk! Az ajtók mögött vannak! Mindenki, fegyverbe!";
			link.l1 = "Gyerünk!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "Nem is emlékszem, mikor szórakoztam utoljára ennyire egy bulin! Még nincs vége! Halljátok ezt? Valaki lövöldözik odakint! Hadd szennyezzük be az utcákat a vérükkel!";
			link.l1 = "Várjatok! Ki a francok ezek?! És mi a faszt akarnak egyáltalán?!";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "De Maure kapitány feleségeként ritkán találkoztam ôszintébb indokkal egy tósztra. Emeljük poharunkat - ez nem egy közönséges káposztás ital. Kelet-Indiából származó fekete teával átitatva és igazi perzsa fûszerekkel ízesítve!";
			link.l1 = "Én meg azon gondolkodtam, hogy miért ég a torkomban, mintha olvadt ólmot ittam volna. Nos, Nathan, egészségedre...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "Várj, elôbb egy tósztot! Hé, uraim, emeljék fel a bögréjüket! Ma Charles de Maure barátunk és társunk a családi élet útjára lép. Fogadjátok ôszinte részvétünket... Ó, Dannie, kérlek, tedd le a fegyvert! Gratulálunk, természetesen! Ti vagytok a vitorlái ugyanannak a hajónak, vezessétek át minden viharon a legtermékenyebb partok felé!";
			link.l1 = "Köszönöm, Nathan, ôszintén. Te és Danielle követendô példa vagytok számunkra.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "Jó hallani. A feleségem és én talán nem vagyunk a világ legjobb párja, de boldogok vagyunk együtt, és te nagyon sokat tettél értünk, úgyhogy ha engem kérdezel, a családom része vagy, és itt leszek neked, amikor csak szükséged van rám. Légy boldog, és kérlek, igyál egyet!";
			link.l1 = "Akkor igyunk! Ó... ennek a rumnak a Szent Inkvizíció fegyvertárában lenne a helye. A francba! Ez égeti az egészet... aghhh! Whew!... Ez tetszik!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "Annyira hasonlítasz rám és Dannie-re húsz évvel ezelôtt!";
			link.l1 = "Még egy csésze, Nathan!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Mi az?!? Jan küldött téged a pincébe, hogy hozz bort? Sétáljunk egyet, segítek neked egy kicsit, és a friss levegô is jól fog esni.";
			link.l1 = "De hol van Dannie és "+sld.name+"? Jan azt mondta, hogy elmentek beszélgetni.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "Igen, Dannie tudja, hogy még a legjobb barátnô jelenléte sem ad idôt a szerencsés uraknak arra, hogy teljes mértékben kikapcsolódjanak. Így hát meghallgatták a bókokat, amiket kaptak, és elmentek a rezidenciára, hogy a fiúk jól érezzék magukat.";
			link.l1 = "Hát akkor induljunk! Sikerült meginnom pár bögrényit, de a fene egye meg, most már tényleg itt az ideje, hogy rendesen berúgjak!";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Szóval, itt van a láda. Fogunk annyit, amennyit bírunk, és visszamegyünk, amíg ez a vén morgós ide nem zár minket.";
			link.l1 = "Túlzol, Nathan. Nem is olyan rossz... Várj, hallottad ezt?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Jan valószínûleg talált még több fickót, és elküldte ôket, hogy segítsenek nekünk. Baszd meg!";
			link.l1 = "Gyerünk, az üvegek szerencsésen eltörnek. Vegyél még egyet és menjünk.";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "Mi a fene folyik itt, kik ezek a rohadékok? Értesz valamit, Charles?";
			link.l1 = "Nem tudom, Nathan, de az egyikük elszaladt segítséget hozni, és mintha még több lépést hallanék. Vissza kell mennünk a kocsmába!";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "Leterítjük ezeket a rohadékokat, de a tenger felôl fegyverek dörögnek, halljátok? Csak két legénységünk áll harcra készen, a Marcus' fregatton és Jan korvettjén. Én, Dannie és a többiek leszállították a mieinket - végül is esküvô -, így a Centurion kiesett. Mi a helyzet a te hajóddal? El kell döntenünk, hogy mit tegyünk, méghozzá gyorsan!";
			link.l1 = "A legénység felét már partra szállítottam, remélem, a többiek józanok. De elôbb meg kell találnom a feleségemet, és meg kell gyôzôdnöm róla, hogy jól van.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "Igen, Dannie-t sem látjuk sehol. Akkor így járunk el - Tyrex és Svenson már a kikötôbe sietett, csónakokon érik el a hajóikat. Mi a feleségekért megyünk a rezidenciára, a többiek - hadd szervezzék meg a védelmet a parton. El tudod küldeni néhány tisztedet, hogy gyûjtsék össze az embereket a hajódon? A segítség ott nyilván nem ártana.";
			link.l1 = "Rendben, mindenki induljon! Minden másodperc számít!";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Gyorsabban, felfelé! Dannie és "+sld.name+" ott kell lennie! És ha ezek a rohadékok bántják ôket...";
			link.l1 = "Ne is gondoljatok rá! Az emeletre! Gyerünk!";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "A francba! Az embered, egyenesen a fegyverhez rohant, hogy az a szemétláda ne lôje le a lányokat!";
			link.l1 = "És kapott egy golyót... Várj, Nathan... lélegzik! Még életben van! A fenébe, szükségem van Ginóra! "+sld.name+", drágám, hogy vagy?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Jól vagyunk, Charles! Eloldozom. Fegyvereket hallok a kikötôben - neked és Nathan-nak oda kell mennetek, különben Barbazon elpusztítja az összes hajónkat. Ne vesztegessétek az idôt!";
			link.l1 = "Megkeresem Ginót, és ideküldöm, segíteni fog... segítenie kell! "+sld.name+", kedvesem, maradj itt, vigyázzatok rá, mindketten.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "Charles, siess! bárhogy is döntesz, az idô most aranyat ér! Ha Jacques' hajók áttörnek a partra, minden hiába!";
			link.l1 = "Igen, tudom. Rohadt szemétláda!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "Gyorsabban, nincs idônk beszélgetni!";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "A francba! Bocsáss meg, Charles. Az emeleten ragadtunk, ott volt egy tucatnyi ilyen szemétláda... Kár, hogy nem értem ide idôben, de látom, a lehetô legjobban kezelted a helyzetet.";
			link.l1 = "Nem mondhatom, hogy könnyû volt, de basszus, nagy örömömre szolgált, amikor megöltem ezt a 'kedves embert'! Ideje partra szállni, Nathan, az embereink ott várnak ránk!";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "Igen, meg kell látogatnunk az indián fiadat, fejezd be itt és menj Sharptownba.";
			link.l1 = "Igazad van, mögötted vagyok.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "Mellesleg, megtaláltuk Marcust! A raktérben volt, megkötözve és eszméletlenül.";
			link.l1 = "Életben van?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "Elég rossz állapotban van, de rendbe fog jönni. Tyrex erôsebb, mint egy koporsószög, úgyhogy ne aggódj, már át is szállították a hajódra, és kért egy szablyát.";
			link.l1 = "Végre egy jó hír! Rendben, fejezzük be itt, és menjünk vissza.";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "Helló, Charles. Hadd nézzelek meg - lett szebb, nem panaszkodhatok! Majdnem olyan, mint Nathan, úgy tíz évvel ezelôtt! Gyere be, ne állj a küszöbön, mindenki csak rád várt!";
			link.l1 = "Köszönöm, Dannie, nagyon örülök, hogy látlak! Kicsit késôbb jövök hozzád és Nátánhoz, aztán majd beszélgetünk!";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, foglalj helyet - Nathan és én nagyon örülünk neked! Marcus, Jan és a férjem készítettek neked valamit - de az ajándékok várnak. Egyelôre hadd gratuláljak nektek és kívánjak boldogságot! A választottad egyszerûen egy csoda! Mondd csak, ugye nem sikerült rávenned, hogy fehér ruhát viseljen ott Martinique-on?";
			link.l1 = "Köszönöm, Dannie. Igen, viccesen alakult a ruhával - biztos vagyok benne, hogy az elôkelô társaságban az esküvônk sok botrányos pletykát keltett. Mindenki ôszintén elfordította a szemét, és úgy tett, mintha semmi rendkívüli nem történt volna. Az illem meg minden ilyesmi - de engem nem érdekelnek a pletykák, én szeretem ôt, és ez a legfontosabb.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "Teljesen igazad van! Én is az oltárhoz sétáltam, karddal és egy pár pisztollyal a pántlika mögött. De ez Port Royalban volt, még mielôtt méltóságteljes gyarmati rezidenciává vált volna. Akkoriban annyi móka volt, még több, mint Tortugán Levasser alatt, és senki sem lepôdött meg... eh. Én azonban végig csevegek - járja körbe a vendégeket, itt már mindenki várta magát, csak egy ölelést adjon!";
			link.l1 = "Ah Dannie, hogy is utasíthatnám vissza, ha-ha! El sem tudod képzelni, hogy én és a feleségem mennyire örülünk, hogy mindannyian itt vagytok!";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "Gyönyörû pár vagytok, Charles!";
			link.l1 = "Köszönöm, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "Charles, igaza van... nincs más választásod. Nem hiszek Jacques, a Kindman kegyelmében, ha Tyrexszel és a többiekkel foglalkozik. Tudod, mit kell tenned.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "Ne hallgass rá! Ha a Kindman ilyen ôrültségre szánta el magát, nem fog senkit sem kímélni!";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Jól vagyunk, Charles! Eloldozom. Ágyúkat hallok a kikötôben, neked és Nátánnak oda kell mennetek, különben Barbazon megfojtja a hajóinkat, mint kacsát a hordóba. Egy percet se veszítsetek!";
			link.l1 = "Megkeresem Ginót, és ideküldöm, segíteni fog... segítenie kell, a fenébe is! "+sld.name+", kedvesem, maradj itt, vigyázz Tichingitu-ra.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nathan, ne!";
			link.l1 = "Megragadta a pillanatot, és a fegyverhez rohant, hogy fedezzen téged, Dannie... "+sld.name+", drágám, hogy vagy?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "Igen, Charles, életben van! A szíve alig dobog, de él! Mit tegyünk?";
			link.l1 = "Azonnal szükségünk van Ginóra! Megkeresem és ideküldöm, segíteni fog... segítenie kell!";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "Charles, nincs idônk! Ha Jacques' hajói áttörnek a partra, minden hiábavaló lesz! A férjem ... megtette, amit kellett. Most rajtad a sor. Én vele maradok. Ti ketten menjetek és keressétek meg Ginót!";
			link.l1 = "Igen, tudom. A rohadt szemétláda, ezért megfizet!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "Végre itt vagy! Mindenki jól van?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "Jól vagyunk, Dannie, ne aggódj. Jacques meghalt, a hajója a tengerfenéken van. Hogy van Tichingitu?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "Jól vagyunk, Dannie, ne aggódj. Jacques meghalt, a hajói a fenéken vannak. Hogy van Nathan?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Jól van! Az olasz orvosod egy zseni! Nathan az emeleten alszik, de Gino szerint semmi sem fenyegeti. Egy-két hét ágyban fekvés, vörösbor, és, ahogy ô mondta 'egy neki jólesô hölgy látogatása' ahem... Általánosságban - minden rendben van, megint megmentettél minket, Charles, hogyan is köszönhetném meg?";
				link.l1 = "Nathaniel volt az, aki megmentette a feleségemet és téged. És ezért örökké az adósa leszek. El sem tudod képzelni, mennyire örülök, hogy hallom, hogy felépült. Hagyd pihenni, késôbb benézek hozzád.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "Jól van, a golyó átment rajta, és a sebészünk 'Centurion' nem volt messze. Elbújt az egész zûrzavar elôl. Nathan tehát élni fog, pár hét ágyban fekvés - kis baj!";
				link.l1 = "Dannie, ô védte meg a feleségemet és téged a golyótól, és ezért örökké az adósa leszek. El sem tudod képzelni, mennyire örülök, hogy hallom, hogy felépül. Hagyd pihenni, majd késôbb benézek hozzád.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "Persze, persze! De most el kell mennem, a férjemhez kell mennem... Nem bánja, ha kölcsönadjuk a barátját? Ha Nathan jobban lesz, én magam viszem el Antiguára. Centurion valahogy csodával határos módon túlélte, már csak egy új csapatot kell toboroznia.";
			link.l1 = "Rendben, Dannie, üdvözöld Ginót és Nathant. Nekem mennem kell.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "Persze, Charles, de... Rossz hírem van. Az az olasz, Guineili, aki ott volt az esküvôdön... A holttestét a kocsma egyik szobájában találták meg. Én... Sajnálom, Charles.";
			link.l1 = "Sajnálom, Charles. Gino?! Ne! Hogy?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "Nem tudom, valószínûleg az egyik rohadék, aki átment a katakombákon és megtámadta a várost. Úgy tûnik, ott bujkáltak, kerestek egy pillanatot, hogy elmenekülhessenek, és rátaláltak...";
			link.l1 = "Bassza meg! Nem, ezt nem hiszem el...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "Sajnálom, Charles. Ez egy istenverte vérfürdô volt, és ô nem volt harcos... Ha akarod, elküldjük a holttestét a hajódra, hazavisszük, és úgy temetjük el, ahogy kell. Nagyon sajnálom...";
			link.l1 = "Köszönöm, Dannie. Adj parancsot, hogy rakják fel a holttestet egy hajóra. Nekem most mennem kell... Gondolkodnom kell. És köszönj Nathan-nek.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Jól van! Az olasz orvosod egy zseni! Az emeleti szobában alszik, és Gino vigyáz rá. Azt mondja 'egy-két hét és rendbe jön'..";
				link.l1 = "Nagyszerû hírek! Gondolom, most nem látogathatom meg?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "Annyira sajnálom, Charles. Megtaláltam a sebészünket a Centurionból, de ô nem tudott semmit tenni... A barátja néhány órája meghalt.";
				link.l1 = "Tichingitu?! Nem! Ezt nem hiszem el!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nem, az olasz szigorúan megtiltotta, hogy megzavarják, hadd pihenjen, és Ginónak is pihennie kell a sok gond után. Még azt is mondtam "+sld.name+" , hogy menjünk el sétálni, amikor kiderült, hogy minden rendben lesz\nÉs még valami... a barátod, ô fedezett a golyótól. Nem is tudom, hogyan köszönjem meg neki, mondd meg neki, hogy mostantól ô is a családunk része, és te - megint megmentettél minket, Charles!";
			link.l1 = "Minden jó, ha a vége jó, Dannie. Menj Nathanhez, már vár rád, én pedig itt tartok egy kis szünetet, és megkeresem a "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Sajnálom, mindent megtettem, amit tudtam, és "+sld.name+"is. Ô fedezett minket attól a golyótól, és ezt soha nem fogom elfelejteni, higgyétek el nekem.";
			link.l1 = "... Régen azt mondta, hogy meghalna értem... Azt hiszem, nem tudta, hogy az életét fogja feláldozni mindannyiunkért... és most már hôs, és én nem fogok másként emlékezni rá... Hol van a "+sld.name+"? Jól van?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "Nem mondhatom... Úgy értem, fizikailag igen. De... tudod... Azt mondta, hogy elment sétálni, hogy kitisztítsa az elméjét. Valószínûleg látta, hogy kikötöttél, és hamarosan visszajön.";
			link.l1 = "Átkozott Jacques Barbazon... Már korábban meg kellett volna ölnünk!";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "Várj... ez még nem minden. Az az olasz, Guineili, igaz? Az a csendes fiatalember. Ôt... a holttestét egy kocsmában találták meg... Nem is tudom, valószínûleg az egyik ilyen szemétláda, aki átment a katakombákon és megtámadta a várost. Úgy tûnik, ott bujkáltak, kerestek egy pillanatot, hogy elmenekülhessenek, és megtalálták ôt...";
			link.l1 = "És Ginót is?! Ma tényleg esôs nap van...";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "Sajnálom, Charles... Ha akarod, elküldjük a holttestüket a hajódra, hazavisszük a srácokat, és eltemetjük ôket, ahogy kell. Nagyon sajnálom...";
			link.l1 = "Köszönöm Dannie. Csináljátok... Mennem kell... Gondolkodnom kell.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, el tudod képzelni, hány lány' szívét törted össze ezzel az esküvôddel? Igen, a fél szigetvilág lányai gyászolhattak az esküvôd után, haha!";
			link.l1 = "Mit tehetek - nekem csak egy kellett, és meg is kaptam. De még korai lenne a lányokat bántani, mert még mindig itt vagy nekik te, Stiven.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "És ez igaz! Itt végzünk, és azonnal gondoskodom róluk, a fenébe is! Gyere, Károly, igyunk a szerencsédre és a családi életedre! Szóval, ahogy mondani szokták, boldogan, amíg meg nem halunk!";
			link.l1 = "Köszönöm barátom!";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "A boldog családi életre, ha-ha!";
			link.l1 = "Egészségünkre!";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, el tudod képzelni, hány lány' szívét törted össze ezzel az esküvôddel? Igen, a fél szigetvilág lányai gyászolhattak az esküvôd után, haha!";
			link.l1 = "Mit tehetek - csak egy kellett, és meg is kaptam. De a lányoknak még túl korán van ahhoz, hogy feldúltak legyenek, mert még mindig itt vagy nekik te, Bernard.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "És ez igaz! Itt végzünk, és azonnal gondoskodom róluk, a fenébe is! Gyere, Charles, igyunk a szerencsédre és a családi életedre! Szóval, ahogy mondani szokták, boldogan, amíg meg nem halunk!";
			link.l1 = "Boldogan, míg meg nem halunk!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "A boldog családi életre, ha ha!";
			link.l1 = "Nagyszerû tószt!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ha, Charles, szóval te is házas és unalmas lettél, mint a mi öreg Nathanunk! A forró viszonyok és minden más már a múlté, mi? Közelítôleg családos ember!";
			link.l1 = "Várj tovább, Bernard! A feleségem nem tartozik azok közé, akik unatkozni fognak egy családi roncs ablak alatt ülve! Az egyetlen dolog, ami változni fog, az a bordélyházi lányok pénztárcájának a telítettsége innen Curacaóig!";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "Nem nagy veszteség, mondom én! Jobb egy aranypénz, mint egy zsáknyi ötcentes. Igyunk egyet! Egészségedre és a feleségedre! Vigyázzatok az aranyatokra és legyetek boldogok!";
			link.l1 = "Köszönöm Bernard. Ó, ez egy nagyon erôs rum. Hú!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "A menyasszonyodra, mármint a feleségedre!";
			link.l1 = "Köszönöm!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "Épp idôben jöttél, Charles, köszönöm!";
			link.l1 = "Mi itt a móka? Azt hittem, már a hajókra rakodnak a kikötôben.";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "Marcus otthagyott, hogy megszervezzem a védelmet a parton. Kevés az emberünk, a kikötôi srácoknak puskapor kell. Gondoltam, beugrom, viszek pár hordót... és aztán ezek a gengszterek. Hah, elbújtak, gondolom, ki akartak várni, vagy ki akartak rabolni valakit. És még mindig tele vagyok Sólyom rummal, szóval nélküled nem tudom, hogy élnék-e még vagy sem.";
			link.l1 = "Mindig szívesen látunk. Rendben, Bernard, te gondoskodj arról, hogy a város biztosítva legyen, én pedig menjek, vigyázz magadra!";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Kapitány, hadd gratuláljak szívbôl neked és kedvesednek ehhez a szerencsés naphoz! Legyetek boldogok és vigyázzatok egymásra!";
			link.l1 = "Köszönöm, Gino. Örülök, hogy eljöttél! Remélem, a helyi... szín nem zavarja?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "Ez... egy nagyon tanulságos utazás. Meg kell mondanom - régóta nem voltam Antiguán kívül, és ebben a társadalomban nem könnyû jól éreznem magam. De te mindig is tudtad, hogyan kell megérteni az embereket, úgyhogy megpróbálok nyugodt maradni, hiszen bízom benned.";
			link.l1 = "Talán valami erôsebbet kellene innod? Nyugodj meg és keress valakit, akivel beszélgethetsz?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Köszönöm, kapitány, van elég hígított borom. Az alkohol, figyelmeztetnem kell, nem tesz jót a májnak és talán a szívnek sem. Ami a beszélgetéseket illeti, a Chirik-Sanango gyógyító tulajdonságairól próbáltam beszélgetni azzal az úrral ott, Manakának is hívják. A maine-i bennszülöttek használják...";
			link.l1 = "Hadd találjam ki - az az úriember nem tudta támogatni a beszélgetést? Gino, a kedvemért és csak ma - kóstolja meg azt a rumot, amit Jan tölt a pultnál. Ha kitalálod az összes összetevôt, Nathaniel Hawk, ott, nagyon le lesz nyûgözve. Biztos vagyok benne, hogy örülni fog a társaságodnak, akárcsak Svenson, a férfi a pultnál, mindketten tisztelik a mûvelt embereket.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "Egészségedre és bájos házastársad egészségére!";
			link.l1 = "Köszönöm, barátom!";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "Kapitány úr, ön az, hála Istennek! Azok az álarcosok, láttam ôket, itt bújtam el, és megpróbálták betörni az ajtót...";
			link.l1 = "Semmi baj, Gino, senki sem fog többé bántani. Nagy szerencse, hogy rád találtam, szükségem van a segítségedre. A barátom megsérült - meglôtték, és sok vért vesztett. Sietnünk kell!";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Lövés... vér... rendben, kapitány. Miközben idejöttem, felkaptam a kempingládámat, benne minden szerszámmal, ha esetleg megsérülne. Vezessetek hozzá, megnézem, mit lehet tenni. És ezek a... álarcosok, talán máshol rejtôzködtek?";
			link.l1 = "Biztos vagyok benne, hogy ôk voltak az utolsók. Gino, csata van a kikötôben, azonnal oda kell mennem. Egyedül kell eljutnod a rezidenciára, nincs messze. A nagy ház a sarkon van - nem fogod elszalasztani. Ne félj - az utcák tele vannak a mieinkkel, és siess, könyörgöm!";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "Kapitány úr, hadd gratuláljak szívbôl önnek és kedvesének ehhez a szerencsés naphoz! Legyetek boldogok és vigyázzatok egymásra!";
			link.l1 = "Köszönöm, Gino. Örülök, hogy úgy döntöttél, eljössz! Remélem, hogy az utazás zökkenômentesen ment?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "Minden rendben, kapitány, köszönöm a gondoskodást. Meg kell mondanom - régóta nem jártam Antiguán kívül, és az elitek között... nem érzem magam túl jól. De az ok, amiért jöttem, nem hagyott más választást. Egyébként - a kiszolgálás kiváló volt, nagyon örülök mindkettôtöknek! A menyasszony ebben a ruhában elbûvölô - ez egy új divat? Kiderült, hogy lemaradtam az életvitelrôl, de nagyon tetszik.";
			link.l1 = "Divat... Valamilyen módon igen, vagy legalábbis hamarosan az lesz. Rendben, érezd jól magad, Gino, és ha a nemes beszélgetôpartnerek unalmassá válnak számodra, akkor gyere a kikötôbe. Az egész legénység a kocsmában van. A fiúk örülni fognak neked.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "Kapitány, még egyszer gratulálok neked és gyönyörû feleségednek! Hosszú és boldog éveket kívánok nektek együtt!";
			link.l1 = "Köszönöm, Gino. Örülök, hogy eljöttél! Remélem, a helyi... szín, nem zavarja?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "Ez a társadalom nem könnyû nekem, hogy jól érezzem magam. De te mindig is tudtad, hogyan kell kiválasztani az embereket, úgyhogy megpróbálok nyugodt maradni, mert bízom benned...";
			link.l1 = "Talán valami erôsebbet kellene innod? Nyugodj meg és keress valakit, akivel beszélgethetsz?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Köszönöm, kapitány, van elég hígított borom. Az alkohol, figyelmeztetnem kell, nem tesz jót a májnak és talán a szívnek sem. Ami a beszélgetéseket illeti, a Chirik-Sanango gyógyító tulajdonságairól próbáltam beszélgetni azzal az úrral, Manakának is hívják. A maine-i bennszülöttek használják...";
			link.l1 = "Hadd találjam ki - az az úriember nem tudta támogatni a vitát? Gino, a kedvemért és csak ma - kóstolja meg azt a rumot, amit Jan tölt a pultnál. Ha kitalálod az összes összetevôt, Nathaniel Hawk, ott, nagyon le lesz nyûgözve. Biztos vagyok benne, hogy örülni fog a társaságodnak, akárcsak Svenson, a férfi a pultnál, mindketten tisztelik a mûvelt embereket.";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "'Most egyedül egy idegen országban, idegennek érzem magam, ezen a fényes ünnepi napon kétszeresen vágyom rokonaim után'";
			link.l1 = "Longway, sosem gondoltam volna, hogy mestere vagy a szónak!";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "Elnézést, kapitány, sokat gondolkodtam. Ezek Wang Wei szavai - egy költôé, aki a Tang-dinasztia egyik korszakában élt, amely réges-régen uralkodott hazámban.";
			link.l1 = "Ezek a szavak olyan gyönyörûek. Remélem, egy nap újra látod a szülôföldedet...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "Lehet-e kezeskedni és tudni, hogy a titokzatos kôlapok boltíve alatt lehetetlen a próbálkozás során olyan átjárót találni, amelyen túl az U-lin-völgy található?'\nNem, kapitány, ezt maga is tudja - Hosszú út nem fog hazatérni. Nos, itt van az otthonom, és ma nagy eseményt tartunk itt! Üdvözletemet küldöm neked és gyönyörû menyasszonyodnak! Legyen boldogságotok olyan hosszú, mint a Jangce folyó, csillagok gyémántjaival ékesítve, lótuszgyöngyök között.";
			link.l1 = "Köszönöm, öreg barátom. A te szavaid nem kevésbé szépek, mint Wang Weié.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "Igyunk egyet, kapitány! Ez a rum elviszi a szomorúságot és felfrissíti az örömöt, nem rosszabb, mint a maotai.";
			link.l1 = "Egészségedre, Longway!";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "Nagyszerû esküvô, kapitány!";
			link.l1 = "Igyál és érezd jól magad!";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Adj egy lángost! Az összes emberünk gratulál neked! Hogy ment a felszolgálás?";
				link.l1 = "Minden rendben van, Charlie! Most már hivatalosan is házas és tiszteletreméltó vagyok, és az elsô tisztem most már madame de Monper.";
			}
			else
			{
				dialog.text = "Üssön meg egy lángossal, ilyen eseményt, kapitány úr! A testvérek majdnem minden bárója itt van! Gondolom, minden spanyol puritán így képzeli el a poklot! És a rum, ez valami különleges, láncos lövés a hordómba!";
				link.l1 = "Igen, az itteniek nem a legtörvénytisztelôbbek, de mi magunk sem vagyunk angyalok, Charlie, és mindegyikük a maga módján kedves nekem.";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Csodálatos, láncdöfés a fenekembe! Kapitány, úgy értem, ez az ünnepség az ön tiszteletére van, nos, én... Gratulálok, úgy értem... én is... Boldogság és... ez, nem vagyok jó a beszédekben. De tudnotok kell, hogy mindannyian szeretünk titeket, és a pokolba is követni fogunk titeket, kapitány!";
				link.l1 = "Köszönöm, öreg barátom.";
			}
			else
			{
				dialog.text = "Várj, úgy értem... Hogy értem egyáltalán, hogy láncos lövés a fenekembe?! Kapitány, úgy értettem, hogy ez a nap az ön tiszteletére van, nos, én... Gratulálok önnek... és egyben... Boldogságot kívánok neked és... és bocsánat, kapitány, lehet, hogy egy kicsit túl részeg vagyok ahhoz, hogy a nyakamhoz tartsak egy beszédes láncdöfést, rég nem voltam józan, ha-ha-ha!";
				link.l1 = "Hah! Semmi baj... köszönöm, öreg barátom.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("Drágaköveket kaptál");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "Ah! És igen, kapitány, fogadja el ezt, kérem. Magának és a hölgyének. Ezeket a köveket egy esôs napra tartogattam... Megértem, hogy nincs hiány aranyból, de ezek nem lesznek feleslegesek, ugye?";
			link.l1 = "Charlie, ön igazán nagylelkû, és ezek a smaragdok remekül fognak mutatni madame de Monper családi fülbevalójában!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "Nos, akkor szurkoljunk ennek, lánclövés az én... hm. Csak örülj, te is és a szépséged is, kapitány!";
			link.l1 = "Úgy lesz, Charlie!";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "Nagyszerû esküvô, kapitány!";
			link.l1 = "Igyál és érezd jól magad!";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Soha nem gondoltam volna, kapitány, hogy nôsnek látom magát. Általában az út, amit választottunk, egy magányos ösvényen vezet egyenesen egy magányos sírba. Emlékeim szerint te vagy az elsô, akinek sikerült lejönnie róla. Megéri a plusz pirítóst, nem igaz?";
			link.l1 = "Ez az, haver! És igazán örülök, hogy életemnek ezt a részét magam mögött hagytam. Egészségedre!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "Egészségedre és a hosszú, boldog közös életedre! A fenébe is, ha rád nézek, eszembe jut, hogy én is voltam egyszer házas.";
			link.l1 = "És te? Házas? Érdekes dolgokat mesélsz! De mi történt?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "Mi az, azt hiszi, hogy mindig is egy vén ciklop voltam, aki puskapor- és vérszagú, kapitány? De nem. Madame Tonzag... azt hiszem, szeretett engem. De aztán történt egy kellemetlen történet. Amelyben a Tonzag házaspár meghalt, és csak a kopasz, sebhelyekkel teli Gaston maradt életben.";
			link.l1 = "Sajnálom, Hercule, nem tudtam...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "Felejtse el, kapitány, az a történet már régen történt. De most, hogy rád nézek, úgy gondolom, hogy a történetemnek még lehet jó vége. Úgyhogy igyunk rá!";
			link.l1 = "Igyunk, pajtás. Tudod - mióta megismertelek, mindig úgy néztem rád, mint a saját apámra, úgyhogy talán egy napon neked is lesz esélyed arra, hogy dédnagyapa legyél. Mindenesetre, egészségedre! A többit el kell intéznem, majd késôbb beszélünk.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "Nagyszerû ünnepség, kapitány!";
			link.l1 = "Igyál és érezd jól magad!";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Itt a kapitányunk! Gratulálok, gyönyörû pár vagytok a feleségeddel! Éljenek boldogan, amíg meg nem halnak!";
			link.l1 = "Köszönöm, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Elküldte Pierre-t";
			dialog.text = "Úgy tûnik, túl józan vagy a saját esküvôdhöz, kapitány. Szeretné helyrehozni? Vettem egy üveg kiváló sherryt a bárban. A helyi rummal keverve remekül megy!";
			link.l1 = "Szeretnék, de valakinek szemmel kell tartania a dolgokat. Különben a "+sTemp+" nem csak a kocsma fog hiányozni, ha eljön a reggel.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "Kitûnô étel és kitûnô rum, kapitány úr! Egészségedre és a fiatal feleségedre!";
			link.l1 = "Köszönjük!";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "Fiatalok, miért törnek be, ha szabad kérdeznem? A hajógyár zárva van, nem tûnik fel? Jöjjenek vissza holnap.";
			link.l1 = "Mester, elnézést a zavarásért, csak átmegyünk a várbörtönökön. Vannak ellátmányok az esküvôre, a kocsmában majdnem elfogyott az ital.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "Ó, Charles de Maure és Nathan Hawk magukra! Az ember valakinek az esküvôjét ünnepli, nem igaz? Rendben - menjetek az üzemanyagért. A fiataloknak szórakozniuk kell - ez a törvény mindenkor. Csak visszafelé ne zörgessétek az üvegeket - én megyek aludni!";
			link.l1 = "Köszönöm, mester, olyan csendesek leszünk, mint a legcsendesebb folyó.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "Gyerünk, ne álljatok, menjetek! Nos, kapitány, mindennel elégedett vagy?";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "Mi a fasz?! mondta Jacques 'Nem jön le ide senki'! Hugo - fuss vissza, hívd a többieket, megtisztítjuk az utat. Öljétek meg ôket, srácok!";
			link.l1 = "Basszus!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "Fiúk, felejtsétek el a ládákat, vendégeink vannak!";
			link.l1 = "Azt hittem, a hozzád hasonló fattyakat Jackman már kinyírta. Rendben, fejezzük be!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "Baszd meg... Megtaláltak minket! Riadó!";
			link.l1 = "El az utamból, seggfej!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "Monsieur de Maure, jó estét, vagy már majdnem reggel van? Jöjjön be, foglaljon helyet.";
			link.l1 = "Angerran De Chievous! Ez az, akin nem lepôdöm meg, hogy látom! A jelentéktelenség, aki csak nôkkel képes harcolni! Te is megkötözted ôket?! Most befejezem, amit a martinique-i párbajban elkezdtem!";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "Nyugodjon meg, fiatalember, látja ezt a fegyvert? Két láda van benne. Lehet, hogy rosszul vívok, de elég pontosan lövök - tegye le a kardját, különben elszalaszt egy-két gyönyörû hölgyet, biztosíthatom.";
			link.l1 = "Szemétláda... A fenébe veled!";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "És ön, kalóz úr, tegye le a fegyvert is, csak úgy, igen. És most - üljön le, töltheti a bort - oda az asztalra. Egy kicsit várnunk kell, amíg Barbazon úr befejezi a barátaid, a kalózbárók hajóinak szétverését. Aztán eldöntjük, hogy mi ketten hogyan rendezzük a... hm, nézeteltéréseinket.";
			link.l1 = "Megoldjuk a nézeteltéréseinket? És hogyan? Párbajt akarsz?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "Ne légy olyan vicces, Charles. Te és Madame Botot sok gondot okoztatok nekem, és én ezt teljes mértékben vissza fogom fizetni. Bár ô sokkal több gondot okozott nekem, mint te... azonban ha te és az impozáns monsieur kalóz csendben leültök, akkor adok egy becsületszót - a feleségeitek életben maradnak. Azt hiszem, a Maine-i spanyol gyarmatokon az ilyen rabszolgákat nagyra értékelik. Még ha nem is hivatalosan. De ez még mindig az élet, nem igaz?";
			link.l1 = "Angerran, gyáva vagy, egy fattyú és... A francba, nincs még megfelelô szó rád semmilyen nyelven!";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "Tudod jól, nincs más választásod. Csak azt ígérhetem, hogy gyorsan fog történni. Szóval, ha szereted ezeket a nôket - viselkedj, mentsd meg az életüket és könnyítsd meg a sorsodat. És igen - zárd be az ajtót, ha nem esik olyan nehezedre. Köszönöm.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "Micsoda harcias hölgyek. Még mindig arra kérlek benneteket, hogy legyetek óvatosak. Soha ne szeressetek nôket ölni.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "Basszus...";
			link.l1 = "Dögölj meg, fattyú!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "Charles de Maure kapitány, Sólyom báró - micsoda kellemes meglepetés! Hadd mutatkozzam be - Mauritz Dussak, ez a nevem.";
			link.l1 = "Tûnj az utamból, fattyú! Hol van a feleségem?";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "Nyugodjanak meg, uraim! Látod ezt a fegyvert? Itt van két bôrönd. Nem véletlenül kaptam ezt a becenevet - szeretem a szablyákat, persze... de jól is lövök, higgyék el. Tegyétek le a kardotokat, vagy elszalasztjátok a hölgyeiteket!";
			link.l1 = "Lemészárollak, mint egy disznót, söpredék...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "De ön már özvegy lesz. Nem akarja? Akkor nyugodjon meg, és tegye le a fegyvert. Sólyom báró, kérem, zárja be az ajtót. Mi pedig megnyugszunk és várunk egy kicsit, amíg Jacques Barbazon ott a kikötôben végez a testvérek vezetôivel.";
			link.l1 = "És most mi következik? Megöleljük egymást és együtt megyünk naplementébe?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "Nem hinném. A fogságodért Jacques arannyal fog elhalmozni, szerencsével talán báró leszek. Ami a nôiteket illeti, talán elengedjük ôket, de ami titeket illet - sajnos... Ha szerencséd van, én fogom kérni a jogot, hogy személyesen ölhesselek meg, kapitány. Híres vívó vagy - érdekes lenne téged próbára tenni. Tudja, én is mesternek tartom magam.";
			link.l1 = "Mestere annak, hogy éjjel betörjek házakba és megkötözzek félálomban lévô nôket? Maga egy féreg, ráadásul - egy funky féreg!";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "Figyeljen, asszonyom, én még sosem öltem nôket, ne akard, hogy elkezdjem, rendben? Idegesíted a kapitányt és a férjedet... A francba!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "Merdo...";
			link.l1 = "Dögölj meg, fattyú!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "Kibaszott francia, nem volt egy szablya vagy egy golyó?!";
			link.l1 = "Tudod, Jacques, mindkettô van számodra. Ôszintén szólva, szinte már bánom, hogy életben hagytalak, amikor rájöttem a Jackmannel való trükködre. De most már helyre fogom hozni.";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "Csak akkor vagy ilyen bátor, amikor a saját embereiddel sétálgatsz? Változtassunk a helyzeten! A bárókkal majd késôbb foglalkozom, de te innen nem jutsz ki élve, patkány!";
			link.l1 = "Várható...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "Kapitány, segítsen, ez a vadember elrabolt engem! I... Haza kell mennem - a nagybácsi valószínûleg már az egész várost felforgatta!";
			link.l1 = "Nyugodj meg, szépségem, minden rendben lesz. Lépjen félre, beszélnem kell a 'savage'.val.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "Köszönöm, kapitány! Megmentettél! Amikor ma reggel felébredtem ezen a parton, nem tudom elhinni, hogy hozzá akartam menni ehhez a vademberhez, ô...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "Igen, a reggel egy kemény kalapács az éjszakai remény kristályára. Értsd meg. De ô a muszkó törzsbôl származik, és a földje kemény törvényei szerint él. A beleegyezéseddel rabolt el téged, és együtt töltöttétek az éjszakát. Így most az ô istenei szemében férj és feleség vagytok. Menjünk, pakoljunk össze, én pedig rendezem a váltságdíj kérdését a nagybátyáddal.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "Sajnálom ezt az egészet. Tichingitu a törzse törvényei szerint él, de ô jó ember. Kérem, felejtse el ezt az emberrablási történetet.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "Feleség? Az istenei szemében?! Ne, kapitány, könyörgöm, ments meg ettôl! Ez csak... egy kaland volt, ô olyan gáláns és kedves volt, nem úgy, mint ezek a parasztok... De férjhez menni? Túl fiatal vagyok ahhoz, hogy egy vademberhez költözzek!";
			link.l1 = "Ô a tisztem és a legjobb barátom, úgyhogy ne aggódj, jól megfizetem, és a legjobb kunyhót kapod, amire valaha is vágytál. Tichingitu jó vadász, élelmet fog neked szerezni, te pedig gyereket fogsz szülni és bébiszitterkedni.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "Gyerekeket? Élelmet szerezni?! Ne, kapitány, kérlek, ne tedd ezt velem, könyörgöm!";
			link.l1 = "Hát, talán meg tudom gyôzni. De nem lesz könnyû. A Muskogue törzs nagyon komolyan veszi az ilyen dolgokat, ha valaki rájön, hogy ellopott egy squaw-t, és nem ment férjhez...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "Meg kell próbálnod, kérlek! Nem mondom el senkinek, senki sem fogja megtudni! Hazudni fogok a bácsinak, nem ez az elsô alkalom!";
			link.l1 = "Jól van, menj csak, te szépasszony! Megpróbálom távol tartani a barátomat.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "Ellopott engem, mint... mint egy kecskét az istállóból! Elmondom mindenkinek! A nagybácsi meg fogja ölni! Szörnyû a haragja! Spanyol hajókat rabolt ki - rossz vicceket mesélni róla!";
			link.l1 = "Rendben, csitt, szép hölgyem, csitt. Talán húszezer 'érv' a megbocsátani neki ékesszólóbb lesz, mint az én szavaim? Vagy adjam oda a nagybátyádnak, mint váltságdíjat egy feleségért? Elvégre mindenki a szigeten van, nem igaz? Holnap megszervezhetünk egy újabb esküvôt...";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "Ne, ne, kapitány, várjon! Meggyôztél engem. Kitalálok valamit, hogy a nagybátyám ne legyen mérges. Viszontlátásra! És viszlát neked is, csôdöröm a távoli síkságról! Találkozunk, ha legközelebb meglátogatsz...";
			link.l1 = "Igen, így van. Örülök, hogy megegyeztünk. Fuss haza, szépségem.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "Nos, kapitány, mindennel elégedett vagy? A legfinomabb rum, bárányborda, disznósonka, sôt még kiváló bor is a személyes készleteimbôl a tudós barátodnak! És - gratulálok neked és gyönyörû feleségednek!";
			link.l1 = "Köszönöm! El kell ismernem, mindent tökéletesen megszervezett. Remélem, van elég rumkészlet a pincéidben, a reggel még messze van.";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "Ne aggódjon, ha a hordók feneket mutatnak, küldök egy segédet a kikötôi raktárba. Jó szórakozást, monsieur, és ne aggódjon semmi miatt.";
			link.l1 = "Fine, "+npchar.name+". Akkor megyek a vendégeimhez.";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "Mit kíván, kapitány? Sült bordát, füstölt sonkát vagy szegyet? Esetleg bort a jobbik felének?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("A kapitány és felesége egészségére!","Éljen boldogan, amíg meg nem hal, kapitány!","Hosszú életet és boldogságot mindkettôtöknek!"), LinkRandPhrase("Éljen a kapitány és a szépsége!","Kövesse a szerencse a kapitányt és házastársát egész életükön át!","Szép szelet a családi életednek, kapitány!"));
			link.l1 = LinkRandPhrase("Köszönöm!","Köszönöm!","Egészségedre!");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Megôrültél? Hentest akartál játszani? Minden kalóz haragszik rád, haver, úgyhogy jobb, ha elhagyod ezt a helyet.", "Úgy tûnik, haver, hogy megharagudtál. Kinyújtóztatni akartad a kezed egy kicsit? Ne vedd sértésnek, de nincs itt semmi keresnivalód. Tûnj innen!");
				link.l1 = RandPhraseSimple("Figyelj, én helyre akarom hozni a helyzetet...", "Segítsen nekem megoldani a problémát...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "Ah, már vártam a látogatását, fônök. Jan Svenson figyelmeztette, hogy biztosan el fog jönni, hogy ellenôrizze, hogy mennek a dolgok Le Francois-ban. Mindent a saját kezembe vettem, és a mennydörgésre esküszöm, ez a falu jobban fog élni, mint az átkozott Kindman-nal, az ördögök szórakozzanak vele a pokol legsötétebb pincéiben!";
					link.l1 = "Maga Jean David, ugye? Svenson mondott valamit a részemrôl...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" fônök. Le Francois-ban minden rendben van, mint mindig. Miért jöttél? Segíthetek valamiben?";
					link.l1 = "Csak beugrottam megnézni, hogy mennek a dolgok.";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "Mi van a részemmel?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" Mate. Miért jöttél? Segíthetek valamiben?";
				link.l1 = "Csak beugrottam köszönni.";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "Szolgálatára, fônök! Ami a részesedést illeti - minden hónap ötödikén levonjuk az aranyérmék egy részét a srácaink cselekedeteibôl, és annyit vár rád, amennyire szükséged van. A következô hónaptól kezdve jöhetsz érte.";
			link.l1 = "Nagyszerû!";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "A többirôl majd én gondoskodom. Az erdei ördög azt mondta, hogy neked nem lesz idôd olyan apróságokkal foglalkozni, mint Le Francois...";
			link.l1 = "Jól mondták neked. Rendben, Jean, számítok rád, remélem, nem hagysz cserben.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "Minden rendben lesz, fônök. Itt mindent kézben tartok, ha-ha, és ne igyak rumot a napok végéig, ha valamit elrontok!";
			link.l1 = "Rendben, viszlát!";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "Vár rád, fônök. Ez idô alatt összegyûjtöttük neked "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+". Vegye el.";
			link.l1 = "Ha, nem rossz. Szép munka, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "Mindent megteszek, fônök. Jöjjön vissza a következô hónapban, vagy amikor csak akar - a pénze biztonságban lesz nálam.";
			link.l1 = "Rendben, viszlát, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "Megoldottad a problémát? Van fogalmad róla, hogy mit tettél? Mindegy, hozz nekem egy millió pezót, és ráveszem a fiúkat, hogy felejtsék el a tettedet. Ha nem tetszik az ötlet, akkor mehetsz a pokolba.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Rendben, kész vagyok fizetni.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Megvan. Elmegyek.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Jól van. Tekintsd magad újra tisztának. De remélem, hogy nem fogsz többé ilyen undorító dolgokat csinálni.";
			link.l1 = "Nem fogok. Túl drága nekem. Viszlát...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 
