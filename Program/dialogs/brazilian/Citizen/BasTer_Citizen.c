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
			link.l1 = "Quero saber mais sobre Fadey, o Moscovita.";
			link.l1.go = "fadey";
			link.l2 = "Ninguém, esquece isso.";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Para onde você quer ir?","O que você está procurando?","O que exatamente você precisa?");
            link.l1 = "Onde fica a casa do Fadey?";
			link.l1.go = "fadey_house";
			link.l2 = "Vamos falar de outra coisa...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("Ah, um homem importante. Ele é dono da fábrica local e tem boas relações com a alta sociedade de Basse-Terre. Fala com um sotaque forte e gosta muito de beber... mas nunca fica bêbado.","Ele é um figurão e amigo do governador. Fadey é dono de uma fábrica aqui na cidade. Ele veio de um país do norte, bem distante daqui... Nem sei o nome desse lugar. Tem mãos fortes e consegue beber um barril inteiro de rum sem ficar bêbado.");
			link.l1 = "Meu obrigado.";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("Siga em frente a partir do píer até chegar à praça, a casa à esquerda é a mansão do Fadey.","Vá até o píer passando pela praça a partir da residência do governador, a casa à direita é a mansão do Fadey.");
			link.l1 = "Meu agradecimento.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
