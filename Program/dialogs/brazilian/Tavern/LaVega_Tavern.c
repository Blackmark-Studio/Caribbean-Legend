// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos os boatos sobre "+GetCityName(npchar.city)+" ao seu dispor. O que gostaria de saber?","Estávamos justamente falando sobre isso. Você deve ter esquecido...","Esta é a terceira vez hoje que você faz essa pergunta...","Você está repetindo as mesmas coisas feito um papagaio...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","Sim...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
