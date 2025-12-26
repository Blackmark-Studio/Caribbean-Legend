// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Pode falar, o que você quer?","Acabamos de falar sobre isso. Você deve ter esquecido...","É a terceira vez hoje que você faz essa pergunta...","Olha, aqui é uma loja. As pessoas vêm comprar coisas. Não me atrapalhe!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","Hm, eu não vou...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
