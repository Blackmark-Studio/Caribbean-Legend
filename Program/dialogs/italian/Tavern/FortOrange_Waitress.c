// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Domande, "+GetAddress_Form(NPChar)+"?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Mh, qual è la grande idea, "+GetAddress_Form(NPChar)+"? ","Di nuovo con le domande strane? Piccola, vai a bere un po' di rum o qualcosa del genere...")+"","Durante tutto il giorno, questa è la terza volta che parli di qualche domanda..."+GetSexPhrase("Questi sono segni di attenzione?","")+"","Altre domande, presumo, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea","Non ho nulla di cui parlare al momento."),"No, no bella...","Assolutamente no, cara...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "Ascolta donna, dicono che eri vicina al mio vecchio amico Francois Gontier. Molto vicina...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "Ti ho portato la tua collana con gemme. Eccola. Dio mi protegga in futuro da donne avidi come te.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "Niente al momento. Sto cercando la tua collana.";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "Sì, lo eravamo. E allora? Non sono una donna sposata e passo il tempo con chi voglio. Francois è un marinaio molto rispettabile, non come i nostri pescatori e contadini locali. È così... Oh! E mi ha fatto dei regali così carini!";
            link.l1 = "Basta così, è sufficiente! Conosco le qualità del mio compagno, non devi elencarle per me. Non mi importa cosa sia successo tra voi due. Potete anche sposarvi, non mi importa. Devo trovarlo subito, capisci? Sai dove è andato?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "Hi hi... Sei il suo compagno di equipaggio, e non sai dove sia andato. È divertente!";
            link.l1 = "Non c'è niente di divertente, donna. Avevamo concordato di incontrarci in Giamaica e poi ci aspettava un viaggio insieme... se mi capisci. Non potrò farlo da solo e lui è partito per chissà dove!";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "Capisco. Beh, se un viaggio così redditizio è alle porte per te, considerando che tu e Francois siete amici... Ti dirò dove si è diretto, ma in cambio di una piccola ricompensa.";
            link.l1 = "Certo, so come funziona. Quanto vuoi?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "Oh, quanto vile! Non ho bisogno di soldi. No, voglio qualcosa di speciale. Francois ha promesso di darmi una bella collana con gemme. Ne ho già parlato con le mie amiche e lui è sparito... Portami il ciondolo e ti dirò dove è andato, he-he!";
            link.l1 = "Tu impertinente sgualdrina! Voi sgualdrine olandesi siete avidi come non mai! Va bene, avrai la tua collana.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "Ah, è bellissimo! Ora i miei amici potranno diventare verdi d'invidia!";
            link.l1 = "Manda loro le mie condoglianze. Ora comincia a parlare. Dove è partito Francois?";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "Sì, certo, signore. Francois è salpato verso Cuba, a L'Avana.";
            link.l1 = "Grazie per la generosa mancia, donzella. Era tutto quello che volevo.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
