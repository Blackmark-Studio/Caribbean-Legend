// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "Haben Sie ein Anliegen bei mir? Nein? Dann raus mit Ihnen!";
			link.l1 = "Ich gehe schon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == int(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Haben Sie Arbeit für mich?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "Ich habe die Spur aufgenommen, aber ich brauche einige Münzen - 30.000 Pesos, um die Ratte aus ihrem Loch zu locken.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Hier, schau dir diesen Brief an, den ich auf der Leiche des Schmugglers gefunden habe";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Es ist vollbracht. Norman Vigo und sein Schiff sind dem See-Teufel anheimgefallen.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... Arbeit, haben Sie gesagt? Eigentlich ist es gut, dass Sie mich gefragt haben. Ich brauche einen Mann von außerhalb. Ich möchte in der nächsten Stadt etwas herausfinden, aber meine Männer sind dort bekannt. Kann Ihnen nicht viel versprechen, aber Sie werden etwas bekommen.";
			link.l1 = "Schön! Was ist die Mission?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Entschuldigung, aber ich werde es nicht für ein paar Krümel riskieren. Lebewohl.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Dann hören Sie zu, ich hatte vor einem Monat einen Deal für die Lieferung von 200 Sklaven mit dem Kapitän der Schoner 'Saintblue'. Ich wollte sie an den örtlichen Plantagenbesitzer verkaufen. Die Zeit ist vergangen und der Kunde hat angefangen sich Sorgen zu machen, aber gestern wurde mir gesagt, dass der Schoner nicht weit von der Insel gesehen wurde. Aber! Der Kapitän hat sich nicht blicken lassen. Heute hat mein Kunde von mir verlangt, seine Vorauszahlung zurückzugeben und sagte, dass ihm angeboten wurde, Sklaven von einem anderen Verkäufer zu kaufen. Teurer, aber die ganze Bande von Sklaven und auf einmal.";
			link.l1 = "Und? Ich muss in ein paar Tagen 200 Sklaven finden, um Sie vor dem Verlust einer Anzahlung zu retten? Für ein paar Münzen?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Sicher nicht. Sehe ich aus wie ein Idiot? Ich werde ihm seine Anzahlung sowieso nicht zurückgeben. Aber ich brauche den Beweis, dass diese Sklaven, die ihm angeboten wurden, meine sind. Finde diejenigen, die ihm ein neues Angebot gemacht haben und du bekommst deine 10.000 Pesos. Abgemacht?";
			link.l1 = "Ich bin dabei. Haben Sie irgendwelche Verdächtigungen? Wer könnte das getan haben?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Keine Chance. Suchen Sie jemand anderen. Nur für 10.000? Tut mir leid, aber das wird nicht funktionieren.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Wenn ich irgendwelche Ideen hätte, würde ich niemals Ihre Dienste in Anspruch nehmen. Diese Männer wären bereits tot. Aber ich bin gespannt, wie sie von der Ladung der 'Saintblue' und meinem Kunden erfahren haben. Es scheint, dass es für sie ziemlich einfach war. Verstehen Sie jetzt?";
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
			dialog.text = "Genau! Ich suche ihn. Das Töten meiner Konkurrenten und die Rückgabe meiner Sklaven sind nicht deine Priorität. Ich brauche diese Ratte, eigentlich seinen Kopf auf einem Spieß, um ehrlich zu sein. Siehst du jetzt, warum meine Männer nichts von deiner Mission wissen sollten? Ich werde jeden verdächtigen, bis ich herausfinde, wer die Informationen verkauft. Und das will ich eigentlich nicht...";
			link.l1 = "Ich verstehe. Dann werde ich ein niedriges Profil behalten. Ich bin auf meinem Weg.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Dreißigtausend sagst du? Das ist eine große Summe... Ich kann dir nur 5.000 Pesos geben, das ist alles, was ich jetzt habe. Und versuche nicht einmal, mit dem Geld zu fliehen, oder ich finde dich und hänge dich an den nächsten Zaun! Verstanden?";
			link.l1 = "Gut, gib mir dann fünftausend...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Nimm es. Ich warte auf das Ergebnis deiner Suche.";
			link.l1 = "Alles wird gut werden.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Ausgezeichnete Nachrichten! Ich war sicher, dass du es schaffen würdest. Ich habe einige faszinierende Informationen.";
			link.l1 = "Ich habe meine Arbeit getan und will meine zehntausend haben.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Sicher, hier ist deine Belohnung. Aber lauf nicht weg, ich habe noch eine Aufgabe für dich.\nPfaifer ist ein Matrose von Norman Vigo auf dem Schoner 'Septima'. Ich bin mir sicher, dass Norman Vigo die Ratte ist, auch wenn er einer von uns ist. Er wurde kürzlich in den Gewässern der Insel gesehen. Deine Aufgabe ist es, diese Ratte zum Seeteufel zu schicken. Du hast mich das erste Mal nicht im Stich gelassen, daher möchte ich dich bitten, dich auch um diese Angelegenheit zu kümmern. Ich zahle dir 15.000 Pesos. Abgemacht?";
			link.l1 = "Ich bin dran! Betrachten Sie den Verräter Norman Vigo als tot.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Weißt du, ich will daran nicht teilnehmen... Ich habe sowieso keine Zeit. Tut mir leid, aber ich mache mich davon.";
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
			dialog.text = "Ich weiß, ich weiß. Meine Männer haben die Schlacht beobachtet und bereits von Ihrem makellosen Sieg berichtet. Gut, Sie haben Ihre Arbeit gut gemacht. Hier sind die 15.000 Pesos, die ich versprochen habe. Und danke, Sie haben mir sehr geholfen.";
			link.l1 = "Es ist in Ordnung, ich habe gerne geholfen! Aber ich muss jetzt gehen, ich bin schon zu lange hier und habe noch viel zu tun. Lebewohl!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
