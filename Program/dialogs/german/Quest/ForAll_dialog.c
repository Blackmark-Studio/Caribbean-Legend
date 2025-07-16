void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Wir haben nichts zu besprechen.";
			link.l1 = "Gut...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin Bürger dieser Stadt und ich bitte dich, deine Klinge zu senken.","Hör zu, ich bin Bürger dieser Stadt und ich würde dich bitten, deine Klinge zu senken.");
				link.l1 = LinkRandPhrase("Gut.","Sicher.","Gut...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, "+GetSexPhrase("Kumpel","Mädchen")+", mit einer Waffe rennend. Ich kann nervös werden...","Ich mag es nicht, wenn es gibt "+GetSexPhrase("Männer","Leute")+" gehen vor mir mit ihrer Waffe bereit. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Ich habe es.","Ich habe es.");
			}
			
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "Komm schon, Kumpel, zeig mir deine Taschen.";
			link.l1 = "Was?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "Du hast mich gehört. Schnell, weniger Worte. Ich mag es nicht zu reden...";
			link.l1 = "Verdammt! Und das tut es"+pchar.questTemp.different.FackWaitress.Name+" mit dir zusammenarbeiten?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "Sie tut es, sie tut es... Gib mir dein Geld oder ich werde dich ausweiden!";
			link.l1 = "Nein! Ich werde dich aufschlitzen!";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "Nimm meine Münzen, Schurke! Aber du wirst nicht davonkommen...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "Sicher, kann man nicht gegen argumentieren. Lebewohl, Kamerad. Und denk daran, du bist nicht so gut aussehend, dass du Kellnerinnen feucht machst. Sei das nächste Mal klüger!";
			link.l1 = "...Geh schon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "Wie du sagst...";
			link.l1 = "Das tue ich...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "Hier bin ich! Willst du mich, Schönling?";
			link.l1 = "Verdammt, das ist schnell eskaliert...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "Lass uns keine Zeit verschwenden!";
			link.l1 = "Heh, ich könnte nicht mehr zustimmen!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "Guten Tag. Mein Name ist "+GetFullName(npchar)+". Ich bin ein Kapitän von "+GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName+"Konto"))+" '"+npchar.Ship.name+"'. "; 
			link.l1 = "Herrlich! Endlich habe ich dich gefunden.";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "Gefunden mich?!";
			link.l1 = "Ja. Nun, ich habe Ihr Logbuch mitgebracht, das Sie im Hafenbüro vergessen haben "+XI_ConvertString("Kolonie"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "Verdammt! Jetzt sehe ich, wo ich es verloren habe. Dieser Verlust hat fast eine Meuterei auf meinem Schiff provoziert...";
			link.l1 = "Also ist alles gut, was gut endet. Nimm dein Logbuch und lass uns über mein Geld sprechen.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Perfektes Timing, ich habe noch keinen neuen gestartet, also werde ich Ihnen so viel zahlen, wie ich kann. "+FindRussianMoneyString(sti(npchar.quest.money))+" und nehme ein paar Stücke meines privaten Schmucks.";
				link.l1 = "Schön. Nimm es.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Hm, weißt du, ich habe bereits das neue Logbuch begonnen. Dennoch hat das alte für mich immer noch Wert. Also werde ich dich bezahlen "+FindRussianMoneyString(sti(npchar.quest.money))+" und akzeptiere ein paar Stücke meines privaten Schmucks.";
					link.l1 = "Abgemacht dann. Nimm dein Logbuch.";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "Ich habe bereits das neue Logbuch begonnen. Und alle Notizen aus dem alten übertragen. Ich brauche es nicht mehr, also gibt es kein Geld für dich.";
					link.l1 = "Großartig. Also war all diese Jagd umsonst.";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "Danke dir. Lebewohl, "+GetSexPhrase("Kumpel","Mädchen")+".";
			link.l1 = "Gleichfalls...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "Ha, arbeite das nächste Mal an deinem Timing.";
			link.l1 = "Wahrhaftig genug.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "Ich begrüße dich auf dem Deck meines Schiffes. Um ehrlich zu sein, hast du mich zu Tode erschreckt - Ich dachte, der einäugige Steed Hunter wäre hinter mir her...";
				link.l1 = "Nein, Kapitän, ich bin heute gut gelaunt. Ich bin hier, um Ihnen zu helfen.";
			}
			else
			{
				dialog.text = "Ich begrüße Sie auf dem Deck meines Schiffes!";
				link.l1 = "Ahoi, Käpt'n! Ich habe nach dir gesucht.";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "Warum?";
			link.l1 = "Sie haben Ihr Logbuch im Hafenmeisterhaus vergessen "+XI_ConvertString("Kolonie"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Verdammt, also war das der Ort! Dieser Verlust hat mir bereits eine Menge Ärger bereitet.";
				link.l1 = "Wie wäre es mit einer Belohnung?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Verdammt, jetzt sehe ich, wo ich es verloren hatte! Danke, aber du hast viel zu lange nach mir gesucht. Ich habe bereits das neue Logbuch begonnen. Trotzdem müssen die alten Notizen noch in das neue übertragen werden...";
					link.l1 = "Und wie viel?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "Ich habe bereits das neue Logbuch gestartet. Und alle Notizen aus dem alten übertragen. Ich brauche es nicht mehr.";
					link.l1 = "Also brauchst du kein altes Tagebuch? Wirklich?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "Ich kann dich bezahlen "+FindRussianMoneyString(sti(npchar.quest.money))+" und einige meiner Juwelen. Das ist alles, was ich mir leisten kann.";
			link.l1 = "Gut dann. Nimm dein Tagebuch.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "Danke nochmal. Lebewohl, Kumpel.";
			link.l1 = "Mach weiter so.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "Das ist sicher. Wenn du jemanden verfolgst, dann musst du schneller sein.";
			link.l1 = "Verliere deine Logbücher erst gar nicht. Gut.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(100/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "Ich dachte, wir hätten alles geklärt.";
			link.l1 = "Ja, das ist wahr.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "Grüße. Was willst du?";
			link.l1 = "Es ist nichts, wollte nur einige Neuigkeiten hören. Haben Sie etwas zum Verkauf?";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "Ich habe nichts zu verkaufen und ich habe auch keine Neuigkeiten. Übrigens, Ihre Anwesenheit hier ist nicht erwünscht. Ist das klar?";
			link.l1 = "Du bist... Lebewohl dann, Kumpel.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "Ich habe dir gesagt, dass du hier nichts zu tun hast!";
			link.l1 = "Ich sehe...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "Warum hast du mich angegriffen?!";
			link.l1 = "Ich muss das Schiff seinem Besitzer zurückgeben..";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "Zu welcher Art von Besitzer? Ich bin der Besitzer!";
			link.l1 = "Nein, das bist du nicht. Ich weiß nicht, wem dieses Schiff gehört. Aber es wurde gestohlen und ich muss es zurückbringen.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "Verdammt! Aber für mich ist es noch nicht vorbei. Zumindest werde ich versuchen, dich zu töten...";
			link.l1 = "Versuchen ist alles, was du tun kannst.";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------поисковый генератор горожан--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "SCQ_exit":
			DialogExit();
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_exit_clear":
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		
//--------------------------------------------поисковые квесты дворян---------------------------------------------
		
		case "SCQ_Nobleman":
			dialog.text = "Grüße, "+GetAddress_Form(NPChar)+". Ich sehe, dass Sie der Kapitän Ihres eigenen Schiffes sind? Mein Name ist "+GetFullName(npchar)+" und ich möchte Ihnen ein Angebot machen.";
			link.l1 = RandPhraseSimple("Es tut mir so leid, aber ich muss gehen.","Es tut mir so leid, aber ich habe keine Zeit, mit dir zu reden.");
			link.l1.go = "SCQ_exit";
			link.l2 = "Ich bin ganz Ohr.";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "Hör dann zu. "+SelectNB_battleText()+"\nIch habe weder Zeit noch Gelegenheit, ihn zu finden. Denn, er taucht hier nie auf. Ich nehme an, du siehst es jetzt, du siehst, was ich dir vorschlagen werde?";
						link.l1 = LinkRandPhrase("Ich vermute, ich muss jemanden aufspüren und zu Ihnen bringen?","Vielleicht, um den Bastard zu finden und ihn zu dir zu bringen?","Du willst, dass ich diesen Mann finde und hierher bringe?");
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "Hört dann zu."+SelectNB_battleText()+"\nIch habe weder Zeit noch Gelegenheit, ihn zu finden. Denn, er zeigt sich hier nie. Ich schätze, du siehst es jetzt, du siehst, was ich dir vorschlagen werde?";
						link.l1 = LinkRandPhrase("Ich vermute, Sie wollen, dass ich jemanden aufspüre und zu Ihnen bringe?","Vielleicht, um den Bastard zu finden und ihn zu dir zu bringen?","Du willst, dass ich diesen Mann finde und ihn hierher bringe?");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = "Hör zu dann. Eigentlich, "+npchar.quest.text+" dient in der Marine als Kapitän. Er weiß nicht einmal, dass ich auch hier bin!\nIch möchte ihn treffen, doch ich habe weder Zeit noch Gelegenheit, ihn zu finden...";
					link.l1 = "Ich nehme an, dass Sie möchten, dass ich diesen Kapitän finde und ihm von Ihnen erzähle?";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //вариант А
			dialog.text = "Nicht ganz so. Findet ihn, aber es ist nicht nötig, ihn hierher zu bringen. Tötet ihn und das wird genug sein. Versenkt ihn mit seinem dreckigen Schiff, erschießt ihn, ersticht ihn mit eurer Klinge - das ist mir eigentlich egal, sorgt einfach dafür, dass dieser Bastard aufhört, diese Welt mit seiner Anwesenheit zu vergiften. Die Belohnung wird großzügig sein.";
			link.l1 = "Ha! Einfach genug. Sag mir seinen Namen und den Namen seines Schiffes.";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			dialog.text = ""+npchar.quest.SeekCap.capName+" der "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Stimm"))+" genannt "+npchar.quest.SeekCap.shipName+". Er ist oft ein Gast im Hafen von "+XI_ConvertString("Kolonie"+npchar.quest.Qcity)+". Ich werde dich bezahlen "+FindRussianMoneyString(sti(npchar.quest.money))+" in goldenen Dublonen.";
			link.l1 = "Das ist alles, was ich wissen muss. Ich werde auf See aufmerksam sein. Und wenn ich Ihren Freund finde, werde ich ihn... 'leise sprechend' ...nicht ganz lebendig machen.";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "Das reicht nicht für diese Art von Arbeit.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "Ich bin froh, dass wir einen Deal gemacht haben. Ich werde auf deine Rückkehr warten.";
			link.l1 = "Wo werde ich dich finden können? Klären wir das jetzt, ich möchte keine Zeit damit verschwenden, dich zu suchen.";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "Jeden Morgen besuche ich einen Gottesdienst in der örtlichen Kirche. Dort kannst du mich jeden Tag von 8 bis 9 Uhr morgens finden.";
			link.l1 = "Abgemacht dann! Erwarte das Ergebnis bald.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_prisoner": //вариант В
			dialog.text = "Genau. Finden Sie ihn und bringen Sie ihn zu mir. Lebendig. Ich möchte mich selbst mit ihm befassen. Ich werde dich großzügig belohnen.";
			link.l1 = "Nun, ich kann versuchen, ihn zu finden, aber ich brauche Details.";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "Der Bastard heißt "+npchar.quest.SeekCap.name+". Er dient auf "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" genannt "+npchar.quest.SeekCap.shipName+", welches unter dem Kommando von "+npchar.quest.SeekCap.capName+". Das Schiff kann oft im Hafen von "+XI_ConvertString("Kolonie"+npchar.quest.Qcity)+". Ich werde dich für diese Arbeit bezahlen "+FindRussianMoneyString(sti(npchar.quest.money))+" in goldenen Dublonen.";
			link.l1 = "Das reicht mir. Ich werde auf hoher See aufmerksam sein.";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "Das reicht nicht für diese Art von Arbeit.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "Ich bin froh, dass wir einen Handel abgeschlossen haben. Ich werde auf deine Rückkehr warten.";
			link.l1 = "Wo werde ich dich finden können? Lassen wir das jetzt klären, ich will keine Zeit mit der Suche nach dir verschwenden.";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "Jeden Morgen nehme ich an einem Gottesdienst in der örtlichen Kirche teil. Du kannst mich dort jeden Tag von 8 bis 9 Uhr morgens finden.";
			link.l1 = "Abgemacht dann! Erwarte bald das Ergebnis.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_peace": //вариант С
			dialog.text = "Genau! Finden Sie ihn und sagen Sie ihm, dass ich in dieser Stadt lebe. Ich werde für Ihre Dienste bezahlen.";
			link.l1 = "Nun... Ich kann es versuchen. Erzähl mir die Einzelheiten.";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = "Sein Name ist "+npchar.quest.SeekCap.capName+". Und er dient auf "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" "+npchar.quest.SeekCap.shipName+"'. Er besucht oft "+XI_ConvertString("Kolonie"+npchar.quest.Qcity)+". Ich werde dich für diese Arbeit bezahlen "+FindRussianMoneyString(sti(npchar.quest.money))+" in goldenen Dublonen.";
			link.l1 = "Abgemacht! Ich nehme an, dass ich Ihren Freund bald genug finden werde.";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "Das reicht mir nicht.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "Ich bin froh, dass wir einen Handel gemacht haben. Ich werde auf deine Rückkehr warten.";
			link.l1 = "Wo werde ich dich finden können? Klären wir das jetzt, ich will keine Zeit mit der Suche nach dir verschwenden.";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "Ich besuche immer einen Abendgottesdienst in der örtlichen Kirche. Dort kannst du mich jeden Tag von 18 bis 20 Uhr finden.";
			link.l1 = "Abgemacht dann! Erwarte das Ergebnis bald.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		//--> разговор на суше, вариант А
		case "NM_battleCap":
			dialog.text = "Und? Was wollen Sie, Herr?";
			link.l1 = "Bist du der Kapitän "+GetFullName(npchar)+"?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "Ja, das bin ich. Was ist los?";
			link.l1 = "Einer Mann hat ein sehr großes Interesse an dir, sein Name ist "+GetFullName(&characters[GetCharacterIndex("QuestBürger_"+npchar.quest.cribCity)])+". Erinnerst du dich?";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "Ich habe gehört, dass es viel Mahagoni in eurem Laderaum gibt. Ich möchte es kaufen. Würdet ihr es mir verkaufen?";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "Es ist das erste Mal, dass ich diesen Namen höre. Sie haben sich irgendwie geirrt, Kapitän. Sind wir fertig?";
			link.l1 = "Hm. Gut, entschuldige mich ...";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "Ach wirklich? Aber er erinnert sich sehr gut an dich. Er erwähnte deine Schuld bei ihm...";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "Welche Schuld? Wovon redest du?";
			link.l1 = "Die Ehrenschuld!";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "Sie irren sich. Ich handle nicht mit Holz. Sind wir fertig?";
			link.l1 = "Hm. Gut, entschuldigen Sie mich...";
			link.l1.go = "NM_battleCap_exit";
		break;
		
		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;
		
		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант В
		case "NM_prisonerCap":
			dialog.text = "Und? Was wünschen Sie, Herr?";
			link.l1 = "Bist du Kapitän "+GetFullName(npchar)+"?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Ja, das bin ich. Was ist los?";
			link.l1 = "Gibt es einen Mann namens "+sld.quest.SeekCap.name+"dienen unter deinem Kommando?";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Ja. Er ist einer meiner Offiziere. Nun sag mir, warum fragst du?";
			link.l1 = "Sicher werde ich es dir erzählen. Ich suche diesen Mann auf Anordnung der Behörden von "+XI_ConvertString("Kolonie"+sld.city+"Gen")+", und ich habe die Macht, ihn zu verhaften und ihn zu übergeben an "+XI_ConvertString("Kolonie"+sld.city)+". Ich bitte Sie, mir bei dieser Angelegenheit zu helfen, damit wir sie friedlich regeln können.";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "Wirklich? Und so ein Mann dient in meiner Besatzung? Meinst du das ernst?";
				link.l1 = "Belästige dich nicht damit, "+GetAddress_FormToNPC(NPChar)+". Ich werde ein Beiboot zu Ihrem Schiff schicken und wir werden ihn selbst holen.";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "Sie sagen es. Wissen Sie was, Sir, seine Vergangenheit ist mir egal. Sie betrifft mich nicht. Und wer sind Sie eigentlich? Behörden? Wirklich? Ha! Ich gebe meine Männer weder Ihnen noch sonst jemandem. Dieses Gespräch ist beendet. Ab mit Ihnen!";
				link.l1 = "Falsche Wahl... Eine schreckliche!";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "Tu, was du tun musst.";
			link.l1 = "Dabei.";
			link.l1.go = "NM_prisonerCap_good_1";
		break;
		
		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_"+(rand(9)+21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(sld.quest.SeekCap.name+" is under arrest");
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
		break;
		
		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "NM_prisonerDeck_exit":
			dialog.text = "Sind wir fertig, Kapitän?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = "Guten Tag. Was wünschen Sie, Kapitän?";
			link.l1 = "Du bist Kapitän "+GetFullName(npchar)+", habe ich recht?";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = "Du hast recht. Hast du etwas für mich?";
			link.l1 = "Ich habe. Ein Mann namens "+GetFullName(sld)+" sucht nach dir. Er möchte, dass du ihn so schnell wie möglich besuchst. Er lebt in "+XI_ConvertString("Kolonie"+npchar.quest.cribCity+"Voc")+".";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "Ha! Also ist er auch in die Neue Welt gezogen? Dann sollte ich ihm wirklich einen Besuch abstatten... Danke für die Information, Herr!";
			link.l1 = "Sie sind willkommen. Ihre Freundin wird für meine Arbeit bezahlen. Viel Glück, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "NM_peaceCap_3";
		break;
		
		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		
		case "NM_peaceCap_exit":
			dialog.text = "Es war ein Vergnügen, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "Das Vergnügen war meinerseits, Kapitän.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = "Ahoi, "+GetAddress_Form(NPChar)+". Was willst du?";
			link.l1 = "Ich habe gehört, dass du viel Rotholz in deiner Ladung hast und ich möchte es kaufen. Wirst du es verkaufen?";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "Sie irren sich. Ich handele nicht mit Holz und Ihr Besuch hier riecht mir verdächtig. Ich denke, es wäre besser, wenn Sie mein Schiff verlassen!";
			link.l1 = "Gut, ich habe nur gefragt. Lebewohl.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "Wollen Sie Ärger, Herr? Soll ich mich wiederholen?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Warum hast du mein Schiff angegriffen, Schurke?";
			link.l1 = "Ich bin hier, um Ihnen die besten Grüße zu überbringen von "+XI_ConvertString("Kolonie"+npchar.quest.cribCity)+" , von dem Mann namens "+GetFullName(&characters[GetCharacterIndex("QuestBürger_"+npchar.quest.cribCity)])+". Ich hoffe, dass du die Situation jetzt verstehst.";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "Unmöglich! Dann habe ich ja nichts zu verlieren...";
			link.l1 = "Wie steht's mit deinem Leben?";
			link.l1.go = "NM_battleBoard_2";
		break;
		
		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		 //--> абордаж, вариант В
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];//квестодатель
			dialog.text = "Weshalb hast du mein Schiff angegriffen, Schurke?";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "Hast du irgendwelche Ideen? Ich habe dich gebeten, mir deinen Offizier friedlich zu übergeben. Jetzt nehme ich ihn, dich und deine Kutsche!";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "Es gibt einen Schurken unter deinem Kommando. Sein Name ist "+sld.quest.SeekCap.name+". Behörden von "+XI_ConvertString("Kolonie"+npchar.quest.cribCity)+" sind wirklich begierig darauf, ihn zu sehen. Er wird verhaftet und in mein Verlies gebracht.";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "Und deshalb hast du ein Gemetzel auf meinem Schiff angerichtet? Bastard! Ich habe noch etwas Kraft übrig... Ich werde dich töten!";
			link.l1 = "Stärkere Männer haben es versucht...";
			link.l1.go = "NM_prisonerBoard_2";
		break;
		
		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завершения квеста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+21); //модель для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;
		
		//--> результаты квестов дворян
		case "SCQ_NM_result":
			dialog.text = "Was sagen Sie, Kapitän? Haben Sie Fortschritte in meiner Angelegenheit gemacht?";
			link.l1 = "Noch nicht. Aber ich bin dabei.";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = "Was sagen Sie, Kapitän? Haben Sie Fortschritte bei meiner Angelegenheit gemacht?";
					link.l1 = "Ich tue es. Und es wird dir gefallen."+npchar.quest.SeekCap.capName+" ist tot und sein "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" liegt auf dem Meeresgrund.";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = "Was sagen Sie, Kapitän? Gibt es Fortschritte in meiner Angelegenheit?";
					link.l1 = "Ich tue es. Und du wirst es mögen."+npchar.quest.SeekCap.Name+" sitzt in der Kajüte meines Schiffes unter Arrest.";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = "Aha, da bist du ja. Ich freue mich, dich zu sehen. Mir wurde mitgeteilt, dass du deine Mission erfolgreich abgeschlossen hast!";
					link.l1 = "Hat dein Freund dich besucht?";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "Prächtig! Ich wusste, dass ich mich auf dich verlassen kann. Hier, nimm dein Gold. Du hast es verdient.";
			link.l1 = "Danke. Sprich wieder mit mir, falls du einen weiteren Feind bekommst.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "SCQ_NM_result_B1":
			dialog.text = "Prächtig! Ich werde meine Männer sofort anordnen, ihn von deinem Schiff zu holen. Er wird jetzt nicht mehr entkommen! Hier, nimm dein Gold. Du hast es verdient.";
			link.l1 = "Danke. Wende dich jederzeit an mich für einen Job wie diesen.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		break;
		
		case "SCQ_NM_result_C1":
			dialog.text = "Ja, er war hier und hat mir von dir erzählt. Hier, nimm dein Gold. Du hast es verdient.";
			link.l1 = "Mein Dank. Auf Wiedersehen, Herr!";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
