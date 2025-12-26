int iBenuaPseudoGlobal;

// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "Es ist gut dich zu sehen, mein Sohn. Bist du hier, um deine Schulden zu begleichen?";
				if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
				{
					link.l1 = "Ja, Vater. Ich bin es.";
					link.l1.go = "FastStart_7";
				}
				else
				{
					link.l1 = "Es tut mir leid für die Verspätung, aber ich bin nicht dafür hier. Aber ich werde bald da sein, mach dir keine Sorgen.";
					link.l1.go = "exit";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
			{
				dialog.text = "Gibt es etwas, was du brauchst, mein Sohn?";
				link.l1 = "Ja, Vater. Ich würde gerne meinen Bruder, Michel de Monper, sehen. Er sagte...";
				link.l1.go = "escape";
				break;
			}
			dialog.text = "Gibt es etwas, was du brauchst, mein Sohn?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua"))
			{
				dialog.text = "Hallo, mein Sohn. Ich freue mich, dass du gekommen bist. Ich wollte mit dir sprechen.";
				link.l1 = ""+TimeGreeting()+", Vater. Ich höre.";
				link.l1.go = "SharlieEpilog_Benua_1";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_back"))
			{
				link.l99 = "Ich möchte über meinen Vater sprechen.";
				link.l99.go = "SharlieEpilog_Benua_3";
			}
			//<-- Эпилог
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Ja, Vater. Ich brauche deine Hilfe. Mein Name ist "+GetFullName(pchar)+". Michel de Monper hat mir geraten, mit Ihnen zu sprechen.";
				link.l1.go = "FastStart";
			}
			if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
			{
				link.l1 = "Ja, Vater. Ich brauche deine Hilfe. Mein Name ist "+GetFullName(pchar)+". Mein Bruder, Michel de Monper, hat mir geraten, mit dir zu sprechen.";
				link.l1.go = "meet";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Ja, Vater. Ich brauche ein Schiff, um Michel zu helfen, doch ich bin erst kürzlich in der Karibik angekommen und meine Brieftasche ist leer. Mein Bruder hat mir erzählt, Sie könnten mir etwas Geld leihen...";
				link.l1.go = "FastStart_2";
			}
			//--> Wilde Rose
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua"))
			{
				link.l1 = "Grüß Gott, Vater. Wir brauchen Ihre Hilfe – in einer ziemlich heiklen Angelegenheit.";
				link.l1.go = "WildRose_Abb_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2") && PCharDublonsTotal() >= 800)
			{
				link.l3 = "Vater, ich habe die geforderte Summe. Acht­hundert Gold­dublonen.";
				link.l3.go = "WildRose_Abb_14_pay";
			}
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3"))
			{
				dialog.text = "Willkommen, mein Sohn. Ich nehme an, du bist gekommen, um das Ergebnis deiner... ähm, eurer Angelegenheit zu besprechen?";
				link.l1 = "Ihr seid wie immer scharfsinnig, Vater. Spann uns nicht länger auf die Folter – was konnte euer Mann herausfinden?";
				link.l1.go = "WildRose_Abb_16";
				break;
			}
			//<-- Wilde Rose
			if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
			{
				link.l1 = "Ja, Vater. Ich brauche deine Hilfe.";
				if (CheckAttribute(npchar, "quest.relation_info")) link.l1.go = "help";
				else link.l1.go = "help_start";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l2 = "Ja, Vater. Ich bin es.";
				link.l2.go = "FastStart_7";
			}
			link.l9 = "Nein, nichts, Vater.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Benua_meeting":
			DelLandQuestMark(npchar);
			if(CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
				DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			dialog.text = "Was führt dich zu mir, mein Sohn?";
			link.l1 = "Hallo, Vater. Mir wurde geraten, mit Ihnen zu sprechen. Mein Name ist Charles de Maure. Ich suche nach Michel de Monper. Soweit ich weiß, sollte er irgendwo auf Martinique sein. Ich bin... sein Bruder.";
			link.l1.go = "Benua_meeting_1";			
		break;
		
		case "Benua_meeting_1":
			dialog.text = "Michel de Monpers Bruder? De Maure? Wie merkwürdig...";
			link.l1 = "Ich verstehe deine Zweifel, Vater. Wir haben einfach verschiedene Nachnamen. Mein Vater ist Henri de Monper.";
			link.l1.go = "Benua_meeting_2";			
		break;
		
		case "Benua_meeting_2":
			dialog.text = "A-ah, ich sehe jetzt. Ich kannte Henri de Monper persönlich. Tritt ins Licht, junger Mann. Richtig! Du siehst genauso aus wie er. Die gleichen Blicke, die gleichen edlen Züge! Ich bin froh, einen Sohn von Henri de Monper in unserer Gemeinde zu sehen.\nUnd zu deiner Frage kann ich dir sagen, dass Michel ein hochrangiger Beamter des Malteserordens ist, aber er ist... in Schwierigkeiten. Glücklicherweise besucht mich gerade ein Ritter des Ordens. Ich glaube, er könnte zustimmen, dich zu deinem unglücklichen Bruder zu begleiten, möge der Herr sich seines Schicksals erbarmen...";
			link.l1 = "Wer ist dieser Mann, heiliger Vater?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;		
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}			
		break;
		
		case "Benua_meeting_3":
			DialogExit();
			NextDiag.CurrentNode = "Benua_meeting_repeat";
			AddQuestRecord("Sharlie", "4");
			pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Benua.win_condition.l1.date.hour  = 6;
			pchar.quest.Sharlie_Benua.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Sharlie_Benua.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;
		
		case "Benua_meeting_repeat":
			dialog.text = "Mein Sohn, komm morgen früh wieder. Im Moment habe ich dir nichts mehr zu erzählen.";
			link.l1 = "In Ordnung.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Benua_meeting_repeat";
		break;
		
		/* case "Benua_maltie":
			dialog.text = "Hallo, mein Sohn. Wie versprochen, wartet die Person, von der ich gestern gesprochen habe, bereits auf dich. Er ist bereit, dich zu deinem Bruder zu bringen, der, wie ich gehört habe, elend ist. Möge der Herr seiner Seele gnädig sein...";
			link.l1 = "Wer ist dieser Mann, heiliger Vater?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */
		
		case "escape":
			dialog.text = "Ja, Charles, das ist mir bewusst. Aber ich muss dich enttäuschen. Michel ist nicht hier.";
			link.l1 = "Was meinen Sie, er ist nicht hier? Er sagte, dass er in Ihrer Kirche auf mich warten würde! Vater, was ist passiert? Wo ist mein Bruder?!";
			link.l1.go = "escape_1";
		break;
		
		case "escape_1":
			dialog.text = "Mein Sohn, dein Bruder war hier und hat mein bescheidenes Tabernakel spät gestern Nacht verlassen. Wohin er ging, weiß ich nicht. Aber er hat diesen Brief für dich hinterlassen.";
			link.l1 = "Ich kann es nicht glauben... nach allem, was ich für ihn getan habe! Gib mir diesen Brief!";
			link.l1.go = "escape_2";
		break;
		
		case "escape_2":
			dialog.text = "Lass dich nicht so aufbringen, Charles. Hier ist der Brief. Lies ihn und dann... dann möchte ich mit dir sprechen. Aber zuerst, lies die Nachricht deines Bruders.";
			link.l1 = "Ich brenne vor Ungeduld!";
			link.l1.go = "escape_3";
		break;
		
		case "escape_3":
			DialogExit();
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Mishelle";
			NextDiag.CurrentNode = "escape_4";
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;
		
		case "escape_4":
			if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
			{
				dialog.text = "Ich sehe, du hast den Brief gelesen. Jetzt möchte ich dir etwas sagen, Charles...";
				link.l1 = "Aber... wie kann das sein? Was für ein Unsinn ist das? Ich weiß, dass mein Bruder eigenartig ist, aber er ist kein Verrückter!";
				link.l1.go = "escape_5";
			}
			else
			{
				dialog.text = "Mein Sohn, lies den Brief. Wir sprechen später.";
				link.l1 = "Ja, Vater...";
				link.l1.go = "exit";
				NextDiag.TempNode = "escape_4";
			}
		break;
		
		case "escape_5":
			dialog.text = "Die Handlungen deines Bruders haben mich auch überrascht, Charles. Ich verspüre immer noch Momente der Verwirrung. Ein treuer Diener des Ordens und der Dreifaltigkeit und er verhält sich wie ein Deserteur.";
			link.l1 = "Haben Sie eine Ahnung, was die Gründe für ein solch seltsames Verhalten sein könnten?";
			link.l1.go = "escape_6";
		break;
		
		case "escape_6":
			dialog.text = "Ach, das tue ich nicht. Aber ich vermute, dass er seine eigenen, tiefgründigen Beweggründe hat. Die Aufhebung seiner gesamten Vergangenheit würde einen äußerst bedeutsamen Grund vermuten lassen. Ich kann mir nicht einmal vorstellen, was es sein könnte. Aber ich habe das Gefühl, dass es etwas extrem Schlechtes... sogar Schreckliches beinhaltet.";
			link.l1 = "Was könnte es sein, Vater?";
			link.l1.go = "escape_7";
		break;
		
		case "escape_7":
			dialog.text = "Mein Sohn, ein Priester sieht nicht mit seinen Augen, sondern mit seinem Herzen. Ich kann es dir nicht in Worten erklären, aber... dein Bruder hat sich vorgenommen, etwas Unreines, Schmutziges zu tun. Ich hätte nie gedacht, dass mein Mund das aussprechen könnte. Jedoch...";
			link.l1 = "Nun, ich bezweifle nicht, dass mein Bruder etwas Schmutziges geplant hat. Ich kann sogar herausfinden, was genau er vorhat. Dieses 'Etwas' hat etwas mit Gelb zu tun und macht ein schönes Klimpergeräusch.";
			link.l1.go = "escape_8";
		break;
		
		case "escape_8":
			dialog.text = "Ich glaube nicht, dass die Gier nach Gold das ist, was deinen Bruder antreibt. Ich würde sagen, dass er etwas Größeres braucht.";
			link.l1 = "Ich habe viel von Michel gelernt und seine Philosophie verstanden, daher denke ich, dass ich einschätzen kann, was ihm wichtig ist und was nicht. Aber ich werde Ihre geschätzten Worte im Gedächtnis behalten, Vater.";
			link.l1.go = "escape_9";
		break;
		
		case "escape_9":
			dialog.text = "Gott segne dich, mein Sohn. Geh, geh jetzt. Möge der Herr über dich wachen!";
			link.l1 = "Danke, Vater. Auf Wiedersehen!";
			link.l1.go = "escape_10";
		break;
		
		case "escape_10":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddDialogExitQuestFunction("Sharlie_Benua_BrotherEscape");
		break;
		
		// уменьшение награды за голову
		case "meet":
			dialog.text = "Michel de Monpers Bruder? De Maure? Wie merkwürdig...";
			link.l1 = "Ich verstehe Ihre Zweifel, Vater. Wir haben einfach verschiedene Nachnamen. Mein Vater ist Henri de Monper.";
			link.l1.go = "meet_1";			
		break;
		
		case "meet_1":
			dialog.text = "A-ah, ich verstehe jetzt. Ich kannte Henri de Monper persönlich. Tritt ins Licht, junger Mann... Richtig! Du siehst ihm ähnlich. Gleiche Aussehen, gleiche edle Seitenansicht! Ich freue mich, einen Sohn von Henri de Monper in unserer Gemeinde zu sehen.\nIch habe bereits gehört, dass Michel von einem Mann aus Europa besucht wurde, aber ich konnte mir nicht vorstellen, dass es sein eigener Bruder ist. Ich hoffe, dass du Michel helfen kannst, er erlebt eine schwierige Zeit. Wie kann ich dir behilflich sein?";
			link.l1 = "Michel hat mir gesagt, dass du mir helfen könntest, wenn ich jemals Ärger mit den Behörden hätte.";
			link.l1.go = "help_info";	
			npchar.quest.meet = true;
		break;
		
		case "help_info":
			dialog.text = "Das hat dir Michel erzählt? Ich verstehe. Nun, ich kann in solchen Angelegenheiten behilflich sein. Ich habe einen gewissen Einfluss auf das Heilige Römische Reich und die niederländischen Kolonien. Daher könnte ich möglicherweise zwischen dir und den spanischen sowie niederländischen Behörden vermitteln. Sicherlich werde ich nicht viel tun können, wenn dein Fehlverhalten zu groß geworden ist - in diesem Fall kann nur eine geringe Milderung erreicht werden.\nEs werden mehrere Fürsprachen für eine vollständige Versöhnung erforderlich sein. Außerdem musst du mir in jedem Fall goldene Dublonen für Wohltätigkeits- und Reiseausgaben zur Verfügung stellen. Außerdem kann ich dir nur bei einer Nation zur Zeit helfen. Wenn du diese Bedingungen akzeptierst, zögere nicht, dich an mich zu wenden, und wir werden sehen, was getan werden kann.";
			link.l1 = "Danke! Ich werde das im Hinterkopf behalten.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "help_start":
			dialog.text = "Was kann ich für dich tun, mein Sohn? Sprich, ich höre zu.";
			link.l1 = "Michel hat mir gesagt, dass du mir helfen könntest, wenn ich jemals Ärger mit den Behörden bekomme.";
			link.l1.go = "help_info";
		break;
		
		case "help":
			dialog.text = "Wie kann ich Ihnen helfen, mein Sohn?";
			//--> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater"))
			{
				link.l1 = "Kehren wir zur Frage der Bezahlung für die Übermittlung der Anweisungen zurück.";
				link.l1.go = "SharlieEpilog_Benua_DublonsLater_2";
			}
			if (CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				link.l1 = "Ich möchte eine Anweisung senden...";
				link.l1.go = "SharlieEpilog_Benua_Delivery";
			}
			//<-- Эпилог
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Ich habe Ärger mit den spanischen Behörden bekommen.";
				link.l1.go = "relation_spa";
			}
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Ich habe Ärger mit den niederländischen Behörden bekommen.";
				link.l2.go = "relation_hol";
			}
			link.l9 = "Entschuldigung, ich denke, ich werde diesmal selbst die Dinge in die Hand nehmen.";
			link.l9.go = "exit";
		break;
		
		case "relation_spa": // patch-10
			pchar.GenQuest.BenuaNation = SPAIN;
			dialog.text = "Also, die edlen Senoren sind begierig darauf, dich in die Kerker von Havanna zu stecken...";
			link.l1 = "Genau so, Vater...";
			link.l1.go = "relation";
		break;
		
		case "relation_hol":
			pchar.GenQuest.BenuaNation = HOLLAND;
			dialog.text = "Also, die klugen Kaufleute sind begierig darauf, dich in die Verliese von Willemstad zu stecken...";
			link.l1 = "Genau so, Vater...";
			link.l1.go = "relation";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.BenuaNation));
			iBenuaPseudoGlobal = DiplomatDublonPayment(rate, "Benua", false);
			sTemp = FindRussianDublonString(iBenuaPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Ja, diese Gerüchte haben auch unsere Kirche erreicht. Ich kann Ihnen bei Ihrem Dilemma helfen. Es ist etwas, das gelöst werden kann. Ich brauche " + sTemp + ", um Ihr Problem zu lösen.";
				if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
				{
					link.l1 = "Großartig! Hier ist das Gold.";
					link.l1.go = "agree";
				}
				link.l2 = "Dann ist es die richtige Zeit für mich, die Dublonen zu finden.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Ja, Gerüchte über deine 'Heldentaten' haben auch unsere Kirche erreicht. Du hast deinen Ruf befleckt, mein Sohn. Du solltest vorsichtiger sein. Aber ich kann dir helfen. Ich brauche " + sTemp + ", um deine Lage zu bereinigen.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Großartig! Hier ist das Gold.";
						link.l1.go = "agree";
					}
					link.l2 = "Dann ist es die richtige Zeit für mich, die Dublonen zu finden.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Ja, mein Sohn. Du bist genauso verzweifelt wie dein Bruder... Wahrscheinlich ist das ein Familienmerkmal. Ich kann die Situation nicht vollständig korrigieren, aber dennoch glaube ich, dass ich dein düsteres Dilemma mildern kann. Und später können wir mehr Opfer bringen, wenn du willst. Ich brauche jetzt " + sTemp + " und ich werde sofort anfangen, dein Dilemma zu lösen.";
					if (PCharDublonsTotal() >= iBenuaPseudoGlobal) // Sinistra legendary edition
					{
						link.l1 = "Großartig! Hier ist das Gold.";
						link.l1.go = "agree";
					}
					link.l2 = "Dann ist es die richtige Zeit für mich, die Dublonen zu finden.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iBenuaPseudoGlobal); // Sinistra legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Jetzt musst du mindestens zwei Wochen warten. Ich denke, dass ich in dieser Zeit die richtigen Leute treffen und mit ihnen sprechen kann.";
			link.l1 = "Danke, Vater! Ich werde warten...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, rate, false);
			pchar.GenQuest.BenuaNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.BenuaNation));
			npchar.quest.relation = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка 1
		case "FastStart":
			dialog.text = "De Maure? Und du bist ein Bruder von Michel de Monper? Seltsam...";
			link.l1 = "Ich verstehe Ihre Zweifel, Padre. Mein Vater ist Henri de Monper.";
			link.l1.go = "FastStart_1";			
		break;
		
		case "FastStart_1":
			dialog.text = "A-ah, ich verstehe. Ich kannte Henri de Monper persönlich. Tritt ins Licht, junger Mann. Richtig! Dieselben Augen, dieselben edlen Züge! Es freut mich, einen Sohn von Henri de Monper in meiner Kirche zu sehen. Ich hoffe, du kannst deinem Bruder helfen. Er hatte in letzter Zeit viel Pech.";
			link.l1 = "Ja, Vater. Ich brauche ein Schiff, um Michel zu helfen, aber ich bin gerade erst in der Karibik angekommen und meine Geldbörse ist leer. Mein Bruder sagte mir, dass du mir etwas Geld leihen könntest...";
			link.l1.go = "FastStart_2";	
			npchar.quest.meet = true;
		break;
		
		case "FastStart_2":
			DelLandQuestMark(npchar);
			dialog.text = "Michel hat es dir gesagt?";
			link.l1 = "Vater, ich mag nicht sehr vertrauenswürdig klingen, doch es ist wahr. Je eher ich ein Schiff bekomme, desto eher kann ich meinen Bruder aus dem Gefängnis holen.";
			link.l1.go = "FastStart_3";
		break;
		
		case "FastStart_3":
			dialog.text = "Ich sehe, mein Sohn. Ich höre, dass du die Wahrheit sprichst. Nun, um Michel und deinem Vater willen werde ich dir helfen. Ich habe einige Ersparnisse, nimm sie. Ich nehme an, 50 000 Pesos und 100 Dublonen werden ausreichen.";
			link.l1 = "Danke, Pater. Was sind die Bedingungen?";
			link.l1.go = "FastStart_4";
		break;
		
		case "FastStart_4":
			AddMoneyToCharacter(pchar, 50000);
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Kein Druck. Ein halbes Jahr zur Rückzahlung wird ausreichen.";
			link.l1 = "Sehr gut, heiliger Vater. Nochmals vielen Dank!";
			link.l1.go = "FastStart_5";
		break;
		
		case "FastStart_5":
			dialog.text = "Geh mit meinen Segnungen, mein Sohn.";
			link.l1 = "...";
			link.l1.go = "FastStart_6";
		break;
		
		case "FastStart_6":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			npchar.quest.FastStart = "true";
			pchar.questTemp.Sharlie.BenuaLoan = "true";
			SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
			AddQuestRecord("Sharlie", "5-2");
		break;
		
		case "FastStart_7":
			dialog.text = "Prächtig, mein Sohn. Hoffe, dass dir das Geld etwas genutzt hat.";
			link.l1 = "Tatsächlich hat es das! Danke!";
			link.l1.go = "FastStart_8";
		break;
		
		case "FastStart_8":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			AddMoneyToCharacter(pchar, -50000);
			RemoveDublonsFromPCharTotal(100);
			pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
			AddQuestRecord("Sharlie", "5-3");
		break;
		
		// Jason Долго и счастливо
		case "LH_abbat":
			dialog.text = "Charles, ich kann meinen Augen nicht trauen! Was führt dich hierher?!";
			link.l1 = "Heiliger Vater, segne mich, denn ich komme mit guten Nachrichten - ich werde heiraten und ich möchte dich als Priester meiner Hochzeit sehen.";
			link.l1.go = "LH_abbat_1";
		break;
		
		case "LH_abbat_1":
			dialog.text = "Mein Sohn, das ist wunderbar! Also hast du diesen Brief von deinem Vater erhalten und dich entschieden, wie üblich, nach deinem eigenen Verständnis zu handeln? Ich freue mich aufrichtig für dich! Aber ich fürchte, ich kann dir nicht helfen, es sei denn, du entscheidest dich, in dieser Kirche hier zu heiraten.";
			link.l1 = "Ich verstehe, dass Ihre Mission in einer Sackgasse ist, Heiliger Vater? Kann ich Ihnen irgendwie helfen? Da die Hochzeit natürlich in einer spanischen Kapelle stattfinden wird, ist es ein Abenteuer, das ich gerne eingehen würde, aber ich bin entschlossen, die Feier in Martinique abzuhalten. Mäßig prächtig, und in Anwesenheit von seriösen Zeugen und ehrenwerten Gästen.";
			link.l1.go = "LH_abbat_2";
		break;
		
		case "LH_abbat_2":
			dialog.text = "Es tut mir leid, mein Sohn, aber all deine Autorität ist nichts wert gegen die Sturheit der höchsten Hierarchen der katholischen Kirche, besonders in den spanischen Kolonien. Wir konnten uns nicht über die Frage der Aufteilung des Einflusses der katholischen Missionen zwischen unseren Ländern einigen, und jetzt bin ich hier, als geehrter Gast und geehrter Geisel. Die Spanier warten auf ein besseres Angebot von unserer Seite. Ich habe eine Nachricht nach Europa geschickt, hoffentlich wird die Antwort in zwei Monaten kommen und wir werden in der Lage sein, die Verhandlungen wieder aufzunehmen. Wenn sie in zwei Monaten noch nicht hier ist, wird sie definitiv in den nächsten sechs Monaten hier sein.\nUnd ja, während der Papst und Mazarin in den letzten paar Wochen einen Kompromiss gefunden haben, ist es zu früh, über eine wirklich herzerwärmende Beziehung zu sprechen. Ehrlich gesagt, bin ich mir nicht sicher, ob wir jemals zu einer Einigung kommen werden. Es scheint mir, dass Palotti mich einfach als Argument in seinen eigenen politischen Machenschaften behält. Allerdings muss ich sagen, der Inquisitor hat ausgezeichneten Kaffee!";
			link.l1 = "Ich habe weder sechs Monate noch zwei Monate! Ich muss den Wunsch meines Vaters erfüllen, sonst wird er mich ohne meine Zustimmung verheiraten. Und seine Gesundheit ist nicht mehr so gut wie früher, doch ich würde ihm gerne meine Auserwählte und die zukünftige Dame von Monper vorstellen.";
			link.l1.go = "LH_abbat_3";
		break;
		
		case "LH_abbat_3":
			dialog.text = "Ich fürchte, du wirst dann einen anderen Priester für deine Hochzeit finden müssen, mein Sohn. Ach, ich werde hier noch lange bleiben.";
			link.l1 = "Was würden Sie sagen, wenn ich Sie vom Kaffee des Inquisitors trenne?";
			link.l1.go = "LH_abbat_4";
		break;
		
		case "LH_abbat_4":
			dialog.text = "Ich würde Ihre Hilfe gerne annehmen. Ich vermute, dass ich nicht zufällig für diese Mission ausgewählt wurde. Im schlimmsten Fall vergessen sie einfach Pater Benoit. Und obwohl der Herr mir befahl zu ertragen, belastet mich mein Schluss trotz all seiner... Segnungen. Aber ich wiederhole - es ist unwahrscheinlich, dass Pater Palotti auf Ihre Bitten hören wird.";
			link.l1 = "Dann werde ich mir etwas Zeit sparen und werde nicht versuchen, ihn zu überzeugen. Wir werden die Kirche einfach verlassen, sobald der Gottesdienst vorüber ist, und zu meinem Schiff gehen. Zögern Sie nicht, Heiliger Vater - sie haben unser Treffen gesehen und sie werden mich erkennen, und es wird viel schwieriger sein, Ihnen zu helfen, wenn ich Sie aus der Residenz des Gouverneurs holen muss.";
			link.l1.go = "LH_abbat_5";
		break;
		
		case "LH_abbat_5":
			dialog.text = "Es ist riskant, mein Sohn, sehr riskant. Eine Gruppe von Wachen wartet draußen, um mich zum Herrenhaus zu begleiten, und die Stadt ist voll von Soldaten.";
			link.l1 = "Wir werden mit dem Überraschungsmoment vorgehen, Vater Benoit. Sie müssen mir einfach vertrauen und alles wird gut. Ich habe etwas... Erfahrung in diesen Angelegenheiten.";
			link.l1.go = "LH_abbat_6";
		break;
		
		case "LH_abbat_6":
			dialog.text = "Wie du wünschst. Aber bitte, tu es ohne unnötiges Blutvergießen! Ich hatte auch schon einige Erfahrungen dieser Art... Führe uns, mein Sohn. Ich bin direkt hinter dir. Aber ich werde keine Waffe aufnehmen, also frage erst gar nicht.";
			link.l1 = "Habe nicht mal darüber nachgedacht, Vater. Ich kann das handhaben. Folge mir, aber sei vorsichtig, sie könnten auf uns schießen.";
			link.l1.go = "LH_abbat_7";
		break;
		
		case "LH_abbat_7":
			DialogExit();
			LongHappy_SantiagoBenuaEscape();
		break;
		
		case "LH_abbat_8":
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
			dialog.text = "Mein Sohn, ich hatte keine Zeit, dir für meine Freilassung zu danken. Anscheinend wollten der spanische Bischof und der Inquisitor Palotti die kaum etablierten Beziehungen zwischen unserem Kardinal und dem Heiligen Stuhl stören, so hast du vollkommen im Interesse unseres Landes gehandelt. Wieder einmal. Aber niemand wird dir 'danke' sagen, außer mir.";
			link.l1 = "Alltägliche Sache, Heiliger Vater. Froh, dass ich helfen konnte. Aber, ich muss Sie auch etwas fragen, erinnern Sie sich?";
			link.l1.go = "LH_abbat_9";
		break;
		
		case "LH_abbat_9":
			dialog.text = "Natürlich! Also lasst uns zum angenehmen Geschäft kommen - Charles, wie laufen die Vorbereitungen für deinen wichtigsten Tag?";
			link.l1 = "Es nimmt langsam Form an. Ich kenne militärische Feldzüge, die einfacher und schneller vorbereitet wurden, aber es lohnt sich!";
			link.l1.go = "LH_abbat_10";
		break;
		
		case "LH_abbat_10":
			dialog.text = "Sicher, mein Sohn! Und bei dieser Gelegenheit möchte ich etwas klarstellen - wie stellst du dir deine Hochzeitszeremonie vor?";
			link.l1 = "Du meinst, wie prahlerisch?";
			link.l1.go = "LH_abbat_11";
		break;
		
		case "LH_abbat_11":
			dialog.text = "Natürlich! Denn ich muss die Kirche vorbereiten, und vielleicht möchten Sie einige wichtige Leute einladen.";
			link.l1 = "Nichts Besonderes, Heiliger Vater. Diejenigen, die ich als unsere Freunde betrachte, werden anderswo auf uns warten. Hier werden nur einige Beamten, meine Leute, und einige gewöhnliche Zuschauer anwesend sein.";
			link.l1.go = "LH_abbat_12";
		break;
		
		case "LH_abbat_12":
			dialog.text = "Nun, dann denke ich, werden wir mit einer kleinen Spende zurechtkommen.";
			link.l1 = "Das klingt nicht allzu beängstigend. Und wie viel ist eine solche Spende in Gold?";
			link.l1.go = "LH_abbat_13";
		break;
		
		case "LH_abbat_13":
			dialog.text = "Für den Chor, feierlichen Gottesdienst und andere Ausgaben - hundertfünfzig, nicht mehr. Dazu die übliche Spende der Neuvermählten, insgesamt - zweihundert Dublonen.";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Hier, Heiliger Vater.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Über diese militärischen Feldzüge... Ich muss wohl einen Spaziergang zur Bank machen und zurückkehren.";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_14":
			DialogExit();
			npchar.dialog.currentnode = "LH_abbat_14_1";
		break;
		
		case "LH_abbat_14_1":
			dialog.text = "Was ist mit Ihrer Spende, mein Sohn?";
			if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
			{
				link.l1 = "Hier haben Sie, Heiliger Vater.";
				link.l1.go = "LH_abbat_15";
			}
			else
			{
				link.l1 = "Ja, ja, ich bringe es bald...";
				link.l1.go = "LH_abbat_14";
			}
		break;
		
		case "LH_abbat_15":
			RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
			dialog.text = "Es bleibt noch eine Frage zu beantworten - wer wird die Braut weggeben und die Ehe von ihrer Seite bezeugen?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Svenson";
				link.l1 = "Jan Svensson, von Blueweld. Er ist ein Engländer, aber eine respektierte Person und an Helen gebunden, als wäre sie seine eigene Tochter, und ihre Adoptivmutter ist Gladys McArthur.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					pchar.questTemp.LongHappy.Pater1 = "Noel";
					link.l1 = "Baron Noel Forget, ich bin sicher, er wird mir die Ehre erweisen.";
				}
				else
				{
					pchar.questTemp.LongHappy.Pater1 = "Puancie";
					link.l1 = "Chevalier Philippe de Poincy, ich bin sicher, er wird mir die Ehre erweisen.";
				}
			}
			link.l1.go = "LH_abbat_16";
		break;
		
		case "LH_abbat_16":
			dialog.text = "Nun, und wer wird für den Bräutigam aussagen? Denken Sie daran, dies muss ein Mann von edler Geburt und würdigem Ruf sein.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
				{
					link.l1 = "Baron Noel Forget, ich bin sicher, er wird mir die Ehre erweisen.";
					link.l1.go = "LH_abbat_17_1";
				}
				else
				{
					link.l1 = "Chevalier Philippe de Poincy, ich bin sicher, er wird mir die Ehre erweisen.";
					link.l1.go = "LH_abbat_17_2";
				}
				link.l2 = "Fadey - ein angesehener Kaufmann aus Guadeloupe. Ich muss nur seinen Lieblingsalkohol besorgen.";
				link.l2.go = "LH_abbat_17_3";
			}
			else
			{
				link.l1 = "Fadey - ein respektabler Kaufmann aus Guadeloupe. Ich muss nur seinen Lieblingsalkohol besorgen.";
				link.l1.go = "LH_abbat_17_3";
			}
		break;
		
		case "LH_abbat_17_1":
			pchar.questTemp.LongHappy.Pater2 = "Noel";
			dialog.text = "Großartig, ich werde die Einladungen aussenden, aber die Gäste werden etwas Zeit brauchen, um hierher zu gelangen. Ich denke, alles wird in einem Monat fertig sein, und die angegebenen Personen werden in der Stadt angekommen sein.";
			link.l1 = "Gut! Dann habe ich Zeit, ein paar Besorgungen zu machen. Bis bald, Heiliger Vater und wünsche mir Glück!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_2":
			pchar.questTemp.LongHappy.Pater2 = "Puancie";
			dialog.text = "Großartig, ich werde die Einladungen verschicken, aber die Gäste brauchen etwas Zeit, um hierher zu gelangen. Ich denke, alles wird in einem Monat fertig sein und die angegebenen Personen werden in der Stadt angekommen sein.";
			link.l1 = "Gut! Dann habe ich Zeit, ein paar Besorgungen zu machen. Bis bald, Heiliger Vater und wünsche mir Glück!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_17_3":
			pchar.questTemp.LongHappy.Pater2 = "Fadey";
			dialog.text = "Großartig, ich werde die Einladungen versenden, aber die Gäste werden einige Zeit brauchen, um hierher zu kommen. Ich denke, alles wird in einem Monat fertig sein, und die angegebenen Personen werden in der Stadt angekommen sein.";
			link.l1 = "Gut! Dann habe ich Zeit, ein paar Besorgungen zu machen. Bis bald, Heiliger Vater und wünsche mir Glück!";
			link.l1.go = "LH_abbat_18";
		break;
		
		case "LH_abbat_18":
			DialogExit();
			AddQuestRecord("LongHappy", "11");
			SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
			if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
			{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true);//закрыть таверну Исла-Тесоро
			}
			npchar.dialog.currentnode = "First time";
		break;
		
		case "LH_abbat_19":
			dialog.text = "Also, der Tag ist gekommen, mein Sohn! Alles ist bereit - in ein paar Stunden können wir starten. Du siehst blass aus!";
			link.l1 = "Ich bin etwas nervös, Heiliger Vater.";
			link.l1.go = "LH_abbat_20";
		break;
		
		case "LH_abbat_20":
			dialog.text = "Das ist üblich. Dies ist der wichtigste Tag in Deinem Leben und ich freue mich aufrichtig für Dich, wie jeder, der gekommen ist. Ich hoffe, Du erinnerst Dich zumindest an die grundlegenden Gebete - Du hast die Kirche ja nie wirklich mit Deiner Aufmerksamkeit verwöhnt, oder? Trotzdem werde ich Dir in jedem Fall helfen.\nUnd noch etwas - soweit ich es verstehe, wird die Braut ihre Prinzipien nicht ändern und wir werden sie nicht in einem Kleid sehen? Nun, die hohe Gesellschaft steht kurz davor, eine weitere Überraschung von Dir zu erleben - Du bist voll davon. Wie auch immer, geh mein Sohn, bring Dich in Form und wir werden beginnen.";
			link.l1 = "Ja, Heiliger Vater. Lass es uns tun.";
			link.l1.go = "LH_abbat_21";
		break;
		
		case "LH_abbat_21":
			DialogExit();
			chrDisableReloadToLocation = true;
			WaitDate("", 0, 0, 0, 2, 0);
			DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;
		
		case "LH_abbat_22":
			pchar.questTemp.LongHappy.Mistake = 0;
			dialog.text = "Vater unser, der du bist im Himmel, geheiligt werde dein Name, zu...";
			link.l1 = "...dein Reich komme";
			link.l1.go = "LH_abbat_23_1";
			link.l2 = "...ewige Ruhe schenke ihnen";
			link.l2.go = "LH_abbat_23_2";
		break;
		
		case "LH_abbat_23_1":
			dialog.text = "...Dein Wille geschehe, wie im Himmel so auf Erden. Unser tägliches Brot gib uns heute, und vergib uns unsere Schuld, als...";
			link.l1 = "...wie auch wir vergeben unseren Schuldnern";
			link.l1.go = "LH_abbat_24_1";
			link.l2 = "...wie es war im Anfang, jetzt und immer und in Ewigkeit. Amen";
			link.l2.go = "LH_abbat_24_2";
		break;
		
		case "LH_abbat_23_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "Ä-ä... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_23_1";
		break;
		
		case "LH_abbat_24_2":
			pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake)+1;
			dialog.text = "Ä-ä... Hm...";
			link.l1 = "";
			link.l1.go = "LH_abbat_24_1";
		break;
		
		case "LH_abbat_24_1":
			dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_25";
		break;
		
		case "LH_abbat_25":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Teuer Geliebte, wir sind hier zusammen versammelt vor Gott und vor dieser Gemeinde, um diesen Mann und diese Frau in heiliger Ehe zu vereinen. Geliebte "+sld.name+" und Charles, du hast auf das Wort Gottes gehört, das dich an die Bedeutung menschlicher Liebe und Ehe erinnert hat. Nun möchte ich im Namen der heiligen Kirche deine Absichten in Frage stellen.\n"+sld.name+" und Charles, hast du einen freiwilligen und aufrichtigen Wunsch, dich mit dem anderen durch das Band der Ehe zu verbinden, im Angesicht unseres Herrn?";
			link.l1 = "Ja.";
			link.l1.go = "LH_abbat_26";
		break;
		
		case "LH_abbat_26":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_27":
			dialog.text = "Gedenkt ihr, einander in Gesundheit und Krankheit, in Glück und Unglück, bis zum Ende eures Lebens treu zu sein?";
			link.l1 = "Ja.";
			link.l1.go = "LH_abbat_28";
		break;
		
		case "LH_abbat_28":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_22";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_29":
			dialog.text = "Haben Sie die Absicht, die Kinder zu lieben und zu akzeptieren, die unser Herr Ihnen senden wird und sie im christlichen Glauben zu erziehen?";
			link.l1 = "Ja.";
			link.l1.go = "LH_abbat_30";
		break;
		
		case "LH_abbat_30":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_31":
			dialog.text = "Nun, wendet euch einander zu und gebt ein Gelübde ab.";
			link.l1 = "";
			link.l1.go = "LH_abbat_32";
		break;
		
		case "LH_abbat_32":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_33":
			dialog.text = "Sollte jemand hier anwesend sein, der einen Grund kennt, warum dieses Paar nicht in heiliger Ehe vereint werden sollte, so spreche er jetzt oder schweige für immer.\nIn diesem Fall erkläre ich euch vor dem Angesicht des Herrn und der hier versammelten Menschen zu Mann und Frau! In nomine Patris, et Filii, et Spiritus Sancti. Amen.";
			link.l1 = "Amen.";
			link.l1.go = "LH_abbat_34";
		break;
		
		case "LH_abbat_34":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LH_abbat_35":
			string sTemp;
			if (sti(pchar.questTemp.LongHappy.Mistake) > 1) sTemp = "(Whispering) Charles, my son, just move your lips, I beg you - don't try to make any sound...";
			else sTemp = "";
			dialog.text = "Neuvermählte, kniet nieder und betet zusammen. Oratio fidelium. "+sTemp+"";
			link.l1 = "";
			link.l1.go = "LH_abbat_36";
		break;
		
		case "LH_abbat_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.lastname = "de Maure";
			sld.SpecialRole = "wife";
			sld.dialog.currentnode = "LongHappy_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;
		
		case "LH_abbat_37":
			dialog.text = "Meine Glückwünsche, Sohn. Dein Vater kann stolz auf dich sein, und ich bin es auch. Seid glücklich und kümmert euch in unserer schwierigen Zeit um einander.";
			link.l1 = "Danke, Heiliger Vater. Es war ein wundervoller Gottesdienst und ich bin froh, dass Sie es waren, der ihn abgehalten hat.";
			link.l1.go = "LH_abbat_38";
		break;
		
		//--> Дикая Роза
		case "WildRose_Abb_2":
			dialog.text = "Ihr seid also zu mir gekommen, um Rat zu suchen, meine Kinder? Nun gut, ich höre zu.";
			link.l1 = "Eher um Unterstützung, Vater. Die Hilfe eines Mannes mit Verbindungen, der viele verschiedene Leute kennt...";
			link.l1.go = "WildRose_Abb_3";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua");
		break;

		case "WildRose_Abb_3":
			dialog.text = "Verzeih, dass ich dich unterbreche, mein Sohn, aber ich möchte daran erinnern, dass ich ein einfacher Abt bin – kein Spion.";
			link.l1 = "Aber ein einfacher Abt kann doch durchaus einen Spion kennen, oder zumindest wissen, wie man ihn erreicht?";
			link.l1.go = "WildRose_Abb_4_fortune";
			link.l2 = "Die Angelegenheit, mit der wir zu Euch kommen, betrifft tatsächlich einige längst vergessene Geheimnisse... Wir versuchen, sie ans Licht zu bringen.";
			link.l2.go = "WildRose_Abb_4_stealth";
		break;

		case "WildRose_Abb_4_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Also, junger Mann, das gefällt mir langsam nicht mehr. Komm zur Sache, und wir werden sehen, ob ich dir helfen kann... oder überhaupt helfen will.";
			link.l1 = "Ja, Vater. Ich versuche, mich kurz zu fassen...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_4_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = ""+pchar.name+", hör auf mit diesen Rätseln – das ist, ehrlich gesagt, ermüdend.";
			link.l1 = "Ja, Vater. Ich versuche, mich kurz zu fassen...";
			link.l1.go = "WildRose_Abb_5";
		break;

		case "WildRose_Abb_5":
			dialog.text = "Fahr fort, mein Sohn.";
			link.l1 = "Meine Begleiterin – Mary Casper – sucht nach ihrem Vater, oder zumindest nach Informationen über ihn. Wir haben herausgefunden, dass er Offizier der Royal Navy war und auf der Brigg 'Wrangler' diente, die 1638 bei Kap Catoche Schiffbruch erlitt.";
			link.l1.go = "WildRose_Abb_6";
		break;

		case "WildRose_Abb_6":
			dialog.text = "Und ihr hofft, dass er noch lebt? Nach all den Jahren?";
			link.l1 = "Selbst wenn er das Schiffsunglück nicht überlebt hat, möchte Mary wissen, woher ihr Vater stammt, was für ein Mensch er war, welches Leben er führte... Offizielle Unterlagen geben wenig her – aber manchmal enthalten sie doch wertvolle Hinweise, nicht wahr, Vater?";
			link.l1.go = "WildRose_Abb_7";
		break;

		case "WildRose_Abb_7":
			dialog.text = "Du hast mit deinen Überlegungen natürlich recht, mein Sohn. Eure Suche ist ehrenwert und gottgefällig. Aber ich habe noch nicht ganz verstanden, was genau ihr von mir wollt?";
			link.l1 = "Ihr lebt doch schon lange auf dem Archipel, Vater. Vielleicht kennt Ihr jemanden, der Zugang zu kolonialen Archiven mit Dokumenten über Offiziere der Royal Navy hat?";
			link.l1.go = "WildRose_Abb_8_stealth";
			link.l2 = "Wir brauchen jemanden mit Zugang zu den Archiven der Kolonialverwaltung, wo Daten über Offiziere der Royal Navy aufbewahrt werden. Ihr habt doch bestimmt jemanden im Sinn, Vater.";
			link.l2.go = "WildRose_Abb_8_charisma";
		break;

		case "WildRose_Abb_8_stealth":
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "Du weißt, worum du bittest, mein Sohn? Es geht nicht nur darum, dass diese Informationen militärisch geheim sein könnten...";
			link.l1 = "Worum geht es dann, Vater? Ich sage es Euch sofort...";
			link.l1.go = "WildRose_Abb_9";
		break;

		case "WildRose_Abb_8_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Du weißt, worum du bittest, mein Sohn? Es geht nicht nur darum, dass diese Informationen militärisch geheim sein könnten...";
			link.l1 = "Worum geht es dann, Vater? Ich sage es Euch sofort...";
			link.l1.go = "WildRose_Abb_9";
		break;
		
		case "WildRose_Abb_9":
			dialog.text = "Das Problem liegt genau in diesen kolonialen Archiven. Vor zwanzig Jahren war Jamaika unter spanischer Kontrolle, und Saint John's sowie Bridgetown waren ständig von Überfällen bedroht. Es ist unwahrscheinlich, dass Schiffe der Royal Navy dort stationiert waren...";
			link.l1 = "Ihr sprecht vom Admiralitätsarchiv in London, Vater?";
			link.l1.go = "WildRose_Abb_10";
		break;

		case "WildRose_Abb_10":
			dialog.text = "Möglich. Die Unterlagen sollten der Admiralität übergeben worden sein. An sie heranzukommen, ist nicht einfach.";
			link.l1 = "Aber es ist möglich, nicht wahr, Vater?";
			link.l1.go = "WildRose_Abb_11";
		break;

		case "WildRose_Abb_11":
			dialog.text = "Nichts ist unmöglich, mein Sohn. Aber es erfordert Mühe... und eine gewisse Zahlung.";
			link.l1 = "Natürlich, Vater. Soll ich euch das Geld übergeben oder muss ich jemanden treffen?";
			link.l1.go = "WildRose_Abb_12";
		break;

		case "WildRose_Abb_12":
			dialog.text = "Den Kontakt übernehme ich persönlich, mein Sohn. Von dir brauche ich... achthundert Dublonen.";
			link.l1 = "In Ordnung, Vater. Wie lange wird das dauern?";
			link.l1.go = "WildRose_Abb_13";
		break;

		case "WildRose_Abb_13":
			dialog.text = "Ich schätze, zwei Monate. Übrigens – du hast mir noch nicht den Namen genannt, nach dem wir suchen.";
			link.l1 = "Sein Name ist Joshua Casper.";
			link.l1.go = "WildRose_Abb_14";
		break;

		case "WildRose_Abb_14":
			dialog.text = "Ich habe es mir gemerkt. Wenn du den Betrag gleich hier übergeben willst – kann ich morgen schon jemanden losschicken.";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Natürlich, Vater. Hier, bitte. Achthundert Goldstücke.";
				link.l1.go = "WildRose_Abb_14_pay";
			}
			link.l2 = "Nein, Vater, ich habe das Geld gerade nicht bei mir. Aber ich kehre bald zurück und bringe es mit.";
			link.l2.go = "WildRose_Abb_14_nopay";
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Sehr gut, "+pchar.name+". Komm in zwei Monaten wieder – ich bin sicher, dass ich bis dahin eine Antwort für dich habe.";
			link.l1 = "Danke, Vater. Auf bald!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "Wie du meinst, mein Sohn.";
			link.l1 = "Ich komme bald wieder.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.WildRose_Etap3_Benua_2 = true;
		break;

		case "WildRose_Abb_16":
			dialog.text = "Er hat sowohl über Joshua Casper als auch über sein Schiff Nachforschungen angestellt – und dabei stellte sich heraus, dass es sich keineswegs um die 'Wrangler' handelte. Eine Brigg mit diesem Namen gehörte nie zur Royal Navy.";
			link.l1 = "Hm... Ich bin mir absolut sicher, dass das Schiff, auf dem Joshua Casper diente, genau diesen Namen trug... Und was ist mit Joshua selbst?";
			link.l1.go = "WildRose_Abb_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_3");
		break;

		case "WildRose_Abb_17":
			dialog.text = "Dieser Mann war ein hervorragender Offizier mit vielen Verdiensten und Auszeichnungen – all das steht in seiner Personalakte. Auch wenn er nicht dem wahren Glauben angehörte, war er doch ein würdiger Kapitän. Mademoiselle kann stolz auf solche Wurzeln sein.";
			link.l1 = "Das sind gute Nachrichten, Vater. Aber erlaubt mir, noch einmal auf das Schiff zurückzukommen. Wenn es nicht 'Wrangler' hieß – wie dann?";
			link.l1.go = "WildRose_Abb_19";
			AddQuestRecordInfo("WildRose_Records_3", "1");
		break;

		case "WildRose_Abb_19":
			dialog.text = "'Cornwall'. Er verließ Plymouth im Januar 1638 mit dem Befehl, Sold an die Garnisonen von Antigua und Providence zu liefern.";
			link.l1 = "Unglaublich...";
			link.l1.go = "WildRose_Abb_20";
			AddQuestRecordInfo("WildRose_Records_4", "1");
		break;

		case "WildRose_Abb_20":
			dialog.text = "Ob das Schiff sein Ziel erreichte, weiß ich nicht. Aber es machte Halt in Saint John's. Im Hafenamt ist ein Bericht von Kapitän Casper vom 2. Juni jenes Jahres erhalten geblieben.";
			link.l1 = "Ich wusste doch, dass Ihr nicht so einfach seid, wie Ihr Euch gebt, Vater! Dieses Dokument enthält sicher wichtige Informationen, oder?";
			link.l1.go = "WildRose_Abb_21_charisma";
			link.l2 = "Wir stehen tief in Eurer Schuld, Vater. Da Ihr dieses Dokument erwähnt habt – enthält es also etwas Wichtiges?";
			link.l2.go = "WildRose_Abb_21_honor";
			AddQuestRecordInfo("WildRose_Records_5", "1");
		break;

		case "WildRose_Abb_21_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Nur ein Bericht über das Gefecht mit der spanischen Galeone 'Toro' bei den Azoren, bei dem ein Drittel der Mannschaft starb – lies den Bericht, dort steht alles.";
			link.l1 = "Noch eine Frage: Wenn Ihr bereits die Unterlagen des Hafens von Antigua eingesehen habt – ist Euch der Name Joshua Casper vielleicht noch irgendwo anders begegnet?";
			link.l1.go = "WildRose_Abb_22";
		break;
		
		case "WildRose_Abb_21_honor":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Nur ein Bericht über das Gefecht mit der spanischen Galeone 'Toro' bei den Azoren, bei dem ein Drittel der Besatzung ums Leben kam – lies den Bericht, dort steht alles.";
			link.l1 = "Noch eine Frage: Da Sie die Aufzeichnungen der Hafenverwaltung von Antigua gesehen haben – ist Ihnen dort irgendwo der Name Joshua Casper begegnet?";
			link.l1.go = "WildRose_Abb_22";
		break;

		case "WildRose_Abb_22":
			dialog.text = "Du verlangst viel von mir, mein Sohn. Wenn du darauf hinauswillst, dass er den Schiffbruch überlebt hat und dann zur Marine zurückkehrte – daran zweifle ich sehr.";
			link.l1 = "Gottes Wege sind unergründlich, Vater.";
			link.l1.go = "WildRose_Abb_23";
		break;

		case "WildRose_Abb_23":
			dialog.text = "Wahrlich, mein Sohn. Doch siehst du – in seiner Personalakte steht, dass Joshua Casper im Jahr 1586 geboren wurde...";
			link.l1 = "Vielleicht haben Sie recht, Vater.";
			link.l1.go = "WildRose_Abb_24_fortune";
			link.l2 = "Wissen Sie, Vater, nach all den Jahren in der Karibik glaube ich selbst an die unglaublichsten Dinge.";
			link.l2.go = "WildRose_Abb_24_charisma";
		break;

		case "WildRose_Abb_24_fortune":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Gewiss, so ein Offizier verdiente es, im Kampf zu sterben. Aber wenn man es philosophisch betrachtet – war das in gewisser Weise auch ein Kampf...";
			link.l1 = "Mit Philosophie kenne ich mich nicht aus, Vater. Doch ich danke Ihnen für alles...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_24_charisma":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "Gewiss, so ein Offizier verdiente es, im Kampf zu sterben. Aber wenn man es philosophisch betrachtet – war das in gewisser Weise auch ein Kampf...";
			link.l1 = "Mit Philosophie kenne ich mich nicht aus, Vater. Doch ich danke Ihnen für alles...";
			link.l1.go = "WildRose_Abb_25";
		break;

		case "WildRose_Abb_25":
			dialog.text = "Der Herr führt euch auf diesem Weg, meine Kinder, und euch zu helfen ist meine bescheidene Pflicht. Doch fürchte ich, in dieser Angelegenheit kann ich euch nicht weiter unterstützen...";
			link.l1 = "Ich verstehe, Vater. Dann erlauben Sie uns, uns zu verabschieden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
		//--> Эпилог
		case "SharlieEpilog_Benua_1":
			dialog.text = "Ich bin tief besorgt über den Zustand deines Vaters. Ich weiß nicht, ob er es dir in seinem Brief offenbart hat, aber in seinem Schreiben an mich gestand er, dass seine körperlichen Kräfte ihn verlassen und er nicht glaubt, noch lange zu leben.";
			link.l1 = "Er erwähnte, dass die Krankheit nicht weicht... Doch von seinen Befürchtungen hat er offenbar geschwiegen.";
			link.l1.go = "SharlieEpilog_Benua_2";
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua");
		break;

		case "SharlieEpilog_Benua_2":
			dialog.text = "Mehr kann ich dir auch nicht sagen – das ist alles, was er mitteilte. Doch eines ist gewiss: er fürchtet, vor den Herrn zu treten, ohne dich noch einmal gesehen zu haben.";
			link.l1 = "Er sprach davon. Ehrlich gesagt, ich habe selbst daran gedacht, ihn zu besuchen... Aber...";
			link.l1.go = "SharlieEpilog_Benua_3";
		break;

		case "SharlieEpilog_Benua_3":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_1"))
			{
				dialog.text = "Mein Sohn, nur dem Herrn ist bekannt, wie viel Zeit jedem von uns bleibt. Verschiebe das Treffen nicht: Manchmal kann eine einzige Umarmung der Seele mehr Frieden bringen als tausend Gebete.";
				npchar.SharlieEpilog_BenuaRazgovor_1 = true;
			}
			else
			{
				dialog.text = ""+pchar.name+", ich hoffe, du wirst deinen Besuch bei ihm nicht weiter aufschieben? Denk daran, dass die Zeit gegen dich arbeitet...";
			}
			link.l1 = "Ihr habt recht, Abt. Ich werde sofort mit den Vorbereitungen zur Abreise beginnen. In Anbetracht meiner derzeitigen Stellung könnte es einige Zeit dauern, bis ich alles geregelt habe...";
			link.l1.go = "SharlieEpilog_Benua_5";
			link.l2 = "Ich verstehe eure Sorge, heiliger Vater, und verspreche, darüber nachzudenken. Aber im Moment habe ich wichtige Angelegenheiten zu regeln, die keinen Aufschub dulden. Wir werden später darauf zurückkommen.";
			link.l2.go = "SharlieEpilog_Benua_4_exit";
		break;

		case "SharlieEpilog_Benua_4_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_2");
		break;

		case "SharlieEpilog_Benua_5":
			dialog.text = "Wenn du Schulden hast, mein Sohn, würde ich dir empfehlen, mit deren Begleichung zu beginnen. Geldverleiher sind rachsüchtige Leute: Sie können deinem Ruf erheblichen Schaden zufügen – und damit dem guten Namen deiner ganzen Familie, selbst in der Alten Welt\n"+
			"Was den Rest betrifft – im Namen meiner Freundschaft mit deinem Vater und zur Ehre des Herrn – werde ich dir jegliche Unterstützung zukommen lassen. Du kannst schriftlich die nötigen Anweisungen erteilen, und ich werde dafür sorgen, dass sie rechtzeitig die Empfänger erreichen. Du musst lediglich die Kurierdienste bezahlen. Ich denke, zweihundert Dublonen sollten für die Zustellung aller Schreiben genügen.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Ich danke euch, heiliger Vater. Eure Hilfe kommt mir sehr gelegen. Hier, bitte.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Danke für eure Anteilnahme, heiliger Vater. Leider habe ich im Moment nicht die erforderliche Summe bei mir. Wir werden zu dieser Frage später zurückkehren.";
			link.l2.go = "SharlieEpilog_Benua_DublonsLater";
			SharlieEpilog_Benua_Dlg_1();
		break;

		case "SharlieEpilog_Benua_DublonsLater":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_DlgExit_3");
		break;

		case "SharlieEpilog_Benua_DublonsLater_2":
			dialog.text = "Natürlich, "+pchar.name+". Ich nehme an, du hast die zweihundert Dublonen mitgebracht?";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Selbstverständlich. Hier, bitte.";
				link.l1.go = "SharlieEpilog_Benua_6";
			}
			link.l2 = "Leider habe ich die nötige Summe noch nicht.";
			link.l2.go = "exit";
		break;

		case "SharlieEpilog_Benua_6":
			dialog.text = "Ausgezeichnet, mein Sohn.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			RemoveDublonsFromPCharTotal(200);
			DeleteAttribute(pchar, "questTemp.SharlieEpilog_Benua_DublonsLater");
		break;
		
		case "SharlieEpilog_Benua_Delivery":
			if (!CheckAttribute(npchar, "SharlieEpilog_BenuaRazgovor_2"))
			{
				dialog.text = "Also, womit möchtest du beginnen?";
				npchar.SharlieEpilog_BenuaRazgovor_2 = true;
			}
			else
			{
				dialog.text = "Wen und worüber möchtest du informieren?";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona"))
			{
				link.l1 = "Einst fand ich eine Insel, die auf keiner Karte verzeichnet war. Dort lebten bereits einige Siedler, über die ich die Schirmherrschaft übernahm. Da ich nun abreise, braucht die Insel einen neuen 'Gouverneur'.";
				link.l1.go = "SharlieEpilog_Benua_IslaMona";
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Baron"))
			{
				link.l2 = "Ich möchte einen Brief an Marcus Tirax in La Vega senden. Es ist keine dringliche Angelegenheit, aber das Schreiben muss pünktlich zugestellt werden.";
				link.l2.go = "SharlieEpilog_Benua_Baron";
			}
			if (CheckCharacterItem(PChar, "patent_fra") && !CheckAttribute(pchar, "questTemp.SharlieEpilog_Patent"))
			{
				link.l3 = "Ich habe ein gültiges Patent von Frankreich – ich möchte die Kanzlei von Capsterville über meine Entscheidung informieren.";
				link.l3.go = "SharlieEpilog_Benua_Patent";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Money"))
			{
				link.l4 = "Heiliger Vater, in all den Jahren, die ich in diesem Land verbracht habe, konnte ich ein beachtliches Vermögen ansammeln. Doch bevor es meiner Familie zufällt, möchte ich es... reinigen. Das Blut abwaschen, mit dem es vielleicht befleckt ist. Ich will dieses Land nicht als Räuber mit Beute verlassen, sondern als jemand, dessen Gewissen und Ruf vor der Gesellschaft rein sind.";
				link.l4.go = "SharlieEpilog_Benua_Money";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Svenson") && CheckAttribute(pchar, "questTemp.SharlieEpilog_IslaMona_France"))
			{
				link.l5 = "Ich möchte Jan Svenson in Blueweld über meine Abreise informieren. Es wäre unhöflich, den Archipel zu verlassen, ohne ihn zu benachrichtigen.";
				link.l5.go = "SharlieEpilog_Benua_Svenson";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Houk"))
			{
				link.l6 = "Ich möchte der Familie Hawke aus Maroon Town von meiner Reise berichten.";
				link.l6.go = "SharlieEpilog_Benua_Houk";
			}
			if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_Jino"))
			{
				link.l7 = "Ich möchte Gino Guineilli aus Saint John's über meine Abreise in die Alte Welt informieren.";
				link.l7.go = "SharlieEpilog_Benua_Jino";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_S") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_M") || CheckAttribute(pchar, "questTemp.SharlieEpilog_gold_L"))
			{
				link.l85 = "Das war’s dann, Vater... Es scheint, ich bin bereit, die Reise anzutreten.";
				link.l85.go = "SharlieEpilog_Benua_TimeToGoHome";
			}
			link.l99 = "Verzeiht, heiliger Vater, ich muss jetzt gehen.";
			link.l99.go = "SharlieEpilog_exit";
		break;
		
		case "SharlieEpilog_exit":
			DialogExit();
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "First time";
		break;
		
		case "SharlieEpilog_Benua_Jino":
			dialog.text = "Natürlich, mein Sohn.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Jino_2";
			pchar.questTemp.SharlieEpilog_Jino = true;
		break;

		case "SharlieEpilog_Benua_Jino_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Jino_3";
			AddQuestRecord("SharlieEpilog", "8_1");
		break;

		case "SharlieEpilog_Benua_Jino_3":
			dialog.text = "...";
			link.l1 = "Erledigt. Es kann abgeschickt werden.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Houk":
			dialog.text = "Natürlich, mein Sohn.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Houk_2";
			pchar.questTemp.SharlieEpilog_Houk = true;
		break;

		case "SharlieEpilog_Benua_Houk_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Houk_3";
			AddQuestRecord("SharlieEpilog", "8");
		break;

		case "SharlieEpilog_Benua_Houk_3":
			dialog.text = "...";
			link.l1 = "Erledigt. Es kann abgeschickt werden.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Svenson":
			dialog.text = "Jan Svenson aus Blueweld... Ich werde es mir merken. Gib mir den Brief – er wird noch heute auf den Weg gebracht.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Svenson_2";
			pchar.questTemp.SharlieEpilog_Svenson = true;
		break;

		case "SharlieEpilog_Benua_Svenson_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Svenson_3";
			AddQuestRecord("SharlieEpilog", "7");
		break;

		case "SharlieEpilog_Benua_Svenson_3":
			dialog.text = "...";
			link.l1 = "Jans Haus zu finden ist einfach. Man muss nur einen der Einwohner fragen – es gibt wohl kaum jemanden in ganz Blueweld, der nicht weiß, wer er ist und wo er wohnt.";
			link.l1.go = "SharlieEpilog_Benua_Svenson_4";
		break;

		case "SharlieEpilog_Benua_Svenson_4":
			dialog.text = "Sorge dich nicht, mein Sohn, unsere Leute verstehen ihr Handwerk. Der Brief wird den richtigen Empfänger erreichen – und das rechtzeitig.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money":
			dialog.text = "Du möchtest, dass die Kirche Gold segnet, das durch Verbrechen erworben wurde?";
			link.l1 = "Sagen wir eher – durch den Dienst an Frankreich und Seiner Majestät.";
			link.l1.go = "SharlieEpilog_Benua_Money_2";
		break;

		case "SharlieEpilog_Benua_Money_2":
			dialog.text = "Ich verstehe dich, mein Sohn. Ich könnte sagen, dass die Kirche kein Geld reinwäscht und nichts an der Art ändert, wie es erlangt wurde. Doch was nützt das, wenn die Hungrigen weiter hungern, die Obdachlosen weiter unter freiem Himmel schlafen und die Kranken ohne Hilfe sterben? Ich bin bereit, meinen Segen zu geben – unter der Bedingung, dass ein kleiner Teil dieses Vermögens nicht dir, sondern den Bedürftigen zugutekommt.";
			link.l1 = "Selbstverständlich, heiliger Vater, ich bin bereit zu spenden, wie ihr es für richtig haltet.";
			link.l1.go = "SharlieEpilog_Benua_Money_3";
		break;

		case "SharlieEpilog_Benua_Money_3":
			dialog.text = "Also, welche Summe möchtest du mit dir nehmen?";
			link.l1 = "Zehn Millionen Pesos.";
			link.l1.go = "SharlieEpilog_Benua_Money_4";
			if (sti(pchar.Money) >= 250000)
			{
				link.l2 = "Fünfundzwanzig Millionen Pesos.";
				link.l2.go = "SharlieEpilog_Benua_Money_5";
			}
			if (sti(pchar.Money) >= 500000)
			{
				link.l3 = "Fünfzig Millionen Pesos.";
				link.l3.go = "SharlieEpilog_Benua_Money_6";
			}
		break;
		
		case "SharlieEpilog_Benua_Money_4":
			dialog.text = "In diesem Fall wird eine Spende von hunderttausend Pesos ausreichen. Mit diesem Geld können wir noch viele Monate lang Mahlzeiten für Bedürftige bereitstellen. Bist du bereit, diesen Betrag sofort zu entrichten, mein Sohn?";
			link.l1 = "Selbstverständlich. Hier, bitte. Ich helfe gern denen, die es wirklich nötig haben, und bin sicher, dass dieses Geld unter eurer Aufsicht mit Weisheit und Ehre eingesetzt wird.";
			link.l1.go = "SharlieEpilog_Benua_Money_4_1";
			link.l2 = "Verzeiht, ich muss noch einmal gründlich darüber nachdenken.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_5":
			dialog.text = "In diesem Fall sollte deine Spende zweihundertfünfzigtausend Pesos betragen. Diese Mittel werden es uns ermöglichen, ein Waisenhaus zu errichten, das deinen Namen tragen und zumindest in der Anfangszeit für seine Bedürfnisse sorgen wird. Bist du bereit, diesen Betrag sofort zu entrichten, mein Sohn?";
			link.l1 = "Selbstverständlich. Hier, bitte. Ich helfe gern denen, die es wirklich nötig haben, und bin sicher, dass dieses Geld unter eurer Aufsicht mit Weisheit und Ehre eingesetzt wird.";
			link.l1.go = "SharlieEpilog_Benua_Money_5_1";
			link.l2 = "Verzeiht, ich muss noch einmal gründlich darüber nachdenken.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_6":
			dialog.text = "Nun, es scheint, du hast deine Zeit nicht vergeudet, "+pchar.name+". Ich denke, eine Spende von fünfhunderttausend Pesos wird völlig ausreichend sein. Dank eines solchen Beitrags können wir ein Hospital errichten und es für viele Jahre mit allem Notwendigen ausstatten. Bist du bereit, diesen Betrag sofort zu entrichten, mein Sohn?";
			link.l1 = "Selbstverständlich. Hier, bitte. Ich helfe gern denen, die es wirklich nötig haben, und bin sicher, dass dieses Geld unter eurer Aufsicht mit Weisheit und Ehre eingesetzt wird.";
			link.l1.go = "SharlieEpilog_Benua_Money_6_1";
			link.l2 = "Verzeiht, ich muss noch einmal gründlich darüber nachdenken.";
			link.l2.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Money_4_1":
			dialog.text = "Ausgezeichnet, mein Sohn.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -100000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "10000000");
			AddQuestUserData("SharlieEpilog", "tSum", "100000");
			pchar.questTemp.SharlieEpilog_gold_S = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_5_1":
			dialog.text = "Ausgezeichnet, mein Sohn.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -250000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "25000000");
			AddQuestUserData("SharlieEpilog", "tSum", "250000");
			pchar.questTemp.SharlieEpilog_gold_M = true;
			pchar.questTemp.SharlieEpilog_Money = true;
		break;

		case "SharlieEpilog_Benua_Money_6_1":
			dialog.text = "Ausgezeichnet, mein Sohn.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
			AddMoneyToCharacter(pchar, -500000);
			AddQuestRecord("SharlieEpilog", "6");
			AddQuestUserData("SharlieEpilog", "sSum", "50000000");
			AddQuestUserData("SharlieEpilog", "tSum", "500000");
			pchar.questTemp.SharlieEpilog_gold_L = true;
			pchar.questTemp.SharlieEpilog_Money = true;
			Achievment_Set("ach_CL_205");
		break;

		case "SharlieEpilog_Benua_Patent":
			dialog.text = "Wie soll deine Entscheidung ausfallen, mein Sohn?";
			link.l1 = "Obwohl mich eine lange Reise erwartet, möchte ich mein Patent behalten – ebenso wie meine Treue zu Frankreich und zum König.";
			link.l1.go = "SharlieEpilog_Benua_Patent_2";
			link.l2 = "Ich habe beschlossen, auf das Patent zu verzichten. Ein langer Weg liegt vor mir, und ich weiß nicht, wann ich zurückkehren werde. Es erscheint mir vernünftiger, die Last dienstlicher Pflichten und Regeln nicht mit mir zu tragen, denen ich womöglich nicht gerecht werden kann.";
			link.l2.go = "SharlieEpilog_Benua_Patent_6";
			pchar.questTemp.SharlieEpilog_Patent = true;
		break;

		case "SharlieEpilog_Benua_Patent_2":
			dialog.text = "Ich bin froh, dass du zu dieser Entscheidung gelangt bist, mein Sohn. Unserem Reich fehlen heute mehr denn je starke und mutige Ritter. Doch sag mir, "+pchar.name+", ist dir nie der Gedanke gekommen, sesshaft zu werden, ein Heim zu finden und nicht mehr jede Stunde dein Leben zu riskieren? Denn der Mensch ist nicht dazu bestimmt, sich ewig im Feuer zu prüfen.";
			link.l1 = "Ich bin mir nicht sicher, ob ich einfach untätig bleiben könnte, heiliger Vater. Doch wie es in der Schrift heißt: 'Auch den Kriegern des Herrn ist Ruhe gewährt, wenn ihr Werk vollendet ist'. So fern ich auch vom Abschluss meines Wirkens sein mag, hoffe ich doch, den Tag selbst zu wählen, an dem ich mein Schwert für immer in die Scheide lege.";
			link.l1.go = "SharlieEpilog_Benua_Patent_3";
		break;

		case "SharlieEpilog_Benua_Patent_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_4";
			AddQuestRecord("SharlieEpilog", "5_2");
		break;

		case "SharlieEpilog_Benua_Patent_4":
			dialog.text = "Ausgezeichnet, mein Sohn. Ich denke, Seine Majestät wird deine Treue und Hingabe nicht unbeachtet lassen.";
			link.l1 = "Meine Gedanken sind im Moment ganz woanders... Ich hoffe, mein Vater wird nicht darauf bestehen, dass ich auf unserem Gut bleibe. Ich glaube nicht, dass ich dafür bereit bin. Doch glücklicherweise werde ich genügend Zeit haben, darüber nachzudenken.";
			link.l1.go = "SharlieEpilog_Benua_Patent_5";
		break;

		case "SharlieEpilog_Benua_Patent_5":
			dialog.text = "...";
			link.l1 = "Nun denn, kehren wir zu den weltlichen Angelegenheiten zurück.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Patent_6":
			dialog.text = "Nun gut, das ist eine vernünftige Entscheidung. Dennoch muss ich anmerken: Dein Weggang wird die Stärke Frankreichs in diesen Gewässern erheblich schwächen.";
			link.l1 = "Ich bin sicher, dass es unter dem Kommando Seiner Majestät genügend würdige Kapitäne gibt, damit die Größe Frankreichs nicht ins Wanken gerät.";
			link.l1.go = "SharlieEpilog_Benua_Patent_7";
		break;
		
		case "SharlieEpilog_Benua_Patent_7":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Patent_8";
			AddQuestRecord("SharlieEpilog", "5_1");
		break;

		case "SharlieEpilog_Benua_Patent_8":
			dialog.text = "...";
			link.l1 = "Das wäre erledigt. Ein Gewicht scheint von meinen Schultern genommen. Ehrlich gesagt habe ich vergessen, wer ich war, als ich hier in die Karibik kam... So viel ist geschehen.";
			link.l1.go = "SharlieEpilog_Benua_Patent_9";
		break;

		case "SharlieEpilog_Benua_Patent_9":
			dialog.text = "Vielleicht hast du das schon oft gehört, mein Sohn: Die Wege des Herrn sind unergründlich. Alles, was dir von oben bestimmt war, hast du mit Würde durchgestanden. Doch ich glaube, deine Prüfungen sind noch nicht vorbei, und vielleicht beginnt dein Ruhm gerade erst, seinem Höhepunkt entgegenzusteigen.";
			link.l1 = "Ruhm belastet, heiliger Vater. Nicht jeder, der ihn sucht, ist imstande, sein Gewicht zu tragen... und rechtzeitig innezuhalten.";
			link.l1.go = "SharlieEpilog_Benua_Patent_10";
		break;

		case "SharlieEpilog_Benua_Patent_10":
			dialog.text = "...";
			link.l1 = "Nun denn, kehren wir zu weltlichen Angelegenheiten zurück.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron":
			dialog.text = "Mein Sohn, hast du Angelegenheiten mit dem Anführer der Piraten?";
			link.l1 = "Kennen Sie den Hüter des Kodex?";
			link.l1.go = "SharlieEpilog_Benua_Baron_2";
			pchar.questTemp.SharlieEpilog_Baron = true;
		break;

		case "SharlieEpilog_Benua_Baron_2":
			dialog.text = "Den Hüter des Kodex? Nein, mit ihm bin ich nicht bekannt. Ich kenne Marcus Tirax – den Henker, hinter dessen Rücken so viel Blut ist, dass selbst Hunderte Jahre im Gebet nicht ausreichen würden, um die Vergebung des Herrn zu erlangen. Und doch... hast du wirklich Geschäfte mit ihm?";
			link.l1 = "Ich musste mir seine Gunst verdienen... um Michel aus dem Gefängnis zu befreien. Wie dem auch sei, ich habe meinen Fehler erkannt und habe nicht die Absicht, mit ihm weiterhin in Verbindung zu stehen. Mit diesem Brief werde ich den letzten Faden trennen, der uns verbindet.";
			link.l1.go = "SharlieEpilog_Benua_Baron_3";
			link.l2 = "Das ist jetzt nicht mehr wichtig. Ich verlasse den Archipel, und unsere Wege werden sich von selbst trennen, heiliger Vater.";
			link.l2.go = "SharlieEpilog_Benua_Baron_7";
		break;

		case "SharlieEpilog_Benua_Baron_3":
			dialog.text = "Und was ist das für ein Faden, mein Sohn? Ich hoffe, er ist nicht mit dem Blut Unschuldiger befleckt?";
			link.l1 = "Offiziell war ich als Anführer der Piratensiedlung Le François geführt. In Wahrheit aber herrschte ein anderer Mann darüber. Heute verzichte ich auf den Titel des Piratenbarons – endgültig und unwiderruflich.";
			link.l1.go = "SharlieEpilog_Benua_Baron_4";
		break;

		case "SharlieEpilog_Benua_Baron_4":
			dialog.text = "Ich bin froh, dass du den rechten Weg eingeschlagen hast, mein Sohn, und ich werde für das Heil deiner Seele beten. Jeder kann einen Fehltritt begehen, aber der Herr vergibt nur denen, deren Reue aufrichtig ist.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Baron_5";
		break;

		case "SharlieEpilog_Benua_Baron_5":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_6";
			AddQuestRecord("SharlieEpilog", "4_1");
		break;

		case "SharlieEpilog_Benua_Baron_6":
			dialog.text = "Ausgezeichnet, "+pchar.name+". Übergib mir den Brief – ich werde dafür sorgen, dass er den Empfänger erreicht. Und vergiss nicht zu beten, mein Sohn. Nur Reue und Gebet können selbst die schwersten Sünden von der Seele waschen.";
			link.l1 = "Danke, heiliger Vater. Vielleicht ist für mich doch noch nicht alles verloren.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_Baron_7":
			dialog.text = "So groß auch die Sünde sein mag, mein Sohn, die Türen der Vergebung sind stets offen. Reue, Gebet und gute Taten reinigen die Seele, wie der Regen den Staub vom Stein wäscht.";
			link.l1 = "Alles zu seiner Zeit, heiliger Vater. Jetzt muss ich mich um weltliche Angelegenheiten kümmern.";
			link.l1.go = "SharlieEpilog_Benua_Baron_8";
		break;
		
		case "SharlieEpilog_Benua_Baron_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_Baron_9";
			AddQuestRecord("SharlieEpilog", "4_2");
		break;
		
		case "SharlieEpilog_Benua_Baron_9":
			dialog.text = "...";
			link.l1 = "Nehmt es bitte.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona":
			dialog.text = "Es ist gut, mein Sohn, dass du dich um diese Menschen sorgst und sie nicht vergessen hast. Wem möchtest du diese Insel anvertrauen?";
			link.l1 = "Ich denke, über ihr sollte die französische Flagge wehen. Früher oder später wird die Insel entdeckt, und andere Nationen könnten versuchen, sie sich anzueignen. Das darf ich nicht zulassen.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France";
			link.l2 = "Diese Insel und ihre Bewohner verdienen es, frei zu leben und nicht unter der Herrschaft eines Königs. Ich werde meinem Freund Jan Svenson aus Blueweld schreiben. Ich bin sicher, er wird sich bereit erklären, sich um dieses Land zu kümmern. Ich bitte Euch, heiliger Vater, dieses Gespräch geheim zu halten – zum Schutz und Wohl dieser Menschen.";
			link.l2.go = "SharlieEpilog_Benua_IslaMona_Pirate";
			pchar.questTemp.SharlieEpilog_IslaMona = true;
		break;

		case "SharlieEpilog_Benua_IslaMona_France":
			dialog.text = "Du handelst klug, "+pchar.name+". Unter dem Schutz des Königs wird diese Insel Ordnung und Sicherheit finden.";
			link.l1 = "Ich werde ein entsprechendes Schreiben an die Kanzlei in Capsterville und an die Menschen auf der Insel senden. Die Koordinaten stehen auf dem Umschlag.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_France_3";
			pchar.questTemp.SharlieEpilog_IslaMona_France = true;
			AddQuestRecord("SharlieEpilog", "3_1");
		break;

		case "SharlieEpilog_Benua_IslaMona_France_3":
			dialog.text = "...";
			link.l1 = "Bitte sehr. Ich hoffe, eure Leute erreichen die Insel, bevor die königliche Flotte eintrifft.";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_France_4";
		break;

		case "SharlieEpilog_Benua_IslaMona_France_4":
			dialog.text = "Keine Sorge, mein Sohn. Ich werde die Zustellung dieser Briefe den besten Kurieren anvertrauen.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate":
			dialog.text = "Es steht mir nicht zu, deinen Weg zu beurteilen, mein Sohn. Früher oder später wird jemand diese Insel entdecken, und irgendeine Nation wird Anspruch auf sie erheben wollen. Das ist nur eine Frage der Zeit. Doch wenn du diese Entscheidung getroffen hast – dann ist es wohl Gottes Wille. Keine Sorge: Ich werde diese Menschen nicht in Gefahr bringen und ein Gebet für sie sprechen.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Benua_IslaMona_Pirate_2";
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_2":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Benua_TimeLater_1");
			NextDiag.CurrentNode = "SharlieEpilog_Benua_IslaMona_Pirate_3";
			pchar.questTemp.SharlieEpilog_IslaMona_Pirate = true;
			AddQuestRecord("SharlieEpilog", "3_2");
		break;

		case "SharlieEpilog_Benua_IslaMona_Pirate_3":
			dialog.text = "Jan Svenson aus Blueweld, richtig?";
			link.l1 = "Ganz genau, heiliger Vater. Und der zweite Brief muss direkt auf die Insel gebracht werden. Die Koordinaten stehen auf dem Umschlag.";
			link.l1.go = "SharlieEpilog_Benua_Delivery";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome":
			dialog.text = "Wunderbar, mein Sohn. Wenn ich mich nicht irre, bist du auf der Pinasse '"+GetShipName("Ulysse")+"' hierhergekommen?";
			link.l1 = "Das stimmt. Aber warum fragt Ihr?";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_2";
		break;

		case "SharlieEpilog_Benua_TimeToGoHome_2":
			dialog.text = "Weil dieses Schiff kürzlich versteigert wurde. Und du, Charles, hast die Möglichkeit, auf demselben Schiff nach Hause zurückzukehren – nur diesmal als Kapitän.";
			link.l1 = "Hm... Ich muss zugeben, das Angebot ist verlockend. Vielleicht sollte ich das Hafenamt aufsuchen. Danke, heiliger Vater.";
			link.l1.go = "SharlieEpilog_Benua_TimeToGoHome_3";
		break;
		
		case "SharlieEpilog_Benua_TimeToGoHome_3":
			DialogExit();
			NextDiag.CurrentNode = "First Time";
			AddDialogExitQuestFunction("SharlieEpilog_PU_Ulysse_1");
		break;
		//<-- Эпилог
		
		case "LH_abbat_38":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
