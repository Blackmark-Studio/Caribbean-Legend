// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hast du Fragen, "+GetSexPhrase("mein Sohn","meine Tochter")+"?","Frag ruhig, ich höre zu..."),"Ich höre zu, sprich jetzt, "+GetSexPhrase("mein Sohn","meine Tochter")+"...","Zum dritten Mal, "+GetSexPhrase("mein Sohn","meine Tochter")+", frag mich, was brauchst du?","Ein Geistlicher hat viel Arbeit und du lenkst mich ab, "+GetSexPhrase("mein Sohn","meine Tochter")+".","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt, Padre..."),"Ich habe nichts zu sagen, Entschuldigt mich.","Ich werde fragen haben, aber nicht jetzt. Verzeiht mir, Vater.","Verzeihen Sie mir, heiliger Vater...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "Heiliger Vater, ich suche Marisa Caldera. Man sagt, sie sei sehr gläubig und habe die Kirche regelmäßig besucht. Können Sie mir sagen, wo ich sie finden kann?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "Marisa war eine unserer treuesten Gemeindemitglieder, die wahre Seele unserer Kirche. Ihr Fehlen ist ein großer Verlust für unsere Gemeinde. Was ihr Verschwinden verursacht hat, weiß ich nicht, aber ich bin überzeugt: sie wurde auf eine ungerechte Probe gestellt, und hier war sicher das Werk des Teufels und seiner Diener im Spiel\nManchmal erreichen mich Gerüchte, dass sie in der Stadt gesehen wurde, aber mehr auch nicht. Uns bleibt nur, auf Gottes Willen zu hoffen und zu glauben, dass sie eines Tages zurückkehrt und erneut Trost unter dem Dach der Kirche findet.";
			link.l1 = "Vielleicht kennen Sie jemanden, der mehr über sie erzählen kann?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("Mein Sohn","Meine Tochter")+", sag mir, warum suchst du Marisa? Ich weiß, dass von Zeit zu Zeit Leute nach ihr fragen, deren Erscheinung kaum die eines Rechtschaffenen ist. Die Welt ist voller Versuchungen, und nicht alle, die sie suchen, tun dies aus guten Absichten. Bevor ich auch nur ein Wort sage, muss ich sicher sein, dass du weder ihr noch denen, die mit ihr in Verbindung stehen, Unheil bringst.";
			link.l1 = "Ich verstehe Ihre Bedenken, heiliger Vater, aber ich versichere Ihnen: Ich habe keine schlechten Absichten. Ich möchte ihr lediglich einen Brief übergeben, der viel zu lange unterwegs war. Wer weiß, vielleicht enthält er etwas Wichtiges für sie. Sehen Sie selbst.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Übergeben: Brief für Marisa Caldera", "None");
		break;
		
		case "LFD_Church_1_3":
			dialog.text = "Ja, dieser Brief scheint viele Stürme und Unwetter überstanden zu haben, bevor er zu dir gelangte. Wer weiß, was darin steht und welche Folgen seine Lektüre haben wird... Aber ihr handelt ehrenhaft, Kapitän, indem ihr ihn der Empfängerin zurückgebt. Wenn jemand weiß, wo sich Marisa derzeit aufhält, dann ist es ihre Freundin Dolores Monjo – die Einzige, der sie vertrauen konnte\nIhr Haus befindet sich links vom Hafenamt. Ich hoffe, dieser Brief bringt Marisa kein neues Leid, denn Prüfungen hatte sie wahrlich genug.";
			link.l1 = "Ich danke Ihnen, heiliger Vater. Gott schütze Sie.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;
		
		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
