// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda non molto tempo fa, "+GetAddress_Form(NPChar)+"...","Durante l'intera giornata, è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho niente di cui parlare al momento."),"Uh, dove se n'è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Ascolta, hai visto un corsaro di nome Francois Gontier? È stato qui recentemente nella tua città.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Ascolta, sapresti dirmi dove trovare un mercante di nome Jaime Silicio? Doveva venire a trovarti...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Guarda, sto cercando un uomo di nome Bertrand Pinette, ne hai sentito parlare? È arrivato a Portobello non molto tempo fa. Un signore imponente con una parrucca riccia. Un commerciante. Potrebbe essere stato qui...";
                link.l1.go = "FMQG";
            }
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("No, non lo so. Non si è fermato alla taverna e non l'ho visto in città neanche.","Hai già chiesto di questo e ti ho risposto.","Ti ho detto 'hai già chiesto di quel Gontier'.","Ascolta, vattene e smetti di infastidirmi! Hai completamente perso la testa?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ebbene, continuerò a cercare.","Mm, suppongo di sì...","Sì, giusto, l'ho chiesto...","Scusa, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "Perdonami, signore, ma solo un traditore o un ubriacone discuterebbe di tali questioni con uno sconosciuto. Non voglio problemi.";
			link.l1 = "Un ubriacone, dici? Ci vediamo in giro, amico.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Mai sentito parlare di lui, amico.";
			link.l1 = "È un conoscente di don Carlos de Milyar. Sei sicuro di non aver mai sentito parlare di lui?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Lo sono. Se è un amico di de Milyar - vai dal governatore e chiedi del signor Carlos. Ti parlerà di questo tuo mercante.";
			link.l1 = "Lo farò. Grazie per il consiglio!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
