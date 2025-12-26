// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já trouxe essa questão pela terceira vez hoje...","Olha, se você não tem nada pra me contar sobre os assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não estou interessado nos assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";

			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "Quero saber sobre a barca que desapareceu depois da revolta dos escravizados.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//Голландский гамбит, против всех
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
            {
    			link.l1 = "Quero encontrar um capitão chamado Toff Keller. Ele é dono de um fluyt chamado 'Leiden'. Disseram-me que ele costuma visitar Willemstad, então não deve ser difícil você me ajudar.";
    			link.l1.go = "SeekTradeFleut";
            }
		break;

		//работорговец
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "Hm... E por que isso te interessa? Negros são a sua especialidade?";
				link.l1 = "Estou aqui por ordem de Mathias Beck, o governador. Tenho todos os motivos para suspeitar que os negros fugitivos roubaram aquele navio e fugiram com ele. Por isso, peço que me ajude de todas as formas possíveis na minha busca.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "Entendo. Bem, não posso te ajudar. O barco '"+pchar.questTemp.Slavetrader.ShipName+"' sumiu antes do amanhecer, ninguém viu nada. Eu estava em casa dormindo. O vigia do cais também desapareceu e não deixou rastro.\nO governador mandou uma escuna para tentar perseguir enquanto ainda havia pistas, mas voltaram de mãos vazias. Nenhum sinal dos negros ou do '"+pchar.questTemp.Slavetrader.ShipName+"Para ser sincero, a escuna nem procurou muito por eles, todo mundo ainda estava em pânico e achava que os cafres iam sair da selva aos montes com forcados e facões – sedentos por sangue branco.";
				link.l1 = "Isso não ajudou muito, mas obrigado mesmo assim. Adeus.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;				
		//Голландский гамбит
		case "SeekTradeFleut":
			DelLandQuestMark(npchar);
			dialog.text = "Toff Keller? Claro, eu conheço ele! Ele costuma navegar para San Jose, que fica em Trinidad, e para Cumana. Ele esteve em Trinidad recentemente. Acho que você pode encontrá-lo por lá.";
			link.l1 = "Obrigado!";
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
