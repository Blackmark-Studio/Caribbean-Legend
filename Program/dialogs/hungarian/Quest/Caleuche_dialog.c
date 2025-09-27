void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ez határozottan egy bogár. Tájékoztatnád Jasont, hogy mikor és hogyan történt ez?";
			link.l1 = "Rendben.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Miért jöttél a kunyhómba, fehér ember? Tuttuathapak nem gondolja, hogy te vagy a kedves vendége.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "Üdvözöllek, nagy sámán Tuttuathapak. Azért jöttem hozzád, hogy segítséget és tanácsot kérjek tôled. Kérlek, fogadd el ezt a muskétát jóakaratom jeléül.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Üdvözöllek, nagy sámán Tuttuathapak. Azért jöttem hozzád, hogy segítséget és tanácsot kérjek tôled.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Tuttuathapak nem segít fehér embernek. A fehér ember rossz ember. Megölik és meghódítják az indiánokat, rabszolgává teszik ôket. Tuttuathapak nem ad tanácsot a fehér embereknek. Most menj el.";
			link.l1 = "Hmm...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("Adtál: "+XI_ConvertString(sTemp)+"");
			dialog.text = "Tudod, mit adnak Tuttuathapaknak, fehér ember. Tuttuathapak elfogadja az ajándékodat. Beszélni fog. Milyen tanácsot kérsz tôlem?";
			link.l1 = "Hallottam, hogy egy távoli helyrôl, délrôl jöttél. Van egy indián amulettem, és egy tudós ember azt mondta nekem, hogy talán tudod, hogyan lehet használni.";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "Mutasd meg az amulettet.";
			link.l1 = "Tessék, nagy sámán.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(az amulettet nézi)... A barátod mondd meg az igazat, fehér ember. Ez az amulett a népemé, nagy indiánoké, Chavin volt a nevük. Átkozott istenkáromló sápadtarcú kurva bemocskolja a szentélyt és elviszi ide. Tuttuathapak megbüntette azt a kutyát.";
			link.l1 = "Megfosztottad az elméjétôl, ha jól értem?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "A fehér ember meglepte Tuttuathapakot a tudásával. Igen, felfaltam annak a görény fattyúnak az elméjét. Ô és a mocskos embere megkapják, ami jár nekik.";
			link.l1 = "Értem... Mondd, sámán, mire használják ezt az amulettet? Talán megvédhet valakit a csatában, vagy védelmet nyújthat a gonosz mágia ellen?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "Ez az amulett nem használ neked, fehér kapitány. Nem tudod használni az erejét. Csak a törzsünk nagy sámánjai tudják, hogyan kell felébreszteni.";
			link.l1 = "Hmm... Szóval, kiderült, hogy hiába tettem meg ezt a hosszú utat. De talán fel tudod ébreszteni ennek az amulettnek az erejét, nagy sámán? Bizonyára meg tudnánk egyezni...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "Még ha fel is ébresztem az amulettet, nem tarthatod sokáig az erejét. De alkut ajánlok neked, fehér ember.";
			link.l1 = "Miféle alkut?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Három ilyen amulettet vittek el a szentélyünkbôl. Különbözô erejük van, de ha egyesítjük ôket, akkor nagyon erôsek lesznek. Találd meg mindhárom amulettet és hozd el nekem, és megjutalmazlak. Olyan hatalmat adok neked, amit örökre megtarthatsz.";
			link.l1 = "Nem egészen értem... Miféle hatalomról beszélsz?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "Tudod, hogy minden a megfelelô idôben történik. Keressétek meg és hozzátok el nekem mindhárom amulettet. A Karib-tengeren vannak. Keressétek és találjátok meg. Könnyen meg tudod mondani, hogy egyformák. Menj, fehér ember. Tuttuathapak várj és kérd meg a szellemeket, hogy segítsenek neked.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Menj, fehér ember. Találjatok még két amulettet.";
				link.l1 = "Már megtaláltam ôket, nagy sámán. Tessék, nézd meg.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Menj, fehér ember. Találd meg a másik két amulettet.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "Megint itt vagy, fehér ember? Úgy nézel ki, mint aki vad jaguárral találkozott a dzsungelben.";
			link.l1 = "Rosszabb, nagy sámán. Ahogy beléptem a tengerbe, a semmibôl hatalmas vihar támadt, és egy élôhalottakkal megrakott hajó támadt rám! A kapitányuk teljesen legyôzhetetlen volt. Elôször elvette tôlem az amulettet, és majdnem megölt - alig éltem túl. Aztán majdnem elsüllyesztették a hajómat, a legénységembôl csak egy maroknyi ember maradt életben.";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "Rossz hírek, fehér ember. A Caleuche újra gyilkolni megy.";
			link.l1 = "A Caleuche? Az az élôhalott kapitány Repülô Szívnek hívta a hajóját. Szóval tudtál a szellemhajóról, és mégsem figyelmeztettél? Ha tudtam volna, hogy ez a vitorlás rémálom az amulettre vadászik, soha...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Tuttuathapak látja, hogy a fehér kapitány feldúlt. Fehér kapitánynak le kell nyugodnia.";
			link.l1 = "Megnyugodni?! Megôrültél? Hogy tudnám túlélni az ilyesmit?!";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Igen, uram. Nyugodj meg és ne kiabálj. Mondd csak - még mindig nagy erôt akarsz tôlem kapni, ami örökre veled marad?";
			link.l1 = "Hát persze, hogy akarom. De már nincs nálam az amulett.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "Megtanítom neked, hogyan vedd el az amulettet a Caleuche kapitányától. Nem lesz könnyû. De ha megteszed, elviszed a hajóját, mint zsákmányt, értékes kincseket találsz, dicsôséget szerzel a népednek, és jutalmat kapsz tôlem.";
			link.l1 = "Az istenit! Szívesen elpusztítanám azt a fonnyadt szörnyeteget! De hogyan gyôzhetném le, ha sem kard, sem golyó nem árthat neki!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "Kész vagy rám hallgatni, fehér kapitány?";
			link.l1 = "Igen, készen állok, nagy sámán.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "Amikor apám fiatal harcos volt, fehér emberek érkeztek a földemre a Repülô Szív nevû hajón. A hegyekbe mentek. A legenda szerint ott van elrejtve ôseink szentélye. A jaguár harcosok szentélye. A fehérek megtalálták a szentélyt és az aranyat, és meggyalázták az ôsi szent dolgokat. Elvitték a chavinok nagy kincsét - Yum Cimil, a halál istenének és a jaguáremberek védôszentjének jáde koponyáját\nA fehér emberek a hajójukra jönnek. Elhatározzák, hogy visszatérnek, hogy még több aranyat vigyenek, de ahogy emberük a szárazföldre lép, szörnyû fájdalmak között meghal. Yum Cimil megátkozta a kapitányt és legénységét. Halhatatlanná válnak, de többé nem léphetnek a szárazföldre. Sok-sok telet hajóznak, fél évszázadot a te idôszámításod szerint. Így keletkezett a Caleuche.\nA testük elszárad, a húsuk elrohad, de még élnek. Ha levágod egy karjukat vagy lábukat, az visszajön. Ha felszeleteled ôket, újra eggyé válnak. Ha elsüllyed a hajójuk, megjavítják a víz alatt, és újra vitorlát bont.";
			link.l1 = "Nagyszerû...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " A caleuche-ok terrorizálják a tengerészeket. Ok nélkül támadnak, és biztos végzetet jelentenek. Nem gyakori vendég a Karib-tengeren. Szívesen vitorlázik a szülôföldem partjainál. Azt hiszem, el akarja távolítani az átkot. De soha nem fogja feloldani.";
			link.l1 = "De miért? Mit kell tennünk, hogy feloldjuk az átkot?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Jáde koponya. Vissza kell térnie Yum Cimil szentélyébe, a jaguár harcosok templomába. Több templom is van ott. A törzsem öregjei azt mondják, hogy van egy a Karib-tengeren egy kis szigeten. Ezért hajózott oda a Caleuche. Ha a koponya a templomban van, Yum Cimil varázslata megtörik, és halandóvá válik, és nem gyógyítja többé a sebeket.";
			link.l1 = "Ha! Valószínûbb, hogy nem fogják visszaadni a koponyát! Miért tennék, ha halhatatlanok és legyôzhetetlenek? És különben is, egyszerûen nem tudják visszahozni, ha nem léphetnek szárazföldre, nem igaz?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "Nincs koponyájuk. A kapitány eldobja az ôseim földjén, amikor visszatér a jaguáremberek szentélyébôl. A jáde nem arany, a fehér embernek nincs szüksége rá, nem tudná elvenni a gyönyörû zöld drágakövet a koponya szemében. És eldobta. Egy tengerész felvette, és nem érintette meg az átok\nAmikor a tengerész látta, hogy mivé vált a Caleuche legénysége, elmenekült. Eljött a falunkba. Apám látta azt a matrózt és Yum Cimil koponyáját. Aztán a fehér ember északra ment a part mentén és magával vitte a koponyát.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "Egy jáde koponyát, zöld kövekkel a szemgödrökben? A kezemben volt, el tudod képzelni? Én magam adtam oda Salomonnak. De ô elment Európába a lányával, és úgy tûnik, magával vitte a koponyát.";
				}
				else
				{
					link.l1 = "Egy jáde koponyát, zöld drágakövekkel a szemgödrökben? Szent szar... I... A saját kezemmel fogtam meg! És eladtam egy portugálnak... Merriman, vagy valami ilyesmi... Igen, ezt mondta - Yum Cimil koponyáját! Nagyon akarta! Félmillió pezót fizetett érte!";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "Egy jáde koponya, zöld drágakövekkel a szemgödrökben? De az a tengerész már ötven éve elpusztulhatott a Selva-ban, és a koponya talán örökre elveszett!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "Tudom, hogy a koponya a Karib-tengeren van. A Caleuche nem véletlenül van itt. Az elmúlt hat hónapban gyakran látták a szigeten. Régebben sok télen át nem volt ott. A Caleuche kapitánya érzi a jaguáremberek leletét. Így talált meg téged és a hajódat.";
			link.l1 = "Szóval, jól értem, hogy újra meg kell találnom ezt a koponyát? És aztán mit csináljak vele?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "A koponyának itt kell lennie, a Karib-tengeren. A Caleuche nem véletlenül van itt. Az elmúlt hat holdhónapban gyakran látták a szigeten. Azelôtt sok télen át nem volt ott. Caleuche kapitánya érzi a jaguáremberek leletét. Így talált meg téged és a hajódat.";
			link.l1 = "Szóval, jól értem, hogy újra meg kell találnom ezt a koponyát? És aztán mit csináljak vele?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "Elôször is, meg kell találnod a két amulettet, amirôl beszéltünk. Nélkülük nem tehetsz semmit. Az amulett erôt ad, hogy szembeszállj a jaguáremberekkel és minden ellenséggel, akivel összefutsz.";
			link.l1 = "Kiállni a jaguáremberek ellen? Mirôl beszélsz?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "A templom, ahová a jáde koponyát kell vinned, egy lakatlan szigeten van a Karib-tengeren. Jaguáremberek ôrzik. Mind halottak, de most már élnek. Amulett nélkül nem jutsz át rajtuk. A jaguáremberek életükben ádáz harcosok voltak, és haláluk után szinte legyôzhetetlenek. Az erôt maga Yum Cimil adta nekik.";
			link.l1 = "Halhatatlanok? Már megint? Szerencsés vagyok...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Miért lepôdtél meg ennyire, fehér kapitány? Yum Cimil a halál istene, a jáde koponya hatalmat ad a halottak és az élôk felett. Karib-tenger. Jaguáremberek ôrzik. Amulett nélkül nem tudsz átjutni rajtuk. Amulettel be tudsz menni a templomba és túlélheted, hagyd ott a koponyát, aztán keresd meg a Caleuche-t, gyôzd le a kapitányát és vedd el az amulettet, amit elvett tôled.";
			link.l1 = "És miért van szüksége a Caleuche kapitányának ezekre az amulettekre?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Szerintem a jaguáremberek templomába akar menni, és azt hiszi, hogy az amulett segít neki. De lehet, hogy tévedek. De a Caleuche-t mindig elcsábítják a földemrôl származó tárgyak. Elhajózott a sziget közelébe, ahol a jaguáremberek temploma van, és elhajózott a szülôföldem partjaihoz.";
			link.l1 = "És hol van az a sziget?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "Elôször is megtalálod Yum Cimil koponyáját és az amuletteket. Aztán beszélünk a szigetrôl.";
			link.l1 = "Rendben, akkor beszéljünk a szigetrôl. Tudnál adni egy tippet, hogy hol keressem a jáde koponyát?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "Nem tudom. De itt van, a Karib-tengeren. És az amulettek is. Kérdezd meg. Keresd. Találd meg.";
			link.l1 = "Heh... Rendben, megpróbálom.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "És légy óvatos, fehér kapitány. A Caleuche érzi Chavins tárgyait. Ha nálad van az amuletted, akkor megkeres téged. Ha megtalálja, menekülj, de gyorsan. Ha elkap, halott ember vagy.";
			link.l1 = "Ez az átkozott hajó ôrülten gyors! Kétszer olyan gyors, mint bármelyik hajó, amit valaha láttam. De azt vettem észre, hogy a széllel szemben nehezen vitorlázik.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "A Caleuche el van átkozva - ezért olyan gyors. Nehéz elmenekülni. Olyan hajóval kell rendelkezned, ami lehagyja a Caleuche-t. Különben meghalsz. Ha megtalálod az amulettet, hozd el nekem. Ne tartsátok az amulettet a hajón.";
			link.l1 = "Már megkaptam. Köszönöm a mesédet, nagyszerû sámán. Itt az ideje, hogy menjek.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "Kérni fogom a szellemeket, hogy segítsenek neked és megmentsenek a Caleuche-tól.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "Santiago_Lightman") {AddLandQuestMark(characterFromId("Santiago_Lightman"), "questmarkmain");}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "BasTer_Lightman") {AddLandQuestMark(characterFromId("BasTer_Lightman"), "questmarkmain");}
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("Odaadtad az amulettet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(néz) Igen, ez az. A második Chavins amulett. Jól van. Még egy amulettet kell találnod.";
			link.l1 = "Emlékszem rá, sámán. Hamarosan meglesz.";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Menj, fehér ember. Keress még egy amulettet.";
				link.l1 = "Már megvan, nagy sámán. Tessék, nézd meg.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Menj, fehér ember. Keress még egy amulettet.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("Odaadtad az amulettet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(néz) Igen, ez az. A harmadik Chavins amulett. Jól van. Megtaláltad az összes amulettet, amivel halott jaguár harcosokat, Yum Cimil szolgáit passzolhatod.";
			link.l1 = "Ha jól értem, szükségem lesz a jáde koponyára?";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "Igazat beszélsz. Yum Cimil jáde koponyája. El kell vinned Chavins templomába. Akkor a Caleuche végleg elveszíti a hatalmát.";
			link.l1 = "Tuttuathapak, kérlek, mondd meg, hol keressük? Van valami ötleted?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Nem. Gondolj arra, hogy hol láttad utoljára a jáde koponyát. Kinek adtad oda. Kezdj el ott keresni.";
				link.l1 = "Rendben, nagy sámán. Megteszek mindent, amit tudok.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "Egy fehér boszorkánymester érdeklôdik Yum Cimil koponyája iránt. Ô keresi. Még a mi falunkba is eljött. Úgy hallottam, hogy a boszorkánymester egy házban lakik a holland szigeten. Keressétek a holland szigeten a boszorkánymestert, és talán megtudtok valamit.";
				link.l1 = "Rendben, nagy sámán. Megteszek mindent, amit tudok.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "Kezdem Curacaóval, ahol átadtam Salamon számára. Talán találok valami nyomot - hogy megtudjam, mi történt a koponyával.";
				else sTemp = "Kezdem azzal, hogy ellátogatok Curacaóra - ott adtam el a jáde koponyát Joachim Merrimannak.";
			}
			else sTemp = "Tuttuathapak elmondta, hogy egy 'fehér varázsló' érdeklôdést mutatott a jádekoponya iránt, és azt tanácsolta, hogy keressük meg a holland szigeteken. Ki lehetett az?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "Menj, fehér ember. Keresd meg Yum Cimil jáde koponyáját.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "Itt van nálam, nagy sámán, nézd meg.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "Menj, fehér ember. Keresd meg Yum Cimil jáde koponyáját.";
			link.l1 = "Attól tartok, nem fog menni. Megtaláltam a varázslót, de az utolsó pillanatban elszökött a koponyával. Fogalmam sincs, hol lehet most.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "Ez nagyon rossz, fehér ember. Most nem mehetsz át a templomon, és nem gyôzheted le a Caleuche-t. Nem adok neked ajándékot. Most pedig menj el.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "Tûnj el, fehér ember.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(nézem) Igen, ez az. Nagyon szép. És nagyon ijesztô.";
			link.l1 = "Persze... De ami még érdekesebb - átkeltem az egész Karib-tengeren Kubától Dominikáig, és a caleuche soha nem próbált megtámadni, amikor nálam volt ez a koponya, nem is láttam. És amikor amuletteket vittem neked, állandóan elgázolt, amint kihajóztam, pár óra alatt rám talált.";
			link.l1.go = "Tuttuat_46a";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Azt hiszem, a Caleuche fél a koponyától, vagy nem érzi azt. Nincs más magyarázatom. Talán Yum Cimil a jáde koponyát nagyon veszélyessé tette a Caleuche számára - az átok mellett. Talán ezért akarta a kapitány annyira elvenni a népem három amulettjét. Hogy bölcsességet szerezzen, hogyan irányítsa Yum Cimil varázslatát.";
			link.l1 = "Tehát amíg a jádekoponya a hajóm fedélzetén van, nem kell félnem a Caleuche támadásaitól?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Pontosan, sápadtarcú. Nézd meg a saját szemeddel.";
			link.l1 = "Nagyon jó! Tehát átvehetem egy nagy hajó parancsnokságát, tisztességes legénységet alkalmazhatok, és szép fogadtatást készíthetek annak a két lábon járó halottnak, ha feloldódik róla a varázslat, anélkül, hogy attól kellene tartanom, hogy korábban elfogna...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...apropó, ami azt a varázslatot illeti - hová vigyem a jáde koponyát?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "El kell vinned Chavins templomába, és befejezni az utadat. El akarok mesélni neked egy történetet. Kész vagy meghallgatni, fehér ember?";
			link.l1 = "A fülem mindig nyitva áll a bölcsességedre, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "Ahogy ôseim legendái mondják, réges-régen, amikor a sápadtarcú emberek még nem érkeztek a mi földünkre, a csavinok nagy törzsfônöke épített egy nagyon-nagyon nagy kenut, és egy harcos csapattal elküldte a sok szigetbôl álló szárazföldre. A nagy törzsfônök fia vezette ôket, és ott volt az egyik nagy sámán is. A sok sziget földjén találtak egy sivatagos földet, és települést alapítottak, és nagy templomot építettek Yum Cimilnek, amilyet csak a mi nagy ôseink tudtak építeni\nA hírnökök jó hírekkel tértek vissza, de senki sem látta többé sem a törzsfônök fiát, sem a sámánt, sem a harcosokat. A legenda úgy tartja, hogy elmentek oda élni, haver a legbölcsebb sámánok beszéltek a szellemekkel, és azt mondták, hogy ott már nem élnek emberek, és hogy Yum Cimil uralja ezt a földet\nA Karib-tenger sok szigetének földje, fehér ember. Yum Cimil temploma olyan szigeten van, ahol sem fehér ember, sem indián nem él. Csak Yum Cimil szolgái, a Chavinavi ôrzik még mindig a templom folyosóit.";
			link.l1 = "És hol van az a sziget?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "A történetből megértem, hogy ez egy kis sziget, ettől a falutól azzal a szigettel abba az irányba, amit a sápadtarcúak 'északnak' hívnak, három sziget között, a negyedik oldalon pedig nagy víz — az óceán.";
			link.l1 = "Hmm... Dominikától északra, egy szigetháromszögben, az óceán szélén? Az ördögbe is, ez egy hatalmas tengerrész! Hogyan találjak ott egy kis szigetet, amelyről eddig senki sem hallott?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "Nem tudom jobban megmondani. De ismerek még egy történetet. A testvéreidtôl hallhattad. Úgy húsz téllel ezelôtt fehér ember találta meg azt a szigetet. Egy nôvel és egy öregemberrel együtt bement Yum Cimil templomába, és elvitt egy hatalmas ereklyét - a felkelô nap gömbjét. A sziget partjainál a sápadtarcú kapitányt megtámadják a Caleuche\nSápadtarcú legyen okos. Megvakítja a Caleuche kapitányát és legénységét a felkelô nappal. A Caleuche átka meggyengült, és a kapitány elsüllyesztette, de a felkelô nap gömbje feloldódott. Ha megtalálod a sápadtarcú embert, megmondja, hol van a sziget.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ha! Azt hiszem, ismerem azt a 'pale-arcú férfit'... A történetek túlságosan hasonlóan hangzanak. Szóval a Caleuche elsüllyedt?";
			else link.l1 = "Hmm... Szóval a Caleuche elsüllyedt?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Igen, de az átok megvédi ôket a haláltól. Megjavították, és folytatták örök útjukat.";
			link.l1 = "Rendben, értem. De mit csináljak a templomban? Hova tegyem a koponyát? Hogyan gyôzhetem le a jaguár harcosokat, akik ôrzik? Ha ôk is olyan Chavinavik, mint amilyeneket az a Merriman nevû varázsló idézett meg, ostobaság lenne egyedül odamenni - mindegyikük olyan erôs, mint tíz katona.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "Nem. A koponyával rendelkezô fehér varázsló által megidézett Chavinavi gyenge. Sokkal gyengébbek, mint azok, akiket maga Yum Cimil idézett meg. Soha nem árthatsz nekik, és a fegyverük egyetlen érintésével megölnek.";
			link.l1 = "Várjunk csak - és hogyan sikerült annak a 'pale-arcú férfinak' bejutnia a templomba és ellopnia a leletet?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "Mielôtt az elsô sápadtarcú belép a templomba, halott ôsök szellemei ôrzik. A sápadtarcú erôs harcos volt, és legyôzte ôket. Amikor ellopta a felkelô nap gömbjét, Yum Cimil dühös lett. Tüzet és kénkôt küldött a sápadtarcú emberre, és majdnem elpusztította a templomot, de az elmenekült a leletével. Yum Cimil most legyôzhetetlen jaguár harcosokat hívott, hogy ôrizzék a templomot.";
			link.l1 = "Dicsôséges! És akkor hogyan fogok beosonni?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "Segítek neked, fehér ember. Adok neked két Chavins amulettet, amit elhozol nekem. Beszélek az ôsök szellemeivel és megerôsítem az amulettet. Ha az egyik nálad van, úgy harcolhatsz a jaguár harcosokkal, mint a közönséges katonák, olyan leszel, mint egy közülük, bár nagyon erôs. Az amulett megvéd téged, és fegyveres erôt ad neked, amivel árthatsz Chavinavinak a templomban.";
			link.l1 = "Biztos vagy benne, hogy az amulettek segíteni fognak?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "Tudom. Beszélek az ôsökkel. Én nagy sámán. Bízz bennem. Vigyél két amulettet. Az egyik megvéd. A másik megerôsíti a fegyvert. Az egyik amulettet használnod kell. Melyiket választod. Ha nem viseled az amulettet, elpusztulsz a jaguár harcosoktól\nés emlékszel, hogy éjfélkor Yum Cimil visszahozza az életbe az összes harcost, akit megöltél. Meg kell találni az idôt, hogy nem harcolni ôket kétszer, vagy nem, szellemek azt mondják, hogy tudsz.";
			link.l1 = "Értem, értem.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "Veszel amuletteket. Itt vannak. Ne feledd, hogy a hatalmuknak vannak határai. Egy holdon belül elenyészik. Emlékszel, amikor azt mondtam, hogy nem birtokolhatod a hatalmadat? Csak a törzsünk nagy sámánjai birtokolhatják.";
			link.l1 = "Emlékszem. Szóval, csak egy holdam van? Egy hónap?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Igen. Amikor a Yum Cimil templomhoz érsz, meg kell találnod a szentélyt és egy nagy Kondor szobrot. Ez a templom legfontosabb része. Ide teszed Yum Cimil jáde koponyáját, és az átok feloldódik a Caleuche-ról. Amikor újra megtámad téged, legyôzöd ôt, mint egy közönséges ember. Aztán elhozod nekem az amulettet, amit elvett tôled.";
			link.l1 = "Kondor? Mi az?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "A kondor egy nagy madár, ami az otthonom hegyeiben él. Az ôseim a szentély közelében szobrot emeltek a kondornak.";
			link.l1 = "Rendben, megkeresem...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "Légy óvatos. Sok veszély leselkedik a templomban a jaguár harcosok mellett.";
			link.l1 = "Milyen veszélyek?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "Nem tudom biztosan. Nézd meg magad. Lehet, hogy csapda, vagy... zûrzavar. Nehéz belépni a szentélybe. A bejárat le van zárva, és meg kell találnod a módját, hogy kinyisd. Az ôseim nem csak nagy harcosok és sámánok voltak, hanem nagyszerû építôk is, hogy kinyissák, gondolkodnod kell.";
			link.l1 = "Heh! Félelmetesnek hangzik, de hadd 'm mindenki jöjjön! Nem vesztegetem az idôt. Azonnal vitorlát bontok!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Menj, fehér harcos! Én megidézem a szellemeket, hogy segítsenek neked a jaguár harcosok és a Caleuche ellen. Ne feledd, ha amuletteket használsz, segíthetek, ha nem, akkor elpusztulsz.";
			link.l1 = "Köszönöm, nagy sámán... elintézem.";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("Kaptál két amulettet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "De van egy nyomom: úgy tûnik, az a fehér kapitány, aki meglátogatta a Chavinok templomát, nem más, mint az én jó barátom, Nathaniel Hawk. Emlékszem, azt mondta, hogy Maroon Townban van egy térképe arról a szigetrôl. Azt hiszem, meglátogatom Nathant.");
			}
			else AddQuestUserData("Caleuche", "sText", "Ez egy hatalmas terület a tengerben, de nincs más választásom. Teljesen át kell fésülnöm. Sámán azt mondta, hogy Dominikától északra, és nem túl messze, így folyamatosan észak felé tudnék haladni, nagyon is lehet, hogy kicsit keletre vagy nyugatra. Említett valami kapitányt is, aki elpusztította az élôhalott hajót, talán szerencsém lesz, és egyszer talán megtalálom, sajnos azt mondta, hogy csak egy hónapom van, hogy megtartsam ezt az erôt, vagy bármi is legyen az, ó, hát ez van, ami van, kezdôdjön a keresés!");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "Én beszélgetek a szellemekkel. A szigeten voltál Yum Cimil templomában. Megtaláltad a Caleuche-t és az amulettet?";
				link.l1 = "Igazad van, nagy sámán. Megtaláltam a szigetet, bementem a templomba és bent hagytam a jáde koponyát.";
				link.l1.go = "Tuttuat_63";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Menj, fehér harcos.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Tuttuathapak, látod... Nem vittem idôben a koponyát a templomba, és az amulettetek elvesztette erejét.";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Felvetted az átkot a Caleuche-ról. Megtalált téged ezután?";
			link.l1 = "Igen. A szigeten találkoztunk. Harcba szálltam vele, és gyôztesen kerültem ki belôle. Most már mindhárom amulett nálam van. Tessék, vedd el ôket.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("Három Chavin amulettet adtál.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Te gyors és erôs harcos, sápadtarcú. Tuttuathapak nem szereti a fehér embereket, de én tisztelem a bátor és ügyes harcost. Nagyon jól csináltad. Megszabadítottad a tengereket a kaleuche-októl. Három amulettet hoztál nekem. Megjutalmazlak.";
			link.l1 = "Ígértél valamit a 'hatalomról, amit örökké tarthatok'?.";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "Igazat beszélsz. Megadom neked ezt a hatalmat. A Karib-tengeren senki sem ismeri a növény titkát, amit én ismerek. Figyelj rám, sápadtarcú! Az én házamban van gyógynövény. Rózsaszín Mangó-nak hívjuk. Hallottál errôl a növényrôl?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Igen. A kezemben tartottam. A cigányok nagy érdeklôdést mutatnak iránta. És az egyikük, Amelia gyógyító, még...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "Fogalmam sincs...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "Én hallottam Amelia gyógynövényszakértôtôl. Ô nem sokat tud, de nem is keveset. Nem ismeri a Rózsaszín Mangó titkát. Csak a nagy sámánok a szülôföldemrôl, ahonnan a Rózsaszín Mangó ide került, tudják használni a teljes erejét.";
			link.l1 = "Milyen erôt?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "Ez a gyógynövény az én hazámban terem, de a Karib-térségben is elôfordul. Ez egy világoszöld, magas növény, levelei olyanok, mint a tenyér, ujjakkal szétterítve, és kellemes illata van. Azonnal felismered, és nem téveszted össze semmivel. Én ismerem ennek a növénynek a titkait. Tudok belôle erôt nyerni.";
			link.l1 = "Értem, de miféle erôt?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "Én tudok fôzetet készíteni a Manga Rosából. Nagyon erôs bájitalokat. A Karib-tengeren rajtam kívül senki más nem tud ilyet készíteni. Az én fôzeteim az embert örökké erôsebbé, gyorsabbá, okosabbá, élesebb szemûvé, szebbé és szerencsésebbé teszik. Három ilyen bájitalt fôzök neked.";
			link.l1 = "Nagyon érdekes!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "Te nagy harcos vagy, ezért elôször is szükséged van egy bájitalra, ami erôsebbé tesz, és egy másikra, ami gyorsabbá tesz. És a harmadik bájitalt választod, miután elkészítettem az elsô kettôt. De hoznod kell nekem Manga Rosát, hogy elkészíthessem ôket - nekem nincs.";
			link.l1 = "Hol keressek Manga Rosát?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "A Rózsaszín Mangó egy ritka gyógynövény a Karib-tengeren. Ott nô, ahol az emberek nem sokat sétálnak. A hülye emberek szedik, szárítják és elszívják. Nagyon hülye emberek. NE FÜSTÖLJ! Ez energiapazarlás... Keressétek a dzsungeleket és az öblöket, a titkos helyeket, ahol a buta emberek nem járnak. Nézzétek meg alaposan. Minden fôzethez öt szál Rózsaszín Mangó kell.";
			link.l1 = "Rendben, nagy sámán. Visszajövök hozzád, amint elég Rózsaszín Mangó van.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Menj, fehér harcos. Hozz nekem Manga Rosát. Nem fogod megbánni. Az én bájitalaim a legjobbak. A szellemek segítenek neked a keresésben.";
			link.l1 = "Köszönöm. Köszönöm. Viszlát, sámán!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "Hoztál öt szál Rózsaszín Mangó-t a bájitalhoz?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Igen. Itt van öt növény, amire szükséged van.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Még nem, nagy sámán. A keresésem folytatódik...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "Nagyon jó. Gyere holnap, amint lemegy a nap. Fôzni fogok neked bájitalokat, amik növelik a reakcióképességedet és az ügyességedet.";
					link.l1 = "Rendben, sámán. Holnap este jövök.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Rendben. Gyere holnap, amint lemegy a nap. Olyan bájitalokat fôzök neked, amik növelik az állóképességedet.";
					link.l1 = "Rendben, sámán. Holnap este jövök.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Nagyon jó. Melyik bájitalt választod? Az erô, az éleslátás, az intelligencia, a szépség vagy a szerencse fôzetét?";
					link.l1 = "Az erô bájitalát.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Az éleslátás bájitala.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Az intelligencia bájitala.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "A szépség bájitala.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "A szerencse bájitala.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  Gyorsabbá teszi a mozgásodat, és jobban harcolsz a finom könnyû fegyverekkel.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  Kitartóbbá tesz a hosszú utakon, és jobban harcolsz éles szablyákkal.";
				dialog.text = "Fôzet kész, sápadt arcú harcos. Vedd el te."+sTemp+"";
				link.l1 = "Köszönöm, nagyszerû sámán.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "Még nincs kész, fehér ember. Gyere késôbb. Ne zavarj.";
				link.l1 = "Rendben...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "Én fôzök neked minden bájitalt, amit ígértem. Erôsebb leszel. Boldog vagy?";
				link.l1 = "Igen, nagy sámán. Ez valóban méltó jutalom volt.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "Ha találsz még öt Rózsaszín Mangó szárat, hozd el nekem. Készítek neked egy másik bájitalt.";
				link.l1 = "Hozok még belôlük. Viszlát!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "Gyere holnap, mint mindig. Fôzök neked egy bájitalt, hogy erôsebb legyél, és jobb, ha nagy baltával harcolsz.";
			link.l1 = "Rendben.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Gyere holnap, mint mindig. Fôzök neked bájitalt, hogy éles legyen a szemed, hogy minden célpontot láss, és jobban üss tüzes fegyverekkel, amelyek üvöltve üvöltenek.";
			link.l1 = "Rendben.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Gyere holnap, mint mindig. Fôzök neked bájitalt, hogy okosabb legyél, és jobban elbújj az ellenség elôl.";
			link.l1 = "Rendben.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Gyere holnap, mint mindig. Fôzök neked bájitalt, hogy szebb legyél, és jobban meggyôzd az embereket.";
			link.l1 = "Rendben.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Gyere holnap, mint mindig. Fôzök neked bájitalt, hogy szerencsésebb legyél, és szerencséd legyen.";
			link.l1 = "Rendben.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "Örülök, hogy tetszik a mûvészetem, a nagy sámán mûvészete.";
			link.l1 = "Mondd, Tuttuathapak, mire kell neked ez a három amulett? Csak kíváncsiságból...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "Már érzed ennek a két amulettnek az erejét. A szellemek segítenek nekem, hogy erôt adjanak nekik, és mindhárom amulett együtt nagy sámán bölcsességet és megvilágosodást ad az ôseimnek, a nagy Chavinoknak.";
			link.l1 = "Értem. Rendben, még egyszer köszönöm a kiváló bájitalokat. Igazán nagyszerû sámán vagy. Itt az ideje, hogy menjek. Isten veled, Tuttuathapak, remélem, még találkozunk.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Isten veled, fehér harcos. Többé nem keresel engem. Elvonulok, hogy megragadjam ôseim bölcsességét. A szellemek segítsenek téged az utadon!";
			link.l1 = "Hát akkor... hah... a szellemek világítsák meg az utadat is, nagyszerû sámán. Búcsúzz el...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("Amulettet adtál");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "Elszomorítasz, sápadtarcú. Én szertartást végzek a szellemekkel, hogy erôt adjak ezeknek az amuletteknek, te meg elpazarolod. Szomorú vagyok. Most menj el. Tuttuathapak, nincs több mondanivalód.";
			link.l1 = "Sajnálom, hogy nem volt szerencsém... Ó, nos... Viszlát, sámán.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "Minden hiába, tengerész. Nem leszel jobb nálam. És minden emberem, aki a fedélzeten fekszik, össze fogja rakni a csontjait, és hajnal elôtt újra felkel. Minket nem lehet megölni, mert a halál örökre elhagyott minket.";
			link.l1 = "Az istenit! Élsz vagy halsz? Valószínûbb, hogy még élsz - a halottak általában csendben fekszenek, és nem kardot lóbálnak. De kik vagytok ti, és miért támadtátok meg a hajómat?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "Balthazar de Cordes vagyok a Repülô Szívbôl. Szánalmas gyávák, akik semmit sem tudnak rólam, Van der Decken-nek hívnak, a Repülô Hollandi kapitányának. De ez nem számít. Ami számít, az az, hogy van nálad egy amulett, amit most elveszek. Szükségem van rá! Érzem! A Chavinok nagy amulettje, a három közül az egyik, végre az enyém lesz! Térdelj le elôttem, halandó! És talán fájdalommentessé teszem a halálodat!";
			link.l1 = "Menj a picsába, hulla!";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "Nem hiszem el! Olyan régen volt már, hogy utoljára a saját véremet láttam és fájdalmat éreztem... HOGYAN?!";
			link.l1 = "Ezúttal vesztettél, Balthazar de Cordes. Ismerem a történeted. A jáde koponya visszakerült Chavins templomába, és Yum Cimil átka többé nem függ rajtad vagy a legénységed tagjain. Többé nem fogod visszahozni a tengerészeidet az életbe.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Ó, szóval talán megváltónak tekintheted magad? Nem! Balthazar de Cordes drágán fogja eladni azt a kevéske életet, ami még megmaradt neki!";
			link.l1 = "A Repülô Szív utolsó útja itt ér véget, Khael Roa-nál. És nem fogod felemelni a hajódat a tengerfenékrôl, mint huszonöt évvel ezelôtt.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "Sólyom! Huszonöt év telt el, és én még mindig úgy emlékszem rá, mintha csak tegnap lett volna. Annak a gömbnek a ragyogására, amely elvakított minket, és kettészakította a hajómat. Az volt a Repülô Szív és Balthazar de Cordes elsô és egyben utolsó veresége... Szóval utoljára keresztezzük egymást, kapitány! A halál a csatában könnyû és üdvözlendô!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Наш Алонсо после финального абордажа на Калеуче
		case "Caleuche_Alonso_1":
			dialog.text = "A rozoga hajó ki van pucolva a söpredéktől, kapitány. Ezúttal a holtak nem keltek fel. De maga a ladik... felfoghatatlan, hogyan úszik még.";
			link.l1 = "Az átok tartotta össze, Alonso. De ennek most vége.";
			link.l1.go = "Caleuche_Alonso_2";
		break;

		case "Caleuche_Alonso_2":
			dialog.text = "Mi legyen a parancs? Felgyújtsuk – és le van tudva az egész?";
			link.l1 = "Még átgondolom. Még így is, darabokra hullva, a 'Repülő Szív' kis híján szitává lőtte a hajónkat.";
			link.l1.go = "Caleuche_Alonso_3";
		break;

		case "Caleuche_Alonso_3":
			dialog.text = "Tűzerőből aztán nincs hiány ezen az átkozott roncsón... De nem is ezért jöttem – van egy matrózunk, Jacques...";
			link.l1 = "Jacques Trudeau? Rémlik. Nemrég csatlakozott hozzánk, igaz?";
			link.l1.go = "Caleuche_Alonso_4";
		break;

		case "Caleuche_Alonso_4":
			dialog.text = "Úgy van, kapitány. Ez a fráter hihetetlen érzékkel szúrja ki az értékeket. Ahogy a holtak elcsendesedtek, azonnal odaugrott egy priccshez, bemászott alá – és előrántott egy ládát. És benne – ötezer dublon!";
			link.l1 = "Ötezer? Hm... Úgy tűnik, Balthazar de Cordes és az emberei tényleg reménykedtek, hogy megszabadulnak az átoktól. Aranyat tömtek a zsebeikbe, szabad életre vágyva... ha egyszer véget érne ez az egész.";
			link.l1.go = "Caleuche_Alonso_5";
		break;
		
		case "Caleuche_Alonso_5":
			dialog.text = "A mi legénységünk se bánná azt az életet, kapitány... Ha megosztja velük a zsákmányt, örökre hálásak lesznek. De ha nem – azt se felejtik el.";
			link.l1 = "Igazad van, Alonso. Megérdemlik, hogy kicsit kényeztessük őket. Add nekik a felét, Jacques pedig kapjon egy hét szabadságot az őrségből. Ma pedig grog helyett rumot tölthettek. De maradjatok éberek – tudod, a tenger nem kegyelmez.";
			link.l1.go = "Caleuche_Alonso_6";
			link.l2 = "Hm... Talán igazad van, Alonso. Rájuk fér egy kis lazítás. Adj nekik a zsákmány negyedéből. És ügyelj rá, hogy ezek a részegek ne kezdjenek ünnepelni, amíg nem horgonyzunk le valami kikötőben.";
			link.l2.go = "Caleuche_Alonso_7";
			link.l3 = "Hogy ezek a naplopók az első kikötőben szétszéledjenek kocsmákba meg bordélyokba? Nem fogok egy hónapot azzal tölteni, hogy egyenként összeszedjem őket. Elég nekik a zsold, amit kapnak. A dublonokat meg hozzátok ide. Nehogy valakinek eszébe jusson lenyúlni.";
			link.l3.go = "Caleuche_Alonso_8";
		break;
		
		case "Caleuche_Alonso_6":
			dialog.text = "Úgy lesz, kapitány. És ne aggódjon, az emberek sosem hagyják cserben.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_2");
		break;
		
		case "Caleuche_Alonso_7":
			dialog.text = "Igenis, kapitány. Tudom, hogyan tartsam féken ezeket az ördögöket – számíthat rám.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_3");
		break;
		
		case "Caleuche_Alonso_8":
			dialog.text = "Ahogy parancsolja, kapitány. A legénység persze többet remélt... de ön a kapitány, ön dönt.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_4");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "Végre felébredtél, kapitány... Hogy érzed magad?";
			link.l1 = "Az istenit, mi történt? Szétrepedt a fejem a fájdalomtól...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Amikor beléptünk a kapitányi kabinba, a padlón feküdtél, még mindig egy mozdulatlanul. A srácok felkaptak és felvonszoltak a hajónkra - és éppen idôben, mert a fedélzeten fekvô halottak újra kelni kezdtek\nSzent Szûzanya és minden szentek! Gyorsan elvágtuk a köteleket, és megpróbáltunk elhajózni, de a hajójukról érkezô salvadó lövedék gyorsan szilánkokra törte a vén teknônket, és elvesztettük az irányítást felette. Aztán felhúzták a vitorlákat, és egy szempillantás alatt eltûntek\nA hajónk körbefutott, és mindenki, akinek sikerült túlélnie, csónakban ért partot. Sok jó ember halt meg ma... bárcsak a fedélzeten maradtunk volna... De biztosak voltunk benne, hogy a vihar végleg végez a hajóval.";
			link.l1 = "Nem az önök hibája, uraim. Ez volt a helyes döntés. Köszönöm, emlékezni fogok rá.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Behúztuk önöket a csónakba, majd a partra vittük. Majdnem meghaltál...";
			link.l1 = "Az életemmel tartozom neked. Mennyi ideig feküdtem itt eszméletlenül?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Egy egész napig. Kimostuk és bekötöttük a sebeidet, gyógyszert adtunk neked, és rumot öntöttünk beléd. Hamarosan meggyógyulsz.";
			link.l1 = "Ezúttal biztosan nem fogok meghalni. Bár nem érzem magam igazán jól...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Az biztos... A repülô holland volt az, kapitány? Miért támadtak meg minket? És miért nem lôttek ránk a beszállás elôtt, hanem késôbb majdnem elsüllyesztették a hajónkat egyetlen sortûzzel?";
			link.l1 = "A kapitányuknak szüksége volt az amulettre, amirôl beszéltem Tuttuathapakkal, egy indián sámánnal. Ezért nem süllyesztettek el minket azonnal, de mivel a vezetôjük elvette az amulettet, gyorsan elintézett minket... Micsoda rémálom! Egy hajó, amit a halottak irányítanak! Lehetetlen elhinni...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Igen, most rajtunk volt a sor, hogy találkozzunk a Repülô Hollandiával. Ha lesz rá lehetôségem, elmegyek a templomba, meggyújtom a gyertyát a csodás szülésemért, és imádkozom a mi Urunkhoz...";
			link.l1 = "Én is... Azt hiszem. De elôbb visszamegyek abba a faluba. Mindent el kell mondanom Tuttuathapaknak. Az az átkozott hajó az amulett miatt támadott meg minket! Biztos vagyok benne, hogy annak a vörösbôrû ördögnek volt néhány ötlete, hogy mi a fenének lehetett szüksége az élôholtaknak rá.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Jól van, rendben. De légy óvatos sapka, a sebeid alig gyógyultak be, legalább vigyél magaddal valakit a biztonság kedvéért.";
			link.l1 = "Óvatos leszek, ígérem. Köszönöm, hogy nem hagytál magamra!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Mirôl beszélsz, kapitány? Mi elmennénk érted a világ végére is, és több ezer élôhalottal harcolnánk! Kár, hogy ennyit vesztettünk, de ez a történet legendákba fog kerülni.";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "Hé! Még nem gyûjtöttem elég kígyóbôrt, hogy eladjam neked, úgyhogy húzz el!";
			link.l1 = "Hmm... Te vagy Fergus Hooper?";
			link.l1.go = "fergus_1";
			DelLandQuestMark(npchar);
		break;
		
		case "fergus_1":
			dialog.text = "Nem, a nevem Tuttuathapak, és megátkozlak, ha nem tûnsz el azonnal. Szóval jobb, ha sietsz, különben...";
			link.l1 = "...elveszítem az eszem, felgyújtom a saját hajómat, a matrózok megölnek és elveszik minden holmimat. Ugye?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Arrgh... Mi a fene, ki vagy te!? Honnan...";
			link.l1 = "Van egy közös barátunk, Fergus. Ô egy világítótoronyôr, és a neve "+GetFullName(sld)+". Ô mesélt rólad, és elküldött, hogy keresselek meg. Egyébként személyesen ismerem Tuttuathapak sámánt, úgyhogy a vicced nem jött be, bocsánat. Figyelj, én nem keresem a bajt. Szeretnék venni tôled valamit, és nem a kígyóbôrökrôl van szó.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "Ó, szóval ismered az öreg barátomat! Hogy van? Még nem halt bele az unalomba a világítótornyában? Kérem, üljön le, matróz, igyon velem egyet!";
			link.l1 = "Sajnálom, Fergus, tényleg nincs sok idôm. Figyelj, szükségem van arra az indián amulettre, egy olyanra, amelyet néhai kapitányod Tuttuathapakkal együtt vitt el a Mainból. Jó árat fizetek érte, te pedig megszabadulsz egy veszélyes csecsebecsétôl.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "És mi olyan veszélyes benne? Be nem láttam semmi rosszat benne. Ez csak egy haszontalan kô.";
			link.l1 = "Azért, mert már nem hajózol a tengeren. Nemrég még nekem is volt egy hasonló amulettem. Egy szellemhajó vadászik ezekre a dolgokra.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Viccelsz, pajtás? Talán Tuttuathapak ismerete megviselte magát? Vigyázz, kapitány, az a vörösbôrû ördög felfalja az elmédet...";
			link.l1 = "Hiszed vagy sem, de az igazat mondom. Magam sem hinném el, ha nem a saját szememmel láttam volna, a Könyvre esküszöm, vagy megkérdezheted azokat, akik velem voltak. Alig éltem túl azt a találkozást a Caleucheal.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "A Caleuche?";
			link.l1 = "Nos, a Repülô Hollandiának hívják, de az igazi neve Repülô Szív. Mindegy. Csak add el nekem azt az amulettet. Úgysem használ neked, tudom.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "Így van. Ez csak egy haszontalan csecsebecse, bár nagyon szép. Figyelj, én minden további nélkül eladtam volna neked, de tudod - már nincs nálam. Ellopták a kunyhómból, többek között, amikor kint a dzsungelben vadásztam. Ez nemrég történt, úgy egy hónapja. Sajnálom, de nem tudok segíteni.";
			link.l1 = "És ki lopta el?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Komolyan azt hiszi, hogy itt ülnék, ha tudnám, ki fosztotta ki az otthonom? Egy tolvaj- és rablóbanda tevékenykedik Belize-en kívül, és vannak besúgóik a városban. Legalábbis a parancsnok ezt gondolja. Biztos vagyok benne, hogy ôk voltak.";
			link.l1 = "A parancsnok tud a banditákról, és mégsem tesz semmit?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Hogy tesz-e valamit vagy sem, azt nem tudom. Az egyetlen dolog, amit biztosan tudok, hogy a dolgaim eltûntek, és velük együtt a te drága amuletted is. Próbáld meg felkutatni ezeket a banditákat - talán megtalálod a zsebükben. Nem valószínû, hogy sikerült eladniuk - a kereskedôknek nincs szükségük ilyesmire.";
			link.l1 = "Rendben, megyek és meglátogatom a parancsnokot. Sok szerencsét, Fergus!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "Hé! Mire van szükséged? Nem várok vendégeket. Tûnjetek el!";
			link.l1 = "Miért vagy ilyen goromba, barátom? Csak meg akartam kérdezni...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "Nem hallottad? Takarodj a picsába, vagy kirúglak az ajtón!";
			link.l1 = "Hmm... Nos, talán mégiscsak te vagy az, akit keresek. Túl idegesnek tûnsz, haver...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Túl okosnak képzeled magad, nem igaz? Még egyszer: vagy most azonnal eltûnsz, vagy hívom az ôrséget, és rács mögé dugnak!";
			link.l1 = "Rács mögé dugnak? Milyen érdekes. Tudod, most már szinte biztos vagyok benne, hogy megtaláltam, akit kerestem. Rendben, egyetértek. Hívjuk az ôröket, aztán együtt megyünk a parancsnoki irodába, mint egy boldog család. Én már jártam ott, így emlékszem az útra... Ôrség! ÔRSÉG!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Cseszd meg! Átgázolok rajtad!";
			link.l1 = "Oh ho-ho! Nos, megpróbálhatod!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "Hé, utazó! Üdvözöllek, üdvözöllek... Vacsora, szállás - mindent a pénzedért. Szóval, készüljetek fel, hogy kifordítsátok a zsebeiteket!";
			link.l1 = "Ne olyan gyorsan, jóember. Van egy kis dolgom veled.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "Üzlet? Ha-ha! Az egyetlen üzleted az, hogy nekem adod az összes ezüstödet és aranyadat!";
			link.l1 = "Fogd már be! Hoztam neked egy levelet Belize-bôl, amire vártál. A hírnök nem tudott kijönni az ôrökkel, ezért rám bízta az ügyet.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "Mutasd meg!";
			link.l1 = "Tessék...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("Adtál egy cetlit");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(olvasás) Hm... Ez bizonyára furcsa... Hogyan keveredtél bele?";
			link.l1 = "Már mondtam, hogy lefoglalták az emberedet, ezért átvettem a munkáját. Pénzt és meleg fogadtatást ígért tôled...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "Meleg fogadtatás? Rendben, haver. Bemelegítünk, megetetünk, pénzt adunk, meg minden ilyesmi - de neked, neked is be kell bizonyítanod, hogy nem vagy egy gárdista' kutya. Most van egy elszámolnivalónk\nA közeli öbölbe nemrég érkezett egy kereskedô; a jelek szerint a vámhivatal mellett akar beosonni a városba az árujával. De a vámot még így is beszedjük tôle. Végül is törvénytisztelô emberek vagyunk! Te is velünk jössz. Tudod, hogy a kard melyik vége hova való?";
			link.l1 = "És kapok én is részt ebbôl a vámból?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Persze, hogy kapsz! Ha bátor vagy a csatában, és ha életben maradsz. De ne várj könnyû menetet, a kereskedô nincs egyedül, kísérete van, méghozzá igen nagy kíséret. Nos, ideje indulni - a zsákmányunk közel van. Fiúk! Készítsétek elô a fegyvereket, indulunk!";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "Látom, nem vagy gyáva. Szép munka! Megérdemeltétek a részeteket. Hogy szeretnétek? Készpénzben? Áru? Sok alkoholt vittek, biztos, hogy sokat ér.";
			link.l1 = "Készpénz.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Áru.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("Kaptál 100 dublont.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Tessék! Ez a táska pedig a levél kézbesítésére szolgál.";
			link.l1 = "Köszönöm! Na, így szeretem én ezt!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("Kaptál 30 üveg rumot");
			Log_Info("Kaptál 12 üveg bort");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Tessék, tessék! Csak ne idd magad halálra, ha-ha-ha-ha! És ez a táska a levél kézbesítésére szolgál.";
			link.l1 = "Köszönöm! Na, így szeretem én ezt!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("Kaptál egy erszényt");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "Nekem rendes fickónak tûnsz. Mit szólnál még egy adaghoz? Arról a levélrôl van szó, amit nekem kézbesítettél.";
			link.l1 = "Persze.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "Akkor gyere a barlangba. Kettô van belôlük. Menj a dzsungelben arra a pontra, ahol utoljára találkoztunk, aztán menj a bal oldali ösvényen. Három nap múlva gyülekezünk a barlang bejáratánál, éjféltôl egyig. Megértetted? Ha jó fiú vagy, felveszünk a bandánkba. De ne feledd - ha bármit is kifecsegsz a városban, véged van. Hosszú a karom.";
			link.l1 = "Ne ijesztgess már. Majd én elintézem. Csendben leszek, mint egy hal. Várjatok meg három nap múlva, ott leszek. Szeretem a könnyû pénzt!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "Rendben, haver. Most pedig tûnj el, mielôtt az ôrök idejönnek. Mi is elmegyünk.";
			link.l1 = "Viszlát, haver...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "Mi van! Úgy veszem, úgy döntöttél, hogy követelsz valamit a tulajdonunkból? Ezt nem úszod meg, te mocskos féreg!";
			link.l1 = "Kit neveztél az elôbb féregnek, te szemétláda?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "Helló, kolléga! Mi szél hozott ide?";
			link.l1 = TimeGreeting()+", mynheer Jackson. Örülök, hogy végre megtaláltalak.";
			link.l1.go = "reginald_1";
			DelLandQuestMark(npchar);
		break;
		
		case "reginald_1":
			dialog.text = "'Mynheer Jackson', ha-ha! Hát, hogy ôszinte legyek, hamarosan én is így fogom hívni magam. Szünet nélkül dolgozom ennek az átkozott cégnek... de jól fizetnek, nagyon jól!... Szóval, mi szél hozott ide, haver?";
			link.l1 = "Közös ismerôsünk, a világítótorony ôrzôje mondta, hogy van egy ôsi indián amuletted. Gondolom, sosem használtad, és nekem nagyon nagy szükségem van rá. Meg akarom venni tôled.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "Ó, arra a díszes csecsebecsére gondol, amelyrôl a nyugdíjas bosunnál érdeklôdtem? Igen, barátom, igazad van, igazából sosem volt hasznos, csak szépen néz ki.";
			link.l1 = "Mennyit kér érte?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "Tudja, van egy kis probléma... Hadd magyarázzam meg. Jelenleg nincs nálam. Mivel soha nem találtam rá hasznát, a parton hagytam a ládámban, a többi holmim között.";
			link.l1 = "Ó, ez megmagyarázza, hogy te még mindig... nos, mindegy. Menjünk a ládádhoz, és megveszem tôled az amulettet. Ilyen egyszerû. Hol van nálad?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "Ez nem olyan egyszerû. A ládám Barbadoson van, a világítótoronyban, és biztonságosan le van zárva, hogy távollétemben senki ne tudjon hasznot húzni belôle. És nagyon sajnálom, de nem mehetek veled Barbadosra, a hollandokkal kötött szerzôdésem szerint Philipsburg és Port Royal között kell hajóznom, és pontosan be kell tartanom a menetrendet. Barbados pedig a közelében sincs ennek az útvonalnak.";
			link.l1 = "És mit tehetünk? Nagyon, nagyon nagy szükségem van arra az amulettre!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Hmm... Nos, van egy lehetôség. Odaadom neked a ládám kulcsát, és te magad hajózol Barbadosra. De kártalanítanod kell minden cuccot, ami benne van, és a tiéd lehet. Sajnálom, hogy bizalmatlan vagyok - de meg kell értened. Még soha nem láttalak.";
			link.l1 = "Mennyibe kerül?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Ötszáz aranypénz. Nem kevesebb.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Megkaptad! Itt van az aranyad.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Hmm... Nincs nálam annyi dublon.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "Akkor gyere vissza hozzám, ha összegyûjtötted a pénzt. Ha egyszer megtaláltál, akkor újra meg fogsz találni. Egy jó ideig St. Martin és Jamaica között fogok hajózni.";
			link.l1 = "Rendben, megegyeztünk.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "reginald_9":
			dialog.text = "Megint te, barátom? Van 500 érméd?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Igen. Itt az aranyad.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Még nem, de dolgozom rajta.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			RemoveDublonsFromPCharTotal(500);
			DelLandQuestMark(npchar);
			
			dialog.text = "Remek! És itt a kulcsod. És csak egy kérésem van: miután elvettél mindent, ami benne van, kérlek, hagyd a kulcsot a zárban. Nem szeretnék új zárat és kulcsot rendelni hozzá.";
			link.l1 = "Rendben.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "Akkor sok szerencsét, barátom! Bon voyage!";
			link.l1 = "Neked is... Bon voyage, mynheer Jackson!";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_SpawnItemsInTheChest");
			AddQuestRecord("Caleuche", "20");
		break;
		
		case "Caleuche_Reginald_21":
			dialog.text = "Mi a pokol kell tőled nekünk? Ez a hajó a Holland Nyugat-Indiai Társaságé, és az ilyen húzások nem maradnak büntetlenül. A föld alól is előszednek – téged is, meg a söpredékedet is.";
			link.l1 = "Lehúzhatják magukat a hollandok a kereskedelmi társaságukkal együtt. Egy régi indián amulettet keresek, és tudom, hogy nálad van – vagy volt.";
			link.l1.go = "Caleuche_Reginald_22";
		break;

		case "Caleuche_Reginald_22":
			dialog.text = "Te megőrültél! Egy semmiség miatt megtámadni egy hajót?";
			link.l1 = "Fogd be, és add ide, talán akkor életben maradsz.";
			link.l1.go = "Caleuche_Reginald_23";
		break;

		case "Caleuche_Reginald_23":
			dialog.text = "A francba... Nincs nálam. Barbadoson van.";
			link.l1 = "Akkor ez a rozzant teknőd most süllyed el, te pedig a patkányokkal utazol a raktérben. Útközben bőven lesz időnk, hogy elmondd, pontosan hol keressem. És hidd el – van pár legényem a fedélzeten, aki még a legkeményebb fejű tuskóból is kiszedi az igazat... szó nélkül, mindenféle udvariaskodás nélkül.";
			link.l1.go = "Caleuche_Reginald_24";
		break;

		case "Caleuche_Reginald_24":
			dialog.text = "Nem kell ezt tovább fokozni. Egy ládában van a világítótoronynál. Le van zárva. Itt a kulcs.";
			link.l1 = "Okos döntés, barátom. Kár, hogy másoknak nincs ennyi eszük... kevesebbet kéne bemocskolnom a kezem.";
			link.l1.go = "Caleuche_Reginald_24_1";
			link.l2 = "Jól döntöttél. Csakhogy… nem hagyhatlak életben. Egyenesen rohannál a holland kufárokhoz, és az ő figyelmükre nincs szükségem.";
			link.l2.go = "Caleuche_Reginald_24_2";
		break;
		
		case "Caleuche_Reginald_24_1":
			dialog.text = "Abban a ládában van minden, amit a hollandok szolgálatában szereztem az évek során...";
			link.l1 = "Akkor állapodjunk meg: a láda az enyém, a bőröd a tiéd. Tisztességes üzlet...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_EndFightWithReginald");
		break;
		
		case "Caleuche_Reginald_24_2":
			dialog.text = "Argh...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_KillToReginald");
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "Helló, kapitány "+GetFullName(pchar)+". Örülök, hogy üdvözölhetem Willemstadban.";
			link.l1 = "Helló, atyám. Nem emlékszem rád. Ismerjük egymást?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "Érdeklôdtem önrôl, amint a hajója kikötött. És azt hiszem, kérhetem a segítségét.";
			link.l1 = "Nagyon érdekes. És miért én?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Mert sokat tett a Szabad Tartományok Köztársaságáért. Jóban vagy a Társasággal, és jóban vagy a kormányzóval. Már több instanciához is fordultam, és megdorgáltak, de remélem, hogy egy olyan nemes ember, mint te, nem utasítaná el Urunk szolgájának szerény kérését.";
			}
			else
			{
				dialog.text = "Mert ön nem áll a kormányzónk szolgálatában. Ön nem a Társaságnak dolgozik, és nem áll kapcsolatban a hadseregünkkel - különben valószínûleg csak félresöpörne, mint egy idegesítô legyet, hiszen már többször fellebbeztem és megdorgáltak.";
			}
			link.l1 = "Akkor jó. Mi a kérésed természete?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "A bank hátsó részén van egy ház. Egy hölgy, aki ott lakott, egy szobát adott ki benne egy nagyon gyanús típusnak, nem helyi, és nem holland. Így ismerte fel ôt a mi elöljárónk, "+sld.name+"atya\nA portugál Joachim Merriman volt, akit az inkvizíció boszorkánysággal és szentségtelen erôkkel való üzérkedéssel vádolt. Az Újvilágban bujkált az inkvizíció elôl. Tudod, a spanyolok gyakran vádolták eretnekséggel és boszorkánysággal a kegyelembôl kikerülteket, hogy máglyán égessék el ôket, de... Ebben az esetben igazuk volt. Merriman egy varázsló\nSzóval, egy ideig Willemstadban élt, aztán olyan hirtelen tûnt el, ahogyan felbukkant. És egy idô után egy nôt, aki a szobát bérelte neki, soha nem látták kimenni abból a házból. Soha! És azóta sem látták soha sehol\nAz éjszaka pedig a polgárok idônként vörös-kék fényeket látnak villogni a második emelet ablakaiban, és furcsa hangokat hallanak, szinte valami szentségtelen sikolyokat. Az atya "+sld.name+" a parancsnokhoz fordult. Ô négy katonából álló járôrt küldött, átkutatták a házat, de nem találtak semmit: sem magát a házinénit, sem mást, sem semmi gyanúsat\nDe ezek a furcsa dolgok továbbra is megtörténnek. A házinéni azóta sem jelent meg, és ez a pokoli fény még mindig ott látható éjszakánként. Ráadásul nemrég két koldus is eltûnt. Hallottam ôket, amint a parvison beszélgettek - tudták, hogy a házban nincsenek gazdák, ezért úgy döntöttek, hogy ott szállnak meg. Azóta senki sem látta ôket.";
			link.l1 = "Gondolom, azt akarja, hogy menjek be a házba, és nézzem meg, mi történt valójában?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Pontosan, nemes uram. Kérem, segítsen a Szent Egyháznak. A parancsnok azt mondja, hogy csak képzelôdünk, mivel az ô járôre nem talált semmit. A kormány is így gondolja. A közembereket egyszerûen nem érdekli, mert nem látják, hogy ez egyértelmû fenyegetést jelentene rájuk nézve.";
			link.l1 = "Hmm... És éjszaka kell majd oda mennem?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Igen, mynheer. Nappal csend van ott, ezért nem találtak semmit a katonák, szerintem a parancsnok félti az embereit, én is félteném. De kérem, könyörgöm. Atyám "+sld.name+" megköszöni és megjutalmazza a szolgálatodat. Ha egyszer az éjszaka folyamán eljutottatok abba a barlangba, kérlek, mondjátok el neki, hogy mit találtok ott. Biztosíthatom, hogy a mi aggályaink megalapozottak.";
			link.l1 = "Rendben. Átgondolom.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Köszönöm, kapitány. Remélem, nem utasítja el szerény kérésemet. Kérem, tegye meg az Urunk, a hitünk és minden szent nevében. Áldásomat adom rá.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "Látogasson el Joaquim Merriman házába, ahol, elmondása szerint, különös dolgok történnek éjszaka. Emlékszem arra a különleges csillogásra Merriman szemében, amikor a jáde koponyára nézett, és egy kicsit hátborzongatóan érzem magam. Úgy tûnik, hogy az öreg zsidó nem tudott ellenállni a félmillió pezó összegének. Akárhogy is van, nincs kedvem éjszaka Merriman egykori lakhelyére menni.";
				else sTemp = "meglátogatom régi ismerôsöm, Joachim Merriman házát, ahol állítólag éjszaka furcsa dolgok történnek. Még mindig emlékszem arra a csillogásra Merriman szemében, amikor a koponyát nézte, és ôszintén szólva megijedtem. Nem igazán tetszik az ötlet, hogy éjszaka meglátogassam egykori lakhelyét, ki tudja, miféle ördögök leselkednek ott.";
			}
			else sTemp = "Meglátogatom a bank hátsó részén lévô házat, ahol valami Joachim Merriman bérelt egy szobát. Úgy tûnik, ez az a boszorkánymester, akirôl Tuttuathapak beszélt. A szerzetes szerint különös dolgok történnek ebben a házban éjszaka. Nagyon kényelmetlenül érzem magam, ha meglátogatom a varázsló egykori otthonát, ki tudja, miféle ördögök leselkednek ott.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "Várj csak, haver. Jobb, ha nem mész oda, ha becsülöd az életed.";
			link.l1 = "És mi az alku?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Hidd el, nem akarod tudni. De maga a halál is ott van a sarkon, és a Könyvre esküszöm, hogy nem fogsz élve visszajönni, vannak dolgok, amik meghaladják a képzeletedet.";
			link.l1 = "Nos, ha te mondod, nem kísértem a sorsot. Köszönöm a figyelmeztetést.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "Szívesen. Maradj távol attól az ösvénytôl.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "Ne menj arra az ösvényre, haver.";
			link.l1 = "Igen, emlékszem...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Biztos, hogy oda akarsz menni?";
			link.l1 = "Abszolút. "+sld.name+", a havannai egyház elöljárója küldött ide. Meg kell állapítanom, mi történik itt, és megfelelô intézkedéseket kell tennem.";
			link.l1.go = "cavehunter_6";
			DelLandQuestMark(npchar);
		break;
		
		case "cavehunter_6":
			dialog.text = "Mi történik itt? Attól tartok, hogy reszketni fog a félelemtôl, ha a saját szemével látja, mi történik itt.";
			link.l1 = "Úgy érti, a két lábon járó holtak?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Igen. És jobb, ha hisz a szavaimnak.";
			link.l1 = "És én hiszek neked. Már találkoztam azzal a szentségtelen dologgal Willemstadban, és elpusztítottam. És most bemegyek oda, és elpusztítok minden mocskot, ami ebben a barlangban lapul.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "Egyedül fogsz odamenni? Halott ember vagy, haver. Fogalmad sincs, hogy mennyi ilyen dolog van ott. Nos, menj, ha muszáj, én pedig elmegyek a templomba, hogy gyertyát gyújtsak a lelked békéjéért.";
					link.l1 = "Ne siess, hogy eltemess engem. Láttam már rosszabbat is.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "Csak ti ketten? Attól tartok, nem jutnak messzire. Fogalmad sincs, mennyi ilyen dolog van ott. Ez öngyilkosság.";
					link.l1 = "Csak nem ismer minket jól, barátom. Lépjen félre, és megtisztítjuk ezt a szentségtelen barlangot.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "Csak ti hárman? Biztos tapasztalt harcosok vagytok, ha ezt meg meritek tenni. De attól tartok, hogy nem fog sikerülni. Fogalmatok sincs, hogy mennyi ilyen dolog van a barlangban.";
					link.l1 = "Csak nem ismer minket jól, barátom. Lépjen félre, és megtisztítjuk ezt a szentségtelen barlangot.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "Látom, nem vagytok gyávák. De tényleg fogalmatok sincs, hogy mennyi ilyen dolog van. Egy ilyen viszonyban minden ember számít. A fenébe is, veletek tartok, és lelövöm azt a mocskot a muskétámmal!";
					link.l1 = "Bátor lélek vagy, barátom. Nem utasítom vissza a segítségedet. Gyerünk, menjünk!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "Gyerünk, gyerünk! Halál a mocskos élôholtakra!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Ez aztán a mészárlás! Ki gondolta volna, hogy ennyi halott rejtôzik ezen a helyen! Nos, most legalább pihenhetünk... Kérlek, szólj errôl annak az atyai elöljáródnak, aki ide küldött téged. Remélem, hogy az inkvizíció a jelentésed után rászáll erre a dologra. Az élôholtakkal való foglalkozás a saját területükön van, elvégre én csak egy egyszerû vadász vagyok.";
			link.l1 = "Mindenképpen szólok neki. Köszönöm a segítséget, haver. Ritka fajta vagy, nem sokan mernének harcolni magával a halállal! Sok szerencsét!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Maradj ott, ahol vagy! Ez a hely tiltott terület!";
			link.l1 = "Ehh... És mi van odabent?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "Egy veszélyes varázslót találtak ott. Csak a szentatyák és az ôket kísérô katonák léphetnek be.";
			link.l1 = "Értem. Letartóztatták a boszorkánymestert?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "Nem vagyok felhatalmazva, hogy ilyen kérdésekre válaszoljak, senor. Itt az ideje, hogy távozzon.";
			link.l1 = "Rendben, értem. Sok szerencsét!";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "Maradj nyugton, ember! A templom szívében vagy, és túl messzire mentél ahhoz, hogy most visszafordulj.";
			link.l1 = "Ki vagy te?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "Én vagyok a Chavinavi törzsfônöke, e szent hely ôrzôje és gondozója. Nem te vagy az elsô, aki belépett ebbe a templomba, de csak két férfi és egy nô lépett be ide, és távozott élve elôtted. Ez az egyetlen ok, amiért most leereszkedem, hogy beszéljek veled. Miért jöttél ide, sápadtarcú?";
			link.l1 = "Egy ôsi ereklyét hoztam ide, a jáde koponyát. Ötven évvel ezelôtt egy indiai templomból vitték el a szárazföld mélyén. Meg akartam találni a szentélyt, és visszaadni az ereklyét az istenednek.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "Furcsa ilyen szavakat hallani egy magadfajtától. Nem hiszek neked. Ti, sápadtarcúak, mindig azért jöttök, hogy elvegyetek valamit, de soha nem adtok vissza semmit.";
			link.l1 = "Nem hazudok. A koponya visszaszolgáltatásával feloldom a Karib-tengeren rettegésben tartó szellemhajó kapitányára kirótt átkot, ami újra halandóvá teszi ôt, és végleg megszabadítom tôle a világot.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "Honnan tudod, hogy Istenünk feloldja az átkot, sápadtarcú? A mi Istenünk beszél hozzád?";
			link.l1 = "Nem. Egy Tuttuathapak nevû nagy sámán tanácsára jöttem ide. Ahogy ô mondta, a koponya a kulcs az átokhoz, és ez az egyetlen templom a Karib-tengeren. És tudod mit - azt hiszem, ô valóban tud beszélgetni a múlt szellemeivel. Talán még veled is, a jaguár harcosok fônöke.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "A szavaid meglepnek, sápadtarcú, de még mindig nem bízom benned teljesen. Mégis, ha azért jöttél ebbe a templomba, hogy visszaadd az ereklyénket, akkor a sámánunk bizonyára mesélt neked errôl a helyrôl, a teremtésérôl, a történetérôl és a lakóiról\nHa így van, akkor könnyedén válaszolsz minden kérdésemre. Akkor elismerem, hogy ôszinte voltál velem, átengedlek, és ráadásul megjutalmazlak.";
			link.l1 = "Akkor kérdezz!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "Én vagyok a chavinavik és a jaguárharcosok vezére. Ezer évvel ezelôtt ember voltam; most szent kötelességemet teljesítem ezekben a kamrákban. Melyik isten parancsol nekem?";
			link.l1 = "Mictlantecuhtli.";
			link.l1.go = "question1_l";
			link.l2 = "Kukulcan.";
			link.l2.go = "question1_l";
			link.l3 = "Yum Cimil.";
			link.l3.go = "question1_r";
			link.l4 = "Inti.";
			link.l4.go = "question1_l";
			link.l5 = "Kauil.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "Mielôtt a ti sápadtarcú népetek megérkezett, ez az egész föld, az északi nagy havasoktól a déli nagy síkságokig, hozzánk tartozott, egy család testvéreihez...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "Mielôtt a ti sápadtarcú népetek megérkezett, ez az egész föld, az északi nagy havasoktól a déli nagy síkságokig, hozzánk tartozott, egy család testvéreihez...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "Melyik indián törzs építette ezt a templomot?";
			link.l1 = "Inka.";
			link.l1.go = "question2_l";
			link.l2 = "Chavins.";
			link.l2.go = "question2_r";
			link.l3 = "Maya.";
			link.l3.go = "question2_l";
			link.l4 = "Azték.";
			link.l4.go = "question2_l";
			link.l5 = "Arawac.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "Népünk fejlôdött, bölcsességet tanult, és új erdôket, síkságokat és szigeteket hódított meg. Az emberek, akik ezt a templomot építették, a Nagy Víz túloldalán lévô erdôségekbôl érkeztek...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "Népünk fejlôdött, bölcsességet tanult, és új erdôket, síkságokat és szigeteket hódított meg. Az emberek, akik ezt a templomot építették, a Nagy Víz túloldalán lévô erdôségekbôl érkeztek...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "Ki vezette e dicsôséges emberek csapatát?";
			link.l1 = "Nagy törzsfônök.";
			link.l1.go = "question3_l";
			link.l2 = "Nagyszerû pap.";
			link.l2.go = "question3_l";
			link.l3 = "A nagy törzsfônök fia.";
			link.l3.go = "question3_r";
			link.l4 = "A nagy pap fia.";
			link.l4.go = "question3_l";
			link.l5 = "A pártnak nem volt vezetôje.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "Az indiánok, vitéz harcosok és utazók, mindig szerették és tisztelték a szülôföldjüket, még akkor is, ha új helyen telepedtek le. Otthonuk iránti szeretetük jeléül szobrot emeltek a templomban egy madár alakú szoborral, hazájuk jelképével. Mögöttem van...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "Az indiánok, vitéz harcosok és utazók, mindig szerették és tisztelték a szülôföldjüket, még akkor is, ha új helyen telepedtek le. Otthonuk iránti szeretetük jeléül szobrot emeltek a templomban egy madár alakú szoborral, hazájuk jelképével. Mögöttem van...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "Mi a neve ennek a madárnak?";
			link.l1 = "Albatross.";
			link.l1.go = "question4_l";
			link.l2 = "Sas.";
			link.l2.go = "question4_l";
			link.l3 = "Keselyû.";
			link.l3.go = "question4_l";
			link.l4 = "Roc.";
			link.l4.go = "question4_l";
			link.l5 = "Kondor.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "A jólét évei elteltek és elhalványultak, mint a lámpa lángja, és az élet elhagyta a szigetet. Csak a templom maradt itt, hogy az ôsi indiánok nagy hatalmának emlékeként álljon. Az utolsó sámán egy talapzaton hagyott egy szent napgömböt, amely erôt adott a bátraknak és megbüntette a gonoszokat. Az a férfi vitte el, aki elôtted járt itt.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "A jólét évei elteltek és elhalványultak, mint a lámpa lángja, és az élet elhagyta a szigetet. Csak a templom maradt itt, hogy az ôsi indiánok nagy hatalmának emlékeként álljon. Az utolsó sámán egy talapzaton hagyott egy szent napgömböt, amely erôt adott a bátraknak és megbüntette a gonoszokat. Az a férfi vitte el, aki elôtted járt itt.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "Mi volt a neve annak a szent gömbnek?";
			link.l1 = "A ragyogó Nap gömbje.";
			link.l1.go = "question5_l";
			link.l2 = "A napsugarak gömbje.";
			link.l2.go = "question5_l";
			link.l3 = "A déli nap gömbje.";
			link.l3.go = "question5_l";
			link.l4 = "A felkelô nap gömbje.";
			link.l4.go = "question5_r";
			link.l5 = "A lenyugvó nap gömbje.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "A rossz válaszok azt jelzik, hogy hazudtál nekem, fehér ember! Gonosz szándékkal jöttél! Sikerült átosonnod a templom és a szentély ôrzôi felett, rájöttél, hogyan mûködik az ajtó mechanizmusa - de a velem vívott halálos harcot mégsem úszod meg. Készülj a halálra, sápadtarcú!";
				link.l1 = "Nos, ha ragaszkodsz hozzá - lássuk, milyen nagyszerû harcos vagy...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "A népemrôl és a templomomról való tudásod becsületére válik, sápadtarcú. Most már hiszek neked. Menj és teljesítsd be, amiért idejöttél. Helyezd a szent ereklyét a kondor elôtti talapzatra, ahol a felkelô nap gömbje szokott állni\nAztán térj vissza hozzám. A Yum Cimil iránti imádatodat és a döntést, hogy önként visszaadod azt, amit a testvéreid elloptak, meg kell jutalmaznom.";
				link.l1 = "Köszönöm a bizalmadat, nagy törzsfônök.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "A rossz válaszok azt jelzik, hogy hazudtál nekem, fehér ember! Gonosz szándékkal jöttél! Sikerült átosonnod a templom és a szentély ôrzôi felett, rájöttél, hogyan mûködik az ajtó mechanizmusa - de a velem vívott halálos harcot mégsem úszod meg. Készülj a halálra, sápadtarcú!";
			link.l1 = "Nos, ha ragaszkodsz hozzá - lássuk, milyen nagyszerû harcos vagy...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "Megtetted, amit ígértél, sápadtarcú. Örülök, hogy nem voltál hazug, mint a legtöbb testvéred. Én is megtartom a szavamat. Tessék, fogadd el tôlem ezt az ajándékot - a jaguár harcosok jelképét' might. Yum Cimil maga ruházta fel ezt a bundát az ereje egy részével.";
			link.l1 = "Hûha! Ez annyira gyönyörû!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("Jaguárbôrt kaptál");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ez nem egy egyszerû bunda. Ha egyszer viseled, a jaguár harcos erejét nyered el. Tüzet okádó és ólmot lövellô fegyvered ereje megtízszerezôdik, és képes leszel ellenségeid hulláival teleszórni a csatateret\nDe egyetlen halandó sem képes megtartani azt az erôt, amelyet Yum Cimil beletett ebbe a prémbe. Ha egyszer elereszted, csak a következô éjfélig kísér el téged, aztán elhalványul. Vigyázz rá, sápadtarcú, és ne pazarold az erejét egy jelentéktelen csetepatéra.";
			link.l1 = "Köszönöm! Csak akkor fogom használni, amikor teljesen elárasztanak az ellenségek.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "Most menjetek. És figyelmeztesd a testvéreidet, hogy ne avatkozzanak bele e szent kamrák nyugalmába. A jaguár harcosok nem kegyelmeznek a sápadtarcúaknak, és nem kegyelmeznek nekik.";
			link.l1 = "Isten veled, törzsfônök.";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
