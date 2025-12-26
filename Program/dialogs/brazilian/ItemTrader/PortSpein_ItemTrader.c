// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Perguntas de novo, "+GetAddress_Form(NPChar)+"...","Perguntas, perguntas... Que tal fazermos um negócio, "+GetAddress_Form(NPChar)+"hã?","Escuta, até quando você pretende conversar?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sem perguntas por enquanto...","Desculpe, não tenho nada a dizer agora..."),"Mais uma vez, desculpe...","Talvez realmente seja hora de negociar...","Desculpe, vamos negociar...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Escuta, o nome 'Juan' te diz alguma coisa?";
				link.l1.go = "Consumption";
			}			
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Não, não tem nada a ver... Agora, por favor, não me incomode, estou muito ocupado... Que pergunta idiota...";
			link.l1 = "Entendi. Desculpe por tomar seu tempo...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
