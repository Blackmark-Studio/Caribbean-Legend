// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Hai parlato della stessa questione per la terza volta oggi...","Guarda, se non hai niente da dirmi riguardo agli affari del porto, allora non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Mai mente.","Certo, già la terza volta...","Mi dispiace, ma per ora non mi interessano gli affari del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";

			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "Vorrei sapere della barca che è scomparsa dopo la rivolta degli schiavi.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//Голландский гамбит, против всех
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
            {
    			link.l1 = "Voglio trovare un capitano di nome Toff Keller. Possiede un fluyt chiamato 'Leiden'. Mi è stato detto che visita spesso Willemstad quindi non sarà difficile per te aiutarmi.";
    			link.l1.go = "SeekTradeFleut";
            }
		break;

		//работорговец
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "Hm... E perché sei interessato? I negri sono la tua specialità?";
				link.l1 = "Sono qui per ordine di Mathias Beck, il governatore. Ho tutte le ragioni per sospettare che i negri fuggiti abbiano rubato quella nave e se ne siano andati con essa. Quindi ti chiedo di aiutarmi in ogni modo possibile nella mia ricerca.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "Capisco. Beh, non posso aiutarti. La barca '"+pchar.questTemp.Slavetrader.ShipName+"' era sparito entro la mattina, nessuno ha visto niente. Ero a casa a dormire. Anche il guardiano del molo è sparito e non ha lasciato traccia.\nIl governatore ha inviato una scialuppa per cercare di inseguirlo mentre la pista era ancora calda, ma sono tornati a mani vuote. Nessun segno dei negri o del '"+pchar.questTemp.Slavetrader.ShipName+"'. Ad essere onesti, la scialuppa non ha cercato troppo attentamente, tutti erano ancora nel panico e pensavano che i kafiri sarebbero usciti bollenti dalla giungla con forconi e machete - affamati di sangue bianco.";
				link.l1 = "Non è stato molto utile, ma grazie comunque. Addio.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;				
		//Голландский гамбит
		case "SeekTradeFleut":
			DelLandQuestMark(npchar);
			dialog.text = "Toff Keller? Certo che lo conosco! Fa regolarmente viaggi per San Jose, che si trova a Trinidad, e Cumana. Di recente ha navigato verso Trinidad. Suppongo che tu possa trovarlo lì.";
			link.l1 = "Grazie!";
			link.l1.go = "SeekTradeFleut_1";
		break;
		
		case "SeekTradeFleut_1":
			DialogExit();
			AddMapQuestMarkIsland("Trinidad", true);
			pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
			AddQuestRecord("Holl_Gambit", "3-59");
			pchar.quest.Seek_Fleut.win_condition.l1 = "location";
			pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
			pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
