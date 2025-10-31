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
				dialog.text = "Was willst du? Ah, du nimmst an der Regatta teil! Liege ich richtig?";
				link.l1 = "Genau, Herr. Ich muss mich hier gemäß den Regeln registrieren.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Art von Fragen?","Was willst du, "+GetAddress_Form(NPChar)+"?"),"Du hast bereits versucht, mir eine Frage zu stellen "+GetAddress_Form(NPChar)+"...","Sie sprechen heute zum dritten Mal über eine bestimmte Frage...","Schau, wenn du mir nichts über die Angelegenheiten des Hafens zu erzählen hast, dann belästige mich nicht mit deinen Fragen.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe nichts zu besprechen."),"Macht nichts.","Tatsächlich, schon das dritte Mal...","Es tut mir leid, aber ich interessiere mich momentan nicht für die Angelegenheiten des Hafens.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ich segle nach Blueweld, um Paprika zu verkaufen. Sag mir, Herr, haben Sie Passagiere, die nach Blueweld fahren? Oder zumindest nach Port-Royal. Es wäre großartig, etwas Geld von einem Passagier zu bekommen, es könnte helfen, den Lohn der Crew zu bezahlen. Ich habe ihn bereits auf ein Minimum reduziert, aber diese faulen Schweine verlangen immer noch Geld...";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "Es gab eine Galeone namens 'Admirable', die in Philipsburg unter dem Kommando von Gaius Marchais beladen wurde. Er sollte eine Ladung Paprika hierher liefern. Können Sie mir helfen, diesen Kapitän zu finden?";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "Ich wollte nach einer Xebek mit einem seltsamen Namen fragen.";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "Ich habe gehört, dass eine Xebec, die einem Kapitän Jack... oder Jackson gehört, oft Ihren Hafen besucht. Könnten Sie mir sagen, wo ich ihn suchen soll?";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "Leider gibt es keine Passagiere nach Blueweld oder Port-Royal. Komm morgen oder übermorgen wieder.";
			link.l1 = "Schade. Auf Wiedersehen dann.";
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
				dialog.text = "Hm... Sie haben die Regeln der Regatta gebrochen und ich muss Sie disqualifizieren. Es tut mir leid. Sie nehmen an der nächsten Reise nicht teil. Ich habe bereits eine Depesche nach Port-Royal vorbereitet.";
				link.l1 = "Eh... was für ein Jammer! Aber ich kann hier nichts tun, Sie waren zu wachsam. Auf Wiedersehen!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "Vielleicht ist es Ihnen, Kapitän, aufgefallen, dass die Stadt belagert wird. Wir erwarten jeden Moment einen Angriff der Spanier und mobilisieren unsere Kräfte. Aber die Regatta geht trotzdem weiter\nLassen Sie uns registrieren: Kapitän "+GetFullName(pchar)+", Schiff ist - "+pchar.Ship.Name+"... Regatta's Zeit in Stunden ist "+sti(pchar.questTemp.Regata.FourthTransitionTime)+". Fertig, Ihr Ergebnis ist registriert, Sie können Ihren Weg fortsetzen.";
				link.l1 = "Sag mir meinen Rang.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Sie sind hier, aber ich sehe Ihr Schiff nicht. Wo ist es?";
			link.l1 = "Es tut mir leid, Herr. Ich werde mein Schiff sofort in den Hafen verlegen.";
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
			dialog.text = "Ach, ja... Es tut mir leid, ich war zu beschäftigt dafür. Du bist der Erste.";
			link.l1 = "Ich verstehe. Danke für Ihre Informationen.";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Ach, ja... Es tut mir leid, ich bin dafür zu beschäftigt. Du bist der Letzte.";
				link.l1 = "Ich verstehe. Danke für Ihre Information.";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
				}
				else
				{
					if (n==2)
					{
						dialog.text = "Ach, ja... Es tut mir leid, ich bin zu beschäftigt dafür. Du bist der Zweite. Es gibt nur einen Kapitän, der dich überholt. Sein Name ist "+sName+" auf dem Schiff "+sShip+".";
						link.l1 = "Ich verstehe. Danke für Ihre Informationen.";
						link.l1.go = "exit";
						AddQuestRecord("Regata", "23");
					}
					else
					{
						dialog.text = "Ach, ja... Es tut mir leid, ich bin zu beschäftigt dafür. Ihr Rang ist "+n+" . Ihr nächster Gegner ist "+sName+" auf dem Schiff "+sShip+".";
						link.l1 = "Ich verstehe. Danke für Ihre Informationen.";
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
			dialog.text = "Ja, diese Galeone war hier, wurde ihrer Güter entledigt und hat unseren Hafen später verlassen. Informationen über ihr Ziel... hm... nichts, es gibt nichts. Es tut mir leid, aber ich kann nichts tun.";
			link.l1 = "Ich verstehe. Schade... Ich werde weiter danach suchen.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Herr, ich brauche den genauen Namen des Schiffes. Wir haben tonnenweise Jacks und Jacksons, die unseren Hafen durchqueren. Also, wie lautet der Name?";
			link.l1 = "Sirene."; 
			link.l1.go = "caleuche_wrong_name";
			link.l2 = "Lamia."; 
			link.l2.go = "caleuche_wrong_name";
			link.l3 = "Harpyie."; 
			link.l3.go = "caleuche_name";
			link.l4 = "Furie."; 
			link.l4.go = "caleuche_wrong_name";
			link.l5 = "Das Problem ist, dass ich den Namen seiner alten Prahme nicht kenne. Es ist seltsam, eine Vogelfrau, geboren...";
			link.l5.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Herr, erzählen Sie Ihre Geschichten und Rätsel in der Taverne, wir haben hier ein ernsthaftes Etablissement. Entweder Sie nennen mir den Namen dieser Xebec, oder Sie hören auf, mich bei meiner Arbeit zu stören.";
			link.l1 = "In Ordnung, ich werde versuchen, es herauszufinden.";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "So? Haben Sie den Namen des Schiffes? Ich höre zu.";
			link.l1 = "Sirene."; 
			link.l1.go = "caleuche_wrong_name";
			link.l2 = "Lamia."; 
			link.l2.go = "caleuche_wrong_name";
			link.l3 = "Harpyie."; 
			link.l3.go = "caleuche_name";
			link.l4 = "Furie."; 
			link.l4.go = "caleuche_wrong_name";
			link.l5 = "Ich muss noch etwas nachdenken.";
			link.l5.go = "exit";
		break;
		
		case "caleuche_name":
			dialog.text = "'Harpy'? Natürlich kenne ich diese Xebec. Ihr Kapitän ist Reginald Jackson. Aber er war lange nicht in Bridgetown. Ich habe gehört, dass er jetzt für die Niederländische Westindien-Kompanie arbeitet. Also sollten Sie ihn in Willemstad suchen.";
			link.l1 = "Vielen Dank! Sie haben mir sehr geholfen.";
			link.l1.go = "caleuche_3";
			DelLandQuestMark(npchar);
		break;
		
		case "caleuche_wrong_name":
			dialog.text = "Es tut mir leid, aber das sagt mir nichts. Sind Sie sicher, dass Ihr Kapitän jemals hier in Bridgetown war?";
			link.l1 = "Ich bin sicher. Nun, vielleicht fällt mir etwas ein ...";
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
