void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "Gazember! Nagy meglepetés ért!";
    		link.l1 = "Micsoda?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "Ha-ha! Itt nincsenek rabszolgák! Miattuk vagy itt, ugye?";
			link.l1 = "Baszd meg! Én meg azon gondolkodtam, hogy mi a fenéért van ennyi katona egy kereskedelmi hajón... Csapda!";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "Igen, te szemétláda, ez egy csapda. Nem kereskedô vagyok, hanem katonatiszt! Bár a harcot megnyerted, az ítéletet nem úszod meg!";
			link.l1 = "És miért? Most végzek veled, elsüllyesztem a hajódat, és senki sem fog tudni semmit.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "Tévedsz. A bankárral folytatott üzleted kiderült. Hamarosan a fôkormányzó is tudomást szerez a kis üzletedrôl, és nem úszod meg az akasztófát. De én szívességet teszek neked azzal, hogy most és itt helyben megöllek!";
			link.l1 = "Próbáld meg, te kormányzó kutyája!";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = "" + GetFullName(pchar) + ", a törvény nevében, le vagy tartóztatva! Adjátok le a fegyvert és kövessetek minket!";
			link.l1 = "Mi folyik itt, biztos úr? Milyen alapon adják meg magukat?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "Ne próbáljon hülyét játszani, kapitány! A mocskos ügyei leleplezôdtek. És a mészárlásért, amit elkövettél, és a " + NationNameGenitive(sti(npchar.nation)) + " hajóért, amit elsüllyesztettél, látni fogjuk, ahogy felakasztanak!";
			link.l1 = "Nos, ha már így fogalmazott... Menj a picsába!";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "Hé, mit keresel itt?!";
    		link.l1 = "Miért ilyen goromba, jó uram? Az a patkány Gontier itt bujkál valahol, mi?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "Nem, nem rejtôzik! Kifelé!";
			link.l1 = "Úgy tûnik, hazudsz. Átkutatom a házat, és meglátom...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "Baszd meg! Francois! Futás! Srácok, segítsetek!";
			link.l1 = "Basszus!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "Ó! Ne erôszakoljatok meg!";
    		link.l1 = "Mi a...? Hol van Francois Gontier? Válaszolj, te mocskos ribanc, vagy véged lesz, mint a társaidnak!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "Nem, nem, mindent elmondok! Kiugrott az ablakon, és elszaladt a hajójára.";
    		link.l1 = "Milyen hajóra? Tudom, hogy nincs a hajója a kikötôben. Ne hazudj nekem, kislány, vagy még rosszabb lesz...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "Nem hazudok, esküszöm! Azt mondta, hogy egy kis szigeten szállt partra, és egy hosszúhajón jött ide... Ott kell lennie! Ne bánts!";
    		link.l1 = "Rendben, úgy tûnik, igazat mondasz. Maradj itt és maradj csendben. És próbálj meg a jövôben okosabban barátkozni. De tudod, látom a szemedben, hogy nincs eszed.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "Kímélj meg minket! Kegyelem! Megadjuk magunkat!";
    		link.l1 = "Ó, tényleg? Azonnal menjetek a raktérbe! Lelövök mindenkit, aki megpróbál hülyét játszani!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "Nocsak, nocsak... Mi van itt? Nem tudjátok, hogy a mi kolóniánkon tilos az árucsere illetéktelenekkel és illetéktelenek között?";
			link.l1 = "Tényleg, tiszt úr? Hogy ôszinte legyek, most hallok errôl elôször. Ezt a rendeletet nemrég fogadták el, igazam van?";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "Mi, kereskedés " + GetGoodsNameAlt(iCGood)+ "? Nem látok itt semmilyen " + GetGoodsNameAlt(iCGood)+ " , biztos úr. Csak ezeket a fényes érméket látom... És ô is ugyanezt látja. Miért nem nézi meg a katonáival együtt a mi érméinket is?";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "Nem tudtad, mi? Hmm... úgy tûnik, nem hazudsz. De mégis megszegted a törvényt. Nem tartóztatlak le, de pénzbüntetést kell fizetned. És a rakomány... errôl majd beszélünk az alku második résztvevôjével.";
				link.l1 = "És mennyi az a bírság?";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "Ne játssza a hülyét, kapitány! Ezt már mindenki tudja, és ha szabad hozzátennem, már régóta. Mindkettôjüket letartóztatom csempészetért, és a rakományukat elkobozzuk.";
				link.l1 = "Nem szeretem a kazamatákat, tiszt úr. Szeretem a nyílt tengert... és most oda fogok hajózni. De úgy tûnik, hogy ezt csak a holttestén keresztül tehetem meg.";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Nincs más választásom, mint megadni magam. De nekem tényleg fogalmam sem volt róla!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "Most már beszélsz... Lássuk az érméidet... Azt hiszem, hallottam egy egészen konkrét számot - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ". Mivel most már három résztvevônk van, szeretném, ha a " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + ". Ez tôled és ugyanez a barátodtól is.";
				link.l1 = "Persze, biztos úr. Itt vannak a fényes érméim, vagy, bocsánat, a fényes érméi - csak véletlenül a partra ejtette ôket... És itt nincs " + GetGoodsNameAlt(iCGood)+ " , ha-ha, ahogy már mondtam.";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "Hûha! Maga túl mohó, biztos úr. Nem tanította meg az anyukád, hogy a kapzsiság nem jó? Gondolom, olcsóbb lenne, ha a pengémmel bánnék el veled.";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "Viccel, kapitány? Meg akar vesztegetni? Le van tartóztatva! Fogjátok el!";
				link.l1 = "Nos, ha nem akarja megnézni a pénzemet, akkor nézze meg a kardomat!";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Nincs más választásom, mint megadni magam. De nekem tényleg fogalmam sem volt róla!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "Igen, úgy tûnik, igaza van... Semmi érdekes nincs itt, kivéve néhány úriembert és a fényes érméimet. Szabadon távozhat, kapitány úr, mi pedig majd beszélgetünk a társával.";
			link.l1 = "Viszlát, tiszt úr. Ne bántsd ôt.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = "" + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + ". Köszönöm a jó kedvemet.";
			link.l1 = "Köszönöm, biztos úr. Tényleg nem tudtam... Tessék, kész vagyok kifizetni a bírságot.";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "Gondolom, maga sem olyan becsületes, biztos úr. Túl nagy a bírság. Gondolom, segíteni fogok a kolónián azzal, hogy megmentem a létezésétôl.";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "Rendben. Most már elmehet. És azt tanácsolom, hogy tanulmányozza a helyi törvényeket, hogy a jövôben elkerülje az ilyen helyzeteket. Most menj, el kell intéznünk ennek a kereskedésnek a második résztvevôjét, ô mindenrôl tudott, az biztos.";
			link.l1 = "Nos, ebben az esetben, szép napot, biztos úr.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "A parancsnok majd foglalkozik magával. Kövessenek!";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "Jó napot! Akar valamit?";
			link.l1 = "Igen, haver. Gondolom, te vagy az én emberem. Te voltál az, aki ellopta "+pchar.GenQuest.Device.Shipyarder.Type+"  a helyi hajógyárból? Minden hozzád vezet, úgyhogy ne vitatkozzunk.";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "Könyörgöm, uram! Igen, én loptam ezt a furcsa dolgot a hajógyárból. De nem sikerült eladnom, senkinek sincs szüksége ilyen tárgyra. Így hát megszabadultam tôle. Kíméljen meg, jó uram, az éhségemet hibáztassa, ne engem... Másképp soha nem mernék lopni semmit!";
					link.l1 = "Ez egy probléma... És te sem kellesz nekem. Meg kell találnom azt a "+pchar.GenQuest.Device.Shipyarder.Type+". Mondd meg, hol dobtad el?";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "Könyörgöm, uram! Igen, én loptam el ezt a furcsa dolgot a hajógyárból. De nem sikerült eladnom, senkinek sincs szüksége ilyen tárgyra. Odaadom neked. Tessék, vedd el, csak ne bánts, és ne hívd a katonákat!";
					link.l1 = "Rendben, élhetsz, gengszter. Nekem nem a te bôröd kell, hanem az az eszköz. Add ide azonnal és tûnj el!";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "Hogy érti ezt? Mi az a "+pchar.GenQuest.Device.Shipyarder.Type+"? Nem értem!";
					link.l1 = "Majd megkapod, ha átkutatlak vagy a holttestedet! Add ide most!";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "Ó... Mi az a "+pchar.GenQuest.Device.Shipyarder.Type+"? Én... és mi az?";
					link.l1 = "Ne próbálj meg hülyét játszani vagy elfutni, úgyis elkaplak. Csak hadd nézzem meg a zsebeidet...";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "A városkapuk mögött, nem messze a dzsungeltôl. Könyörgöm, jó uram! Ha tényleg szükséged van arra a dologra, magad is fel tudod venni. Biztos vagyok benne, hogy még mindig ott van.";
			link.l1 = "Kényszerítenem kellene, hogy megtaláld és elhozd nekem, de félek, hogy több idôt töltenék a keresésével, mint a "+pchar.GenQuest.Device.Shipyarder.Type+". Majd én magam megcsinálom. De akkor is megtalálom, ha hazudtál nekem!";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "Tessék, vedd el. Köszönöm, kedves uram!";
			link.l1 = "Hát, biztos ez az, amit kerestem... ha! Most már szabadon távozhatsz. Menjetek. És legközelebb légy óvatos.";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("Megkaptad az ellopott hangszert");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "Figyelj, errôl a hangszerrôl beszélsz? Ez az enyém, és nem loptam el! És nem fogom ingyen odaadni neked. Ha meg akarod szerezni, fizess nekem " + FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)) + ".";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "Hm... Rendben. Fizetek neked. Itt vannak az érméid, és add ide a hangszert!";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "Tényleg? Tényleg azt hitted, hogy megbízom benned, nyomorult tolvaj? Add ide a "+pchar.GenQuest.Device.Shipyarder.Type+" vagy hívom az ôrséget, hogy együtt mehessünk a hajógyárba, és eldöntsük, kié ez a mûszer valójában.";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "Hülye vagy, vagy mi? Figyelj, te szemétláda, két lehetôséged van: vagy ideadod a "+pchar.GenQuest.Device.Shipyarder.Type+" , vagy leszúrlak, és elveszem a hangszert a holttestedbôl!";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "Szép üzlet, kapitány! Gondolom, mindannyian megkapjuk a hasznunkat, ôôô... vedd el.";
			link.l1 = "Kevesebb beszéd, tolvaj! Ne hidd, hogy átvertél, én csak békésen és kevesebb problémával akarom csinálni. Ezek az érmék úgysem segítenek neked semmi jót. Tûnjetek el!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("Megkaptad az ellopott hangszert");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Ne! Ne hívd az ôröket! Én... én odaadom neked ezt az átkozott eszközt. Tessék, vedd el!";
				link.l1 = "Ez sokkal jobb, ha tudod! Tûnjetek el! Vagy a bitófán fogod végezni, csak idô kérdése.";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "Milyen ôrök, kapitány? Csak te és én vagyunk itt. Túl sokat vitatkoztok, úgyhogy le kell, hogy nyugtassalak titeket... a pengémmel.";
				link.l1 = "Fenyegetni mersz, te szemétláda?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Ah! Segítség! Gyilkos!";
				link.l1 = "Állj meg ott, kutya!";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "Lássuk, ki kit szúr le, kapitány!";
				link.l1 = "Fenyegetni mersz, te szemétláda?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "Keresed? Kérem, jó uram!";
			link.l1 = "Na ide figyelj, vagy békésen átadod nekem azt, amit az imént elloptál a hajógyárból, vagy elviszlek a parancsnokságra. Ezt a dolgot mindenképpen átadod nekem, de elôbb a sarkadat égetem meg a vörösen izzó vassal. Lehet, hogy utána még fel is akasztanak. A választás a tiéd.";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "Azonnal add ide, amit elloptál, te fattyú, vagy ott végzek veled, ahol állsz!";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезёт
			{
				dialog.text = "Nos, elôbb el kell kapnod, ha el akarsz vinni a parancsnokságra...";
				link.l1 = "Maradj ott, kutya!";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "Ne, ne vigyél a parancsnoki irodába! Majd én magam adom! Tessék, fogd meg, biztos ezt a dolgot keresed. Úgysem venné meg senki...";
				link.l1 = "Eh, azt hiszem, az erôdbe is elvihetnélek... Rendben, add ide a szerszámot és tûnj el!";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "Aú! Ne bánts, mindent odaadok neked, amim csak van! Tessék, vedd el!";
			link.l1 = "Most már beszélsz! Tûnj el, ha még egyszer meglátlak ebben a városban, átadlak a parancsnoknak. Viszontlátásra!";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("Megkaptad az ellopott hangszert");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "Állj meg, haver! Szükségünk van egy dologra, ami nálad van. Add ide, aztán menj tovább.";
			link.l1 = "Mi az a dolog, amirôl beszélsz?";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "Ezek az utcai emberek túl szemtelenek manapság... Készüljetek, gazemberek!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "Ne tegyetek úgy, mintha bolondok lennétek! Adjátok ide a csomagot, és életben maradtok. Máskülönben... el fogjuk venni a holttestetekbôl!";
			link.l1 = "Az esélyek a ti oldalatokon állnak... vegyétek el, szemetek, nincs más választásom.";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "Nos, megpróbálhatjátok!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "Vigyázz a nyelvedre, haver... Okos dolog, hogy nem hívod ki a szerencsédet. A vége ugyanaz lett volna, ha-ha! Egy darabig még élni fogsz... Viszlát.";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "Várj, " + GetAddress_Form(NPChar) + ", ne siess így. Van egy üzletem a számodra.";
			link.l1 = "Milyen üzlet? Nem ismerlek.";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "Ismerem magát, kapitány. Most pedig egyenesen az üzlethez. Most kapta meg "+pchar.questTemp.WPU.Current.Add+" a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". Ne próbálja tagadni, ezt biztosan tudjuk - elvégre már napok óta keressük ezt a dokumentumot.";
			link.l1 = "Most már értem. Na és akkor mi van?";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "Adja ide a csomagot, és rövid találkozónk véget ér. Ne próbáljon hôst játszani, kapitány, szándékunkban áll megszerezni ezeket a papírokat, és készen állunk arra, hogy harcoljunk a városi helyôrséggel, ha kell\nAmint talán megérti, ön fog elôször meghalni, ha a csetepaté elkezdôdik. Szóval add ide az iratokat, és barátként válunk el.";
			link.l1 = "Az esélyek a ti oldalatokon állnak... fogjátok, szemetek, nincs más választásom.";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "Meg akartok ijeszteni, láttam már olyan kis halakat, akik jobban küzdöttek, mint ti valaha is tudnátok! Húzzatok el!";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "Örülök, hogy ésszerû volt, kapitány. Nagy veszélynek tette ki magát azzal, hogy elvállalta ezt a munkát. Most elmegyek, ha nem bánja.";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "A maga döntése volt...";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap(false);//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "Várj, " + GetAddress_Form(NPChar) + ", ne siess így. Van egy üzletem a számodra.";
			link.l1 = "Milyen ügyben? Beszéljen gyorsan, sietek.";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "Tudom, hogy ki vagy. És azt is tudom, hogy most kaptál egy "+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". Ezek a papírok az oka annak, hogy annyira szeretnék beszélni önnel.";
			link.l1 = "És nem akarom ezt az ügyet olyan emberekkel megvitatni, akiket nem ismerek. Meg akarod szerezni azokat a papírokat? Csak mondj egy okot...";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "Elég, kapitány! Úgy nézek ki, mint egy rabló? Üzletember vagyok, és a " + NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation)) + "érdekeit képviselem. Szeretnék egy nagyon jövedelmezô üzletet ajánlani, de nem itt. Menjünk a kocsma szobájába, és beszéljük meg ezt az ügyet. Nem fog sok idôtökbe kerülni.";
			link.l1 = "Ez túl gyanús... Nem fogok üzletet kötni önnel, uram! Tûnjetek el!";
			link.l1.go = "PostAgent_getout";
			link.l2 = "Hm... Lássuk, mit tudsz ajánlani nekem. De meg se próbáljon megtámadni, annak nem lesz jó vége. Menjünk, én követlek.";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "Maga egy makacs és ostoba ember, kapitány! Felajánlottam neked egy esélyt, hogy könnyû pénzt keress. És te... meg fogod bánni.";
			link.l1 = "Húzzon el!";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "Pompás! Jöjjön utánam.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "Most már szabadon beszélhetünk.";
			link.l1 = "És mi a javaslata?";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "Mint mondtam, ez az egész a kikötôi hivatalban kapott papírokról szól. Csak egy másolatra van szükségem róluk, ennyi\nAz eredetit megtartja, így fizetnek magának a munkáért. Soha senki nem fogja megtudni, mi történt, ráadásul jól megfizetlek.";
			link.l1 = "Elnézést... De a csomag le van zárva. Nem fog tudni másolatot készíteni anélkül, hogy feltörné a pecsétet!";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "Erre a kérdésre számítottam. Fel kell törnöm a pecsétet, de ne aggódjon, vissza tudom majd állítani. Természetesen van egy másolati klisém és pecsétviaszom. Senki sem fogja észrevenni, hogy a csomagot felbontották.";
			link.l1 = "Van egy hamis kliséje a kikötô adminisztrációjának " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ "?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "Miért kérdezi, kapitány? Igen, van egy. Tényleg azt hiszi, hogy csak játszadozom? Felajánlom önnek a "+ FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" lehetôséget, hogy megnézhesse ezeket a papírokat. Szóval, végre odaadja nekem a csomagot? Kérem.";
			link.l1 = "Fogadja el, de vissza kell kapnom és lepecsételve!";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "Tudod, hogy nem fogom. Nem tetszik ez nekem.";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "Ne aggódjon. Én profi vagyok. Foglaljon helyet és pihenjen. Egy óra múlva kezdôdik.";
			link.l1 = "Rendben.";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "Hm... erre nem számítottam. Túl makacs vagy, kapitány, úgyhogy kénytelen leszek megölni téged ott, ahol állsz, és ingyen elvinni a csomagot. Imádkozz, mert a pengémmel ugyanolyan jól dolgozom, mint a hamis klisékkel.";
			link.l1 = "Neked kellene imádkoznod, kém!";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "Kész. Mint mondtam, a legpontosabb módon történt. Vegye a csomagot és ígérje meg "+ FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+". És nekem mennem kell. Sok szerencsét, kapitány, örülök, hogy megegyeztünk.";
			link.l1 = "Ég veled...";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "Üdvözletem! Ó, annyira örülök, hogy látlak!";
			link.l1 = "Jó napot! Hm, mondd csak, nem te vagy a "+pchar.questTemp.WPU.Escort.ShipName+"parancsnoka?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "Ó! És honnan tudtál a "+pchar.questTemp.WPU.Escort.ShipName+"? Igen, én vagyok a kapitánya. Vagyis voltam... A hajó nem messze innen elsüllyedt.";
			link.l1 = "Ah, akkor megtaláltalak... Hadd mutatkozzam be - " + GetFullName(pchar) + ". A kikötômester kérésére vagyok itt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Röviden beszámolt nekem a karavánotok gondjairól, és elküldött, hogy keressem meg a hajótokat.";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "Tehát te vagy a mentôcsapat kapitánya?";
			link.l1 = "Valami ilyesmi. Az volt a feladatom, hogy megtaláljam a hajótokat, vagy bizonyítékokat arra, hogy elsüllyedt vagy hajózásra képtelen. Sajnos, a hajót nem találtam meg, de a kapitánya életben van, ez biztos, hogy jó dolog...";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "Ó, elnézést, elfelejtettem bemutatkozni. A nevem " + GetFullName(npchar) + ". Tudod már, hogy kerültünk ide? A vihar irányíthatatlanná tette a hajónkat\nPár nap múlva, ettôl az öböltôl nem messze zátonyra futott, és az orkán percek alatt elpusztította. A legénységembôl csak néhány tucatnyian élték túl. A többiek a tenger fenekén fekszenek. Minden nap imádkozunk a lelkükért...";
			link.l1 = "Fogadja részvétemet, kapitány " + GetFullName(npchar) + ". Nagyon sajnálom.";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "Köszönöm... A túlélôk tábort vertek a parton, segítséget remélve. Épp idôben érkezett, kapitány! A helyi harcias indiánok tudnak a jelenlétünkrôl, több száz indián ellen esélyünk sem lesz, ha megtámadnak minket\nEgy kalózhajó is cirkál a környéken, úgy tûnik, minket keresnek. Találkozott már ezzel a kalózzal, kapitány?";
			link.l1 = "Nem, még nem.";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "Hála az Úrnak ezért. Ô egyike azoknak, akik megtámadtak minket az átkozott vihar elôtt. Mint egy hiéna, úgy akar végezni egy sebesült imádkozóval, ezért érkezett ide, erre a szigetre.";
			link.l1 = "Értem. Itt az ideje, hogy eldöntsük, mi legyen a következô lépés.";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "Mit kell eldöntenünk, kapitány? Vigyél minket a fedélzetre, és tûnjünk el errôl az átkozott helyrôl.";
			link.l1 = "Hát persze. Nem sikerült megmentenem a hajót, de legalább a legénységét megmentem. Szedjétek össze a táborotokat, én pedig parancsot adok, hogy küldjetek ide hosszúhajókat. Isten hozott a fedélzeten!";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "Köszönöm, kapitány! Nem tart sokáig. Várjatok... Mi a fene? Argh! Azok a vörösbôrû ördögök megint jönnek értünk! Riadó! Fegyverbe!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "Fuh, megcsináltuk... Látja, kapitány, mondtam, hogy ez az öböl maga a pokol. Ez már a harmadik indián támadás! El kell hagynunk ezt a helyet, amilyen gyorsan csak lehet, nem élünk túl még egy támadást.";
			link.l1 = "Igen, igaza van. Gyûjtsetek össze minden élô lelket és menjetek a hajómon! Azonnal elrendelem, hogy küldjenek nekünk hosszúhajókat!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "Hic... Mit akarsz tôlem? Tûnj el, nem akarok veled beszélni.";
			link.l1 = "Ön "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "De igen, az vagyok. És mi a dolgod?";
			link.l1 = "Elég egyszerû. Van valaki a városban, akinek elege van a maga trükkjeibôl. Ennek az embernek elege van belôlük. Most ránézek magára, és látom, hogy miért. Soha többé ne jelenjen meg a helyi bordélyházban, különben bajba kerül. Megértetted?";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "Argh! Te... meg mersz fenyegetni, te barom? A pengémre szegezlek és megsütlek, mint egy csirkét a nyárson!";
						link.l1 = "Készülj fel, köcsög!";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "Mi van? Mi van? Milyen trükkök? Nem volt semmilyen trükk. Berúgtam, és egy párszor a bordélyházban iszogattam. Senki sem tökéletes... Jól van, jól van, jól van... Soha többé nem veszem igénybe a szolgáltatásaikat. Most már elégedett? A szavamat adom.";
						link.l1 = "Remélem, hogy a becsületszavad jelent valamit neked, és tisztában vagy a következményekkel, ha megszeged. Ezt tartsd észben. Viszontlátásra.";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "Maga egy szemtelen ember, uram! Esküszöm, hogy még napnyugta elôtt megbánja a szavait. Kihívlak! Azt hiszem, jobb, ha négyszemközt harcolunk, valahol nyugodtan. A dzsungel jó lesz, találkozzunk ott két óra múlva!";
					link.l1 = "Remek ötlet! Legalább nem lenne gond elrejteni a holttestedet.";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "Micsoda? - Nem, nem, nem. Milyen trükkök? Nem volt semmilyen trükk. Lerészegedtem, és néhányszor a bordélyházban tomboltam. Senki sem tökéletes... Jól van, jól van, jól van... Soha nem fogom igénybe venni a szolgáltatásaikat. Most már elégedett vagy? A szavamat adom.";
					link.l1 = "Remélem, hogy a becsületszavad jelent valamit neked, és tisztában vagy a következményekkel, ha megszeged. Ezt tartsd észben. Viszontlátásra.";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "Várj! Állj! Megadom magam! Kíméljen meg!";
			link.l1 = "És most így beszélsz!";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "Könyörgöm, kíméljen meg! Megteszem, amit kérsz! Soha nem megyek be abba a bordélyházba!";
			link.l1 = "Ez a póz csak egy olyan söpredékhez illik, mint te. Remélem, hogy ez egy lecke lesz számodra egész életedre. És viselkedj rendesen ebben a városban.";
			link.l1.go = "Badboy_exit";
			link.l2 = "Persze, hogy nem fogsz. A csalásodnak itt és most véget vetünk.";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "Ideje, hogy a pokolba menj, te rohadék! Imádkozz magadért, de gyorsan, nincs egy egész rohadt napom...";
			link.l1 = "Kevesebb beszéd, több harc, söpredék!";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "És ott van ez a szemtelen fattyú! Mutassuk meg neki, kié ez a város, fiúk!";
			link.l1 = "Ah, milyen degenerált vagy! De én figyelmeztettelek. Téged és a majmaidat egy percen belül a pokolba küldelek!";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "Üdvözletem. Mit akarsz?";
			link.l1 = "Nem "+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Nem fogsz hinni nekem, ha-ha. A fejedet akarom.";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "Hm... Nem... Semmiség. Úgy tûnik, tévedtem. Bocsáss meg, hogy zavarlak.";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "Micsoda ostoba vicc, uram! Magyarázza meg, vagy én...";
			link.l1 = "És mit fogsz csinálni, te nyomorult hering? Rosszat tettél egy jó emberrel, és ô nagyon feldúlt. Imádkozz hát most, és tedd gyorsan, mert sietek.";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "Mit... mit csinálsz, uram! Segítség! Valaki segítsen! Gyilkos!";
			link.l1 = "És én még azt hittem, hogy az utolsó másodperceidet imádkozással töltöd, legalább az égig érhettél volna...";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "Már megint te? Miért nem mondtad meg, hogy mit akarsz?";
			link.l1 = "Semmit.";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "Ah?! Mi az? Mi a fenét keresel itt, te átkozott? Ki engedte be magát?";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "A ligának szüksége van az életére, kapitány...";
			link.l1 = "Mi van? - Nem tudom. Bassza meg!";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én ennek a városnak a polgára vagyok, és arra kérem, hogy tegye hüvelybe a pengéjét.", "Figyelj, én ennek a városnak a polgára vagyok, és arra kérnélek, hogy tedd hüvelybe a pengédet.");
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Persze...");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, "+ GetSexPhrase("haver","lány") +", miközben fegyverrel futsz. Tudok ideges lenni...", "nem szeretem, ha olyan "+ GetSexPhrase("férfiak vannak, akik","emberek, akik") +" fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
				link.l1 = LinkRandPhrase("Megvan.", "Minden rendben.", "Ne aggódj...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
