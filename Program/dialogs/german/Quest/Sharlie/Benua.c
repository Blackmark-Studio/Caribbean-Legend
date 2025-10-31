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
			else
			{
				link.l1 = "Nein, Vater, ich habe das Geld gerade nicht bei mir. Aber ich kehre bald zurück und bringe es mit.";
				link.l1.go = "WildRose_Abb_14_nopay";
			}
		break;

		case "WildRose_Abb_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Sehr gut, "+pchar.name+". Komm in zwei Monaten wieder – ich bin sicher, dass ich bis dahin eine Antwort für dich habe.";
			link.l1 = "Danke, Vater. Auf bald!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap3_Benua_2");
		break;

		case "WildRose_Abb_14_nopay":
			dialog.text = "Wie du meinst, mein Sohn.";
			link.l1 = "Ich komme bald wieder.";
			link.l1.go = "exit";
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
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_5");
		break;
		//<-- Дикая Роза
		
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
