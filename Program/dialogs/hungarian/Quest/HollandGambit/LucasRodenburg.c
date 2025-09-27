// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "Beszélj, fiú, de gyorsan. Elfoglalt ember vagyok.";
				link.l1 = "Hallottam, hogy kapitányokat vesznek fel.";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "Van valami üzleted számomra?";
			link.l1 = "Nem, sajnálom. Elmegyek.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "Már félúton kellett volna lenned Sint Maarten felé, kapitein.";
				link.l1 = "Készülök a kihajózásra, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "Á, kapitein, hát itt vagy! Nem láttam, hogy jössz, épp most fejeztem be Ridderbrock levelének olvasását. Nagy benyomást tettél rám. A kereskedôk 'ôrzôjének és a kalózok ostorának nevez téged. Isten ajándéka a Társaságnak!' Mit szólsz ehhez?";
				link.l1 = "Inkább maradnék egy egyszerû kapitány. Egy átlagos, de gazdag kapitány.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "Miért vagy még mindig itt, és nem Kubába tartasz?!";
				link.l1 = "Igen, igen, úton vagyok, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "Ah, kapitein! Bevallom, kezdtem aggódni. Milyen volt?";
				link.l1 = "Nem volt zökkenômentes, de errôl majd késôbb mesélek. Elôbb az üzlet. Senor " + GetFullName(sld) + " azt mondta, hogy mondjam el neked a következôket: 'ez az embernek meg kell halnia'. Akkor Geraldi elintézettnek tekinti az esetet. Azt is mondta, hogy ez a döntés a családjuk akarata.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "Örülök, hogy látlak, kapitány! Jó, hogy eljöttél hozzám.";
				link.l1 = "Jó napot, mynheer. Gondolom, van egy másik céges munkája számomra.";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "Mondtam, hogy kössék ki a hajójukat. Túl hülye vagy ahhoz, hogy közvetlen parancsot kövess?";
					link.l1 = "Egyik sem, mynheer. Már úton vagyok.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Szóval, kikötötted a hajódat. Most pedig kölcsönadom a xebecemet. Készen állsz arra, hogy azonnal elkezdjük a küldetést? A hajóm jól felszerelt és hajózásra kész, így nincs miért aggódnod.";
					link.l1 = "Igen, persze. Készen állok, Mynheer Rodenburg.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "Miért vagy még mindig itt? Azonnal menj Longwayhez.";
				link.l1 = "Sajnálom, már úton vagyok.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "Kapitein... Már tudok az utazásodról.";
					link.l1 = "Ó, tényleg? Szóval tudnod kell, hogy...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "Kapitein... Már tudok az utazásodról.";
					link.l1 = "Tényleg? Szóval tudnod kell, hogy...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "Kapitein... Már tudok az utazásodról.";
					link.l1 = "Tényleg? Szóval tudnod kell, hogy...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "Tessék, kapitány... Már mindent tudok az utazásodról.";
					link.l1 = "Tényleg? Szóval tudnod kell, hogy...";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Menj Antiguába. Menjetek Antigua-ba.";
				link.l1 = "Sajnálom, már úton vagyok.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "Értesítettek az érkezésedrôl, Kapitein. Azt is tudom, hogy elvesztetted a Mirage-omat a csatában.";
					link.l1 = "Jól informált vagy, Mynheer Rodenburg. Minden erôfeszítésem ellenére nem tudtuk megmenteni.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "Értesültem az érkezésedrôl, kapitein. Látom, hogy a Mirage biztonságban dokkolt. Ez jó.";
					link.l1 = "Az ön utasításai szerint történt, mynheer. Te parancsoltad, hogy öljem meg Fleetwoodot, és ô halott. Te parancsoltad, hogy hozzam vissza a Mirage-t a helyi kikötôbe, és most itt van.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "Á, hát itt vagy. Örülök, hogy látlak. Van egy másik küldetésem számodra, ahogy ígértem.";
				link.l1 = "Hallgatlak, mynheer.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Örülök, hogy látlak, fiam. Késôn jöttél, és már kezdtem aggódni. Sikerült valamit megtudnod Abigailtôl?";
				link.l1 = "Nem csak ezt, hanem a többi problémádat is megoldottam. Megtaláltam a szigetet és Shneur elveszett vagyonát. Salamon boldog, Abigail pedig igent fog mondani az ajánlatodra. Gratulálok, mynheer!";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Örülök, hogy látlak, barátom. Sikerült valamit megtudnod Abigailtôl?";
				link.l1 = "Igen. Beszéltem Abigail-lel és az apjával. Van egy probléma, mynheer: az apja elveszett vagyona. Abigail méltatlannak érzi magát hozzád, fél az emberek pletykáitól és suttogásától, ha ô hozomány nélküli lányként hozzámegy egy olyan úriemberhez, mint te. Remélem, hogy megérted.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, barátom! Remélem, jó híreket hoztál?";
				link.l1 = "A terved sikeres volt. Abigail igent fog mondani. Gratulálok, mynheer.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "Már vártalak. Fiam, nagy veszélyben vagy.";
				link.l1 = "Hogy érti ezt?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "Az ügynökeim a dokknál szóltak, hogy megérkeztél. Johan van Merden halott?";
				link.l1 = "Igen. Ô és a bûntársa eltûntek. Kemény küzdelem volt, de végigcsináltam.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Nincs több megbeszélnivalónk, kapitány.";
			link.l1 = "Értettem, én megyek.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Mi a baj? Az idô pénz.";
		link.l1 = "Sajnálom, elmegyek.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Talán. Ki maga? Beszéljen gyorsan, az idô pénz.";
			link.l1 = "Én vagyok a kapitány " + pchar.name + ", a hajóm és hasznos lehet az Ön számára.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "Hm, egy ismeretlen ötvözet, amit a tégelyben kell megvizsgálni.";
			link.l1 = "Ezért vagyok itt, mynheer.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Nagyon jó, majd meglátjuk, milyen színû a bátorságod. Rendben Kapetein, akárhogy is hívnak, ismered Balthazar Ridderbrockot? Nem? Milyen szerencsés. Az ilyen kapzsi, mogorva, indulatos idióták, mint ô, ritka látványosságnak számítanak.\nDe úgy tûnik, hogy ilyen kiváló tulajdonságok nem voltak elégségesek a férfinak, így volt annyi esze, hogy a helyi kocsmában megsértett egy " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " nevû filibustert, és rögtön az ôrséget hívta rá, amint a sértett fél kardhoz nyúlt...";
			link.l1 = "...és az elsô szabad kötéllel felakasztották a kalózt?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "Ez nem ilyen egyszerû. " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " nem egy közönséges kalóz, hanem egy holland magánhajós, a britek elleni utolsó két háború veteránja. A helyi adófizetôk nagyon szeretik ôt. Ridderbrockról ugyanezt nem mondhatom el.";
			link.l1 = "Szóval a mi kalózunk még mindig él?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "Igen ám, de nagyon dühös. Ezért van Ridderbrock szarrá rémülve.";
			link.l1 = "Gondolom, a szerencsémnek hamarosan vége. Mikor találkozom Mynheer Ridderbrockkal?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "Azonnal. Philipsburg jó népe cukorszállítmányra vár, amelyet közös ismerôsünk, Ridderbrock ígért, hogy leszállít. Nem hiszem, hogy az az ember megérné a csizmája bôrét, de sajnos nekünk dolgozik, úgyhogy irány a kikötôi iroda. Keressétek meg ott Ridderbrockot, és mondjátok meg neki, hogy utasítottam, hogy azonnal induljon útnak.\nEl kell követnetek ôt, és... egy darabban elkísérni Philipsburgba. Nem akarom " + GetName( NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " , hogy a Társaság hírnevét a rakományával együtt a Karib-tenger fenekére küldje.";
			link.l1 = "Ugh, egy kísérô küldetés. Mi van a fizetséggel ezért a... kellemetlen megbízatásért?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "Kapitein, elôbb végezd el a munkát. Balthazar fizetni fog neked, amint elérte a célját. Philipsburgban! Nem Davy Jones' Locker! Utána jelezz vissza nekem, ha a munkát elvégezted. Ha sikerrel jársz, számíthatsz a további pártfogásomra és a Társaságéra. Leléphet.";
			link.l1 = "Viszlát, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "Igen, Ridderbrock még holland létére is egy fukar kurva. De mindegy is, ô már nem tartozik rám. Beszéljünk inkább rólad, Kapitein, akármi is a neved. Tetszik a stílusod, ezért felajánlok neked egy másik munkát. Ezúttal én magam fogom kifizetni.";
			link.l1 = "Hallgatlak, mynheer.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Á, szóval te vagy az a bátor kapitein, aki elkísérte azt a gazember Ridderbrockot? Mindent hallottunk róla... Csak ötezer pezót fizetett neked! Megállás nélkül dicsekedett vele a Philipsburgi kocsmában, részegen, mint egy disznó. Én a maga helyében, kapitány, kirángatnám az utcára és megveretném.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "Szükségem van egy emberre egy nagyon fontos ügyben. A Ridderbrock-ügyben jól teljesített, így a Társaság úgy gondolja, hogy önre bízhatom az ügyet.";
			link.l1 = "Azt hiszem, ez megtisztelô. Mi a baj?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "Nem tudom megadni a pontos részleteket, de tudnia kell, hogy ez nem az én munkám, ez a cég, így van egy esélye, hogy a kegyeibe, Amely biztosíthatom, hogy nagyon jövedelmezô.\nSail to Santiago Kubában, és szállítsa ezt a csomagot Don " + GetFullName(sld) + ". Ô magas pozíciót tölt be Geraldi bankjában, és ô az én... az üzleti partnerem is. Át kell adnod neki ezt az aranyat, amit most azonnal átadok neked. Bízom az ôszinteségedben, kapitein. Nos, ha nem is az ôszinteségedben, de a túlélési ösztönödben igen. A Társaság mindig megtalálja azokat, akik megpróbálnak lopni tôlünk.";
			link.l1 = "Kételkedsz bennem, mynheer?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " Azért is adom neked ezt a rövid távú kereskedelmi engedélyt, hogy megkíméljelek a spanyolokkal való diplomáciai bonyodalmaktól. Ez lehetôvé teszi, hogy egy ideig a spanyol kolóniákon dokkolhassanak.";
			else sTemp = "";
			dialog.text = "Jelenleg nem kételkedem benned. Hidd el, ha mégis, akkor sem beszélnék veled errôl az ügyrôl. Tudja, hogy sok idôt pazaroltunk arra, hogy ezt a munkát felsorakoztassuk, így már csak tizenöt napja van arra, hogy teljesítse."+sTemp+"\nAz üzenetemet és a csomagomat idôben kell kézbesíteni. Ez létfontosságú, fiam. Siess, de légy óvatos, ez nem lesz egy tejfeles futás.";
			link.l1 = "Van még valami? Miért figyelmeztet engem, mynheer Rodenburg?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "Mondjuk úgy, hogy gyanakszom. Ne aggódj, ha olyan gyorsan végzed, mint a legutóbbi munkát, akkor lesz esélyed arra, hogy értékes ügynökké válj a Társaság kényes ügyeiben.";
			link.l1 = "Csak annyit kell tennem, hogy tizenöt napon belül eljuttatom ezt a levelet és a pénzt a Santiagóban lévô bankárhoz? Felületesen nem hangzik túl nehéznek.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "Ne olyan gyorsan fiú... Gondolom, nem igazán érted a helyzet súlyosságát. Ha elvégzed ezt a munkát, nagyon hálás leszek neked. Másrészt, ha nem sikerül, akkor nagyon dühös leszek. Ebben az esetben le foglak hugyozni. Megértjük egymást, kapitein " + GetFullName(pchar) + "?";
			link.l1 = "Értettem. A szavamat adom. Mindent megteszek, hogy jó hangulatban tartsalak.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "Rendben. Most pedig fogd a levelet, ezeket a ládákat és ne feledd a feltételeket. És még valami: ne keveredj bajba Santiagóban.";
			link.l1 = "Rendben.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "'Meg kell halnia'.... csak úgy. Erre nem számítottam. Hm. Jól végezted a munkádat, kapitein. Most pedig adj egy jelentést.";
			link.l1 = "Semmi különös... ez csak egy tejes futás volt.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "Elkábított és elrabolt egy férfi Santiagóban. Nagyon érdekelte a Geraldival folytatott üzleted. Sikerült megszöknöm, de elôbb meg kellett ölnöm. Az egyetlen nyom, amit elejtett, egy Gaston nevû férfi neve volt, akirôl nem tudom, mirôl lehetett szó.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "Egy férfi Santiagóban elkábított és elrabolt. Nagyon érdekelte a Geraldival folytatott üzleted. Sikerült megszöknöm, de elôbb meg kellett ölnöm. Nem tudtam meg belôle semmit, mielôtt a pokolba küldtem volna.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "A Társaság hálája nem csupán szavakra korlátozódik. Vedd el a jutalmad, megérdemelted.";
			link.l1 = "A Cégnek dolgozni elég jövedelmezô.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "Mi? Emberrablás... Várjunk csak... Gaston! Megértem... Azt hiszem. Sajnos, fiam, belerángattak egy mocskos ügybe. Ismeretlen vizeken járunk, úgyhogy meg kell néznünk, hogyan alakul a dolog. Örülök, hogy életben maradtál.\nBeszéljünk kellemesebb dolgokról - fogadd el ezt a jutalmat, megérdemelted.";
			link.l1 = "A Cégnek dolgozni elég jövedelmezô.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "Badarság! Elrabolni téged... Bár van egy kis gyanúm. Többet fogsz megtudni, ha továbbra is nekem dolgozol. Szerencsés vagy, és örülök, hogy sikerült.\nBeszéljünk kellemesebb dolgokról - fogadd el ezt a jutalmat, megérdemled.";
			link.l1 = "A Cégnek dolgozni elég jövedelmezô.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "Pontosan, fiam! Jól fizetett ügynökévé válhatsz a Társaságnak, ha továbbra is együtt dolgozunk. Most menj, pihend ki az utadat. Megfeleltél az elvárásaimnak. Igazán hálás lennék, ha egy hét múlva visszajönnél, még sok dolgunk van.";
			link.l1 = "Számíthatsz rám, Mynheer Rodenburg.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("A bátyám a Cégnél azt mondja, hogy Mynheer Rodenburg nagyon elégedett a teljesítményeddel, kapitein. Ne veszítsd el a lehetôséget, Lucas ritkán mutat ilyen kegyet.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "Okos vagy, kapitány. Pontosan. Nos, beszéljünk a közelgô küldetés részleteirôl...";
			link.l1 = "Csupa fül vagyok.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "Nagyon komoly és fontos küldetésem van számodra, és elvárom, hogy mindent az utasításaim szerint tegyél. Mint tudja, az Egyesült Tartományok és Anglia között a viszony... nem szívélyes. Az angolok biztosak abban, hogy nekik kell uralniuk a világot. A probléma az, hogy nem mindenki ért egyet ezzel az állítással. Bárhová hajóznak, hogy üzletet kössenek, biztosak lehetnek benne, hogy a Holland Nyugat-indiai Társaság ért oda elôször.\nMi hollandok rendelkezünk a világ legnagyobb kereskedelmi flottájával, és katonai századaink képesek megvédeni a Köztársaság érdekeit itthon és külföldön egyaránt. Az angolok irigyelnek minket a kereskedelmi hatalmunkért, és mindent megtesznek, hogy szabotálják a Társaság tevékenységét. Nos, van egy bizonyos Richard Fleetwood nevû angol haditengerészeti kapitány. Annak ellenére, hogy a Nemzetközösség megbízott tisztje, jelenleg kalózként tevékenykedik. Megtámad és kifoszt minden olyan hajót, amely a holland zászló alatt merészkedik a Karib-tengeren. Tetteit azzal magyarázza, hogy ellenlépéseket tesz az 'szellemhajó' az angol kereskedôk elsüllyesztésére. Azt állítja, hogy ez 'szellemhajó' egy magánhajó, amely holland hajólevéllel hajózik.\nHallottál már a 'szellemhajó', kapiteinrôl?";
			link.l1 = "Ilyen ostobaságokat bármelyik kocsmában hallhatsz. Csak vegyél egy kis rumot egy öreg hajóskapitánynak, és máris hallhatsz bármilyen történetet...";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "Ez az ügy nem a részegek fantáziája. Utánajártam ennek a 'szellemhajónak'. tetteinek, és kiderítettem, hogy egy fából és vászonból készült hajó, amelynek legénysége egyszerû emberekbôl áll, egy ketch, a neve 'Mirage'. Egy Jacob van Berg nevû férfi parancsnoksága alatt áll, aki a legendás 'repülô hollandnak adja ki'..";
			link.l1 = "Van Berg? Ez egy holland vezetéknév. Egy igazi repülô holland, mi?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "Helyes. Jacob van Berg holland, eredetileg Leidenbôl származik. De a köztársaság már régen akasztófára ítélte. Ô egy szökésben lévô bûnözô, egy kalóz, aki csak a saját érdekei szerint cselekszik. Richard Fleetwood vadászik van Bergre. Ezt a tényt fogjuk felhasználni a szemtelen angol ellen.\nNem szeretném Fleetwoodot egyenesen megölni, bár már régen megérdemelte volna. A halál nem lenne elég neki. Nemcsak megölni akarom, hanem a nevét és a becsületét is tönkretenni. Ez az, amit én akarok. Ez a többi arrogáns angol disznónak is feladja a leckét.\nBeszéljünk a részletekrôl.";
			link.l1 = "Mynheer, ez kezd úgy hangzani, mintha valami személyes dolog lenne...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "Ez nem tartozik rád. Követni fogod a parancsokat, aztán megkapod a fizetésed. Az ügynökömnek köszönhetôen megtudtam, hogy Jacob van Berg hol ólálkodik a 'Mirage', . Egy dél-spanyolországi városból tevékenykedik. Menjetek el hozzá, és derítsétek ki, hol horgonyzott le a szellemhajójával\nAztán öljétek meg, találjátok meg a 'Mirage', zsákmányát, és szállítsátok vissza ide. El kell fognod a 'Mirage', ne is gondolj arra, hogy elsüllyesztheted.";
			link.l1 = "Elég egyszerûen hangzik. Hol keressem van Berget?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "Az ügynököm minden részletet közölni fog önnel. A neve Longway, egy kínai. A személyes hajómat, a xebec 'Meifeng' t bocsátom rendelkezésükre ehhez a küldetéshez. Longway a kapitánya, de ô fogadja el a parancsokat tôled.\nMenj a helyi kikötôi hivatalba, és köss ki ott minden hajódat. Ha ez megtörtént, térjetek vissza hozzám.";
			link.l1 = "Rendben, meglátogatom a kikötômestert. Nem akarom, hogy túl sokáig várjatok.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "Longway odakint vár rád. Megmutatja neked az új hajódat, és ad néhány információt van Berg hollétérôl. Sok szerencsét, kapitein, és ne hagyj cserben. Ne feledd, hogy vissza kell hoznod a 'Meifeng' hozzám, úgyhogy próbáld meg nem elsüllyeszteni, miközben a 'Mirage'.veszed.";
			link.l1 = "Máris megyek!";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "Te inkompetens bolond. Elbuktad a küldetésedet, hogy elfogd a kalózhajót. Minden tervemet tönkretetted. Elveszem 'Meifeng' tôled. Takarodj, nincs rád többé szükségünk.";
			link.l1 = "Sajnálom. Sajnálom. Isten veled, Mynheer Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "Te ostoba idióta. Elvesztetted a 'Meifeng'. Ez elfogadhatatlan... Elveszem a 'Mirage' tôled, és visszatartom a fizetésedet, mint kárpótlást a veszteségemért. Takarodjon, nincs többé szükségünk magára.";
			link.l1 = "Sajnálom. Sajnálom. Isten veled, Mynheer Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "Istenem, te tényleg egy ritka példány vagy. Egy inkompetens bunkó ÉS egy idióta. Nem sikerült elkapnod a Mirage-t, és elvesztetted vele együtt a Meifeng-et is. Takarodj a picsába az irodámból!";
			link.l1 = "Elmegyek.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "Szép munka. Sikerének híre már eljutott a fülembe. Van Berg halott, és te elfogtad a hajóját. A fizetséged 50.000 pezó, vedd el.\nvisszaszerzem a 'Meifeng' tôled. Most itt az ideje, hogy átvegye a 'Mirage', parancsnokságát, fontos szerepet fog játszani a következô szakaszban. Készen állsz?";
			link.l1 = "Igen, Mynheer Rodenburg.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("Azt mondják, hogy különleges megbízást kaptál magától Mynheer Rodenburgtól. Valami olyasmi, hogy az angolokat a tenger fenekére küldi. Úgy tûnik, hogy te egy felemelkedôben lévô ember vagy, kapitány.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("Azt mondják, hogy cserbenhagytad magát Mynheer Rodenburgot. Sok szerencsét, szükséged lesz rá.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Most a Fleetwooddal foglalkozunk. A 'szellemhajóMirage segítségével fogod elôcsalogatni, amire olyan lelkesen vadászik. Állíts csapdát Dominica közelében, a Mirage csaliként fog szolgálni.\nElôször is tudasd Fleetwooddal, hogy a Mirage-t nem messze Dominicától látták. Bátor angolunk mindent félbehagy, amit csinál, és azonnal Dominicára siet, hogy megkeresse a zsákmányt. Ne beszélj közvetlenül Fleetwooddal, különben nem éled túl a találkozást. Keresse meg a gyógyszertárat St. John' s-ban. A patikus John Murdock régi barátom.\nmondd meg neki, hogy a parancsomra cselekszel, és ô segít neked helyi fülest találni, amit szaftos hazugságokkal tömhetsz tele a 'szellemhajó' támadó angol kereskedôkrôl Dominika környékén.";
			link.l1 = "Ezt megtehetem. A cél az, hogy csapdába csaljuk Fleetwoodot Dominicánál, igazam van?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "Pontosan. Longway és 'Meifeng' várni fog rád Dominika közelében. Ti ketten könnyedén el tudjátok vinni az angol kutyát. Szálljatok fel a hajójára, és kutassátok át a kabinját. A hajónaplóját akarom. Felárat fizetek érte.\nDe a fô prioritásotok az, hogy megöljétek azt a szemét Fleetwoodot, úgyhogy ha a fedélzetre szállása nem kivitelezhetô - küldjétek a fenébe. Mindenekelôtt meg kell ôriznie 'Mirage' mindenáron. Kritikus szerepe van a terv következô szakaszában.";
			link.l1 = "Megértettem.";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "Egy jó tanács, kapitein. Ne horgonyozzatok le Szent Jánosnál. Szállj ki a sziget egyik öblében, és gyalogolj a városba a dzsungelen keresztül, különben John nem fog veled beszélgetni. Ha túlságosan felhívod magadra a figyelmet, úgy fog tenni, mintha nem is ismerné. A tengeren is légy óvatos - a 'Mirage' hírhedt az angol gyarmatok között, ezért kerüld el a hadihajóikat és a településeiket, ha nem akarod, hogy egy falka tengeri farkas támadjon rád. Ez minden. Isten legyen veletek.";
			link.l1 = "Igenis, uram.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "Visszatértél, kapitein... Megvan Richard Fleetwood naplója?";
				link.l1 = "Sajnos nincs. Nem volt alkalmam felszállni a hajójára, mielôtt elsüllyesztette volna.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "Visszatértél, kapitein... Megvan Richard Fleetwood naplója?";
				link.l1 = "Sajnos nem. Sikerült felszállnom a Valkûrre, és közelharcban megöltem a férfit, de a naplóját nem találtam meg. Az egyik embere elsütötte a tárat, és csak másodperceink maradtak, hogy megmeneküljünk az életünkkel.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "Visszatértél, kapitein... Megvan Richard Fleetwood naplója?";
			link.l1 = "Én meg is tettem. Itt is van. Sikerült felszállnom a Valkûrre, bár majdnem sikerült. A szemétláda elsütötte a tárat a hajóján, és az égbe repítette. Épphogy megúsztuk az életünkkel.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "Ez nagy kár, mert sok kérdésre választ adott volna. Most már mindegy. Megölted azt a szemtelen angol kutyát, és ez az, ami a legfontosabb. Itt a jutalmad - 100,000 pezó. Elveszem a 'Mirage' tól, visszavisszük ezt a hajót Angliába.";
			link.l1 = "Mi az ördög?! Ez egy remek hajó, meg akartam tartani!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "Kiváló! Ön egy nagyon ügyes ember. Ha minden kapitányunk olyan lenne, mint ön, a Holland Köztársaság elsô lenne a történelem legnagyobb tengeri nemzetei között. Itt a jutalma - 100.000 pezó és 50.000 pezó plusz a hajónaplóért. Elveszem a 'Mirage' öntôl, ezt a hajót visszavisszük Angliába.";
			link.l1 = "Mi az ördög?! Ez egy remek hajó, meg akartam tartani!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "Fiam, te kiváló katona vagy, de bízz bennem és a politikai kérdésekben szerzett tapasztalataimban. Emlékszel, mit mondtam Fleetwoodról? A nevét és a hírnevét egy malomkôhöz fogom szögezni, és a mélybe dobom. És ezeknek a Port Royal-i arrogáns nemeseknek nyelniük és fulladozniuk kell majd.\nMegcsináljuk Richard Fleetwoodot a 'szellemhajó' Mirage kapitányává, egy vérfarkassá, aki egymás ellen játssza ki a két nemzetet, Angliát és Hollandiát, fosztogat, fosztogat és gyilkol mindkettô békés polgárait, csak hogy meggazdagodjon! Micsoda paródia! Már elôkészítettem a bizonyítékokat és a tanúkat, de a 'Mirage' tökéletes színdarabom fô eseménye lesz.";
			link.l1 = "Akkor baszódjak meg! Feláldozod a kiváló hajómat a tervedért?!?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "Vigyázz a nyelvedre, fiú, ez háború. Néha nemcsak embereket, hanem hajókat és gazdag településeket is fel kell áldoznunk politikai céljaink elérése érdekében. Minden háború veszteségekkel jár... Ha már a veszteségeknél tartunk, rossz híreim vannak számodra.\nMíg távol voltál, Willemstadot megtámadták az angol kalózok. Az erôdnek sikerült elkergetnie ôket, de nem azelôtt, hogy tûzhajókkal bejutottak volna a kikötôbe.\nA hajótokat horgonyon ragadták, és a vízvonalig leégtek. Teljesen elpusztult.";
			link.l1 = "Mynheer, most csak viccelsz velem, baszd meg! A pokolba az egésszel! Most mit fogok csinálni?!";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "Ne bosszankodj annyira kapitein, nekem is van jó hírem. Hogy enyhítsem a felháborodásodat, neked adom az én Szép Szelemet, a xebec 'Meifeng'. A hajót szabadon használhatod, ahogy akarod, az ésszerûség határain belül. Ezenkívül holnap találkozzunk a kormányzó rezidenciáján, a Holland Köztársaság és a Nyugat-indiai Társaság hálájával állami kitüntetésre jelöltek. Ne hagyd el a várost, amíg meg nem kapod, kapitein.";
			link.l1 = "Ez egy kicsit enyhíti a veszteségemet. Megtiszteltetés számomra. Egyébként, mynheer, hová tûnt Longway?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "Longway hirtelen eltûnt, miután megparancsoltam neki, hogy hajózzon el Dominikára. Az a gyanúm, hogy angol ügynökök támadtak rá... vagy talán mégsem. Nyomozok utána.";
			link.l1 = "Értem. Az ô segítségét Dominicán nagyon szívesen fogadtuk volna. Fleetwood és az ô 'Valkerie' félelmetes párost alkottak. Remélem, hogy Longway még életben van... Tot zeins, mynheer!";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			pchar.quest.Award_FromLucas.win_condition.l1 = "Timer";
			pchar.quest.Award_FromLucas.win_condition.l1.date.hour  = 8.00;
			pchar.quest.Award_FromLucas.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l2 = "location";
			pchar.quest.Award_FromLucas.win_condition.l2.location = "Villemstad_townhall";
			pchar.quest.Award_FromLucas.function = "AwardFromFromLucas";
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "Te nem csak egy közönséges bohóc vagy, hanem az egész cirkusz. Olyan közel voltunk az utolsó felvonáshoz, és te elszúrtad... 30,000 pezó-t fizetek neked Fleetwood kieséséért. Nincs több küldetésem számodra, és a megállapodásunknak vége. Kifelé!";
			link.l1 = "Ahogy óhajtja.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Rossz hírem van számodra.\nMíg távol voltál, Willemstadot megtámadták az angol kalózok. Az erôdnek sikerült elkergetnie ôket, de csak azután, hogy tûzhajókkal bejutottak a kikötôbe.\nA hajódat horgonyra vetették, és a vízvonalig leégett. Teljesen elpusztult.";
			link.l1 = "Azt hiszem, akkor én most megyek a picsába! Köszönöm a semmit!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Kapitein " + GetFullName(pchar) + "! Richard Fleetwood, egy veszélyes államellenes bûnözô likvidálásáért, a köztársaság elleni áruló angol összeesküvés leleplezéséért, bátorságáért és bátorságáért a Holland Köztársaság nevében ezer aranydublonnal jutalmazunk!\nEzt az értékes navigációs eszközt is megkapod - minden katonai tengerész álma.";
			link.l1 = "Örömmel szolgálom a Köztársaságot!";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "Még egyszer gratulálok, barátom. És kérem, látogasson meg egy hét múlva. Szükségünk van rád egy rendkívül kényes ügyben.";
			link.l1 = "Értettem, Mynheer Rodenburg. Egy hét múlva meglátogatom Önt.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("Azt mondják, hogy maga Matias Beck adta át az állami kitüntetést! A Köztársaság büszke lehet az olyan emberekre, mint te, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "Hadd meséljek el egy történetet. Segíteni fog megérteni, milyen kényes a következô feladat. Néhány hónappal ezelôtt egy angol zászló alatt közlekedô, Willemstadba tartó flottát megtámadott a néhai Jacob van Berg. Elvette a hajót és elsüllyesztette egy olyan szigettôl nem messze, amely nem szerepel egyik térképünkön sem. A hajó utasai közül csak ketten maradtak életben. Egy Solomon Shneur nevû zsidó és a lánya, Abigail. Az összes többi utas elpusztult, beleértve a család többi tagját is. A mi két zsidónk úgy jutott el a szigetre, hogy néhány roncson úszva\nSolomonnak még egy ládát is sikerült magával rántania, ami tele volt a család aranyával. Nagyon takarékos volt tôle. Történetünk egy másik szereplôje, Richard Fleetwood a közelben hajózott, és harci hangokat hallott. Túl késôn érkezett, hogy elkapja van Berget, és a 'Mirage' menekült. Fleetwood elhatározta, hogy megnézi a szigetet, nincs-e túlélô\nÔ mentette meg Salomont és Abigailt a biztos haláltól azon a lakatlan szigeten. Az öreg zsidó szerencsétlenségére Salamon nem rendelkezik tengerészszemmel. Összetévesztette Richard 'Valkerie' Jákobéval 'Mirage' és - megrémülve attól, hogy a kalóz visszatér, hogy befejezze a munkát - elrejtette az aranyát valahol a szigeten. Ennek eredményeképpen ô és a lánya egy fillér nélkül érkeztek ide, Fleetwood tette ki ôket a Blanca Lagúnánál, Willemstad közelében, az eredeti célállomásuknál.\nSolomon mesélte ezt a történetet. A Holland Köztársaság támogatja a szabad vallásgyakorlást. Ennek a politikának a részeként a társaság támogatja az itteni zsidó közösséget. Ezért gondoskodtam arról, hogy tetô legyen a fejük felett, és legyen mit enniük és viselniük. Sokat jártam náluk. Abigail egy... figyelemre méltó fiatal nô. Ôszinte és bizalomgerjesztô\nNem fogok hazudni magának, kapitány, akarom ôt, és szándékomban áll feleségül venni. Ô viszont szeret engem, de valami közénk állt.";
			link.l1 = "Az apja nem túl lelkes egy gój vô miatt?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "Ha! Az öreg Salamon a hetedik mennyországban lenne, ha feleségül venném Abigailt, akár körülmetéletlen a vejem, akár nem. Ami azt illeti, arra ösztökéli, hogy fogadja el a lánykérésemet. Nem, nem, ez olyasmi, ami túlmutat zsidón és pogányon. Arra kérlek, fiam, hogy oldd meg nekem ezt a problémát. Beszélj Abigéllel, és derítsd ki, mi a baj\nidegen vagy, lehet, hogy olyan dolgokat mond neked, amiket bájos szerénysége miatt ismerôsöknek soha nem mondana el. Shneur háza a cég irodájától jobbra található, ha háttal állsz neki. Tudom, hogy maga egy simulékony beszédû\nDe egy dolgot ne feledjen: Richard Fleetwood volt a 'szellemhajó igazi kapitánya'.... Ezt tartsd észben, miközben Abigail-lel beszélgetsz.";
			link.l1 = "Ha! Persze, hogy emlékszem rá, Mynheer Rodenburg. Hát nem ez a hivatalosan elismert tény mégiscsak? Akkor nem vesztegetem az idôt, azonnal meglátogatom a kedvesét.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "Tényleg megtaláltad a szigetet, ahol Salamon elrejtette az aranyat? Ez igazán kiváló! Már kezdtem azt hinni, hogy bármilyen feladatra képes vagy... Találtál még valamit a rejtekhelyen?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "Nem, semmi mást. Csak pénzt.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "Volt egy érdekes tárgy - egy jáde koponya. Odaadtam Salomonnak, azt mondta, hogy családi örökség. Azt is mondta, hogy azt tervezted, hogy megveszed tôle...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Hm. Rendben. Bár elég furcsa. Mindegy... Tartozom neked, mynheer, és ezt soha nem fogom elfelejteni. Készítettem neked jutalmat - 50,000 pezót és ezt az amulettet. Mostantól a tiéd.";
			link.l1 = "Köszönöm, Mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "Kitûnô! Igen, meg fogom venni ezt a leletet Salomontól, neki nincs rá szüksége, és van rá egy nagyon nagylelkû vevôm. Készítettem egy jutalmat neked - 50,000 pezó és ez az amulett. Mostantól a tiéd.";
			link.l1 = "Köszönöm, Mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "Jelenleg nincs olyan munkám, ami méltó lenne egy ilyen kapitányhoz, mint te. De ne hagyd el Curacaót túl sokáig, hamarosan újra szükségem lesz a szolgálataidra.";
			link.l1 = "Megvan, mynheer. Viszontlátásra!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Hallottad a legfrissebb híreket? Mynheer Rodenburg feleségül fogja venni Abigail Shneurt, az öreg ôrült zsidó Salamon gyönyörû lányát. Mit mondhatnék, szerencsés lány. Ha Isten is úgy akarja, még az esküvô elôtt megkeresztelik igazi kereszténynek!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "Ha, és ennyi? Nyilvánvalóan abszurd... mennyire hasonlít egy nôre. Figyelj rám, fiam, ez a probléma könnyen megoldható. Tudom, mennyi pénz volt Salamon rejtekhelyén: 200,000 pezó. Kész vagyok megspórolni ezt az összeget az én és Abigail boldogságáért. Odaadom neked a pénzt, te pedig egy-két hétre elhagyod Curacaót. Aztán visszatérsz Salamonhoz, és átadod neki a pénzt. Tégy úgy, mintha megtaláltad volna a rejtekhelyet. A farkas jóllakik, a bárányok pedig érintetlenül maradnak. Tessék, vedd el a szükséges összeget.";
			link.l1 = "Jó és egyszerû terv. Vágjunk bele!";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "Hajózz ki a nyílt tengerre, és tíz nap múlva térj vissza hozzám. Menj, csinálj valami hasznosat. Keressétek meg Manga Rosát, készítsetek valami anyagot, vagy valami ilyesmi.";
			link.l1 = "Ahogy akarod, Mynheer Rodenburg.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Nagyszerû! Ismét tökéletesen elvégezted a feladatot. Tartozom neked, Mynheer, és ezt soha nem fogom elfelejteni. Készítettem neked jutalmat - 50.000 pezót és ezt az amulettet. Mostantól a tiéd.";
			link.l1 = "Köszönöm, Mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "Igen, pontosan így van. Barátom, néha nehéz észrevenni, hogy ki a barátod és ki az ellenséged. Néha nem érted a lényeget, amikor a legközelebbi társad a nemeziseddé válik. Közös ismerôsünk a St John's-ból, John Murdock - más néven Johan van Merden - a Cég volt ügynöke, aki eladta magát az angol haditengerészetnek.\nÚjabb küldetése, hogy likvidálja a Cég egyik legfényesebb csillagát... téged.";
			link.l1 = "Ez hízelgô. Örülök, hogy szóltál, különben nem gondoltam volna, hogy ez lesz.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "Pontosan, kapitein. Ô egy ravasz kutya. Találd meg a fattyút és öld meg, mielôtt lecsapna. Hajózz Antiguára, és keresd meg a gyógyszertárának titkos bejáratát. A templom elôtt van egy lejáró, ami egy titkos alagútba vezet. Használd azt.";
			link.l1 = "Majd én gondoskodom róla.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "Még egy dolog, kapitein. Ha Johan meghalt, kutassátok át a holttestét, a házat és a pincét. Van egy archívuma - egy vaskos fôkönyv, amibe a Cégnek végzett munkája során néhány kárhozatos feljegyzést írt. Ezek az információk mindannyiunkat elpusztítanak, ha az ellenségeink megtalálják.\nKeresd meg azt az átkozott archívumot, és szállítsd el nekem, külön fizetek érte. Most menj. Isten éltessen, Kapitein " + pchar.name + ", és igyekezz épségben visszatérni. A Köztársaságnak szüksége van rád!";
			link.l1 = "Megígérem, mynheer, hogy egy darabban térek vissza. Ez a legbiztosabb érdekem!";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "Kitûnô, kapitány! Örülök, tényleg örülök. Megtalálta az archívumát?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "Igen, itt van. A vegyész holttestén vagy a ládáiban nem volt más irat.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "Nem. Mindenhol kerestem, de nem találtam semmit.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "Ez sajnálatos, de nekem megfelel. Biztos vagyok benne, hogy Johannak nem volt elég ideje, hogy az angoloknak adja, különben már hurok lenne a nyakunkon... Valószínû, hogy valami titkos rejtekhelyen rejtette el... maradjon ott örökre! Gratulálok, kapitein, küldetésünk sikeres befejezéséhez!";
			link.l1 = "Köszönetnyilvánítás!";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "Nagyszerû! Most már biztonságban van ott, ahová való. Ismét bebizonyítottad, hogy te vagy a legjobb... Add ide a könyvet... Az archívumért jutalom jár - ez a remek muskéta. Kiválóan szolgált engem, és most a tiéd!";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "Mi a játékod, kapitány? Több oldal hiányzik - olyan oldalak, amelyek nagyon fontosak számomra. Azt hitte, nem veszem észre, hogy felhasználhassa ellenem? Vagy azt remélte, hogy többet kaphat belôle? Attól tartok, mindkettôben csalódást kell okoznom.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Megbízható", "Trustworthy");
				link.l1 = "(Megbízható) Elnézést kérek. Az egyetlen hibám az volt, hogy nem néztem meg elôzetesen magam az archívumot.";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				notification("A képességek ellenôrzése sikertelen.", "Trustworthy");
				link.l1 = "Tényleg kitépném a lapokat, majd közömbös tekintettel átadnám az archívumot?";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "A kapzsiság, az ostobaság és a szemtelenség néha a legôrültebb tettekre készteti az embereket, kapitány.";
			link.l1 = "Biztosíthatom, hogy engem e három közül egyik sem motivált.";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "Tehát azt mondod, hogy van Merden eltávolította azokat az oldalakat, és máshová rejtette ôket?";
			link.l1 = "Pontosan. Visszamehetek és megkereshetem ôket - felforgathatom az egész patikát, vagy akár az egész St. John's-t -, ha szükségesnek tartja.";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "Nem szükséges, uram. A legtöbb fontos dolog amúgy is itt van, és a hiányzó lapok nélkül a többi nem jelent veszélyt rám.";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "Tehát inkább a törôdés vagy a kíváncsiság hiánya, mint a becstelenség vagy a titkos szándék? Gondolja, hogy már akkor is ilyen volt, amikor megtalálta?";
			link.l1 = "Valószínûleg, Mynheer Rodenburg. Talán van Merden már korábban kitépte azokat a lapokat. ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "Talán így a legjobb. Azok nélkül az oldalak nélkül az archívum többi része nem jelent veszélyt rám - különösen nem tudatlan kezekben.";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "Van jutalom az archívumért - ez a remek muskéta. Kiválóan szolgált engem, és most a tiéd!";
			link.l1 = "Köszönet!";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "Jól csináltuk, te és én, kapitány. Nem túlzás, hogy mindez nem történt volna meg nélküled. Hihetetlen karriert fogsz elérni abban az esetben, ha továbbra is a Köztársaságot fogod szolgálni, talán még nemesíteni is fognak.";
			link.l1 = "Azt hiszem, itt a búcsú, Mynheer Rodenburg.";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "Ez a búcsú, " + pchar.name + ". Mindent elértem, amit itt akartam, így egy hét múlva indulok haza Amszterdamba. Új feleségem, Abigail és apósom, Salamon elkísérnek. Peter Stuyvesant már megtalálta az új cégigazgató-helyettest, szóval beszéljetek vele, ha szükségetek van valamire\nA szolgálatotokra bemutatom a Meifenget. Most már a tiéd, kapitány, megérdemled.";
			link.l1 = "Köszönöm, Mynheer Rodenburg. Eléggé kötôdöm a Meifenghez, és máris a sajátomnak tekintem.";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "És most meg kell kérnem, hogy hagyj itt, fiam. Sok dolgom van még, mielôtt kihajózunk... Látogass meg egyszer Amszterdamban! Megiszunk egy italt, és felidézzük a régi szép idôket...";
			link.l1 = "Igenis, uram. Remélem, hogy mindannyian boldogok és sikeresek lesztek az új életetekben! Isten veletek!";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "Igenis, uram. Remélem, hogy mindannyian boldogok és sikeresek lesztek az új életetekben!\n(fogcsikorgatva) ... Remélem, nem találkozunk többet, te arrogáns pöcs. Csak várj, amíg felfedezed, milyen örömökkel jár, ha egy 'demure' zsidó harridával házasodsz össze.";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			CheckPortugalHWIC();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg Amszterdamba hajózott fiatal feleségével és apósával. Maga az új igazgatóhelyettes?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			CheckPortugalHWIC();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg Amszterdamba hajózott fiatal feleségével és apósával. Maga az új igazgatóhelyettes?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "Isten a Hemelben! Fleetwood kutyája! Lehet, hogy ma gyôzni fogsz, de Lucas Rodenburg drágán fogja eladni az életét.";
			link.l1 = "Nem hinném. Az életét ingyen adja át nekem, maga holland zsugori.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "A pokol mélyérôl a szádba fogok szarni! Épp most gyújtottam fel a raktérben, és a tûz hamarosan átterjed a lôporraktárra is! A hajóinkat szorosan összefogták, így nincs remény a menekülésre! Vagy elégsz, vagy megeteted a cápákat!";
			link.l1 = "A francba! Vissza, emberek, vissza kell vonulnunk!";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "Nem megyek el, amíg a lelked el nem hagyja a tested. Maradj nyugton, ez fájni fog.";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "Miért vagy itt, te szemétláda? Azért jöttél, hogy kigúnyolj? Talán végre elmondod, mi a helyed ebben a darabban. Te voltál az, aki elfogta a brigantint, igaz? Ez volt a terved a kezdetektôl fogva?";
			link.l1 = "Azért jöttem, hogy üdvözöljem, Lucas Rodenburg. A legjobb üdvözletem John Merdocktól, akit elárultál. Te voltál a feladatom, és én elvégeztem. Egyelôre búcsúzom.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Johan? Haha! Szóval ô állt az egész mögött! Az a vén gazember! De a játéknak még nincs vége. Jacob van Berg eljön érted, és nem fogsz megmenekülni! Te és a hajód elveszett, te szánalmas tengeri koldus!";
			link.l1 = "Kíméld a hangodat a hóhérbíróságra, Rodenburg.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
