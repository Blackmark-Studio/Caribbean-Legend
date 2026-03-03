// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais são as suas dúvidas?","Em que posso ajudar?"),"Você tentou me fazer uma pergunta há pouco tempo enquanto estava na loja...","Já é a terceira pergunta hoje. Eu preciso trabalhar, não ficar em conversas sem sentido...","Mais perguntas? Que tal fecharmos um acordo em vez disso?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Sim, é isso mesmo. Eu tentei... enquanto estava na loja...","Sim, é a terceira pergunta...","Hm, talvez possamos fazer um acordo...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;				
	}
	UnloadSegment(NPChar.FileDialog2);
}
