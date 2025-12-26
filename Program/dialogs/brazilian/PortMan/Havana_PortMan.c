// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já trouxe essa questão pela terceira vez hoje...","Olha, se você não tem nada para me contar sobre os assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não estou interessado nos assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Bom dia para você. Gostaria de saber sobre uma corveta chamada '"+pchar.questTemp.Slavetrader.ShipName+"' sob o comando de François Gontier.";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Com licença, chegou ao seu porto um homem chamado Joachim Merriman? Um senhor de meia-idade, português, com bigode, barba imperial e olhar penetrante?";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "Estou interessado em um navio chamado 'Cantavro'. Estou procurando o capitão dele, Esberdo Cabanas, por um assunto particular. Você poderia me ajudar?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Sim, ele esteve aqui. Mas já foi embora. Pergunte ao nosso taverneiro sobre ele, ele alugou um quarto no andar de cima.","Você já perguntou sobre isso e eu já respondi.","Eu já te disse, você já perguntou sobre esse Gontier..","Peço que não me incomode!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Obrigado. Vou fazer isso.","Hm, bem ...","Sim, eu realmente pedi ...","Com licença, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Não posso te dizer nada sobre ele. Mesmo que tenha chegado, nunca se registrou em lugar nenhum.";
			link.l1 = "Entendo. Que pena... Tudo bem, vou continuar minha busca...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "Let's see... the schooner 'Cantavro' set sail two days ago on patrol... however, the location is not listed. It is a military vessel, so the destination is known only to its captain and the fort commandant. I would suggest you speak with the commandant directly; you can find him at the fort if you wish to know more. Unfortunately, that is all I can do for you.";
			link.l1 = "Entendi. Bem, obrigado pelo seu tempo...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
