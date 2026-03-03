// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já fez essa pergunta pela terceira vez hoje...","Olha, se você não tem nada para me contar sobre os assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não estou interessado nos assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Me diga, o nome 'Juan' significa algo para você?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Senhor, houve uma fragata aqui sob o comando de Miguel Dichoso em abril de 1654. Ele desapareceu naquela época. Não se lembra de nada sobre isso? Talvez Dichoso tenha passado por aqui e registrado seu navio...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Juan? Só isso? Señor, o senhor está bêbado ou está fazendo uma piada sem graça comigo? Consegue lembrar o sobrenome dele ou pelo menos o nome do navio? Esta é uma colônia espanhola, pelo amor de Deus. Sabe quantos Juans temos por aqui? Não vou conseguir te ajudar sem mais detalhes.";
			link.l1 = "Entendi. Desculpe incomodar...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Deixe-me ver minhas anotações... ah, sim! O Capitão Miguel Dichoso esteve aqui em abril de 1654, na fragata 'Santa-Quiteria'. Ele se registrou como vindo da colônia de San-Andres, Providence. Estava indo para Cádis, na Espanha. Partiu em 14 de abril de 1654. É tudo o que tenho.";
			link.l1 = "Viajando para a Europa? Entendi. Obrigado por avisar!";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
