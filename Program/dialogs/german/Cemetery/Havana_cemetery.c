// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Wie kann ich Ihnen helfen?","Was kann ich für Sie tun?"),"Erzählen Sie, was Sie bedrückt, "+GetAddress_Form(NPChar)+"?","Zum dritten Mal, "+GetAddress_Form(NPChar)+", was brauchen Sie?","Ich habe genug von Ihnen. Verschwinden Sie!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt, Entschuldigung.","Es gibt nichts, entschuldigen Sie mich."),"Verzeihen Sie, es gibt nichts.","Sie haben recht, es ist bereits das dritte Mal. Verzeihen Sie...","Entschuldigung.",npchar,Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Hören Sie, haben Sie einen Mann namens Joachim Merriman gesehen oder getroffen, hier in Havanna oder in der Nähe? Er ist ein mittelalter, portugiesischer Senor mit einem durchdringenden Blick und einem Schnurrbart, der fast schon kaiserlich anmutet. Vielleicht haben Sie ihn in einer Bucht oder im Dschungel gesehen? Ich suche ihn.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "N-nein, Senor, g-ganz sicher nicht. Ich bekomme selten Besucher hier unten, sehen Sie, äh... und ich... ich habe niemanden gesehen, der diesem Mann entspricht, den Sie beschrieben haben, also...";
			link.l1 = "Wirklich? Warum stottern Sie dann und verstecken Ihre Augen? Lügen Sie mich nicht an, Sie kennen die Wahrheit. Fangen wir nochmal von vorne an - haben Sie diesen Mann gesehen?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "I-Ich sage I-Ihnen, Senor, ich h-habe niemanden gesehen! I-Ich st-stottere s-seit ich ein K-Kind war...";
			link.l1 = "Lügen, alles Lügen. Ich kann es in Ihren Augen sehen. Wo ist er, wo ist Merriman?! Sagen Sie es mir, JETZT!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Ich kenne keinen Merriman! Ich habe diesen Namen auch noch nie gehört! Und versuchen Sie nicht, mir weh zu tun, sonst wird Sie der Kommandant im Fort aufhängen! Also verschwinden Sie schnell, Senor!";
			link.l1 = "Oh, so ist das also? Gut. Jetzt hören Sie mir mal sehr genau zu: Joachim Merriman ist ein Hexenmeister. Die Heilige Inquisition sucht ihn. Vor vielen Jahren wurde er in Europa zum Tod auf dem Scheiterhaufen verurteilt, für das Schänden von Gräbern, die Entweihung der Toten und Hexerei. Und ich weiß mit Sicherheit, dass er sich jetzt irgendwo hier, am Rande von Havanna, versteckt...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "...neulich habe ich die nahegelegene Höhle von Untoten befreit und ich weiß, wer dafür verantwortlich ist! Wohin sonst würde Merriman gehen, wenn nicht zum Friedhof! Sie wissen, wo er ist. Aber gut, ich werde Ihnen nichts antun, aber ich werde den Inquisitoren in Santiago einen Besuch abstatten. Pater Vincento wird es sehr interessant finden, dass Joachim Merriman sich mit seinem Komplizen, dem örtlichen Wachmann, auf dem Friedhof von Havanna versteckt...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "...Ist das Blut schon aus Ihrem Gesicht gewichen? Ich gebe Ihnen das Wort eines Adeligen: Am Tag nachdem ich meine Erkenntnisse melde, wird die ganze Insel von spanischen Soldaten wimmeln. Und Sie werden auf einer Streckbank liegen, flehen und weinen, bis Sie verraten, wo sich dieser Hexenmeister versteckt hält. Spätestens dann werden Sie als sein Komplize auf dem Scheiterhaufen verbrannt, während ich mir das Spektakel ansehe. Wie wäre es damit?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "B-bitte, Herr! Ich habe an nichts davon teilgenommen, ich schwöre! Ich... ich konnte einfach nichts tun... Wie könnte ich mich gegen ihn stellen?! Er ist ein schrecklicher Mann, er kann... Sie haben keine Ahnung, was er tun kann! Gnade, ich bitte Sie!";
			link.l1 = "Vertrauen Sie mir, ich weiß, was er kann. Ich habe es mit meinen eigenen Augen gesehen. Also? Wo ist er? Sagen Sie es mir und ich verspreche, ich werde Sie nicht weiter in diese Angelegenheit verwickeln.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Er... Er versteckt sich in einer Höhle unter dem Friedhof. Man kann nur durch die Tür der Kapelle dorthin gelangen. Wenn er herauskommt, verstecke ich mich in meinem Haus und bleibe dort. Sie haben keine Ahnung, wie sehr ich dieses Grauen loswerden möchte!\nAber ich würde es nicht wagen, mich auch nur zu nähern. Ich... Ich habe ihn gesehen, wie er ein frisches Grab aufgrub, und dann... dann stand der tote Mann auf und spazierte im Mondlicht auf dem Friedhof herum! Ich habe damals fast meinen Verstand verloren! Aber Merriman hat mir verboten zu gehen. Er drohte mir, dass wenn ich mein Haus auch nur für einen halben Tag ohne seine Erlaubnis verlasse, wird er mich finden und in diese Abscheulichkeit verwandeln... ein wandelndes Skelett!";
			link.l1 = "Wie oft verlässt er seine Höhle?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Nun, ich bringe ihm Essen und Heiltränke aus der Stadt und... was auch immer er verlangt. Er verlässt die Höhle ein oder zweimal im Monat... wenn Vollmond ist. Er hinterlässt einen Zettel an der Tür, schreibt, was er braucht... I-ich liefere es und lege es an die Tür, und er nimmt es, sobald er zurückgekehrt ist.";
			link.l1 = "Ich verstehe. Ist diese Tür zu seinem Versteck auf irgendeine Weise verriegelt?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "Das ist sie. Sie ist immer verschlossen. Sie ist sehr robust und das Schloss ist massiv und komplex.";
			link.l1 = "Hm... Merriman ist kein Narr, sicherlich muss er einen anderen Ausgang aus seinem Versteck haben, wie bei seinem Haus in Europa. Wenn wir die Tür aufbrechen würden, würde er sich davonschleichen, und nie wieder gefunden werden. Hmmm...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Herr, schwören Sie, dass Sie mich nicht der Inquisition ausliefern?";
			link.l1 = "Ich habe Ihnen mein Wort gegeben, und das Wort eines Adeligen ist heilig. Ich schwöre, dass ich Sie nicht verraten werde.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Oh, ich segne Sie, Senor! Ich weiß, wie man zur Höhle kommt. Es gibt einen Schlüssel, einen zweiten Schlüssel... Ich habe ihn. Merriman weiß nicht, dass es zwei Schlüssel für dieses Schloss gibt. Ich würde mich nie trauen einzutreten, aber Sie...";
			link.l1 = "Geben Sie mir den Schlüssel, und ich werde Sie von diesem Alptraum befreien.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Hier, Senor. Gehen Sie wirklich in seine Höhle?";
			link.l1 = "Ja, das werde ich. Schließen Sie sich in Ihrem Haus ein und warten Sie dort, wenn ich hineingehe. Sollte ich nicht zurückkehren, lassen Sie alles stehen und liegen und laufen, so schnell Sie können.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Aber seien Sie vorsichtig, Senor. Gruselige Geräusche habe ich aus seiner Höhle gehört und ich fürchte mich sogar daran zu denken, welche Wesen sie bewohnen könnten. Aber Merriman ist nicht allein - das ist sicher.";
			link.l1 = "Ich werde alle Maßnahmen ergreifen, die ich kann. Leb wohl.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
