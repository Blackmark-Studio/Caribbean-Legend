// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudar você?"),"Você tentou me fazer essa pergunta não faz muito tempo...","É, deixa eu adivinhar... Dando voltas de novo?","Escute, eu cuido das finanças aqui, não respondo perguntas...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ufa, onde foi parar minha memória...","Você adivinhou, me desculpe...","Entendi...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// Реакция ростовщика Панамы на репутацию ГГ или на разграбление Картахены по сюжету
		case "Panama_Deposit_NoReputation":
			dialog.text = "Isso mesmo... Um homem de honra, respeitado pelos súditos do Rei, nunca será recusado pelo meu banco, não importa sua nacionalidade.";
			link.l1 = "Entendi. Adeus.";
			link.l1.go = "exit";
		break;
		
		case "Panama_Deposit_Cartahena":
			dialog.text = "Mas minha filha e meu sogro pegaram, infelizmente. Eles moravam em Cartagena. Vá embora, "+GetAddress_Form(NPChar)+". Você não é bem-vindo aqui.";
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "Me perdoe. Adeus.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Sua perda. Adeus.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
		
		case "Panama_Deposit_SgorelVklad":
			dialog.text = "Os fundos foram confiscados pela Coroa para ajudar as vítimas do saque à cidade de Cartagena. Não posso ajudá-lo. Vou pedir que saia do meu banco imediatamente antes que eu chame os guardas!";
			link.l1 = "Você vai se arrepender disso...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
