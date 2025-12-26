// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que você quer?");
			link.l1 = RandPhraseSimple("Mudei de ideia.'","Não tenho nada a dizer agora.");
		    link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Me diga, o nome 'Juan' te soa familiar?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Escute, amigo, uma fragata sob o comando de Miguel Dichoso atracou aqui no porto em abril de 1654. Ele desapareceu naquele dia. Você se lembra de algo sobre isso?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Você acha que eu trabalho para o serviço secreto de "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Bem... não. Então, até logo.";
			link.l1.go = "exit";
			link.l2 = "Mais alguma pergunta, então?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Por acaso eu pareço algum tipo de investigador? Não sei, não faço ideia.";

            link.l1 = "Você é mesmo um cabeça de vento! Cai fora.";
			link.l1.go = "exit";
			link.l2 = "Mais alguma pergunta, então?";
			link.l2.go = "new question";
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Você está brincando comigo? Tem uns vinte Juans em cada colônia!";
			link.l1 = "Entendi. Desculpe incomodar você...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Ah, capitão! Você acha mesmo que eu lembro dessas coisas?","Me perdoe, senhor, não posso ajudá-lo com isso.","Senhor, você acha mesmo que eu vou lembrar de uma bobagem dessas? Já tenho problemas demais.");
			link.l1 = LinkRandPhrase("Entendi. Desculpe incomodar você...","Que pena. Adeus.","Certo, até logo...");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
