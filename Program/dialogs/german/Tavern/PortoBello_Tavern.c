// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),"Du hast versucht, mir vor kurzem eine Frage zu stellen, "+GetAddress_Form(NPChar)+"..., Freund.","Den ganzen Tag über ist dies das dritte Mal, dass du von irgendeiner Frage sprichst...","Noch mehr Fragen, nehme ich an?","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt...","Ich habe im Moment nichts zu besprechen."),"Humph, wo ist mein Gedächtnis hin...","Ja, es ist wirklich das dritte Mal...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Hör zu, hast du einen Freibeuter namens Francois Gontier gesehen? Er war vor kurzem hier in deiner Stadt.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Hör zu, könntest du mir sagen, wo ich einen Händler namens Jaime Silicio finden kann? Er sollte dich besuchen kommen...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Schau, ich suche einen Mann namens Bertrand Pinette, hast du von ihm gehört? Er kam vor kurzem nach Portobello. Ein eindrucksvoller Herr mit einer lockigen Perücke. Ein Händler. Er könnte hier gewesen sein...";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "Kannst du mir sagen, wo ich Marisa Caldera finden kann?";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("Nein, ich weiß es nicht. Er hat die Taverne nicht besucht und ich habe ihn auch nicht in der Stadt gesehen.","Du hast bereits danach gefragt und ich habe dir geantwortet.","Ich habe dir gesagt 'du hast schon nach diesem Gontier gefragt'.","Hör zu, geh weg und hör auf, mich zu belästigen! Hast du völlig den Verstand verloren?","Block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nun, dann werde ich weiter suchen.","Hm, ich denke schon...","Ja, stimmt, das habe ich gefragt...","Entschuldigung, "+npchar.name+"..., Freund.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "Verzeihen Sie mir, senor, aber nur ein Verräter oder ein Betrunkener würde solche Angelegenheiten mit einem Fremden besprechen. Ich will keinen Ärger.";
			link.l1 = "Ein Betrunkener, sagst du? Wir sehen uns, Kumpel.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Noch nie von ihm gehört, Kumpel.";
			link.l1 = "Er ist ein Bekannter von Don Carlos de Milyar. Bist du sicher, dass du noch nie von ihm gehört hast?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Ich bin es. Wenn er ein Freund von de Milyar ist - geh zum Gouverneur und frag nach Senor Carlos. Er wird dir von diesem Händler von dir erzählen.";
			link.l1 = "Ich werde das tun. Danke für den Rat!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "Marisa? Hm... Ich habe sie schon lange nicht mehr gesehen. Seit sie vom Tod ihres Mannes erfahren hat, zeigt sie sich nicht mehr in der Stadt.";
			link.l1 = "Also ist sie eine Witwe?";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Tavern_1_2":
			dialog.text = "Ja. Ihr Mann war Kapitän des Handelspinas 'Wellenbrecher'. Dank einer Lizenz der Niederländischen Westindien-Kompanie standen ihm fast alle Häfen des Archipels offen. Man sagt, er überlebte einen Piratenüberfall auf dem Weg von Belize nach Capsterville nicht. So etwas ist hier nicht ungewöhnlich, aber für sie war es ein harter Schlag.";
			link.l1 = "Und sie ist einfach verschwunden?";
			link.l1.go = "LFD_Tavern_1_3";
		break;
		
		case "LFD_Tavern_1_3":
			dialog.text = "Na ja, verschwunden ist vielleicht zu viel gesagt. Aber seitdem sieht man sie kaum noch in der Stadt. Seltsam ist nur... von Zeit zu Zeit fragen verschiedene Männer nach ihr. So wie Ihr, Kapitän. Wäre sie nicht so fromm gewesen, hätte ich gedacht, sie hätte sich zurückgezogen und verdient ihr Geld... auf andere Weise. Doch Marisa hat vor dem Tod ihres Mannes keine einzige Heilige Messe verpasst – sie hat praktisch in der Kirche gelebt. Also wohl kaum.";
			link.l1 = "Das ist alles? Weißt du sonst nichts?";
			link.l1.go = "LFD_Tavern_1_4";
		break;
		
		case "LFD_Tavern_1_4":
			dialog.text = "Alles, was ich weiß, habe ich Euch bereits erzählt, Kapitän.";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;
		
		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
