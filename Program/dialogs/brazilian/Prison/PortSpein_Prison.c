// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Fale, estou ouvindo";
			link.l1 = "Eu estava enganado. Adeus.";
			link.l1.go = "Exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Fui informado de que há uma epidemia aqui, estou certo?";
				link.l1.go = "Consumption";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Está certo, então evite visitar as masmorras sem um bom motivo. Por que esse interesse?";
			link.l1 = "Só por curiosidade. Então se meus rapazes ficarem bêbados demais, fizerem muito barulho e acabarem aqui, devo preparar uns lençóis amarelos então?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Infelizmente, senhor, não entendi a piada, caso tenha sido uma. As masmorras são úmidas e frias, como o clima daqui. A tuberculose é uma visitante frequente nesses calabouços. Eu até preciso pagar um extra aos meus homens para levarem comida às celas. Patrulhar lá é considerado tão ruim quanto trabalho forçado.";
			link.l1 = "Desculpe, só queria saber o quão grave é isso?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Far too serious. We don't even have a physician here; he died of the damn consumption too. Now only a medic from the local garrison examines prisoners once a week. But who cares about these tramps and criminals?\nMost folks think they fully deserved such a fate, and it's hard to argue with that.";
			link.l1 = "Meu conhecimento de medicina é modesto, mas pelo que sei, a tuberculose é perigosa e mortal, só que não mata as pessoas em poucos dias como acontece aqui. As vítimas não deveriam sofrer por meses ou até anos?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Como você mesmo disse, não é médico, então falar sobre as características da doença pode ser só... uma mentira inventada. Só repeti o que nosso médico vinha dizendo antes da doença levá-lo também. Então não entendo sua curiosidade e esse comportamento cínico. As pessoas morrem aqui!";
			link.l1 = "Você não acabou de dizer que eles mereceram isso?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Basta, señor! Acho que você e eu temos assuntos mais importantes a tratar do que ficar competindo em esperteza. A porta está logo atrás de você.";
			link.l1 = "Certo, perdoe minha falta de tato, já estou indo embora.";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
