// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

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
				dialog.text = "Helló, helló... Új vagy itt? Nem emlékszem az arcodra. Engedje meg, hogy bemutatkozzam - Giuseppe Fazio vagyok, a problémák megoldásának specialistája ezen a kis szigeten.";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". Igazad van, új vagyok itt. Bocsáss meg a kíváncsiságomért - de milyen problémákat oldasz meg?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Á, már megint te, kedves "+pchar.name+"! Mi szél hozott szerény házamba?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "Fazio, komoly konfliktusom van egy klánnal. Meg kell oldanom ezt a problémát.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "Giuseppe, egy Adolf Barbier nevû embert keresek. Úgy hallottam, hogy nemrég együtt ittál vele a kocsmában...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "Giuseppe, azt mondják, hogy ön teljesen ellenáll az italoknak. Akármennyit iszik, még mindig talpon marad.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && PCharDublonsTotal() >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "Készen állok a játékodra. Itt a tétem.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "Tudni akarom a klánok jelenlegi jelszavát, hogy beléphessek a területükre.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád a legújabb pletykákat?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Semmi különös, Giuseppe. Csak látni akartalak.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Mindenféle, kedvesem, mindenféle. Én például elsimítom a dolgokat az admirális és a klánok között. Mint azt már talán tudod, a Rivados, a Narwhals és az admirális kölcsönös ellenségek. Én közvetítôként lépek fel, amikor a dolgok kényessé válnak.\nMellett gyakran játszom a semleges fél szerepét, amikor az admirális ellátmányt ad el a klánoknak. De ez csak egy apró része az üzletemnek. Szóval ha gondjaid vannak a Rivadosokkal vagy a Narwhalokkal - ne habozz, kérd a segítségemet, meglátjuk, mit lehet tenni.";
			link.l1 = "Rendben. Megfontolom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "Milyen klán?";
			link.l1 = "Narvál.";
			link.l1.go = "parol_nrv";
			link.l2 = "Rivados.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "Donald Greenspen-t akarod látni, igazam van?";
			link.l1 = "Igen, így van. Tudja a jelszót?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "Fekete Eddie-t akarja látni, igazam van?";
			link.l1 = "Valami ilyesmi. Tudod a jelszót?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "Persze! De elôbb hadd mondjak néhány részletet. A jelszavak csak egy szót tartalmaznak, és hetente változnak. Minden hónap hetedik, tizennegyedik, huszonegyedik és huszonnyolcadik napján\nSzóval figyeld az aktuális dátumot, hogy elkerüld a hibákat. Végül, ahogyan azt meg kell értened, ez nem jótékonysági akció. Ötven dublont egy jelszóért. Ne feledjétek, csak dublonokat.";
				link.l1 = "Ötven dublont? Ez egy hatalmas összeg!";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "Persze, fiam. Tudod az árat. Van ötven dublonod?";
				if (PCharDublonsTotal() >= 50)
				{
					link.l1 = "Igen. Fogd az érméidet.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "Sajnos, nincs. Talán késôbb...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "Nos- nos, fiam, nyugodj meg. Ne légy mohó, bízz bennem: Tudom az információim valódi árát. Ugye nem fogsz csak úgy sétálgatni a "+pchar.questTemp.LSC.parol+" hajóin? Nem. Szóval készen kell állnod arra, hogy veszíts egy kis pénzt... Szóval, kész vagy ötven dublont fizetni?";
			if (PCharDublonsTotal() >= 50)
			{
				link.l1 = "Igen. Fogd az érméidet.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "Sajnos, nincs ennyi pénzem. Talán késôbb...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveDublonsFromPCharTotal(50);
			dialog.text = "Nagyszerû! Örülök, hogy üzletet kötöttünk. A "+pchar.questTemp.LSC.parol+" jelenlegi jelszava: '"+sTotalTemp+"'. Jól jegyezd meg és ne hibázz, különben egy érmét sem adok az életedért.";
			link.l1 = "Tudom, tudom... Köszönöm!";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "Á, de persze, az én jó öreg Adolfóm! Igen, beszéltem vele. Látja, kedvesem, örültem, hogy visszakaptam a pénzemet, azt a pénzt, amirôl azt hittem, hogy soha többé nem látom! Adolfo nagy összeget vett fel kölcsön a kintlévô puskája fedezetére, és gondjai voltak a pénzem visszaadásával\nMinden reményemet elvesztettem, hogy visszakapjam, és el akartam adni azt a stutzen a mi szeretett Axel Yostunknak. De hirtelen a kedves Adolfo elhozta nekem az aranyamat! Kiderült, hogy sikerült annyi érmét szereznie, hogy nem csak a stutzenjét váltotta vissza, hanem egy Sessile Gallard faházat is tudott venni a 'Santa Florentina'!\nS persze, ez sokkal jobb, mint egy félig vizes raktárban élni\nEzért Adolfo visszakapta a puskáját, egy új otthont, én pedig a pénzemet. Miért is utasíthattam volna vissza, hogy megigyak vele egy italt, fôleg, hogy ô fizetett?";
			link.l1 = "Ó, persze! Volt mire innia. És ingyen... Köszönöm, Giuseppe, sokat segítettél nekem. Most már tudom, hol találom Adolfot.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Mindig örömömre szolgál, kedvesem. De ne keressétek Adolfot a kabinjában estig, nagyon elfoglalt, valami üzlet miatt rohangál... Igen, és látogass meg gyakrabban, beszélgessünk!";
			link.l1 = "Majd meghívlak, ha lesz saját kabinom... Viszlát és sok szerencsét!";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "Jó utat, és sok sikert! Miért törsz be hozzám, mintha tûz lenne? Mit gondolsz, ki vagy te?";
					link.l1 = "A te igazságod... mérgezô!";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "Kímélj meg! Esküszöm, kényszerítettek! Fegyvert szegeztek a...";
					link.l1 = "Kussolj már! Tudom. Hol van az utolsó szemétláda? Hol van Marcello Cyclops?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "Esküszöm, kényszerítettek! Már mindent elmondtam az admirálisnak! Nem tudtam ellenállni nekik, ôk...";
					link.l1 = "Kussolj már! Tudom. Hol van az utolsó szemétláda? Hol van Marcello Cyclops?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "Mit... mit mondtál?";
			link.l1 = "Mindent tudok, te szemétláda. Chad Kapperrel dolgoztál együtt. Egy hordó mérgezett rumot vittél az admirálisnak. Most pedig imádkozz, te szerencsétlen buzi...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Várj! Állj! Kímélj meg! Esküszöm, kényszerítettek! Fegyvert fogtak a...";
			link.l1 = "Kussolj már! Tudom. Hol van az utolsó szemétláda? Hol van Marcello Cyclops?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "I... I.... Nem tudom! Nem tudom!";
			link.l1 = "Hazudsz, te szemétláda! Azt látom. Hol van Küklopsz?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Ô... kapott valami parancsot Kapper-tôl és elment. Nem tudom, hol van!";
			link.l1 = "Megint hazudik. Te mindent tudsz. Ne légy gyáva, te mocskos teremtés - Kapper halott, és nem fog bántani téged. De ha nem mondod meg, hol van Marcello - most azonnal leváglak, mint egy disznót! Mit parancsolt Chad a Küklopsznak?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Elküldte, hogy ölje meg... Red Mary-t.";
			link.l1 = "Micsoda?! Beszélj már, hogy fogja ezt megtenni? Lehetetlen bejutni a kabinjába! Hogy akarja megölni?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "Bejut Jurgen kunyhójába, amíg a kovács nincs bent. Ezután a raktér aljához megy, átkel rajta, és eléri Mary kunyhóját\nAztán már csak arra lesz szüksége, hogy megvárja, amíg a lány hátat fordít neki, vagy elalszik. Ezt mondta nekem Chad. Ennél többet nem tudok, esküszöm!";
			link.l1 = "Ez elég lesz. Mikor ment el? Mikor, kérdezem én, mikor ment el Küklopsz a 'Ceres kovácsmûhelybe'?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "Biztosan már Jurgen kabinjában van... vagy a raktérben...";
			link.l1 = "Bassza meg! Nincs idôm körbeúszni a szigetet! Mondd meg a Narwhals hajóinak jelszavát! Beszélj, és ha hazudsz nekem, én úgyis életben maradok, de te biztosan meghalsz!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"'...";
			link.l1 = "Megvan. Most imádkozz, hogy a lány túlélje.";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "Már mindent elmondtam neked, amit tudtam! Esküszöm!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "Ô... Valahol a 'Fleron'. belsejében van, Chad utasította, hogy ott rejtôzzön el, és várja meg a következô parancsot.";
			link.l1 = "Értem, értem. Remélem, igazat mond...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "Valóban? Nos, fiam, melyik klán aggaszt téged?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "Narvál.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "Rivados.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "Az admirális kalózai.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "Nincs ilyen. Csak vicceltem, Giuseppe, jól vagyok.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "Nos, ez valójában nem konfliktus, csak egy kis félreértés, he-he. "+sti(npchar.quest.price)+"  dublont, és a problémád egy nap alatt megoldódik.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "Persze, hallottam róla. Nagy zûrzavart csináltál, kedvesem. De van kiút. "+sti(npchar.quest.price)+" dublonok és a problémád egy nap alatt megoldódik.";
				else dialog.text = "Az egész Sziget tisztában van azzal, hogy milyen mészárlást követtek el. Nem lesz könnyû segíteni nektek, de van rá esély. "+sti(npchar.quest.price)+" dublont és megpróbálom megoldani a problémádat.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Tessék, fogd az érméket és intézd el.";
				link.l1.go = "pay";
			}
			link.l2 = "Sajnos most nincs nálam elég dubloon. De majd késôbb hozom ôket, és akkor majd újra beszélünk.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "Nos, ez valójában nem konfliktus, csak egy kis félreértés, he-he. "+sti(npchar.quest.price)+"  dublont, és a problémád egy nap alatt megoldódik.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "Persze, hallottam róla. Nagy zûrzavart csináltál, kedvesem. De van kiút. "+sti(npchar.quest.price)+"  dublonok és a problémád egy nap alatt megoldódik.";
				else dialog.text = "Az egész Sziget tisztában van azzal, hogy milyen mészárlást követtek el. Nem lesz könnyû segíteni nektek, de van rá esély. "+sti(npchar.quest.price)+" dublont és megpróbálom megoldani a problémádat.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Tessék, fogd az érméket és intézd el.";
				link.l1.go = "pay";
			}
			link.l2 = "Sajnos most nincs nálam elég dublón. De majd késôbb hozok, és akkor majd újra beszélünk.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "Nos, ez valójában nem konfliktus, csak egy kis félreértés, he-he. "+sti(npchar.quest.price)+" dublont, és a problémád egy nap alatt megoldódik.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "Persze, hallottam róla. Nagy zûrzavart csináltál, kedvesem. De van kiút. "+sti(npchar.quest.price)+" dublonok és a problémád egy nap alatt megoldódik.";
				else dialog.text = "Az egész Sziget tisztában van azzal, hogy milyen mészárlást követtek el. Nem lesz könnyû segíteni nektek, de van rá esély. "+sti(npchar.quest.price)+" dublont és megpróbálom megoldani a problémádat.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Tessék, fogd az érméket és intézd el.";
				link.l1.go = "pay";
			}
			link.l2 = "Sajnos most nincs nálam elég dublón. De majd késôbb hozok, és akkor majd újra beszélünk.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveDublonsFromPCharTotal(sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("Adtál "+sti(npchar.quest.price)+" dublont.");
			dialog.text = "Nagyszerû. Most pedig ülj le és pihenj egy kicsit. Jobb, ha a kabinomban maradsz, amíg megoldom a problémádat. Nem akarom, hogy még rosszabb legyen, kedvesem.";
			link.l1 = "Rendben...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("Egy nappal késôbb..."+ NewStr() +"Fazio foglalkozott a konfliktussal...", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "Gyere, fiam! Hazudnak, mind hazudnak, he-he-he. Az én fejem csak egy kicsit keményebb, mint egy átlagos fej, de ugyanolyan ember vagyok, mint te, ezért én is berúgok a rumtól. Az emberek azért isznak rumot, hogy berúgjanak, ez az egyetlen célja. Gondoltál már erre, kedvesem?";
			link.l1 = "Nagyon is igaz.";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "Akarsz velem valami vicces játékot játszani? Úgy hívják 'iszom a mocsokig!', ha-ha! Biztos vagyok benne, hogy már hallottál róla. Igazam van?";
			link.l1 = "Igen, volt néhány suttogás errôl... Én ezt nevezném 'arcot az asztalra'.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "Ha-ha-ha, kedves fiam, megnevettetted az öreget, mi mást is mondhatnék! 'arc az asztalon!' Emlékezni fogok rá... Na, mit szólsz hozzá? Játsszunk száz dublonnal?";
			link.l1 = "Száz dublont?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "Igen, és a vesztes fizeti az italokat. Megegyeztünk?";
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "Igen, áll az alku. Itt a tétem.";
				link.l1.go = "drink_4";
			}
			link.l2 = "Hm. Nincs annyi dublonom.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "Nos, jöjjön el hozzám, ha lesz, és játszunk!";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveDublonsFromPCharTotal(100);
			Log_Info("Adtál 100 dublont.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Kitûnô, kedvesem! Akkor találkozzunk este kilenckor Sancho kocsmájában! Igen, a téted nálam marad, ha késel, ez az egyik szabály. De nem fogsz elkésni, fiam, ugye?";
			link.l1 = "Persze, Giuseppe. Készüljetek az üvegcsatára!";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "És te, és te, kedvesem! Arccal az asztalra! Ha-ha!";
			link.l1 = "Kilenckor találkozunk a kocsmában!";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "Nos, kedvesem, kész vagy megcsókolni egy asztalt, he-he-he? A jó Sancho már hozott nekünk rumot. Gondolom, nem kell elmondanom a szabályokat. Elég egyszerûek: addig isszuk ugyanazt az üveget, amíg egyikünk le nem fogy.\nIgen, beszélgethetünk, beszélgetnünk kell! Rendes emberekkel beszélgetni jó dolog, nem? És ha nyersz, akkor Sanchótól megkaphatod a nyereményedet. Készen állsz?";
			link.l1 = "Én azt mondanám, hogy igen. Kezdjük, Giuseppe!";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "Öt-tizenkilenc me-eeen a halottakra... hic! Aha! Yo-ho-ho-kha... És... üveg...";
			link.l1 = "Dicsôséges...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
