// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que você quer?","O que você gostaria de saber?"),"O que você precisa, "+GetAddress_Form(NPChar)+"?","Essa já é a terceira vez que você tenta me perguntar...","Já cansei de você, suma daqui!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Desculpe, mudei de ideia.","Não foi nada, me desculpe."),"Esqueci, me desculpe...","Terceira vez é a certa, né? Com licença...","Desculpa, desculpa! Eu já estou de saída então...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
