// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Jó napot, uram. Még sosem láttam önt. Maga újonnan érkezett? És most elôször látogat el erre a platformra?";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". Újonnan jöttem ide és csak nézelôdöm, hogy megismerjem az embereket....";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "Figyelj, "+pchar.name+", ha folyton elvonod a figyelmemet, soha nem fogom befejezni a javítást.";
					link.l1 = "Igen, igen, emlékszem rá. Sajnálom, hogy zavartalak!";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "Ah! Nézzenek oda! A megfulladt ember visszatért a túlvilágról! Mondd csak, hogy voltál képes ilyen trükköt végrehajtani? Temetést rendeztek neked, és eltemettek a távollétedben, ha esetleg nem tudnád...";
					link.l1 = "Kár, hogy még nem fogok meghalni. A trükk egyszerû - csak megérintettem a Kukulcan bálványát az alján. Ez teleportált engem Dominikára, egyenesen a karibi' faluba...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "Henrik, van egy üzletem a számodra. Egy nagyon fontos üzlet. Ole Christiansen mesélt magáról. Úgy is hívják, hogy a Fehér Fiú.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "Henrik, hoztam neked elegendô mennyiségû 'ezüstöt'. Pontosan úgy, ahogy kérted: egy a tiédbôl, plusz plusz tíz darab. Tessék, fogd ôket.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "Megint én, Henrik. Hogy van az öltönyöd? Sikerült megjavítani?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "Van elég fémem, amennyit kértél. Vedd el.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "Jó napot, Henrik. Szóval, a ruha készen áll a merülésre?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "Vége van, megbirkóztam a problémáimmal, és készen állok a merülésre. Mikor kezdünk?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "Helló, Henrik. Szóval, készen áll a ruha a merülésre?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "Vissza akarom adni a ruhádat.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
				link.l1.go = "rumours_LSC";
				link.l3 = "Csak tudni akartam, hogy vagy.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Én pedig Henrik Vedecker vagyok. Bár a helyiek többsége úgy ismer engem, mint a Mechanikust, és ez a meghatározás igaz is.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "Te vagy Henrik Vedecker? Örülök, hogy megismerhetem! Már kerestem magát.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "Maga biztosan minden szakma nagymestere, igaz?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "Ó, igen, a narválok nagyra értékelik a képességeimet. A szerszámaim lehetôvé teszik számukra, hogy a külsô gyûrû elveszett hajóiról sok értéktárgyat szerezzenek, így ellátmányt vásárolhatnak Dodson admirálistól\nA tudomány és a felfedezések a szenvedélyem. Ezért elnézést kérek, ha nem tudok majd elég idôt tölteni veled - a kísérleteim szinte az egészet elveszik.";
			link.l1 = "Értem. Biztosíthatom, hogy nem fogom ok nélkül zavarni, Vedecker úr. Nagyon örülök, hogy megismerhetem!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "Tényleg? És miért?";
			link.l1 = "Ole Christiansen mesélt magáról. Ôt is Fehér Fiúnak hívják.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "Ah, az a vicces fickó! Igen, igen, ismerem ôt. És mit mondott neked?";
			link.l1 = "Sajnálom, ha a következô kérdésem hülyén hangzik, de... de azért megkérdezem. Ole azt mondta nekem, hogy megtaníthatsz arra, hogyan kell merülni a víz alatt. Ne nevess ki, kérlek, ha ez csak a képzelete.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "Ez igaz. Én magam is többször voltam már a mélyponton. Bár, már nem merülök, a zátonyon mostanában óriásrákok nyüzsögnek, és bizonyára, mint látod, nem vagyok képes harcolni velük, tudós vagyok, nem tudok harcolni ezekkel a dolgokkal.\nMellesleg volt még két másik férfi, két narwhal, akik régebben búvárkodtak, de végül abbahagyták - a külsô gyûrû hajóinak raktereit fosztogatni biztonságosabbnak bizonyult, mint az óriásrákok által fertôzött helyre merülni\nmár ritkán használják a felszerelésemet, az elmúlt hónapokban egyetlen merülést sem végeztek a ruha törése miatt...";
			link.l1 = "Tényleg van olyan ruhád, amivel a fenékig tudsz merülni? Rosszul hallottam?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "A füle a helyén van, fiatalember. Én magam találtam ki és készítettem el a ruhát. Vastag, átázott, teljesen vízhatlan vászonból, fém alkatrészekbôl és egy acélsisakból készült, amit én és Jurgen kovácsoltunk a kovácsmûhelyében\nA ruhát fém mellvéddel, térdvédôkkel, mellkasdarabokkal és csizmákkal is megerôsítettem a rákok elleni jobb védelem és az extra súly érdekében\nA nyomás alatt lévô levegôvel töltött speciális tartályok biztosítják az életfenntartó funkciót és a víz alatt eltöltött idô képességét. A ruha egyedi, és én nagyon büszke vagyok rá.";
			link.l1 = "Ez nagyszerû. De említette, hogy a ruha sérült?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "Sajnos ez így van. A ruha több részét fémlemezekkel kötötték össze a rugalmasság és az extra védelem érdekében, de a tengervíz csúnyán megviselte ôket. A lemezek az évekig tartó mûködés során megrozsdásodtak, és elvesztették vízvédelmi képességüket\nJó, hogy észrevettem a kárt, és megakadályoztam az emberek halálát. Még a szárazruha is tartalmazott némi sót és vizet, teljesen befejezték beteges munkájukat.";
			link.l1 = "Nos... De meg lehet javítani a ruhát! A régi rozsdás részeket kicserélheted újakra... Nem igaz?";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "Milyen céllal? Hogy egy év múlva újra kicseréld ôket? Tudod, milyen nehéz ez a munka? Összeállítani a ruhát rugalmas illesztésekkel és vízállóvá tenni? Ez legalább egy hét munka pihenés nélkül.";
			link.l1 = "És ez az oka annak, hogy miért hajlandó eldobni a találmányát?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "Nem, természetesen nem. Van egy ötletem. Az ízületeket olyan fémbôl kell készítenem, amit a víz és a só nem tud tönkretenni. És tudom, hogy milyen fém segíthet...";
			link.l1 = "Akkor mi a probléma?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "A probléma az, hogy ez a fém nagyon ritka. Csak egy darab van belôle, ami biztosan nem elég. Még legalább tíz, de inkább tizenöt darabra van szükségem.";
			link.l1 = "És mi ez a fém, amirôl beszélsz?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "Ó, ez egy egyedülálló fém, sokan tényleg alábecsülik. Nagy tartóssággal, képlékenységgel rendelkezik, és teljesen immunis az expozícióra - sem a víz, sem a só nem tud kárt tenni benne\nTalán már találkoztál korábban ezzel a fémmel. Fehér, úgy néz ki, mint az ezüst, ezért nevezték el a spanyolok 'silver'. Ha! Százszor jobb, mint az ezüst! Még az aranynál is jobb! Egyszer majd megértik ezt, de még nem jött el a megfelelô idô.";
			link.l1 = "Figyelj, miért nem tudsz másfajta fémet használni helyette? Miért nem használsz aranyat azokhoz a lemezekhez? Soha nem hallottam még, hogy az arany rozsdásodhat vagy tönkremehet.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "Rugalmas és élô elméd van, fiatalember. Ezt jó tudni. Sajnos, a javaslata nem fog mûködni. Az arany gondolata volt az elsô dolog, ami eszembe jutott. De az arany túl puha ahhoz, hogy összekapcsolja a ruha különbözô részeit\nA sajnos a platina az egyetlen anyag, ami megfelel. Csak ebbôl fogok alkatrészeket készíteni, még ha évekbe is telik, mire összegyûjtöm az eleget. De láttam már korábban is darabokat ebbôl a fémbôl a Szigeten - a kinézete miatt gyakran keverik ezüsttel.";
			link.l1 = "Hm. És ha segítek neked, hogy találj belôle eleget... 'silver', kölcsönadod a ruhát, hogy lemerülhessek a víz alá?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "Nem kell kérni! Persze, hogy megteszem. Már mondtam neked, hogy nem merülnék ott a rákok miatt, és senki más nem akarja ezt megtenni.";
			link.l1 = "Akkor mutasd meg ezt a fémdarabot, hogy megértsem, mit kell találnom.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "Szóval meg fogod keresni? Kiváló. Tessék, vegyük ezt a darabot példának. Keresd meg az ezüstérc és a rögök között. Nem lesz könnyû megtalálni, de meg fogod tudni oldani. Az ezüstön vannak apró sötétedések, de a mi fémünk tiszta és sokkal keményebb, mint az ezüst. A legegyszerûbb módja a tesztelésnek az lenne, ha az ezüstérmét megkarcolnád rajta, ha az érme megsérül, akkor megtaláltad.";
			link.l1 = "Finom. Azonnal megkeresem. Van valami javaslatod, hogy hol keressem?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("Kaptál egy platina rudat");
			dialog.text = "Sajnos, nem kaptam. Ha tudnám, hol találom, magam tenném meg. De egy tanácsot azért adhatok. Keress a Rivados hajókon. Én nem látogatom ôket, így nagyon valószínû, hogy náluk is lehet.";
			link.l1 = "Megfontolom, Henrik. Remélem, szerencsém lesz.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "Gyûjtsön össze még tíz darabot. Ez a minimum a ruha javításához. Sok szerencsét!";
			link.l1 = "Köszönöm. Viszlát, szerelô!";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "Nocsak, nocsak, mutasd meg... Kitûnô! Szép munka, fiatalember! Nehéz volt?";
			link.l1 = "Nem igazán...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "Nos, most már elkezdhetem a javításokat. Nem vesztegetem az idôt, és holnap kezdem. Nagyon szeretnél merülni, ugye?";
			link.l1 = "Nagyon is. Nagyon szeretném felfedezni a víz alatti világot.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "Ez nagyon jó, mert lesz egy kérésem számodra, amikor megszervezzük a merülést. De errôl majd késôbb beszélünk. Gyere el hozzám öt nap múlva, remélem, hogy befejezem a javításokat.";
			link.l1 = "Rendben. Sok szerencsét!";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "Szerencsére biztosan szükség van, de a ruha javításához fôleg ügyességre lesz szükség. Emellett egy napot a kemence mellett kell töltenem Jurgennel, hogy a fémbôl, amit hoztál nekem, lemezt készítsek.";
			link.l1 = "Aztán nem foglak zavarni. Öt nap múlva találkozunk. Viszlát!";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "Igen, uram. Én és Jürgen pokoli munkát végeztünk, és a darabok mennyisége, amit hoztál, elég volt hozzá. A ruha megjavítva és elkészítve. Már csak néhány tesztet kell lefuttatnom, de biztos vagyok benne, hogy rendben van. Gyere holnap délelôtt 10-kor - feltöltöm a tartályokat levegôvel, és akkor azt csinálhatsz, amit akarsz.";
				link.l1 = "Kitûnô! Alig várom, hogy megtegyem. Holnap találkozunk, Henrik!";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Csalódást kell okoznom neked, "+pchar.name+". Ahogy feltételeztem, nincs elég fém. Szükségem van még "+FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty))+" darabokra, hogy befejezzem a javítást. Ismét a segítségét kell kérnem.";
				link.l1 = "Nos, nem számítottam ilyen fordulatra. Rendben, megpróbálom megtalálni a hiányzó rögöket.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "Várni fogok rád. Biztos lehetsz benne, hogy ez az összeg biztosan elegendô lesz. Csak hozd el ôket, és egy nap alatt befejezem a munkát.";
			link.l1 = "Remélem... Viszlát!";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "Nagyszerû! Most már a ruha is helyre lesz állítva. Már csak néhány tesztet kell lefuttatnom, de biztos vagyok benne, hogy rendben van. Jöjjön el holnap 10 órakor - feltöltöm a tartályokat levegôvel, és akkor azt csinálhat, amit akar.";
			link.l1 = "Kitûnô! Alig várom, hogy megtegyem. Holnap találkozunk, Henrik!";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "holnapután";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "holnap";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "Igen, a ruha készen áll, és meg van töltve levegôvel. Merülhetsz.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "Rendben. De most nem tudok merülni, meg kell oldanom egy problémát a... barátommal, Nathan Hawkkal kapcsolatban. Nem találom ôt. Nem várhat a ruha egy kicsit?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "Nagyszerû! Mikor kezdünk? Most?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "Persze. Várhat. Nem fogod egy évig keresni a barátodat?";
			link.l1 = "Persze, hogy nem. Talán még ma megtalálom. Meglátogatlak, miután befejeztem az üzletet vele.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "Igen, kérem. Gyere, ha készen állsz a merülésre.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "Most azonnal, ha akarod. De elôbb hadd adjak egy kis útmutatást. A merülést a 'Phoenix' platformról kezditek, oda a San Gabriel tatjáról tudtok eljutni. Van egy emelô, amivel lejuthatsz a fenékre és vissza. Ez az egyetlen módja a visszatérésnek\nSzóval jobb, ha megjegyzi az emelô helyét a víz alatt, és nem téved el. A ruha tartályaiban húsz percnyi merülésre elegendô levegô van. Figyelj az idôdre, különben megfulladsz\nNe menj túl messzire az emelôtôl, különben nem tudsz idôben visszatérni, és Isten óvjon attól, hogy elhagyd a zátonyunkat - szétlapítanak, mint egy laposhalat\nVigyázz, és figyelj a rákokra. Ha túlságosan közeledsz hozzájuk, megtámadnak téged. Ne kockáztass, ha nem muszáj, nem fogsz tudni megölni egy egész falkát, és a gyors menekülés sem opció odalent.";
			link.l1 = "Majd én foglalkozom a rákokkal. A többit elintézem. Ne merülj mélyebbre, ne menj messzire az emelôtôl és ne feledkezz meg az idôrôl. Mikor merülhetek le?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "Amikor csak akarsz, de csak reggel 7-tôl este 9-ig, mert sötétben semmit sem fogsz látni.";
			link.l1 = "Megvan.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "Ez az. Vidd el a ruhát az emelvényen lévô szobából. Vedd le a merülés után, és hozd ide nekem. Én majd újra feltöltöm levegôvel. De ne próbálj meg naponta egynél többször merülni, még a 20 perces merülés és a sûrített levegô belélegzése is árt az egészségednek.";
			link.l1 = "Nos, akkor nem fogok többször merülni egy nap.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "Örülök, hogy megértetted. Most menj és sok szerencsét!";
			link.l1 = "Köszönjük!";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "Szóval, miért vagy még mindig itt? A ruha már vár rád.";
				link.l1 = "Igen, igen, igen. Már úton vagyok.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Szóval, hogy ment az elsô merülés?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "A legkiválóbb és elégedett vagyok az eredményekkel. Találtam egy kôbálványt az elsüllyedt gályán. Úgy hallottam, hogy Rivados korábban áldozatokat mutatott be neki. Mondja, Henrik, ismer valakit, aki többet tudna mondani róla?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "Rendben. Megcsináltam! Nagyon érdekes volt, bár kicsit izgalmas.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "Érdekli a történelmünk? Menj Antonio Betancourt-hoz. Ô itt született. A Plútó fuvolában lakik. Ha ô nem tud róla semmit - senki sem tud.";
			link.l1 = "Kitûnô! Mindenképpen meglátogatom.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "Hagyja itt az öltönyt. Jöjjön vissza holnap vagy másnap, én megtöltöm levegôvel.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Persze. Itt van az öltönyöd. Köszönöm.";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Persze. Azonnal hozom!";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "Nos, elhoztad a felszerelésemet?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Persze. Itt van az öltönyöd. Köszönöm.";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Azonnal megcsinálom!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "Igen, persze. A ruhát kipróbálták és levegôvel töltötték meg. Magánál van a fogadalom? 500 000 pezó?";
				if (sti(pchar.money) >= 500000)
				{
					link.l1 = "Igen, persze. Tessék, vegye el.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "Oups! Elfelejtettem. Azonnal hozom...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Igen, persze. A ruhát tesztelték és levegôvel töltötték fel. Ellenôrizze a 'Phoenix' platformot, mint mindig.";
				link.l1 = "Aztán lemerülök. Köszönöm.";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "Rendben. Gyere vissza holnap vagy késôbb. Elôkészítem a ruhát.";
			link.l1 = "Köszönöm, szerelô!";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "Visszakapja a pénzét, ha visszaadja a ruhát. Tisztességes üzlet.";
			link.l1 = "Köszönöm, szerelô! Most megyek merülni.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "Várjon egy pillanatot, kérem! Milyen szobor? Most már értem. Arra a bálványra gondolsz az elsüllyedt hajóban 'San-Geronimo', ugye? Szóval igazak azok a Rivados mesék?";
			link.l1 = "Pontosan! És nincsenek mesék. Ismerek még két bálványt a szigetvilágban, amelyek körkörösen teleportálják az embereket, akik megérintik ôket, egyikbôl a másikba.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Értem, értem. Meg kell bíznom benned, bár a szavaid tudományellenes ostobaságok. Teleportok, szobrok... ha! És ki gondolná meg, hogy egyáltalán hogyan mûködnek az ilyenek?";
			link.l1 = "Csak bízz bennem, és ne próbálj itt logikát keresni. Nem hazudok.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Nem hazudok. De remélem, hogy nem vesztetted el a ruhádat a teleportálás közben?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Persze, hogy nem. Úgymond megmentett a Caribs-tól. Itt is van.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "Persze, hogy nem. Megmentett a Kariboktól, hogy úgy mondjam. De most nincs nálam.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "Akkor hozd ide nekem, a fenébe is! Addig nem beszélünk, amíg vissza nem adod nekem, tudd meg!";
			link.l1 = "Nyugodj meg, Mechanikus. Visszaadom neked!";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "Ah, te tényleg elhoztad az öltönyömet! Köszönöm, már kezdtem aggódni miatta.";
				link.l1 = "Nem kellett volna aggódni miatta. Megígértem, hogy visszaadom.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "Ne is gyere ide, amíg nincs nálad az öltönyöm.";
				link.l1 = "Rendben, rendben.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "Nagyon jó. Elkezdtem gondolkodni az új elkészítésén, de ez egy évnyi munka lenne, nem kevesebb... Örülök, hogy takarékosnak bizonyultál, és egy darabban adtad vissza a tulajdonomat. Még ajándékot is adok neked.";
			link.l1 = "Komolyan mondod?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "Persze, hogy komolyan! Segítettél megjavítani a ruhát, és nem dobtad ki az elsô alkalommal. Gondoskodtál róla, és végül visszahoztad nekem. Mindenesetre itt van egy remek szerszámosláda. Tanuld meg, hogyan kell használni. Sok hasznos dolgot fogsz tudni készíteni a segítségével.";
			link.l1 = "És mi mást várhattam volna a Mechanikustól! Persze, a szerszámosládát! Köszönöm szépen, Henrik, meghatódtam... Nem érdemeltem meg egy ilyen ajándékot.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("Kaptál egy szerszámosládát");
			PlaySound("interface\important_item.wav");
			dialog.text = "Én jobban tudom, hogy mit érdemeltél és mit nem. Vedd el! Hasznos lesz neked. De csak akkor adom vissza a ruhát, ha 500 000 pezót adsz, mert szokásod, hogy bálványokon keresztül teleportálsz.";
			link.l1 = "Hûha! Nos, megértem... elôvigyázatosságból...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "Persze. És mi van, ha egy nap megszökik vele? Akkor a pénz lesz a kárpótlásom.";
			link.l1 = "Rendben, Henrick. Egyetértek. Hogy ôszinte legyek, azt hittem, hogy soha többé nem adod nekem.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "Semmi esélye. Félmilliót ígérj, és az egész a tiéd.";
			link.l1 = "Megegyeztünk! Akkor elvihetem a szokásos módon a búvárkodáshoz? Holnaptól kezdve?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "Pontosan.";
			link.l1 = "Köszönöm! Viszlát, Henrik!";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, mi? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat!", "Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!");
			link.l1 = "A francba!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Mi?! Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!";
			link.l1 = "Bolond lány!...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Figyeljen, jobb, ha elveszi a fegyverét. Ideges leszek tôle.", "Tudod, a pengével való rohangálást itt nem tolerálják. Vidd el.", "Figyelj, ne játszd a középkori lovagot, aki karddal rohangál. Vidd el, nem illik hozzád...");
			link.l1 = LinkRandPhrase("Jól van.", "Persze.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tegye hüvelybe a pengéjét.", "Figyelj, én a város polgára vagyok, és arra kérlek, hogy tedd hüvelybe a pengédet!");
				link.l1 = LinkRandPhrase("Jól van.", "Persze.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, haver, amikor fegyverrel futsz. Ideges tudok lenni...", "Nem szeretem, ha az emberek fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
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
