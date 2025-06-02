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
				dialog.text = "Was willst du? A-ha, du bist der Teilnehmer der Regatta! Liege ich richtig?";
				link.l1 = "Genau, Herr. Laut den Regeln muss ich mich hier registrieren.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Art von Fragen?","Was willst du, "+GetAddress_Form(NPChar)+"?"),"Du hast schon versucht, mir eine Frage zu stellen "+GetAddress_Form(NPChar)+"...","Du sprichst heute zum dritten Mal über eine Frage...","Schau, wenn du mir nichts über die Hafenangelegenheiten zu sagen hast, dann belästige mich nicht mit deinen Fragen.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe nichts zu besprechen."),"Macht nichts.","Tatsächlich, schon das dritte Mal...","Entschuldigung, aber ich habe momentan kein Interesse an den Angelegenheiten des Hafens.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "Ich habe gehört, dass ein Attentat auf Sie verübt wurde und Sie versuchen, den Angreifer zu finden?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "Der Mann, der Ihr Leben bedrohte, ist tot, Herr "+npchar.lastname+". Sie sind nicht länger in Gefahr.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
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
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Hm... Sie haben die Regeln der Regatta gebrochen und ich muss Sie disqualifizieren. Es tut mir leid. Sie nehmen an der nächsten Reise nicht teil. Ich habe bereits eine Sendung nach Port-Royal vorbereitet.";
			link.l1 = "Ach du meine Güte... wie schade! Aber ich kann hier nichts tun, du warst zu wachsam. Auf Wiedersehen!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "Lassen Sie uns registrieren: Kapitän "+GetFullName(pchar)+", Schiff ist "+pchar.Ship.Name+"... die Regatta-Zeit in Stunden beträgt "+sti(pchar.questTemp.Regata.FirstTransitionTime)+". Fertig, Ihr Ergebnis ist registriert, Sie können Ihren Weg fortsetzen.";
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
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Du bist in Führung. Herzlichen Glückwunsch! Mach weiter so!";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Du bist der Letzte. Du solltest dich beeilen.";
				link.l1 = "Ich bin auf dem Weg!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Du bist der Zweite. Der Anführer ist "+sName+" auf dem Schiff "+sShip+". Ich nehme an, dass du ihm immer noch davonlaufen kannst.";
					link.l1 = "Danke! Ich werde es versuchen!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "Dein Rang ist "+n+". Dein nächster Gegner ist "+sName+" auf dem Schiff "+sShip+".";
					link.l1 = "Danke!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "Es gab tatsächlich ein Attentat, das ist wahr. Was die Ermittlungen betrifft... das ist etwas anders. Ich brauche keinen flüchtigen Verbrecher – ich will seinen Kopf. Nur dann werde ich wieder Ruhe finden.";
			Link.l1 = "Haben Sie eine Ahnung, wer Sie angegriffen hat und warum?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "GS_Portman_2":
			dialog.text = "Ich... Ich weiß nicht, wer er ist! Ich weiß nicht, woher er kam und warum er mich angegriffen hat. Aber eines ist mir klar – er wollte meinen Tod. Und jetzt... jetzt wünsche ich seinen Tod mit derselben Wut! Verstehen Sie mich?\nLassen Sie also Ihre nutzlosen Fragen. Ihre Neugier hilft mir nicht, nur Taten zählen. Zweihundert Dublonen für seinen Kopf – das ist mein Preis. Machen Sie sich auf die Suche oder verschwenden Sie nicht meine Zeit mit leerem Gerede.";
			Link.l1 = "Ich verstehe, dass Angst und Wut Ihren Verstand trüben, und ich verzeihe Ihnen diesen Ton. Aber reißen Sie sich zusammen. Ich sehe keine Schlange von Freiwilligen, die Ihre Probleme lösen wollen, also mäßigen Sie Ihren Eifer. Zweihundert Dublonen sind akzeptabel, aber bevor ich mich der Sache annehme, muss ich alles wissen.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "Ihre Worte sind nur leeres Gerede, und es gibt keine Anhaltspunkte. Jemanden im Dschungel zu suchen, ohne zu wissen, wer es ist – das ist wie die Suche nach einer Nadel im Heuhaufen. Ich werde meine Zeit nicht mit sinnlosen Suchen verschwenden. Viel Glück. Sie werden es brauchen.";
			Link.l2.go = "GS_Portman_End";
		break;

		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;

		case "GS_Portman_3":
			dialog.text = "Ah... Verzeihen Sie, "+GetAddress_Form(NPChar)+", ich bin völlig nervös... Was genau möchten Sie wissen?";
			Link.l1 = "Haben Sie irgendwelche Merkmale bemerkt, die mir helfen könnten, ihn zu identifizieren? War er allein, oder steckt ein mächtigerer Feind hinter ihm? Je mehr Sie mir erzählen, desto schneller können Sie ruhig schlafen.";
			Link.l1.go = "GS_Portman_4";
		break;

		case "GS_Portman_4":
			dialog.text = "Welcher Feind?! Ich habe keine Feinde! Und ich hatte nie welche! Ich tue nichts, was den Tod mitten auf der Straße, am helllichten Tag, verdient\nDieser Schurke... er ist einfach ein verbitterter Wahnsinniger, wie es sie in diesen Kolonialsiedlungen zuhauf gibt\nWas seinen Aufenthaltsort betrifft... ich denke, er versteckt sich im Dschungel. In diesen verfluchten Wäldern kann man sich leicht verirren, aber ich bin sicher – er wird sich zu Grotten oder Buchten begeben, dort kann man sich leichter verstecken\nWas sein Aussehen betrifft, sein Gesicht war mit einem Tuch bedeckt, auf dem Kopf ein Hut, und er trug mehr Waffen als ein königlicher Wachmann. Mehr konnte ich nicht erkennen.";
			Link.l1 = "Nun, es ist nicht viel Information, aber es reicht, um mit der Suche zu beginnen. Ich mache mich sofort auf den Weg. Verstecken Sie das Gold nicht zu weit – ich werde bald zurück sein.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddQuestRecord("GS", "2");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
			
			PChar.quest.GS_Peshera.win_condition.l1 = "location";
			PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
			PChar.quest.GS_Peshera.function = "GS_Peshera";
			locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
			
			PChar.quest.GS_Peshera_pusto.win_condition.l1 = "location";
			PChar.quest.GS_Peshera_pusto.win_condition.l1.location = "Beliz_Cave_2";
			PChar.quest.GS_Peshera_pusto.function = "GS_Peshera_pusto";
		break;
		
		case "GS_Portman_6":
			dialog.text = "Ausgezeichnet, "+GetFullName(pchar)+"! Einfach hervorragend! Sie haben bewiesen, dass Ihre Fähigkeiten unübertroffen sind. Hier ist Ihre Belohnung – zweihundert Dublonen. Bitte nehmen Sie sie an!";
			Link.l1 = "Danke! Aber sagen Sie, haben Sie Grund zu der Annahme, dass der Mörder von einem Ihrer früheren Kunden beauftragt wurde?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;

		case "GS_Portman_7":
			dialog.text = "Frühere Kunden?.. Was für ein Unsinn!.. Ich bin ein ehrlicher Mann, und meine Geschäfte waren immer sauber! Aber da Sie mir geholfen haben, werde ich es Ihnen erzählen. Vor nicht allzu langer Zeit kamen Piraten zu mir\nSie boten mir an, ihnen für Geld Hinweise auf Handelsschiffe zu verkaufen. Ich habe abgelehnt, und sie haben mich mit Drohungen und Flüchen überschüttet, bevor sie gingen. Ich denke, dieser Mörder ist ihr Werk. Sie dulden keinen Widerspruch.";
			Link.l1 = "In diesem Fall passen Sie gut auf sich auf. Wer weiß, wie viele Auftragsmörder diese 'Piraten', wie Sie sie nannten, noch schicken werden. Ich muss mich nun verabschieden – die Geschäfte rufen.";
			Link.l1.go = "GS_Portman_8";
		break;

		case "GS_Portman_8":
			dialog.text = "Warten Sie, Kapitän. Ich möchte mich noch einmal bei Ihnen bedanken. Neben dem Geld haben Sie sich auch meine Gunst verdient. Solange ich hier Hafenmeister bin, können Sie ein beliebiges Schiff so lange Sie wollen mit fünfzig Prozent Rabatt hier lassen. Was halten Sie von diesem Angebot?";
			Link.l1 = "Sehr großzügig von Ihnen! Nochmals vielen Dank!";
			Link.l1.go = "GS_Portman_9";
		break;

		case "GS_Portman_9":
			dialog.text = "Und ich danke Ihnen nochmals für Ihre geleistete Arbeit. Ich bin sicher, dass Ihre Geschäfte weiterhin genauso erfolgreich sein werden wie heute, solange Sie sich nicht von unnötigen Gedanken ablenken lassen. Auf Wiedersehen, Kapitän.";
			Link.l1 = "Auf Wiedersehen.";
			Link.l1.go = "GS_Portman_10";
		break;

		case "GS_Portman_10":
			DialogExit();
			AddQuestRecord("GS", "4");
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_NaemnikMertv");
			pchar.questTemp.GS_BelizSkidka = true;
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
