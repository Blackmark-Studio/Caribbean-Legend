// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda non molto tempo fa, "+GetAddress_Form(NPChar)+"...","Durante tutto il giorno, questa è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Uh, dove se n'è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Сага
			if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "valet")
			{
				link.l1 = "Cerco un uomo soprannominato Valet. Lo conosci?";
				link.l1.go = "valet_1";
				link.l2 = "Sto cercando il capitano di una polacca chiamata 'Marlin'. Potresti dirmi dove trovarlo?";
				link.l2.go = "valet_2";
			}
		break;
		
		case "valet_1":
			dialog.text = NPCStringReactionRepeat("No, non lo so, amico. Quindi non c'è nulla con cui posso aiutarti.","Ti ho già detto che non lo so!","Sei ubriaco o stai solo scherzando?","Lasciami in pace!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Capisco. Che peccato...","Che peccato. Pensavo ti saresti ricordato...","Sono sobrio! Sono solo persistente...","Mh...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "valet_2":
			dialog.text = NPCStringReactionRepeat("Ah, signor David Fackman! Affitta una casa non lontano dal cantiere navale. Cercalo lì.","Ti ho appena risposto. Come mi hai ascoltato?","Sei ubriaco o stai solo scherzando?","Lasciami in pace!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Grazie!","Sì. Mi dispiace.","Sono sobrio! Sono solo persistente...","Mh...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
