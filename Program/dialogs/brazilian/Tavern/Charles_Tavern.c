// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco, "+GetAddress_Form(NPChar)+"...","Durante todo este dia, esta é a terceira vez que você faz essa pergunta...","Mais perguntas, imagino?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Sim, realmente é a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Сага
			if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "valet")
			{
				link.l1 = "Estou procurando por um homem chamado Valet. Você o conhece?";
				link.l1.go = "valet_1";
				link.l2 = "Estou procurando o capitão de uma polaca chamada 'Marlin'. Você poderia me dizer onde posso encontrá-lo?";
				link.l2.go = "valet_2";
			}
		break;
		
		case "valet_1":
			dialog.text = NPCStringReactionRepeat("Não, eu não sei. Então não tem nada com que eu possa te ajudar.","Já te disse que eu não sei!","Você está bêbado ou só está fazendo graça?","Me deixe em paz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Entendi. Que pena...","Que pena. Achei que você fosse se lembrar...","Estou sóbrio! Só sou persistente...","Hm...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "valet_2":
			dialog.text = NPCStringReactionRepeat("Ah, Sr. David Fackman! Ele aluga uma casa não muito longe do estaleiro. Procure por ele lá.","Eu acabei de te responder. Você estava me ouvindo mesmo?","Você está bêbado ou só está de brincadeira?","Me deixe em paz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Obrigado!","Sim. Me desculpe.","Estou sóbrio! Só sou persistente...","Hm...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
