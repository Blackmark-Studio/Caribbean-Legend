// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parla, ti sto ascoltando";
			link.l1 = "Mi sono sbagliato. Addio.";
			link.l1.go = "Exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "Ufficiale, tenete prigioniero qui un uomo chiamato Bartolomeo il Portoghese...";
                link.l1.go = "Portugal";
            }
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Certo. E perché te ne importa? Solo gli inviati della Compagnia Olandese delle Indie Occidentali possono vederlo e solo con l'ordine scritto del governatore. Un ufficiale della Compagnia sta interrogando questo pirata proprio ora. Quindi se sei venuto qui solo per vederlo, sarebbe meglio che te ne andassi, lo vedrai quando verrà impiccato, ora vattene.";
			link.l1 = "Sono venuto qui non per vederlo.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Allora, se posso chiedere, perché?";
			link.l1 = "Sono venuto qui... per liberarlo!";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
