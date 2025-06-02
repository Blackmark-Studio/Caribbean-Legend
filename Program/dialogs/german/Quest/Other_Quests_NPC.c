void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Was willst du?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "Schurke! Große Überraschung für dich!";
    		link.l1 = "Was?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "Ha-ha! Keine Sklaven hier! Du bist wegen ihnen hier, oder?";
			link.l1 = "Verdammt. Und ich habe mich gefragt, warum zum Teufel so viele Soldaten auf einer Handelspinasse waren... Eine Falle!";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "Ja, Bastard, es ist eine Falle. Ich bin kein Händler, ich bin ein Militäroffizier! Obwohl du den Kampf gewonnen hast, wirst du dem Urteil nicht entkommen!";
			link.l1 = "Und warum ist das so? Ich werde dich jetzt beenden, dein Schiff versenken und niemand wird etwas wissen.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "Du liegst falsch. Deine Geschäfte mit diesem Bankier wurden aufgedeckt. Bald wird der Generalgouverneur von deinem kleinen Geschäft erfahren und du wirst dem Galgen nicht entkommen. Aber ich werde dir einen Gefallen tun, indem ich dich hier und jetzt töte!";
			link.l1 = "Versuch es, du Hund des Gouverneurs!";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = ""+GetFullName(pchar)+", im Namen des Gesetzes, bist du verhaftet! Übergebe deine Waffen und folge uns!";
			link.l1 = "Was ist los, Offizier? Auf welchen Grundlagen sollen wir uns ergeben?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "Versuche nicht, dich dumm zu stellen, Kapitän! Deine schmutzigen Geschäfte wurden aufgedeckt. Und für das Massaker, das du verübt hast, und für das Schiff von "+NationNameGenitive(sti(npchar.nation))+" dass du gesunken bist, wir werden dich hängen sehen!";
			link.l1 = "Nun, wenn du es so formulierst... Verpiss dich!";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "He, was machst du hier?!";
    		link.l1 = "Warum sind Sie so unhöflich, guter Herr? Versteckt sich diese Ratte Gontier irgendwo hier, hm?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "Nein, das ist er nicht! Raus!";
			link.l1 = "Sieht so aus, als würden Sie lügen. Ich werde eine Durchsuchung des Hauses durchführen und ich werde sehen...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "Verdammt! Francois! Lauf! Jungs, helft mir!";
			link.l1 = "Mist!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "Oh! Vergewaltige mich nicht!";
    		link.l1 = "Was zum...? Wo ist Francois Gontier? Antworte mir, du dreckige Schlampe, oder du wirst enden wie diese Gefährten von dir!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "Nein, nein, ich werde dir alles erzählen! Er ist aus dem Fenster gesprungen und zu seinem Schiff geflüchtet.";
    		link.l1 = "Welches Schiff? Ich weiß, dass sein Schiff nicht im Hafen ist. Lüge mich nicht an, Mädchen, oder es wird schlimmer...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "Ich lüge nicht, ich schwöre! Er sagte, er sei auf einer kleinen Insel gelandet und mit einem Langboot hierher gekommen... Er muss dort sein! Verletz mich nicht!";
    		link.l1 = "Also gut, es scheint, dass du die Wahrheit sagst. Bleib hier und halt den Mund. Und versuche in der Zukunft auf eine klügere Weise Freunde zu finden. Aber, weißt du, ich sehe es in deinen Augen und sie sagen mir, dass du keinen Verstand hast.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "Verschont uns! Gnade! Wir ergeben uns!";
    		link.l1 = "Oh, ist das so? Geh jetzt zum Frachtraum! Ich werde jeden erschießen, der versucht, dumm zu spielen!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "Nun, nun... Was haben wir denn hier? Weißt du nicht, dass der Handel mit Waren zwischen unbefugten Personen in unserer Kolonie verboten ist?";
			link.l1 = "Ist das so, Offizier? Um ehrlich zu sein, höre ich davon zum ersten Mal. Dieses Dekret wurde vor nicht allzu langer Zeit verabschiedet, habe ich recht?";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "Was, Handel "+GetGoodsNameAlt(iCGood)+"? Ich sehe nichts "+GetGoodsNameAlt(iCGood)+" um dich herum, Offizier. Ich sehe nur diese glänzenden Münzen... Und er sieht dasselbe. Warum werfen Sie und Ihre Soldaten nicht auch einen Blick auf unsere Münzen?";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "Du wusstest es nicht, hm? Hmm... es sieht so aus, als ob du nicht lügst. Aber trotzdem hast du das Gesetz verletzt. Ich werde dich nicht verhaften, aber ich werde dich dazu bringen, eine Strafe zu zahlen. Und die Ladung... wir werden darüber mit dem zweiten Teilnehmer des Geschäfts sprechen.";
				link.l1 = "Und wie hoch ist diese Strafe?";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "Spiel nicht den Dummen, Kapitän! Jeder weiß das schon lange, darf ich hinzufügen. Ich verhafte euch beide wegen Schmuggels und eure Ladung wird konfisziert.";
				link.l1 = "Ich mag keine Kajüten, Offizier. Ich mag das offene Meer... und ich werde jetzt dorthin segeln. Aber es scheint, dass ich das nur über deine tote Leiche tun muss.";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Ich habe keine Wahl, ich muss mich ergeben. Aber ich hatte wirklich keine Ahnung!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "Jetzt redest du... Lass deine Münzen sehen... Ich glaube, ich habe eine ziemlich bestimmte Zahl gehört - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". Da wir jetzt drei Teilnehmer haben, würde ich gerne "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". Das kommt von dir und das Gleiche von deinem Freund.";
				link.l1 = "Sicher, Offizier. Hier sind meine glänzenden Münzen, oder, es tut mir leid, Ihre glänzenden Münzen - Sie haben sie zufällig am Strand fallen lassen... Und es gibt keine "+GetGoodsNameAlt(iCGood)+" hier, ha-ha, wie ich dir gesagt habe.";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "Holla! Du bist zu gierig, Offizier. Hat deine Mutter dir nicht beigebracht, dass Gier nicht gut ist? Ich nehme an, es wäre billiger für mich, dich mit meiner Klinge zu erledigen.";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "Scherzt ihr, Kapitän? Wollt ihr mir ein Bestechungsgeld anbieten? Ihr seid unter Arrest! Ergreift ihn!";
				link.l1 = "Nun, wenn du mein Geld nicht anschauen willst, dann schau dir mein Schwert an!";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Ich habe keine andere Wahl, als mich zu ergeben. Aber ich hatte wirklich keine Ahnung!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "Ja, es scheint, als ob Sie richtig liegen... Nichts von Interesse hier, außer einigen Herren und meinen glänzenden Münzen. Sie können gehen, Kapitän und wir werden ein Gespräch mit Ihrem Partner führen.";
			link.l1 = "Auf Wiedersehen, Offizier. Verletz ihn nicht.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = ""+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". Danke meiner guten Laune.";
			link.l1 = "Danke Offizier. Ich hatte wirklich keine Ahnung... Hier, ich bin bereit, meine Strafe zu zahlen.";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "Ich nehme an, dass Sie auch nicht so ehrlich sind, Offizier. Ihre Strafe ist zu groß. Ich vermute, dass ich dieser Kolonie helfen werde, indem ich sie vor Ihrer Existenz rette.";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "Gut. Du darfst jetzt gehen. Und ich rate dir, die örtlichen Gesetze zu studieren, um in Zukunft Situationen wie diese zu vermeiden. Geh jetzt, wir müssen uns mit dem zweiten Teilnehmer dieses Handels befassen, er wusste sicherlich alles.";
			link.l1 = "Nun, in diesem Fall, einen schönen Tag noch, Offizier.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "Der Kommandant wird sich um dich kümmern. Folge mir!";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "Guten Tag. Wünschen Sie etwas?";
			link.l1 = "Ich tue, Kumpel. Ich nehme an, dass du mein Kerl bist. Du warst es, der gestohlen hat "+pchar.GenQuest.Device.Shipyarder.Type+"  vom örtlichen Schiffswerft? Alles führt zu dir, also kein Streit.";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "Ich flehe Sie an, mein Herr! Ja, ich habe dieses seltsame Ding aus der Werft gestohlen. Aber ich konnte es nicht verkaufen, niemand braucht so ein Ding. Also habe ich es losgeworden. Verschonen Sie mich, guter Herr, tadeln Sie meinen Hunger, nicht mich... Ich würde sonst nie wagen, etwas zu stehlen!";
					link.l1 = "Das ist ein Problem... Und ich brauche dich auch nicht. Ich muss das finden "+pchar.GenQuest.Device.Shipyarder.Type+". Sag mir, wo hast du es weggeschmissen?";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "Ich bitte Sie, mein Herr! Ja, ich habe dieses seltsame Ding aus der Werft gestohlen. Aber ich konnte es nicht verkaufen, niemand braucht so einen Gegenstand. Ich werde es Ihnen geben. Hier, nehmen Sie es, tun Sie mir bitte keinen Schaden an und rufen Sie nicht die Soldaten!";
					link.l1 = "Gut, du darfst leben, du Schurke. Ich brauche deine Haut nicht, ich brauche dieses Instrument. Gib es mir sofort und verschwinde!";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "Was meinst du? Was ist "+pchar.GenQuest.Device.Shipyarder.Type+"? Ich verstehe es nicht!";
					link.l1 = "Du wirst es bekommen, wenn ich dich oder deine Leiche durchsuche! Gib es mir jetzt!";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "Oh... Was ist das "+pchar.GenQuest.Device.Shipyarder.Type+"? Ich... und was ist das?";
					link.l1 = "Lass es nicht darauf ankommen, dich dumm zu stellen oder wegzulaufen, ich werde dich sowieso erwischen. Lass mich nur mal in deine Taschen schauen...";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "Gleich hinter den Stadttoren, nicht weit von den Dschungeln. Ich bitte Sie, guter Herr! Wenn Sie dieses Ding wirklich brauchen, können Sie es selbst abholen. Es muss noch dort sein, da bin ich sicher.";
			link.l1 = "Ich sollte dich zwingen, es zu finden und es zu mir zu bringen, aber ich fürchte, dass ich mehr Zeit damit verbringen würde, dich zu finden als das "+pchar.GenQuest.Device.Shipyarder.Type+". Ich werde es selbst machen. Aber ich werde dich finden, wenn du mich angelogen hast!";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "Hier, nimm es. Danke, freundlicher Herr!";
			link.l1 = "Nun, es muss das sein, wonach ich gesucht habe... ha! Du kannst jetzt gehen. Beweg dich. Und sei das nächste Mal vorsichtig.";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "Hör zu, sprichst du von diesem Instrument? Es gehört mir und ich habe es nicht gestohlen! Und ich werde es dir nicht kostenlos geben. Wenn du es haben willst, bezahle mich "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))+".";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "Hm... Gut. Ich werde dich bezahlen. Hier sind deine Münzen und gib mir das Instrument!";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "Ach wirklich? Hast du wirklich gedacht, dass ich dir vertraue, elender Dieb? Gib das "+pchar.GenQuest.Device.Shipyarder.Type+" Sprich jetzt mit mir oder ich rufe die Wachen, damit wir gemeinsam zur Werft gehen und entscheiden können, wem dieses Instrument wirklich gehört.";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "Bist du dumm oder was? Hör zu, Mistkerl, du hast zwei Möglichkeiten: Entweder du gibst mir das "+pchar.GenQuest.Device.Shipyarder.Type+" oder ich steche dich ab und nehme das Instrument von deinem toten Körper!";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "Schöner Deal, Kapitän! Ich nehme an, dass wir alle unseren Gewinn bekommen, he-he... nimm es.";
			link.l1 = "Weniger reden, Dieb! Denke nicht, dass du mich getäuscht hast, ich möchte es nur friedlich und mit weniger Problemen machen. Diese Münzen werden dir sowieso nichts Gutes tun. Verschwinde!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Nein! Rufen Sie nicht die Wachen! Ich...Ich gebe Ihnen dieses verdammte Instrument. Hier, nehmen Sie es!";
				link.l1 = "Das ist ja viel besser jetzt! Verschwinde jetzt! Oder du wirst am Galgen enden, es ist nur eine Frage der Zeit.";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "Was für Wachen, Käpt'n? Hier sind nur du und ich. Du streitest zu viel, also muss ich dich beruhigen... mit meiner Klinge.";
				link.l1 = "Du wagst es, mich zu bedrohen, Abschaum?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Ach! Hilf mir! Mörder!";
				link.l1 = "Halt, du Hund!";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "Nun, mal sehen, wer wen erstechen wird, Kapitän!";
				link.l1 = "Du wagst es, mich zu bedrohen, Abschaum?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "Suchen? Bitte, guter Herr!";
			link.l1 = "Nun hör zu, entweder du gibst mir friedlich das Ding, das du gerade aus der Werft gestohlen hast, oder ich bringe dich zum Kommandantenbüro. Du wirst mir dieses Ding sowieso geben, aber zuerst werden deine Fersen mit einem glühenden Eisen verbrannt. Vielleicht hängen sie dich danach sogar auf. Die Entscheidung liegt bei dir.";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "Gib mir sofort zurück, was du gestohlen hast, du Mistkerl, oder ich werde dich genau dort beenden, wo du stehst!";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезёт
			{
				dialog.text = "Nun, du musst mich erst fangen, wenn du mich ins Kommandantenbüro bringen willst ...";
				link.l1 = "Halt, du Hund!";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "Nein, bring mich nicht ins Kommandantenbüro! Ich werde es selbst geben! Hier, nimm es, du suchst sicherlich nach diesem Ding. Niemand würde es sowieso kaufen...";
				link.l1 = "Eh, ich nehme an, ich könnte dich trotzdem zum Fort bringen... Gut, gib mir das Werkzeug und verschwinde!";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "Autsch! Tu mir nicht weh, ich gebe dir alles, was ich habe! Hier, nimm es!";
			link.l1 = "Jetzt redest du! Verschwinde, ich werde dich dem Kommandanten ausliefern, wenn ich dich jemals wieder in dieser Stadt sehe. Lebewohl!";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "Halt, Kumpel! Wir brauchen das Ding, das du bei dir trägst. Gib es uns und dann geh deinen Weg.";
			link.l1 = "Wovon redest du?";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "Diese Straßenleute sind heutzutage zu unverschämt... Macht euch bereit, Schurken!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "Täusche nicht vor, ein Narr zu sein! Gib uns das Paket und du wirst leben. Andernfalls... wir werden es von deiner Leiche nehmen!";
			link.l1 = "Die Chancen stehen zu euren Gunsten... nehmt es, ihr Bastarde, ich habe keine Wahl.";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "Nun, du kannst es versuchen!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "Achtet auf eure Zunge, Freund... Es ist klug von euch, euer Glück nicht herauszufordern. Das Ende wäre das Gleiche gewesen, ha-ha! Ihr werdet noch eine Weile leben... Bis dann.";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "Warte, "+GetAddress_Form(NPChar)+", hetz nicht so. Ich habe ein Geschäft für dich.";
			link.l1 = "Welches Geschäft? Ich kenne dich nicht.";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "Ich kenne dich, Kapitän. Jetzt direkt zum Geschäft. Du hast gerade erhalten "+pchar.questTemp.WPU.Current.Add+" in "+XI_ConvertString("Kolonie"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". Versuche nicht, es zu leugnen, wir wissen das sicher - schließlich haben wir einige Tage nach diesem Dokument gesucht.";
			link.l1 = "Jetzt verstehe ich. Na und?";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "Gib mir das Paket und unser kurzes Treffen endet. Versuch nicht, den Helden zu spielen, Kapitän, wir beabsichtigen, diese Papiere zu bekommen, und wir sind bereit, gegen die Stadtwache zu kämpfen, wenn wir müssen\nWie du vielleicht verstehst, wirst du der Erste sein, der stirbt, wenn das Gefecht beginnt. Also gib uns die Dokumente und wir werden uns als Freunde trennen.";
			link.l1 = "Die Chancen stehen zu euren Gunsten... nehmt es, ihr Bastarde, ich habe keine andere Wahl.";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "Versuchst du, mir Angst zu machen? Ich habe kleine Fische gesehen, die mehr Widerstand leisten als du es jemals könntest! Zisch ab.";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "Es freut mich, dass Sie vernünftig waren, Kapitän. Sie haben sich in große Gefahr gebracht, indem Sie diesen Job angenommen haben. Jetzt werde ich mich verabschieden, wenn es Ihnen nichts ausmacht.";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "Es war deine Entscheidung...";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap();//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "Warte, "+GetAddress_Form(NPChar)+", renn nicht so hastig. Ich habe ein Geschäft für dich.";
			link.l1 = "Welches Geschäft? Sprich schnell, ich habe es eilig.";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "Ich weiß, wer du bist. Und ich weiß auch, dass du gerade eine "+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Kolonie"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". Diese Papiere sind der Grund, warum ich so begierig darauf bin, mit Ihnen zu sprechen.";
			link.l1 = "Und ich möchte diese Angelegenheit nicht mit Leuten besprechen, die ich nicht kenne. Willst du diese Papiere bekommen? Gib mir einfach einen Grund...";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "Genug, Kapitän! Sehe ich aus wie ein Räuber? Ich bin ein Geschäftsmann und vertrete die Interessen von "+NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation))+". Ich möchte Ihnen ein sehr lukratives Geschäft anbieten, aber nicht hier. Lassen Sie uns zum Tavernenzimmer gehen und diese Angelegenheit besprechen. Es wird nicht viel Ihrer Zeit in Anspruch nehmen.";
			link.l1 = "Das ist viel zu verdächtig... Ich werde keine Geschäfte mit Ihnen machen, Herr! Verschwinden Sie!";
			link.l1.go = "PostAgent_getout";
			link.l2 = "Hm.. Lass uns mal sehen, was du mir anbieten kannst. Aber versuch erst gar nicht, mich anzugreifen, das wird nicht gut enden. Los geht's, ich folge dir.";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "Du bist ein sturer und dummer Mann, Kapitän! Ich habe dir die Chance geboten, leichtes Geld zu verdienen. Und du... du wirst es bereuen.";
			link.l1 = "Verpiss dich!";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "Prächtig! Folge mir.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "Jetzt können wir frei sprechen.";
			link.l1 = "Und was ist Ihr Vorschlag?";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "Wie ich sagte, es geht alles um die Papiere, die du im Hafenbüro erhalten hast. Alles, was ich brauche, ist eine Kopie von ihnen, das ist alles\nDu behältst das Original, also werden sie dich für die Arbeit bezahlen. Niemand wird jemals erfahren, was passiert ist, außerdem werde ich dich gut bezahlen.";
			link.l1 = "Entschuldigung... Aber das Paket ist versiegelt. Sie können keine Kopien anfertigen, ohne das Siegel zu brechen!";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "Ich habe diese Frage erwartet. Ich muss das Siegel brechen, aber keine Sorge, ich kann es wiederherstellen. Ich habe natürlich ein Duplikat-Klischee und Siegelwachs. Niemand wird bemerken, dass das Paket geöffnet wurde.";
			link.l1 = "Haben Sie ein falsches Klischee von der Hafenverwaltung von "+XI_ConvertString("Kolonie"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "Warum fragen Sie, Kapitän? Ja, ich habe eins. Glauben Sie wirklich, dass ich nur herumspiele? Ich biete Ihnen an "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" für eine Möglichkeit, diese Papiere zu sehen. Also, wirst du mir endlich das Paket geben? Bitte.";
			link.l1 = "Nimm es, aber ich brauche sie zurück und versiegelt!";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "Weißt du, ich werde nicht. Es gefällt mir nicht.";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "Mach dir keine Sorgen. Ich bin ein Profi. Setz dich und ruh dich aus. Es wird ungefähr eine Stunde dauern.";
			link.l1 = "Gut.";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "Hm... Das habe ich nicht kommen sehen. Du bist zu stur, Kapitän, also muss ich dich genau dort töten, wo du stehst und das Paket kostenlos nehmen. Beten Sie, denn ich arbeite mit meiner Klinge genauso gut wie ich mit falschen Klischees arbeite.";
			link.l1 = "Du solltest beten, Spion!";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "Fertig. Wie gesagt, es wurde auf genaueste Weise erledigt. Nimm das Paket und das Versprochene "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+". Und ich muss gehen. Viel Glück, Kapitän, ich freue mich, dass wir einen Handel abgeschlossen haben.";
			link.l1 = "Auf Wiedersehen...";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "Grüße! Oh, ich bin so froh, dich zu sehen!";
			link.l1 = "Guten Tag. Hm, sag mal, bist du nicht der Kapitän des "+pchar.questTemp.WPU.Escort.ShipName+"?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "Ach! Und wie haben Sie von dem erfahren "+pchar.questTemp.WPU.Escort.ShipName+"? Ja, ich bin ihr Kapitän. Oder ich war es... Das Schiff wurde nicht weit von hier versenkt.";
			link.l1 = "Ach, dann habe ich dich gefunden... Lass mich mich vorstellen - "+GetFullName(pchar)+". Ich bin hier auf Bitte des Hafenmeisters von "+XI_ConvertString("Kolonie"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Er hat mir kurz von den Problemen Ihrer Karawane erzählt und mich losgeschickt, um Ihr Schiff zu finden.";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "Also bist du der Kapitän der Rettungspartei?";
			link.l1 = "Etwas in der Art. Meine Aufgabe war es, dein Schiff zu finden oder Beweise dafür zu finden, dass es gesunken ist oder nicht in der Lage ist zu segeln. Leider habe ich das Schiff nicht gefunden, aber ihr Kapitän ist am Leben, das ist sicherlich eine gute Sache...";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "Oh, es tut mir leid, ich habe vergessen, mich vorzustellen. Ich bin "+GetFullName(npchar)+". Wissen Sie schon, wie wir hier gelandet sind? Der Sturm machte unser Schiff unkontrollierbar\nEin paar Tage später traf sie die Riffe nicht weit von dieser Bucht und der Sturm zerstörte sie in Minuten. Nur ein paar Dutzend meiner Crew überlebten. Der Rest liegt auf dem Grund. Wir beten jeden Tag für ihre Seelen...";
			link.l1 = "Nehmen Sie mein Beileid, Kapitän "+GetFullName(npchar)+". Es tut mir so leid.";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "Danke... Überlebende haben ein Lager am Ufer aufgeschlagen, in der Hoffnung auf Hilfe. Sie kommen gerade rechtzeitig, Kapitän! Die kriegerischen Ureinwohner kennen unsere Anwesenheit, wir haben keine Chance gegen Hunderte von ihnen, wenn sie uns angreifen\nEs gibt auch ein Piratenschiff, das in dieser Gegend kreuzt, es sieht so aus, als würden sie uns suchen. Haben Sie diesen Piraten getroffen, Kapitän?";
			link.l1 = "Nein, das habe ich nicht.";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "Lobet den Herrn dafür. Er ist einer von denen, die uns vor diesem verdammt Sturm angegriffen haben. Wie eine Hyäne, ist er begierig, ein verwundetes Gebet zu beenden, also ist er hierher gekommen, auf diese Insel.";
			link.l1 = "Ich verstehe. Jetzt ist es an der Zeit zu entscheiden, was wir als nächstes tun.";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "Entscheiden was, Kapitän? Nehmt uns an Bord und lasst uns von diesem verfluchten Ort wegkommen.";
			link.l1 = "Absolut. Ich habe es nicht geschafft, das Schiff zu retten, zumindest werde ich ihre Mannschaft retten. Baut euer Lager ab und ich werde befehlen, hier Langboote zu schicken. Willkommen an Bord!";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "Dankbarkeit, Kapitän! Es wird nicht lange dauern. Warte... Was zum Teufel? Argh! Diese rothäutigen Teufel kommen wieder auf uns zu! Alarm! Zu den Waffen!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "Fuh, wir haben es geschafft... Siehst du, Kapitän, ich habe dir gesagt, dass diese Bucht die Hölle selbst ist. Es ist bereits der dritte Indianerangriff! Wir müssen diesen Ort so schnell wie möglich verlassen, wir überleben einen weiteren Angriff nicht.";
			link.l1 = "Ja, du hast recht. Sammle jede lebende Seele und komm an Bord meines Schiffes! Ich werde sofort anordnen, uns Ruderboote zu schicken!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "Hic... Was willst du von mir? Verschwinde, ich habe keine Lust, mit dir zu reden.";
			link.l1 = "Bist du "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Ja, das bin ich. Und was ist dein Anliegen?";
			link.l1 = "Es ist ziemlich einfach. Es gibt jemanden in dieser Stadt, der genug von deinen Tricks hat. Diese Person hat die Nase voll von ihnen. Jetzt schaue ich dich an und verstehe warum. Zeig dich nie wieder im örtlichen Bordell oder du wirst Ärger bekommen. Verstanden?";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "Argh! Du... wagst es, mich zu bedrohen, du Tölpel? Ich werde dich auf meine Klinge spießen und dich wie ein Huhn am Spieß braten!";
						link.l1 = "Bereite dich vor, du Mistkerl!";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "Was? Welche Tricks? Es gab keine Tricks. Ich habe mich betrunken und bin ein paar Mal im Bordell auf den Putz gehauen. Niemand ist perfekt... In Ordnung, in Ordnung, in Ordnung... Ich werde ihre Dienste nie wieder in Anspruch nehmen. Zufrieden jetzt? Du hast mein Wort.";
						link.l1 = "Ich hoffe, dass das Wort der Ehre für dich etwas bedeutet und du dir über die Folgen im Falle eines Bruches bewusst bist. Behalte das im Kopf. Lebe wohl jetzt.";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "Sie sind ein solch unverschämter Mann, Herr! Ich schwöre, dass ich Sie vor Sonnenuntergang Ihre Worte bereuen lassen werde. Ich fordere Sie heraus! Ich vermute, dass wir besser im Privaten kämpfen, irgendwo in Ruhe. Der Dschungel wird es tun, treffen Sie mich dort in zwei Stunden!";
					link.l1 = "Eine großartige Idee! Zumindest wäre es kein Problem, deine Leiche zu verstecken.";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "Was? Welche Tricks? Es gab keine Tricks. Ich habe mich betrunken und bin ein paar Mal im Bordell auf den Putz gehauen. Niemand ist perfekt... In Ordnung, in Ordnung, in Ordnung... Ich werde nie wieder ihre Dienste in Anspruch nehmen. Zufrieden jetzt? Du hast mein Wort.";
					link.l1 = "Ich hoffe, dass das Wort der Ehre für dich etwas bedeutet und du dir über die Folgen im Falle eines Bruchs im Klaren bist. Behalte das im Hinterkopf. Lebe wohl jetzt.";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "Warte! Halt! Ich ergebe mich! Verschone mich!";
			link.l1 = "Und so sprichst du jetzt!";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "Ich flehe Sie an, bitte, verschonen Sie mich! Ich werde tun, was Sie verlangen! Ich werde nie wieder in diesem Bordell auftauchen!";
			link.l1 = "Diese Pose passt nur zu einem Abschaum wie dir. Ich hoffe, dass dies eine Lektion für dich für den Rest deines Lebens sein wird. Und benimm dich ordentlich in dieser Stadt.";
			link.l1.go = "Badboy_exit";
			link.l2 = "Sicher, das wirst du nicht. Deine Trickserei wird hier und jetzt beendet.";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "Zeit, zur Hölle zu gehen, Wichser! Bet für dich selbst, aber mach es schnell, ich habe nicht den ganzen verdammten Tag...";
			link.l1 = "Weniger reden, mehr kämpfen, Abschaum!";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "Und da ist er, dieser freche Bastard! Zeigen wir ihm, wer hier das Sagen hat, Jungs!";
			link.l1 = "Ach, du bist so ein Degenerierter! Aber ich habe dich gewarnt. Du und deine Affen werden in einer Minute direkt zur Hölle geschickt!";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "Grüße. Was willst du?";
			link.l1 = "Bist du nicht "+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Du wirst mir nicht glauben, ha-ha. Ich will deinen Kopf.";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "Hm... Nein... Es ist nichts. Es sieht so aus, als hätte ich mich geirrt. Entschuldigen Sie die Störung.";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "Was für ein dummer Witz, Herr! Erklären Sie sich oder ich werde...";
			link.l1 = "Und was wirst du tun, elendes Hering? Du hast einem guten Mann übel mitgespielt und er ist wirklich verärgert. Also bete jetzt und mach es schnell, denn ich habe es eilig.";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "Was... was machen Sie, Herr! Hilfe! Jemand hilft! Mörder!";
			link.l1 = "Und ich dachte, du würdest deine letzten Sekunden mit Beten verbringen, zumindest hättest du eine Chance gehabt, den Himmel zu erreichen...";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "Du schon wieder? Warum sagst du mir nicht, was du willst?";
			link.l1 = "Es ist nichts.";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "Ach?! Was? Was zur Hölle machst du hier, verdammt? Wer hat dich hereingelassen?";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "Die Liga braucht dein Leben, Kapitän...";
			link.l1 = "Was? Verdammt!";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar,"Hört zu, ich bin ein Bürger dieser Stadt und ich bitte euch, euer Schwert zu scheiden.","Hör zu, ich bin Bürger dieser Stadt und ich bitte dich, deine Klinge zu ummanteln.");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Sicher...");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, "+GetSexPhrase("Kumpel","Mädchen")+", während ich mit einer Waffe laufe. Ich kann nervös werden...","Ich mag es nicht, wenn es gibt "+GetSexPhrase("Männer, die","Leute, die")+" gehen vor mir mit gezogener Waffe. Es macht mir Angst...");
				link.l1 = LinkRandPhrase("Ich habe es.","Es ist in Ordnung.","Mach dir keine Sorgen...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
