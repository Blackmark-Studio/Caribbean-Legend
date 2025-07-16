// Жак Барбазон в Ле Франсуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            dialog.text = NPCStringReactionRepeat("Hast du mir etwas zu sagen? Nein? Dann verschwinde von hier!","Ich glaube, ich habe mich klar ausgedrückt, hör auf, mich zu nerven.","Obwohl ich mich klar ausgedrückt habe, nervst du mich weiterhin!","Also gut, ich habe genug von dieser Unhöflichkeit.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ich gehe schon.","Sicher, Jacques...","Entschuldigung, Jacques...","Autsch...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Bist du verrückt? Wolltest du den Metzger spielen? Alle Piraten sind wütend auf dich, Junge, du solltest besser diesen Ort verlassen...","Es scheint, dass du verrückt geworden bist, Junge. Wolltest du deine Hände ein bisschen strecken? Nichts für ungut, aber du hast hier nichts zu tun. Verschwinde!");
				link.l1 = RandPhraseSimple("Hör zu, ich will die Situation klären...","Hilf mir, dieses Problem zu lösen...");
				link.l1.go = "pirate_town";
				break;
			}
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "Ich muss mit dir sprechen, Jacques... unter vier Augen.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "Ich komme aus Saint Martin, Jacques...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "Und wann wirst du aufhören zu bellen und anfangen wie ein Mann zu sprechen, Jacques? Hast mich nicht erwartet?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Ich bin hier wegen Ihres Gefangenen.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Hallo, Jacques, ich bin wegen deiner Mission hier.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Ich bin hier wegen Ihres Gefangenen.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Ich habe gehört, dass Sie im Geschäft mit Gefangenen tätig sind...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"! Was brauchst du diesmal?","Haben Sie vergessen, mir etwas zu erzählen? Ich höre zu.","Wie lange wird das noch dauern... Wenn du nichts zu tun hast, dann belästige nicht andere Leute!","Du hast mich gebeten, höflich zu sein. Aber ich verlange das Gleiche von dir!","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Es ist nichts. Nur ein Besuch.","Nichts...","Gut...","Du hast recht. Es tut mir leid.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Bist du verrückt? Wolltest du den Metzger spielen? Alle Piraten sind wütend auf dich, Junge, du solltest besser diesen Ort verlassen...","Es scheint, dass du verrückt geworden bist, Junge. Wolltest du deine Hände ein bisschen strecken? Nichts für ungut, aber du hast hier nichts zu tun. Verschwinde!");
				link.l1 = RandPhraseSimple("Hör zu, ich will die Situation klären...","Hilf mir, dieses Problem zu lösen...");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Ich bin wegen Ihres Gefangenen hier.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Hallo, Jacques, es geht um deine Mission.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "Ich bin hier wegen Ihres Gefangenen.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Ich habe gehört, dass du dich mit Geschäften im Zusammenhang mit Gefangenen beschäftigst...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "Weißt du, dass es riskant ist, mich zu belästigen? Gut, ich höre dir zu.";
			link.l1 = "Ich habe eine Schuld. Eine große. Die Zeit zu zahlen kommt bald und ich habe keine Münzen. Gütige Leute haben geflüstert, dass du ein Talent für das Schmieden von Plänen hast und immer weißt, wo man einen großen Jackpot schnappen kann...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "Hör zu, Junge! Ich bin Jacques der Gütige nur für die, die mir treu sind. Für die anderen bin ich Barbazon und manchmal sogar der Teufel selbst. Wie könnte ich wissen, dass ich dir vertrauen kann?";
			link.l1 = "Versuch es. Ich schwöre, du wirst es nicht bereuen!";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Hm... Ich nehme an, du weißt, was Jacques der Gütige mit Leuten macht, die ihn betrügen, nicht wahr? Wie auch immer, ich werde dich nicht mit schrecklichen Details verwirren. Ich habe eine kleine Mission. Wenn du Erfolg hast, sind all deine finanziellen Probleme verschwunden.";
			link.l1 = "Zweifle nicht an mir, ich war in vielen Kämpfen und...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Halt die Klappe und hör mir zu! Vor ein paar Wochen hat eine niederländische Patrouille einen meiner Angestellten nicht weit von Saint Martin gefangen. Er lieferte mir niederländische Seide. Sie ist sehr selten, die Niederländer bringen hier nur kleine Mengen für die Bedürfnisse der Firmenmarine.\nSo, ich habe es geschafft, sechs Ballen Seide zu beißen und Simon Morel sollte sie mir auf seiner Brigantine 'Salt Dog' bringen, aber er stieß zufällig auf eine niederländische Patrouille. Oder nicht zufällig. Das sagte Morels Navigator, er erzählte mir, er sei der einzige, der den Kampf überlebt hat.\nEr gab mir auch Morels Logbuch, das die Geschichte bestätigt. Laut Logbuch hat Morel die Seide während eines Fluchtversuchs weggeworfen. Ist das nicht merkwürdig? Die Seide ist leicht. Sie hätten ihre Kanonen werfen sollen, sie hatten sowieso keine Chance gegen die Patrouille.";
			link.l1 = "Etwas ist hier wirklich falsch.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "Alles ist möglich. Viele tapfere Männer arbeiten für mich und noch weniger kluge. Nichts gegen dich, heh. Du musst den Ort überprüfen, an dem Morel die Ladung losgeworden ist. Laut Kapitänstagebuch liegt es bei 21 Grad 10' Nord und 61 Grad 30' West. \nDie Holländer wickeln die Seide um Korkstäbe, so dass die Ballen noch über dem Wasser bleiben sollten. Es müssen sechs Ballen sein. Setze sofort die Segel, die Zeit ist entscheidend.";
			link.l1 = "Ich bin auf dem Weg!";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "Großartig! Hast du meine Seide gefunden?";
			link.l1 = "Ja, sechs von ihnen, wie du gesagt hast.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "Ja. Aber es waren mehr als du gesagt hast, neun von ihnen, nicht sechs. Ich habe sie alle hierher gebracht, es ist deine Aufgabe herauszufinden, wie das passieren konnte.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "Falsche Antwort. Es hätten neun Ballen sein müssen. Und wenn du sechs von ihnen gefunden hast, dann musst du auch den Rest gefunden haben. Also bist du entweder eine Ratte oder einfach nur ein fauler Idiot. Du schuldest mir drei Ballen Seide und drei weitere als... 'moralische Entschädigung' dafür, dass du versucht hast, mich zu betrügen.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "So ein Schlaumeier! Das werde ich mir merken. Hier ist deine Seide und vergessen wir meinen Fehler.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "Mir wurde gesagt, dass es sechs Ballen gab, kein einziger Ball mehr. Ich habe dir alles gegeben, was ich gefunden habe und ich scheiß auf deine Gedanken. Ich habe keine Seide mehr.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "Gut. Ich hoffe, dass es nicht wieder vorkommt, denn ich möchte dir eine wichtige Aufgabe geben. Wie viel Geld möchtest du verdienen?";
			link.l1 = "Geld ist immer willkommen, für jetzt wären fünfzigtausend Pesos in Ordnung.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "Oh, so sprichst du jetzt! Das wirst du nicht ungestraft lassen. Ich habe dich gewarnt - versuche verdammt noch mal nicht, mich zu betrügen! Wachen! Es gibt eine verdammte Ratte in der Residenz!";
			link.l1 = "Scheiße!";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "Gute Arbeit. Ich habe dich auf Gier geprüft und du hast meinen Test bestanden. Es müssen neun Ballen gewesen sein. Einer von ihnen gehört dir. Jetzt können wir ernsthaft reden. Wie viel Geld brauchst du?";
			link.l1 = "Geld ist immer willkommen, für jetzt wären fünfzigtausend Pesos in Ordnung.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "Du hast die Möglichkeit, noch mehr zu verdienen. Ein ernsthafter Mann hat mich gebeten, einen zuverlässigen Kerl wie dich für eine heikle und gefährliche Mission zu finden. Dieser Mann ist sehr reich und er wird dich entsprechend belohnen, wenn du ihn nicht im Stich lässt.";
			link.l1 = "Ich bin bereit.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "Gut. Hör jetzt zu. Du musst seinen Agenten finden, der 'Schurke' heißt. Er ist der Kapitän der Polacre 'Marlin', das ist alles, was ich über ihn weiß. Du wirst ihn in Kapsterville finden. Das Passwort lautet 'die Jagd hat begonnen'. Er wird dir sagen, was zu tun ist. Du schuldest mir nichts. Ich möchte dir nur helfen. Wenn du Glück hast, werden wir uns wiedersehen.";
			link.l1 = "Danke für deine Hilfe. Ich bin auf dem Weg!";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "Was?! Ich werde dir deine...";
			link.l1 = "Du wirst nicht, Barbazon. Lasst uns unsere Karten sehen! Ich arbeite für Jan Svenson. Ich habe deine Verschwörung mit Jackman aufgedeckt. Ich weiß alles, was du geplant hast und welche Rolle du auch hattest. Jackman und sein Bruder sind tot, der erste hat Blaze Sharp getötet und das hat sein Schicksal besiegelt, der zweite war leider nicht gesprächig genug ...";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "Verdammt! Tyrex wird mir das nie verzeihen, aber ich bin immer noch..";
			link.l1 = "Mach nichts Dummes, Jacques. Ich wusste, dass es kein leichtes Gespräch werden würde, also habe ich mich vorbereitet. Schau aus dem Fenster... deine Hütte ist von meinen Musketieren umgeben. Meine Leute sind überall in deinem Dorf und eine Schlagkraftgruppe steht direkt vor den Toren. Willst du ein Gemetzel beginnen? Einfach genug!";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "Verdammt noch mal! Was willst du?";
			link.l1 = "Du wirst es mir nicht glauben, Barbazon, aber alles, was ich will, ist... Frieden! Ich will Frieden. Deshalb werde ich Tyrex nichts von deiner Beteiligung an dieser Verschwörung gegen ihn erzählen. Aber nur, wenn du tust, was ich will...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "Was willst du von mir? Geld? Wie viel?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Oh, nein, überlass das deinen Agenten ohne Hirn. Ich brauche etwas anderes. Ich brauche deine Stimme für Steven Dodson.";
			}
			else
			{
				link.l1 = "Oh, nein, überlasse das deinen Agenten ohne Gehirn. Ich brauche etwas Anderes. Ich brauche deine Stimme für Marcus Tyrex.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "And Steven Dodson is on our side.";
			else sTemp = "";
			dialog.text = "Ernsthaft? Lass mich nachdenken... und was, wenn ich Nein sage?";
			link.l1 = "Dann wirst du alleine stehen. Absolut alleine. Svenson, Tyrex und Hawk werden gegen dich vorgehen."+sTemp+"Ich werde ihnen nur den Brief des Schurken zeigen, Jackmans Bruder, und auch meinem Wort wird vertraut. Wie lange glaubst du, wirst du danach noch auf deinem gemütlichen Platz sitzen?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "Hawk? Er lebt noch?!";
			link.l1 = "Er ist es. Ich habe ihn aus der Falle gerettet, die Jackman gestellt hat. Also wird der engste Freund von Jacob sein Blutfeind sein. Und ich werde mich ihnen anschließen, merk dir das, Barbazon.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "Jackman ist nicht mein Freund! Verdammt seist du! Du hast mich in die Enge getrieben!";
			link.l1 = "Unsinn. Gib deine Stimme für den Mann, den ich dir gesagt habe und nichts wird sich für dich ändern. Ich habe dir schon gesagt, Jacques, ich will Frieden. Ich könnte alle Barone dazu bringen, dich zu hassen, aber ich werde nicht... noch nicht.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "Gut. Einverstanden. Du hast mein Wort. Hier, nimm meinen Steinbrocken, du brauchst ihn, nicht wahr?";
			link.l1 = "Genau. Ich bin froh, dass wir einen Deal abgeschlossen haben, Jacques. Und nimm 'Knave's' Brief als süßes Andenken. Oder noch besser, verbrenne es, du willst nicht, dass es gefunden wird. Ach, und noch eine letzte Sache...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Eine letzte Sache?! Was brauchst du noch von mir?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "Lass mich dich an etwas erinnern. Nicht allzu lange her hast du deinen Hund Ignacio Marco losgeschickt, um mich zu ermorden. Ich war es, der ihn getötet hat. Ich war es, der deinen Plan, eine spanische Goldgaleone zu plündern, vereitelt hat. Ich war es, der deine Freunde in den spanischen Hinterhalt in der Nähe von Saint Martin geschickt hat. Mein Name ist Charlie Prince! Wir sind fertig, Jacques, und sei das nächste Mal höflicher mit mir, wenn wir uns sehen. Glaub mir, 'Junge', wir werden uns wiedersehen, und das mehr als einmal, schätze ich.";
				link.l1.go = "terrax_8_1";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Lass mich dich an etwas erinnern. Nicht allzu lange her hast du deinen Hund Ignacio Marco losgeschickt, um mich zu ermorden. Ich war es, der ihn getötet hat. Ich war es, der deinen Plan, eine spanische Goldgaleone zu plündern, zunichte gemacht hat. Mein Name ist Charlie Prince! Wir sind jetzt fertig, Jacques, und sei das nächste Mal höflicher mit mir, wenn wir uns wiedersehen. Glaub mir, 'Junge', wir werden uns wiedersehen, und mehr als nur einmal schätze ich. Vergiss nicht, ich habe jeden Piratenbaron auf meiner Seite. Auf Wiedersehen, Barbazon...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "Sei das nächste Mal höflicher mit mir, wenn wir uns sehen. Glaub mir, 'Junge', wir werden uns wiedersehen, und ich vermute mehr als einmal. Vergiss nicht, ich habe jeden Piratenbaron auf meiner Seite. Lebewohl, Barbazon...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_8_1":
			dialog.text = "";
			link.l1 = "Vergiss nicht, ich habe jeden Piratenbaron auf meiner Seite. Auf Wiedersehen, Barbazon...";
			link.l1.go = "terrax_9";
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetCitizenType(sld);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			bDisableFastReload = false;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Glaubst du, dass ich hier nur einen Gefangenen habe? Nenne seinen Namen.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". Ist er hier?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Er war es. Ich habe ihn an diesen Plantagenbesitzer aus Barbados verkauft - Oberst Bishop, als er vor einer Woche hier war.";
				link.l1 = "Verdammt...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ach, endlich. Ich dachte schon, ich verkaufe ihn an diesen Plantagenbesitzer aus Barbados, der wird in einer Woche oder zwei hier sein... Hast du ein Lösegeld?";
				link.l1 = "Schau mal, es gibt ein kleines Problem... Eigentlich habe ich nicht so viel Geld. Aber ich bin bereit zu arbeiten.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150.000 Pesos. Wo kann ich ihn abholen?";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Du warst zu langsam... Und warum kümmert er dich? Ich habe nur mit seinen Verwandten verhandelt.";
			link.l1 = "Sie haben mich gebeten, hierher zu kommen.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Nun, du bist spät dran. Ich kann nichts tun.";
			link.l1 = "Hör zu, für wie viel hast du ihn verkauft, wenn es kein Geheimnis ist?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, das ist es nicht. Aber ich werde es dir nicht sagen... Du wirst lachen, wenn ich es tue. Ha-ha-ha-ha! Auf Wiedersehen.";
			link.l1 = "Bis dann.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "Nun, "+pchar.name+", weißt du, so funktioniert das nicht. Komm zurück mit dem Geld und du bekommst deinen Schwächling, ha-ha.";
				link.l1 = "Gut. Wir sehen uns.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Nun, nun.. Ich habe etwas vor... Weiß noch nicht einmal, wie ich anfangen soll. Ich muss einen Piraten versenken, der die Linie überschritten hat.";
				link.l1 = "Kann er nicht einfach im Dschungel getötet werden?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Das ist nicht, wie Geschäfte funktionieren, weißt du... Ich brauche seinen Tod nicht, ich muss einigen Leuten beibringen, meinen Anteil an der Beute nicht zu nehmen. Aber wenn er den Haien zum Fraß vorgeworfen wird, werde ich nicht verärgert sein.";
			link.l1 = "Warum schicken Sie nicht Ihre eigenen Leute hinter ihm her?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Nun, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" hat einige Piraten davon überzeugt, dass ihr Anteil an der Beute nicht weit von unserem Versteck aufbewahrt wird "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Geschlecht")+". Ihre beiden Schiffe '"+pchar.GenQuest.CaptainComission.ShipName1+"' und '"+pchar.GenQuest.CaptainComission.ShipName2+"' hat vor kurzem die Anker gelichtet und ist nach "+sLoc+". Jetzt siehst du, warum ich meinen Männern diese Arbeit nicht anvertrauen kann?";
			link.l1 = "Ich tue. Wie viel Zeit habe ich?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 bis 15 Tage nicht mehr, es ist mir wichtig, wenn sie nicht zum Versteck kommen, oder es wäre Unsinn, sie mit wertvoller Ladung zu versenken. In diesem Fall wäre es besser, wenn sie es hierher bringen würden...";
			link.l1 = "Gut, ich bin dabei. Ich werde versuchen, sie zu fangen.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Mach dir keine Sorgen. Meine Männer werden ihn zu deinem Schiff bringen. Und warum kümmert er dich?";
			link.l1 = "Ich nicht. Seine Verwandten haben mich gebeten, ihn zu liefern.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ach, das ist gut. Ich war fast traurig, so einen niedrigen Preis für deinen Mann zu geben. Ha-ha-ha-ha! Lebewohl.";
			link.l1 = "Bis dann.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Also, , "+GetFullName(pchar)+", hast du meine Kumpels versenkt? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nein. Ich habe es nicht geschafft, sie zu fangen. Und ich habe sie bei der Rückkehr nicht getroffen.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Ich hab's getan. Ich habe sie dazu geschickt, die Haie zu füttern.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Verdammt! Ob du sie getroffen hast oder nicht, spielt jetzt keine Rolle! Und was wird dein nächster Vorschlag sein?";
			link.l1 = "Vielleicht haben Sie einen einfacheren Job für mich?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Hör zu, "+NPChar.name+", senke den Preis für den Gefangenen...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nein.";
			link.l1 = "Dann leb wohl...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Den Preis senken?! Ich habe gerade meinen Vorrat wegen deiner Inkompetenz verloren! Und jetzt kann ich den Preis erhöhen! Du kannst ihn für 200.000 Pesos haben, wenn du willst, oder du kannst zum Teufel hier raus.";
			link.l1 = "Es ist zu teuer... Auf Wiedersehen...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Verdammt, nimm deine Münzen.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Du kannst diesen Schwächling nehmen...";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Gut gemacht! Nimm deinen Schwächling und viel Glück.";
			link.l1 = "Danke. Lebewohl.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Du hast das Lösegeld gebracht"+GetSexPhrase("","ла")+"? Ich habe nicht gescherzt, als ich sagte, dass ich ihn an die Pflanzer verkaufen werde.";			
			link.l1 = "Hör zu, "+NPChar.name+", hier ist die Sache... Im Grunde habe ich nicht so viel Geld. Aber ich bin bereit"+GetSexPhrase("","а")+" abarbeiten.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150000 Pesos. Wo kann ich ihn bekommen?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Hast du das Geld mitgebracht? Ich habe nicht gescherzt, als ich davon sprach, diesen Mann an die Plantage zu verkaufen.";			
			link.l1 = "Ich habe das Geld nicht, "+NPChar.name+", aber ich arbeite daran.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150.000 Pesos. Wo kann ich ihn abholen?"link.l2.go ="HauptComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "Und warum interessiert es dich, was ich tue? Weißt du, du solltest besser gehen...";
			link.l1 = "Tshh, beruhige dich. Ich habe Geschäfte mit dir. Es geht um deinen Gefangenen.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ach, gut. Wen möchtest du auslösen?";
			link.l1 = "Warte. Ich bin nicht hier, um auszukaufen, ich biete dir an, einen Gefangenen zu kaufen. Und nun ja, du wirst die Möglichkeit haben, ein Lösegeld für ihn zu bekommen.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. Und warum brauchst du meine Vermittlung? Warum willst du das Geld nicht direkt für dich selbst bekommen?";
			link.l1 = "Es ist ziemlich riskant für mich. Ich könnte Probleme mit den Behörden bekommen.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... gut dann. Lass uns mal sehen. Wer ist dein Gefangener?";
			link.l1 = "Das ist "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Ich sehe... es wäre ein guter Handel, wenn du nicht lügst. Ich nehme an, dass ich dir für diesen Mann bezahlen kann "+iTemp+" Pesos oder gebe dir stattdessen einige interessante Informationen. Es ist deine Wahl.";
			link.l1 = "Ich nehme besser Pesos. Ich habe genug von diesem Geschäft...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Erzähl mir mehr. Ich bin sicher, dass du mir etwas Interessantes geben wirst.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Geld also. Nimm sie. Jetzt ist es nicht mehr dein Problem. Bring das Verkaufsobjekt hierher.";
			link.l1 = "Er muss schon in der Nähe des Stadttors sein. Danke! Du hast mir wirklich geholfen.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Du bist willkommen, bring mir mehr... Bis dann!";
			link.l1 = "Viel Glück...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Es ist gut, Geschäfte mit einem klugen Mann zu machen. Jetzt hör zu: in ein paar Tagen "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" eine spanische Expedition wird aus Main eintreffen, beladen mit wertvollen Gütern. Sie werden auf ein Schiff warten, das die Fracht übernehmen soll. Wenn du innerhalb einer Woche dort bist, hast du die Chance, die Fracht für dich zu nehmen.\nWenn ich du wäre, würde ich mich bereits zu meinem Schiff bewegen. Und bring den Gefangenen hierher.";
					link.l1 = "Danke! Die Waren werden eine schöne Entschädigung für meine Mühen sein. Und mein Passagier muss bereits in der Nähe der Stadttore sein. Er wird zu dir gebracht.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Es ist gut, Geschäfte mit einem klugen Mann zu machen. Jetzt hör zu: in etwa einer Woche kommt eine spanische Brigantine '"+pchar.GenQuest.Marginpassenger.ShipName1+"' beladen mit wertvollen Gütern wird segeln von "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" zu "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Wenn du dich beeilst, wirst du es leicht erwischen.\nBist du immer noch hier? Wenn ich du wäre, würde ich schon zu meinem Schiff gehen. Und bring den Gefangenen hierher.";
					link.l1 = "Danke! Die Waren werden eine schöne Entschädigung für meine Mühen sein. Und mein Passagier muss bereits in der Nähe des Stadttors sein. Er wird zu Ihnen gebracht.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Raub!!! Das ist inakzeptabel! Mach dich bereit, "+GetSexPhrase("Junge","Mädchen")+"...","He, was zum Teufel machst du da?! Dachtest du könntest mich ausrauben? Du bist erledigt... ","Warte, was zum Teufel? Nimm deine Hände weg! Es stellt sich heraus, dass du ein Dieb bist! Ende der Linie, Bastard...");
			link.l1 = LinkRandPhrase("Scheiße!","Verdammt!!","Verdammt noch mal!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = "Verschwinde hier!";
			link.l1 = "Ups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Belästige mich nicht mit deinem billigen Gerede. Das nächste Mal wird dir das Ergebnis nicht gefallen...";
        			link.l1 = "Ich hab's.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Es ist vorbei, kein Geplapper.","Ich will nicht mehr mit dir reden, also belästige mich besser nicht mehr.");
			link.l1 = RandPhraseSimple("Wie du wünschst...","Hm, gut dann...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ich hoffe, dass du mehr Respekt zeigen und aufhören wirst, grob zu sein?";
        			link.l1 = "Du kannst sicher sein, Jacques, ich werde.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "Das Problem lösen? Verstehst du, was du getan hast? Wie dem auch sei, bring mir eine Million Pesos und ich werde die Jungs dazu überreden, deine 'Heldentaten' zu vergessen. Wenn dir die Idee nicht gefällt, dann kannst du zur Hölle fahren.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Gut, ich bin bereit zu zahlen.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Verstanden. Ich gehe jetzt.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Gut! Betrachte dich als wieder sauber. Aber ich hoffe, dass du solche widerlichen Dinge nicht wieder tust.";
			link.l1 = "Ich werde nicht. Viel zu teuer für mich. Lebewohl...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
