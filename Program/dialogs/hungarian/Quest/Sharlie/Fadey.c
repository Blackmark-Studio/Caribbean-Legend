int iFadeyPseudoGlobal;

// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> LoyaltyPack
			if (GetDLCenabled(DLC_APPID_1))
			{
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "ready"))
				{
					link.l32 = "Fadey, do you know a man named Alonso?";
					link.l32.go = "LoyaltyPack_Fadey_1";
				}
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "money") && PCharDublonsTotal() >= 1000)
				{
					link.l32 = "Fadey, I'm ready to buy your mirror breastplate.";
					link.l32.go = "LoyaltyPack_Fadey_1000";
				}
			}
			//<-- LoyaltyPack
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "Mit tehetek önért, Monsieur? Nem beszélek olyanokkal, akiket nem ismerek. Ha azért ugrott be, hogy beszélgessünk, vagy hogy megkérdezze, a hónap melyik szakában érkezik a spanyol ezüstvonat Maricaibóba 1640-ben, akkor ki kell ábrándítanom. Nem vesztegetem az idômet üres fecsegésre.";
					link.l1 = "Jó napot, Monsieur Fadey. Ön persze engem még nem ismer, de a bátyámat már ismeri. Engedje meg, hogy bemutatkozzam: Charles de Maure, Michel de Monper testvére.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "Aha, már megint Charles! Kak dela? Ezúttal mi a baj?";
					link.l1 = "Azt mondtad, hogy kiraboltak... Megtaláltad a tetteseket?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "Szóval Charles, elmentél beszélni azzal a vademberrel?";
					link.l1 = "Igen, beszéltem... Ezért jöttem vissza hozzád.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "Á, megint te vagy az, kedves barátom! Nos, elhoztad a váltságdíjat az indiánért?";
					if (CheckAttribute(npchar, "questTemp.Sharlie.Tichingitu_Skidka"))
					{
						if (PCharDublonsTotal() >= 35) // belamour legendary edition
						{
							link.l1 = "Igen. Itt van 35 dublont.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Nem, még nem gyûjtöttem eleget.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 40) // belamour legendary edition
						{
							link.l1 = "Igen. Itt van 40 dublont.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Nem, még nem gyûjtöttem eleget.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ha, hát ez maga Monsieur de Maure! Azt mondtam, gyere be, ne állj ott! Mi szél hozott a házamba?";
					link.l1 = TimeGreeting()+", Fadey, a bátyám mondta, hogy találkozzunk. Azt mondta, hogy segítesz munkát találni.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ha, te vagy az! Mi szél hozta ide, Monsieur de Maure?";
					link.l1 = TimeGreeting()+", Fadey. A bátyám ragaszkodott hozzá, hogy ne beszéljek önnel errôl, de nem tudtam magam távol tartani... ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "Á, öreg barátom! Gyere be, gyere be, "+pchar.name+"! Hogy vagy?";
					link.l1 = TimeGreeting()+", Fadey. Örülök, hogy látom. Valójában, fontos üzleti megbeszélnivalóm van. Fekete arany.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "Á, megint te vagy az, kedves barátom! Megvan a zsákmány? Találtál elég dublont?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "Da, Monsieur Fadey! Itt van az aranyad.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "Nem, csak beugrottam. Még mindig keresem a megfelelô összeget.";
						link.l1.go = "exit";
					}
					
					link.l2 = "Fadey, van egy ötletem. Már nincs szükségem a rabszolgákra. Bocsáss meg, késôbb találkozunk!";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "Á, öreg barátom! Gyere be, gyere be, "+pchar.name+"! Hogy vagy?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", Megint szükségem van a segítségedre.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Fadey. Örülök, hogy látlak. Van egy kis dolgom veled.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Á, megint te vagy az, kedves barátom! Nos, megtaláltad a pénzt?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "Igen, Monsieur Fadey! Itt van a 75 dublona.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Itt van, Monsieur Fadey! Itt van a 40,000 pezó.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "Nem, csak látogatóba jöttem. Még keresem a megfelelô összeget.";
						link.l3.go = "exit";
					}
					link.l4 = "Elnézést, Fadey, de nem engedhetem meg magamnak. Megpróbálok egyedül boldogulni. Viszlát!";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "Gyere be, gyere be, "+pchar.name+"! Látom a szemedben, hogy hallani akarsz a sikeremrôl.";
					link.l1 = "Pontosan, Fadey. Bízom benne, hogy megvan, amit akarok.";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Á, megint te vagy az, kedves barátom! Szóval, megtaláltad a pénzt?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "Vegyél 75 dublont. Megkérem a matrózokat, hogy vigyék ezt a ládát a hajómra. Ó, mihez kezdenék nélküled, Fadey?! Fogalmad sincs, mennyit segítettél nekem!";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Vigyél 40,000 pezót. Megkérem a matrózokat, hogy vigyék ezt a ládát a hajómra. Ó, mihez kezdenék nélküled, Fadey?! Fogalmad sincs, mennyit segítettél nekem!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "Nem, csak beugrottam. Még mindig próbálok eleget gyûjteni.";
						link.l3.go = "exit";
					}
					link.l4 = "Bocsáss meg, Fadey, de le vagyok égve. Tartsa meg az elôleget, remélem, elég lesz, hogy kompenzálja a költségeit ezzel az üzlettel, én pedig megpróbálok egyedül boldogulni. Viszlát!";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				//--> Дикая Роза
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey"))
				{
					dialog.text = "Ah, here you are, good man! When I learned your ship had dropped anchor in our harbor, I hoped you might pay me a visit.";
					link.l1 = "Hello, "+npchar.name+". I won't bore you with a long tale. My companion Mary and I are searching for her father, who vanished without a trace twenty years ago...";
					link.l1.go = "WildRose_Fadey_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2")) 
				{
					link.l31 = "As for Mary's father...";
					link.l31.go = "WildRose_Fadey_return";
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3"))
				{
					dialog.text = "Well, look who it is, "+pchar.name+"!";
					link.l1 = "You positively glow, "+npchar.name+". So, tell me—did you manage to find anything out?";
					link.l1.go = "WildRose_Fadey_16";
					break;
				}
				//<-- Дикая Роза
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "Ah, Marked One - úgy értem "+pchar.name+"! Gyerünk, mondd el, mit hoztál nekem!";
					link.l1 = TimeGreeting()+", Fadey. Örülök, hogy látlak. Azért jöttem, hogy beszéljek veled az üzletrôl.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Fogadok, hogy kíváncsian várja a pappal folytatott lélektani beszélgetésem eredményét.";
					link.l1 = "Hát persze, hogy kíváncsi vagyok! Hogy ment?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "Ah, bocsáss meg, annyira elvonta a figyelmemet a zsebeid csilingelése!";
					link.l1 = "Micsoda kapzsiság, Fadey! Itt van az aranyad.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "Aha, öreg barátom! Gyere be, gyere be, "+pchar.name+"! Szóval, van valami újdonságod?";
					link.l1 = "Helló, Fadey. Ismét a támogatásodat kérem.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "Mi vagy te? Egy szobor? Ha van valamid, akkor mesélj, ha nincs, akkor húzz el, "+pchar.name+"!";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Nézd meg, Fadey. Gondolom ez egy perzsa shamshir, talán egy olyan, amit a gyûjteményedbôl loptak el?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "Jó hírem van a számodra. Van még egy perzsa shamshirem a számodra.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "Van egy harmadik perzsa shamshirem. Ahogy kérte, visszahoztam, amint tudtam.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "A könnyû páncél miatt vagyok itt, amirôl beszéltünk.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, szeretnék vásárolni a híres köteledbôl.";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, szükségem van a segítségedre.";
				link.l1.go = "help";
 				link.l9 = "Nem, jelenleg semmi.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "Mit tehetek önért, Monsieur? Nem beszélek olyan emberekkel, akiket nem ismerek.";
				link.l1 = "Ó, csak beugrottam megnézni, ki lakik itt.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "Á, szóval maga a jó öreg Michel öccse! Ez megváltoztatja a helyzetet! Jöjjön be, jöjjön be, Monsieur, foglaljon helyet. Szeretne egy pohár vodkával koccintani a találkozónkra? Van még néhány üveggel, és örömmel osztoznék az egyiket egy jó barátom testvérével, da!";
			link.l1 = "Bocsásson meg, Monsieur Fadey, de ma este nem áll módomban inni. Inkább rátérnék az üzletre.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Chto vy govorite! Ez a helyi rum gyenge húgyvíz az orosz vodkához képest! Nem tudod, mit hagysz ki, vigyen el a tenger, ha hazudok! Rendben, akkor az üzletre. Csupa fül vagyok, Charles.";
			link.l1 = "Monsieur, gyanítom, hogy amit mondani fogok, az elég kellemetlen lesz, de sajnos a kötelességem arra kényszerít, hogy elmondjam! Michel azt mondta nekem, hogy ön tartozik neki egy csomó pénzzel a vele való szerencsejátékból. Azt is elrendelte, hogy adja át nekem a pénzt, mert a bátyám... jelenleg nem tud személyesen eljönni önhöz.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Ó, fiatalember! Természetesen emlékszem mindenre, és elismerem, hogy tartozom a bátyjának. A szerencsejáték-dolg szent, e kötelesség tiszteletben tartása az egyetlen dolog, ami megment minket a halálos anarchiától és a veszélyes banditáktól! De könyörgöm, kérem, értse meg a helyzetemet! Kellemetlen történet történt velem nemrég - kiraboltak a legpofátlanabb módon!\nAz átkozott tolvajok elvettek mindent, amit csak tudtak, mindent, amit évek munkájával kerestem, moy pénzt és moy felbecsülhetetlen értékû gyûjteményt! Egyszerûen nem tudok most adósságot törleszteni, nyet\nDe, Monsieur de Maure, nem mondok le a kötelezettségeimrôl! Csak azt kérem, hogy jöjjön elém félúton. Mivel most amúgy sincs a birtokomban pénzérme, felajánlom ezt a kiváló, ritka tôrt. Nézze meg!\nEz egy igazi remekmû az acélból, a lopott gyûjteményem büszkesége. Ráadásul indiai sámánok varázsolták el, és erôs rejtett erôkkel rendelkezik! Az indiánok a törzsfônök karma\nNem egyeztem volna bele, hogy elajándékozom, mert nagy összeget fizettem a tôrért, sokkal többet, mint amennyivel tartoztam, de a körülményeket és a nagy testvéreddel való kapcsolatomat figyelembe véve kész vagyok odaadni neked. Beri, ez egy nagyon jó üzlet!";
			link.l1 = "Én tényleg jobban örülnék a pénznek, mint a tôrnek...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "De nincs nálam a pénz, és van nálam ez a ritka elvarázsolt ereklye! Tényleg azt hiszed, drogos moy, hogy más körülmények között ezt a csodálatos varázstôrt kínálnám neked néhány ócska ezüstpénz helyett? Pezót bárhol találsz, még az utcán heverészve is! El kell ismerned, hogy egy kicsit bajban vagyok. Vérzik a szívem, ha csak arra gondolok, hogy megváljak ettôl a hihetetlen mûtárgytól, de a szerencsejáték adóssága becsületbeli adósság, ezért csak neked vagyok hajlandó adni, bár nagyon drága nekem, mert te egy igazi becsületes ember és egy igaz barát vagy.";
			link.l1 = "Rendben, mivel megesküszöl, hogy nincs pénzed, elfogadom ezt a varázstôrödet. Remélhetôleg jó áron tudom majd eladni...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'Eladni'!? Takarodj innen, úgy értem, Charles! Nyet, alig hiszek a fülemnek! Odaadom a legértékesebb javamat, amibôl legalább tízszer többet kapnék vissza Európába, és te ott állsz pimaszul, és azt mondod, hogy csak elmész és zálogba adod!? Miért mentette meg ez a tôr, fiatalember, egy ember életét! Hadd mondjam el...";
			link.l1 = "És mi a rejtett ereje, amit említettél?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Oh, ho ho! Charles, én jó keresztény vagyok, tudod, nem valami indián sámán. Nem ismerhetem ennek a pengének minden rejtett tulajdonságát. De léteznek, oh da! Tartsd a kezedben ezt a tôrt, és érezni fogod a benne rejlô erôt! Vedd el, beri! Mit szólsz hozzá? Érzel valamit?";
			link.l1 = "Hm... Nem érzek semmit. Bár kényelmesen illeszkedik a kezembe.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Ah ha! Tessék! De ez csak a legkisebb tulajdonsága. Ha ezt a tôrt csatában használod, biztos vagyok benne, hogy sok drámai módon fogja megmutatni erejét! Nos, akkor elviszed?";
			link.l1 = "Nos, van választásom? Elviszem, mivel nincs nálad az érme...";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "Spasibo, Charles. Nem fogod megbánni, biztosan nem fogod! Tessék, tessék. És üdvözöld Michel-t a nevemben! Mondd meg neki, hogy ugorjon be néha, amint lehetôsége lesz rá.";
			link.l1 = "Megmondom neki...";
			link.l1.go = "exit";
			link.l2 = "Azt mondta, hogy kirabolták... Megtaláltad a tetteseket?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "Az a baj, hogy nem. Azok a gazemberek kiürítették az egész házat, elszöktek az összes ezüsttel, arannyal, a megtakarításaimmal, amiket évekig dolgoztam. Na, ez általában nem zavar, elvégre egy igazi úriember, még ha el is veszíti mindenét, nem mutathat érzelmeket! A pénznek olyan messze kell lennie egy úriember alatt, hogy aligha érdemes vele foglalkozni. De a legrosszabb az, hogy elrabolták a csodálatos perzsa sámshir gyûjteményemet! Nincs ehhez fogható gyûjtemény az egész Új- és Óvilágban együttvéve. Igazán figyelemre méltó perzsa lovassági kardok...";
			link.l1 = "Perzsa kardok, azt mondja? Elég érdekesen hangzik. Szóval maga gyûjtô?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Szeretek ritka dolgokat gyûjteni... Slushay, Charles, talán tudnátok segíteni nekem ebben a kérdésben...";
			link.l1 = "Segíteni? De hogyan? Úgy érti, hogy elkapjuk a tolvajokat?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "Nyet. Nem érdekelnek különösebben a tolvajok. A perzsa lovassági kardjaimat szeretném visszakapni. Ha megtaláljátok ôket, biztosan meg fogom érni, ígérem.";
			link.l1 = "Hm. De egyáltalán hol keressem ôket? A Karib-tenger környékén? Vagy talán az egész világon?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Hát, talán a szigeteken megpillanthatod ôket néhány utcai kereskedônél, azok a gazemberek fel sem tudják fogni azoknak a lovaskardoknak az értékét, és biztos, hogy ócskavasért fogják eladni ôket. Ha tehát bárhol látjátok a perzsa kardokat, hozzátok el nekem. Képes leszel felismerni ôket?";
			link.l1 = "Azt hiszem, igen. Rendben, nyitva tartom a szemem, és ha látok olyan szokatlan pengéket, amelyek megfelelnek a leírásnak, mindenképpen elhozom neked.";
			link.l1.go = "Sharlie_12";
			link.l2 = "Tudja, nem vagyok szakértôje a finom fegyvereknek. Attól tartok, nem tudok segíteni. Szóval nem lenne tisztességes részemrôl, ha hamis reményt adnék önnek.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Horosho! Remélem, szerencséd lesz, és megtalálod azokat a leleteket, és én majd gondoskodom róla, hogy megérje. Jó vadászatot, leselkedô - mármint kapitány! Da, Charles, el tudod képzelni, nemrég újabb rablási kísérletem volt!\nEgy tolvaj próbált bejutni a házamba néhány nappal ezelôtt\nEz már túl sok volt nekem! Ezúttal azonban nem szökött meg elôlem, sikerült elkapnom, jól elvertem, és átadtam a városi börtön ôrségének. Remélem, hamarosan felakasztják!";
			link.l1 = "Gondolod, hogy ô az egyik tolvaj, aki ellopta a shamshirjeidet?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Kár, de hiába sírunk a Holdért. Da, Charles, el tudod képzelni, hogy nemrég újabb rablási kísérletem volt!\nEgy tolvaj próbált bejutni a lakásomba néhány napja\nEz már túl sok volt nekem! De nem szökött meg elôlem: sikerült elkapnom, jól elvertem, és a helyi börtönbe küldtem. Nem lehetsz boldog más boldogtalansága árán. Remélem, hamarosan felakasztják!";
			link.l1 = "Gondolod, hogy ô az egyik tolvaj, aki ellopta a shamshirjeidet?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "Nyet, nem hiszem. A pénzre hajtott. A szobámban kaptam rajta, ahogy a ládáimban kutakodott\nEgy indián a spanyol fôsziget mély dzsungelébôl. Nevetségesen néz ki, más, mint az itteniek. Teljesen be van festve, és színes jelmezbe van öltözve... Ha gondolod, látogass el a börtönbe, és nézd meg magadnak azt a bolondot, amíg még él.";
			link.l1 = "Hm... Talán majd beugrom és meglátogatom.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Gyerünk, nézzétek meg a szörnyszülötteket... Horosho, Charles, ez egy kellemes beszélgetés volt. Jó utat Martinique-ra, poputniy veterán!";
			link.l1 = "Minden jót, Fadey.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("Tichingitu_SetTichingituJail");
			SetFunctionTimerCondition("Tichingitu_FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Milyen érdekes! Hallgatom.";
			link.l1 = "Fadey, beszéltem azzal az indiánnal. És azért jöttem hozzád, hogy segítséget kérjek, hogy kihozzuk. Szegény fattyú csak enni akart valamit...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Hahaha, és te elhitted ezt a mesét? A fiatalok manapság olyan hiszékenyek...";
			link.l1 = "Fadey, lehet, hogy fiatalabb vagyok nálad, de még én is meg tudom mondani, mikor mondanak igazat, és mikor hazudnak nekem. Különben is, tényleg úgy gondolja, hogy az akasztás megfelelô büntetés egy ilyen bûntényért? Túlzásnak tûnik. Otthon csak néhány korbácsütést vagy megbélyegzést kapna a visszaesô.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Túlzás!? Betört a házamba! Annak a vadembernek nem kellett volna idejönnie! Mit tennél az én helyzetemben? Biztos vagyok benne, hogy a belsôségeit külsôvé változtatnád, és féreghúst csinálnál belôle, da?!";
			link.l1 = "Nem tenném, Fadey. Még mindig dühös vagy az ellopott shamshir gyûjteményed miatt. Ha ez nem történt volna meg, akkor inkább hajlandó lennél jól elpáholni ezt a buta rézbôrût, és seggbe rúgni, nem tévedek?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Ahhhh, Charles... Pont olyan vagy, mint a bátyád... Horosho. Tisztességes üzletemberek módjára fogjuk ezt elintézni. Ha már ennyire akarod ezt az indiánt, kárpótolj az általa okozott erkölcsi és anyagi kárért, én pedig cserébe közlöm a parancsnokkal, hogy nem kívánok feljelentést tenni. Hogy hangzik?";
			link.l1 = "Mennyibe kerül?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ha, máris kezded megtanulni a Karib-tengeri szokásokat, Charles. Százötven aranydublonnal, egy kopijkával sem kevesebb.";
			link.l1 = "Fadey, Isten irgalmazzon...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Horosho, horosho, 40 gold doubloons. But that's the final price. And doubloons, not pesos. Our moneylender will surely have some.";
			if(PCharDublonsTotal() >= 40) // belamour legendary edition
			{
				link.l1 = "I have the required amount right now. Here, take your 40 doubloons.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(Megbízható) Fadey, listen... Megértem a frusztrációdat, de én vagyok az egyetlen, aki hajlandó valódi pénzzel kárpótolni téged ezért a kellemetlenségért.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "Rendben, megyek és hozom, amire szükséged van.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "Messzire mész, barátom. Meggyőztél! 35 arany — nem kevesebb érme!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			npchar.questTemp.Sharlie.Tichingitu_Skidka = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "És siess, Charles! Már csak tíz napod van a kivégzéséig.";
			link.l1 = "Ezt észben tartom. Viszontlátásra!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka"))
			{
				RemoveDublonsFromPCharTotal(35);
				DeleteAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka");
			}
			else RemoveDublonsFromPCharTotal(40); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Nagyon jó. Azonnal írok egy feljegyzést, és ráteszem a pecsétemet, várjon egy pillanatot... tessék. Add ezt oda a parancsnoknak, és viheted magaddal az indiánodat. Nem tudom, hogy pontosan miért aggódsz miatta ennyire, de ez a te problémád. Mit fogsz csinálni, kiállítod egy maszkarádon? Haha, micsoda gondolat!";
			link.l1 = "Isten mindent lát, Fadey. Egy ember életének megmentése nemes cselekedet.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "Az elsô állításoddal egyetértek, de a második vitatható, Charles. Mi van akkor, ha megmentesz egy gyilkost vagy egy erôszaktevôt a kötél végén rá váró igazságszolgáltatástól?  Bah, mindegy, már nem az én problémám. Isten legyen veled. Menj a parancsnokságra, mielôtt a vörösbôrû barátod elsápad a nyakán lévô huroktól...";
			link.l1 = "Máris megyek. Késôbb találkozunk, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "Komoran nézel ki, barátom! Gondolom, rossz híreket akarsz hozni nekem?";
			link.l1 = "Ez a hosszú és rövid összefoglaló, igen. Ôszinte leszek veled, Fadey: Michel azt mondta, hogy átvertél ezzel a 'Chiefs claw' szarsággal. Azt mondta, hogy ez nem mûtárgy, és bármelyik utcai kereskedôtôl megvehetném pár száz pezóért. Körbekérdezôsködtem a fémtárgyakkal kereskedô utcai árusok között. Pontosan ezt az árat adták.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Ó, Monsieur de Maure... Megsebesültem! Meglepett a bátyja. Ezek a félkegyelmû utcai árusok azt mondanak, amit akarnak, de ô! Mondd csak, Charles, ha valaki hozna neked egy régi kétkezes lovagi kardot Nagy Károly idejébôl, és el akarná adni neked, mennyit adnál érte?";
			link.l1 = "Egy kétkezest? Most szórakozol velem, Fadey? Mi hasznom lenne valami rozsdás, öreg hóhérkardból? Ez az Úr Jézus Krisztus tizenhetedik százada! Egy pezót sem adnék érte!";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "Ah, most már látom a rövidlátásodat barátom! Ezzel a hozzáállással sosem fogsz boldogulni. És ha elhoznál nekem egy ilyen leletet, háromszáz dublont fizetnék érte. Kérdezd meg, miért? Mert ez egy régiség, egy történelmi kincs, amit manapság nehéz megtalálni! Nem érted, mégis ítélkezel! \nAz Isten és az Ô Szûzanyja a tanúm, a Fônök karma egy mestermûves tôr, a forrásaim szerint maga Cortez birtokolta. A Hernan Cortez! A legendás hódító, aki kifosztotta Tenochtitlánt és elfogta az aztékok császárát! És te gúnyolódsz, és azt mondod, hogy ez közönséges baromság!\nMellesleg, már mondtam neked, hogy ez nem akármilyen tôr, hanem egy elvarázsolt tôr! Még mindig olyan zöldfülû vagy, hogy nem láttad a Karib-tenger minden csodáját? Varázslatokat és mágiát, rituálékat és átkokat? Charles, ez az Újvilág, a maják és aztékok hazája, akiknek tudása az ilyen ördögi mûvészetekben olyan magasságokba jutott, amelyek számunkra, keresztények számára elképzelhetetlenek!\nEz a tôr rejtett erôkkel rendelkezik. Sajnos még senki sem tudja, hogy miféle erôk. Egyedülálló, hihetetlen lehetôséged van rá, hogy magad derítsd ki, mire képes, és mégis azt állítod, hogy ez egy 'szarság' és a kedves szegény öreg barátod, Fadey megpróbált átverni téged!\nHa csak annyi pénzem lenne, hogy fedezzem a bátyádnak való tartozásomat, azonnal visszaváltanám tôled a hitvány érmédre... Ez egy nagyon értékes tárgy, és az ára nem csak pénzben mérhetô, da!";
			link.l1 = "Rendben, rendben, nyugodj meg Fadey. Hiszek neked. Az érveid elég meggyôzôek, és az a tüzes buzgalom, amit tanúsítasz, vagy az ôszinteségedrôl, vagy a páratlan sikkasztásodról tanúskodik.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Spasiba! Jól tetted, Charles, hogy nem sértôdtél meg, és egyenesen hozzám fordultál magyarázatért. Bízom benne, hogy most már el van vetve a kérdés?";
			link.l1 = "Igen, Monsieur Fadey. Teljesen. És most kérem, engedje meg, hogy távozzam...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Stoi, Charles! Ôszinte leszek, tetszik a stílusa. Talán egy nap mi ketten legjobb barátok lehetnénk. És miért ne tehetnénk meg az elsô lépést a barátság felé már most? Két üveg kiváló orosz vodkát hûtöttem jeges forrásvízben lent a pincében. Mit szólsz, nyissunk ki egy üveggel a bátyád egészségére?";
			link.l1 = "Hm. Sajnálom, Monsieur Fadey, de nekem már ideje lenne a tengerre szállnom. Egy kicsit sietek.";
			link.l1.go = "vodka_no";
			link.l2 = "Legutóbb is felajánlotta, de én visszautasítottam... Udvariatlanság lenne kétszer visszautasítani. Rendben, Fadey. Benne vagyok!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "Kár érte. A vodkához képest a rum csak víz, olcsó moslék. De mivel sietsz, nem tartalak fel tovább. Jó vadászatot, Charles!";
			link.l1 = "Önnek is, Monsieur Fadey...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "Ezt szeretem hallani! Pompás! Foglaljon helyet, és pihenje ki magát! Kérem, Monsieur, érezze magát otthon, amíg én hozom a vodkát. Ó, mennyire hiányoztak az ilyen délutáni baráti beszélgetések! Ah, a vodka jó hideg, biztosan ízleni fog, nazdorovijja! Hadd tegyek ki egy kis savanyúságot és füstölt sonkát.";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Hûha... Szóval, mondd csak, Fadey, hogy megy ez? Hic! Megittunk... két üveg v-vodkát... egyébként! - Te kôkeményen zokogsz, én meg... részeg vagyok, mint egy bûzös borz. Hogy tetszik, mi?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, drogos fiú, nyugi. Mi köze van ennek az egészhez? Épp most ittunk le egy kiváló vodkát. Aludj egy kicsit, és ragyogó szemmel és bozontos farkkal fogsz ébredni. Még a fejed is kitisztul másnaposság nélkül. Majd meglátod.";
			link.l1 = "Igen, a vodka... ez... ez a vodka egyszerûen csodálatos. Soha nem ittam még ehhez foghatót.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ha! Jól mondod! Az a fajta vodka titkos receptek alapján készült, és az én szülôföldemrôl, Oroszországból szállították, és még ott sem tudja mindenki, hogyan kell helyesen elkészíteni. Én csak a legjobbat veszem! Mint ezt a cuccot itt, amit mi ketten már volt alkalmunk megkóstolni.";
			link.l1 = "De mondd csak, Fadey: h-hogyan tudsz ennyit inni és nem berúgni? Hogy csinálod ezt, mi? Oszd meg velem a titkot. Talán késôbb még hasznodra válik... Hic!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ha! Nos, nem hasonlíthatod össze magadat és engem, ifjú Charles! Csak nézz magadra, sovány vagy, mint egy ostor. Ráadásul nem is szoktál komolyan inni, da! De mivel igaz barátok vagyunk, megosztok veled néhány titkot arról, hogyan kell úgy inni, hogy ne pisáld össze magad.";
			link.l1 = "P-kérlek d-csináld...hic!";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "Nos, ha inni akarsz, és nem akarsz azonnal berúgni, be kell tartanod néhány fontos szabályt. A legfontosabb, hogy soha ne igyál, ha üres a gyomrod. Egyél valami kiadósat, mielôtt elkezdôdik az ivászat\nMásodik, ne felejts el enni valamit minden pohár után. Hús vagy hal lesz a legjobb, valami finom és sós. Harmadszor, ne mossa a szája belsejét a vodkával, nyelje le egyszerre\nSzintén, ha a fôétel elôtt iszik egy kis - legfeljebb fél korsó - felest, az felkészíti a szervezetét a komolyabb alkoholadagok befogadására. Ne vidd túlzásba ezt az elôételt, különben a hatás éppen ellenkezôleg fog hatni, és még a vitorlázás elôtt tönkreteszed magad\nVégül a fegyelmezett edzés a kulcs, a rum vagy más alkoholfajták rendszeres, mérsékelt fogyasztása ellenállóbbá tesz.";
			link.l1 = "Hm-mm... Szóval így kell csinálni! Én d-definitíve...hic!... megjegyzem az összes instrukciódat, Fadey. Köszönöm. És most azt hiszem, jó ötlet lenne, ha aludnék egyet, mert most nem érzem magam túl jól.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Pihenj egy kicsit, Charles. Kellemes esténk volt, neked és nekem! Jó vadászatot nektek!";
			link.l1 = "D-d-do svidaniya, Fadey! Én megyek... hic! - a Kívánságteljesítôhöz!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "Mi az, tényleg azt mondta, hogy segítek neked?";
			link.l1 = "Hát, nagyjából. Segítenél a régi barátod testvérének? Nem mintha koldusként kérnék alamizsnát. Arra kérlek, hogy adj egy lehetôséget, hogy pénzt keressek.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "Ó, Charles! Elkéstél. Ha korábban jöttél volna, megtaláltam volna a megfelelô dolgot számodra, de most - prosti. Ne aggódj, sétálj a városokban, beszélgess az emberekkel. Sok a tennivaló a Karib-tengeren.";
			link.l1 = "Értem, ez sajnálatos. Viszontlátásra!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "Hm. Nyet, természetesen nem utasítom vissza. Ha etetni akarsz egy embert, ne halat adj neki, hanem horgászbotot. Nem így van, Monsieur de Maure? Szóval munkát keres... Nem nehéz. Beszélek egy ismerôsömmel, és beajánlom magát neki. És minden más attól függ, hogy mennyire jól végzi a munkát.";
			link.l1 = "Csodálatos. Kivel kell beszélnem?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Jöjjön be holnap a boltba. Egy Gerard LeCroix nevû férfi fog várni rád. Ô majd ad neked munkát. Csak holnap estig fog itt ülni a telepen. Találkozz vele hamarosan, és végezd el a munkát rendesen. Ne hozzon kellemetlen helyzetbe.";
			link.l1 = "Megegyeztünk. Köszönöm, Fadey!";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ah, miben segíthetek, barátom?";
			link.l1 = "Fadey, figyelj, tényleg szükségem van ötven rabszolgára csempészektôl. A gond az, hogy ismeretlen vagyok számukra, és szükségem van rád, hogy bemutass nekem. Nélküled meg sem hallgatnának, és ez élet-halál kérdése egy nagyon fontos ember számára.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "Oh ho! Látom, elágazik az üzleted! Milyen jövedelmezô! Segítek neked, kedves barátom. De mint tudja, nem dolgozom ingyen. 150 aranydublon kell ahhoz, hogy meggyôzzem az eladót a jó szándékodról, hogy megvegye a négereket, és persze egy kis plusz a szorgos munkámért...";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "Nem vártam mást, Monsieur Fadey! Itt van az aranyad.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "Azonnal megyek az uzsoráshoz! Tartson ki, Monsieur Fadey, mindjárt jövök!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Fadey, úgy tûnik, kitaláltam valamit, és nincs szükségem többé a négerekre. Sajnálom, uram. Viszlát!";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "Kitûnô, barátom. De ha meg akarsz csapni azzal, hogy szükséged van a vásárlásodra, és az értéktelen célokra történik, akkor nagyon fel fogsz dühíteni. Ezt nem akarod. Holnap tíz órakor, napnyugtakor a Capster Beachen, szervezek neked egy találkozót, ne ültess fel.";
			link.l1 = "Nincs miért aggódnod, visszajövök az áruért.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Helló helló! Mondd csak, jóember, mi szél hozta szerény házamba?";
			link.l1 = "Fegyverekre van szükségem. A helyi kereskedôk nem tudnak annyi mennyiséget találni, amennyire szükségem van, de úgy gondolom, te tudsz nekem segíteni.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "Elôször is, kedves barátom, mondd meg, hogy pontosan mire van szükséged. Aztán megmondom, hogy pontosan tudok-e segíteni.";
			link.l1 = "Szükségem van 30 katonapisztolyra, két gyufaszálas muskétára, 70 töltényre hozzájuk és 90 gyógyitalra.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name + ", Megijesztesz engem. Elôször ötven néger, aztán fegyverek. Rabszolgalázadást akarsz kirobbantani, barátom?";
					link.l1 = "Nagyon éleslátó, Fadey. Mint már mondtam, mindez egy fontos személy megmentéséhez szükséges. Ne aggódjon, kihúzza a spanyolok karmai közül, így az itteni hírneve nem fog csorbát szenvedni.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "Ezt jó hallani. Segíthetek.";
			link.l1 = "Örömmel hallom. Mennyit?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "Örülök, hogy elmagyarázta. És ha tényleg a spanyolokhoz van köze, akkor segítek. De ha kiderül, hogy átvertél, akkor nagyon dühös leszek.";
			link.l1 = "Bízz bennem, Fadey. Mennyire?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "Horosho, szóval... pisztolyok és pár muskéták, puskaporral és golyóval mindegyikhez... Ezért... Nem ígérhetem, hogy mindent megkapok, amit kértél, de mindent megteszek, ami tôlem telik. Addig is, szükségem van 40.000 pezó elôlegre, vagy 75 dublonnak, ha úgy tetszik.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "Vegyél dublont, Fadey. Véletlenül van nálam most is néhány.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Az összes dublonom elfogyott, vegyél pesót, Fadey.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Beszélnem kell a bankárommal. Mindjárt jövök!";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Elnézést, Fadey, de nem engedhetem meg magamnak. Megpróbálok egyedül boldogulni. Viszlát!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Jöjjön el holnap, "+pchar.name+", és meglesz az anyag, amire szüksége van.";
			link.l1 = "Akkor nem leszek útban. Holnap találkozunk!";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Jöjjön el holnap, "+pchar.name+", és meglesz az anyag, amire szüksége van.";
			link.l1 = "Akkor nem leszek útban. Holnap találkozunk!";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "Nos, fiam, szerencsés voltam, hogy mindent megtaláltam, amit kértél ilyen rövid idô alatt. Hálás lehetsz! Most pedig, a végsô fizetség. Adj pontosan annyit, amennyit elôlegként adtál, és vedd el a fegyvereidet.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "Vegyél 75 dublont. Az embereim elviszik a fegyvereket a hajómra. Mihez kezdenék nélküled, Fadey? Fogalmad sincs, mennyit segítettél nekem!";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Vigyél 40 000 pezót. Az embereim elviszik a fegyvereket a hajómra. Mit tennék nélküled, Fadey? Fogalmad sincs, mennyit segítettél nekem!";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "A fenébe, hogy is felejthettem volna el a pénzt? Hamarosan visszajövök.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Elnézést, Fadey, le vagyok égve. Tartsa meg az elôleget, remélem, elég lesz, hogy kompenzálja a költségeit ezzel az üzlettel kapcsolatban, én pedig megpróbálok egyedül boldogulni. Viszlát!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey fegyvereit felpakolták a hajóra");
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "A rászorulókon segíteni megtiszteltetés. Segíteni azoknak, akik fizetnek, öröm. Ha legközelebb Basse-Terre-ben jár, feltétlenül látogasson meg, hogy köszönjön nekem.";
			link.l1 = "Ez abszurd - Basse-Terre-ben lenni és nem találkozni a barátommal, Fadey-vel! Viszlát legközelebb!";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey fegyvereit felpakolták a hajóra");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "A rászorulókon segíteni megtiszteltetés. Segíteni azoknak, akik fizetnek, öröm. Ha legközelebb Basse-Terre-ben jár, feltétlenül látogasson meg, hogy köszönjön nekem.";
			link.l1 = "Ez abszurd - Basse-Terre-ben lenni és nem találkozni a barátommal, Fadey-vel! Viszlát legközelebb!";
			link.l1.go = "exit";
		break;
		// <-- legendary edition
		
		//--> Дикая Роза
		case "WildRose_Fadey_4":
			dialog.text = "What a scheme you've set in motion, "+pchar.name+"! The intent, no doubt, is noble, yet is it feasible? Twenty years can do anything to a man...";
			link.l1 = "You're right, Fadey. But we've spent much time and effort, come a long way — and we're almost at the goal. We've learned nearly everything about him: his name, his service in His Majesty's Royal Navy, the name of the ship he served on... and some other details of his biography. The trace ends at the wreck that occurred off Cape Catoche in June 1638.";
			link.l1.go = "WildRose_Fadey_5";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey");
		break;

		case "WildRose_Fadey_5":
			dialog.text = "Catoche? Oh-ho, good man, I wouldn't be driven to those parts with a stick — there wander hordes of cursed savages. If he ended up there and did not perish in the sea, then, plain as God's day, the damned natives made a meal of him...";
			link.l1 = "We have evidence that this man survived the wreck and afterwards managed to reach Cuba. Perhaps he met his end there, but from what we've heard — he was crafty enough to avoid the inquisitors' clutches. Unlikely he stayed on Cuba — more likely he settled in one of the Archipelago's settlements...";
			link.l1.go = "WildRose_Fadey_6";
		break;

		case "WildRose_Fadey_6":
			dialog.text = "Many wonders occur in this world, my friend, and anything may be. But I still do not see why you have told me all this.";
			link.l1 = ""+npchar.name+", you have more connections than some governors. I'm sure you have able men at hand who can perform simple tasks...";
			link.l1.go = "WildRose_Fadey_7_1";
			link.l2 = ""+npchar.name+", you are a respected and influential man. You move in high circles and have connections. I am sure your business interests reach far beyond Guadeloupe. Since you cannot do all this alone, you surely use trusted agents and clever men capable of carrying out not-too-complex assignments...";
			link.l2.go = "WildRose_Fadey_7_2";
		break;

		case "WildRose_Fadey_7_1":
			dialog.text = "You are a clever and perceptive man, "+pchar.name+". Indeed, you've been told that before. I do have capable and knowing men, you speak truth. But tell me plainly — what do you want them to do.";
			link.l1 = "I'd ask you to send them to several colonies of the Archipelago to try to learn something about the man we seek. Perhaps someone heard of him, or even knew him personally. I'll cover the expenses in full, of course. "+npchar.name+", this is very important to Mary, and we have nowhere else to turn.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Fadey_7_2":
			dialog.text = "You are a clever and perceptive man, "+pchar.name+". Indeed, you've been told that before. I do have capable and knowing men, you speak truth. But tell me plainly — what do you want them to do.";
			link.l1 = "I'd ask you to send them to several colonies of the Archipelago to try to learn something about the man we seek. Perhaps someone heard of him, or even knew him personally. I'll cover the expenses in full, of course. "+npchar.name+", this is very important to Mary, and we have nowhere else to turn.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Fadey_8":
			dialog.text = "Can I refuse such a good friend as you, "+pchar.name+"? Especially since you are ready to spend on this godly matter. So tell me the name of the man you wish to find.";
			link.l1 = "As for the name, I'm not certain, but I think he might have been called Rupert Casper or Joshua Northwood.";
			link.l1.go = "WildRose_Fadey_9";
		break;

		case "WildRose_Fadey_9":
			dialog.text = "Very well, we'll find the fellow if he went by the names you say...";
			link.l1 = "Excellent, "+npchar.name+". Shall we discuss payment for your services?";
			link.l1.go = "WildRose_Fadey_10";
		break;

		case "WildRose_Fadey_10":
			dialog.text = "An unpleasant business, but, alas, necessary.";
			link.l1 = "Then let's begin. He would hardly risk going among the Spaniards or Dutch. The man left trouble in Antigua, so no point searching there, nor probably on Barbados. He might have settled on the Western Main, on Jamaica after the Spaniards were driven out, in French colonies, and perhaps even in pirate settlements.";
			link.l1.go = "WildRose_Fadey_11";
		break;
		
		case "WildRose_Fadey_11":
			dialog.text = "I'll say plainly, dear friend: in all the time I've lived in Basse-Terre, I never heard of a gentleman by either of those names. So there's no need to search here. On Martinique and Saint Christopher I know English gentlemen, and he is not among them either.";
			link.l1 = "Then the search area is considerably narrowed.";
			link.l1.go = "WildRose_Fadey_12";
		break;

		case "WildRose_Fadey_12":
			dialog.text = "We must check Tortuga, certainly — and I'll have the same fellow visit La Vega, Puerto Principe and Port-au-Prince. I'll dispatch my capable men to Belize and Blueveld, and also to Jamaica and Isla Tesoro.";
			link.l1 = "And how much will all this cost me?";
			link.l1.go = "WildRose_Fadey_13";
		break;

		case "WildRose_Fadey_13":
			dialog.text = "These are knowledgeable, industrious men, and thus for each of them you'll pay one hundred and fifty doubloons. The emissary I send to Tortuga and Hispaniola with Cuba should be rewarded extra — fifty gold coins on top. After all, four settlements are not one.";
			link.l1 = "So that makes 800 doubloons... Shall we proceed to settlement of accounts?";
			link.l1.go = "WildRose_Fadey_14";
		break;

		case "WildRose_Fadey_14":
			dialog.text = "Right, why waste time? Do you have the required sum on you, good man?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Of course. Here, take it.";
				link.l1.go = "WildRose_Fadey_14_pay";
			}
			else
			{
				link.l1 = "Hmm... I do not have the full sum with me.";
				link.l1.go = "WildRose_Fadey_14_nopay";
			}
		break;

		case "WildRose_Fadey_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Splendid, my dear friend! I will dispatch written orders to my agents at once, and they will set to work. They'll need to find ships bound that way, which will take some time. The journey itself depends on the wind's strength, and that is in our Lord's hands. But I understand my men should return within a month.";
			link.l1 = "So we'll meet in a month, "+npchar.name+". Thank you again. You've been a great help. Until then!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2");
		break;

		case "WildRose_Fadey_14_nopay":
			dialog.text = "I understand, "+pchar.name+", the sum is sizable. I'll await you at my place once you've procured it.";
			link.l1 = "I'll return soon.";
			link.l1.go = "exit";
			pchar.questTemp.WildRose_Etap5_Fadey_2 = true;
		break;

		case "WildRose_Fadey_return":
			dialog.text = "I remember your matter, dear friend. I suppose you've gathered the eight hundred doubloons?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l21 = "Here you are, Monsieur Fadey! Here's your gold. Everything as agreed.";
				link.l21.go = "WildRose_Fadey_14_pay";
			}
			link.l31 = "I'm still gathering the required sum, but don't worry — I won't delay long.";
			link.l31.go = "exit";
		break;

		case "WildRose_Fadey_16":
			dialog.text = "It succeeded, my friend — oh, how it succeeded! All my men returned with nothing but one thing. Jerome Sauvernier, whom I sent to Belize, did not return — but he sent word. With good news for you.";
			link.l1 = "He sent you a letter? May we read it?";
			link.l1.go = "WildRose_Fadey_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Fadey_17":
			dialog.text = "Of course, "+pchar.name+". I kept it specially for you, knowing you'd want to read it. Please, my friend.";
			link.l1 = "Thank you, we'll read it now.";
			link.l1.go = "WildRose_Fadey_18";
			AddQuestRecordInfo("WildRose_Records_6", "1");
		break;

		case "WildRose_Fadey_18":
			dialog.text = "I haven't seen such a smile on your face for a long time, good man!";
			link.l1 = "No wonder, "+npchar.name+"! We've waited so long! But you know, we believed in success! I don't know how to thank you for being such a crucial part of it.";
			link.l1.go = "WildRose_Fadey_19";
		break;

		case "WildRose_Fadey_19":
			dialog.text = "Oh, stop that, brave fellow! You are my friend, and friends must help one another. Come back to me soon — I'm sure Monsieur Jerome will recover quickly and board the first ship...";
			link.l1 = "I think we'll hasten matters. We'll go to Belize ourselves and speak with your agent. Thanks again, "+npchar.name+". You can't imagine what you've done for us! Until we meet!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_5");
		break;
		//<-- Дикая Роза
		
		//--> LoyaltyPack
		case "LoyaltyPack_Fadey_1":
			dialog.text = "My dear friend Alonso Pimentel who serves on your vessel? Ha! But of course. Every time your ship makes port, that good fellow always stops by for a drink. Few friends remain to me, "+pchar.name+". I treasure each one.";
			link.l1 = "Alonso told me amazing stories about your war adventures. He even gave me your bandolier.";
			link.l1.go = "LoyaltyPack_Fadey_2";
			DelLandQuestMark(npchar);
		break;

		case "LoyaltyPack_Fadey_2":
			dialog.text = "I hope and trust that he kept the most remarkable ones to himself. But since Alonso has shared our friendship with you, I have a curiosity for you as well. Behold!";
			link.l1 = "Is that... armor?";
			link.l1.go = "LoyaltyPack_Fadey_3";
		break;

		case "LoyaltyPack_Fadey_3":
			dialog.text = "Ah, my friend. This is all that remains of my mirror armor that I wore during that accursed war. And later, near Smolensk, I had occasion to\n"+
			" Be that as it may, even in this condition it looks magnificent and protects even better. And it doesn't fit me at all anymore!";
			link.l1 = "Looks exotic... even for these parts. A magnificent gift, Fadey. Thank you.";
			link.l1.go = "LoyaltyPack_Fadey_4";
		break;
		
		case "LoyaltyPack_Fadey_4":
			dialog.text = "For you, my friend, merely one thousand doubloons.";
			if (PCharDublonsTotal() >= 600)
			{
				if (GetSummonSkillFromName(pchar, SKILL_Commerce) >= 60)
				{
					link.l1 = "Allow me to correct you, dear Fadey. A thousand doubloons would be for a full suit of armor. But for just the breastplate?";
					link.l1.go = "LoyaltyPack_Fadey_5";
					Notification_Skill(true, 60, SKILL_COMMERCE);
				}
				else if (PCharDublonsTotal() >= 1000)
				{
					link.l1 = "No wonder you and Alonso get along. Here's your gold.";
					link.l1.go = "LoyaltyPack_Fadey_1000";
					Notification_Skill(false, 60, SKILL_COMMERCE);
				}
			}
			link.l2 = "Ha! You almost had me there, Fadey! Perhaps another time.";
			link.l2.go = "LoyaltyPack_Fadey_MoneyLater";
		break;
		
		case "LoyaltyPack_Fadey_MoneyLater":
			dialog.text = "Of course, no rush. My mirror armor will always be waiting for you.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LoyaltyPack.Fadey = "money";
		break;
		
		case "LoyaltyPack_Fadey_5":
			dialog.text = "Oh, you're a sharp one! Very well then, I'll part with it for six hundred gold pieces.";
			link.l1 = "No wonder you and Alonso get along. Here's your gold.";
			link.l1.go = "LoyaltyPack_Fadey_600";
		break;
		
		case "LoyaltyPack_Fadey_1000":
			dialog.text = "A good bargain. I thank you and entrust my mirror armor to worthy hands. And take care of Alonso, captain.";
			link.l1 = "Who's taking care of whom here...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(1000);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_600":
			dialog.text = "A good bargain. I thank you and entrust my mirror armor to worthy hands. And take care of Alonso, captain.";
			link.l1 = "Who's taking care of whom here...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(600);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_end":
			DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_Fadey_DlgExit");
		break;
		//<-- LoyaltyPack

		case "guardoftruth":
			dialog.text = "Nos, ki kételkedne abban, hogy üzleti ügyben jöttél, barátom! Sajnos most nincs vodka, amit megkínálhatnék, mindet megittam. Mondja, milyen bajban van most?";
			link.l1 = "Egy helyi egyházközségnek egy bizonyos magánhajós egy arany mellkeresztet ajánlott fel lazurittal a bûnei bocsánatáért. Egyedi és értékes darab. A probléma az, hogy ezt a keresztet egy másik plébániáról lopták el. Nem mellesleg a rablás során megöltek egy papot.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ó szeplôtelen Teotokos! Ne is mondd!";
			link.l1 = "Igenis. Én képviselem a kirabolt plébániát, és megpróbálom visszaadni a keresztet az eredeti tulajdonosoknak.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Nemes cselekedet, és nagyon jámbor. Próbálsz pontot szerezni a Mindenható elôtt?";
			link.l1 = "De a helyi atya nem hajlandó visszaadni nekem, hiába mondtam neki. Nem értem. Hogyan lehet nyugodtan elhelyezni egy ellopott keresztet, amelyen egy ártatlan ember vére van, Isten házában? Ez istenkáromlás!";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Nos, gyakorlatilag minden megszentelt kehelyen az ártatlan Krisztus vére van... de elkalandoztam. Gondolom, azt akarja, hogy segítsek?";
			link.l1 = "Igen! Maga nagy befolyással bír Basse-Terre-ben. Tisztelnek téged, így talán a pap meghallgatja majd a figyelmeztetéseidet.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", Elmondta a papunknak az ellopott kereszt pontos történetét?";
			link.l1 = "Persze, hogy elmeséltem! Felhívtam a vallásos érzelmeire, a keresztényi szolidaritásra, az isten szerelmére, az átkozott lelkiismeretére, de becsukta a fülét.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Hm... Próbáltad más módszerrel meggyôzni?";
			link.l1 = "Úgy érti, megvesztegetni? Nem vesztegetek meg egy papot. Ha bankár lenne, vagy kereskedô, vagy akár kormányzó, akkor megpróbálnám így megoldani a kérdést, de nem egy papot!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Kedves naiv barátom, ha a pap füle tényleg zárva van a lelkiismereti kijelentések elôtt, akkor a keze bizonyára nyitva áll az arany elôtt... Vagy fordítva. Segítek neked, szerintem egy ilyen szennyezett kincs itt tartása csak nagyobb bajt fog okozni a késôbbiekben. Ehhez azonban bizonyos kiadásokra lesz szükség."
			link.l1 = "Miért nem vagyok meglepve? Ezúttal mennyit?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Gyere be holnap, "+pchar.name+", az árat még nem tudom megnevezni. De az ellopott keresztet megkapja, biztos lehet benne.";
			link.l1 = "Rendben Fadey, akkor nem zavarlak tovább. Holnap találkozunk!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Ahogy ígértem, megvan a kereszt. Ami a részleteket illeti... ó, felejtsd el ôket... minden ostobaságot megbocsátott a mi drága Megváltónk kiontott vére...";
			link.l1 = "Mennyivel tartozom neked?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Kétszázötven dublonnal. A költségeim fedezésére, és persze örülnék egy kis plusznak az igazságos segítségemért...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Igenis, Monsieur Fadey. Itt az aranyad.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "El kell hoznom az aranyat a kabinomból. Mindjárt jövök.";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "Horosho. Itt van az ellopott kereszt.";
			link.l1 = "Köszönöm, Fadey. El sem tudod képzelni, mennyi mindent tettél értem!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "Mindig örülök, ha egy kedves - és ami még fontosabb - nagylelkû barátnak segíthetek. Ugorj be gyakrabban. Talán majd iszunk egy kis vodkát, ha majd az anyaországból hozzám szállítják.";
			link.l1 = "Örömmel!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Lám-lám, a tenger még nem követelt téged! Tájékoztass! Milyen szerencsétlenségek hozták ezúttal az ajtómhoz?";
			link.l1 = "Nem tudom, hogy nevezzem-e szerencsétlenségnek, vagy sem, de mégis itt vagyok. Fadey, az elsô napon, amikor találkoztunk, egy ritka tôrt adtál nekem, a Fônök karmait. Most már tudom, hogy korábban egy Archibald Calhoun nevû emberé volt. Kérem, mondja el, mit tud errôl az emberrôl.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Semmit sem lehet eltitkolni elôled, "+pchar.name+". Te mindent átlátsz, akárcsak a bátyád. Igen, ezt a tôrt egy kockajátékban nyertem Calhountól. Ki az a Calhoun? Nekem fogalmam sincs. Véletlenül találkoztunk a kocsmában, beszélgetésbe elegyedtünk, ittunk egy kicsit, és ô elkezdett mesélni nekem a múltjának néhány bûnérôl, ami nyomasztotta...";
			link.l1 = "Mi vagy te, a gyóntatója? Milyen bûnöket?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibaldot felemésztette annak az embernek az emléke, akit az inkvizíció halálra kínzott miatta és több mint más ártatlan lélek miatt, akiket megölt. Folyton Júdásnak nevezte magát. Azt mondta, hogy Isten bünteti ôt a bûneiért, és az inkvizíció vadászik rá\nElmondta, hogy maga a spanyol inkvizítor, Vincento Vincento akarja a halálát, és zsoldosokat küldött, hogy üldözzék ôt a Karib-tengeren keresztül. Aztán az alkohol gyôzött a jobb belátása felett, és eljátszottuk ezt a régi tôrt.";
			link.l1 = "Ez minden? Soha többé nem láttad?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Persze, hogy nem, ô már halott. Egy csapat szerencsétlen kalóz küldte a folyékonyát Davy Joneshoz' Lockerhez, az egész legénységet pedig Mictlantecuhtlihez. Az igazat megvallva, a pletykák szerint kalóznak öltözött szakemberek támadták meg ôket... az inkvizíció ügynökei. Vincento atya mindig elkapja az emberét, mondják.";
			link.l1 = "Archibald Calhoun életben van. Nemrég láttam ôt egy bizonyos William Patersonnal együtt. Ô az elsô tisztje.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Ó, micsoda meglepetés! Archibald legalább fellélegezhet Paterson kapitány szárnyai alatt. Jó társaságban van. A spanyolok úgy félnek Pattersontól, mint a pestistôl. Nem mernek összeesküvést szôni Archibald ellen, amíg Patteron védelme alatt áll.";
			link.l1 = "Ismered Patersont?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Ki ne ismerné William Patersont!? Ô is újonc a Karib-tengeren, akárcsak te. És hozzád hasonlóan máris hatalmas hírnevet szerzett magának. Patterson úr Fox ezredes legközelebbi barátja, és jóban van magával Lord Windsorral, az összes karibi angol gyarmat fôkormányzójával. Gyakran látogatja a kormányzó palotáját Port Royalban, Jamaicán.";
			link.l1 = "Megvan. Köszönöm az információt, Fadey!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Ó, ne is említsd, barátom. Gyere el hozzám valamikor! Jó vadászatot!";
			link.l1 = "Mindenképpen!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Nézzük meg, "+pchar.name+"... Da! Ez egy közülük! Ez az én fiam, feldobtad a napomat! Hol találtad?";
			link.l1 = "Nem számít. A lényeg, hogy visszatalált hozzád.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "Jól megfizetem az alapos nyomozásodat. Háromszáz arany dublonnal elég jutalom lesz a fáradozásodért...";
			link.l1 = "Azzal a dublonnal fizetsz, amit korábban kiszedtél belôlem? Bár természetesen nem fogom visszautasítani ôket. Itt van a shamshired.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Spasiba, barátom! Köszönöm a kardot és a gúnyos szavaidat. Korodnál bölcsebb vagy, "+pchar.name+", de az emberi baráti kötelékek felülmúlják az arany értékét. Ha már az aranyról beszélünk, - teljes egészében kifizetlek. Tessék, itt vannak a dublónjaid.";
			link.l1 = "Köszönjük!";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "És ha már a baráti kötelékekrôl beszélünk, a tiédrôl és az enyémrôl különösen, "+pchar.name+". Van valamim, ami nagyon érdekelni fog téged.";
			link.l1 = "Hadd találjam ki, még több vodkát?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Ha! A vodka jó, de nem ez az egyetlen dolog, amirôl az országom híres. Van egy különleges anyag, amit csak Russiya gyárt. Ezt az anyagot az otthoni kapcsolataimtól kapom, hogy itthon kereskedjek vele. Minden kapitánynak kell, mert minden hajót feljavít. Kenderkötelekrôl beszélek\nKenderkötelek, amelyek immunisak a nedvességre és a tengeri sóra egyaránt. Azt mondják, hogy ez a legjobb anyag a kötélzethez\nMinden hónapban kapok egy bizonyos mennyiséget Revalból. Általában minden hónap közepe táján néhány száz tekercs van a raktáramban. Ezért "+pchar.name+", felajánlom, hogy eladok önnek egy ötven tekercsbôl álló tételt. Tíz dublont egy tekercs\nMindössze két feltételem van: elôször is, minden hónap 20-ig megtartom a köteleidet; másodszor, csak az egész tételt veheted meg. Ötven tekercs ötszáz dublonért. Bizalmasan szólva "+pchar.name+", azt mondják, hogy vannak bizonyos helyek, ahol sokkal nagyobb áron lehet ezeket a köteleket továbbértékesíteni, de mit tudom én!\ Teljesen elégedett vagyok a mûködésem jelenlegi állapotával, és nem kell magamnak viszonteladókat keresnem. Ha találsz egy jó kereskedôt, akkor szép profitot tudsz csinálni.";
			link.l1 = "Megvan. Ez egy remek ajánlat, Fadey! Azt hiszem, élni fogok a lehetôséggel, amit bemutatott nekem. Szóval, minden hónap huszadik napján ötszáz dublont ötven darabért?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "Da. Menj és vedd át a vásárolt árut. De várj, várj, kedves barátom! Ezen a shamshiren kívül, amelyet igazi jóindulatból adtál vissza nekem, volt még két másik. Könyörgöm, ha megtalálod ôket, hozd vissza nekem, és én több mint tisztességes árat fizetek neked a visszaszolgáltatásukért.";
			link.l1 = "Határozottan, Fadey. Ha megtalálom ôket, visszahozom ôket.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Jó híreket kaptál. Van egy másik perzsa shamshirem.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "Ó, jó barátom! Épp most szúrtad le a könnyeimet! Hadd nézzem meg... Da! Ez az, drága sámshirom! Tessék, ahogy ígértem neked, háromszáz dublon jutalom érte.";
			link.l1 = "Spasibo!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Kérem, fogadja hálámat és szerény, de nagyon hasznos ajándékomat. Nekem nincs rá szükségem, de önnek vagy a hajóasztalosának igen hasznos lesz\nTessék, nézze ezt a szép gyûrût! Most már a tiéd. De ez nem akármilyen közönséges gyûrû, ez egy elvarázsolt gyûrû. Segít a szônyegezésben és a hajójavításban. Sok mesterember szeretné megszerezni, de én különleges alkalomra tartogatom. Fogadd el, barátom, kívánom, hogy könnyítsen a terheiden!";
			link.l1 = "Biztosan sok érdekes tárgyat hordasz magadnál. Köszönöm, Fadey!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Az elveszett gyûjteményembôl már csak egy shamshir van hátra. Számítok rád, "+pchar.name+", és a szerencsédre. Ha megtalálod, ne habozz, siess vissza hozzám.";
			link.l1 = "Mindenképpen! Hamarosan találkozunk...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Miért kellene sietnem? A kard velem van.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "Ó, hála Istennek, hogy pont Tôled kértem segítséget, "+pchar.name+". Te egy csoda ember vagy, barátom! Mutasd meg nekem... Ohooo! Ez, ez ô. Drágám! Krasavitsa! Gramercy, derék fickó, meghajolok elôtted! Tessék, itt a pénzed. Négyszáz dublon, és egy kopijkával sem kevesebb! Nem leszek fukar.";
			link.l1 = "Köszönöm, Fadey. Öröm volt segíteni.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "A shamshir gyûjteményem újra együtt van! Senki sem meri majd újra ellopni tôlem, errôl gondoskodni fogok! Különleges jutalmam van számodra, jóember. Két héten belül egy kereskedô hoz nekem Európából egy kiváló vívópáncélt. Egy nemesember megrendelésére, egészen különleges páncélzat\nSzóval, ha akarod, mindössze hétszáz aranydublonnáért megveheted. Megmondom a nemesnek, hogy elveszett szállítás közben.";
			link.l1 = "Mi olyan jó ebben a páncélban?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "Nagyon kényelmes és tartós, mégis ugyanolyan jól teljesít, mint a vaskürasz. Ráadásul remekül néz ki! Pár hét múlva visszajöhetnél, és megnézhetnéd. De ne tartson tovább egy hónapnál, különben eladom az eredeti vevônek.";
			link.l1 = "Megegyeztünk. Két hét múlva beugrom hozzád.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Da, már kiszállították, és már vár rád. Elhoztad a pénzt?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "Igen. Itt van hétszáz dublon.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "A francba! A hajón felejtettem a pénzt. Mindjárt hozom!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Igen, jóember! Tessék, vedd el. Ez a fonott páncél jól fog szolgálni, biztosíthatlak. Nincs még egy ilyen az egész Karib-tengeren!";
			link.l1 = "Igen, azt látom. Köszönöm, uram! Alig várom, hogy felpróbálhassam...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "Miért kell várnia? Menjen csak. Lássuk, hogy áll.";
			link.l1 = "Hozom. Viszlát késôbb, Monsieur Fadey!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "Jöjjön be, kedves barátom. Az áru készen áll a vásárlásra. 2125 dublont kétszázötven darabért.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "Minden úgy van, ahogy megbeszéltük. Fogja a pénzt.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Csak hadd hozzam az érméket a kabinomból.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Jöjjön be, kedves barátom. Az áru készen áll a vásárlásra. Ötszáz dublont ötven darabért.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "Minden úgy van, ahogy megbeszéltük. Fogja a pénzt.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Csak hadd hozzam az érméket a kabinomból.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Fadey, növelhetnénk az ügyleteink mennyiségét? Kész vagyok ötször annyi árut vásárolni tôled! Azt hiszem, ez mindkettônknek elônyös lenne. Mit szólsz hozzá?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Fadey, elhoztam a pénzt! Háromezer arany dublont, ahogy megbeszéltük.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Örülök, hogy üzletet kötöttünk, "+pchar.name+". Megparancsolom az embereimnek, hogy vigyék a köteleket a hajójára.";
			link.l1 = "Köszönöm!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "Ha még mindig szükséged van kötelekre, gyere vissza egy hónap múlva.";
			link.l1 = "Rendben, Fadey. Viszlát késôbb!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "Mit tehetek érted, kedves barátom?";
				link.l1 = "Te egy befolyásos ember vagy, Fadey. A kormányzó barátja, és ahogy a pletykák mondják, vannak kapcsolatai az udvarban. Képes lennél kérvényezni a hatóságoknál, ha esetleg bajba kerülnék a törvénnyel?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "Miben segíthetek, barátom?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Van egy kis problémám az angol hatóságokkal.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "A francia hatóságokkal is meggyûlt a bajom.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Hatalmas problémám van a csempészekkel.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Sajnálom, azt hiszem, egyedül is el tudom intézni.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "Oh ho ho, jóember, ki mondta ezt neked? Mindenki hazudik. De mivel te Michel testvére vagy és jó barátom, megpróbálhatom rendbe hozni a dolgokat. Csak az angol és a francia hatóságoknál tudok kérvényt benyújtani az ön érdekében, bár a kapcsolataimnak vannak határai. A spanyolokkal és a hollandokkal nem üzletelek\nAzt is figyelmeztetlek, hogy a befolyásom csak arra elég, hogy megmentselek a kisebb kihágásoktól. Enyhe vétségek esetén rávehetem ôket, hogy vizsgálják felül az önökkel szembeni magatartásukat, vagy enyhítsenek némi enyhe haragot. Szóval menjetek, kezdjetek háborút, és várjátok el, hogy kihúzzam a gesztenyéteket a tûzbôl!\nEzeken felül egyszerre csak egy nemzetet tudok megnyugtatni: Franciaországot vagy Angliát. Nem tudom magam kettészakítani, hogy egyszerre két munkát végezzek. Természetesen pénzérmére is szükség lesz ahhoz, hogy kenôpénzt tudjak adni. Ne habozzatok hozzám fordulni segítségért, ha elfogadhatónak találjátok a feltételeimet.";
			link.l1 = "Köszönöm, Fadey. Ezt észben fogom tartani.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.FadeyNation));
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", false);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Természetesen. Hallottam már a kalandjaidról - vagy baleseteidrôl. El tudom intézni a kis problémádat, semmi olyat, amit a megfelelô mennyiségû arany a megfelelô tenyérbe kenve ne tudna megoldani. " + sTemp + ", és kihúzlak a bográcsból.";
				if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
				{
					link.l1 = "Remek! Itt van az arany.";
					link.l1.go = "agree";
				}
				link.l2 = "Akkor éppen itt az ideje, hogy elmenjek az érmékért.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Hát persze. Biztosan hallottam már a kalandjaidról - vagy baleseteidrôl. El tudom intézni a kis problémádat, semmi olyat, amit a megfelelô mennyiségû, megfelelô tenyereket megzsírozó arany ne tudna megoldani. " + sTemp + ", és kihúzlak a bográcsból.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "Remek! Itt van az arany.";
						link.l1.go = "agree";
					}
					link.l2 = "Akkor éppen itt az ideje, hogy elmenjek az érmékért.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Igen, elég nagy pácban vagy! Nem tudom teljesen megoldani ezt a helyzetet. Azonban enyhíthetem a villámcsapást, amely hamarosan a bûnös fejedre hull. És késôbb bármikor, bármikor újra bemutathatunk egy kenôpénzt, ha van rá pénzed és kedved. " + sTemp + ", és máris elkezdhetem elsimítani a gondjaidat.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "Elegem van abból, hogy a kalózvadászok üldöznek. Itt van az arany.";
						link.l1.go = "agree";
					}
					link.l2 = "Akkor éppen itt az ideje, hogy elmenjek az érmékért.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Rendben, adj nekem tíz-tizenöt napot. Addig is, megbeszélek egy találkozót, és elintézem ezt-azt. Két hét múlva minden kész lesz. ";
			link.l1 = "Köszönöm, Fadey! Várni fogom...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.FadeyNation));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", true);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			dialog.Text = "Miért mentél oda, hogy felbosszantsd ôket, jóember? A csempészek nem a legrosszabb népek a világnak ezen a részén, és jó hasznot hozhatnak neked. Rendben, segítek neked, tudom, hogyan kell ôket megpuhítani... " + sTemp + " lesz, nem kell alkudozni.";
			if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
			{
				Link.l1 = "Rendben, Fadey, egyetértek. Fogd az aranyat.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Most nincs nálam annyi arany. Majd késôbb visszajövök!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Jó, majd én elsimítom a vitát, ne aggódj. Újra üzletelni fognak veled, mint a régi szép idôkben.";
			Link.l1 = "Köszönöm!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "Ho-ho, látom, hogy az üzleted virágzik és az étvágyad növekszik! Igazad van, az árunk jó, és az árak nem túl borsosak. Viszont vigyázz, befektetésekre van szükség! Az ilyen üzlet komoly megközelítést igényel, hogy minden tökéletes legyen.";
			link.l1 = "Jönnék én egy ilyen ajánlattal anélkül, hogy lenne pár száz dublont tartalékban?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "Tudom, hogy vannak érmék a ládádban, és nem csak pár, biztosan ötven is belefér! De a mi üzletünk nem hétköznapi - nem csak az áruk mozgatásáról van szó, hanem arról, hogy megtaláljuk a módját... mondjuk úgy, hogy diszkréten. Az ilyen léptékhez komoly befektetésekre van szükség, nem csak fizetésre, hogy nyereséges legyen! És hogy a pénzed ne tûnjön el a semmibe. Ha hajlandó vagy megválni háromezer aranydublontól, akkor szavamat adom, hogy mindent jól fogunk csinálni, mint jó barát, és nem fogunk lebecsülni az árban.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "Háromezer dublont! Nos, be kell vallanom, ilyen nagylelkû ajánlatot még a legvirágzóbb kereskedôk is ritkán hallanak, még a legfantasztikusabb mesékben is! Kevesen hajlandóak ilyen nagylelkûen befektetni egy ilyen vállalkozásba. De én szerencsére közéjük tartozom. Itt a pénze, Monsieur Fadey.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "Háromezer arany dublont! Nem állok készen egy ilyen összegre, Fadey. Sajnos. Késôbb visszajövök.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "Háromezer, azt mondja? Hát... Az igazat megvallva, egy ilyen összeg tiszteletet parancsol az ambíciódnak. De be kell vallanom - ez nem nekem való.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "Micsoda fordulat! Jössz egy ajánlattal, aztán azonnal visszalépsz! Bevallom, csalódott vagyok, de nem fogom feladni a barátságunkat. Maradjunk a régiben: a korábbi megállapodásunk áll - ötven tekercs, fejenként tíz dublonnal, minden hónap 20-án.";
			link.l1 = "Jó, hogy megértettél, Fadey. Szívesen meggondolnám magam, de az ilyen kiadások meghaladják a képességeimet. Sajnos, az eszközeim korlátozottak ebben a kérdésben.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "Nos, ha ez a döntésed, akkor nincs mit megbeszélni. Ez a fordulat nem befolyásolja a barátságunkat. Látogasson el, "+GetSexPhrase("jó uram","szép hölgy")+".";
			link.l1 = "Ég veled!";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "Na, ez aztán a józan ész! Te nem az üres fecsegés híve vagy, hanem tudod, hogyan kell cselekedni. Az olyan üzletemberek számára, mint maga, mindig van kedvezmény! Tizenöt százalék kedvezmény minden jövôbeli szállítmányra! Íme az ajánlatunk: 250 tekercs kenderkötél, amit minden hónapban készenlétben tartok önnek. Átveheted ôket, ahogy eddig is, 20-án, 2125 dublont fizetve mindenért, maradék nélkül.";
			link.l1 = "Tökéletes, Fadey! Magával rendkívül könnyû üzletet kötni. Biztos vagyok benne, hogy siker vár ránk. A következô alkalomig!";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}