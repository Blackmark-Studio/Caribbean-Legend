// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen?"),"Du hast versucht, mir diese Frage vor nicht allzu langer Zeit zu stellen...","Ja, lass mich raten... Wieder mal im Kreis unterwegs?","Hör zu, ich mache die Finanzen hier, ich beantworte keine Fragen...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Ich habe im Moment nichts zu besprechen."),"Hmm, wo ist mein Gedächtnis hin...","Du hast es erraten, es tut mir leid...","Ich verstehe...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Werfen Sie einen Blick auf diese Ohrringe, Monsieur. Ich habe sie in der Tasche eines Banditen im Dschungel gefunden. Dies ist eindeutig die Arbeit eines feinen Juweliers, der, da bin ich mir sicher, nicht aus dieser Wildnis stammt. Was sagen Sie dazu?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "Ich weiß, dass Sie einen Schuldner namens Folke Deluc haben. Sagen Sie mir, wie schlimm ist seine... Verzug?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Ich bin hier wegen Folke Delucs Schulden.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "Ich habe Ihren Auftrag erledigt, Monsieur. Hier ist Ihr... spanischer Freund.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "Ich bin hier wegen...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "Haben Sie 100 Dublonen mitgebracht?";
				if (PCharDublonsTotal() >= 100)
				{
					link.l1 = "Hier ist Ihr Geld für meinen Offizier...";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "Nein, ich denke noch nach.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Und warum kümmert es Sie, darf ich fragen?";
			link.l1 = "Ich brauche diesen Mann frei, nicht hinter Gittern. Und soweit ich informiert wurde, wird er nicht freigelassen, bis diese Schuld Ihnen zurückgezahlt wird. Ich bin daran interessiert, diese Schuld zu begleichen.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Aha, das ändert alles. Ich bin auch daran interessiert, dass mein Geld zu mir zurückkehrt... Dieser Folke Deluc ist ein seltsamer Kerl. Er hat eine relativ kleine Summe Geld geliehen - fünftausend Pesos. Er wollte es einfach nicht zurückgeben und fing an, sich zu verstecken. Am Ende stieg die Zinsen bis zum Preis der ursprünglichen Schuld und er fand sich hinter Gittern wieder.";
			link.l1 = "Es folgt also, dass seine Schuld derzeit auf zehntausend angesammelt hat?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Genau zehntausendvierhundertfünfzig Pesos, mein Herr. So wird seine Freiheit zu diesem Preis bewertet. Sind Sie bereit, es mir zu zahlen? Ich bin ein wenig überrascht...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Wundere dich nicht. Hier ist das Geld.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Hm... In der Tat eine stattliche Summe. Hör zu, mein Herr, vielleicht sollten Sie und ich versuchen, einen Deal zu machen? Beispielsweise haben Sie etwas, um das ich mich kümmern könnte und Sie könnten meinen Gefallen auf diese zehntausendfünfhundert bewerten...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Ja, es scheint, dass Sie diesen Seemann wirklich brauchen, wenn Sie bereit sind, eine solche Summe Geld für ihn auszugeben. Wie auch immer, es geht mich nichts an, oder Herr? Hier ist seine Schuldschein, jetzt haben Sie Anspruch auf seine Schuld und das Recht, Geld von ihm zu verlangen. Nun, und natürlich können Sie seine Freilassung aus dem Gefängnis beantragen.";
			link.l1 = "Das ist genau das, was ich wollte. Auf Wiedersehen, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "Eine Gefälligkeit? Ach, ich brauche keine Gefälligkeiten von dir. Zumindest vorerst.";
			link.l1 = "Schade. Dann sollte ich das Geld für Folke bringen. Tschüss!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Gefallen? Hm... Wissen Sie, mein Herr, ich hätte Ihnen gestern eine negative Antwort gegeben, aber jetzt... ja, ich habe etwas, das erledigt werden muss, aber ich warne Sie, es ist ziemlich gefährlich.";
			link.l1 = "Gefährlich für was?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Für dein kostbares Leben, natürlich. Also denk darüber nach, bevor du zustimmst und entscheide, ob du bereit bist, so etwas zu tun oder nicht.";
			link.l1 = "Herr, Gefahr ist mir nicht fremd. Ich war schon so oft in gefährlichen Situationen. Also, lass uns ins Detail gehen. Solange es nicht darum geht, die ganze Garnison des Forts im Alleingang auszuschalten, könnte ich vielleicht in der Lage sein, das zu erreichen, was Sie so geheimnisvoll andeuten.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Gut. Hör zu. Heute Abend werden mehrere Piraten und ein Gefangener das Piratennest von Le Francois verlassen und zur Bucht von Le Marin gehen. Der Gefangene ist ein spanischer Offizier und ein hervorragender Experte für Festungsingenieurwesen. Die Briten beabsichtigen, ihn für ihre eigenen Zwecke zu nutzen, daher werden sie ein Kriegsschiff schicken, um den Mann aus der Bucht abzuholen\nDer Offizier ist mein alter Freund und ich möchte nicht, dass er als englischer Gefangener endet. Ich kann die örtlichen Behörden nicht um Hilfe bitten, weil wir mit Spanien im Krieg sind. Hätte ich mehr Zeit, würde ich Männer einstellen, die in der Lage sind, den Spanier... Entschuldigung, meinen Freund zurückzuholen, aber leider!\nDu bist der einzige Mann, dem ich diesen Job anvertrauen kann. Du musst zur Bucht von Le Marin gehen und... die Piraten überzeugen, den Gefangenen dir zu übergeben. Ich bezweifle, dass sie viel Kooperation zeigen werden, also liegt es an dir.";
			link.l1 = "Wie viele Piraten werden im Konvoi sein?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "Ich weiß es nicht. Vielleicht zwei Personen, vielleicht drei oder vier. Nun, was würden Sie sagen?";
			link.l1 = "Ich habe dir bereits gesagt, 'Gefahr ist für mich kein Fremder' und ich weiß, von welcher Seite man ein Schwert halten muss.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Hm. Du hast recht, es ist gefährlich. Ich werde eine Piratencrew nicht alleine angreifen.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Das ist Ihre Entscheidung. Wenn Sie glauben, dass Sie dieser Aufgabe nicht gewachsen sind, sollten Sie besser sofort ablehnen. Dann werde ich auf Delucs Schuldgeld warten.";
			link.l1 = "In Ordnung. Ich bringe das Geld für ihn. Bis später!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Sehr gut. Schön das zu hören. Dann sollten Sie zur Bucht von Le Marin gehen, die Piraten werden dort von sieben Uhr abends bis vier Uhr morgens sein. Verpassen Sie sie nicht! Und denken Sie nicht einmal daran, ein Schiff zu benutzen! Solche Aktionen werden sie verschrecken, gehen Sie durch den Dschungel!\nBringen Sie den Gefangenen zu mir, wenn Sie ihn finden, ich werde die Tür offen halten. Ich empfehle, bis ein Uhr morgens zu warten, bevor Sie in die Stadt zurückkehren, weil Sie die Aufmerksamkeit der Wachen vermeiden müssen. Seien Sie vorsichtig und viel Glück!";
			link.l1 = "Danke! Ich werde definitiv etwas Glück brauchen...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Warte eine Minute! Ich sehe, du hast nicht einmal eine Pistole. Nimm eine von mir. Ich habe auch einige Kugeln dafür. Ich denke, es wird dir nützlich sein.";
			link.l1 = "Ja, das wird definitiv nützlich sein. Danke, Monsieur.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("You have received a combat pistol");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "Und jetzt geh, möge Gott dir helfen!";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Wunderbar! Ich bin sehr erfreut, dass Sie es erfolgreich bewältigen konnten. Ich nehme an, ich muss die Einzelheiten der Operation nicht wissen, oder? Also, mein lieber spanischer Gast kann sich jetzt sicher in meinem Haus fühlen...";
			link.l1 = "Was ist mit Folke Delucs Schulden?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Natürlich, ja. Nehmen Sie seine Schuldanerkennung, jetzt haben Sie das Recht auf seine Schulden und dürfen ihm Geld abverlangen. Nun, und natürlich, beantragen Sie seine Freilassung aus dem Gefängnis. Habe ich alles wie versprochen erledigt?";
			link.l1 = "Ja, Monsieur. Alles ist streng nach der Vereinbarung. Erlauben Sie mir jetzt, mich zu verabschieden.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "Also, sind Sie bereit, seine Schuld zu begleichen?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Ja. Hier ist das Geld.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Leider habe ich immer noch nicht die erforderliche Summe gesammelt...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Hm. Es scheint, du hast Recht, das sind teure Ohrringe und sie wurden sicherlich in der Alten Welt hergestellt... Was soll ich sagen? Ich gebe dir dafür dreißig... nein, sogar fünfunddreißig Gold-Doubloons. Nimm das Geld, du wirst sie nicht für mehr verkaufen.";
			link.l1 = "Dreißig fünf Dublonen? Das ist kein schlechter Preis. Ich stimme zu. Hier, bitte.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Nein. Ich denke, ich behalte diese Ohrringe für mich selbst.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "Ich weiß, ich weiß, Kapitän. Ihr Navigator scheint Schulden in fast jeder französischen Kolonie angehäuft zu haben. Um ehrlich zu sein, ich wusste es schon lange. Ich habe mit meinen Kollegen nachgeprüft, eine Standardprozedur, verstehen Sie...";
			link.l1 = "Und Sie dachten nicht, dass es wichtig genug war, mich während unserer vorherigen Vereinbarung zu informieren?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Warum? Damals war ich hauptsächlich mit Delucs Schulden bei mir beschäftigt, die übrigens die größten waren. Sobald du das geregelt hast, habe ich meine Kollegen umgehend benachrichtigt... Wir haben eine riesige Flotte von professionellen Kurieren, so dass es nicht lange dauerte, bis ich einen Haufen von Delucs Rechnungen auf meinem Schreibtisch hatte.";
			link.l1 = "Ich verstehe... Sie haben sie gekauft, wissend, dass ich ein lebenswichtiges Interesse an ihm habe und Mittel zum Bezahlen... Das ist Erpressung, Monsenior.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Es ist nur Geschäft, Kapitän! Delucs Gesamtschulden betragen hundert Dublonen und Zinsen häufen sich... Sind Sie bereit, es auszukaufen?";
			link.l1 = "Ich bin noch nicht bereit zu antworten, aber ich werde es in Betracht ziehen. Auf Wiedersehen!";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Ausgezeichnet! Sie wissen, was als nächstes zu tun ist - genau wie beim letzten Mal. Hier sind die Dokumente - übergeben Sie sie dem Gefängniskommandanten. Es war mir ein Vergnügen, Geschäfte mit Ihnen zu machen, Kapitän.";
			link.l1 = "Es gibt wenig an dieser Situation zu genießen. Auf Wiedersehen.";
			link.l1.go = "exit";
			RemoveItems(pchar, "gold_dublon", 100);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
