void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Es wurde Alarm in der Stadt geschlagen. Jeder sucht dich! Wenn ich du wäre, würde ich hier nicht zu lange warten.","Die ganze Stadtwache durchsucht die Stadt, um dich zu finden. Ich bin kein Idiot und ich werde nicht mit dir reden!","Lauf, Kumpel, bevor die Soldaten Hackfleisch aus dir machen..."),LinkRandPhrase("Was brauchst du, Schurke?! Die Stadtwache ist dir auf den Fersen. Du wirst nicht weit kommen, du schmutziger Pirat!","Verlassen Sie mein Haus, Mörder! Wachen!!","Ich habe keine Angst vor dir, du Lümmel! Bald werden sie dich aufhängen, du wirst nicht davonkommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ich mache mir nicht zu viele Sorgen um den Alarm...","Sie haben keine Chance, mich zu fangen."),RandPhraseSimple("Halt die Klappe, "+GetWorkTypeOfMan(npchar,"")+", oder ich schneide deine verdammte Zunge ab!","Heh, "+GetWorkTypeOfMan(npchar,"")+", du willst auch einen Piraten jagen! Hör zu, Kumpel, bleib ruhig und du wirst leben..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Ich habe Sie noch nie zuvor gesehen, senor. Darf ich annehmen, dass Sie ein Kapitän sind... Habe ich recht geraten? Mein Name ist "+GetFullName(npchar)+", und mein Laden steht zu Eurem Dienst. Gold, Silber, und noch viel mehr, um das Interesse eines neugierigen Mannes zu wecken.";
				Link.l1 = "Ich verstehe. Ich bin "+GetFullName(pchar)+". Freut mich, Sie kennenzulernen, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", senor! Ich freue mich, Sie wieder in meinem Laden zu sehen. Möchten Sie vielleicht einige Goldklumpen erwerben? Oder sind Sie heute vielleicht an Mineralien interessiert?";
				link.l1 = "Zeig mir deine Ware, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "Nein, ich brauche nichts, "+npchar.name+". Ich bin nur vorbeigekommen, um dir Hallo zu sagen.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Auch ich, Herr. Möchten Sie einen Blick auf meine Waren werfen? Ich bin sicher, ich habe etwas, das Sie interessieren könnte.";
			link.l1 = "Dies ist mein erstes Mal hier und ich möchte ein bisschen mehr über diese Siedlung erfahren.";
			link.l1.go = "info";
			link.l2 = "Dann zeig mir, was du zum Verkauf hast.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Unsere kleine Stadt wurde dank der Goldmine gebaut. Sie fördern Gold, Silber und Goldnuggets. Manchmal sogar Edelsteine. Wir hatten hier nur eine Garnison, bis freundliche Indianer und einige weiße Siedler zu uns stießen\nIgnacio Ortega hat eine Taverne gebaut und unser Leben ein bisschen fröhlicher gemacht. Allerlei Abenteurer besuchen diesen Ort mit der dummen Absicht, uns auszurauben. Wir haben hier kein Gericht, also ging ihre Zahl zurück, nachdem wir einige Idioten mitten in der Stadt aufgehängt hatten\nGold wird unter dem Schutz von Soldaten und freundlichen Indianern zu den Schiffen geschickt, Nuggets jedoch können Sie direkt hier, in diesem Laden, kaufen\nAußerdem habe ich manchmal sehr interessante Mineralien anzubieten, also besuchen Sie mich, wenn Sie Zeit haben, ich fülle meinen Bestand immer wieder auf.";
			link.l1 = "Danke für die interessante Geschichte! Ich werde sie im Kopf behalten.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Raub bei hellichtem Tag!!! Was geht hier vor?! Warte, halt ein, Kumpel...","He, was machst du da?! Versuchst du mich zu berauben? Jetzt bist du geliefert...","Warte, was zum Teufel machst du? Es stellt sich heraus, dass du ein Dieb bist! Betrachte dies als das Ende der Linie, du Bastard...");
			link.l1 = LinkRandPhrase("Teufel!!","Donnerwetter!!","Ach, Scheiße!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
