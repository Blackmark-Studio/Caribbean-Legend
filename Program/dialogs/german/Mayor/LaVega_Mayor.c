// заместитель Маркуса Тиракса в Ла Веге
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
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
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat("Haben Sie mir etwas zu sagen? Nein? Dann verschwinden Sie von hier!","Ich denke, ich habe mich klar ausgedrückt, hör auf, mich zu belästigen.","Obwohl ich mich klar ausgedrückt habe, belästigst du mich weiterhin!","Richtig, ich habe genug von dieser Unhöflichkeit.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ich gehe schon.","Sicher"+npchar.name+"...","Entschuldigung, "+npchar.name+"...","Ups...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", ich freue mich, Sie zu sehen! Was wünschen Sie?","Was sonst?"," Du schon wieder? Belästige die Leute nicht, wenn du nichts zu tun hast!","Ich weiß, dass Sie ein anständiger Mann sind. Aber ich habe genug davon, mit Ihnen zu reden.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nichts. Ich wollte dich nur sehen.","Nichts...","In Ordnung, "+npchar.name+", Entschuldigung...","Verdammt, es ist nur meine Schuld...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Diebstahl!!! Meinst du das ernst?! Du bist erledigt, Kumpel...","Warte, was zum Teufel? Es stellt sich heraus, dass du ein Dieb bist! Du bist erledigt...");
			link.l1 = LinkRandPhrase("Scheiße!","Carramba!!","Verdammt noch mal!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Geh weg","Verschwinde ")+" von hier!","Verlassen Sie sofort mein Haus!");
			link.l1 = "Ups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Belästigen Sie mich nicht mit Ihrem billigen Gerede. Das nächste Mal wird Ihnen das Ergebnis nicht gefallen...";
        			link.l1 = "Ich habe es verstanden.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "Es ist vorbei, kein Gespräch.";
			link.l1 = RandPhraseSimple("Wie Ihr wünscht...","Gut dann...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ich hoffe, Sie werden mir mehr Respekt entgegenbringen und aufhören, unhöflich zu sein? Andernfalls müsste ich Sie töten. Das wäre sehr unangenehm.";
        			link.l1 = ""+npchar.name+", Sie können sicher sein, ich werde es tun.";
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
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			dialog.text = "Ach, das bist du, de Maure. Nun, welch Überraschung. Beim See Teufel, deine Ankunft ist das interessanteste, was seit Langem passiert ist, verdammt noch mal.";
			link.l1 = "Es freut mich auch, dich zu sehen, Vensan. Genießt du es, das Dorf zu regieren?";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "Wie könnte ich? Ich bin ein Kapitän, ein verdammt guter dazu, nicht irgendein verfluchter Buchhalter. Und ich habe länger auf die Boten von Marcus gewartet, um mich zu einer neuen Reise zu rufen, als ich auf Weihnachten gewartet habe, verfluchte Flüche!";
			link.l1 = "Weihnachten und Flüche in einem Satz, das ist etwas. Ja, ich beneide dich nicht. Obwohl, viele würden gerne in deiner aktuellen Position sein. Aber ich bin geschäftlich zu dir gekommen, Vensan.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Geschäfte?! Nun, spuck es aus - hast du dir etwas überlegt? Hast du eine gute Spur? Ich bin dabei, den örtlichen Keller aus purer Langeweile und all diesen verfluchten Berechnungen leer zu trinken.";
			link.l1 = "Nun, es ist mehr so, dass ich eine Frage an Sie habe, nichts weiter.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Verdammt nochmal! Aber gut, ich höre zu, Charles.";
			link.l1 = "Ist eine Frau zu Ihnen gekommen? Oder haben Sie sie vielleicht in La Vega gesehen? Sie nennt sich Belle Étoile, obwohl das nur ein Alias ist, daher könnte sie sich unter einem anderen Namen vorgestellt haben. Was wichtig ist, dass sie... sie hat gelbe Haut. Aber sie ist keine Sklavin oder Arbeiterin - sie ist eine wohlhabende Frau.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "Gelbhäutig, aber wohlhabend? So jemanden hatten wir hier noch nie, niemals! Scheint, du führst immer noch dieses interessante Leben von dir, de Maure! Ich bin fast eifersüchtig.";
			link.l1 = "Ist das so... Nun, danke für Ihre Zeit, Vensan. Ich werde Sie nicht länger von Ihrer Buchhaltung ablenken, heh-heh.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "40");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}
