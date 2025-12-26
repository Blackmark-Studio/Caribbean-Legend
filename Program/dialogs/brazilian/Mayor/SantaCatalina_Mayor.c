// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que deseja? Pode perguntar.","Estou ouvindo, qual é a pergunta?"),"Esta é a segunda vez que você tenta perguntar...","Esta é a terceira vez que você tenta perguntar...","Quando isso vai acabar?! Sou um homem ocupado, cuidando dos assuntos da colônia, e você ainda está me importunando!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, desculpe.","Agora não. Lugar e momento errados."),"É verdade, não tenho nada a dizer agora, desculpe.","Vou perguntar depois.","Me desculpe, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Você já levou tudo. O que mais você quer?","Ficou alguma coisa que você ainda não pegou?");
            link.l1 = RandPhraseSimple("Só estou dando uma olhada...","Só estou conferindo, talvez eu tenha esquecido de pegar alguma coisa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
