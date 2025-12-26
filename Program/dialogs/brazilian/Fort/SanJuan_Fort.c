// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que acha do nosso forte? Está bonito, não acha? E a guarnição não fica atrás, ha...","A vida de um soldado de forte é bem monótona... Vigiar e patrulhar, dormir e descansar, e depois tudo de novo. Mas na cidade é diferente... O que você quer, "+GetAddress_Form(NPChar)+"?"),"Não é bem-vindo incomodar um soldado com perguntas tolas, "+GetAddress_Form(NPChar)+"...","É a terceira vez que você tenta me perguntar isso hoje...","Não é fácil ser soldado, e mesmo assim aqui está você de novo"+GetSexPhrase(", idiota,  "," ")+" tentando me irritar. Cuidado ou vai acabar no porão do forte...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, desculpe incomodar.","Não tenho nada a dizer, desculpe."),"Você tem razão, me desculpe.","Você tem razão, já é a terceira vez. Me desculpe.","Desculpe, não é nada.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
