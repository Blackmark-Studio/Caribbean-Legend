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
			dialog.text = "Egy bogár. Feltétlenül szólj a fejlesztôknek.";
			link.l1 = "OK";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "Üdvözletem, kapitány. Akarsz tôlem valamit?";
			link.l1 = "Igen. Pontosan, "+GetAddress_FormToNPC(NPChar)+". Van egy utas a hajóján, aki nagyon érdekel. A neve "+pchar.GenQuest.Marginpassenger.q1Name+". Azt akarom, hogy az ön utasa az én utasom legyen. Ha önnek ez megfelel, akkor elválnak útjaink, és soha többé nem látjuk egymást.";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "Így van? És mi van, ha nemet mondok?";
			link.l1 = "Akkor kénytelen leszek néhány sortûzzel a fegyverembôl, amely ebben a pillanatban éppen felétek irányul, rávenni titeket, hogy gondoljátok át a döntéseteket. Ne kérdôjelezze meg a szerencséjét, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (7-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (7-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "Akkor nincs más választásom. A legénységem sorsa értékesebb számomra, mint egy ember sorsa. De ezt nem úszod meg csak úgy! Nem fogom elfelejteni!";
				link.l1 = "Nyugodj meg, és mentsd meg magad a szívrohamodtól... Hozd ide az új utasomat!";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "Jobb, ha elhagyja a hajómat, uram, amíg még megengedem. Ne próbáljon megijeszteni. És ne merészelje megtámadni a hajómat, különben azonnal visszavertetem. Tûnjön el, amíg még jó kedvem van!";
				link.l1 = "Figyelmeztettelek. Úton vagyok. Hamarosan találkozunk, "+GetAddress_FormToNPC(NPChar)+"!";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "Már beszéltünk, emlékszel? Tûnj el a hajómról!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "Argh, te szemétláda! Égj a pokolban a tetteidért!";
				link.l1 = "Felajánlottam neked, hogy békésen átadod nekem az utast... és te visszautasítottad az ajánlatomat. Most már csak te vagy a hibás!";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "Argh, te szemétláda! Miért támadtad meg a békés hajót? Nincs nálunk arany vagy értékes áru!";
				link.l1 = "De van egy értékes ember a fedélzeten..."+pchar.GenQuest.Marginpassenger.q1Name+". Az utasát akarom.";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "Te... vagy a mocskos kalóz!";
			link.l1 = "Kevesebb beszédet, barátom...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "És ezért követtél el mészárlást a hajómon? Sok ember meghalt! Kalóz!";
			link.l1 = "Kevesebb beszédet, barátom...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "Mit akarsz, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Ön "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "Igen, én vagyok az. Akarsz jelentkezni? Akkor tudnod kell, hogy...";
			link.l1 = "Várjon egy percet, uram. Nekem egy kicsit másfajta alkalmazásom van... Ismer egy "+pchar.GenQuest.Marginpassenger.q1Name+"nevû személyt?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "Igen, ismerem... Persze, hogy ismerem! Mi a baj?";
					link.l1 = "Egy igen kellemetlen történetbe keveredett: a hajóját kalózok fogták el. Szerencsére volt alkalmam felszállni a hajójukra és megmenteni szegényt. Megmondta a nevedet, és itt vagyok.";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "Igen, nagyon jól ismerem ezt az embert. Mi a baj?";
					link.l1 = "Kellemetlen történetbe keveredett: hajóját kalózok fogták el. Szerencsére volt alkalmam a hajójukra szállni, és megmenteni ezt a foglyot. Megmondta a nevedet, és itt vagyok.";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "Ó, Istenem! Hol van most? Miért nem hoztad ide?";
			link.l1 = "Biztonságban van. És ami a kérdésedet illeti... ez nem ilyen egyszerû. Én magam is hazavihettem volna, de ezt a lehetôséget neked adom. Természetesen szerény összegért.";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "Hm... nem értem...";
			link.l1 = "Miért nem érti? Fizetsz nekem aranyban, én odaadom neked a lányt, te pedig a saját érdekedben használhatod ezt a helyzetet... El akarod venni feleségül, igazam van? Én pedig megjavítom a hajómat azokból az érmékbôl, ami megsérült a kalózokkal való harcban.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "Ó, Istenem! Hol van most? Miért nem hoztad ide?";
			link.l1 = "Biztonságban van. És a kérdéseddel kapcsolatban... ez nem ilyen egyszerû. Én magam is hazavihettem volna, de ezt a lehetôséget neked adhatom, tekintettel arra, hogy a családja érdekeltségi körébe tartozik. Természetesen szerény összegért.";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "Hm... nem értem...";
			link.l1 = "Miért nem teszed meg? Aranyban fizetsz nekem, én pedig átadom neked a barátodat, és te a saját érdekedben használhatod ezt a helyzetet. Van néhány információm, tudja... Megjavítom a hajómat azokból az érmékbôl, megsérült a kalózokkal való harcban.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "Nocsak, nocsak... és mennyit akarsz?";
			link.l1 = "Vegye figyelembe, hogy dublont akarok, nem pezót.";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "Rendben, rendben... Szóval, hány dublont akarsz?";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "Nagyon vicces. Rendben, tegyünk úgy, mintha a vicce vicces lenne. Viszontlátásra!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "Rendben, egyetértek. Rendelkezem a szükséges összeggel. Hol van a "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "Mostanra már a mólón kell lennie. Akkor menj és hozd el az utast.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "Sajnálom, de nincs ennyi dublonom. A pezó is megteszi?";
				link.l1 = "Én dublont szeretnék, de gondolom, a hajóparancsnok elfogadja a pesót... Adja ide.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "Nem, csak dublont kérek.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "Sajnos nincs nálam ennyi pénz. Szóval nem tudom elfogadni az ajánlatát, még akkor sem, ha minden vágyam az lenne.";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "Uram, érti egyáltalán, hogy mirôl beszél? Tudja, hogy ez az összeg túl nagy? Takarodj innen a pokolba!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "Hát... Uram, el kell mennie az orvoshoz, méghozzá azonnal. Úgy tûnik, hogy nagyon magas láza van, vagy... mindenképpen orvosra van szüksége. És én túl elfoglalt vagyok. Viszontlátásra!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "Itt van, a teljes összeg pezó, csak amit akartál... Hol van a "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "Mostanra már biztos a mólón van. Akkor menj, és hozd el az utast...";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*100;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "Akkor nem fogadhatom el az ajánlatát, még akkor sem, ha minden vágyam az, hogy ezt tegyem. Viszontlátásra!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "Mi a... Mi folyik itt?!";
			link.l1 = "Ez nagyon egyszerû, "+NPCharSexPhrase(NPChar, "pal","lány")+". Most már te vagy a kedves utasom. Egy ôrzött utas. Ne próbálj ellenállni, különben a raktérben végzed.";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "Úgy érted, hogy a foglyod vagyok?";
			link.l1 = "Ó, nem. Persze, hogy nem. Nem fogoly, hanem kedves vendég. Egy nagyon értékes vendég...";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "Maga... meg fog fizetni a tetteiért!";
			link.l1 = "Már megint tévedsz,"+NPCharSexPhrase(NPChar, ", pajtás",", kedves")+". Nem fogok fizetni, de fizetni fogok. Elég a dumából, menj a kabinodba!";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
