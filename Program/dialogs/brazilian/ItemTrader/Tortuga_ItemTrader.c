// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"De novo com as perguntas, "+GetAddress_Form(NPChar)+"...","Perguntas, perguntas... Que tal fazermos um negócio, "+GetAddress_Form(NPChar)+"hã?","Escute, por quanto tempo você pretende conversar?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sem perguntas por agora...","Desculpe, não tenho nada a dizer agora..."),"Mais uma vez, desculpe...","Talvez realmente seja hora de negociar...","Desculpe, vamos negociar...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