//<-- поисковые квесты дворян

		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("Grüße, Kapitän. Ich möchte um Ihre Hilfe bitten.","Kapitän! Könnten Sie mir helfen? Bitte.","Kapitän, ich bitte um Ihre Hilfe!");
			link.l1 = RandPhraseSimple("Ich bin beschäftigt.","Ich habe es eilig.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Was ist los?","Sag, was dich stört. Vielleicht kann ich dir helfen.");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Vor einem Jahr versprach mir ein Kapitän, mich mitzunehmen nach "+XI_ConvertString("Kolonie"+SelectNotEnemyColony(NPChar)+"Konto")+". Aber während ich auf seinem Schiff war, wurde ich in den Laderaum geworfen und danach in die Sklaverei verkauft. Ich habe es kaum überstanden. Mehrere Male war ich dem Tod nahe... Wie auch immer, ich möchte meinem 'Freund' daran erinnern, dass ich noch am Leben bin."; // belamour gen
					link.l1 = "Was meinst du? Sag mir genau, was du willst.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "Meine Frau wurde entführt. Ein Kapitän, ein Pirat, wie sie sagen, umwarb sie. Meine Frau musste tagelang zu Hause bleiben, wegen seiner Belästigung. Ich habe versucht, die Stadtautoritäten um Hilfe zu bitten, aber es ist mir nicht gelungen. Und jetzt...";
					link.l1 = "Und jetzt?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "Sie wissen, ich suche meinen Landsmann. Vor drei Jahren kamen wir zusammen aus Europa hierher, um ein besseres Leben zu finden. Wir haben uns verloren. Aber vor nicht allzu langer Zeit hörte ich, dass er jetzt ein Handelskapitän ist! Ich habe versucht, ihn selbst zu finden, aber ich habe versagt.";
					link.l1 = "So?";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "Ich will, dass du ihn findest und tötest. Ich will, dass er so sehr tot ist, dass ich nicht einmal essen kann...";
			link.l1 = "Ich verstehe... Ich denke, ich kann Ihnen dabei helfen. Nennen Sie mir seinen Namen und den Namen seines Schiffes.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "Es tut mir leid, aber ich bin nicht interessiert.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = ""+npchar.quest.SeekCap.capName+" der "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Hallo, Freund."))+" genannt "+npchar.quest.SeekCap.shipName+". Ich werde dich bezahlen  "+FindRussianMoneyString(sti(npchar.quest.money))+", plus all meine Juwelen."; // belamour gen
			link.l1 = "Ich verstehe. Ich werde auf hoher See aufmerksam sein. Wenn ich das Ziel finde... Betrachte ihn dann als tot.";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "Ich werde für so wenig Geld nichts tun. Finden Sie einen anderen Narren, der sich an Ihrer Stelle rächt.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "Das ist was ich zu hören hoffte! Oh, ich kann jetzt essen! Endlich! Ich muss etwas zu essen bekommen...";
			link.l1 = "Guten Appetit. Ich werde dich finden, sobald die Arbeit erledigt ist.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "Ich werde auf dich in der örtlichen Kirche warten.";
			link.l1 = "Gut.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "Ich war zu faul und der Bastard hat meine Frau gepackt und sie an Bord seines Schiffes gebracht. Ich bitte dich, diesen Schurken zu finden!";
			link.l1 = "Hm, und warum sollte ich mit einem Mitgauner kämpfen?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "Ich bin nicht reich, aber es wird mir eine Freude sein, Ihnen alle Wertsachen zu geben, die ich besitze! Wenn Sie meine Frau befreien und sie zu mir bringen, werde ich Sie bezahlen "+FindRussianMoneyString(sti(npchar.quest.money))+", plus all meine Juwelen.";
			link.l1 = "Gut, ich bin dabei. Erzähl mir die Einzelheiten. Sein Name, sein Schiff und wie heißt deine Frau.";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "Nein, Kumpel, für so einen kleinen Betrag mache ich es nicht. Tut mir leid...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "Ihr Name ist "+npchar.quest.SeekCap.name+". Und der Name des Bastards ist "+npchar.quest.SeekCap.capName+", er schwimmt auf "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Hallo, Freund."))+" genannt "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Scheiße schwimmt, Kumpel. Kapitäne segeln...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "Ja, ja, es tut mir so leid! Ich bin kein Seemann, ich hoffe, Sie werden es verstehen...";
			link.l1 = "Es ist in Ordnung, mach dir keine Sorgen. Was auch immer, ich komme zurück, sobald es erledigt ist.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "Vielen Dank! Ich werde in der örtlichen Kirche auf Sie warten. Aber ich bitte Sie, sich zu beeilen. Ich mache mir wirklich Sorgen um meine Frau...";
			link.l1 = "Ja, ich beneide sie auch nicht.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "Das Problem ist, mein Freund hat kein Anwesen. Sein Schiff ist sein Zuhause. Also kann ich ihn nicht finden, weil er immer segelt. Und ich kann mir nutzlose Reisen nicht leisten, ich muss Geld fürs Leben verdienen.";
			link.l1 = "Ich kann dir nicht helfen, wenn du kein Geld hast...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Ich kann dich bezahlen "+FindRussianMoneyString(sti(npchar.quest.money))+" und ich werde dir all meine Juwelen geben. Das ist alles, was ich mir jetzt leisten kann.";
			link.l1 = "Diese Summe passt mir. Ich bin dabei. Tatsächlich, du kannst dich mir als Passagier anschließen, so wirst du deinen Freund sehen, sobald wir ihn finden.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "Das reicht mir nicht. Such dir jemand anderen, der es macht.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "Nein, ich denke, ich würde hier bleiben. Wir wissen nicht, wie lange diese Suchen dauern werden und ich könnte all mein Geld verlieren. Ich habe hier einen Job.";
			link.l1 = "Ich verstehe. Nun sag mir, wer ist dein Freund und auf welchem Schiff ist er.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "Sein Name ist "+npchar.quest.SeekCap.capName+". Soweit ich weiß, kommandiert er ein "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Acc"))+" genannt "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Ich verstehe. Nun, ich werde deinem Freund von dir erzählen, wenn ich ihn sehe.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "Danke. Ich werde auf Ihre Ankunft in der örtlichen Kirche warten. Sie werden Ihre Münzen bekommen, sobald die Arbeit erledigt ist.";
			link.l1 = "Sicher. Lebewohl dann, erwarte bald die Ergebnisse.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "Guten Tag an Sie, Kapitän. Haben Sie schon Ergebnisse?";
			link.l1 = "Erinnere mich an dein Problem...";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "Ich nehme an, dass ich gerächt wurde. Ist das so?";
					link.l1 = "Genau. "+npchar.quest.SeekCap.capName+" ist tot und sein "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" liegt auf dem Grund des Meeres.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "Du hast meine Frau gefunden! Ich kann es nicht glauben! Oder doch?";
					link.l1 = "Du kannst. Sie ist meine Passagierin. Du kannst sie zurückbringen, wenn "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+" wirklich ist deine Frau...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "Guten Tag an Sie, Kapitän. Haben Sie meinen Kameraden gefunden?";
					link.l1 = "Ich habe es ihm erzählt und von dir erzählt.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Was? Hast du wirklich vergessen, dass ich dich gebeten habe, dich für den Kapitän zu rächen "+npchar.quest.SeekCap.capName+" für ein Jahr meiner Sklaverei?";
					link.l1 = "Nein, habe ich nicht.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "Ich kann meinen Ohren nicht trauen! Hast du vergessen, dass ich dich gebeten habe, meine Frau zu finden und zu befreien? Sie wurde von dem Piraten namens "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Ich habe nicht.";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "Warte mal... Hast du etwa dein Versprechen vergessen, meinen Kameraden zu finden "+npchar.quest.SeekCap.capName+"?";
					link.l1 = "Ich habe nicht.";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "Ausgezeichnet, ich lag richtig mit dir! Also, wie ich dir versprochen habe, hier sind deine "+FindRussianMoneyString(sti(npchar.quest.money))+" und Juwelen. Danke für deine Hilfe.";
			link.l1 = "Sei willkommen...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "Oh mein Gott! Sie haben uns gerettet! Bitte, nehmen Sie Ihr "+FindRussianMoneyString(sti(npchar.quest.money))+" und Juwelen. Und wisse, dass wir für immer für dich beten werden!";
			link.l1 = "Bete, wenn du willst. Ich habe damit kein Problem.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "Prächtig!... Hier, nimm "+FindRussianMoneyString(sti(npchar.quest.money))+" und Juwelen. Und danke, Kapitän.";
			link.l1 = "Du bist willkommen, Freund. Leb wohl...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("Grüße, Kapitän. Können Sie mir helfen?","Kapitän! Könnten Sie einer Frau helfen? Wären Sie so freundlich...","Kapitän, hilfe "+GetSexPhrase("ein Mädchen","ich")+".");
			link.l1 = RandPhraseSimple("Ich bin beschäftigt.","Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+", aber ich habe keine Zeit zu verschwenden...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Was ist dein Problem, "+GetAddress_FormToNPC(NPChar)+"?","Sprechen Sie Ihre Probleme aus, "+GetAddress_FormToNPC(NPChar)+". Ich werde versuchen, dir zu helfen.");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Mein Mann ist ein Händler, er liefert Waren an jede Kolonie herum. Vor drei Monaten ging er aufs Meer. Er ist noch nicht zurückgekehrt!";
					link.l1 = "Glaubst du, dass ihm etwas passiert ist?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+GetSexPhrase("Kapitän, ich sehe, dass Sie ein mutiger Kapitän sind, ein perfekter Schurke","Kapitänin, ich sehe, dass Sie eine starke Frau sind, die mit jedem Mann fertig werden kann")+"...";
					link.l1 = "Und warum sagst du das, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "Kapitän, bitte helfen Sie mir, ich flehe Sie an! Mein Mann wurde gefangen genommen! Können Sie ihn retten?";
					link.l1 = "Warte mal, ich verstehe es nicht. Wer wurde von wem gefangen genommen?";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "Ich weiß es nicht, aber ich hoffe immer noch, dass er einfach zu beschäftigt ist, um mir zu schreiben. Er hätte mir einen Brief schicken können, er weiß, dass ich mir Sorgen um ihn mache!";
			link.l1 = "Es ist nicht sicher auf dem Meer, alles könnte passieren...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Genau! Du verstehst, wovon ich spreche. Du siehst aus wie ein "+GetSexPhrase("tapferer Kapitän","tapferes Mädchen")+", also möchte ich dich bitten, meinen Ehemann zu finden. Ich bin bereit, dich zu bezahlen "+FindRussianMoneyString(sti(npchar.quest.money))+", plus ich werde dir all meine Juwelen geben.";
			link.l1 = "Gut. Ich werde Ihrem Mann von Ihren Sorgen erzählen, wenn ich ihn auf See oder woanders treffe. Nennen Sie mir seinen Namen und den Namen seines Schiffes.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "Ich interessiere mich nicht für eine so kleine Summe.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "Sein Name ist "+npchar.quest.SeekCap.capName+". Er segelt auf einem "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Stimme"))+" genannt "+npchar.quest.SeekCap.shipName+".";  // belamour gen
			link.l1 = "Ich verstehe. Jetzt musst du warten. Versuche, die meiste Zeit in der Kirche zu verbringen, damit ich dich finden kann.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+GetSexPhrase("Ich sage das, guter Herr, weil ich Sie anheuern möchte, um die Arbeit zu erledigen, an die Sie gewöhnt sind... sozusagen.","Ich möchte, dass du mir hilfst. Ich hoffe, du wirst mich als Frau verstehen.")+"Einer Kapitän hat mich geärgert und ich will ihn tot sehen.";
			link.l1 = "Und was hat diese arme Seele dir angetan?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "Dieser Bastard hat mich betrogen. Er gab vor, in mich verliebt zu sein, er war sogar am Hofieren. Und der Grund, warum er all das tat, war, um etwas Wertvolles von meinem Mann zu bekommen! Und als der Hund seinen Knochen bekam, sagte er mir, dass es nichts bedeutete... dass wir nur Freunde waren!";
			link.l1 = "Hm, vielleicht hatte er recht?";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "Sehe ich aus wie ein Idiot?! Glaubst du, dass ich den Unterschied zwischen einer Hofmacherei und einfachem Geschwätz nicht sehe?";
			link.l1 = "Sicher, das tust du...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "Er hat mich benutzt, dieser Schurke! Das werde ich ihm nie verzeihen!";
			link.l1 = "Ja, Männer sind eben so. Aber könnten Sie sich vielleicht beruhigen? Daran ist nichts Schreckliches...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "Nichts Schreckliches?! "+GetSexPhrase("Du bist eine Art Moralapostel, du bist kein echter Pirat!","Es scheint, dass du noch nie in einer solchen Situation warst! Oh, ja, wer würde ein Risiko eingehen... und ich bin nur eine schwache Frau...");
			link.l1 = "Gut. Genug. Ich möchte einfach nur wissen, wie ernst deine Absichten sind.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "Verdammt, "+GetSexPhrase(" du weißt einfach nicht, wie die Rache einer abgewiesenen Frau aussieht ","du bist eine Frau und du musst verstehen, wie es sich anfühlt, abgelehnt zu werden! Ich will Rache ")+"!";
			link.l1 = ""+GetSexPhrase("Es ist wahr, hatte noch nie so eine Erfahrung","Nun, weißt du, sie würde nur ein bisschen weinen, etwas Glas zerbrechen und das wäre vorbei")+"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+GetSexPhrase("Betrachten Sie sich als glücklich. Die zurückgewiesene und in ihren Erwartungen getäuschte Frau ist eine Furie, ein Teufel im Rock! Nichts in der Welt könnte ihren Zorn mildern","Und ich bin nicht wie sie. Nichts könnte meinen Zorn mildern")+"!\nAlso ich möchte, dass du ihn persönlich tötest. Und bevor er stirbt, muss er erfahren, wer für seinen Tod bezahlt...";
			link.l1 = "Hm, ich weiß nicht einmal, was ich sagen soll... Und wie viel zahlst du?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Alles, was ich habe. Ich werde dir meine Juwelen und "+FindRussianMoneyString(sti(npchar.quest.money))+"! Abgemacht?";
			link.l1 = "Es interessiert mich. Sag mir seinen Namen und den Namen seines Schiffes.";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "Nicht interessiert. Tschüss.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "Der Schurke heißt "+npchar.quest.SeekCap.capName+" und er segelt auf einem "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Gen"))+" genannt "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Betrachte es als erledigt, "+GetAddress_FormToNPC(NPChar)+". Warte auf mich in der örtlichen Kirche. Ich hoffe, du wirst dich ein wenig beruhigen...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("",""));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "Ich werde es erklären. Das Problem ist, dass mein Mann, der nur ein gewöhnlicher Mann ist, von Piraten gefangen genommen wurde! Sie haben jeden getötet und niemanden verschont...";
			link.l1 = "Es scheint, dass der Kapitän es gewagt hat, Widerstand zu leisten. Ansonsten hätten sie die Besatzung verschont.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Vielleicht, aber mein Mann ist eine unschuldige Seele. Er war nur ein Passagier dort. Er musste ihnen sagen, dass er reich ist, um sein Leben zu retten. Die Piraten verschonten ihn, er wurde nicht einmal in einen Laderaum gesteckt.";
			link.l1 = "Und woher wissen Sie das?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "Er hat es geschafft, mir einen Brief zu schicken. Er schrieb, dass es ihm gut geht und er nicht wie der Rest der Gefangenen in einer Kabine festgehalten wird.";
			link.l1 = "Und was planst du zu tun? Es kann nicht einfach so weitergehen. Früher oder später werden die Piraten ihn durchschauen.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "Bist du auch ein Pirat? Ja-ja, ich weiß... Ich flehe dich an, hilf uns, rette meinen Mann! Er hat dieses Piratenschiff beschrieben und den Namen des Kapitäns geschrieben. Es wird dir nicht schwer fallen, sie zu finden!";
			link.l1 = "Es ist nicht so einfach, wie Sie denken. Alle Gefangenen sind der rechtmäßige Preis des Kapitäns, der Ihren Mann gefangen hat, außerdem wird es Zeit brauchen.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "Aber du könntest es zumindest versuchen! Außerdem hast du genug Zeit zur Suche. Mein Mann ist kein Narr und gibt sich als Kaufmann aus der Alten Welt aus, sodass diese Piraten vorerst keine Münzen von ihm verlangen. Wenn du ihn befreist, gebe ich dir alles, was ich habe!";
			link.l1 = "Und was hast du?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Nicht viel, "+FindRussianMoneyString(sti(npchar.quest.money))+" und all meine Juwelen... Aber ich werde für immer für deine Seele beten!";
			link.l1 = "Ja, das ist wirklich nicht viel... Gut, ich bin bereit, dir zu helfen.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "Es tut mir leid, aber das ist für mich nicht genug.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Danke, vielen Dank!";
			link.l1 = "Du wirst mir danken, wenn ich es schaffe, also hör auf. Du solltest mir besser den Namen deines Mannes und alles, was du über diese Piraten weißt, sagen.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "Sein Name ist "+GetFullName(forName)+". Kapitäns "+npchar.quest.SeekCap.capName+", er segelt weiter "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" genannt "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Ich verstehe. Nun, jetzt sollten Sie warten und hoffen, dass ich bei meiner Suche Erfolg haben werde. Bleiben Sie in der Kirche, warten Sie und beten Sie ...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Oh, Kapitän, ich bin so froh, Sie zu sehen! Sagen Sie mir jetzt, was können Sie mir zu meiner Aufgabe sagen?";
			link.l1 = "Hm, erinnere mich, "+GetAddress_FormToNPC(NPChar)+", von welcher Aufgabe sprichst du?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "Ach, Kapitän, ich habe einen Brief von meinem Mann erhalten! Er hat geschrieben, dass Sie ihn gefunden haben.";
					link.l1 = "Ja, das ist korrekt, "+GetAddress_FormToNPC(NPChar)+". Ihr Ehemann, "+npchar.quest.SeekCap.capName+", ist wohlauf und gesund. Er ist einfach zu beschäftigt...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "Was würden Sie sagen, Kapitän? Haben Sie getan, was ich Sie gefragt habe? Ist Kapitän "+npchar.quest.SeekCap.capName+" tot?";
					link.l1 = "Ja, er ist tot, "+GetAddress_FormToNPC(NPChar)+". Ich habe ihm gesagt, wer der Grund für seinen Tod war. Das letzte, was er in seinem Leben hörte, war dein Name.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "Du hast meinen Mann gerettet! Bitte sag mir, dass es wahr ist!";
					link.l1 = "Ja, das ist er. Er ist gerade auf meinem Schiff. Du kannst ihn sehen, wenn "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+"ist wirklich dein Ehemann...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Hast du wirklich vergessen, dass du mir versprochen hast, meinen Mann zu finden? Sein Name ist "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Oh, ja, sicher... Ich habe nicht vergessen.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "Ich verstehe es nicht! Hast du vergessen, dass du meinen Angreifer töten musst, einen Kapitän namens "+npchar.quest.SeekCap.capName+"Was?!";
					link.l1 = "Ach bitte, natürlich habe ich nicht. Ihre Bestellung wird bearbeitet, bitte warten Sie...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "Jesus, Kapitän, haben Sie Ihr Versprechen vergessen, meinen Mann zu befreien?";
					link.l1 = "Ich habe nicht. Erinnerst du dich ... 'Warte und bete!'. Warte einfach, "+GetAddress_FormToNPC(NPChar)+" "+npchar.lastname+".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "Oh, Gott, ich bin so dankbar! Und ja, nimm dein "+FindRussianMoneyString(sti(npchar.quest.money))+". Und nochmals Danke!";
			link.l1 = "Hm, du bist willkommen...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "Ausgezeichnet! Nun, nimm dein "+FindRussianMoneyString(sti(npchar.quest.money))+" und Juwelen. Lebewohl...";
			link.l1 = "Auf Wiedersehen. ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			TakeNItems(pchar, "jewelry47", rand(3));
			TakeNItems(pchar, "jewelry43", rand(3));
			TakeNItems(pchar, "jewelry41", rand(3));
			TakeNItems(pchar, "jewelry48", rand(3));
			TakeNItems(pchar, "jewelry51", rand(3));
			TakeNItems(pchar, "jewelry46", rand(3));
			TakeNItems(pchar, "jewelry49", rand(3));
			TakeNItems(pchar, "jewelry40", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "Sicher, er ist es! Oh Gott, Kapitän, ich bin so dankbar. Nimm dein "+FindRussianMoneyString(sti(npchar.quest.money))+". Ich werde jeden Tag meines Lebens für dich beten!";
			link.l1 = "Klingt gut...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Grüße an meine Kollegen. Wollen Sie etwas"+GetSexPhrase(", Kumpel ",", Mädchen")+"?";
					link.l1 = "Dein Name ist "+GetFullName(npchar)+", habe ich recht?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "Ja, das bist du!";
			link.l1 = "Schade für dich. Ich werde dir einen Namen nennen und du solltest ihn besser kennen."+GetFullName(&characters[GetCharacterIndex("QuestBürger_"+npchar.quest.cribCity)])+". Erinnern Sie sich an ihn?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "Hm, ich tue...";
			link.l1 = "Jetzt hör zu, er ist sehr wütend auf dich, Kumpel. Es ist Zeit zu zahlen für den Verkauf eines freien Mannes in die Sklaverei.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "Zahlen?! Wovon zum Teufel redest du?";
			link.l1 = "Ich meine, dass ich dich genau dort töten werde, wo du stehst.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "Denk mal nach, für wen arbeitest du?! Dieser Mann ist elend und sein Platz ist auf der Zuckerplantage!";
			link.l1 = "Nun, das geht dich nichts an. Jetzt musst du für das, was du getan hast, Rechenschaft ablegen!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "Ho! Ich werde nur so antworten, wie ich es normalerweise tue!";
			link.l1 = "Mach weiter...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "Was willst du?";
			link.l1 = "Ich möchte Sie fragen, nehmen Sie Passagiere mit? ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "Und was geht dich das an?";
			link.l1 = "Nur mal gefragt.";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "Nur eine Frage... Hör zu, du solltest besser verschwinden, solange ich dir noch diese Möglichkeit gebe. Ich mag dich nicht!";
			link.l1 = "Gut, gut, beruhige dich. Ich gehe schon...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "Wir haben bereits gesprochen, also teste mich nicht!";
			link.l1 = "Ich werde nicht.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Grüße, Kollege! Brauchst du etwas?";
			link.l1 = "Ich würde gerne wissen, hast du die Frau nicht weggenommen von "+XI_ConvertString("Kolonie"+npchar.quest.cribCity+"Gen")+" genannt "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "Heh, du hast recht, sie ist in meiner Kabine! Hübsche Frau, tolle Beine übrigens... Warum fragst du?";
			link.l1 = "Kumpel, diese Frau ist verheiratet. Das ist falsch.";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "Na und? Ich mag sie und das ist es. Ich werde nicht zulassen, dass irgendein zerlumpter Idiot sich in unsere Beziehung einmischt, nur weil er ihr Ehemann ist!";
			link.l1 = "Lass mich dir sagen, dass die Brüderschaft Dinge wie diese nicht gutheißt, und wenn gewisse Leute von dem hören, was du getan hast, wird die schwarze Marke auf dich geworfen.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "Wirst du anfangen, mir eine Predigt zu halten?";
			link.l1 = "Beruhige dich, ich hatte nur Interesse... Auf Wiedersehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "Wir haben bereits über die Frau gesprochen. Ich möchte die Angelegenheit nicht noch einmal diskutieren!";
			link.l1 = "Was auch immer...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Ich freue mich, einen Kollegen auf meinem Deck zu begrüßen! Was möchtest du?";
			link.l1 = "Ich möchte wissen, ob Sie eine Frau entführt haben aus "+XI_ConvertString("Kolonie"+npchar.quest.cribCity+"Gen")+" mit dem Namen"+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "Heh, du hast recht, sie ist in meiner Kabine! Heiße Braut, schöne Beine übrigens! ... Warum fragst du?";
			link.l1 = "Kumpel, diese Frau ist verheiratet. Das ist falsch.";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "So was? Ich mag sie und das ist es. Ich werde nicht zulassen, dass irgendein Lump in unsere Beziehung eingreift, nur weil er ihr Ehemann ist!";
			link.l1 = "Lass mich dir sagen, dass die Bruderschaft solche Dinge nicht gutheißt und wenn bestimmte Leute von dem hören, was du getan hast, wird das schwarze Zeichen dir geschickt.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "Wirst du anfangen, mir zu predigen?";
			link.l1 = "Beruhige dich, ich habe nur Interesse gezeigt... Auf Wiedersehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Was willst du von mir, Abschaum?!";
			link.l1 = "Ich bin hier für die Frau, die du ihrem Ehemann gestohlen hast. Erinnere dich "+XI_ConvertString("Kolonie"+npchar.quest.cribCity)+"? Ihr Name ist "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "Verdammt! Sie werden sie genauso wenig sehen wie Sie Ihre Ohren niemals sehen werden!";
			link.l1 = "Trottel. Ich kann sie in einem Spiegel sehen. Und ich werde deine abschneiden!";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_"+(hrand(3)+7); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "Wer bist du?";
			link.l1 = "Hallo. Ich bin gekommen, weil Ihr Mann mich gebeten hat. Jetzt bist du frei und ich kann dich zu ihm bringen.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "Ist es ein Traum?! Ist es wahr?!";
			link.l1 = "Es ist, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "Preist den Herrn! Ich bin bereit, lass uns von hier verschwinden!";
			link.l1 = "Sicher, "+GetAddress_FormToNPC(NPChar)+", bereite dich auf eine sichere Rückkehr zu deinem Mann vor.";
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "Hallo! Froh, einen Kollegen auf dem Boden zu begrüßen...";
			link.l1 = TimeGreeting()+", Ich habe Geschäft mit dir.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "Ich höre zu.";
			link.l1 = "Ein Kamerad von Ihnen sucht Sie. Sie sind zusammen gesegelt und kamen hier aus der Alten Welt an."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+", erinnerst du dich?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "Ha, sicher weiß ich das! Und wo lebt er jetzt?";
			link.l1 = "In "+XI_ConvertString("Kolonie"+npchar.quest.cribCity+"Dat");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = " Danke! Sie wissen, ich dachte, dass Sie ein Pirat sind!";
			link.l1 = "Ich bin es. Irgendwie. Oder ich bin es nicht. Aber so oder so, ich bin heute gut gelaunt, also musst du dir keine Sorgen machen. Lebewohl.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "Gibt es ein Problem? Es tut mir leid, ich bin ein bisschen nervös...";
			link.l1 = "Es ist alles in Ordnung, Kumpel.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting()+". Was wollen Sie von mir? Ich bin nur ein gewöhnlicher Händler und...";
			link.l1 = "Ich weiß, Kumpel. Mach dir keine Sorgen, sie sagen, es sei nicht gut für die Gesundheit. Ich habe ein Geschäft mit dir.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "Welche Art von Geschäft?";
			link.l1 = "Ein Freund von dir sucht dich. Sein Name ist "+GetFullName(&characters[GetCharacterIndex("QuestBürger_"+npchar.quest.cribCity)])+". Kennst du ihn?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "Oh, endlich! Das ist großartig... Es tut mir so leid für diese grobe Begrüßung, aber ich dachte, du wärst ein Pirat.";
			link.l1 = "Ich bin es. Irgendwie. Oder ich bin es nicht. Aber trotzdem, heute bin ich gut gelaunt, also musst du dir keine Sorgen machen. Ich wurde gebeten, dir eine Nachricht zu überbringen und ich habe meinen Job erledigt. Dein Kamerad lebt in "+XI_ConvertString("Kolonie"+npchar.quest.cribCity+"Hallo, Freund.")+"."; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "Ist das nicht etwas! Sie sind ein ehrenhafter Mann. Danke!";
			link.l1 = "Du bist willkommen. Leb wohl und pass auf dich auf, Kumpel.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "Hallo. Willst du etwas?";
			link.l1 = "Dein Name ist "+GetFullName(npchar)+", habe ich recht?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "Ja, ich bin es.";
			link.l1 = "Es klingt wahrscheinlich dumm, aber deine Frau hat mich gebeten, dir zu sagen, dass sie sich um dich sorgt.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "Ha! Ich sehe... Tatsächlich war ich zu beschäftigt, es gibt viele profitable Angebote und ich kann mögliche Einnahmen nicht verlieren, nur weil meine Frau sich zu sehr sorgt.";
			link.l1 = "Aber du könntest ihr zumindest einen Brief schreiben und ihr sagen, dass es dir gut geht.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "Ja, du hast recht. Ich werde ihr sofort schreiben! Danke, dass du dich an unseren Familienangelegenheiten beteiligst!";
			link.l1 = "Du bist willkommen, Kumpel.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "Guten Tag. Wie kann ich Ihnen helfen?";
			link.l1 = "Dein Name ist "+GetFullName(npchar)+", habe ich recht?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Ja, ich bin es.";
			link.l1 = "Es klingt wahrscheinlich dumm, aber Ihre Frau hat mich gebeten, Ihnen zu sagen, dass sie sich Sorgen um Sie macht.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Fuh, verdammt! Ich habe befürchtet, dass es der berühmte Kopfgeldjäger war, der nach mir sucht, Einäugiger Steve ist sein Name. Gut, dass ich mich geirrt habe\nSiehst du, ich bin so beschäftigt mit meiner Arbeit und ich kann keine Zeit für sie erübrigen. Ich bekomme ständig profitable Angebote und kann sie wegen der Sorgen meiner Frau nicht ablehnen.";			
			link.l1 = "Du hast recht, sicher. Aber du könntest ihr zumindest einen Brief schreiben und sagen, dass es dir gut geht.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Ja, du hast recht. Ich werde es im allerersten Hafen tun... Danke, dass du dich an unseren Familienangelegenheiten beteiligst!";
			link.l1 = "Du bist willkommen, Kumpel.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Sie haben meinen Dank, Kapitän...";
			link.l1 = "Du bist willkommen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "Freut mich, Sie in dieser Stadt zu sehen, Kapitän. Brauchen Sie etwas von mir?";
			link.l1 = ""+GetSexPhrase("Weißt du, Kapitän... Fuh, ich weiß nicht einmal, wie ich es sagen soll!","Ja, das habe ich.")+"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+GetSexPhrase("Sag es, wie es ist.","Interessant, und was ist es?")+"";
			link.l1 = " Ich habe eine Frage an dich. Kennst du eine Frau namens "+GetFullName(&characters[GetCharacterIndex("QuestBürger_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "Heh, das tue ich. Hatte ein Pech, sie zu kennen. Ein törichtes Mädchen, kann ich dir sagen...";
			link.l1 = "Hm... Ja, und dieses törichte Mädchen hat mich gebeten, dich zu töten. Das ist es....";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "Unsinn.";
			link.l1 = ""+GetSexPhrase("Ich stimme zu. Entschuldigung, aber es gibt eine Belohnung für deinen Kopf","Das ist es nicht. Es gibt eine Belohnung")+". Und ich werde es nehmen.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "Ho-ho!... Machst du Witze mit mir, Kapitän?";
			link.l1 = ""+GetSexPhrase("Nein, Freund.","War nicht mal dabei!")+"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+GetSexPhrase("Du bist nicht mein Freund, Idiot! Du kannst dich nicht einmal einen Kapitän nennen. Du bist ein Spielzeug dieser törichten Wut!","Verdammt! Eine Furie hat eine andere angeheuert! Was zur Hölle geht in dieser Welt vor?")+"!";
			link.l1 = ""+GetSexPhrase("Pass auf deinen Mund auf, Dreckssack.","Du hast sie benutzt, also wundere dich nicht, dass sie sich entschieden hat, Rache zu nehmen.")+"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+GetSexPhrase("Habe ich einen Nerv getroffen?","Frauensolidarität?!")+"";
			link.l1 = "Lass uns das beenden!";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "Ich habe bereits mit dir gesprochen. Verschwinde, Trottel!";
			link.l1 = "Trottel?! Na gut dann...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "Froh, Sie an Bord zu sehen, Kapitän. Was wollen Sie?";
			link.l1 = "Ich habe eine Frage an dich. Kennst du eine Frau namens "+GetFullName(&characters[GetCharacterIndex("QuestBürger_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "Heh, das tue ich. Hatte Pech, sie zu kennen. Ein törichtes Mädchen, kann ich dir sagen...";
			link.l1 = "Ja, und dieses törichte Mädchen hat mich gebeten, dich zu töten.";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "Kapitän, bring mich nicht zum Lachen. Wenn du keine ernsthafte Geschäfte mit mir hast, dann sage ich dir auf Wiedersehen.";
			link.l1 = "Lebewohl, dann. Aber denke über das nach, was ich dir gesagt habe.";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "Sicher, Kapitän, wie könnte es anders sein?!";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "Ich möchte nicht mehr über diese Angelegenheit sprechen, Kapitän. Das ist viel zu lächerlich.";
			link.l1 = "Wie du willst...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "Was zum Teufel geht hier vor?! Warum habt ihr mein Schiff angegriffen?";
			link.l1 = "Im Auftrag der Dame namens "+GetFullName(&characters[GetCharacterIndex("QuestBürger_"+npchar.quest.cribCity)])+". Kennst du sie?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "Was zum Teufel!!! Ich kann es nicht glauben...";
			link.l1 = "Du musst! Kennst du keine Frauen, Kumpel? Sie können beißen.";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "Nun, ich werde nicht einfach so sterben. Danke für den Plausch, jetzt habe ich etwas Kraft zurückgewonnen.";
			link.l1 = "Es wird dir nicht helfen.";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Froh, Sie an Bord zu sehen. Kann ich Ihnen helfen?";
			link.l1 = "Du kannst. Ich suche einen Mann namens "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "Dieser Mann ist mein Gefangener und ich plane, ihn zu erpressen.";
			link.l1 = "Ich will ihn nehmen.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "Leider ist das unmöglich. Wenn das alles ist, würde ich Sie bitten, mein Schiff zu verlassen.";
			link.l1 = "Gut, Kapitän, wie Sie sagen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "Wir haben bereits über meinen Gefangenen gesprochen. Nichts hat sich geändert.";
			link.l1 = "Ich sehe...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Freut mich, Sie zu treffen. Darf ich Ihnen helfen?";
			link.l1 = "Sie dürfen. Ich suche einen Mann namens "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "Dieser Mann ist mein Gefangener und ich plane, ihn auszulösen.";
			link.l1 = "Ich will ihn nehmen.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "Es tut mir leid, aber es ist nicht möglich.";
			link.l1 = "Schade...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Verdammt! Was zur Hölle?!";
			link.l1 = "Ich brauche Ihren Gefangenen namens "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ha! Auf keinen Fall, nur über meine Leiche!";
			link.l1 = "Da du gefragt hast...";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+11); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "Wer bist du?";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+". Mach dir keine Sorgen, ich bin hier, um dich zu deiner Frau zu bringen.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Verdammt, ich muss träumen!";
			link.l1 = "Ich kann Ihnen versichern, dass es nicht der Fall ist... Nun, es ist jetzt alles vorbei, lassen Sie uns Sie von hier wegbringen.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Ich bin erschöpft, hilf mir.","Ich habe keine Kraft mehr, so zu leben!"),RandPhraseSimple("Diese Arbeit frisst uns lebendig auf.","Verdammte Wachen haben kein Stück Haut auf meinem Rücken gelassen!"));				
				link.l1 = RandPhraseSimple("Wie schade.","Ja, das Leben ist eine Schlampe.");
				link.l1.go = "exit";				
    		} 
		break;
		
		//=====================================================================================================================================
		// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);
			
			if(LoadedLocation.type == "tavern")
			{
				// "Честь мундира".
				if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = "Oh, Kapitän, setz dich zu mir. Ich lade ein!";
					link.l1 = "Mit Vergnügen.";
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if(NPChar.sex == "man")
				{
					// "Невольник чести".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
					{
						dialog.text = "Hallo, Kapitän. Sie sind ein Kapitän, nicht wahr? Vielleicht sogar ein Marinekapitän?\nJa, Sie müssen gut mit einem Schwert umgehen können im Gegensatz zu meinem nichtsnutzigen Sohn, der morgen sterben wird... Wegen dieses lüsternen Bastards, der ein Auge auf die Dame meines Sohnes geworfen hat!";
						link.l1 = "Ja, ich bin ein Kapitän, und mein Schwert hat mich schon viele Male gerettet, aber was ist mit dem Rest deiner depressiven Rede? Könntest du das erklären?";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "Красотка и пират".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "Grüße, Kapitän. Darf ich fragen, bist du zufällig ein Pirat? Oh, natürlich nicht! Du bist es nicht. Piraten sehen schlecht aus, benehmen sich wie Tiere und dieser Gestank...";
						link.l1 = "Hast du Groll auf Piraten?";
						link.l1.go = "AffairOfHonor_BeautifulPirate_1";
						PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;
					}
					
					// "Заносчивый нахал".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
					{
						//if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
						//{
						// Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
							dialog.text = "He, du! Ja, du, sag mir, wo sind deine Manieren? Warum zum Teufel stehst du hier und belästigst mich? Nein, sieh ihn dir nur an, so ein Idiot! Ich rede mit dir! Mach Platz! Zu viele Außenseiter hier!";
							link.l1 = "Beruhige dich, ich wollte dich nicht stören. Entschuldigung.";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "Hüte deine Zunge, oder ich schneide sie ab, mein guter Herr.";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "Волки и овцы".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "Grüße, Kapitän. Ich habe eine Bitte an Sie. Sie werden nicht untätig bleiben, wenn Sie ein Ehrenmann sind.\nAlso, kommen wir zur Sache: Vor einem Monat übernachtete ein Adliger in unserer Taverne. Er stellte sich als Wüstling und Schurke heraus! Noch mehr, er ist ein Mörder!";
						link.l1 = "Soweit ich mich erinnere, ist die Strafe für den Mord an einem Unschuldigen der Galgen. Ein liederlicher und unehelicher Kerl zu sein, wird vor Gericht auch nicht viel nützen. Habe ich Recht?";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "Трусливый фехтовалщик".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "Kapitän, warten Sie, ich flehe Sie an. Sie sehen aus wie ein geschickter Fechter, viel besser als ich. Also möchte ich Sie bitten, mich zu ersetzen.";
						link.l1 = "Faszinierend. Mach weiter.";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "Божий суд".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "Bitte, ich flehe dich an, geh nicht weg! Warte... Würdest du einer armen Seele in einer Angelegenheit helfen, die die Einmischung eines so tapferen Militäroffiziers wie dir erfordert?\nDie Sache ist, dass ich mich wegen der örtlichen Weinplantagen mit meinem Nachbarn gestritten habe, der übrigens im Verdacht steht, mit Schmugglern Geschäfte zu machen. Ja, ja, und er könnte sogar einige Geschäfte mit Piraten haben, wie sonst könnte er in so kurzer Zeit ein solches Vermögen gemacht haben?\nVor einem Jahr hatte er nichts als eine Barkasse und jetzt will er meine Weinberge nehmen, hörst du?! Meine Weinberge!";
						link.l1 = "Ich bedauere Ihre Weinberge. Wirklich. Auf Wiedersehen.";
						link.l1.go = "exit";
						link.l2 = "Entschuldigen Sie, aber könnten Sie sich nicht an die örtlichen Behörden wenden?";
						link.l2.go = "AffairOfHonor_GodJudgement_1";
						PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "Навязчивый кавалер".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = "Kapitän, Kapitän, ich flehe Sie an! Schützen Sie die Ehre des unschuldigen Mädchens!";
						link.l1 = "Ich habe keine Zeit für so etwas, Hübsche. Such dir jemand anderen...";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "Grüße, meine Dame. Zittern Sie nicht so! Was ist passiert?";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "Fehler. Informiert die Entwickler.";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "Kapitän, ich wurde auf unverhohlene Weise von einem Offizier unserer Garnison verfolgt. Du könntest diese schmutzigen Gerüchte gehört haben, die er über mich verbreitet, um mich zu beschämen!\nAch, ich habe keine Freunde, die meinen ehrlichen Namen schützen können! Ich bin verzweifelt! Oh, Gott, das ist er! Hilf mir!";
			link.l1 = "Mach dir keine Sorgen, ich werde es durchstehen.";
			link.l1.go = "exit";
			int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_14"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
			float Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;
		
		case "AffairOfHonor_Cavalier_2":
			dialog.text = "Ach, da bist du ja, meine Dame! Noch ein Kavalier, nehme ich an? Wann wirst du dich niederlassen? Vielleicht nie... Geh im Bordell arbeiten, das ist der geeignetste Ort für dich...";
			link.l1 = "Offizier, halte dein Mundwerk vom Ausspucken von Beleidigungen ab, oder ich werde es auf meine ganz besondere Weise zum Schweigen bringen!";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "Hm... Wer bist du? A-ah, vom Meer selbst gesalzen der mutige Kapitän eines kleinen Bootes, habe ich recht? Und was hast du vor, Seebärchen?";
			link.l1 = "Diese Dame ist meine Freundin! Und ich werde einen Handschuh für dich übrig haben!";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "Was?! Du wirst mich nicht wegen diesem herausfordern...";
			link.l1 = "Genug! Ich werde in zwei Stunden nahe beim Leuchtturm auf dich warten. Und vergiss nicht, dein Schwert zu bringen!";
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;
		
		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;
		
		case "AffairOfHonor_Cavalier_5":
			dialog.text = "Ach, ich weiß alles, Herr! Sie können sich gar nicht vorstellen, wie dankbar ich Ihnen bin! Möge der Herr Sie schützen!";
			link.l1 = "Ich bin froh, dass ich Ihnen helfen konnte. Viel Glück!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar, "nobility", 7);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Cavalier_6":
			dialog.text = "Ach, du bist genau wie alle anderen, verlass mich!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "or in the brothel ";
			dialog.text = "Ach, "+GetAddress_Form(NPChar)+"... Ich wage es nicht zu hoffen, aber vielleicht könnte dein Schwert dieses Mal meine Familie schützen?\nWie ich sagte, mein Sohn ist kein Fechter, aber er wird am nächsten Morgen zum Duell gehen. Ach, wenn es nicht um seine Dame und die verdammte Ehre ginge\nAber er konnte nicht beiseite treten und jetzt ist er verdammt, siehst du das nicht? Ich bin verzweifelt, er ist mein einziger Sohn und Erbe, daher bitte ich dich, den Bastard zu töten, der meinen kleinen Jungen vor der Morgendämmerung herausgefordert hat. Ich werde es deiner Zeit wert machen, darauf kannst du zählen!\nDu wirst den Mann in der Taverne finden "+sTemp+" - dort, wo Bastarde wie er ihre Freizeit verbringen... Ich flehe Sie an...";
			link.l1 = "Mir ist weder du noch dein Sohn wichtig. Lass mich gehen!";
			link.l1.go = "exit";
			link.l2 = "Hm ... Einfach so? Gut, wir werden sehen, wie das endet.";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "Wirst du wirklich meinem Sohn helfen? Oh, "+GetAddress_Form(NPChar)+"! Ich werde für dich und dein Glück beten!";
			link.l1 = "Ich sehe darin kein Unheil... Warte auf mich!";
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;
		
		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
			Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04","blade_06"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			if(rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;
		
		case "AffairOfHonor_HonorSlave_3":
			dialog.text = "Was zum Teufel willst du von mir? Ich habe hier eine Pause und ich möchte nicht gestört werden. Es gibt genug freie Plätze und offene Ohren, also lass mich in Ruhe, Herr!";
			link.l1 = "Leider müssen Sie Ihre Ruhe bis zu besseren Zeiten unterbrechen.";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "Was?! Und wer bist du, um mir zu sagen, was ich tun soll?!";
			link.l1 = "Hast du mich vergessen, huh? Aber ich erinnere mich an dich! Und mein Punkt ist, dass Schurken wie du unsere Welt nur durch ihre Anwesenheit vergiften!";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "Ach?! Seemann, es scheint, du bist viel zu betrunken! Es ist das erste Mal, dass ich dich sehe! Aber ich werde dein Verhalten nicht ignorieren! Dies ist deine letzte Chance, dein elendes Leben zu retten! Entschuldige dich jetzt, du aufgeblasener Hering, und ich werde deine unverschämte Rede vergessen!";
			link.l1 = "Ich mache Ausreden nur für ehrenwerte Männer, nicht für dreckige Schweine!";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "Was zum Teufel?! Suchst du Ärger, Latrinenlaus?";
			link.l1 = "Ich werde deinen verdammten Hals mit deinen Worten stopfen, Ratte! Ich werde in zwei Stunden in der Nähe des Leuchtturms auf dich warten und vergiss nicht, diesen rostigen Schrott mitzubringen, den du an deinem Gürtel trägst!";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "Ha! Ich werde da sein!";
			link.l1 = "Bis bald!";
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;
		
		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
		break;
		
		case "AffairOfHonor_HonorSlave_7":
			dialog.text = "Ach, du bist es! Du lebst, was bedeutet, dass...";
			link.l1 = "Ja, das bin ich, und dein Sohn muss morgen früh nicht duellieren...";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "So ein schöner Tag! Ich sollte gehen und meiner Frau gute Nachrichten erzählen!\nKapitän, das Schicksal selbst hat dich geschickt, um mir zu helfen. Hier, nimm diese Münzen und akzeptiere die Dankbarkeit unserer Familie!";
			link.l1 = "Danke dir!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(iTemp)+"");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_9":
			dialog.text = "Verpiss dich, Kindermörder!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "Ich? Gott sei Dank, mir geht es gut, aber meine Schwester hat weniger Glück. Sie arbeitet in einer Taverne\nDa ist ein Freibeuter, der oft dort auftaucht, ein sehr gefährlicher Typ. Pirat! Sein Schiff ist schon seit mindestens einer Woche auf See. Der Kerl trinkt, bedroht Leute und verspricht, jeden zu töten, der versucht, ihm Vernunft beizubringen. Das Schlimmste ist, dass meine Schwester mir erzählt hat, er prahlt damit, sie zu stehlen und sie weiß der Teufel wohin zu bringen, wenn sie seinen schmutzigen Wünschen nicht nachkommt!\nIch weiß nicht, was ich tun soll! Die Behörden kümmern sich nicht um ein Dienstmädchen und friedliche Bürger wie ich haben Angst vor diesem Freibeuter. Bitte helfen Sie uns, mit ihm fertig zu werden!";
			link.l1 = "Ich habe keine Zeit, um Betrunkene in Tavernen zu beruhigen. Sprich mit dem Kommandanten, sie bezahlen ihn, um solche Angelegenheiten zu klären.";
			link.l1.go = "exit";
			link.l2 = "Hm, ein bedrohlicher Freibeuter? Gut, ich werde mich darum kümmern.";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "Ach, danke, Kapitän! Ich bin sicher, er wird Ihnen zuhören, wie ein Seemann einem Seemann zuhört! Lassen Sie ihn meine Schwester für immer in Ruhe! Wir sind nicht reich, aber wir werden Sie für Ihre Mühen ausreichend bezahlen!";
			link.l1 = "Gut, gut... Ich bin auf dem Weg, deine Probleme zu lösen. Wartet auf mich!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 25+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;
		
		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = "Na und? Hast du mit diesem Piraten gesprochen? Wird er uns in Ruhe lassen?";
			link.l1 = "Warte mal. Ich kümmere mich darum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "Was willst du? Siehst du nicht, dass ich hier eine Pause mache?";
			link.l1 = "Nun, nun... Sieh an, der große Herr der Bierbecher, Mädchenräuber und Sturm dieses kleinen Städtchens in Fleisch und Blut, habe ich recht? Und wärst du auch so mutig außerhalb der Stadt? In der Nähe des Leuchtturms, ein Duell, in zwei Stunden?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "Oh-ho-ho! Tust du so als wärst du ein Held? Wie auch immer, Kumpel, ich bin heute gut drauf, also verzeihe ich dir. Geh und kaufe mir ein paar Krüge Bier!";
			link.l1 = "Ich bin nicht dein Kumpel. Soll ich mich für einen Idioten wie dich wiederholen? Wärst du so mutig, zum Duell zu erscheinen, wie du mutig bist, in der Kneipe zu erscheinen?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "Fordern Sie mich heraus?! Was stimmt nicht mit Ihnen? Haben Sie genug vom Leben, wollen Sie sterben, Sie Tölpel? Gut, wenn Sie das wirklich wollen, werde ich zum Leuchtturm gehen, Ihnen die Eingeweide herausreißen und dann werde ich diese verdammte Taverne zerstören!";
			link.l1 = "Reden ist billig, Schwerter sind es nicht, also denk daran, eines mitzubringen!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;
		
		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = "Na und? Hast du mit diesem Piraten gesprochen? Wird er uns in Ruhe lassen? Meine Schwester hat mir erzählt, dass er die Kneipe verlassen hat und nicht zurückgekommen ist...";
			link.l1 = "Ich habe. Der Kerl war etwas unhöflich, aber meine Argumente waren ziemlich vernünftig und überzeugend. Ihre Schwester hat jetzt nichts mehr zu befürchten.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "Das... ist es vorbei? Können wir jetzt frei atmen? Danke, Kapitän! Und wo... wo ist dieser Schurke??";
			link.l1 = "Er... ist auf seinem Schiff. Er hat beschlossen, diese Stadt so schnell wie möglich zu verlassen.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "Sie haben den Bürgern dieser Kolonie einen großen Dienst erwiesen! Hier, nehmen Sie diese Belohnung für Ihre Hilfe! Sie ist ziemlich bescheiden, aber Sie werden den Respekt all meiner Freunde gewinnen und, glauben Sie mir, ich habe eine Menge davon!";
			link.l1 = "Mein Dank! Viel Glück euch und eurer Schwester. Ich wünsche ihr, dass sie einen ehrenwerten Mann heiratet. Lebewohl!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Jackanapes_1":
			dialog.text = "Oh, wirklich? Und wie planst du mich aufzuhalten?";
			link.l1 = "Mit meinem Schwert natürlich, das ist der einzige passende Weg für so ein freches Schwein wie dich.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "Hervorragend! Ich werde in zwei Stunden in der Nähe des Leuchtturms auf dich warten.";
			link.l1 = "Prima! Ich werde sicher dort sein.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;
		
		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // Еще успеем.
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
		break;
		
		case "AffairOfHonor_Jackanapes_2":
			dialog.text = "Komm aus meinem Weg, Feigling!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "Kapitän, der Bastard ist nicht so einfach, Tom, mein alter Freund, starb in einem Duell gegen ihn, beschuldigt des Kartenbetrugs! Er war unschuldig, ich schwöre es. Aber der Gouverneur sagte, dass in diesem verfluchten Duell kein Verbrechen vorlag.";
			link.l1 = "Hm... Es ist alles die Schuld deines Freundes. Falschspiel kann schlecht für deine Gesundheit enden.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "Ja? In den letzten zwei Wochen gab es bereits vier Kartenschwindler in unserer Stadt. Und alle versuchten, unseren Edelmann zu betrügen? Was würdest du dazu sagen? Meiner Meinung nach ist dieser Edelmann selbst der Kartenschwindler. Wenn du mir nicht glaubst, dann geh und überprüfe es selbst.";
			link.l1 = "Du meinst, mit ihm zu spielen? Nein, ich spiele nicht gerne. Keine Chance.";
			link.l1.go = "exit";
			link.l2 = "Ich nehme an, ich werde das tun... Hier stimmt etwas ganz und gar nicht.";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "Kapitän, ich und meine Freunde haben eine Summe gesammelt, um den Mann zu bezahlen, der diesen Adligen entlarven und sich für all seine Taten an ihm rächen wird. Ich werde in der Stadt auf dich warten, um dir deine Belohnung zu geben, sobald die Arbeit erledigt ist.";
			link.l1 = "Ich werde das tun, wenn das, was du sagst, wahr ist.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = "Mein Respekt, Herr! Ich sehe einen edlen Mann und vielleicht... einen Spieler? Lust auf ein Spiel?";
			link.l1 = "Sicher! Lass uns über den Einsatz reden. Wie wäre es mit 50 Münzen?";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "Du machst wohl Witze? Du hast sie nicht!";
				link.l1 = "Du hast recht...";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "Einsatz ist irrelevant, wir werden spielen, das ist der beste Teil. Ich habe fast vergessen, wie die Karten aussehen, wegen der hiesigen Idioten.";
				link.l1 = "Nun, lasst uns beginnen.";
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = "Also, der Einsatz beträgt 50 Münzen.";
			link.l1 = "...";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
            PChar.GenQuest.Cards.SitType = true;
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = "Warten Sie mal, was ist das?.. Unmöglich! Herr, Sie sind ein Betrüger! Geben Sie mir meine Münzen zurück!";
			link.l1 = "Du musst stichhaltige Gründe haben, um mich zu beschuldigen,  "+GetAddress_FormToNPC(NPChar)+". Du solltest sie jetzt besser abschießen, oder es wird ein Duell geben!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "Ach, einfach so? Gut, dann ein Duell! Heute, in zwei Stunden, in der Nähe des Leuchtturms!";
			link.l1 = "Abgemacht!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = "Gibt es Neuigkeiten, Kapitän?";
			link.l1 = "Du hattest recht, man beschuldigte mich auch des Betrugs, also musste ich den Bastard im Duell niederstrecken.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "Siehst du jetzt? Das wusste ich! Vielen Dank von mir und meinen Freunden! Hier, nimm deine Belohnung, Kapitän.";
			link.l1 = "Danke.";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_1":
			dialog.text = "Habe ich dir erzählt, dass ich hierher gekommen bin, um mich als Fechtlehrer zu bewerben? Nein? Also, der örtliche Gouverneur sucht einen Lehrer für seinen Neffen und das passt mir gerade perfekt. Ich kenne die Grundlagen dieser Kunst, habe es aber noch nie in der Praxis ausprobiert\nIch hatte den Job fast in der Tasche, doch es stellte sich heraus, dass der örtliche Händler in Schwierigkeiten geraten ist, irgendein gefährlich aussehender Schurke bedroht ihn. Der Gouverneur hat mir den Auftrag gegeben, mich um diese Angelegenheit zu kümmern, um meine beruflichen Fähigkeiten zu testen.";
			link.l1 = "Tu es dann. Lebewohl.";
			link.l1.go = "exit";
			link.l2 = "Und was will dieser Schurke vom Kaufmann und wofür braucht ihr mich?";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "Ich dachte, der Mann sei ein Söldner und mit Söldnern kann man immer einen Handel eingehen. Alte Schulden oder was auch immer... Aber der Mann war ernsthaft in seiner Absicht, den Druck auf den Kaufmann weiter zu erhöhen. Ich wollte dich bitten, dem Kaufmann und mir zu helfen, indem du ihn vor dem Söldner rettest und die Anordnungen des Gouverneurs erfüllst.\nIch brauche diese Position wirklich und ich kann den Söldner nicht alleine loswerden. Bitte, hilf mir und ich werde dir jeden Groschen geben, den ich gespart habe, oder ich werde gezwungen sein, die Stadt in Schande zu verlassen!";
			link.l1 = "Gut, gut, ich helfe dir... 'Meister des Fechtens'.";
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;
		
		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
			Scl = 30+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_"+(rand(7)+23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06","blade_10"), RandPhraseSimple("pistol4","pistol6"), "bullet", Scl*3+70);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;
		
		case "AffairOfHonor_CowardFencer_2":
			dialog.text = "Was willst du? Siehst du nicht, dass ich beschäftigt bin?!";
			link.l1 = "Belästigt einen anständigen Kaufmann und macht Krach!?";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "Bah! Noch ein Beschützer? Es wäre billiger, mich zu bezahlen, anstatt jeden Tag Wachen zu mieten. Ich mag die Tötungsarbeit nicht wirklich im Vergleich zum Schulden eintreiben, also wenn du so ein Held bist, dann komm zum Leuchtturm und wir werden uns in einem Duell testen. Und wenn du es nicht bist, dann belästige mich nicht noch einmal.";
			link.l1 = "Abgemacht! Ich werde dort auf dich warten.";
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;
		
		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = "Es scheint, du bist noch größerer Feigling als ich...";
			link.l1 = "Ja, das bin ich.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "Gibt es Neuigkeiten, Kapitän?";
			link.l1 = "Der Söldner ist tot. Ich hoffe, dass die Position jetzt Ihnen gehört?";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "Oh, Kapitän, mein Dank! Nimm deine Belohnung und ich werde unserem Gouverneur Bericht erstatten!";
			link.l1 = "Auf Wiedersehen... Meister.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			GiveItem2Character(pchar, "chest"); 
			Log_Info("You have received a chest filled with doubloons");
			PlaySound("interface\important_item.wav");
		break;
		
		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "AffairOfHonor_CoatHonor_2":
			dialog.text = "Noch einer?";
			link.l1 = "Ex runter.";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "Und noch mehr!";
			link.l1 = "Warte mal! Wo rennst du so eilig hin?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "Zum Teufel mit den Fragen! Trink!";
			link.l1 = "Gut, aber vielleicht erzählst du mir später, was dir passiert ist?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "Bist du wirklich interessiert? Dann hör zu, während ich noch sprechen kann! In ein paar Tagen werde ich nicht mehr sprechen können, denn ich werde tot sein... Ja, tot! Und der Rum ist schuld. Viel Rum und dieser Offizier, anscheinend vom Teufel über meinen Kopf gebracht!\nSicher würde ich nicht mit dem besten Fechter unserer Garnison und der ganzen Stadt kämpfen, wenn ich nüchtern oder zumindest nicht so betrunken wäre. Aber was jetzt? Ich bin verdammt, verschwendet und ich bin tot! Ich bin so ein dummer Narr...";
			link.l1 = "Ja, das war zu dumm. Aber wahrscheinlich wirst du in der Zukunft klüger handeln... falls du natürlich das Duell überlebst. Lebewohl.";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "Betrunken zu werden ist auch nicht die beste Option, Offizier. Ich bin sicher, dass es eine Lösung für dieses Problem gibt.";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "Welche Art von Lösung? Zu desertieren und meinen Ruf und meine Offiziersuniform zu verlieren? Oder einen Selbstmord zu begehen, um zu verhindern, dass ich wie ein Schwein abgeschlachtet werde? Was wird dein Rat sein?";
			link.l1 = "Keiner von beiden. Ich werde Ihnen helfen und versuchen, zu verhindern, dass Ihr Gegner Ihnen vor der Zeit Ihres Duells Schaden zufügt. Wo kann ich ihn finden?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "Bist du ernst? Du wirst es tun?! Oh, ich schwöre, ich werde es dir wert machen!\nEr kann in der Stadt gefunden werden. Seine Geliebte lebt hier, alle Offiziere haben von ihr gehört, aber leider ist ihre Adresse unbekannt... Also meine Wette ist, dass du ihn auch dort finden kannst.";
			link.l1 = "Das reicht. Warte hier auf mich. Ich werde mit diesem... 'besten Fechter' mal ein Wörtchen reden.";
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;
		
		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
		break;
		
		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = "Haben Sie Neuigkeiten für mich, Herr? Gute oder... sind sie nicht so gut?";
			link.l1 = "Ich habe noch keine Neuigkeiten. Warte hier. Alles wird gut.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "Haben Sie Neuigkeiten für mich, Herr? Gute oder... sind sie nicht so gut?";
			link.l1 = "Es ist vorbei. Ihr potenzieller Gegner wird niemandem mehr Schaden zufügen können... Sie sind jetzt sicher. Aber ich hoffe, dass Sie aus dieser Lektion lernen und nicht aggressiv gegenüber Menschen sein werden, die Sie nicht kennen.";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "Du machst wohl Witze, oder? Ich... Ich bin wirklich dankbar, "+GetAddress_Form(NPChar)+"! Hier, nimm alles, was ich habe. Das ist mein Lohn, nimm ihn ganz!\nEine Lektion, sagst du? Ja, verdammt, du hast Recht! Das wird nie wieder passieren! Das verspreche ich dir, und danke dir noch einmal, dass du mir eine weitere Chance gegeben hast!";
			link.l1 = "Na gut dann. Auf Wiedersehen, Offizier...";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("You have received a purse with doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "Nochmals danke, "+GetAddress_Form(NPChar)+", für deine Hilfe!";
			link.l1 = "Du bist immer willkommen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "He, was zur Hölle? Was machst du in den Gemächern meiner Dame? Verschwinde von hier, oder ich werde dich mit Gewalt hinauszerren!";
			link.l1 = "Ich gehe wohin ich will und ich werde dich wegen solchem Verhalten nicht melden! Mit Gewalt? Versuch's doch!";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "So eine Frechheit! Ungehörte Anmaßung! Herr, Sie irren sich wirklich! Verlassen Sie sofort dieses Haus, oder ich schwöre, dass Sie Ihr Leben bereuen werden!";
			link.l1 = "Reden ist billig! Du wirst das bereuen, nicht ich, "+GetAddress_FormToNPC(NPChar)+"! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "Wirklich? Dann sei vorsichtig! Wenn ich dich in diesem Haus töte, wird es ein Mord sein. Also wird dein Tod meinen Namen nicht beschmutzen, Ehrenmänner regeln solche Angelegenheiten in der Nähe eines Leuchtturms!\nIch fordere dich heraus, "+GetAddress_Form(NPChar)+", du unverschämter Kerl! Du wirst für deine Worte büßen! Also, ein Duell in zwei Stunden?";
			link.l1 = "Sicher, "+GetAddress_FormToNPC(NPChar)+" mutiger Kerl.";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "Dann sorge dafür, dass du zur richtigen Zeit da bist. Du hast noch Zeit, ein Requiem von unserem Priester zu bestellen.";
			link.l1 = "Ein Requiem für dich? Du bist keinen einzigen Peso wert. Wir sehen uns in der Nähe des Leuchtturms!";
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;
		
		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
		break;
		
		case "AffairOfHonor_CoatHonor_9":
			dialog.text = "Verschwinde!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Meinst du den Gouverneur? Ha! 'Gottes Urteil' ist, was der Gouverneur mir als Antwort auf meine Beschwerden sagte! Duell! Wie gefällt dir das? Ich bin nur ein ruhiger, friedliebender Pflanzer, kein Bandit oder Kämpfer\nDas wird ein Mord sein, kein Duell! Und du bist zweifellos besser in solchen Dingen als ich. Daher bitte ich dich, als mein Vertreter für das bevorstehende Duell zu handeln. Glaube mir, ich werde nicht in der Schuld bleiben.";
			link.l1 = "Wann ist das Duell?";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "Heute vor Mitternacht in der Nähe des Leuchtturms. Wirst du mir helfen?";
			link.l1 = "Gut, ich werde dir helfen. Warte auf mich in der Stadt!";
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;
		
		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05","blade_07"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;
		
		case "AffairOfHonor_GodJudgement_2":
			dialog.text = "Sag mir, was dort passiert ist? Haben wir... Entschuldigung, hast du gewonnen?";
			link.l1 = "Ich bin sicher, es wird für Sie interessant sein zu erfahren, dass es einen Hinterhalt gab. Vielleicht hat Ihr Nachbar entschieden, sich abzusichern, indem er ein paar mehr Vertreter statt nur einen einlud und alle waren erfahrene Banditen. Glücklicherweise bin ich ein erfahrener Fechter.";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "So ein Bastard! Jetzt, nehme ich an, hat unser Gouverneur keine Gründe mehr, meine Bitte um die Verhaftung des Schurken abzulehnen! Danke! Nehmen Sie Ihre Belohnung und ich muss zur Residenz gehen.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("You have received purses of doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		// Диалоги до боя -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = "Es macht Spaß ohne Bugs zu spielen, da diese Mistkerle schwer zu finden sind.";
			link.l1 = "Entspannen Sie sich, ich werde die Entwickler informieren.";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "Ach, da bist du ja. Das sind meine Freunde und Sekundanten. Sollen wir anfangen?";
					link.l1 = "Ich stehe zu Ihren Diensten!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "Alle sind versammelt. Bist du bereit?";
					link.l1 = "Ja, wir können anfangen!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "Endlich! Ich dachte schon, ich müsste diesen langen Weg umsonst gehen... Lass uns das schnell beenden, ich habe einen Becher Rum und eine heiße Dirne in der Taverne zurückgelassen!";
					link.l1 = "Ich bin sicher, dass du sie beide nicht mehr brauchen wirst!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "Jackanapes":
					dialog.text = "Also hast du dich entschieden zu kommen? Endlich! Dann lasst uns beginnen!";
					link.l1 = "Mach keine solche Eile, du könntest auf eine Klinge fallen.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "Und das sind meine Sekunden, Herr. Jetzt bereite dich auf den Tod vor!";
					link.l1 = "Nach dir.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CowardFencer":
					dialog.text = "Hier sind wir. Bereiten Sie Ihr Schwert vor, Herr!";
					link.l1 = "Gerne, möge der bessere Mann gewinnen!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CoatHonor":
					dialog.text = "Ausgezeichnet, alle sind angekommen... Lassen Sie uns beginnen, Herr!";
					link.l1 = "Lass uns tanzen!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "GodJudgement":
					dialog.text = "Und wer bist du? Sie sehen nicht aus wie ein gewöhnlicher Bürger, Kumpel...";
					link.l1 = "So? Ich habe ein Duell mit dir arrangiert?!";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1"
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "Ha! Ein Duell! Es scheint, dass du unser Kunde bist. Jungs, lasst uns ihn erstechen und einfach gehen und unsere Belohnung nehmen. Ausnehmen!";
			link.l1 = "Einen Hinterhalt? Wie erbärmlich, du wirst viel mehr als das brauchen, um mich zu Fall zu bringen...";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;
		
		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if(hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("Seconds will fight");
			}
			// В квесте "Божий суд" всегда нападают.
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("Global massacre");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = hrand(3);
				if(AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for(i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги до боя.
		
		// Диалоги после боя -->
		case "AffairOfHonor_AfterFight_1":
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = "Glaubst du wirklich, wir lassen dich einfach so unseren Freund töten und davonkommen? Zu den Waffen!";
				link.l1 = "Ich hätte das von so einem elenden Bastard erwarten sollen!";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "Kapitän, die Ehre ist wiederhergestellt, Sie haben gewonnen. Aber erlauben Sie mir, Ihnen einen guten Rat zu geben - verlassen Sie die Stadt und zeigen Sie sich hier für einige Zeit nicht ...";
				link.l1 = "Und was ist das Problem??";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "Es war alles Ehrensache und jetzt lass uns gehen und unseren Freund holen.";
				link.l1 = "Sicher, ich werde dich nicht aufhalten...";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "Das Problem ist, dass du einen Ordnungshüter unseres Kommandanten getötet hast. Er war ein schlechter Mensch und niemand wird seinen Tod bedauern... aber der Kommandant mochte ihn wirklich und er wird dir den Tod seines Freundes nie vergeben.";
			link.l1 = "Danke für den Rat, ich werde ihn sicherlich beachten. Lebewohl.";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;
		
		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				ChangeCharacterComplexReputation(PChar, "nobility", 5);
			}
		break;
		
		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = hrand(3);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for(i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги после боя.
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. He got frightened and run away on his ship" break;
		case 1: sText = "One dishonourable bastard has lost a huge sum to me in gambling and has run away on his ship" break;
		case 2: sText = "One scoundrel has loaned money from me, and when I wasn't at home he has repaid the debt with false coins to my servant. Now he is hiding somewhere on his ship" break;
		case 3: sText = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed and this bastard had run away on his ship " break;
		case 4: sText = "It was my mistake, I have hired some rogue as an accountant. He has committed a great peculation, bought a ship and run away " break;
		case 5: sText = "My ex-guard has stolen a box filled with jewels from my wife's boudoir and run away. Now I see where has he got enough coins to buy a ship " break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. But he got hired as a ship master and sailed away";
			npchar.quest.text1 = " dishonoured a woman and cowardly run away";
		break;
		case 1:
			npchar.quest.text = "One dishonourable bastard had lost a huge sum to me in gambling but he didn't pay me yet, I heard that he got hired as a cannoneer and run away";
			npchar.quest.text1 = "lost all his money in gambling and didn't want to repay the debit ";
		break;
		case 2:
			npchar.quest.text = "One scoundrel has loaned money from me, and when I wasn't at home he had repaid the debt with false coins to my servant. Now he is serving on one ship as quartermaster and hiding from me ";
			npchar.quest.text1 = "counterfeiter who has committed a crime";
		break;
		case 3:
			npchar.quest.text = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed. Luckily for him bastard got hired as a doctor on one ship and run away";
			npchar.quest.text1 = "slanderer and intrigant who has tried to dishonour one good citizen";
		break;
		case 4:
			npchar.quest.text = "It was my mistake, I have hired some rogue as an accountant. He had committed a great peculation and now he is serving on one ship as quartermaster and hiding from me";
			npchar.quest.text1 = "is blamed in peculation and misappropriation";
		break;
		case 5:
			npchar.quest.text = "My ex-guard stole a box filled with jewels from my wife's boudoir and run away. He got hired as an officer for the boarding party on one ship";
			npchar.quest.text1 = "a common thief and his place is in jail. He has stolen jewels from his own employer";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "my old pal, who was my close friend in the Old World";
			npchar.quest.text1 = "he is your old friend";
		break;
		case 1:
			npchar.quest.text = "a man, who basically was my father";
			npchar.quest.text1 = "you were like a father for him";
		break;
		case 2:
			npchar.quest.text = "my stepbrother, who had left the old world in his youth";
			npchar.quest.text1 = "you are his stepbrother";
		break;
		case 3:
			npchar.quest.text = "a man who really helped me in the Old World";
			npchar.quest.text1 = "you have helped him a lot";
		break;
		case 4:
			npchar.quest.text = "my sister's husband who was my friend in the Old World";
			npchar.quest.text1 = "you are his sister's husband";
		break;
		case 5:
			npchar.quest.text = "my friend, my brother in arms in the Old World";
			npchar.quest.text1 = "you were brothers in arms";
		break;
	}
}
