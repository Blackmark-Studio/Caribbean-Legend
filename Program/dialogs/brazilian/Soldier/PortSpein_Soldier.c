// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem para um soldado?","O soldado já tem a vida toda planejada - vigiar, correr atrás... Em que posso ajudar, "+GetAddress_Form(NPChar)+"?"),"Você não devia incomodar um soldado com perguntas idiotas, "+GetAddress_Form(NPChar)+"...","Já é a terceira vez hoje que você tenta me fazer uma pergunta...","O destino de um soldado não é fácil, e agora você, seu verme, está me tirando do sério...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Entendi...","É, você tem razão, já é a terceira vez...","Desculpa...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Me diga, o nome Juan significa algo para você?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Não. Só isso?";
			link.l1 = "Sim. Desculpe incomodar você, soldado...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
