//Jason общий диалог уличных контриков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Lenne egy kérdésem hozzád.", "Információra van szükségem.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "Hé, kapitány! Igen, te. Gyere ide, van egy ajánlatom a számodra...";
					link.l1 = "És mi az alku?";
					link.l1.go = "passenger";
					link.l2 = "Sietek, barátom. Talán legközelebb.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hé, kapitány, igazából elfoglalt vagyok. Mire van szüksége?","Mit akar, kapitány?","Kapitány, nincs kedvem beszélgetni. Mit akar?");
				link.l1 = "Üdvözlet, "+GetAddress_FormToNPC(NPChar)+". Várj egy percet, szeretném, ha elmondanál valamit.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Lenne egy kérdésem önhöz.", "Információra van szükségem.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Semmiség, a kocsmába tartok...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "Hm. Te egy hajó kapitánya vagy, de nem úgy nézel ki, mint egy kereskedô. Úgy néz ki, mintha lenne néhány érme a zsebedben... Mi lenne, ha egy maréknyi dublonnáért cserébe kapnánk néhány érdekes információt?";
				link.l1 = "Elôször is, bizonyítsd be, hogy az információd megér egy darab pesot.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "Így van, kapitány, így van. Sokkal többe kerül, mint amennyit kérek. Te ideadod az aranyat, én pedig megmondom, mikor és melyik hajón hajózik egy bizonyos nagyon fontos személy. Nagyon jó pénzért váltságdíjat tudsz majd érte kérni... Még a vevô nevét is megmondom. Megegyeztünk?";
				link.l1 = "Szó sem lehet róla! Nem vagyok emberrabló. Húzzon el!";
				link.l1.go = "exit_quest";
				link.l2 = "És honnan tudjam, hogy igazat mondasz?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "Nem lenne bölcs dolog becsapni téged, tengeri kutya. Én ebben a városban élek, és nincs szükségem a bajra. Csak "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" dublonokért teljes körû tájékoztatást adok. Sokkal többet fogsz keresni.";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Igazad van. Fogd az aranyat és kezdj el beszélgetni.";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Most nincs nálam elég érme.";
				link.l2.go = "passenger_3";
				link.l3 = "Most viccelsz velem? Igazi aranyat fizetsz üres ígéretekért? Tûnj el...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "Nem igaz? Rendben, sapka. Tudok még várni néhány napot, és ez az információ is. Keress meg, ha megkapod az aranyadat. Nem lesz nehéz megtalálni engem... ma, ha-ha-ha-ha!";
				link.l1 = "Ne mutogasd így a fogaidat. Rendben, elhozom neked az aranyat... ha nem gondolom meg magam. ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "Elhoztad az aranyamat?";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Igen. Vedd el. Ne is próbálj hazudni...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Még nem. Talán késôbb...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveDublonsFromPCharTotal(sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+hrand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = "Tartsd szárazon a puskaport, hamarosan szükséged lesz rá, sapka. Most figyelj, a "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+" egy hajó fog elhajózni a kolóniánkról, a hajó neve "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Neve")))+" név '"+pchar.GenQuest.Marginpassenger.ShipName+"' és a "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+"felé fog tartani. Lesz egy utas -  "+pchar.GenQuest.Marginpassenger.Text+", név "+pchar.GenQuest.Marginpassenger.q1Name+"\nA kapitány "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Név")+"Gen"))+" egy sárgahasú gyáva, mint minden kereskedô, ha-ha-ha! Talán még a harcokat is elkerüli. Csak ültessétek belé az ördögtôl való félelmet, és ô maga adja át a célpontot, ô-ô\nAmint értitek, "+pchar.GenQuest.Marginpassenger.Text1+", valószínûleg megkapjátok az érméteket, igen, de a helyi hatóságok utána halálra fognak vadászni titeket. Jobb, ha a zsákmányt a "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+". Ott találsz majd egy "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" nevû embert, és még a nevedet sem kell megmondanod. A te döntésed, hogy hol váltságdíjat kérsz az emberedért, de ne harapj le többet, mint amennyit meg tudsz rágni... De "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+" dublont biztosan kérhetsz. Megvan?";
				link.l1 = "Igen. Visszamegyek a hajómra és beírom a naplóba.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "Pontosan! Helyes választás. Rendben, sapka, sok szerencsét ehhez a könnyû feladathoz. Ó, igen, majdnem elfelejtettem: "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "név")))+" nem a kikötôbôl, hanem az egyik közeli öbölbôl fog kihajózni. Szóval vigyázzatok. Sok sikert és köszönöm az aranyat!";
				link.l1 = "Szívesen. Ne költsd el az egészet egy éjszaka alatt.";
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Figyelj, pajtás, nyugodj meg, és tedd el a fegyvered.", "Figyelj pajtás, nyugodj meg és tedd hüvelybe a fegyvered.");
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy kívánod.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("Ne kerülgesse a forró kását, kapitány. Mondd, amit akarsz!","Ó, rendben. Mit akarsz?","Kérdések? Rendben, matróz, hallgatlak.");
			link.l1 = LinkRandPhrase("Elmondanád a legfrissebb pletykákat?","Történt itt mostanában valami érdekes?","Mi történik a Karib-tengeren?");
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (hrand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "He wants to marry her and will pay a significant sum for the girl.";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "A boltos lánya";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "a hajógyári mester lánya";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "a kocsmáros lánya";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "bankár lánya";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "a kikötômester lánya";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "He has been planning to ingratiate himself with this family and he will pay a lot for the prisoner ";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "kereskedô rokona, hajóparancsnok lánya";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "hajógyári mester rokona";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "kocsmáros rokona";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "bankár rokona";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "kikötômester rokona";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
