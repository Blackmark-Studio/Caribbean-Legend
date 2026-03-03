// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos os boatos sobre "+GetCityName(npchar.city)+" ao seu dispor. O que gostaria de saber?","Estávamos justamente falando sobre isso. Você deve ter esquecido...","Esta já é a terceira vez que você me incomoda...","Você está repetindo as mesmas coisas feito um papagaio...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","É...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && !CheckAttribute(npchar, "quest.gonsales"))
			{
				link.l1 = "Estou procurando por Enrique Gonzales. Você poderia me dizer como encontrá-lo?";
				link.l1.go = "saga";				
			}
		break;
			
		case "saga":
			dialog.text = "Todo mundo conhece o Señor Gonzales! A casa dele fica ao lado da capitania do porto.";
			link.l1 = "Quantos anos ele tem?";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Olha, não posso afirmar com certeza, mas ele parece ter pelo menos cinquenta anos. Já mora naquela casa faz um bom tempo. Adora contar todo tipo de história mirabolante sobre piratas que provavelmente só conheceu nos sonhos dele.";
			link.l1 = "Parece que ele é o homem que eu preciso. Obrigado, "+npchar.name+", você foi de grande ajuda!";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			DialogExit();
			npchar.quest.gonsales = "true";
			pchar.questTemp.Saga.Gonsales = "true";
			pchar.quest.Saga_Gonsales1.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales1.win_condition.l1.location = "Cartahena_houseF2";
			pchar.quest.Saga_Gonsales1.function = "Saga_CreateGonsalesA";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
