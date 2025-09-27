// шаман команчей Змеиный Глаз
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "Üdvözletem, sápadt barátom.";
				link.l2 = "Én is örülök, hogy látlak, vörösbôrû testvér. Ismét fontos dolgom van számodra.";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "Üdvözletem, sápadt barátom.";
			link.l1 = "Én is örülök, hogy látlak, Kígyószem.";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "Elhoztam neked az amuletteket, amiket kértél. Cseréljünk.";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "Megtaláltam a tamburádat, Kígyószem. Nézd meg.";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "Találtam egy érdekes indián pipát, Kígyószem. Nézd meg.";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "Helló, sámán. Használtam a szobrot, és hihetetlen utazást éltem át. Teljesen igazad volt. Megtaláltam a hajótemetôt, a fehér kapitányt és még a raktérben is megtaláltam az ellátmányt!";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "Kígyószem, szükségem van a segítségedre.";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//---------------------------------------- первая встреча------------------------------------------------
		case "SnakeEye":
			dialog.text = "Üdvözletem, sápadt barátom.";
			link.l1 = "Helló, sámán. Miért gondolod, hogy a barátod vagyok?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Sok mindent tudok, de nem mindig tudom, hogy pontosan mit. Szándékosan jöttél ide. A sors vezetett ide, és én segítek neked.";
			link.l1 = "Jó tudni! Valóban a segítségedért vagyok itt, vörösbôrû barátom. Egyenes leszek: mit értettél az alatt, hogy Sólyom feleségének Kukulcanról beszéltél?";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "Még a döglött halak is elszállnak. Az élô embert pedig a sors vezeti célról célra. A leláncolt kapitány célja, akit a rossz emberek Selvában üldöztek, Kukulcan szobra volt. Ha feláldozta magát, messze kerülhet innen.";
			link.l1 = "Nem értettem semmit. Mirôl szól az istened szobra, és hogyan tudott Sólyom olyan messzire eljutni gyalog, hogy még most sem találja senki?";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Ha Kukulcan megette Sólymot, akkor az bárhová kiköpheti ôt. Talán még egy másik világba is. Kukulcan háromszor evett meg engem. És minden alkalommal máshol voltam. Már régen ideértem, és úgy döntöttem, hogy nincs több kockázat. Nem mentem Kukulcan szájába, és nem tudom, hol köpi ki az áldozatait.";
			link.l1 = "Jézusom, ez meghaladja az én felfogóképességemet! Azt akarod mondani, hogy a kôbálvány képes messzire teleportálni az embereket?";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Nem csak az. Kukulcan nem csak a teret, hanem az idôt is uralja. Vagy még annál is többet. Meséltem a láncos kapitánynak az aranyszoborról, ami embereket eszik. Talán úgy döntött, hogy megkockáztatja, amikor látta, hogy az üldözôk közel vannak...";
			link.l1 = "Várj, a szobor kôbôl van. És te egy arany szoborról beszélsz...";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Éjfélkor a bálvány életre kel és arannyá válik. Ebben a pillanatban Kukulcan szelleme él benne. Féljetek a közelébe menni, különben máshol láthatjátok a napfelkeltét. Még a csillagok is megváltoztathatják helyüket az égen. Találkozhatsz azokkal, akik még meg sem születtek, vagy láthatod azok születését, akik már régen meghaltak, vagy meg sem születtek.";
			link.l1 = "Mi a... rejtvények és megint rejtvények... Érdekelsz engem, Kígyószem. Azt mondtad, hogy túléltél három találkozást Kukulcannal, az istennel, akiben hiszel. Akkor miért ne próbáljak szerencsét annak az istennek a bálványával, akiben nem hiszek?";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Kár. Kár, hogy nem hiszel. Talán maga Kukulcan hívott téged, hogy elhagyd ôseid földjét. De te még nem hallod ôt. Minden jó okkal történik. Ha úgy döntesz, hogy kockáztatsz, akkor tudnod kell, hogy én minden alkalommal csak azért éltem túl, mert csodálatos komancs bájitalaim voltak.";
			link.l1 = "Comanche? Az egy másik törzs?";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Így hívják az ellenségek az én népemet, akiket soha többé nem látok. A bájital helyreállítja az erôt és az állóképességet, valamint gyógyít és megment az erôs mérgektôl. Több lombikra van szükséged, de nekem csak három maradt.\nNégy lombik volt, de az egyiket elvesztettem egy furcsa helyen, úgy néz ki, mint a fehér ember hajóinak temetôje. Ott kezdtem el az utam ebben a világban. Talán Kukulcan ott köpte ki a kapitányt. Ha így van, nem irigylem ôt.";
			link.l1 = "Mi ez a hely? A hajótemetô?";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Furcsa hely... Nem kellene léteznie, de mégis létezik. Olyan emberek élnek ott, akik a bôrszínük miatt gyilkolnak. A nagy hajóban tartják a készleteiket, ahol Kukulcan kiköpött engem. Nem mentem be a raktérbe, amit megvédtek a tolvajoktól, nem bíznak a szomszédokban. Ha odaérsz - keress egy másik kijáratot, ne menj be a raktérbe, különben baj történik.\nFehér Fiú segít megtalálni egy másik szobrot, ha még él. Add neki ezt a fehér gyöngyöt. Ô szereti ôket.";
			link.l1 = "Hm. Már most pörög a fejem, és ez egyre érdekesebb lesz. Gyerünk, vörösbôrû testvér.";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			Log_Info("Kaptál egy fehér gyöngyöt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "Ha élve találod meg a kapitányt, lehet, hogy nagyon beteg. Nem volt idôm bájitalt adni neki. Ott keresd a tamburámat. A nagyapámtól kaptam. Sok minden van a táskámban, amit elvesztettem, de nekem csak a tamburin kell. Nehéz nélküle beszélni a szellemekkel.";
			link.l1 = "Nos, ez a hely nagyon érdekesen hangzik! Reméljük, Sólyom oda teleportálódott... Ideadnád a bájitalodat?";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Odaadom neked. De cserébe három helyi amulettet kell adnod nekem: "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian)+", "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet)+" és "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg)+". Minden amulettért egy-egy flaska. Szóval ez így fair. Gyere vissza, ha megvan az összes amulett. Akkor majd kicseréljük ôket. Ne hidd, hogy kapzsi vagyok. Vagy talán átgondolod, miközben amuletteket keresel.";
			link.l1 = "Nem fogom ezt gondolni. Várj meg, Kígyószem, hamarosan visszajövök.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
			pchar.questTemp.HelenDrinking.GiveAmulets = true;
			
			//if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))	// Временно так
			{
				// Квест "Путеводная звезда", начало 4 этапа
				PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
				PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
				locations[FindLocation("Shore9")].DisableEncounters = true;
			}
		break;
		
		// даёт зелья - идем на телепортацию
		case "SnakeEye_potion":
			dialog.text = "Jól van, barátom. Azért hoztál nekem amulettet, hogy Kukulcanba mehess?";
			link.l1 = "Igen. Kész vagyok megtenni ugyanazt az utat, amit Nathaniel, a láncos kapitány tett.";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("Amulettet adtál");
			Log_Info("Kaptál három sokoldalú bájitalt");
			PlaySound("interface\important_item.wav");
			dialog.text = "Fogd ezeket a bájitalokat. Ne feledd, hogy egyet azonnal meg kell innod, miután Kukulcan kiköpött, különben meghalsz vagy nagyon-nagyon beteg maradsz. Ne feledjétek azt sem, hogy ne menjetek a raktérbe, ahol a sápadtarcúak tartják az ellátmányukat. Van egy másik módja is a hajó elhagyásának. Valójában két módon is. Keressétek meg a vörös nôt az elsô éjszakán, ez nagyon fontos. Ez minden, amit mondhatok nektek.";
			link.l1 = "Emlékezni fogok erre, vörösbôrû testvér.";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "Akkor menjetek. Ha éjfélkor megérinted Kukulcant, megesz téged. Szellemeket fogok hívni, hogy vezessenek téged.";
			link.l1 = "Köszönöm, Kígyószem. Ne aggódj miattam, minden rendben lesz. Még találkozunk!";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // телепорты работают!
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
			QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		// пришёл из LSC
		case "LSC_hello":
			dialog.text = "Örülök, hogy látlak, barátom. Hogy tértél vissza a hajótemetôbôl?";
			link.l1 = "Megtaláltam Kukulcan szobrát, ahogy mondtad. Fehér Fiú segített nekem - Ole Christiansen. A szobor a tengerbe süllyedt, de én el tudtam érni. Egy dominikai indián faluba teleportált.";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "Monkitekuvri ott találkozott veled?";
			link.l1 = "Hm. Monkitekuvri? Ki az?";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "Ô a falu fônöke.";
			link.l1 = "Nem kérdeztem a nevét. Talán Monkitekuvri volt, talán nem.";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "Madártollakból készült pompás fejdísz volt a fején?";
			link.l1 = "Persze, hogy volt. Rengeteg toll... Úgy tûnik, hogy az összes papagájt kitépte a dzsungelben.";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "A neve Monkitekuvri. Ezek nem papagájtollak, hanem sastollak. Ez a fejdísz az én fejdíszem. Monkitekuvrinak adtam át, amikor Kukulcan visszaköpött. Aztán elvittek egy másik szoborhoz...";
			link.l1 = "Hát nem semmi! Ôk is 'feláldoztak engem' Kukulcannak! Én pedig itt találtam magam, az elsô szobor közelében.";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "Igen, sápadt barátom. Az én utam is itt ért véget.";
			link.l1 = "A bálványok körbe teleportálnak... De mi értelme van ennek? Van valami ötleted, Kígyószem?";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "Gondolom, a szobrok nem mûködnek jól. Jelenleg az embereket körbe-körbe mozgatják, de egy helyre kellene ôket mozgatniuk. Valami nem stimmel velük.";
			link.l1 = "Mibôl gondolod ezt?";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "Mert a körbe teleportálásnak nincs értelme. Kukulcannak minden áldozatot egy helyre kell vinnie, nem pedig körbe-körbe mozgatnia ôket.";
			link.l1 = "És hol lehet az a hely?";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "Ez nagy titok, fehér testvér, még nekem is.";
			link.l1 = "Értem. Rendben, a pokolba a bálványokkal. Soha többé nem megyek a közelükbe. Megtaláltam a láncos kapitányt, nem kell többé a portálokon átutazni.";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "Amikor a hajótemetôben voltál. Megtaláltad ott a tamburámat?";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "Azt hiszem, igen. Nézd meg.";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "Nem. Sajnos nem találtam meg. De tudom, hol van a sziget, és el tudom érni. Megkeresem a tamburádat.";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "Keresd meg, sápadt barátom. Nagyon kérlek. A tamburám nélkül nem hallom jól a szellemeket.";
			link.l1 = "Rendben, Kígyószem. Viszlát!";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ez az én tamburám. Köszönöm, sápadt barátom. Meg tudom hálálni. Bemutatom neked ezt a fegyvert, ami a népednek még sokáig nem lesz a birtokában. Ez a fegyver az én idôm sápadtarcúinak fegyvere.";
			link.l1 = "Érdekes! Mutasd meg nekem, vörösbôrû barátom...";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			Log_Info("Kaptál egy Colt revolvert.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "Vedd el. Csak három töltet van benne, a többit én használtam. De talán megtanulsz majd töltést készíteni hozzá. Néhány tucat töltet alkatrészt elvesztettem a hajótemetôben, ott megtalálod ôket.";
			link.l1 = "Oho! Ez egy pisztoly! Még soha nem láttam ilyet... micsoda furcsa gépezet? Valami forgó szerkezet... öt töltet! Szép!";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "Colt revolvernek hívják. Nincs még egy ilyen pisztoly a maga idejében. Könnyû használni, felhúzza a kakasát és meghúzza a ravaszt. Jól lô.";
			link.l1 = "Köszönöm! Köszönöm, Kígyószem! Szép meglepetés lesz az ellenségeimnek... Kár, hogy csak három töltet van benne...";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "Próbáld meg megtanulni, hogyan kell töltetet készíteni a Colt revolverhez. Akkor te leszel korod nagy harcosa. Ah, sápadt testvérem, elfelejtettem megkérni, hogy keresd meg a pipámat a hajótemetôben. Nagyon szép pipa volt.";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "Ha! És azon gondolkodtam, hogy kinek a festett pipája lehet ez? Nézd csak meg.";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "Nézd csak meg. Megkeresem a te pipádat is. Viszlát!";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ez az én pipám, testvérem. Örülök, hogy megtaláltad. És adhatok neked egy másik ajándékot is érte. Ez egy okos könyv a sápadtarcúakról az én idômbôl. Nem értem. Próbálj találni egy okos embert, aki el tudja olvasni és megérti ezt a könyvet.";
			link.l1 = "Köszönöm, Kígyószem. Azt hiszem, ismerek valakit, akit érdekelni fog.";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			Log_Info("Kaptál egy Lavoisier kémia tankönyvet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Add oda neki, fehér testvér. Ez a könyv a sápadtarcú bölcsesség nagy titkait tartalmazza.";
			link.l1 = "Jó. Viszlát, Kígyószem!";
			link.l1.go = "exit";
		break;
		
		// лечение Натаниэля
		case "Saga_nathaniel":
			dialog.text = "Hallgatlak, sápadtarcú testvér.";
			link.l1 = "Magammal hoztam a láncos kapitányt, akit a hajótemetôben kerestem. Nagyon beteg. Tudom, hogy csak te tudod meggyógyítani...";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "Kukulcan elfogyasztotta az egészségét. Azt hiszem, segíthetek neki meggyógyulni. De ehhez nem kevesebb kell, mint egy telihold. Kukulcan már régen megette a kapitányt, és a betegség mélyen elterjedt benne.";
			link.l1 = "Kérlek, gyógyítsd meg, sámán! Elhozom neked, amire szükséged van!";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "Megpróbálom, fehér testvér. Nem kell semmit sem hoznod nekem. Mindenem megvan. Az idô erôsíti a betegséget, de a láncos kapitány egy holdon belül újra egészséges lesz.";
			link.l1 = "Köszönöm, vörösbôrû testvér. Ismét megmentetted az életemet.";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "Hagyd a láncos kapitányt a kunyhómban, fehér testvér, és sétálj nyugodtan. Vidd a feleségét is, senki sem láthatja a szertartásomat.";
			link.l1 = "Rendben, Kígyószem. Magammal viszem Danielle-t. Viszlát!";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "Hallgatlak, barátom.";
			link.l1 = "Emlékszel a Kukulcan szobrokról szóló beszélgetésünkre? Azt mondtad 'az embereket egy különleges helyre kellene költöztetni'.";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "Emlékszem, fehér kapitány.";
			link.l1 = "Tudom, hova kellett volna vinniük azokat az embereket, akiket Kukulcan megevett.";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "Hol?";
			link.l1 = "A régi maja városba, Tayasalba. A Main dzsungel mélyén található.";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "Nagyon érdekes. Honnan tudod ezt?";
			link.l1 = "Ez egy hosszú történet, Kígyószem. Azt is tudom, hogy kerültél ide. Még meg sem születtél, igaz?";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "Még az apám sem a te idôdben született. De én a te idôdben élek, és ez nagy rejtély.";
			link.l1 = "Ez valójában megmagyarázható. Egy Kanek nevû Itza pap, aki Tayasalban él, meghívta Kukulkant, hogy halandóként szülessen meg ezen a világon, és szívja magába a fehér faj bölcsességét. Egyúttal létrehozott egy idôlyukat is, amely néhány embert teleportált a jövôbôl a mi idônkbe...";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "Hogy Kukulcan magába szívhassa a jövô embereinek bölcsességét?";
			link.l1 = "Igen. És Kukulcan azt tervezi, hogy elmegy a múltba, hogy átadja a tudást a régen meghalt maja embereknek. A történelem meg fog változni, és a maják uralni fogják Amerikát, és talán még többet is...";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "De valami történt a portálokkal, és elkezdték az embereket körbe teleportálni Tayasal helyett. És ezért vagyok itt, szükségem van a tanácsodra, Kígyószem.";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "Miért én, fehér kapitány?";
			link.l1 = "Mert Kukulcan megevett téged. És mert a falud közelében lévô Kukulcan-szobornak van egy furcsa jele ezen a térképen, ami erôsen kapcsolódik Kanek rítusaihoz.";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "Mutasd meg ezt a térképet?";
			link.l1 = "Tessék, nézze meg...";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "(Nézd) Ez a kerek jel, igen? És mit jelent?";
			link.l1 = "Nem tudom, sámán. Azt tudom, hogy a három Kukulcan-szobor közül csak az egyiknek van ilyen jele. És hogy a jelet viselô szobor a tiéd. Ebbôl arra következtetek, hogy a te szobrod különleges. Van valami ötleted?";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "Adj idôt holnap reggelig, fehér testvér. Hagyd itt ezt a bôrtérképet. Meg kell kérdeznem a szellemeket. Gyere vissza holnap.";
			link.l1 = "Rendben, vörösbôrû testvér. Holnap itt leszek. Köszönöm, hogy segítesz nekem.";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "Gyere késôbb, fehér testvér. Ne zavarj most.";
			link.l1 = "Persze, sámán...";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "Valamit el kell mondanom neked, fehér testvér.";
			link.l1 = "Találtál valamit? Vagy csak találgatsz?";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "Az ôsök szelleme látomást adott nekem, és elmentem Kukulcanhoz a térképpel. Kerestem és találtam. Biztos az, amit keresel, fehér testvér.";
			link.l1 = "Mit találtál?";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "A Kukulcan szobornak két vaskapcsa és mélyedése van. A mélyedésnek kerek, sima formája van. A kerek és sima tárgyhoz igazodik a bôrtérképedrôl.";
			link.l1 = "Mi a baj?";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "Nem tudom. Csak azt tudom, hogy kerek, lapos, mérete olyan, mint egy kis tök, és talán vastag, mint egy ujj. Elmehetsz és megnézheted magadnak a mélyedést és a bilincseket. A bilincsnek meg kell tartania.";
			link.l1 = "Van valami ötleted? Vagy egy tipp, hogy mi lehet?";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "A kônek van egy kis tûz nyoma. Tudom, mi történt vele. Égi láng csapott bele.";
			link.l1 = "Villám? Villám csapott bele?";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "Ebben biztos vagyok. Megkérdeztem Miskitót errôl a bálványról. Az egyik harcos azt mondta, hogy régen néhány szép festett dolgot láttak a szobornál. Nagyon hasonlítottak a sziklákra. Azt mondta, hogy nagyon szép vörös sziklák voltak. Egy fehér ember a fehér faluból megvette ôket.";
			link.l1 = "Hm. Amennyire én értem, úgy tûnik, hogy villám csapott bele ebbe a kerek 'something', darabokra törte, majd ezeket a darabokat eladták valami fehér fickónak?";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "Úgy tûnik.";
			link.l1 = "És ki volt az a fehér ember? A harcosod elmondta neked?";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "Ô mondta nekem. Miskito nagy barátja volt, és Blueweld faluban él. A neve Forest Devil. Ismerem ôt, biztosan te is ismered.";
			link.l1 = "Jan Svenson? Várjunk csak... vörösre festett sziklákat mondtál? Úgy tûnik, nagy szerencsém volt. Nézd csak, sámán, nézd ezeket a vörös sziklákat! Az erdei ördög ajándékozta nekem.";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("Díszes mintadarabokat kaptál");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "Biztosan ôk azok. Öt kô. Nézd meg, fehér testvér. Ha így helyezed el ôket... (összerakni)";
			link.l1 = "...";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "...akkor megvan a kerek tárgy. Nézzétek! Összeillenek. Azelôtt egy darab volt.";
			link.l1 = "A francba! És ezek a dolgok már olyan régóta a zsebemben vannak... Figyelj, sámán, ha a szilánkokat a mélyedésbe teszem...";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "Kukulcan ki fogja köpni az áldozatot az öreg indián városnál, ahogy mondtad.";
			link.l1 = "Az nagyszerû lenne! Oda kell jutnom! Gondolod, hogy a dísztárgy mûködni fog, ha szilánkokra tört?";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "Szerintem össze kell hozni ôket, és utána a dísztárgyat a mélyedésbe tenni.";
			link.l1 = "Összehozni ôket? De hogyan lehet ôket összerakni?";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "Bízd rám és az ôsök szellemeire, fehér testvér. Ezek nem egyszerû kövek. Ez egy csodatárgy. Gyere vissza három éjszaka múlva, fehér testvér. Hívom a szellemeket, a bölcsességet és az életben való jártasságot, és megpróbálom egyesíteni a szilánkokat.";
			link.l1 = "Hihetetlen... Hogy tudnám ezt valaha is meghálálni, Kígyószem?";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "Majd késôbb megköszönöd, fehér testvér. Most menj. Gyere vissza három éjszaka múlva.";
			link.l1 = "Rendben. Remélem, hogy sikerülni fog...";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "Boldoggá tudlak tenni, fehér testvér.";
			link.l1 = "Sikerült egyesítened a szilánkokat?";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "Igen. Nem volt könnyû, és a naptárban maradtak hegek, de most már teljes.";
			link.l1 = "Naptár? Miért hívtad így?";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "Mert ez a kerek dolog egy naptár. Alaposan tanulmányoztam. Van rajta idôszámítás. Az ôsi város indiánjai számolják az éjszakákat, holdakat, éveket és korokat.";
			link.l1 = "Hihetetlen... Bár, ha belegondolok, mire képesek a maja papok - ennek a naptárnak a készítése nem tûnik semmi különösnek.";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			Log_Info("Kaptál egy maja naptárat");
			dialog.text = "Fogd meg, fehér kapitány. Tegye a szoborra. Aztán talán kiköp téged az indiánvárosban.";
			link.l1 = "Hogyan hálálhatnám meg, Kígyószem?";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = "Mondd 'Köszönöm'. Istenek vezetnek az utadon, még akkor is, ha nem látod. A fehérek azt mondják - sors. Kukulcan hívott téged, az istenek vezetnek téged. Menj most. Tedd a dolgod és hagyd, hogy a jó szellemek vezessenek.";
			link.l1 = "Köszönöm, Kígyószem! Soha nem foglak elfelejteni.";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			Log_Info("Négy sokoldalú bájitalt kaptál");
			PlaySound("interface\important_item.wav");
			dialog.text = "Várjatok. Majdnem elfelejtettük a legfontosabbat. Kukulcan megeszi az embert és felemészti az életét. Készítettem nektek bájitalt. Komancs bájitalokat. Neked adom ôket. Négy flaskát készítettem, hogy három hûséges és bátor társadat magaddal vihesd.";
			link.l1 = "Olyan sokat tettél értem, vörösbôrû testvér...";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "A testvér nem csak a komancs törzs indiánjaira vonatkozik. Ha visszatérsz Kukulcan városából, látogass el a falunkba. Sok-sok saraiakát fôzünk. Örülni fogok, ha találkozunk.";
			link.l1 = "Persze, vörösbôrû testvér! Természetesen meglátogatlak!";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // кожаную карту можно выкладывать 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
