// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
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
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting()+"! Ich bin "+GetFullName(NPChar)+", der neue Gouverneur dieses Lochs. Es wird nicht einfach sein, die örtlichen Schläger zur Ordnung zu rufen, aber sie stellen keine Bedrohung mehr für die spanischen Kolonien dar.";
					Link.l1 = "Ich freue mich, Sie zu treffen. Ich bin Kapitän "+GetFullName(Pchar)+". Entschuldigung, aber ich muss gehen.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting()+". Ich bin beschäftigt, wirklich beschäftigt, ich muss die lokalen Schläger kontrollieren, um jede Bedrohung für die spanischen Kolonien zu verhindern.";
					Link.l1 = "Ich werde Sie dann nicht belästigen.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("Haben Sie mir etwas zu berichten? Nein? Dann "+GetSexPhrase("verschwinde von hier!","Ich bitte Sie, mich nicht zu stören.")+"","Ich glaube, dass ich mich klar ausgedrückt habe...","Obwohl ich mich klar ausgedrückt habe, belästigen Sie mich weiterhin!","Nun, Sie sind unermesslich "+GetSexPhrase("zu unhöflich, mon cheri","so eine Unhöflichkeit, Mädchen","so eine Unhöflichkeit, Mädchen")+"...","repeat",30,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ich gehe.","Ja, "+npchar.name+", ich sehe das.","Entschuldigung, "+npchar.name+"...","Autsch...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}


					if (npchar.city == int(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Haben Sie irgendwelche Arbeit für mich?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "Ich habe die Spur aufgenommen, aber ich benötige einige Münzen - 30.000 Pesos, um die Ratte aus ihrem Loch zu locken.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Hier, schau dir diesen Brief an, den ich auf der Leiche des Schmugglers gefunden habe";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Es ist vollbracht. Norman Vigo und sein Schiff gehören dem See-Teufel.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm.. Arbeit, sagst du? Tatsächlich ist es gut, dass du mich gefragt hast. Ich brauche einen Mann von außerhalb. Ich möchte in der nächsten Stadt etwas herausfinden, aber meine Männer sind dort bekannt. Kann dir nicht viel versprechen, aber du wirst etwas bekommen.";
			link.l1 = "Was ist die Mission?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Entschuldigung, aber ich werde das Risiko nicht für ein paar Krümel eingehen. Lebewohl.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Dann hören Sie zu, ich hatte vor einem Monat einen Deal zur Lieferung von 200 Sklaven mit dem Kapitän der Schoner 'Saintblue'. Ich wollte sie an den örtlichen Plantagenbesitzer verkaufen. Die Zeit ist vergangen und der Kunde hat begonnen sich Sorgen zu machen, aber gestern wurde mir gesagt, dass der Schoner nicht weit von der Insel gesehen wurde. Aber! Der Kapitän zeigte sich nicht. Heute hat mein Kunde mich aufgefordert, seine Anzahlung zurückzugeben und sagte, dass ihm angeboten wurde, Sklaven von einem anderen Verkäufer zu kaufen. Teurer, aber die ganze Menge Sklaven auf einmal.";
			link.l1 = "Und? Ich muss in wenigen Tagen 200 Sklaven finden, um dich vor dem Verlust einer Anzahlung zu retten? Für ein paar Münzen?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Natürlich nicht. Sehe ich aus wie ein Idiot? Ich werde ihm die Anzahlung sowieso nicht zurückgeben. Aber ich brauche den Beweis, dass diese Sklaven, die ihm angeboten wurden, meine sind. Finde diejenigen, die ihm einen neuen Deal angeboten haben und du bekommst deine 10.000 Pesos. Abgemacht?";
			link.l1 = "Ich bin dabei. Haben Sie irgendwelche Verdächtige, wer es sein könnte?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Keine Chance. Such dir jemand anderen, nur für 10.000? Tut mir leid, aber das wird nicht funktionieren.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Wenn ich irgendwelche Ideen hätte, würde ich niemals Ihre Dienste in Anspruch nehmen. Diese Männer wären schon tot. Aber ich bin gespannt, wie sie von der Ladung der 'Saintblue' und meinem Klienten erfahren haben. Es scheint, als wäre es für sie ziemlich einfach gewesen. Sehen Sie jetzt?";
			link.l1 = "Ja, jemand hat dich verraten.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Genau! Ich suche ihn. Das Töten meiner Konkurrenten und die Rückkehr meiner Sklaven sind nicht Ihre Priorität. Ich brauche diese Ratte, eigentlich seinen Kopf auf einem Spieß, um ehrlich zu sein. Sehen Sie jetzt, warum meine Männer nichts von Ihrer Mission wissen sollten? Ich werde jeden verdächtigen, bis ich herausfinde, wer die Informationen verkauft. Und das möchte ich wirklich nicht...";
			link.l1 = "Ich verstehe. Dann werde ich mich bedeckt halten. Ich bin auf dem Weg.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Dreißigtausend sagst du? Das ist eine große Summe... Ich kann dir nur 5.000 Pesos geben, das ist alles was ich jetzt habe. Und versuche nicht einmal, mit dem Geld zu fliehen, oder ich finde dich und hänge dich am nächsten Zaun auf! Verstanden?";
			link.l1 = "Gut, gib mir dann fünftausend...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Nehmen Sie es. Ich warte auf das Ergebnis Ihrer Suche.";
			link.l1 = "Es wird gut werden.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Ausgezeichnete Neuigkeiten! Ich war mir sicher, dass du es schaffen würdest. Ich habe einige faszinierende Informationen.";
			link.l1 = "Ich habe meine Arbeit getan und möchte meine zehntausend haben.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Sicher, hier ist deine Belohnung. Aber lauf nicht weg, ich habe noch einen Auftrag für dich.\nPfaifer ist ein Matrose von Norman Vigo auf der Lugger 'Septima'. Ich bin mir sicher, dass Norman Vigo die Ratte ist, auch wenn er einer von uns ist. Er wurde kürzlich in den Gewässern der Insel gesehen. Deine Aufgabe ist es, diese Ratte dem Meeresdämon zu senden. Du hast mich das erste Mal nicht enttäuscht, deshalb möchte ich dich bitten, dich auch um diese Angelegenheit zu kümmern. Ich werde dir 15.000 Pesos zahlen. Abgemacht?";
			link.l1 = "Ich bin dran! Betrachte den Verräter als tot.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Sie wissen, ich möchte daran nicht teilnehmen... Ich habe sowieso keine Zeit. Entschuldigung, aber ich muss los.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Ich weiß, ich weiß. Meine Männer haben die Schlacht beobachtet und haben mir bereits von Ihrem makellosen Sieg berichtet. Gut, Sie haben Ihre Arbeit gut gemacht. Hier sind 15.000 Pesos, wie ich versprochen habe. Und danke, Sie haben mir sehr geholfen.";
			link.l1 = "Es ist gut, ich habe gerne geholfen! Aber ich muss jetzt gehen, ich bin schon zu lange hier und ich habe viel zu tun. Lebewohl!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "Grüße, mein Name ist Alistair Good. Ich wurde nach Mansfields Tod zum Anführer der Freibeuter gewählt.";
			link.l1 = "Freut mich, Sie kennenzulernen, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "Ich habe keine Zeit, mit Ihnen zu sprechen. Besuchen Sie mich später.";
			link.l1 = "Ich gehe bereits.";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Holen","Holen")+" raus!","Verlassen Sie mein Zuhause!");
			link.l1 = "Ups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > int(npchar.angry.terms))
                {
         			dialog.text = "Stör mich nicht, erinnere dich daran.";
        			link.l1 = "Ich habe es.";
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
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
