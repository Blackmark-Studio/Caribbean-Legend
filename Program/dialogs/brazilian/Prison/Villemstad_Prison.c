// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Fale, estou ouvindo";
			link.l1 = "Eu estava enganado. Adeus.";
			link.l1.go = "Exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "Oficial, você está mantendo aqui um prisioneiro chamado Bartolomeo, o Português...";
                link.l1.go = "Portugal";
            }
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Temos sim. E por que você se importa? Só enviados da Companhia Holandesa das Índias Ocidentais podem vê-lo, e apenas com ordem escrita do governador. Um dos oficiais da Companhia está interrogando esse pirata agora mesmo. Então, se você veio só para vê-lo, é melhor ir embora. Você vai vê-lo quando ele for enforcado. Agora vá embora.";
			link.l1 = "Não vim aqui para vê-lo.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Por que, então, se me permite perguntar?";
			link.l1 = "Eu vim aqui... para libertá-lo!";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
