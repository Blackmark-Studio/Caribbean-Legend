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
			dialog.text = "Was willst du?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche Informationen.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "Hallo, Kapitän! Ja, du. Komm her, ich habe ein Angebot für dich...";
					link.l1 = "Und was ist das Geschäft?";
					link.l1.go = "passenger";
					link.l2 = "Ich habe es eilig, Freund. Vielleicht das nächste Mal.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("He, Kapitän, ich bin eigentlich beschäftigt. Was brauchst du?","Was wünschen Sie, Kapitän?","Cap'n, ich bin nicht in der Stimmung zu reden. Was willst du?");
				link.l1 = "Grüß dich, "+GetAddress_FormToNPC(NPChar)+". Warte mal, ich möchte, dass du mir etwas erzählst.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche Informationen.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Es ist nichts, ich bin auf dem Weg zur Taverne...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "Hm. Du bist der Kapitän eines Schiffes, aber du siehst nicht aus wie ein Händler. Es scheint, als hättest du einige Münzen in deiner Tasche... Wie wäre es mit einigen interessanten Informationen im Austausch für eine Handvoll Dublonen?";
				link.l1 = "Zuerst beweise, dass deine Informationen einen einzigen Acht-Reales-Stück wert sind.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "Es ist so, Kapitän, es ist so. Es kostet viel mehr als ich verlange. Du gibst mir das Gold und ich sage dir wann und auf welchem Schiff eine bestimmte sehr wichtige Person segeln wird. Du wirst diese Person für einen sehr guten Preis erpressen können... Ich verrate dir sogar den Namen des Käufers. Abgemacht?";
				link.l1 = "Unmöglich! Ich bin kein Entführer. Zieh Leine!";
				link.l1.go = "exit_quest";
				link.l2 = "Und wie kann ich wissen, dass du die Wahrheit sagst?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "Es wäre äußerst unklug, dich zu betrügen, Seehund. Ich lebe in dieser Stadt und brauche die Schwierigkeiten nicht. Nur für "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" Für Dublonen gebe ich vollständige Informationen. Du wirst viel mehr verdienen.";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Du hast recht. Nimm das Gold und fang an zu reden.";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Ich habe jetzt nicht genug Münzen bei mir.";
				link.l2.go = "passenger_3";
				link.l3 = "Bist du bei Sinnen? Echtes Gold für leere Versprechungen bezahlen? Verschwinde...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "Tust du nicht? Gut, Kapitän. Ich kann noch ein paar Tage warten und diese Information auch. Finde mich, wenn du dein Gold hast. Es wird nicht schwer sein, mich zu finden... heute, ha-ha-ha!";
				link.l1 = "Zeig nicht so deine Zähne. Gut, ich bringe dir das Gold... wenn ich meine Meinung nicht ändere. ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "Hast du mein Gold mitgebracht?";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Ja. Nimm es. Versuche nicht einmal jetzt zu lügen...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Noch nicht. Vielleicht später...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
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
				dialog.text = "Behalte dein Pulver trocken, du wirst es bald brauchen, Käpt'n. Nun hör zu, in "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+" ein Schiff wird von unserer Kolonie wegfahren, das Schiff ist "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" genannt '"+pchar.GenQuest.Marginpassenger.ShipName+"' und es wird in Richtung "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+". Es wird einen Passagier geben -  "+pchar.GenQuest.Marginpassenger.Text+", genannt "+pchar.GenQuest.Marginpassenger.q1Name+"\nDer Kapitän "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")+"Geschlecht"))+" ist ein gelbbauchiger Feigling wie alle Händler, ha-ha-ha! Vielleicht wirst du sogar jeden Kampf vermeiden. Jag ihm einfach die Angst des Teufels ein und er sollte das Ziel selbst übergeben, he-he\nWie du verstehst, "+pchar.GenQuest.Marginpassenger.Text1+", du wirst wahrscheinlich deine Münzen bekommen, ja, aber danach werden dich die örtlichen Behörden bis zum Tod jagen. Du solltest deine Beute besser zu "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+". Dort findest du einen Mann namens "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" und du musst nicht einmal deinen Namen nennen. Es liegt an dir, wo du deinen Mann auslösen willst, aber beiß nicht mehr ab, als du kauen kannst... Aber "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+" Dublonen kannst du sicher verlangen. Verstanden?";
				link.l1 = "Ja. Ich werde auf mein Schiff zurückkehren und es ins Logbuch schreiben.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "Genau! Richtige Wahl. Gut, Kapitän, viel Glück bei dieser leichten Aufgabe. Ach ja, ich hätte es fast vergessen: "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" wird nicht vom Hafen aus segeln, sondern von einer der nahegelegenen Buchten. Also pass auf. Viel Glück und danke für das Gold!";
				link.l1 = "Bitte sehr. Gib nicht alles in einer Nacht aus.";
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
			dialog.text = NPCharSexPhrase(NPChar,"Hör zu Kumpel, beruhige dich und stecke deine Waffe weg.","Hör zu, Kumpel, beruhige dich und stecke deine Waffe weg.");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du wünschst.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("Rede nicht um den heißen Brei herum, Käpt'n. Sag, was du willst!","Oh, gut. Was willst du?","Fragen? Gut, Seemann, ich höre zu.");
			link.l1 = LinkRandPhrase("Können Sie mir das neueste Gerede erzählen?","Ist hier in letzter Zeit etwas Interessantes passiert?","Was geht in der Karibik vor?");
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
				pchar.GenQuest.Marginpassenger.Text = "store keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's daughter";
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
				pchar.GenQuest.Marginpassenger.Text = "trader's relative, shipmaster's";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's relative";
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
