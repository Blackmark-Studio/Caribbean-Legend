// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Art von Fragen?","Was willst du, "+GetAddress_Form(NPChar)+"?"),"Du hast mir schon eine Frage gestellt "+GetAddress_Form(NPChar)+"...","Sie sprechen heute zum dritten Mal über irgendeine Frage...","Schau, wenn du mir nichts über die Hafenangelegenheiten zu sagen hast, dann belästige mich nicht mit deinen Fragen.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe nichts zu besprechen."),"Macht nichts.","Tatsächlich, schon das dritte Mal...","Entschuldigung, aber ich interessiere mich momentan nicht für die Angelegenheiten des Hafens.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Guten Tag. Ich würde gerne wissen, wo Kapitän Francois Gontier ist. Ich habe eine wichtige Angelegenheit.";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "Ich bin ein Kaufmann, ich komme aus Caracas, und Ihr Kollege von der örtlichen Hafenbehörde hat mich gebeten, Ihnen einige Korrespondenz zu übergeben ...";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "Ja, ich bin für die Zahlung.";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;

		case "Portobello_ratP_1":
			dialog.text = "Eine wichtige Angelegenheit sagst du? Lass uns sehen. Nun... Francois Gontier, in der Korvette '"+pchar.questTemp.Slavetrader.ShipName+"'... Nach meinen Notizen, war Senor Gontier auf dem Weg nach Jamaika.";
			link.l1 = "Danke! Du hast sehr geholfen!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// на пару с Акулой -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "Ach, endlich! Sie sagen, Sie sind ein Händler? Wieder versuchen sie, Geld bei Kurieren zu sparen und die Lieferung bis zur letzten verdammt... Ja, sicher! Das ist wahr. Und so soll ich in so einem Zeitrahmen die Staffel damit ausrüsten?...";
			link.l1 = "Klingt unverantwortlich...";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Das ist eine Möglichkeit, es auszudrücken! Nun, gut, was soll man machen. Wir werden Sie rechtzeitig treffen... Ich spreche von meiner, achten Sie nicht darauf. Hören Sie, kehren Sie zufällig zurück?";
			link.l1 = "Nun, eigentlich wollte ich hier Waren verkaufen und dann - ja, zurück nach Caracas ...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Großartig! Jetzt werde ich ihnen eine Antwort schreiben und Sie bitten, sie zurückzusenden. Also... Bitte liefern Sie sie innerhalb von zehn Tagen, sonst werden sie keine Zeit haben, rechtzeitig etwas zu tun... Und nennen Sie Ihren Namen.";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "Mein Name ist "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "Mein Name ist Andreas Garcia.";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "Warte eine Minute... Aufgenommen. Hier, bitte. Denken Sie daran: zehn Tage! In der Zwischenzeit werde ich genauer lesen, was Sie mir gebracht haben.";
			link.l1 = "Ja, ich erinnere mich. Auf Wiedersehen!";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "Warte mal... Ich verstehe nicht... Noch einmal, wie sagten Sie war Ihr Name?";
			link.l1 = "Ich?.. Nun... Warum ist das so wichtig?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			dialog.text = "Es ist sehr wichtig! Es heißt... Also... "+n+" "+month+"... Nein, das ist es nicht... 12, 50, 69, 55... Aber wo ist es... Ah, hier ist es! Der Brief muss vom Kapitän zugestellt werden "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+". Und Sie sagten, Ihr Name ist... "+GetFullName(pchar)+"?";
			link.l1 = "Es muss ein Missverständnis vorliegen...";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "Nein, es kann keinen Fehler geben. Gib mir den Brief zurück, den ich dir gegeben habe. Ich muss das herausfinden!";
			link.l1 = "Komm schon... Ich werde es liefern, alles wird in Ordnung sein.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Nein! Gib mir den Brief zurück! Wachen!!!";
			link.l1 = "Ach, du willst es also auf die harte Tour machen, hm?";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			if (CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				TakeNationLicence(HOLLAND);
				log_info("Trading license cancelled!");
			}
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "Warte einen Moment... Da haben wir es. Dann werde ich deinen Namen in einem Antwortbrief niederschreiben. Hier, bitte. Denke daran: du hast zehn Tage! In der Zwischenzeit werde ich genauer lesen, was du mir gebracht hast.";
			link.l1 = "Ja, ich erinnere mich. Auf Wiedersehen!";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "Bezahlung?..";
			link.l1 = "In Caracas hat mir Ihr Kollege gesagt, dass Sie für die Zustellung des Briefes zahlen würden.";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Nein, also, die sind dort völlig verrückt! Jetzt muss ich für sie bezahlen!";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Und wie viel haben sie dir versprochen?";
			link.l1 = "Fünftausend Pesos.";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "Zehntausend Pesos.";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "Anscheinend haben sie beschlossen, auf meine Kosten dort zu leben... Nicht nur, dass sie kein Geld für Kuriere ausgeben wollen und solche Fälle vorübergehenden Handelsschiffen anvertrauen, sie hängen auch die Kosten an mich! Ich werde eine Beschwerde gegen sie in Havanna einreichen!";
			link.l1 = "Ich verstehe Ihre Entrüstung, senor, aber was soll ich tun?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "Anscheinend haben sie beschlossen, auf meine Kosten dort zu leben... Nicht nur, dass sie kein Geld für Kuriere ausgeben wollen, solche Fälle an vorbeifahrende Handelsschiffe anvertrauen, sie hängen auch die Ausgaben an mich! Ich werde eine Beschwerde gegen sie nach Havanna schreiben!";
			link.l1 = "Ich verstehe Ihre Empörung, mein Herr, aber was soll ich tun?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Argh, du bist nicht schuld an der Gier der Beamten aus Neuspanien in Caracas. Aber ich habe gerade nicht so viel Geld bei mir. Und das Budget sollte erst morgen kommen ... Warte bitte hier, ich gehe jetzt zum Geldverleiher - und ich komme gleich zurück.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "Es tut mir leid für die Wartezeit. Hier sind Ihre "+makeint(pchar.questTemp.SharkGoldFleet)+" Stücke von Acht. Und in diesem Fall werden sie selbst für die Antwort in Caracas bezahlen. Sag mir, dass ich es getan habe.";
			link.l1 = "Gut, ich werde es weitergeben. Danke und viel Glück!";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
