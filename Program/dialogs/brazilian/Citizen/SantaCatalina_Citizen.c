// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que você quer?");
			link.l1 = RandPhraseSimple("Mudei de ideia.'","Não tenho nada a dizer agora.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Em quem você está interessado?","De quem você está falando?","Bem, quem é?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Quero saber mais sobre Jan Svenson.";
				link.l1.go = "svenson";
			}
			link.l2 = "Vamos mudar de assunto...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Para onde você quer ir?","O que você está procurando?","O que exatamente você precisa?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Onde fica a casa do Jan Svenson?";
				link.l1.go = "svenson_house";
			}
			link.l2 = "Vamos mudar de assunto...";
			link.l2.go = "new question";
		break;
		
		case "svenson":
			dialog.text = RandPhraseSimple("Oh, nosso Jan Svenson é uma pessoa muito importante. No passado, ele foi o pirata mais ousado do Caribe Ocidental e, mesmo agora, ainda não perdeu o brilho, ha! Mas aqueles tempos já passaram, ele não é mais tão ativo quanto antes. Ele tem uma mansão e mora lá com sua jovem esposa, e está sempre entre os convidados bem-vindos na residência do governador. Muitos visitantes vão até Jan, na maioria piratas.","Jan Svenson é uma lenda do Oeste! Diabo da Floresta, era assim que os espanhóis o chamavam quando ele os expulsava daqui. Ele já foi um corsário famoso, mas agora é um cidadão respeitado da nossa colônia.\nEmbora ainda faça alguns 'negócios' por fora, não é mais ele quem põe a mão na massa. Desde que se casou com uma jovem bela, raramente sai de casa.");
			link.l1 = "Meu agradecimento.";
			link.l1.go = "exit";
		break;
		
		case "svenson_house":
			dialog.text = RandPhraseSimple("Siga em frente do cais até chegar à praça, a casa à direita perto da fonte é a mansão do Svenson.","Vá para o píer passando pela praça a partir da residência do governador, a casa à esquerda perto da fonte é a mansão do Svenson.");
			link.l1 = "Meu obrigado.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
