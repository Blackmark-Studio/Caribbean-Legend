// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "Üdvözlet, "+pchar.name+". Jöjjön be, már értesítettek.";
				link.l1 = "Értesítettek? Lehet, hogy valami tévedés történt, excellenciás uram. Azért jöttem, hogy jelentse a küldetése sikeres befejezését, de látom, hogy nincs a legjobb hangulatban.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Örülök, hogy látlak, "+pchar.name+". Tájékozódtam az eredményeidrôl és ami a legfontosabb, hogy sikerrel teljesítetted a küldetésedet! A legjobb oldaladról mutattad meg magad, és örülök, hogy nem tévedtem veled kapcsolatban.";
				link.l1 = "Kaphatnék most már írásos formában egy parancsot a testvérem szabadon bocsátására tôled?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Örülök, hogy látlak, "+pchar.name+". Hallottam a tetteidrôl és ami a legfontosabb, a küldetésed teljesítve! Bár meg kell mondjam, okosabb ötletre számítottam, mint egy frontális támadásra. Sajnálom a halott francia katonákat.\nDe a háború az háború, mindig vannak áldozatok. Te teljesítetted a kötelességedet, és örülök, hogy igazam volt veled kapcsolatban.";
				link.l1 = "Kaphatnék most egy parancsot a testvérem szabadon bocsátására írásban Öntôl?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Örülök, hogy látlak, Charles. Elôször is engedd meg, hogy gratuláljak neked ahhoz, hogy sikeresen teljesítetted a Saint-Pierre kolónia védelmének összetett feladatát a spanyol támadókkal szemben. Briliáns munka, barátom!";
					link.l1 = "Köszönöm, Chevalier.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Örülök, hogy látom, Charles. Elôször is, engedje meg, hogy gratuláljak a Saint-Pierre-i gyarmat spanyol megszállók elleni védelmének összetett feladatának sikeres elvégzéséhez. Nagyszerû munka, barátom! Egy újabb lehetôséget ajánlok önnek, hogy együttmûködjön a haditengerészettel. Franciaországnak nagy szüksége van az önhöz hasonló tisztekre. Remélem, hogy ezúttal józanabb leszel... Vegye át a szabadalmat, Charles de Maure kapitány!";
					link.l1 = "Köszönöm, Chevalier. Örülök, hogy segíthetek az országnak, és alig várom, hogy továbbra is szolgálhassam!";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Charles, csalódást okozol nekem. Meggondolatlan cselekedeteid következtében elvesztetted a szabadalmadat és a rangodat a Királyi Haditengerészetnél. Nincs helye további együttmûködésnek. Leléphet.";
					link.l1 = "Hmm...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Örülök, hogy látlak, Charles. Jelentést!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "A feladatot elvégezték, a San Jose kolóniától kapott váltságdíjat megkapták. De vannak rossz hírek: a csatában az erôd 'Eclatant' elsüllyedt. Figyelmeztettem a kapitányt, hogy vigyázzon, de nem hallgatott rám, és...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "A feladatot elvégezték, a San Jose kolóniától a váltságdíjat megkapták.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "Monsieur, mától kezdve csakis megfelelô egyenruhában lépjen be a termembe!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "Báró, kapitány! Örülök, hogy látom!";
					link.l1 = "A megbízás teljesítve, Chevalier.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", kapitány. Milyen híreket hoz?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "A spanyolok valóban támadást terveztek Kikötô-au-Prince ellen. Hispaniola nyugati végén egy erôs ellenséges hajórajjal találkoztunk. Teljesen elpusztították. However, 'Eclatant' was sunk.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "A spanyolok támadást terveztek Kikötô-au-Prince ellen. Hispaniola nyugati végénél egy erôs ellenséges hajórajra bukkantunk. Teljesen megsemmisült.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Hogy van Mynheer Stuyvesant?";
					link.l1 = "Minden rendben, Chevalier. A szállítás sikeres volt, itt a válasz a levelére.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "Charles, báró... Már vissza is jöttél?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "Nem tetszik a homlokod, Charles. Mit mondott Stuyvesant? Jelentést!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Szó szerint azt mondta: 'mondja meg Chevalier-nek, hogy többé nem ô irányítja Sint-Maartent. Elég volt belôle. Ami pedig az anyaállami ellenôrzést illeti - hadd találjon ki valamit, de Poincy-nak sosem volt nehéz mindent a feje tetejére állítani'. Miután ezt az üzenetet bejelentette, mynheer kirúgott a rezidenciáról. Ez volt a tárgyalásaink vége.";
					else link.l1 = "Nos, a következôket mondta: 'a felséged az utóbbi idôben túlságosan mohó volt Sint-Maartenen, úgyhogy itt az ideje, hogy csillapítsa csillapíthatatlan éhségét.' Ezután megpróbált letartóztatni. Egy pengével kellett megtisztítanom az utat a hajóhoz. Ennyit a holland diplomáciáról.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "Kapitány, már vártuk önt. Elmagyaráztam a bárónak a dolgok jelenlegi állását, és ô teljes mértékben támogatta a döntésemet. A hollandok felelni fognak az arroganciájukért.";
					link.l1 = "Akkor háború van?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "Szóval, barátom, látom, hogy elfoglaltad a kelet-indiai hajót az áruval. Kitûnô!";
						link.l1 = "Átadok önnek egy hajót, adjon utasítást a kikötôi tisztviselôknek, Chevalier.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "Van kérdésed, Charles?";
						link.l1 = "Jelenleg nincs, uram. Akkor én megyek is...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "Végre megérkezett, kapitány úr! A Szent Kristófon van egy vészhelyzet!";
					link.l1 = "Egy ellenséges hajóraj?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					dialog.text = "Készen áll a futárhajónk fogadására?";
					link.l1 = "Igen, készen.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "De Maure kapitány, Sir Doily! Örülök, hogy látom! Az egész város végignézte, ahogy ön megleckéztette a spanyol-holland gazembereket, akik a gyarmatunkra vágytak!";
					link.l1 = "Ez volt a kötelességem, Chevalier.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Kezdjük, rendben?";
					link.l1 = "Természetesen, Chevalier. Ezért vagyok itt.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "Örömmel üdvözlöm irodámban a francia királyi haditengerészet ellentengernagyát! Igen, barátom, nem tévedett: Személyesen írtam alá a kinevezésérôl szóló parancsot. Hivatalosan még jóvá kell hagyni Franciaországban, de még csak kételkednie sem kell abban, hogy ez meg fog történni. Gratulálok!";
					link.l1 = "A nemzetemet szolgálom!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "Hamarosan kész lesz."; // в зависимости от времени сколько добирался
					else sTemp = "készen áll és";
					dialog.text = "Sikerrel jártak az erôfeszítései? Doily ezredes elégedett volt?";
					link.l1 = "Minden tökéletesen ment, Chevalier. Stuyvesant karavánját elfogták, az összes rabszolgát Jamaikába vitték, az ezredes "+sTemp+" századát Curacao felé tartva.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "Dicsôség a gyôzteseknek! Gratulálok, gratulálok, barátom! Te mindig lenyûgözöl.";
					link.l1 = "Köszönöm, Chevalier. Stuyvestant megbûnhôdött és kész kártérítést fizetni, a béke helyreállt, Saint Martin most már kizárólag Franciaországé.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "Szóval, barátom, örülök, hogy újra látlak. Jól kipihente magát?";
					link.l1 = "Igen, Chevalier. Szükségünk volt egy kis szünetre... Említett valami kényes ügyet?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "Barátom, te biztos varázsló vagy! Sikerült megcsinálnod egy bravúrt! A bárónk nem akar többé kereskedelmi társaságot alapítani itt.";
					link.l1 = "Azt hiszem, az egyetlen vágya most az, hogy visszamehessen Párizsba.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Charles, hallottál a báróról? Elrabolták a kalózok...";
					link.l1 = "Igen, Chevalier. Sajnos, a báró meghalt. Ezt biztosan tudom.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Charles, hogy haladsz? Azt mondták, hogy a báró felszállt a hajójára...";
					link.l1 = "Igen, Chevalier. A fedélzeten volt, én dolgoztam rajta, de... lázban meghalt.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Charles, hogy haladsz? Azt mondták, hogy a báró felszállt a hajójára...";
					link.l1 = "Igen, Chevalier. A fedélzeten volt, dolgoztam rajta, de... meghalt a csatában.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "Barátom, te biztos varázsló vagy! Sikerült megcsinálnod egy bravúrt! A bárónk nem akar többé kereskedelmi társaságot alapítani itt.";
					link.l1 = "Valószínûleg most Párizsba tart.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "Van kérdésed, Charles?";
				link.l1 = "Jelenleg nem, uram. Akkor én megyek...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Mit akar? Monsieur?";
			link.l1 = "Semmi komoly, csak egy udvariassági látogatás. Most elmegyek...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "Jó napot, Charles. Hadd mutatkozzam be: Philippe de Poincy vagyok, és én...";
			link.l1 = "Mi a fenének zártak be a börtönbe? Ez nem helyénvaló! Francia nemes vagyok és...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "Jó napot... Jó napot! Jó vicc, uram. Honnan tudja, hogy ki vagyok?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "Fiatalember, kérem, ne szakítson félbe! Ön a Karib-tengeri szigetvilág francia gyarmatainak fôkormányzójával beszél! Csak azért bocsátom meg a pimasz hangnemét, mert nem tudhatta, ki áll ön elôtt. De azt javaslom, hogy legyen visszafogottabb.";
			link.l1 = "Hmm... Elnézést, felség.";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "Figyeljen rám, fiatalember, és ne szakítson félbe! Ön a karibi szigetvilág francia gyarmatainak fôkormányzójával beszélget! Csak azért bocsátom meg a hangnemét, mert nem tudta, hogy kivel beszélget. De javaslom, hogy a jövôben legyen visszafogottabb.";
			link.l1 = "Hm... bocsásson meg, excellenciás uram.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Jobb. Ami az elôzô kérdését illeti - Önt - tévedésbôl - spanyol kémnek tekintették, és letartóztatták, amíg státusza tisztázódik. Az átkozott kasztíliaiak az utóbbi idôben egyre aktívabbak lettek, ezért elrendeltem, hogy minden gyanús személyt vegyenek ôrizetbe.\nDe most már tudjuk, hogy ki vagy - te valójában Charles de Maure vagy, Michel de Monper egyik testvére, és személyesen jöttem le ide, hogy szabadon engedjelek. Maga pedig úgy ordítozik velem, mint egy kisfiú!";
			link.l1 = "Bocsásson meg még egyszer, excellenciás uram. Most már szabad vagyok?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Igen, szabad. De szeretnék négyszemközt beszélni önnel, mielôtt az ôrmester kinyitja a celláját. Tudja, hogy a testvérét, a máltai rend egyik legméltóbb harcosát letartóztatták és ôrizetbe vették?";
			link.l1 = "Csak azt tudtam, hogy a bátyám bajban van, és segítségre van szüksége. Ezért jöttem ide Párizsból.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Ezt örömmel hallom. Szeretném, ha tudná, hogy Monsieur de Monper komoly bajban van. Minden okom megvan rá, hogy hatalommal való visszaéléssel, hûtlen kezeléssel és hamis tanúzással gyanúsítsam. De ön segíthet rajta.";
			link.l1 = "Monsieur, tudna többet mondani? Nem értem, Michel volt a rend büszkesége és...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "Én is így gondoltam. Mindannyian azt hittük! De a legutóbbi tettei miatt... elbizonytalanodtunk a rend iránti hûségében, ezért letartóztattuk. Michel maga fogja elmondani a részleteket. Elmagyarázza majd, hogyan segíthetsz neki elintézni a vádakat, és elkerülni a szégyent.";
			link.l1 = "Hol van most a bátyám? Azt mondtad, hogy a börtönben van, de nem láttam a környéken...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "Azt mondtam, hogy bebörtönözve, fiatalember? Figyelsz te egyáltalán?! Azt mondtam, le van tartóztatva! Ez nem ugyanaz. Michel de Monper-t letartóztatásban tartják a Saint Pierre-i földalatti bázison, amely a Máltai Lovagrend tulajdona.\nMegengedem, hogy korlátozás nélkül látogassa a bázist, és olyan gyakran beszéljen a testvérével, amilyen gyakran csak szükségesnek tartja. A rend tisztjei és katonái tisztában vannak az utasításaimmal, és nem fognak megállítani téged.";
			link.l1 = "Hol van az a földalatti bázis?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "Természetesen itt, Saint Pierre-ben. Keresd meg a helyi börtönt, és lépj be a Rend szimbólumaival ellátott ajtón. Menj le a földszintre, a pincében lévô kazamatába, a második szintre. Monsieur Monper ott lesz. De ne aggódj: a börtönbôl kilépve várni fognak és elkísérnek a testvéredhez - mindent elintéztem... Ennyi. Remélem, hogy még találkozunk, Charles. Ôrmester!";
			link.l1 = "Kérem, várjon, excellenciás uram! És mi lesz a... holmimmal? A kardommal és a többivel?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "A holmiját elkobozták, hogy visszafizesse a bátyja adósságát. Viszlát, Monsieur de Maure.";
			link.l1 = "Mi a f...";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "Aha, maga Charles de Maure! Örülök, hogy látom. Gondolom, azért jött ide, hogy megbeszélje velem a bátyja sorsát?";
			link.l1 = "Kész vagyok visszafizetni, amivel Michel de Monper tartozik a rendnek és személyesen önnek.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Hm... De hol van a pénz? Furcsa humorérzéke van, fiatalember, és én nem értem.";
			link.l1 = "Bocsásson meg, Chevalier. Pénzt felejtettem a szekrényemben a hajón. Hamarosan visszajövök.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "Elhozta a pénzt, Charles?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Persze! Remélem, hogy ez az összeg teljesen megtéríti az összes költségét.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Még nem...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "Pompás! Elveszem tôled. A legjobb oldaladról mutatkoztál meg, Charles!";
			link.l1 = "Mikor kapok parancsot Michel de Monper szabadon bocsátására?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "Ne siessen, fiatalember. Csak azt tudom tiszteletben tartani, hogy az adósságokat törleszted, és a családodat véded azzal, hogy a saját életedet teszed kockára. Ritka nemeslelkûség ez manapság... De nem a pénz a fôszereplô ebben a szomorú történetben. A bátyád egy nagyon kényes küldetés teljesítésének feltételei mellett jutott ekkora összeghez.\nMichel de Monper, mint hûséges katolikus, a könyvre esküdött, hogy megtalálja a módját, hogy megbüntessen egy szemtelen eretneket, és helyreállítsa az általa megsértett igazságot a rend és a szent egyház dicsôségére...";
			link.l1 = "De a letartóztatás alatt nem fogja tudni megtartani a szavát! Ha elengeded, ketten sokkal gyorsabban képesek leszünk elvégezni a küldetést, mintha egyedül csinálnám.";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "Látod, barátom, a bátyád nyomós okot adott arra, hogy ne bízzak a tisztességében. Semmi sem garantálja, hogy nem szökik meg és nem szegi meg az esküjét. Ha tehát minden vádat el akarsz venni tôle - magad végezd el az esküt. Monsieur de Monper majd elmondja a részleteket.";
			link.l1 = "Hm... erre nem számítottam. De nem hagy nekem más választást. A végsô döntésemet a bátyámmal való beszélgetés után hozom meg.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "Kezdem igazán megkedvelni magát, Charles. Egy nap talán barátok leszünk. Mindenesetre, ez az utolsó kifejezés, hogy elengedem a bátyádat. A szavamat adom, hogy a családod hírneve nem fog sérülni, ha megteszed, amit a bátyád nem tett meg. És a jövôben számíthatsz a barátságomra.";
			link.l1 = "Teljesen megértettem téged. Viszontlátásra!";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "Ne aggódj, "+pchar.name+", megtartom a szavam. A bátyádat szabadon engedem, és minden vádat el fogok venni tôle. A családod hírneve most már nincs veszélyben. Azt mondanám, hogy ez mind a te érdemed és csakis a tiéd. Apád büszke lehet, hogy ilyen fiút nevelt.";
			link.l1 = "Köszönöm a kedves szavakat, Chevalier. Gondolom, azonnal indulhatok Martinique-ra?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Várj egy kicsit, barátom. Remélem, hogy a barátomnak nevezhetlek, ugye? Személyesen szeretném kifejezni hálámat. Figyelem a fejlôdésedet, mióta ideérkeztél, és a legtöbb tettedrôl tudok. Nagy nevet szereztél magadnak a Karib-térségben, és kétségtelen, hogy a társadalom bizonyos rétegeiben is jól ismert és elismert vagy. Franciaországnak szüksége van az olyan emberekre, mint Ön\nKapitány "+GetFullName(pchar)+"! Ôfelsége, a francia király által rám ruházott hatalommal megtiszteltetés számomra, hogy felajánlhatom Önnek a királyi haditengerészet kapitányi szabadalmát, és hogy az Ön parancsnoksága alá vehetem a francia haditengerészet hajóját, egy könnyû fregattot 'Gryffondor'!\nA volt kapitánya, de Fontenot az Ön jóvoltából Tortuga kormányzója lesz, és a Karib-tenger legjobb könnyû fregattjának kapitányra van szüksége. Elfogadod az ajánlatot?";
			link.l1 = "Érdekes. És mit kapok cserébe?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "Csak egy kicsit. A fogásod egy tizedét, és néha kényes küldetések teljesítését. Várom a döntését.";
			link.l1 = "Senki sem utasítana vissza egy ilyen ajánlatot, excellenciás uram! Megtiszteltetés a nemzetemet szolgálni!";
			link.l1.go = "serve_3";
			link.l2 = "Bocsássa meg, hogy szerénytelen vagyok, de egyelôre vissza kell utasítanom az ajánlatát. A családi ügyeim megkövetelhetik az azonnali visszatérést a hazámba.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Kár. Reméltem, hogy egyetértesz... De mindazonáltal kénytelen vagyok még egy szívességet kérni tôled, ami tulajdonképpen a te érdekedben is áll. Martinique támadás alatt áll. Súlyos harcok dúlnak a kikötôben és magában a városban.\nA sajnos, nincs senki, akit odaküldhetnék, hogy segítsen a helyôrségnek, csak te. Arra kérlek, mint hazád hazafiát, hogy minden szükséges eszközzel verjétek vissza a támadást. Remélem, hogy van elég erôforrásod ehhez.\nMellesleg a testvéred még mindig ott van, megmentheted az életét.";
			link.l1 = "A testvérem veszélyben van? Már úton vagyok!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "Micsoda megtisztelô szavak! Egy igazi katona és a haza hûséges fiának szavai! Gratulálok, monsieur "+GetFullName(pchar)+". Ön megkapja a francia haditengerészeti erôk parancsnoki rangját. Fogadja el tôlem ezt az egyenruhát. Viselje büszkén és legyen méltó rá!";
			link.l1 = "A nemzetemet szolgálom!";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "A nehéz korvett 'Gryffondor' mostantól az ön parancsnoksága alatt áll. Ettôl a pillanattól kezdve ez a kiváló hajó a tiéd. Használja fel kiváló tulajdonságait ôfelsége dicsôségére és a francia befolyás megerôsítésére a Karib-tengeri szigetvilágban!";
			link.l1 = "Azonnal!";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "De a századod már túl nagy, úgyhogy gyere vissza a 'Gryffondor' ért, amikor megszabadulsz egy hajótól.";
				link.l1 = "Rendben. Megteszem.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "A hajóval együtt megkapod a megbízott kapitányt és a legénységet is. Ha akarod, hagyhatod a parancsnokságod alatt, vagy kirendelheted egy hajóról, és mi majd találunk neki egy másik pozíciót.";
				link.l1 = "Megvan!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "De rossz híreim vannak, kapitány. Most értesültem, hogy Martinique-ot megtámadták. Súlyos harcok dúlnak a kikötôben és magában a városban.\nAz önön kívül sajnos nincs senki, akit odaküldhetnék, hogy segítsen a helyôrségnek. Íme az elsô küldetésed:\n Védd meg Saint Pierre-t! Emellett a testvéred még mindig ott van, megmentheted az életét.";
			link.l1 = "A testvérem veszélyben van? Már úton vagyok!";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "Készen állsz arra, hogy 'Gryffondort' a parancsnokságod alá vedd?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Még nem, átrendezem a hajóimat az osztagban...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Igen, készen.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "Nagyszerû! A hajóval együtt megkapod a megbízott kapitányt és a legénységet is. Ha akarod, a parancsnokságod alatt hagyhatod, vagy kirakhatod egy hajóról, és mi majd találunk neki egy másik pozíciót.";
			link.l1 = "Megvan!";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			DelCharleePrince("");
			dialog.text = "És ez csak a kezdet, Monsieur! Biztos vagyok benne, hogy ilyen katonai tehetséggel messzire jutsz! És máris van egy másik megbízásom egy kiváló tengerésztiszt számára, akivel, biztos vagyok benne, hogy ugyanolyan jól fog boldogulni. Ráadásul ez közvetlenül kapcsolódik az elôzô küldetéséhez.";
			link.l1 = "Csupa fül vagyok, monsiuer.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "De elôbb hadd mutassam be önnek azt a személyt, aki belépett az irodámba. Ismerje meg Noel Forget bárót, a Francia Nyugat-indiai Kereskedelmi Társaság tiszteletbeli tagját. Azért érkezett a szigetvilágba, hogy megvizsgálja a gyarmatainkat a cukornád- és egyéb növénytermesztô ültetvények szervezésének bôvítése céljából, valamint hogy feltárja a kereskedelmi kapcsolatok fejlesztésének lehetôségét a térségünkben. Párizsból azt írták elô, hogy mindenféle támogatást és segítséget meg kell adni neki ezekben az ügyekben, amit kétségtelenül meg is fogunk tenni. Báró úr, bemutatom önnek Monsieur Charles de Maure-t, Franciaország egyik legtehetségesebb kapitányát...";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "Tehát, Charles, amíg én és a báró Szent Kristófot vizsgáljuk, a következô feladatot bízom rád. Senki sem támadhat meg francia településeket úgy, hogy azt várja, hogy megússzák, és a spanyoloknak, bár már megkapták a leckét a Martinique-on elkövetett agresszió miatt, a pénztárcájukkal kell felelniük a bûneikért, és meg kell téríteniük a gyarmaton okozott kárt.\nA francia báróval együtt egy erôs hajóraj érkezett, amely egy 66 ágyús, erôs hajóból áll 'Eclatant'. A hajó kapitánya tapasztalt tengerész, de a Karib-tengeren elôször jár, így a te parancsnokságod alá kerül. Együtt 'Eclatant' a spanyol Trinidad szigetének partjaihoz mész, és háromszázezer pezó nagyságú pénzbeli kártérítést követelsz a spanyoloktól a Saint Pierre elleni támadásért.";
			link.l1 = "Chevalier, komolyan azt hiszi, hogy a spanyolok bele fognak egyezni?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Biztos vagyok benne - miután a 'Eclatant' és a századod darabokra robbantotta Fort San Josét. A csapatok partraszállása és a város elfoglalása, a katonák elvesztése, azt hiszem, nem lesz szükség. Támadjatok figyelmeztetés nélkül, romboljátok le az erôdöt, majd jelezzétek a parancsnoknak, hogy meg akarjátok teremteni a feltételeket. Ebben a helyzetben a spanyoloknak nem lesz hova menniük, és inkább fizetni fognak. Mit tennél, ha a védelem nélkül maradt város helytartója helyett cselekednél?";
			link.l1 = "Hmm, ésszerûnek tûnik, Chevalier.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Világos, hogy mit kell tennie?";
			link.l1 = "Igen, felség.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = " Akkor lásson hozzá. Itt egy levél aEclatant kapitányának 'Eclatant' az ön felhatalmazásának megerôsítésével. Ez a kiváló hajó jól képzett legénységgel mostantól az ön rendelkezésére áll. Charles, és ne felejtse el, hogy mostantól Franciaországot szolgálja, és a hozzám hasonló hivatalnokokkal való megfelelô kommunikációhoz tanácsos egyenruhát viselni. Ez tökéletesen illik önhöz. Sok szerencsét, de Maure kapitány!";
			}
			else
			{
				dialog.text = " Akkor lásson hozzá. Itt egy levél a 'Eclatant kapitányának' az ön felhatalmazásának megerôsítésével. Ez a kiváló hajó jól képzett legénységgel mostantól az ön rendelkezésére áll. Ja és Charles: vegyen fel kapitányi egyenruhát, megparancsolom! Elôször is, a francia királyi haditengerészet tisztjéhez nem méltó, hogy úgy nézzen ki, mint egy kereskedô vagy valami kalóz, másodszor pedig az egyenruha tökéletesen illik hozzád. Azonnal hajtsa végre, de Maure kapitány!";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "'Eclatant' sank? Charles, ez egy katasztrófa! Mit fog most mondani a miniszter? Cserbenhagytál, Charles! Biztos voltam benne, hogy számíthatok a tapasztalatodra, és te... Sajnos, de ezért te leszel a felelôs. Írok egy jelentést, te pedig jobb, ha eltûnsz egy idôre. A szolgálata a Királyi Haditengerészetnél véget ért.";
			link.l1 = "Hmm... Sajnálom, Monsieur. Úgy tûnik, tényleg jobb, ha eltûnök egy-két hónapra, amíg a miniszter úr lecsillapodik. Viszlát, és még egyszer nagyon sajnálom, hogy cserbenhagytam.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "Tökéletes!";
				link.l1 = "Tessék, kérem, vegye el ezt a háromszázezret.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Tökéletes, de hol a pénz, Charles?";
				link.l1 = "Huh, a ládában a hajón, mindjárt átadom!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "Szóval, Charles, Trinidadból hoztad a váltságdíjat?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Igen, uram. Itt is van.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "Mindjárt hozom!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "Elégedett vagyok veled, Charles, sosem okozol csalódást. A feladat nem volt könnyû, és a váltságdíjból ötvenezer pezót kapsz jutalmul. Fogadd el, ez mind a tiéd.";
			link.l1 = "Köszönöm, Chevalier.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Máris van egy új feladat számodra. Monsieur Forget befejezte az ellenôrzést Szent Kristófnál, és most szeretné meglátogatni az északi gyarmatainkat. Arra kérem, hogy vigye el a bárót Tortugára és Hispaniolára, segítsen mindenben az ügyeiben, és teljesítse a kéréseit. Világos, Charles?";
			link.l1 = "Természetesen, Chevalier.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "A bárónak kevés az ideje, ezért arra kérem, hogy ne zavarják meg más ügyek, és ne késleltesse az utazást két hónapnál tovább.";
			link.l1 = "Természetesen, Monsieur. A szigetek közötti utazás nem vesz igénybe olyan sok idôt, hacsak Forget úr ügyei a gyarmatokon nem idôigényesek.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Tökéletes. Akkor a báró az ön hajóján fog utazni. Adja meg neki a legjobb kabinját.";
			link.l1 = "Természetesen, Chevalier!";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "És még valami, Charles: megint nincs rajtad a tiszti egyenruhád! Ez az utolsó figyelmeztetés. Ettôl a pillanattól kezdve arra kérem, hogy csak egyenruhában jöjjön hozzám, különben nem hallgatom meg. Ön szolgálatban van, és a fegyelemnek kell lennie mindennek, különösen egy tengerésztiszt megjelenésében!";
			link.l1 = "Bocsásson meg, Chevalier. Ez nem fog még egyszer elôfordulni.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "Nem kételkedtem abban, hogy az útja sikeres lesz. Van valami hír Tortugáról vagy Kikötô-au-Prince-bôl?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "Igen, Chevalier, híreket hozok, de nem túl kellemeseket. Elôször is, Kikötô-au-Prince kormányzója biztos benne, hogy a spanyolok támadásra készülnek a gyarmat ellen, és ehhez egy katonai századot állítanak össze ... em-m, hogy is hívják ... Santiagón, igen. És ez nem tûnik pletykának. Azt hiszem, nem hagyhatjuk figyelmen kívül ezt az ügyet, különösen azért, mert a Kikötô-au-Prince-i ültetvények az egyik legjobbak közül valaha is láttam.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "A spanyolok Kikötô-au-Prince megtámadására készülnek? Hmm... Rendben. Megbízzuk, hogy foglalkozzon ezzel a Charles de Maure kapitánnyal. 'Eclatant' most javították meg, felszerelték, és készen áll a kihajózásra...";
			link.l1 = "És még valami, uram: Párizsban Saint Martin szigetét, amely innen északra fekszik, francia gyarmatnak tekintik, de Charles de Maure kapitány azt mondta nekem, hogy ott a hollandok irányítanak. Így van, Chevalier?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "Hmm... Ez bizonyos mértékig igaz. Saint Martin francia gyarmat. Azonban, Baron, gazdasági szempontból ez a sziget teljesen használhatatlan - a terület kicsi, a talaj ott sovány, sovány, az édesvíz kevés, és ami a kutakban van, az iszapos és keserû. Még azt is mondták, hogy az esôvizet ott gyûjtik ivásra.\nEzért Saint Martint hosszú távú bérletre átadták a Holland Nyugat-indiai Kereskedelmi Társaságnak, amely a Társaság hajóinak északi tranzitpontjaként használja a térségbôl a metropoliszba tartó hajók számára. A hollandok kibôvítették az ottani Phillipsburg települést, erôdöt és kikötôt építettek, és azok számára, akik viszonylag nemrég érkeztek a szigetvilágba, mint Charles de Maure kapitány, Saint Martin holland gyarmatnak tûnik.";
			link.l1 = "De de jure a sziget hozzánk tartozik?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Természetesen igen. De mint mondtam, jövedelmezôbb pénzt kapni a bérleti díjért, mint használni a szûkös erôforrásait.";
			link.l1 = "Nekem úgy tûnik, hogy ez a sziget nagyon hasznos lenne a francia Nyugat-indiai Kereskedelmi Társaság számára, amikor megjelenik a Karib-tengeren. A jelentését az imént közölte - az északi elôôrs az Európába vezetô úton. Meg kell látogatnom ezt a gyarmatot, és nagyon valószínû, hogy a sziget hollandoknak történô bérbeadása megszûnik.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Elôször is meg kell küldeni egy megkeresést Willemstadba, a Holland Nyugat-indiai Kereskedelmi Társaság igazgatójához, Peter Stuyvesant pénzverdéjéhez. Neki engedélyt kell adnia a sziget megtekintésére - elvégre a hollandok már régóta ott vannak.";
			link.l1 = "Aztán el kell küldenünk egy futárt Willemstadba.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "A gond csak az, hogy mynheer Stuyvesant ritkán van jelen Willemstadban, állandóan úton van, és a gályáján intézi a Társaság ügyeit...";
			link.l1 = "De legalább néha jelen van ott, gondolom? Mindenesetre a hollandok kötelesek biztosítani a sziget ellenôrzését a jogos tulajdonosoknak. Miért nem küldünk egy levelet Philipsburg kormányzójának?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Mynheer Martin Thomas, minden tiszteletem az övé, de ô csak egy egyszerû alkalmazott, az igazi irányítást a Társaság végzi. Báró, meg fogom oldani ezt a problémát, ne aggódjon, idôbe telik.";
			link.l1 = "Nos, nekem rengeteg idôm van. Elvégre még meg kell látogatnunk a déli gyarmatokat, Guadeloupe-ot és Martinique-ot. Kár, hogy Charles de Maure kapitány ezúttal nem tart velem - neki ismét Hispaniolára kell mennie...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "Igen, igen, unalmas beszélgetéseinkkel késleltetjük kedves kapitányunkat! Charles, vigye a 'Eclatant' századhoz, nyomuljon Hispaniola felé, és derítse ki, hogy a spanyolok valóban fenyegetik-e Kikötô-au-Prince-t. Ha vannak, akkor gondoskodjatok róla. Azonban nem az én dolgom, hogy tanítsalak, te mindent jobban tudsz, mint én. Ha nem találsz semmit, akkor ne vesztegesd az idôdet, nekem itt van rád szükségem. Várlak a jelentéssel legkésôbb egy hónap múlva. Sok szerencsét, barátom!";
			link.l1 = "Köszönöm, Chevalier. Azonnal kihajózom.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "És még valami, Charles: úgy hallottam, hogy gondjaid vannak a holland hatóságokkal? Kérlek, rendezd ezt a kérdést minél hamarabb, a közeljövôben meg kell látogatnod a gyarmataikat. Mint érti, ez lehetetlen lenne az erôdök tûz alatt.";
			link.l1 = "Rendben, uram, meglesz.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "És még valami, Charles: figyelmeztetlek: kerülj minden konfliktust a hollandokkal. A közeljövôben meg kell látogatnod a gyarmataikat. Mint érted, ez lehetetlen lenne az erôdök tüze alatt...";
			link.l1 = "Rendben, Monsieur. Nincs vita a hollandokkal.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "'Eclatant' sank? Charles, ez egy katasztrófa! Mit fog most mondani a miniszter? Cserbenhagytál, Charles! Biztos voltam benne, hogy számíthatok a tapasztalatodra, és te ... Sajnos, de ezért te leszel a felelôs. Írok egy jelentést, te pedig jobb, ha eltûnsz egy idôre. A szolgálata a Királyi Haditengerészetnél véget ért.";
			link.l1 = "Hmm ... Sajnálom, Monsieur. Úgy tûnik, tényleg jobb, ha eltûnök egy-két hónapra, amíg a miniszter úr lecsillapodik. Viszlát, és még egyszer nagyon sajnálom, hogy cserbenhagytam.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "Kiváló! Amíg vannak olyan kapitányok a haditengerészetünkben, mint te, addig nem kell félnünk a kasztíliaiak trükkjeitôl. Holnap küldök egy futárt Kikötô-au-Prince-be egy küldeményt és egy levelet Franciaországból, és egyúttal személyes levélben hagyok egy utalást Monsieur Jeremy Deschamps du Mussaca úrnak, hogy jó lenne megköszönni a szolgálatot, így biztosíthatom, hogy te, Charles, megkapod a jól megérdemelt kitüntetést.\nÉs most pedig térjünk át a következô feladatodra. Igen, barátom, van egy új megbízásom számodra, ezúttal azonban nem katonai, hanem nagyon kényes, és szeretném, ha elvégeznéd.";
			link.l1 = "Csupa fül vagyok, Chevalier.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Gondolom, emlékszik a beszélgetésemre Monsieur Forget úrral Saint Martinról? Biztosítanunk kell a bárót, hogy a gyarmatot átvizsgálták, és ön Curacaóra, Willemstadba, Peter Stuyvesant társasági igazgatóhoz megy. Ô most is ott van, és még három hétig ott lesz. Emellett el kell kísérned a Társaság áruját szállító fluytot Curacaóba, és át kell adnod Mynheer Stuyvesantnak egy levelet tôlem.";
			link.l1 = "Ez minden feladat?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Igen, kapitány. Tájékoztasson Mynheer Stuyvesant válaszáról. Éppen idôben leszünk, mielôtt Monsieur Forget visszatér a martinique-i és guadeloupe-i útjáról, és végre meglátogathatja Saint Martint, amelyet nagyon szeretne meglátogatni.";
			link.l1 = "Rendben van. Mehetek?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "Megengedi, Charles. Ne tartson túl sokáig, a báró nem szeret várni. És amikor Peter Stuyvesantot meglátogatod, mindenképpen vedd fel az egyenruhádat! Mindennek hivatalosan kell kinéznie, ha érted, mire gondolok.";
			link.l1 = "Természetesen, Chevalier. Viszontlátásra!";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Köszönöm, kapitány, adja ide... (olvasás)... Hát akkor, kiváló! Peter Stuyvesant azt mondja, hogy Forget báró meglátogathatja Saint Martint ellenôrzés céljából, és hogy Philipsburg kormányzóját értesítik errôl, és együttmûködik vele. Azt hiszem, a látogatás után a báró helyes döntést fog hozni - a hollandoknak bérbe adandó szigetet meghagyja.\nÉs most pedig a legszívmelengetôbb hír, kapitány úr! Van néhány dolog, amit el kell mondanom. Elôször is: figyelembe véve az összes katonai teljesítményét, Önt kinevezem 'Kommodornokká'. Fogadja gratulációmat, Monsieur!";
			link.l1 = "Franciaországot szolgálom!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "Másodszor: Kikötô-au-Prince kormányzója küldött nekünk egy kereskedelmi hajót, tele áruval az Ön számára: 500 nagy zsák kávét és további 500 zsák kakaót. Ez mind a Hispaniolán lévô ültetvények termése, azoké, amelyeket ön védett meg a spanyol portyáktól. Emellett egy különösen értékes szállítmányt is nektek szántak - 50 egység lignum vitae-t. Nem hiszem, hogy el kell magyaráznom, mi az. Az árud a capsterville-i bolt raktárában van, és bármikor elmehetsz érte a kereskedôhöz.";
			link.l1 = "Köszönöm, Chevalier! Fantasztikus hírek!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "Ami pedig a következô feladatot illeti: Forget báró bármelyik nap visszatérhet Saint-Christopherbe. Ön elviszi ôt Saint-Martinba, és gondoskodik róla, hogy jól ôrizzék. És, hogy úgy mondjam, közelrôl figyeli majd, mi történik Philipsburgban, és aztán jelentést tesz nekem. Ne hagyja el a várost, kapitány, amint a báró megérkezik - a peonom meg fogja találni, és jelenteni fog.";
			link.l1 = "Minden tiszta. Mehetek?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Elmehetsz. Néhány nap pihenés a szárazföldön jót fog tenni és hasznos lesz számodra.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "Igenis, Chevalier, máris vissza! Holland barátaid Saint Martin mellett az erôd ágyúinak tüzével találkoztak velünk, és három hajóból álló hajórajjal támadtak ránk. Csak Charles de Maure kapitány és legénysége ügyességének köszönhetôen sikerült elmenekülnünk! Úgy tûnik, Mynheer Peter Stuyvesant valójában nem akarja látni a francia király követei Philipsburgban, mit gondol errôl, Chevalier?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "Mit?! Itt van egy levél Stuyvesant-tól személyes aláírásával, amelyben garantálja...";
			link.l1 = "De a Philipsburgi erôd parancsnoka nyilván más levelet kapott Stuyvesant-tól, amelyben azt írja neki, hogy tüzeljen kedvére, és támadjon ránk egy századdal! Ez véletlen volt, Chevalier?! Nem! Nyilvánvalóan ott vártak ránk! Ágyúgolyókkal és sörétekkel!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Báró, könyörgöm... Majd én elintézem. Azonnal elküldjük kedves kapitányunkat, Charles de Maure-t Curacaóba, hogy újra találkozzon Stuyvesant-tal. A kapitánynak nagy tapasztalata van a kényes helyzetek kezelésében... És most megkérem a szolgákat, hogy készítsenek önnek egy fürdôt és egy jó ebédet.";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "Charles, barátom, sietnie kell Willemstadba. Talán Stuyvesant még mindig ott van. Ha nem - derítsd ki, hol van, és keresd meg. A találkozó során mesélj neki az incidensrôl, és követelj magyarázatot. Számítok az ön tapasztalatára és tekintélyére, és megbízom önt a tárgyalások lefolytatásával. Ezután, egy percet sem vesztegetve, jöjjön vissza, és számoljon be nekem a megbeszélés eredményérôl.";
			link.l1 = "A feladat világos, Chevalier. Elôkészítem a hajót és azonnal indulok.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "Ezt nem hiszem el...";
			link.l1 = "Ráadásul a visszaúton megtámadott egy holland hajóraj. Kérem, magyarázza el nekem, Chevalier, mi folyik itt?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "Barátom, tisztában vagyok vele, hogy milyen éleslátó vagy, ezért nem fogok semmit sem eltitkolni elôled. Az egyetlen dolog, amit kérek tôled - amit hallani fogsz, nem szabad, hogy kikerüljön ebbôl a szobából. Megígéri?";
			link.l1 = "Természetesen, Chevalier.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "Jól van, rendben. Biztos vagyok benne, hogy nagyszerû karrier vár rád a francia haditengerészetnél. Természetesen az én segítségemmel az admirális-helyettesi rangig emelkedhetsz! De elkalandoztam... És most, ami a hollandokat és Saint Martint illeti.\nMár jóval azelôtt, hogy önök Saint Martinra jöttek volna, nagy sólelôhelyeket találtak ott. Eleinte senkit sem érdekelt, de aztán a spanyolok Kubában és Hispaniolán nagy érdeklôdést mutattak iránta - a bikák' sózására. Mint azt bizonyára önök is tudják, nem kereskedhetünk közvetlenül Spanyolországgal, ezért...";
			link.l1 = "...létrehoztál egy 'tárgyalót' a Holland Nyugat-Indiai Kereskedelmi Társaság formájában...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "Pontosan! Gyorsan gondolkodik - és pontosan, Charles! És most, hogy tudott a párizsi ellenôrzésrôl, Stuyvesant úgy döntött, hogy bátran teljesen a saját kezébe veszi a sóüzletet, számítva arra, hogy nem szívesen beszélünk mindenkinek a spanyolokkal kötött üzletünkrôl. De ebben tévedett. A francia fôkormányzó kezébôl senki sem mer büntetlenül elvenni! És mi ezt meg is fogjuk neki mutatni.";
			link.l1 = "Ha jól tudom, Forget báró nem tudhat errôl...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "Barátom, teljesen igaza van, a bárónak nem kell tudnia a részletekrôl. Elég történt már: a francia király képviselôjének életére tett kísérlet, a diplomáciai misszió hajóinak megtámadása, vagyis - ön ellen, és ami a legfontosabb: Saint Martin szigetének de facto annektálása! Mindez elégséges indok a hollandok elleni katonai fellépéshez.";
			link.l1 = "Háború?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "Pontosan! Barátom, az admirálishelyettesi pozíció nem áll olyan messze Öntôl, érti? Képzelje el magát a Louvre-ban tartott tárgyalásokon admirálisi egyenruhában, és maga XIV. Lajos is elfogad egy ilyen megtisztelô vendéget... Helyükre kell tennünk a hollandokat! Stuyvesant meg fogja bánni, amit tett. Egyetértesz?";
			link.l1 = "Egyetértek, Chevalier. A hollandoknak felelniük kell felháborító és aljas tetteikért.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Kiváló. Értesítem a bárót a döntésünkrôl, és azonnal futárokat küldök a francia gyarmatokra! Ön pedig, barátom, pihenhet a hosszú út után, és kérem, holnap reggel kilenc után látogasson meg. Elôkészítek neked egy harci feladatot.";
			link.l1 = "Rendben, Monsieur. Engedje meg, hogy elnézést kérjek.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "Nem nevezném háborúnak, inkább békére kényszerítésnek. És ha Stuyvesant meggondolja magát, az csak boldogabbá tesz minket. Ezért kell most megmutatnunk neki, hogy ha megpróbálja magának követelni Saint Martin szigetét, sokkal többet veszít, mint amennyit nyer. És itt jössz te a képbe, Charles.";
			link.l1 = "Hallgatlak.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Saint Martin az Európába tartó holland hajók átrakodási bázisa. A társaság hajói rendszeresen a Philipsburgi öbölben tartózkodnak. Eddig a vizek elég biztonságosak voltak számukra. Mostanáig, kapitány... Elindulsz Saint Martin partjai felé, és a Társaság kereskedelmi hajóinak ôrjáratozásával és elfogásával foglalkozol.\nAz értékes áruk szállítására a Társaság a Kelet-Indiánokat használja - kemény, jól felfegyverzett, nagy rakterû hajókat. Ezek lesznek a célpontjaitok. Foglalj el öt ilyen hajót az árukkal együtt, és hozd ôket zsákmányként Casterville-be. Ezután folytatjuk a tárgyalásokat Stuyvesant-tal, és talán a veszteségek számbavétele után meggondolja magát.";
			link.l1 = "A feladat világos. Mehetek?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "Monsieur, kénytelen vagyok megkérdezni, de nem tudna-e részt venni ennek a hadmûveletnek a finanszírozásában. Hónapokig tartó hajózás lesz ez, folyamatos javítások és veszteségek...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "Attól tartok, a tartalékaink kimerültek, Charles. Az Ecliaton karbantartása és a harcok máris a francia gyarmatok féléves költségvetésének a felébe kerültek. Nos, ez minden, amit most adhatok. Gondolj a jövôbeli díjakra, Charles! Nagy jövô vár rád!";
			link.l1 = "Igenis, uram!";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "Menj, barátom, és a szerencse kövesse minden lépésedet.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "Teljesítetted a feladatot, kapitány. Köszönöm a kiváló szolgálatot! A trófeák eladásából származó bevétel egy részét - kétszázezer pezót - önnek kellene megkapnia.";
				link.l1 = "Örömmel hallom, Monsieur!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "Tehát már csak "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" holland hajók maradtak, amelyeket a mi kikötônkbe hozhat.";
				link.l1 = "Igen, Chevalier!";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "És ez még nem minden. A minap elgondolkodtam egy kicsit... Charles, te tényleg sokat tettél Franciaországért. Az áruló Levasseur kiiktatása, ôszintén szólva, Saint-Pierre védelme a spanyolok alattomos támadásától, a San Jose kolónia erôdjének sikeres legyôzése és a spanyoloktól kapott kártérítés átvétele büntetésül a merész cselért... Ezt követôen pedig személyesen kísérte el az Európából érkezô francia korona képviselôjét, és még az életét is megmentette, amikor a hollandok csapdájából menekült meg a Philipsburgi vizeken!";
			link.l1 = "Monsieur, igazán zavarba hoz engem... Én csak a kötelességemet teljesítem.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Ön szerény, mint mindig, barátom. És most, a következô feladat végrehajtása során, hogy Hollandiát békére kényszerítsük, ismét nem hagytál cserben. Nem félsz ettôl a szótól - a nemzet hôse! Mint a szigetvilág francia gyarmatainak fôkormányzója, nálam van Franciaország legmagasabb kitüntetésének több példánya és ... De egyébként arra kérem, hogy olvassa el ezt a dokumentumot.";
			link.l1 = "Franciaországnak tett kiemelkedô szolgálataiért... Ôfelsége, Franciaország királya nevében... kitüntetést adományoz Franciaország szolgálatában álló tengerésztisztnek, Charles de Maure kapitánynak, Henri de Montpe fiának... Chevalier, viccelsz?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "Egy kicsit sem, barátom. Megtiszteltetés számomra, hogy megjutalmazhatom önt, ahogy megérdemli, Franciaország legmagasabb kitüntetésével, a Szent Lajos-renddel! Hazánk minden polgárának ismernie kell a hôsét! És Saint-Pierre tartozik neked! Megérdemled ezt a rendet, Charles.";
			link.l1 = "Tényleg, nem tudom, mit mondhatnék... Köszönöm, fôkormányzó úr! Esküszöm, hogy továbbra is büszkén szolgálom Franciaországot, és nem hátrálok meg az ellenséggel szemben!";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("Megkaptad a Szent Lajos-rendet! Te vagy a nemzet hôse!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "Egy igazi tiszt szavai! Igazán büszke vagyok rád, Charles. Most pihenj egy kicsit. Megérdemled. Addig is, majd én elintézem a tárgyalásokat Stuyvesant-tal - talán már rájött, hogy sokkal elônytelenebb számára, ha ellenségeskedik velünk, mintha barátok lennénk. Ne hagyd el a várost, két nap múlva szükségem lesz rád.";
			link.l1 = "Rendben, Monsieur. Megvárom a további utasításokat.";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "Igen. Úgy tûnik, Stuyvesant katonai akciókkal kezdett válaszolni a Spanyolországgal való szövetségre. Egy közös holland-spanyol hajóraj ostromolja Saint-Christopher-t. Az ôrszemek óránként jelentenek nekem minden egyes mozgásukról.";
			link.l1 = "Ostrom?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Nyilvánvalóan. Nem indítottak közvetlen támadást, és ez tulajdonképpen jó. Gyorsan kell cselekednünk, kapitány, amíg az ellenségnek nem sikerült blokád alá vennie az egész szigetet.";
			link.l1 = "Mit kell tennünk?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "Saint-Jonesban, Antiguán állomásozik Doily ezredes angol haditengerészeti osztaga. Most éppen Sir Jonathan Foxot látogatja meg. Az ellenséges hajók mellett kell elhaladnia, és el kell jutnia Antiguára. Ott találkozol az ezredessel, átadod neki a levelemet és segítséget kérsz tôle.";
			link.l1 = "Gondolod, hogy az ezredes hajlandó lesz segíteni nekünk?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "Remélem is. A levélnek meg kell gyôznie ôt arról, hogy a segítségéért járó jutalom elég jelentôs lesz... Emellett levelet kell küldenünk a 'Eclatant', jelenleg Guadeloupe partjai közelében tartózkodó kapitányának is, neki Saint-Christopherbe kell sietnie. A 'Eclatant' tüzelési ereje jelentôsen segít a csatában. Mivel nem lehet egyszerre két helyen, a futárszállító luggerünk csatlakozik a századához - sértetlenül kell átvezetnie az ellenséges körön, és elindul Guadeloupe felé, mielôtt a 'Eclatant' déli irányba indulna...";
			link.l1 = "Értem. Menj át az ostromon, kísérd el a futárhajót, és siess Saint-Jonesba Doily ezredeshez a leveleddel.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Pontosan. Készen áll egy újabb hajó felvételére a századába?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Megszabadulok egy hajótól, és visszajövök hozzád.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Igen.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Remek. Vigye a levelet, a teherhajó készen áll és várja a parancsát.";
			link.l1 = "Ne vesztegessük az idôt, Chevalier!";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "Igen-igen, barátom, mindent tudok a szerénységérôl. Maga egy igazi tiszt! És jutalmat fog kapni, biztosíthatom! Gondolom, a nehéz csata után szükséged lesz egy kis pihenésre? Van egy egész hete. Gyere el a szobámba, hogy hét nap múlva beszélgessünk - a város jutalmat készít a hôsének.";
			link.l1 = "Igen, uram. Elmehetek?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Menjen és pihenjen jól. Késôbb komoly kérdésekkel kell foglalkoznunk - Mint látja, a hollandokkal való béke jelenleg lehetetlen. Most az ezredes úrral megbeszélünk néhány fontos kérdést.";
			link.l1 = "Akkor egy hét múlva találkozunk, Chevalier.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "Megbeszélést folytattunk Doily ezredessel, és beleegyezett, hogy segít nekem. Anglia segíteni fog nekünk a hollandok elleni háborúban. Neked és nekem vissza kell vágnunk és helyre kell állítanunk az igazságot - Saint Martin szigetének vissza kell térnie Franciaországhoz. Ezt a feladatot a legjobb tengerészkapitányra bízom - rád, Charles de Maure! Az ellenség még nem heverte ki a hajóraj vereségét, megtámadjuk Philipsburgot, és elfoglaljuk.\nA csata nem lesz könnyû. Elôször is el kell pusztítanunk az erôdöt, aztán meg kell törnünk a helyôrség védelmét...(suttogás) Emellett kényszermarschot kell tennünk a dzsungelen keresztül a sólelôhelyig, amirôl már meséltem, és meg kell ölnünk az ott táborozó ellenséget...";
			link.l1 = "A feladat elég nehéz, Chevalier...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "Tökéletesen megértelek, barátom. Az osztagodat meg fogjuk erôsíteni. Basse-Terre és Saint-Pierre kormányzóinak mostanra egy-egy hajót - egy fregattot - kellett volna elôkészíteniük. Önnek csak Guadeloupe-ot és Martinique-ot kell felkeresnie, és ezeket a fregattokat a parancsnoksága alá venni. Ha persze magad akarod ôket - nem fogok ragaszkodni a hajóválasztásodhoz. Emellett 20.000 pezó formájában támogatást is adok neked, hogy ellátmányt és felszerelést vásárolhass a zászlóshajód számára. Tessék, vegye el...";
			link.l1 = "Rendben, uram.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Továbbá, mint mindig, a hajó 'Eclatant' a parancsnokságod alatt áll. Megjavították és felszerelték, az úttoronyban várakozik, és a kapitánnyal való beszélgetés után bármelyik pillanatban átveheted.";
			link.l1 = "Kiváló!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Nem vesztegethetjük az idôt, kapitány. Ahogy a kémeim tájékoztattak, a hollandok megértették a Saint Martinra leselkedô veszélyt, és meg akarják erôsíteni a védelmét. De még mindig van két hónapjuk. Idôben be kell fejeznie a feladatot!";
			link.l1 = "Majd én... (suttogás) Hol van a Szent Márton sótelep? A sziget egyik térképén sincs jelölve...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(suttogás) Amikor megtámadod a várost, kérdezd ki Philipsburg alkirályát, Mynheer Martin Thomast, ô majd elmondja. Az a holland gyáva, és nem fog ellenállni neked, ezt garantálom.";
			link.l1 = "Értem. Akkor indulhatok?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Várj egy percet, Charles. Még nem kaptad meg a jutalmadat Saint-Christopher megmentéséért. Fogadd el ezeket az aranyládákat a város népétôl, valamint ôszinte hálánkat, amelyet semmilyen pénzösszeg nem fejezhet ki!";
			link.l1 = "Köszönöm, Monsieur!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("Megkaptad a 10 láda dublont.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Most már elmehetsz. Sok szerencsét, kapitány! Mindannyian várjuk a gyôzelmét!";
			link.l1 = "Viszontlátásra, Chevalier.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "A 'Eclatant' hadihajó szintén az én parancsnokságom alá tartozik.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "Ki gondolta volna egy évvel ezelôtt, hogy elôléptetik admirális-helyettesi rangra, barátom? Csak sejteni tudom, hogy apád milyen büszke lesz, amikor ennek híre eléri Franciaországot!";
			link.l1 = "Az én drága apám nagyon fog örülni neki.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "Kiérdemelted a helyed a flottában! Saint Martin visszakerült Franciaországba, Stuyvesant megtanulta a kemény leckét. Ez egy nagyszerû gyôzelem volt! De nem állhatunk meg, nem hagyhatjuk a hollandokat egy percig sem pihenni. Felelôsségre fogják vonni ôket az árulásukért! Doily ezredes most éppen Kikötô-Royalban van, elôkészíti a haditengerészeti századát: Curacaóra lecsapva megtörjük az ellenség gerincét. De erre majd késôbb kerül sor, most két legyet kell ütnünk egy csapásra, Charles.\nA Társaság nem a kereskedelemmel szerezte meg minden mérhetetlen vagyonát. A hollandok bevételeinek fô forrása a térségben az ültetvényeiken végzett rabszolgamunka volt. Ha nem tudnád, Charles: Hollandia a legnagyobb rabszolgatartó és rabszolgakereskedô nemzet. A 'fekete elefántcsontot' hordozó kelet-indiaiak rendszeresen érkeznek Curacaóra Nyugat-Afrikából. És én történetesen tudok errôl valamit, Stuyvesant szerencsétlenségére.\nEzen a pillanatban két holland kelet-indiai hajózik a Karib-tenger felé Guineából. A rakterük tele van fekete foglyokkal. Tíz nap múlva, vagy körülbelül ekkor a karaván elhajózik Trinidad szigete körül Curacao irányába. A feladatod az, hogy megtaláld a karavánt, és elfogd a két kelet-indiai hajót és rakományukat. El kell pusztítanod a kísérôhajókat, és a rabszolgákat szövetségesünkhöz, Doily ezredeshez kell vinned Jamaikára. Ez nagyon fontos, Charles, így elnyerhetjük a bizalmát... Remélem, megérted.\nSajnálom, hogy nem hagyok neked idôt a pihenésre, de ez a feladat fontos és kényes, és csak rád bízhatom.";
			link.l1 = "A szolgálat nem cukor, Chevalier. Ezt mindenkinél jobban tudom. Elôkészítem a hajómat, és indulok, amint tudok.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "Jó szelet és jó utat kívánok, admirális-helyettes. És mire ön visszatér Saint-Christopherbe, közös barátunk, Monsieur Noel Forget befejezi a Philipsburgi szemlét, és én gondoskodom róla, hogy a hollandoktól elvett trófeák egy része személyesen önhöz kerüljön.";
			link.l1 = "Nagyon hálás leszek érte, Chevalier. Elmehetek?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Menjen csak. Sok szerencsét, barátom!";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "Kiváló! Nem ismered a szót 'impossible', Charles. Régebben úgy gondoltam, hogy a bátyád a legjobb tengerésztiszt a Karib-tengeren, de van mit tanulnia tôled, ha megbocsátod ezt a durva összehasonlítást. Azt hiszem, már tudod, hogy ki megy kedves ezredesünkhöz, hogy részt vegyen a Willemstad elleni támadásban.";
			link.l1 = "Egyáltalán nem, Monsieur! Honnan is tudhatnám!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "Á, a híres humorérzéke, kedves barátom! Ha-hah! Természetesen ön lesz az, ellentengernagy úr. A legméltóbb mind közül. Készen áll?";
			link.l1 = "Természetesen, Chevalier. Csak néhány javításra és felszerelésre van szükségem - és máris indulhatok.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "Ne felejtsd el a 'Eclatant' parancsnokságod alá venni. Megjavították és felszerelték, a dokkokban vár rád. Hubert Dassier márki már türelmetlenül várja, hogy újabb csatába indulhasson veled.";
			link.l1 = "Nagyszerû. Pontosan egy hatalmas hajóra van szükségem nagy hatótávolságú golyószórókkal, hogy bombázhassam az erôdöt.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Várj egy percet, Charles. Barátunk, Forget báró híreket hozott neked Saint Martinból.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "Híreim vannak számodra Párizsból. A király aláírta a kinevezésedet az ellentengernagyi posztra. Megkapja a vonatkozó papírokat. Gratulálok Önnek!";
			link.l1 = "Köszönöm, Monsieur! Örömmel szolgálom Franciaországot és a királyt!";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "És én, mint mindig, nagyon örülök, hogy ezeket a szavakat hallom Öntôl. Charles, talán szeretne meginni velem egy kis bort? Egyenesen Párizsból hoztam, ilyet itt egy nap alatt nem találsz!";
			link.l1 = "Köszönöm, chevalier, de azt hiszem, inkább kihagyom. Késôbb vissza kell térnem a hajóra, és nem lenne illendô, hogy Franciaország ellentengernagya részegen álldogáljon a fedélzeten.";
			link.l1.go = "patria_coat_01";
			link.l2 = "Nos, miért ne? Nem minden nap adódik lehetôségem arra, hogy magával a fôkormányzóval igyak egyet!";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "Nos, tarthat egy kis szünetet, nem kell azonnal visszatérnie a hajóra. De ez az ön kívánsága, és én tiszteletben tartom. Rendben, térjünk rögtön az üzletre.";
			link.l1 = "Figyelmesen hallgatom.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "És nem minden fôkormányzónak adatik meg az a szerencse, hogy az ellentengernagya nemcsak a legjobb tengerésztiszt, hanem barátja is, akivel egy asztalhoz ülhet, és távoli hazájából hozott bort ihat!";
			link.l1 = "Franciaországért!";
			link.l1.go = "patria_coat_03";
			link.l2 = "Egészségére, chevalier!";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "És a királyra!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "És a tiédre, Károly!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "Hm, kitûnô bor! Nem gondolja?";
			link.l1 = "Igen, igazad volt. Arra a borra emlékeztet, amit otthon, Gascogne-ban készítenek...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "Egy kicsit tévedsz, barátom - ez Bordeaux. Mindazonáltal, biztos vagyok benne, hogy a gascogne-i bor ugyanolyan jó!";
			link.l1 = "Azt hiszem, kezdem elfelejteni az ízét... Mennyi idô telt el azóta, hogy elhagytam Franciaországot? Egy év? Két év?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "Á, Charles, mintha csak nemrég találkoztunk volna... és nem a legkellemesebb körülmények között. Bocsáss meg, hogy ezt felhozom, de ha valaki akkoriban azt mondja nekem, hogy a börtöncellában elôttem áll a leendô jobbkezem a francia gyarmatokon, valószínûleg hangosan felnevettem volna.";
			link.l1 = "Inscrutabiles sunt viae Domini.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "Elnézést, mit mondott az elôbb?";
			link.l1 = "Ez latinul van, chevalier. Az Úr útjai kifürkészhetetlenek. Senki sem tudja, mit tartogat az élet.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "Mindig megdöbbentesz, Charles. Nézzenek oda - fogalmam sem volt róla, hogy latinul is tudsz beszélni. De másrészt, bizonyos mértékig mi magunk alakítjuk a sorsunkat, nem igaz?";
			link.l1 = "Szerintem mindkettô igaz. Csak az Úr tudja, mi vár ránk. De a kitartóakat megjutalmazza.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "Nem is tudnék jobban egyetérteni. Emlékszem például, amikor átadták neked a tengerésztiszti kinevezést, és odaadták neked azt az egyenruhát. És most itt áll elôttem egy admirális-helyettes, nem kevesebb, mint!";
			link.l1 = "Repül az idô, chevalier.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "Valóban... És még az egyenruháján is látom a szablyák által hagyott vágásokat; néhány vágást már összevarrtak, néhány pedig nyilvánvalóan friss. Ezt ki kell javítani.";
			link.l1 = "Mire gondol, fôkormányzó úr?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "A Karib-tengeri szigetvilág francia flottájának altengernagyi posztján kívül van még egy ajándékom az Ön számára.";
			link.l1 = "Elpirítasz, chevalier. Milyen ajándék?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "Elintéztem a személyi szabómmal - a legjobb a francia gyarmatokon! - hogy varrjon önnek egy rangjához illô egyenruhát. Ne aggódjon a fizetés miatt, mindent elintéztem.";
			link.l1 = "Nagyon hálás vagyok! Mindenképpen meglátogatom a szabóját. Hol találom meg?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "Most éppen a kikötôi irodában kellene lennie - egy új futárhajó érkezett a szárazföldrôl kis csomagokkal. A szabónk mindig rendel néhány olyan anyagot, amit itt nehéz beszerezni.";
			link.l1 = "Akkor megyek a kikötôi hivatalba. Még egyszer köszönöm, monsieur!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "És most, biztos vagyok benne, hogy jól ki kell pihennie magát. Egy hónapot adok önnek, és gondoskodjon róla, hogy jól töltse el. Semmi munka, semmi gond. Minden munkát bízzon a tisztjeire, és pihenjen jól. Használhatja a szobáimat a rezidenciámban. A szolgák a legkényelmesebbé teszik majd a nyaralásodat. Egy hónap múlva újra találkozunk - és egy kényes ügyet kell majd megbeszélnem veled.";
			link.l1 = "Rendben, Chevalier. Viszontlátásra!";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "Igen, Charles. Azt hittem, hogy ezt magam is elintézem, de... sajnos, meg kell kérnem, hogy még egyszer igénybe vegyem a tehetségét. De elôbb adnom kell valamit: háromszázezer pezót és öt láda duplont. Ez a Stuyvesant által nekem fizetett hozzájárulás nagy része az egyezség értelmében. Gondolom, mindezt kiérdemelted, hiszen a munka nagy részét te végezted. Fogadd el. Elégedett vagy, barátom?";
			link.l1 = "A pénz még senkinek sem ártott, Monsieur, ezt a leckét jól megtanultam.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Á, ellentengernagy úr, remélem, nem sértôdött meg a múltban történtek miatt... Ön most a nemzet hôse, tudta? Hogy érzi magát ebben az új pozícióban? Ne feledje: sok érdemes tiszt évtizedeken át mászott a ranglétrán, de tapasztalt kéz nélkül... parancsnoki pozícióban maradtak. Neked azonban, barátom, egyedülálló képességed van arra, hogy mindig elérd a lehetetlent! És van egy barátod a magasban, aki egyben a gyámod is, így ha a jövôben bármilyen problémád adódna, én ott leszek, hogy segítsek neked.";
			link.l1 = "Köszönöm ezeket a kedves szavakat, excellenciád. Az az érzésem, hogy szinte mindent elértem ezen a vidéken. Természetesen az Ön segítségével. Gondolom, most már nyugodtan foglalkozhatok a saját ügyeimmel? Gondolnom kell a családomra.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "Meg akarsz házasodni, Charles? Ah-ha-ha-ha! Mutasson Párizs bármelyik gyönyörû nôjére - és azonnal a magáé lesz! De sajnos, erre még várni kell. Szükségem van rád itt, barátom, legalábbis egyelôre.";
			link.l1 = "Úgy tûnik, Franciaország erôsebb, mint valaha a szigetvilágban. Szövetség az angolokkal, fegyverszünet a Társasággal. Nincsenek problémás... 'Levasseurs' left. Ugye?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "A nemzetek, akárcsak az emberek, mindig többre vágynak, függetlenül attól, hogy mennyi mindenük van... És valóban van egy új 'Levasseur', ellentengernagyunk...";
			link.l1 = "Tényleg? Igen. És ki az?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "Ô a régi közös ismerôsünk, Noel Forget báró. Emlékszik, miért jött ide?";
			link.l1 = "Hmm... Mondott valamit a nyugat-indiai kereskedelmi társaságról. Párizs úgy döntött, hogy létrehozza ugyanazt a szervezetet, mint a hollandok?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Pontosan. A holland társasághoz hasonlóan. De a semmibôl létrehozni egyet nagyon nehéz. Tudja, Stuyvesantnak évtizedes tapasztalata volt a különbözô kontinensekkel folytatott kereskedelemben, fejlett ügynökhálózata és hatalmas kereskedelmi hajóflottája. Franciaországnak ez nincs meg, és ha nem tudnád, Károly, a király most komoly pénzhiánnyal küzd. A kereskedelmet ide terelve szeretnék rendbe hozni a metropolisz anyagi helyzetét, de nem értik, mivel kell szembenéznünk.\nAz angolok és a hollandok rivalizálása, a spanyolok területi törekvései, a kalózkodás virágzása, mint még soha. Minden kereskedelmi flottát el kell kísérnie egy hadihajónak, különben fennáll a veszélye, hogy soha nem jut el a célállomásra. Nekünk pedig nincs olyan hatalmas flottánk, mint a hollandok kelet-indiai flottája, vagy olyan hatalmas gályáink, mint a spanyoloké.";
			link.l1 = "De vajon elmagyaráztad mindezt a bárónak? A kalózokról is?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Persze, hogy elmondtam. És a kalózok Tortugáról való számûzésérôl is, miután az önök küldetése Levasseur eltávolítására irányult, amit a kalózok nem felejtettek el, és mindig is neheztelni fognak ránk. Találkozókat szerveztem különbözô emberekkel, akik megerôsítették az aggodalmaimat, de sajnos ez nem volt hatással a báróra. A miniszterek küldték ide, és ô tartozik nekik... Ez már csak így van.";
			link.l1 = "Huh...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "És ne titkoljuk, hogy egy kereskedelmi társaság a szigetvilágban, közvetlen párizsi irányítással... ön és én, ellentengernagy úr... nekünk itt nincs rá szükségünk.";
			link.l1 = "Megértem, uram.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "Látja, barátom, én nagyon ôszinte vagyok magához... Szóval, teljes szívembôl reméltem, hogy Monsieur Forget meggondolja magát a kereskedelmi társaság létrehozásával kapcsolatban, de... ez nem történt meg. Minden befolyásomat elpazaroltam a báróra, és most neked kell beszállnod a játékba.";
			link.l1 = "Hmm... Mint Levasseur esetében?";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "Ó, Istenem, ne! Kinek nézel te engem, Charles?! A báró egy befolyásos személyiség, a pénzügyminiszter barátja! És különben is, fizikai eltávolításával nem érünk el semmit: egyszerûen csak egy új politikust küldenek Párizsból. Meg kell semmisítenünk azt az ötletet, hogy egyáltalán megszervezzenek egy ilyen társaságot, érted, Charles? Hogy a báró visszatérjen Franciaországba, és jelentse, hogy ez pénzügyileg kockázatos, képtelenség...";
			link.l1 = "Van valami ötlete, Monsieur?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Sajnos, nincs, Charles. Már mindent megpróbáltam. Megijesztettem a hajó- és pénzhiánnyal, a hollandokkal, a kalózokkal... Semmi eredmény.";
			link.l1 = "Úgy tûnik, valami komolyabbra van szükségünk a puszta szavaknál. Hm... Kalózok, azt mondod?";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "Látom, van egy ötleted, barátom? Nem kételkedtem. Zseniális elméd van. Gyôzd meg ezt a bárót, és én gondoskodom róla, hogy apádnak legyen elég pénze, hogy az egész házadat a Louvre-hoz méltó gazdagsággal töltse meg. Megígérem, Charles.";
			link.l1 = "Rendben, Chevalier. A feladat világos.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "Esküszöm, Charles, nem fogja megbánni, ha sikerrel jár. Ebben biztos lehetsz. Elárultalak valaha is, barátom?";
			link.l1 = "Egyáltalán nem, Monsieur. Hol találom a bárót?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "Jelenleg Kikötô-au-Prince-ben van. Azt mondta, nagyon szépnek találja Hispaniola végtelen mezôit és völgyeit...";
			link.l1 = "Nagyszerû. Most pedig engedje meg, hogy elnézést kérjek.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Pontosan. A báró mindent elmondott nekem. Azok után, amin keresztülment... Ön azonban úgy tudja elmagyarázni a dolgokat, mint senki más, ellentengernagy úr! Ezt magától kellene megtanulnom!";
			link.l1 = "Sokat tanultam öntôl, Chevalier.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "Barátom, tartozom neked. Biztosíthatom, hogy drága apádnak mindene meglesz, amire szüksége van vagy valaha is szüksége lesz az életben, és a családi házatok a legjobb lesz a tartományban... és az egyik legjobb Franciaországban. Ezen kívül fizetek neked 100 000 pezót - remélem, ez fedezi a kalózokkal szembeni adósságodat...";
			link.l1 = "Ezt örömmel hallom, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "Egy különleges ajándékot is készítettem önnek. Biztos vagyok benne, hogy meg fogja érteni ennek a tárgynak az értékét, és hogy ôszintén hálás vagyok hûséges szolgálataiért! Tehát, Charles de Maure ellentengernagy, átadom Önnek a Máltai Lovagrend személyes díszkardját! Ez a drága fegyver illik majd az egyenruhájához, azt hiszem! Ha úgy dönt, hogy visszatér Párizsba, Noel Forget báró megígérte, hogy bemutatja önt a királynak - teljes díszben kell eljönnie hozzá: egyenruhában és ezzel a kiváló pengével! Még több dicsôséges karrierlehetôség vár rád a francia haditengerészetnél!";
			link.l1 = "Ez a kard páratlanul szép! Köszönöm, Monsieur, igazán nem érdemlem meg ezt a megtiszteltetést...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("Megkaptad a máltai kardot");
			PlaySound("interface\important_item.wav");
			dialog.text = "De igen! És ha már itt vagy, nagy változások várnak rád. Jó változások. Charles de Maure ellentengernagy, kinevezem önt Saint Martin kormányzójává!";
			link.l1 = "Hah! Jól hallottam?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Igen, barátom. Ön mostantól Saint Martin kormányzója, amelyet oly szorgalmasan védett.";
			link.l1 = "Chevalier, engedje meg, hogy visszautasítsam ezt a megtiszteltetést. Nem kívánok ehhez a szegény szigethez kötôdni! És ezek a belügyek... Én nem erre születtem!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "Nem fogadom el a visszautasítást. Barátom, ne félj: úgy fogsz élni, mint eddig. Az összes unalmas dolgot a jelenlegi megbízott kormányzó fogja elintézni. Te leszel a tényleges kormányzó. Charles, nem érted, miért pont téged neveztek ki Saint Martin kormányzására? Most van itt a megfelelô pillanat, amikor senki sem fog kérdezôsködni. Szükségem van az egyik emberemre, mint kormányzóra, érted, mire gondolok?";
			link.l1 = "A sóbánya?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "Hát persze, hogy értem! És a második jó hír: mostantól kezdve minden hónap 15-én megkapod a bánya hasznának egy részét, valamint a Doily kereskedelmébôl származó nyereséget. A passzív jövedelmed 100.000 pezó lesz havonta.";
			link.l1 = "Hah! Ezt örömmel hallom! Köszönöm, Chevalier. Nos, ha nem leszek kötve, hogy ott üljek, elfogadom a kormányzói posztot. És mi van, ha úgy döntök, hogy Franciaországba hajózom?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "Ha úgy dönt - elmegy, és én, bár nagyon csalódott vagyok, találok ön helyett egy helyettest. De ez még nem minden. Van itt egy levél apádtól. Nézd meg.";
			link.l1 = "Az apámtól? Nagyon izgatott vagyok... Nagyon jó, Monsieur, megegyeztünk. Most már mehetek? Szeretném elolvasni a levelet... Nincs új feladat számomra?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Most nem, kormányzó úr, de ha találok valami munkát, tudom, hol találom önt. Sok szerencsét, Charles!";
			link.l1 = "Önnek is, Chevalier!";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "Az istenit, micsoda katasztrófa! Most már több problémával kell foglalkoznunk. Maga a felelôs ezért, Charles? Mondd meg az igazat. Baleset volt?";
			link.l1 = "Nos, valami rosszul sült el...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "Az istenit, micsoda katasztrófa! Most már több problémával kell foglalkoznunk. A báró nagyon rossz helyet választott a halálához! Biztos vagy benne, hogy nem te segítettél neki elhagyni ezt a világot?";
			link.l1 = "Mirôl beszélsz, Chevalier?! Persze, hogy nem!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "Az istenit, micsoda katasztrófa! Most már több problémával kell foglalkoznunk. Biztos vagy benne, hogy nem segítettél neki eltávozni ebbôl a világból?";
			link.l1 = "Mirôl beszélsz, Chevalier?! Persze, hogy nem!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "Rendben van. Nos, akkor, barátom, talán mégsem ment minden tönkre. A láz az láz, nem igaz? És amíg a minisztérium új felügyelôje meg nem érkezik, addig mi itt feltakarítjuk a rendetlenséget, és jól felfegyverkezve várjuk a vendégeinket... És most, Charles, le kell zárnunk minden kapcsolatunkat. Remélem, érted, miért?";
			link.l1 = "Hát persze.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "Rendben. Nos akkor, barátom, talán mégsem ment minden tönkre. A Karib-tengeren várhatóak a csaták, nem igaz? És amíg a minisztérium új felügyelôje meg nem érkezik, addig mi itt feltakarítjuk a rendetlenséget, és jól felfegyverkezve várjuk a vendégeinket... És most, Charles, le kell zárnunk minden kapcsolatunkat. Remélem, érted, miért?";
			link.l1 = "Hát persze.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "Rendben. Nos akkor, barátom, talán mégsem ment minden tönkre. A kalózok az kalózok, nem igaz? És amíg a minisztérium új felügyelôje meg nem érkezik, addig mi itt feltakarítjuk a rendetlenséget, és jól felfegyverkezve várjuk a vendégeinket... És most, Charles, le kell zárnunk minden kapcsolatunkat. Remélem, érti, miért?";
			link.l1 = "Hát persze.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "Mindenesetre, barátom, mindent megtettél, amit lehetett. És ez jobb, mint a semmi. Örülök, hogy a sors összehozott minket. Megtarthatod a pozíciódat, és biztos vagyok benne, hogy nagyszerû karrier vár rád Franciaországban. És azt hiszem, itt az ideje, hogy visszatérj Párizsba. Tessék, egy levél apádtól. Vedd el.";
			link.l1 = "Az apám? Nagyon szívesen! Rendben, Monsieur, értem. Nincs kapcsolat, teljes titoktartás, és amint lehet - Párizsba megyek. Most már mehetek? Szeretném elolvasni a levelet...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Menj, Charles. Sok szerencsét!";
			link.l1 = "Önnek is, Chevalier!";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "Pontosan. Ön úgy tudja elmagyarázni a dolgokat, mint senki más, admirális-helyettes! Ezt nekem is meg kellene tanulnom tôled!";
			link.l1 = "Sokat tanultam Öntôl, Chevalier.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "Barátom, tartozom neked. Biztosíthatom, hogy drága édesapja mindent megkap majd, amire szüksége van, vagy amire valaha is szüksége lesz az életben, és a családi házuk a legjobb lesz a tartományban... és az egyik legjobb Franciaországban. Emellett 100.000 pezót fizetek neked - remélem, ez fedezi az útiköltségedet, és lehetôvé teszi, hogy jól megérdemelt pihenésed legyen.";
			link.l1 = "Ezt örömmel hallom, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "Hogy tehetted, Charles! Hogy tehetted ezt velem?!";
			link.l1 = "Ahem...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "Tudom, hogy te voltál! Te voltál! Ne tagadd! A te segítséged nélkül Forget báró soha nem szerezte volna meg sem a bánya igazgatójának jelentéseit, sem a bánya helyét, de még Peter Stuyvesant iratait sem. A te neved ott nem hangzott el, de hadd mondjam el, biztosan tudom: te voltál. Miért, Charles? Csak válaszolj... Miért? Michel? Egymillió pezó? Levasseur? Vagy talán a fôkormányzói poszt?";
			// belamour legendary edition -->
			link.l1 = "Emlékszik az elsô találkozásunkra, Chevalier? Hogy a helyemre tettél? Hogyan zsarolt ki tôlem egymillió pezót? Csak azt kívántam, hogy egy nap helyet cserélhessünk. Nincs több mondanivalóm magának.";
			link.l1.go = "patria_prison_2";
			link.l2 = "Levasseur-ért. Egy milliós adósságot még mindig meg tudok érteni. Dolgoztam, öltem, kerestem, raboltam, de minden kárt megtérítettem neked. És ez nem volt elég neked. Te Chevalier öngyilkos küldetésre küldtél a korona ellen, hogy tovább erôsítsem a személyes hatalmadat! Az árulásod választ követelt. És meg is kaptad!";
			link.l2.go = "patria_prison_2";
			link.l3 = "Ambíció, Chevalier. Ebben a furcsa, új világban már szinte mindent elértem, amit csak lehetett. A fôkormányzói poszt számomra figyelemre méltó célnak tûnt. Sokat tanultam tôled. Viszontlátásra!";
			link.l3.go = "patria_prison_2";
			link.l4 = "Hogy ôszinte legyek, nem ismerem magam. Talán azért, mert lenyûgözött a báró és a hazánk iránti hûséges szolgálata? Mindenesetre most már lesz elég ideje, hogy átgondolja ezt a kérdést számomra. Viszontlátásra!";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "Örülök, hogy találkoztunk, Charles. Hallottam a hôstetteidrôl. Ragyogó munka!";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Ez még nem minden, excellenciás uram.";
					link.l1.go = "PZ_2";
				}
				else
				{
					link.l1 = "Kaphatnék egy írásos parancsot, hogy a bátyámat mostantól szabadon engedik az ôrizetbôl?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "Üdvözletem, Charles. Jöjjön be, már értesítettek.";
				link.l1 = "Értesítettek? Lehet, hogy valami tévedés történt, excellenciás uram. Azért jöttem, hogy jelentse a küldetése sikeres befejezését, de látom, hogy nincs a legjobb hangulatban.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ_2":
			dialog.text = "Valóban? Hogy érti ezt, kapitány?";
			link.l1 = "Sikerült Levasseur-t élve elfognom és elhoznom önhöz. Amint végeztünk, elrendelem, hogy hozzák ide.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Soha nem gondoltam volna, hogy ilyesmi egyáltalán lehetséges! Igazán zseniális munka, Charles! Kétlem, hogy még a híres bátyád is képes lett volna jobbat alkotni. Apád büszke lenne rád, barátom.";
			link.l1 = "Köszönöm kedves szavait, Monsieur Philippe.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ_5":
			dialog.text = "Nagyon jó, Charles. Elégedett vagyok veled.";
			link.l1 = "Kaphatnék egy írásos parancsot, hogy a bátyámat mostantól szabadon engedik az ôrizetbôl?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "Talán figyelembe kellett volna vennem, hogy ön nem a bátyja - nem katona, nem titkosügynök, és még nincs tapasztalata a kényes mûveletekben. Nem kellett volna nyíltan katonákkal harcolnia Tortuga utcáin. Kérdezôsködni fognak, és rólam is. Komoly emberektôl érkeznek, ahogy megérti.";
			link.l1 = "Elnézését kérem, Chevalier. Mint tudja, Levasseur nem mondott volna le harc nélkül.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "Igaz, de... mindegy. Nem rossz egy elsô mûvelethez képest. Jelentem, hogy megtámadta a királyi könyvvizsgálót és kíséretét egy hivatalos ellenôrzés során.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "Excellenciád, ha ez segít, elhozhatom Levasseur-t önhöz. Az embereim és én szerencsésen elfogtuk egy félreesô helyen, miután a csatlósai megpróbáltak letartóztatni minket az utcán.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "Kaphatnék egy írásos parancsot, hogy a bátyámat mostantól szabadon engedik az ôrizetbôl?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "Mit mondott, Charles? Mondja még egyszer.";
			link.l1 = "François Levasseur most is a fogdámban van, készen arra, hogy átadjam önnek, Monsieur Philippe.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "Felejtsen el mindent, amit korábban mondtam. Túlreagáltam a dolgot. Remek munka. Nem vagyok benne biztos, hogy még a híres bátyád sem tudta volna ezt megcsinálni.";
			link.l1 = "Köszönöm, Chevalier.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "Nagyon ígéretes vagy, barátom. Bárcsak gyakrabban használnák a tehetségedet az ország javára. De kérlek, próbálj meg ezentúl diszkrétebben viselkedni. A munkánk általában kényes megközelítést igényel. Ó, igen, és még valami.";
			link.l1 = "Igen, ôlordsága?";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
