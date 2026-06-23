// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was wünschen Sie? Fragen Sie los.","Ich höre Ihnen zu, was ist die Frage?"),"Dies ist das zweite Mal, dass Sie versuchen zu fragen...","Das ist das dritte Mal, dass Sie versuchen zu fragen...","Wann wird das endlich aufhören?! Ich bin ein beschäftigter Mann, der sich um Kolonialangelegenheiten kümmert und Sie belästigen mich immer noch!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt. Falscher Ort und Zeit."),"Wahr... Aber später, nicht jetzt...","Ich werde fragen... Aber ein bisschen später...","Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "Eure Exzellenz, ich möchte über illegale Handelsaktivitäten auf dieser Insel berichten.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "Ich möchte einen Bericht über Ihre Mission bezüglich des Schmuggels von Seiden-Segeltuch hören.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "Ich bin im Auftrag des Generalgouverneurs Phillipe de Poincy angekommen. Meine Aufgabe ist es, Ihnen die von den Holländern gefangenen Sklaven zu bringen, ist das richtig?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "Ich habe Ihnen die Sklaven gebracht, wie vereinbart.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "Ich bin auf Anweisung des Gouverneurs-Generals Phillipe de Poincy angekommen, um an einer gemeinsamen Expedition nach Curacao gegen die Holländer teilzunehmen.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "Mein Geschwader wurde reduziert, wir können jetzt aufbrechen.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Interessant. Ich bin ganz Ohr.";
			link.l1 = "Ich habe aus zuverlässiger Quelle erfahren, dass die niederländische Brigantine 'Utrecht' unter englischer Flagge schon seit langem hohe Mengen an Seegeltuch in der Portland Bucht entlädt. Sie operieren seit über einem Jahr, während der Nacht, zwischen dem 10. und 15. jeden Monats.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Sind Sie sicher, dass Ihre Quelle vertrauenswürdig ist?";
			link.l1 = "Manchmal traue ich selbst mir nicht, jedoch ist der Mann, der diese Information preisgegeben hat, vertrauenswürdig. Außerdem hatte er keinen Grund zu lügen.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (int(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "Sehr gut, Kapitän. Dies ist eine ernste Angelegenheit und ich muss auf die vorgelegten Informationen reagieren, auch wenn Ihr Informant gelogen hat oder einfach nur falsch lag. Ich werde zur angegebenen Zeit eine Küstenpatrouille schicken, und wenn Ihre Informationen bestätigt werden, werden Sie großzügig belohnt, solche illegalen Aktivitäten sollten streng unterdrückt werden.";
			link.l1 = "Ich werde dich sehen "+sTemp+" Monat am 16. Die Situation wird sich bis dahin sicherlich von selbst lösen.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = int(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (int(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "Ihre Informationen haben sich als korrekt herausgestellt, Kapitän. Wir haben die Verbrecher während der Transaktion überfallen. Die 'Utrecht' hat versucht zu fliehen und zu kämpfen, wurde aber von unserer Patrouillenkorvette versenkt. Vier Käufer haben Widerstand geleistet. Einer wurde erschossen und die anderen drei sind in den Dschungel geflohen. Die volle Ladung von 80 Rollen Seide wurde in die Schatzkammer von Port Royal überführt. Obwohl es uns nicht gelungen ist, den Kopf dieses Netzwerks zu ermitteln, der tote Mann nicht identifiziert wurde und die anderen geflohen sind, erkläre ich diese Operation als vollen Erfolg. Ich bezweifle, dass diese Schurken es jemals wagen werden, hierher zurückzukehren.\nSie haben uns einen großen Dienst erwiesen, Kapitän, indem Sie fleißig waren und die Betrüger aufgedeckt haben. Hier sind 10.000 Pesos als Belohnung für Sie.";
			link.l1 = "Sehr verpflichtet, Eure Exzellenz. Es freut mich zu sehen, dass alles nach Plan verlief und die Schmuggler das bekamen, was sie verdienten. Damit verlasse ich Sie, einen schönen Tag noch.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "Das ist genau. Wie viele Sklaven hast du mitgebracht?";
				link.l1 = "Ich arbeite noch daran. Ich werde bald mit den Ergebnissen zurückkehren.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "Das ist genau. Wie viele Sklaven haben Sie mitgebracht?";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "Hmm, Chevalier versprach, dass es nicht weniger als 3000 Sklaven geben würde";
			link.l1 = "Das stimmt. Dies ist mein Fehler: Einige der Sklaven wurden unter dem Kanonenfeuer eines feindlichen Schiffes getötet, einige starben auf dem Weg. Ich werde meinen Fehler korrigieren und zu Ihnen zurückkehren. Alles wird gemäß dem Vertrag erledigt werden.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "Ausgezeichnet! Mit Chevalier de Poincy kann man wirklich Geschäfte machen. Sag dem Generalgouverneur, dass meine Staffel für den Angriff auf Curacao in einem Monat bereit sein wird. Ich bin sicher, er wird dich für diese Kampagne zu mir schicken, also werde ich dich bald sehen, Monsieur de Maure.";
			link.l1 = "Es würde mich freuen, Sie wiederzusehen, Oberst. Und nun lassen Sie mich Abschied nehmen.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "Ich zweifelte nicht daran, dass du es sein würdest. Noch besser! Unsere Staffel ist bereit. Ein Schlachtschiff ersten Ranges und zwei Schiffe vierten Ranges. Die maximale Größe der gesamten Staffel darf fünf Schiffe nicht überschreiten.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "Dann werde ich die zusätzlichen Schiffe in den Docks lassen und nur zwei behalten. Wir werden fünf Schiffe als Ergebnis bekommen.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "Ja, genau fünf und nicht mehr. Wir sollten losgehen.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "Perfekt. Nun werde ich Ihnen den Plan erklären, nach dem wir handeln werden: vielleicht möchten Sie etwas ändern oder hinzufügen, dann werden wir es besprechen.";
			link.l1 = "Ich bin ganz Ohr, Oberst.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "Es hat keinen Sinn, Curacao zu erobern: es ist die Hauptkolonie der Niederländer im Archipel, und selbst wenn wir ihre Flagge im Fort von Willemstad erobern und eine englische oder französische hissen, wird es sehr schwierig sein, die Insel zu halten. Die Niederländer werden alles tun, um sie zurückzubekommen und sie mit Militäreskadronen ins Visier zu nehmen. Im Allgemeinen gibt es keinen Sinn, es zu erobern, da es nicht obligatorisch ist. Für uns ist es wichtiger, Steivesant dazu zu drängen, den Vertrag unter Bedingungen zu unterzeichnen, die für uns vorteilhaft sind, und um dies zu tun, wird es ausreichen, die Hauptverteidigung des Feindes zu zerstören und die Niederländer unter die Bedrohung der vollständigen Zerstörung der Kolonie Willemstad zu setzen.";
			link.l1 = "Worum wird der Vertrag handeln?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "Der Vertrag wurde von mir und Chevalier de Poincy verfasst. Er betrifft verschiedene Aspekte des Handels, das Ende des 'Handelskrieges' zwischen der Kompanie und England, die Ablehnung von Stuyvesants Ansprüchen auf die Insel Sint Maarten und andere politische Punkte, die für Sie von geringem Interesse sind.";
			link.l1 = "Verstanden.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "Hier ist der Plan: Zunächst werden wir mit allen Kräften das Fort angreifen und zerstören. Die Holländer werden mit einer Landung der Truppen rechnen, aber das werden wir nicht tun, die meisten Verluste erleiden wir normalerweise beim Angriff auf ein Bollwerk vom Meer aus. Stattdessen werden wir Angriffsteams an zwei Punkten auf der Insel landen lassen: am Kap Santa Maria und an der Lagune von Blanca, und wir werden über Land zum Stadttor von Willemstad marschieren. Ich habe angeordnet, dass wir Feldartillerie mit uns auf die Schiffe nehmen - es gibt keine schwer zugänglichen Dickichte auf Curaçao, und wir werden in der Lage sein, die Kanonen auf Rädern ohne Schwierigkeiten über den Boden zu rollen.\nWährend die Holländer ratlos sein werden, was vor sich geht, werden wir die Stadt aus dem Dschungel ins Visier nehmen und jede Möglichkeit blockieren, Verstärkungen vom Fort über Land zu senden. Danach werden wir die Stadt unter Kanonenfeuer setzen. Sicherlich wird die Besatzung des Forts versuchen anzugreifen, aber sie werden nichts gegen Feldkanonen und unsere Musketiere ausrichten können, und wenn ihre im Fort gehaltenen Kanonen noch funktionsfähig sein sollten, werden sie sie nicht in den Dschungel bringen können.\nZusätzlich werden unsere Schiffe die Vorbereitungen für eine Landung der Truppen vom Meer aus simulieren, um den Feinden Angst einzuflößen und ihre Moral zu senken. Nach einiger Zeit, wenn die Holländer sich ihrer verzweifelten Situation voll bewusst sind, werden wir die Parlamentarier zu Verhandlungen rufen. Was denken Sie, Kapitän?";
			link.l1 = "Brillanter Plan! Und das Beste daran ist, dass wir keine Soldaten an den Mauern der Festung verlieren werden.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "Ich freue mich, dass Ihnen meine Ideen gefallen haben. Lassen Sie uns dann weitermachen!";
			link.l1 = "Auf geht's!";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
