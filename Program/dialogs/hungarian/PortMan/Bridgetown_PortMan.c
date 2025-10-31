// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Mit akarsz? A-ha, te vagy a regatta résztvevôje! Igazam van?";
				link.l1 = "Pontosan, uram. A szabályok szerint regisztrálnom kell itt.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Már próbáltál kérdezni " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Nézze, ha nincs mondanivalója a kikötô ügyeirôl, akkor ne zavarjon a kérdéseivel.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam.", "Nincs mirôl beszélnem."), "Nevermind.", "Valóban, már harmadszor...", "Sajnálom, de egyelôre nem érdekelnek a kikötô ügyei.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Blueweldbe hajózom, hogy eladjak egy kis paprikát. Mondja, uram, vannak utasai, akik Blueweldbe tartanak? Vagy legalábbis Kikötô-Royalba. Jó lenne egy kis pénzt kapni egy utastól, az segíthetne kifizetni a legénység bérét. Már lecsökkentettem a minimumra, de ezek a lusta disznók még mindig pénzt kérnek...";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "Volt egy gálya 'Admirable' megszállt Philipsburgban Gaius Marchais parancsnoksága alatt. Egy rakomány paprikát kellett ide szállítania. Tudna segíteni nekem megtalálni ezt a kapitányt?";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "Egy furcsa nevû xebecrôl szeretnék érdeklôdni.";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "Úgy hallottam, hogy egy Jack... vagy Jackson kapitányhoz tartozó xebec gyakran megfordul az önök kikötôjében. Meg tudná mondani, hol keressem?";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "Sajnos, sem Blueweldbe, sem Kikötô-Royalba nem érkeznek utasok. Jöjjön vissza holnap vagy holnapután.";
			link.l1 = "Kár érte. Akkor viszlát.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-9");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Hm... Megszegted a regatta szabályait, ezért ki kell, hogy zárjalak. Sajnálom. Nem vehetsz részt a következô hajón. Már elôkészítettem egy küldeményt Kikötô-Royalba.";
				link.l1 = "Eh... milyen kár! De itt nem tehetek semmit, túl éber voltál. Viszontlátásra!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "Talán észrevette, kapitány, hogy a város ostrom alatt áll. Arra számítunk, hogy a spanyolok bármikor megtámadnak minket, és mozgósítjuk erôinket. De a regatta még mindig folytatódik\nNevezzünk: kapitány "+ GetFullName(pchar) +", a hajó - "+pchar.Ship.Name+"... A regatta ideje órákban: "+sti(pchar.questTemp.Regata.FourthTransitionTime)+". Kész, az eredményed regisztrálva, folytathatod az utadat.";
				link.l1 = "Mondd meg a rangomat.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Itt vagy, de nem látom a hajódat. Hol van?";
			link.l1 = "Sajnálom, uram. Azonnal átviszem a hajómat a kikötôbe.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Ah, igen... Sajnálom, hogy túl elfoglalt voltam ehhez. Te vagy az elsô.";
			link.l1 = "Értem. Köszönöm az információt.";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Ah, igen... Sajnálom, hogy túl elfoglalt voltam. Te vagy az utolsó.";
				link.l1 = "Értem. Köszönöm az információt.";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
				}
				else
				{
					if (n==2)
					{
						dialog.text = "Ah, igen... Sajnálom, túl elfoglalt vagyok ehhez. Te vagy a második. Csak egy kapitány van, aki megelôz téged. A neve "+sName+" a hajón "+sShip+".";
						link.l1 = "Értem. Köszönöm az információt.";
						link.l1.go = "exit";
						AddQuestRecord("Regata", "23");
					}
					else
					{
						dialog.text = "Ah, igen... Sajnálom, hogy túl elfoglalt vagyok ehhez. A rangod: "+n+" . A legközelebbi ellenfeled "+sName+" a "+sShip+"hajón.";
						link.l1 = "Értem. Köszönöm az információt.";
						link.l1.go = "exit";
						if (n==3) AddQuestRecord("Regata", "24");
						if (n==4) AddQuestRecord("Regata", "25");
						if (n==5) AddQuestRecord("Regata", "26");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Repair", 30);//починка
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Bridgetown = "true";//отметка Бриджтауна
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "Curacao";
			pchar.questTemp.Regata.AttackNation = HOLLAND;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//третья засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Барбадоса
			pchar.quest.Regata_Finish.win_condition.l1 = "location";
			pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Finish.function = "RegataFinishSea";
			pchar.quest.Regata_Finish1.win_condition.l1 = "location";
			pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
			pchar.quest.Regata_Finish1.function = "RegataFinishTown";//финиш регаты
			//ситуации
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_Siege.function = "RegataSiegeOfficer";//на квест по вывозу жителей
		break;
		//регата
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Igen, ez a gálya itt volt, megszabadult az árujától és késôbb elhagyta a kikötônket. Információ a célállomásáról... hm... nincs, nincs semmi. Sajnálom, de nem tehetek semmit.";
			link.l1 = "Értem, értem. Kár... Folytatom a keresést.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Uram, szükségem van a hajó pontos nevére. Rengeteg Jack és Jackson jár a kikötônkben. Szóval, mi a neve?";
			link.l1 = "Szíréna."; 
			link.l1.go = "caleuche_wrong_name";
			link.l2 = "Lámia."; 
			link.l2.go = "caleuche_wrong_name";
			link.l3 = "Harpia."; 
			link.l3.go = "caleuche_name";
			link.l4 = "Fúria."; 
			link.l4.go = "caleuche_wrong_name";
			link.l5 = "Az a baj, hogy nem tudom a régi kádjának a nevét. Furcsa, valami madaras nô, aki...";
			link.l5.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Uram, menjen és meséljen a kocsmában, itt komoly üzem van. Vagy megmondja annak a xebecnek a nevét, vagy ne zavarjon a munkámban.";
			link.l1 = "Rendben, megpróbálom kideríteni.";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "Na, és? Tudod a hajó nevét? Hallgatom.";
			link.l1 = "Szíréna."; 
			link.l1.go = "caleuche_wrong_name";
			link.l2 = "Lámia."; 
			link.l2.go = "caleuche_wrong_name";
			link.l3 = "Harpia."; 
			link.l3.go = "caleuche_name";
			link.l4 = "Fúria."; 
			link.l4.go = "caleuche_wrong_name";
			link.l5 = "Még gondolkodnom kell egy kicsit.";
			link.l5.go = "exit";
		break;
		
		case "caleuche_name":
			dialog.text = "'Harpy'? Természetesen tudom, hogy xebec. A kapitánya Reginald Jackson. De nem régen járt Bridgetownban. Úgy hallottam, hogy most a Holland Nyugat-indiai Társaságnak dolgozik. Szóval Willemstadban kellene keresnie.";
			link.l1 = "Köszönöm szépen! Sokat segített nekem.";
			link.l1.go = "caleuche_3";
			DelLandQuestMark(npchar);
		break;
		
		case "caleuche_wrong_name":
			dialog.text = "Sajnálom, de ez nem ismerôs. Biztos benne, hogy a kapitánya valaha is járt itt, Bridgetownban?";
			link.l1 = "Biztos vagyok benne. Rendben, talán kitalálok valamit...";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "18");
			pchar.questTemp.Caleuche.Garpiya = "gwik"; 
			npchar.quest.garpiya = "true";
			AddLandQuestMarkToPhantom("GVIK", "HWIC_headclerk");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
