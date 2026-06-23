//navy 26.07.06
//генератор дуэлей...
//в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
//если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
//для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Wie wagst du es, mich zu beleidigen, Schurke?!","Diese Worte werden dich viel kosten!"),RandPhraseSimple("Du hast meine Ehre beleidigt, "+GetAddress_Form(NPChar)+"! Und dafür wirst du bezahlen.","Wie wagst du es? Nimm deine Worte sofort zurück!"));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("Ha?! I don't even want to stain my sword with your blood!", "Ha?! I don't even want to stain my sword with your blood!"), 
				RandPhraseSimple("I am always at your service!", "I am not going to choose words while speaking with the rabble!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I didn't mean it!", "I fired up..."), 
				RandPhraseSimple("That was a mistake. I am sorry.", "I took you for someone else, " + GetAddress_FormToNPC(NPChar) + ". Please forgive me.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,RandPhraseSimple("Ich schneide dir die Ohren ab!","Ich schneide dein Herz heraus!"),RandPhraseSimple("Ich hoffe, dass ich deine Entschuldigungen hören werde oder ich kann nicht garantieren, dass ich mich beherrschen werde!","Begreifen Sie, was das bedeutet... tun Sie das?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I hope that your saber is as swift as your tongue!", "My blade will speak for me."), 
				RandPhraseSimple("I challenge you to a duel!", "That's a matter of honor!")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("I think I am not ready yet!", "Think, we shouldn't get excited! These are words only!"), 
				RandPhraseSimple("I remembered, I am waiting. All blessings...", "Ah! Seems, my ship is sailing already. Bye.")), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && int(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "Erst regelst du deine Angelegenheiten mit anderen, und dann werden wir reden.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "Wir haben bereits eine Vereinbarung getroffen.";
			}
			link.l1 = RandSwear()+"Ach, wie konnte ich das vergessen...";
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("Duell?! Verzieh dich, du bist es nicht wert, Zeit mit dir zu verschwenden.","Duell? Du verdienst diese Ehre nicht! Verschwinde!");
			link.l1 = RandPhraseSimple("In Ordnung...","Schätze, ich kann warten...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("Glaubst du das? Sei dir da nicht so sicher, Bastard!!!","Ach wirklich?! Ich werde mal sehen, welche Farbe dein Blut hat!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("Das Duell, sagst du? Das ist mir recht. Schwerter und Pistolen werden unsere Waffen sein.","Kannst du überhaupt ein Schwert halten?");
		link.l1 = RandPhraseSimple("Du wirst auf deinen Knien um Gnade betteln.","Ich werde dich mit meinen bloßen Händen würgen, du Schurke!");
		link.l1.go = "land_duel";
		if (int(pchar.Ship.Type) != SHIP_NOTUSED && int(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text+"Oder wir können auslaufen und sehen, wer wer ist!","Das Duell?!! Ha, ich zermalme dich wie ein Insekt! Wähle, wie du sterben möchtest!");
			link.l2 = RandPhraseSimple("Auf See bin ich der Beste da draußen.","Mein Schiff wird deine alte Kiste leicht versenken!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "Ich habe meine Meinung geändert...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("Ich sehe dein Schiff nicht im Hafen...","Verschwinde, bis du mindestens eine alte Schaluppe findest!");
		link.l1 = RandPhraseSimple("Mein Fehler...","Dann verlasse ich dich.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Gut, ich werde auf dich am Ausgang der Bucht warten...";
			link.l1 = "Ich werde Sie nicht zu lange warten lassen.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = int(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear()+RandPhraseSimple("Zieh Stahl, und lass uns sehen, welche Farbe dein Blut hat!","Nun, wenn du einen Todeswunsch hast...");
		link.l1 = RandPhraseSimple("Wir sollten besser an einen Ort gehen, wo es nicht zu viele Zeugen gibt. Ich kenne genau den richtigen Ort hinter den Stadttoren. Lass uns dort treffen in "+iHour+" Stunden.","Halt deine Pferde. Solche Dinge werden besser ohne Zeugen geregelt. Komm rein "+iHour+"  Stunden bis zum Eingang zur Stadt.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Nun, wenn du so sehr sterben willst...","Verdammt! Ich werde dir helfen, die Hölle mit deinen eigenen Augen zu sehen!");
		link.l2.go = "fight_right_now";
		link.l3 = "Ich habe meine Meinung geändert...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear()+RandPhraseSimple("Ich denke, wir sollten besser an den Stadttoren vorbeigehen. Ich werde dort auf dich warten in "+pchar.questTemp.Duel.WaitTime+" Stunden. Verzögere nicht!","Dies ist nicht der beste Ort, um Streitigkeiten zu klären. Wir sollten besser aus der Stadt rauskommen. In "+pchar.questTemp.Duel.WaitTime+" Stunden werde ich dort sein.");
			link.l1 = RandPhraseSimple("Du verdienst diese Ehre nicht! Verteidige dich!","Ich habe keine Zeit! Zieh Stahl!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("In Ordnung, machen wir einen Spaziergang.","Du hast wahrscheinlich recht. Treffen wir uns hinter den Toren.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("Du verdienst diese Ehre nicht! Verteidige dich!","Ich habe keine Zeit! Hier und jetzt!");
		link.l1 = RandPhraseSimple("Nun, wenn du so sehr sterben willst...","Verdammt! Ich werde dir helfen, die Hölle mit deinen eigenen Augen zu sehen!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("In Ordnung, wir machen einen Spaziergang.","Du hast wahrscheinlich recht. Treffen wir uns hinter den Toren.");
			link.l1 = RandPhraseSimple("Ich werde dort auf dich warten.","Zögere nicht.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//что ж, пойдём выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//на случай, если не дождется, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, int(GetTime() + 0.5) + int(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = int(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "Also, bist du bereit?";
		link.l1 = "Ja. Lass uns sehen, wer der bessere Mann ist!";
		link.l1.go = "fight_right_now";
		link.l2 = "Nein, ich habe beschlossen, die Entschuldigungen zu dir zu bringen. Ich lag falsch, entflammt.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("Hallo, hör zu, ich habe darüber nachgedacht und sehe jetzt, dass ich falsch lag. Meine Entschuldigung.","Verdammt! Es ist dieser verdammte Rum!!! Meine Entschuldigung, "+GetSexPhrase("Bruder","Schwester")+"!");
			link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Nein, nur dein Blut kann mir jetzt Befriedigung geben!","Zieh Stahl und hör auf, so ein weinendes Mädchen zu sein!"),RandPhraseSimple("Nein! Ich verlange Genugtuung!","Du bist eine Schande für deine Familie! Zieh dein Schwert!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,RandPhraseSimple("Also gut, ich stimme zu. Wir haben uns ein bisschen aufgeregt.","Wer führt schon unter Freunden die Rechnung!"),RandPhraseSimple("Du hast wahrscheinlich recht. Wir sollten nicht wegen solcher Kleinigkeiten Blut vergießen.","Meine Großzügigkeit kennt keine Grenzen! Du bist vergeben!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//дуэли быть!
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();	
		break;
		
	//передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Dann verschwinde!","Verschwinde dann, bevor ich meine Meinung ändere."),RandPhraseSimple("In diesem Fall halte ich Sie nicht länger auf!","Dann solltest du besser gehen, bevor ich meine Meinung ändere."));
		link.l1 = "Ich gehe schon...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Verzieh dich!","Verschwinde aus meiner Sicht, bevor ich meine Meinung ändere."),RandPhraseSimple("Kann ich Ihnen helfen?","Möchten Sie etwas?"));
		link.l1 = "Ich gehe.";
		link.l1.go = "peace";
		break;

	//мир и все такое.
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}
